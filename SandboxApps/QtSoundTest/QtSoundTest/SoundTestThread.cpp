#include "SoundTestThread.h"
#include "SoundTestLogic.h"
#include <QDebug>

//============================================================================
SoundTestThread::SoundTestThread( SoundTestLogic& renderLogic )
    : m_RenderLogic( renderLogic )
{
}

//============================================================================
void SoundTestThread::startRenderThread()
{
    //connect( this, &QThread::finished, &m_RenderLogic, &QObject::deleteLater );
 
    start();
}

//============================================================================
void SoundTestThread::run()
{
    qDebug() << "hello from render thread " << currentThreadId();

    m_RenderLogic.initSoundTestSystem();
    while( m_ShouldRun )
    {
    }

    m_RenderLogic.destroySoundTestSystem();
    qDebug() << "render thread done " << currentThreadId();
}
