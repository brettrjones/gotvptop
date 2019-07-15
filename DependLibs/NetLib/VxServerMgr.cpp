//============================================================================
// Copyright (C) 2009 Brett R. Jones 
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
// http://www.gotvptop.com
//============================================================================

#include "VxSktUtil.h"
#include "VxSktAccept.h"
#include "VxServerMgr.h"
#include "GoTvDebugConfig.h"

#include <CoreLib/VxParse.h>
#include <CoreLib/VxGlobals.h>
#include <CoreLib/AppErr.h>

#include <stdio.h>
#include <memory.h>
#include <time.h>

//#define DEBUG_VXSERVER_MGR
#define DISABLE_WATCHDOG 1

int VxServerMgr::m_iAcceptMgrCnt = 0;				// number of accept managers that have been created

//============================================================================
namespace
{
	int32_t VxServerMgrVxThreadFunc(  void * pvContext )
	{
		VxThread * poVxThread = (VxThread *)pvContext;
		poVxThread->setIsThreadRunning( true );
		VxServerMgr * poMgr = (VxServerMgr *)poVxThread->getThreadUserParam();

#if defined(DEBUG_SKT_CONNECTIONS)
		LogMsg( LOG_INFO, "#### VxServerMgr: Mgr id %d Listen port %d thread started\n", poMgr->m_iMgrId, poMgr->m_u16ListenPort );
#endif // DEBUG_VXSERVER_MGR
		poMgr->listenForConnectionsToAccept( poVxThread );

		// quitting
#ifdef DEBUG_SKT_CONNECTIONS
		LogMsg( LOG_INFO, "#### VxServerMgr: Mgr id %d Listen port %d thread tid %d quiting\n", poMgr->m_iMgrId, poMgr->getListenPort(), poVxThread->getThreadTid() );
#endif // DEBUG_VXSERVER_MGR
		//! VxThread calls this just before exit
		poVxThread->threadAboutToExit();
		return 0;
	}
}

//============================================================================
VxServerMgr::VxServerMgr()
: VxSktBaseMgr()
, m_u16ListenPort( 0 )		// what port to listen on
, m_iActiveListenSktCnt( 0 )		// listening socket
, m_LastWatchdogKick( 0 )
, m_IsReadyToAcceptConnections( false )
{
	m_iAcceptMgrCnt++;
	m_iMgrId = m_iAcceptMgrCnt;
	m_eSktMgrType = eSktMgrTypeTcpAccept;
	memset( m_aoListenSkts, 0, sizeof( m_aoListenSkts ) );
}

//============================================================================
VxServerMgr::~VxServerMgr()
{
	stopListening();
}

//============================================================================
// overrides VxSktBaseMgr
void VxServerMgr::sktMgrShutdown( void )
{
	stopListening();
	VxSktBaseMgr::sktMgrShutdown();
}

//============================================================================
void VxServerMgr::fromGuiKickWatchdog( void )
{
	//LogMsg( LOG_SKT, "VxServerMgr: fromGuiKickWatchdog\n" );
	m_LastWatchdogKick = time(0);
}

//============================================================================
bool VxServerMgr::checkWatchdog( void )
{
	// there is an issue with android.. in some cases it can leave the listen socket open even though the
	// app is stopped or crashed. this watchdog is used to force the listen socket to close
	// and terminate the app if it is unresponsive.
#ifdef _DEBUG
	return true; // if we are debugging don't timeout because we are on a breakpoint
#endif 
#ifdef DISABLE_WATCHDOG
	return true; // if we are debugging don't timeout because we are on a breakpoint
#endif 

	if( ( time(0) - m_LastWatchdogKick ) < 4 )
	{
		return true;
	}

	LogMsg( LOG_INFO, "Listen Watchdog Timeout\n" );
	return false;
}

//============================================================================
VxSktBase * VxServerMgr::makeNewAcceptSkt( void )				
{ 
	return new VxSktAccept(); 
}

//============================================================================
RCODE VxServerMgr::startListening( const char * ip,  uint16_t u16ListenPort )
{
	stopListening();
	if( m_ListenVxThread.isThreadRunning() )
	{
		m_ListenVxThread.killThread();
	}

	if( VxIsAppShuttingDown() )
	{
		return -1;
	}

	if( 0 == u16ListenPort )
	{
		AppErr( eAppErrBadParameter, "VxServerMgr::startListening Bad param port %d\n", u16ListenPort );
		return -1;
	}

	m_LastWatchdogKick = time( 0 );
	std::string ipv4String = ip;
	m_u16ListenPort = u16ListenPort;
#if defined(DEBUG_SKT_CONNECTIONS)
	LogMsg( LOG_INFO, "333######### NOT IN THREAD VxServerMgr::startListening ip %s port %d app sec %d\n", ip, u16ListenPort, GetApplicationAliveSec() );
#endif // DEBUG_SKT_CONNECTIONS

#ifdef TARGET_OS_ANDROID
	// can't get ip's in native android... for now just do ipv4 TODO listen for ipv6 in android
	// ipv4 only
    SOCKET sock = socket( AF_INET, SOCK_STREAM, 0 );
	if( sock < 0 )
	{
		RCODE rc = VxGetLastError();
#if defined(DEBUG_SKT_CONNECTIONS)
        LogMsg( LOG_ERROR, "VxServerMgr::startListening create skt error %d\n", rc );
#endif // DEBUG_SKT_CONNECTIONS
        if( 0 == rc )
        {
            rc = -1;
        }

        return rc;
	}

	// don't know why reuse port doesn't work
	VxSetSktAllowReusePort( sock );

#ifdef DEBUG_VXSERVER_MGR
	LogMsg( LOG_INFO, "StartListen binding ip %s port %d \n", ip, u16ListenPort );
#endif // DEBUG_VXSERVER_MGR
	struct sockaddr_in listenAddr;
    memset(&listenAddr, 0, sizeof( struct sockaddr_in ) );
	listenAddr.sin_family = AF_INET;
	listenAddr.sin_port = htons(u16ListenPort);
    listenAddr.sin_addr.s_addr = INADDR_ANY; //inet_addr(ip);;
	bool bindSuccess = false;
	for( int tryCnt = 0; tryCnt < 5; tryCnt++ )
	{
		if( 0 > bind (sock, (struct sockaddr *) &listenAddr, sizeof (sockaddr_in) ) )
		{
			RCODE rc = VxGetLastError();
			LogMsg( LOG_ERROR, "VxServerMgr::startListening bind skt %d error %d %s try cnt %d\n", sock, rc, VxDescribeSktError( rc ), tryCnt + 1 );
			VxSleep( 1000 );
			continue;
		}
		
		bindSuccess = true;
		break;
	}

	if( false == bindSuccess )
	{
		LogMsg( LOG_ERROR, "VxServerMgr::startListening bind skt %d FAILED\n", sock );
		::VxCloseSktNow( sock );
		return false;
	}

   #ifdef DEBUG_VXSERVER_MGR
        LogMsg( LOG_INFO, "StartListen socket %d index %d ip %s port %d \n", sock, m_iActiveListenSktCnt, ip, u16ListenPort );
   #endif // DEBUG_VXSERVER_MGR
	m_aoListenSkts[ m_iActiveListenSktCnt ] = sock;
	m_iActiveListenSktCnt++;
	m_LclIp.setIp( ip );
	m_LclIp.setPort( u16ListenPort );

    return internalStartListen();
#endif // TARGET_OS_ANDROID

	//LogMsg( LOG_INFO, " VxServerMgr::startListening %s:%d\n", ip, u16ListenPort ); 
	std::vector<InetAddress> allAddresses;
	InetAddress addrGetter;
	addrGetter.getAllAddresses( allAddresses );

	std::vector<InetAddress>::iterator iter;
	for( iter = allAddresses.begin(); iter != allAddresses.end(); ++iter )
	{
		// Highly unlikely, but check anyway.
		if( FD_SETSIZE == m_iActiveListenSktCnt ) 
		{
			LogMsg( LOG_ERROR, "getaddrinfo returned more addresses than we could use.\n");
			break;
		}

		InetAddress thisAddr = *iter;
		std::string thisIp = thisAddr.toStdString();
		if( thisAddr.isIPv4() )
		{
			// user specified which ipv4 address to use. If this is not it then skip it
			if( thisIp != ipv4String )
			{
				//LogMsg( LOG_INFO, "VxServerMgr::startListening Skip ip %s\n", thisIp.c_str() );
				continue;
			}
#ifdef DEBUG_VXSERVER_MGR
			else
			{
				LogMsg( LOG_INFO, "VxServerMgr::startListening found local ip4 %s\n", thisIp.c_str() );
			}
#endif // DEBUG_VXSERVER_MGR
		}
		else
		{
#ifdef SUPPORT_IPV6
			if( false == thisAddr.isIPv6GlobalAddress() )
			{
				continue;
			}

			LogMsg( LOG_INFO, "VxServerMgr::startListening found global ipv6 %s\n", thisIp.c_str() );
#else
			continue;
#endif //  SUPPORT_IPV6
		}

		// Open a socket with the correct address family for this address.
		SOCKET sock = socket( thisAddr.isIPv4() ? AF_INET : AF_INET6, SOCK_STREAM, 0);
		if( INVALID_SOCKET == sock )
		{
			LogMsg( LOG_ERROR,  "VxServerMgr::startListening socket() failed with error %d: %s\n",
				VxGetLastError(), VxDescribeSktError( VxGetLastError() ) );
			continue;
		}

		if( thisAddr.isIPv4() )
		{
			struct sockaddr_in oAddr;
			memset(&oAddr, '\0', sizeof( struct sockaddr_in ) );
			oAddr.sin_family = AF_INET;
			oAddr.sin_port = htons(u16ListenPort);
			oAddr.sin_addr.s_addr = inet_addr(thisIp.c_str());
			bool bindFailed = true;
			for( int i = 0; i < 3; i++ )
			{
				if (bind (sock, (struct sockaddr *) &oAddr, sizeof (oAddr)) < 0)
				{
					RCODE rc = VxGetLastError();
					LogMsg( LOG_INFO, "VxServerMgr::startListening bind skt error %d %s try %d\n", rc, VxDescribeSktError( rc ), i+1 );
					VxSleep( 1000 );
					continue;
				}
				else
				{
					bindFailed = false;
					break;
				}
			}

			if( bindFailed )
			{
				::VxCloseSktNow( sock );
				continue;
			}

	
			if( SOCKET_ERROR == listen( sock, 10 ) ) // SOMAXCONN) ) ( SOMAXCONN == maximum number of qued allowed
			{
				LogMsg( LOG_ERROR, "ipv4 listen() failed with error %d: %s\n", VxGetLastError(), VxDescribeSktError( VxGetLastError() ) );
				// fail completely
				::VxCloseSktNow( sock );
				continue;
			}

			m_LclIp.setIp( thisIp.c_str() );
			m_LclIp.setPort( u16ListenPort );

			m_aoListenSkts[ m_iActiveListenSktCnt ] = sock;
			m_iActiveListenSktCnt++;
			break;

		}
		else
		{
			struct sockaddr_in6 oAddr;
			memset(&oAddr, '\0', sizeof( struct sockaddr_in6 ) );
			oAddr.sin6_family = AF_INET6;
			oAddr.sin6_port = htons(u16ListenPort);
			inet_pton(AF_INET6, thisIp.c_str(), (void *)&oAddr.sin6_addr.s6_addr);
			bool bindFailed = true;
			for( int i = 0; i < 3; i++ )
			{
				if( bind (sock, (struct sockaddr *) &oAddr, sizeof (oAddr)) < 0)
				{
					RCODE rc = VxGetLastError();
					LogMsg( LOG_INFO, "VxServerMgr::startListening bind skt ipv6 error %d %s\n", rc, VxDescribeSktError( rc ) );
					::VxCloseSkt( sock );
					continue;
				}
				else
				{
					bindFailed = false;
					break;
				}
			}

			if( bindFailed )
			{
				::VxCloseSktNow( sock );
				continue;
			}


			if( SOCKET_ERROR == listen( sock, 10 ) ) // SOMAXCONN) ) ( SOMAXCONN == maximum number of qued allowed
			{
				::VxCloseSkt( sock );
				continue;
			}

			m_LclIp.setIp( thisIp.c_str() );
			m_LclIp.setPort( u16ListenPort );
			m_aoListenSkts[ m_iActiveListenSktCnt ] = sock;
			m_iActiveListenSktCnt++;

			LogMsg( LOG_INFO, "VxServerMgr::startListening success ipv6 %s\n", thisIp.c_str() ); 
			break;
		}
	}

	if( 0 == m_iActiveListenSktCnt ) 
	{
		LogMsg( LOG_ERROR, "### ERROR: VxServerMgr::startListening unable to serve on any address.\n");
		return -1;
	}

	return internalStartListen();
 }

//============================================================================
RCODE VxServerMgr::internalStartListen( void )
{
	// make a useful thread name
	std::string strVxThreadName;
	StdStringFormat( strVxThreadName, "VxServerMgr%d", m_iMgrId );
    return m_ListenVxThread.startThread( (VX_THREAD_FUNCTION_T)VxServerMgrVxThreadFunc, this, strVxThreadName.c_str() );
}

//============================================================================
RCODE VxServerMgr::startListening(  uint16_t u16ListenPort )
{
	stopListening();
	if( m_ListenVxThread.isThreadRunning() )
	{
		m_ListenVxThread.killThread();
	}

	if( VxIsAppShuttingDown() )
	{
		return -1;
	}

	if( 0 == u16ListenPort )
	{
		AppErr( eAppErrBadParameter, "VxServerMgr::startListening Bad param port %d\n", u16ListenPort );
			return -1;
	}

#if defined(DEBUG_SKT_CONNECTIONS)
	LogMsg( LOG_INFO, "VxServerMgr::startListening port %d\n", u16ListenPort );
#endif // DEBUG_VXSERVER_MGR
	RCODE rc = 0;

	//
	// By setting the AI_PASSIVE flag in the hints to getaddrinfo, we're
	// indicating that we intend to use the resulting address(es) to bind
	// to a socket(s) for accepting incoming connections.  This means that
	// when the Address parameter is NULL, getaddrinfo will return one
	// entry per allowed protocol family containing the unspecified address
	// for that family.
	//
	char *Address = NULL;

	struct addrinfo *AddrInfo, *AI;
	struct addrinfo oHints;
	VxFillHints( oHints );

    char as8Port[10];
	sprintf( as8Port, "%d", u16ListenPort );

	//LogMsg( LOG_INFO, " VxServerMgr::startListening port %d\n",  u16ListenPort ); 
	int RetVal = getaddrinfo(Address, as8Port, &oHints, &AddrInfo);
	if( 0 != RetVal ) 
	{
		LogMsg( LOG_INFO, "getaddrinfo failed with error %d: %s\n", RetVal, gai_strerror(RetVal));
		return RetVal;
	}
	//
	// For each address getaddrinfo returned, we create a new socket,
	// bind that address to it, and create a queue to listen on.
	//
	for(AI = AddrInfo; AI != NULL; AI = AI->ai_next) 
	{
		// Highly unlikely, but check anyway.
		if( FD_SETSIZE == m_iActiveListenSktCnt ) 
		{
			LogMsg( LOG_ERROR, "getaddrinfo returned more addresses than we could use.\n");
			break;
		}
		// This example only supports PF_INET and PF_INET6.
		if ((AI->ai_family != PF_INET) && (AI->ai_family != PF_INET6))
			continue;

		// Open a socket with the correct address family for this address.
        SOCKET sock = socket(AI->ai_family, AI->ai_socktype, AI->ai_protocol);
        if( INVALID_SOCKET == sock )
        {
			LogMsg( LOG_ERROR,  "socket() failed with error %d: %s\n",
				VxGetLastError(), VxDescribeSktError(VxGetLastError()));
			continue;
		}

#if 0 //#ifdef TARGET_OS_WINDOWS
		if ((PF_INET6 == AI->ai_family ) &&
			IN6_IS_ADDR_LINKLOCAL((IN6_ADDR *) INETADDR_ADDRESS(AI->ai_addr)) &&
			(((SOCKADDR_IN6 *) (AI->ai_addr))->sin6_scope_id == 0)
			) 
		{
			LogMsg( LOG_ERROR, "IPv6 link local addresses should specify a scope ID!\n");
		}
#endif // TARGET_OS_WINDOWS
		//
		// bind() associates a local address and port combination
		// with the socket just created. This is most useful when
		// the application is a server that has a well-known port
		// that clients know about in advance.
		//

		bool bindFailed = true;
		for( int i = 0; i < 3; i++ )
		{
			if( bind( sock, AI->ai_addr, (int) AI->ai_addrlen ) < 0 )
			{
				RCODE rc = VxGetLastError();
				LogMsg( LOG_INFO, "VxServerMgr::startListening bind() skt error %d %s try %d\n", rc, VxDescribeSktError( rc ), i+1 );
				VxSleep( 1000 );
				continue;
			}
			else
			{
				bindFailed = false;
				break;
			}
		}

		if( bindFailed )
		{
			::VxCloseSktNow( sock );
			continue;
		}

		m_LclIp.setIpAndPort( *AI->ai_addr );
		m_LclIp.setPort( u16ListenPort );
		m_aoListenSkts[ m_iActiveListenSktCnt ] = sock;
		m_iActiveListenSktCnt++;

        if( 0 != internalStartListen() )
        {
			m_iActiveListenSktCnt = 0;
            continue;
        }

		LogMsg( LOG_INFO, "'Listening' on port %s, protocol %s, protocol family %s\n",
			as8Port, 
			"TCP",
			(AI->ai_family == PF_INET) ? "PF_INET" : "PF_INET6");
		break;
	}

	freeaddrinfo(AddrInfo);

	if( 0 == m_iActiveListenSktCnt ) 
	{
		LogMsg( LOG_ERROR, "### Fatal error: unable to serve on any address.\n");
		return -1;
	}

	return rc;
}

//============================================================================
RCODE VxServerMgr::stopListening( void )
{
	m_IsReadyToAcceptConnections = false;
	m_u16ListenPort = 0;
#if defined(DEBUG_SKT_CONNECTIONS)
	LogMsg( LOG_SKT, "### VxServerMgr: Mgr %d stop listening skt cnt %d\n", m_iMgrId, m_iActiveListenSktCnt );
#endif // defined(DEBUG_SKT_CONNECTIONS)

	// kill previous thread if running
    m_ListenVxThread.abortThreadRun( true );
#if defined(DEBUG_SKT_CONNECTIONS)
	if( 0 == m_iActiveListenSktCnt )
	{
		LogMsg( LOG_ERROR, "VxServerMgr:stopListening called with no listen sockets\n" );
	}
#endif // defined(DEBUG_SKT_CONNECTIONS)

	for( int i = 0; i < m_iActiveListenSktCnt; i++ )
	{
		if( INVALID_SOCKET != m_aoListenSkts[ i ] )
		{
#if defined(DEBUG_SKT_CONNECTIONS)
			LogMsg( LOG_INFO, "VxServerMgr: Mgr %d closing listen skt %d\n", m_iMgrId, i );
#endif // defined(DEBUG_SKT_CONNECTIONS)
			// closing the thread should release it so it can exit
			SOCKET sktToClose = m_aoListenSkts[ i ];
			m_aoListenSkts[ i ] = INVALID_SOCKET;
			::VxCloseSktNow( sktToClose );
		}
		else
		{
			LogMsg( LOG_ERROR, "VxServerMgr:stopListening skt idx %d had invalid socket\n", i );
		}
    }

	m_iActiveListenSktCnt = 0;
#if defined(DEBUG_SKT_CONNECTIONS)
	LogMsg( LOG_SKT, "VxServerMgr: Mgr %d stop listening done\n", m_iMgrId );
#endif // defined(DEBUG_SKT_CONNECTIONS)
	return 0;
}

//============================================================================
RCODE VxServerMgr::acceptConnection( VxThread * poVxThread, SOCKET oListenSkt )
{
	RCODE rc = 0;
	if( INVALID_SOCKET == oListenSkt )
	{
		LogMsg( LOG_ERROR, "VxServerMgr::acceptConnection INVALID LISTEN SOCKET\n" );
		return -2;
	}

	if( VxIsAppShuttingDown() )
	{
		return -3;
	}

	// perform accept
	// setup address
	struct  sockaddr oAcceptAddr;
#if defined( TARGET_OS_WINDOWS ) || defined( TARGET_OS_ANDROID )
	socklen_t iAcceptAddrLen = sizeof( oAcceptAddr );
	memset( &oAcceptAddr, 0, sizeof( oAcceptAddr ) );
	// NOTE: in android the return to blocking on listen doesn't work so we just set it once before start listening so accept does not get hung
	SOCKET oAcceptSkt = accept( oListenSkt, ( struct sockaddr * )&oAcceptAddr, &iAcceptAddrLen );
#else //LINUX
	socklen_t iAcceptAddrLen = sizeof( struct  sockaddr );
	memset( &oAcceptAddr, 0, sizeof( oAcceptAddr ) );
	// NOTE: accept can hang waiting for connection in linux or android if
	// connection is dropped before the accept happens so set to non blocking.. the reason it hangs is it will wait until next connection occures	
	VxSetSktBlocking( oListenSkt, false );
	SOCKET oAcceptSkt = accept( oListenSkt, ( struct sockaddr * )&oAcceptAddr, &iAcceptAddrLen );
	VxSetSktBlocking( oListenSkt, true );
#endif // LINUX
    if( INVALID_SOCKET == oAcceptSkt )
    {
		rc = VxGetLastError();
		if( 0 == rc )
		{
			// not sure how it happens but seems to get in a loop where the clear doesn't clear and there is no error
			// so sleep just in case so doesn't eat up all the CPU
			VxSleep( 500 );
			return -1;
		}
		else
		{
			VxSleep( 200 );
			return rc;
		}
    }

#ifdef DEBUG_SKT_CONNECTIONS
    LogMsg( LOG_INFO, "VxServerMgr::acceptConnection: listen skt %d accepted skt %d\n", oListenSkt, oAcceptSkt );
#endif // DEBUG_SKT_CONNECTIONS
	if( poVxThread->isAborted() || VxIsAppShuttingDown() ) 
	{
		return -1;
	}

	// valid accept socket
	if( m_aoSkts.size() >= m_u32MaxConnections )
	{
		LogMsg( LOG_INFO, "VxServerMgr: reached max connections %d\n", m_u32MaxConnections );
		// we have reached max connections
		// just close it immediately
        VxCloseSktNow( oAcceptSkt );

		// sleep awhile
		VxSleep( 200 );
		return 0; // keep running until number of connections clear up
	}

	// add a skt to our list	
	VxSktAccept * sktBase = (VxSktAccept *)this->makeNewAcceptSkt();
	m_SktMgrMutex.lock(__FILE__, __LINE__); // dont let other threads mess with array while we add
	m_aoSkts.push_back( sktBase );
	// do tell skt to do accept stuff
	sktBase->m_Socket = oAcceptSkt;
	sktBase->setReceiveCallback( m_pfnOurReceive, this );
	sktBase->setTransmitCallback( m_pfnOurTransmit, this );
	m_SktMgrMutex.unlock(__FILE__, __LINE__);

#ifdef DEBUG_SKT_CONNECTIONS
	LogMsg( LOG_INFO, "VxServerMgr: doing accept\n" );
#endif // DEBUG_SKT_CONNECTIONS
	RCODE rcAccept = sktBase->doAccept( this, *(( struct sockaddr * )&oAcceptAddr) );
	if( rcAccept || poVxThread->isAborted() || INVALID_SOCKET == oListenSkt )
	{
		sktBase->closeSkt(67823);
		LogMsg( LOG_ERROR, "VxServerMgr: error %d doing accept\n", rc );
		// if error occurred then remove it from our list or it
		// will never get removed
		m_SktMgrMutex.lock(__FILE__, __LINE__); // dont let other threads mess with array while we remove
		m_aoSkts.pop_back();
		m_SktMgrMutex.unlock(__FILE__, __LINE__);
		delete sktBase;
		return -1;
	}

	return 0;
}

//============================================================================
void VxServerMgr::listenForConnectionsToAccept( VxThread * poVxThread )
{
#ifdef DEBUG_SKT_CONNECTIONS
	//LogMsg( LOG_INFO, "111 IN THREAD VxServerMgr::listenForConnectionsToAccept started\n" ); 
	//LogMsg( LOG_INFO, "111 IN THREAD VxServerMgr::listen port %d ip %s skt %d\n", m_LclIp.getPort(), m_LclIp.toStdString().c_str(), m_aoListenSkts[0] ); 
#endif // DEBUG_SKT_CONNECTIONS

	m_IsReadyToAcceptConnections = true;
#ifdef TARGET_OS_ANDROID
	// android set listen skt back to blocking doesn't work so just set to non blocking always ( part of accept hang fix ) 
	VxSetSktBlocking( m_aoListenSkts[0], false );

	// for some unknown reason code that works on mac/windows/linux to use select does not work on android
	// on android when use select the select seems to work but in the accept it gets error 22 (invalid param) .. so do this crap
	while ( ( false == poVxThread->isAborted() )
	   && ( false == VxIsAppShuttingDown() )
	   && ( 0 < m_iActiveListenSktCnt )
	   && ( checkWatchdog() ) )
	{
		if( 0 > listen( m_aoListenSkts[0], 8 ) )
		{
			break;
		}
		
		if( poVxThread->isAborted() 
			|| VxIsAppShuttingDown()
			|| ( 0 >= m_iActiveListenSktCnt ) ) 
		{
			break;
		}
		
		acceptConnection( poVxThread, m_aoListenSkts[0] );
	}	
	
	m_IsReadyToAcceptConnections = false;
	if( INVALID_SOCKET != m_aoListenSkts[ 0 ] )
	{
		SOCKET sktToClose = m_aoListenSkts[ 0 ];
		LogMsg( LOG_INFO, "VxServerMgr:listenForConnectionsToAccept closing listen skt %d\n", sktToClose );
		m_aoListenSkts[ 0 ] = INVALID_SOCKET;
		::VxCloseSktNow( sktToClose );
	}

	if( (false == VxIsAppShuttingDown() )
		&& ( false == checkWatchdog() ) )
	{
		LogMsg( LOG_ERROR, "Listen Failed Watchdog\n" );
		std::terminate();
	}

#else
	
	int iSelectResult;
	RCODE rc = 0;
	//LogMsg( LOG_INFO, "Listen VxThread start\n" );
    fd_set					oListenSocketFileDescriptors;
    fd_set					oReadSocketFileDescriptors;
	struct timeval			oListenTimeout;

    FD_ZERO( &oListenSocketFileDescriptors );
    FD_ZERO( &oReadSocketFileDescriptors );

    // keep track of the biggest file descriptor
    SOCKET largestFileDescriptor = 0;
    for( int iSktSetIdx = 0; iSktSetIdx < m_iActiveListenSktCnt; iSktSetIdx++ )
    {
        FD_SET( m_aoListenSkts[ iSktSetIdx ], &oListenSocketFileDescriptors);
        if( m_aoListenSkts[ iSktSetIdx ] > largestFileDescriptor )
        {
            largestFileDescriptor = m_aoListenSkts[ iSktSetIdx ];
        }
    }

    while( ( false == poVxThread->isAborted() )
           && ( false == VxIsAppShuttingDown() )
           && ( 0 < m_iActiveListenSktCnt ) )
	{
        oReadSocketFileDescriptors = oListenSocketFileDescriptors;
        // use a timeout so that thread can exit if aborted
        oListenTimeout.tv_sec	= 3;
        oListenTimeout.tv_usec	= 0;
        iSelectResult = select( largestFileDescriptor + 1, &oReadSocketFileDescriptors, 0, 0, &oListenTimeout );
        //LogMsg( LOG_INFO, "Listen VxThread select result %d\n", iSelectResult );

		if( poVxThread->isAborted() 
			|| VxIsAppShuttingDown()
			|| ( 0 >= m_iActiveListenSktCnt ) ) 
		{
			break;
		}

        if( 0 < iSelectResult )
		{
			// at least one valid selected
            for( int iSelectedIdx = 0; iSelectedIdx < m_iActiveListenSktCnt; iSelectedIdx++ )
			{
                if( FD_ISSET( m_aoListenSkts[iSelectedIdx], &oReadSocketFileDescriptors) )
				{
#ifdef DEBUG_SKT_CONNECTIONS
					LogMsg( LOG_INFO, "#### VxServerMgr::acceptConnection: accepting at index %d\n", iSelectedIdx );
#endif // DEBUG_SKT_CONNECTIONS
					rc = acceptConnection( poVxThread, m_aoListenSkts[iSelectedIdx] );
					if( rc )
					{
						LogMsg( LOG_ERROR, "#### VxServerMgr::acceptConnection: error %d %s doing accept\n", rc, VxDescribeSktError(rc) );
					}
					else
					{
#ifdef DEBUG_SKT_CONNECTIONS
						LogMsg( LOG_INFO, "#### VxServerMgr::acceptConnection: success doing accept\n" );
#endif // DEBUG_SKT_CONNECTIONS
					}

                    FD_CLR( m_aoListenSkts[iSelectedIdx], &oReadSocketFileDescriptors);
				}
			}
		}
#ifndef TARGET_OS_WINDOWS
        else if( ( 0 > iSelectResult ) 
			&& ( EINTR == errno ) )
		{
			// errno 4 can occur if in Linux and app gets CTRL-C signal
			break;
		}
#endif
        else if( 0 > iSelectResult )
        {
            LogMsg( LOG_INFO, "listenForConnectionsToAccept error %d\n", VxGetLastError() );
        }

		if( poVxThread->isAborted() 
			|| VxIsAppShuttingDown()
			|| ( 0 >= m_iActiveListenSktCnt ) ) 
		{
			break;
		}
    }
#endif // 	
	m_IsReadyToAcceptConnections = false;
}
