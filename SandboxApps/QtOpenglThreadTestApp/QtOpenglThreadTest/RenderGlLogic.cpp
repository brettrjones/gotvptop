#include "RenderGlLogic.h"
#include "RenderGlWidget.h"
#include "RenderGlOffScreenSurface.h"

#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QRandomGenerator>
#include <QSurface>
#include <qmath.h>
#include <QTimer>

#include "VxDebug.h"
# if defined(TARGET_OS_APPLE)
#  include <OpenGLES/ES2/gl.h>
# elif defined(TARGET_OS_ANDROID)
#  include <GLES2/gl2.h>
#  include <GLES2/gl2ext.h>
#  include <GLES3/gl3.h>
# elif defined(TARGET_OS_LINUX)
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glext.h>
# elif defined(TARGET_OS_WINDOWS)
#  include <GL/gl.h>
#  include <GL/glu.h>
# endif // defined(TARGET_OS_ANDROID)


//============================================================================
RenderGlLogic::RenderGlLogic( RenderGlWidget& renderWidget, QWidget *parent )
: m_RenderWidget( renderWidget )
, m_RenderShaders( *this )
, m_LogoRenderer( m_RenderShaders )
{
    m_RendererGlThread = new RenderGlThread( *this );
}

//============================================================================
void RenderGlLogic::aboutToDestroy()
{
    setRenderThreadShouldRun( false );
    if( m_RendererGlThread )
    {
        m_RendererGlThread->quit(); // some platforms may not have windows to close so ensure quit()
        m_RendererGlThread->wait();
        delete m_RendererGlThread;
        m_RendererGlThread = nullptr;
    }
 }

//============================================================================
void RenderGlLogic::setRenderThreadShouldRun( bool shouldRun )
{
    if( m_RendererGlThread )
    {
        m_RendererGlThread->setRenderThreadShouldRun( shouldRun );
    }
}

//============================================================================
//! must be called from render thread
void RenderGlLogic::startRenderThread() 
{ 
    if( m_RendererGlThread )
    {
        m_RendererGlThread->startRenderThread();
    }
}

//============================================================================
//! must be called from render thread
void RenderGlLogic::initRenderContext()
{

    m_ThreadGlContext = new QOpenGLContext( this );
    QSurfaceFormat surfaceFormat = m_ThreadGlContext->format();
    surfaceFormat.setColorSpace( QSurfaceFormat::ColorSpace::sRGBColorSpace );
#ifndef TARGET_OS_ANDROID
    surfaceFormat.setRenderableType( QSurfaceFormat::RenderableType::OpenGL ); // QSurfaceFormat::RenderableType::OpenGLES );
#endif // TARGET_OS_ANDROID
    surfaceFormat.setSwapBehavior( QSurfaceFormat::SwapBehavior::DoubleBuffer );
    surfaceFormat.setAlphaBufferSize( 8 );
    surfaceFormat.setRedBufferSize( 8 );
    surfaceFormat.setGreenBufferSize( 8 );
    surfaceFormat.setBlueBufferSize( 8 );
    surfaceFormat.setDepthBufferSize( 24 );
    surfaceFormat.setStencilBufferSize( 8 );
    surfaceFormat.setSwapInterval( 1 );
    surfaceFormat.setSamples( 0 );


    m_ThreadGlContext->setFormat( surfaceFormat );
    m_ThreadGlContext->create();
    //m_ThreadGlContext->blockSignals( true );

    m_RenderThreadSurface = new RenderGlOffScreenSurface( this, &m_RenderWidget, m_ThreadGlContext ); // BRJ geometry not set at this point nullptr, geometry().size() );
    m_RenderThreadSurface->setFormat( surfaceFormat );
    m_RenderThreadSurface->create();
    //m_RenderThreadSurface->blockSignals( true );

    m_ThreadGlContext->makeCurrent( m_RenderThreadSurface );

    m_Glf = m_ThreadGlContext->functions();
    Q_ASSERT( m_Glf );
    m_Glf->initializeOpenGLFunctions();

    m_GlfExtra = m_ThreadGlContext->currentContext()->extraFunctions();
    Q_ASSERT( m_GlfExtra );
    if( m_GlfExtra )
    {
        m_GlfExtra->initializeOpenGLFunctions();
        m_Glf = m_GlfExtra;
    }

    m_RenderThreadSurface->setRenderFunctions( m_Glf, m_GlfExtra );

    glWidgetInitialized( m_ThreadGlContext, m_RenderThreadSurface );
    m_ThreadGlContext->doneCurrent();

    m_RenderInitialized = true;
}


//============================================================================
//! called from gui thread when ready for opengl rendering
void RenderGlLogic::glWidgetInitialized( QOpenGLContext * threadGlContext, RenderGlOffScreenSurface * renderSurface )
{
    m_ThreadGlContext = threadGlContext;
    m_RenderThreadSurface = renderSurface;

    // shader initialize must be done in gui thread
    m_RenderShaders.initLogoShaders( m_GlfExtra );
    m_RenderInitialized = true;
}

//============================================================================
void RenderGlLogic::setSurfaceSize( QSize surfaceSize )
{
    if( m_RenderThreadSurface 
        && surfaceSize.width() > 0
        && surfaceSize.height() > 0 )
    {
        m_RenderThreadSurface->setSurfaceSize( surfaceSize );
    }
}

//============================================================================
// called from thread
void RenderGlLogic::render()
{
    QMutexLocker locker(&m_renderMutex);

    m_RenderThreadSurface->makeCurrent();
  
    // do not call m_RenderThreadSurface->size.. we want the frame buffer surface size
    //QSize viewSize = m_RenderThreadSurface->getSurfaceSize();

    locker.unlock();

    //glViewport( 0, 0, viewSize.width(), viewSize.height() );

    m_LogoRenderer.render();
}

//============================================================================
bool RenderGlLogic::initRenderGlSystem()
{
    if( m_RenderThreadSurface )
    {
        m_RenderThreadSurface->initRenderGlSystem();
        m_LogoRenderer.initialize();
    }

    return true;
}

//============================================================================
bool RenderGlLogic::destroyRenderGlSystem()
{
    if( m_RenderThreadSurface )
    {
        m_RenderThreadSurface->destroyRenderGlSystem();
    }

    return true;
}

//============================================================================
bool RenderGlLogic::beginRenderGl()
{
    if( m_RenderThreadSurface )
    {
        m_RenderThreadSurface->beginRenderGl();
    }

    return true;
}

//============================================================================
bool RenderGlLogic::endRenderGl()
{
    render();

    if( m_RenderThreadSurface )
    {
        m_RenderThreadSurface->endRenderGl();
    }

    return true;
}

//============================================================================
void RenderGlLogic::presentRenderGl( bool rendered, bool videoLayer )
{
    if( m_RenderThreadSurface )
    {
        m_RenderThreadSurface->presentRenderGl( rendered, videoLayer );
        emit signalFrameRendered();
    }
}
 

//============================================================================
#ifdef DEBUG
void  RenderGlLogic::VerifyGLStateQtDbg( const char* szfile, const char* szfunction, int lineno )
{
    GLenum err = glGetError();
    if( err == GL_NO_ERROR )
        return;
    LogMsg( LOG_ERROR, "GL ERROR: %d thread %d %s\n", err, VxGetCurrentThreadId(), gluErrorString( err ) );
    if( szfile && szfunction )
    {
        LogMsg( LOG_ERROR, "In file:%s function:%s line:%d", szfile, szfunction, lineno );
    }

}
#else
void RenderGlLogic::VerifyGLStateQt()
{
    GLenum err = m_Glf->glGetError();
    if( err == GL_NO_ERROR )
        return;
#ifdef TARGET_OS_ANDROID
    LogMsg( LOG_ERROR, "GL ERROR: %s\n", err );
#else
    LogMsg( LOG_ERROR, "GL ERROR: %s\n", gluErrorString( err ) );
#endif // TARGET_OS_ANDROID
}
#endif
