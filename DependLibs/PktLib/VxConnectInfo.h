#pragma once
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
// bjones.engineer@gmail.com
// http://www.gotvptop.com
//============================================================================

#include "VxConnectId.h"
#include "VxRelayFlags.h"
#include "VxFriendMatch.h"
#include "VxSearchFlags.h"

#define OS_APPLE_FLAG				0x01	
#define OS_ANDROID_FLAG				0x02	
#define OS_LINUX_FLAG				0x04	
#define OS_WINDOWS_FLAG				0x08	


#define MAX_ONLINE_NAME_LEN		24	//maximum length of online name including 0 terminator
#define MAX_ONLINE_DESC_LEN		28	//maximum length of online description including 0 terminator

#pragma pack(push) 
#pragma pack(1)
// size
// +  1 byte VxRelayFlags
// +  1 byte FriendMatch
// +  2 bytes VxSearchFlags
// +  4 bytes m_LanIPv4
// + 38 bytes m_DirectConnectId
// + 38 bytes m_RelayConnectId 
// = 84 bytes 
class VxConnectBaseInfo : public VxRelayFlags, public FriendMatch, public VxSearchFlags
{
public:
	VxConnectBaseInfo() = default;
	VxConnectBaseInfo( const VxConnectBaseInfo& rhs );

	VxConnectBaseInfo& operator =( const VxConnectBaseInfo& rhs );

	void						setMyOnlineId( uint64_t u64HiPart, uint64_t u64LoPart );
	VxGUID&						getMyOnlineId();
	void						getMyOnlineId( std::string& strRetId );
    std::string&				getMyOnlineIdHexString( void )  { return m_DirectConnectId.toHexString(); }
    uint64_t					getMyOnlineIdLoPart();
	uint64_t					getMyOnlineIdHiPart();
	void						setMyOnlinePort( uint16_t port );
	uint16_t					getMyOnlinePort( void );

	VxGUID&						getRelayOnlineId();
	void						getRelayOnlineId( std::string& strRetId );
	uint64_t					getRelayOnlineIdLoPart();
	uint64_t					getRelayOnlineIdHiPart();
	void						setRelayPort( uint16_t port );
	uint16_t					getRelayPort( void );

	void						getMyOnlineIPv4( std::string& strRetIp );
	void						getMyOnlineIPv6( std::string& strRetIp );
	InetAddrIPv4&				getMyOnlineIPv4( void );
	InetAddress&				getMyOnlineIPv6( void );

	InetAddrIPv4&				getLanIPv4( void )					{ return m_LanIPv4; }

	InetAddress					getOnlineIpAddress( void );
	InetAddress					getRelayIpAddress( void );

	void						setOnlineIpAddress( InetAddress& oIp );
	void						setOnlineIpAddress( const char * pIp );

	uint16_t					getOnlinePort( void );
	void						getOnlinePort( std::string& strRetPort );
	void						setOnlinePort( uint16_t u16Port );

	bool						hasValidRelay( void );

	VxConnectId&				getDirectConnectId( void )							{ return m_DirectConnectId; }
	VxConnectId&				geRelayConnectId( void )							{ return m_RelayConnectId; }

	//=== vars ===//
	InetAddrIPv4				m_LanIPv4;
	VxConnectId					m_DirectConnectId;
	VxConnectId					m_RelayConnectId;
};

//    84 bytes VxConnectBaseInfo
// +  24 bytes Online Name
// +  28 bytes Online Mood Message
// = 136 bytes
// + 16  reserved bytes
// = 152 bytes

class VxConnectIdent : public VxConnectBaseInfo
{
public:
	VxConnectIdent();

	VxConnectBaseInfo& 			getConnectBaseInfo( void )	{ return * ((VxConnectBaseInfo *)this); }
	VxConnectIdent& 			getConnectIdent( void )		{ return * ((VxConnectIdent *)this); }

	void 						setOnlineName( const char * pUserName );
    char *                      getOnlineName( void );

	void 						setOnlineDescription( const char * pUserDesc );
	char *						getOnlineDescription( void );

	void 						setTimeLastContact( int64_t timeStamp )				{ m_TimeLastContact = timeStamp; }
	int64_t	    				getTimeLastContact( void )					        { return m_TimeLastContact; }		

    /// @brief return indenty unique folder name in the form of OnlineName_GuidHexString
    std::string	    			getIdentFolderName( void );

	//=== vars ===//
private:
	char						m_OnlineName[ MAX_ONLINE_NAME_LEN ];	// users online name
	char						m_OnlineDesc[ MAX_ONLINE_DESC_LEN ]; // users online description 28 bytes
	int64_t	    				m_TimeLastContact;
	uint32_t					m_IdentRes1;
	uint32_t					m_IdentRes2;
};

//   152 bytes VxConnectBaseInfo
// +   8 bytes m_u32TimeTcpLastContact
// +   8 bytes last connect attempt
// +   8 bytes reserved to fill to 16 byte boundary
// = 176 bytes total
class VxConnectInfo : public VxConnectIdent
{
public:
	VxConnectInfo();
	VxConnectInfo( const VxConnectInfo& rhs );

	VxConnectInfo& operator =( const VxConnectInfo& rhs );

	void						setTimeLastConnectAttemptMs( int64_t timeLastAttempt );
	int64_t 					getTimeLastConnectAttemptMs( void );
	bool						isTooSoonToAttemptConnectAgain( void );

	void						setTimeLastTcpContactMs( int64_t time );
	int64_t	    				getTimeLastTcpContactMs( void );

	int64_t		    			getElapsedMsAnyContact( void );	
	int64_t			    		getElapsedMsTcpLastContact( void );

	//=== vars ===//
private:
	int64_t					    m_s64TimeLastConnectAttemptMs;
	int64_t					    m_s64TimeTcpLastContactMs;	// time of last contact via tcp
    int64_t					    m_u64TimeReserved;
};

#pragma pack(pop)
