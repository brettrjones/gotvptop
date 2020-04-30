#ifndef NET_CLIENT_THREAD_H
#define NET_CLIENT_THREAD_H

#include "NetClientCommon.h"
#include "NetClientLogic.h"

#include <QWidget>
#include <QMutex>

class NetClientThread : public QThread
{
	Q_OBJECT
public:
    explicit NetClientThread( NetClientLogic& renderLogic );


	void						setRenderThreadShouldRun(bool shouldRun) { m_ShouldRun = shouldRun; }

protected:
    NetClientLogic&				m_RenderLogic;
	bool						m_ShouldRun = true;
};

#endif // NET_CLIENT_THREAD_H
