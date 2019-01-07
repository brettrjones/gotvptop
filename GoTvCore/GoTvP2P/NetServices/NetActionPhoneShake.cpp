//============================================================================
// Copyright (C) 2014 Brett R. Jones
// Issued to MIT style license by Brett R. Jones in 2017
//
// You may use, copy, modify, merge, publish, distribute, sub-license, and/or sell this software
// provided this Copyright is not modified or removed and is included all copies or substantial portions of the Software
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// brett.jones@engineer.com
// http://www.gotvptop.net
//============================================================================

#include "NetActionPhoneShake.h"
#include "NetServicesMgr.h"
#include "NetServiceHdr.h"

#include <GoTvCore/GoTvP2P/Anchor/AnchorList.h>
#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>

#include <CoreLib/VxGlobals.h>
#include <CoreLib/VxParse.h>
#include <CoreLib/VxCrypto.h>
#include <PktLib/PktAnnounce.h>

#include <string.h>
#include <stdarg.h>
#include <stdio.h>

//============================================================================
NetActionPhoneShake::NetActionPhoneShake( NetServicesMgr& netServicesMgr, std::string& anchorIp, uint16_t u16AnchorPort, EAnchorAction eAnchorAction )
: NetActionBase( netServicesMgr )
, m_eAnchorAction( eAnchorAction )
, m_FoundCnt( 0 )
{
}

//============================================================================
NetActionPhoneShake::~NetActionPhoneShake()
{
}

//============================================================================
void NetActionPhoneShake::doAction( void )
{
	if( m_Engine.getEngineSettings().getIsThisNodeAnAnchor() )
	{
		// we are the anchor
		// put ourself directly into the database
		AnchorList			anchorListIn;
		AnchorList			anchorListOut;
		anchorListIn.addEntry( &m_Engine.getMyPktAnnounce() );
		anchorListIn.m_AnchorAction = eAnchorActionPhoneShake;

		m_NetServicesMgr.getNetServiceAnchor().getAnchorDb().handleAnnounce( anchorListIn, anchorListOut );
		m_NetServicesMgr.netActionResultPhoneShake( eAppErrNone, &anchorListOut );
		return;
	}

	VxSktConnectSimple netServConn;
	if( false == m_NetServicesMgr.actionReqConnectToAnchor( netServConn ) )
	{
		m_NetServicesMgr.netActionResultPhoneShake( eAppErrFailedConnectAnchor, 0 );
		sendPhoneShakeStatus( ePhoneShakeStatusContactAnchorFail, "Could not connect to Anchor\n" );
		return;
	}

	m_FoundCnt = 0;
	if( doPhoneShakeAction( netServConn, 1 ) )
	{
		VxSleep( 10000 );
		if( false == m_NetServicesMgr.actionReqConnectToAnchor( netServConn ) )
		{
			m_NetServicesMgr.netActionResultPhoneShake( eAppErrFailedConnectAnchor, 0 );
			sendPhoneShakeStatus( ePhoneShakeStatusContactAnchorFail, "Could not connect to Anchor\n" );
			return;
		}

		if( doPhoneShakeAction( netServConn, 2 ) )
		{
			VxSleep( 10000 );
			if( false == m_NetServicesMgr.actionReqConnectToAnchor( netServConn ) )
			{
				m_NetServicesMgr.netActionResultPhoneShake( eAppErrFailedConnectAnchor, 0 );
				sendPhoneShakeStatus( ePhoneShakeStatusContactAnchorFail, "Could not connect to Anchor\n" );
				return;
			}

			doPhoneShakeAction( netServConn, 3 );
		}
	}

	sendPhoneShakeStatus( ePhoneShakeStatusSearchComplete, "Phone Shake: search complete %d found\n", m_FoundCnt );
}

//============================================================================
bool NetActionPhoneShake::doPhoneShakeAction( VxSktConnectSimple& netServConn, int tryCnt )
{

	std::string strNetCmdHdr;
	AnchorList anchorList;
	uint16_t cryptoPort = netServConn.getRemotePort();
    buildAnnounceCmd( strNetCmdHdr, cryptoPort, anchorList, eAnchorActionPhoneShake );
	int anchorDataLen = anchorList.m_TotalLen;

	RCODE rc = netServConn.sendData( strNetCmdHdr.c_str(), strNetCmdHdr.length() );
	if( rc )
	{
		netServConn.closeSkt();
		LogMsg( LOG_ERROR, "NetActionPhoneShake::doAction: send header error %d\n", rc );
		m_NetServicesMgr.netActionResultPhoneShake( eAppErrTxError, 0 );
		sendPhoneShakeStatus( ePhoneShakeStatusSendRequestFail, "Phone Shake: send anchor header error %d\n", rc );
		return false;
	}

	VxKey cryptKey;
	m_NetServiceUtils.generateNetServiceCryptoKey( cryptKey, cryptoPort );
	VxSymEncrypt( &cryptKey, (char *)&anchorList, anchorDataLen );

	rc = netServConn.sendData( (char *)&anchorList, anchorDataLen );
	if( rc )
	{
		netServConn.closeSkt();
		LogMsg( LOG_ERROR, "NetActionPhoneShake::doAction: send anchor list error %d\n", rc );
		m_NetServicesMgr.netActionResultPhoneShake( eAppErrTxError, 0 );
		sendPhoneShakeStatus( ePhoneShakeStatusSendRequestFail, "Phone Shake: send anchor list error %d\n", rc );
		return false;
	}

	NetServiceHdr netServiceHdr;
	char rxBuf[4096 * 4];
    if( false == m_NetServiceUtils.rxNetServiceCmd( &netServConn, rxBuf, sizeof( rxBuf ), netServiceHdr, PHONE_SHAKE_RX_TIMEOUT, PHONE_SHAKE_RX_TIMEOUT ) )
	{
		netServConn.closeSkt();
		m_NetServicesMgr.netActionResultPhoneShake( eAppErrRxError, 0 );
		sendPhoneShakeStatus( ePhoneShakeStatusInvalidResponse, "Phone Shake: Invalid Anchor Response\n" );
		return false;
	}

	if( false == decryptAnchorList( rxBuf, netServiceHdr.m_ContentDataLen, cryptoPort ) )
	{
		netServConn.closeSkt();
		m_NetServicesMgr.netActionResultPhoneShake( eAppErrRxError, 0 );
		sendPhoneShakeStatus( ePhoneShakeStatusDecryptError, "Phone Shake: decrypt error \n" );
		return false;
	}

	netServConn.closeSkt();
	AnchorList * anchorListResult;
	anchorListResult = (AnchorList *)rxBuf;
	if( 0 == anchorListResult->m_EntryCount )
	{
		if( tryCnt > 2 )
		{
			sendPhoneShakeStatus( ePhoneShakeStatusEmptyList, "Phone Shake: empty search list \n" );
		}
	}
	else
	{
		m_FoundCnt = anchorListResult->m_EntryCount;
	}

	m_NetServicesMgr.netActionResultPhoneShake( eAppErrNone, anchorListResult );
	return true;
}

//============================================================================
bool NetActionPhoneShake::decryptAnchorList( char * content, int contentDataLen, uint16_t clientPort )
{
	if( false == m_NetServiceUtils.decryptNetServiceContent( content, contentDataLen, clientPort ) )
	{
		return 0;
	}

	AnchorList * anchorList = (AnchorList *)content;
	if( anchorList->m_TotalLen != contentDataLen )
	{
		LogMsg( LOG_ERROR, "NetActionPhoneShake::decryptAnchorList: invalid anchorList->m_TotalLen\n" );
		return false;
	}

    if( MAX_ANCHOR_ENTRIES <= anchorList->m_EntryCount )
	{
		LogMsg( LOG_ERROR, "NetActionPhoneShake::decryptAnchorList: invalid anchorList->m_EntryCount\n" );
		return false;
	}

	return true;
}

//============================================================================
int NetActionPhoneShake::buildAnnounceCmd( std::string& strNetCmdHdr, uint16_t clientPort, AnchorList& anchorList, EAnchorAction anchorAction )
{
	// build Anchor list
	PktAnnounce& pktAnn = m_Engine.getMyPktAnnounce();
	
	anchorList.m_AnchorAction = anchorAction;
	anchorList.addEntry( &pktAnn );
	int listLen = anchorList.calculateLength();

	std::string netServChallengeHash;
	m_NetServiceUtils.generateNetServiceChallengeHash( netServChallengeHash, clientPort );

	return m_NetServiceUtils.buildNetCmdHeader( strNetCmdHdr, eNetCmdAnchorReq, netServChallengeHash, listLen );
}

//============================================================================
int NetActionPhoneShake::getAnnounceData( VxSktConnectSimple * netServConn, char * pRxBuf, int bufLen )
{
	bool bGotCrLfCrLf = false;
	int iMaxToReceive = bufLen - 8;
	int iTotalRxed = 0;
	for( int i = 0; i < 10; ++i )
	{
		int iRxed = 0;
		netServConn->recieveData(		&pRxBuf[ iTotalRxed ],	// data buffer to read into
										iMaxToReceive,			// length of data	
										&iRxed,					// number of bytes actually received
										ANCHOR_RX_DATA_TIMEOUT,	// timeout attempt to receive
										false, 					// if true then abort receive when \r\n\r\n is received
										&bGotCrLfCrLf );						
		if( iRxed <= 0 )
		{
			break;
		}
		pRxBuf[ iTotalRxed + iRxed ] = 0; 
		if( strstr( &pRxBuf[ iTotalRxed ], "Footer" ) )
		{
			iTotalRxed += iRxed;
			break;
		}
		iTotalRxed += iRxed;
		iMaxToReceive -= iRxed;
	}

	pRxBuf[ iTotalRxed ] = 0; 

	return iTotalRxed;
}

//============================================================================
void NetActionPhoneShake::sendPhoneShakeStatus( EPhoneShakeStatus eStatus, const char * msg, ... )
{
	char as8Buf[ 1024 ];
	va_list argList;
	va_start( argList, msg );
	vsnprintf( as8Buf, sizeof( as8Buf ), msg, argList );
	as8Buf[sizeof( as8Buf ) - 1] = 0;
	va_end( argList );
	m_Engine.getToGuiInterface().toGuiPhoneShakeStatus( eStatus, as8Buf );
}
