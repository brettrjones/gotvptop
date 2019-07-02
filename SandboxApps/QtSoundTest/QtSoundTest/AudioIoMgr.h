#pragma once

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QElapsedTimer>
#include <QWidget>
#include <QAudioOutput>
#include <QAudioInput>

#include "IGoTvDefs.h"
#include "AudioMixer.h"
#include "AudioOutIo.h"
#include "AudioInIo.h"

class IAudioCallbacks
{
public:
    /// for visualization of audio output
    virtual void                speakerAudioPlayed( QAudioFormat& /*format*/, void * /*data*/, int /*dataLen*/ ){};
    /// for visualization of audio input
    virtual void                microphoneAudioRecieved( QAudioFormat& /*format*/, void * /*data*/, int /*dataLen*/ ){};

    /// Microphone sound capture ( 8000hz PCM 16 bit data, 80ms of sound )
    virtual void				fromGuiMicrophoneData( int16_t* pu16PcmData, uint16_t pcmDataLenBytes ) = 0;
    /// Microphone sound capture with info for echo cancel ( 8000hz PCM 16 bit data, 80ms of sound )
    virtual void				fromGuiMicrophoneDataWithInfo( int16_t * pcmData, int pcmDataLenBytes, int totalDelayTimeMs, int clockDrift ) = 0;
    /// Mute/Unmute microphone
    virtual void				fromGuiMuteMicrophone( bool muteMic ) = 0;
    /// Returns true if microphone is muted
    virtual bool				fromGuiIsMicrophoneMuted( void ) = 0;
    /// Mute/Unmute speaker
    virtual void				fromGuiMuteSpeaker(	bool muteSpeaker ) = 0;
    /// Returns true if speaker is muted
    virtual bool				fromGuiIsSpeakerMuted( void ) = 0;
    /// Enable/Disable echo cancellation
    virtual void				fromGuiEchoCancelEnable( bool enableEchoCancel ) = 0;
    /// Returns true if echo cancellation is enabled
    virtual bool				fromGuiIsEchoCancelEnabled( void ) = 0;
    /// Called when need more sound for speaker output
    virtual void				fromGuiAudioOutSpaceAvail( int freeSpaceLen ) = 0;

};

class IAudioRequests
{
public:
    // enable disable fromGuiMicrophoneData callback
    virtual void				toGuiWantMicrophoneRecording( bool wantMicInput ) = 0;
    // enable disable
    virtual void				toGuiWantSpeakerOutput( bool wantSpeakerOutput ) = 0;
    // add audio data to play.. assumes 16 bit
    virtual void				toGuiPlayAudio( int16_t * pu16PcmData, int pcmDataLenInBytes ) = 0;
    // add audio data to play.. convert float to s16 pcm data before calling writeData
    virtual int				    toGuiPlayAudio( EAppModule appModule, int16_t * pu16PcmData, int pcmDataLenInBytes ) = 0;
    // delay of audio calculated from amount of data in queue
    virtual double				toGuiGetAudioDelaySeconds() = 0;
    // maximum queue cache size in seconds
    virtual double				toGuiGetAudioCacheTotalSeconds() = 0;
    // amount of free queue space in bytes
    virtual int				    toGuiGetAudioCacheFreeSpace( EAppModule appModule ) = 0;
};


class AudioIoMgr : public QWidget, public IAudioRequests
{
    Q_OBJECT
public:
    explicit AudioIoMgr( IAudioCallbacks& audioCallbacks, QWidget * parent );

    ~AudioIoMgr() override = default;

    void                        initAudioIoSystem();
    void                        destroyAudioIoSystem();

    QAudioFormat&                getAudioOutFormat() { return m_AudioOutFormat; }
    QAudioFormat&                getAudioInFormat() { return m_AudioInFormat; }

    bool                        isMicrophoneAvailable()     { return m_MicrophoneAvailable; }
    bool                        isMicrophoneEnabled()       { return m_MicrophoneEnabled; }
    bool                        isMicrophoneMuted()         { return m_MicrophoneMuted; }
    bool                        isSpeakersMuted()           { return m_SpeakersMuted; }

    void                        lockAudioOut() { m_AudioOutMutex.lock(); }
    void                        unlockAudioOut() { m_AudioOutMutex.unlock(); }

    void                        lockAudioIn() { m_AudioInMutex.lock(); }
    void                        unlockAudioIn() { m_AudioInMutex.unlock(); }

    // volume is from 0.0 to 1.0
    void						setVolume( float volume );

    void                        pauseAudioOut( );
    void                        resumeAudioOut( );

    //=== IAudioRequests ===//
    // enable disable microphone data callback
    virtual void				toGuiWantMicrophoneRecording( bool wantMicInput ) override;
    // enable disable
    virtual void				toGuiWantSpeakerOutput( bool wantSpeakerOutput ) override;
    // add audio data to play.. assumes 16 bit
    virtual void				toGuiPlayAudio( int16_t * pu16PcmData, int pcmDataLenInBytes ) override;
    // add audio data to play.. convert float to s16 pcm data before calling writeData
    virtual int				    toGuiPlayAudio( EAppModule appModule, int16_t * pu16PcmData, int pcmDataLenInBytes ) override;
    // delay of audio calculated from amount of data in queue
    virtual double				toGuiGetAudioDelaySeconds( ) override;
    // maximum queue cache size in seconds
    virtual double				toGuiGetAudioCacheTotalSeconds() override;
    // amount of free queue space in bytes
    virtual int				    toGuiGetAudioCacheFreeSpace( EAppModule appModule ) override;

signals:
    void                        signalNeedMoreAudioData( int requiredLen );

public slots:
    void                        slotNeedMoreAudioData( int  requiredLen );
    void                        playerStateChanged( QAudio::State state );

protected:
    void						stopAudioOut( );
    void                        stopAudioIn();
    //void                        addToQue( const char * data, int len );

    //void                        run( ) override; // thread override

    int                         getCachedDataLength( bool requireLock = true );
    int                         getCachedMaxLength( ) { return AUDIO_OUT_CACHE_SIZE; }

    void                        checkAudioState( int lastLenWrote );


    void                        aboutToDestroy();

private:
    IAudioCallbacks&            m_AudioCallbacks;

    bool                        m_AudioIoInitialized = false;
    bool                        m_MicrophoneAvailable = false;
    bool                        m_MicrophoneEnabled = false;
    bool                        m_MicrophoneMuted = false;
    bool                        m_SpeakersMuted = false;

    QMutex                      m_AudioOutMutex;
    QMutex                      m_AudioInMutex;

    QAudioFormat                m_AudioOutFormat;
    AudioOutIo                  m_AudioOutIo;
    QAudioDeviceInfo            m_AudioOutDeviceInfo;

    QAudioFormat                m_AudioInFormat;
    AudioInIo                   m_AudioInIo;
    QAudioDeviceInfo            m_AudioInDeviceInfo;

    AudioMixer                  m_AudioOutMixer;

    bool                        m_IsPaused = false;
    bool                        m_IsTestMode = true;
    int                         m_CacheAuidioLen = 0;
    QMutex                      m_AudioQueueMutex;
    int                         m_OutWriteCount = 0;
    int16_t                     m_MyLastAudioOutSample = 0;

};
