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
// http://www.nolimitconnect.com
//============================================================================

#include "VxSktUtil.h"
#include "VxSktAccept.h"
#include "VxServerMgr.h"
#include "GoTvDebugConfig.h"

#include <CoreLib/VxParse.h>
#include <CoreLib/VxGlobals.h>
#include <CoreLib/AppErr.h>
#include <CoreLib/VxTime.h>
#include <CoreLib/VxThread.h>

#include <stdio.h>
#include <memory.h>
#include <time.h>

//#define DEBUG_VXSERVER_MGR
#define DISABLE_WATCHDOG 1

int VxServerMgr::m_iAcceptMgrCnt = 0;				// number of accept managers that have been created

//============================================================================
namespace
{
    void * VxServerMgrVxThreadFunc(  void * pvContext )
	{
        if( pvContext )
        {
            VxThread * poVxThread = (VxThread *)pvContext;
            poVxThread->setIsThreadRunning( true );
            VxServerMgr * poMgr = (VxServerMgr *)poVxThread->getThreadUserParam();
            if( poMgr )
            {
                LogModule( eLogListen, LOG_INFO, "#### VxServerMgr: Mgr id %d Listen port %d thread started thread 0x%x", poMgr->m_iMgrId, poMgr->getListenPort(), VxGetCurrentThreadId() );

                poMgr->listenForConnectionsToAccept( poVxThread );

                // quitting
                LogModule( eLogListen, LOG_INFO, "#### VxServerMgr: Mgr id %d Listen port %d thread 0x%x tid %d quiting\n", poMgr->m_iMgrId, poMgr->getListenPort(), VxGetCurrentThreadId(), poVxThread->getThreadTid() );
            }

            //! VxThread calls this just before exit
            poVxThread->threadAboutToExit();
        }
        return nullptr;
	}
}

//============================================================================
VxServerMgr::VxServerMgr()
: VxSktBaseMgr()
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
	m_LastWatchdogKickMs = GetTimeStampMs();
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

	if( ( GetTimeStampMs() - m_LastWatchdogKickMs ) < 4000 )
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
bool VxServerMgr::isListening( void )							
{ 
    return m_u16ListenPort && m_ListenVxThread.isThreadRunning() && m_aoListenSkts[ 0 ] != INVALID_SOCKET;
}

//============================================================================
bool VxServerMgr::startListening( const char * ip,  uint16_t u16ListenPort )
{
    stopListening();
#if !USE_BIND_LOCAL_IP
    return startListeningNoBind( u16ListenPort );
#endif 

	if( VxIsAppShuttingDown() )
	{
		return false;
	}

	if( 0 == u16ListenPort )
	{
		AppErr( eAppErrBadParameter, "VxServerMgr::startListening Bad param port %d", u16ListenPort );
		return false;
	}

	m_LastWatchdogKickMs = GetTimeStampMs();
	std::string ipv4String = ip;
	m_u16ListenPort = u16ListenPort;

    LogModule( eLogListen, LOG_INFO, "### NOT IN THREAD VxServerMgr::startListening ip %s port %d app sec %d thread 0x%X", ip, u16ListenPort, GetApplicationAliveSec(), VxGetCurrentThreadId() );

#ifdef TARGET_OS_ANDROID
	// can't get ip's in native android... for now just do ipv4 TODO listen for ipv6 in android
	// ipv4 only
    SOCKET sock = socket( AF_INET, SOCK_STREAM, 0 );
	if( sock < 0 )
	{
		RCODE rc = VxGetLastError();
        LogMsg( LOG_ERROR, "VxServerMgr::startListening create skt error %d thread 0x%x", rc, VxGetCurrentThreadId() );

        if( 0 == rc )
        {
            rc = -1;
        }

        return false;
	}

	// don't know why reuse port doesn't work
	VxSetSktAllowReusePort( sock );

    LogModule( eLogListen, LOG_INFO, "StartListen binding ip %s port %d thread 0x%x", ip, u16ListenPort, VxGetCurrentThreadId() );

	struct sockaddr_in listenAddr;
    memset(&listenAddr, 0, sizeof( struct sockaddr_in ) );
	listenAddr.sin_family = AF_INET;
	listenAddr.sin_port = htons(u16ListenPort);
#if !USE_BIND_LOCAL_IP
    listenAddr.sin_addr.s_addr = INADDR_ANY; //inet_addr(ip);;
#else
    listenAddr.sin_addr.s_addr = ip ? inet_addr(ip) : INADDR_ANY;
#endif
	bool bindSuccess = false;
	for( int tryCnt = 0; tryCnt < 5; tryCnt++ )
	{
		if( 0 > bind (sock, (struct sockaddr *) &listenAddr, sizeof (sockaddr_in) ) )
		{
			RCODE rc = VxGetLastError();
			LogMsg( LOG_ERROR, "VxServerMgr::startListening bind skt %d error %d %s try cnt %d thread 0x%x", sock, rc, VxDescribeSktError( rc ), tryCnt + 1, VxGetCurrentThreadId() );
			VxSleep( 1000 );
			continue;
		}
		
		bindSuccess = true;
		break;
	}

	if( false == bindSuccess )
	{
		LogMsg( LOG_ERROR, "VxServerMgr::startListening bind skt %d FAILED thread 0x%x", sock, VxGetCurrentThreadId() );
		::VxCloseSktNow( sock );
		return false;
	}

    LogModule( eLogListen, LOG_INFO, "StartListen socket %d index %d ip %s port %d thread 0x%x", sock, m_iActiveListenSktCnt, ip, u16ListenPort, VxGetCurrentThreadId() );

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
			else
			{
                LogModule( eLogListen, LOG_INFO, "VxServerMgr::startListening found local ip4 %s\n", thisIp.c_str() );
			}
		}
		else
		{
#ifdef SUPPORT_IPV6
			if( false == thisAddr.isIPv6GlobalAddress() )
			{
				continue;
			}

            LogModule( eLogListen, LOG_INFO, "VxServerMgr::startListening found global ipv6 %s\n", thisIp.c_str() );
#else
			continue;
#endif //  SUPPORT_IPV6
		}

		// Open a socket with the correct address family for this address.
		SOCKET sock = socket( thisAddr.isIPv4() ? AF_INET : AF_INET6, SOCK_STREAM, 0);
		if( INVALID_SOCKET == sock )
		{
			LogMsg( LOG_ERROR,  "VxServerMgr::startListening socket() port %d ip %s failed with error %d: %s thread 0x%x", u16ListenPort, thisIp.c_str(),
				VxGetLastError(), VxDescribeSktError( VxGetLastError() ), VxGetCurrentThreadId() );
			continue;
		}

		if( thisAddr.isIPv4() )
		{
			struct sockaddr_in listenAddr;
			memset(&listenAddr, '\0', sizeof( struct sockaddr_in ) );
            listenAddr.sin_family = AF_INET;
            listenAddr.sin_port = htons(u16ListenPort);
#if !USE_BIND_LOCAL_IP
            listenAddr.sin_addr.s_addr = INADDR_ANY;
#else
            listenAddr.sin_addr.s_addr = ip ? inet_addr( thisIp.c_str() ) : INADDR_ANY;
#endif
			bool bindFailed = true;
			for( int i = 0; i < 3; i++ )
			{
				if (bind (sock, (struct sockaddr *) &listenAddr, sizeof ( struct sockaddr_in )) < 0)
				{
					RCODE rc = VxGetLastError();
                    LogModule( eLogListen, LOG_INFO, "VxServerMgr::startListening bind skt error %d %s try %d\n", rc, VxDescribeSktError( rc ), i+1 );
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
                LogModule( eLogListen, LOG_ERROR, "ipv4 listen() failed with error %d: %s thread 0x%x", VxGetLastError(), VxDescribeSktError( VxGetLastError() ), VxGetCurrentThreadId() );
				// fail completely
				::VxCloseSktNow( sock );
				continue;
			}
            else
            {
                LogModule( eLogListen, LOG_DEBUG, "ipv4 listen() success lcl ip %s port %d thread 0x%x", thisIp.c_str(), u16ListenPort, VxGetCurrentThreadId() );
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

            LogModule( eLogListen, LOG_INFO, "VxServerMgr::startListening success ipv6 %s thread 0x%x", thisIp.c_str(), VxGetCurrentThreadId() );
			break;
		}
	}

	if( 0 == m_iActiveListenSktCnt ) 
	{
		LogMsg( LOG_ERROR, "### ERROR: VxServerMgr::startListening unable to serve on any address thread 0x%x", VxGetCurrentThreadId());
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
bool VxServerMgr::startListening(  uint16_t u16ListenPort )
{
#if !USE_BIND_LOCAL_IP
    return startListeningNoBind( u16ListenPort );
#endif 
	stopListening();

	if( VxIsAppShuttingDown() )
	{
		return false;
	}

	if( 0 == u16ListenPort )
	{
		AppErr( eAppErrBadParameter, "VxServerMgr::startListening Bad param port %d\n", u16ListenPort );
		return false;
	}

    LogModule( eLogConnect, LOG_INFO, "VxServerMgr::startListening attempt on port %d thread 0x%x", u16ListenPort, VxGetCurrentThreadId() );

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
		return false;
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

		// only support PF_INET and PF_INET6.
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
        m_u16ListenPort = u16ListenPort;
		m_aoListenSkts[ m_iActiveListenSktCnt ] = sock;
		m_iActiveListenSktCnt++;

        if( 0 != internalStartListen() )
        {
			m_iActiveListenSktCnt = 0;
            continue;
        }

        LogModule( eLogListen, LOG_INFO, "'Listening' on port %s, protocol %s, protocol family %s\n",
			as8Port, 
			"TCP",
			(AI->ai_family == PF_INET) ? "PF_INET" : "PF_INET6");
		break;
	}

	freeaddrinfo(AddrInfo);

	if( 0 == m_iActiveListenSktCnt ) 
	{
		LogMsg( LOG_ERROR, "### Fatal error: unable to serve on any address.\n");
		return false;
	}

	return true;
}

//============================================================================
/// @brief listen on port without binding to a ip address
bool VxServerMgr::startListeningNoBind( uint16_t u16ListenPort )
{
    stopListening();

    if( VxIsAppShuttingDown() )
    {
        return false;
    }

    if( 0 == u16ListenPort )
    {
        AppErr( eAppErrBadParameter, "VxServerMgr::startListeningNoBind Bad param port %d\n", u16ListenPort );
        return false;
    }

    LogModule( eLogConnect, LOG_INFO, "VxServerMgr::startListeningNoBind attempt on port %d thread 0x%x", u16ListenPort, VxGetCurrentThreadId() );

    SOCKET sock = socket( AF_INET, SOCK_STREAM, 0 );
    if( sock < 0 ) {
        perror( "ERROR opening socket" );
        LogModule( eLogListen, LOG_ERROR, "VxServerMgr::startListeningNoBind failed to create socket" );
        return false;
    }

    struct sockaddr_in sktAddr;
    memset( &sktAddr, 0, sizeof( struct sockaddr_in ) );
    sktAddr.sin_family = AF_INET;
    sktAddr.sin_port = htons( u16ListenPort );
    sktAddr.sin_addr.s_addr = INADDR_ANY; // if set to specific address then PureVPN does not work //inet_addr( thisIp.c_str() );
    bool bindFailed = true;
    for( int i = 0; i < 3; i++ )
    {
        if( bind( sock, ( struct sockaddr * ) &sktAddr, sizeof( struct sockaddr_in ) ) < 0 )
        {
            RCODE rc = VxGetLastError();
            LogModule( eLogListen, LOG_INFO, "VxServerMgr::startListening bind skt error %d %s try %d\n", rc, VxDescribeSktError( rc ), i + 1 );
            VxSleep( 1000 );
            continue;
        }
        else
        {
            bindFailed = false;
            m_ListenSktIsBoundToIp = true;
            break;
        }
    }

    if( bindFailed )
    {
        ::VxCloseSktNow( sock );
        return false;
    }

    if( SOCKET_ERROR == listen( sock, 10 ) ) // SOMAXCONN) ) ( SOMAXCONN == maximum number of qued allowed
    {
        LogModule( eLogListen, LOG_ERROR, "ipv4 listen() failed with error %d: %s thread 0x%x", VxGetLastError(), VxDescribeSktError( VxGetLastError() ), VxGetCurrentThreadId() );
        // fail completely
        ::VxCloseSktNow( sock );
        return false;
    }
    else
    {
        LogModule( eLogListen, LOG_DEBUG, "ipv4 listen() success any ip port %d thread 0x%x", u16ListenPort, VxGetCurrentThreadId() );
    }

    m_ListenMutex.lock();
    bool listenStatus = true;
    m_u16ListenPort = u16ListenPort;
    m_LclIp.setIpAndPort( "", u16ListenPort );
    m_aoListenSkts[ m_iActiveListenSktCnt ] = sock;
    m_iActiveListenSktCnt++;
    m_ListenMutex.unlock();

    if( 0 != internalStartListen() )
    {
        LogModule( eLogListen, LOG_ERROR, "ipv4 listen() internalStartListen failed" );
        closeListenSocket();
        listenStatus = false;
    }

     return listenStatus;
}

//============================================================================
void VxServerMgr::closeListenSocket( void )
{
    if( m_iActiveListenSktCnt )
    {
        m_ListenSktIsBoundToIp = false;
        m_IsReadyToAcceptConnections = false;
        LogModule( eLogListen, LOG_DEBUG, "### VxServerMgr: Mgr %d stop listening %d skt cnt %d thread 0x%x\n", m_iMgrId, m_u16ListenPort, m_iActiveListenSktCnt, VxGetCurrentThreadId() );
        m_u16ListenPort = 0;

        // kill previous thread if running
        m_ListenVxThread.abortThreadRun( true );
        m_ListenMutex.lock();
        for( int i = 0; i < m_iActiveListenSktCnt; i++ )
        {
            if( INVALID_SOCKET != m_aoListenSkts[ i ] )
            {
                LogModule( eLogListen, LOG_INFO, "VxServerMgr: Mgr %d closing listen skt %d\n", m_iMgrId, i );

                // closing the thread should release it so it can exit
                SOCKET sktToClose = m_aoListenSkts[ i ];
                m_aoListenSkts[ i ] = INVALID_SOCKET;
                ::VxCloseSktNow( sktToClose );
            }
            else
            {
                LogModule( eLogListen, LOG_ERROR, "VxServerMgr:stopListening skt idx %d had invalid socket\n", i );
            }
        }

        m_iActiveListenSktCnt = 0;
        m_ListenMutex.unlock();
        if( m_ListenVxThread.isThreadRunning() )
        {
            m_ListenVxThread.killThread();
        }
    }
    else
    {
        LogModule( eLogListen, LOG_DEBUG, "VxServerMgr:stopListening called with no listen sockets\n" );
    }
}

//============================================================================
RCODE VxServerMgr::stopListening( void )
{
    if( !isListening() )
    {
        return 0; // not listening
    }

    closeListenSocket();
	return 0;
}

//============================================================================
RCODE VxServerMgr::acceptConnection( VxThread * poVxThread, SOCKET oListenSkt )
{
	RCODE rc = 0;
	if( INVALID_SOCKET == oListenSkt )
	{
        LogModule( eLogListen, LOG_ERROR, "VxServerMgr::acceptConnection INVALID LISTEN SOCKET thread 0x%x", VxGetCurrentThreadId() );
		return -2;
	}

	if( VxIsAppShuttingDown() )
	{
        LogModule( eLogListen, LOG_ERROR, "VxServerMgr::acceptConnection App Shutting down thread 0x%x", VxGetCurrentThreadId() );
        return -3;
	}

    static int dumpAcceptCnt = 0;
    dumpAcceptCnt++;
    if( dumpAcceptCnt > 20 )
    {
        dumpAcceptCnt = 0;
        LogModule( eLogAcceptConn, LOG_INFO, "VxServerMgr: start acceptConnection skt %d rc %d thread 0x%x", oListenSkt, VxGetLastError(), VxGetCurrentThreadId() );
    }

	// perform accept
	// setup address
    struct  sockaddr acceptAddr;
    socklen_t acceptAddrLen = sizeof( struct  sockaddr );
    memset( &acceptAddr, 0, sizeof( struct sockaddr ) );

#if defined( TARGET_OS_WINDOWS ) || defined( TARGET_OS_ANDROID )
    // NOTE: in android the return to blocking on listen doesn't work so we just set it once before start listening so accept does not get hung
    SOCKET oAcceptSkt = accept( oListenSkt, &acceptAddr, &acceptAddrLen );
#else //LINUX
	// NOTE: accept can hang waiting for connection in linux or android if
	// connection is dropped before the accept happens so set to non blocking.. the reason it hangs is it will wait until next connection occures	
	VxSetSktBlocking( oListenSkt, false );
    SOCKET oAcceptSkt = accept( oListenSkt, &acceptAddr, &acceptAddrLen );
	VxSetSktBlocking( oListenSkt, true );
#endif // LINUX

static int acceptErrCnt = 0;
    if( INVALID_SOCKET == oAcceptSkt )
    {
		rc = VxGetLastError();
        acceptErrCnt++;
        if( acceptErrCnt > 50 )
        {
            acceptErrCnt = 0;
            LogModule( eLogListen, LOG_DEBUG, "VxServerMgr::acceptConnection: listen port %d skt %d error %d thread 0x%x", m_u16ListenPort, oListenSkt, rc, VxGetCurrentThreadId() );
        }

		if( 0 == rc )
		{
			// not sure how it happens but seems to get in a loop where the clear doesn't clear and there is no error
			// so sleep just in case so doesn't eat up all the CPU
            LogModule( eLogListen, LOG_INFO, "VxServerMgr: no rc acceptConnection skt %d rc %d thread 0x%x", oListenSkt, VxGetLastError(), VxGetCurrentThreadId() );
			VxSleep( 500 );
			return -1;
		}
        else if( 10035 == rc )
        {
            // windows non blocking operation could not be done immediate error
            VxSleep( 200 );
            static int intRetry1Cnt = 0;
            intRetry1Cnt++;
            if( intRetry1Cnt > 20 )
            {
                intRetry1Cnt = 0;
                LogModule( eLogAcceptConn, LOG_INFO, "VxServerMgr: non blocking operation  acceptConnection skt %d rc %d thread 0x%x", oListenSkt, VxGetLastError(), VxGetCurrentThreadId() );
            }

            return 0;
        }
        else if( 11 == rc )
        {
            // linux/android non blocking operation could not be done immediate error
            VxSleep( 200 );
            static int intRetry2Cnt = 0;
            intRetry2Cnt++;
            if( intRetry2Cnt > 20 )
            {
                intRetry2Cnt = 0;
                LogModule( eLogAcceptConn, LOG_INFO, "VxServerMgr: non blocking operation  acceptConnection skt %d rc %d thread 0x%x", oListenSkt, VxGetLastError(), VxGetCurrentThreadId() );
            }

            return 0;
        }
		else
		{
            LogModule( eLogListen, LOG_INFO, "VxServerMgr: other error acceptConnection skt %d rc %d thread 0x%x", oListenSkt, VxGetLastError(), VxGetCurrentThreadId() );
			VxSleep( 200 );
			return rc;
		}
    }
    else
    {
        acceptErrCnt = 0;
    }

    LogModule( eLogListen, LOG_DEBUG, "VxServerMgr::acceptConnection: listen skt %d accepted skt %d thread 0x%x", oListenSkt, oAcceptSkt, VxGetCurrentThreadId() );
	if( poVxThread->isAborted() || VxIsAppShuttingDown() ) 
	{
		return -1;
	}

	// valid accept socket
	if( m_aoSkts.size() >= m_u32MaxConnections )
	{
        LogMsg( LOG_ERROR, "VxServerMgr: reached max connections %d thread 0x%x", m_u32MaxConnections, VxGetCurrentThreadId() );
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

    LogModule( eLogListen, LOG_INFO, "VxServerMgr: doing accept skt %d skt id %d thread 0x%x", sktBase->m_Socket, sktBase->getSktId(), VxGetCurrentThreadId() );

    RCODE rcAccept = sktBase->doAccept( this, *(( struct sockaddr * )&acceptAddr) );
	if( rcAccept || poVxThread->isAborted() || INVALID_SOCKET == oListenSkt )
	{
		sktBase->closeSkt(67823);
		LogMsg( LOG_ERROR, "VxServerMgr: error %d doing accept skt %d skt id %d thread 0x%x", rc, sktBase->m_Socket, sktBase->getSktId(), VxGetCurrentThreadId() );
		// if error occurred then remove it from our list or it
		// will never get removed
		m_SktMgrMutex.lock(__FILE__, __LINE__); // dont let other threads mess with array while we remove
		m_aoSkts.pop_back();
		m_SktMgrMutex.unlock(__FILE__, __LINE__);
		delete sktBase;
        rc = -5;
	}
    else
    {
        acceptErrCnt = 0; // reset counter
        LogModule( eLogListen, LOG_INFO, "VxServerMgr: accept success skt %d skt id %d thread 0x%x", sktBase->m_Socket, sktBase->getSktId(), VxGetCurrentThreadId() );
    }

	return rc;
}

//============================================================================
void VxServerMgr::listenForConnectionsToAccept( VxThread * poVxThread )
{
#ifdef DEBUG_SKT_CONNECTIONS
	//LogMsg( LOG_INFO, "111 IN THREAD VxServerMgr::listenForConnectionsToAccept started\n" ); 
	//LogMsg( LOG_INFO, "111 IN THREAD VxServerMgr::listen port %d ip %s skt %d\n", m_LclIp.getPort(), m_LclIp.toStdString().c_str(), m_aoListenSkts[0] ); 
#endif // DEBUG_SKT_CONNECTIONS

    m_IsReadyToAcceptConnections = true;
//#ifdef TARGET_OS_ANDROID
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
		
        RCODE rc = VxGetLastError();

        if( rc )
        {
            if( rc == EAGAIN )
            {
                static int listenErrCnt = 0;
                listenErrCnt++;
                if( listenErrCnt > 50 )
                {
                    listenErrCnt = 0;
                    LogModule( eLogListen, LOG_DEBUG, "listenForConnectionsToAccept: try again: listen ip %s port %d skt %d error %d thread 0x%x", m_LclIp.toStdString().c_str(), m_u16ListenPort, m_aoListenSkts[0], rc, VxGetCurrentThreadId() );
                }

                VxSleep( 200 );
                continue;
            }
        }

		acceptConnection( poVxThread, m_aoListenSkts[0] );
	}	
	
	m_IsReadyToAcceptConnections = false;
	if( INVALID_SOCKET != m_aoListenSkts[ 0 ] )
	{
		SOCKET sktToClose = m_aoListenSkts[ 0 ];
        LogModule( eLogListen, LOG_INFO, "VxServerMgr:listenForConnectionsToAccept closing listen skt %d\n", sktToClose );
		m_aoListenSkts[ 0 ] = INVALID_SOCKET;
		::VxCloseSktNow( sktToClose );
	}

	if( (false == VxIsAppShuttingDown() )
		&& ( false == checkWatchdog() ) )
	{
        LogModule( eLogListen, LOG_ERROR, "Listen Failed Watchdog\n" );
		std::terminate();
	}
/*
#else
	
	int iSelectResult;
	RCODE rc = 0;
	//LogMsg( LOG_INFO, "Listen VxThread start\n" );
    fd_set					oListenSocketFileDescriptors;
    fd_set					oReadSocketFileDescriptors;
	struct timeval			oListenTimeout;

    FD_ZERO( &oListenSocketFileDescriptors );
    FD_ZERO( &oReadSocketFileDescriptors );

    LogModule( eLogConnect, LOG_INFO, "listenForConnectionsToAccept has %d listen sockets thread 0x%x", m_iActiveListenSktCnt, VxGetCurrentThreadId() );
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
        // LogModule( eLogConnect, LOG_INFO, "Listen VxThread select result %d at %d seconds", iSelectResult, GetApplicationAliveSec() );

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
                    LogModule( eLogConnect, LOG_INFO, "#### VxServerMgr::acceptConnection: accepting at index %d\n", iSelectedIdx );
					rc = acceptConnection( poVxThread, m_aoListenSkts[iSelectedIdx] );
					if( rc )
					{
						LogMsg( LOG_ERROR, "#### VxServerMgr::acceptConnection: error %d %s doing accept\n", rc, VxDescribeSktError(rc) );
					}
					else
					{
						LogModule( eLogConnect, LOG_INFO, "#### VxServerMgr::acceptConnection: success doing accept\n" );
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
#endif 
*/
    LogModule( eLogConnect, LOG_INFO, "Listen Thread is exiting thread 0x%x", VxGetCurrentThreadId() );
	m_IsReadyToAcceptConnections = false;
}
