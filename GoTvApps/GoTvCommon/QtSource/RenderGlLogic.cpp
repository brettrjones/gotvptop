#include "RenderGlLogic.h"
#include "RenderKodiThread.h"
#include "RenderGlOffScreenSurface.h"
#include "RenderGlWidget.h"

//============================================================================
RenderGlLogic::RenderGlLogic( RenderGlWidget& renderWidget )
: QObject()
, m_RenderKodiThread( new RenderKodiThread( *this ) )
, m_RenderWidget( renderWidget )
, m_RenderGlShaders( renderWidget )
#ifdef RENDER_LOGO_INSTEAD_OF_KODI
, m_LogoShaders( renderWidget )
, m_LogoRenderer( m_LogoShaders )
#endif // RENDER_LOGO_INSTEAD_OF_KODI
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
bool RenderGlLogic::isRenderThreadStarted()
{
    return m_RenderKodiThread && m_RenderKodiThread->isRenderThreadStarted();
}

//============================================================================
void RenderGlLogic::startRenderThread()
{
    if( m_RenderKodiThread && !m_RenderKodiThread->isRenderThreadStarted() )
    {
        m_RenderKodiThread->startRenderThread();
    }
}

//============================================================================
void RenderGlLogic::stopRenderThread()
{
    if( m_RenderKodiThread && m_RenderKodiThread->isRenderThreadStarted() )
    {
        m_RenderKodiThread->stopRenderThread();
    }
}

//============================================================================
//! called from gui thread when ready for opengl rendering
void RenderGlLogic::glWidgetInitialized( )
{

    if( m_RenderKodiThread )
    {
         // shader initialize must be done in gui thread
#ifdef RENDER_LOGO_INSTEAD_OF_KODI
        m_LogoShaders.initLogoShaders();
#else
        m_RenderGlShaders.initShaders();
#endif // RENDER_LOGO_INSTEAD_OF_KODI

        moveToThread( m_RenderKodiThread );
        m_ThreadGlContext->moveToThread( m_RenderKodiThread );
        m_OffScreenSurface->moveToThread( m_RenderKodiThread );
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

#ifdef RENDER_LOGO_INSTEAD_OF_KODI
    m_LogoRenderer.render();
#endif // RENDER_LOGO_INSTEAD_OF_KODI
}

//============================================================================
bool RenderGlLogic::initRenderGlSystem()
{
    if( m_OffScreenSurface )
    {
        m_OffScreenSurface->initRenderGlSystem();
#ifdef RENDER_LOGO_INSTEAD_OF_KODI
        m_LogoRenderer.initialize();
#endif // RENDER_LOGO_INSTEAD_OF_KODI
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

        //QMutexLocker locker(&m_renderMutex);

        //m_OffScreenSurface->makeCurrent();

        // do not call m_OffScreenSurface->size.. we want the frame buffer surface size
        //QSize viewSize = m_OffScreenSurface->getSurfaceSize();

        //locker.unlock();

        if (!m_initialized) {
            //initialize();
            m_initialized = true;
        }

       // glViewport( 0, 0, viewSize.width(), viewSize.height() );


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
        emit signalFrameRendered();
    }
}

