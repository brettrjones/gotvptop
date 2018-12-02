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

import android.content.Context;
import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.util.Log;

public class PcmSoundInOld extends Thread 
{
	MyApp 				m_MyApp;
	AudioRecord 		m_oMicRecorder 		= null;
	public static String LOG_TAG 			= "PcmSoundIn";

	int 				m_iMinReadSize 		= 0;
	int 				m_iReadAttemptSize 	= 0;
	byte[] 				m_au8SoundBuffer 	= null;
	int 				m_iSpeexEncodeSize 	= 1280;
	int 				m_iTotalBufferSize 	= 0;
	int 				m_iReadPosition 	= 0;
	boolean 			m_bSpecial 			= false;
	boolean 			m_AmStarted 		= false;
	boolean 			m_AppShutdown 		= false;

	//========================================================================
	public PcmSoundInOld(MyApp oMyApp) 
	{
		m_MyApp = oMyApp;
		start();
	}
	
	//========================================================================
	public void startupPcmSoundIn() 
	{
		if( m_AmStarted )
		{
			return;
		}
		
		m_AmStarted = true;
		if( null == m_oMicRecorder ) 
		{
			int iFrequency = 8000;
			int iChannel = AudioFormat.CHANNEL_IN_MONO;
			int iEncoding =  AudioFormat.ENCODING_PCM_16BIT;
			
			m_iMinReadSize = AudioRecord.getMinBufferSize(iFrequency, iChannel, iEncoding );
			if( m_iMinReadSize >= m_iSpeexEncodeSize )
			{
				m_iTotalBufferSize = 3 * m_iMinReadSize;
			}
			else
			{
				int iMinReadsPerSpeex = (m_iSpeexEncodeSize/m_iMinReadSize) + 1;
				m_iTotalBufferSize = iMinReadsPerSpeex * m_iMinReadSize * 3;
			}
			m_iReadPosition = 0;
			m_au8SoundBuffer = new byte[m_iTotalBufferSize];
			m_oMicRecorder = new AudioRecord(MediaRecorder.AudioSource.MIC,
					iFrequency, // frequency
					iChannel,
					iEncoding, 
					m_iMinReadSize * 3 );
			if( m_oMicRecorder.getState() != AudioRecord.STATE_INITIALIZED ) 
			{
				Log.i(LOG_TAG, "Microphone input fail state " + m_oMicRecorder.getState() );
				shutdownPcmSoundIn();
			}
		}
	}
	
	//========================================================================
	public void shutdownPcmSoundIn() 
	{
		if( false == m_AmStarted )
		{
			return;
		}	
		
		m_oMicRecorder.stop();
		m_oMicRecorder.release();
		m_oMicRecorder = null;		
		if(m_bSpecial)
		{
			AudioManager am = (AudioManager) m_MyApp.m_oMyP2PWeb.getSystemService(Context.AUDIO_SERVICE);
			am.setMode(AudioManager.MODE_IN_CALL);
			am.setMode(AudioManager.MODE_NORMAL);
		}
		
		m_AmStarted = false;
	}
	
	//========================================================================
	void setMute( boolean bMute ) 
	{
		if( bMute )
		{
			stopSoundInput();
		}
		else
		{
			startSoundInput();
		}		
	}
	
	//========================================================================
	void startSoundInput() 
	{
		try 
		{
			if( null != m_oMicRecorder )
			{
				m_oMicRecorder.startRecording();				
			}
		} 
		catch (Exception e) 
		{
			Log.i("PcmSoundIn","Error:"+e.toString());
		}
	}
	
	//========================================================================
	public void stopSoundInput() 
	{
		try 
		{
			if( null != m_oMicRecorder )
			{
				m_oMicRecorder.stop();				
			}
		}
		catch (Exception e) 
		{
			Log.i("PcmSoundIn","Error:"+e.toString());
		}
	}

	//========================================================================
	public void run() 
	{	
		Log.i( LOG_TAG, "PcmSoundIn run() started " );		
		android.os.Process.setThreadPriority(android.os.Process.THREAD_PRIORITY_URGENT_AUDIO);
		startupPcmSoundIn();
		while( false == m_MyApp.getIsAppShuttingDown() ) 
		{
			if( null == m_oMicRecorder )
			{
				// app is in background.. basically do nothing
				try 
				{
					sleep(500);
				} 
				catch (InterruptedException e) 
				{
					// TODO Auto-generated catch block
					e.printStackTrace();
				} 
				
				continue;
			}
			
			if( ( m_iTotalBufferSize - m_iReadPosition ) > m_iMinReadSize )
			{
				int iSndBytesRead = m_oMicRecorder.read(m_au8SoundBuffer, m_iReadPosition, m_iMinReadSize);
				if( 0 >= iSndBytesRead )
				{
					try 
					{
						sleep(200);
					} 
					catch (InterruptedException e) 
					{
						// TODO Auto-generated catch block
						e.printStackTrace();
					} 
					
					continue;
				}

				//Log.i( LOG_TAG, "PcmSoundIn read " +  iSndBytesRead + " pos " + m_iReadPosition );
				m_iReadPosition += iSndBytesRead;
				while( m_iReadPosition >= m_iSpeexEncodeSize )
				{
					if( m_MyApp.getIsAppShuttingDown() )
					{
						break;
					}
					
					//NativeTxTo.fromGuiMicrophoneData( m_au8SoundBuffer, m_iSpeexEncodeSize );
					int iBytesLeft = m_iReadPosition - m_iSpeexEncodeSize;
					if( iBytesLeft > 0 )
					{
						System.arraycopy(m_au8SoundBuffer, m_iSpeexEncodeSize, m_au8SoundBuffer, 0, iBytesLeft ); 
						m_iReadPosition = iBytesLeft;
					}
					else
					{
						m_iReadPosition = 0;
					}
				}
			}
 		}
		
		Log.e( LOG_TAG, "PcmSoundIn thread exit " );		
	}
}
