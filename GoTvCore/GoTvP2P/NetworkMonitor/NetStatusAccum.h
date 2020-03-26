#pragma once
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

#include <GoTvInterface/IDefs.h>
#include <CoreLib/VxMutex.h>

class P2PEngine;

// network state accumulator
class NetStatusAccum
{
public:
    NetStatusAccum( P2PEngine& toGui );
    virtual ~NetStatusAccum() = default;

    void                        resetNetStatus( void );

    void                        setInternetAvail( bool avail );
    void                        setNetHostAvail( bool avail );
    void                        setConnectionTestAvail( bool avail );
    void                        setDirectConnectTested( bool isTested, bool requiresRelay = false );
    void                        setConnectToRelay( bool connectedToRelay );
    void                        setIpAddress( std::string& ipAddr );
    void                        setIpPort( uint16_t ipPort );

    bool                        isInternetAvailable( void )       { return m_InternetAvail; };
    bool                        isNetHostAvailable( void )        { return m_NetworkHostAvail; };
    bool                        isDirectConnectTested( void )     { return m_DirectConnectTested; };
    bool                        isP2PAvailable( void )            { return m_DirectConnectTested && (!m_RequriesRelay || m_ConnectedToRelay); };
    bool                        requiresRelay( void )             { return m_RequriesRelay; };
    void                        getNodeUrl( std::string& retNodeUrl );
    std::string                 getIpAddress( void );
    uint16_t                    getIpPort( void );

protected:
    void                        onNetStatusChange( void );

    P2PEngine&					m_Engine;
    VxMutex                     m_AccumMutex;

    bool                        m_InternetAvail{ false };
    bool                        m_NetworkHostAvail{ false };
    bool                        m_ConnectionTestAvail{ false };
    bool                        m_DirectConnectTested{ false };
    bool                        m_RequriesRelay{ false };
    bool                        m_ConnectedToRelay{ false };
    bool                        m_GroupListHostAvail{ false };
    bool                        m_GroupHostAvail{ false };
    bool                        m_IsConnectedGroupHost{ false };
    std::string                 m_IpAddr;
    uint16_t                    m_IpPort{ 0 };
};
