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

#include "NetworkMonitor.h"

#include "../P2PEngine/P2PEngine.h"

#include <CoreLib/VxGlobals.h>
#include <NetLib/InetAddress.h>
#include <NetLib/VxSktUtil.h>
#include <NetLib/VxSktConnectSimple.h>


#include <vector>
#include <time.h>

namespace
{
	const int NET_MONITOR_CHECK_INTERVAL_SEC = 4;
    const int NET_MONITOR_CONNECT_TO_HOST_TIMOUT_MS = 8000;

    const int NET_INTERNET_ATTEMPT_CONNECT_TIMEOUT_MS = 10000;
    const int NET_INTERNET_VERIFY_ACITIVE_TIMEOUT_MS = 55000;

    const char * NET_TEST_WEB_CONNECTION_HOST = "www.google.com";

    //============================================================================
    static void * NetworkMonitorThreadFunc( void * pvContext )
    {
        VxThread * poThread = ( VxThread * )pvContext;
        poThread->setIsThreadRunning( true );
        NetworkMonitor * netMonitor = ( NetworkMonitor * )poThread->getThreadUserParam();
        if( netMonitor )
        {
            netMonitor->doNetworkMonitoring( poThread );
        }

        poThread->threadAboutToExit();
        return nullptr;
    }
}

//============================================================================
void NetworkMonitor::doNetworkMonitoring( VxThread * startupThread )
{
    while ( !startupThread->isAborted() )
    {
        bool wasSignaled = m_NetSemaphore.wait( 1000 );
        if( startupThread->isAborted() )
        {
            return;
        }

        if( wasSignaled )
        {
            onDetermineIp();
        }
    }
}

//============================================================================
void NetworkMonitor::triggerDetermineIp( void )
{
    if( VxIsAppShuttingDown() )
    {
        return;
    }

    if(!m_NetMonitorThread.isThreadRunning() )
    {
        m_NetMonitorThread.startThread( ( VX_THREAD_FUNCTION_T )NetworkMonitorThreadFunc, this, "NetworkMonitor" );
    }

    LogMsg( LOG_DEBUG, "triggerDetermineIp" );
    m_NetSemaphore.signal();
}

//============================================================================
void NetworkMonitor::onDetermineIp( void )
{
    std::string lclIp = determineLocalIp();
    LogMsg( LOG_DEBUG, "NetworkMonitor::onDetermineIp %s", lclIp.c_str() );

    static int findIpTryCnt = 0;
    findIpTryCnt++;

    if( lclIp.length() )
    {
        findIpTryCnt = 0;
        // LogModule( eLogNetworkState, LOG_VERBOSE, " NetworkMonitor::onOncePerSecond net avail %s", lclIp.c_str() );
        if( ( lclIp != m_strLastFoundIp ) || !getIsInternetAvailable() )
        {
            m_strLastFoundIp = lclIp;
            setIsInternetAvailable( true );
            m_Engine.fromGuiNetworkAvailable( m_strLastFoundIp.c_str(), false );
        }
    }
    else
    {
        m_Engine.getNetStatusAccum().setInternetAvail( false );
        m_Engine.getNetStatusAccum().setNetHostAvail( false );

        LogModule( eLogNetworkState, LOG_INFO, " NetworkMonitor::onOncePerSecond network lost" );
        if( findIpTryCnt > 3 )
        {
            LogMsg( LOG_ERROR, "Could Not Get Connection To Internet" );
            if( getIsInternetAvailable() )
            {
                setIsInternetAvailable( false );
                m_Engine.fromGuiNetworkLost();
            }
        }
    }
}

//============================================================================
NetworkMonitor::NetworkMonitor( P2PEngine& engine )
: m_Engine( engine )
, m_bIsStarted( false )
, m_iCheckInterval( NET_MONITOR_CHECK_INTERVAL_SEC )
{
}

//============================================================================
void NetworkMonitor::networkMonitorStartup( const char * preferredNetIp, const char * cellNetIp )
{
	m_strPreferredAdapterIp	= preferredNetIp;
	m_strCellNetIp			= cellNetIp;
	m_bIsStarted			= true;
    LogModule( eLogStartup, LOG_INFO, "networkMonitorStartup preferred ip %s cell ip %s", m_strPreferredAdapterIp.c_str(), m_strCellNetIp.c_str() );
}

//============================================================================
void NetworkMonitor::networkMonitorShutdown( void )
{
	m_bIsStarted		= false;
	m_strPreferredAdapterIp	= "";
	m_strCellNetIp		= "";
	m_Engine.fromGuiNetworkLost();
}

//============================================================================
NetworkMonitor::~NetworkMonitor()
{
    m_NetMonitorThread.abortThreadRun( true );
    m_NetSemaphore.signal();
    m_NetMonitorThread.killThread();
}

//============================================================================
void NetworkMonitor::onOncePerSecond( void )
{
	if( ( false == m_bIsStarted )
		|| VxIsAppShuttingDown() )
	{
		return;
	}

	bool foundSameAsLastIp	= false;
	bool foundCellIp		= false;
	bool foundPreferredAdapterIp	= false;
	std::vector<std::string> pickAddresss;

	m_iCheckInterval++;
	if( NET_MONITOR_CHECK_INTERVAL_SEC > m_iCheckInterval )
	{
		return;
	}

	m_iCheckInterval = 0;

    /*
	//LogMsg( LOG_INFO, "NetworkStateMachine::onOncePerSecond\n" );
	m_strPreferredAdapterIp = m_Engine.getEngineSettings().getPreferredNetworkAdapterIp();

	std::vector<InetAddress> aipAddresses;
	InetAddress	netAddr;
	netAddr.getAllAddresses( aipAddresses );
    //netAddr.dumpAddresses( aipAddresses );   

	for( InetAddress& inetAddr : aipAddresses )
	{
		if( ( false == inetAddr.isIPv4() )
			|| inetAddr.isLoopBack() )
		{
			continue;
		}
		
		std::string strIp = inetAddr.toStdString();
		pickAddresss.push_back( strIp );
		if( strIp == m_strLastFoundIp )
		{
			foundSameAsLastIp = true;
			break;
		}

		if( strIp == m_strCellNetIp )
		{
			foundCellIp = true;
		}

		if( strIp == m_strPreferredAdapterIp )
		{
			foundPreferredAdapterIp = true;
		}
	}

	if( foundSameAsLastIp && getIsInternetAvailable() )
	{
        // LogModule( eLogNetworkState, LOG_INFO, " NetworkMonitor::onOncePerSecond foundSameAsLastIp" );
        return;
	}

	if( foundPreferredAdapterIp )
	{
		m_strLastFoundIp = m_strPreferredAdapterIp;
        LogModule( eLogNetworkState, LOG_INFO, " NetworkMonitor::onOncePerSecond foundPreferredAdapterIp %s", m_strLastFoundIp.c_str() );
        setIsInternetAvailable( true );
        m_Engine.fromGuiNetworkAvailable( m_strLastFoundIp.c_str(), false );
		return;
	}

	if( foundCellIp )
	{
		m_strLastFoundIp = m_strCellNetIp;
        LogModule( eLogNetworkState, LOG_INFO, " NetworkMonitor::onOncePerSecond foundCellIp %s", m_strLastFoundIp.c_str() );
        setIsInternetAvailable( true );
		m_Engine.fromGuiNetworkAvailable( m_strLastFoundIp.c_str(), true );
		return;
	}
    */

    // only reevaluate network every 10 seconds
    static int64_t timeLastAttempt = 0;
    int64_t timeNow = GetTimeStampMs();

    if( ( !getIsInternetAvailable() && ( timeNow - timeLastAttempt ) > NET_INTERNET_ATTEMPT_CONNECT_TIMEOUT_MS ) || // time to attempt internet connect/verifiy local ip 
        ( getIsInternetAvailable() && ( timeNow - timeLastAttempt ) > NET_INTERNET_VERIFY_ACITIVE_TIMEOUT_MS ) ) // time to verify internet still connected and what is local ip 
    {
        timeLastAttempt = timeNow;
        // it can take many seconds to determine ip address .. fire off a thread to do this
        triggerDetermineIp();
	}
}

//============================================================================
std::string NetworkMonitor::determineLocalIp( void )
{
    std::string localIp;
    std::string externIp;
    m_Engine.getEngineSettings().getExternalIp( externIp );

    VxSktConnectSimple sktConnect;

    if( !m_Engine.getHasHostService( eHostServiceNetworkHost )
        || ( VxIsIPv4Address( VxGetNetworkHostName() ) && !externIp.empty() && ( externIp != VxGetNetworkHostName() ) ) )
    {
        SOCKET skt = sktConnect.connectTo( VxGetNetworkHostName(),		// remote ip or url 
                                           VxGetNetworkHostPort(),		// port to connect to 
                                           NET_MONITOR_CONNECT_TO_HOST_TIMOUT_MS );	// timeout attempt to connect
        if( INVALID_SOCKET != skt )
        {
            // get local address
            InetAddrAndPort lclAddr;
            if( 0 == VxGetLclAddress( skt, lclAddr ) )
            {
                localIp = lclAddr.toStdString();
                m_Engine.getNetStatusAccum().setIpAddress( localIp );
                m_Engine.getNetStatusAccum().setIpPort( m_Engine.getEngineSettings().getTcpIpPort() );
                m_Engine.getNetStatusAccum().setInternetAvail( true );
                m_Engine.getNetStatusAccum().setNetHostAvail( true );
            }

            VxCloseSkt( skt );
        }
    }

    if( localIp.empty() )
    {
        LogModule( eLogNetworkState, LOG_WARNING, "Failed verify No Limit Hosted internet conection to %s:%d", VxGetNetworkHostName(), VxGetNetworkHostPort() );

        // try again but use google
        SOCKET skt = sktConnect.connectTo( NET_TEST_WEB_CONNECTION_HOST,		// remote ip or url
                                           80,						// port to connect to
                                           NET_MONITOR_CONNECT_TO_HOST_TIMOUT_MS );	// timeout attempt to connect
        if( INVALID_SOCKET != skt )
        {
            // get local address
            InetAddrAndPort lclAddr;
            if( 0 == VxGetLclAddress( skt, lclAddr ) )
            {
                localIp = lclAddr.toStdString();
                m_Engine.getNetStatusAccum().setIpAddress( localIp );
                m_Engine.getNetStatusAccum().setIpPort( m_Engine.getEngineSettings().getTcpIpPort() );
                m_Engine.getNetStatusAccum().setInternetAvail( true );
             }

            VxCloseSkt( skt );
            /* NOT REQUIRED TO VERIFY LOCAL ADAPTER IP.. also while using VPN specifing local ip address causes issues
            skt = sktConnect2.connectTo( m_strLastFoundIp.c_str(),  // local adapter ip
                                         "www.google.com",		    // remote ip or url
                                         80,						// port to connect to
                                         NET_MONITOR_CONNECT_TO_HOST_TIMOUT_MS );					// timeout attempt to connect
            if( INVALID_SOCKET != skt )
            {
                VxCloseSkt( skt );
            }
            else
            {
                m_strLastFoundIp.clear();
            }
            */
        }

        if( localIp.empty() )
        {
            LogModule( eLogNetworkState, LOG_WARNING, "Failed verify internet conection to %s:%d", NET_TEST_WEB_CONNECTION_HOST, VxGetNetworkHostName(), 80 );
        }
    }

    return localIp;
}


