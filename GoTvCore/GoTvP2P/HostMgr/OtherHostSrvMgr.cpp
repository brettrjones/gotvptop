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

#include "OtherHostSrvMgr.h"
#include "OtherHostInfo.h"

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>

//============================================================================
OtherHostSrvMgr::OtherHostSrvMgr( P2PEngine& engine )
    : m_Engine( engine )
{

}

//============================================================================
void OtherHostSrvMgr::callbackNetAvailStatusChanged( ENetAvailStatus netAvalilStatus )
{
    LogMsg( LOG_DEBUG, "OtherHostSrvMgr callbackNetAvailStatusChanged %s", DescribeNetAvailStatus( netAvalilStatus ));
}

//============================================================================
void OtherHostSrvMgr::addHostInfo( EOtherHostType otherHostType, std::string& hostIp, uint16_t hostPort, const char * hostUrl )
{
    bool needQueryHostId = otherHostType == eOtherHostNetworkHost;
    OtherHostInfo otherHostInfo( this, otherHostType, hostIp, hostPort, hostUrl );
    otherHostInfo.setNeedQueryHostId( needQueryHostId );
    addHostInfo( otherHostInfo );
}

//============================================================================
void OtherHostSrvMgr::addHostInfo( EOtherHostType otherHostType, VxGUID onlineId, std::string& hostIp, uint16_t hostPort, const char * hostUrl )
{
    OtherHostInfo otherHostInfo( this, otherHostType, onlineId, hostIp, hostPort, hostUrl );
    addHostInfo( otherHostInfo );
}

//============================================================================
void OtherHostSrvMgr::addHostInfo( EPluginType ePluginType, VxGUID onlineId, std::string& hostIp, uint16_t hostPort, const char * hostUrl )
{
    OtherHostInfo otherHostInfo( this, ePluginType, onlineId, hostIp, hostPort, hostUrl );
    addHostInfo( otherHostInfo );
}

//============================================================================
void OtherHostSrvMgr::addHostInfo( OtherHostInfo& otherHostInfo )
{
    m_HostListMutex.lock();
    OtherHostInfo *hostInfo = findHostMatch( otherHostInfo );
    if( hostInfo )
    {
        hostInfo->addPluginService( otherHostInfo );
    }
    else
    {
        m_HostInfoList.push_back( otherHostInfo );
    }

    m_HostListMutex.unlock();
}

//============================================================================
OtherHostInfo* OtherHostSrvMgr::findHostMatch( OtherHostInfo& otherHostInfo )
{
    OtherHostInfo* foundEntry = nullptr;
    for( auto iter = m_HostInfoList.begin(); iter != m_HostInfoList.end(); ++iter )
    {
        OtherHostInfo& hostEntry = *iter;
        if( hostEntry.isMatch( otherHostInfo ) )
        {
            foundEntry = &( *iter );
            break;
        }
    }

    return foundEntry;
}

//============================================================================
void OtherHostSrvMgr::requestHostConnection( EHostConnectType connectType, IHostConnectCallback* callback )
{
    /*
    bool alreadyConnected = false;


    if( callback )
    {
        m_CallbackMutex.lock();
        bool alreadyExists = false;
        callback->addHostConnectType( connectType );
        // make sure not a duplicate
        for( auto cb : m_ConnectionCallbacks )
        {
            if( cb == callback )
            {
                alreadyExists = true;
                break;
            }
        }

        if( !alreadyExists )
        {
            m_ConnectionCallbacks.push_back( callback );
        }

        // see if we already have a connection
        for( auto hostInfo : m_HostConnectList )
        {
            if( hostInfo.hasHostService( connectType ) && hostInfo.isConnected( connectType ))
            {
                m_Engine.getConnectList().connectListLock();
                alreadyConnected = true;
                callback->onContactConnected( connectType, hostInfo.getConnectInfo(), true );
                m_Engine.getConnectList().connectListUnlock();
                break;
            }
        }

        m_CallbackMutex.unlock();
    }

    if( !alreadyConnected )
    {
        // do the connection request
    }
    */
}

//============================================================================
void OtherHostSrvMgr::onEngineContactConnected( RcConnectInfo * poInfo, bool connectionListLocked )
{

}

//============================================================================
void OtherHostSrvMgr::onEngineContactDisconnected( RcConnectInfo * poInfo, bool connectionListLocked )
{

}
