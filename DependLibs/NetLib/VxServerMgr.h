#pragma once
//============================================================================
// Copyright (C) 2009 Brett R. Jones 
// Issued to MIT style license by Brett R. Jones in 2017
//
// You may use, copy, modify, merge, publish, distribute, sub-license, and/or sell this software 
// provided this Copyright is not modified or removed and is included all copies or substantial portions of the Software
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// bjones.engineer@gmail.com
// http://www.gotvptop.net
//============================================================================

#include "VxSktThrottle.h"
#include "VxSktBaseMgr.h"

#include <CoreLib/VxThread.h>
#include <vector>

// from header in case not defined
#ifndef FD_SETSIZE
#define FD_SETSIZE      64
#endif /* FD_SETSIZE */

// implements a manager to manage accept sockets
class VxServerMgr : public VxSktBaseMgr 
{
public:
	VxServerMgr();
	virtual ~VxServerMgr();

	// overrides SktMgrBase
	virtual void				sktMgrShutdown( void );

	// overrides SktMgrBase
	//! make a new socket... give derived classes a chance to override
	virtual VxSktBase *			makeNewAcceptSkt( void );

	virtual bool				isReadyToAcceptConnections( void )			{ return m_IsReadyToAcceptConnections; }
	virtual bool				isListening( void )							{ return m_ListenVxThread.isThreadRunning(); }
	virtual uint16_t					getListenPort( void )						{ return m_u16ListenPort; }
	virtual InetAddrAndPort		getLocalIp( void )							{ return m_LclIp; }
	virtual void				fromGuiKickWatchdog( void );
	virtual bool				checkWatchdog( void );


	virtual RCODE				startListening(  const char * ip, uint16_t u16ListenPort );
	virtual RCODE				startListening( uint16_t u16ListenPort );
	virtual RCODE				stopListening( void );

	void						listenForConnectionsToAccept( VxThread * poVxThread );

public:
    VxThread					m_ListenVxThread;		// thread to listen for incoming connections
    int							m_iMgrId;									// unique id for this manager

protected:
    RCODE						internalStartListen( void );
    RCODE 						acceptConnection( VxThread * poVxThread, SOCKET oListenSkt );

    static int					m_iAcceptMgrCnt;				// number of managers created
    RCODE						m_rcLastError;					// last error that occurred

    uint16_t							m_u16ListenPort;				// what port to listen on
    SOCKET						m_aoListenSkts[ FD_SETSIZE ];	// array of listen sockets
    int							m_iActiveListenSktCnt;			// number of active listening sockets
	InetAddrAndPort				m_LclIp;
	time_t						m_LastWatchdogKick;
	bool						m_IsReadyToAcceptConnections;
};

