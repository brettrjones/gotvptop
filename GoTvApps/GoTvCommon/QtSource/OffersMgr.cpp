//============================================================================
// Copyright (C) 2016 Brett R. Jones
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

#include "OffersMgr.h"
#include "AppCommon.h"
#include "GuiOfferSession.h"
#include "OfferSessionState.h"
#include "GuiHelpers.h"

#include <QTimer>

//========================================================================
OffersMgr::OffersMgr( AppCommon&  myApp )
: m_MyApp( myApp )
, m_UserIsInSession( false )
, m_RingTimerCycleCnt( 0 )
, m_RingTimerSecondCnt( 0 )
, m_LastOfferUpdateTime( 0 )
//, m_OncePerSecTimer( new QTimer( this ) )
{
	connect( &myApp, SIGNAL(signalContactOffline(VxNetIdent*)),					this,		SLOT(slotToGuiContactOffline(VxNetIdent*)));

	connect( this, SIGNAL(signalToGuiRxedPluginOffer(GuiOfferSession *)),		this,		SLOT(slotToGuiRxedPluginOffer(GuiOfferSession *)) );
	connect( this, SIGNAL(signalToGuiRxedOfferReply(GuiOfferSession *)),		this,		SLOT(slotToGuiRxedOfferReply(GuiOfferSession *)) );
	connect( this, SIGNAL(signalToGuiPluginSessionEnded(GuiOfferSession *)),	this,		SLOT(slotToGuiPluginSessionEnded(GuiOfferSession *)) );

	//connect( m_OncePerSecTimer, SIGNAL(timeout()), this, SLOT(slotOncePerSecond()) );
	//m_OncePerSecTimer->setInterval( 1000 );
	//m_OncePerSecTimer->start();
}

//========================================================================
void OffersMgr::toGuiRxedPluginOffer( GuiOfferSession * offerSession )
{
	emit signalToGuiRxedPluginOffer( offerSession );
}

//========================================================================
void OffersMgr::slotToGuiRxedPluginOffer( GuiOfferSession * offerSession )
{
	lockOffersMgr();
	OfferSessionState * sessionState = findOrAddOfferSession( offerSession );
	changeOfferState( sessionState, eOfferStateRxedOffer );
	updateSndsAndMessages( sessionState );
	unlockOffersMgr();
	m_MyApp.onToGuiRxedPluginOffer( offerSession );
}

//========================================================================
void OffersMgr::toGuiRxedOfferReply( GuiOfferSession * offerSession )
{
	emit signalToGuiRxedOfferReply( offerSession );
}

//========================================================================
void OffersMgr::slotToGuiRxedOfferReply( GuiOfferSession * offerSession )
{
	lockOffersMgr();
	OfferSessionState * sessionState = findOfferSession( offerSession->getOfferSessionId() );
	if( sessionState )
	{
		EOfferState newOfferState = eOfferStateReplyBusy;
		switch( offerSession->getOfferResponse() )
		{
		case eOfferResponseAccept:
			newOfferState = eOfferStateReplyAccept;
			break;

		case eOfferResponseReject:
			newOfferState = eOfferStateReplyRejected;
			break;

		case eOfferResponseBusy:
			newOfferState = eOfferStateReplyBusy;
			break;

		case eOfferResponseCancelSession:
		case eOfferResponseEndSession:
			newOfferState = eOfferStateReplyCanceled;
			break;

		case eOfferResponseUserOffline:
			newOfferState = eOfferStateUserOffline;
			break;

		case eOfferResponseNotSet:
			LogMsg( LOG_INFO, "toGuiRxedOfferReply Response was not set" );
			newOfferState = eOfferStateUnknown;
			break;

		default:
			LogMsg( LOG_INFO, "toGuiRxedOfferReply Unknown Response " + offerSession->getOfferResponse() );
			newOfferState = eOfferStateUnknown;
			break;
		}

		changeOfferState( sessionState, newOfferState );
		updateSndsAndMessages( sessionState );
	}

	unlockOffersMgr();
	m_MyApp.onToGuiRxedOfferReply( offerSession );
}

//========================================================================
void OffersMgr::toGuiPluginSessionEnded( GuiOfferSession * offerSession )
{
	emit signalToGuiPluginSessionEnded( offerSession );
}

//========================================================================
void OffersMgr::slotToGuiPluginSessionEnded( GuiOfferSession * offerSession )
{
	lockOffersMgr();
	OfferSessionState * sessionState = findOfferSession( offerSession->getOfferSessionId() );		
	updateSndsAndMessages( sessionState );
	unlockOffersMgr();
}

//========================================================================
void OffersMgr::slotToGuiContactOffline( VxNetIdent * friendIdent )
{
	lockOffersMgr();
	std::vector<OfferSessionState *>::iterator iter = m_aoOffersList.begin();
	while( iter != m_aoOffersList.end() )
	{
		OfferSessionState * sessionState = (*iter);
		if( sessionState->getHisIdent()->getMyOnlineId() == friendIdent->getMyOnlineId() )
		{
			changeOfferState( sessionState, eOfferStateUserOffline );
			iter = m_aoOffersList.erase( iter );
			std::vector<ToGuiOfferInterface *>::iterator callbackIter;
			for( callbackIter = m_OfferCallbackList.begin(); callbackIter != m_OfferCallbackList.end(); ++callbackIter )
			{
				ToGuiOfferInterface * offerInterface = (*callbackIter);
				offerInterface->doGuiOfferRemoved( sessionState );
			}

			sessionState->deleteLater();
		}
		else
		{
			iter++;
		}
	}

	unlockOffersMgr();
}

//========================================================================
void OffersMgr::changeOfferState( OfferSessionState * sessionState, EOfferState newOfferState )
{
	if( 0 == sessionState )
	{
		return;
	}

	switch( newOfferState )
	{
	case eOfferStateRxedOffer:
		// always play notify sound
		m_MyApp.playSound( eSndDefNotify1 );
		m_MyApp.toGuiStatusMessage( sessionState->describeOffer().c_str() );
		// just in case thinks in session
		forceToNotInSession( sessionState );
		sessionState->setOfferState( newOfferState );
		startRingTimerIfNotInSession();	
		break;
	case eOfferStateSentAccept:
	case eOfferStateInSession:			
	case eOfferStateSentRejected:
	case eOfferStateWaitingReply:
		sessionState->setOfferState( newOfferState );
		stopRingTimer();	
		break;

	case eOfferStateOfferCanceled:
		sessionState->setOfferState( newOfferState );
		m_MyApp.toGuiStatusMessage( (sessionState->getOnlineName() + " Canceled Offer " + sessionState->describePlugin()).c_str() );
		m_MyApp.playSound( eSndDefOfferRejected );
		break;

	case eOfferStateReplyBusy:
		sessionState->setOfferState( newOfferState );
		m_MyApp.toGuiStatusMessage( (sessionState->getOnlineName() + " Is Too Busy For " + sessionState->describePlugin()).c_str() );
		m_MyApp.playSound( eSndDefBusy );
		break;

	case eOfferStateReplyAccept:
		sessionState->setOfferState( newOfferState );
		break;

	case eOfferStateReplyRejected:		
		sessionState->setOfferState( newOfferState );
		m_MyApp.playSound( eSndDefOfferRejected );
		m_MyApp.toGuiStatusMessage( (sessionState->getOnlineName() + " Rejected Offer " + sessionState->describePlugin()).c_str() );
		break;

	case eOfferStateReplyCanceled:
		m_MyApp.playSound( eSndDefOfferRejected );
		m_MyApp.toGuiStatusMessage( (sessionState->getOnlineName() + " Canceled Offer " + sessionState->describePlugin()).c_str() );
		break;

	case eOfferStateReplyEndSession:
		//m_MyApp.playSound( eSndDefOfferRejected );
		m_MyApp.toGuiStatusMessage( (sessionState->getOnlineName() + " Ended Session " + sessionState->describePlugin()).c_str() );
		break;

	case eOfferStateUserOffline:
		m_MyApp.toGuiStatusMessage( (sessionState->getOnlineName() + " cannot " + sessionState->describePlugin() + " because is offline").c_str() );
		break;

	default:
		LogMsg( LOG_INFO, "changeOfferState Unknown Offer State " + newOfferState );
		break;
	}	

	if( m_aoOffersList.size() )
	{
		OfferSessionState * sessionStateTop = m_aoOffersList[0];
		if( sessionStateTop == sessionState )
		{
			std::vector<ToGuiOfferInterface *>::iterator callbackIter;
			for( callbackIter = m_OfferCallbackList.begin(); callbackIter != m_OfferCallbackList.end(); ++callbackIter )
			{
				ToGuiOfferInterface * offerInterface = (*callbackIter);
				offerInterface->doGuiUpdatePluginOffer( sessionState );
			}
		}
	}
}

//========================================================================
void OffersMgr::forceToNotInSession( OfferSessionState * sessionState )
{
	EOfferState oldOfferState = sessionState->getOfferState();
	if( ( eOfferStateWaitingReply == oldOfferState )
		||	( eOfferStateInSession == oldOfferState ) )	
	{
        LogMsg( LOG_INFO, "forceToNotInSession %s %s\n", sessionState->getOnlineName().c_str(), sessionState->describePlugin().c_str() );
		sessionState->setOfferState( eOfferStateUnknown );
	}
}

//========================================================================
void OffersMgr::startRingTimerIfNotInSession()
{
	if( false == m_UserIsInSession )
	{
		m_RingTimerSecondCnt				= RING_ELAPSE_SEC;	
		m_RingTimerCycleCnt					= RING_COUNT;
	}	
}

//========================================================================
void OffersMgr::stopRingTimer()
{
	m_RingTimerCycleCnt					= 0;
	m_RingTimerSecondCnt				= 0;		
}

//========================================================================
void OffersMgr::slotOncePerSecond() 
{
	if( 0 != m_RingTimerCycleCnt )
	{
		if( 0 != m_RingTimerSecondCnt )
		{
			m_RingTimerSecondCnt--;
		}

		if( 0 == m_RingTimerSecondCnt )
		{
			m_RingTimerSecondCnt = RING_ELAPSE_SEC;
			m_RingTimerCycleCnt--;
			m_MyApp.playSound( eSndDefOfferStillWaiting );
		}			
	}		
}

//========================================================================
void OffersMgr::updateSndsAndMessages( OfferSessionState * sessionState )
{
	if( 0 == sessionState )
	{
		return;
	}
}

//========================================================================
void OffersMgr::wantToGuiOfferCallbacks( ToGuiOfferInterface * clientInterface, bool wantCallbacks )
{
	std::vector<ToGuiOfferInterface *>::iterator iter;
	for( iter = m_OfferCallbackList.begin(); iter != m_OfferCallbackList.end(); ++iter )
	{
		ToGuiOfferInterface * offerInterface = (*iter);
		if( offerInterface == clientInterface )
		{
			if( wantCallbacks )
			{
				// already in list
				return;
			}
			else
			{
				// remove from list
				m_OfferCallbackList.erase( iter );
				return;
			}
		}
	}

	if( wantCallbacks )
	{
		m_OfferCallbackList.push_back( clientInterface );
	}
}

//========================================================================
OfferSessionState *	 OffersMgr::getTopGuiOfferSession( void ) // returns null if no session offers
{
	if( m_aoOffersList.size() )
	{
		std::vector<OfferSessionState *>::iterator iter;
		iter = m_aoOffersList.begin(); 
		if( iter != m_aoOffersList.end() )
		{
			return *iter;
		}
	}

	return 0;
}

//========================================================================
void OffersMgr::acceptOfferButtonClicked( EPluginType ePluginType, VxGUID offerSessionId, VxNetIdent * hisIdent )
{
	OfferSessionState * offerState = findOfferSession( offerSessionId );
	if( 0 == offerState )
	{
		checkAndUpdateIfEmptyOfferList();
		return;
	}

	GuiOfferSession * offerSession = offerState->getGuiOfferSession();
	if( 0 == offerSession )
	{
		removePluginSessionOffer( offerSessionId );
		return;
	}

	if( ePluginTypeFileOffer == offerSession->getPluginType() )
	{
		VxGUID lclSessionId = offerSession->getLclSessionId();
		if( false == lclSessionId.isVxGUIDValid() )
		{
			lclSessionId = offerSession->getRmtSessionId();
		}

		if( false == lclSessionId.isVxGUIDValid() )
		{
			lclSessionId.initializeWithNewVxGUID();
			offerSession->setLclSessionId( lclSessionId );
		}

		if( false == m_MyApp.getEngine().fromGuiToPluginOfferReply( offerSession->getPluginType(), 
																	offerSession->getHisIdent()->getMyOnlineId(),
																	0, // user data
																	eOfferResponseAccept,
																	lclSessionId ) )
		{
            QString strErrMsg = offerSession->getHisIdent()->getOnlineName();
            strErrMsg += QObject::tr( " Is Offline " );
			m_MyApp.toGuiStatusMessage( strErrMsg.toUtf8().constData() );
		}
	}
	else
	{
		m_MyApp.executeActivity( offerSession, m_MyApp.getCentralWidget() );
	}

	removePluginSessionOffer( offerSessionId );
}

//========================================================================
void OffersMgr::rejectOfferButtonClicked( EPluginType ePluginType, VxGUID offerSessionId, VxNetIdent * hisIdent )
{
	OfferSessionState * offerState = findOfferSession( offerSessionId );
	if( 0 == offerState )
	{
		checkAndUpdateIfEmptyOfferList();
		return;
	}

	GuiOfferSession * offerSession = offerState->getGuiOfferSession();
	if( 0 == offerSession )
	{
		removePluginSessionOffer( offerSessionId );
		return;
	}

	if( offerSession->getHisIdent()->isOnline() 
		&&  offerState->isAvailableAndActiveOffer() )
	{
		VxGUID lclSessionId	= offerSession->getLclSessionId();
		bool sentMsg = m_MyApp.getEngine().fromGuiToPluginOfferReply(	offerSession->getPluginType(), 
																		offerSession->getHisIdent()->getMyOnlineId(), 
																		offerSession->getUserData(),
																		eOfferResponseReject,
																		lclSessionId );
		if( false == sentMsg )
		{
			LogMsg( LOG_INFO, "ActivityOfferListDlg::slotRejectOfferClicked user went offline\n" );
		}
	}

	removePluginSessionOffer( offerSessionId );
}

//========================================================================
void OffersMgr::removePluginSessionOffer( EPluginType ePluginType, VxNetIdent * netIdent )
{
	std::vector<OfferSessionState *>::iterator iter;
	iter = m_aoOffersList.begin();
	while( iter != m_aoOffersList.end() )
	{
		OfferSessionState * sessionState = (*iter);
		if( ( ePluginType == sessionState->getPluginType() )
			&& ( sessionState->getHisIdent()->getMyOnlineId() == netIdent->getMyOnlineId() ) )
		{
			iter = m_aoOffersList.erase( iter );
			std::vector<ToGuiOfferInterface *>::iterator callbackIter;
			for( callbackIter = m_OfferCallbackList.begin(); callbackIter != m_OfferCallbackList.end(); ++callbackIter )
			{
				ToGuiOfferInterface * offerInterface = (*callbackIter);
				offerInterface->doGuiOfferRemoved( sessionState );
			}

			sessionState->deleteLater();
		}
		else
		{
			++iter;
		}
	}

	checkAndUpdateIfEmptyOfferList();
}

//========================================================================
void OffersMgr::checkAndUpdateIfEmptyOfferList( void )
{
	if( 0 == m_aoOffersList.size() )
	{
		std::vector<ToGuiOfferInterface *>::iterator callbackIter;
		for( callbackIter = m_OfferCallbackList.begin(); callbackIter != m_OfferCallbackList.end(); ++callbackIter )
		{
			ToGuiOfferInterface * offerInterface = (*callbackIter);
			offerInterface->doGuiAllOffersRemoved();
		}
	}
}

//========================================================================
void OffersMgr::removePluginSessionOffer( VxGUID&  offerSessionId )
{
	std::vector<OfferSessionState *>::iterator iter;
	iter = m_aoOffersList.begin();
	while( iter != m_aoOffersList.end() )
	{
		OfferSessionState * sessionState = (*iter);
		if( sessionState->getOfferSessionId() == offerSessionId )
		{
			iter = m_aoOffersList.erase( iter );
			std::vector<ToGuiOfferInterface *>::iterator callbackIter;
			for( callbackIter = m_OfferCallbackList.begin(); callbackIter != m_OfferCallbackList.end(); ++callbackIter )
			{
				ToGuiOfferInterface * offerInterface = (*callbackIter);
				offerInterface->doGuiOfferRemoved( sessionState );
			}

			sessionState->deleteLater();
		}
		else
		{
			++iter;
		}
	}
}

//========================================================================
void OffersMgr::recievedOffer( EPluginType ePluginType, VxGUID offerSessionId, VxNetIdent * hisIdent )
{

}

//========================================================================
void OffersMgr::sentOffer( EPluginType ePluginType, VxGUID offerSessionId, VxNetIdent * hisIdent )
{

}

//========================================================================
void OffersMgr::sentOfferReply( EPluginType ePluginType, VxGUID offerSessionId, VxNetIdent * hisIdent, EOfferResponse eOfferResponse )
{
	//m_MyApp.getOfferListDialog()->sentOfferReply( ePluginType, offerSessionId, hisIdent, eOfferResponse );
}

//========================================================================
void OffersMgr::recievedOfferReply( EPluginType  ePluginType, VxGUID offerSessionId, VxNetIdent * hisIdent, EOfferResponse eOfferResponse )
{

}

//========================================================================
void OffersMgr::recievedSessionEnd( EPluginType ePluginType, VxGUID offerSessionId, VxNetIdent * hisIdent, EOfferResponse eOfferResponse )
{
}

//========================================================================
void OffersMgr::startedSessionInReply( EPluginType ePluginType, VxGUID offerSessionId, VxNetIdent * hisIdent )
{
	if( GuiHelpers::isPluginSingleSession( ePluginType ) )
	{
		removePluginSessionOffer( ePluginType, hisIdent );			
	}
	else
	{
		removePluginSessionOffer( offerSessionId );	
	}	
}

//========================================================================
void OffersMgr::onIsInSession( EPluginType ePluginType, VxGUID offerSessionId, VxNetIdent * hisIdent, bool isInSession )
{
	if( GuiHelpers::isPluginSingleSession( ePluginType ) )
	{
		removePluginSessionOffer( ePluginType, hisIdent );			
	}
	else
	{
		removePluginSessionOffer( offerSessionId );	
	}	
}

//========================================================================
void OffersMgr::onSessionExit( EPluginType ePluginType, VxGUID offerSessionId, VxNetIdent * hisIdent )
{
	if( GuiHelpers::isPluginSingleSession( ePluginType ) )
	{
		removePluginSessionOffer( ePluginType, hisIdent );			
	}
	else
	{
		removePluginSessionOffer( offerSessionId );	
	}	
}

//========================================================================
OfferSessionState * OffersMgr::findOrAddOfferSession( GuiOfferSession * offerSession )
{
    VxGUID thisSessionId = offerSession->getOfferSessionId();
	OfferSessionState * retSessionState = findOfferSession( thisSessionId );
	if( 0 == retSessionState )
	{
		retSessionState = offerSession->createNewSessionState( m_MyApp, offerSession );
		m_aoOffersList.push_back( retSessionState );
	}

	return retSessionState;
}

//========================================================================
OfferSessionState * OffersMgr::findOfferSession( VxGUID sessionId )
{
	OfferSessionState * retSessionState = 0;
	std::vector<OfferSessionState *>::iterator iter;
	for( iter = m_aoOffersList.begin(); iter != m_aoOffersList.end(); ++iter )
	{
		OfferSessionState * sessionState = (*iter);
		if( sessionState->getOfferSessionId() == sessionId )
		{
			retSessionState = sessionState;
			break;
		}
	}

	return retSessionState;
}

//============================================================================
GuiOfferSession * OffersMgr::findActiveAndAvailableOffer( VxNetIdent * netIdent, EPluginType ePluginType )
{
	std::vector<OfferSessionState *>::iterator iter;
	for( iter = m_aoOffersList.begin(); iter != m_aoOffersList.end(); ++iter )
	{
		if( ((*iter)->getPluginType() == ePluginType ) 
			&& ((*iter)->getHisIdent()->getMyOnlineId() == netIdent->getMyOnlineId() )  )
		{
			if( (*iter)->isAvailableAndActiveOffer() )
			{
				return (*iter)->getGuiOfferSession();
			}
		}
	}

	return NULL;
}
