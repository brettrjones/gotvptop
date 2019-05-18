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
{
    connect( this, SIGNAL( signalInitialize() ), this, SLOT( slotInitialize() ) );
    connect( this, SIGNAL( signalCheckForBufferUnderun() ), this, SLOT( slotCheckForBufferUnderun() ) );
    connect( this, SIGNAL( signalStart() ), this, SLOT( slotStart() ) );
    connect( this, SIGNAL( signalStop() ), this, SLOT( slotStop() ) );
    connect( this, SIGNAL( signalSuspend() ), this, SLOT( slotSuspend() ) );
    connect( this, SIGNAL( signalResume() ), this, SLOT( slotResume() ) );
}

//============================================================================
bool AudioOutIo::initAudioOut( QAudioFormat& audioFormat )
{
    m_AudioFormat = audioFormat;
    emit signalInitialize();
    return true;
}

//============================================================================
void AudioOutIo::slotInitialize()
{
    if( m_initialized ) 
    {
        return;
    }

    m_initialized = setAudioDevice( QAudioDeviceInfo::defaultOutputDevice() );
}

//============================================================================
bool AudioOutIo::setAudioDevice( QAudioDeviceInfo deviceInfo )
{
    if( !deviceInfo.isFormatSupported( m_AudioFormat ) ) 
	{
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
    this->stopAudio();
    this->startAudio();
}

//============================================================================
void AudioOutIo::startAudio()
{
	// Reinitialize audio output
	delete m_AudioOutputDevice;
	m_AudioOutputDevice = new QAudioOutput( m_deviceInfo, m_AudioFormat, this );

	// Set constant values to new audio output
	connect( m_AudioOutputDevice, SIGNAL( notify() ), SLOT( slotAudioNotified() ) );
	connect( m_AudioOutputDevice, SIGNAL( stateChanged( QAudio::State ) ), SLOT( onAudioDeviceStateChanged( QAudio::State ) ) );


    this->open( QIODevice::ReadOnly );
	//m_AudioOutputDevice->setBufferSize( AUDIO_BUF_SIZE_48000_2 );
	//m_AudioOutputDevice->setNotifyInterval( AUDIO_BUF_MS );
	m_AudioOutputDevice->start( this );
	//LogMsg( LOG_DEBUG, "AudioOutIo default buffer size %d periodic size %d", m_AudioOutputDevice->bufferSize(), m_AudioOutputDevice->periodSize() );
}


//============================================================================
void AudioOutIo::slotStart()
{
	startAudio();
}

//============================================================================
void AudioOutIo::slotStop()
{
	stopAudio();
}

//============================================================================
void AudioOutIo::slotSuspend()
{
    stopAudio();
}

//============================================================================
void AudioOutIo::slotResume()
{
	startAudio();
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
    this->stopAudio();
	if( m_AudioOutputDevice )
	{
		m_AudioOutputDevice->reset();
	}

    this->startAudio();
}

//============================================================================
void AudioOutIo::stopAudio()
{
    if( m_AudioOutputDevice && m_AudioOutputDevice->state() != QAudio::StoppedState )
    {
        // Stop audio output
		m_AudioOutputDevice->stop();
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
    //return m_AudioOutQt.speakerOutReadData( data, maxlen );
    // If audio is suspended and buffer is full, resume

    //apply_s16le_volume( m_volume, ( uchar * )data, outlen );

    //m_buffer.remove( 0, outlen );

	//memset( data, 0, maxlen );
	m_AudioBufMutex.lock();

	int toWriteByteCnt = std::min( (int)maxlen, m_AudioBuffer.size() );
	if( toWriteByteCnt )
	{
		memcpy( data, m_AudioBuffer.data(), toWriteByteCnt );
		m_AudioBuffer.remove( 0, toWriteByteCnt ); //pop front what is written
	}

	//if( toWriteByteCnt )
	//{
	//	LogMsg( LOG_DEBUG, "enqueueAudioData total bytes avail %lld", bytesAvailable() );
	//}

	m_AudioBufMutex.unlock();
	//if( ( 0 == towritedevice ) && m_AudioOutputDevice )
	//{
	//	// suspend until we have data available
	//	m_AudioOutputDevice->suspend();
	//}
	//else
	//{
		//emit signalCheckForBufferUnderun();
	//}

	return toWriteByteCnt;
}

//============================================================================
// not used
qint64 AudioOutIo::writeData( const char *data, qint64 len )
{
    Q_UNUSED( data );
    Q_UNUSED( len );

    return 0;
}

//============================================================================
/// space available to que audio data into buffer
int AudioOutIo::audioQueFreeSpace()
{
	int freeSpace = AUDIO_OUT_CACHE_SIZE - m_AudioBuffer.size();
	if( freeSpace < 0 )
	{
		freeSpace = 0;
	}

	return freeSpace;
}

//============================================================================
/// space used in audio que buffer
int AudioOutIo::audioQueUsedSpace()
{
	emit signalCheckForBufferUnderun();

	return m_AudioBuffer.size();
}

//============================================================================
// write to audio buffer.. return total written to buffer
int AudioOutIo::enqueueAudioData( char* pcmData, int countBytes )
{
	m_AudioBufMutex.lock();
	int toWriteByteCnt = std::min( audioQueFreeSpace(), countBytes );
	if( countBytes != toWriteByteCnt )
	{
		// if not enough space then do not write anything or kodi gets confused
		toWriteByteCnt = 0;
	}

	if( toWriteByteCnt )
	{
		m_AudioBuffer.append( pcmData, toWriteByteCnt );
	}

	m_AudioBufMutex.unlock();

	emit signalCheckForBufferUnderun();

	return toWriteByteCnt;
}

//============================================================================
qint64 AudioOutIo::bytesAvailable() const
{
	//m_AudioBufMutex.lock();
	qint64 audioBytesAvailableToRead = m_AudioBuffer.size() + QIODevice::bytesAvailable();
	//m_AudioBufMutex.unlock();

    return audioBytesAvailableToRead;
}

//============================================================================
void AudioOutIo::slotAudioNotified()
{
}

//============================================================================
void AudioOutIo::onAudioDeviceStateChanged( QAudio::State state )
{
	if( m_AudioOutputDevice )
	{
		// Start buffering again in case of underrun...
		// Required on Windows, otherwise it stalls idle
		if( state == QAudio::IdleState && m_AudioOutputDevice->error() == QAudio::UnderrunError )
		{
			// This check is required, because Mac OS X underruns often
			m_AudioOutputDevice->suspend();
#ifdef DEBUG_QT_AUDIO
			qWarning() << "audio suspending due to underrun ";
#endif // DEBUG_QT_AUDIO
			return;
		}      
#ifdef DEBUG_QT_AUDIO
		qWarning() << "audio stateChanged state = " << state;
#endif // DEBUG_QT_AUDIO
	}
}

//============================================================================
// resume qt audio if needed
void AudioOutIo::slotCheckForBufferUnderun()
{
	m_AudioBufMutex.lock();
	int bufferedAudioData = m_AudioBuffer.size();
	m_AudioBufMutex.unlock();

	if( bufferedAudioData && m_AudioOutputDevice )
	{
		QAudio::State audioState = m_AudioOutputDevice->state();
		//qWarning() << "checkForBufferUnderun audioState = " << audioState;
		QAudio::Error audioError = m_AudioOutputDevice->error();
		//qWarning() << "checkForBufferUnderun audioError = " << audioError;
//		qWarning() << "checkForBufferUnderun bufferSize = " << m_AudioOutputDevice->bufferSize();
		//qWarning() << "checkForBufferUnderun bytesAvail = " << bufferedAudioData;

		switch( audioState )
		{
		case QAudio::ActiveState:
			break;
		case QAudio::IdleState:
			if( audioError == QAudio::UnderrunError )
			{
				LogMsg( LOG_DEBUG, "suspending due to underrun" );
				m_AudioOutputDevice->suspend();
			}
			else if( bufferedAudioData )
			{
				LogMsg( LOG_DEBUG, "starting due to idle and have data" );
				this->startAudio();
				//m_AudioOutputDevice->start( this );
			}
			else
			{
				// already stopped
				//m_AudioOutputDevice->stop();
			}
			break;

		case QAudio::SuspendedState:
			if( bufferedAudioData )
			{ 
                LogMsg( LOG_DEBUG, "restarting due to suspended and have data" );
				m_AudioOutputDevice->start( this );
			}
			break;

		case QAudio::StoppedState: 
			if( bufferedAudioData )
			{
                LogMsg( LOG_DEBUG, "restarting due to stopped and have data" );
                m_AudioOutputDevice->start( this );
			}
			break;
#ifdef TARGET_OS_WINDOWS // seems to be a windows only thing
		case QAudio::InterruptedState:
            LogMsg( LOG_DEBUG, "Interrupted state.. how to handle?" );
			break;
#endif // // TARGET_OS_WINDOWS
		};
	}
}
