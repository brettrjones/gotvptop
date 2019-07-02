
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
};

MySndMgr& GetSndMgrInstance( void );
