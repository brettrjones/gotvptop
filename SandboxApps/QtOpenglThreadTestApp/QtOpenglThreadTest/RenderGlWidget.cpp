#include "RenderGlWidget.h"
#include "RenderGlThread.h"
#include "RenderGlOffScreenSurface.h"

#include <QPainter>
#include <QCoreApplication>

#include <GL/glu.h>
#include <VxDebug.h>


//============================================================================
RenderGlWidget::RenderGlWidget(QWidget *parent)
: RenderGlLogic( *this, parent )
{
    //setMinimumSize(20, 20);

    connect( this, SIGNAL( signalFrameRendered() ), this, SLOT( slotOnFrameRendered() ) );
    initRenderContext();

}

//============================================================================
RenderGlWidget::~RenderGlWidget()
{
    aboutToDestroy();
}

//============================================================================
void RenderGlWidget::takeSnapshot()
{
    if( m_WidgetGlInitialized && getIsRenderInitialized() )
    {
        lockRenderer();
        QImage frameImage = getLastRenderedImage();
        if( !frameImage.isNull() )
        {
            frameImage.save( QString( "F:\\ThreadTestOpenglImage.png" ) );
        }

        unlockRenderer();
    }
}

//============================================================================
void RenderGlWidget::slotOnFrameRendered()
{
   update();
}
/*
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
  
    }
}
*/
//============================================================================

void RenderGlWidget::paintEvent( QPaintEvent * ev )
{
    QWidget::paintEvent( ev );

    if( getIsRenderInitialized() )
    {
        QImage frameImage = getLastRenderedImage();
        if( !frameImage.isNull() )
        {
            QPainter painter;
            painter.begin( this );
            painter.setRenderHint( QPainter::Antialiasing );
            painter.drawImage( 0, 0, frameImage );
            painter.end();
        }
    }
}


//============================================================================
void RenderGlWidget::showEvent( QShowEvent * ev )
{
    QWidget::showEvent( ev );

    setRenderWindowVisible( true );
    startRenderThread();
}

//============================================================================
void RenderGlWidget::hideEvent( QHideEvent * ev )
{
    setRenderWindowVisible( false );
    static bool destroyCalled = false;
    if( !destroyCalled )
    {
        destroyCalled = true;
        aboutToDestroy();
    }
    QWidget::hideEvent( ev );
}

//============================================================================

void RenderGlWidget::closeEvent( QCloseEvent * ev )
{
    QWidget::closeEvent( ev );
}

//============================================================================
void RenderGlWidget::resizeEvent( QResizeEvent * ev )
{
    QWidget::resizeEvent( ev );
    setSurfaceSize( ev->size() );
}

//============================================================================
void RenderGlWidget::mousePressEvent( QMouseEvent * ev )
{
    QWidget::mousePressEvent( ev );
}
