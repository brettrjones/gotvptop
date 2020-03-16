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
#pragma once

#include <GoTvCore/GoTvP2P/P2PEngine/EngineSettings.h>
#include <NetLib/NetHostSetting.h>
#include <QString>

class AppletNetworkSettingsData
{
public:
    AppletNetworkSettingsData() = default;
    virtual ~AppletNetworkSettingsData() = default;

    AppletNetworkSettingsData&	operator =( const AppletNetworkSettingsData& rhs ) = default;
    bool						operator == ( const AppletNetworkSettingsData& rhs ) const;
    bool						operator != ( const AppletNetworkSettingsData& rhs ) const;

    void                        setNetHostSetting( NetHostSetting& netHostSetting ) { m_NetHostSetting = netHostSetting;  }
    NetHostSetting&             getNetHostSetting( void ) { return m_NetHostSetting; }

    void                        setPreferredNetworkAdapterIp( std::string& preferredAdaptIp ) { m_PreferredNetworkAdapterIp = preferredAdaptIp; }
    std::string&                getPreferredNetworkAdapterIp( void ) { return m_PreferredNetworkAdapterIp; }
    void                        setTcpPort( uint16_t tcpPort ) { m_TcpPort = tcpPort; }
    uint16_t                    getTcpPort( void ) { return m_TcpPort; }
    void                        setExternalIp( std::string& externIp ) { m_ExternalIp = externIp; }
    std::string&                getExternalIp( void ) { return m_ExternalIp; }
    void                        setFirewallTestType( EngineSettings::EFirewallTestType firewallTestType ) { m_FirewallTestType = firewallTestType; }
    EngineSettings::EFirewallTestType getFirewallTestType( void ) { return m_FirewallTestType; }
    void                        setUseUpnpPortForward( bool useUpnp ) { m_UseUpnp = useUpnp; }
    bool                        getUseUpnpPortForward( void ) { return m_UseUpnp; }

    //=== vars ===//
    NetHostSetting				m_NetHostSetting;
    std::string					m_PreferredNetworkAdapterIp;
    uint16_t                    m_TcpPort{ NET_DEFAULT_NETSERVICE_PORT };
    std::string					m_ExternalIp;
    EngineSettings::EFirewallTestType m_FirewallTestType{ EngineSettings::EFirewallTestType::eFirewallTestUrlConnectionTest };
    bool					    m_UseUpnp{ false };
};

