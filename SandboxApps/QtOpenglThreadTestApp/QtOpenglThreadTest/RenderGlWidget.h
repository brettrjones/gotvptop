#ifndef RENDERGLWIDGET_H
#define RENDERGLWIDGET_H

#include "RenderGlThread.h"
#include "RenderGlLogic.h"

#include <QEvent>
#include <QOpenGLWidget>
#include <QOpenGLFramebufferObject>

class RenderGlOffScreenSurface;

class RenderGlWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit RenderGlWidget(QWidget *parent = nullptr);
    virtual ~RenderGlWidget() override;

    QOpenGLContext *			getContext( void )              { return m_WidgetContext; }

    QOpenGLFunctions *          getGlFunctions() { return m_GlWidgetFunctions; }

#ifdef DEBUG
    void VerifyGLStateQtDbg( const char* szfile, const char* szfunction, int lineno );
#  define VerifyGLStateQt() VerifyGLStateQtDbg(__FILE__, __FUNCTION__, __LINE__)
#else
    void VerifyGLStateQt();
#endif

    void                        takeSnapshot();

signals:
    void                        renderRequested();

public slots:
    void                        slotOnFrameRendered();

private slots:
    void                        onAboutToCompose();
    void                        onFrameSwapped();
    void                        onAboutToResize();
    void                        onResized();

protected:
    void                        initializeGL() override;
    void                        paintGL() override;
    void                        resizeGL(int, int) override;

    void                        paintEvent( QPaintEvent * ) override;

    virtual void				showEvent( QShowEvent * ev );
    virtual void				hideEvent( QHideEvent * ev );
    virtual void				closeEvent( QCloseEvent * ev );
    virtual void				resizeEvent( QResizeEvent * ev );

    virtual void                mousePressEvent(QMouseEvent *) override;

    int                         m_colorIndex = 0;
    QColor                      m_color;
	RenderGlThread *            m_RendererGlThread = nullptr;
    RenderGlLogic *             m_RendererLogic = nullptr;
    mutable QMutex              m_colorLock;
    QOpenGLContext *            m_WidgetContext = nullptr;
    QOpenGLContext *            m_RenderThreadGlContext = nullptr;


    RenderGlOffScreenSurface *  m_RenderThreadSurface = nullptr;
    QOpenGLContext *            m_ThreadGlContext = nullptr;

    QOpenGLFramebufferObject *  m_ThreadGlFbo = nullptr;
    QOpenGLFramebufferObject *  m_WidgetFbo = nullptr;

    QOpenGLFunctions *          m_GlWidgetFunctions = nullptr;

    QOpenGLFunctions *          m_GlThreadFunctions = nullptr;
#if QT_VERSION < 0x050300
# if defined(QT_OPENGL_ES_2)
    QOpenGLFunctions_ES2 *      m_ThreadGlF = nullptr;
# else
    QOpenGLFunctions_1_1 *      m_ThreadGlF = nullptr;
# endif
#else
    QOpenGLFunctions *          m_ThreadGlF = nullptr;

#endif
    bool                        m_WidgetGlInitialized = false;
};

#endif // RENDERGLWIDGET_H
