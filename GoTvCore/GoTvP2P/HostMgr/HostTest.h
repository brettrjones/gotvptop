//============================================================================
// Copyright (C) 2019 Brett R. Jones 
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
#pragma once

#include <GoTvInterface/IToGui.h>

#include <CoreLib/VxThread.h>
#include <CoreLib/VxMutex.h>

class P2PEngine;
class EngineSettings;
class PktAnnounce;
class NetworkMgr;
class NetServicesMgr;

class HostTest
{
public:
	HostTest( P2PEngine& engine, EngineSettings& engineSettings, NetServicesMgr& netServicesMgr );
	virtual ~HostTest() = default;

    IToGui&                     getToGui();
	virtual void				fromGuiVerifyNetHostSettings( void );

	void						doHostUrlTest( void );
	void						doNetServiceUrlTest( void );

private:

	const char *				getTestName( bool isHost );
	void						startHostUrlTest( void );
	void						startNetServiceUrlTest( void );
	void						sendTestStatus( EHostTestStatus eStatus, const char * msg, ... );
	void						sendTestLog( const char * msg, ... );
	bool						doConnectionTest( std::string& nodeUrl, bool isHost );
	bool						doConnectTestFailed( bool isHost );
	bool						doConnectTestSuccess( bool isHost, std::string& pongResult );

	//=== vars ===//
    P2PEngine&					m_Engine;
	EngineSettings&				m_EngineSettings;
	NetServicesMgr&				m_NetServicesMgr;

	VxThread					m_HostThread;
	VxThread					m_NetServiceThread;
};

