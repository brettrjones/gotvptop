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
// http://www.nolimitconnect.com
//============================================================================

#include "config_gotvapps.h"

#include <QObject>
#include <QIODevice>
#include <QByteArray>
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QIODevice>

#include <CoreLib/VxMutex.h>

class AudioOutQt;

class AudioOutIo : public QIODevice
{
    Q_OBJECT
public:
    explicit AudioOutIo( AudioOutQt& outQt, QObject *parent = 0 );

    bool                        initAudioOut( QAudioFormat& audioFormat );

    void                        stopAudio();
    void                        startAudio();

    void                        suspend()           { if( m_AudioOutputDevice ) m_AudioOutputDevice->suspend(); }
    void                        resume()            { if( m_AudioOutputDevice ) m_AudioOutputDevice->resume(); }
 
    bool                        setAudioDevice( QAudioDeviceInfo deviceInfo );

    void                        setVolume( float volume );
    void                        flush();

    QAudio::State               getState()      { return ( m_AudioOutputDevice ? m_AudioOutputDevice->state() : QAudio::StoppedState); }
    QAudio::Error               getError()      { return ( m_AudioOutputDevice ? m_AudioOutputDevice->error() : QAudio::NoError); }

    QAudioOutput *              getAudioOut( )  { return m_AudioOutputDevice; }

	/// space available to que audio data into buffer
	int							audioQueFreeSpace();

	/// space used in audio que buffer
	int							audioQueUsedSpace();

	///  write to audio buffer.. return total written to  buffer
	int 						enqueueAudioData( char* pcmData, int countBytes );

signals:
    void                        signalInitialize();
    void						signalCheckForBufferUnderun();
    void						signalStart();
	void						signalStop();
	void						signalSuspend();
	void						signalResume();

protected slots:
    void                        slotAudioNotified();
    void						slotCheckForBufferUnderun();
    void                        onAudioDeviceStateChanged( QAudio::State state );
    void                        slotInitialize();
    void						slotStart();
	void						slotStop();
	void						slotSuspend();
	void						slotResume();

protected:
	qint64                      bytesAvailable() const override;

	qint64                      readData( char *data, qint64 maxlen ) override;
	qint64                      writeData( const char *data, qint64 len )  override;;
    bool						isSequential() const  override { return true; }

private:
    void                        reinit();

private:
    AudioOutQt&                 m_AudioOutQt;
    bool                        m_initialized = 0;
    QAudioFormat                m_AudioFormat;
    QAudioDeviceInfo            m_deviceInfo;
    QAudioOutput*               m_AudioOutputDevice = nullptr;
    float                       m_volume = 1.0f;

	mutable VxMutex				m_AudioBufMutex;
	QByteArray					m_AudioBuffer;
};
