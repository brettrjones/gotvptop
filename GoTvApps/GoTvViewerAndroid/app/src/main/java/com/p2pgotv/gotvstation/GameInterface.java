//============================================================================
// Copyright (C) 2010 Brett R. Jones 
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

// implements basic sound play functionality callable from jni

package com.p2pgotv.gotvstation;

// implements game interface to native code
public class GameInterface
{
	// declare native functions
    private static native void nativeGamePause();
    private static native void nativeGameResume();
    private static native void nativeGameRestart();
    private static native void nativeGameShutdown();

    private static native void nativeAppSleep();
    private static native void nativeAppResume();
    
	//=== vars ===// 
	private static final String LOG_TAG = "GameInterface: ";
	private static MyP2PWeb m_oActivity;
	private static MyApp 		m_MyApp;
	
    //=== constructors ===//  
    public GameInterface(MyApp oApp) 
    {
    	m_MyApp = oApp;
    	//Log.i(LOG_TAG, "constructed");
    }
    //=== startup ===//  
    public void Startup(MyP2PWeb oActivity) 
    {
    	//Log.i(LOG_TAG, "startup");
        m_oActivity = oActivity;
    }
    //========================================================================
    // to native code
    //========================================================================
    //========================================================================
    //! tell native code to pause game
	public void fromGuiGamePause() 
    {
		nativeGamePause();
    }
    //========================================================================
    //! tell native code to resume game
	public void fromGuiGameResume() 
    {
		nativeGameResume();
    }
    //========================================================================
    //! tell native code application has went to sleep
	public void fromGuiAppPause() 
    {
		nativeAppSleep();
    }
    //========================================================================
    //! tell native code application has been awakened
	public void fromGuiAppResume() 
    {
		nativeAppResume();
    }
    //========================================================================
    //! tell native code to start a new game
	public void fromGuiGameRestart() 
    {
		nativeGameRestart();
    }
	//! called when app is about to exit
	public void fromGuiGameShutdown()
	{
		nativeGameShutdown();
	}
    
    //========================================================================
    // from native code
    //========================================================================
	//! pause the game 
	//@SuppressWarnings("static-access")
	public static void GameIsPaused() 
    {
    }
	//! resume game
	public static void GameIsResumed() 
    {
    }

	//! vibrate phone
    public void Vibrate(long s64MilliSec )
    {
    	//m_MyApp.getMgrVibrator().vibrate( s64MilliSec );
//	    if(m_oActivity.m_oVibrator != null)
//	    {
//	    	m_oActivity.m_oVibrator.vibrate(s64MilliSec);   
	    	  
	    	// 2. Vibrate in a Pattern with 500ms on, 500ms off for 5 times   
	    	//long[] pattern = { 500, 300 };   
	    	//vibrator.vibrate(pattern, 5);  
	    	//vibrator.vibrate(pattern, -1);
//	    }
    }

};
