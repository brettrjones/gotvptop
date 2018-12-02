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

#include "AudioOutIo.h"
#include "AudioOutQt.h"


#include <CoreLib/VxDebug.h>

#include <QDebug>
#include <QtEndian>
#include <math.h>


//============================================================================
AudioOutIo::AudioOutIo( AudioOutQt& outQt, QObject *parent ) 
: QIODevice( parent )
, m_AudioOutQt( outQt )
, m_initialized( false )
, m_output( 0 )
, m_volume( 0.0f )
{
}

//============================================================================
bool AudioOutIo::initAudioOut( QAudioFormat& audioFormat )
{
    m_AudioFormat = audioFormat;
    if( m_initialized ) 
    {
        return false;
    }

    //if( bits != 16 ) 
    //{
    //    return false;
    //}

    //m_format.setSampleSize( bits );
    //m_format.setChannelCount( channels );
    //m_format.setSampleRate( samplerate );
    //m_format.setCodec( "audio/pcm" );
    //m_format.setByteOrder( QAudioFormat::LittleEndian );
    //m_format.setSampleType( bits == 16 ? QAudioFormat::SignedInt : QAudioFormat::SignedInt );

    m_initialized = setDevice( QAudioDeviceInfo::defaultOutputDevice() );
    return m_initialized;
}

//============================================================================
bool AudioOutIo::setDevice( QAudioDeviceInfo deviceInfo )
{
    if( !deviceInfo.isFormatSupported( m_AudioFormat ) ) {
        qDebug() << "Format not supported!";
        return false;
    }

    m_deviceInfo = deviceInfo;
    this->reinit();
    return true;
}

//============================================================================
void AudioOutIo::reinit()
{
    bool running = false;
    if( m_output && m_output->state() != QAudio::StoppedState ) 
    {
        running = true;
    }

    this->stop();

    // Reinitialize audio output
    delete m_output;
    m_output = new QAudioOutput( m_deviceInfo, m_AudioFormat, this );
    //m_output->setBufferSize( AudioOutQt::AUDIO_BUF_SIZE_48000_2 );

    // Set constant values to new audio output
    connect( m_output, SIGNAL( notify() ), SLOT( notified() ) );
    connect( m_output, SIGNAL( stateChanged( QAudio::State ) ), SLOT( stateChanged( QAudio::State ) ) );

    if( running ) 
    {
        this->start();
    }
}

//============================================================================
void AudioOutIo::start()
{
    if( m_output == 0 || m_output->state() != QAudio::StoppedState ) 
    {
        return;
    }

    this->open( QIODevice::ReadOnly );
    m_output->start( this );
    //m_output->suspend();
}

//============================================================================
void AudioOutIo::setVolume( float volume )
{
    m_volume = volume;
}

//============================================================================
void AudioOutIo::flush()
{
    // Flushing buffers is a bit tricky...
    // Don't modify this unless you're sure
    this->stop();
    m_output->reset();
    this->start();
}

//============================================================================
void AudioOutIo::stop()
{
    if( m_output && m_output->state() != QAudio::StoppedState ) 
    {
        // Stop audio output
        m_output->stop();
        this->close();
    }
}

//============================================================================
static void apply_s16le_volume( float volume, uchar *data, int datalen )
{
    int samples = datalen / 2;
    float mult = pow( 10.0, 0.05*volume );

    for( int i = 0; i < samples; i++ ) {
        qint16 val = qFromLittleEndian<qint16>( data + i * 2 )*mult;
        qToLittleEndian<qint16>( val, data + i * 2 );
    }
}

//============================================================================
qint64 AudioOutIo::readData( char *data, qint64 maxlen )
{
    // Calculate output length, always full samples
    return m_AudioOutQt.speakerOutReadData( data, maxlen );
    // If audio is suspended and buffer is full, resume

    //apply_s16le_volume( m_volume, ( uchar * )data, outlen );
    //m_buffer.remove( 0, outlen );
}

//============================================================================
qint64 AudioOutIo::writeData( const char *data, qint64 len )
{
    Q_UNUSED( data );
    Q_UNUSED( len );

    return 0;
}

//============================================================================
qint64 AudioOutIo::bytesAvailable() const
{
    return QIODevice::bytesAvailable();
}

//============================================================================
void AudioOutIo::notified()
{
}

//============================================================================
void AudioOutIo::stateChanged( QAudio::State state )
{
    // Start buffering again in case of underrun...
    // Required on Windows, otherwise it stalls idle
    if( state == QAudio::IdleState && m_output->error() == QAudio::UnderrunError ) 
    {
        // This check is required, because Mac OS X underruns often
        m_output->suspend();

        return;
    }

    qWarning() << "state = " << state;
}