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

import java.util.TreeMap;

import android.content.Context;
import android.media.AudioManager;
import android.media.SoundPool;
import android.util.Log;


class MgrSoundSfx
{
	private static final String LOG_TAG = "SoundSfxMgr: ";
	private final int 			MAX_SFX_STREAMS = 28;
	
	//private MyApp 				m_MyApp;
	private Context 			m_oApplicationContext = null;

	private SoundPool 			m_oSoundPool = null;
	private AudioManager  		m_oAudioManager;
	private TreeMap<String,Integer> m_oNameToId = new TreeMap<String, Integer>();
	private float 				m_MaxSndEffectVolume 	= 0.99f;
	private float 				m_CurSndEffectVolume 	= 0.99f;
	//private int					m_iNextSndId 			= 0;
	
	private boolean				m_bInitialized = false;
	
    //========================================================================
	MgrSoundSfx( MyApp myApp ) 
	{
		//m_MyApp = myApp;
	}
	
    //========================================================================
    public void startup( Context applicationContext )
    {
    	if( m_bInitialized )
    	{
    		return;
    	}
    	
    	m_oApplicationContext = applicationContext;
		m_oAudioManager = (AudioManager)m_oApplicationContext.getSystemService(Context.AUDIO_SERVICE);
		//re-init sound pool to work around bugs
		releaseSoundPool();

		m_oSoundPool = new SoundPool( MAX_SFX_STREAMS, AudioManager.STREAM_MUSIC, 0 );
		m_MaxSndEffectVolume = m_oAudioManager.getStreamMaxVolume(AudioManager.STREAM_MUSIC);
		setSndEffectsVolume( ( float ) 0.7 );

		// this sucks.. must preload sounds because
		// otherwise sounds will not be ready first time loaded and will not
		// play first attempt. In level 8 sdk the sound could be played as soon
		// as load completes by using OnLoadCompleteListener
		
		// NOTE: OGG format must be 16 bit, 48000 hz, 192kbs, CBR mode
		
		
		sfxLoadSound("snd_alarm2");
		sfxLoadSound("snd_alarmclock");
		sfxLoadSound("snd_keyclick2");
		sfxLoadSound("snd_notify1");
		sfxLoadSound("snd_papershredder1");

		sfxLoadSound("snd_phone_ring1");
		sfxLoadSound("snd_beep_spring");
		sfxLoadSound("snd_microwave_beep");
		sfxLoadSound("snd_joshua_no");
		sfxLoadSound("snd_busy_phone_signal");

		sfxLoadSound("snd_sonar");
		sfxLoadSound("snd_camera_snapshot");
		sfxLoadSound("snd_file_xfer_complete");
		sfxLoadSound("snd_bike_bell");
		sfxLoadSound("snd_neck_snap");
		sfxLoadSound("snd_morse_code");
		sfxLoadSound("snd_byebye");
		sfxLoadSound("snd_yes");
		
		//Log.e("SoundSfxMgr", "Preload Resources Done");
		m_bInitialized = true;
    }
    
    //========================================================================    
    public void shutdown()
    {
    	releaseSoundPool();
    	//m_bInitialized = false;
    }
    
    //========================================================================
	private void releaseSoundPool()
	{
		if( m_oSoundPool != null)
		{
			m_oSoundPool.release();
			m_oSoundPool = null;
		}
	}
	
    //========================================================================
    //! sets volume ( normalized to 0.0 to 1.0 range )
	public void setSndEffectsVolume( float volume0To1 )
	{
		if( ( volume0To1 >= 1.0f ) || ( volume0To1 < 0.0f ) )
		{
			volume0To1 = 0.99f;
		}

		m_CurSndEffectVolume = volume0To1;
		Log.i( LOG_TAG, "setSndEffectsVolume cur "  + m_CurSndEffectVolume + " max " + m_MaxSndEffectVolume );
	}
	
    //========================================================================
    //! gets volume ( normalized to 0.0 to 1.0 range )
	public float getCurVolume0To1()
	{
		float streamVolume = m_oAudioManager.getStreamVolume(AudioManager.STREAM_MUSIC);
		streamVolume = streamVolume / m_MaxSndEffectVolume;

		if( ( streamVolume >= 1.0f ) || ( streamVolume < 0.0f ) )
		{
			streamVolume = 0.99f;
		}
		
		return streamVolume;
	}
    
    //========================================================================
    //! load sound into cache 
	private int sfxLoadSound(String strSndFile)
	{
		// get path to resource then get resource id
		
		// get resource id from full file path
		String strSndResource = m_oApplicationContext.getPackageName()+":raw/" + strSndFile;
		//Log.i(LOG_TAG, "SfxLoadSound: loading " + strSndResource );
		
		int iSndResourceId = m_oApplicationContext.getResources().getIdentifier(strSndResource, null, null);
		if( iSndResourceId == 0 )
		{
			// could not locate resource
			//Log.e("SoundSfxMgr", "Could not open Sound Resource" + strSndResource);
			return 0;
		}
		
		int iSndId = m_oSoundPool.load( m_oApplicationContext, iSndResourceId, 1 );
		
		// add sound association to our map of file to id
		m_oNameToId.put( strSndFile, iSndId );
		//Log.e("SoundSfxMgr", "Assigned sound " + strSndResource + " to " + iSndId);
		
		return iSndId;
	}
	
    //========================================================================
    //! play sound
	public void sfxPlay( String strSndFile )
	{
		if( ( false == m_bInitialized )
				|| ( null == m_oApplicationContext )
				|| ( null == m_oSoundPool ) )
		{
			return;
		}		
		
		//Log.i(LOG_TAG, "SfxPlay: file " + strSndFile );
		if( strSndFile.length() == 0 )
		{
			Log.i(LOG_TAG, "SfxPlay: null sound file name" );
			return;
		}
		
		// Remove the extension if exists.. 
	    int iExtensionIndex = strSndFile.lastIndexOf("."); 
	    if (iExtensionIndex > 0 )
	    {
	    	strSndFile = strSndFile.substring(0, iExtensionIndex);
	    }

		int iSndId = 0;
		if( m_oNameToId.containsKey(strSndFile) )
		{
			iSndId = m_oNameToId.get(strSndFile);
		}
			
		if( iSndId <= 0 )
		{
			// sound was not previously loaded.. load into sound pool cache and get sound id
			iSndId = sfxLoadSound( strSndFile );
			if( iSndId <= 0 )
			{
				// sound could not be loaded
				Log.i(LOG_TAG, "SfxPlay: Could Not load file" + strSndFile );
				return;		
			}
		}
		
		Log.i(LOG_TAG, "SfxPlay: Id " + iSndId + " vol " + m_CurSndEffectVolume + " max vol " + m_MaxSndEffectVolume  );
		if( 0.0f != m_CurSndEffectVolume )
		{
			// play non looped
			m_oSoundPool.play( iSndId, 					// sound id
								m_CurSndEffectVolume, 	// left volume
								m_CurSndEffectVolume, 	// right volume
								1,						// priority 
								0, 						// loop if not zero ( -1 = forever )
								1.0f );					// playback rate
		}
		
		// to play looping
		//m_oSoundPool.play( iSndId, streamVolume, streamVolume, 1, -1, 1.0f);
	}
};


