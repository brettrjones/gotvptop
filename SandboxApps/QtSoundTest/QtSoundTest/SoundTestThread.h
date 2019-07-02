#ifndef SOUND_TEST_THREAD_H
#define SOUND_TEST_THREAD_H

//#include "SoundTestLogic.h"

#include <QWidget>
#include <QMutex>
#include <QThread>

class SoundTestLogic;

class SoundTestThread : public QThread
{
	Q_OBJECT
public:
    SoundTestThread( SoundTestLogic& renderLogic );

    void                        startRenderThread();

	void						setRenderThreadShouldRun(bool shouldRun) { m_ShouldRun = shouldRun; }

protected:
    virtual void                run() override;

    SoundTestLogic&				m_RenderLogic;
	bool						m_ShouldRun = true;
};

#endif // SOUND_TEST_THREAD_H
