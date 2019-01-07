/*
 *  Copyright (c) 2015 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */
// Code Modified for MyP2PWeb by Brett R. Jones

package com.p2pgotv.gotvstation;

import java.lang.Thread;
import java.nio.ByteBuffer;
import java.util.concurrent.Semaphore;

import android.annotation.TargetApi;
import android.content.Context;
import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;
import android.os.Process;
import android.util.Log;

class WebRtcAudioTrack
{
	private static final boolean DEBUG = false;

	private static final String LOG_TAG = "WebRtcAudioTrack";

	// Default audio data format is PCM 16 bit per sample.
	// Guaranteed to be supported by all devices.
	private static final int BITS_PER_SAMPLE = 16;

	// Requested size of each recorded buffer provided to the client.
	private static final int CALLBACK_BUFFER_SIZE_MS = 10;

	// Average number of callbacks per second.
	private static final int BUFFERS_PER_SECOND = 1000 / CALLBACK_BUFFER_SIZE_MS;

	private final Context 		context;
	private final long 			nativeAudioTrack;
	private final AudioManager 	audioManager;

	private ByteBuffer 			byteBuffer;

	private AudioTrack 			audioTrack 				= null;
	private AudioTrackThread 	audioThread 			= null;
	private boolean 			m_PlayoutStarted 		= false;
	private static boolean 		m_WantSpeakerOutput 	= false;
	final Semaphore 			m_SpeakerSemaphore 		= new Semaphore(1); 

	/**
	 * Audio thread which keeps calling AudioTrack.write() to stream audio. Data
	 * is periodically acquired from the native WebRTC layer using the
	 * nativeGetPlayoutData callback function. This thread uses a
	 * Process.THREAD_PRIORITY_URGENT_AUDIO priority.
	 */
	private class AudioTrackThread extends Thread implements ToGuiHardwareControlInterface
	{
		private volatile boolean m_KeepAlive = true;

		//========================================================================
		public AudioTrackThread( String name )
		{
			super( name );
		}

		//========================================================================
		@Override
		public void run()
		{
		    final String orgName = Thread.currentThread().getName();
		    Thread.currentThread().setName( orgName + " AudioTrackThread" );		

			Process.setThreadPriority( Process.THREAD_PRIORITY_URGENT_AUDIO );
			Log.d( LOG_TAG,
					"AudioTrackThread" + WebRtcAudioUtils.getThreadInfo() );

			try
			{
				// In MODE_STREAM mode we can optionally prime the output buffer
				// by
				// writing up to bufferSizeInBytes (from constructor) before
				// starting.
				// This priming will avoid an immediate underrun, but is not
				// required.
				// TODO(henrika): initial tests have shown that priming is not
				// required.
				audioTrack.play();
				assertTrue( audioTrack.getPlayState() == AudioTrack.PLAYSTATE_PLAYING );
			}
			catch( IllegalStateException e )
			{
				Log.e( LOG_TAG, "AudioTrack.play failed: " + e.getMessage() );
				return;
			}

			// Fixed size in bytes of each 10ms block of audio data that we ask
			// for
			// using callbacks to the native WebRTC client.
			final int sizeInBytes = byteBuffer.capacity();
			try
			{
				NativeRxFrom.wantToGuiHardwareControl( this, true );
				while( m_KeepAlive )
				{
					if( false == m_WantSpeakerOutput )
					{
						//  basically do nothing
						m_SpeakerSemaphore.acquire();						
						if( false == m_KeepAlive )
						{
							break;
						}

						if( false == m_WantSpeakerOutput )
						{
							sleep( 100 );
							continue;
						}
					}
					
					// Get 10ms of PCM data from the native WebRTC client. Audio
					// data is
					// written into the common ByteBuffer using the address that was
					// cached at construction.
					NativeTxTo.fromGuiGetPlayoutData( sizeInBytes, nativeAudioTrack );
					// Write data until all data has been written to the audio sink.
					// Upon return, the buffer position will have been advanced to
					// reflect
					// the amount of data that was successfully written to the
					// AudioTrack.
					assertTrue( sizeInBytes <= byteBuffer.remaining() );
					int bytesWritten = 0;
					if( WebRtcAudioUtils.runningOnLollipopOrHigher() )
					{
						bytesWritten = writeOnLollipop( audioTrack, byteBuffer,
								sizeInBytes );
					}
					else
					{
						bytesWritten = writePreLollipop( audioTrack, byteBuffer,
								sizeInBytes );
					}
					if( bytesWritten != sizeInBytes )
					{
						Log.e( LOG_TAG, "AudioTrack.write failed: " + bytesWritten );
						if( bytesWritten == AudioTrack.ERROR_INVALID_OPERATION )
						{
							m_KeepAlive = false;
						}
					}
					// The byte buffer must be rewinded since byteBuffer.position()
					// is
					// increased at each call to AudioTrack.write(). If we don't do
					// this,
					// next call to AudioTrack.write() will fail.
					byteBuffer.rewind();
	
					// TODO(henrika): it is possible to create a delay estimate here
					// by
					// counting number of written frames and subtracting the result
					// from
					// audioTrack.getPlaybackHeadPosition().
				}
			}
			catch( InterruptedException e )
			{
				// TODO Auto-generated catch block
				e.printStackTrace();
			}

			NativeRxFrom.wantToGuiHardwareControl( this, false );
			try
			{
				audioTrack.stop();
			}
			catch( IllegalStateException e )
			{
				Log.e( LOG_TAG, "AudioTrack.stop failed: " + e.getMessage() );
			}
			assertTrue( audioTrack.getPlayState() == AudioTrack.PLAYSTATE_STOPPED );
			audioTrack.flush();
		}

		//========================================================================
		@TargetApi(21)
		private int writeOnLollipop( AudioTrack audioTrack,
				ByteBuffer byteBuffer, int sizeInBytes )
		{
			return audioTrack.write( byteBuffer, sizeInBytes,
					AudioTrack.WRITE_BLOCKING );
		}

		//========================================================================
		private int writePreLollipop( AudioTrack audioTrack,
				ByteBuffer byteBuffer, int sizeInBytes )
		{
			return audioTrack.write( byteBuffer.array(),
					byteBuffer.arrayOffset(), sizeInBytes );
		}

		//========================================================================
		public void joinThread()
		{
			m_KeepAlive = false;
			m_SpeakerSemaphore.release();
			while( isAlive() )
			{
				try
				{
					join();
				}
				catch( InterruptedException e )
				{
					// Ignore.
				}
			}
		}

		//========================================================================
		@Override
		public void doGuiShutdownHardware()
		{
			m_KeepAlive = false;
			m_SpeakerSemaphore.release();
		}

		//========================================================================
		@Override
		public void doGuiWantMicrophoneRecording( boolean wantMicInput )
		{
		}

		//========================================================================
		@Override
		public void doGuiWantSpeakerOutput( boolean wantSpeakerOutput )
		{
			m_WantSpeakerOutput = wantSpeakerOutput;
			if( m_WantSpeakerOutput )
			{
				m_SpeakerSemaphore.release();
			}			
		}

		//========================================================================
		@Override
		public void doGuiWantVideoCapture( boolean wantVideoCapture )
		{
		}
	}

	//========================================================================
	WebRtcAudioTrack( Context context, long nativeAudioTrack )
	{
		Log.d( LOG_TAG, "ctor" + WebRtcAudioUtils.getThreadInfo() );
		this.context = context;
		this.nativeAudioTrack = nativeAudioTrack;
		audioManager = ( AudioManager ) context.getSystemService( Context.AUDIO_SERVICE );
	}

	//========================================================================
	private boolean initPlayout( int sampleRate, int channels )
	{
		Log.d( LOG_TAG, "initPlayout(sampleRate=" + sampleRate + ", channels=" + channels + ")" );
		if( null == audioTrack )
		{
			final int bytesPerFrame = channels * ( BITS_PER_SAMPLE / 8 );
			byteBuffer = byteBuffer.allocateDirect( bytesPerFrame * ( sampleRate / BUFFERS_PER_SECOND ) );
			Log.d( LOG_TAG, "byteBuffer.capacity: " + byteBuffer.capacity() );
			// Rather than passing the ByteBuffer with every callback (requiring
			// the potentially expensive GetDirectBufferAddress) we simply have the
			// the native class cache the address to the memory once.
			NativeTxTo.fromGuiCachePlayoutDirectBufferAddress( byteBuffer, nativeAudioTrack );
	
			// Get the minimum buffer size required for the successful creation of
			// an
			// AudioTrack object to be created in the MODE_STREAM mode.
			// Note that this size doesn't guarantee a smooth playback under load.
			// TODO(henrika): should we extend the buffer size to avoid glitches?
			final int minBufferSizeInBytes = AudioTrack.getMinBufferSize(
					sampleRate, AudioFormat.CHANNEL_OUT_MONO,
					AudioFormat.ENCODING_PCM_16BIT );
			Log.d( LOG_TAG, "AudioTrack.getMinBufferSize: " + minBufferSizeInBytes );
			assertTrue( audioTrack == null );
	
			// For the streaming mode, data must be written to the audio sink in
			// chunks of size (given by byteBuffer.capacity()) less than or equal
			// to the total buffer size |minBufferSizeInBytes|.
			assertTrue( byteBuffer.capacity() < minBufferSizeInBytes );
			try
			{
				// Create an AudioTrack object and initialize its associated audio
				// buffer.
				// The size of this buffer determines how long an AudioTrack can
				// play
				// before running out of data.
				audioTrack = new AudioTrack( AudioManager.STREAM_MUSIC,
											sampleRate, 
											AudioFormat.CHANNEL_OUT_MONO,
											AudioFormat.ENCODING_PCM_16BIT, 
											minBufferSizeInBytes,
											AudioTrack.MODE_STREAM );
			}
			catch( IllegalArgumentException e )
			{
				String exceptMsg = e.getMessage();
				Log.d( LOG_TAG, "initPlayout ERROR " + exceptMsg );
				return false;
			}
	
			// It can happen that an AudioTrack is created but it was not
			// successfully
			// initialized upon creation. Seems to be the case e.g. when the maximum
			// number of globally available audio tracks is exceeded.
			if( audioTrack.getState() != AudioTrack.STATE_INITIALIZED )
			{
				Log.e( LOG_TAG, "Initialization of audio track failed." );
				return false;
			}
			
			//setStreamVolume( getStreamMaxVolume() );
		}
		else
		{
			Log.e( LOG_TAG, "ERROR WebRtcAudioTrack.initPlayout audioTrack is not null" );			
		}
		
		return true;
	}

	//========================================================================
	private boolean startPlayout()
	{
		if( false == m_PlayoutStarted )
		{
			m_PlayoutStarted = true;
			Log.d( LOG_TAG, "startPlayout" );
			assertTrue( audioTrack != null );
			assertTrue( audioThread == null );
			if( audioTrack.getState() != AudioTrack.STATE_INITIALIZED )
			{
				Log.e( LOG_TAG, "Audio track is not successfully initialized." );
				return false;
			}
			
			audioThread = new AudioTrackThread( "AudioTrackJavaThread" );
			audioThread.start();
		}
		else
		{
			Log.e( LOG_TAG, "Audio track startPlayout called while allready playing." );
		}
		
		return true;
	}

	//========================================================================
	private boolean stopPlayout()
	{
		if( m_PlayoutStarted )
		{
			m_PlayoutStarted = false;
			Log.d( LOG_TAG, "stopPlayout" );
			if( null != audioThread )
			{
				audioThread.joinThread();
				audioThread = null;
			}
			
			if( audioTrack != null )
			{
				audioTrack.stop();
				audioTrack.release();
				audioTrack = null;
			}

			Log.d( LOG_TAG, "stopPlayout done" );
		}
		else
		{
			Log.e( LOG_TAG, "Audio track startPlayout called when not playing." );
		}
		
		return true;
	}

	//========================================================================
	/** Get max possible volume index for a phone call audio stream. */
	private int getStreamMaxVolume()
	{
		Log.d( LOG_TAG, "getStreamMaxVolume" );
		assertTrue( audioManager != null );
		return audioManager.getStreamMaxVolume( AudioManager.STREAM_MUSIC );
	}

	//========================================================================
	/** Set current volume level for a phone call audio stream. */
	private boolean setStreamVolume( int volume )
	{
		Log.d( LOG_TAG, "setStreamVolume(" + volume + ")" );
		assertTrue( audioManager != null );
		if( isVolumeFixed() )
		{
			Log.e( LOG_TAG, "The device implements a fixed volume policy." );
			return false;
		}
		
		Log.e( LOG_TAG, "setStreamVolume " + volume);
		audioManager.setStreamVolume( AudioManager.STREAM_MUSIC, volume, 0 );
		return true;
	}

	//========================================================================
	private boolean isVolumeFixed()
	{
		if( !WebRtcAudioUtils.runningOnLollipopOrHigher() )
			return false;
		return audioManager.isVolumeFixed();
	}

	//========================================================================
	/** Get current volume level for a phone call audio stream. */
	private int getStreamVolume()
	{
		Log.d( LOG_TAG, "getStreamVolume" );
		assertTrue( audioManager != null );
		return audioManager.getStreamVolume( AudioManager.STREAM_MUSIC );
	}

	//========================================================================
	/** Helper method which throws an exception when an assertion has failed. */
	private static void assertTrue( boolean condition )
	{
		if( !condition )
		{
			throw new AssertionError( "Expected condition to be true" );
		}
	}
}
