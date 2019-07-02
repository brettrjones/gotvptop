#include "AudioIoMgr.h"

#include <QSurface>
#include <qmath.h>
#include <QTimer>

#include "VxDebug.h"


//============================================================================
AudioIoMgr::AudioIoMgr( IAudioCallbacks& audioCallbacks, QWidget * parent )
: QWidget( parent )
, m_AudioCallbacks( audioCallbacks )
, m_AudioOutIo( *this, m_AudioOutMutex, this )
, m_AudioInIo( *this, m_AudioInMutex, this )
, m_AudioOutDeviceInfo( QAudioDeviceInfo::defaultOutputDevice() )
{
    m_AudioOutFormat.setSampleRate( 48000 );
    m_AudioOutFormat.setChannelCount( 2 );
    m_AudioOutFormat.setSampleSize( 16 );
    m_AudioOutFormat.setCodec( QStringLiteral("audio/pcm") );
    m_AudioOutFormat.setByteOrder( QAudioFormat::LittleEndian );
    m_AudioOutFormat.setSampleType( QAudioFormat::SignedInt );

    QAudioDeviceInfo info( m_AudioOutDeviceInfo );
    if( !info.isFormatSupported( m_AudioOutFormat ) )
    {
        LogMsg( LOG_DEBUG, "Default audio out format not supported - trying to use nearest" );
        m_AudioOutFormat = info.nearestFormat( m_AudioOutFormat );
    }

    m_AudioOutIo.initAudioOut( m_AudioOutFormat  );

    m_AudioInFormat.setSampleRate( 8000 );
    m_AudioInFormat.setChannelCount( 1 );
    m_AudioInFormat.setSampleSize( 16 );
    m_AudioInFormat.setCodec( QStringLiteral("audio/pcm") );
    m_AudioInFormat.setByteOrder( QAudioFormat::LittleEndian );
    m_AudioInFormat.setSampleType( QAudioFormat::SignedInt );

    QAudioDeviceInfo info( m_AudioInDeviceInfo );
    if( !info.isFormatSupported( m_AudioInFormat ) )
    {
        LogMsg( LOG_DEBUG, "Default audio out format not supported - trying to use nearest" );
        m_AudioInFormat = info.nearestFormat( m_AudioInFormat );
    }

    m_AudioOInIo.initAudioIn( m_AudioInFormat  ) ;
}

//============================================================================
void AudioIoMgr::pauseAudioOut()
{
    if( !m_IsPaused )
    {
        if( m_AudioOutIo.getState() == QAudio::SuspendedState )
        {
            //m_AudioDevice->resume();
        }
        else if( m_AudioOutIo.getState() == QAudio::ActiveState )
        {
            m_IsPaused = true;
            m_AudioOutIo.suspend();
        }
        else if( m_AudioOutIo.getState() == QAudio::StoppedState )
        {
            // m_AudioDevice->resume();
        }
        else if( m_AudioOutIo.getState() == QAudio::IdleState )
        {
            // no-op
        }
    }
}

//============================================================================
void AudioIoMgr::resumeAudioOut()
{
    if( m_IsPaused )
    {
        if( m_AudioOutIo.getState() == QAudio::SuspendedState )
        {
            m_IsPaused = false;
            m_AudioOutIo.resume();
        }
        else if( m_AudioOutIo.getState() == QAudio::ActiveState )
        {
            //m_AudioDevice->suspend();
        }
        else if( m_AudioOutIo.getState() == QAudio::StoppedState )
        {
            m_IsPaused = false;
            m_AudioOutIo.resume();
        }
        else if( m_AudioOutIo.getState() == QAudio::IdleState )
        {
            // no-op
        }
    }
}

//============================================================================
void AudioIoMgr::initAudioIoSystem()
{
    m_AudioOutIo.initAudioOut( m_AudioOutFormat );
    m_AudioInIo.initAudioIn( m_AudioInFormat );

    connect( m_AudioOutIo.getAudioOut(), SIGNAL( stateChanged( QAudio::State ) ), this, SLOT( playerStateChanged( QAudio::State ) ) );
    //connect( m_AudioOutIo.getAudioOut(), SIGNAL( notify() ), SLOT( notifyNeedData() ) );
    connect( this, SIGNAL( signalNeedMoreAudioData( int ) ), SLOT( slotNeedMoreAudioData( int ) ) );
    m_AudioOutIo.startAudio();

    connect( m_AudioInIo.getAudioIn(), SIGNAL( stateChanged( QAudio::State ) ), this, SLOT( microhpneStateChanged( QAudio::State ) ) );
    //connect( m_AudioInIo.getAudioOut(), SIGNAL( notify() ), SLOT( notifyNeedData() ) );
    connect( this, SIGNAL( signalNeedMoreAudioData( int ) ), SLOT( slotNeedMoreAudioData( int ) ) );
    m_AudioInIo.startAudio();
}

//============================================================================
void AudioIoMgr::stopAudioOut()
{
    m_AudioOutIo.stopAudio();
}

//============================================================================
void AudioIoMgr::stopAudioIn()
{
    m_AudioInIo.stopAudio();
}

//============================================================================
// volume is from 0.0 to 1.0
void AudioIoMgr::setVolume( float volume )
{
    m_AudioOutIo.setVolume( volume );
}


//============================================================================
double AudioIoMgr::toGuiGetAudioDelaySeconds()
{
    m_AudioOutMutex.lock();
    int totalCachedData = getCachedDataLength( );
    double sndDelaySec = ((double)totalCachedData / (double)( 48000 * 2 * 2 ) );
    m_AudioOutMutex.unlock();
    //LogMsg( LOG_DEBUG, "soundBuffer delay seconds %3.3f", sndDelaySec );
    return sndDelaySec;
}

//============================================================================
double AudioIoMgr::toGuiGetAudioCacheTotalSeconds()
{
    int totalCachedData = getCachedMaxLength();
    double sndSeconds = ( (double)totalCachedData / (double)( 48000 * 2 * 2 )); //48000 * 2 bytes per sample * 2 channels
    //LogMsg( LOG_DEBUG, "Max soundBuffer seconds %3.3f", sndSeconds );
    return sndSeconds;
}

//============================================================================
int AudioIoMgr::getCachedDataLength( bool requireLock )
{
    //return m_AudioBuf.bytesAvailable();
    int bytesInCache = m_AudioOutIo.audioQueUsedSpace();
    //LogMsg( LOG_DEBUG, "Bytes in snd buffer %d", bytesInCache );

    return bytesInCache;
}

//============================================================================
int AudioIoMgr::toGuiGetAudioCacheFreeSpace( EAppModule appModule )
{
    int freeSpace =  getCachedMaxLength() - getCachedDataLength( );
    if( freeSpace < 0 ) // can happen because getCachedDataLength is all awaiting read including what is in the device
    {
        freeSpace = 0;
    }

    //LogMsg( LOG_DEBUG, "snd buffer free space %d", freeSpace );

    if( eAppModuleKodi == appModule )
    {
        // for kodi the sound goes through a float to 16 bit pcm conversion so report what kodi wants
        freeSpace *= sizeof( float ) / sizeof( uint16_t );
    }

    return freeSpace;
}

//============================================================================
uint16_t SwapEndian16( uint16_t src )
{
    return ( ( src & 0xFF00 ) >> 8 ) | ( ( src & 0x00FF ) << 8 );
}

static uint32_t SwapEndian32( uint32_t x ) {
    return( ( x << 24 ) | ( ( x << 8 ) & 0x00FF0000 ) | ( ( x >> 8 ) & 0x0000FF00 ) | ( x >> 24 ) );
}

//============================================================================
//! playback audio
int AudioIoMgr::toGuiPlayAudio( EAppModule appModule, int16_t * pu16PcmData, int pcmDataLenInBytes )
{
    // it seems Qt does not handle anything but pcm 16 bit signed samples correctly so convert to what Qt can handle
    int wroteByteCnt = 0;
    int desiredWriteByteCnt = 0;
    if( m_IsTestMode && ( eAppModuleTest == appModule ) )
    {
        return pcmDataLenInBytes;
    }

    //LogMsg( LOG_INFO, "slotPlayAudio %d len %d from %s\n", ePluginType, u16PcmDataLen, netIdent->getOnlineName());
    if( eAppModulePtoP == appModule )
    {
        // convert 8000hz mono to 48000hz 2 channel
        float upResampleMultiplier = 48000 / 8000;
        upResampleMultiplier *= 2; // 2 channels
        int iDestIdx = 0;

        int outBufSize = (int)(pcmDataLenInBytes * upResampleMultiplier);
        unsigned char * outAudioData = new unsigned char[ outBufSize ];

        int mySampleCnt = pcmDataLenInBytes >> 1;
        int16_t * srcSamples = pu16PcmData;
        int16_t * destSamples = ( int16_t * )outAudioData;
        int16_t firstSample = m_MyLastAudioOutSample;
        int16_t secondSample = firstSample;
        float sampleStep;
        for( int i = 0; i < mySampleCnt; i++ )
        {
            firstSample = secondSample;
            secondSample = srcSamples[ i ];
            if( secondSample >= firstSample )
            {
                // ramp up
                sampleStep = ( ( secondSample - firstSample ) / upResampleMultiplier );
            }
            else
            {
                // ramp down
                sampleStep = -( ( firstSample - secondSample ) / upResampleMultiplier );
            }

            if( 0 == sampleStep )
            {
                for( int j = 0; j < upResampleMultiplier; ++j )
                {
                    destSamples[ iDestIdx ] = firstSample;
                    iDestIdx++;
                }
            }
            else
            {
                float sampleOffs = sampleStep;
                int resampleCnt = ( int )upResampleMultiplier;
                for( int j = 0; j < resampleCnt; ++j )
                {
                    destSamples[ iDestIdx ] = ( int16_t )( firstSample + sampleOffs );
                    iDestIdx++;
                    sampleOffs += sampleStep;
                }
            }
        }

        // save the last sample to be used as first sample reference in next frame
        m_MyLastAudioOutSample = srcSamples[ mySampleCnt - 1 ];

        desiredWriteByteCnt = pcmDataLenInBytes * upResampleMultiplier;
        wroteByteCnt = m_AudioOutIo.enqueueAudioData( (char *)outAudioData, desiredWriteByteCnt );
        //wrote = m_AudioBuf.writeData( ( char * )outAudioData, pcmDataLenInBytes * upResampleMultiplier );
        delete outAudioData;
    }
    else
    {
        // convert float 48000 2 channel to pcm 16 bit 2 channel
        int sampleCnt = pcmDataLenInBytes / sizeof( float );
        int16_t * outAudioData = new int16_t[ sampleCnt ];
        float * inSampleData = ( float * )pu16PcmData;

        for( int i = 0; i < sampleCnt; i++ )
        {
             outAudioData[ i ] = ( int16_t )(inSampleData[ i ] * 32767.0f);
        }

        desiredWriteByteCnt = sampleCnt * sizeof( int16_t );
        wroteByteCnt = m_AudioOutIo.enqueueAudioData( (char *)outAudioData, desiredWriteByteCnt );
        //wrote += m_AudioBuf.writeData( ( char * )outAudioData, sampleCnt * sizeof( int16_t ) );
        wroteByteCnt *= sizeof( float ) / sizeof( int16_t ); // amount written needs int16 to float size as far as kodi is concerned

        delete outAudioData;
    }

    return wroteByteCnt;
}

//============================================================================
void AudioIoMgr::checkAudioState( int lastLenWrote )
{
    if( m_AudioOutIo.getError() != QAudio::NoError )
    {
        // Error handling
        LogMsg( LOG_DEBUG, "AudioIoMgr error %d", m_AudioOutIo.getError() );
    }

    QAudio::State audioState = m_AudioOutIo.getState();
    switch( audioState )
    {
    case QAudio::SuspendedState:
        LogMsg( LOG_DEBUG, "AudioIoMgr now SuspendedState" );
        break;

    case QAudio::ActiveState:
        //LogMsg( LOG_DEBUG, "AudioIoMgr now ActiveState" );
        break;

    case QAudio::StoppedState:
        LogMsg( LOG_DEBUG, "AudioIoMgr now StoppedState" );
        // Stopped for other reasons
        if( m_AudioOutIo.getError() != QAudio::NoError )
        {
            // Error handling
        }

        break;

    case QAudio::IdleState:
        // Finished playing (no more data)
        //m_AudioOutDev->stop();
        //sourceFile.close();
        //delete audio;
        LogMsg( LOG_DEBUG, "AudioIoMgr now IdleState" );
        break;

    default:
        LogMsg( LOG_DEBUG, "AudioIoMgr Unknown State %d", audioState );
        break;
    }

    if( 0 != m_AudioOutIo.audioQueUsedSpace() )
    {
        LogMsg( LOG_DEBUG, "AudioIoMgr device bytes available for audio device read %d", m_AudioOutIo.audioQueUsedSpace() );
    }

    //if(  m_AudioOutIo.getAudioOut() )
    //{
    //    m_AudioOutIo.getAudioOut()->setVolume( 1.0f );
    //}
}


//============================================================================
void AudioIoMgr::playerStateChanged( QAudio::State newState )
{
    switch( newState )
    {
    case QAudio::SuspendedState:
        LogMsg( LOG_DEBUG, "AudioIoMgr now SuspendedState" );
        break;

    case QAudio::ActiveState:
        LogMsg( LOG_DEBUG, "AudioIoMgr now ActiveState" );
        break;

    case QAudio::StoppedState:
        LogMsg( LOG_DEBUG, "AudioIoMgr now StoppedState" );
        // Stopped for other reasons
        if( m_AudioOutIo.getError() != QAudio::NoError )
        {
            // Error handling
        }

        break;

    case QAudio::IdleState:
        // Finished playing (no more data)
        //m_AudioOutDev->stop();
        //sourceFile.close();
        //delete audio;
        LogMsg( LOG_DEBUG, "AudioIoMgr now IdleState" );
        break;

    default:
        LogMsg( LOG_DEBUG, "AudioIoMgr Unknown State %d",  newState );
        break;
    }

}

//============================================================================
void AudioIoMgr::slotNeedMoreAudioData( int requiredLen )
{
    static int cnt = 0;
    cnt++;
    LogMsg( LOG_DEBUG, "AudioIoMgr notifyNeedData %d", cnt );

    /*
    if( m_IsTestMode )
    {
        char * data = new char[ AUDIO_BUF_SIZE_48000_2 ];
        m_AudioGen->readData( (char *)data, AUDIO_BUF_SIZE_48000_2 );
        float * floatData = new float[ AUDIO_BUF_SIZE_48000_2 * 2];
        int16_t * intData = ( int16_t * )data;
        for( int i = 0; i < AUDIO_BUF_SIZE_48000_2 / 2; i++ )
        {
            floatData[i] = (float)intData[i] / 32768.0f;
        }

        toGuiPlayAudio( eAppModuleTest, (int16_t *)floatData,   AUDIO_BUF_SIZE_48000_2 * 2 );
        delete data;
        delete floatData;
    }
    */
}

//============================================================================
void AudioIoMgr::aboutToDestroy()
{
}
