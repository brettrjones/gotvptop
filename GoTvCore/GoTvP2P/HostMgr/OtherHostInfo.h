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

#include "HostInfoBase.h"

#include <CoreLib/VxMutex.h>

class RcConnectInfo;
class OtherHostSrvMgr;

class OtherHostInfo : public HostInfoBase
{
public:
    OtherHostInfo() = delete;
    virtual ~OtherHostInfo() = default;

    OtherHostInfo( const OtherHostInfo& rhs );
    OtherHostInfo( OtherHostSrvMgr* srvMgr, EOtherHostType otherHostType, std::string& hostIp, uint16_t hostPort, const char * hostUrl );
    OtherHostInfo( OtherHostSrvMgr* srvMgr, EOtherHostType otherHostType, VxGUID onlineId, std::string& hostIp, uint16_t hostPort, const char * hostUrl );
    OtherHostInfo( OtherHostSrvMgr* srvMgr, EPluginType ePluginType, VxGUID onlineId, std::string& hostIp, uint16_t hostPort, const char * hostUrll );

    OtherHostInfo&				operator=( const OtherHostInfo& rhs );
    bool        				operator==( const OtherHostInfo& rhs );

    virtual bool                requiresAction( void ) override;
    void                        setNeedQueryHostId( bool needQuery )        { m_NeedHostQueryId = needQuery; }
    bool                        getNeedQueryHostId( void )                  { return m_NeedHostQueryId; }
    void                        setFailedActionCnt( int failedCnt )         { m_FailedActionCnt = failedCnt; }
    int                         getFailedActionCnt( void )                  { return m_FailedActionCnt; }

protected:
    //=== vars ===//
    OtherHostSrvMgr*            m_SrvMgr{ nullptr };
    VxMutex                     m_CallbackMutex;
    std::vector<IHostConnectCallback *> m_ConnectionCallbacks;
    bool                        m_NeedHostQueryId{ false };
    int                         m_FailedActionCnt{ 0 };

};


