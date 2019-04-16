
#include <GoTvInterface/IGoTv.h>
#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>

#include <CoreLib/VxGlobals.h>
#include <CoreLib/VxDebug.h>
#include "RenderKodiThread.h"
#include "RenderGlOffScreenSurface.h"
#include "RenderGlWidget.h"

//============================================================================
RenderKodiThread::RenderKodiThread( QWidget * parent )
: QThread()
{
    connect( this, SIGNAL( finished() ), this, SLOT( deleteLater() ) );
}

//============================================================================
void RenderKodiThread::run()
{
    if( !m_IsKodiRunning )
    {
        m_IsKodiRunning = true;

        IGoTv& iGoTv = IGoTv::getIGoTv();
        // will not return from doRun until kodi is shutdown
        iGoTv.doRun( eAppModuleKodi );
        // BRJ FIXME
        // BRJ for no reason I can see g_RunKodi->deleteLater() will let memory allocated by Qt to be overwritten by normal malloc calls in kodi
        //    g_RunKodi->deleteLater();
        //g_RunKodi = nullptr;
        m_IsKodiRunning = false;
    }
}
