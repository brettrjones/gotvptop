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
}

//============================================================================
NetworkMonitor::NetworkMonitor( P2PEngine& engine )
: m_Engine( engine )
, m_bIsStarted( false )
, m_iCheckInterval( 0 )
{
}

//============================================================================
void NetworkMonitor::networkMonitorStartup( const char * preferredNetIp, const char * cellNetIp )
{
	m_strPreferredAdapterIp	= preferredNetIp;
	m_strCellNetIp			= cellNetIp;
	m_bIsStarted			= true;
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
void NetworkMonitor::onOncePerSecond( void )
{
#ifdef TARGET_OS_ANDROID
	// android monitors network in java code
	return;
#endif // TARGET_OS_ANDROID

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

	if( foundSameAsLastIp )
	{
		return;
	}

	if( foundPreferredAdapterIp )
	{
		m_strLastFoundIp = m_strPreferredAdapterIp;
		m_Engine.fromGuiNetworkAvailable( m_strLastFoundIp.c_str(), false );
		return;
	}

	if( foundCellIp )
	{
		m_strLastFoundIp = m_strCellNetIp;
		m_Engine.fromGuiNetworkAvailable( m_strLastFoundIp.c_str(), true );
		return;
	}

    static int findIpTryCnt = 0;
	if( pickAddresss.size() )
	{
		if( m_strCellNetIp.empty() && m_strPreferredAdapterIp.empty() )
		{
static int64_t timeLastAttempt = 0;
			int64_t timeNow = GetTimeStampMs();
			if( ( timeNow - timeLastAttempt ) > 10000 )
			{
                timeLastAttempt = timeNow;
                findIpTryCnt++;
                m_strLastFoundIp.clear();

				// no network ip specified..
				// picking the first one might pick one that is disconnected we need a active connection to internet
				//m_strLastFoundIp = pickAddresss[0];
				VxSktConnectSimple sktConnect;
                std::string externIp;
                m_Engine.getEngineSettings().getExternalIp( externIp );
    
				if( !m_Engine.getHasHostService( eHostServiceNetworkHost ) 
                    || ( VxIsIPv4Address( VxGetNetworkHostName() ) && !externIp.empty() && ( externIp != VxGetNetworkHostName() ) ) )
				{
                    SOCKET skt = sktConnect.connectTo( VxGetNetworkHostName(),		// remote ip or url 
                                                       VxGetNetworkHostPort(),		// port to connect to 
                                                       NET_MONITOR_CONNECT_TO_HOST_TIMOUT_MS );					    // timeout attempt to connect
                    if( INVALID_SOCKET != skt )
                    {
                        // get local address
                        InetAddrAndPort lclAddr;
                        if( 0 == VxGetLclAddress( skt, lclAddr ) )
                        {
                            m_strLastFoundIp = lclAddr.toStdString();
                            findIpTryCnt = 0;
                        }

                        VxCloseSkt( skt );
                        /* NOT REQUIRED TO VERIFY LOCAL ADAPTER IP
                        skt = sktConnect2.connectTo( m_strLastFoundIp.c_str(),                  // local adapter ip
                                                     VxGetNetworkHostName(),		            // remote ip or url
                                                     VxGetNetworkHostPort(),					// port to connect to
                                                     NET_MONITOR_CONNECT_TO_HOST_TIMOUT_MS );	// timeout attempt to connect
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
				}
				
                if( m_strLastFoundIp.empty() )
				{
					// try again but use google
                    SOCKET skt = sktConnect.connectTo( "www.google.com",		// remote ip or url
						                               80,						// port to connect to
                                                       NET_MONITOR_CONNECT_TO_HOST_TIMOUT_MS );					// timeout attempt to connect
					if( INVALID_SOCKET != skt )
					{
						// get local address
						InetAddrAndPort lclAddr;
						if( 0 == VxGetLclAddress( skt, lclAddr ) )
						{
							m_strLastFoundIp = lclAddr.toStdString();
                            findIpTryCnt = 0;
						}

						VxCloseSkt( skt );        
                        /* NOT REQUIRED TO VERIFY LOCAL ADAPTER IP
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
				}
			}
		}

		if( m_strLastFoundIp.length() )
		{
			m_Engine.fromGuiNetworkAvailable( m_strLastFoundIp.c_str(), false );
		}
		else
		{
			m_Engine.fromGuiNetworkLost();
		}

        if( findIpTryCnt > 3 )
        {
            LogMsg( LOG_ERROR, "Could Not Get Connection To Internet" );
        }

		return;
	}
	else if( m_strLastFoundIp.length() )
	{
		m_strLastFoundIp = "";
		m_Engine.fromGuiNetworkLost();
		return;
	}
}


