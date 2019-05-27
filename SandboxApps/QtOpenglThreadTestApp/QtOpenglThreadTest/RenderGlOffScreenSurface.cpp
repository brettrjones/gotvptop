#include "RenderGlOffScreenSurface.h"
#include "RenderGlThread.h"
#include "RenderGlWidget.h"
#include "VxDebug.h"

#include <QtCore/QCoreApplication>
#include <QtGui/QPainter>

//============================================================================
RenderGlOffScreenSurface::RenderGlOffScreenSurface( RenderGlLogic * renderLogic,
													RenderGlWidget * glWidget,
                                                    QOpenGLContext* renderThreadContext,
                                                    QScreen* targetScreen, 
                                                    const QSize& size )
: QOffscreenSurface( targetScreen )
, m_RenderGlLogic( renderLogic )
, m_GlWidget( glWidget )
, m_initialized( false )
, m_updatePending( false )
, m_RenderThreadContext( renderThreadContext )
, m_SurfaceSize( size )
, m_NextSurfaceSize( size )
, m_TestTexure1( -1 )
{
}

//============================================================================
RenderGlOffScreenSurface::~RenderGlOffScreenSurface()
{
    // to delete the FBOs we first need to make the context current
    m_RenderThreadContext->makeCurrent( this );
    // destroy framebuffer objects
    if( m_fbo ) 
    {
        m_fbo->release();
        delete m_fbo;
        m_fbo = nullptr;
    }

    if( m_resolvedFbo ) 
    {
        m_resolvedFbo->release();
        delete m_resolvedFbo;
        m_resolvedFbo = nullptr;
    }

    // destroy shader
    delete m_blitShader;
    m_blitShader = nullptr;
    // free context
    m_RenderThreadContext->doneCurrent();
    delete m_RenderThreadContext;
    m_RenderThreadContext = nullptr;
    // gui will clean up its own context
    m_initialized = false;
    m_updatePending = false;
    destroy();
}

//============================================================================
void RenderGlOffScreenSurface::setSurfaceSize( QSize surfaceSize )
{
    m_mutex.lock();
    m_NextSurfaceSize = surfaceSize;
    m_mutex.unlock();
}

//============================================================================
// called from kodi thread
void RenderGlOffScreenSurface::initRenderGlSystem()
{
	m_RenderThreadContext->makeCurrent( this );
    initializeInternal();
	m_RenderSystemInitialized = true;
}

//============================================================================
// called from kodi thread
void RenderGlOffScreenSurface::destroyRenderGlSystem()
{
    m_RenderSystemInitialized = false;
    m_RenderThreadContext->makeCurrent( this );
    // free old FBOs
    if( m_fbo )
    {
        m_fbo->release();
        delete m_fbo;
        m_fbo = nullptr;
    }

    if( m_resolvedFbo )
    {
        m_resolvedFbo->release();
        delete m_resolvedFbo;
        m_resolvedFbo = nullptr;
    }

    m_RenderThreadContext->makeCurrent( 0 );
}

//============================================================================
// called from thread
bool RenderGlOffScreenSurface::beginRenderGl()
{
    m_updatePending = true;
    m_RenderGlLogic->VerifyGLStateQt();

    if( m_Glf && !m_initialized )
    {
        // initialize for render
        initializeInternal();
    }

    //LogMsg( LOG_DEBUG, " RenderGlOffScreenSurface::beginRender size x(%d) y(%d)", m_SurfaceSize.width(), m_SurfaceSize.height() );
    // make context current and bind framebuffer
    makeCurrent();
    checkForSizeChange();

    bindFramebufferObject();
    if( m_RenderThreadContext )
    {
        m_Glf->glViewport( 0, 0, getSurfaceSize().width(), getSurfaceSize().height() );
    }

    //testTexureRender( true );

    return true;
}

//============================================================================
// called from thread
bool RenderGlOffScreenSurface::endRenderGl()
{
    return true;
}

//============================================================================
// called from thread
void RenderGlOffScreenSurface::presentRenderGl( bool rendered, bool videoLayer )
{
    // order of execution
    // beginRender
    // endRender
    // presentRender
    m_RenderGlLogic->VerifyGLStateQt();

    // LogMsg( LOG_DEBUG, " RenderGlOffScreenSurface::endRender swapBuffers" );
    if( m_Glf && m_initialized )
    {
        // make sure all paint operation have been processed
        m_RenderGlLogic->VerifyGLStateQt();
        m_Glf->glFlush();
        m_RenderGlLogic->VerifyGLStateQt();

        if( rendered )
        {
  
            m_RenderGlLogic->VerifyGLStateQt();
            QImage image = grabFramebuffer();
            m_RenderGlLogic->setLastRenderedImage( image );
            m_RenderGlLogic->VerifyGLStateQt();
            //swapBuffers();
            m_RenderGlLogic->VerifyGLStateQt();

            checkForSizeChange();
            m_RenderGlLogic->VerifyGLStateQt();

			doneCurrent();
		}

        //LogMsg( LOG_DEBUG, " RenderGlOffScreenSurface::presentRender done size x(%d) y(%d)", m_SurfaceSize.width(), m_SurfaceSize.height() );
    }

    // mark that we're done with updating
    m_updatePending = false;
    // LogMsg( LOG_DEBUG, " RenderGlOffScreenSurface::endRender size x(%d) y(%d)", m_SurfaceSize.width(), m_SurfaceSize.height() );
}

//============================================================================
/// @brief return true if has been initialized from kodi thread
bool RenderGlOffScreenSurface::isReadyForRender()
{
    return( m_initialized && m_RenderSystemInitialized );
}

//============================================================================
// called from thread
void RenderGlOffScreenSurface::testTexureRender( bool startRender )
{
    if( !isValid() )
    {
        return;
    }

    if( startRender )
    {
        //glShadeModel( GL_FLAT );
        //glEnable( GL_DEPTH_TEST );
        glEnable( GL_TEXTURE_2D );

        if( m_TestTexure1 == -1 )
        {
            m_TestTexure1 = 0;
            glGenTextures( 1, &m_TestTexure1 );
        }

        glBindTexture( GL_TEXTURE_2D, m_TestTexure1 );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

        // Black/white checkerboard
#define checkImageWidth 4
#define checkImageHeight 4
        static GLubyte checkImage[ checkImageHeight ][ checkImageWidth ][ 4 ];
        static bool checkerImageInitialize = false;
        if( !checkerImageInitialize )
        {
            checkerImageInitialize = true;
            int i, j, c;

            for( i = 0; i < checkImageHeight; i++ ) 
            {
                for( j = 0; j < checkImageWidth; j++ ) 
                {
                     if( ( ( i & 0x01 ) && ( j & 0x01 ) ) 
                        || ( ( 0 == ( i & 0x01 ) ) && ( 0 == ( j & 0x01 ) ) ) )
                    {
                        c = 255;
                    }
                    else
                    {
                        c = 0;
                    }

                    checkImage[ i ][ j ][ 0 ] = ( GLubyte )c;
                    checkImage[ i ][ j ][ 1 ] = ( GLubyte )c;
                    checkImage[ i ][ j ][ 2 ] = ( GLubyte )c;
                    checkImage[ i ][ j ][ 3 ] = ( GLubyte )255;
                }
            }
        }

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage );

#if !defined(QT_OPENGL_ES_2)
        glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );
        glBegin( GL_QUADS );
            glTexCoord2f( 0.0, 0.0 ); glVertex3f( -0.5, -0.5, 0.0 );
            glTexCoord2f( 0.0, 1.0 ); glVertex3f( -0.5, 1.0, 0.0 );
            glTexCoord2f( 1.0, 1.0 ); glVertex3f( 1.0, 1.0, 0.0 );
            glTexCoord2f( 1.0, 0.0 ); glVertex3f( 1.0, -0.5, 0.0 );
        glEnd();
#else
 // figure out equivilent for gles


#endif


    }
}

//============================================================================
/// @doc must be called from render thread
void RenderGlOffScreenSurface::setRenderFunctions( QOpenGLFunctions * glFunctions, QOpenGLExtraFunctions* glExtraFunctions )
{
    m_Glf = glFunctions;
    m_GlfExtra = glExtraFunctions;
}

//============================================================================
/// @brief  change surface size in thread if required
void RenderGlOffScreenSurface::checkForSizeChange()
{
    if( m_NextSurfaceSize != m_SurfaceSize )
    {
        m_SurfaceSize = m_NextSurfaceSize;

        recreateFBOAndPaintDevice();
    }
}

//============================================================================
QOpenGLFunctions* RenderGlOffScreenSurface::functions() const
{
    return ( m_Glf );
}

//============================================================================
GLuint RenderGlOffScreenSurface::framebufferObjectHandle() const
{
    return ( m_fbo ? m_fbo->handle() : 0 );
}

//============================================================================
const QOpenGLFramebufferObject* RenderGlOffScreenSurface::getFramebufferObject() const
{
    return ( m_fbo );
}

//============================================================================
void RenderGlOffScreenSurface::bindFramebufferObject()
{
    if( m_fbo ) 
    {
        m_fbo->bind();
    }
    else 
    {
        QOpenGLFramebufferObject::bindDefault();
    }
}

//============================================================================
bool RenderGlOffScreenSurface::isValid() const
{
    return ( m_initialized && m_RenderThreadContext && m_fbo );
}

//============================================================================
void RenderGlOffScreenSurface::makeCurrent()
{
    if( m_RenderThreadContext )
    {
        m_RenderThreadContext->makeCurrent( this );
    }
    else
    {
        throw ( "RenderGlOffScreenSurface::makeCurrent() - Window not yet properly initialized!" );
    }
}

//============================================================================
void RenderGlOffScreenSurface::doneCurrent()
{
    if( m_RenderThreadContext )
    {
        m_RenderThreadContext->doneCurrent();
    }
}

//============================================================================
QImage RenderGlOffScreenSurface::grabFramebuffer()
{
    std::lock_guard <std::mutex> locker( m_mutex );
    m_RenderGlLogic->VerifyGLStateQt();

    makeCurrent();
    m_RenderGlLogic->VerifyGLStateQt();

    // blit framebuffer to resolve framebuffer first if needed
    if( m_fbo->format().samples() > 0 ) 
    {
        // check if we have glFrameBufferBlit support. this is true for desktop OpenGL 3.0+, but not
        // OpenGL ES 2.0
#ifndef TARGET_OS_ANDROID
        if( m_GlfExtra )
        {
            // only blit the color buffer attachment
            m_GlfExtra->glBindFramebuffer( GL_READ_FRAMEBUFFER, m_fbo->handle() );
            m_GlfExtra->glBindFramebuffer( GL_DRAW_FRAMEBUFFER, m_resolvedFbo->handle() );
            m_GlfExtra->glBlitFramebuffer( 0, 0,
                                                getSurfaceSize().width(), getSurfaceSize().height(),
                                                0, 0,
                                                getSurfaceSize().width(), getSurfaceSize().height(),
                                                GL_COLOR_BUFFER_BIT, GL_NEAREST );

            m_GlfExtra->glBindFramebuffer( GL_FRAMEBUFFER, 0 );
        }
        else
#endif // TARGET_OS_ANDROID
        {
            // we must unbind the FBO here, so we can use its texture and bind the default
            // back-buffer
            m_Glf->glBindFramebuffer( GL_FRAMEBUFFER, m_resolvedFbo->handle() );
            // now use its texture for drawing in the shader
            // --> bind shader and draw textured quad here
            // bind regular FBO again
            m_Glf->glBindFramebuffer( GL_FRAMEBUFFER, m_fbo->handle() );
        }

        // check if OpenGL errors happened
        if( GLenum error = m_Glf->glGetError() != GL_NO_ERROR )
        {
            qDebug() << "RenderGlOffScreenSurface::grabFramebuffer() - OpenGL error" << error;
        }

        // now grab from resolve FBO
        return ( grabFramebufferInternal( m_resolvedFbo ) );
    }
    else 
    {
        // no multi-sampling. grab directly from FBO
        return ( grabFramebufferInternal( m_fbo ) );
    }

}  // RenderGlOffScreenSurface::grabFramebuffer

//============================================================================
QImage RenderGlOffScreenSurface::grabFramebufferInternal( QOpenGLFramebufferObject* fbo )
{
    m_RenderGlLogic->VerifyGLStateQt();

    QImage image;
#if !defined(QT_OPENGL_ES_2)
    // bind framebuffer first
    m_Glf->glBindFramebuffer( GL_READ_FRAMEBUFFER, fbo->handle() );

    m_RenderGlLogic->VerifyGLStateQt();

#if 0 // this causes error in windows
    if( m_GlfExtra )
    {
        m_GlfExtra->glReadBuffer( GL_COLOR_ATTACHMENT0 );
    }
#endif // 0

    m_RenderGlLogic->VerifyGLStateQt();

    GLenum internalFormat = fbo->format().internalTextureFormat();
    bool hasAlpha = internalFormat == GL_RGBA || internalFormat == GL_BGRA
        || internalFormat == GL_RGBA8;
    if( internalFormat == GL_BGRA )
    {
        image = QImage( fbo->size(), hasAlpha ? QImage::Format_ARGB32 : QImage::Format_RGB32 );
        m_Glf->glReadPixels( 0, 0, getSurfaceSize().width(),
            getSurfaceSize().height(), GL_BGRA, GL_UNSIGNED_BYTE, image.bits() );
    }
    else if( ( internalFormat == GL_RGBA ) || ( internalFormat == GL_RGBA8 ) )
    {
        int width = fbo->size().width();
        int height = fbo->size().height();

        image = QImage( fbo->size(), hasAlpha ? QImage::Format_RGBA8888 : QImage::Format_RGBX8888 );
        m_Glf->glReadPixels( 0, 0, getSurfaceSize().width(),
            getSurfaceSize().height(), GL_RGBA, GL_UNSIGNED_BYTE, image.bits() );
       //LogMsg( LOG_DEBUG, "fbo w %d h %d surface w %d h %d image w %d h %d\n", 
       //    width, height,
       //    m_SurfaceSize.width(), m_SurfaceSize.height(), 
       //    image.width(), image.height() );
    }
    else
    {
        qDebug() << "RenderGlOffScreenSurface::grabFramebuffer() - Unsupported framebuffer format"
            << internalFormat << "!";
    }
#else
    image = m_fbo->toImage();
#endif // !defined(QT_OPENGL_ES_2)
    m_RenderGlLogic->VerifyGLStateQt();

    m_Glf->glBindFramebuffer( GL_FRAMEBUFFER, m_fbo->handle() );
    m_Glf->glViewport( 0, 0, m_SurfaceSize.width(), m_SurfaceSize.height() );
    m_RenderGlLogic->VerifyGLStateQt();

//    m_GlWidget->VerifyGLStateQt();

    return ( image.mirrored() );
}  // RenderGlOffScreenSurface::grabFramebufferInternal

//============================================================================
void RenderGlOffScreenSurface::swapBuffers()
{
    swapBuffersInternal();
    //emit frameSwapped();
}

//============================================================================
void RenderGlOffScreenSurface::swapBuffersInternal()
{
    // check if OpenGL errors happened
    m_RenderGlLogic->VerifyGLStateQt();

    // blit framebuffer to back buffer
    //makeCurrent();
    // make sure all paint operation have been processed
    //m_Glf->glFlush();
    // check if we have glFrameBufferBlit support. this is true for desktop OpenGL 3.0+, but not
    // OpenGL ES 2.0
#if !defined(QT_OPENGL_ES_2)
    if( m_GlfExtra )
    {
        // if our framebuffer has multi-sampling, the resolve should be done automagically
        m_GlfExtra->glBindFramebuffer( GL_READ_FRAMEBUFFER, m_fbo->handle() );
        m_GlfExtra->glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 );
        // blit all buffers including depth buffer for further rendering
        m_GlfExtra->glBlitFramebuffer( 0, 0, getSurfaceSize().width(),
                                            getSurfaceSize().height(), 0, 0, getSurfaceSize().width(),
                                            getSurfaceSize().height(), GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
                                            GL_NEAREST );
        m_GlfExtra->glBindFramebuffer( GL_FRAMEBUFFER, m_fbo->handle() );
    }
    else
#endif // !defined(QT_OPENGL_ES_2)
    {
        // we must unbind the FBO here, so we can use its texture and bind the default back-buffer
        m_Glf->glBindFramebuffer( GL_FRAMEBUFFER, 0 );
        // now use its texture for drawing in the shader
        // --> bind shader and draw textured quad here
        // bind regular FBO again
        m_Glf->glBindFramebuffer( GL_FRAMEBUFFER, m_fbo->handle() );
    }

    // check if OpenGL errors happened
    m_RenderGlLogic->VerifyGLStateQt();

    // now swap back buffer to front buffer
    m_RenderThreadContext->swapBuffers( this );
}  // RenderGlOffScreenSurface::swapBuffersInternal

//============================================================================
void RenderGlOffScreenSurface::recreateFBOAndPaintDevice()
{
    if( m_RenderThreadContext && ( ( m_fbo == nullptr ) || ( m_fbo->size() != getSurfaceSize() ) ) )
    {
        m_RenderThreadContext->makeCurrent( this );
        // free old FBOs
        if( m_fbo ) 
        {
            m_fbo->release();
            delete m_fbo;
            m_fbo = nullptr;
        }

        if( m_resolvedFbo ) 
        {
            m_resolvedFbo->release();
            delete m_resolvedFbo;
            m_resolvedFbo = nullptr;
        }

        // create new frame buffer
//        QOpenGLFramebufferObjectFormat format = QGLInfo::DefaultFramebufferFormat();
//        format.setSamples(QGLInfo::HasMultisamplingSupport(m_context) ? 4 : 0);
        QOpenGLFramebufferObjectFormat format;
        format.setSamples( 0 );

        m_fbo = new QOpenGLFramebufferObject( getSurfaceSize(), format );
        if( !m_fbo->isValid() ) 
        {
            throw ( "RenderGlOffScreenSurface::recreateFbo() - Failed to create background FBO!" );
        }

        // clear framebuffer
        m_fbo->bind();
        m_Glf->glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
        m_fbo->release();
        // if multi sampling is requested and supported we need a resolve FBO
        if( format.samples() > 0 ) 
        {
            // create resolve framebuffer with only a color attachment
            format.setAttachment( QOpenGLFramebufferObject::NoAttachment );
            format.setSamples( 0 );
            m_resolvedFbo = new QOpenGLFramebufferObject( getSurfaceSize(), format );
            if( !m_resolvedFbo->isValid() ) 
            {
                throw ( "RenderGlOffScreenSurface::recreateFbo() - Failed to create resolve FBO!" );
            }

            // clear resolve framebuffer
            m_resolvedFbo->bind();
            m_Glf->glClear( GL_COLOR_BUFFER_BIT );
            m_resolvedFbo->release();
        }
    }
} 

//============================================================================
void RenderGlOffScreenSurface::initializeInternal()
{
    if( m_RenderThreadContext && !m_initialized.exchange( true ) )
    {
        // now we have a context, create the FBO

        recreateFBOAndPaintDevice();
    }
}  

//============================================================================
void RenderGlOffScreenSurface::update()
{
    // only queue an update if there's not already an update pending
    if( !m_updatePending.exchange( true ) ) 
    {
        QCoreApplication::postEvent( this, new QEvent( QEvent::UpdateRequest ) );
    }
}

//============================================================================
void RenderGlOffScreenSurface::render(  )
{
	// never gets called
    std::lock_guard <std::mutex> locker( m_mutex );
    // check if we need to initialize stuff
    initializeInternal();

    // make context current and bind framebuffer
    makeCurrent();
    bindFramebufferObject();

    // call user paint function
    doneCurrent();

    // mark that we're done with updating
    m_updatePending = false;
}  // RenderGlOffScreenSurface::render

//============================================================================
void RenderGlOffScreenSurface::exposeEvent( QExposeEvent*  )
{
    // render window content if window is exposed
    //render();
}  // RenderGlOffScreenSurface::exposeEvent

//============================================================================
bool RenderGlOffScreenSurface::event( QEvent* event )
{
    switch( event->type() ) 
    {
    case QEvent::UpdateLater:
        update(); // never gets called
        return ( true );

    case QEvent::UpdateRequest:
        render(); // never gets called
        return ( true );

	case QEvent::PlatformSurface:
	default:
        return ( false );
    }  // switch

}  
