#include "RenderGlLogic.h"
#include "RenderKodiThread.h"
#include "RenderGlOffScreenSurface.h"
#include "RenderGlWidget.h"

//============================================================================
RenderGlLogic::RenderGlLogic( RenderGlWidget& renderWidget )
: RenderGlShaders( renderWidget )
, m_RenderWidget( renderWidget )
, m_RenderKodiThread( new RenderKodiThread( nullptr ) )
{

}

//============================================================================
void RenderGlLogic::aboutToDestroy()
{
    setRenderThreadShouldRun( false );
    if( m_RenderKodiThread )
    {
        m_RenderKodiThread->quit(); // some platforms may not have windows to close so ensure quit()
        m_RenderKodiThread->wait();
        delete m_RenderKodiThread;
    }
}

//============================================================================
void RenderGlLogic::setRenderThreadShouldRun( bool shouldRun )
{
    if( m_RenderKodiThread )
    {
        m_RenderKodiThread->setRenderThreadShouldRun( shouldRun );
    }
}

//============================================================================
//! called from gui thread when ready for opengl rendering
void RenderGlLogic::glWidgetInitialized( )
{

    if( m_RenderKodiThread )
    {
        m_OffScreenSurface = new RenderGlOffScreenSurface( m_RenderKodiThread, &m_RenderWidget, m_WidgetGlContext ); // BRJ geometry not set at this point nullptr, geometry().size() );
        m_OffScreenSurface->setFormat( m_ThreadGlContext->format() );
        m_OffScreenSurface->create();
        m_OffScreenSurface->setRenderFunctions( m_GlThreadFunctions );

        // shader initialize must be done in gui thread
        initShaders();

        m_RenderWidget.moveToThread( m_RenderKodiThread );
        m_ThreadGlContext->moveToThread( m_RenderKodiThread );
        m_OffScreenSurface->moveToThread( m_RenderKodiThread );

        m_RenderKodiThread->start();
    }
}

//============================================================================
void RenderGlLogic::setSurfaceSize( QSize surfaceSize )
{
    if( m_OffScreenSurface )
    {
        m_OffScreenSurface->setSurfaceSize( surfaceSize );
    }
}

//============================================================================
// called from thread
void RenderGlLogic::render()
{
    QMutexLocker locker(&m_renderMutex);

    m_OffScreenSurface->makeCurrent();

    // do not call m_OffScreenSurface->size.. we want the frame buffer surface size
    QSize viewSize = m_OffScreenSurface->getSurfaceSize();

    locker.unlock();

    if (!m_initialized) {
        //initialize();
        m_initialized = true;
    }

    glViewport( 0, 0, viewSize.width(), viewSize.height() );

    //m_LogoRenderer.render();
}

Q_GLOBAL_STATIC(QMutex, initMutex)

//============================================================================
bool RenderGlLogic::initRenderGlSystem()
{
    if( m_OffScreenSurface )
    {
        m_OffScreenSurface->initRenderGlSystem();
        //m_LogoRenderer.initialize();
    }

    return true;
}

//============================================================================
bool RenderGlLogic::destroyRenderGlSystem()
{
    if( m_OffScreenSurface )
    {
        m_OffScreenSurface->destroyRenderGlSystem();
    }

    return true;
}

//============================================================================
bool RenderGlLogic::beginRenderGl()
{
    if( m_OffScreenSurface )
    {
        QMutexLocker locker(&m_renderMutex);

        m_OffScreenSurface->makeCurrent();

        // do not call m_OffScreenSurface->size.. we want the frame buffer surface size
        QSize viewSize = m_OffScreenSurface->getSurfaceSize();

        locker.unlock();

        if (!m_initialized) {
            //initialize();
            m_initialized = true;
        }

        glViewport( 0, 0, viewSize.width(), viewSize.height() );

        m_OffScreenSurface->beginRenderGl();
    }

    return true;
}

//============================================================================
bool RenderGlLogic::endRenderGl()
{
    render();

    if( m_OffScreenSurface )
    {
        m_OffScreenSurface->endRenderGl();
    }

    return true;
}

//============================================================================
void RenderGlLogic::presentRenderGl( bool rendered, bool videoLayer )
{
    if( m_OffScreenSurface )
    {
        m_OffScreenSurface->presentRenderGl( rendered, videoLayer );
        m_RenderWidget.onThreadFrameRendered();
    }
}

