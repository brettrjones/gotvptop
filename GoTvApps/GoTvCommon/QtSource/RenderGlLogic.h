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

#include "RenderGlShaders.h"

class RenderGlWidget;
class RenderKodiThread;
class RenderGlOffScreenSurface;


class RenderGlLogic : public RenderGlShaders
{
public:
    explicit RenderGlLogic( RenderGlWidget& renderWidget );
    virtual ~RenderGlLogic() = default;

    void						setRenderThreadShouldRun( bool shouldRun );
    void						setRenderWindowVisible( bool isVisible ) {  }

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

    RenderGlOffScreenSurface *  m_OffScreenSurface = nullptr;

protected:
    void                        render();

    RenderGlWidget&             m_RenderWidget;

    RenderKodiThread*           m_RenderKodiThread = nullptr;

    bool                        m_initialized   = false;

    QMutex                      m_renderMutex;
    QMutex                      m_grabMutex;
    QWaitCondition              m_grabCond;
    bool                        m_exiting = false;

    bool                        m_RenderWindowVisible = false;
};

#endif // RENDERGLLOGIC_H
