#include "RenderGlThread.h"

//============================================================================
RenderGlThread::RenderGlThread( RenderGlLogic& renderLogic )
    : m_RenderLogic( renderLogic )
{
}

//============================================================================
void RenderGlThread::startRenderThread()
{
    //connect( this, &QThread::finished, &m_RenderLogic, &QObject::deleteLater );
 
    start();
}

//============================================================================
void RenderGlThread::run()
{
    qDebug() << "hello from render thread " << currentThreadId();

    m_RenderLogic.initRenderGlSystem();
    while( m_ShouldRun )
    {
        m_RenderLogic.VerifyGLStateQt();

        if( !m_RenderLogic.beginRenderGl() )
        {
            qDebug() << "thread beginRender failed";
            break;
        }

        m_RenderLogic.VerifyGLStateQt();
        if( !m_RenderLogic.endRenderGl() )
        {
            qDebug() << "thread endRender failed";
            break;
        }

        m_RenderLogic.VerifyGLStateQt();
        m_RenderLogic.presentRenderGl( true, true );
        m_RenderLogic.VerifyGLStateQt();
        msleep( 30 );
    }

    m_RenderLogic.destroyRenderGlSystem();
    qDebug() << "render thread done " << currentThreadId();
}