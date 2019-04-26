#include <GoTvInterface/IGoTv.h>
#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>

#include <CoreLib/VxGlobals.h>
#include <CoreLib/VxDebug.h>
#include "RunKodiThread.h"
#include "RenderGlOffScreenSurface.h"
#include "RenderGlWidget.h"

//============================================================================
RunKodiThread::RunKodiThread( RenderGlLogic& renderLogic )
    : QThread()
    , m_RenderLogic( renderLogic )
{
    connect( this, SIGNAL( finished() ), this, SLOT( deleteLater() ) );
    connect( this, SIGNAL( signalStartRenderThread() ), this, SLOT( slotStartRenderThread() ) );
}

//============================================================================
void RunKodiThread::run()
{
    static bool isKodiRunning = false;
    if( !isKodiRunning )
    {
        LogMsg( LOG_ERROR, "size of bool %d\n", sizeof( bool ) );
        isKodiRunning = true;
#ifdef RENDER_LOGO_INSTEAD_OF_KODI
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
#else
        IGoTv& iGoTv = IGoTv::getIGoTv();
        // will not return from doRun until kodi is shutdown
        iGoTv.doRun( eAppModuleKodi );
        // BRJ FIXME
        // BRJ for no reason I can see g_RunKodi->deleteLater() will let memory allocated by Qt to be overwritten by normal malloc calls in kodi
        //    g_RunKodi->deleteLater();
        //g_RunKodi = nullptr;
#endif // RENDER_LOGO_INSTEAD_OF_KODI
        isKodiRunning = false;
    }
    else
    {
        LogMsg( LOG_ERROR, "Tried to run kodi twice\n" );
    }
}

//============================================================================
void RunKodiThread::startRunKodiThread()
{
    if( !isRunKodiThreadStarted() )
    {
        m_IsThreadStarted = true;
        emit signalStartRunKodiThread();
    }
}

//============================================================================
void RunKodiThread::slotStartRunKodiThread()
{
    start();
}

//============================================================================
void RunKodiThread::stopRunKodiThread()
{
    if( isRunKodiThreadStarted() )
    {
        m_IsThreadStarted = false;
        //stop();
    }
}
