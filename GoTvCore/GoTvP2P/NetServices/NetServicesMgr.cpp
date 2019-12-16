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

#include "NetServicesMgr.h"
#include "NetServiceHdr.h"
#include "NetActionQueryMyIp.h"
#include "NetActionIsMyPortOpen.h"
#include "NetActionAnnounce.h"
#include "NetActionRandomConnect.h"
#include <GoTvCore/GoTvP2P/Network/NetworkStateMachine.h>
#include <GoTvCore/GoTvP2P/Network/NetworkMgr.h>

#include  <GoTvCore/GoTvP2P/P2PEngine/EngineSettingsDefaultValues.h>

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>
#include <GoTvCore/GoTvP2P/P2PEngine/EngineSettings.h>

#include <GoTvCore/GoTvP2P/Network/NetConnector.h>

#include <NetLib/VxSktBase.h>
#include <NetLib/VxSktUtil.h>
#include <CoreLib/VxGlobals.h>
#include <CoreLib/VxParse.h>
#include <CoreLib/OsDetect.h>
#include "GoTvDebugConfig.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _MSC_VER
# pragma warning(disable: 4355) //'this' : used in base member initializer list
#endif //_MSC_VER

namespace
{
	//============================================================================
    void * NetServicesMgrThreadFunc( void * pvContext )
	{
		VxThread * poThread = (VxThread *)pvContext;
		poThread->setIsThreadRunning( true );

		NetServicesMgr * poMgr = (NetServicesMgr *)poThread->getThreadUserParam();
        if( poMgr && false == poThread->isAborted() )
        {
            poMgr->runNetActions();
        }

		poThread->threadAboutToExit();
        return nullptr;
	}
}

//============================================================================
NetServicesMgr::NetServicesMgr( P2PEngine& engine )
: m_Engine( engine )
, m_PktAnn( engine.getMyPktAnnounce() )
, m_EngineSettings( engine.getEngineSettings() )
, m_NetworkMgr( engine.getNetworkMgr() )
, m_NetServiceUtils( engine )
, m_NetServiceHost( engine, *this, m_NetServiceUtils )
, m_NetActionIdle( *this )
, m_CurNetAction( &m_NetActionIdle )
{
}

//============================================================================
NetServicesMgr::~NetServicesMgr()
{
	netServicesShutdown();
}

//============================================================================
VxGUID& NetServicesMgr::getMyOnlineId( void )
{
	return m_PktAnn.getMyOnlineId();
}

//============================================================================
void NetServicesMgr::netServicesStartup( void )
{
	m_NetServiceHost.netServiceHostStartup();
	m_NetActionThread.startThread( (VX_THREAD_FUNCTION_T)NetServicesMgrThreadFunc, this, "NetServMgrThrd" );
}

//============================================================================
void NetServicesMgr::netServicesShutdown( void )
{
	m_NetActionThread.abortThreadRun( true );
	m_NetActionMutex.lock();
	if( m_CurNetAction )
	{
		LogMsg( LOG_INFO, "NetServicesMgr::netServicesShutdown: action type %d\n", m_CurNetAction->getNetActionType() );
	}

	m_NetActionMutex.unlock();
	m_NetActionSemaphore.signal();
	m_NetServiceHost.netServiceHostShutdown();
	m_NetActionThread.killThread();
}

//============================================================================
void NetServicesMgr::addNetActionCommand( NetActionBase * netActionBase )
{
	m_NetActionMutex.lock();
	m_NetActionList.push_back( netActionBase );
	m_NetActionMutex.unlock();
	m_NetActionSemaphore.signal();
}

//============================================================================
bool NetServicesMgr::isActionQued( ENetActionType eNetActionType )
{
	if( m_NetActionList.size() )
	{
		m_NetActionMutex.lock();
		std::vector<NetActionBase*>::iterator iter;
		for( iter = m_NetActionList.begin(); iter != m_NetActionList.end(); ++iter )
		{
			if( eNetActionType == (*iter)->getNetActionType() )
			{
				m_NetActionMutex.unlock();
				return true;
			}
		}

		m_NetActionMutex.unlock();
	}

	return false;
}

//============================================================================
void NetServicesMgr::runNetActions( void )
{
	while( ( false == m_NetActionThread.isAborted() )
			&& ( false == VxIsAppShuttingDown() ) )
	{
		m_NetActionSemaphore.wait();
		if( m_NetActionThread.isAborted()
			|| VxIsAppShuttingDown() )
		{
			return;
		}

		while( m_NetActionList.size() )
		{

			m_NetActionMutex.lock();
			m_CurNetAction = m_NetActionList[0];
			m_NetActionList.erase( m_NetActionList.begin() );
			m_NetActionMutex.unlock();

			if( m_NetActionThread.isAborted()
				|| VxIsAppShuttingDown() )
			{
				return;
			}

			m_CurNetAction->enterAction();
			m_CurNetAction->doAction();
			m_CurNetAction->exitAction();

			m_NetActionMutex.lock();
			delete m_CurNetAction;
			if( m_NetActionThread.isAborted()
				|| VxIsAppShuttingDown() )
			{
				m_CurNetAction = NULL;
				m_NetActionMutex.unlock();
				return;
			}

			m_CurNetAction = &m_NetActionIdle;
			m_NetActionMutex.unlock();

			if( m_NetActionThread.isAborted()
				|| VxIsAppShuttingDown() )
			{
				return;
			}

			// we keep the connection open until command que is empty
			if( 0 == m_NetActionList.size() )
			{
				if( m_SktToNetServices.isConnected() )
				{
					m_SktToNetServices.closeSkt(43);
				}
			}
		}
	}
}

//============================================================================
RCODE NetServicesMgr::handleNetCmdPing( VxSktBase * sktBase, NetServiceHdr& netServiceHdr )
{
	//LogMsg( LOG_INFO, "Got ping from %s\n", sktBase->getRemoteIp() );
	return  sendPong( sktBase, netServiceHdr );
}

//============================================================================
RCODE NetServicesMgr::sendPong( VxSktBase * sktBase, NetServiceHdr& netServiceHdr )
{
	std::string content;
	StdStringFormat( content, "PONG-%s", sktBase->getRemoteIp() );
	return m_NetServiceUtils.buildAndSendCmd( sktBase, eNetCmdPong, content );
}

//============================================================================
RCODE NetServicesMgr::handleNetCmdPong( VxSktBase * sktBase, NetServiceHdr& netServiceHdr )
{
	LogMsg( LOG_INFO, "Got PONG from %s\n", sktBase->getRemoteIp() );
	return 0;
}

//============================================================================
RCODE NetServicesMgr::handleNetCmdIsMyPortOpenReq( VxSktBase * sktBase, NetServiceHdr& netServiceHdr )
{
	InetAddrAndPort rmtAddr;
    VxGetRmtAddress( sktBase->m_Socket, rmtAddr );
	std::string strRmtAddr = rmtAddr.toStdString().c_str();

	std::string toClientContent = "0-"; // assume fail
	toClientContent += strRmtAddr;

	if( strRmtAddr.empty() )
	{
		LogMsg( LOG_ERROR, "NetServicesMgr::handleNetCmdIsMyPortOpenReq: could not determine remote address\n");
		return m_NetServiceUtils.buildAndSendCmd( sktBase, eNetCmdIsMyPortOpenReply, toClientContent, (int)eAppErrFailedToResolveAddr );
	}

	char *	pSktBuf = (char *)sktBase->getSktReadBuf();
	if( false == ( '/' == pSktBuf[ netServiceHdr.m_TotalDataLen - 1 ] ) )
	{
		sktBase->sktBufAmountRead( 0 );
		LogMsg( LOG_ERROR, "NetServicesMgr::handleNetCmdIsMyPortOpenReq: invalid content\n");
		return m_NetServiceUtils.buildAndSendCmd( sktBase, eNetCmdIsMyPortOpenReply, toClientContent, (int)eAppErrFailedToResolveAddr );
	}

	sktBase->sktBufAmountRead( 0 );

	pSktBuf[ netServiceHdr.m_TotalDataLen - 1 ] = 0;

	std::string fromClientContent = &pSktBuf[ netServiceHdr.m_SktDataUsed ];
	
	if( fromClientContent.empty() )
	{
		LogMsg( LOG_ERROR, "NetServicesMgr::handleNetCmdIsMyPortOpenReq: could not parse from client content\n");
		return m_NetServiceUtils.buildAndSendCmd( sktBase, eNetCmdIsMyPortOpenReply, toClientContent, (int)eAppErrParseError );
	}

	uint16_t u16Port = (uint16_t)atoi( fromClientContent.c_str() );
	if( 0 == u16Port )
	{
		LogMsg( LOG_ERROR, "NetServicesMgr::handleNetCmdIsMyPortOpenReq: could not parse client port\n");
		return m_NetServiceUtils.buildAndSendCmd( sktBase, eNetCmdIsMyPortOpenReply, toClientContent, (int)eAppErrParseError );
	}

	LogMsg( LOG_ERROR, "handleNetCmdIsMyPortOpenReq: Attempting ping ip %s port %d\n", strRmtAddr.c_str(), u16Port );
	std::string retPong;
	bool pingSuccess = doNetCmdPing( strRmtAddr.c_str(), u16Port, retPong );
	if( false == pingSuccess )
	{
		LogMsg( LOG_ERROR, "handleNetCmdIsMyPortOpenReq: FAILED PING ip %s port %d\n", strRmtAddr.c_str(), u16Port );
		return m_NetServiceUtils.buildAndSendCmd( sktBase, eNetCmdIsMyPortOpenReply, toClientContent, (int)eAppErrPortIsClosed );
	}

	LogMsg( LOG_ERROR, "handleNetCmdIsMyPortOpenReq: SUCCESS PING ip %s port %d\n", strRmtAddr.c_str(), u16Port );
	toClientContent = "1-";
	toClientContent += strRmtAddr;
	return m_NetServiceUtils.buildAndSendCmd( sktBase, eNetCmdIsMyPortOpenReply, toClientContent, (int)eAppErrNone );
}

//============================================================================
bool NetServicesMgr::doNetCmdPing( const char * ipAddress, uint16_t u16Port,	std::string& retPong )
{
	VxSktConnectSimple toClientConn;
	VxTimer	pingTimer;

	if( INVALID_SOCKET == toClientConn.connectTo( ipAddress, u16Port, PORT_TEST_CONNECT_TO_CLIENT_TIMEOUT ) )
	{
		LogMsg( LOG_ERROR, "##P NetServicesMgr::doNetCmdPing: timeout %d could not connect to %s:%d %3.3f sec\n", PORT_TEST_CONNECT_TO_CLIENT_TIMEOUT, ipAddress, u16Port, pingTimer.elapsedSec() );
		return false;
	}
	
	double connectTime = pingTimer.elapsedSec();
	LogMsg( LOG_INFO, "##P NetServicesMgr::doNetCmdPing connect to %s:%d in %3.3f sec\n", ipAddress, u16Port, connectTime );
	return sendAndRecievePing( pingTimer, toClientConn, retPong, PONG_RX_TIMEOUT );
}

//============================================================================
bool NetServicesMgr::sendAndRecievePing( VxTimer& pingTimer, VxSktConnectSimple& toClientConn, std::string& retPong, int receiveTimeout )
{	
	std::string strNetCmd;
	std::string strPing = "PING";
	
	std::string netServChallengeHash;
	uint16_t cryptoKeyPort = toClientConn.getCryptoKeyPort();
	m_NetServiceUtils.generateNetServiceChallengeHash(netServChallengeHash, cryptoKeyPort );

	m_NetServiceUtils.buildNetCmd( strNetCmd, eNetCmdPing, netServChallengeHash, strPing );

	LogMsg( LOG_ERROR, "##P NetServicesMgr::sendAndRecievePing: cypto port %d strNetCmd(%s)\n", cryptoKeyPort, strNetCmd.c_str() );
	double connectTime = pingTimer.elapsedSec();
	RCODE rc = toClientConn.sendData( strNetCmd.c_str(), strNetCmd.length(), 8000 );
	if( rc )
	{
		double failSendTime = pingTimer.elapsedSec();
		LogMsg( LOG_ERROR, "##P NetServicesMgr::sendAndRecievePing: sendData error %d in %3.3f sec\n", rc, failSendTime - connectTime  );
		toClientConn.closeSkt();
		return false;
	}

	double sendTime = pingTimer.elapsedSec();
	char rxBuf[ 512 ];
	rxBuf[0] = 0;
	NetServiceHdr netServiceHdr;
	if( false == m_NetServiceUtils.rxNetServiceCmd( &toClientConn, rxBuf, sizeof( rxBuf ), netServiceHdr, receiveTimeout, receiveTimeout )  )
	{
		double failResponseTime = pingTimer.elapsedSec();
		LogMsg( LOG_ERROR, "##P NetServicesMgr::sendAndRecievePing: timeout %d no response connect %3.3f sec send %3.3f sec fail respond %3.3f sec\n",
			receiveTimeout, connectTime, sendTime - connectTime,  failResponseTime - sendTime );
		toClientConn.closeSkt();
		return false;
	}

	toClientConn.closeSkt();

	double successResponseTime = pingTimer.elapsedSec();
	if( ( 0 == netServiceHdr.m_TotalDataLen )
		|| ( 511 <= netServiceHdr.m_TotalDataLen )
		|| ( '/' != rxBuf[ netServiceHdr.m_ContentDataLen - 1 ] ) )
	{
		LogMsg( LOG_ERROR, "##P NetServicesMgr::sendAndRecievePing: invalid response  connect %3.3f sec send %3.3f sec fail respond %3.3f sec\n",
		connectTime, sendTime - connectTime,  successResponseTime - sendTime );
		return false;
	}

	LogMsg( LOG_ERROR, "##P NetServicesMgr::sendAndRecievePing: SUCCESS  connect %3.3f sec send %3.3f sec response %3.3f sec\n",
		connectTime, sendTime - connectTime,  successResponseTime - sendTime );
	rxBuf[ netServiceHdr.m_ContentDataLen - 1 ] = 0; 
	retPong = rxBuf;
	return true;
}

//============================================================================
RCODE NetServicesMgr::handleNetCmdIsMyPortOpenReply( VxSktBase * sktBase, NetServiceHdr& netServiceHdr )
{
	RCODE rc = -1;
	// not called here.. handled in NetAction
	return rc;
}

//============================================================================
RCODE NetServicesMgr::handleNetCmdHostReq( VxSktBase * sktBase, NetServiceHdr& netServiceHdr )
{
	return m_NetServiceHost.handleNetCmdHostReq( sktBase, netServiceHdr );
}

//============================================================================
RCODE NetServicesMgr::handleNetCmdHostReply( VxSktBase * sktBase, NetServiceHdr& netServiceHdr )
{
	return m_NetServiceHost.handleNetCmdHostReply( sktBase, netServiceHdr );
}

//============================================================================
void NetServicesMgr::queryWhatsMyIp( void )
{
	addNetActionCommand( new NetActionQueryMyIp( *this ) );
}

//============================================================================
void NetServicesMgr::netActionResultQueryWhatsMyIp( const char * ipAddress )
{
	LogMsg( LOG_INFO, "NetServicesMgr::netActionResultQueryWhatsMyIp IP %s\n", ipAddress );
}

//============================================================================
void NetServicesMgr::setMyPortOpenResultCallback( MY_PORT_OPEN_CALLBACK_FUNCTION pfuncPortOpenCallbackHandler, void * userData )
{
	m_pfuncPortOpenCallbackHandler = pfuncPortOpenCallbackHandler;
	m_PortOpenCallbackUserData = userData;
}

//============================================================================
void NetServicesMgr::testIsMyPortOpen( void )
{
	addNetActionCommand( new NetActionIsMyPortOpen( *this ) );
}

//============================================================================
void NetServicesMgr::announceToHost( std::string& anchorIp, uint16_t u16HostPort, EHostAction eHostAction )
{
	addNetActionCommand( new NetActionAnnounce( *this, anchorIp, u16HostPort, eHostAction ) );
}

//============================================================================
void NetServicesMgr::performRandomConnect( void )
{
	if( false == isActionQued( eNetActionRandomConnect ) )
	{
		addNetActionCommand( new NetActionRandomConnect( *this, 
			m_Engine.getNetworkStateMachine().getHostIp(),
			m_Engine.getNetworkStateMachine().getHostPort(),
			eHostActionRandomConnect ) );
	}
	else
	{
		LogMsg( LOG_INFO, "Net Action Random Connect already qued\n" );
	}
}

//============================================================================
void NetServicesMgr::netActionResultRandomConnect( EAppErr eAppErr, HostList * anchorList )
{
	if( eAppErrNone == eAppErr )
	{
		m_Engine.getNetConnector().handleRandomConnectResults( anchorList );
	}
	else
	{
		LogMsg( LOG_INFO, "NetServicesMgr::netActionResultRandomConnect ERROR %d\n", eAppErr );
	}
}

//============================================================================
void NetServicesMgr::netActionResultIsMyPortOpen( EAppErr eAppErr, std::string& myExternalIp )
{
    #ifdef LOG_PORT_TEST
	LogMsg( LOG_INFO, "NetServicesMgr::netActionResultIsMyPortOpen %d ip %s\n", eAppErr, myExternalIp.c_str() );
    #endif // LOG_PORT_TEST
	if( m_pfuncPortOpenCallbackHandler )
	{
		m_pfuncPortOpenCallbackHandler( m_PortOpenCallbackUserData, eAppErr, myExternalIp );
	}
}

//============================================================================
void NetServicesMgr::netActionResultAnnounce( EAppErr eAppErr, HostList * anchorList, EHostAction eHostAction )
{
	if( eAppErrNone == eAppErr )
	{
		m_Engine.getNetConnector().handleAnnounceResults( anchorList, ( eHostActionRelaysOnly == eHostAction ) ?  eConnectReasonRelaySearch : eConnectReasonAnnouncePing );
	}
}

//============================================================================
VxSktConnectSimple * NetServicesMgr::actionReqConnectToNetService( void )
{
	if( m_SktToNetServices.isConnected() )
	{
		// already connected
		return &m_SktToNetServices;
	}

	bool sktConnected = actionReqConnectToNetService( m_SktToNetServices );
	return sktConnected ? &m_SktToNetServices : 0;
}

//============================================================================
bool NetServicesMgr::actionReqConnectToNetService( VxSktConnectSimple& sktSimple )
{
	sktSimple.closeSkt();
	std::string netSrvUrl;
	if( m_Engine.getNetworkStateMachine().isNetworkWebsitesResolved() )
	{
		StdStringFormat( netSrvUrl, "http://%s:%d",  m_Engine.getNetworkStateMachine().getNetServiceIp().c_str(),  m_Engine.getNetworkStateMachine().getNetServicePort() );
	}
	else
	{
		m_EngineSettings.getNetServiceWebsiteUrl( netSrvUrl );
	}

	std::string strHost;
	std::string strFile;
	uint16_t u16Port;

	if( false == sktSimple.connectToWebsite( netSrvUrl.c_str(), strHost, strFile, u16Port, NETSERVICE_CONNECT_TIMEOUT ) )
	{
#ifdef LOG_PORT_TEST
		LogMsg( LOG_ERROR, "NetServicesMgr::actionReqConnectToNetService: FAILED to Connect to %s\n", netSrvUrl.c_str() );
#endif // LOG_PORT_TEST

		return false;
	}

	//LogMsg( LOG_VERBOSE, "actionReqConnectToNetService: SUCCESS\n" );
	return true;
}

//============================================================================
VxSktConnectSimple * NetServicesMgr::actionReqConnectToHost( void )
{
	if( m_SktToHost.isConnected() )
	{
		// already connected
		return &m_SktToHost;
	}

	if( false == actionReqConnectToHost( m_SktToHost ) )
	{
		return 0;
	}

	return &m_SktToHost;
}

//============================================================================
bool NetServicesMgr::actionReqConnectToHost( VxSktConnectSimple& sktSimple )
{
	std::string anchorUrl;
	if( m_Engine.getNetworkStateMachine().isNetworkWebsitesResolved() )
	{
		StdStringFormat( anchorUrl, "http://%s:%d",  m_Engine.getNetworkStateMachine().getHostIp().c_str(),  m_Engine.getNetworkStateMachine().getHostPort() );
	}
	else
	{
		m_EngineSettings.getNetHostWebsiteUrl( anchorUrl );
	}

	std::string strHost;
	std::string strFile;
	uint16_t u16Port;

	if( false == sktSimple.connectToWebsite( anchorUrl.c_str(), strHost, strFile, u16Port, ANCHOR_CONNECT_TIMEOUT ) )
	{
        if( IsLogEnabled( eLogModuleNetworkState ) )
        {
            LogMsg( LOG_ERROR, "### ERROR NetServicesMgr::actionReqConnectToHost: FAILED to Connect to %s timeout %d\n", anchorUrl.c_str(), ANCHOR_CONNECT_TIMEOUT );
        }

		return false;
	}

	//LogMsg( LOG_INFO, "actionReqConnectToHost: SUCCESS\n" );
	return true;
}

//============================================================================
EAppErr NetServicesMgr::doIsMyPortOpen( std::string& retMyExternalIp, bool testLoopbackFirst )
{
    retMyExternalIp = "";
	std::string rmtIP = m_NetworkMgr.getLocalIpAddress();
    if( rmtIP.empty() )
    {
        if( IsLogEnabled( eLogModuleNetworkState ) )
        {
            LogMsg( LOG_ERROR, "NetServicesMgr::doIsMyPortOpen no local ip\n" );
        }

        return eAppErrBadParameter;
    }

	int tcpListenPort = m_Engine.getMyPktAnnounce().getOnlinePort();

#if 0 //#ifdef TARGET_OS_WINDOWS
static int lastPort = 0;
    if( tcpListenPort != m_Engine.getEngineSettings().getLastFirewallPort() )
	{
		// this only affects windows firewall and not external firewalls like macafee :(
		m_Engine.getEngineSettings().setLastFirewallPort( tcpListenPort );
		const wchar_t* name = L"MyP2PWeb";
		wchar_t exePathAndName[ VX_MAX_PATH ];
		int iRetStrLen = GetModuleFileNameW( NULL, exePathAndName, VX_MAX_PATH );
		if( 0 != iRetStrLen )
		{
			m_WindowsFirewall.addFilewallException( exePathAndName, name, tcpListenPort, DEFAULT_UDP_PORT );
			lastPort = tcpListenPort;
		}

		//didnt work for macafee firewall
		//Windows XP:
		//add: netsh firewall add allowedprogram mode=ENABLE profile=ALL name=[exception name] program=[program path]
		//remove: netsh firewall delete allowedprogram profile=ALL program=[program path]
		//Windows 7:
		//add: netsh advfirewall firewall add rule action=allow profile=any protocol=any enable=yes direction=[in|out] name=[exception name] program=[program path]
		//remove: advfirewall firewall delete rule profile=any name=[exception name]
		// example netsh advfirewall firewall add rule name="Allow Messenger" dir=in action=allow program="C:\programfiles\messenger\msnmsgr.exe"
		char exePathAndNameA[ VX_MAX_PATH ];
		int pathStrLen = GetModuleFileNameA( NULL, exePathAndNameA, VX_MAX_PATH );
		char cmdBuf[ 2048 ];
		if( 0 != pathStrLen )
		{
			//if( 6.0 <= OsDetect::getWindowsVersionNumber() )
			//{
			//	// requires admin but xp version doesnt and seems to work
			//	// vista or higher
			//	strcpy( cmdBuf, "netsh advfirewall firewall add rule action=allow profile=any protocol=any enable=yes direction=in name=MyP2PWeb program=" );
			//}
			//else
			//{
				strcpy( cmdBuf, "netsh firewall add allowedprogram mode=ENABLE profile=ALL name=MyP2PWeb program=" );
			//}

			strcat( cmdBuf, exePathAndNameA );
			system( cmdBuf );
			sprintf( cmdBuf, "netsh firewall add portopening TCP %d MyP2PWeb%d", tcpListenPort, tcpListenPort );			system( cmdBuf );
		}
	}
#endif // TARGET_OS_WINDOWS
	
	VxTimer portTestTimer;

    #ifdef LOG_PORT_TEST
	    LogMsg( LOG_INFO, "555######### Starting IsPort Open Test ip %s port %d app sec %d\n", rmtIP.c_str(), tcpListenPort, VxGetApplicationAliveSeconds() );
    #endif // LOG_PORT_TEST
	if( testLoopbackFirst )
	{
		// we need to wait until listen port is up and running.. keep testing till we can connect
		bool loopbackSuccess = false;
		int retryLoopbackCnt = 5;
		while( retryLoopbackCnt )
		{
			if( false == testLoobackPing( rmtIP, tcpListenPort ) )
			{
				//LogMsg( LOG_INFO, "666 FAILED LOOPBACK Test ip %s port %d app sec %d\n", rmtIP.c_str(), tcpListenPort, VxGetApplicationAliveSeconds() );
				VxSleep( 1000 );
				retryLoopbackCnt--;
				continue;
			}
			else
			{
				loopbackSuccess = true;
				break;
			}
		}

		if( false == loopbackSuccess )
		{
#ifdef LOG_PORT_TEST
			LogMsg( LOG_ERROR, "777######### FAILED ALL LOOPBACK Tests ip %s port %d app sec %d\n", rmtIP.c_str(), tcpListenPort, VxGetApplicationAliveSeconds() );
#endif // LOG_PORT_TEST
		}
	}

	bool isCellDataNetwork = m_NetworkMgr.isCellularNetwork();
	EAppErr	portOpenTestError = eAppErrPortIsClosed;
	VxSktConnectSimple portOpenConn1;
	if( actionReqConnectToNetService( portOpenConn1 ) )
	{
		portOpenTestError = sendAndRecieveIsMyPortOpen( portTestTimer, 
														&portOpenConn1, 
														tcpListenPort,
														retMyExternalIp,
														isCellDataNetwork );
		portOpenConn1.closeSkt();
	}
	else if( false == portOpenConn1.isConnected() )
	{
		
        if( IsLogEnabled( eLogModuleNetworkState ) )
        {
            LogMsg( LOG_INFO, "NetServicesMgr::doIsMyPortOpen FAILED Connect to net services\n" );
            m_Engine.sendToGuiStatusMessage( "FAILED Connect to Connect Test Server\n" );
        }
    }

	if( isCellDataNetwork 
		|| ( eAppErrNone == portOpenTestError )
		|| ( portTestTimer.elapsedMs() > 15000 ) )
	{

		if( eAppErrNone == portOpenTestError )
		{
            if( IsLogEnabled( eLogModuleNetworkState ) )
            {
                LogMsg( LOG_INFO, "NetActionIsMyPortOpen::doAction: Your TCP Port %d IS OPEN :) IP is %s->%s in %3.3f sec\n", tcpListenPort, retMyExternalIp.c_str(), rmtIP.c_str(), retMyExternalIp.c_str(), portTestTimer.elapsedSec() );
                m_Engine.sendToGuiStatusMessage( "Your TCP Port %d IS OPEN :)", tcpListenPort  );
            }
		}
		else
		{
            if( IsLogEnabled( eLogModuleNetworkState ) )
            {
                LogMsg( LOG_INFO, "NetActionIsMyPortOpen::doAction: Your TCP Port %d IS CLOSED :) IP %s->%s in %3.3f sec\n", tcpListenPort, retMyExternalIp.c_str(), rmtIP.c_str(), portTestTimer.elapsedSec() );
                m_Engine.sendToGuiStatusMessage( "Your TCP Port %d IS CLOSED :( IP is %s->%s  (%3.3f sec)", tcpListenPort, retMyExternalIp.c_str(), rmtIP.c_str(), portTestTimer.elapsedSec() );
            }
		}

		return portOpenTestError; // messages sent and result set and no sense in retying because all ports blocked on cell network
	}

	// try again with new connection
    if( IsLogEnabled( eLogModuleNetworkState ) )
    {
	    LogMsg( LOG_INFO, "NetActionIsMyPortOpen::doAction: retry port open test\n" );
    }

	VxSktConnectSimple portOpenConn2;
	if( actionReqConnectToNetService( portOpenConn2 ) )
	{
		portOpenTestError = sendAndRecieveIsMyPortOpen( portTestTimer, 
														&portOpenConn2, 
														tcpListenPort,
														retMyExternalIp,
														true );
		portOpenConn2.closeSkt();
	}

	if( eAppErrNone == portOpenTestError )
	{
        if( IsLogEnabled( eLogModuleConnect ) )
		    LogMsg( LOG_INFO, "NetActionIsMyPortOpen::doAction: (2)Your TCP Port %d IS OPEN :) IP is %s->%s in %3.3f sec\n", tcpListenPort, retMyExternalIp.c_str(), rmtIP.c_str(), retMyExternalIp.c_str(), portTestTimer.elapsedSec() );
		m_Engine.sendToGuiStatusMessage( "(2)Your TCP Port %d IS OPEN :)", tcpListenPort  );
	}
	else
	{
        if( IsLogEnabled( eLogModuleConnect ) )
		    LogMsg( LOG_INFO, "NetActionIsMyPortOpen::doAction: (2)Your TCP Port %d IS CLOSED :) IP %s->%s in %3.3f sec\n", tcpListenPort, retMyExternalIp.c_str(), rmtIP.c_str(), portTestTimer.elapsedSec() );
		m_Engine.sendToGuiStatusMessage( "(2)Your TCP Port %d IS CLOSED :( IP is %s->%s  (%3.3f sec)", tcpListenPort, retMyExternalIp.c_str(), rmtIP.c_str(), portTestTimer.elapsedSec() );
	}

	return portOpenTestError; 
}

//============================================================================
bool NetServicesMgr::testLoobackPing( std::string localIP, uint16_t tcpListenPort )
{
	VxSktConnectSimple toClientConn;
	VxTimer	pingTimer;
	std::string ipAddress = localIP;

	if( INVALID_SOCKET == toClientConn.connectTo( ipAddress.c_str(), tcpListenPort, 2000 ) )
	{
        if( IsLogEnabled( eLogModuleNetworkState ) )
        {
		    LogMsg( LOG_ERROR, "##P NetServicesMgr::testLoobackPing: could not connect to %s:%d %3.3f sec\n", ipAddress.c_str(), tcpListenPort, pingTimer.elapsedSec() );
        }

		return false;
	}

	toClientConn.closeSkt();
	return true;
}

//============================================================================
EAppErr NetServicesMgr::sendAndRecieveIsMyPortOpen( VxTimer&				portTestTimer, 
													VxSktConnectSimple *	netServConn, 
													int						tcpListenPort,
													std::string&			retMyExternalIp,
													bool					sendMsgToUser )
{
	if( NULL == netServConn )
	{
		LogMsg( LOG_INFO, "Is Your TCP Port %d Open Test Connect FAILED (%3.3f sec)\n", tcpListenPort, portTestTimer.elapsedSec()  );
		if( sendMsgToUser )
		{
			m_Engine.sendToGuiStatusMessage( "Is TCP Port %d Open Test Connect FAILED (%3.3f sec)\n", tcpListenPort, portTestTimer.elapsedSec()  );
		}

		return eAppErrFailedToConnect;
	}

	if( false == netServConn->isConnected() )
	{
		LogMsg( LOG_INFO, "Is Your TCP Port %d Open Test Connect FAILED (NO SERVER CONNECTION) (%3.3f sec)\n", tcpListenPort, portTestTimer.elapsedSec()  );
		if( sendMsgToUser )
		{
			m_Engine.sendToGuiStatusMessage( "Is TCP Port %d Open Test Connect FAILED (NO SERVER CONNECTION) (%3.3f sec)\n", tcpListenPort, portTestTimer.elapsedSec()  );
		}

		return eAppErrFailedToConnect;
	}

	std::string strNetActionUrl;
	m_NetServiceUtils.buildIsMyPortOpenUrl( netServConn, strNetActionUrl, tcpListenPort );

	LogMsg( LOG_INFO, "Is Port %d Open Connected in  %3.3f sec now Sending data\n", tcpListenPort, portTestTimer.elapsedSec());
	portTestTimer.startTimer();
	RCODE rc = netServConn->sendData( strNetActionUrl.c_str(), strNetActionUrl.length() );
	if( rc )
	{
		LogMsg( LOG_ERROR, "Is TCP Port %d Open Send Command Error (%3.3f sec)\n", tcpListenPort, portTestTimer.elapsedSec()  );
		if( sendMsgToUser )
		{
			m_Engine.sendToGuiStatusMessage( "Is TCP Port %d Open Send Command Error (%3.3f sec)\n", tcpListenPort, portTestTimer.elapsedSec()  );
		}

		return eAppErrTxError;
	}

	VxSleep( 1000 );
	char rxBuf[ 512 ];
	rxBuf[ 0 ] = 0;
	NetServiceHdr netServiceHdr;
	if( false == m_NetServiceUtils.rxNetServiceCmd( netServConn, 
													rxBuf, 
													sizeof( rxBuf ), 
													netServiceHdr, 
													IS_PORT_OPEN_RX_HDR_TIMEOUT, 
													IS_PORT_OPEN_RX_DATA_TIMEOUT ) )
	{
		if( sendMsgToUser )
		{
			LogMsg( LOG_ERROR,  "Is TCP Port %d Open Connect Test Server Response Time Out (%3.3f sec)\n", tcpListenPort, portTestTimer.elapsedSec()  );
		}

		m_Engine.sendToGuiStatusMessage( "Is TCP Port %d Open Connect Test Server Response Time Out (%3.3f sec)\n", tcpListenPort, portTestTimer.elapsedSec()  );
		return eAppErrNetServicesFailedToRespond;
	}

	std::string content = rxBuf;
	if( 0 == content.length() )
	{
		LogMsg( LOG_ERROR, "Is TCP Port %d Open No Server Response Content (%3.3f sec)\n", tcpListenPort, portTestTimer.elapsedSec()  );
		if( sendMsgToUser )
		{
			m_Engine.sendToGuiStatusMessage( "Is TCP Port %d Open No Server Response Content (%3.3f sec)\n", tcpListenPort, portTestTimer.elapsedSec()  );
		}

		return eAppErrRxError;
	}

	const char * contentBuf = content.c_str();
	if( '/' != contentBuf[content.length() -1] )
	{
		LogMsg( LOG_ERROR, "Is TCP Port %d Open Test Invalid Response Content (%3.3f sec)\n", tcpListenPort, portTestTimer.elapsedSec()  );
		if( sendMsgToUser )
		{
			m_Engine.sendToGuiStatusMessage( "Is TCP Port %d Open Test Invalid Response Content (%3.3f sec)\n", tcpListenPort, portTestTimer.elapsedSec()  );
		}

		return eAppErrRxError;
	}

	((char *)contentBuf)[content.length() -1] = 0;

	std::vector<std::string> contentParts;
	StdStringSplit( content, '-', contentParts );
	if( 2 != contentParts.size() )
	{
		LogMsg( LOG_ERROR, "Is TCP Port %d Open Test Invalid Content Parts (%3.3f sec)\n", tcpListenPort, portTestTimer.elapsedSec()  );
		if( sendMsgToUser )
		{
			m_Engine.sendToGuiStatusMessage( "Is TCP Port %d Open Test Invalid Content Parts (%3.3f sec)\n", tcpListenPort, portTestTimer.elapsedSec()  );
		}

		return eAppErrParseError;
	}

	retMyExternalIp = contentParts[1];

	std::string strPayload = contentParts[0];
#ifdef DEBUG_NETSERVICE
    if( IsLogEnabled( eLogModuleConnect ) )
	    LogMsg( LOG_INFO, "NetActionIsMyPortOpen::doAction: can direct connect %s my ip %s:%d\n", strPayload.c_str(), retMyExternalIp.c_str(), tcpListenPort );
#endif // DEBUG_NETSERVICE
	int iIsOpen = atoi( contentParts[0].c_str() );

	return iIsOpen ? eAppErrNone : eAppErrPortIsClosed;
}
