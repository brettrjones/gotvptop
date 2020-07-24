#pragma once
//============================================================================
// Copyright (C) 2015 Brett R. Jones
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
// http://www.nolimitconnect.com
//============================================================================

#include <config_gotvcore.h>

#include "HostListCallbackInterface.h"

#include <CoreLib/VxMutex.h>

class P2PEngine;
class IToGui;

class HostListInfo;
class HostListMgr;
class HostListLocationMgr;
class HostListHistoryMgr;

class HostListMgrBase : public HostListCallbackInterface
{
public:
	class AutoResourceLock
	{
	public:
		AutoResourceLock( HostListMgrBase * assetMgrBase ) : m_Mutex(assetMgrBase->getResourceMutex())	{ m_Mutex.lock(); }
		~AutoResourceLock()																			{ m_Mutex.unlock(); }
		VxMutex&				m_Mutex;
	};

	HostListMgrBase( P2PEngine& engine );
	virtual ~HostListMgrBase() = default;

    IToGui&						getToGui();

	VxMutex&					getResourceMutex( void )					{ return m_ResourceMutex; }
	void						lockResources( void )						{ m_ResourceMutex.lock(); }
	void						unlockResources( void )						{ m_ResourceMutex.unlock(); }

	void						addHostListMgrClient( HostListCallbackInterface * client, bool enable );
	bool						isAllowedFileOrDir( std::string strFileName );

protected:
	void						lockClientList( void )						{ m_ClientListMutex.lock(); }
	void						unlockClientList( void )					{ m_ClientListMutex.unlock(); }
	//=== vars ===//
	P2PEngine&					m_Engine;
	VxMutex						m_ResourceMutex;
	VxMutex						m_ClientListMutex;

	std::vector<HostListCallbackInterface *> m_HostListClients;
};

