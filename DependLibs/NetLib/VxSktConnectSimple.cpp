//============================================================================
// Copyright (C) 2008 Brett R. Jones 
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
#include "VxSktConnectSimple.h"

#include <CoreLib/VxDebug.h>
#include <CoreLib/VxGlobals.h>

#include <memory.h>

#ifndef TARGET_OS_WINDOWS
	#include <fcntl.h>
#endif // TARGET_OS_WINDOWS

//============================================================================
VxSktConnectSimple::VxSktConnectSimple()
: m_Socket( INVALID_SOCKET )
, m_LclIp( VxGetLclIpAddress().c_str() )
{
}

//============================================================================
VxSktConnectSimple::~VxSktConnectSimple()
{
	closeSkt( 99 );
}

//============================================================================
bool VxSktConnectSimple::isConnected( void )
{
	if( INVALID_SOCKET == m_Socket )
	{
		m_bIsConnected = false;
	}

	return m_bIsConnected;
}

//============================================================================
//! connect to remote ip
SOCKET VxSktConnectSimple::connectTo(	const char *	pIpOrUrl,				// remote ip or url
										uint16_t				u16Port,				// port to connect to
										int				iTimeoutMilliSeconds )	// milli seconds before connect attempt times out
{
	if( isConnected() )
	{
		LogMsg( LOG_INFO, "VxSktConnectSimple::connectTo: connect attempt on allready connected socket\n" );
		return -1;
	}

	m_bIsConnected	= false;
	m_Socket		= VxConnectTo( m_LclIp, m_RmtIp, pIpOrUrl, u16Port, iTimeoutMilliSeconds );
	if( INVALID_SOCKET != m_Socket )
	{
		VxGetLclAddress( m_Socket, m_LclIp );
		m_bIsConnected = true;
	}

	return m_Socket;
}

//============================================================================
RCODE VxSktConnectSimple::sendData(	const char *	pData,					// data to send
									int				iDataLen,				// length of data
									int				iTimeoutSeconds )		// seconds before send attempt times out
{
	if( false == this->isConnected() )
	{
		LogMsg( LOG_INFO, "VxSktConnectSimple::sendData: attempted send on disconnected socket\n" );
		return -1;
	}

	RCODE rc = VxSendSktData( m_Socket, pData, iDataLen, iTimeoutSeconds );
	if( rc || (INVALID_SOCKET == m_Socket) )
	{
		closeSkt(8689);		
	}

	return rc;
}
		
//============================================================================
//! receive data.. if timeout is set then will keep trying till buffer is full or error or timeout expires
RCODE VxSktConnectSimple::recieveData(	char *			pRetBuf,				// buffer to receive data into
										int				iBufLenIn,				// length of buffer
										int *			iRetBytesReceived,		// number of bytes actually received
										int				iTimeoutMilliSeconds,	// milliseconds before receive attempt times out ( 0 = dont wait )
										bool			bAbortIfCrLfCrLf,		// if true then abort receive when \r\n\r\n is received
										bool *			pbRetGotCrLfCrLf )		// if received \r\n\r\n set to true
{
	return VxReceiveSktData( m_Socket, pRetBuf, iBufLenIn, iRetBytesReceived, iTimeoutMilliSeconds, bAbortIfCrLfCrLf, pbRetGotCrLfCrLf);
}

//============================================================================
//! close socket
void VxSktConnectSimple::closeSkt( int iInstance )
{
	m_bIsConnected	= false;
	if( INVALID_SOCKET != m_Socket )
	{
		SOCKET skt = m_Socket;
		m_Socket = INVALID_SOCKET;

		VxCloseSktNow( skt );
	}
}

//============================================================================
bool VxSktConnectSimple::connectToWebsite( 	const char *		pWebsiteUrl,
											std::string&		strHost,		// return host name.. example http://www.mysite.com/index.htm returns www.mysite.com
											std::string&		strFile,		// return file name.. images/me.jpg
											uint16_t&				u16Port,
											int					iConnectTimeoutMs )
{
	closeSkt( 99 );
	m_bIsConnected	= false;
	m_Socket = VxConnectToWebsite( m_LclIp, m_RmtIp, pWebsiteUrl, strHost, strFile, u16Port, iConnectTimeoutMs );
	if( INVALID_SOCKET != m_Socket )
	{
		m_bIsConnected = true;
		VxGetLclAddress( m_Socket, m_LclIp );
		VxGetRmtAddress( m_Socket, m_RmtIp );
#ifdef DEBUG_SKT
		LogMsg( LOG_INFO, "VxSktConnectSimple::connectToWebsite Lcl port %d (0x%4.4x) Rmt port %d (0x%4.4x)\n", 
			m_LclIp.getPort(),
			m_LclIp.getPort(),
			m_RmtIp.getPort(),
			m_RmtIp.getPort() );
#endif // DEBUG_SKT
	}

	return m_bIsConnected;
}

//============================================================================
void VxSktConnectSimple::dumpConnectionInfo( void )
{
	InetAddrAndPort  rmtAddr;
	InetAddrAndPort  lclAddr;

	VxGetRmtAddress( m_Socket, rmtAddr );
	uint16_t rmtPort = rmtAddr.getPort();
	std::string rmtIp = rmtAddr.toStdString();
	
	VxGetLclAddress( m_Socket, lclAddr );
	uint16_t lclPort = lclAddr.getPort();
	std::string lclIp = lclAddr.toStdString();

	LogMsg( LOG_INFO, "VxSktConnectSimple: Rmt ip %s port %d Lcl ip %s port %d\n",
			rmtIp.c_str(),
			rmtPort,
			lclIp.c_str(),
			lclPort );

	rmtPort = m_RmtIp.getPort();
	rmtIp = m_RmtIp.toStdString();

	lclPort = m_LclIp.getPort();
	lclIp = m_LclIp.toStdString();
	LogMsg( LOG_INFO, "VxSktConnectSimple: 2 Rmt ip %s port %d Lcl ip %s port %d\n",
		rmtIp.c_str(),
		rmtPort,
		lclIp.c_str(),
		lclPort );

}
