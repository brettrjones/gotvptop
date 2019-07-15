#pragma once
//============================================================================
// Copyright (C) 2014 Brett R. Jones 
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
// http://www.gotvptop.com
//============================================================================

#include <GoTvInterface/IToGui.h>

#include <CoreLib/VxThread.h>
#include <CoreLib/VxMutex.h>

class P2PEngine;
class EngineSettings;
class PktAnnounce;
class NetworkMgr;
class NetServicesMgr;

class AnchorTest
{
public:
	AnchorTest( EngineSettings& engineSettings, NetServicesMgr& netServicesMgr );
	virtual ~AnchorTest() = default;

    IToGui&                     getToGui();
	virtual void				fromGuiVerifyAnchorSettings( void );

	void						doAnchorUrlTest( void );
	void						doNetServiceUrlTest( void );

private:

	const char *				getTestName( bool isAnchor );
	void						startAnchorUrlTest( void );
	void						startNetServiceUrlTest( void );
	void						sendTestStatus( EAnchorTestStatus eStatus, const char * msg, ... );
	void						sendTestLog( const char * msg, ... );
	bool						doConnectionTest( std::string& nodeUrl, bool isAnchor );
	bool						doConnectTestFailed( bool isAnchor );
	bool						doConnectTestSuccess( bool isAnchor, std::string& pongResult );

	//=== vars ===//
	//P2PEngine&					m_Engine;
	//
	EngineSettings&				m_EngineSettings;
	NetServicesMgr&				m_NetServicesMgr;

	VxThread					m_AnchorThread;
	VxThread					m_NetServiceThread;
};

