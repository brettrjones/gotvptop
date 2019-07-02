#ifndef SoundTestLOGIC_H
#define SoundTestLOGIC_H


#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>

#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QVector3D>
#include <QMatrix4x4>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QElapsedTimer>
#include <QWindow>
#include <QOpenGLWidget>

#include "SoundTestThread.h"
#include "AudioIoMgr.h"
#include "AudioTestGenerator.h"

class SoundTestWidget;
class SoundTestThread;

class SoundTestLogic : public QWidget, public IAudioCallbacks
{
    Q_OBJECT
public:
    explicit SoundTestLogic( SoundTestWidget& renderWidget, QWidget *parent );

    void						setRenderThreadShouldRun( bool shouldRun );
    void						setRenderWindowVisible( bool isVisible ) { m_RenderWindowVisible = isVisible; }

    bool                        getIsRenderInitialized() { return m_RenderInitialized; }

    void                        startRenderThread();


    virtual bool                initSoundTestSystem();
    virtual bool                destroySoundTestSystem();

    virtual bool                beginSoundTest();
    virtual bool                endSoundTest();

    void                        lockRenderer() { m_renderMutex.lock(); }
    void                        unlockRenderer() { m_renderMutex.unlock(); }

    void                        aboutToDestroy();

    /// for visualization of audio output
    virtual void                speakerAudioPlayed( QAudioFormat& /*format*/, void * /*data*/, int /*dataLen*/ ) override;
    /// for visualization of audio input
    virtual void                microphoneAudioRecieved( QAudioFormat& /*format*/, void * /*data*/, int /*dataLen*/ ) override;

    /// Microphone sound capture ( 8000hz PCM 16 bit data, 80ms of sound )
    virtual void				fromGuiMicrophoneData( int16_t* pu16PcmData, uint16_t pcmDataLenBytes )  override;
    /// Microphone sound capture with info for echo cancel ( 8000hz PCM 16 bit data, 80ms of sound )
    virtual void				fromGuiMicrophoneDataWithInfo( int16_t * pcmData, int pcmDataLenBytes, int totalDelayTimeMs, int clockDrift ) override;
    /// Mute/Unmute microphone
    virtual void				fromGuiMuteMicrophone( bool muteMic ) override;
    /// Returns true if microphone is muted
    virtual bool				fromGuiIsMicrophoneMuted( void ) override;
    /// Mute/Unmute speaker
    virtual void				fromGuiMuteSpeaker(	bool muteSpeaker ) override;
    /// Returns true if speaker is muted
    virtual bool				fromGuiIsSpeakerMuted( void ) override;
    /// Enable/Disable echo cancellation
    virtual void				fromGuiEchoCancelEnable( bool enableEchoCancel ) override;
    /// Returns true if echo cancellation is enabled
    virtual bool				fromGuiIsEchoCancelEnabled( void ) override;
    /// Called when need more sound for speaker output
    virtual void				fromGuiAudioOutSpaceAvail( int freeSpaceLen ) override;

signals:
    void                        signalFrameRendered();

public slots:
    void                        render();

private:
    SoundTestWidget&            m_RenderWidget;
    SoundTestThread *			m_SoundTestThread = nullptr;

    AudioIoMgr                  m_AudioIoMgr;
    AudioTestGenerator          m_AudioGenIn;
    AudioTestGenerator          m_AudioGenOut;

    bool                        m_RenderInitialized = false;
  
    QMutex                      m_renderMutex;

    bool                        m_exiting = false;

    bool                        m_RenderWindowVisible = false;
};

#endif // SoundTestLOGIC_H
