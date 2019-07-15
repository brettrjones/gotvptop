#pragma once
//============================================================================
// Copyright (C) 2018 Brett R. Jones
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
// http://www.gotvptop.com
//============================================================================

//#include "config_gotvapps.h"

#include <QObject>
#include <QIODevice>
#include <QByteArray>
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QIODevice>
#include <QMutex>
#include <QElapsedTimer>

//#include <CoreLib/VxMutex.h>
#include "VxTimer.h"

class AudioIoMgr;
class QTimer;

class AudioOutIo : public QIODevice
{
    Q_OBJECT
public:
    explicit AudioOutIo( AudioIoMgr& mgr, QMutex& audioOutMutex, QObject *parent = 0 );
     ~AudioOutIo() override = default;

    bool                        initAudioOut( QAudioFormat& audioFormat );

    void                        stopAudio();
    void                        startAudio();

    void                        suspend()           { if( m_AudioOutputDevice ) m_AudioOutputDevice->suspend(); }
    void                        resume()            { if( m_AudioOutputDevice ) m_AudioOutputDevice->resume(); }
 
    bool                        setAudioDevice( QAudioDeviceInfo deviceInfo );

    void                        setVolume( float volume );
    void                        flush();

    QAudio::State               getState()      { return ( m_AudioOutputDevice ? m_AudioOutState : QAudio::StoppedState); }
    QAudio::Error               getError()      { return ( m_AudioOutputDevice ? m_AudioOutputDevice->error() : QAudio::NoError); }

    QAudioOutput *              getAudioOut( )  { return m_AudioOutputDevice; }

signals:
    void						signalCheckForBufferUnderun();
    void						signalStart();
	void						signalStop();
	void						signalSuspend();
	void						signalResume();

protected slots:
    void                        slotAudioNotify();
    void						slotCheckForBufferUnderun();
    void                        onAudioDeviceStateChanged( QAudio::State state );
    void						slotStart();
	void						slotStop();
	void						slotSuspend();
	void						slotResume();

protected:

	qint64                      readData( char *data, qint64 maxlen ) override;
    qint64                      writeData( const char *data, qint64 len )  override;
    qint64                      bytesAvailable() const override;
    bool						isSequential() const  override { return true; }

private:
    void                        reinit();

private:
    AudioIoMgr&                 m_AudioIoMgr;
    QMutex&                     m_AudioBufMutex;

    bool                        m_initialized = 0;
    QAudioFormat                m_AudioFormat;
    QAudioDeviceInfo            m_deviceInfo;
    QAudioOutput*               m_AudioOutputDevice = nullptr;
    qint64                      m_ProccessedMs = 0;
    float                       m_volume = 1.0f;
    QTimer *                    m_PeriodicTimer;
    VxTimer                     m_NotifyTimer;
    QElapsedTimer               m_ElapsedTimer;
    QAudio::State               m_AudioOutState = QAudio::State::StoppedState;
};
