//============================================================================
// Copyright (C) 2019 Brett R. Jones
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

#include "AudioMixer.h"
#include "IAudioInterface.h"
#include "AudioIoMgr.h"
#include "AudioUtils.h"

#include "VxDebug.h"
#include <algorithm>
#include <memory.h>

//============================================================================
AudioMixer::AudioMixer( AudioIoMgr& audioIoMgr, IAudioCallbacks& audioCallbacks, QWidget * parent )
: QWidget( parent )
, m_AudioIoMgr( audioIoMgr  )
, m_AudioCallbacks( audioCallbacks )
 {
     memset( m_BufIndex, 0, sizeof( m_BufIndex ) );
     m_AtomicBufferSize = 0;
     m_ElapsedTimer.restart();
 }

//============================================================================
// add audio data to mixer.. assumes pcm signed short 2 channel 48000 Hz.. return total written to buffer
int AudioMixer::enqueueAudioData( EAppModule appModule, int16_t * pcmData, int pcmDataLenInBytes, bool isSilence )
{
    if( appModule == eAppModulePtoP )
    {
        int appWriteIdx = m_BufIndex[ appModule ];
        //LogMsg( LOG_DEBUG, "enqueueAudioData in que %d at %lld", appWriteIdx + pcmDataLenInBytes, m_ElapsedTimer.elapsed() );
    }

    int toWriteByteCnt = 0;

    if( ( pcmDataLenInBytes > 0 ) && ( appModule > 1 ) && ( appModule < eMaxAppModule ) )
    {
        m_MixerMutex.lock();
        int queSpace = audioQueFreeSpace( appModule );
        int maxSpace = m_AudioIoMgr.getCachedMaxLength();

        int samplesCnt = pcmDataLenInBytes / 2;
        int toWriteByteCnt = std::min( queSpace, pcmDataLenInBytes );
        if( pcmDataLenInBytes > toWriteByteCnt )
        {
            // if not enough space then do not write anything or kodi gets confused
            if( eAppModuleKodi == appModule )
            {
                m_AtomicBufferSize = m_AudioBuffer.size();
                LogMsg( LOG_DEBUG, "enqueueAudioData need %d space but have %d ", pcmDataLenInBytes, queSpace );
                emit signalCheckSpeakerOutState();
                m_MixerMutex.unlock();
                return 0;
            }
        }

        if( toWriteByteCnt )
        {
            // BRJ what to do with silence
 
            int appWriteIdx = m_BufIndex[ appModule ];
            int curBufSize = m_AudioBuffer.size();
            if( appWriteIdx > curBufSize )
            {
                LogMsg( LOG_ERROR, "enqueueAudioData mismatch write idx %d existing data %d ", appWriteIdx, curBufSize );
                appWriteIdx = curBufSize;
            }

            if( appWriteIdx == curBufSize )
            {
                // no mixing required
                m_AudioBuffer.append( (char *)pcmData, toWriteByteCnt );
                updateWriteBufferIndex( appModule, toWriteByteCnt );
                //LogMsg( LOG_DEBUG, "enqueueAudioData no mix mod %d len %d written %d buf len %d", appModule, m_BufIndex[ appModule ], toWriteByteCnt, m_AudioBuffer.size() );
            }
            else
            {
                // some or all requires mixing
                int appEndIdx = appWriteIdx + toWriteByteCnt;
                int toMixLen = std::min( curBufSize - appWriteIdx, toWriteByteCnt );
                char * audioOutData = m_AudioBuffer.data();
                char * audioWriteData = &audioOutData[ appWriteIdx ];

                if( toMixLen > 0 )
                {
                    AudioUtils::mixPcmAudio( pcmData, (int16_t *)audioWriteData, toMixLen );
                    if( toMixLen != toWriteByteCnt )
                    {
                        int toAppendLen = toWriteByteCnt - toMixLen;
                        //LogMsg( LOG_DEBUG, "enqueueAudioData mix len %d append len %d total %d index now %d", toMixLen, toAppendLen, toMixLen + toAppendLen, m_BufIndex[ appModule ] + toWriteByteCnt  );
                        // append remainder
                        char * audioPcmData = (char *)pcmData;
                        char * audioReadData = &audioPcmData[ toMixLen ];
                        m_AudioBuffer.append( audioReadData, toWriteByteCnt - toMixLen );
                    }

                    //m_BufIndex[ appModule ] += toWriteByteCnt;
                    updateWriteBufferIndex( appModule, toWriteByteCnt );

                }
                else
                {
                    LogMsg( LOG_ERROR, "enqueueAudioData error in mix len " );
                }

                //int16_t * sampleBuf = (int16_t *)( &audioOutData[ appWriteIdx ] );
                //int sampleCnt = toWriteByteCnt / 2;
                //LogMsg( LOG_DEBUG, "enqueueAudioData first %d second %d last %d ", sampleBuf[ 0 ], sampleBuf[ 2 ], sampleBuf[ sampleCnt - 1 ] );
               
            }

        }

//        if( toWriteByteCnt && ( queSpace < maxSpace / 2 ) )
//        {
//            emit signalCheckSpeakerOutState();
//        }

        m_AtomicBufferSize = m_AudioBuffer.size();
        m_MixerMutex.unlock();
        emit signalCheckSpeakerOutState();
    }
    else
    {
        // should probably be considered a fatal error
        if( 0 == pcmDataLenInBytes )
        {
            LogMsg( LOG_ERROR, "enqueueAudioData 0 bytes " );
            return 0;
        }
        else
        {
            LogMsg( LOG_ERROR, "enqueueAudioData invalid module %d ", appModule );
        }
    }

    return toWriteByteCnt;
}

//============================================================================
// read audio data from mixer.. assumes pcm 2 channel 48000 Hz
qint64 AudioMixer::readDataFromMixer( char *data, qint64 maxlen )
{
    if( maxlen <= 0 )
    {
//        LogMsg( LOG_DEBUG, "readDataFromMixer %lld bytes ", maxlen );
        return maxlen;
    }

    m_MixerMutex.lock();
    int toReadByteCnt = std::min( (int)maxlen, m_AudioBuffer.size() );
 //   LogMsg( LOG_DEBUG, "readDataFromMixer in que %d at %lld ms", toReadByteCnt, m_ElapsedTimer.elapsed() );

    if( 0 == toReadByteCnt )
    {
        LogMsg( LOG_DEBUG, "*** readDataFromMixer avail %d of %lld bytes at %3.3f ms ", toReadByteCnt, maxlen, m_ReadBufTimer.elapsedMs() );
    }

    //if( 0 == toReadByteCnt )
    //{
    //    LogMsg( LOG_DEBUG, "*** readDataFromMixer avail %d of %lld bytes at %3.3f ms ", toReadByteCnt, maxlen, m_ReadBufTimer.elapsedMs() );
    //}

    m_ReadBufTimer.resetTimer();

    if( toReadByteCnt )
    {
        if( m_SpeakersMuted )
        {
            memset( data, 0, toReadByteCnt );
        }
        else
        {
            memcpy( data, m_AudioBuffer.data(), toReadByteCnt );
        }

        m_AudioBuffer.remove( 0, toReadByteCnt ); //pop front what is written

            // update indexes that applications write data into buffer at
        updateReadBufferIndexes( toReadByteCnt );
        //int bytesRead = (int)maxlen;
        //if( bytesRead > toReadByteCnt )
        //{
        //    // if not enough data to read then fill with silence
        //    memset( &data[ toReadByteCnt ], 0, bytesRead - toReadByteCnt );
        //}

        m_AudioCallbacks.speakerAudioPlayed( m_AudioIoMgr.getAudioOutFormat(), (void *)data, toReadByteCnt );
        //LogMsg( LOG_ERROR, "readDataFromMixer requested %d read %d len left %d ptop len %d", maxlen, toReadByteCnt, m_AudioBuffer.size(), m_BufIndex[ eAppModulePtoP ] );
    }


    m_AtomicBufferSize = m_AudioBuffer.size();
    m_MixerMutex.unlock();

    return toReadByteCnt;
}

//============================================================================
// update indexes that applications write data into buffer at
void AudioMixer::updateReadBufferIndexes( int byteCnt )
{
    if( byteCnt > 0 )
    {
        // 0 = eAppModuleInvalid, 1 = eAppModuleAll
        for( int i = 2; i < eMaxAppModule; i++ )
        {
            if( m_BufIndex[ i ] >= byteCnt )
            {
                m_BufIndex[ i ] -= byteCnt;
                if( m_BufIndex[ i ] )
                {
                    int bytesInBuffer = m_BufIndex[ i ];
                    LogMsg( LOG_ERROR, "updateReadBufferIndexes mod %d bytes %d  ", i, bytesInBuffer );
                }
            }
            else
            {
                // more has been read than available so reset
                m_BufIndex[ i ] = 0;
            }
        }
    }
}

//============================================================================
// update indexes that applications write data into buffer at ( add data count written to mixer )
void AudioMixer::updateWriteBufferIndex( EAppModule appModule, int byteCnt )
{
    if( ( byteCnt > 0 ) && ( appModule > 1 ) && ( appModule < eMaxAppModule ) )
    {
        m_BufIndex[ appModule ] += byteCnt;
        int bytesInBuffer = m_BufIndex[ appModule ];
        LogMsg( LOG_ERROR, "updateWriteBufferIndex mod %d idx %d bytes ", appModule, bytesInBuffer );
    }
}

//============================================================================
/// space available to que audio data into buffer
int AudioMixer::audioQueFreeSpace( EAppModule appModule )
{
    int freeSpace = AUDIO_OUT_CACHE_USABLE_SIZE - audioQueUsedSpace( appModule );
    if( freeSpace < 0 )
    {
        freeSpace = 0;
    }

    return freeSpace;
}

//============================================================================
/// space used in audio que buffer
int AudioMixer::audioQueUsedSpace( EAppModule appModule )
{
    if( ( appModule > 1 ) && ( appModule < eMaxAppModule ) )
    {
        return m_BufIndex[ appModule ];
    }

    return 0;
}

//============================================================================
// get length of data buffered and ready for speaker out
int AudioMixer::getDataReadyForSpeakersLen()
{
    return m_AtomicBufferSize;
}
