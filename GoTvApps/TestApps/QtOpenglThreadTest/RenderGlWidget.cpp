#include "RenderGlWidget.h"
#include "RenderGlThread.h"
#include <QWindow>

RenderGlWidget::RenderGlWidget(QWidget *parent)
: QOpenGLWidget(parent)
{

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3, 2);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);

    setMinimumSize(300, 250);

    connect(this, &QOpenGLWidget::aboutToCompose, this, &RenderGlWidget::onAboutToCompose);
    connect(this, &QOpenGLWidget::frameSwapped, this, &RenderGlWidget::onFrameSwapped);
    connect(this, &QOpenGLWidget::aboutToResize, this, &RenderGlWidget::onAboutToResize);
    connect(this, &QOpenGLWidget::resized, this, &RenderGlWidget::onResized);

	m_RendererLogic = new RenderGlLogic( format );
	m_RendererGlThread = new RenderGlThread( *m_RendererLogic );
	m_RendererLogic->setRenderThread( m_RendererGlThread );

    setFormat(format);

    //create();

    updateColor();

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
void RenderGlWidget::grabContext()
{
    m_RendererLogic->lockRenderer();
    QMutexLocker lock(m_RendererLogic->grabMutex());
    //context()->moveToThread(m_thread);
    m_RendererLogic->grabCond()->wakeAll();
    m_RendererLogic->unlockRenderer();
}

//============================================================================
void RenderGlWidget::initializeGL()
{
    initializeOpenGLFunctions();
    m_WidgetContext = this->context();
    m_RendererLogic->glWidgetInitialized( m_WidgetContext  );
}

//============================================================================
void RenderGlWidget::paintGL()
{
    m_RendererLogic->beginRender();
    m_RendererLogic->endRender();
    m_RendererLogic->presentRender( true, false );

}

//============================================================================
void RenderGlWidget::resizeGL(int, int)
{
}

//============================================================================
void RenderGlWidget::showEvent( QShowEvent * ev )
{
    QWidget::showEvent( ev );
    m_RendererLogic->setAnimating( this, true );

    m_RendererLogic->render();
}

//============================================================================
void RenderGlWidget::hideEvent( QHideEvent * ev )
{
    m_RendererLogic->setAnimating( this, false );

    QWidget::hideEvent( ev );
}

//============================================================================
void RenderGlWidget::closeEvent( QCloseEvent * ev )
{
	m_RendererLogic->setRenderThreadShouldRun(false);
    m_RendererLogic->setAnimating( this, false );
    m_RendererLogic->destroyRenderSystem();

    QWidget::closeEvent( ev );

}

//============================================================================
void RenderGlWidget::resizeEvent( QResizeEvent * ev )
{
    QWidget::resizeEvent( ev );
}

//============================================================================
void RenderGlWidget::mousePressEvent(QMouseEvent *)
{
    updateColor();
}

//============================================================================
QColor RenderGlWidget::color() const
{
    QMutexLocker locker(&m_colorLock);
    return m_color;
}

//============================================================================
void RenderGlWidget::updateColor()
{
    QMutexLocker locker(&m_colorLock);

    QColor colors[] =
    {
        QColor(100, 255, 0),
        QColor(0, 100, 255)
    };

    m_color = colors[m_colorIndex];
    m_colorIndex = 1 - m_colorIndex;
}

