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

#include "NetworkStateMachine.h"
#include "NetworkStateLost.h"
#include "NetworkStateAvail.h"
#include "NetworkStateTestConnection.h"
#include "NetworkStateRelaySearch.h"
#include "NetworkStateAnnounce.h"
#include "NetworkStateOnlineDirect.h"
#include "NetworkStateOnlineThroughRelay.h"
#include "NetworkStateGetRelayList.h"

#include "NetworkEventBase.h"
#include "NetworkEventAvail.h"
#include "NetworkEventLost.h"

#include <GoTvCore/GoTvP2P/Network/NetworkMgr.h>
#include <GoTvCore/GoTvP2P/Network/NetConnector.h>
#include <GoTvCore/GoTvP2P/NetServices/NetServicesMgr.h>

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>

#include <CoreLib/VxGlobals.h>
#include <NetLib/VxSktUtil.h>
#include <NetLib/VxResolveHost.h>
#include <NetLib/VxPeerMgr.h>

#include "GoTvDebugConfig.h"

#include <time.h>
#include <atomic>


#ifdef _MSC_VER
# pragma warning(disable: 4355) //'this' : used in base member initializer list
#endif

namespace
{
	//============================================================================
    void * NetworkStateMachineThreadFunc( void * pvContext )
	{
        static std::atomic_int threadCnt(0);
#ifdef DEBUG_PTOP_NETWORK_STATE
        LogMsg( LOG_INFO, "NetworkStateMachineThreadFunc thread starting %d\n", threadCnt.load() );
#endif // DEBUG_PTOP_NETWORK_STATE
		VxThread * poThread = (VxThread *)pvContext;
		poThread->setIsThreadRunning( true );
		NetworkStateMachine * stateMachine = (NetworkStateMachine *)poThread->getThreadUserParam();
		if( false == poThread->isAborted() )
		{
			stateMachine->runStateMachineThread();
		}

		poThread->threadAboutToExit();
        threadCnt--;
#ifdef DEBUG_PTOP_NETWORK_STATE
        LogMsg( LOG_INFO, "NetworkStateMachineThreadFunc Thread exiting %d\n", threadCnt.load() );
#endif // DEBUG_PTOP_NETWORK_STATE
        return nullptr;
	}
}

//============================================================================
NetworkStateMachine::NetworkStateMachine(	P2PEngine& engine,
											NetworkMgr&	networkMgr )
: m_Engine( engine )
, m_EngineSettings( engine.getEngineSettings() )
, m_PktAnn( engine.getMyPktAnnounce() )
, m_NetworkMgr( networkMgr )
, m_NetServicesMgr( engine.getNetServicesMgr() )
, m_NetConnector( engine.getNetConnector() )
, m_StateMachineInitialized( false )
, m_NetPortForward( *this )
, m_DirectConnectTester( *this )
, m_bUserLoggedOn( false )
, m_bIsCellNetwork( false )
, m_bRelayServiceConnected( false )
, m_eCurRunningStateType( eNetworkStateTypeLost )
, m_bWebsiteUrlsResolved( false )
, m_LastKnownExternalIpAddr( "0.0.0.0" )
, m_LastUpnpForwardTime( 0 )
, m_LastUpnpForwardPort( 0 )
, m_LastUpnpForwardIp( "" )
{
}

//============================================================================
NetworkStateMachine::~NetworkStateMachine()
{
	stateMachineShutdown();
}

//============================================================================
void NetworkStateMachine::stateMachineStartup( void )
{	
	if( m_StateMachineInitialized )
	{
		stateMachineShutdown();
	}

	startupNetworkModules();

	m_NetworkStateLost = new NetworkStateLost(  *this );
	m_CurNetworkState = m_NetworkStateLost;
	m_NetworkStateList.push_back( m_NetworkStateLost );
	m_NetworkStateList.push_back( new NetworkStateAvail( *this ) );
	m_NetworkStateList.push_back( new NetworkStateTestConnection( *this ) );
	m_NetworkStateList.push_back( new NetworkStateRelaySearch( *this ) );
	m_NetworkStateList.push_back( new NetworkStateAnnounce( *this ) );
	m_NetworkStateList.push_back( new NetworkStateOnlineDirect( *this ) );
	m_NetworkStateList.push_back( new NetworkStateOnlineThroughRelay( *this ) );
	m_NetworkStateList.push_back( new NetworkStateGetRelayList( *this ) );
	m_StateMachineInitialized = true;

    m_NetworkStateThread.startThread( (VX_THREAD_FUNCTION_T)NetworkStateMachineThreadFunc, this, "NetworkStateMachineThread" );
}

//============================================================================
void NetworkStateMachine::startupNetworkModules( void )
{
#ifdef DEBUG_PTOP_NETWORK_STATE
    LogMsg( LOG_INFO, "NetworkStateMachine::startupNetworkModules 1\n" );
#endif // DEBUG_PTOP_NETWORK_STATE
	m_NetworkMgr.networkMgrStartup();
	uint16_t u16MulticastPort;
#ifdef DEBUG_PTOP_NETWORK_STATE
    LogMsg( LOG_INFO, "NetworkStateMachine::startupNetworkModules 2\n" );
#endif // DEBUG_PTOP_NETWORK_STATE
	m_Engine.getEngineSettings().getMulticastPort( u16MulticastPort );
	m_NetworkMgr.setBroadcastPort( u16MulticastPort );

	bool multicastEnable = false;
	m_Engine.getEngineSettings().getMulticastEnable( multicastEnable );
	m_NetworkMgr.setBroadcastEnable( multicastEnable );

	m_NetServicesMgr.netServicesStartup();
	m_NetConnector.netConnectorStartup();
	m_NetConnector.stayConnectedStartup();
}

//============================================================================
void NetworkStateMachine::stateMachineShutdown( void )
{
	if( m_StateMachineInitialized )
	{
		m_StateMachineInitialized = false;
		m_NetworkStateThread.abortThreadRun( true );
		shutdownNetworkModules();
		m_CurNetworkState->exitNetworkState();
		m_NetworkStateThread.killThread();
		destroyNetworkStates();
	}
}

//============================================================================
void NetworkStateMachine::shutdownNetworkModules( void )
{
	m_NetPortForward.netPortForwardShutdown();
	m_NetConnector.stayConnectedShutdown();
	m_NetConnector.netConnectorShutdown();
	m_NetServicesMgr.netServicesShutdown();
	m_NetworkMgr.networkMgrShutdown();
}

//============================================================================
bool NetworkStateMachine::isP2POnline( void )
{
	return ( eNetworkStateTypeOnlineDirect == m_eCurRunningStateType ) 
			|| ( eNetworkStateTypeOnlineThroughRelay == m_eCurRunningStateType );
}

//============================================================================
bool NetworkStateMachine::shouldAbort( void )
{
	if( ( false == m_StateMachineInitialized )
		|| m_NetworkStateThread.isAborted() 
		|| VxIsAppShuttingDown() )
	{
#ifdef DEBUG_PTOP_NETWORK_STATE
        if( false == m_StateMachineInitialized )
        {
            LogMsg( LOG_INFO, "NetworkStateMachine::shouldAbort: m_StateMachineInitialized false\n" );
        }
        else if( m_NetworkStateThread.isAborted() )
        {
            LogMsg( LOG_INFO, "NetworkStateMachine::shouldAbort: m_NetworkStateThread.isAborted()\n" );
        }
        else
        {
            LogMsg( LOG_INFO, "NetworkStateMachine::shouldAbort: VxIsAppShuttingDown()\n" );
        }
#endif // DEBUG_PTOP_NETWORK_STATE

		return true;
	}

	return false;
}

//============================================================================
bool NetworkStateMachine::isNetworkStateChangePending( void )
{
	if( shouldAbort() )
	{
		return true;
	}

	if( m_eCurRunningStateType != m_CurNetworkState->getNetworkStateType() )
	{
		return true;
	}

	return false;
}

//============================================================================
void NetworkStateMachine::destroyNetworkStates( void )
{
#ifdef DEBUG_PTOP_NETWORK_STATE
    LogMsg( LOG_INFO, "NetworkStateMachine::destroyNetworkStates\n" );
#endif // DEBUG_PTOP_NETWORK_STATE
	std::vector<NetworkStateBase *>::iterator iter;
	for( iter = m_NetworkStateList.begin(); iter != m_NetworkStateList.end(); ++iter )
	{
		delete *iter;
	}

	m_NetworkStateList.clear();
}

//============================================================================
void NetworkStateMachine::changeNetworkState( ENetworkStateType eNetworkStateType )
{
	m_NetworkStateMutex.lock();
	ENetworkStateType curNetworkStateType = getCurNetworkStateType();
	m_NetworkStateMutex.unlock();
	if( shouldAbort() )
	{
		if( eNetworkStateTypeLost != curNetworkStateType )
		{
			m_NetworkStateMutex.lock();
			m_CurNetworkState = findNetworkState( eNetworkStateTypeLost );
			m_NetworkStateMutex.unlock();
		}	
		
		return;
	}

	if( curNetworkStateType != eNetworkStateType )
	{
#ifdef DEBUG_PTOP_NETWORK_STATE
		LogMsg( LOG_INFO, "changeNetworkState %s to %s\n", DescribeNetworkState( curNetworkStateType ), DescribeNetworkState( eNetworkStateType ) );
#endif // DEBUG_PTOP_NETWORK_STATE
		m_NetworkStateMutex.lock();
		m_CurNetworkState = findNetworkState( eNetworkStateType );
		m_NetworkStateMutex.unlock();
	}
}

//============================================================================
NetworkStateBase * NetworkStateMachine::findNetworkState( ENetworkStateType eNetworkStateType )
{
	std::vector< NetworkStateBase * >::iterator iter;
	for( iter = m_NetworkStateList.begin(); iter != m_NetworkStateList.end(); ++iter )
	{
		if( eNetworkStateType == (*iter)->getNetworkStateType() )
		{
			return (*iter);
		}
	}

	vx_assert( false );
	return NULL;
}

//============================================================================
ENetworkStateType NetworkStateMachine::getCurNetworkStateType( void )
{
	return m_CurNetworkState->getNetworkStateType();
}

//============================================================================
void NetworkStateMachine::runStateMachineThread( void )
{
	while( false == shouldAbort() )
	{
		NetworkStateBase * thisStateToRun = m_CurNetworkState;
		m_eCurRunningStateType = thisStateToRun->getNetworkStateType();

		thisStateToRun->enterNetworkState();
		if( false == shouldAbort() )
		{
			thisStateToRun->runNetworkState();
		}

		if( false == shouldAbort() )
		{
			thisStateToRun->exitNetworkState();
		}
	}
}

//============================================================================
bool NetworkStateMachine::checkAndHandleNetworkEvents( void )
{
    if( shouldAbort() )
    {
        return true;
    }

	if( m_NetworkEventList.size())
	{
		m_NetworkStateMutex.lock();
		NetworkEventBase * eventBase = m_NetworkEventList[0];
		m_NetworkEventList.erase( m_NetworkEventList.begin() );
		m_NetworkStateMutex.unlock();

		if( eNetworkEventTypeLost == eventBase->getNetworkEventType() )
		{
			changeNetworkState( eNetworkStateTypeLost );
		}
		else if( eNetworkEventTypeAvail == eventBase->getNetworkEventType() )
		{
			NetworkEventAvail * eventAvail = (NetworkEventAvail *)eventBase;
			eventAvail->runNetworkEvent();
			m_NetworkMgr.fromGuiNetworkAvailable( eventAvail->getLclIp(), eventAvail->getIsCellNetwork() );

			changeNetworkState( eNetworkStateTypeAvail );
		}
	}

	return isNetworkStateChangePending();
}

//============================================================================
void NetworkStateMachine::fromGuiUserLoggedOn( void )
{
#ifdef DEBUG_PTOP_NETWORK_STATE
	LogMsg( LOG_INFO, "NetworkStateMachine::fromGuiUserLoggedOn\n" );
#endif // DEBUG_PTOP_NETWORK_STATE
	EngineSettings& engineSettings = m_Engine.getEngineSettings();
	logonUpdateFromEngineSettings( engineSettings );

	m_bUserLoggedOn = true;
}

//============================================================================
void NetworkStateMachine::logonUpdateFromEngineSettings( EngineSettings& engineSettings )
{
	uint16_t u16TcpPort = engineSettings.getTcpIpPort();
	m_PktAnn.setOnlinePort( u16TcpPort );

	std::string networkName;
	engineSettings.getNetworkKey( networkName );
	m_NetworkMgr.setNetworkKey( networkName.c_str() );

	m_Engine.getBigListMgr().dbRestoreAll( networkName.c_str() );
}

//============================================================================
void NetworkStateMachine::restartNetwork( void )
{
	bool isCell		= m_bIsCellNetwork;
	std::string ip	= m_LocalNetworkIp;

    static bool hasCnaged = false;
    static bool lastIsCell = false;
    static std::string lastIpFound;
    if( ( lastIpFound != m_LocalNetworkIp )  || ( lastIsCell != isCell ) )
    {
        fromGuiNetworkLost();
        fromGuiNetworkAvailable( ip.c_str(), isCell );
    }
}

//============================================================================
void NetworkStateMachine::fromGuiNetworkAvailable( const char * lclIp, bool isCellularNetwork )
{
    bool hasChanged = ( m_LocalNetworkIp != lclIp );
	m_LocalNetworkIp = lclIp;
	VxSetLclIpAddress( lclIp );
	//LogMsg( LOG_INFO, "NetworkStateMachine::fromGuiNetworkAvailable\n" );

    uint16_t u16TcpPort = m_Engine.getEngineSettings().getTcpIpPort();
	m_PktAnn.setOnlinePort( u16TcpPort );
    hasChanged |= ( m_PktAnn.getOnlinePort() != u16TcpPort );
	m_PktAnn.getLanIPv4().setIp( lclIp );
    hasChanged |= ( m_bIsCellNetwork != isCellularNetwork );
    if( hasChanged )
    {
        m_Engine.getToGui().toGuiUpdateMyIdent( &m_PktAnn );
    }

	m_bIsCellNetwork = isCellularNetwork;
	m_NetworkStateMutex.lock();
	m_NetworkEventList.push_back( new NetworkEventAvail( *this, lclIp, isCellularNetwork ) );
	m_NetworkStateMutex.unlock();
}

//============================================================================
void NetworkStateMachine::fromGuiNetworkLost( void )
{
	m_Engine.getPeerMgr().stopListening();
	m_LocalNetworkIp = "";
	m_NetworkStateMutex.lock();
	m_NetworkEventList.push_back( new NetworkEventLost( *this ) );
	m_NetworkStateMutex.unlock();
}

//============================================================================
void NetworkStateMachine::fromGuiNetworkSettingsChanged( void )
{
	if( m_LocalNetworkIp.length() )
	{
		bool isCell = isCellularNetwork();
		std::string ip = m_LocalNetworkIp;

		fromGuiNetworkLost();
		m_PktAnn.getLanIPv4().setIp( ip.c_str() );
		fromGuiNetworkAvailable( ip.c_str(), isCell );
	}
}

//============================================================================
void NetworkStateMachine::fromGuiUseRelay( VxConnectInfo& connectInfo, bool useRelay )
{
	std::vector< NetworkStateBase * >::iterator iter;
	for( iter = m_NetworkStateList.begin(); iter != m_NetworkStateList.end(); ++iter )
	{
		(*iter)->fromGuiUseRelay( connectInfo, useRelay );
	}
}

//============================================================================
void NetworkStateMachine::onPktRelayServiceReply( VxSktBase * sktBase, PktRelayServiceReply * poPkt )
{
	m_CurNetworkState->onPktRelayServiceReply( sktBase, poPkt );
}

//============================================================================
bool NetworkStateMachine::checkForAbortOrShutdown( void )
{
	if( VxIsAppShuttingDown() || m_NetworkStateThread.isAborted() )
	{
		return true;
	}

	//if( 36000 < m_PortForwardTimer.elapsedSec() )
	if( 30 < m_PortForwardTimer.elapsedSec() )
	{
		// time to run upnp again
		startUpnpOpenPort();
	}

	return false;
}

//============================================================================
void NetworkStateMachine::startUpnpOpenPort( void )
{
	if( m_bUserLoggedOn && 
		( eNetworkStateTypeLost != getCurNetworkStateType() ) )
	{
		uint16_t u16Port;
		//LogMsg( LOG_INFO, "NetworkStateMachine::startUpnpOpenPort\n" );

        u16Port = m_Engine.getEngineSettings().getTcpIpPort();
		if( u16Port != m_PktAnn.getOnlinePort() )
		{
#ifdef DEBUG_PTOP_NETWORK_STATE
            LogMsg( LOG_ERROR, "startUpnpOpenPort engine port %d different than pkt ann port %d\n", u16Port, m_PktAnn.getOnlinePort() );
#endif // DEBUG_PTOP_NETWORK_STATE
			m_PktAnn.setMyOnlinePort( u16Port );
		}

		if( m_Engine.getEngineSettings().getUseUpnpPortForward() )
		{
			std::string			lclIp			= m_NetworkMgr.getLocalIpAddress();
			int64_t				timeNow			= GetTimeStampMs();

			if( ( ( timeNow - m_LastUpnpForwardTime ) < 180000 )
				&& ( m_LastUpnpForwardPort == u16Port )
				&& ( m_LastUpnpForwardIp == lclIp ) )
			{
#ifdef DEBUG_PTOP_NETWORK_STATE
                LogMsg( LOG_INFO, "Skipping UNPNP due to not enough elapsed time\n" );
#endif // DEBUG_PTOP_NETWORK_STATE
			}
			else
			{
				m_LastUpnpForwardTime	= timeNow;
				m_LastUpnpForwardPort	= u16Port;
				m_LastUpnpForwardIp		= lclIp;

				m_NetPortForward.beginPortForward( u16Port, lclIp.c_str() );
				m_PortForwardTimer.startTimer();
			}
		}
	}
}

//============================================================================
bool NetworkStateMachine::hasUpnpOpenPortFinished( void )
{
	if( false == m_Engine.getEngineSettings().getUseUpnpPortForward() )
	{
		return true;
	}

	// timeout after 8 seconds
	if( 8 < m_PortForwardTimer.elapsedSec() )
	{
		return true;
	}

	return m_NetPortForward.hasPortForwardCompleted();
}

//============================================================================
bool NetworkStateMachine::didUpnpOpenPortSucceed( void )
{
	return m_NetPortForward.didUpnpPortOpen();
}

//============================================================================
void NetworkStateMachine::setPktAnnounceWithCanDirectConnect( std::string& myIpAddr, bool requiresRelay )
{
	m_PktAnn.setRequiresRelay( requiresRelay );
	m_PktAnn.m_DirectConnectId.getIPv4().setIp( myIpAddr.c_str() );
	if( false == requiresRelay )
	{
		m_PktAnn.setHasRelay( false );
		if( false == m_PktAnn.m_DirectConnectId.getIPv4().isValid() )
		{
			vx_assert( m_PktAnn.m_DirectConnectId.getIPv4().isValid() );
			m_PktAnn.m_DirectConnectId.getIPv4().setIp( m_LastKnownExternalIpAddr.c_str() );
		}
		else
		{
			m_LastKnownExternalIpAddr = myIpAddr;
		}
	}

	m_PktAnn.m_RelayConnectId.clear();
}

//============================================================================
void NetworkStateMachine::setPktAnnounceWithRelayInfo( const char * relayOnlineID, const char * relayIP, uint16_t u16Port )
{
	m_PktAnn.setRequiresRelay( true );
	m_PktAnn.setHasRelay( true );
	m_PktAnn.m_RelayConnectId.getOnlineId().fromVxGUIDHexString( relayOnlineID );
	m_PktAnn.m_RelayConnectId.getIPv4().setIp( relayIP );
	m_PktAnn.m_RelayConnectId.setPort( u16Port );
}

//============================================================================
bool NetworkStateMachine::resolveWebsiteUrls( void )
{
	std::string anchorWebsiteUrl;
	m_EngineSettings.getNetHostWebsiteUrl( anchorWebsiteUrl );
	std::string netServiceWebsiteUrl;
	m_EngineSettings.getNetServiceWebsiteUrl( netServiceWebsiteUrl );
	if( m_bWebsiteUrlsResolved
		&& ( anchorWebsiteUrl == m_LastResolvedHostWebsite )
		&& ( netServiceWebsiteUrl == m_LastResolvedNetServiceWebsite ) )
	{
		//LogMsg( LOG_INFO, "NetworkStateMachine::resolveWebsiteUrls already resolved\n" );
		return true;
	}
	else
	{
		m_bWebsiteUrlsResolved = false;
	}

	//LogMsg( LOG_INFO, "NetworkStateMachine::resolveWebsiteUrls\n" );
	bool resolveHostResult		= resolveUrl( anchorWebsiteUrl, m_HostIp, m_u16HostPort );
	bool resolveConnectTestResult	= resolveUrl( netServiceWebsiteUrl, m_NetServiceIp, m_u16NetServicePort );
	EngineParams& engineParams		= m_Engine.getEngineParams();
	if( resolveHostResult )
	{
		m_LastResolvedHostWebsite = anchorWebsiteUrl;
		engineParams.setLastHostWebsiteUrl( m_LastResolvedHostWebsite );
		engineParams.setLastHostWebsiteResolvedIp( m_HostIp );
	}
	else
	{
		// use last known resolved ip
		std::string lastHostUrl;
		engineParams.getLastHostWebsiteUrl( lastHostUrl );
		if( lastHostUrl == anchorWebsiteUrl )
		{
			std::string lastHostIp = "";
			engineParams.setLastHostWebsiteResolvedIp( lastHostIp );
			if( 0 != lastHostIp.length() )
			{
				m_HostIp = lastHostIp;
				resolveHostResult = true;
			}
		}
	}

	if( resolveConnectTestResult )
	{
		m_LastResolvedNetServiceWebsite = netServiceWebsiteUrl;
		engineParams.setLastNetServiceWebsiteUrl( m_LastResolvedNetServiceWebsite );
		engineParams.setLastNetServiceWebsiteResolvedIp( m_NetServiceIp );
	}
	else
	{
		// use last known resolved ip
		std::string lastNetServiceUrl;
		engineParams.getLastNetServiceWebsiteUrl( lastNetServiceUrl );
		if( lastNetServiceUrl == netServiceWebsiteUrl )
		{
			std::string lastNetServiceIp;
			engineParams.getLastNetServiceWebsiteResolvedIp( lastNetServiceIp );
			if( 0 != lastNetServiceIp.length() )
			{
				m_NetServiceIp = lastNetServiceIp;
				resolveConnectTestResult = true;
			}
		}
	}

	if( resolveHostResult && resolveConnectTestResult )
	{
		m_bWebsiteUrlsResolved = true;
		std::string myLclIp = VxGetLclIpAddress();

		m_bHostIpMatch = false;
		if( myLclIp == m_HostIp )
		{
			m_bHostIpMatch = true;
		}

		m_bNetServiceIpMatch = false;
		if( myLclIp == m_NetServiceIp )
		{
			m_bNetServiceIpMatch = true;
		}
	}
	else
	{
#ifdef DEBUG_PTOP_NETWORK_STATE
		    LogMsg( LOG_ERROR, "Failed to resolve network websites %s %s\n", anchorWebsiteUrl.c_str(), netServiceWebsiteUrl.c_str() );
#endif // DEBUG_PTOP_NETWORK_STATE
	}


	return ( resolveHostResult && resolveConnectTestResult );
}

//============================================================================
bool NetworkStateMachine::resolveUrl( std::string& websiteUrl, std::string& retIp, uint16_t& u16RetPort )
{
	return VxResolveHostToIp( websiteUrl.c_str(), retIp, u16RetPort );
}

//============================================================================
void NetworkStateMachine::onOncePerHour( void )
{
#ifdef DEBUG_PTOP_NETWORK_STATE
	LogMsg( LOG_INFO, "NetworkStateMachine::onOncePerHour\n" );
#endif // DEBUG_PTOP_NETWORK_STATE
	//if( isP2POnline() && m_EngineSettings.getUseUpnpPortForward() )
	//{
	//	if( m_NetPortForward.elapsedSecondsLastAttempt() > 60 )
	//	{
	//		m_NetPortForward.beginPortForward( m_PktAnn.getOnlinePort(), m_NetworkMgr.getLocalIpAddress().c_str() );
	//	}
	//}

	if( isP2POnline() && ( false == m_Engine.getHasHostService( eHostServiceNetworkHost ) ) )
	{
		m_NetServicesMgr.announceToHost( getHostIp(), getHostPort() );
	}
}
