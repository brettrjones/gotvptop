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

package com.p2pgotv.gotvstation;

//import javax.microedition.khronos.egl.EGLConfig;
//import javax.microedition.khronos.opengles.GL10;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

import android.app.Activity;
import android.content.Context;
import android.content.res.AssetManager;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnCompletionListener;
import android.os.Bundle;
import android.os.Vibrator;
import android.util.Log;

import android.view.Menu;
import android.view.MenuItem;
import android.view.WindowManager;
import android.widget.VideoView;
import android.widget.ViewFlipper;

 

public class ActivityVideoClip extends Activity implements OnCompletionListener
{

    //==== const ===//
	private static final String LOG_TAG = "ActivityVideoClip: ";

	private static final int INVISIBLE = (0x00000004);
	private static final int VISIBLE = (0x00000000);
	
    public static final int MENU_NEW_GAME = 1;
    public static final int MENU_PAUSE = 2;
    public static final int MENU_RESUME = 3;
    public static final int MENU_QUIT = 4;
    
    //==== vars ===//
    private static MyApp		m_MyApp = null;
	VxFileUtil 					m_oUtil = new VxFileUtil(); 
	private SensorMgr 			m_oSensorMgr;//Declare Sensor Manager class object
    public Vibrator 			m_oVibrator; 
 	private MediaPlayer 		m_oMediaPlayer;
    public 	VideoView 			m_oVideoView;  
    //private MyGlSurfaceView 	m_oGameView;
 	private ViewFlipper			m_oViewFlipper;

    public GameInterface		m_oGame;
	private String				m_strCurVideoPath;
	private String				m_strLastVideoPath;
	public boolean				m_bShuttingDown = false;
	
	Timer 						m_oLoadSoundsTimer = null;   
     
    //==== methods ===//
    //========================================================================
    // menu
    //========================================================================
    //! Creates the menu items 
    @Override
    public boolean onCreateOptionsMenu(Menu menu) 
    {
    	menu.add(0, MENU_NEW_GAME, 0, "New Game");
    	menu.add(0, MENU_PAUSE, 0, "Pause");
    	menu.add(0, MENU_RESUME, 0, "Resume");
    	menu.add(0, MENU_QUIT, 0, "Quit");
    	return true;
    }
    //! Invoked when the user selects an item from the Menu.
    //! @param item the Menu entry which was selected     
    //! @return true if the Menu item was legit (and we consumed it), false otherwise     
    @Override    
    public boolean onOptionsItemSelected(MenuItem item) 
    {        
    	switch (item.getItemId()) 
    	{            
    	case MENU_NEW_GAME:   
    		m_oGame.fromGuiGameRestart();
    		return true;            
    	case MENU_PAUSE:
    		m_oGame.fromGuiGamePause();
    		return true;
    	case MENU_RESUME:
    		m_oGame.fromGuiGameResume();
    		return true;
    	case MENU_QUIT:
    		Log.e(LOG_TAG, "RogueConnectionsActivity:: Shutdown" );
    		Shutdown();
    		return true;
    	}
    	return false;
    }

    //========================================================================
    // create
    //========================================================================
    @Override
    protected void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        m_MyApp = (MyApp) this.getApplication();
        /*
        //Log.e(LOG_TAG, "RogueConnectionsActivity::onCreate stage 1" );
	    this.setContentView(R.layout.dtw_activity);
	    getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
	    // setup view for media player
		m_oVideoView = (VideoView)this.findViewById(R.id.video_view);
		m_oVideoView.setVisibility(INVISIBLE);
		m_oVideoView.setFocusable(true);
		m_oVideoView.setBackgroundResource(0);
		m_oViewFlipper=(ViewFlipper)findViewById(R.id.details);
		*/


        // setup to allow vibrate
    	m_oVibrator = (Vibrator)getSystemService(Context.VIBRATOR_SERVICE);
    	// initialize utilities
        m_oUtil.Startup( getResources());
        
        // copy game assets to sdcard for access from native code
        
        // make a list of subdirectories of assets used by the game
        List<String> listAssetSubDirs = new ArrayList<String>();

        listAssetSubDirs.add("campaigns");
        listAssetSubDirs.add("gui");
        listAssetSubDirs.add("levels");
        listAssetSubDirs.add("meshes");
        listAssetSubDirs.add("scenes");
        listAssetSubDirs.add("scripts");
        listAssetSubDirs.add("snds");
        listAssetSubDirs.add("textures");

       // Log.e(LOG_TAG, "RogueConnectionsActivity::onCreate stage 2" );
        
        // copy game assets to sdcard for access from native code
        String strSdcardPath = m_oUtil.m_strSdcardDir + "/dtw/";
        VxFileUtil.createDirectory( strSdcardPath );
		Iterator<String> itSubdirs = listAssetSubDirs.iterator();
		while(itSubdirs.hasNext())
		{
			// make asset sub directories
			String strSubDir = (String)itSubdirs.next();
			VxFileUtil.createDirectory( strSdcardPath + strSubDir );
		    // for each asset folder .. copy to sdcard folder
		    AssetManager assetManager = getAssets();  
		    String[] files = null;  
		    try 
		    {  
		         files = assetManager.list(strSubDir);  
		    }
		    catch (IOException e) 
		    {  
		         Log.e(LOG_TAG, e.getMessage());  
		    }  
		    int iFileCnt = files.length;
		    for( int i = 0; i < iFileCnt; i++)
		    {
		    	// copy file from asset folder to sdcard in correct folder
		    	String strFileNameSrc = files[i];
		    	m_oUtil.VxCopyAsssetToSdcard( strSubDir + "/" + strFileNameSrc, 
		    			strSdcardPath + strSubDir + "/" + strFileNameSrc, true);
		    }
		}
		//Log.e(LOG_TAG, "RogueConnectionsActivity::onCreate stage 3" );
		
		// initialize interface to native game code
		//m_oGame.Startup( this );
     
		//Log.e(LOG_TAG, "RogueConnectionsActivity::onCreate stage 4" );
		
		// create opengl view for game
		//m_oGameView = new RogueConnectionsGLSurfaceView(this, this);
		//setContentView(m_oGameView);
		// setup view for opengl game render
		//m_oGameView = new RogueConnectionsGLSurfaceView(this, this);
		//setContentView(m_oGameView);
		//m_oGameView = (RogueConnectionsGLSurfaceView) this.findViewById(R.id.game_view);
		//m_oGameView.SetParentActivity( this );
		//m_oGameView.Startup(this);
		m_oViewFlipper.showNext();  
		
		//Log.e(LOG_TAG, "RogueConnectionsActivity::onCreate stage 5" );
		
		// setup sensor inputs
		m_oSensorMgr = new SensorMgr( this);
    }
    
    class LoadSoundsTask extends TimerTask 
    {   
    	public void run() 
    	{ 
    		m_oLoadSoundsTimer.cancel();
    		//m_MyApp.getMgrSound().SfxPlay("choice2.ogg");
    	}
    }
    
    //========================================================================
    void Shutdown()
    {
    	m_bShuttingDown = true;
    	m_oGame.fromGuiGameShutdown();
    	try 
    	{
			this.finish();
	    	System.exit(0);
		} 
    	catch (Throwable e) 
		{
			e.printStackTrace();
		}
    }
    
    //========================================================================
    // application activity events
    //========================================================================
    @Override
    protected void onPause() 
    {
        //Log.e(LOG_TAG, "RogueConnectionsActivity::onPause" );
        //m_oGame.fromGuiAppPause();
        super.onPause();
        m_MyApp.setActivityPause( true );
        //m_oGameView.onPause();
    	Shutdown();
    }

    @Override
    protected void onResume() 
    {
        //Log.e(LOG_TAG, "RogueConnectionsActivity::onResume" );
        //m_oGame.fromGuiAppResume();
        m_MyApp.setActivityPause( false );
        super.onResume();
        //m_oGameView.onResume();
		//m_oSensorMgr.onResume();
    }
    
    //========================================================================
    @Override
    protected void onStop() 
    {
    	super.onStop();
    	m_oSensorMgr.onStop();
    	/*
    	if( null != m_oWakeLock )
    	{
    		m_oWakeLock.release();
    		m_oWakeLock = null;
    	}*/
   	}
    
    //========================================================================
    // game
    //========================================================================
    void fromGuiGamePause()
    {
		//Log.d(LOG_TAG, "Game Pause");  
    	m_oGame.fromGuiGamePause();
    }
    
    //========================================================================
    void fromGuiGameResume()
    {
		//Log.d(LOG_TAG, "Game Resume");  
    	m_oGame.fromGuiGameResume();
    }

    //========================================================================
    // media player
    //========================================================================
    //========================================================================
    // handle media player callback
	//public void onBufferingUpdate(MediaPlayer arg0, int percent) 
	//{  
		//Log.d(LOG_TAG, "onBufferingUpdate called --->   percent:" + percent);  
	//}  

    //========================================================================
    // handle media player callback
	//public void onCompletion(MediaPlayer mediaPlayer) 
	//{  
		//Log.d(LOG_TAG, "onCompletion called");  
		//mediaPlayer.release(); 
	//}  

    //========================================================================
    // handle media player callback
	//public void onPrepared(MediaPlayer mediaplayer) 
	//{  
		//Log.d(LOG_TAG, "onPrepared called");  
	//}
	public void playMovie( String strMovie ) 
	{
		m_strCurVideoPath = strMovie;
		//only the gui thread can show movies.. therefore
        runOnUiThread(new Runnable() 
    	{
        	public void run() 
        	{
        		//m_oGameView.setVisibility(INVISIBLE);
        		m_oVideoView.setVisibility(VISIBLE);
        		m_oVideoView.setOnCompletionListener((OnCompletionListener) ActivityVideoClip.this);
        		//m_oGame.fromGuiGamePause();
        		m_oVideoView.requestFocus();  

        		//m_oViewFlipper.showNext();
        		//final String path = m_strVideoPath;  
        		//Log.v(LOG_TAG, "path: " + path);  
        		// open the raw resource, get the stream
                //InputStream stream = getResources().openRawResource(R.raw.explodeplanet);
                InputStream stream = null;
                //create a  temp file from stream and set path
                String strTmp;
        		try 
        		{
        			strTmp = createFileFromStream(stream);

        			if (strTmp == null || strTmp.length() == 0) 
        			{  
        				//Toast.makeText(this, "File URL/path is empty",  
        				//	 Toast.LENGTH_LONG).show();  
        			} 
        			else 
        			{  
        				// If the path has not changed, just start the media player  
        				if ((m_strCurVideoPath != null) && m_strCurVideoPath.equals(m_strLastVideoPath) && m_oVideoView != null) 
        				{  
        					m_oVideoView.start();  
        					m_oVideoView.requestFocus();  
        					return;  
        				}  
        				m_strLastVideoPath = m_strCurVideoPath;
        				m_oVideoView.setVideoPath(strTmp);  
        				m_oVideoView.start();  
        				m_oVideoView.requestFocus();  
        				//m_strTmpVidFile = strTmp;
        			}  
        		}
        		catch (Exception e) 
        		{  
        			Log.e(LOG_TAG, "playMovie: error " + e.getMessage(), e);  
        		} 
        		
        		//final long[] pattern = {100L, 100L}; 
        		
                Vibrator vibrator = (Vibrator)getSystemService(Context.VIBRATOR_SERVICE); 
                if(vibrator != null)
                {
                	// 1. Vibrate for 1000 milliseconds   
                	long milliseconds = 5000;   
                	vibrator.vibrate(milliseconds);   
                	  
                	// 2. Vibrate in a Pattern with 500ms on, 500ms off for 5 times   
                	//long[] pattern = { 500, 300 };   
                	//vibrator.vibrate(pattern, 5);  
                	//vibrator.vibrate(pattern, -1);
                }
            }
          
    	});

	}

		
	// method to create a temp file from InputStream
    private String createFileFromStream(InputStream stream)
            throws IOException
    {
        if (stream == null)
        {
            throw new IOException("stream is null");
        }
        File temp = File.createTempFile("mediaplayertmp", "dat");
        String tempPath = temp.getAbsolutePath();
        FileOutputStream out = new FileOutputStream(temp);
        byte buf[] = new byte[128];
        do
        {
            int numread = stream.read(buf);
            if (numread <= 0)
            {
                break;
            }
            out.write(buf, 0, numread);
        }
        while (true);
        try
        {
            stream.close();
            out.close();
        }
        catch (IOException ex)
        {
            Log.e(LOG_TAG, "playMovie error: " + ex.getMessage(), ex);
        }
        
        return tempPath;
    }
    
	public void onCompletion(MediaPlayer arg0) 
	{
        //Log.e(LOG_TAG, "playMovie: movie completed " );
		m_oVideoView.setVisibility(INVISIBLE);
		//m_oGameView.setVisibility(VISIBLE);
		//m_oGame.fromGuiGameResume();	
	}
}

