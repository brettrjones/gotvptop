//============================================================================
// Copyright (C) 2010 Brett R. Jones
// Issued to MIT style license by Brett R. Jones in 2017
//
// You may use, copy, modify, merge, publish, distribute, sub-license, and/or sell this software
// provided this Copyright is not modified or removed and is included all copies or substantial portions of the Software
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// brett.jones@engineer.com
// http://www.gotvptop.net
//============================================================================

#ifdef ANDROID_PLATFORM

#else
#ifdef TARGET_OS_WINDOWS
#else
#define DISABLE_AUDIO
#endif
#endif


#include "MySndMgr.h"
#include "MyQtSoundInput.h"
#include "MyQtSoundOutput.h"
#include "VxSndInstance.h"
#include "AppCommon.h"

#include <CoreLib/VxDebug.h>
#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>

#include <QDebug>
//#include <QSound>
#include <QMessageBox>

#undef USE_ECHO_CANCEL

namespace
{
	const int					MYP2PWEB_SAMPLE_RATE = 8000;
}

//============================================================================
MySndMgr& GetSndMgrInstance( void )
{
	return GetAppInstance().getSoundMgr();
}

//============================================================================
MySndMgr::MySndMgr( AppCommon& app )
: m_MyApp( app )
, m_Engine( app.getEngine() )
, m_MicrophoneInput(NULL)
, m_bMicrophoneEnabled(true)
, m_VoiceOutput(NULL)
, m_bAudioOutputStarted(false)
, m_bMutePhoneRing(false)
, m_bMuteNotifySnd(false)
, m_CurSndPlaying( 0 )
#ifdef USE_ECHO_CANCEL
, m_WaveWin( 1 )
, m_MyFrameReadIdx( 0 )
, m_MyFrameDataAvail( 0 )
#endif // USE_ECHO_CANCEL
{
#ifdef USE_VX_WAVE
#ifndef USE_ECHO_CANCEL
	m_WaveIn.setWaveInCallback( this, this );
	m_WaveOut.setWaveOutCallback( this, this );
#endif // USE_ECHO_CANCEL
#endif // USE_VX_WAVE
}

//============================================================================
MySndMgr::~MySndMgr()
{
}

//============================================================================ 
void MySndMgr::slotStartPhoneRinging( void )
{
	playSnd( eSndDefPhoneRing1, true );
}

//============================================================================ 
void MySndMgr::slotStopPhoneRinging( void )
{
	if( m_CurSndPlaying 
		&& ( eSndDefPhoneRing1 == m_CurSndPlaying->getSndDef() ) )
	{
		m_CurSndPlaying->stopPlay();
	}
}

//============================================================================
void MySndMgr::slotPlayNotifySound( void )
{
	playSnd( eSndDefNotify1, true );
}

//============================================================================
void MySndMgr::slotPlayShredderSound( void )
{
	playSnd( eSndDefPaperShredder, true );
}

//============================================================================
void MySndMgr::mutePhoneRing( bool bMute )
{
	m_bMutePhoneRing = bMute;
	if( bMute )
	{
		slotStopPhoneRinging();
	}
}

//============================================================================
void MySndMgr::muteNotifySound( bool bMute )
{
	m_bMuteNotifySnd = bMute;
}

//============================================================================
bool MySndMgr::sndMgrStartup( void )
{
#ifdef ANDROID_PLATFORM
	LogMsg( LOG_INFO, "MySndMgr::Android defined\n" );
    return false;
#else
	#ifdef TARGET_OS_WINDOWS
	LogMsg( LOG_INFO, "Windows defined\n" );
 	#else
	    LogMsg( LOG_INFO, "Linux defined\n" );
		#define DISABLE_AUDIO
	#endif
#endif

    for( int i = 0; i < eMaxSndDef; i++ )
    {
        VxSndInstance * sndInstance = new VxSndInstance( (ESndDef)i, this );
        connect( sndInstance, SIGNAL(sndFinished(VxSndInstance *)), this, SLOT(slotSndFinished(VxSndInstance *)) );
        m_SndList.push_back( sndInstance );
    }

#ifdef  DISABLE_AUDIO
    return false;
#endif //  DISABLE_AUDIO

    LogMsg( LOG_INFO, "MySndMgr::sndMgrStartup 2222\n" );
	bool result = true;
#ifdef USE_VX_WAVE
#ifdef USE_ECHO_CANCEL
	m_MyFrameReadIdx	= 0;
	m_MyFrameDataAvail	= 0;
	m_MyLastReadSample	= 0;

	memset( m_MyFrameBuf, 0, sizeof( m_MyFrameBuf ) );

	webrtc::AudioDeviceModule::AudioLayer audioLayer = webrtc::AudioDeviceModule::kWindowsWaveAudio;
	if( -1 == m_WaveWin.ActiveAudioLayer( audioLayer ) ) 
	{
		LogMsg( LOG_ERROR, "sndMgrStartup m_WaveWin.ActiveAudioLayer returned error\n");
		result = false;
	}

	m_WaveWin.AttachAudioBuffer( &m_AudioDeviceBuffer );
	m_AudioDeviceBuffer.RegisterAudioCallback( this );

	int rc = m_WaveWin.Init();
	if( 0 != rc )
	{
		LogMsg( LOG_ERROR, "sndMgrStartup m_WaveWin.Init returned error %d\n", rc );
		result = false;
	}


	rc = m_WaveWin.InitSpeaker();
	if( 0 != rc )
	{
		LogMsg( LOG_ERROR, "sndMgrStartup m_WaveWin.InitSpeaker returned error %d\n", rc );
		result = false;
	}

	webrtc::AudioDeviceModule::WindowsDeviceType audioDeviceType = webrtc::AudioDeviceModule::kDefaultDevice;
	rc = m_WaveWin.SetPlayoutDevice( audioDeviceType );
	if( 0 != rc )
	{
		LogMsg( LOG_ERROR, "sndMgrStartup m_WaveWin.SetPlayoutDevice returned error %d\n", rc );
		result = false;
	}

	rc = m_WaveWin.SetRecordingDevice( audioDeviceType );
	if( 0 != rc )
	{
		LogMsg( LOG_ERROR, "sndMgrStartup m_WaveWin.SetRecordingDevice returned error %d\n", rc );
		result = false;
	}

	rc = m_WaveWin.InitPlayout();  // InitPlayout calls InitSpeaker
	if( 0 != rc )
	{
		LogMsg( LOG_ERROR, "sndMgrStartup m_WaveWin.InitPlayout returned error %d\n", rc );
		result = false;
	}

	rc = m_WaveWin.InitRecording(); // InitRecording calls InitMicrophone
	if( 0 != rc )
	{
		LogMsg( LOG_ERROR, "sndMgrStartup m_WaveWin.InitRecording returned error %d\n", rc );
		result = false;
	}

    //BRJ disabled until can replace
	//rc = m_WaveWin.StartPlayout();
	if( 0 != rc )
	{
		LogMsg( LOG_ERROR, "sndMgrStartup m_WaveWin.StartPlayout returned error %d\n", rc );
		result = false;
	}

	rc = m_WaveWin.StartRecording();
	if( 0 != rc )
	{
		LogMsg( LOG_ERROR, "sndMgrStartup m_WaveWin.StartRecording returned error %d\n", rc );
		result = false;
	}

#else	
		m_WaveIn.startWaveInput();
		m_WaveOut.startWaveOutput();
#endif // USE_ECHO_CANCEL
#endif // USE_VX_WAVE

	m_MyApp.wantToGuiHardwareCtrlCallbacks( this, true );
	return result;
}


//============================================================================
bool MySndMgr::sndMgrShutdown( void )
{
	m_MyApp.wantToGuiHardwareCtrlCallbacks( this, false );
#ifdef DISABLE_AUDIO
	return false;
#endif
#ifdef USE_ECHO_CANCEL
	m_WaveWin.StopRecording();
	m_WaveWin.StopPlayout();
	m_WaveWin.Terminate();
#endif // USE_ECHO_CANCEL

	return true;
}

//============================================================================
void MySndMgr::doGuiWantMicrophoneRecording( bool wantMicInput )
{
	if( wantMicInput )
	{
		startMicrophoneRecording();
	}
	else
	{
		stopMicrophoneRecording();
	}
}

//============================================================================
void MySndMgr::doGuiWantSpeakerOutput( bool wantSpeakerOutput )
{
	enableSpeakerOutput( wantSpeakerOutput );
}

//============================================================================
VxSndInstance * MySndMgr::playSnd( ESndDef sndDef, bool loopContinuous  )
{

#ifdef DISABLE_AUDIO
    return 0;
#endif // DISABLE_AUDIO

	if( m_bMutePhoneRing 
		&& ( eSndDefPhoneRing1 == sndDef ) )
	{
		return m_SndList[ eSndDefNone ];
	}

	if( m_bMuteNotifySnd 
		&& ( ( eSndDefNotify1 == sndDef ) || ( eSndDefNotify2 == sndDef ) ) )
	{
		return m_SndList[ eSndDefNone ];
	}

    if( ( sndDef < m_SndList.size() )
		&& ( 0 <= sndDef ) )
	{
		if( m_CurSndPlaying )
		{
			m_CurSndPlaying->stopPlay();
		}

		m_CurSndPlaying = m_SndList[ sndDef ];
		m_CurSndPlaying->startPlay( loopContinuous );
		return m_CurSndPlaying;
	}
	else
	{
		return m_SndList[ eSndDefNone ];
	}
}

//============================================================================
void MySndMgr::stopSnd( ESndDef sndDef )
{
	if( m_CurSndPlaying 
		&& ( sndDef == m_CurSndPlaying->getSndDef() ) )
	{
		m_CurSndPlaying->stopPlay();
		m_CurSndPlaying = 0;
	}
}

//============================================================================
void MySndMgr::slotSndFinished( VxSndInstance * sndInstance )
{
	if( m_CurSndPlaying == sndInstance )
	{
		m_CurSndPlaying = 0;
	}
}

//============================================================================
//! called when microphone recoding is needed
void MySndMgr::startMicrophoneRecording()
{
	enableMicrophoneInput( true );
}

//============================================================================
//! called when microphone recoding not needed
void MySndMgr::stopMicrophoneRecording()
{
	enableMicrophoneInput( false );
}

//============================================================================
void MySndMgr::enableMicrophoneInput( bool enable )
{
	if( enable != m_bMicrophoneEnabled )
	{
		m_bMicrophoneEnabled = enable;
		LogMsg( LOG_INFO, "Microphone Enable %d\n", enable );
	}
}

//============================================================================
void MySndMgr::enableSpeakerOutput( bool bEnable )
{
	if( bEnable != m_bVoiceOutputEnabled )
	{
		m_bVoiceOutputEnabled = bEnable;
	}
}

//============================================================================
void MySndMgr::recievedAudioData( char * pu16PcmData, int u16PcmDataLen)
{
#ifdef USE_VX_WAVE
#ifdef USE_ECHO_CANCEL
		if( u16PcmDataLen == sizeof( m_MyFrameBuf ) )
		{
			memcpy( m_MyFrameBuf, pu16PcmData, u16PcmDataLen );
			m_MyFrameDataAvail = u16PcmDataLen;
			m_MyFrameReadIdx = 0;
		}
#else
	if( m_bVoiceOutputEnabled )
	{
		m_WaveOut.sendAudioDataToSpeaker( pu16PcmData, u16PcmDataLen );
	}
#endif // USE_ECHO_CANCEL
#else
	if( m_bVoiceOutputEnabled )
	{
		if( m_VoiceOutput )
			m_VoiceOutput->recieveAudioData(pu16PcmData, u16PcmDataLen );
	}
#endif // USE_VX_WAVE
}

#ifdef USE_VX_WAVE
//============================================================================
void MySndMgr::waveInPcmDataAvail( char * sndData, int dataLen, void * /*userData*/ )
{
	if( m_bMicrophoneEnabled )
	{
		m_MyApp.getEngine().fromGuiMicrophoneData( (int16_t *)sndData, dataLen );
	}
}

//============================================================================
void MySndMgr::waveOutSpaceAvail( int freeSpaceLen, void * /*userData*/ )
{
	m_MyApp.getEngine().fromGuiAudioOutSpaceAvail( freeSpaceLen );
}

#ifdef USE_ECHO_CANCEL
//============================================================================
int32_t MySndMgr::RecordedDataIsAvailable(			const void* audioSamples,
													const size_t nSamples,
													const size_t nBytesPerSample,
													const size_t nChannels,
													const uint32_t samplesPerSec,
													const uint32_t totalDelayMS,
													const int32_t clockDrift,
													const uint32_t currentMicLevel,
													const bool keyPressed,
													uint32_t& newMicLevel )
{
	//LogMsg( LOG_INFO, "MySndMgr::RecordedDataIsAvailable nSamples %d\n", nSamples );
	float dnFreqDiv = (float)samplesPerSec  / (float)MYP2PWEB_SAMPLE_RATE;
	float dnResampleDiv = dnFreqDiv * nChannels;

	if( 1.0f == dnResampleDiv )
	{
		// no resample required
		m_Engine.fromGuiMicrophoneDataWithInfo( (int16_t *)audioSamples, nSamples * nBytesPerSample, totalDelayMS, clockDrift );
	}
	else
	{
		// down resample to 8000 hz
		int mySampleCnt				= nSamples / dnFreqDiv;
		int middleOfSampleOffset	= (int)(dnFreqDiv / 2.0f);
		int16_t * dnSampledBuf			= new int16_t[ mySampleCnt ];
		int16_t * srcSamples			= (int16_t *)audioSamples;
		float smpInc				= dnResampleDiv;
		for( int i = 0; i < mySampleCnt; i++ )
		{
			int iSrcIdx = (int)(smpInc * (float)i) + middleOfSampleOffset;
			dnSampledBuf[i] = srcSamples[ iSrcIdx ];
		}

		m_Engine.fromGuiMicrophoneDataWithInfo( dnSampledBuf, mySampleCnt << 1, totalDelayMS, clockDrift );
		delete dnSampledBuf;
	}

	return 0;
}

//============================================================================
int32_t MySndMgr::NeedMorePlayData(		const size_t nSamples,
										 const size_t nBytesPerSample,
										 const size_t nChannels,
										 const uint32_t samplesPerSec,
										 void* audioSamples,
										 size_t& nSamplesOut,
										 int64_t* elapsed_time_ms,
										 int64_t* ntp_time_ms )
{
	//LogMsg( LOG_INFO, "MySndMgr::NeedMorePlayData nSamples %d\n", nSamples );
	if( 0 == m_MyFrameDataAvail )
	{
		m_Engine.fromGuiAudioOutSpaceAvail( MY_FRAME_DATA_LEN );
	}

	size_t deviceReqDataLen = nSamples * nBytesPerSample * nChannels;
	float upResampleMultiplier = samplesPerSec  / MYP2PWEB_SAMPLE_RATE;
	int myUsedDataLen = deviceReqDataLen / upResampleMultiplier;
	int iDestIdx = 0;
	if( nChannels == 2 )
	{
		upResampleMultiplier *= 2;
	}

	size_t resampledLenAvail = m_MyFrameDataAvail * upResampleMultiplier;

	if( resampledLenAvail >= deviceReqDataLen )
	{
		if( 1 == upResampleMultiplier )
		{
			memcpy( audioSamples, &m_MyFrameBuf[m_MyFrameReadIdx], myUsedDataLen );
		}
		else
		{
			int mySampleCnt = myUsedDataLen >> 1;
			int16_t * srcSamples	= (int16_t *)&m_MyFrameBuf[m_MyFrameReadIdx];
			int16_t * destSamples	= (int16_t *)audioSamples;
			int16_t firstSample		= m_MyLastReadSample;
			int16_t secondSample	= firstSample;
			float sampleStep;
			for( int i = 0; i < mySampleCnt; i++ )
			{
				firstSample = secondSample;
				secondSample = srcSamples[i];
				if( secondSample >= firstSample )
				{
					// ramp up
					sampleStep = ((secondSample - firstSample) / upResampleMultiplier); 
				}
				else
				{
					// ramp down
					sampleStep = -((firstSample - secondSample) / upResampleMultiplier); 
				}

				if( 0 == sampleStep )
				{
					for( int j = 0; j < upResampleMultiplier; ++j )
					{
						destSamples[iDestIdx] = firstSample; 
						iDestIdx++;
					}
				}
				else
				{
					float sampleOffs = sampleStep;
					int resampleCnt = (int)upResampleMultiplier;
					for( int j = 0; j < resampleCnt; ++j )
					{
						destSamples[iDestIdx] = (int16_t)(firstSample + sampleOffs); 
						iDestIdx++;
						sampleOffs += sampleStep;
					}
				}
			}

			// save the last sample to be used as first sample reference in next frame
			m_MyLastReadSample = srcSamples[ mySampleCnt - 1 ];
		}

		m_MyFrameDataAvail -= myUsedDataLen;
		m_MyFrameReadIdx	+= myUsedDataLen;
		if( m_MyFrameReadIdx >= MY_FRAME_DATA_LEN )
		{
			m_MyFrameReadIdx = 0;
		}
	}
	else
	{
		memset( audioSamples, 0, deviceReqDataLen );
	}


	nSamplesOut = nSamples;
	return 0;
}

//============================================================================
int MySndMgr::OnDataAvailable(	const int voe_channels[],
											size_t number_of_voe_channels,
											const int16_t* audio_data,
											int sample_rate,
											size_t number_of_channels,
											size_t number_of_frames,
											int audio_delay_milliseconds,
											int current_volume,
											bool key_pressed,
											bool need_audio_processing )
{
	LogMsg( LOG_INFO, "MySndMgr::OnDataAvailable number_of_frames %d\n", number_of_frames );
	return 0;
}

//============================================================================
void MySndMgr::OnData( int voe_channel,
								   const void* audio_data,
								   int bits_per_sample,
								   int sample_rate,
								   size_t number_of_channels,
								   size_t number_of_frames)
{
	LogMsg( LOG_INFO, "MySndMgr::OnData number_of_frames %d\n", number_of_frames );
}

//============================================================================
void MySndMgr::PushCaptureData(	int voe_channel,
								const void* audio_data,
								int bits_per_sample,
								int sample_rate,
								size_t number_of_channels,
								size_t number_of_frames )
{
	LogMsg( LOG_INFO, "MySndMgr::PushCaptureData number_of_frames %d\n", number_of_frames );
}

//============================================================================
void MySndMgr::PullRenderData(	int bits_per_sample,
								int sample_rate,
								size_t number_of_channels,
								size_t number_of_frames,
								void* audio_data,
								int64_t* elapsed_time_ms,
								int64_t* ntp_time_ms )
{
	LogMsg( LOG_INFO, "MySndMgr::PullRenderData number_of_frames %d\n", number_of_frames );
}

#endif // USE_ECHO_CANCEL

#endif // USE_VX_WAVE
