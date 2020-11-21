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
#include <NetLib/VxSktConnect.h>
#include <NetLib/VxPeerMgr.h>
#include <CoreLib/VxGlobals.h>

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
    if( !m_ActionThread.isThreadRunning() && !VxIsAppShuttingDown() )
    {
        m_ActionThread.startThread( ( VX_THREAD_FUNCTION_T )OtherHostSrvMgrThreadFunc, this, "OtherHostSrvMgrThreadFunc" );
    }
    else if( VxIsAppShuttingDown() )
    {
        shutdownOtherHostSrvMgr();
    }
}

//============================================================================
void OtherHostSrvMgr::shutdownOtherHostSrvMgr()
{
    m_ActionThread.abortThreadRun( true );
}

//============================================================================
/// called by action thread
void OtherHostSrvMgr::actionThreadFunction( VxThread * poThread )
{
    while( !poThread->isAborted() && !VxIsAppShuttingDown() )
    {
        bool actionTaken = executeHostActions();
        actionTaken |= executeHostConnections();

        if( !actionTaken )
        {
            // have action but it has not timed out since last attempt
            VxSleep( 5000 );
            continue;
        }
    }
}

//============================================================================
bool OtherHostSrvMgr::executeHostActions( void )
{
    bool actionTaken = false;
    int actionIdx = 0;

    m_HostListMutex.lock();
    int listSize = (int)m_HostDirtyList.size();
    m_HostListMutex.unlock();

    if( listSize <= 0 )
    {
        // nothing to do
        return actionTaken;
    }

    // work backwards so erased entries do not affect index
    for( int idx = listSize - 1; idx >= 0; idx-- )
    {
        // get the info.. do not lock list for a long time so other threads can modify
        m_HostListMutex.lock();
        if( idx >= m_HostDirtyList.size() )
        {
            // list has been modified and is no longer contains the index desired
            m_HostListMutex.unlock();
            continue;
        }

        OtherHostInfo* otherHostSave = m_HostDirtyList[idx];
        if( !otherHostSave->isActionTakenTimeExpired() )
        {
            // have action but it has not timed out since last attempt
            m_HostListMutex.unlock();
            continue;
        }

        // we make a copy of the host info we need to avoid locking the list for long periods while performing action
        OtherHostInfo otherHostInfo = *otherHostSave;

        // remove from list
        m_HostDirtyList.erase( m_HostDirtyList.begin() + idx );  
        m_HostListMutex.unlock();

        // attempt to take action
        bool actionSuccess = false;
        if( otherHostInfo.getNeedQueryHostId() )
        {
            VxGUID hostId;
            if( otherHostInfo.doActionQueryHostId( hostId ) && hostId.isVxGUIDValid() )
            {
                // action success
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
            // error occured.. add back into the list after setting timer so is not attempted continuously
            m_HostListMutex.lock();
            OtherHostInfo* listInfo = findHostMatch( otherHostInfo );
            if( listInfo )
            {
                int failedActionCnt = listInfo->getFailedActionCnt();
                // TODO.. should probably fail after X attemps but in some cases like connect to group we want to try until success
                listInfo->setFailedActionCnt( failedActionCnt + 1 );
                listInfo->updateConnectAttemptTime();

                /// TODO  should probably quit trying or expand time between attempts
                // for now just put it at the end of the action required list
                m_HostDirtyList.push_back( listInfo );
            }

            m_HostListMutex.unlock();
        }

        actionTaken |= actionSuccess;
    }

    return actionTaken;
}

//============================================================================
bool OtherHostSrvMgr::executeHostConnections( void )
{
    bool actionTaken = false;
    int actionIdx = 0;

    m_HostListMutex.lock();
    int listSize = ( int )m_NeedConnectList.size();
    m_HostListMutex.unlock();

    if( listSize <= 0 )
    {
        // nothing to do
        return actionTaken;
    }

    // work backwards so erased entries do not affect index
    for( int idx = listSize - 1; idx >= 0; idx-- )
    {
        // get the info.. do not lock list for a long time so other threads can modify
        m_HostListMutex.lock();
        if( idx >= m_NeedConnectList.size() )
        {
            // list has been modified and is no longer contains the index desired
            m_HostListMutex.unlock();
            continue;
        }

        OtherHostInfo* otherHostSave = m_NeedConnectList[ idx ];
        if( otherHostSave->getSktListCount() )
        {
            // already have a connection
            m_NeedConnectList.erase( m_NeedConnectList.begin() + idx );
            continue;
        }

        if( !otherHostSave->isConnectAttemptTimeExpired() )
        {
            // have action but it has not timed out since last attempt
            m_HostListMutex.unlock();
            continue;
        }

        // we make a copy of the host info we need to avoid locking the list for long periods while performing action
        OtherHostInfo otherHostInfo = *otherHostSave;

        // remove from list
        m_NeedConnectList.erase( m_NeedConnectList.begin() + idx );
        m_HostListMutex.unlock();

        // attempt to take action
        bool actionSuccess = false;
        VxGUID hostOnlineId = otherHostInfo.getHostOnlineId();
        if( hostOnlineId.isVxGUIDValid() && otherHostInfo.getHostPort() && !otherHostInfo.getHostIpAddr().empty() )
        {
            VxSktConnect* sktBase = m_Engine.getPeerMgr().connectTo( otherHostInfo.getHostIpAddr().c_str(), otherHostInfo.getHostPort(), CONNECT_TO_HOST_TIMEOUT_MS );
            if( sktBase )
            {
                // now send announce to remote user

                // request reverse connection and STUN have to do with firewall and relays. Hosts must always have a open port
                bool requestReverseConnection = false;
                bool requestSTUN = false;

                //LogMsg( LOG_INFO, "sendMyPktAnnounce 1\n" ); 
                bool sendAnnResult = sendMyPktAnnounce( hostOnlineId,
                                                        sktBase,
                                                        true,
                                                        false,
                                                        requestReverseConnection,
                                                        requestSTUN );


                if( sendAnnResult )
                {
                    // action success
                    m_HostListMutex.lock();

                    OtherHostInfo* listInfo = findHostMatch( otherHostInfo );
                    if( listInfo )
                    {
                        manageHostList( m_NeedConnectList, listInfo, false, true );
                    }

                    actionSuccess = true;
                    m_HostListMutex.unlock();
                }
            }
        }

        if( !actionSuccess )
        {
            // error occured.. add back into the list after setting timer so is not attempted continuously
            m_HostListMutex.lock();
            OtherHostInfo* listInfo = findHostMatch( otherHostInfo );
            if( listInfo )
            {
                int failedActionCnt = listInfo->getFailedActionCnt();
                // TODO.. should probably fail after X attemps but in some cases like connect to group we want to try until success
                listInfo->setFailedActionCnt( failedActionCnt + 1 );
                listInfo->updateConnectAttemptTime();

                /// TODO  should probably quit trying or expand time between attempts
                // for now just put it at the end of the action required list
                m_NeedConnectList.push_back( listInfo );
            }

            m_HostListMutex.unlock();
        }

        actionTaken |= actionSuccess;
    }

    return actionTaken;
}

//============================================================================
//! encrypt and send my PktAnnounce to someone of whom we have no biglist record
bool OtherHostSrvMgr::sendMyPktAnnounce(  VxGUID&				destinationId,
                                          VxSktBase *			sktBase,
                                          bool					requestAnnReply,
                                          bool					requestTop10,
                                          bool					requestReverseConnection,
                                          bool					requestSTUN )
{
    m_Engine.lockAnnouncePktAccess();
    m_Engine.getMyPktAnnounce().setAppAliveTimeSec( GetApplicationAliveSec() );
    PktAnnounce pktAnn;
    memcpy( &pktAnn, &m_Engine.getMyPktAnnounce(), sizeof( PktAnnounce ) );
    m_Engine.unlockAnnouncePktAccess();

    pktAnn.setIsPktAnnReplyRequested( requestAnnReply );
    pktAnn.setIsTopTenRequested( requestTop10 );
    pktAnn.setIsPktAnnRevConnectRequested( requestReverseConnection );
    pktAnn.setIsPktAnnStunRequested( requestSTUN );

    // TODO something better than assuming guest
    EFriendState eMyFriendshipToHim = eFriendStateGuest;
    EFriendState eHisFriendshipToMe = eFriendStateGuest;

    pktAnn.setMyFriendshipToHim( eMyFriendshipToHim );
    pktAnn.setHisFriendshipToMe( eHisFriendshipToMe );

    //LogMsg( LOG_INFO, "SendMyPktAnnounce; to %s Hi 0x%llX, Lo 0x%llX skt %d request reply %d\n", 
    //	m_Engine.knownContactNameFromId( destinationId ),
    //	destinationId.getVxGUIDHiPart(),
    //	destinationId.getVxGUIDLoPart(),
    //	sktBase->m_iSktId,
    //	requestAnnReply );

    return txPacket( destinationId, sktBase, &pktAnn );
}

//============================================================================
bool OtherHostSrvMgr::txPacket( VxGUID&				destinationId,
                                VxSktBase *			sktBase,
                                VxPktHdr *			poPkt )
{
    bool bSendSuccess = false;
    poPkt->setSrcOnlineId( m_Engine.getMyOnlineId() );

    if( 0 == ( poPkt->getPktLength() & 0xf ) )
    {
        if( sktBase->isConnected() && sktBase->isTxEncryptionKeySet() )
        {
            sktBase->m_u8TxSeqNum++;
            poPkt->setPktSeqNum( sktBase->m_u8TxSeqNum );
            RCODE rc = sktBase->txPacket( destinationId, poPkt, false );
            if( 0 == rc )
            {
                bSendSuccess = true;
            }
            else
            {
                LogMsg( LOG_ERROR, "OtherHostSrvMgr::txPacket: %s error %d\n", sktBase->describeSktType().c_str(), rc );
            }
        }
        else
        {
            if( false == sktBase->isConnected() )
            {
                LogMsg( LOG_ERROR, "OtherHostSrvMgr::txSystemPkt: error skt %d not connected\n", sktBase->m_iSktId );
            }
            else
            {
                LogMsg( LOG_ERROR, "OtherHostSrvMgr::txSystemPkt: error skt %d has no encryption key\n", sktBase->m_iSktId );
            }
        }
    }
    else
    {
        LogMsg( LOG_ERROR, "OtherHostSrvMgr::txPluginPkt: Invalid system Packet length %d type %d\n",
                poPkt->getPktLength(),
                poPkt->getPktType() );
    }

    return bSendSuccess;
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
    else if( hostInfo )
    {
        manageHostList( m_NeedConnectList, hostInfo, true, true );
    }

    m_HostListMutex.unlock();
    if( actionNeeded )
    {
        startActionThread();
    }
}


//============================================================================
bool OtherHostSrvMgr::manageHostList( std::vector<OtherHostInfo*>& hostList, OtherHostInfo* hostInfo, bool addTrueRemoveFalse, bool isListLocked )
{
    bool listModified = false;
    if( hostInfo )
    {
        if( !isListLocked )
        {
            m_HostListMutex.lock();
        }

        if( addTrueRemoveFalse )
        {
            // add to list
            bool isInList = false;
            for( auto hostEntry : hostList )
            {
                if( hostEntry == hostInfo )
                {
                    isInList = true;
                    break;
                }
            }

            if( !isInList )
            {
                hostList.push_back( hostInfo );
                listModified = true;
            }
        }
        else
        {
            // remove from list
            for( auto iter = hostList.begin(); iter != hostList.end(); ++iter )
            {
                if( *iter == hostInfo )
                {
                    hostList.erase( iter );
                    listModified = true;
                    break;
                }
            }
        }

        if( !isListLocked )
        {
            m_HostListMutex.unlock();
        }
    }

    return listModified;
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
