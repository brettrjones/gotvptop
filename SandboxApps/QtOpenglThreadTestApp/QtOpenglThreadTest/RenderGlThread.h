#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H

#include "GlTestCommon.h"
#include "RenderGlLogic.h"

#include <QWidget>
#include <QMutex>

class RenderGlThread : public QThread
{
	Q_OBJECT
public:
    explicit RenderGlThread( RenderGlLogic& renderLogic );

    void                        startRenderThread();

	void						setRenderThreadShouldRun(bool shouldRun) { m_ShouldRun = shouldRun; }

protected:
    virtual void                run() override;

    RenderGlLogic&				m_RenderLogic;
	bool						m_ShouldRun = true;
};

#endif // RENDERTHREAD_H
