#ifndef RENDERGLLOGIC_H
#define RENDERGLLOGIC_H


#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QVector3D>
#include <QMatrix4x4>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QElapsedTimer>

#include "LogoRenderer.h"

class RenderGlWidget;
class RenderGlThread;
class RenderGlOffScreenSurface;


class RenderGlLogic : public QObject
{
    Q_OBJECT
public:
    explicit RenderGlLogic( RenderGlWidget& renderWidget );

    void						setRenderThread( RenderGlThread * renderThread ) { m_RenderThread = renderThread; }
    void						setRenderThreadShouldRun( bool shouldRun );
    void						setRenderWindowVisible( bool isVisible ) { m_RenderWindowVisible = isVisible; }

    //! called from gui thread when ready for opengl rendering
    void						glWidgetInitialized( QOpenGLContext * widgetGlContext, QOpenGLContext * threadGlContext, RenderGlOffScreenSurface * offScreenSurface );

    void                        setSurfaceSize( QSize surfaceSize );

    virtual bool                initRenderGlSystem();
    virtual bool                destroyRenderGlSystem();

    virtual bool                beginRenderGl();
    virtual bool                endRenderGl();
    virtual void                presentRenderGl( bool rendered, bool videoLayer );

    void                        lockRenderer() { m_renderMutex.lock(); }
    void                        unlockRenderer() { m_renderMutex.unlock(); }
    QMutex *                    grabMutex() { return &m_grabMutex; }
    QWaitCondition *            grabCond() { return &m_grabCond; }
    void                        prepareExit() { m_exiting = true; m_grabCond.wakeAll(); }

    virtual int                 getMaxTextureSize() { return 2048; }

signals:
    void                        signalFrameRendered();

public slots:
    void                        render();

private:
    RenderGlWidget&             m_RenderWidget;
    QOpenGLContext *            m_WidgetGlContext = nullptr;
    QOpenGLContext *            m_ThreadGlContext = nullptr;
    RenderGlOffScreenSurface *  m_OffScreenSurface = nullptr;

    LogoRenderer                m_LogoRenderer;

    bool                        m_initialized   = false;
  
    QMutex                      m_renderMutex;
    QMutex                      m_grabMutex;
    QWaitCondition              m_grabCond;
    bool                        m_exiting = false;

    QColor                      m_backgroundColor;
	RenderGlThread *			m_RenderThread = nullptr;
    bool                        m_RenderWindowVisible = false;
};

#endif // RENDERGLLOGIC_H
