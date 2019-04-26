#pragma once
#include "config_gotvapps.h"

#include <QThread>
#include <QOpenGLContext>
#include <QOffscreenSurface>

class RenderGlOffScreenSurface;
class QOpenGLFramebufferObject;
class RenderGlWidget;
class RenderGlLogic;
class AppCommon;

class RunKodiThread : public QThread
{
    Q_OBJECT
public:
    explicit RunKodiThread( RenderGlLogic& renderLogic );
    virtual ~RunKodiThread() override = default;

    void						setRunKodiThreadShouldRun( bool shouldRun ) { m_ShouldRun = shouldRun; }

    bool                        isRunKodiThreadStarted() { return m_IsThreadStarted; }
    void                        startRunKodiThread();
    void                        stopRunKodiThread();

signals:
    void                        signalStartRunKodiThread();

protected slots:
    void                        slotStartRunKodiThread();

protected:
    virtual void                run() override;

    RenderGlLogic&				m_RenderLogic;
    bool						m_ShouldRun = true;
    bool                        m_IsThreadStarted = false;
    bool                        m_IsKodiRunning = false;
};
