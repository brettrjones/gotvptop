//============================================================================
// Copyright (C) 2009 Brett R. Jones
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

import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;
import android.os.Handler;
import android.util.Log;

public class PcmSoundOutOld extends Thread 
{
	static final String			LOG_TAG 			= "PcmSoundOut";
	static final int			MAX_PCM_BUFS 		= 4;
	static final int			PCM_BUF_LEN 		= 640;
	
	MyApp 						m_MyApp;
	AudioTrack 					m_oSpeakerTrack		= null;
	volatile boolean  			m_bIsTrackPlaying 	= false;
	volatile boolean 			m_bIsMuted 			= false;
	static final int			m_bSpeakerMode 		= 0;

	private Semaphore 			m_Mutex				= new Semaphore(1);
	private int 				m_CirBufHeadIdx		= 0;
	private int 				m_CirBufTailIdx		= 0;
	private int 				m_BufInUseCnt		= 0;
	private short[] 			m_SndBuf1 			= new short[PCM_BUF_LEN];
	private short[] 			m_SndBuf2 			= new short[PCM_BUF_LEN];
	private short[] 			m_SndBuf3 			= new short[PCM_BUF_LEN];
	private short[] 			m_SndBuf4 			= new short[PCM_BUF_LEN];
	private ArrayList<short[]> 	m_BufList 			= new ArrayList<short[]>();
	private Handler 			m_ChangeStateHandler = new Handler(); 
	private boolean				m_ThreadRunning		= false;

	
	//========================================================================
	public PcmSoundOutOld( MyApp myApp ) 
	{
		m_MyApp = myApp;
		initialize();
	}
	
	//========================================================================
	public void pcmSoundOutShutdown() 
	{
		m_oSpeakerTrack.release();
	}
	
	//========================================================================
	private void initialize() 
	{
		try 
		{
			m_BufList.add( m_SndBuf1 );
			m_BufList.add( m_SndBuf2 );
			m_BufList.add( m_SndBuf3 );
			m_BufList.add( m_SndBuf4 );
			resetBuffers();
			
			m_oSpeakerTrack = new AudioTrack(	AudioManager.STREAM_MUSIC, 
												8000,
												AudioFormat.CHANNEL_OUT_MONO,
												AudioFormat.ENCODING_PCM_16BIT, 
												1280,
												AudioTrack.MODE_STREAM );
			
			Log.i(LOG_TAG, "state:" + m_oSpeakerTrack.getState());						
		} 
		catch (Exception e) 
		{
			Log.i(LOG_TAG,"Error:"+e.toString());
		}
	}

	//========================================================================
	public void lockResources()
	{
		try {
			m_Mutex.acquire();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	//========================================================================
	public void unlockResources()
	{
		m_Mutex.release();	
	}
	
	//========================================================================
	public void resetBuffers()
	{
		for( int i = 0; i < MAX_PCM_BUFS; i++ )
		{
			clearPcmBuf( m_BufList.get( i ) );
		}
		
		m_CirBufHeadIdx			= MAX_PCM_BUFS - 1;
		m_CirBufTailIdx			= 0;
		m_BufInUseCnt			= 1;		
	}
	
	//========================================================================
	public void clearPcmBuf( short[] buf )
	{
		for( int i = 0; i < PCM_BUF_LEN; i++ )
		{
			buf[i] = 0;
		}
	}
	
	//========================================================================
	public void toGuiWantSpeakerOutput( boolean wantSpeakerOutput )
	{
		Log.i(LOG_TAG,"toGuiWantSpeakerOutput start " + wantSpeakerOutput );
		final boolean lclWantSpeakerOutput = wantSpeakerOutput;
		m_ChangeStateHandler.post(new Runnable()
		{
			public void run() 
			{
				if( lclWantSpeakerOutput )
				{
					startSoundOutput();
				}
				else
				{
					stopSoundOutput();			
				}
				
				Log.i(LOG_TAG,"toGuiWantSpeakerOutput end " + lclWantSpeakerOutput );				
			}
		});
	
		Log.i(LOG_TAG,"toGuiWantSpeakerOutput posted " + wantSpeakerOutput );
	} 
	
	//========================================================================
	public void setMute(boolean bMute ) 
	{
		m_bIsMuted = bMute;
	}
	
	//========================================================================
	void startSoundOutput() 
	{
		try 
		{
			if( false == m_bIsTrackPlaying )
			{	
				Log.i( LOG_TAG,"startSoundOutput lock resource " );
				lockResources();
				Log.i( LOG_TAG,"startSoundOutput resetBuffers " );
				resetBuffers();
				Log.i( LOG_TAG,"startSoundOutput m_oSpeakerTrack.play " );
				m_oSpeakerTrack.play();			
				Log.i( LOG_TAG,"startSoundOutput start thread " );
				m_bIsTrackPlaying = true;				
				if( false == m_ThreadRunning )
				{
					start();
					m_ThreadRunning = true;
				}
				unlockResources();
				Log.i( LOG_TAG,"startSoundOutput done " );
			}
		} 
		
		catch (Exception e) 
		{
			Log.i("PcmSoundOut","Error:"+e.toString());
		}
	}
	
	//========================================================================
	public void stopSoundOutput() 
	{
		try 
		{
			if( m_bIsTrackPlaying )
			{
				m_bIsTrackPlaying = false;				
				m_oSpeakerTrack.stop();
				Log.i(LOG_TAG,"stop state:"+ m_oSpeakerTrack.getState());
			}
		}
		catch (Exception e) 
		{
			Log.i("PcmSoundOut","Error:"+e.toString());
		}
	}
	
	//========================================================================
	void writePcmSound( short pcmData[], int dataLenInShorts ) 
	{
		if(  m_MyApp.getIsAppShuttingDown() || false == m_bIsTrackPlaying )
		{
			return;
		}
		
		if( PCM_BUF_LEN != dataLenInShorts )
		{
			Log.i( LOG_TAG, "Invalid pcm len " + dataLenInShorts );
			return;
		}

		int bufsFreeCnt		= MAX_PCM_BUFS - m_BufInUseCnt;
		if( 0 == bufsFreeCnt )
		{
			Log.i( LOG_TAG, "No Free Buffers " );
			return;
		}
		
		//Log.i(LOG_TAG, "app snd writ to buf " + m_CirBufHeadIdx );
		short[] sndBuf = m_BufList.get( m_CirBufHeadIdx );
		for( int i = 0; i < PCM_BUF_LEN; i++ )
		{
			sndBuf[i] = pcmData[i];
		}
		
		lockResources();
		m_BufInUseCnt++;
		m_CirBufHeadIdx++;
		if( MAX_PCM_BUFS <= m_CirBufHeadIdx )
		{
			m_CirBufHeadIdx = 0;
		}
		
		unlockResources();
	}

	//========================================================================
	public void run() 
	{
		System.gc();
		while( false ==  m_MyApp.getIsAppShuttingDown() ) 
		{
			if( false == m_bIsTrackPlaying  )
			{
				try 
				{
					Thread.sleep( 300 );
				} 
				catch (InterruptedException e) 
				{
					e.printStackTrace();
				}
				
				continue;
			}
			
			short[] sndBuf = m_BufList.get( m_CirBufTailIdx );
			m_oSpeakerTrack.write( sndBuf, 0, PCM_BUF_LEN );
			
			//Log.d(LOG_TAG, "played snd buf " + m_CirBufTailIdx + " " + VxTimeUtil.getCurrentTime() );
			lockResources();
			m_CirBufTailIdx++;
			if( MAX_PCM_BUFS <= m_CirBufTailIdx )
			{
				m_CirBufTailIdx = 0;
			}
	
			if( 0 == m_BufInUseCnt )
			{
				// even though no user input data we keep incrementing as if there was but fill with silence
				//Log.d(LOG_TAG, "clearing snd buf " + m_CirBufHeadIdx );
				clearPcmBuf( m_BufList.get( m_CirBufHeadIdx ) );
				m_CirBufHeadIdx++;
				if( MAX_PCM_BUFS <= m_CirBufHeadIdx )
				{
					m_CirBufHeadIdx = 0;
				}
			}

			if( 0 != m_BufInUseCnt )
			{
				m_BufInUseCnt--;
			}

			unlockResources();		
			if( m_MyApp.getIsAppShuttingDown() )
			{
				break;
			}
			
			//int freeSpace = PCM_BUF_LEN * 2;
			//NativeTxTo.fromGuiAudioOutSpaceAvail( freeSpace );
		}
	}
	
	//========================================================================
	public void toGuiPlayAudio( short[] pu16PcmData, int u16PcmDataLenInBytes )
    {
		if( m_MyApp.getIsAppShuttingDown() )
		{
			return;
		}
		
		writePcmSound( pu16PcmData, u16PcmDataLenInBytes/2 );
	}
}
