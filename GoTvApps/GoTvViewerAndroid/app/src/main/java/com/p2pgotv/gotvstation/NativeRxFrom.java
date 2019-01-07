package com.p2pgotv.gotvstation;

import java.util.ArrayList;
import java.util.UUID;
import java.util.concurrent.Semaphore;

import android.util.Log;
import android.view.View;

public class NativeRxFrom 
{
	//=== constants ===// 
	private static final String LOG_TAG = "NativeRxFrom:";

	//=== activity vars ===//  
	private static MyApp 					m_MyApp;             
	private static UUID 					m_UuidTmp = null;
	private static ArrayList<MediaCallbackInterface> 	m_MediaCallbackList 			= new ArrayList<MediaCallbackInterface>();
	private static ArrayList<AssetCallbackInterface> 	m_AssetCallbackList 			= new ArrayList<AssetCallbackInterface>();
	private static ArrayList<ToGuiActivityInterface> 	m_ToGuiActivityList 			= new ArrayList<ToGuiActivityInterface>();
	private static ArrayList<ToGuiMessageInterface> 	m_ToGuiMessageList 				= new ArrayList<ToGuiMessageInterface>();
	private static ArrayList<ToGuiSearchInterface> 		m_ToGuiSearchList 				= new ArrayList<ToGuiSearchInterface>();
	private static ArrayList<ToGuiFileXferInterface> 	m_ToGuiFileXferClientList 		= new ArrayList<ToGuiFileXferInterface>();	
	private static ArrayList<ToGuiNetworkStateInterface>m_ToGuiNetworkStateClientList 	= new ArrayList<ToGuiNetworkStateInterface>();	
	private static ArrayList<ToGuiHardwareControlInterface>m_ToGuiHardwareControlList 	= new ArrayList<ToGuiHardwareControlInterface>();	
	private static ArrayList<ToGuiAssetMessageInterface>m_ToGuiAssetMsgList 			= new ArrayList<ToGuiAssetMessageInterface>();	

	private static Semaphore 							m_RxMutex 						= new Semaphore(1); 
	private static Semaphore 							m_MsgListMutex 					= new Semaphore(1); 

	//========================================================================
	public NativeRxFrom(MyApp myApp) 
	{
		m_MyApp = myApp;  
	}
	
	//========================================================================
	public static MyApp getMyApp()
	{
		return m_MyApp; 
	}
	
	//========================================================================
	public static void lockNativeRxFrom( int instanceId )
	{
		//String strInstance = String.valueOf( instanceId );
		//Log.i( LOG_TAG, "lockNativeRxFrom " + strInstance );
		try 
		{
			m_RxMutex.acquire();
		} 
		catch (InterruptedException e) 
		{
			e.printStackTrace();
		}
	}
	
	//========================================================================
	public static void unlockNativeRxFrom( int instanceId )
	{
		//String strInstance = String.valueOf( instanceId );
		//Log.i( LOG_TAG, "unlockNativeRxFrom " + strInstance );
		m_RxMutex.release();
	}
	
	
	//========================================================================
	public static void lockMsgList( int instanceId )
	{
		//String strInstance = String.valueOf( instanceId );
		//Log.i( LOG_TAG, "lockMsgList " + strInstance );
		try 
		{
			m_MsgListMutex.acquire();
		} 
		catch (InterruptedException e) 
		{
			e.printStackTrace();
		}
	}
	
	//========================================================================
	public static void unlockMsgList( int instanceId )
	{
		//String strInstance = String.valueOf( instanceId );
		//Log.i( LOG_TAG, "unlockMsgList " + strInstance );
		m_MsgListMutex.release();
	}
	
	//========================================================================
	public static void toGuiLog( int logFlags, String strLogMsg )
	{	
		final String NATIVE_LOG_TAG = "toGuiLog:";
		int pluginNum = logFlags >> 16;
		if( 0 != pluginNum )
		{
			// plugin log
			lockMsgList( 44 );
	    	for( ToGuiMessageInterface callbackClient:  m_ToGuiMessageList )
	    	{
	    		callbackClient.toGuiPluginLogMessage( pluginNum, strLogMsg );
	    	}
			
			unlockMsgList( 44 );
		}
		else
		{
			// normal log
			switch( logFlags )
			{
			case LogHandler.LOG_FATAL:
			case LogHandler.LOG_SEVERE:			
			case LogHandler.LOG_ASSERT:			
			case LogHandler.LOG_ERROR:
				Log.e( NATIVE_LOG_TAG, strLogMsg );
				break;
			case LogHandler.LOG_WARN:
				Log.w( NATIVE_LOG_TAG, strLogMsg );
				break;		
			case LogHandler.LOG_DEBUG:
				Log.d( NATIVE_LOG_TAG, strLogMsg );
				break;
				
			default:
				Log.i( NATIVE_LOG_TAG, strLogMsg ); 
			}			
		}
		
		
		//LogHandler.logMsg( logFlags, strLogMsg );   
	} 
	
	//========================================================================
	public static void toGuiAppErr( int errorNum, String errMsg )
	{		
		LogHandler.appErr( errorNum, errMsg );   
	} 
	
	//========================================================================
	public static void toGuiStatusMessage( String strMsg )
	{
		//Log.i( LOG_TAG, "toGuiStatusMessage" );
//		if( null != m_MyApp )
//		{
//			LogHandler.logMsg( LogHandler.LOG_INFO, strMsg ); 
//		}	
		
		lockMsgList( 1 );
    	for( ToGuiMessageInterface callbackClient:  m_ToGuiMessageList )
    	{
    		callbackClient.toGuiStatusMessage( strMsg );
    	}
    	
    	unlockMsgList( 1 );
	}
	
	//========================================================================
	// NOTE: only call toGuiUserMessage from java.. not thread safe
	public static void toGuiUserMessage( String userMsg )
	{
		//Log.i( LOG_TAG, "toGuiUserMessage" );
		if( ( null != m_MyApp )
			&& 	( false == m_MyApp.getIsAppShuttingDown() ) )
		{
			//LogHandler.logMsg( LogHandler.LOG_INFO, userMsg ); 
			lockMsgList(97);
	    	for( ToGuiMessageInterface callbackClient:  m_ToGuiMessageList )
	    	{
	    		callbackClient.toGuiUserMessage( userMsg );
	    	}
	    	
	    	unlockMsgList(97);
		}		
	}
	
	//========================================================================
	// NOTE: only call toGuiUserMessage from java.. not thread safe
	public static void toGuiUserMessage( int stringResId )
	{		
		if( ( null != m_MyApp )
			&& 	( false == m_MyApp.getIsAppShuttingDown() ) )
		{
			lockMsgList(98);
			for( ToGuiMessageInterface callbackClient:  m_ToGuiMessageList )
			{
				callbackClient.toGuiUserMessage( stringResId );
			}
			
			unlockMsgList(98);
		}
	}
	
	//========================================================================
	public static void toGuiShutdownHardware()
	{
		LogHandler.logMsg( LogHandler.LOG_DEBUG, "toGuiShutdownHardware " );
		lockNativeRxFrom( 2 );
    	for( ToGuiHardwareControlInterface callbackClient:  m_ToGuiHardwareControlList )
    	{
    		callbackClient.doGuiShutdownHardware();
    	}
    	
    	unlockNativeRxFrom( 2 );	
	}

	//========================================================================
	public static void toGuiWantMicrophoneRecording( boolean wantMicInput )
	{
		LogHandler.logMsg( LogHandler.LOG_DEBUG, "toGuiWantMicrophoneRecording " + wantMicInput );
		if( ( null != m_MyApp.getMainActivity() )
			&& ( false == m_MyApp.getIsAppShuttingDown() ) )
		{
			final boolean enableMicInput = wantMicInput;
			m_MyApp.getMainActivity().runOnUiThread( new Runnable() 
			{
				public void run() 
				{
					lockNativeRxFrom( 3 );
			    	for( ToGuiHardwareControlInterface callbackClient:  m_ToGuiHardwareControlList )
			    	{
			    		callbackClient.doGuiWantMicrophoneRecording( enableMicInput );
			    	}
			    	
			    	unlockNativeRxFrom( 3 );	
				}
			});
		}
	}
	
	//========================================================================
	public static void toGuiWantSpeakerOutput( boolean wantSpeakerOutput )
	{
		Log.i( LOG_TAG, "NativeRxFrom toGuiWantSpeakerOutput" );
		if( ( null != m_MyApp.getMainActivity() )
				&& ( false == m_MyApp.getIsAppShuttingDown() ) )
		{
			final boolean enableSpeakerOutput = wantSpeakerOutput;
			m_MyApp.getMainActivity().runOnUiThread( new Runnable() 
			{
				public void run() 
				{
					lockNativeRxFrom( 4 );
			    	for( ToGuiHardwareControlInterface callbackClient:  m_ToGuiHardwareControlList )
			    	{
			    		callbackClient.doGuiWantSpeakerOutput( enableSpeakerOutput );
			    	}
			    	
			    	unlockNativeRxFrom( 4 );	
				}
			});
		}
	} 
	
	//========================================================================
	public static void	toGuiWantVideoCapture( boolean wantVideoCapture )
	{
		LogHandler.logMsg( LogHandler.LOG_DEBUG, "toGuiWantVideoCapture = " + wantVideoCapture );
		if( ( null != m_MyApp.getMainActivity() )
			&& ( false == m_MyApp.getIsAppShuttingDown() ) )
		{
			final boolean enableVideoCapture = wantVideoCapture;
			m_MyApp.getMainActivity().runOnUiThread( new Runnable() 
			{
				public void run() 
				{
					lockNativeRxFrom( 5 );
			    	for( ToGuiHardwareControlInterface callbackClient:  m_ToGuiHardwareControlList )
			    	{
			    		callbackClient.doGuiWantVideoCapture( enableVideoCapture );
			    	}
			    	
			    	unlockNativeRxFrom( 5 );	
				}
			});
		}
	}
	
	//========================================================================
	public static void handleHaveTextOffer( VxNetIdent hisIdent, boolean haveTextOffer )
	{
		NativeTxTo.fromGuiSetIdentHasTextOffers( hisIdent.getOnlineId().m_u64IdHiPart, hisIdent.getOnlineId().m_u64IdLoPart, haveTextOffer );
		lockNativeRxFrom( 6 );	
    	for( ToGuiNetworkStateInterface callbackClient:  m_ToGuiNetworkStateClientList )
    	{
    		callbackClient.doGuiSetIdentHasTextOffers( hisIdent, haveTextOffer );
    	}
    	
    	unlockNativeRxFrom( 6 );	
	}
		
	//========================================================================
	public static void toGuiPlayVideoFrame( long s64IdHiPart, long s64IdLoPart, byte[] pu8Jpg, int jpgDataLen, int motion0to100000 )
	{
		//Log.i( LOG_TAG, "toGuiPlayVideoFrame" );
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			VxGUID oOnlineId = new VxGUID( s64IdHiPart, s64IdLoPart );
			lockNativeRxFrom( 7 );
			
			//if( false == oOnlineId.equals( m_MyApp.getMyOnlineId() ) )
			//{
			//	Log.i( LOG_TAG, "toGuiPlayVideoFrame not my feed" );			
			//}
			
	    	for( MediaCallbackInterface callbackClient:  m_MediaCallbackList )
	    	{
	    		callbackClient.toGuiPlayVideoFrame( oOnlineId, pu8Jpg, jpgDataLen, motion0to100000 );
	    	}
	    		
	    	for( ToGuiActivityInterface activityClient:  m_ToGuiActivityList )
	    	{
	    		activityClient.toGuiPlayVideoFrame( oOnlineId, pu8Jpg, jpgDataLen, motion0to100000 );
	    	}
	    	
	    	unlockNativeRxFrom( 7 );		
		}
	}
	
	//========================================================================
	public static void toGuiNetworkTestResult( int result )
	{
		LogHandler.logMsg( LogHandler.LOG_DEBUG, "toGuiNetworkTestResult " + result );
	}
	
	//========================================================================
	public static void toGuiNetworkState( int eNetworkStateIn, String stateMsgIn )
	{
		if( m_MyApp.getIsAppShuttingDown() )
		{
			return;
		}

		final int eNetworkState		= eNetworkStateIn;
		final String stateMsg 		= stateMsgIn;
		m_MyApp.getMainActivity().runOnUiThread(new Runnable() 
		{
			public void run() 
			{
				String networkState = Constants.describeNetworkState( eNetworkState );
				String formatedMsg;
				if( (null != stateMsg) && ( 0 != stateMsg.length() ) )
				{
					formatedMsg = "#Network " + networkState + " " + stateMsg;
				}
				else
				{
					formatedMsg = "#Network " + networkState;
				}
				
				if( ( Constants.eNetworkStateTypeOnlineDirect	== eNetworkState )
					|| ( Constants.eNetworkStateTypeOnlineThroughRelay	== eNetworkState ) )
				{
					formatedMsg += m_MyApp.getMgrNetwork().describeDataNetwork();
				}
				
				toGuiUserMessage( formatedMsg ); 
				m_MyApp.setNetworkState( eNetworkState );
				for( ToGuiNetworkStateInterface callbackClient:  m_ToGuiNetworkStateClientList )
				{
					callbackClient.doGuiNetworkStateChange( eNetworkState );
		    	}			
			}
		});
	}
	
	//========================================================================
	public static void toGuiMyRelayStatus( int eRelayStatusIn, String msgIn )
	{
		if( m_MyApp.getIsAppShuttingDown() )
		{
			return;
		}
	
		final int eRelayStatus		= eRelayStatusIn;
		final String msg 			= msgIn;
		m_MyApp.getMainActivity().runOnUiThread(new Runnable() 
		{
			public void run() 
			{
				String relayStatus = Constants.describeRelayStatus( eRelayStatus );
				String  formatedMsg;
				if( (null != msg) && ( 0 != msg.length() ) )
				{
					formatedMsg = "#Relay " + msg;
				}
				else
				{
					formatedMsg = "#Relay " + relayStatus;
				}
		
				toGuiStatusMessage( formatedMsg );  
		
				if( Constants.eMyRelayStatusConnected == eRelayStatus )
				{
					//toGuiStatusMessage( "#Relay Connected " );
					if(null != m_MyApp)
					{
						m_MyApp.getMainActivity().toGuiMyRelayConnected( true );
					}
					/*
					if( ( Constants.eFriendViewMyProxies == m_MyApp.m_eLastSelectedWhichContactsToView ) ||
						( Constants.eFriendViewAllProxies == m_MyApp.m_eLastSelectedWhichContactsToView ) )
					{
						m_MyApp.refreshFriendList( Constants.eFriendViewEverybody );
					}*/
				}		
			}
		});
	}
	
	//========================================================================
	public static void toGuiAnchorStatus( int eAnchorStatusIn, String msgIn )
	{
		if( m_MyApp.getIsAppShuttingDown() )
		{
			return;
		}
		
		final int eAnchorStatus		= eAnchorStatusIn;
		final String msg 			= msgIn;
		m_MyApp.getMainActivity().runOnUiThread(new Runnable() 
		{
			public void run() 
			{		
				String  formatedMsg;
				if( (null != msg) && ( 0 != msg.length() ) )
				{
					formatedMsg = "\n#" + msg;
				}
				else
				{
					String anchorStatus = Constants.describeAnchorStatus( eAnchorStatus );
					formatedMsg = "\n#" + anchorStatus;
				}
		
				toGuiStatusMessage( formatedMsg );  
				m_MyApp.toGuiAnchorStatus( formatedMsg );
			}
		});
	}
	
	//========================================================================
	public static void toGuiIsPortOpenStatus( int eIsPortOpenStatusIn, String msgIn )
	{
		if( m_MyApp.getIsAppShuttingDown() )
		{
			return;
		}
		
		final int eIsPortOpenStatus		= eIsPortOpenStatusIn;
		final String msg 				= msgIn;
		m_MyApp.getMainActivity().runOnUiThread(new Runnable() 
		{
			public void run() 
			{		
				String  formatedMsg;
				if( (null != msg) && ( 0 != msg.length() ) )
				{
					formatedMsg = "#" + msg;
				}
				else
				{
					String portOpenStatus = Constants.describePortOpenStatus( eIsPortOpenStatus );
					formatedMsg = "#" + portOpenStatus + "\n";
				}
		
				toGuiStatusMessage( formatedMsg );  
				m_MyApp.toGuiIsPortOpenStatus( formatedMsg );
			}	
		});
	}

	//========================================================================
	public static void toGuiPhoneShakeStatus( int ePhoneShakeStatusIn, String msgIn )
	{
		if( m_MyApp.getIsAppShuttingDown() )
		{
			return;
		}
		
		final int ePhoneShakeStatus		= ePhoneShakeStatusIn;
		final String msg 				= msgIn;
		m_MyApp.getMainActivity().runOnUiThread(new Runnable() 
		{
			public void run() 
			{		
				String  formatedMsg;
				if( (null != msg) && ( 0 != msg.length() ) )
				{
					formatedMsg = "#" + msg;
				}
				else
				{
					String portOpenStatus = Constants.describePhoneShakeStatus( ePhoneShakeStatus );
					formatedMsg = "#" + portOpenStatus + "\n";
				}
		
				toGuiUserMessage( formatedMsg );  
				lockNativeRxFrom( 8 );		
		    	for( ToGuiSearchInterface callbackClient:  m_ToGuiSearchList )
		    	{
		    		callbackClient.toGuiPhoneShakeStatus( formatedMsg );
		    	}
		    	
		    	unlockNativeRxFrom( 8 );		
			}	
		});
	}
	
	//========================================================================
	public static void toGuiContactOnline( VxNetIdent netIdent, boolean newContact )
	{
		//Log.i(LOG_TAG, "toGuiContactOnline start");
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			//friendIdent.debugDumpIdent();
			m_MyApp.getMainActivity().UpdateFriend( netIdent, false );			
			lockNativeRxFrom( 9 );
	    		
	    	for( ToGuiActivityInterface activityClient:  m_ToGuiActivityList )
	    	{
	    		activityClient.toGuiContactOnline( netIdent, newContact );
	    	}
	    	
	    	unlockNativeRxFrom( 9 );		
		}
		
		//Log.i(LOG_TAG, "toGuiContactOnline done");
	}
	
	//========================================================================
	public static void toGuiContactOffline( VxNetIdent netIdent )
	{
		//Log.i(LOG_TAG, "toGuiContactOffline start");
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			//friendIdent.debugDumpIdent();
			m_MyApp.getMainActivity().UpdateFriend( netIdent, false );
			lockNativeRxFrom( 10 );			
			m_MyApp.getOffersMgr().toGuiContactOffline( netIdent );
	    	for( ToGuiActivityInterface activityClient:  m_ToGuiActivityList )
	    	{
	    		activityClient.toGuiContactOffline( netIdent );
	    	}
	    	
	    	unlockNativeRxFrom( 10 );		
		}
		
		//Log.i(LOG_TAG, "toGuiContactOffline done");
	}
	
	//========================================================================
	public static void toGuiContactNearby( VxNetIdent netIdent )
	{
		Log.i(LOG_TAG, "toGuiContactNearby");
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			netIdent.debugDumpIdent();
			m_MyApp.getMainActivity().UpdateFriend( netIdent, false );
		}
	}
	
	//========================================================================
	public static void toGuiContactNotNearby( VxNetIdent netIdent )
	{
		Log.i(LOG_TAG, "toGuiContactNotNearby");
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			netIdent.debugDumpIdent();
			m_MyApp.getMainActivity().UpdateFriend( netIdent, false );
		}
	}
		
	//========================================================================
	public static void toGuiContactNameChange( VxNetIdent netIdent )
	{
		Log.i(LOG_TAG, "toGuiContactNameChange");
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			netIdent.debugDumpIdent();
			m_MyApp.getMainActivity().UpdateFriend( netIdent, false );
		}
	}
	
	//========================================================================
	public static void toGuiContactDescChange( VxNetIdent netIdent )
	{
		Log.i(LOG_TAG, "toGuiContactDescChange");
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			netIdent.debugDumpIdent();
			m_MyApp.getMainActivity().UpdateFriend( netIdent, false );
		}
	}
	
	//========================================================================
	public static void toGuiContactMyFriendshipChange( VxNetIdent netIdent )
	{
		Log.i(LOG_TAG, "toGuiContactMyFriendshipChange");
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			netIdent.debugDumpIdent();
			m_MyApp.getMainActivity().UpdateFriend( netIdent, false );
		}
	}
	
	//========================================================================
	public static void toGuiContactHisFriendshipChange( VxNetIdent netIdent )
	{
		Log.i(LOG_TAG, "toGuiContactHisFriendshipChange");
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			netIdent.debugDumpIdent();
			m_MyApp.getMainActivity().UpdateFriend( netIdent, false );
		}
	}
	
	//========================================================================
	public static void toGuiContactSearchFlagsChange( VxNetIdent netIdent )
	{
		Log.i(LOG_TAG, "toGuiContactSearchFlagsChange");
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			netIdent.debugDumpIdent();
			m_MyApp.getMainActivity().UpdateFriend( netIdent, false );
		}
	}
	
	//========================================================================
	public static void toGuiContactConnectionChange( VxNetIdent netIdent )
	{
		Log.i(LOG_TAG, "toGuiContactConnectionChange");
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			netIdent.debugDumpIdent();
			m_MyApp.getMainActivity().UpdateFriend( netIdent, false );
		}
	}
	
	//========================================================================
	public static void toGuiPluginPermissionChange( VxNetIdent netIdent )
	{
		Log.i(LOG_TAG, "toGuiPluginPermissionChange");
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			netIdent.debugDumpIdent();
			m_MyApp.getMainActivity().UpdateFriend( netIdent, false );
		}
	}
	
	//========================================================================
	public static void toGuiContactAnythingChange( VxNetIdent netIdent )
	{
		Log.i(LOG_TAG, "toGuiContactAnythingChange");
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			netIdent.debugDumpIdent();
			m_MyApp.getMainActivity().UpdateFriend( netIdent, false );
		}
	}
	
	//========================================================================
	public static void toGuiContactLastSessionTimeChange( VxNetIdent netIdent )
	{
		Log.i(LOG_TAG, "toGuiContactLastSessionTimeChange");
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			netIdent.debugDumpIdent();
			m_MyApp.getMainActivity().UpdateFriend( netIdent, true );
		}
	}

	//========================================================================
	public static void toGuiUpdateMyIdent( VxNetIdent netIdent )
	{
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			//LogHandler.logMsg( LogHandler.LOG_DEBUG, "toGuiUpdateMyIdent"); 
			//netIdent.debugDumpIdent();
			m_MyApp.toGuiUpdateMyIdent( netIdent );
		}
	}
	 
	//========================================================================
	//=== activity methods ===//
	//========================================================================
	//! add offer to notify list
	public static void	toGuiRxedPluginOffer( VxNetIdent friendIdent, 
												int ePluginType, 
												String offerMsg, 
												int pvUserData, 
												String fileName,
												byte[] fileHash, 
												long lclIdHiPart, 
												long lclIdLoPart, 
												long rmtIdHiPart, 
												long rmtIdLoPart )
	{
		Log.i( LOG_TAG, "toGuiRxedPluginOffer from " + friendIdent.m_as8OnlineName );
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			lockNativeRxFrom( 12 );
			
			VxGUID lclSessionId = new VxGUID( lclIdHiPart, lclIdLoPart );
			VxGUID rmtSessionId = new VxGUID( rmtIdHiPart, rmtIdLoPart );
			GuiOfferSession offerSession = new GuiOfferSession();
			offerSession.m_HisIdent 		= friendIdent;
			offerSession.m_ePluginType 		= ePluginType;
			offerSession.m_strMsg 			= offerMsg;
			offerSession.m_pvUserData 		= pvUserData;
			offerSession.m_strFileName 		= fileName;
			offerSession.setLclSessionId( lclSessionId );
			offerSession.setRmtSessionId( rmtSessionId );
			offerSession.m_FileHash			= fileHash;
			offerSession.assuredValidLclSessionId();
			
			m_MyApp.getOffersMgr().toGuiRxedPluginOffer( offerSession );
			
			for( ToGuiActivityInterface callbackClient:  m_ToGuiActivityList )
	    	{
	    		callbackClient.toGuiRxedPluginOffer( offerSession );
	    	}
	 		
	    	unlockNativeRxFrom( 12 );		
		}
		
		Log.i( LOG_TAG, "toGuiRxedPluginOffer done" );
	}
	
	//========================================================================
	//! response to offer
	public static void	toGuiRxedOfferReply(	VxNetIdent 	friendIdent, 
												int 		ePluginType, 
												int 		pvUserData, 
												int			eOfferResponse, 
												String 		fileName,
												byte[] 		fileHash, 
												long 		lclIdHiPart, 
												long 		lclIdLoPart, 
												long 		rmtIdHiPart, 
												long 		rmtIdLoPart )
	{
		Log.i( LOG_TAG, "toGuiRxedOfferReply start" ); 
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			lockNativeRxFrom( 13 );
			
			VxGUID lclSessionId = new VxGUID( lclIdHiPart, lclIdLoPart );
			VxGUID rmtSessionId = new VxGUID( rmtIdHiPart, rmtIdLoPart );
			GuiOfferSession offerSession = new GuiOfferSession();
			offerSession.m_HisIdent 		= friendIdent;
			offerSession.m_ePluginType 		= ePluginType;
			offerSession.m_pvUserData 		= pvUserData;
			offerSession.m_eOfferResponse	= eOfferResponse;
			offerSession.m_strFileName 		= fileName;
			offerSession.m_FileHash			= fileHash;
			offerSession.setLclSessionId( lclSessionId );
			offerSession.setRmtSessionId( rmtSessionId );
			offerSession.assuredValidLclSessionId();
			
			m_MyApp.getOffersMgr().toGuiRxedOfferReply( offerSession );
				
	    	for( ToGuiActivityInterface callbackClient:  m_ToGuiActivityList )
	    	{
	    		callbackClient.toGuiRxedOfferReply( offerSession );
	    	}
	 		
	    	unlockNativeRxFrom( 13 );		
		}
		
		Log.i( LOG_TAG, "toGuiRxedOfferReply done" ); 
	}
	
	//========================================================================
	public static void	toGuiPluginSessionEnded(	VxNetIdent 	friendIdent, 
													int 		ePluginType, 
													int 		pvUserData, 
													int			eOfferResponse, 
													long 		lclIdHiPart, 
													long 		lclIdLoPart )
	{
		Log.i( LOG_TAG, "toGuiPluginSessionEnded start" );
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			lockNativeRxFrom( 14 );
			
			VxGUID lclSessionId = new VxGUID( lclIdHiPart, lclIdLoPart );
			GuiOfferSession offerSession = new GuiOfferSession();
			offerSession.m_HisIdent 		= friendIdent;
			offerSession.m_ePluginType 		= ePluginType;
			offerSession.m_pvUserData 		= pvUserData;
			offerSession.m_eOfferResponse	= eOfferResponse;
			offerSession.setLclSessionId( lclSessionId );
			offerSession.assuredValidLclSessionId();
			
			m_MyApp.getOffersMgr().toGuiPluginSessionEnded( offerSession );
			
	    	for( ToGuiActivityInterface callbackClient:  m_ToGuiActivityList )
	    	{
	    		callbackClient.toGuiPluginSessionEnded( offerSession );
	    	}
	 		
	    	unlockNativeRxFrom( 14 );		
		}
		
		Log.i( LOG_TAG, "toGuiPluginSessionEnded done" );
	}
	
	//========================================================================
	public static void	toGuiPluginStatus(	int 		ePluginType,
											int			statusType,
											int			statusValue )
	{
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			final int finalPluginType		= ePluginType;
			final int finalStatusType 		= statusType;
			final int finalStatusValue 		= statusValue;			
			m_MyApp.getMainActivity().runOnUiThread(new Runnable() 
			{
				public void run() 
				{
					Log.i( LOG_TAG, "toGuiPluginStatus " );
			    	for( ToGuiMessageInterface callbackClient:  m_ToGuiMessageList )
			    	{
			    		callbackClient.doToGuiPluginStatus( finalPluginType, finalStatusType, finalStatusValue );
			    	}
				}
			});
		}
	}
	
	//========================================================================
	public static void	toGuiInstMsg(	VxNetIdent 	netIdent, 
										int 		iPluginTypeIn,
										String		strMsgIn )
	{
		//Log.i( LOG_TAG, "toGuiInstMsg msg " + strMsgIn + " from " + netIdent.getOnlineName() );
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			lockNativeRxFrom( 15 );		
	    	for( ToGuiActivityInterface callbackClient:  m_ToGuiActivityList )
	    	{
	    		callbackClient.toGuiInstMsg( netIdent, iPluginTypeIn, strMsgIn );
	    	}
	 		
	    	unlockNativeRxFrom( 15 );		
		}
		
		//Log.i( LOG_TAG, "toGuiInstMsg msg done " );
	}

	//========================================================================
	public static void toGuiFileList(	String			fileName,
										long			fileLen, 										
										int				fileType, 
										boolean			isInLibrary,
										boolean			isShared,
										byte[]			fileHash )
	{
		//Log.i( LOG_TAG, "toGuiFileList start" );													
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			VxFileInfo fileInfo = new VxFileInfo( fileName, fileLen, fileType, fileHash );
			fileInfo.setIsInLibrary( isInLibrary );
			fileInfo.setIsShared( isShared );
			fileInfo.setFilePath( m_MyApp.removeRootStorageDir( fileInfo.getFilePath() ) );
			lockNativeRxFrom( 16 );		
	    	for( ToGuiFileXferInterface callbackClient: m_ToGuiFileXferClientList )
	    	{
	    		callbackClient.toGuiFileList( fileInfo );
	    	}
	 		
	    	unlockNativeRxFrom( 16 );		
		}
		
		//Log.i( LOG_TAG, "toGuiFileList done" );			
	}
	
	//========================================================================
	public static void toGuiFileListReply(			VxNetIdent		netIdent, 
													int				ePluginType, 
													int				fileType, 
													long			fileLen, 
													String			fileName,
													byte[]			fileHash )
	{
		//Log.i( LOG_TAG, "toGuiFileListReply start" );													
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			VxGUID lclSession = new VxGUID( 0, 0);
			GuiFileXferSession xferSession = new GuiFileXferSession( netIdent, ePluginType, lclSession, fileType, fileLen, fileName, fileHash );
			lockNativeRxFrom( 17 );		
	    	for( ToGuiFileXferInterface callbackClient:  m_ToGuiFileXferClientList )
	    	{
	    		callbackClient.toGuiFileListReply( xferSession );
	    	}
	 		
	    	unlockNativeRxFrom( 17 );		
		}
		
		//Log.i( LOG_TAG, "toGuiFileListReply done" );	
	}

	//========================================================================
	public static void	toGuiStartUpload(	VxNetIdent		netIdent, 
											int				ePluginType,
											long			fileInstanceIdHi, 
											long			fileInstanceIdLo, 
											int				fileType, 
											long			fileLen, 
											String			fileName,
											byte[]			fileHash )
	{
		//Log.i( LOG_TAG, "toGuiStartUpload start " );
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			VxGUID lclSession = new VxGUID( fileInstanceIdHi, fileInstanceIdLo );
			GuiFileXferSession xferSession = new GuiFileXferSession( netIdent, ePluginType, lclSession, fileType, fileLen, fileName, fileHash );
			lockNativeRxFrom( 18 );		
			m_MyApp.getUploadsAdapter().toGuiStartUpload( xferSession );
	    	for( ToGuiFileXferInterface callbackClient:  m_ToGuiFileXferClientList )
	    	{
	    		callbackClient.toGuiStartUpload( xferSession );
	    	}
	 		
	    	unlockNativeRxFrom( 18 );		
		}
		
		//Log.i( LOG_TAG, "toGuiStartUpload done " );
	}
	
	//========================================================================
	public static void	toGuiStartDownload(	VxNetIdent		netIdent, 
											int				ePluginType,
											long			fileInstanceIdHi, 
											long			fileInstanceIdLo, 
											int				fileType, 
											long			fileLen, 
											String			fileName,
											byte[]			fileHash )
	{
		//Log.i( LOG_TAG, "toGuiStartDownload start " );
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			VxGUID lclSession = new VxGUID( fileInstanceIdHi, fileInstanceIdLo );
			GuiFileXferSession xferSession = new GuiFileXferSession( netIdent, ePluginType, lclSession, fileType, fileLen, fileName, fileHash );
			lockNativeRxFrom( 19 );
			m_MyApp.getDownloadsAdapter().toGuiStartDownload( xferSession );
	    	for( ToGuiFileXferInterface callbackClient:  m_ToGuiFileXferClientList )
	    	{
	    		callbackClient.toGuiStartDownload( xferSession );
	    	}
	 		
	    	unlockNativeRxFrom( 19 );		
		}
		
		//Log.i( LOG_TAG, "toGuiStartDownload done " );
	}

	//========================================================================
	public static void	toGuiFileXferState(	long			fileInstanceIdHi, 
											long			fileInstanceIdLo, 
											int				eXferState, 
											int				param1,
											int				param2 )
	{
		//Log.i( LOG_TAG, "toGuiFileXferState" );
		//Log.i( LOG_TAG, "toGuiFileXferState start " );
		VxGUID lclSession = new VxGUID( fileInstanceIdHi, fileInstanceIdLo );
		lockNativeRxFrom( 20 );		
		
		switch( eXferState )
		{
		case Constants.eXferStateUploadNotStarted:
		case Constants.eXferStateWaitingOfferResponse:
		case Constants.eXferStateInUploadQue:
		case Constants.eXferStateBeginUpload:
		case Constants.eXferStateInUploadXfer:
		case Constants.eXferStateCompletedUpload:
		case Constants.eXferStateUserCanceledUpload:
		case Constants.eXferStateUploadOfferRejected:
		case Constants.eXferStateUploadError:
			m_MyApp.getUploadsAdapter().toGuiFileXferState( lclSession, eXferState, param1, param2 );
			break;

		case Constants.eXferStateDownloadNotStarted:
		case Constants.eXferStateBeginDownload:
		case Constants.eXferStateInDownloadXfer:
		case Constants.eXferStateCompletedDownload:
		case Constants.eXferStateUserCanceledDownload:
		case Constants.eXferStateDownloadError:
			m_MyApp.getDownloadsAdapter().toGuiFileXferState( lclSession, eXferState, param1, param2 );
		
		}
 		
    	for( ToGuiFileXferInterface callbackClient:  m_ToGuiFileXferClientList )
    	{
    		callbackClient.toGuiFileXferState( lclSession, eXferState, param1, param2 );
    	}

    	unlockNativeRxFrom( 20 );	
    	//Log.i( LOG_TAG, "toGuiFileXferState done " );
	}

	//========================================================================
	public static void	toGuiFileDownloadComplete(	long			fileInstanceIdHi, 
													long			fileInstanceIdLo, 
													String 			newFileName, 
													int				xferError )
	{
		//Log.i( LOG_TAG, "toGuiFileDownloadComplete start " );
		m_MyApp.playSoundFromThread( ESndDef.eSndDefFileXferComplete );
		VxGUID lclSession = new VxGUID( fileInstanceIdHi, fileInstanceIdLo );
		lockNativeRxFrom( 21 );		
		m_MyApp.getDownloadsAdapter().toGuiFileDownloadComplete( lclSession, newFileName, xferError );

    	for( ToGuiFileXferInterface callbackClient:  m_ToGuiFileXferClientList )
    	{
    		callbackClient.toGuiFileDownloadComplete( lclSession, newFileName, xferError );
    	}
		 
 		
    	unlockNativeRxFrom( 21 );		
    	//Log.i( LOG_TAG, "toGuiFileDownloadComplete done " );
	}

	//========================================================================
	public static void	toGuiFileUploadComplete(		long			fileInstanceIdHi, 
														long			fileInstanceIdLo, 
														int				xferError )
	{
		//Log.i( LOG_TAG, "toGuiFileUploadComplete start" );
		VxGUID lclSession = new VxGUID( fileInstanceIdHi, fileInstanceIdLo );
		lockNativeRxFrom( 22 );		
		m_MyApp.getUploadsAdapter().toGuiFileUploadComplete( lclSession, xferError );
    	for( ToGuiFileXferInterface callbackClient:  m_ToGuiFileXferClientList )
    	{
    		callbackClient.toGuiFileUploadComplete( lclSession, xferError );
    	}
		
    	unlockNativeRxFrom( 22 );		
    	//Log.i( LOG_TAG, "toGuiFileUploadComplete done" );
	}
	
	//========================================================================
	// scan
	//========================================================================
	public static void	toGuiScanSearchComplete( int eScanType )
	{
		//Log.i( LOG_TAG, "toGuiScanSearchComplete start" );
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			lockNativeRxFrom( 23 );		
	    	for( ToGuiSearchInterface callbackClient:  m_ToGuiSearchList )
	    	{
	    		callbackClient.toGuiScanSearchComplete( eScanType );
	    	}
	    	
	    	unlockNativeRxFrom( 23 );		
		}	
		
		//Log.i( LOG_TAG, "toGuiScanSearchComplete done" );
	}
	
	//========================================================================
	public static void	toGuiScanSearchResultSuccess( int eScanType, VxNetIdent	netIdent )
	{
		//Log.i( LOG_TAG, "toGuiScanSearchResultSuccess start" );
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			lockNativeRxFrom( 24 );		
	    	for( ToGuiSearchInterface callbackClient:  m_ToGuiSearchList )
	    	{
	    		callbackClient.toGuiScanSearchResultSuccess( eScanType, netIdent );
	    	}
	    	
	    	unlockNativeRxFrom( 24 );		
		}
		
		//Log.i( LOG_TAG, "toGuiScanSearchResultSuccess done" );
	}
	
	//========================================================================
	public static void toGuiScanSearchResultError( int eScanType, VxNetIdent netIdent, int errCode )
	{
		//Log.i( LOG_TAG, "toGuiScanSearchResultError start" );
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			lockNativeRxFrom( 25 );		
	    	for( ToGuiSearchInterface callbackClient:  m_ToGuiSearchList )
	    	{
	    		callbackClient.toGuiScanSearchResultError( eScanType, netIdent, errCode );
	    	}
	    	
	    	unlockNativeRxFrom( 25 );		
		}	
		
		//Log.i( LOG_TAG, "toGuiScanSearchResultError done" );
	}

	//========================================================================
	public static void	toGuiSearchResultProfilePic( VxNetIdent netIdent, byte[] jpgData, int jpgDataLen )
	{
		//Log.i( LOG_TAG, "toGuiSearchResultProfilePic start" );
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			lockNativeRxFrom( 26 );		
	    	for( ToGuiSearchInterface callbackClient:  m_ToGuiSearchList )
	    	{
	    		callbackClient.toGuiSearchResultProfilePic( 	netIdent, jpgData, jpgDataLen );
	    	}
	    	
	    	unlockNativeRxFrom( 26 );		
		}		
		
		//Log.i( LOG_TAG, "toGuiSearchResultProfilePic done" );
	}
	
	//========================================================================
	public static void	toGuiSearchResultFileSearch( 
							VxNetIdent		netIdent, 		
							long 			sessionIdHiPart, 
							long 			sessionIdLoPart, 
							int				u8FileType, 
							long			u64FileLen, 
							String			pFileName )
	{
		//Log.i( LOG_TAG, "toGuiSearchResultFileSearch start" );
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			VxGUID sessionId = new VxGUID( sessionIdHiPart, sessionIdLoPart );
			lockNativeRxFrom( 27 );		
	    	for( ToGuiSearchInterface callbackClient:  m_ToGuiSearchList )
	    	{
	    		callbackClient.toGuiSearchResultFileSearch( netIdent, sessionId, u8FileType, u64FileLen, pFileName );
	    	}
	    	
	    	unlockNativeRxFrom( 27 );		
		}		
		
		//Log.i( LOG_TAG, "toGuiSearchResultFileSearch done" );
	}
	
	//========================================================================
	public static void	toGuiSetGameValueVar( int iPlugin, long sessionIdHiPart, long sessionIdLoPart, int s32VarId, int s32VarValue )
	{
		//Log.i( LOG_TAG, "toGuiSetGameValueVar start" );	
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			Log.i( LOG_TAG, "toGuiMultiSessionAction" );
			VxGUID sessionId = new VxGUID( sessionIdHiPart, sessionIdLoPart );
			lockNativeRxFrom( 28 );		
	    	for( ToGuiActivityInterface callbackClient:  m_ToGuiActivityList )
	    	{
	    		callbackClient.toGuiSetGameValueVar( iPlugin, sessionId, s32VarId, s32VarValue );
	    	}
	 		
	    	unlockNativeRxFrom( 28 );		
		}
	
		//Log.i( LOG_TAG, "toGuiSetGameValueVar done" );	
	}

	//========================================================================
	public static void	toGuiSetGameActionVar( int iPlugin, long sessionIdHiPart, long sessionIdLoPart, int s32VarId, int s32VarValue )
	{
		//Log.i( LOG_TAG, "toGuiSetGameActionVar start" );		
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			Log.i( LOG_TAG, "toGuiMultiSessionAction" );
			VxGUID sessionId = new VxGUID( sessionIdHiPart, sessionIdLoPart );
			lockNativeRxFrom( 29 );		
	    	for( ToGuiActivityInterface callbackClient:  m_ToGuiActivityList )
	    	{
	    		callbackClient.toGuiSetGameActionVar( iPlugin, sessionId, s32VarId, s32VarValue );
	    	}
	 		
	    	unlockNativeRxFrom( 29 );		
		}
		
		//Log.i( LOG_TAG, "toGuiSetGameActionVar done" );		
	}
	
	//========================================================================
	public static long	toGuiGenerateGuidHiPart()
	{
		m_UuidTmp = UUID.randomUUID(); 
	 	return m_UuidTmp.getMostSignificantBits();	
	}

	//========================================================================
	public static long	toGuiGenerateGuidLoPart()
	{
	 	return m_UuidTmp.getLeastSignificantBits();	
	}
	
	//============================================================================
	public static void	toGuiAssetAdded( AssetGuiInfo assetInfo )
	{
		if( m_MyApp.getIsAppShuttingDown() )
		{
			return;
		}

		//Log.i( LOG_TAG, "toGuiAssetAdded start" );
		lockNativeRxFrom( 30 );	
		final AssetGuiInfo lclAssetInfo = assetInfo; 
		boolean isMyAsset = ( 0 == assetInfo.getCreatorId().compareTo( m_MyApp.getMyOnlineId() ) );
    	for( AssetCallbackInterface callbackClient:  m_AssetCallbackList )
    	{
    		callbackClient.toGuiAssetAdded( lclAssetInfo );
    	}
 		
    	unlockNativeRxFrom( 30 );		
    	//Log.i( LOG_TAG, "toGuiAssetAdded done" );
    	if( false == isMyAsset )
    	{
    		m_MyApp.playSoundFromThread( ESndDef.eSndDefUserBellMessage );
    	}
	}

	//============================================================================
	public static void	toGuiSessionHistory( AssetGuiInfo assetInfo )
	{
		if( m_MyApp.getIsAppShuttingDown() )
		{
			return;
		}
		
		//Log.i( LOG_TAG, "toGuiSessionHistory start" );
		lockNativeRxFrom( 31 );		
    	for( AssetCallbackInterface callbackClient:  m_AssetCallbackList )
    	{
    		callbackClient.toGuiSessionHistory( assetInfo );
    	}
 		
    	unlockNativeRxFrom( 31 );	
    	//Log.i( LOG_TAG, "toGuiSessionHistory done" );
	}

	//============================================================================
	public static void	toGuiAssetAction(	int			assetAction, 
											long		assetIdHi, 
											long		assetIdLo, 
											int			actionParam )
	{
		if( m_MyApp.getIsAppShuttingDown() )
		{
			return;
		}

		Log.i( LOG_TAG, "toGuiAssetAction start assetAction=" + String.valueOf( assetAction ) + 
				" assetParm=" + String.valueOf( actionParam ) + 
				" assetIdHi=" + String.valueOf( assetIdHi ) + 
				" assetIdLo=" + String.valueOf( assetIdLo ) );
		//Log.i( LOG_TAG, "toGuiAssetAction start" );
		VxGUID assetId = new VxGUID( assetIdHi, assetIdLo );
		lockNativeRxFrom( 32 );		
		if( ( Constants.eAssetActionRxNotifyNewMsg == assetAction )
			|| ( Constants.eAssetActionRxViewingMsg == assetAction ) )
		{
			if( Constants.eAssetActionRxNotifyNewMsg == assetAction )
			{
		    	for( ToGuiAssetMessageInterface callbackClient:  m_ToGuiAssetMsgList )
		    	{
		    		callbackClient.toGuiNewAssetMessage( assetAction, assetId, actionParam );
		    	}						
			}
			else
			{
		    	for( ToGuiAssetMessageInterface callbackClient:  m_ToGuiAssetMsgList )
		    	{
		    		callbackClient.doGuiAssetViewingMessage( assetAction, assetId, actionParam );
		    	}		
			}
		}
		else
		{
			//Log.i( LOG_TAG, " assetAction=" + String.valueOf( assetAction ) + " assetParm=" + String.valueOf( actionParam ) );
			if( 0 != m_AssetCallbackList.size() )
			{	
		    	for( AssetCallbackInterface callbackClient:  m_AssetCallbackList )
		    	{
		    		callbackClient.toGuiAssetAction( assetAction, assetId, actionParam );
		    	}
			}
//			else
//			{
//				Log.i( LOG_TAG, "NO CLIENTS TO CALL FOR assetAction=" + String.valueOf( assetAction ) + " assetParm=" + String.valueOf( actionParam ) );			
//			}
		}
		
    	unlockNativeRxFrom( 32 );	
    	Log.i( LOG_TAG, "toGuiAssetAction done" );
	}

	//============================================================================
	public static void	toGuiMultiSessionAction(	int			sessionAction, 
													long		onlineIdHi, 
													long		onlineIdLo, 
													int			actionParam )
	{
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			//Log.i( LOG_TAG, "toGuiMultiSessionAction start" );
			VxGUID onlineId = new VxGUID( onlineIdHi, onlineIdLo );
			lockNativeRxFrom( 33 );		
	    	for( ToGuiActivityInterface callbackClient:  m_ToGuiActivityList )
	    	{
	    		callbackClient.toGuiMultiSessionAction( sessionAction, onlineId, actionParam );
	    	}
	 		
	    	unlockNativeRxFrom( 33 );	
	    	//Log.i( LOG_TAG, "toGuiMultiSessionAction done" );
		}
	}
	
	//========================================================================
	public static void onFileXferFileIconButClick( View v )
	{
		//Log.i( LOG_TAG, "onFileXferFileIconButClick start" );
		lockNativeRxFrom( 34 );		
    	for( ToGuiFileXferInterface callbackClient:  m_ToGuiFileXferClientList )
    	{
    		callbackClient.onFileXferFileIconButClick( v );
    	}
 		
    	unlockNativeRxFrom( 34 );	
    	//Log.i( LOG_TAG, "onFileXferFileIconButClick done" );
	}
    
	//========================================================================
	public static void onFileXferAcceptButClick( View v )
	{
		//Log.i( LOG_TAG, "onFileXferAcceptButClick start" );
		lockNativeRxFrom( 35 );		
    	for( ToGuiFileXferInterface callbackClient:  m_ToGuiFileXferClientList )
    	{
    		callbackClient.onFileXferAcceptButClick( v );
    	}
 		
    	unlockNativeRxFrom( 35 );	
    	//Log.i( LOG_TAG, "onFileXferAcceptButClick done" );
	}
    
	//========================================================================
	public static void onFileXferPlayButClick( View v )
	{
		//Log.i( LOG_TAG, "onFileXferPlayButClick start" );
		lockNativeRxFrom( 36 );		
    	for( ToGuiFileXferInterface callbackClient:  m_ToGuiFileXferClientList )
    	{
    		callbackClient.onFileXferPlayButClick( v );
    	}
 		
    	unlockNativeRxFrom( 36 );		
    	//Log.i( LOG_TAG, "onFileXferPlayButClick done" );
	}
    
	//========================================================================
	public static void onFileXferLibraryButClick( View v )
	{
		//Log.i( LOG_TAG, "onFileXferLibraryButClick start" );
		lockNativeRxFrom( 37 );		
    	for( ToGuiFileXferInterface callbackClient:  m_ToGuiFileXferClientList )
    	{
    		callbackClient.onFileXferLibraryButClick( v );
    	}
 		
    	unlockNativeRxFrom( 37 );	
    	//Log.i( LOG_TAG, "onFileXferLibraryButClick done" );
	}
    
	//========================================================================
	public static void onFileXferShareButClick( View v )
	{
		//Log.i( LOG_TAG, "onFileXferShareButClick start" );
		lockNativeRxFrom( 38 );		
    	for( ToGuiFileXferInterface callbackClient:  m_ToGuiFileXferClientList )
    	{
    		callbackClient.onFileXferShareButClick( v );
    	}
 		
    	unlockNativeRxFrom( 38 );	
    	//Log.i( LOG_TAG, "onFileXferShareButClick done" );
	}
    
	//========================================================================
	public static void onFileXferShredButClick( View v )
	{
		//Log.i( LOG_TAG, "onFileXferShredButClick start" );
		lockNativeRxFrom( 39 );		
    	for( ToGuiFileXferInterface callbackClient:  m_ToGuiFileXferClientList )
    	{
    		callbackClient.onFileXferShredButClick( v );
    	}
 		
    	unlockNativeRxFrom( 39 );		
    	//Log.i( LOG_TAG, "onFileXferShredButClick done" );
	}
	
	
	//========================================================================
	// NOTE: no lockNativeRxFrom used and not thread safe
	public static void wantToGuiMessageClient( ToGuiMessageInterface client, boolean wantCallbacks ) throws InterruptedException
	{
		if( null == client )
		{
			Log.e( LOG_TAG, "NULL client wantToGuiMessageClient" );
			return;
		}
		
		lockMsgList(99);
  	    int listIdx = 0;
    	for( ToGuiMessageInterface callbackClient:  m_ToGuiMessageList )
    	{
    		if( callbackClient == client )
    		{
    			if( wantCallbacks )
    			{
    				// already in list
    				unlockMsgList(99);
    				return;
    			}
    			else
    			{
    				m_ToGuiMessageList.remove( listIdx );
    				unlockMsgList(99);
    				return;
    			}
    		}
    		
    		listIdx++; 
    	}
	
    	if( wantCallbacks )
    	{
    		m_ToGuiMessageList.add(client);
    	}
    	
    	unlockMsgList(99);
	}
		
	//========================================================================
	public static void wantMediaCallbackClient( MediaCallbackInterface client, boolean wantCallbacks ) throws InterruptedException
	{
		if( null == client )
		{
			Log.e( LOG_TAG, "NULL client wantMediaCallbackClient" );
			return;
		}
		
		//Log.i( LOG_TAG, "wantMediaCallbackClient start" );
		lockNativeRxFrom( 40 );
   	    int listIdx = 0;
    	for( MediaCallbackInterface callbackClient:  m_MediaCallbackList )
    	{
    		if( callbackClient == client )
    		{
    			if( wantCallbacks )
    			{
    				// already in list
        	    	unlockNativeRxFrom( 40 );	
        	    	return;
    			}
    			else
    			{
        			m_MediaCallbackList.remove( listIdx );
        	    	unlockNativeRxFrom( 40 );	
        	    	return;
    			}
    		}
    		
    		listIdx++; 
    	}
 
		if( wantCallbacks )
		{
			//Log.d( LOG_TAG, "fromNetworkTesterTestLog adding " + strMsgIn );
			m_MediaCallbackList.add(client);
			//Log.d( LOG_TAG, "fromNetworkTesterTestLog release" );
		}
		
		unlockNativeRxFrom( 40 );	
		//Log.i( LOG_TAG, "wantMediaCallbackClient done" );
	}
		
	//========================================================================
	public static void wantAssetCallbackClient( AssetCallbackInterface client, boolean wantCallbacks ) throws InterruptedException
	{
		if( null == client )
		{
			Log.e( LOG_TAG, "NULL client wantAssetCallbackClient" );
			return;
		}
	
		//Log.i( LOG_TAG, "wantAssetCallbackClient start" );
		lockNativeRxFrom( 41 );	
   	    int listIdx = 0;
    	for( AssetCallbackInterface callbackClient:  m_AssetCallbackList )
    	{
    		if( callbackClient == client )
    		{
       			if( wantCallbacks )
    			{
    				// already in list
        	    	unlockNativeRxFrom( 41 );	
        	    	return;
    			}
    			else
    			{
    				m_AssetCallbackList.remove( listIdx );
        	    	unlockNativeRxFrom( 41 );	
        	    	return;
    			}
    		}
    		
    		listIdx++; 
    	}
			
    	if( wantCallbacks )
		{
    		m_AssetCallbackList.add( client );
		}
 		
    	unlockNativeRxFrom( 41 );	
    	//Log.i( LOG_TAG, "wantAssetCallbackClient done" );
	}
		
	//========================================================================
	public static void wantToGuiActivityClient( ToGuiActivityInterface client, boolean wantCallbacks ) throws InterruptedException
	{
		if( null == client )
		{
			Log.e( LOG_TAG, "NULL client removeToGuiActivityClient" );
			return;
		}
		
		//Log.i( LOG_TAG, "wantToGuiActivityClient start" );
		lockNativeRxFrom( 42 );	
   	    int listIdx = 0;
    	for( ToGuiActivityInterface callbackClient:  m_ToGuiActivityList )
    	{
    		if( callbackClient == client )
    		{
      			if( wantCallbacks )
    			{
    				// already in list
        	    	unlockNativeRxFrom( 42 );	
        	    	return;
    			}
    			else
    			{
    				m_ToGuiActivityList.remove( listIdx );
        	    	unlockNativeRxFrom( 42 );	
        	    	return;
    			}
    		}
    		
    		listIdx++; 
    	}
    	
       	if( wantCallbacks )
		{
       		m_ToGuiActivityList.add( client );
		}
     		
    	unlockNativeRxFrom( 42 );	
    	//Log.i( LOG_TAG, "wantToGuiActivityClient done" );
	}
		
	//========================================================================
	public static void wantToGuiSearchClient( ToGuiSearchInterface client, boolean wantCallbacks ) throws InterruptedException
	{
		if( null == client )
		{
			Log.e( LOG_TAG, "NULL client removeToGuiSearchClient" );
			return;
		}
		
		//Log.i( LOG_TAG, "wantToGuiSearchClient start" );
 		lockNativeRxFrom( 43 );	
 	    int listIdx = 0;
    	for( ToGuiSearchInterface callbackClient:  m_ToGuiSearchList )
    	{
    		if( callbackClient == client )
    		{
       			if( wantCallbacks )
    			{
    				// already in list
        	    	unlockNativeRxFrom( 43 );	
        	    	return;
    			}
    			else
    			{
    				m_ToGuiSearchList.remove( listIdx );
        	    	unlockNativeRxFrom( 43 );	
        	    	return;
    			}
    		}
    		
    		listIdx++; 
    	}
       	
       	if( wantCallbacks )
		{
       		m_ToGuiSearchList.add( client );
		}
 		
    	unlockNativeRxFrom( 43 );	
    	//Log.i( LOG_TAG, "wantToGuiSearchClient done" );
	}
		
	//========================================================================
	public static void wantToGuiFileXferClient( ToGuiFileXferInterface client, boolean wantCallbacks ) throws InterruptedException
	{
		if( null == client )
		{
			Log.e( LOG_TAG, "NULL client wantToGuiFileXferClient" );
			return;
		}
		
		//Log.i( LOG_TAG, "wantToGuiFileXferClient start" );
		lockNativeRxFrom( 44 );	
   	    int listIdx = 0;
    	for( ToGuiFileXferInterface callbackClient:  m_ToGuiFileXferClientList )
    	{
    		if( callbackClient == client )
    		{
       			if( wantCallbacks )
    			{
    				// already in list
        	    	unlockNativeRxFrom( 44 );	
        	    	return;
    			}
    			else
    			{
    				m_ToGuiFileXferClientList.remove( listIdx );
        	    	unlockNativeRxFrom( 44 );	
        	    	return;
    			}
    		}
    		
    		listIdx++; 
    	}
      	
       	if( wantCallbacks )
		{
       		m_ToGuiFileXferClientList.add( client );
		}
	
    	unlockNativeRxFrom( 44 );	
    	//Log.i( LOG_TAG, "wantToGuiFileXferClient done" );
	}
	
	//========================================================================
	public static void wantToGuiNetworkState( ToGuiNetworkStateInterface client, boolean wantCallbacks )
	{
		if( null == client )
		{
			Log.e( LOG_TAG, "NULL client wantToGuiNetworkState" );
			return;
		}
		
		//Log.i( LOG_TAG, "wantToGuiNetworkState start" );
		lockNativeRxFrom( 45 );	
		int listIdx = 0;
		for( ToGuiNetworkStateInterface callbackClient:  m_ToGuiNetworkStateClientList )
		{
			if( callbackClient == client )
			{
	   			if( wantCallbacks )
				{
					// already in list
	   				unlockNativeRxFrom( 45 );
	    	    	return;
				}
				else
				{
					m_ToGuiNetworkStateClientList.remove( listIdx );
					unlockNativeRxFrom( 45 );
	    	    	return;
				}
			}
			
			listIdx++; 
		}
	  	
	   	if( wantCallbacks )
		{
	   		m_ToGuiNetworkStateClientList.add( client );
		}
	   	
	   	unlockNativeRxFrom( 45 );
	   	//Log.i( LOG_TAG, "wantToGuiNetworkState done" );
	}
	
	//========================================================================
	public static void wantToGuiHardwareControl( ToGuiHardwareControlInterface client, boolean wantCallbacks )
	{
		if( null == client )
		{
			Log.e( LOG_TAG, "NULL client wantToGuiHardwareControl" );
			return;
		}
		
		lockNativeRxFrom( 49 );
		int listIdx = 0;
		for( ToGuiHardwareControlInterface callbackClient:  m_ToGuiHardwareControlList )
		{
			if( callbackClient == client )
			{
	   			if( wantCallbacks )
				{
					// already in list
	   				unlockNativeRxFrom( 49 );
	    	    	return;
				}
				else
				{
					m_ToGuiHardwareControlList.remove( listIdx );
					unlockNativeRxFrom( 49 );
	    	    	return;
				}
			}
			
			listIdx++; 
		}
	  	
	   	if( wantCallbacks )
		{
	   		m_ToGuiHardwareControlList.add( client );
		}
	   	
	   	unlockNativeRxFrom( 49 );
	}
	
	//========================================================================
	public static void wantToGuiAssetMessages( ToGuiAssetMessageInterface client, boolean wantCallbacks )
	{
		if( null == client )
		{
			Log.e( LOG_TAG, "NULL client wantToGuiAssetMessages" );
			return;
		}
		
		//Log.i( LOG_TAG, "wantToGuiAssetMessages start" );
		lockNativeRxFrom( 46 );	
		int listIdx = 0;
		for( ToGuiAssetMessageInterface callbackClient:  m_ToGuiAssetMsgList )
		{
			if( callbackClient == client )
			{
	   			if( wantCallbacks )
				{
					// already in list
	   				unlockNativeRxFrom( 46 );
	    	    	return;
				}
				else
				{
					m_ToGuiAssetMsgList.remove( listIdx );
					unlockNativeRxFrom( 46 );
	    	    	return;
				}
			}
			
			listIdx++; 
		}
	  	
	   	if( wantCallbacks )
		{
	   		m_ToGuiAssetMsgList.add( client );
		}
	   	
		unlockNativeRxFrom( 46 );
	   	//Log.i( LOG_TAG, "wantToGuiAssetMessages done" );
	}
}


