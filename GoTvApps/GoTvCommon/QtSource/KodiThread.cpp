
#include <GoTvInterface/IGoTv.h>
#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>

#include <CoreLib/VxGlobals.h>
#include <CoreLib/VxDebug.h>
#include "KodiThread.h"
#include "RenderGlOffScreenSurface.h"


bool KodiThread::m_IsKodiRunning = false;

//============================================================================
KodiThread::KodiThread( AppCommon& app, QWidget * parent )
: QThread()
, m_MyApp( app )
{
    //connect( this, SIGNAL( started() ), this, SLOT( slotStartKodiRunFromThread() ) );
    connect( this, SIGNAL( finished() ), this, SLOT( deleteLater() ) );
}

//============================================================================
void KodiThread::run()
{
    if( !m_IsKodiRunning )
    {
        m_IsKodiRunning = true;

        makeCurrentGlContext();
        IGoTv& iGoTv = IGoTv::getIGoTv();
        // will not return from doRun until kodi is shutdown
        iGoTv.doRun( eAppModuleKodi );
        //GetAppInstance().setKodiThread( nullptr );
        // BRJ FIXME
        // BRJ for no reason I can see g_RunKodi->deleteLater() will let memory allocated by Qt to be overwritten by normal malloc calls in kodi
        //    g_RunKodi->deleteLater();
        //g_RunKodi = nullptr;
        m_IsKodiRunning = false;
    }
}

//void KodiThread::resize( int width, int height )
//{
    //m_Context->makeCurrent( m_Surface );
//}

void KodiThread::makeCurrentGlContext()
{
    if( m_KodiThreadContext && m_KodiThreadSurface )
    {
        m_KodiThreadContext->makeCurrent( m_KodiThreadSurface );
    }
}
