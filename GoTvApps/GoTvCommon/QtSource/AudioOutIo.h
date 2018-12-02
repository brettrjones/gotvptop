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
// brett.jones@engineer.com
// http://www.gotvptop.net
//============================================================================

#include "config_gotvapps.h"

#include <QObject>
#include <QIODevice>
#include <QByteArray>
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QIODevice>

class AudioOutQt;

class AudioOutIo : public QIODevice
{
    Q_OBJECT
public:
    explicit AudioOutIo( AudioOutQt& outQt, QObject *parent = 0 );

    bool                        initAudioOut( QAudioFormat& audioFormat );
    void                        suspend()           { if( m_output ) m_output->suspend(); }
    void                        resume()            { if( m_output ) m_output->resume(); }
    void                        stopAudioOut( );

    bool                        setDevice( QAudioDeviceInfo deviceInfo );

    void                        start();
    void                        setVolume( float volume );
    void                        output( const QByteArray & data );
    void                        flush();
    void                        stop();

    qint64                      readData( char *data, qint64 maxlen );
    qint64                      writeData( const char *data, qint64 len );

    qint64                      bytesAvailable() const;

    QAudio::State               getState()      { return (m_output ? m_output->state() : QAudio::StoppedState); }
    QAudio::Error               getError()      { return (m_output ? m_output->error() : QAudio::NoError); }

    QAudioOutput *              getAudioOut( )  { return m_output; }

private:
    void                        reinit();

private:
    AudioOutQt&                 m_AudioOutQt;
    bool                        m_initialized;
    QAudioFormat                m_AudioFormat;
    QAudioDeviceInfo            m_deviceInfo;
    QAudioOutput*               m_output;
    float                       m_volume;

signals:

public slots :
    void                        notified();
    void                        stateChanged( QAudio::State state );
};
