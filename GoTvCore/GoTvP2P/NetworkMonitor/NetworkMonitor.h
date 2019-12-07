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
// http://www.nolimitconnect.com
//============================================================================

#include <string>

class P2PEngine;

class NetworkMonitor
{
public:
	NetworkMonitor( P2PEngine& engine );
	~NetworkMonitor() = default;

	void						networkMonitorStartup( const char * preferredNetIp = "", const char * cellNetIp = "" );
	void						networkMonitorShutdown( void );

	void						onOncePerSecond( void );

protected:
	P2PEngine&					m_Engine;
	bool						m_bIsStarted;
	std::string					m_strPreferredAdapterIp;
	std::string					m_strCellNetIp;
	std::string					m_strLastFoundIp;
	int							m_iCheckInterval;

};
