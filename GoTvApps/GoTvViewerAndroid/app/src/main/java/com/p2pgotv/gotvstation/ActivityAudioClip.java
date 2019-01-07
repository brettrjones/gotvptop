//============================================================================
// Copyright (C) 2010-2013 Brett R. Jones 
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

/*
//import javax.microedition.khronos.egl.EGLConfig;
//import javax.microedition.khronos.opengles.GL10;


import android.app.Activity;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnCompletionListener;
import android.os.Bundle;
import android.util.Log;

import android.widget.VideoView;
import android.widget.ViewFlipper;

 

public class ActivityAudioClip extends Activity implements OnCompletionListener
{
    //==== const ===//
	private static final String LOG_TAG = "ActivityAudioClip: ";

	private static final int INVISIBLE = (0x00000004);
	//private static final int VISIBLE = (0x00000000);
	
    public static final int MENU_NEW_GAME = 1;
    public static final int MENU_PAUSE = 2;
    public static final int MENU_RESUME = 3;
    public static final int MENU_QUIT = 4;
    
    //==== vars ===//
    private static MyApp		m_MyApp = null;

 	//private MediaPlayer 		m_oMediaPlayer;

 	public 	VideoView 			m_oVideoView;  
    private MyGlSurfaceView 	m_MyGlSurfaceView;
 	private ViewFlipper			m_oViewFlipper;

	public boolean				m_bShuttingDown = false;
	public boolean				m_GlShutdownWasRequested = false;

	//========================================================================
    @Override
    protected void onCreate(Bundle savedInstanceState) 
    {
	    Log.e(LOG_TAG, "onCreate start" );
	    super.onCreate(savedInstanceState);
        m_MyApp = (MyApp) this.getApplication();
	    
        //Log.e(LOG_TAG, "ActivityAudioClip::onCreate stage 1" );
 	    this.setContentView(R.layout.activity_audio_clip);
	    // setup view for media player
		m_oVideoView = (VideoView)this.findViewById(R.id.video_view);
		m_oVideoView.setVisibility(INVISIBLE);
		m_oVideoView.setFocusable(true);
		m_oVideoView.setBackgroundResource(0);
		m_oViewFlipper=(ViewFlipper)findViewById(R.id.view_flipper);

		
		// create opengl view
     	m_MyGlSurfaceView = (MyGlSurfaceView) this.findViewById(R.id.myglsurface_view);
      	m_MyGlSurfaceView.Startup(this);
		
		m_oViewFlipper.showNext();  
				
	    Log.e(LOG_TAG, " onCreate start done" );
	}
    
    //========================================================================
    @Override
    protected void onDestroy() 
    {
    	shutdownRequestedFromGl();
    	// let phone sleep
    	//m_MyApp.phoneWakeLock( false );
    	super.onDestroy();
    }

    //========================================================================
	@Override
	public void onCompletion(MediaPlayer mp) 
	{
        //Log.e(LOG_TAG, "playMovie: movie completed " );
		//m_oVideoView.setVisibility(INVISIBLE);
		//m_MyGlSurfaceView.setVisibility(VISIBLE);		
	}
	
    //========================================================================
	public void shutdownRequestedFromGl() 
	{
		//HACK fix because gl surface destroy is never called
		if( false == m_GlShutdownWasRequested )
		{
			m_GlShutdownWasRequested = true;
			Log.e(LOG_TAG, "shutdownRequestedFromGl " );
			NativeRxFrom.toGuiWantMicrophoneRecording( false );
	    	NativeTxTo.fromGuiNativeGlDestroy();			
		}
	}
}
*/

