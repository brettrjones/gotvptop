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

#include <NetLib/VxSktBase.h>

namespace
{
    //============================================================================
    static void * OtherHostSrvMgrThreadFunc( void * pvContext )
    {
        VxThread * poThread = ( VxThread * )pvContext;
        poThread->setIsThreadRunning( true );
        OtherHostSrvMgr * poMgr = ( OtherHostSrvMgr * )poThread->getThreadUserParam();
        if( poMgr )
        {
            poMgr->actionThreadFunction( poThread );
        }

        poThread->threadAboutToExit();
        return nullptr;
    }
}


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
void OtherHostSrvMgr::startActionThread()
{
    if( !m_ActionThread.isThreadRunning() )
    {
        m_ActionThread.startThread( ( VX_THREAD_FUNCTION_T )OtherHostSrvMgrThreadFunc, this, "OtherHostSrvMgrThreadFunc" );
    }
}

//============================================================================
/// called by action thread
void OtherHostSrvMgr::actionThreadFunction( VxThread * poThread )
{
    while( m_HostDirtyList.size() )
    {
        bool actionTacken = false;
        m_HostListMutex.lock();
        if( m_HostDirtyList.size() )
        {
            OtherHostInfo* otherHostSave = m_HostDirtyList.front();
            if( !otherHostSave->isActionTakenTimeExpired() )
            {
                // have action but it has not timed out since last attempt
                m_HostListMutex.unlock();
                VxSleep( 5000 );
                continue;
            }

            // we make a copy of the host info we need to avoid locking the list for long periods while performing action
            m_HostDirtyList.erase( m_HostDirtyList.begin() );
            OtherHostInfo otherHostInfo = *otherHostSave;
            m_HostListMutex.unlock();

            bool actionSuccess = false;
            if( otherHostInfo.getNeedQueryHostId() && otherHostInfo.isActionTakenTimeExpired() )
            {
                actionTacken = true; 
                VxGUID hostId;
                if( otherHostInfo.doActionQueryHostId( hostId ) && hostId.isVxGUIDValid() )
                {
                    m_HostListMutex.lock();
                    OtherHostInfo* listInfo = findHostMatch( otherHostInfo );
                    if( listInfo )
                    {
                        listInfo->setHostOnlineId( hostId );
                        listInfo->setNeedQueryHostId( false );
                        listInfo->setFailedActionCnt( 0 );
                        if( !listInfo->requiresAction() && listInfo->needConnection() )
                        {
                            m_NeedConnectList.push_back( listInfo );
                        }
                    }

                    actionSuccess = true;
                    m_HostListMutex.unlock();
                }
            }

            if( !actionSuccess )
            {
                m_HostListMutex.lock();
                OtherHostInfo* listInfo = findHostMatch( otherHostInfo );
                if( listInfo )
                {
                    int failedActionCnt = listInfo->getFailedActionCnt();
                    listInfo->setFailedActionCnt( failedActionCnt + 1 );
                    listInfo->updateActionTakenTime();

                    /// TODO  should probably quit trying or expand time between attempts
                    // for now just put it at the end of the action required list
                    m_HostDirtyList.push_back( listInfo );
                }

                m_HostListMutex.unlock();
            }
        }
        else
        {
            m_HostListMutex.unlock();
        }
    }
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
    bool actionNeeded = false;
    m_HostListMutex.lock();
    OtherHostInfo *hostInfo = findHostMatch( otherHostInfo );
    if( hostInfo )
    {
        hostInfo->addPluginService( otherHostInfo );
    }
    else
    {
        hostInfo = new OtherHostInfo( otherHostInfo );
        m_HostInfoList.push_back( hostInfo );
    }

    if( hostInfo && hostInfo->requiresAction() )
    {
        // first see if already in the action list
        bool isInList = false;
        for( auto hostEntry : m_HostDirtyList )
        {
            if( ( hostEntry == hostInfo ) || hostEntry->isMatch( *hostInfo ) )
            {
                isInList = true;
                break;
            }
        }

        if( !isInList )
        {
            m_HostDirtyList.push_back( hostInfo );
            actionNeeded = true;
        }
    }

    m_HostListMutex.unlock();
    if( actionNeeded )
    {
        startActionThread();
    }
}

//============================================================================
OtherHostInfo* OtherHostSrvMgr::findHostMatch( OtherHostInfo& otherHostInfo )
{
    OtherHostInfo* foundEntry = nullptr;
    for( auto iter = m_HostInfoList.begin(); iter != m_HostInfoList.end(); ++iter )
    {
        OtherHostInfo* hostEntry = *iter;
        if( hostEntry->isMatch( otherHostInfo ) )
        {
            foundEntry = ( *iter );
            break;
        }
    }

    return foundEntry;
}

/*
//============================================================================
EOtherHostType OtherHostSrvMgr::connectTypeToHostType( EHostConnectType connectType )
{
    EOtherHostType hostType = eOtherHostUnknown;
    switch( connectType )
    {
    case eHostConnectGroupFind:
    case eHostConnectGroupAnnounce:
        hostType = eOtherHostNetworkHost;
        break;

    case eHostConnectRelayFind:
    case eHostConnectRelayJoin:
    case eHostConnectGroupJoin:
        hostType = eOtherHostGroupHost;
        break;

    case eHostConnectChatRoomAnnounce:
    case eHostConnectChatRoomFind:
    case eHostConnectChatRoomJoin:
        hostType = eOtherHostChatHost;
        break;

    default:
        break;
    }

    return hostType;
}
*/

//============================================================================
bool OtherHostSrvMgr::requestHostConnection( EHostConnectType connectType, IHostConnectCallback* callback, bool enableCallback )
{
    bool addedOrExists = false;
    EOtherHostType hostType = HostInfoBase::connectTypeToHostType( connectType );
    if( callback && ( hostType != eOtherHostUnknown ) )
    {
        callback->addHostConnectType( connectType );
        m_HostListMutex.lock();

        bool wasTypeFound = false;
        std::vector<VxSktBase *> sktList;

        for( OtherHostInfo* hostEntry : m_HostInfoList )
        {
            if( hostType == hostEntry->getOtherHostType() )
            {
                if( enableCallback )
                {
                    addedOrExists |= hostEntry->addConnectionRequest( connectType, callback );
                }
                else
                {
                    bool callbackRemoved = hostEntry->removeConnectionRequest( connectType, callback );
                    addedOrExists |= callbackRemoved;
                    if( callbackRemoved )
                    {
                        hostEntry->addToSktListIfSktNotInUse( sktList );
                    }
                }
            }
        }

        if( !enableCallback && addedOrExists && !sktList.empty() )
        {
            // decide if we can close a skt because no longer needed
            std::vector<VxSktBase *> sktList;
            for( auto sktBase : sktList )
            {
                bool isSktInUse = false;
                for( OtherHostInfo* hostEntry : m_HostInfoList )
                {
                    if( hostType == hostEntry->getOtherHostType() )
                    {
                        if( hostEntry->isSktInUse( sktBase ) )
                        {
                            isSktInUse = true;
                            break;
                        }
                    }
                }

                if( !isSktInUse )
                {
                    // we are done with socket
                    sktBase->closeSkt(444, true);
                }
            }
        }

        m_HostListMutex.unlock();
    }
    else
    {
        LogMsg( LOG_ERROR, "OtherHostSrvMgr::requestHostConnection null callback" );
    }

    return addedOrExists;
}

//============================================================================
void OtherHostSrvMgr::onSktConnectedWithPktAnn( VxSktBase* sktBase )
{
    m_HostListMutex.lock();
    for( OtherHostInfo* hostInfo : m_HostInfoList )
    {
        hostInfo->onSktConnectedWithPktAnn( sktBase );
    }

    m_HostListMutex.unlock();
}

//============================================================================
void OtherHostSrvMgr::onSktDisconnected( VxSktBase* sktBase )
{
    m_HostListMutex.lock();
    for( OtherHostInfo* hostInfo : m_HostInfoList )
    {
        hostInfo->onSktDisconnected( sktBase );
    }

    m_HostListMutex.unlock();
}
