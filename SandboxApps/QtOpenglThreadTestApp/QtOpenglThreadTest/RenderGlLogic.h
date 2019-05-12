#ifndef RENDERGLLOGIC_H
#define RENDERGLLOGIC_H


#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>

#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QVector3D>
#include <QMatrix4x4>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QElapsedTimer>
#include <QWindow>
#include <QOpenGLWidget>

#include "RenderLogoShaders.h"
#include "RenderGlThread.h"

#include "LogoRenderer.h"

class RenderGlWidget;
class RenderGlThread;
class RenderGlOffScreenSurface;


class RenderGlLogic : public QWidget
{
    Q_OBJECT
public:
    explicit RenderGlLogic( RenderGlWidget& renderWidget, QWidget *parent );

#ifdef DEBUG
    void VerifyGLStateQtDbg( const char* szfile, const char* szfunction, int lineno );
#  define VerifyGLStateQt() VerifyGLStateQtDbg(__FILE__, __FUNCTION__, __LINE__)
#else
    void VerifyGLStateQt();
#endif

    void                        setLastRenderedImage( QImage& image ){ m_renderMutex.lock();  m_LastRenderedImage = image;  m_renderMutex.unlock(); }
    QImage                      getLastRenderedImage()
    {
        m_renderMutex.lock();
        QImage retImage = m_LastRenderedImage;
        m_renderMutex.unlock();
        return retImage;
    }

    QOpenGLFunctions *          getGlFunctions() { return m_Glf; }

    void						setRenderThreadShouldRun( bool shouldRun );
    void						setRenderWindowVisible( bool isVisible ) { m_RenderWindowVisible = isVisible; }

    bool                        getIsRenderInitialized() { return m_RenderInitialized; }

    void                        startRenderThread();

    //! called from render thread
    void						initRenderContext();

    //! called from render thread when ready for opengl rendering
    void						glWidgetInitialized( QOpenGLContext * threadGlContext, RenderGlOffScreenSurface * offScreenSurface );

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

    RenderGlThread *			m_RendererGlThread = nullptr;

    QOpenGLContext *            m_ThreadGlContext = nullptr;
    QOpenGLFunctions *          m_Glf = nullptr;
    QOpenGLExtraFunctions *     m_GlfExtra = nullptr;

    RenderGlOffScreenSurface *  m_RenderThreadSurface = nullptr;

    bool                        m_RenderInitialized = false;
  
    QMutex                      m_renderMutex;

    QImage                      m_LastRenderedImage;

    bool                        m_exiting = false;

    bool                        m_RenderWindowVisible = false;
};

#endif // RENDERGLLOGIC_H
