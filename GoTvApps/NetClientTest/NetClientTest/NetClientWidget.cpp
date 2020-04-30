#include "NetClientWidget.h"
#include "NetClientThread.h"
#include <QWindow>

NetClientWidget::NetClientWidget(QWidget *parent)
: QWidget(parent)
{
	m_RendererLogic = new NetClientLogic( format );
	m_RendererGlThread = new NetClientThread( *m_RendererLogic );
	m_RendererLogic->setRenderThread( m_RendererGlThread );

    setFormat(format);

    //create();

    updateColor();

}

//============================================================================
void NetClientWidget::onAboutToCompose()
{
    // We are on the gui thread here. Composition is about to
    // begin. Wait until the render thread finishes.
    m_RendererLogic->lockRenderer();
}

//============================================================================
void NetClientWidget::onFrameSwapped()
{
    m_RendererLogic->unlockRenderer();
    // Assuming a blocking swap, our animation is driven purely by the
    // vsync in this example.
    emit renderRequested();
}

//============================================================================
void NetClientWidget::onAboutToResize()
{
    m_RendererLogic->lockRenderer();
}

//============================================================================
void NetClientWidget::onResized()
{
    m_RendererLogic->unlockRenderer();
}

//============================================================================
void NetClientWidget::grabContext()
{
    m_RendererLogic->lockRenderer();
    QMutexLocker lock(m_RendererLogic->grabMutex());
    //context()->moveToThread(m_thread);
    m_RendererLogic->grabCond()->wakeAll();
    m_RendererLogic->unlockRenderer();
}

//============================================================================
void NetClientWidget::initializeGL()
{
    initializeOpenGLFunctions();
    m_WidgetContext = this->context();
    m_RendererLogic->glWidgetInitialized( m_WidgetContext  );
}

//============================================================================
void NetClientWidget::paintGL()
{
    m_RendererLogic->beginRender();
    m_RendererLogic->endRender();
    m_RendererLogic->presentRender( true, false );

}

//============================================================================
void NetClientWidget::resizeGL(int, int)
{
}

//============================================================================
void NetClientWidget::showEvent( QShowEvent * ev )
{
    QWidget::showEvent( ev );
    m_RendererLogic->setAnimating( this, true );

    m_RendererLogic->render();
}

//============================================================================
void NetClientWidget::hideEvent( QHideEvent * ev )
{
    m_RendererLogic->setAnimating( this, false );

    QWidget::hideEvent( ev );
}

//============================================================================
void NetClientWidget::closeEvent( QCloseEvent * ev )
{
	m_RendererLogic->setRenderThreadShouldRun(false);
    m_RendererLogic->setAnimating( this, false );
    m_RendererLogic->destroyRenderSystem();

    QWidget::closeEvent( ev );

}

//============================================================================
void NetClientWidget::resizeEvent( QResizeEvent * ev )
{
    QWidget::resizeEvent( ev );
}

//============================================================================
void NetClientWidget::mousePressEvent(QMouseEvent *)
{
    updateColor();
}

//============================================================================
QColor NetClientWidget::color() const
{
    QMutexLocker locker(&m_colorLock);
    return m_color;
}

//============================================================================
void NetClientWidget::updateColor()
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

