//============================================================================
// Copyright (C) 2020 Brett R. Jones 
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

#include "NetStatusAccum.h"

#include "../P2PEngine/P2PEngine.h"
#include <GoTvInterface/IToGui.h>

#include <CoreLib/VxGlobals.h>

//============================================================================
NetStatusAccum::NetStatusAccum( P2PEngine& engine )
    : m_Engine(engine)
{
}

//============================================================================
void NetStatusAccum::resetNetStatus( void )
{
    m_InternetAvail = false;
    m_NetworkHostAvail = false;
    m_ConnectionTestAvail = false;
    m_DirectConnectTested = false;
    m_RequriesRelay = false;
    m_ConnectedToRelay = false;
    m_GroupListHostAvail = false;
    m_GroupHostAvail = false;
    m_IsConnectedGroupHost = false;

    onNetStatusChange();
}

//============================================================================
void NetStatusAccum::onNetStatusChange( void )
{
    ENetAvailStatus netAvailStatus = eNetAvailNoInternet;
    if( m_NetworkHostAvail )
    {
        netAvailStatus = eNetAvailHostAvail;
        if( m_DirectConnectTested )
        {
            netAvailStatus = eNetAvailP2PAvail;
            if( m_GroupHostAvail || !m_GroupHostAvail ) // TODO implement group available status
            {
                netAvailStatus = eNetAvailGroupHost;
                if( requiresRelay() )
                {
                    if( m_ConnectedToRelay )
                    {
                        netAvailStatus = eNetAvailFullOnlineWithRelay;
                    }
                }
                else
                {
                    netAvailStatus = eNetAvailFullOnlineDirectConnect;
                }
            }
        }
    }

    m_Engine.getToGui().toGuiNetAvailableStatus( netAvailStatus );
}

//============================================================================
void NetStatusAccum::setInternetAvail( bool avail )
{
    if( avail != m_InternetAvail )
    {
        m_InternetAvail = avail;
        LogModule( eLogNetAccessStatus, LOG_VERBOSE, "Internet available %d", avail );
        onNetStatusChange();
    }
}

//============================================================================
void NetStatusAccum::setNetHostAvail( bool avail )
{
    if( avail != m_NetworkHostAvail )
    {
        m_NetworkHostAvail = avail;
        LogModule( eLogNetAccessStatus, LOG_VERBOSE, "Network Host available %d", avail );
        onNetStatusChange();
    }
}

//============================================================================
void NetStatusAccum::setConnectionTestAvail( bool avail )
{
    if( avail != m_ConnectionTestAvail )
    {
        m_ConnectionTestAvail = avail;
        LogModule( eLogNetAccessStatus, LOG_VERBOSE, "Connection Test available %d", avail );
        onNetStatusChange();
    }
}

//============================================================================
void NetStatusAccum::setDirectConnectTested( bool isTested, bool requiresRelay )
{
    if( isTested != m_DirectConnectTested || requiresRelay != m_RequriesRelay )
    {
        m_DirectConnectTested = isTested;
        m_RequriesRelay = requiresRelay;
        LogModule( eLogNetAccessStatus, LOG_VERBOSE, "Direct Connect Tested %d relay required ? %d", isTested, requiresRelay );
        onNetStatusChange();
    }
}

//============================================================================
void NetStatusAccum::setConnectToRelay( bool connectedToRelay )
{
    if( connectedToRelay != m_ConnectedToRelay )
    {
        m_ConnectedToRelay = connectedToRelay;
        LogModule( eLogNetAccessStatus, LOG_VERBOSE, "Connected to relay %d", connectedToRelay );
        onNetStatusChange();
    }
}

//============================================================================
void NetStatusAccum::setIpAddress( std::string& ipAddr )
{
    m_AccumMutex.lock();
    m_IpAddr = ipAddr;
    m_AccumMutex.unlock();
}

//============================================================================
void NetStatusAccum::setIpPort( uint16_t ipPort )
{
    m_AccumMutex.lock();
    m_IpPort = ipPort;
    m_AccumMutex.unlock();
}

//============================================================================
void NetStatusAccum::getNodeUrl( std::string& retNodeUrl )
{
    if( !isInternetAvailable() )
    {
        retNodeUrl = "No Internet Connection";
    }
    else
    {
        retNodeUrl = "ptop://";
        retNodeUrl += getIpAddress();
        retNodeUrl += ":";
        retNodeUrl += std::to_string( m_IpPort );
    }
}

//============================================================================
std::string NetStatusAccum::getIpAddress( void )
{
    std::string ipAddr;
    m_AccumMutex.lock();
    ipAddr = m_IpAddr;
    m_AccumMutex.unlock();
    return ipAddr;
}

//============================================================================
uint16_t NetStatusAccum::getIpPort( void )
{
    uint16_t port = 0;
    m_AccumMutex.lock();
    port = m_IpPort;
    m_AccumMutex.unlock();
    return port;
}
