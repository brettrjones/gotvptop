#include "SoundTestLogic.h"

#include <QSurface>
#include <qmath.h>
#include <QTimer>

#include "VxDebug.h"


//============================================================================
SoundTestLogic::SoundTestLogic( SoundTestWidget& renderWidget, QWidget *parent )
: m_RenderWidget( renderWidget )
, m_AudioIoMgr( this )
{
    m_SoundTestThread = new SoundTestThread( *this );

    //...do pre-caching etc of the sounds here
    m_AudioGen = new AudioTestGenerator( m_AudioFormat, AUDIO_BUF_MS * 1000, 800, this );
}

//============================================================================
void SoundTestLogic::aboutToDestroy()
{
    setRenderThreadShouldRun( false );
    if( m_SoundTestThread )
    {
        m_SoundTestThread->quit(); // some platforms may not have windows to close so ensure quit()
        m_SoundTestThread->wait();
        delete m_SoundTestThread;
        m_SoundTestThread = nullptr;
    }
 }

/// for visualization of audio output
void SoundTestLogic::speakerAudioPlayed( QAudioFormat& /*format*/, void * /*data*/, int /*dataLen*/ ) override;
/// for visualization of audio input
void SoundTestLogic::microphoneAudioRecieved( QAudioFormat& /*format*/, void * /*data*/, int /*dataLen*/ ) override;

/// Microphone sound capture ( 8000hz PCM 16 bit data, 80ms of sound )
void SoundTestLogic::romGuiMicrophoneData( int16_t* pu16PcmData, uint16_t pcmDataLenBytes )
{

}

/// Microphone sound capture with info for echo cancel ( 8000hz PCM 16 bit data, 80ms of sound )
void SoundTestLogic::fromGuiMicrophoneDataWithInfo( int16_t * pcmData, int pcmDataLenBytes, int totalDelayTimeMs, int clockDrift )
{

}

/// Mute/Unmute microphone
void SoundTestLogic::fromGuiMuteMicrophone( bool muteMic )
{
    m_AudioIoMgr.fromGuiMuteMicrophone( muteMic );
}

/// Returns true if microphone is muted
bool SoundTestLogic::fromGuiIsMicrophoneMuted()
{
    return m_AudioIoMgr.fromGuiIsMicrophoneMuted();
}

/// Mute/Unmute speaker
void SoundTestLogic::fromGuiMuteSpeaker( bool muteSpeaker )
{
    m_AudioIoMgr.fromGuiMuteSpeaker( muteSpeaker );
}

/// Returns true if speaker is muted
bool SoundTestLogic::fromGuiIsSpeakerMuted()
{
    return m_AudioIoMgr.fromGuiIsSpeakerMuted();
}

/// Enable/Disable echo cancellation
void SoundTestLogic::fromGuiEchoCancelEnable( bool enableEchoCancel )
{

}

/// Returns true if echo cancellation is enabled
bool SoundTestLogic::fromGuiIsEchoCancelEnabled( void )
{

    return true;
}

/// Called when need more sound for speaker output
void SoundTestLogic::romGuiAudioOutSpaceAvail( int freeSpaceLen )
{

}


//============================================================================
void SoundTestLogic::setRenderThreadShouldRun( bool shouldRun )
{
    if( m_SoundTestThread )
    {
        m_SoundTestThread->setRenderThreadShouldRun( shouldRun );
    }
}

//============================================================================
//! must be called from render thread
void SoundTestLogic::startRenderThread()
{ 
    if( m_SoundTestThread )
    {
        m_SoundTestThread->startRenderThread();
    }
}

//============================================================================
// called from thread
void SoundTestLogic::render()
{
}

//============================================================================
bool SoundTestLogic::initSoundTestSystem()
{

    return true;
}

//============================================================================
bool SoundTestLogic::destroySoundTestSystem()
{
    return true;
}

//============================================================================
bool SoundTestLogic::beginSoundTest()
{

    return true;
}

//============================================================================
bool SoundTestLogic::endSoundTest()
{
    render();


    return true;
}
