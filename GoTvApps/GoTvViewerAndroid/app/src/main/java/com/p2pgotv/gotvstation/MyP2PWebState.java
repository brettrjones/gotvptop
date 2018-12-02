//============================================================================
// Copyright (C) 2015 Brett R. Jones
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

import java.io.IOException;
import java.net.DatagramSocket;
import java.net.ServerSocket;

import android.content.Intent;
import android.os.SystemClock;
import android.util.Log;
import android.widget.Toast;

import com.p2pgotv.gotvstation.NativeTxTo;

public class MyP2PWebState
{
	private static final String LOG_TAG = "MyP2PWebState:";
	
	private static MyApp 			m_MyApp						= null;
	private static MyP2PWeb			m_MyP2PWeb 					= null;
	public static  boolean			m_ProfileIsSetup 			= false;
	public static  boolean			m_WaitingForProfileSetup 	= true;
	private static boolean			m_LoggedOn 					= false;
	private static boolean			m_IsMyMainInitialized 		= false;
	private static boolean			m_IsNativeLogonSent			= false;	
	private static boolean			m_IsUserSpecificDirSet 		= false;
	
	//========================================================================
	public void setIsNativeLogonSent( boolean isSent )
	{
		m_IsNativeLogonSent = isSent;
	}
	
	//========================================================================
	public boolean getIsNativeLogonSent()
	{
		return m_IsNativeLogonSent;
	}
	
	//========================================================================
	public void setIsMainInitialized( boolean isInitialized )
	{
		m_IsMyMainInitialized = isInitialized;
	}
	
	//========================================================================
	public boolean getIsMainInitialized()
	{
		return m_IsMyMainInitialized;
	}
	
	//========================================================================
	public boolean getIsNativeReadyForCalls()
	{
		return m_IsUserSpecificDirSet;
	}

	//========================================================================
	public void doStartupTasks( MyApp myApp, MyP2PWeb activity )
	{
		m_MyApp 					= myApp;
		m_MyP2PWeb 					= activity;
		m_ProfileIsSetup 			= false;
		m_WaitingForProfileSetup 	= true;
		m_LoggedOn 					= false;
		m_IsMyMainInitialized 		= false;
		m_IsNativeLogonSent			= false;	
		
		NativeTxTo.fromGuiSetupContext( activity.getApplicationContext() );
	}	

	//========================================================================
	public void doMainStateShutdown()
	{
	}

	//========================================================================
	public void onOncePerSecond()
	{
		if( m_MyApp.getIsAppShuttingDown() )
    	{
    		return;
    	}

		if( false == m_ProfileIsSetup )
		{
 			Log.d( LOG_TAG, "MyP2PWeb DoProfileTask start\n" );
     		try 
    		{
     			m_MyApp.setupDefaultProfile();
     			m_ProfileIsSetup = true;
			} 
    		catch (IOException e) 
			{
				e.printStackTrace();
			}   
			
 			Log.d( LOG_TAG, "MyP2PWeb DoProfileTask done MyP2PWeb.m_ProfileIsSetup " + m_ProfileIsSetup );							
		}
		else if( m_WaitingForProfileSetup )
    	{
    		if( true == m_ProfileIsSetup )
    		{
    	    	//Log.d(LOG_TAG, "Activity Startup Running Login" );
    			m_WaitingForProfileSetup = false;
            	//checkExternalMedia();	
    			LoginOrCreateProfile();   	    			
    			m_MyApp.startAppIdleTimer();
    		}
    	}
	}
 
	//========================================================================
	public boolean LoginOrCreateProfile() 
	{
		//Log.d(LOG_TAG, "LoginOrCreateProfile ");	
		if( m_MyApp.updateUserAccountFromDatabase() )
		{
			int tcpPort = m_MyApp.getMySettings().getMyTcpInPort();
			if( false == isPortAvailable(  tcpPort ) )
			{
				Toast.makeText( m_MyP2PWeb, "Your Network Port " + String.valueOf( tcpPort ) + " Is In Use And Cannot Be Opened ", Toast.LENGTH_LONG ).show();
				SystemClock.sleep( 3000 );
			}
		}
		
		UserAccount oAccount 	= m_MyApp.getUserAccount(); 
		oAccount.setHasRelay( false );
		oAccount.setHasSharedWebCam( false );
		oAccount.setIsMyPreferedRelay( false );
		oAccount.setIsOnline( false );
		
		boolean bLoginSuccess 	= false;		
		if( oAccount.isValid() ) 
		{ 
			Log.d(LOG_TAG, "Doing Login ");
			bLoginSuccess = DoLogin(); 
		} 
		else
		{
			Log.d(LOG_TAG, "Account is invalid ");			
		}
		
		if( false == bLoginSuccess )
		{ 
			Log.d(LOG_TAG, "Launching ActivityCreateProfile ");
			Intent myIntent = new Intent( m_MyP2PWeb, ActivityCreateProfile.class );
			m_MyP2PWeb.startActivityForResult( myIntent, Constants.ACTIVITY_CREATE_PROFILE ); 
			return false;
		}
		
		Log.d(LOG_TAG, "LoginOrCreateProfile success ");
		return bLoginSuccess;
	}
	
		
	//========================================================================
	public static boolean isPortAvailable(int port) 
	{
	    if (port < 80 || port > 65535 ) 
	    {
	        throw new IllegalArgumentException("Invalid start port: " + port);
	    }

	    ServerSocket ss = null;
	    DatagramSocket ds = null;
	    try {
	        ss = new ServerSocket(port);
	        ss.setReuseAddress(true);
	        ds = new DatagramSocket(port);
	        ds.setReuseAddress(true);
	        return true;
	    } catch (IOException e) {
	    } finally {
	        if (ds != null) {
	            ds.close();
	        }

	        if (ss != null) {
	            try {
	                ss.close();
	            } catch (IOException e) {
	                /* should not be thrown */
	            }
	        }
	    }

	    return false;
	}
	
	//========================================================================
	public boolean DoLogin() 
	{
		UserAccount oAccount = m_MyApp.getUserAccount();
		if( ( false == m_LoggedOn) && ( null != oAccount ) )
		{
			if( 0 != oAccount.getOnlineName().length() )
			{
				m_LoggedOn = true;
				oAccount.setRequiresRelay( m_MyApp.m_bRelayRequired );
				/*Log.i( LOG_TAG,
						"login with found user account. calling native with name"
								+ oAccount.m_as8OnlineName + " PORT "
								+ oAccount.m_OnlinePort + " ID " + oAccount.describeMyId() );*/
				oAccount.debugDumpIdent();
				if( false == getIsNativeLogonSent() )
				{
					String userXferDir 	= m_MyApp.getAppUsersDir() + oAccount.m_as8OnlineName + "/";
					Log.i( LOG_TAG, "Sending user xfer dir " + userXferDir );
					m_MyApp.setUserXferDirectory( userXferDir );
					NativeTxTo.fromGuiSetUserXferDir( userXferDir );				

					String userSpecificDir 	= m_MyApp.getAppAccountsDir() + oAccount.m_as8OnlineName + "/";
					Log.i( LOG_TAG, "Sending user specific dir " + userSpecificDir );
					m_MyApp.setUserSpecificDirectory( userSpecificDir );
					NativeTxTo.fromGuiSetUserSpecificDir( userSpecificDir );	
					m_IsUserSpecificDirSet = true;
				}
				else
				{
					Log.i( LOG_TAG, "NativeLogonSent so no specific dir" );					
				}
				
				m_MyApp.sendNetworkSettingsToNative();
				
				if( false == getIsNativeLogonSent() )
				{
					Log.i( LOG_TAG, "Sending fromGuiUserLoggedOn " );
					NativeTxTo.fromGuiUserLoggedOn(	oAccount );
					if( false == m_MyApp.m_bNetworkMgrStarted )
					{
						m_MyApp.m_bNetworkMgrStarted = true;
						//Log.d(Constants.LIFETIME, "&&&&& APPLICATION applicationStartup startupMgrNetwork" );
						m_MyApp.getMgrNetwork().startupMgrNetwork( m_MyApp.m_ApplicationContext );
					}
				}
				else
				{
					Log.i( LOG_TAG, "NativeLogon Sent so no logon" );					
				}
				
				setIsNativeLogonSent( true );				
				m_MyP2PWeb.RefreshContacts();
			}
			else
			{
				Log.d(LOG_TAG, "DoLogin No Online Name ");				
			}
		}
			
		Log.d(LOG_TAG, "DoLogin Logged On ? " + m_LoggedOn );
		return m_LoggedOn;
	}
};

