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

#include "RenderLogoShaders.h"
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


    virtual int                 getMaxTextureSize() { return 2048; }

    void                        aboutToDestroy();
signals:
    void                        signalFrameRendered();

public slots:
    void                        render();

private:
    RenderGlWidget&             m_RenderWidget;
    RenderLogoShaders           m_RenderShaders;
    LogoRenderer                m_LogoRenderer;

    QOpenGLContext *            m_WidgetGlContext = nullptr;
    QOpenGLContext *            m_ThreadGlContext = nullptr;
    RenderGlOffScreenSurface *  m_OffScreenSurface = nullptr;


    bool                        m_initialized   = false;
  
    QMutex                      m_renderMutex;
    bool                        m_exiting = false;

    QColor                      m_backgroundColor;
	RenderGlThread *			m_RenderThread = nullptr;
    bool                        m_RenderWindowVisible = false;
};

#endif // RENDERGLLOGIC_H