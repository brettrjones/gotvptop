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

#include "PktTypes.h"
#include "PktsHostListXfer.h"
#include <GoTvCore/GoTvP2P/HostListMgr/HostListInfo.h>

#include <CoreLib/VxChop.h>
#include <CoreLib/VxDebug.h>
#include <CoreLib/VxParse.h>

#include <string.h>

//============================================================================
// PktHostListSendReq
//============================================================================
PktHostListSendReq::PktHostListSendReq()
: m_HostListType( (uint16_t)eHostListTypeUnknown ) 
, m_u32Error(0)
, m_s64HostListLen(0)
, m_s64HostListOffs(0) 
, m_CreationTime(0)
, m_HostListNameLen(0)
, m_HostListTagLen(0)
, m_u32Res1(0)
, m_u32Res2(0)
, m_u32Res3(0)
, m_u32Res4(0)
{ 
	setPktType( PKT_TYPE_HOST_LIST_SEND_REQ );
	m_HostListNameAndTag[0] = 0;
}

//============================================================================
void PktHostListSendReq::fillPktFromHostList( HostListInfo& hostInfo )
{
	setHostListType( (uint16_t)hostInfo.getHostListType() );
	setCreatorId( hostInfo.getCreatorId() );
	setHistoryId( hostInfo.getHistoryId() );
	setUniqueId( hostInfo.getHostListUniqueId() );
	setHostListHashId( hostInfo.getHostListHashId() );
	setHostListLen( hostInfo.getHostListLength() );
	setCreationTime( (uint32_t) hostInfo.getCreationTime() );
	setHostListNameAndTag( hostInfo.getHostListName().c_str(), hostInfo.getHostListTag().c_str() );
}

//============================================================================
void PktHostListSendReq::fillHostListFromPkt( HostListInfo& hostInfo )
{
	hostInfo.setHostListType( (EHostListType)getHostListType() );
	hostInfo.setHostListUniqueId( getUniqueId() );
	hostInfo.setCreatorId( getCreatorId() );
	hostInfo.setHistoryId( getHistoryId() );
	hostInfo.setHostListHashId( getHostListHashId() );
	hostInfo.setHostListLength( getHostListLen() );
	hostInfo.setCreationTime( (time_t)getCreationTime() );
	std::string assetName = getHostListName();
	hostInfo.setHostListName( assetName );
	if( getHostListTagLen() )
	{
		hostInfo.setHostListTag(  &m_HostListNameAndTag[ getHostListNameLen() ] );
	}
}

//============================================================================
std::string PktHostListSendReq::getHostListName()
{
	return m_HostListNameAndTag;
}

//============================================================================
std::string PktHostListSendReq::getHostListTag()
{
	std::string strTag = "";
	if( getHostListTagLen() )
	{
		strTag = &m_HostListNameAndTag[ getHostListNameLen() ];
	}

	return strTag;
}

//============================================================================
void PktHostListSendReq::setHostListNameAndTag( const char * pHostListName, const char * pHostListTag )
{
	int nameLen = (int)strlen( pHostListName );
	if( nameLen > 4095 )
	{
		nameLen = 4095;
		strncpy( m_HostListNameAndTag, pHostListName, nameLen );
		m_HostListNameAndTag[ nameLen ] = 0;
	}
	else
	{
		strcpy( m_HostListNameAndTag, pHostListName );	
	}

	nameLen += 1;
	setHostListNameLen( (uint16_t)nameLen );

	int tagLen = 0;
	if( pHostListTag )
	{
		tagLen = (int)strlen( pHostListTag );
		if( tagLen > 0 )
		{
			if( tagLen > 4095 )
			{
				tagLen = 4095;
				strncpy( &m_HostListNameAndTag[nameLen], pHostListTag, tagLen );
				m_HostListNameAndTag[ nameLen = tagLen ] = 0;
			}
			else
			{
				strcpy( &m_HostListNameAndTag[nameLen], pHostListTag );	
			}

			tagLen += 1;
			setHostListTagLen( (uint16_t)tagLen );
		}
	}

	uint16_t u16PktLen = ( uint16_t )( ( sizeof( PktHostListSendReq ) - sizeof( m_HostListNameAndTag ) ) + nameLen + tagLen );
	setPktLength( ROUND_TO_16BYTE_BOUNDRY( u16PktLen ) );
}

//============================================================================
PktHostListSendReply::PktHostListSendReply()
: m_u8RequiresFileXfer( 0 )
, m_u8Res( 0 )
, m_u16Res( 0 )
, m_s64HostListOffs( 0 )
, m_u32Error(0) 
, m_u32Res1( 0 )
, m_u32Res2(0)
{ 
	setPktType( PKT_TYPE_HOST_LIST_SEND_REPLY );
	setPktLength( sizeof( PktHostListSendReply ) );
	vx_assert( 0 == ( getPktLength() & 0x0f ) );
}

//============================================================================
PktHostListChunkReq::PktHostListChunkReq()
: m_u16Res(0)
, m_u16HostListChunkLen(0)
, m_u32Error(0)
, m_u32Res1(0) 
{
	setPktType( PKT_TYPE_HOST_LIST_CHUNK_REQ );
	setPktLength( emptyLength() );
}

//============================================================================
uint16_t PktHostListChunkReq::emptyLength( void )
{ 
	return (uint16_t)(sizeof( PktHostListChunkReq) - PKT_TYPE_HOST_LIST_MAX_DATA_LEN);
}

//============================================================================
void PktHostListChunkReq::setChunkLen( uint16_t u16ChunkLen ) 
{ 
	m_u16HostListChunkLen = htons( u16ChunkLen ); 
	setPktLength( ROUND_TO_16BYTE_BOUNDRY( emptyLength() + u16ChunkLen ) );
}

//============================================================================
uint16_t PktHostListChunkReq::getChunkLen( void ) 
{ 
	return htons( m_u16HostListChunkLen ); 
}

//============================================================================
PktHostListChunkReply::PktHostListChunkReply()
: m_u16Res(0)
, m_u16HostListChunkLen(0)
, m_u32Error(0) 
{
	setPktType( PKT_TYPE_HOST_LIST_CHUNK_REPLY );
	setPktLength( (uint16_t)sizeof( PktHostListChunkReply ) );
}

//============================================================================
PktHostListSendCompleteReq::PktHostListSendCompleteReq()
: m_u32Error( 0 )
, m_u32Res1( 0 )
{
	setPktType(  PKT_TYPE_HOST_LIST_SEND_COMPLETE_REQ );
	setPktLength( (uint16_t)sizeof( PktHostListSendCompleteReq ) );
	vx_assert( 0 == ( getPktLength() & 0x0f ) );}

//============================================================================
PktHostListSendCompleteReply::PktHostListSendCompleteReply()
: m_u32Error( 0 )
, m_u32Res1( 0 )
{
	setPktType( PKT_TYPE_HOST_LIST_SEND_COMPLETE_REPLY );
	setPktLength( (uint16_t)sizeof( PktHostListSendCompleteReply ) );
	vx_assert( 0 == ( getPktLength() & 0x0f ) );
}

//============================================================================
PktHostListXferErr::PktHostListXferErr()
: m_u16Err(0xffff) 
, m_u16Res1(0)
, m_u32ResP1(0)
, m_u32ResP2(0)
, m_u32ResP3(0)
, m_u32Res1(0) 
, m_u32Res2(0)
{
	setPktType( PKT_TYPE_HOST_LIST_XFER_ERR );
	setPktLength( sizeof( PktHostListXferErr ) );
	vx_assert( 0 == ( getPktLength() & 0x0f ) );
}

//============================================================================
const char * PktHostListXferErr::describeError( void )
{
	switch( m_u16Err )
	{
	case PKT_REQ_STATUS_OK:
		return "200 Ok";
	case PKT_REQ_STATUS_CREATED:
		return "201 Created";
	case PKT_REQ_STATUS_ACCEPTED:
		return "202 Accepted";
	case PKT_REQ_ERR_NO_CONTENT:
		return "204 No Content";
	case PKT_REQ_ERR_MOVED_PERM:
		return "301 Moved Permanently";
	case PKT_REQ_ERR_MOVED_TEMP:
		return "301 Moved Temporarily";
	case PKT_REQ_ERR_NOT_MODIFIED:
		return "304 Not Modified";
	case PKT_REQ_ERR_BAD_REQUEST:
		return "400 Bad Request";
	case PKT_REQ_ERR_UNAUTHORIZED:
		return "401 Unauthorized";
	case PKT_REQ_ERR_FORBIDDEN:
		return "403 Forbidden";
	case PKT_REQ_ERR_NOT_FOUND:
		return "404 Not Found";
	case PKT_REQ_ERR_INTERNAL_SERVER_ERR:
		return "500 Internal Server Error";
	case PKT_REQ_ERR_NOT_IMPLEMENTED:
		return "501 Not Implemented";
	case PKT_REQ_ERR_BAD_GATEWAY:
		return "502 Bad Gateway";
	case PKT_REQ_ERR_SERVICE_UNAVAIL:
		return "503 Service Unavailable";
		//custom statuses
	case PKT_REQ_ERR_BANDWITH_LIMIT:
		return "600 Refused because of Bandwidth limit";
	case PKT_REQ_ERR_CONNECT_LIMIT:
		return "601 Refused because of Connection limit";
	case PKT_REQ_ERR_SERVICE_DISABLED:
		return "602	Refused because Service was disabled";
	case PKT_REQ_ERR_ALL_THREADS_BUSY:
		return "602	Refused because all threads are busy";
	default:
		return "Unknown Err";
	}
}


