//============================================================================
// Copyright (C) 2010 Brett R. Jones
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

#include <PktLib/VxCommon.h>

#include "PluginBaseFileXfer.h"
#include "PluginMgr.h"
#include "FileXferPluginSession.h"

#include <GoTvInterface/IToGui.h>
#include <PktLib/PktsPluginOffer.h>

#ifdef _MSC_VER
# pragma warning(disable: 4355) //'this' : used in base member initializer list
#endif

//============================================================================
PluginBaseFileXfer::PluginBaseFileXfer( P2PEngine& engine, PluginMgr& pluginMgr, VxNetIdent * myIdent )
: PluginBase( engine, pluginMgr, myIdent )
, m_PluginSessionMgr( *this, pluginMgr )
, m_FileXferMgr( *this, m_PluginSessionMgr )
{
}

//============================================================================ 
P2PSession * PluginBaseFileXfer::createP2PSession( VxGUID& lclSessionId, VxSktBase * sktBase, VxNetIdent * netIdent )
{
	P2PSession * pSession = new FileXferPluginSession( lclSessionId, sktBase, netIdent );
	pSession->setPluginType( m_ePluginType );
	return pSession;
}

//============================================================================
//! user wants to send offer to friend.. return false if cannot connect
bool PluginBaseFileXfer::fromGuiMakePluginOffer(		VxNetIdent *	netIdent,		
													int				pvUserData,
													const char *	pOfferMsg,		
													const char *	pFileName,
													uint8_t *			fileHashId,
													VxGUID			lclSessionId )	
{
	return m_PluginSessionMgr.fromGuiMakePluginOffer(		false,
															netIdent,
															pvUserData,	
															pOfferMsg,
															pFileName,
															fileHashId,
															lclSessionId );
}

//============================================================================
//! handle reply to offer
bool PluginBaseFileXfer::fromGuiOfferReply(	VxNetIdent *	netIdent,
											int				pvUserData,				
											EOfferResponse	eOfferResponse,
											VxGUID			lclSessionId )
{
	return m_PluginSessionMgr.fromGuiOfferReply(	false,
													netIdent,
													pvUserData,				
													eOfferResponse, 
													lclSessionId );
}

//============================================================================
void PluginBaseFileXfer::fromGuiStartPluginSession( PluginSessionBase * poOffer )
{
	m_FileXferMgr.fromGuiStartPluginSession( false, poOffer );
}

//============================================================================
int PluginBaseFileXfer::fromGuiDeleteFile( const char * fileName, bool shredFile )
{
	PluginBase::AutoPluginLock pluginMutexLock( this );
	std::map<VxGUID, PluginSessionBase *>& xferSessionList = m_PluginSessionMgr.getSessions();
	PluginSessionMgr::SessionIter iter;

	bool sessionCanceled = true;
	while( sessionCanceled )
	{
		sessionCanceled = false;
		for( iter = xferSessionList.begin(); iter != xferSessionList.end(); ++iter )
		{
			FileXferPluginSession * xferSession = (FileXferPluginSession *)iter->second;
			if( xferSession->getRxXferInfo().getLclFileName() == fileName )
			{
				xferSession->cancelDnload( *this, xferSession->getRxXferInfo().getLclSessionId() );
				sessionCanceled = true;
			}
			else if( xferSession->getTxXferInfo().getLclFileName() == fileName )
			{
				xferSession->cancelUpload( *this, xferSession->getTxXferInfo().getLclSessionId() );
				sessionCanceled = true;
			}

			if( sessionCanceled )
			{
				delete xferSession;
				xferSessionList.erase( iter );
				break;
			}
		}
	}

	return 0;
}

//============================================================================
void PluginBaseFileXfer::fromGuiCancelDownload( VxGUID& lclSessionId )
{
	cancelXferSession( lclSessionId );
}

//============================================================================
void PluginBaseFileXfer::fromGuiCancelUpload( VxGUID& lclSessionId )
{
	cancelXferSession( lclSessionId );
}

//============================================================================
void PluginBaseFileXfer::cancelXferSession( VxGUID& lclSessionId )
{
	PluginBase::AutoPluginLock pluginMutexLock( this );
	std::map<VxGUID, PluginSessionBase *>& xferSessionList = m_PluginSessionMgr.getSessions();
	PluginSessionMgr::SessionIter iter;

	bool sessionCanceled = true;
	while( sessionCanceled )
	{
		sessionCanceled = false;
		for( iter = xferSessionList.begin(); iter != xferSessionList.end(); ++iter )
		{
			FileXferPluginSession * xferSession = (FileXferPluginSession *)iter->second;
			if( xferSession->getRxXferInfo().getLclSessionId() == lclSessionId )
			{
				xferSession->cancelDnload( *this, lclSessionId );
				sessionCanceled = true;
			}
			else if( xferSession->getTxXferInfo().getLclSessionId() == lclSessionId )
			{
				xferSession->cancelUpload( *this, lclSessionId );
				sessionCanceled = true;
			}

			if( sessionCanceled )
			{
				delete xferSession;
				xferSessionList.erase( iter );
				break;
			}
		}
	}
}

//============================================================================
void PluginBaseFileXfer::onPktPluginOfferReq( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_PluginSessionMgr.onPktPluginOfferReq( sktBase, pktHdr, netIdent );
}

//============================================================================
//! packet with remote users reply to offer
void PluginBaseFileXfer::onPktPluginOfferReply( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_PluginSessionMgr.onPktPluginOfferReply( sktBase, pktHdr, netIdent );
}

//============================================================================
//! called by session manager if offer was accepted by remote user
void PluginBaseFileXfer::onSessionStart( PluginSessionBase * session, bool pluginIsLocked )
{
	// put the file that was offered in the que of files to send
	FileXferPluginSession * xferSession = (FileXferPluginSession *)session;
	if( xferSession->getOfferFile().size() )
	{
		xferSession->m_astrFilesToSend.push_back( FileToXfer(xferSession->m_strOfferFile, 
													0, 
													xferSession->getLclSessionId(), 
													xferSession->getRmtSessionId(),
													xferSession->getFileHashId(),
													0 ) );
		m_FileXferMgr.fromGuiStartPluginSession( true, session );
	}
	else
	{
		LogMsg( LOG_INFO, "PluginBaseFileXfer::onSessionStart: No files in plugin session to send\n" );
	}
}

//============================================================================
void PluginBaseFileXfer::replaceConnection( VxNetIdent * netIdent, VxSktBase * poOldSkt, VxSktBase * poNewSkt )
{
	m_PluginSessionMgr.replaceConnection( netIdent, poOldSkt, poNewSkt );
}

//============================================================================
void PluginBaseFileXfer::onConnectionLost( VxSktBase * sktBase )
{
	m_PluginSessionMgr.onConnectionLost( sktBase );
}

//============================================================================
void PluginBaseFileXfer::onContactWentOffline( VxNetIdent * netIdent, VxSktBase * sktBase )
{
	m_PluginSessionMgr.onContactWentOffline( netIdent, sktBase );
}