//============================================================================
// Copyright (C) 2016 Brett R. Jones
// All Rights Reserved ( After My Death I Brett R. Jones Issue this source code to Public Domain )
//
// You may not modify or redistribute this code for any reason
// without written consent of Brett R. Jones
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// brett1900@usa.com
// http://www.gotvp2p.net
//============================================================================
package com.p2pgotv.gotvstation;

import java.util.ArrayList;
import java.util.concurrent.Semaphore;

import android.util.Log;

public class OffersMgr implements FromGuiOfferInterface
{
	private static final String LOG_TAG 				= "OffersMgr:"; 
	private static final int 	RING_COUNT 				= 4; 
	private static final int 	RING_ELAPSE_SEC 		= 4; 
	
	private MyApp				m_MyApp;
	private static Semaphore 	m_OffersMgrMutex 					= new Semaphore(1); 
	private ArrayList<GuiOfferSession>	m_OfferStateList 			= new ArrayList<GuiOfferSession>();	
	private ArrayList<ToGuiOfferInterface> 	m_OfferCallbackList		= new ArrayList<ToGuiOfferInterface>();	
	private boolean				m_UserIsInSession					= false;
	private int					m_RingTimerCycleCnt					= 0;
	private int					m_RingTimerSecondCnt				= 0;
	
	//========================================================================
	OffersMgr( MyApp myApp )
	{
		m_MyApp = myApp;
	}	
	
	//========================================================================
	public void lockOffersMgr()
	{
		try 
		{
			m_OffersMgrMutex.acquire();
		} 
		catch (InterruptedException e) 
		{
			e.printStackTrace();
		}
	}
	
	//========================================================================
	public void unlockOffersMgr()
	{
		m_OffersMgrMutex.release();
	}

	//========================================================================
	public void toGuiRxedPluginOffer( GuiOfferSession offerSession )
	{
		if( null == offerSession )
		{
			return;
		}
		
		final GuiOfferSession finalOfferSession = offerSession;
		m_MyApp.getMainActivity().runOnUiThread(new Runnable() 
		{
			public void run() 
			{
				doGuiRxedPluginOffer( finalOfferSession );
			}
		});
	}

	//========================================================================
	public void doGuiRxedPluginOffer( GuiOfferSession offerSession )
	{
		GuiOfferSession sessionState = findOrAddOfferSession( offerSession );
		changeOfferState( sessionState, EOfferState.eOfferStateRxedOffer );		
		if( ( Constants.ePluginTypeTruthOrDare == offerSession.getPluginType() )
			|| ( Constants.ePluginTypeVideoPhone == offerSession.getPluginType() )
			|| ( Constants.ePluginTypeVoicePhone == offerSession.getPluginType() ) )
		{
			m_MyApp.playSound( ESndDef.eSndDefPhoneRing1 );
		}		
	}

	//========================================================================
	public void toGuiRxedOfferReply( GuiOfferSession offerSession )
	{
		if( null == offerSession )
		{
			return;
		}
		
		final GuiOfferSession finalOfferSession = offerSession;
		m_MyApp.getMainActivity().runOnUiThread( new Runnable() 					
		{	
			@Override
			public void run() 
			{
				doGuiRxedOfferReply( finalOfferSession );
			}
		});
	}

	//========================================================================
	public void doGuiRxedOfferReply( GuiOfferSession offerSession )
	{
		EOfferState newOfferState = EOfferState.eOfferStateReplyBusy;
		switch( offerSession.getOfferResponse() )
		{
		case Constants.eOfferResponseAccept:
			newOfferState = EOfferState.eOfferStateReplyAccept;
			break;
			
		case Constants.eOfferResponseReject:
			newOfferState = EOfferState.eOfferStateReplyRejected;
			break;
			
		case Constants.eOfferResponseBusy:
			newOfferState = EOfferState.eOfferStateReplyBusy;
			break;
			
		case Constants.eOfferResponseEndSession:
			//newOfferState = EOfferState.eOfferStateReplyEndSession;
			//break;
		case Constants.eOfferResponseCancelSession:
			newOfferState = EOfferState.eOfferStateReplyCanceled;
			break;		
		
		case Constants.eOfferResponseUserOffline:
			newOfferState = EOfferState.eOfferStateUserOffline;
			break;
	
		case Constants.eOfferResponseNotSet:
			Log.e( LOG_TAG, "toGuiRxedOfferReply Response was not set" );
			newOfferState = EOfferState.eOfferStateUnknown;
			break;
			
		default:
			Log.e( LOG_TAG, "toGuiRxedOfferReply Unknown Response " + offerSession.getOfferResponse() );
			newOfferState = EOfferState.eOfferStateUnknown;
			break;
		}
	
		changeOfferState( offerSession, newOfferState );
	}

	//========================================================================
	public void toGuiPluginSessionEnded( GuiOfferSession offerSession )
	{
		final GuiOfferSession finalOfferSession = offerSession;
		m_MyApp.getMainActivity().runOnUiThread( new Runnable() 					
		{	
			@Override
			public void run() 
			{
				
				doGuiPluginSessionEnded( finalOfferSession );
			}
		});
	}
	
	//========================================================================
	public void doGuiPluginSessionEnded( GuiOfferSession offerSession )
	{
		GuiOfferSession sessionState = findOfferSession( offerSession.getOfferSessionId(), offerSession.getPluginType() );	
		changeOfferState( sessionState, EOfferState.eOfferStateReplyCanceled );
	}

	//========================================================================
	public void toGuiContactOffline( VxNetIdent netIdent )
	{
		final VxGUID hisOnlineId = netIdent.getMyOnlineId();
		m_MyApp.getMainActivity().runOnUiThread( new Runnable() 					
		{	
			@Override
			public void run() 
			{					
				boolean offerRemoved = true;
				while( offerRemoved )
				{
					offerRemoved = false;
					lockOffersMgr();
					int listIdx = 0;
					
				   	for( GuiOfferSession sessionState:  m_OfferStateList )
			    	{
			    		if( sessionState.getHisIdent().getMyOnlineId().equals( hisOnlineId ) )
			    		{
			    			
			    			offerRemoved = true;
			    			final GuiOfferSession finalOfferSession = sessionState;
			    			final int listPosition = listIdx;
			    			doGuiContactOffline( finalOfferSession, listPosition );
			    			break;
		    			}
		    			
			    		listIdx++;
		    		}
		    		
				   	unlockOffersMgr();
		    		
		    	}			
			}
		});
	}
	
	//========================================================================
	public void doGuiContactOffline( GuiOfferSession offerSession, int listPosition )
	{
		changeOfferState( offerSession, EOfferState.eOfferStateUserOffline );
		int removeIdx = 0;
	   	for( GuiOfferSession sessionState:  m_OfferStateList )
    	{
    		if( 0 == offerSession.getHisIdent().getOnlineId().compareTo( sessionState.getHisIdent().getMyOnlineId() )
    			&& ( offerSession.getPluginType() == sessionState.getPluginType() ) )
    		{
    			m_OfferStateList.remove( removeIdx );
    			break;
    		}
    		
    		removeIdx++;
    	}

		for( ToGuiOfferInterface callbackClient:  m_OfferCallbackList )
    	{
    		callbackClient.doGuiOfferRemoved( offerSession );
    	}	    			
	}
	
	//========================================================================
	private void updateOurSessionStateBySessionIdOrOnlineId( VxGUID offerSessionId, VxGUID onlineId, EOfferState newOfferState )
	{
		// first try by session id
	   	for( GuiOfferSession sessionState:  m_OfferStateList )
    	{
    		if( 0 == sessionState.getOfferSessionId().compareTo( offerSessionId ) )
    		{
    			sessionState.setOfferState( newOfferState );
    			return;
    		}
    	}
		   	
		// as backup try by online id
	   	for( GuiOfferSession sessionState:  m_OfferStateList )
    	{
    		if( 0 == sessionState.getHisIdent().getOnlineId().compareTo( onlineId ) )
    		{
    			sessionState.setOfferState( newOfferState );
    			return;
    		}
    	}
	}

	//========================================================================
	public void changeOfferState( GuiOfferSession sessionState, EOfferState newOfferState )
	{
		if( null == sessionState )
		{
			Log.d( LOG_TAG, "NULL session State " );
			return;
		}
		
		switch( newOfferState )
		{
		case eOfferStateRxedOffer:
			// always play notify sound
			m_MyApp.playSoundFromThread( ESndDef.eSndDefNotify1 );
			NativeRxFrom.toGuiStatusMessage( sessionState.describeOffer() );
			// just in case thinks in session
			forceToNotInSession( sessionState );
			sessionState.setOfferState( newOfferState );
			startRingTimerIfNotInSession();	
			break;
		case eOfferStateSentAccept:
		case eOfferStateInSession:			
		case eOfferStateSentRejected:
		case eOfferStateWaitingReply:
			sessionState.setOfferState( newOfferState );
			stopRingTimer();	
			break;
			
		case eOfferStateOfferCanceled:
			sessionState.setOfferState( newOfferState );
			NativeRxFrom.toGuiStatusMessage( sessionState.getOnlineName() + " Canceled Offer " + sessionState.describePlugin() );
			m_MyApp.playSoundFromThread( ESndDef.eSndDefOfferRejected );
			break;
			
		case eOfferStateReplyBusy:
			sessionState.setOfferState( newOfferState );
			NativeRxFrom.toGuiStatusMessage( sessionState.getOnlineName() + " Is Too Busy For " + sessionState.describePlugin() );
			m_MyApp.playSoundFromThread( ESndDef.eSndDefBusy );
			break;
			
		case eOfferStateReplyAccept:
			sessionState.setOfferState( newOfferState );
			m_MyApp.playSoundFromThread( ESndDef.eSndDefOfferAccepted );
			NativeRxFrom.toGuiStatusMessage( sessionState.getOnlineName() + " Accepted Offer " + sessionState.describePlugin() );
			break;
			
		case eOfferStateReplyRejected:		
			sessionState.setOfferState( newOfferState );
			m_MyApp.playSoundFromThread( ESndDef.eSndDefOfferRejected );
			NativeRxFrom.toGuiStatusMessage( sessionState.getOnlineName() + " Rejected Offer " + sessionState.describePlugin() );
			break;
			
		case eOfferStateReplyCanceled:
			sessionState.setOfferState( newOfferState );
			m_MyApp.playSoundFromThread( ESndDef.eSndDefOfferRejected );
			NativeRxFrom.toGuiStatusMessage( sessionState.getOnlineName() + " Canceled Offer " + sessionState.describePlugin() );
			break;
			
		case eOfferStateReplyEndSession:
			sessionState.setOfferState( newOfferState );
			// dont play any sound m_MyApp.playSoundFromThread( ESndDef.eSndDefOfferRejected );
			NativeRxFrom.toGuiStatusMessage( sessionState.getOnlineName() + " Ended Session " + sessionState.describePlugin() );
			break;
			
		case eOfferStateUserOffline:
			sessionState.setOfferState( newOfferState );
			NativeRxFrom.toGuiStatusMessage( sessionState.getOnlineName() + " cannot " + sessionState.describePlugin() + " because is offline" );
			removeOfferSession( sessionState );
			return;
		
		default:
			Log.e( LOG_TAG, "changeOfferState Unknown Offer State " + newOfferState );
			break;
		}	

		updateOurSessionStateBySessionIdOrOnlineId( sessionState.getOfferSessionId(), sessionState.getHisIdent().getOnlineId(), newOfferState );

		for( ToGuiOfferInterface callbackClient:  m_OfferCallbackList )
    	{
			callbackClient.doGuiUpdatePluginOffer( sessionState );
    	}
	}
	
	//========================================================================
	public void forceToNotInSession( GuiOfferSession sessionState )
	{
		EOfferState oldOfferState = sessionState.getOfferState();
		if( ( EOfferState.eOfferStateWaitingReply == oldOfferState )
			||	( EOfferState.eOfferStateInSession == oldOfferState ) )	
		{
			Log.e( LOG_TAG, "forceToNotInSession " + sessionState.getHisIdent().getOnlineName() + " " + sessionState.describePlugin() );
			sessionState.setOfferState( EOfferState.eOfferStateUnknown );
		}
	}
	
	//========================================================================
	public void startRingTimerIfNotInSession()
	{
		if( false == m_UserIsInSession )
		{
			m_RingTimerSecondCnt				= RING_ELAPSE_SEC;	
			m_RingTimerCycleCnt					= RING_COUNT;
		}	
	}
	
	//========================================================================
	public void stopRingTimer()
	{
		m_RingTimerCycleCnt					= 0;
		m_RingTimerSecondCnt				= 0;		
	}
	
	//========================================================================
	public void onOncePerSecond() 
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
				m_MyApp.playSoundFromThread( ESndDef.eSndDefOfferStillWaiting );
			}			
		}		
	}

	//========================================================================
	public void recievedOffer( int ePluginType, VxGUID lclSessionId, VxNetIdent hisIdent )
	{
		
	}

	//========================================================================
	public void sentOffer( int ePluginType, VxGUID lclSessionId, VxNetIdent hisIdent )
	{
		
	}

	//========================================================================
	public void recievedOfferReply( int ePluginType, VxGUID lclSessionId, VxNetIdent hisIdent, int eOfferResponse )
	{
		
	}

	//========================================================================
	public void recievedSessionEnd( int ePluginType, VxGUID lclSessionId, VxNetIdent hisIdent, int eOfferResponse )
	{
		
	}

	//========================================================================
	public void sentOfferReply( int ePluginType, VxGUID lclSessionId, VxNetIdent hisIdent, int eOfferResponse )
	{
		
	}
	
	//========================================================================
	public void startedSessionInReply( int ePluginType, VxGUID offerSessionId, VxNetIdent hisIdent )
	{
    	lockOffersMgr();
    	if( GuiHelpers.isPluginSingleSession( ePluginType ) )
		{
			removeOfferByOnlineId( ePluginType, hisIdent.getMyOnlineId() );			
		}
		else
		{
			removeOfferBySessionId( offerSessionId );	
		}	
		
	   	unlockOffersMgr();
	}

	//========================================================================
	public void onIsInSession( int ePluginType, VxGUID offerSessionId, VxNetIdent hisIdent, boolean isInSession )
	{
    	lockOffersMgr();
		if( GuiHelpers.isPluginSingleSession( ePluginType ) )
		{
			removeOfferByOnlineId( ePluginType, hisIdent.getMyOnlineId() );
		}
		else
		{
			removeOfferBySessionId( offerSessionId );				
		}
		
	   	unlockOffersMgr();
	}

	//========================================================================
	public void contactWentOffline( VxNetIdent hisIdent )
	{
		
	}
	
	//========================================================================
	public void onSessionExit( int ePluginType, VxGUID lclSessionId, VxNetIdent hisIdent )
	{
		
	}
	
	//========================================================================
	protected GuiOfferSession findOrAddOfferSession( GuiOfferSession offerSession )
	{
		VxGUID thisSessionId = offerSession.getOfferSessionId();
		GuiOfferSession retSessionState = findOfferSession( thisSessionId, offerSession.getPluginType() );
		if( null == retSessionState )
		{
			retSessionState = offerSession;
			m_OfferStateList.add( retSessionState );
		}
		
		return retSessionState;
	}
	
	//========================================================================
	protected GuiOfferSession findOfferSession( VxGUID sessionId, int pluginType )
	{
		GuiOfferSession retSessionState = null;
	   	for( GuiOfferSession sessionState:  m_OfferStateList )
    	{
    		if( ( sessionState.getOfferSessionId().equals( sessionId ) )
    			&& ( sessionState.getPluginType() == pluginType ) )
    		{
    			retSessionState = sessionState;
    			break;
    		}
    	}
	   	
	   	return retSessionState;
	}
	
	//========================================================================
	private boolean removeOfferSession(  GuiOfferSession offerSession )
	{
		if( null == offerSession )
		{
			Log.e( LOG_TAG, "ERROR removeOfferSession null offerSession" );
			return false;
		}
		
		return removeOfferBySessionId( offerSession.getOfferSessionId() );
 	}
	
	//========================================================================
	public boolean removeOfferBySessionId( VxGUID offerSessionId )
	{
		if( null == offerSessionId )
		{
			Log.e( LOG_TAG, "ERROR removeOfferBySessionId null sessionId" );
			return false;
		}
		
		boolean offerRemoved = false;
  	    int iPosition = 0;
  	    GuiOfferSession sessionRemoved = null;
	   	for( GuiOfferSession sessionState:  m_OfferStateList )
    	{
    		if( sessionState.getOfferSessionId().equals( offerSessionId ) )
    		{
    			sessionRemoved = m_OfferStateList.get( iPosition );
    			m_OfferStateList.remove( iPosition );
    			offerRemoved = true;
    			break;
    		}
    		
    		iPosition++; 
    	}
	   	
	   	if( offerRemoved )
		{
			boolean allOffersRemoved = ( 0 == getTotalOfferCount() );
			for( ToGuiOfferInterface callbackClient:  m_OfferCallbackList )
	    	{
				if( allOffersRemoved )
				{
					callbackClient.doGuiAllOffersRemoved();
				}
				else
				{
					if( null != sessionRemoved )
					{
						callbackClient.doGuiOfferRemoved( sessionRemoved );
					}
				}
	    	}
		}		
   	
	   	return offerRemoved;
 	}
	
	//========================================================================
	public boolean removeOfferByOnlineId( int ePluginType, VxGUID onlineId )
	{
		if( null == onlineId )
		{
			Log.e( LOG_TAG, "ERROR removeOfferByOnlineId null onlineId" );
			return false;
		}
		
		boolean offerRemoved = false;
  	    int iPosition = 0;
  	    GuiOfferSession sessionRemoved = null;
	   	for( GuiOfferSession sessionState:  m_OfferStateList )
    	{
    		if( ( sessionState.getPluginType() == ePluginType )
    			&& ( sessionState.getHisIdent().getMyOnlineId().equals( onlineId ) ) )
    		{
    			sessionRemoved = m_OfferStateList.get( iPosition );
    			m_OfferStateList.remove( iPosition );
    			offerRemoved = true;
    			break;
    		}
    		
    		iPosition++; 
    	}
	   	
		if( offerRemoved )
		{
			boolean allOffersRemoved = ( 0 == getTotalOfferCount() );
			for( ToGuiOfferInterface callbackClient:  m_OfferCallbackList )
	    	{
				if( allOffersRemoved )
				{
					callbackClient.doGuiAllOffersRemoved();
				}
				else
				{
					if( null != sessionRemoved )
					{
						callbackClient.doGuiOfferRemoved( sessionRemoved );
					}
				}
	    	}
		}		
   	
	   	return offerRemoved;
 	}
	
	//========================================================================
	@Override
	public int getTotalOfferCount()
	{
		return m_OfferStateList.size();
	}

	//========================================================================
	@Override
	public GuiOfferSession getTopGuiOfferSession()
	{
		if( 0 != m_OfferStateList.size() )
		{
			return m_OfferStateList.get( 0 );
		}
		
		return null;
	}
	
	//========================================================================
	public void offerAcknowlegedByUser( GuiOfferSession offerSession )
	{
		if( null == offerSession )
		{
			return;
		}
		
		lockOffersMgr();
		stopRingTimer();
		removeOfferSession( offerSession );
		unlockOffersMgr();
	}

	//========================================================================
	@Override
	public void wantToGuiOfferCallbacks( ToGuiOfferInterface clientInterface, boolean wantCallbacks )
	{
		if( null == clientInterface )
		{
			Log.e( LOG_TAG, "NULL client removeToGuiMessageClient" );
			return;
		}
		
  	    int listIdx = 0;
		lockOffersMgr();
		for( ToGuiOfferInterface callbackClient:  m_OfferCallbackList )
    	{
    		if( callbackClient == clientInterface )
    		{
    			if( wantCallbacks )
    			{
    				// already in list
    				unlockOffersMgr();
    				return;
    			}
    			else
    			{
    				m_OfferCallbackList.remove( listIdx );
    				// already in list
    				unlockOffersMgr();
    				return;
    			}
    		}
    		
    		listIdx++; 
    	}
		
		if( wantCallbacks )
		{
			m_OfferCallbackList.add( clientInterface );
		}
		
		unlockOffersMgr();	
	}

	//========================================================================
	public GuiOfferSession findAvailableAndActiveOffer( int ePluginType, VxNetIdent netIdent )
	{
	   	for( GuiOfferSession offerSession:  m_OfferStateList )
    	{
    		VxNetIdent oIdent = offerSession.getHisIdent();
    		if( ( oIdent.m_u64IdLoPart == netIdent.m_u64IdLoPart ) &&
    			( oIdent.m_u64IdHiPart == netIdent.m_u64IdHiPart ) &&
    			( offerSession.m_ePluginType == ePluginType ) )
    		{
    			return offerSession;
     		}   		
    	}
	   	
		return null;
	}

}


