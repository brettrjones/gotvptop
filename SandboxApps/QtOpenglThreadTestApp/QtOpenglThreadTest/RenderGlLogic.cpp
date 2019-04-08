#include "RenderGlLogic.h"
#include "RenderGlWidget.h"
#include "RenderGlOffscreenSurface.h"

#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QRandomGenerator>
#include <QSurface>
#include <qmath.h>
#include <QTimer>

//============================================================================
RenderGlLogic::RenderGlLogic( RenderGlWidget& renderWidget )
: m_RenderWidget( renderWidget )
{
    m_backgroundColor = QColor::fromRgbF(0.1f, 0.1f, 0.2f, 1.0f);
    m_backgroundColor.setRed(QRandomGenerator::global()->bounded(64));
    m_backgroundColor.setGreen(QRandomGenerator::global()->bounded(128));
    m_backgroundColor.setBlue(QRandomGenerator::global()->bounded(256)); 
}

//============================================================================
void RenderGlLogic::setRenderThreadShouldRun( bool shouldRun )
{
    if( m_RenderThread )
    {
        m_RenderThread->setRenderThreadShouldRun( shouldRun );
    }
}

//============================================================================
//! called from gui thread when ready for opengl rendering
void RenderGlLogic::glWidgetInitialized( QOpenGLContext * widgetGlContext, QOpenGLContext * threadGlContext, RenderGlOffScreenSurface * renderSurface )
{
    m_WidgetGlContext = widgetGlContext;
    m_ThreadGlContext = threadGlContext;
    m_OffScreenSurface = renderSurface;

    // shader initialize must be done in gui thread
    //m_RenderShaders.setGlContext( widgetGlContext );
    //m_RenderShaders.initShaders();

    if( m_RenderThread )
    {
        moveToThread( m_RenderThread );
        m_ThreadGlContext->moveToThread( m_RenderThread );
        m_OffScreenSurface->moveToThread( m_RenderThread );

        m_RenderThread->start();
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

    m_LogoRenderer.render();
}

Q_GLOBAL_STATIC(QMutex, initMutex)

//============================================================================
bool RenderGlLogic::initRenderGlSystem()
{
    if( m_OffScreenSurface )
    {
        m_OffScreenSurface->initRenderGlSystem();
        m_LogoRenderer.initialize();
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
 
