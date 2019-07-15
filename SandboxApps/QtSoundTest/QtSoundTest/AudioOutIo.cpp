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

#include "AudioOutIo.h"
#include "AudioIoMgr.h"

#include "VxDebug.h"

#include <QDebug>
#include <QtEndian>
#include <QTimer>
#include <math.h>


//============================================================================
AudioOutIo::AudioOutIo( AudioIoMgr& mgr, QMutex& audioOutMutex, QObject *parent )
: QIODevice( parent )
, m_AudioIoMgr( mgr )
, m_AudioBufMutex( audioOutMutex )
, m_PeriodicTimer( new QTimer( this ) )
, m_AudioOutState( QAudio::StoppedState )
{
    m_PeriodicTimer->setInterval( 20 );
     connect( this, SIGNAL( signalCheckForBufferUnderun() ), this, SLOT( slotCheckForBufferUnderun() ) );
    connect( this, SIGNAL( signalStart() ), this, SLOT( slotStart() ) );
    connect( this, SIGNAL( signalStop() ), this, SLOT( slotStop() ) );
    connect( this, SIGNAL( signalSuspend() ), this, SLOT( slotSuspend() ) );
    connect( this, SIGNAL( signalResume() ), this, SLOT( slotResume() ) );
    connect( m_PeriodicTimer, SIGNAL( timeout() ), this, SLOT( slotAudioNotify() ) );
    connect( &m_AudioIoMgr.getAudioOutMixer(), SIGNAL( signalCheckSpeakerOutState() ), this, SLOT( slotCheckForBufferUnderun() ) );
}

//============================================================================
bool AudioOutIo::initAudioOut( QAudioFormat& audioFormat )
{
    if( !m_initialized )
    {
        m_AudioFormat = audioFormat;
        m_initialized = setAudioDevice( QAudioDeviceInfo::defaultOutputDevice() );
    }

    return m_initialized;
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
    delete m_AudioOutputDevice;
    m_AudioOutputDevice = new QAudioOutput( m_deviceInfo, m_AudioFormat, this );

    connect( m_AudioOutputDevice, SIGNAL( stateChanged( QAudio::State ) ), SLOT( onAudioDeviceStateChanged( QAudio::State ) ) );

//    this->reinit();
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
    m_ProccessedMs = 0;

    this->open( QIODevice::ReadOnly );
    m_NotifyTimer.resetTimer();
    m_AudioOutputDevice->setBufferSize( AUDIO_OUT_CACHE_USABLE_SIZE ); // must be called before start
    m_AudioOutputDevice->start( this );
    m_PeriodicTimer->start();
    m_ElapsedTimer.start();
    //m_AudioOutputDevice->setBufferSize( AUDIO_BUF_SIZE_48000_2_S16 );
    LogMsg( LOG_DEBUG, "AudioOutIo default buffer size %d periodic size %d", m_AudioOutputDevice->bufferSize(), m_AudioOutputDevice->periodSize() );
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
    //m_PeriodicTimer->stop();
    if( m_AudioOutputDevice && m_AudioOutputDevice->state() != QAudio::StoppedState )
    {
        // Stop audio output
		m_AudioOutputDevice->stop();
        //this->close();
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
    if( maxlen <= 0 )
    {
        emit signalCheckForBufferUnderun();
        return maxlen;
    }

    qint64 readAmount = m_AudioIoMgr.readDataFromOutMixer( data, maxlen );
    if( readAmount != maxlen )
    {
        // suspend until we have data available
        //m_AudioOutputDevice->suspend();
    }

    return readAmount;
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
// not used
qint64 AudioOutIo::bytesAvailable() const
{
    qint64 avail = m_AudioIoMgr.getAudioOutMixer().getDataReadyForSpeakersLen();
    avail += QIODevice::bytesAvailable();
    LogMsg( LOG_DEBUG, "bytesAvailable %lld device avail %lld", avail, QIODevice::bytesAvailable() );
    return avail;
}

//============================================================================
void AudioOutIo::slotAudioNotify()
{
    qint64 processedMs = m_AudioOutputDevice->elapsedUSecs() / 1000;
    static int callCnt = 0;
    static uint64_t seconds = 0;
    static uint64_t lastSecond = 0;
    if( ( processedMs - m_ProccessedMs ) >= AUDIO_MS_SPEAKERS )
    {
        // round down to nearest 80 ms
        m_ProccessedMs = processedMs - ( processedMs % AUDIO_MS_SPEAKERS );
//        LogMsg( LOG_DEBUG, "AudioOutIo Notify %3.3f ms processed %lld interval %d buf size %d elapsed %d", m_NotifyTimer.elapsedMs(), processedMs, m_AudioOutputDevice->notifyInterval(), 
//            m_AudioOutputDevice->bufferSize(), m_ElapsedTimer.elapsed() );
        m_NotifyTimer.resetTimer();
       // m_ElapsedTimer.restart();
        m_AudioIoMgr.getAudioOutMixer().getAudioCallbacks().fromGuiAudioOutSpaceAvail( AUDIO_BUF_SIZE_8000_1_S16 );
//        if( m_AudioOutState != QAudio::ActiveState )
//        {
//            emit signalCheckForBufferUnderun();
//        }

        callCnt++;
        uint64_t secondsNow = time( NULL );
        if( secondsNow != lastSecond )
        {
            lastSecond = secondsNow;
            if( !seconds )
            {
                m_ElapsedTimer.restart();
                seconds = secondsNow;
            }

            uint64_t elapsedSec = secondsNow - seconds;
            if( elapsedSec )
            {
                LogMsg( LOG_DEBUG, "* %d calls per second %d-%d-%d", callCnt / elapsedSec, elapsedSec, m_ElapsedTimer.elapsed() / 1000, processedMs / 1000 );
            }
        }
    }
}

//============================================================================
void AudioOutIo::onAudioDeviceStateChanged( QAudio::State state )
{
    if( m_AudioOutState != state )
    {
        LogMsg( LOG_DEBUG, "Audio Out state change from %s to %s ", m_AudioIoMgr.describeAudioState( m_AudioOutState ), m_AudioIoMgr.describeAudioState( state ) );
        m_AudioOutState = state;
    }

	if( m_AudioOutputDevice )
	{
		// Start buffering again in case of underrun...
		// Required on Windows, otherwise it stalls idle
		if( state == QAudio::IdleState && m_AudioOutputDevice->error() == QAudio::UnderrunError )
		{
			// This check is required, because Mac OS X underruns often
			m_AudioOutputDevice->suspend();
//#ifdef DEBUG_QT_AUDIO
            LogMsg( LOG_DEBUG, "speaker out suspending due to underrun " );
//#endif // DEBUG_QT_AUDIO
			return;
		}      
	}
}

//============================================================================
// resume qt audio if needed
void AudioOutIo::slotCheckForBufferUnderun()
{
	//m_AudioBufMutex.lock();
	//int bufferedAudioData = m_AudioBuffer.size();
	//m_AudioBufMutex.unlock();

    int bufferedAudioData = m_AudioIoMgr.getDataReadyForSpeakersLen();
    
	if( m_AudioOutputDevice )
	{
		m_AudioOutState = m_AudioOutputDevice->state();
		//qWarning() << "checkForBufferUnderun audioState = " << audioState;
		QAudio::Error audioError = m_AudioOutputDevice->error();
        if( audioError != QAudio::NoError )
        {
            LogMsg( LOG_DEBUG, "speaker Error %s", m_AudioIoMgr.describeAudioError( audioError ) );
        }
		//qWarning() << "checkForBufferUnderun audioError = " << audioError;
//		qWarning() << "checkForBufferUnderun bufferSize = " << m_AudioOutputDevice->bufferSize();
		//qWarning() << "checkForBufferUnderun bytesAvail = " << bufferedAudioData;

		switch( m_AudioOutState )
		{
		case QAudio::ActiveState:
			break;
		case QAudio::IdleState:
            if( !bufferedAudioData && audioError == QAudio::UnderrunError )
			{
                LogMsg( LOG_DEBUG, "speaker idle due to underrun" );
                //m_AudioOutputDevice->suspend();
			}
			else if( bufferedAudioData )
			{
                LogMsg( LOG_DEBUG, "speaker resuming due to idle and have data" );
#ifdef Q_OS_WIN
                // The Windows backend seems to internally go back into ActiveState
                // while still returning SuspendedState, so to ensure that it doesn't
                // ignore the resume() call, we first re-suspend
                m_AudioOutputDevice->suspend();
#endif
                m_AudioOutputDevice->resume();
            }
			else
			{
				// already stopped and have no data
			}
			break;

		case QAudio::SuspendedState:
			if( bufferedAudioData  )
			{ 
                LogMsg( LOG_DEBUG, "speaker out resuming due to suspended and have data" );
//#ifdef Q_OS_WIN
                // The Windows backend seems to internally go back into ActiveState
                // while still returning SuspendedState, so to ensure that it doesn't
                // ignore the resume() call, we first re-suspend
                m_AudioOutputDevice->suspend();
//#endif
                m_AudioOutputDevice->resume();
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
