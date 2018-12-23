//============================================================================
// Copyright (C) 2013 Brett R. Jones
// Issued to MIT style license by Brett R. Jones in 2017
//
// You may use, copy, modify, merge, publish, distribute, sub-license, and/or sell this software
// provided this Copyright is not modified or removed and is included all copies or substantial portions of the Software
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// brett.jones@engineer.com
// http://www.gotvptop.net
//============================================================================

#include "VxConnectInfo.h"

#include <CoreLib/VxParse.h>
#include <CoreLib/VxGlobals.h>
#include <NetLib/VxSktUtil.h>

#include <memory.h>

#ifdef TARGET_OS_LINUX
# include <sys/types.h>
# include <netinet/in.h>
# include <inttypes.h>

# define ntohll be64toh
# define htonll htobe64
#endif // TARGET_OS_LINUX

namespace
{
    const unsigned int MIN_INTERVAL_CONNECT_REQUEST_MS				= (5 * 60000);
}

//============================================================================
VxConnectBaseInfo::VxConnectBaseInfo()
{
}

//============================================================================
VxConnectBaseInfo::VxConnectBaseInfo( const VxConnectBaseInfo &rhs )
{
	*this = rhs;
}


//============================================================================
VxConnectBaseInfo& VxConnectBaseInfo::operator =( const VxConnectBaseInfo &rhs )
{
	if( this != &rhs )
	{
		// we can get away with memcpy because no virtual functions
		memcpy( this, &rhs, sizeof( VxConnectBaseInfo ) );
	}

	return *this;
}

//============================================================================
void VxConnectBaseInfo::setMyOnlineId( uint64_t u64HiPart, uint64_t u64LoPart )
{ 
	m_DirectConnectId.setVxGUID( u64HiPart, u64LoPart );
}

//============================================================================
VxGUID& VxConnectBaseInfo::getMyOnlineId()								
{ 
	return m_DirectConnectId; 
}

void			VxConnectBaseInfo::getMyOnlineId( std::string& strRetId )		{ return m_DirectConnectId.toVxGUIDHexString( strRetId ); }
uint64_t		VxConnectBaseInfo::getMyOnlineIdLoPart()						{ return m_DirectConnectId.getVxGUIDLoPart(); }
uint64_t		VxConnectBaseInfo::getMyOnlineIdHiPart()						{ return m_DirectConnectId.getVxGUIDHiPart(); }

VxGUID&			VxConnectBaseInfo::getRelayOnlineId()							{ return m_RelayConnectId; }
void			VxConnectBaseInfo::getRelayOnlineId( std::string& strRetId )	{ return m_RelayConnectId.toVxGUIDHexString( strRetId ); }
uint64_t		VxConnectBaseInfo::getRelayOnlineIdLoPart()						{ return m_RelayConnectId.getVxGUIDLoPart(); }
uint64_t		VxConnectBaseInfo::getRelayOnlineIdHiPart()						{ return m_RelayConnectId.getVxGUIDHiPart(); }
void			VxConnectBaseInfo::setRelayPort( uint16_t port )						{ m_RelayConnectId.setPort( port ); }		
uint16_t		VxConnectBaseInfo::getRelayPort( void )							{ return m_RelayConnectId.getPort(); }

void			VxConnectBaseInfo::getMyOnlineIPv4( std::string& strRetIp )		{ strRetIp = m_DirectConnectId.m_IPv4OnlineIp.toStdString(); }
void			VxConnectBaseInfo::getMyOnlineIPv6( std::string& strRetIp )		{ m_DirectConnectId.getIPv6( strRetIp );}
InetAddrIPv4&	VxConnectBaseInfo::getMyOnlineIPv4( void )						{ return m_DirectConnectId.m_IPv4OnlineIp; }
InetAddress&	VxConnectBaseInfo::getMyOnlineIPv6( void )						{ return m_DirectConnectId.m_IPv6OnlineIp;}
void			VxConnectBaseInfo::setMyOnlinePort( uint16_t port )					{ m_DirectConnectId.setPort( port ); }		
uint16_t		VxConnectBaseInfo::getMyOnlinePort( void )						{ return m_DirectConnectId.getPort(); }

//============================================================================
//! get ip based on if we can connect ipv6 or ipv4 if not
InetAddress	VxConnectBaseInfo::getOnlineIpAddress( void )
{
	//if( VxCanConnectUsingIPv6() && m_DirectConnectId.m_IPv6OnlineIp.isValid() )
	//{
	//	return m_DirectConnectId.m_IPv6OnlineIp;
	//}
	//else
	//{
		//InetAddress oAddr;
		//oAddr.setIp( m_DirectConnectId.m_IPv4OnlineIp.getIPv4Address() );
		//return oAddr;
//	}
	return m_DirectConnectId.m_IPv4OnlineIp.toInetAddress();
}

//============================================================================
//! get ip based on if we can connect ipv6 or ipv4 if not
InetAddress	VxConnectBaseInfo::getRelayIpAddress( void )
{
	//if( VxCanConnectUsingIPv6() && m_RelayConnectId.m_IPv6OnlineIp.isValid() )
	//{
	//	return m_RelayConnectId.m_IPv6OnlineIp;
	//}
	//else
	//{
		return m_RelayConnectId.m_IPv4OnlineIp.toInetAddress();
//	}
}

//============================================================================
void VxConnectBaseInfo::setOnlineIpAddress( const char * pIp )			
{ 
	m_DirectConnectId.setIpAddress( pIp ); 
};

//============================================================================
void VxConnectBaseInfo::setOnlineIpAddress( InetAddress& oIp )			
{ 
	if( oIp.isIPv4() )
	{
		m_DirectConnectId.m_IPv4OnlineIp.setIp( oIp.getIPv4AddressInNetOrder() );
	}
	else
	{
		m_DirectConnectId.m_IPv6OnlineIp  = oIp;
	}
}

//============================================================================
uint16_t	VxConnectBaseInfo::getOnlinePort( void )							
{ 
	return m_DirectConnectId.getPort(); 
};

//============================================================================
void VxConnectBaseInfo::getOnlinePort( std::string& strRetPort )	
{ 
	StdStringFormat( strRetPort, "%d", m_DirectConnectId.getPort() ); 
}

//============================================================================
void VxConnectBaseInfo::setOnlinePort( uint16_t u16Port )				
{ 
	m_DirectConnectId.setPort( u16Port ); 
}

//============================================================================
bool VxConnectBaseInfo::hasValidRelay( void )
{
	if( 0 == m_RelayConnectId.getVxGUIDHiPart() 
		|| 0 == m_RelayConnectId.getVxGUIDLoPart() 
		|| (0 == m_RelayConnectId.getPort()) )
	{
		return false;
	}
	return true;
}

//============================================================================
// VxConnectIdent
//============================================================================
VxConnectIdent::VxConnectIdent()
: m_TimeLastContact( 0 )
, m_IdentRes1( 0 )
, m_IdentRes2( 0 )
{
	m_OnlineName[0] = 0;
	m_OnlineDesc[0] = 0;
}

//============================================================================
char *	VxConnectIdent::getOnlineName( void )							
{ 
	return m_OnlineName; 
}

//============================================================================
void 	VxConnectIdent::setOnlineName( const char * pUserName )			
{ 
	SafeStrCopy( m_OnlineName, pUserName, sizeof( m_OnlineName )); 
}

//============================================================================
//! return users online description
char *	VxConnectIdent::getOnlineDescription( void )					
{	
	return m_OnlineDesc; 
}

//============================================================================
//! set users online description
void 	VxConnectIdent::setOnlineDescription( const char * pUserDesc )	
{ 
	SafeStrCopy( m_OnlineDesc, pUserDesc, sizeof( m_OnlineDesc )); 
}

//============================================================================
// VxConnectInfo
//============================================================================
VxConnectInfo::VxConnectInfo()
: m_s64TimeTcpLastContactMs( 0 )
, m_s64TimeLastConnectAttemptMs( 0 )
, m_u64TimeReserved( 0 )
{
}

//============================================================================
VxConnectInfo::VxConnectInfo( const VxConnectInfo &rhs )
{
	*this = rhs;
}

//============================================================================
VxConnectInfo& VxConnectInfo::operator =( const VxConnectInfo &rhs )
{
	if( this != &rhs )
	{
		// we can get away with memcpy because no virtual functions
		memcpy( this, &rhs, sizeof( VxConnectInfo ) );
	}

	return *this;
}

//============================================================================
void VxConnectInfo::setTimeLastConnectAttemptMs( int64_t timeLastAttemptGmtMs )
{
	m_s64TimeLastConnectAttemptMs = timeLastAttemptGmtMs;
}

//============================================================================
int64_t VxConnectInfo::getTimeLastConnectAttemptMs( void )
{
	return m_s64TimeLastConnectAttemptMs;
}

//============================================================================
bool VxConnectInfo::isTooSoonToAttemptConnectAgain( void )
{
	return ( MIN_INTERVAL_CONNECT_REQUEST_MS > ( GetGmtTimeMs() - m_s64TimeLastConnectAttemptMs ) );
}

//============================================================================
void VxConnectInfo::setTimeLastTcpContactMs( int64_t timeGmtMs )
{
	m_s64TimeTcpLastContactMs = htonll( timeGmtMs );
}

//============================================================================
int64_t	VxConnectInfo::getTimeLastTcpContactMs( void )
{
	return ntohll( m_s64TimeTcpLastContactMs );
}

//============================================================================
//! get seconds since any last contact
int64_t VxConnectInfo::getElapsedMsAnyContact( void )	
{ 
    return ( GetGmtTimeMs() -  getTimeLastTcpContactMs() );
}

//============================================================================
//! get milli seconds since last tcp contact
int64_t VxConnectInfo::getElapsedMsTcpLastContact( void )	
{ 
	return ( GetGmtTimeMs() - getTimeLastTcpContactMs() ); 
}
