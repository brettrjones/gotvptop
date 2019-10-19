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

#include "PluginMessenger.h"
#include "P2PSession.h"
#include "PluginMgr.h"

#include <PktLib/PktsVideoFeed.h>
#include <PktLib/PktsMultiSession.h>
#include <PktLib/PktsTodGame.h>

#include <GoTvInterface/IToGui.h>
#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>

#include <memory.h>

#ifdef _MSC_VER
# pragma warning(disable: 4355) //'this' : used in base member initializer list
#endif //_MSC_VER

//============================================================================
PluginMessenger::PluginMessenger( P2PEngine& engine, PluginMgr& pluginMgr, VxNetIdent * myIdent )
: PluginBase( engine, pluginMgr, myIdent )
, m_PluginSessionMgr( *this, pluginMgr )
, m_VoiceFeedMgr( *this, m_PluginSessionMgr )
, m_VideoFeedMgr( *this, m_PluginSessionMgr )
, m_AssetXferMgr( *this, m_PluginSessionMgr )
{
	m_ePluginType = ePluginTypeMessenger;
}

//============================================================================
void PluginMessenger::fromGuiUserLoggedOn( void )
{
	m_AssetXferMgr.fromGuiUserLoggedOn();
}

//============================================================================
bool PluginMessenger::fromGuiMakePluginOffer(	VxNetIdent *	netIdent,		
													int				pvUserData,
													const char *	pOfferMsg,		
													const char *	pFileName,
													uint8_t *			fileHashId,
													VxGUID			lclSessionId )	
{
	bool result = false;
	P2PSession * poSession = 0;
	//LogMsg( LOG_INFO, "PluginMessenger::fromGuiMakePluginOffer autoLock start\n" );
	PluginBase::AutoPluginLock pluginMutexLock( this );
	//LogMsg( LOG_INFO, "PluginMessenger::fromGuiSetGameValueVar autoLock done\n" );

	poSession = (P2PSession *)m_PluginSessionMgr.findP2PSessionByOnlineId( netIdent->getMyOnlineId(), true );
	if( poSession )
	{
		LogMsg( LOG_ERROR, "PluginMessenger already in session\n");
		result = true;
	}
	else
	{
		const char * offerMsg = pOfferMsg;
		if( ( 0 == offerMsg ) || ( 0 == strlen( offerMsg ) ) )
		{
			offerMsg = "Text Chat";
		}

		result = m_PluginSessionMgr.fromGuiMakePluginOffer(	true, 
															netIdent,
															pvUserData,	
															offerMsg,
															pFileName,
															fileHashId,
															lclSessionId );
	}

	//LogMsg( LOG_INFO, "PluginMessenger::fromGuiMakePluginOffer autoLock destroy\n" );
	return result;
}

//============================================================================
bool PluginMessenger::fromGuiOfferReply(	VxNetIdent *	netIdent,
											int				pvUserData,				
											EOfferResponse	eOfferResponse,
											VxGUID			lclSessionId )
{
	//LogMsg( LOG_INFO, "PluginMessenger::fromGuiOfferReply start\n" );
	bool result = m_PluginSessionMgr.fromGuiOfferReply( false,	netIdent, pvUserData, eOfferResponse, lclSessionId );
	//LogMsg( LOG_INFO, "PluginMessenger::fromGuiOfferReply done\n" );
	return result;
}

//============================================================================
void PluginMessenger::onPktSessionStopReq( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	//LogMsg( LOG_INFO, "PluginMessenger::onPktSessionStopReq start\n" );
	m_PluginSessionMgr.onPktSessionStopReq( sktBase, pktHdr, netIdent );
	//LogMsg( LOG_INFO, "PluginMessenger::onPktSessionStopReq done\n" );
}

//============================================================================
void PluginMessenger::fromGuiSendAsset( AssetInfo& assetInfo )
{
	//LogMsg( LOG_INFO, "PluginMessenger::fromGuiSendAsset start\n" );
	m_AssetXferMgr.fromGuiSendAsset( assetInfo );
	//LogMsg( LOG_INFO, "PluginMessenger::fromGuiSendAsset done\n" );
}

//============================================================================
bool PluginMessenger::fromGuiIsPluginInSession( VxNetIdent * netIdent, VxGUID lclSessionId )
{
	return m_PluginSessionMgr.fromGuiIsPluginInSession( false, netIdent, lclSessionId );
}

//============================================================================
//! called to start service or session with remote friend
void PluginMessenger::fromGuiStartPluginSession( VxNetIdent * netIdent, int pvUserData, VxGUID lclSessionId )
{
}

//============================================================================
//! called to stop service or session with remote friend
void PluginMessenger::fromGuiStopPluginSession( VxNetIdent * netIdent, int pvUserData, VxGUID lclSessionId )
{
	//LogMsg( LOG_INFO, "PluginMessenger::fromGuiStopPluginSession start\n" );
	m_VoiceFeedMgr.fromGuiStopPluginSession( true, netIdent );
	m_VideoFeedMgr.fromGuiStopPluginSession( true, &getEngine().getMyPktAnnounce() );

	m_PluginSessionMgr.fromGuiStopPluginSession( false, netIdent, pvUserData, lclSessionId );
	//LogMsg( LOG_INFO, "PluginMessenger::fromGuiStopPluginSession done\n" );
}

//============================================================================
bool PluginMessenger::fromGuiMultiSessionAction( VxNetIdent * netIdent, EMSessionAction mSessionAction, int pos0to100000, VxGUID lclSessionId )
{
	LogMsg( LOG_INFO, "PluginMessenger::fromGuiMultiSessionAction action %d \n", mSessionAction );
	bool sendSucces = false;

	if( eMSessionActionAccept == mSessionAction )
	{
		switch( pos0to100000 )
		{
		case eMSessionTypePhone:
			m_VoiceFeedMgr.fromGuiStartPluginSession( true, netIdent );
			break;

		case eMSessionTypeVidChat:
			m_VoiceFeedMgr.fromGuiStartPluginSession(  true, netIdent );
			m_VideoFeedMgr.fromGuiStartPluginSession(  true, &getEngine().getMyPktAnnounce() );
			break;

		case eMSessionTypeTruthOrDare:
			m_VoiceFeedMgr.fromGuiStartPluginSession(  true, netIdent );
			m_VideoFeedMgr.fromGuiStartPluginSession(  true, &getEngine().getMyPktAnnounce() );
			break;
		}
	}
	else if(  eMSessionActionHangup == mSessionAction )
	{
		switch( pos0to100000 )
		{
		case eMSessionTypePhone:
			m_VoiceFeedMgr.fromGuiStopPluginSession(  true, netIdent );
			break;

		case eMSessionTypeVidChat:
			m_VoiceFeedMgr.fromGuiStopPluginSession(  true, netIdent );
			m_VideoFeedMgr.fromGuiStopPluginSession( true, netIdent );
			m_VideoFeedMgr.fromGuiStopPluginSession(  true, &getEngine().getMyPktAnnounce() );
			break;

		case eMSessionTypeTruthOrDare:
			m_VoiceFeedMgr.fromGuiStopPluginSession( true, netIdent );
			m_VideoFeedMgr.fromGuiStopPluginSession( true, netIdent );
			m_VideoFeedMgr.fromGuiStopPluginSession( true, &getEngine().getMyPktAnnounce() );
			break;
		}
	}

	#ifdef DEBUG_AUTOPLUGIN_LOCK
		LogMsg( LOG_INFO, "PluginMessenger::fromGuiMultiSessionAction autoLock start\n" );
	#endif //DEBUG_AUTOPLUGIN_LOCK
	PluginBase::AutoPluginLock pluginMutexLock( this );
	#ifdef DEBUG_AUTOPLUGIN_LOCK
		LogMsg( LOG_INFO, "PluginMessenger::fromGuiMultiSessionAction autoLock done\n" );
	#endif //DEBUG_AUTOPLUGIN_LOCK
	PluginSessionBase * poSession = m_PluginSessionMgr.findPluginSessionByOnlineId( netIdent->getMyOnlineId(), true );
	if( 0 == poSession )
	{
		LogMsg( LOG_ERROR, "ERROR PluginMessenger::fromGuiMultiSessionAction missing plugin session \n" );
	}
	else
	{
		PktMultiSessionReq pktReq;
		pktReq.setMSessionAction( (uint32_t)mSessionAction );
		pktReq.setMSessionParam( (uint32_t)pos0to100000 );
		sendSucces = m_PluginMgr.pluginApiTxPacket( m_ePluginType, netIdent, poSession->getSkt(), &pktReq );
	}

	#ifdef DEBUG_AUTOPLUGIN_LOCK
		LogMsg( LOG_INFO, "PluginMessenger::fromGuiMultiSessionAction autoLock destroy\n" );
	#endif //DEBUG_AUTOPLUGIN_LOCK
	return sendSucces;
}

//============================================================================
bool PluginMessenger::fromGuiSetGameValueVar( VxNetIdent * netIdent, int32_t varId, int32_t varValue )
{
	#ifdef DEBUG_AUTOPLUGIN_LOCK
		LogMsg( LOG_INFO, "PluginMessenger::fromGuiSetGameValueVar autoLock start\n" );
	#endif //DEBUG_AUTOPLUGIN_LOCK
	bool sendSucces = false;
	PluginBase::AutoPluginLock pluginMutexLock( this );
	#ifdef DEBUG_AUTOPLUGIN_LOCK
		LogMsg( LOG_INFO, "PluginMessenger::fromGuiSetGameValueVar autoLock done\n" );
	#endif //DEBUG_AUTOPLUGIN_LOCK
	PluginSessionBase * poSession = m_PluginSessionMgr.findPluginSessionByOnlineId( netIdent->getMyOnlineId(), true );
	if( poSession )
	{
		PktTodGameValue pktGameValue;
		pktGameValue.setValue( (ETodGameVarId) varId, varValue );
		sendSucces = m_PluginMgr.pluginApiTxPacket( m_ePluginType, netIdent, poSession->getSkt(), &pktGameValue );
	}

	#ifdef DEBUG_AUTOPLUGIN_LOCK
		LogMsg( LOG_INFO, "PluginMessenger::fromGuiSetGameValueVar autoLock destroy\n" );
	#endif //DEBUG_AUTOPLUGIN_LOCK
	return sendSucces;
}

//============================================================================
bool PluginMessenger::fromGuiSetGameActionVar( VxNetIdent * netIdent, int32_t actionId, int32_t actionValue )
{
	#ifdef DEBUG_AUTOPLUGIN_LOCK
		LogMsg( LOG_INFO, "PluginMessenger::fromGuiSetGameActionVar autoLock start\n" );
	#endif //DEBUG_AUTOPLUGIN_LOCK
	bool sendSucces = false;
	PluginBase::AutoPluginLock pluginMutexLock( this );
	PluginSessionBase * poSession = m_PluginSessionMgr.findPluginSessionByOnlineId( netIdent->getMyOnlineId(), true );
	if( poSession )
	{
		PktTodGameAction pktGameAction;
		pktGameAction.setAction( (ETodGameAction) actionId, actionValue );
		sendSucces = m_PluginMgr.pluginApiTxPacket( m_ePluginType, netIdent, poSession->getSkt(), &pktGameAction );
	}

	#ifdef DEBUG_AUTOPLUGIN_LOCK
		LogMsg( LOG_INFO, "PluginMessenger::fromGuiSetGameActionVar autoLock done\n" );
	#endif //DEBUG_AUTOPLUGIN_LOCK
	return sendSucces;
}

//============================================================================
void PluginMessenger::callbackOpusPkt( void * userData, PktVoiceReq * pktOpusAudio )
{
	m_VoiceFeedMgr.callbackOpusPkt( userData, pktOpusAudio );
}

//============================================================================
void PluginMessenger::callbackAudioOutSpaceAvail( int freeSpaceLen )
{
	m_VoiceFeedMgr.callbackAudioOutSpaceAvail( freeSpaceLen );
}

//============================================================================
void PluginMessenger::callbackVideoPktPic( void * /*userData*/, VxGUID& onlineId, PktVideoFeedPic * pktVid, int pktsInSequence, int thisPktNum )
{
	m_VideoFeedMgr.callbackVideoPktPic( onlineId, pktVid, pktsInSequence, thisPktNum );
}

//============================================================================
void PluginMessenger::callbackVideoPktPicChunk( void * /*userData*/, VxGUID& onlineId, PktVideoFeedPicChunk * pktVid, int pktsInSequence, int thisPktNum ) 
{
	m_VideoFeedMgr.callbackVideoPktPicChunk( onlineId, pktVid, pktsInSequence, thisPktNum );
}

//============================================================================
void PluginMessenger::onPktPluginOfferReq( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	//LogMsg( LOG_INFO, "PluginMessenger::onPktPluginOfferReq start\n" );
	m_PluginSessionMgr.onPktPluginOfferReq( sktBase, pktHdr, netIdent );
	//LogMsg( LOG_INFO, "PluginMessenger::onPktPluginOfferReq done\n" );
}

//============================================================================
void PluginMessenger::onPktPluginOfferReply( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	//LogMsg( LOG_INFO, "PluginMessenger::onPktPluginOfferReply start\n" );
	m_PluginSessionMgr.onPktPluginOfferReply( sktBase, pktHdr, netIdent );
	//LogMsg( LOG_INFO, "PluginMessenger::onPktPluginOfferReply done\n" );
}

//============================================================================
void PluginMessenger::onPktVideoFeedReq( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_VideoFeedMgr.onPktVideoFeedReq( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginMessenger::onPktVideoFeedStatus( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_VideoFeedMgr.onPktVideoFeedStatus( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginMessenger::onPktVideoFeedPic( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_VideoFeedMgr.onPktVideoFeedPic( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginMessenger::onPktVideoFeedPicChunk( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_VideoFeedMgr.onPktVideoFeedPicChunk( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginMessenger::onPktVideoFeedPicAck( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_VideoFeedMgr.onPktVideoFeedPicAck( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginMessenger::onPktVoiceReq( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_VoiceFeedMgr.onPktVoiceReq( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginMessenger::onPktVoiceReply( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_VoiceFeedMgr.onPktVoiceReply( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginMessenger::onPktAssetSendReq( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
#ifdef DEBUG_SEND_ASSET
	LogMsg( LOG_INFO, "PluginMessenger::onPktAssetSendReq start\n" );
#endif // DEBUG_SEND_ASSET
	m_AssetXferMgr.onPktAssetSendReq( sktBase, pktHdr, netIdent );
#ifdef DEBUG_SEND_ASSET
	LogMsg( LOG_INFO, "PluginMessenger::onPktAssetSendReq done\n" );
#endif // DEBUG_SEND_ASSET
}

//============================================================================
void PluginMessenger::onPktAssetSendReply( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
#ifdef DEBUG_SEND_ASSET
	LogMsg( LOG_INFO, "PluginMessenger::onPktAssetSendReply start\n" );
#endif // DEBUG_SEND_ASSET
	m_AssetXferMgr.onPktAssetSendReply( sktBase, pktHdr, netIdent );
#ifdef DEBUG_SEND_ASSET
	LogMsg( LOG_INFO, "PluginMessenger::onPktAssetSendReply done\n" );
#endif // DEBUG_SEND_ASSET
}

//============================================================================
void PluginMessenger::onPktAssetChunkReq( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
#ifdef DEBUG_SEND_ASSET
	LogMsg( LOG_INFO, "PluginMessenger::onPktAssetChunkReq start\n" );
#endif // DEBUG_SEND_ASSET
	m_AssetXferMgr.onPktAssetChunkReq( sktBase, pktHdr, netIdent );
#ifdef DEBUG_SEND_ASSET
	LogMsg( LOG_INFO, "PluginMessenger::onPktAssetChunkReq done\n" );
#endif // DEBUG_SEND_ASSET
}

//============================================================================
void PluginMessenger::onPktAssetChunkReply( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
#ifdef DEBUG_SEND_ASSET
	LogMsg( LOG_INFO, "PluginMessenger::onPktAssetChunkReply start\n" );
#endif // DEBUG_SEND_ASSET
	m_AssetXferMgr.onPktAssetChunkReply( sktBase, pktHdr, netIdent );
#ifdef DEBUG_SEND_ASSET
	LogMsg( LOG_INFO, "PluginMessenger::onPktAssetChunkReply done\n" );
#endif // DEBUG_SEND_ASSET
}

//============================================================================
void PluginMessenger::onPktAssetSendCompleteReq( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
#ifdef DEBUG_SEND_ASSET
	LogMsg( LOG_INFO, "PluginMessenger::onPktAssetSendCompleteReq start\n" );
#endif // DEBUG_SEND_ASSET
	m_AssetXferMgr.onPktAssetSendCompleteReq( sktBase, pktHdr, netIdent );
#ifdef DEBUG_SEND_ASSET
	LogMsg( LOG_INFO, "PluginMessenger::onPktAssetSendCompleteReq done\n" );
#endif // DEBUG_SEND_ASSET
}

//============================================================================
void PluginMessenger::onPktAssetSendCompleteReply( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
#ifdef DEBUG_SEND_ASSET
	LogMsg( LOG_INFO, "PluginMessenger::onPktAssetSendCompleteReply start\n" );
#endif // DEBUG_SEND_ASSET
	m_AssetXferMgr.onPktAssetSendCompleteReply( sktBase, pktHdr, netIdent );
#ifdef DEBUG_SEND_ASSET
	LogMsg( LOG_INFO, "PluginMessenger::onPktAssetSendCompleteReply done\n" );
#endif // DEBUG_SEND_ASSET
}

//============================================================================
void PluginMessenger::onPktAssetXferErr( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
#ifdef DEBUG_SEND_ASSET
	LogMsg( LOG_INFO, "PluginMessenger::onPktAssetXferErr start\n" );
#endif // DEBUG_SEND_ASSET
	m_AssetXferMgr.onPktAssetXferErr( sktBase, pktHdr, netIdent );
#ifdef DEBUG_SEND_ASSET
	LogMsg( LOG_INFO, "PluginMessenger::onPktAssetXferErr done\n" );
#endif // DEBUG_SEND_ASSET
}

//============================================================================
void PluginMessenger::onPktMultiSessionReq( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	PktMultiSessionReq * pktReq			= (PktMultiSessionReq *)pktHdr;
	EMSessionAction eMSessionAction		= ( EMSessionAction )pktReq->getMSessionAction();
	EMSessionType eMSessionType			= ( EMSessionType )pktReq->getMSessionParam(); 

	if( eMSessionActionAccept == eMSessionAction )
	{
		switch( eMSessionType )
		{
		case eMSessionTypePhone:
			m_VoiceFeedMgr.fromGuiStartPluginSession( true, netIdent );
			break;

		case eMSessionTypeVidChat:
			m_VoiceFeedMgr.fromGuiStartPluginSession( true, netIdent );
			m_VideoFeedMgr.fromGuiStartPluginSession( true, &getEngine().getMyPktAnnounce());
			break;

		case eMSessionTypeTruthOrDare:
			m_VoiceFeedMgr.fromGuiStartPluginSession( true, netIdent );
			m_VideoFeedMgr.fromGuiStartPluginSession( true, &getEngine().getMyPktAnnounce() );
			break;
		default:
			break;
		}
	}
	else if(  eMSessionActionHangup == eMSessionAction )
	{
		switch( eMSessionType )
		{
		case eMSessionTypePhone:
			m_VoiceFeedMgr.fromGuiStopPluginSession( true, netIdent );
			break;

		case eMSessionTypeVidChat:
			m_VoiceFeedMgr.fromGuiStopPluginSession( true, netIdent );
			m_VideoFeedMgr.fromGuiStopPluginSession( true, netIdent );
			m_VideoFeedMgr.fromGuiStopPluginSession( true, &getEngine().getMyPktAnnounce() );
			break;

		case eMSessionTypeTruthOrDare:
			m_VoiceFeedMgr.fromGuiStopPluginSession( true, netIdent );
			m_VideoFeedMgr.fromGuiStopPluginSession( true, netIdent );
			m_VideoFeedMgr.fromGuiStopPluginSession( true, &getEngine().getMyPktAnnounce() );
			break;
		default:
			break;
		}
	}

	IToGui::getToGui().toGuiMultiSessionAction( eMSessionAction, netIdent->getMyOnlineId(), pktReq->getMSessionParam() );
#ifdef DEBUG_AUTOPLUGIN_LOCK
	LogMsg( LOG_INFO, "PluginMessenger::onPktMultiSessionReq autoLock start\n" );
#endif // DEBUG_AUTOPLUGIN_LOCK
	PluginBase::AutoPluginLock pluginMutexLock( this );
#ifdef DEBUG_AUTOPLUGIN_LOCK
	LogMsg( LOG_INFO, "PluginMessenger::onPktMultiSessionReq autoLock done\n" );
#endif // DEBUG_AUTOPLUGIN_LOCK
	P2PSession * poSession = m_PluginSessionMgr.findOrCreateP2PSessionWithOnlineId( netIdent->getMyOnlineId(), sktBase, netIdent, true );
	poSession->setSkt( sktBase );

#ifdef DEBUG_AUTOPLUGIN_LOCK
	LogMsg( LOG_INFO, "PluginMessenger::onPktMultiSessionReq autoLock destroy\n" );
#endif // DEBUG_AUTOPLUGIN_LOCK
}

//============================================================================
void PluginMessenger::onPktMultiSessionReply( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	LogMsg( LOG_INFO, "PluginMessenger::onPktMultiSessionReply start\n" );
	PktMultiSessionReply * pktReply = (PktMultiSessionReply *)pktHdr;

	IToGui::getToGui().toGuiMultiSessionAction( ( EMSessionAction )pktReply->getMSessionAction(), netIdent->getMyOnlineId(), pktReply->getMSessionParam() );
	LogMsg( LOG_INFO, "PluginMessenger::onPktMultiSessionReply done\n" );
}

//============================================================================
void PluginMessenger::onPktTodGameStats( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	PktTodGameStats * poPkt = (PktTodGameStats *)pktHdr;
	for( int i = 0; i < eMaxTodGameStatId; ++i )
	{
		IToGui::getToGui().toGuiSetGameValueVar( m_ePluginType, netIdent->getMyOnlineId(), i, poPkt->getVar((ETodGameVarId)i) );
	}

	IToGui::getToGui().toGuiSetGameActionVar( m_ePluginType, netIdent->getMyOnlineId(), eTodGameActionSendStats, 1 );
}

//============================================================================
void PluginMessenger::onPktTodGameAction( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	PktTodGameAction * poPkt = (PktTodGameAction *)pktHdr;
	IToGui::getToGui().toGuiSetGameActionVar( m_ePluginType, netIdent->getMyOnlineId(), poPkt->getActionVarId(), poPkt->getActionVarValue() );
}

//============================================================================
void PluginMessenger::onPktTodGameValue( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	PktTodGameValue * poPkt = (PktTodGameValue *)pktHdr;
	IToGui::getToGui().toGuiSetGameValueVar( m_ePluginType, netIdent->getMyOnlineId(), poPkt->getValueVarId(), poPkt->getValueVar() );
}

//============================================================================
void PluginMessenger::onSessionStart( PluginSessionBase * session, bool pluginIsLocked )
{
	PluginBase::onSessionStart( session, pluginIsLocked ); // mark user session time so contact list is sorted with latest used on top

	//NOTE: for chat session the video and audio is started/stopped through MSession commands
	//m_VoiceFeedMgr.fromGuiStartPluginSession( session->getIdent() );
	// in order to get my video packets to send out the ident has to by myself
	//m_VideoFeedMgr.fromGuiStartPluginSession( &getEngine().getMyPktAnnounce() );
}

//============================================================================
void PluginMessenger::onSessionEnded( PluginSessionBase * session, bool pluginIsLocked, EOfferResponse eOfferResponse )
{
	m_VoiceFeedMgr.fromGuiStopPluginSession( true, session->getIdent() );
	m_VideoFeedMgr.fromGuiStopPluginSession( true, session->getIdent() );
	m_VideoFeedMgr.fromGuiStopPluginSession( true, &getEngine().getMyPktAnnounce() );
}

//============================================================================
void PluginMessenger::replaceConnection( VxNetIdent * netIdent, VxSktBase * poOldSkt, VxSktBase * poNewSkt )
{
#ifdef DEBUG_SKT_CONNECTIONS
	LogMsg( LOG_INFO, "PluginMessenger::replaceConnection start\n" );
#endif // DEBUG_SKT_CONNECTIONS
	m_AssetXferMgr.replaceConnection( netIdent, poOldSkt, poNewSkt );
	m_PluginSessionMgr.replaceConnection( netIdent, poOldSkt, poNewSkt );
#ifdef DEBUG_SKT_CONNECTIONS
    LogMsg( LOG_INFO, "PluginMessenger::replaceConnection done\n" );
#endif // DEBUG_SKT_CONNECTIONS
}

//============================================================================
void PluginMessenger::onConnectionLost( VxSktBase * sktBase )
{
#ifdef DEBUG_SKT_CONNECTIONS
    LogMsg( LOG_INFO, "PluginMessenger::onConnectionLost start\n" );
#endif // DEBUG_SKT_CONNECTIONS
	m_AssetXferMgr.onConnectionLost( sktBase );
	m_PluginSessionMgr.onConnectionLost( sktBase );
#ifdef DEBUG_SKT_CONNECTIONS
    LogMsg( LOG_INFO, "PluginMessenger::onConnectionLost done\n" );
#endif // DEBUG_SKT_CONNECTIONS
}

//============================================================================
void PluginMessenger::onContactWentOnline( VxNetIdent * netIdent, VxSktBase * sktBase )
{
	m_AssetXferMgr.onContactWentOnline( netIdent, sktBase );
}

//============================================================================
void PluginMessenger::onContactWentOffline( VxNetIdent *	netIdent, VxSktBase * sktBase )
{
	LogMsg( LOG_INFO, "PluginMessenger::onContactWentOffline start\n" );
	m_VoiceFeedMgr.fromGuiStopPluginSession( true, netIdent );
	m_VideoFeedMgr.fromGuiStopPluginSession( true, netIdent );
	m_VideoFeedMgr.fromGuiStopPluginSession( true, &getEngine().getMyPktAnnounce() );
	m_PluginSessionMgr.onContactWentOffline( netIdent, sktBase );
	LogMsg( LOG_INFO, "PluginMessenger::onContactWentOffline done\n" );
}
