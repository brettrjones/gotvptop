#pragma once

#include <QThread>
#include <QOpenGLContext>
#include <QOffscreenSurface>

class RenderGlOffScreenSurface;
class QOpenGLFramebufferObject;
class RenderGlWidget;
class RenderGlLogic;
class AppCommon;

class RenderKodiThread : public QThread
{
    Q_OBJECT
public:
    explicit RenderKodiThread( QWidget * parent );
    virtual ~RenderKodiThread() override = default;


    void                        startRenderThread();

    void						setRenderThreadShouldRun(bool shouldRun) { m_ShouldRun = shouldRun; }

protected:
    virtual void                run() override;

    bool						m_ShouldRun = true;
    bool                        m_IsKodiRunning = false;
};
