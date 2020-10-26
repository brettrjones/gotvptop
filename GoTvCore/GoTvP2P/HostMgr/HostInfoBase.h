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

#include "HostDefs.h"
#include <GoTvInterface/IDefs.h>

#include <CoreLib/VxGUID.h>

#include <vector>

class HostInfoBase
{
public:
    HostInfoBase() = default;
    virtual ~HostInfoBase() = default;

    HostInfoBase( const HostInfoBase& rhs );
    HostInfoBase( EOtherHostType otherHostType, std::string& hostIp, uint16_t hostPort, const char * hostUrl );
    HostInfoBase( EOtherHostType otherHostType, VxGUID onlineId, std::string& hostIp, uint16_t hostPort, const char * hostUrl );
    HostInfoBase( EPluginType ePluginType, VxGUID onlineId, std::string& hostIp, uint16_t hostPort, const char * hostUrl );

    HostInfoBase&				operator=( const HostInfoBase& rhs );
    bool                        operator==( const HostInfoBase& rhs );

    HostInfoBase&               getHostInfoBase( void ) { return *this; }

    void                        setOtherHostType( EOtherHostType hostType );
    EOtherHostType              getOtherHostType( void )                        { return m_HostType; }

    void                        setRequiresAction( bool needAction )            { m_RequiresAction = needAction; }
    bool                        getRequiresAction( void )                       { return m_RequiresAction; }

    void                        setHostOnlineId( VxGUID& onlineId )     { m_OnlineId = onlineId; }
    VxGUID&                     getHostOnlineId( void )                 { return m_OnlineId; }
    void                        setHostIpAddr( std::string& ipAddr )    { m_HostIpAddr = ipAddr; }
    std::string&                getHostIpAddr( void )                   { return m_HostIpAddr; }
    void                        setHostPort( uint16_t port )            { m_HostPort = port; }
    uint16_t                    getHostPort( void )                     { return m_HostPort; }
    void                        setHostUrl( const char * url )          { m_HostUrl = url ? url : ""; }
    std::string&                getHostUrl( void )                      { return m_HostUrl; }

    std::vector<EPluginType>&   getPluginList( void )                   { return m_PluginList; }

    void                        addPluginService( EPluginType pluginType );
    void                        addPluginService( HostInfoBase& rhs );
    void                        removePluginService( EPluginType pluginType );
    bool                        hasPluginService( EPluginType pluginType );

    /// return true if matches host type and either online id or ip and port
    virtual bool                isMatch( HostInfoBase& rhs );

protected:
    EOtherHostType              m_HostType{ eOtherHostUnknown };
    std::vector<EPluginType>    m_PluginList;
    std::string                 m_HostUrl{ "" };
    std::string                 m_HostIpAddr{ "" };
    uint16_t                    m_HostPort{ 0 };
    VxGUID                      m_OnlineId;
    bool                        m_RequiresAction{ false };
};



