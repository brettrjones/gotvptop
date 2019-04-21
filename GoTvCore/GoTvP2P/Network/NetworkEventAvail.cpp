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
// brett.jones@engineer.com
// http://www.gotvptop.net
//============================================================================

#include "NetworkEventAvail.h"
#include "NetworkStateMachine.h"

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>

#include <PktLib/PktAnnounce.h>
#include <CoreLib/VxGlobals.h>

//============================================================================
NetworkEventAvail::NetworkEventAvail( NetworkStateMachine& stateMachine, const char * lclIp, bool isCellularNetwork )
: NetworkEventBase( stateMachine )
{
	setNetworkEventType( eNetworkEventTypeAvail );
	if( lclIp )
	{
		m_LclIp = lclIp;
	}
	else
	{
		m_LclIp = "";
	}

	VxSetLclIpAddress( m_LclIp.c_str() );
	m_bIsCellNetwork = isCellularNetwork;
}

//============================================================================
void NetworkEventAvail::runNetworkEvent( void )
{

	LogMsg( LOG_INFO, "NetworkEventAvail::runNetworkEvent start\n" );
	m_NetworkStateMachine.resolveWebsiteUrls();
	//m_NetworkStateMachine.changeNetworkState( eNetworkStateTypeAvail );

	//m_PktAnn.getLanIPv4().setIp( m_LclIp.c_str() );
	//uint16_t u16TcpPort;
	//m_Engine.getEngineSettings().getTcpIpPort( u16TcpPort );
	//m_PktAnn.setOnlinePort( u16TcpPort );
	//m_Engine.getToGui().toGuiUpdateMyIdent( &m_PktAnn );
	LogMsg( LOG_INFO, "NetworkEventAvail::runNetworkEvent done\n" );
}


