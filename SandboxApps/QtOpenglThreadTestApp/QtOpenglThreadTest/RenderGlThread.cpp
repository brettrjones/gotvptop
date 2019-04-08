#include "RenderGlThread.h"

//============================================================================
RenderGlThread::RenderGlThread( RenderGlLogic& renderLogic )
    : m_RenderLogic( renderLogic )
{
}

//============================================================================
void RenderGlThread::startRenderThread()
{
    connect( this, &QThread::finished, &m_RenderLogic, &QObject::deleteLater );
 
    start();
}

void RenderGlThread::run()
{
    qDebug() << "hello from worker thread " << currentThreadId();
    m_RenderLogic.initRenderGlSystem();
    while( m_ShouldRun )
    {
        if( !m_RenderLogic.beginRenderGl() )
        {
            qDebug() << "thread beginRender failed";
            break;
        }

        if( !m_RenderLogic.endRenderGl() )
        {
            qDebug() << "thread endRender failed";
            break;
        }

        m_RenderLogic.presentRenderGl( true, true );
        msleep( 30 );
    }

    m_RenderLogic.destroyRenderGlSystem();
    qDebug() << "worker thread done " << currentThreadId();
}