//============================================================================
// Copyright (C) 2014 Brett R. Jones 
// Issued to MIT style license by Brett R. Jones in 2017
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

#include "NetworkMgr.h"
#include "NetworkDefs.h"

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>
#include <GoTvCore/GoTvP2P/P2PEngine/P2PConnectList.h>
#include <GoTvCore/GoTvP2P/BigListLib/BigListMgr.h>
#include <GoTvCore/GoTvP2P/BigListLib/BigListInfo.h>

#include <NetLib/VxSktBase.h>
#include <NetLib/VxPeerMgr.h>
#include <NetLib/VxSktConnect.h>
#include <NetLib/VxSktCrypto.h>

#include <PktLib/VxCommon.h>
#include <PktLib/PktAnnounce.h>
#include <PktLib/PktsRelay.h>

#include <CoreLib/VxDebug.h>
#include <CoreLib/VxGlobals.h>

#ifdef _MSC_VER
# pragma warning(disable: 4355) //'this' : used in base member initializer list
#endif

namespace
{
	void NetworkPeerSktCallbackHandler( VxSktBase *  sktBase, void * pvUserCallbackData )
	{
        if( pvUserCallbackData )
		{
            NetworkMgr * netMgr = (NetworkMgr *)pvUserCallbackData;
            netMgr->handleTcpSktCallback( sktBase );
		}
	}

	//void NetworkMulticastCallbackHandler( VxSktBase *  sktBase, void * pvUserCallbackData )
	//{
	//	if( pvUserCallbackData )
	//	{
	//		((NetworkMgr *)pvUserCallbackData)->handleMulticastSktCallback( sktBase );
	//	}
	//}
}

//============================================================================
NetworkMgr::NetworkMgr( P2PEngine&		engine, 
						VxPeerMgr&		peerMgr,
						BigListMgr&		bigListMgr,
						P2PConnectList&	connectionList
						)
: m_Engine( engine )
, m_PktAnn( engine.getMyPktAnnounce() )
, m_PeerMgr( peerMgr )
, m_BigListMgr( bigListMgr )
, m_ConnectList( connectionList )
#ifdef ENABLE_MULTICAST
, m_MulticastBroadcast( *this )
, m_MulticastListen( *this, *this )
#endif // ENABLE_MULTICAST
{
	VxSetNetworkLoopbackAllowed( false );

	m_PeerMgr.setReceiveCallback( NetworkPeerSktCallbackHandler, this );
#ifdef ENABLE_MULTICAST
	m_MulticastListen.getUdpSkt().setReceiveCallback( NetworkMulticastCallbackHandler, this );
#endif // ENABLE_MULTICAST
}

//============================================================================
void NetworkMgr::networkMgrStartup( void )
{
}

//============================================================================
void NetworkMgr::networkMgrShutdown( void )
{
#ifdef ENABLE_MULTICAST
	m_MulticastBroadcast.getUdpSkt().closeSkt();
	m_MulticastListen.stopListen();	
#endif // ENABLE_MULTICAST
	m_PeerMgr.sktMgrShutdown();
}

//============================================================================
void NetworkMgr::fromGuiNetworkAvailable( const char * lclIp, bool isCellularNetwork )
{
    if( !lclIp )
    {
        LogMsg( LOG_SEVERE, "fromGuiNetworkAvailable invalid param lclIp is null" );
        return;
    }

    std::string strIp = lclIp;
    if( strIp.empty() )
    {
        LogMsg( LOG_ERROR, "fromGuiNetworkAvailable param lclIp is empty" );
        return;
    }

    if( m_bNetworkAvailable 
        && ( m_strLocalIpAddr == strIp )
        && ( m_bIsCellularNetwork == isCellularNetwork ) )
    {
        LogModule( eLogModuleNetworkMgr, LOG_DEBUG, "fromGuiNetworkAvailable but network already set to %s\n", m_strLocalIpAddr.c_str() );
        return;
    }

	m_bIsCellularNetwork = isCellularNetwork;
	m_strLocalIpAddr = lclIp;
	m_LocalIp.setIp( lclIp );
    m_bNetworkAvailable = true;

	m_PeerMgr.setLocalIp( m_LocalIp );
//#ifdef ENABLE_MULTICAST
//	m_MulticastListen.setLocalIp( m_LocalIp );
//	m_MulticastBroadcast.setLocalIp( m_LocalIp );
//#endif // ENABLE_MULTICAST

	if( m_LocalIp.isIPv4() && m_LocalIp.isValid() )
	{
		m_Engine.getMyPktAnnounce().getLanIPv4().setIp( lclIp );
	}
	else
	{
		m_Engine.getMyPktAnnounce().getLanIPv4().setToInvalid();
	}

    // no need for this .. NetworkEventAvail will start listening to network
	// m_PeerMgr.startListening( lclIp, m_Engine.getMyPktAnnounce().getOnlinePort() );
#ifdef ENABLE_MULTICAST
	m_MulticastListen.beginListen();	
#endif // ENABLE_MULTICAST
}

//============================================================================
void NetworkMgr::fromGuiNetworkLost( void )
{
	m_bNetworkAvailable =  false ;

    // no need for this .. NetworkEventLost will stop listening
	// m_PeerMgr.stopListening();
#ifdef ENABLE_MULTICAST
	m_MulticastListen.stopListen();
#endif // ENABLE_MULTICAST
}

//============================================================================
void NetworkMgr::setBroadcastPort( uint16_t u16Port )
{
#ifdef ENABLE_MULTICAST
	m_MulticastBroadcast.setMulticastPort( u16Port );
	m_MulticastListen.setMulticastPort( u16Port );
#endif // ENABLE_MULTICAST
}

//============================================================================
void NetworkMgr::setBroadcastEnable( bool enable )
{
#ifdef ENABLE_MULTICAST
	m_MulticastBroadcast.setBroadcastEnable( enable );
#endif // ENABLE_MULTICAST
}

//============================================================================
void NetworkMgr::multicastPktAnnounceAvail( VxSktBase * skt, PktAnnounce * pktAnnounce )
{
	//BRJ TODO handle multicast
}

//============================================================================
void NetworkMgr::onPktAnnUpdated( void )
{
#ifdef ENABLE_MULTICAST
	m_MulticastBroadcast.onPktAnnUpdated();
#endif // ENABLE_MULTICAST
}

//============================================================================
void NetworkMgr::onOncePerSecond( void )
{
#ifdef ENABLE_MULTICAST
	if ( VxIsAppShuttingDown() )
	{
		return;
	}
	
	m_MulticastBroadcast.onOncePerSecond();
#endif // ENABLE_MULTICAST
}

//============================================================================
void NetworkMgr::handleTcpSktCallback( VxSktBase * sktBase )
{
	if( VxIsAppShuttingDown() )
	{
		return;
	}

	sktBase->setLastActiveTimeMs( GetGmtTimeMs() );

	switch( sktBase->getCallbackReason() )
	{
	case eSktCallbackReasonConnectError:
        if( IsLogEnabled( eLogModuleNetworkMgr ) )
		    LogMsg( LOG_ERROR, "NetworkMgr:TCP Skt %d connect error %s\n", sktBase->m_iSktId, sktBase->describeSktError( sktBase->getLastSktError() ) );
		break;

	case eSktCallbackReasonConnected:
        if( IsLogEnabled( eLogModuleNetworkMgr ) )
            LogMsg( LOG_INFO, "NetworkMgr:TCP %s port %d to local port %d\n", sktBase->describeSktType().c_str(), sktBase->m_RmtIp.getPort(), sktBase->m_LclIp.getPort() );
		break;

	case eSktCallbackReasonData:
		m_Engine.handleTcpData( sktBase );
		break;

	case eSktCallbackReasonClosed:
		m_Engine.onConnectionLost( sktBase );
        if( IsLogEnabled( eLogModuleNetworkMgr ) )
		    LogMsg( LOG_INFO, "NetworkMgr:TCP Skt %d closed %s\n", sktBase->m_iSktId, sktBase->describeSktError( sktBase->getLastSktError() ) );
		break;

	case eSktCallbackReasonError:
        if( IsLogEnabled( eLogModuleNetworkMgr ) )
		    LogMsg( LOG_ERROR, "NetworkMgr:TCP Skt %d error %s\n", sktBase->m_iSktId, sktBase->describeSktError( sktBase->getLastSktError() ) );
		break;

	case eSktCallbackReasonClosing:
        if( IsLogEnabled( eLogModuleNetworkMgr ) )
		    LogMsg( LOG_INFO, "NetworkMgr:TCP eSktCallbackReasonClosing Skt %d \n", sktBase->m_iSktId );
		break;

	case eSktCallbackReasonConnecting:
        if( IsLogEnabled( eLogModuleNetworkMgr ) )
		    LogMsg( LOG_INFO, "NetworkMgr:TCP eSktCallbackReasonConnecting Skt %d \n", sktBase->m_iSktId );
		break;

	default:
		LogMsg( LOG_ERROR, "NetworkMgrTCP: UNKNOWN CallbackReason %d Skt %d error %s\n", sktBase->getCallbackReason(), sktBase->m_iSktId, sktBase->describeSktError( sktBase->getLastSktError() ) );
		break;
	}
}

//============================================================================
void NetworkMgr::handleMulticastSktCallback( VxSktBase * sktBase )
{
	if( VxIsAppShuttingDown() )
	{
		return;
	}

	switch( sktBase->getCallbackReason() )
	{
	case eSktCallbackReasonConnectError:
        if( IsLogEnabled( eLogModuleMulticast ) )
		    LogMsg( LOG_ERROR, "NetworkMgr:Multicast Skt %d connect error %s\n", sktBase->m_iSktId, sktBase->describeSktError( sktBase->getLastSktError() ) );
		break;

	case eSktCallbackReasonConnected:
        if( IsLogEnabled( eLogModuleMulticast ) )
		    LogMsg( LOG_INFO, "NetworkMgr:Multicast Skt %d connected from %s port %d\n", sktBase->m_iSktId, sktBase->getRemoteIp(), sktBase->m_LclIp.getPort() );
		break;

	case eSktCallbackReasonData:
		if( 16 > sktBase->getSktBufDataLen() )
		{
			// don't even bother.. not enough to decrypt
			break;
		}

        if( IsLogEnabled( eLogModuleMulticast ) )
		    LogMsg( LOG_INFO, "NetworkMgr:Multicast Data Skt %d\n", sktBase->m_iSktId );
		m_Engine.handleMulticastData( sktBase );
		break;

	case eSktCallbackReasonClosed:
        if( IsLogEnabled( eLogModuleMulticast ) )
		    LogMsg( LOG_INFO, "NetworkMgr:Multicast Skt %d closed %s\n", sktBase->m_iSktId, sktBase->describeSktError( sktBase->getLastSktError() ) );
		break;

	case eSktCallbackReasonError:
        if( IsLogEnabled( eLogModuleMulticast ) )
		    LogMsg( LOG_ERROR, "NetworkMgr:Multicast Skt %d error %s\n", sktBase->m_iSktId, sktBase->describeSktError( sktBase->getLastSktError() ) );
		break;

	case eSktCallbackReasonClosing:
        if( IsLogEnabled( eLogModuleMulticast ) )
		    LogMsg( LOG_INFO, "NetworkMgr:Multicast eSktCallbackReasonClosing Skt %d \n", sktBase->m_iSktId );
		break;

	case eSktCallbackReasonConnecting:
        if( IsLogEnabled( eLogModuleMulticast ) )
		    LogMsg( LOG_INFO, "NetworkMgr:Multicast eSktCallbackReasonConnecting Skt %d \n", sktBase->m_iSktId );
		break;

	default:
		LogMsg( LOG_ERROR, "NetworkMgr:Multicast: Skt %d error %s\n", sktBase->m_iSktId, sktBase->describeSktError( sktBase->getLastSktError() ) );
		break;
	}
}
