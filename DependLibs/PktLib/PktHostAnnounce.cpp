//============================================================================
// Copyright (C) 2003 Brett R. Jones 
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

#include "PktHostAnnounce.h"
#include "PktTypes.h"

#include <CoreLib/VxParse.h>
#include <CoreLib/VxGlobals.h>
#include <CoreLib/VxMutex.h>
#include <CoreLib/VxTime.h>

#include <memory.h>

//============================================================================
//============================================================================
PktHostAnnounce::PktHostAnnounce()
    : PktAnnounce()
{ 
	setPktLength( sizeof( PKT_TYPE_HOST_ANNOUNCE ) );
	setPktType(  PKT_TYPE_HOST_ANNOUNCE );
    setPktVersionNum( PKT_HOST_ANNOUNCE_VERSION );

	vx_assert( 0 == ( getPktLength() & 0x0f ) );
}

//============================================================================
PktHostAnnounce *	PktHostAnnounce::makeHostAnnCopy( void )
{
	vx_assert( sizeof( PktHostAnnounce ) ==  getPktLength() );
	vx_assert( PKT_TYPE_HOST_ANNOUNCE == getPktType() );
	char * pTemp = new char[ getPktLength() ];
	vx_assert( pTemp );
	memcpy( pTemp, this, getPktLength() );
	return ( PktHostAnnounce *)pTemp;
}

//============================================================================
PktHostAnnounce *	PktHostAnnounce::makeHostAnnReverseCopy( void )
{
	PktHostAnnounce * pTemp = makeHostAnnCopy();
	pTemp->reversePermissions();
	return pTemp;
}

//============================================================================
bool PktHostAnnounce::isValidPktHostAnn( void )
{
	return ( ( getPktLength() == sizeof( PktHostAnnounce ) ) &&
			 ( getPktType() == PKT_TYPE_HOST_ANNOUNCE ) );
}


//============================================================================
//! dump contents of pkt announce for debug
void PktHostAnnounce::DebugHostDump( void )
{
	std::string strName;
	std::string strDesc;
	std::string strIp;
	std::string strId;

	this->getMyOnlineId( strId );
	this->getMyOnlineIPv4( strIp );
	uint16_t u16Port = this->getOnlinePort();
	strName = this->getOnlineName();
	strDesc = this->getOnlineDescription();
	//strNetwork = this->getNetworkKey();

	LogMsg( LOG_INFO, "PktHostAnnounce Len %d Version #%d name %s Ip %s Port %d desc %s\n",
			getPktLength(),		// packet length
			getPktVersionNum(),		// version of program
			strName.c_str(),		
			strIp.c_str(),		// IP of announcer
			u16Port,			// Port announcer listens on
			strDesc.c_str()
			);		
}

