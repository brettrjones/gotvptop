#include "SoundTestThread.h"
#include "SoundTestLogic.h"
#include <QDebug>
#include "VxDebug.h"
#include "VxTime.h"
#include "AudioDefs.h"

//============================================================================
SoundTestThread::SoundTestThread( SoundTestLogic& renderLogic )
: m_SoundTestLogic( renderLogic )
, m_AudioIoMgr( renderLogic.getAudioIoMgr() )
, m_AudioGenOut( renderLogic.getAudioOutGenerator() )
{
}

//============================================================================
void SoundTestThread::startSoundTestThread()
{
    //connect( this, &QThread::finished, &m_RenderLogic, &QObject::deleteLater );
 
    start();
}

//============================================================================
void SoundTestThread::stopSoundTestThread()
{
    //connect( this, &QThread::finished, &m_RenderLogic, &QObject::deleteLater );

    terminate();
}

//============================================================================
void SoundTestThread::run()
{
    LogMsg( LOG_DEBUG, "SoundTestThread thread %d", currentThreadId() );
    const qreal audioBufLen = AUDIO_BUF_SIZE_48000_2_FLOAT;
    char audioBuf[ AUDIO_BUF_SIZE_48000_2_FLOAT ];
    qreal amountRead = m_AudioGenOut->readDataNoPositionUpdate( audioBuf, audioBufLen );
    if( audioBufLen != amountRead )
    {
        LogMsg( LOG_ERROR, "requested audio len %3.3f got %3.3f ", audioBufLen, amountRead );
        return;
    }

    m_AudioIoMgr.toGuiWantSpeakerOutput( eAppModuleKodi, true );
    float * audioAsFloat = (float *)audioBuf;

    while( m_ShouldRun )
    {
        int spaceFree = m_AudioIoMgr.toGuiGetAudioCacheFreeSpace( eAppModuleKodi );
        if( !m_PauseSound && ( spaceFree >= AUDIO_BUF_SIZE_48000_2_FLOAT ) )
        {
            //int sampleCnt = (int)( AUDIO_BUF_SIZE_48000_2_FLOAT / 4 );
            //LogMsg( LOG_DEBUG, "kodi first %3.3f second %3.3f last %3.3f ", audioAsFloat[ 0 ], audioAsFloat[ 2 ], audioAsFloat[ sampleCnt - 1 ] );

            m_AudioIoMgr.toGuiPlayAudio( eAppModuleKodi, (float *)audioBuf, audioBufLen );
        }
        else
        {
            VxSleep( 10 );
        }
    }

    m_AudioIoMgr.toGuiWantSpeakerOutput( eAppModuleKodi, false );

    LogMsg( LOG_DEBUG, "SoundTestThread done thread %d", currentThreadId() );
}