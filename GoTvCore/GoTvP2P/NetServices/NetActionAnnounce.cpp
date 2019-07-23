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
// bjones.engineer@gmail.com
// http://www.gotvptop.com
//============================================================================

#include "NetActionAnnounce.h"
#include "NetServicesMgr.h"
#include "NetServiceHdr.h"

#include <GoTvCore/GoTvP2P/Anchor/AnchorList.h>
#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>

#include <CoreLib/VxGlobals.h>
#include <CoreLib/VxParse.h>
#include <CoreLib/VxCrypto.h>
#include <PktLib/PktAnnounce.h>

#include <string.h>

//============================================================================
NetActionAnnounce::NetActionAnnounce( NetServicesMgr& netServicesMgr, std::string& anchorIp, uint16_t u16AnchorPort, EAnchorAction eAnchorAction )
: NetActionBase( netServicesMgr )
, m_eAnchorAction( eAnchorAction )
{
}

//============================================================================
NetActionAnnounce::~NetActionAnnounce()
{
}

//============================================================================
void NetActionAnnounce::doAction( void )
{
	if( m_Engine.getEngineSettings().getIsThisNodeAnAnchor() )
	{
		if( m_Engine.getEngineSettings().getExcludeMeFromAnchorList() )
		{
			LogMsg( LOG_INFO, "NetActionAnnounce::doAction ignoring because getExcludeMeFromAnchorList true\n" );
			return;
		}

		LogMsg( LOG_INFO, "NetActionAnnounce::doAction anouncing as anchor\n" );
		// we are the anchor
		AnchorList			anchorListOut;
		AnchorList			anchorListIn;
		// put ourself directly into the database
		anchorListIn.addEntry( &m_Engine.getMyPktAnnounce() );

		m_NetServicesMgr.getNetServiceAnchor().getAnchorDb().handleAnnounce( anchorListIn, anchorListOut );
		m_NetServicesMgr.netActionResultAnnounce( eAppErrNone, &anchorListOut );
		return;
	}

	VxSktConnectSimple netServConn;
	if( false == m_NetServicesMgr.actionReqConnectToAnchor( netServConn ) )
	{
		m_NetServicesMgr.netActionResultAnnounce( eAppErrFailedConnectAnchor, 0 );
		AppErr( eAppErrFailedConnectAnchor, "Anchor Announce: Could not connect to Anchor\n" );
		return;
	}

	std::string strNetCmdHdr;
	AnchorList anchorList;
	uint16_t acceptedPort = netServConn.getRemotePort();
    buildAnnounceCmd( strNetCmdHdr, acceptedPort, anchorList, eAnchorActionAnnounce );
	int anchorDataLen = anchorList.m_TotalLen;

	RCODE rc = netServConn.sendData( strNetCmdHdr.c_str(), (int)strNetCmdHdr.length() );
	if( rc )
	{
		LogMsg( LOG_ERROR, "### ERROR NetActionAnnounce::doAction: send header error %d %s\n", rc, VxDescribeSktError( rc ) );
		m_NetServicesMgr.netActionResultAnnounce( eAppErrTxError, 0 );
		AppErr( eAppErrTxError, "Anchor Announce: send anchor header error %d %s\n", rc, VxDescribeSktError( rc ) );
		netServConn.closeSkt();
		return;
	}

	VxKey cryptKey;
	m_NetServiceUtils.generateNetServiceCryptoKey( cryptKey, acceptedPort );
	VxSymEncrypt( &cryptKey, (char *)&anchorList, anchorDataLen );

	rc = netServConn.sendData( (char *)&anchorList, anchorDataLen );
	if( rc )
	{
		netServConn.closeSkt();
		LogMsg( LOG_ERROR, "### ERROR NetActionAnnounce::doAction: send anchor list error %d %s\n", rc, VxDescribeSktError( rc ) );
		m_NetServicesMgr.netActionResultAnnounce( eAppErrTxError, 0 );
		AppErr( eAppErrTxError, "Anchor Announce: send anchor list error %d %s\n", rc, VxDescribeSktError( rc ) );
		return;
	}

	NetServiceHdr netServiceHdr;
	char rxBuf[4096 * 4];
	if( false == m_NetServiceUtils.rxNetServiceCmd( &netServConn, 
													rxBuf, 
													sizeof( rxBuf ), 
													netServiceHdr,
													ANCHOR_RX_HDR_TIMEOUT,
													ANCHOR_RX_DATA_TIMEOUT ) )
	{
		LogMsg( LOG_ERROR, "### ERROR NetActionAnnounce::rxNetServiceCmd: hdr timout %d data timeout %d\n", ANCHOR_RX_HDR_TIMEOUT, ANCHOR_RX_DATA_TIMEOUT );
		netServConn.closeSkt();
		m_NetServicesMgr.netActionResultAnnounce( eAppErrRxError, 0 );
		AppErr( eAppErrRxError, "Anchor Announce: receive cmd error \n" );
		return;
	}

	if( false == decryptAnchorList( rxBuf, netServiceHdr.m_ContentDataLen, acceptedPort ) )
	{
		netServConn.closeSkt();
		m_NetServicesMgr.netActionResultAnnounce( eAppErrRxError, 0 );
		AppErr( eAppErrRxError, "Anchor Announce: decrypt error \n" );
		return;
	}

	netServConn.closeSkt();
	m_NetServicesMgr.netActionResultAnnounce( eAppErrNone, (AnchorList *)rxBuf );
}

//============================================================================
bool NetActionAnnounce::decryptAnchorList( char * content, int contentDataLen, uint16_t clientPort )
{
	if( false == m_NetServiceUtils.decryptNetServiceContent( content, contentDataLen, clientPort ) )
	{
		return 0;
	}

	AnchorList * anchorList = (AnchorList *)content;
	if( anchorList->m_TotalLen != contentDataLen )
	{
		LogMsg( LOG_ERROR, "NetActionAnnounce::decryptAnchorList: invalid nchorList->m_TotalLen\n" );
		return false;
	}

    if( MAX_ANCHOR_ENTRIES < anchorList->m_EntryCount )
	{
		LogMsg( LOG_ERROR, "NetActionAnnounce::decryptAnchorList: invalid anchorList->m_EntryCount\n" );
		return false;
	}

	return true;
}

//============================================================================
int NetActionAnnounce::buildAnnounceCmd( std::string& strNetCmdHdr, uint16_t clientPort, AnchorList& anchorList, EAnchorAction anchorAction )
{
	// build Anchor list
	PktAnnounce& pktAnn = m_Engine.getMyPktAnnounce();
	
	anchorList.m_AnchorAction = anchorAction;
	anchorList.addEntry( &pktAnn );
	int listLen = anchorList.calculateLength();

	std::string netServChallengeHash;
	m_NetServiceUtils.generateNetServiceChallengeHash( netServChallengeHash, clientPort );

	int totalLen = m_NetServiceUtils.buildNetCmdHeader( strNetCmdHdr, eNetCmdAnchorReq, netServChallengeHash, listLen );
	return totalLen;
}

//============================================================================
int NetActionAnnounce::getAnnounceData( VxSktConnectSimple * netServConn, char * pRxBuf, int bufLen )
{
	int iMaxToReceive = bufLen - 8;
	int iTotalRxed = 0;
	for( int i = 0; i < 10; ++i )
	{
		int iRxed = 0;
		netServConn->recieveData(	&pRxBuf[ iTotalRxed ],		// data buffer to read into
									iMaxToReceive,				// length of data	
									&iRxed,						// number of bytes actually received
									ANCHOR_RX_DATA_TIMEOUT );	// timeout attempt to receive
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


