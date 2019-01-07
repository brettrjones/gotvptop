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

import android.content.Context;
//import android.util.Log;

class MgrSound 
{
	//private static final String LOG_TAG = "SoundMgr: ";
		
	//=== vars ===//
	private MyApp 				m_MyApp;
	private Context 			m_oApplicationContext;
	private MgrSoundSfx			m_SndSfxMgr;		// manager of short sound effects
	
	//========================================================================
    public MgrSound(MyApp oApp) 
    {
    	//Log.i(LOG_TAG, "SoundMgr: constructed");
    	m_MyApp 		= oApp;
    	m_SndSfxMgr 	= new MgrSoundSfx( m_MyApp );
     }
    
    //========================================================================
    public void startup( Context applicationContext ) 
    {
    	//Log.i(LOG_TAG, "SoundMgr: Startup");
    	m_oApplicationContext = applicationContext;
    	m_SndSfxMgr.startup( m_oApplicationContext );	// manager of music and background sound
     }
    
    //========================================================================
    public void shutdown() 
    {
    	//Log.i(LOG_TAG, "SoundMgr: Shutdown");
    	m_SndSfxMgr.shutdown();	// manager of music and background sound
    }
	
	//========================================================================
	void playOfferSound(int ePluginType)
	{
		switch(ePluginType)
		{
		case Constants.ePluginTypeCamServer:
			// don't play sound for cam server
			break;
		case Constants.ePluginTypeVoicePhone:
		case Constants.ePluginTypeVideoPhone:
		case Constants.ePluginTypeTruthOrDare:
			playSound( ESndDef.eSndDefPhoneRing1 );
			break;
		default:
			playSound( ESndDef.eSndDefNotify1 );
		}		
	}

	//========================================================================
	void playButtonClick()
	{
		playSound( ESndDef.eSndDefButtonClick );
	}
	
	//========================================================================
	void playShredSound()
	{
		playSound( ESndDef.eSndDefPaperShredder );
	}
	
	//========================================================================
	void playSound( ESndDef eSndDef )
	{
		switch( eSndDef )
		{
		case eSndDefAlarmPleasant:
			m_SndSfxMgr.sfxPlay("snd_alarm2");
			break;
			
		case eSndDefAlarmAnoying:
			m_SndSfxMgr.sfxPlay("snd_alarmclock");
			break;
			
		case eSndDefMicrowaveBeep:
			m_SndSfxMgr.sfxPlay("snd_microwave_beep");
			break;
			
		case eSndDefButtonClick:
			m_SndSfxMgr.sfxPlay("snd_keyclick2");
			break;
			
		case eSndDefNotify1:
			m_SndSfxMgr.sfxPlay("snd_notify1");
			break;
			
		case eSndDefPaperShredder:
			m_SndSfxMgr.sfxPlay("snd_papershredder1");
			break;
			
		case eSndDefPhoneRing1:
			m_SndSfxMgr.sfxPlay("snd_phone_ring1");
			break;
			
		case eSndDefOfferArrived:
			m_SndSfxMgr.sfxPlay("snd_beep_spring");
			break;
			
		case eSndDefOfferAccepted:
			m_SndSfxMgr.sfxPlay("snd_alarm2");
			break;
			
		case eSndDefOfferRejected:
			m_SndSfxMgr.sfxPlay("snd_joshua_no");
			break;
			
		case eSndDefBusy:
			m_SndSfxMgr.sfxPlay("snd_busy_phone_signal");
			break;
			
		case eSndDefOfferStillWaiting:
			m_SndSfxMgr.sfxPlay("snd_sonar");
			break;
			
		case eSndDefCameraClick:
			m_SndSfxMgr.sfxPlay("snd_camera_snapshot");
			break;
			
		case eSndDefFileXferComplete:
			m_SndSfxMgr.sfxPlay("snd_file_xfer_complete");
			break;
			
		case eSndDefUserBellMessage:
			m_SndSfxMgr.sfxPlay("snd_bike_bell");
			break;		
			
		case eSndDefNeckSnap:
			m_SndSfxMgr.sfxPlay("snd_neck_snap");
			break;	
			
		case eSndDefSending:
			m_SndSfxMgr.sfxPlay("snd_morse_code");
			break;		
			
		case eSndDefYes:
			m_SndSfxMgr.sfxPlay("snd_yes");
			break;	
			
		case eSndDefAppShutdown:
			m_SndSfxMgr.sfxPlay("snd_byebye");
			break;

		default:
			break;
		}		
	}

	//========================================================================
	public void playSoundFromThread( ESndDef sndDef ) 
	{
		final ESndDef finalSndDef = sndDef;
		if( null != m_MyApp.getMainActivity() )
		{
			m_MyApp.getMainActivity().runOnUiThread(new Runnable() 
			{
				public void run() 
				{
					playSound( finalSndDef );
				}
			});
		}
	}
 };
