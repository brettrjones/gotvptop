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

#include "NetServiceAnchor.h"
#include <GoTvCore/GoTvP2P/Anchor/AnchorList.h>

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>
#include <GoTvCore/GoTvP2P/NetServices/NetServiceHdr.h>
#include <GoTvCore/GoTvP2P/NetServices/NetServiceUtils.h>

#include <NetLib/VxSktBase.h>

#include <CoreLib/VxParse.h>
#include <CoreLib/VxGlobals.h>
#include <CoreLib/OsDetect.h>

namespace
{
	//const int		NET_CMD_ANCHOR_REPLY_VERSION			= 1;	 
	const char *	ANCHOR_DB_FILE_NAME						= "AnchorDb.db3";
	const int 		ANCHOR_DATABASE_VERSION 				= 1;
}

//============================================================================
NetServiceAnchor::NetServiceAnchor( P2PEngine& engine, NetServicesMgr& netServicesMgr, NetServiceUtils& netServiceUtils )
: m_Engine( engine )
, m_NetServicesMgr( netServicesMgr )
, m_NetServiceUtils( netServiceUtils )
{
}

//============================================================================
NetServiceAnchor::~NetServiceAnchor()
{
}

//============================================================================
void NetServiceAnchor::netServiceAnchorStartup( void )
{
	std::string anchorFileName = VxGetSettingsDirectory() + ANCHOR_DB_FILE_NAME;
	m_AnchorDb.dbStartup( ANCHOR_DATABASE_VERSION, anchorFileName );
}

//============================================================================
void NetServiceAnchor::netServiceAnchorShutdown( void )
{
	m_AnchorDb.dbShutdown();
}

//============================================================================
RCODE NetServiceAnchor::handleNetCmdAnchorReq( VxSktBase * sktBase, NetServiceHdr& netServiceHdr )
{
	RCODE rc = -1;
	if( ( 0 == netServiceHdr.m_ContentDataLen )
		|| ( 0x0f & netServiceHdr.m_ContentDataLen ) )
	{
		VxReportHack( sktBase, "handleNetCmdAnchorReq: Invalid content len %d\n", netServiceHdr.m_ContentDataLen );
		sktBase->closeSkt( 8776 );
		return -1;
	}
	
	char * pSktBuf = (char *)sktBase->getSktReadBuf();
	sktBase->sktBufAmountRead( 0 );

	char * content = &pSktBuf[ netServiceHdr.m_SktDataUsed ];
	int contentDataLen = netServiceHdr.m_ContentDataLen;
	uint16_t clientPort = sktBase->getCryptoKeyPort();
	AnchorList * anchorList = (AnchorList *)content;

	VxKey key;
	m_NetServiceUtils.generateNetServiceCryptoKey( key, clientPort );
	VxSymDecrypt( &key, content, contentDataLen );

	if( false == verifyAnchorList( anchorList, contentDataLen ) )
	{
		VxReportHack( sktBase, "handleNetCmdAnchorReq: Invalid list\n" );
		sktBase->closeSkt( 8776 );
		return -1;
	}

	AnchorList anchorResult;
	if( m_Engine.getEngineSettings().getExcludeMeFromNetHostList() )
	{
		rc = m_AnchorDb.handleAnnounce( *anchorList, anchorResult, m_Engine.getMyOnlineId() );
	}
	else
	{
		rc = m_AnchorDb.handleAnnounce( *anchorList, anchorResult );
	}

	int sendContentLen = anchorResult.calculateLength();

	std::string cmdHdr;
	m_NetServiceUtils.buildNetCmdHeader( cmdHdr, eNetCmdAnchorReply, netServiceHdr.m_ChallengeHash, sendContentLen, rc, 1 );
	VxSymEncrypt( &key, (char *)&anchorResult, sendContentLen );

	if( sktBase->isConnected() )
	{
		sktBase->sendData( cmdHdr.c_str(), cmdHdr.length() );
		sktBase->sendData( (char *)&anchorResult, sendContentLen );
	}
	else
	{
		rc = -1;
	}

	return rc;
}

//============================================================================
bool NetServiceAnchor::verifyAnchorList( AnchorList * anchorList, int contentDataLen )
{
	if( anchorList->m_TotalLen != contentDataLen )
	{
		LogMsg( LOG_ERROR, "handleNetCmdAnchorReq: invalid nchorList->m_TotalLen\n" );
		return false;
	}

	if( ( 0 == anchorList->m_EntryCount )
		|| ( MAX_ANCHOR_ENTRIES < anchorList->m_EntryCount ) )
	{
		LogMsg( LOG_ERROR, "handleNetCmdAnchorReq: invalid anchorList->m_EntryCount\n" );
		return false;
	}

	return true;
}

//============================================================================
RCODE NetServiceAnchor::handleNetCmdAnchorReply( VxSktBase * sktBase, NetServiceHdr& netServiceHdr )
{
	// not done here .. done by net action
	return 0;
}
