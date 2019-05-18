
#pragma once
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
// bjones.engineer@gmail.com
// http://www.gotvptop.net
//============================================================================

#include "SoundDefs.h"
#include "ToGuiHardwareControlInterface.h"

#include <PktLib/VxCommon.h>

#include <QVector>
#include <QObject>

#ifdef TARGET_OS_WINDOWS
    #include <QAudioDeviceInfo>
//  #define USE_VX_WAVE	1
#endif // TARGET_OS_WINDOWS
#ifdef USE_VX_WAVE
	#ifdef USE_ECHO_CANCEL
	#define USE_AUDIO_CORE	1	// comment this define out to use AudioDeviceWaveWin instead of AudioDeviceCoreWin
		#include "AudioDeviceWaveWin.h"
		#include "AudioDeviceCoreWin.h"
		#include <GoTvCore/GoTvP2P/EchoCancel/audio_device_defines.h>
	#else
		#include "VxWaveIn.h"
		#include "VxWaveOut.h"
	#endif // USE_ECHO_CANCEL
#endif // USE_VX_WAVE

const uint32_t					MY_FRAME_DATA_LEN			= 1280;
const uint32_t					MY_FRAME_SAMPLES			= 640;

class AppCommon;
class P2PEngine;
class QIODevice;
class QSound;
class MyQtSoundInput;
class MyQtSoundOutput;
class VxSndInstance;

class MySndMgr : public QObject, public ToGuiHardwareControlInterface
#ifdef USE_VX_WAVE
#ifdef USE_ECHO_CANCEL
	, public webrtc::AudioTransport
#else
	, public VxWaveInCallback
	, public VxWaveOutCallback
#endif // USE_ECHO_CANCEL
#endif // USE_VX_WAVE
{
	Q_OBJECT
public:
	MySndMgr( AppCommon& app );
	virtual ~MySndMgr();

	AppCommon&				    getApp( void )						{ return m_MyApp; }

	bool						sndMgrStartup( void );
	bool						sndMgrShutdown( void );

	virtual void 				doGuiWantMicrophoneRecording( bool wantMicInput ); 
	virtual void 				doGuiWantSpeakerOutput( bool wantSpeakerOutput ); 

	VxSndInstance *			    playSnd( ESndDef sndDef, bool loopContinuous = false );
	void						stopSnd( ESndDef sndDef );

	void						startMicrophoneRecording();
	void						stopMicrophoneRecording();

	void						recievedAudioData( char * pu16PcmData, int u16PcmDataLen );
	void						sendingAudioData( QByteArray& audioData );

signals:
	void						signalMicrophoneAudioData( QByteArray audioData );

public slots:
	void						mutePhoneRing( bool bMute );
	void						muteNotifySound( bool bMute );
	void						slotStartPhoneRinging( void );
	void						slotStopPhoneRinging( void );
	void						slotPlayNotifySound( void );
	void						slotPlayShredderSound( void );

private slots:
	void						slotSndFinished( VxSndInstance * sndInstance );

protected:
	void						enableMicrophoneInput( bool enable );
	void						enableSpeakerOutput( bool bEnable );

	//=== vars ===//
	AppCommon&				    m_MyApp;
	P2PEngine&					m_Engine;
	MyQtSoundInput *			m_MicrophoneInput;
	bool						m_bMicrophoneEnabled;

	MyQtSoundOutput *			m_VoiceOutput;
	bool						m_bVoiceOutputEnabled;
	bool						m_bAudioOutputStarted;

	bool						m_bMutePhoneRing;
	bool						m_bMuteNotifySnd;

	QVector<VxSndInstance *>	m_SndList;
	VxSndInstance *			    m_CurSndPlaying;

#ifdef USE_VX_WAVE
	virtual void				waveInPcmDataAvail( char * sndData, int dataLen, void * userData );
	virtual void				waveOutSpaceAvail( int freeSpaceLen, void * userData );

#ifdef USE_ECHO_CANCEL
	virtual int32_t				RecordedDataIsAvailable(	const void* audioSamples,
															const size_t nSamples,
															const size_t nBytesPerSample,
															const size_t nChannels,
															const uint32_t samplesPerSec,
															const uint32_t totalDelayMS,
															const int32_t clockDrift,
															const uint32_t currentMicLevel,
															const bool keyPressed,
															uint32_t& newMicLevel );

	virtual int32_t				NeedMorePlayData(	const size_t nSamples,
													const size_t nBytesPerSample,
													const size_t nChannels,
													const uint32_t samplesPerSec,
													void* audioSamples,
													size_t& nSamplesOut,
													int64_t* elapsed_time_ms,
													int64_t* ntp_time_ms );

	// Method to pass captured data directly and unmixed to network channels.
	// |channel_ids| contains a list of VoE channels which are the
	// sinks to the capture data. |audio_delay_milliseconds| is the sum of
	// recording delay and playout delay of the hardware. |current_volume| is
	// in the range of [0, 255], representing the current microphone analog
	// volume. |key_pressed| is used by the typing detection.
	// |need_audio_processing| specify if the data needs to be processed by APM.
	// Currently WebRtc supports only one APM, and Chrome will make sure only
	// one stream goes through APM. When |need_audio_processing| is false, the
	// values of |audio_delay_milliseconds|, |current_volume| and |key_pressed|
	// will be ignored.
	// The return value is the new microphone volume, in the range of |0, 255].
	// When the volume does not need to be updated, it returns 0.
	// TODO(xians): Remove this interface after Chrome and Libjingle switches
	// to OnData().
	virtual int					OnDataAvailable(	const int voe_channels[],
													size_t number_of_voe_channels,
													const int16_t* audio_data,
													int sample_rate,
													size_t number_of_channels,
													size_t number_of_frames,
													int audio_delay_milliseconds,
													int current_volume,
													bool key_pressed,
													bool need_audio_processing ); 

	// Method to pass the captured audio data to the specific VoE channel.
	// |voe_channel| is the id of the VoE channel which is the sink to the
	// capture data.
	// TODO(xians): Remove this interface after Libjingle switches to
	// PushCaptureData().
	virtual void				OnData( int voe_channel,
										const void* audio_data,
										int bits_per_sample,
										int sample_rate,
										size_t number_of_channels,
										size_t number_of_frames);

	// Method to push the captured audio data to the specific VoE channel.
	// The data will not undergo audio processing.
	// |voe_channel| is the id of the VoE channel which is the sink to the
	// capture data.
	// TODO(xians): Make the interface pure virtual after Libjingle
	// has its implementation.
	virtual void				PushCaptureData(	int voe_channel,
													const void* audio_data,
													int bits_per_sample,
													int sample_rate,
													size_t number_of_channels,
													size_t number_of_frames );

	// Method to pull mixed render audio data from all active VoE channels.
	// The data will not be passed as reference for audio processing internally.
	// TODO(xians): Support getting the unmixed render data from specific VoE
	// channel.
	virtual void				PullRenderData(	int bits_per_sample,
												int sample_rate,
												size_t number_of_channels,
												size_t number_of_frames,
												void* audio_data,
												int64_t* elapsed_time_ms,
												int64_t* ntp_time_ms );

#ifdef USE_AUDIO_CORE
	webrtc::AudioDeviceWindowsCore	m_WaveWin;
#else
	webrtc::AudioDeviceWindowsWave	m_WaveWin;
#endif // USE_AUDIO_CORE

	webrtc::AudioDeviceBuffer	m_AudioDeviceBuffer;
	uint8_t					    m_MyFrameBuf[MY_FRAME_DATA_LEN];
	int							m_MyFrameReadIdx;
	int							m_MyFrameDataAvail;
	int16_t						m_MyLastReadSample;
#else
	VxWaveIn					m_WaveIn;
	VxWaveOut					m_WaveOut;
#endif // USE_ECHO_CANCEL

#endif // USE_VX_WAVE
};

MySndMgr& GetSndMgrInstance( void );
