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

#include "OtherHostInfo.h"

//============================================================================
OtherHostInfo::OtherHostInfo( const OtherHostInfo& rhs )
    : HostInfoBase(rhs)
    , m_SrvMgr(rhs.m_SrvMgr)
    , m_NeedHostQueryId( rhs.m_NeedHostQueryId )
{
}

//============================================================================
OtherHostInfo::OtherHostInfo( OtherHostSrvMgr* srvMgr, EOtherHostType otherHostType, std::string& hostIp, uint16_t hostPort, const char * hostUrl )
    : HostInfoBase( otherHostType, hostIp, hostPort, hostUrl )
    , m_SrvMgr( srvMgr )
{
}

//============================================================================
OtherHostInfo::OtherHostInfo( OtherHostSrvMgr* srvMgr, EOtherHostType otherHostType, VxGUID onlineId, std::string& hostIp, uint16_t hostPort, const char * hostUrl )
    : HostInfoBase( otherHostType, onlineId, hostIp, hostPort, hostUrl )
    , m_SrvMgr( srvMgr )
{
}

//============================================================================
OtherHostInfo::OtherHostInfo( OtherHostSrvMgr* srvMgr, EPluginType ePluginType, VxGUID onlineId, std::string& hostIp, uint16_t hostPort, const char * hostUrl )
    : HostInfoBase( ePluginType, onlineId, hostIp, hostPort, hostUrl )
    , m_SrvMgr( srvMgr )
{
}

//============================================================================
OtherHostInfo& OtherHostInfo::operator=( const OtherHostInfo& rhs )
{
    getHostInfoBase() = rhs;
    // set derive class member vars
    m_SrvMgr = rhs.m_SrvMgr;
    m_NeedHostQueryId = rhs.m_NeedHostQueryId;

    return *this;
}

//============================================================================
bool OtherHostInfo::operator==( const OtherHostInfo& rhs )
{
    bool isEqual = getHostInfoBase() == const_cast< OtherHostInfo&>(rhs).getHostInfoBase();
    if( isEqual )
    {
        // compare derived class members
        isEqual = m_NeedHostQueryId == rhs.m_NeedHostQueryId;
    }

    return isEqual;
}
