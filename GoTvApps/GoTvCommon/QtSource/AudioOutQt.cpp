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

#include "AudioOutQt.h"

#include <CoreLib/VxDebug.h>
#include <CoreLib/VxTime.h>

//============================================================================
AudioOutQt::AudioOutQt( AppCommon& myApp )
    : m_MyApp( myApp )
    , m_AudioOutIo( *this, this )
    , m_AudioGen( nullptr )
    , m_AudioDeviceInfo( QAudioDeviceInfo::defaultOutputDevice() )
    , m_IsPaused( false )
    //, m_IsTestMode( false )
    //, m_PartialInBuf( AUDIO_BUF_SIZE_48000_2 )
    //, m_PartialOutBuf( AUDIO_BUF_SIZE_48000_2 )
    , m_OutWriteCount( 0 )
    , m_MyLastAudioOutSample( 0 )
{
    m_AudioFormat.setSampleRate( 48000 );
    m_AudioFormat.setChannelCount( 2 );
    m_AudioFormat.setSampleSize( 16 );
    m_AudioFormat.setCodec( QStringLiteral("audio/pcm") );
    m_AudioFormat.setByteOrder( QAudioFormat::LittleEndian );
    m_AudioFormat.setSampleType( QAudioFormat::SignedInt );

    QAudioDeviceInfo info( m_AudioDeviceInfo );
    if( !info.isFormatSupported( m_AudioFormat ) )
    {
        LogMsg( LOG_DEBUG, "Default format not supported - trying to use nearest" );
        m_AudioFormat = info.nearestFormat( m_AudioFormat );
    }

    //...do pre-caching etc of the sounds here
    m_AudioGen = new AudioTestGenerator( m_AudioFormat, AUDIO_BUF_MS * 1000, 800, this );

    start();

    // Move event processing of sound to this thread
    QObject::moveToThread( this );
}

//============================================================================
AudioOutQt::~AudioOutQt( )
{
    quit();
    wait();
}

//============================================================================
void AudioOutQt::pauseAudioOut()
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
void AudioOutQt::resumeAudioOut()
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
void AudioOutQt::initAudioOut()
{
    m_AudioOutIo.start();
}
    
//============================================================================
void AudioOutQt::run() // thread override
{
    //m_AudioOutDev = new QAudioOutput( m_AudioFormat );
    m_AudioOutIo.initAudioOut( m_AudioFormat );

    connect( m_AudioOutIo.getAudioOut(), SIGNAL( stateChanged( QAudio::State ) ), this, SLOT( playerStateChanged( QAudio::State ) ) );
    //connect( m_AudioOutIo.getAudioOut(), SIGNAL( notify() ), SLOT( notifyNeedData() ) );
    connect( this, SIGNAL( signalNeedMoreAudioData( int ) ), SLOT( slotNeedMoreAudioData( int ) ) );

    initAudioOut();

    exec();
}

//============================================================================
void AudioOutQt::stopAudioOut()
{
    m_AudioOutIo.stop();
}

//============================================================================
// volume is from 0.0 to 1.0
void AudioOutQt::setVolume( float volume )
{
    m_AudioOutIo.setVolume( volume );
}

//============================================================================
qint64 AudioOutQt::speakerOutReadData( char * data, qint64 maxlen )
{
    if( 0 >= maxlen )
    {
        return 0;
    }

    // if there is not enough data then fill the beginning of data with silence
    int dataLenRead = 0;
    int dataAvail = m_AudioBuf.bytesAvailable();
    if( dataAvail < maxlen )
    {
        memset( data, 0, maxlen - dataAvail );
        dataLenRead = maxlen - dataAvail;
    }

    if( dataAvail )
    {
        dataLenRead += m_AudioBuf.readData( &data[dataLenRead], maxlen - dataLenRead );

        m_OutWriteCount += dataLenRead;
        while( m_OutWriteCount >= AUDIO_BUF_SIZE_48000_2 )
        {
            m_OutWriteCount -= AUDIO_BUF_SIZE_48000_2;
            emit signalNeedMoreAudioData( AUDIO_BUF_SIZE_48000_2 );
        }

        if( dataLenRead < maxlen )
        {
            LogMsg( LOG_ERROR, "AudioOutQt::speakerOutReadData lenRead %d of total len %lld time %lld", dataLenRead, maxlen, GetApplicationAliveMs() );
        }
    }
 
    checkAudioState( dataLenRead );

    return dataLenRead;
}

//============================================================================
double AudioOutQt::getAudioDelaySeconds() 
{
    int totalCachedData = getCachedDataLength( );
    return ((double)totalCachedData / (double)AUDIO_SIZE_DIV_TO_MS_48000_2) / 1000.0;
}

//============================================================================
double AudioOutQt::toGuiGetAudioCacheTotalSeconds()
{
    int totalCachedData = getCachedMaxLength();
    return ( ( double )totalCachedData / ( double )AUDIO_SIZE_DIV_TO_MS_48000_2 ) / 1000.0;
}

//============================================================================
int AudioOutQt::getCachedDataLength( bool requireLock )
{
    return m_AudioBuf.bytesAvailable();
}

//============================================================================
int AudioOutQt::toGuiGetAudioCacheFreeSpace( )
{
    return  getCachedMaxLength() - getCachedDataLength( );
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
int AudioOutQt::toGuiPlayAudio( EAppModule appModule, int16_t * pu16PcmData, int pcmDataLenInBytes )
{
    // it seems Qt does not handle anything but pcm 16 bit signed samples correctly so convert to what Qt can handle
    int wrote = 0;
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

        unsigned char * outAudioData = new unsigned char[ pcmDataLenInBytes * upResampleMultiplier ];

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

        wrote = m_AudioBuf.writeData( ( char * )outAudioData, pcmDataLenInBytes * upResampleMultiplier );
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
        
        wrote += m_AudioBuf.writeData( ( char * )outAudioData, sampleCnt * sizeof( int16_t ) );
        wrote *= sizeof( float ) / sizeof( int16_t ); // amount written needs int16 to float size as far as kodi is concerned

        delete outAudioData;
    }

    return wrote;
}

//============================================================================
void AudioOutQt::checkAudioState( int lastLenWrote )
{
    if( m_AudioOutIo.getError() != QAudio::NoError )
    {
        // Error handling
        LogMsg( LOG_DEBUG, "AudioOutQt error %d", m_AudioOutIo.getError() );
    }

    QAudio::State audioState = m_AudioOutIo.getState();
    switch( audioState )
    {
    case QAudio::SuspendedState:
        LogMsg( LOG_DEBUG, "AudioOutQt now SuspendedState" );
        break;

    case QAudio::ActiveState:
        //LogMsg( LOG_DEBUG, "AudioOutQt now ActiveState" );
        break;

    case QAudio::StoppedState:
        LogMsg( LOG_DEBUG, "AudioOutQt now StoppedState" );
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
        LogMsg( LOG_DEBUG, "AudioOutQt now IdleState" );
        break;

    default:
        LogMsg( LOG_DEBUG, "AudioOutQt Unknown State %d", audioState );
        break;
    }

    if( 0 != m_AudioOutIo.bytesAvailable() )
    {
        LogMsg( LOG_DEBUG, "AudioOutQt device bytes available %lld", m_AudioOutIo.bytesAvailable() );
    }

    //if(  m_AudioOutIo.getAudioOut() )
    //{
    //    m_AudioOutIo.getAudioOut()->setVolume( 1.0f );
    //}
}


//============================================================================
void AudioOutQt::playerStateChanged( QAudio::State newState )
{
    switch( newState ) 
    {
    case QAudio::SuspendedState:
        LogMsg( LOG_DEBUG, "AudioOutQt now SuspendedState" );
        break;

    case QAudio::ActiveState:
        LogMsg( LOG_DEBUG, "AudioOutQt now ActiveState" );
        break;

    case QAudio::StoppedState:
        LogMsg( LOG_DEBUG, "AudioOutQt now StoppedState" );
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
        LogMsg( LOG_DEBUG, "AudioOutQt now IdleState" );
        break;

    default:
        LogMsg( LOG_DEBUG, "AudioOutQt Unknown State %d",  newState );
        break;
    }
 
}

//============================================================================
void AudioOutQt::slotNeedMoreAudioData( int requiredLen )
{
    static int cnt = 0;
    cnt++;
    //LogMsg( LOG_DEBUG, "AudioOutQt notifyNeedData %d", cnt );
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
}
