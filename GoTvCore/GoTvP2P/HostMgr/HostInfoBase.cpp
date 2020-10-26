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

#include "HostInfoBase.h"

//============================================================================
HostInfoBase::HostInfoBase( const HostInfoBase& rhs )
{
    *this = rhs;
}

//============================================================================
HostInfoBase::HostInfoBase( EOtherHostType otherHostType, std::string& hostIp, uint16_t hostPort, const char * hostUrl )
{
    setOtherHostType( otherHostType );
    m_HostIpAddr = hostIp;
    m_HostPort = hostPort;
    m_HostUrl = hostUrl ? hostUrl : "";
}

//============================================================================
HostInfoBase::HostInfoBase( EOtherHostType otherHostType, VxGUID onlineId, std::string& hostIp, uint16_t hostPort, const char * hostUrl )
{
    setOtherHostType( otherHostType );
    m_OnlineId = onlineId;
    m_HostIpAddr = hostIp;
    m_HostPort = hostPort;
    m_HostUrl = hostUrl ? hostUrl : "";
}

//============================================================================
HostInfoBase::HostInfoBase( EPluginType ePluginType, VxGUID onlineId, std::string& hostIp, uint16_t hostPort, const char * hostUrl )
{
    addPluginService( ePluginType );
    m_OnlineId = onlineId;
    m_HostIpAddr = hostIp;
    m_HostPort = hostPort;
    m_HostUrl = hostUrl ? hostUrl : "";
}

//============================================================================
HostInfoBase& HostInfoBase::operator=( const HostInfoBase& rhs )
{
    if( this != &rhs )
    {
        m_HostType = rhs.m_HostType;
        m_PluginList = rhs.m_PluginList;
        m_HostUrl = rhs.m_HostUrl;
        m_HostIpAddr = rhs.m_HostIpAddr;
        m_HostPort = rhs.m_HostPort;
        m_OnlineId = rhs.m_OnlineId;
        m_RequiresAction = rhs.m_RequiresAction;
    }

    return *this;
}

//============================================================================
bool HostInfoBase::operator==( const HostInfoBase& rhs )
{
    return  m_HostType == rhs.m_HostType &&
        m_PluginList == rhs.m_PluginList &&
        m_HostUrl == rhs.m_HostUrl &&
        m_HostIpAddr == rhs.m_HostIpAddr &&
        m_HostPort == rhs.m_HostPort &&
        m_OnlineId == rhs.m_OnlineId &&
        m_RequiresAction == rhs.m_RequiresAction;
}

//============================================================================
void HostInfoBase::addPluginService( EPluginType pluginType )
{
    if( !hasPluginService( pluginType ) )
    {
        m_PluginList.push_back( pluginType );
    }

    if( m_HostType == eOtherHostUnknown )
    {
        switch( pluginType )
        {
        case ePluginTypeChatRoom:
            m_HostType = eOtherHostChatHost;
            break;
        case ePluginTypeHostGroup:
            m_HostType = eOtherHostGroupHost;
            break;
        case ePluginTypeServiceConnectTest:
            m_HostType = eOtherHostConnectTest;
            break;
        case ePluginTypeHostNetwork:
            m_HostType = eOtherHostNetworkHost;
            break;

        default:
            // do nothing
            break;
        }
    }
}

//============================================================================
void HostInfoBase::addPluginService( HostInfoBase& rhs )
{
    for( auto pluginType : rhs.getPluginList() )
    {
        addPluginService( pluginType );
    }
}

//============================================================================
void HostInfoBase::removePluginService( EPluginType pluginType )
{
    for( auto iter = m_PluginList.begin(); iter != m_PluginList.end(); ++iter )
    {
        if( *iter == pluginType )
        {
            m_PluginList.erase( iter );
            break;
        }
    }
}

//============================================================================
bool HostInfoBase::hasPluginService( EPluginType pluginType )
{
    for( auto plugin : m_PluginList )
    {
        if( plugin == pluginType )
        {
            return true;
        }
    }

    return false;
}

//============================================================================
void HostInfoBase::setOtherHostType( EOtherHostType hostType )
{
    m_HostType = hostType;

    switch( m_HostType )
    {
    case eOtherHostNetworkHost:
        // network host always provides group listing and optionally connection test
        addPluginService( ePluginTypeHostGroupListing );
        break;
    case eOtherHostConnectTest:
        addPluginService( ePluginTypeServiceConnectTest );
        break;
    case eOtherHostGroupHost:
        addPluginService( ePluginTypeHostGroup );
        break;
    case eOtherHostChatHost:
        addPluginService( ePluginTypeChatRoom );
        break;
  
    case eOtherPeerUserHost:
    case eOtherHostUnknown:
    default:
        // do nothing
        break;
    }
}

//============================================================================
/// return true if matches host type and either online id or ip and port
bool HostInfoBase::isMatch( HostInfoBase& rhs )
{
    bool matches = false;
    if( m_HostType == rhs.getOtherHostType() )
    {
        if( m_OnlineId.isVxGUIDValid() && m_OnlineId == rhs.getHostOnlineId() )
        {
            // matches id.. should always be unique
            // TODO check for duplicate GUID Hack
            matches = true;
        }
        else if( !m_HostIpAddr.empty() && m_HostIpAddr == rhs.getHostIpAddr() && m_HostPort == rhs.getHostPort() )
        {
            matches = true;
        }
    }

    return matches;
}