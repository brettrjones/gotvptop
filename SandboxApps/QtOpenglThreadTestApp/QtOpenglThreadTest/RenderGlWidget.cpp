#include "RenderGlWidget.h"
#include "RenderGlThread.h"
#include "RenderGlOffScreenSurface.h"

#include <QPainter>
#include <GL/glu.h>
#include <VxDebug.h>

//============================================================================
#ifdef DEBUG
void  RenderGlWidget::VerifyGLStateQtDbg( const char* szfile, const char* szfunction, int lineno )
{
    GLenum err = glGetError();
    if( err == GL_NO_ERROR )
        return;
    LogMsg( LOG_ERROR, "GL ERROR: %d\n", err );
    if( szfile && szfunction )
    {
       LogMsg( LOG_ERROR, "In file:%s function:%s line:%d", szfile, szfunction, lineno );
    }

}
#else
void RenderGlWidget::VerifyGLStateQt()
{
    GLenum err = glGetError();
    if( err == GL_NO_ERROR )
        return;
    LogMsg( LOG_ERROR, "GL ERROR: %s\n", gluErrorString( err ) );
}
#endif

//============================================================================
RenderGlWidget::RenderGlWidget(QWidget *parent)
: QOpenGLWidget(parent)
{
    m_RendererLogic = new RenderGlLogic( *this );
    m_RendererGlThread = new RenderGlThread( *m_RendererLogic );
    m_RendererLogic->setRenderThread( m_RendererGlThread );

    setMinimumSize(20, 20);

    connect( m_RendererLogic, SIGNAL( signalFrameRendered() ), this, SLOT( slotOnFrameRendered() ) );
 
//    connect(this, &QOpenGLWidget::aboutToCompose, this, &RenderGlWidget::onAboutToCompose);
//    connect(this, &QOpenGLWidget::frameSwapped, this, &RenderGlWidget::onFrameSwapped);
//    connect(this, &QOpenGLWidget::aboutToResize, this, &RenderGlWidget::onAboutToResize);
//    connect(this, &QOpenGLWidget::resized, this, &RenderGlWidget::onResized);

}

//============================================================================
RenderGlWidget::~RenderGlWidget()
{
    m_RendererLogic->aboutToDestroy();
}

//============================================================================
void RenderGlWidget::takeSnapshot()
{
    if( m_WidgetGlInitialized && m_WidgetContext && m_RenderThreadSurface )
    {
        m_RendererLogic->lockRenderer();
        QImage frameImage = m_RenderThreadSurface->getLastRenderedImage();
        if( !frameImage.isNull() )
        {
            frameImage.save( QString( "F:\\ThreadTestOpenglImage.png" ) );
        }

        m_RendererLogic->unlockRenderer();
    }
}

//============================================================================
void RenderGlWidget::slotOnFrameRendered()
{
    update();
}

//============================================================================
void RenderGlWidget::onAboutToCompose()
{
    // We are on the gui thread here. Composition is about to
    // begin. Wait until the render thread finishes.
    m_RendererLogic->lockRenderer();
}

//============================================================================
void RenderGlWidget::onFrameSwapped()
{
    m_RendererLogic->unlockRenderer();
    // Assuming a blocking swap, our animation is driven purely by the
    // vsync in this example.
    emit renderRequested();
}

//============================================================================
void RenderGlWidget::onAboutToResize()
{
    m_RendererLogic->lockRenderer();
}

//============================================================================
void RenderGlWidget::onResized()
{
    m_RendererLogic->unlockRenderer();
}

//============================================================================
void RenderGlWidget::initializeGL()
{
    initializeOpenGLFunctions();
    m_WidgetContext = this->context();

    m_GlWidgetFunctions = m_WidgetContext->functions();
    Q_ASSERT( m_GlWidgetFunctions );
    m_GlWidgetFunctions->initializeOpenGLFunctions();

    m_RenderThreadGlContext = new QOpenGLContext;
    m_RenderThreadGlContext->setShareContext( m_WidgetContext ); // required or just get white logo with no animation
    m_RenderThreadGlContext->setFormat( m_WidgetContext->format() );
    m_RenderThreadGlContext->create();

    m_GlThreadFunctions = m_RenderThreadGlContext->functions();
    Q_ASSERT( m_GlThreadFunctions );
    m_GlThreadFunctions->initializeOpenGLFunctions();

    m_RenderThreadSurface = new RenderGlOffScreenSurface( m_RendererGlThread, this, m_WidgetContext, m_RenderThreadGlContext ); // BRJ geometry not set at this point nullptr, geometry().size() );
    m_RenderThreadSurface->setFormat( m_RenderThreadGlContext->format() );
    m_RenderThreadSurface->create();
    m_RenderThreadSurface->setRenderFunctions( m_GlThreadFunctions );

    m_RendererLogic->glWidgetInitialized( m_WidgetContext, m_RenderThreadGlContext, m_RenderThreadSurface );
    m_WidgetGlInitialized = true;
    doneCurrent();
}

//============================================================================
void RenderGlWidget::paintGL()
{
    if( m_WidgetGlInitialized && m_WidgetContext && m_RenderThreadSurface )
    {
        m_RendererLogic->lockRenderer();
        QImage frameImage = m_RenderThreadSurface->getLastRenderedImage();
        m_RendererLogic->unlockRenderer();

        QPainter painter;
        painter.begin( this );

        painter.setRenderHints( QPainter::Antialiasing );
        painter.drawImage( 0, 0, frameImage );

        painter.end();
  /*
        m_RendererLogic->lockRenderer();
        m_WidgetContext->makeCurrent( m_RenderThreadSurface );
        QOpenGLPaintDevice fboPaintDev( surfaceSize );
        QPainter painter( &fboPaintDev );
        //painter.setRenderHints( QPainter::Antialiasing | QPainter::TextAntialiasing );
        QImage frameImage = m_RenderThreadSurface->getLastRenderedImage();
        if( !frameImage.isNull() )
        {
            painter.drawImage( 0, 0, frameImage );
        }

        painter.end();

        m_RendererLogic->unlockRenderer();
        */

    }
}

//============================================================================
void RenderGlWidget::paintEvent( QPaintEvent * ev )
{
    QOpenGLWidget::paintEvent( ev );
    /*
    if( m_WidgetGlInitialized && m_WidgetContext && m_RenderThreadSurface )
    {
        QImage frameImage = m_RenderThreadSurface->getLastRenderedImage();
        if( !frameImage.isNull() )
        {
            QPainter painter;
            painter.begin( this );
            painter.setRenderHint( QPainter::Antialiasing );
            painter.drawImage( 0, 0, frameImage );
            painter.end();
        }
    }*/
}

//============================================================================
void RenderGlWidget::resizeGL( int width, int height )
{
    m_RendererLogic->setSurfaceSize( QSize( width, height ) );
}

//============================================================================
void RenderGlWidget::showEvent( QShowEvent * ev )
{
    QOpenGLWidget::showEvent( ev );
    m_RendererLogic->setRenderWindowVisible( true );
}

//============================================================================
void RenderGlWidget::hideEvent( QHideEvent * ev )
{
    m_RendererLogic->setRenderWindowVisible( false );
    QOpenGLWidget::hideEvent( ev );
}

//============================================================================
void RenderGlWidget::closeEvent( QCloseEvent * ev )
{
	m_RendererLogic->setRenderThreadShouldRun(false);
 
    QOpenGLWidget::closeEvent( ev );
}

//============================================================================
void RenderGlWidget::resizeEvent( QResizeEvent * ev )
{
    QOpenGLWidget::resizeEvent( ev );
    m_RendererLogic->setSurfaceSize( ev->size() );
}

//============================================================================
void RenderGlWidget::mousePressEvent( QMouseEvent * ev )
{
    QOpenGLWidget::mousePressEvent( ev );
}
