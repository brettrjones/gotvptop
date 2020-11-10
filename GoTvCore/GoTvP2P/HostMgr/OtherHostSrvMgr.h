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

#include "HostDefs.h"
#include "OtherHostInfo.h"

#include <GoTvCore/GoTvP2P/HostMgr/OtherHostInfo.h>
#include <GoTvCore/GoTvP2P/NetworkMonitor/NetStatusAccum.h>

#include <CoreLib/VxMutex.h>
#include <CoreLib/VxThread.h>

class P2PEngine;

class OtherHostSrvMgr : public NetAvailStatusCallbackInterface
{
public:
    OtherHostSrvMgr( P2PEngine& engine );
    void                        addHostInfo( EOtherHostType otherHostType, std::string& hostIp, uint16_t hostPort, const char * hostUrl = "" );
    void                        addHostInfo( EOtherHostType otherHostType, VxGUID onlineId, std::string& hostIp, uint16_t hostPort, const char * hostUrl );
    void                        addHostInfo( EPluginType ePluginType, VxGUID onlineId, std::string& hostIp, uint16_t hostPort, const char * hostUrl = "" );

    void                        addHostInfo( OtherHostInfo& otherHostInfo );
    // not mutex protected
    OtherHostInfo*              findHostMatch( OtherHostInfo& otherHostInfo );

    bool                        requestHostConnection( EHostConnectType connectType, IHostConnectCallback* callback, bool enableCallback );

    virtual void                onSktConnectedWithPktAnn( VxSktBase* sktBase );
    virtual void                onSktDisconnected( VxSktBase* sktBase );

    /// called by action thread
    void                        actionThreadFunction( VxThread * poThread );

    P2PEngine&                  getEngine() { return m_Engine; }

protected:
    virtual void				callbackNetAvailStatusChanged( ENetAvailStatus netAvalilStatus ) override;

    void                        startActionThread();

    //=== vars ===//
    P2PEngine&                  m_Engine;
    VxMutex                     m_HostListMutex;
    VxThread                    m_ActionThread;
    std::vector<OtherHostInfo*> m_HostInfoList;
    std::vector<OtherHostInfo*> m_HostDirtyList;    // hosts that require action like query host id
    std::vector<OtherHostInfo*> m_NeedConnectList;  // hosts that need connection 
};
