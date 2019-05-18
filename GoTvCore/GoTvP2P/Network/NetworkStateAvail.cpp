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
// http://www.gotvptop.net
//============================================================================

#include "NetworkStateAvail.h"
#include "NetworkStateMachine.h"
#include "NetworkMgr.h"

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>
#include <GoTvCore/GoTvP2P/P2PEngine/EngineSettings.h>

#include <NetLib/VxPeerMgr.h>

#include <CoreLib/VxParse.h>

#include <stdio.h>

//============================================================================
NetworkStateAvail::NetworkStateAvail( NetworkStateMachine& stateMachine )
: NetworkStateBase( stateMachine )
, m_DirectConnectTester( stateMachine.getDirectConnectTester() )
{
	setNetworkStateType( eNetworkStateTypeAvail );
}

//============================================================================
void NetworkStateAvail::enterNetworkState( void )
{
#ifdef DEBUG_PTOP_NETWORK_STATE
    LogMsg( LOG_STATUS, "eNetworkStateTypeAvail start\n" );
#endif // DEBUG_PTOP_NETWORK_STATE
	m_Engine.getToGui().toGuiNetworkState( eNetworkStateTypeAvail );
}

//============================================================================
void NetworkStateAvail::runNetworkState( void )
{
	VxTimer availTimer;
#ifdef DEBUG_PTOP_NETWORK_STATE
    LogMsg( LOG_INFO, "111 NetworkStateAvail::runNetworkState start %3.3f\n", availTimer.elapsedSec() );
#endif // DEBUG_PTOP_NETWORK_STATE
    std::string netServiceUrl;
	m_Engine.getEngineSettings().getNetServiceWebsiteUrl( netServiceUrl );

	// wait for log on if need be
	while( ( false == m_NetworkStateMachine.checkAndHandleNetworkEvents() )
		&& ( false == m_NetworkStateMachine.isUserLoggedOn() ) )
	{
		VxSleep( 500 );
	}

	if( m_NetworkStateMachine.checkAndHandleNetworkEvents() )
	{
		return;
	}

	//BRJ it seems that while upnp is communicating with router the router may temporarily stop accepting incoming connections
	// so startup order has been changed. 
	// 1. test if port is open
	// 2. if open move to online
	// 3. if closed start upnp open port and move to relay search but retest for port open before accepting relay connection

	//// tell Upnp to open port if possible
	//m_NetworkStateMachine.startUpnpOpenPort();
 //   if( m_NetworkStateMachine.checkAndHandleNetworkEvents() )
 //   {
 //       return;
 //   }
#ifdef DEBUG_PTOP_NETWORK_STATE
	//LogMsg( LOG_INFO, "111 NetworkStateAvail::runNetworkState resolving urls time %3.3f\n", availTimer.elapsedSec() );
#endif // DEBUG_PTOP_NETWORK_STATE
    bool websitesResolved = m_NetworkStateMachine.resolveWebsiteUrls();
	if( false == websitesResolved )
	{
		m_Engine.getToGui().toGuiNetworkState( eNetworkStateTypeFailedResolveAnchor, "" );
	}

    if( m_NetworkStateMachine.checkAndHandleNetworkEvents() )
    {
        return;
    }

	EngineSettings::EFirewallTestType firewallTestType = m_Engine.getEngineSettings().getFirewallTestSetting();
	if( EngineSettings::eFirewallTestAssumeNoFirewall == firewallTestType )
	{
		std::string externIp;
		m_Engine.getEngineSettings().getExternalIp( externIp );
		InetAddress externAddr;
		externAddr.setIp( externIp.c_str() );
		if( false == externAddr.isValid() )
		{
#ifdef DEBUG_PTOP_NETWORK_STATE
            LogMsg( LOG_STATUS, "eNetworkStateTypeLost Assume No Firewall Setting Must Specify An Valid External IP Address\n" );
			AppErr( eAppErrBadParameter, "Assume No Firewall Setting Must Specify An Valid External IP Address\n" );
#endif // DEBUG_PTOP_NETWORK_STATE

			m_Engine.getToGui().toGuiNetworkState( eNetworkStateTypeLost, "Assume No Firewall Setting Must Specify An Valid External IP Address\n" );
		}
		else
		{
			m_NetworkStateMachine.setPktAnnounceWithCanDirectConnect( externIp, false );
			m_NetworkStateMachine.changeNetworkState( eNetworkStateTypeAnnounce );
#ifdef DEBUG_PTOP_NETWORK_STATE
            LogMsg( LOG_STATUS, "eNetworkStateTypeAvail Assume No Firewall User Extern IP %s\n", externIp.c_str() );
#endif // DEBUG_PTOP_NETWORK_STATE

			m_Engine.getToGui().toGuiNetworkState( eNetworkStateTypeAvail, externIp.c_str() );
			return;
		}
	}

	//LogMsg( LOG_INFO, "111 NetworkStateAvail::runNetworkState checking listen ready %3.3f\n", availTimer.elapsedSec() );
	int waitForListenCnt = 0;
	while( ( false == m_NetworkStateMachine.checkAndHandleNetworkEvents() )
		&& ( false == m_Engine.getPeerMgr().isReadyToAcceptConnections() ) )
	{
		VxSleep( 1000 );
		waitForListenCnt++;
		if( waitForListenCnt > 5 )
		{
            #ifdef DEBUG_PTOP_NETWORK_STATE
                LogMsg( LOG_ERROR, "NetworkStateAvail::runNetworkState timed out waiting for isReadyToAcceptConnections\n" );
                char timeoutMsg[128];
                sprintf( timeoutMsg, "ERROR Timeout waiting for listen port %d", m_PktAnn.getOnlinePort() );
                m_Engine.getToGui().toGuiStatusMessage( timeoutMsg );
            #endif // DEBUG_PTOP_NETWORK_STATE
			break;
		}
	}

    #ifdef DEBUG_PTOP_NETWORK_STATE
	    LogMsg( LOG_INFO, "Notify GUI Starting Direct connect Test %3.3f\n", availTimer.elapsedSec() );            
        m_Engine.getToGui().toGuiStatusMessage( "#Network Testing if port is open" );
    #endif // DEBUG_PTOP_NETWORK_STATE

	VxSleep( 3500 ); // give listen port time to open first
    #ifdef DEBUG_PTOP_NETWORK_STATE
	    LogMsg( LOG_INFO, "Network State Avail Starting Direct connect Test %3.3f\n", availTimer.elapsedSec() );
    #endif // DEBUG_PTOP_NETWORK_STATE

	DirectConnectTestResults& directConnectTestResults = m_DirectConnectTester.getDirectConnectTestResults();
	m_DirectConnectTester.testCanDirectConnect();
	while( ( false == m_NetworkStateMachine.checkAndHandleNetworkEvents() )
		&& ( false == m_NetworkStateMachine.getDirectConnectTester().isDirectConnectTestComplete() ) )
	{
		VxSleep( 250 );
	}

    if( m_NetworkStateMachine.checkAndHandleNetworkEvents() )
    {
        return;
    }

	// check if error instead of port is open or port is closed result
	if( ( eAppErrNone != directConnectTestResults.m_eAppErr )
		&& ( eAppErrPortIsClosed != directConnectTestResults.m_eAppErr ) )
	{
        #ifdef DEBUG_PTOP_NETWORK_STATE
		LogMsg( LOG_STATUS, "eNetworkStateTypeAvail Failed To Connect To Connection Test Server %s  %3.3f\n", netServiceUrl.c_str(), availTimer.elapsedSec() ); 

		if( EngineSettings::eFirewallTestUrlConnectionTest == firewallTestType )
		{
			if( eAppErrRxError == directConnectTestResults.m_eAppErr )
			{
				AppErr( eAppErrFailedConnectNetServices, "Connection test node failed to respond.\nPlease check connection test settings" );

			}
			else
			{
				AppErr( eAppErrFailedConnectNetServices, "Could not connect to connection test node.\nPlease check connection test settings" );
			}
		}
		else
		{
			// TODO handle failed to connect and other errors
		}
        #endif // DEBUG_PTOP_NETWORK_STATE
	}

	if( m_NetworkStateMachine.checkAndHandleNetworkEvents() )
	{
		return;
	}

	InetAddress externAddr;
	externAddr.setIp( directConnectTestResults.m_MyIpAddr.c_str() );
    if( false == externAddr.isValid() )
	{
#ifdef DEBUG_PTOP_NETWORK_STATE
        AppErr( eAppErrBadParameter, "Could not determine external IP.\n" );
#endif // DEBUG_PTOP_NETWORK_STATE
	}

	if( ( false == directConnectTestResults.getCanDirectConnect() )
		&& m_Engine.getEngineSettings().getUseUpnpPortForward() )
	{
        #ifdef DEBUG_PTOP_NETWORK_STATE
            LogMsg( LOG_INFO, "NetworkStateAvail::runNetworkState Starting UPNP %3.3f\n", availTimer.elapsedSec() );
        #endif // DEBUG_PTOP_NETWORK_STATE
		m_NetworkStateMachine.startUpnpOpenPort();
	}
	else
	{
#ifdef DEBUG_PTOP_NETWORK_STATE
        LogMsg( LOG_STATUS, "eNetworkStateTypeAvail extern ip %s\n",
			directConnectTestResults.m_MyIpAddr.c_str() );
#endif // DEBUG_PTOP_NETWORK_STATE
        m_Engine.getToGui().toGuiNetworkState( eNetworkStateTypeAvail, directConnectTestResults.m_MyIpAddr.c_str() );
	}

	if( m_NetworkStateMachine.checkAndHandleNetworkEvents() )
	{
		return;
	}

	if( m_DirectConnectTester.isTestResultCanDirectConnect() )
	{
		std::string availMsg;
		StdStringFormat( availMsg, "IP %s\n", directConnectTestResults.m_MyIpAddr.c_str() );
#ifdef DEBUG_PTOP_NETWORK_STATE
        LogMsg( LOG_STATUS, "eNetworkStateTypeAvail %s %3.3f\n", availMsg.c_str(), availTimer.elapsedSec() );
#endif // DEBUG_PTOP_NETWORK_STATE
        m_Engine.getToGui().toGuiNetworkState( eNetworkStateTypeAvail, availMsg.c_str() );
		
		if( EngineSettings::eFirewallTestAssumeFirewalled == firewallTestType )
		{
#ifdef DEBUG_PTOP_NETWORK_STATE
            LogMsg( LOG_STATUS, "NetworkStateAvail::runNetworkState eFirewallTestAssumeFirewalled %3.3f\n", availTimer.elapsedSec() );
#endif // DEBUG_PTOP_NETWORK_STATE
            m_NetworkStateMachine.setPktAnnounceWithCanDirectConnect( directConnectTestResults.m_MyIpAddr, true );
			m_NetworkStateMachine.changeNetworkState( eNetworkStateTypeRelaySearch );
		}
		else
		{
#ifdef DEBUG_PTOP_NETWORK_STATE
            LogMsg( LOG_STATUS, "NetworkStateAvail::runNetworkState announce with direct connect %3.3f\n", availTimer.elapsedSec() );
#endif // DEBUG_PTOP_NETWORK_STATE
            m_NetworkStateMachine.setPktAnnounceWithCanDirectConnect( directConnectTestResults.m_MyIpAddr, false );
			m_Engine.getToGui().toGuiUpdateMyIdent( &m_PktAnn );
			m_NetworkStateMachine.changeNetworkState( eNetworkStateTypeAnnounce );
		}
	}
	else
	{
		if( EngineSettings::eFirewallTestUrlConnectionTest == firewallTestType )
		{
#ifdef DEBUG_PTOP_NETWORK_STATE
			LogMsg( LOG_STATUS, "NetworkStateAvail::runNetworkState relay search %3.3f\n", availTimer.elapsedSec() ); 
#endif // DEBUG_PTOP_NETWORK_STATE
            m_NetworkStateMachine.setPktAnnounceWithCanDirectConnect( directConnectTestResults.m_MyIpAddr, true );
			m_NetworkStateMachine.changeNetworkState( eNetworkStateTypeRelaySearch );
		}
		else if( EngineSettings::eFirewallTestAssumeNoFirewall == firewallTestType )
		{
#ifdef DEBUG_PTOP_NETWORK_STATE
            LogMsg( LOG_STATUS, "NetworkStateAvail::runNetworkState assume no firewall %3.3f\n", availTimer.elapsedSec() );
#endif // DEBUG_PTOP_NETWORK_STATE
            m_NetworkStateMachine.setPktAnnounceWithCanDirectConnect( directConnectTestResults.m_MyIpAddr, false );
			m_Engine.getToGui().toGuiUpdateMyIdent( &m_PktAnn );
			m_NetworkStateMachine.changeNetworkState( eNetworkStateTypeAnnounce );
		}
		else if( EngineSettings::eFirewallTestAssumeFirewalled == firewallTestType )
		{
#ifdef DEBUG_PTOP_NETWORK_STATE
            LogMsg( LOG_STATUS, "NetworkStateAvail::runNetworkState assume firewall %3.3f\n", availTimer.elapsedSec() );
#endif // DEBUG_PTOP_NETWORK_STATE
            m_NetworkStateMachine.setPktAnnounceWithCanDirectConnect( directConnectTestResults.m_MyIpAddr, true );
			m_NetworkStateMachine.changeNetworkState( eNetworkStateTypeRelaySearch );
		}
		else
		{
#ifdef DEBUG_PTOP_NETWORK_STATE
            LogMsg( LOG_ERROR, "ERROR invalid firewall test type %d  %3.3f\n", firewallTestType, availTimer.elapsedSec() );
#endif // DEBUG_PTOP_NETWORK_STATE

			m_NetworkStateMachine.setPktAnnounceWithCanDirectConnect( directConnectTestResults.m_MyIpAddr, true );
			m_NetworkStateMachine.changeNetworkState( eNetworkStateTypeTestConnection );
		}
	}

#ifdef DEBUG_PTOP_NETWORK_STATE
	//LogMsg( LOG_INFO, "111 NetworkStateAvail::runNetworkState done  %3.3f\n", availTimer.elapsedSec() );
#endif // DEBUG_PTOP_NETWORK_STATE
}

