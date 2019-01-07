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

import android.media.MediaPlayer;
//import android.os.Bundle;
import android.util.Log;
import android.content.Context;
import android.content.res.AssetFileDescriptor;
import android.media.AudioManager;
import android.media.MediaPlayer.OnBufferingUpdateListener;
import android.media.MediaPlayer.OnCompletionListener;
import android.media.MediaPlayer.OnErrorListener;
import android.media.MediaPlayer.OnPreparedListener;
import android.media.MediaPlayer.OnVideoSizeChangedListener;
import android.view.SurfaceHolder;
//import android.view.SurfaceView;

public class VideoMgr implements
	OnBufferingUpdateListener, 
	OnCompletionListener,
	OnPreparedListener, 
	OnVideoSizeChangedListener, 
	SurfaceHolder.Callback, 
	OnErrorListener 
{
    private static final String LOG_TAG = "VideoMgr:";
	//private static final int INVISIBLE = (0x00000004);
	//private static final int VISIBLE = (0x00000000);

    
    private int 				mVideoWidth;
    private int 				mVideoHeight;
    private MediaPlayer 		mMediaPlayer = null;
    //private SurfaceView 		mPreview;
    private SurfaceHolder 		m_oSurfaceHolder;
    //private String 				path;
   //private Bundle 				extras;
    private boolean 		mIsVideoSizeKnown = false;
    private boolean 		mIsVideoReadyToBePlayed = false;
    private Context			m_oContext;
    //private ActivityVideoClip 	m_oActivity;
    private boolean 		m_bSurfaceOk = false;
    //private int				m_iResourceId = 0;

    VideoMgr(Context oContext, ActivityVideoClip oActivity)
    {
    	m_oContext = oContext;
    	//m_oActivity = oActivity;
    }
    
    void SetSurfaceHolder( SurfaceHolder oHolder )
    {
    	m_oSurfaceHolder = oHolder;
    	m_oSurfaceHolder.addCallback(this);
    	m_oSurfaceHolder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
    }

    // play video from raw resourse example "R.raw.explodeplanet.mp4"
	public void PlayVideo(int iResourceId, SurfaceHolder oHolder ) 
	{
        doCleanUp();
        //m_iResourceId = iResourceId;
        if( mMediaPlayer != null )
        {
        	mMediaPlayer.stop();
            mMediaPlayer.release();
            mMediaPlayer = null;
        }
        if( oHolder != m_oSurfaceHolder )
        {
        	m_oSurfaceHolder = oHolder;
        	m_oSurfaceHolder.addCallback(this);
        	m_oSurfaceHolder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
        }
        if( m_bSurfaceOk )
        {
        	DoPlayVideo( iResourceId, oHolder );
        }
	}
    private void DoPlayVideo(int iResourceId, SurfaceHolder oHolder ) 
    {

        try 
        {
        	AssetFileDescriptor fd = m_oContext.getResources().openRawResourceFd(iResourceId);
        	if( null != fd)
        	{
        		mMediaPlayer = new MediaPlayer();
        		mMediaPlayer.setScreenOnWhilePlaying(true);
	    		mMediaPlayer.setOnErrorListener(this);  
	    		mMediaPlayer.setDataSource(fd.getFileDescriptor(), fd.getStartOffset(), fd.getLength() );
	            mMediaPlayer.setDisplay(m_oSurfaceHolder);
	            mMediaPlayer.prepare();
	            
	            mMediaPlayer.setOnBufferingUpdateListener(this);
	            mMediaPlayer.setOnCompletionListener(this);
	            mMediaPlayer.setOnPreparedListener(this);
	            mMediaPlayer.setOnVideoSizeChangedListener(this);
	            mMediaPlayer.setAudioStreamType(AudioManager.STREAM_MUSIC);            
	            
        		fd.close();
        	}
        } 
        catch (Exception e) 
        {
            Log.e(LOG_TAG, "error: " + e.getMessage(), e);
        }
    }
	public boolean onError(MediaPlayer mediaPlayer, int what, int extra) 
	{  
		Log.e(LOG_TAG, "onError--->   what:" + what + "    extra:" + extra);  
		releaseMediaPlayer();
		return false;
	}  


    public void onBufferingUpdate(MediaPlayer arg0, int percent) 
    {
        //Log.d(LOG_TAG, "onBufferingUpdate percent:" + percent);
    }

    public void onCompletion(MediaPlayer arg0) 
    {
        //Log.d(LOG_TAG, "onCompletion called");
        releaseMediaPlayer();
        doCleanUp();
    }

    public void onVideoSizeChanged(MediaPlayer mp, int width, int height) 
    {
        //Log.v(LOG_TAG, "onVideoSizeChanged called");
        if (width == 0 || height == 0) 
        {
            //Log.e(LOG_TAG, "invalid video width(" + width + ") or height(" + height + ")");
            return;
        }
        mIsVideoSizeKnown = true;
        mVideoWidth = width;
        mVideoHeight = height;
        if (mIsVideoReadyToBePlayed && mIsVideoSizeKnown) 
        { 
            startVideoPlayback();
        }
    }

    public void onPrepared(MediaPlayer mediaplayer) 
    {
        //Log.d(LOG_TAG, "onPrepared called");
        mIsVideoReadyToBePlayed = true;
        if (mIsVideoReadyToBePlayed && mIsVideoSizeKnown) 
        {
            startVideoPlayback();
        }
    }

    public void surfaceChanged(SurfaceHolder surfaceholder, int i, int j, int k) 
    {
        //Log.d(LOG_TAG, "surfaceChanged called");
        m_bSurfaceOk = true;
        if (mIsVideoReadyToBePlayed && mIsVideoSizeKnown) 
        {
            startVideoPlayback();
        }
    }

    public void surfaceDestroyed(SurfaceHolder surfaceholder) 
    {
    	 m_bSurfaceOk = false;
    	 //Log.d(LOG_TAG, "surfaceDestroyed called");
    }


    public void surfaceCreated(SurfaceHolder holder) 
    {
    	//Log.d(LOG_TAG, "surfaceCreated called");
        if (mIsVideoReadyToBePlayed && mIsVideoSizeKnown) 
        {
            startVideoPlayback();
        }
    }

    protected void DoOnPause() 
    {
        releaseMediaPlayer();
        doCleanUp();
    }

    protected void DoOnDestroy() 
    {
        releaseMediaPlayer();
        doCleanUp();
    }

    private void releaseMediaPlayer() 
    {
        if (mMediaPlayer != null) 
        {
            mMediaPlayer.release();
            mMediaPlayer = null;
        }
    }

    private void doCleanUp() 
    {
        mVideoWidth = 0;
        mVideoHeight = 0;
        mIsVideoReadyToBePlayed = false;
        mIsVideoSizeKnown = false;
    }

    private void startVideoPlayback() 
    {
        Log.v(LOG_TAG, "startVideoPlayback");
        m_oSurfaceHolder.setFixedSize(mVideoWidth, mVideoHeight);
        mMediaPlayer.start();
    }
    /*
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
        }
        catch (IOException ex)
        {
            Log.e(LOG_TAG, "playMovie error: " + ex.getMessage(), ex);
        }
        return tempPath;
    }
    */

}
