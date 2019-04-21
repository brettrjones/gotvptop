#ifndef RENDERGLLOGIC_H
#define RENDERGLLOGIC_H

#include "config_gotvapps.h"

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

#include "RenderGlShaders.h"
#include "RenderLogoShaders.h"
#include "LogoRenderer.h"

// uncomment to render qt logo as test instead of running kodi
//#define RENDER_LOGO_INSTEAD_OF_KODI

class RenderGlWidget;
class RenderKodiThread;
class RenderGlOffScreenSurface;

class RenderGlLogic : public QObject
{
    Q_OBJECT
public:
    explicit RenderGlLogic( RenderGlWidget& renderWidget );
    virtual ~RenderGlLogic() = default;

    void						setRenderWindowVisible( bool isVisible ) { m_RenderWindowVisible = isVisible; }

    void						setRenderThreadShouldRun( bool shouldRun );
    bool						isRenderThreadStarted();
    void						startRenderThread();
    void						stopRenderThread();

    //! called from gui thread when ready for opengl rendering
    void						glWidgetInitialized();

    void                        setSurfaceSize( QSize surfaceSize );

    virtual bool                initRenderGlSystem();
    virtual bool                destroyRenderGlSystem();

    virtual bool                beginRenderGl();
    virtual bool                endRenderGl();
    virtual void                presentRenderGl( bool rendered, bool videoLayer );

    void                        lockRenderer() { m_renderMutex.lock(); }
    void                        unlockRenderer() { m_renderMutex.unlock(); }

    void                        aboutToDestroy();

    // initialized by RenderGlWidget
    QOpenGLContext *            m_WidgetGlContext = nullptr;
    // initialized by RenderGlWidget
    QOpenGLContext *            m_ThreadGlContext = nullptr;
    // initialized by RenderGlWidget
    RenderGlOffScreenSurface *  m_OffScreenSurface = nullptr;

    RenderKodiThread*           m_RenderKodiThread = nullptr;

    RenderGlWidget&             m_RenderWidget;
    RenderGlShaders             m_RenderGlShaders;

signals:
    void                        signalFrameRendered();

protected:
    void                        render();


#ifdef RENDER_LOGO_INSTEAD_OF_KODI
    RenderLogoShaders           m_LogoShaders;
    LogoRenderer                m_LogoRenderer;
#endif // RENDER_LOGO_INSTEAD_OF_KODI

    bool                        m_initialized   = false;

    QMutex                      m_renderMutex;
    QMutex                      m_grabMutex;
    QWaitCondition              m_grabCond;
    bool                        m_exiting = false;

    bool                        m_RenderWindowVisible = false;
};

#endif // RENDERGLLOGIC_H
