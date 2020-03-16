#include "AppletNetworkSettingsData.h"
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

#include "AppletNetworkSettingsData.h"

//============================================================================
bool AppletNetworkSettingsData::operator == ( const AppletNetworkSettingsData& rhs ) const
{
    return ( m_NetHostSetting == rhs.m_NetHostSetting )
        && m_PreferredNetworkAdapterIp == rhs.m_PreferredNetworkAdapterIp
        && m_TcpPort == rhs.m_TcpPort
        && m_ExternalIp == rhs.m_ExternalIp
        && m_FirewallTestType == rhs.m_FirewallTestType
        && m_UseUpnp == rhs.m_UseUpnp;
}

//============================================================================
bool AppletNetworkSettingsData::operator != ( const AppletNetworkSettingsData& rhs ) const
{
    return !( *this == rhs );
}
