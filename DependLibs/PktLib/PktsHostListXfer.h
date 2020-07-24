#pragma once
//============================================================================
// Copyright (C) 2010 Brett R. Jones 
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

#include "VxCommon.h"
#include "VxPktHdr.h"
#include "PktRequestErrors.h"

#include <CoreLib/IsBigEndianCpu.h>
#include <CoreLib/VxSha1Hash.h>

#define PKT_TYPE_HOST_LIST_MAX_DATA_LEN		14320	// maximum length of chunk of HostList data
#define PKT_TYPE_HOST_LIST_MAX_NAME_AND_TAG_LEN		( 4096 * 2 + 48 )	// maximum length of chunk of HostList data

#define MAX_HOST_LIST_LIST_LEN				4096	// maximum length of list of HostLists


#pragma pack(push) 
#pragma pack(1)

//============================================================================
// HostList Offer Packets
//============================================================================
enum EHostListXferCmd
{
	eHostListXferCmdHostListSend		    = 0,
	eHostListXferCmdHostListGet			= 1,
	eHostListXferCmdHostListChecksum	    = 2,
	eHostListXferCmdHostListDirectory	    = 3
};

enum EHostListXferOption
{
	eHostListXferOptionReplaceIfExists 	= 0,
	eHostListXferOptionResumeIfExists	    = 1,
	eHostListXferOptionFailIfExists		= 2
};

class HostListInfo;

class PktHostListSendReq : public VxPktHdr
{
public:
	PktHostListSendReq();
	void						setHostListNameAndTag( const char * pHostListName, const char * assetTag = 0 );
	void						setHostListNameLen( uint16_t nameLen )				{ m_HostListNameLen = htons( nameLen ); }
	uint16_t					getHostListNameLen( void )							{ return ntohs( m_HostListNameLen ); }
	void						setHostListTagLen( uint16_t tagLen )				{ m_HostListTagLen = htons( tagLen ); }
	uint16_t					getHostListTagLen( void )							{ return ntohs( m_HostListTagLen ); }

	std::string					getHostListName();
	std::string					getHostListTag();
	void						setHostListHashId( VxSha1Hash& HostListHashId )		{ m_HostListHashId = HostListHashId; }
	VxSha1Hash&					getHostListHashId( void )							{ return m_HostListHashId; }

	void						setLclSessionId( VxGUID& lclId )				{ m_LclSessionId = lclId; }
	VxGUID&						getLclSessionId( void )							{ return m_LclSessionId; }
	void						setRmtSessionId( VxGUID& rmtId )				{ m_RmtSessionId = rmtId; }
	VxGUID&						getRmtSessionId( void )							{ return m_RmtSessionId; }

	void						setUniqueId( VxGUID& uniqueId )					{ m_UniqueId = uniqueId; }
	VxGUID&						getUniqueId( void )								{ return m_UniqueId; }
	void						setCreatorId( VxGUID& creatorId )				{ m_CreatorId = creatorId; }
	VxGUID&						getCreatorId( void )							{ return m_CreatorId; }
	void						setHistoryId( VxGUID& historyId )				{ m_HistoryId = historyId; }
	VxGUID&						getHistoryId( void )							{ return m_HistoryId; }

    void						setCreationTime( uint32_t createTime )			{ m_CreationTime = htonl( createTime ); }
	uint32_t					getCreationTime( void )						    { return ntohl( m_CreationTime ); }

	void						setHostListOffset( int64_t offset )				{ m_s64HostListOffs = htonU64( offset ); }
	int64_t						getHostListOffset( void )						{ return ntohU64( m_s64HostListOffs ); }
	void						setHostListLen( int64_t len )					{ m_s64HostListLen = htonU64( len ); }
	int64_t						getHostListLen( void )							{ return ntohU64( m_s64HostListLen ); }

	void						setHostListType( uint16_t HostListType )		{ m_HostListType = htons( HostListType ); }
	uint16_t					getHostListType( void )							{ return ntohs( m_HostListType ); }

	void						setError( uint32_t error )						{ m_u32Error = htonl( error ); }
	uint32_t					getError( void )								{ return ntohl( m_u32Error ); }

	void						fillPktFromHostList( HostListInfo& assetInfo );
	void						fillHostListFromPkt( HostListInfo& assetInfo );

private:
	uint16_t					m_HostListType;
	VxGUID						m_UniqueId;
	VxGUID						m_CreatorId;
	VxGUID						m_HistoryId; 
	VxGUID						m_LclSessionId;
	VxGUID						m_RmtSessionId;
	VxSha1Hash					m_HostListHashId;
	uint32_t					m_u32Error; 
	int64_t						m_s64HostListLen;
	int64_t						m_s64HostListOffs;
	uint32_t					m_CreationTime;
	uint16_t					m_HostListNameLen;
	uint16_t					m_HostListTagLen;

	uint32_t					m_u32Res1; 
	uint32_t					m_u32Res2; 
	uint32_t					m_u32Res3; 
	uint32_t					m_u32Res4; 
	char						m_HostListNameAndTag[ PKT_TYPE_HOST_LIST_MAX_NAME_AND_TAG_LEN ];
};

class PktHostListSendReply : public VxPktHdr
{
public:
	PktHostListSendReply();

	void						setUniqueId( VxGUID& uniqueId )					{ m_UniqueId = uniqueId; }
	VxGUID&						getUniqueId( void )								{ return m_UniqueId; }

	void						setLclSessionId( VxGUID& lclId )				{ m_LclSessionId = lclId; }
	VxGUID&						getLclSessionId( void )							{ return m_LclSessionId; }
	void						setRmtSessionId( VxGUID& rmtId )				{ m_RmtSessionId = rmtId; }
	VxGUID&						getRmtSessionId( void )							{ return m_RmtSessionId; }

	void						setHostListOffset( int64_t offset )				{ m_s64HostListOffs = htonU64( offset ); }
	int64_t						getHostListOffset( void )						{ return ntohU64( m_s64HostListOffs ); }

	void						setError( uint32_t error )						{ m_u32Error = htonl( error ); }
	uint32_t					getError( void )								{ return ntohl( m_u32Error ); }

	void						setRequiresFileXfer( bool requiresXfer )		{ m_u8RequiresFileXfer = (uint8_t)requiresXfer; }
	bool						getRequiresFileXfer( void )						{ return m_u8RequiresFileXfer ? true : false; }

private:
	uint8_t						m_u8RequiresFileXfer;
	uint8_t						m_u8Res;
	uint16_t					m_u16Res; 
	int64_t						m_s64HostListOffs;
	VxGUID						m_UniqueId;
	VxGUID						m_LclSessionId;
	VxGUID						m_RmtSessionId;
	uint32_t					m_u32Error; 
	uint32_t					m_u32Res1;
	uint32_t					m_u32Res2; 
};

//============================================================================
// HostList chunk packets
//============================================================================
class PktHostListChunkReq : public VxPktHdr
{
public:
	PktHostListChunkReq();
	uint16_t					emptyLength( void );
	void						setChunkLen( uint16_t u16ChunkLen ); // also calculates packet length
	uint16_t					getChunkLen( void );

	void						setLclSessionId( VxGUID& lclId )				{ m_LclSessionId = lclId; }
	VxGUID&						getLclSessionId( void )							{ return m_LclSessionId; }
	void						setRmtSessionId( VxGUID& rmtId )				{ m_RmtSessionId = rmtId; }
	VxGUID&						getRmtSessionId( void )							{ return m_RmtSessionId; }

	void						setDataLen( uint16_t len )						{ m_u16HostListChunkLen = htons( len ); }
	uint16_t					getDataLen( void )								{ return ntohs( m_u16HostListChunkLen ); }

	void						setError( uint32_t error )						{ m_u32Error = htonl( error ); }
	uint32_t					getError( void )								{ return ntohl( m_u32Error ); }

private:
	uint16_t					m_u16Res;
	uint16_t					m_u16HostListChunkLen;
	VxGUID						m_LclSessionId;
	VxGUID						m_RmtSessionId;
	uint32_t					m_u32Error; 
	uint32_t					m_u32Res1; 
public:
	uint8_t						m_au8HostListChunk[ PKT_TYPE_HOST_LIST_MAX_DATA_LEN ];
};

class PktHostListChunkReply : public VxPktHdr
{
public:
	PktHostListChunkReply();

	void						setLclSessionId( VxGUID& lclId )				{ m_LclSessionId = lclId; }
	VxGUID&						getLclSessionId( void )							{ return m_LclSessionId; }
	void						setRmtSessionId( VxGUID& rmtId )				{ m_RmtSessionId = rmtId; }
	VxGUID&						getRmtSessionId( void )							{ return m_RmtSessionId; }

	void						setDataLen( uint16_t len )						{ m_u16HostListChunkLen = htons( len ); }
	uint16_t					getDataLen( void )								{ return ntohs( m_u16HostListChunkLen ); }

	void						setError( uint32_t error )						{ m_u32Error = htonl( error ); }
	uint32_t					getError( void )								{ return ntohl( m_u32Error ); }

private:
	uint16_t					m_u16Res;	
	uint16_t					m_u16HostListChunkLen;
	VxGUID						m_LclSessionId;
	VxGUID						m_RmtSessionId;
	uint32_t					m_u32Error; 
};

//============================================================================
// PktHostListSendComplete
//============================================================================
class PktHostListSendCompleteReq : public VxPktHdr
{
public:
	PktHostListSendCompleteReq();

	void						setLclSessionId( VxGUID& lclId )			{ m_LclSessionId = lclId; }
	VxGUID&						getLclSessionId( void )						{ return m_LclSessionId; }
	void						setRmtSessionId( VxGUID& rmtId )			{ m_RmtSessionId = rmtId; }
	VxGUID&						getRmtSessionId( void )						{ return m_RmtSessionId; }

	void						setHostListUniqueId( VxGUID& uniqueId  )		{ m_HostListUniqueId = uniqueId; }
	VxGUID&						getHostListHashId( void )						{ return m_HostListUniqueId; }

	void						setError( uint32_t error )					{ m_u32Error = htonl( error ); }
	uint32_t					getError( void )							{ return ntohl( m_u32Error ); }

private:
	VxGUID						m_LclSessionId;
	VxGUID						m_RmtSessionId;
	VxGUID						m_HostListUniqueId;
	uint32_t					m_u32Error; 
	uint32_t					m_u32Res1; 
};

class PktHostListSendCompleteReply : public VxPktHdr
{
public:
	PktHostListSendCompleteReply();

	void						setLclSessionId( VxGUID& lclId )			{ m_LclSessionId = lclId; }
	VxGUID&						getLclSessionId( void )						{ return m_LclSessionId; }
	void						setRmtSessionId( VxGUID& rmtId )			{ m_RmtSessionId = rmtId; }
	VxGUID&						getRmtSessionId( void )						{ return m_RmtSessionId; }

	void						setHostListUniqueId( VxGUID& uniqueId  )	{ m_HostListUniqueId = uniqueId; }
	VxGUID&						getHostListUniqueId( void )					{ return m_HostListUniqueId; }

	void						setError( uint32_t error )					{ m_u32Error = htonl( error ); }
	uint32_t					getError( void )							{ return ntohl( m_u32Error ); }

private:
	VxGUID						m_LclSessionId;
	VxGUID						m_RmtSessionId;
	VxGUID						m_HostListUniqueId;
	uint32_t					m_u32Error; 
	uint32_t					m_u32Res1; 
};

//============================================================================
// PktHostListXferErr
//============================================================================
class PktHostListXferErr : public VxPktHdr
{
public:
	PktHostListXferErr();

	const char *				describeError();

	void						setRxInstance( VxGUID& instanceGuid )			{ m_RxHostListInstance = instanceGuid; }
	VxGUID& 					getRxInstance( void )							{ return m_RxHostListInstance; }
	void						setTxInstance( VxGUID& instanceGuid )			{ m_TxHostListInstance = instanceGuid; }
	VxGUID&						getTxInstance( void )							{ return m_TxHostListInstance; }

	void						setError( uint16_t error )						{ m_u16Err = htons( error ); }
	uint16_t					getError( void )								{ return ntohs( m_u16Err ); }

private:
	uint16_t					m_u16Err;
	uint16_t					m_u16Res1;
	uint32_t					m_u32ResP1;
	uint32_t					m_u32ResP2;
	uint32_t					m_u32ResP3;

	VxGUID						m_RxHostListInstance; 
	VxGUID						m_TxHostListInstance; 
	uint32_t					m_u32Res1; 
	uint32_t					m_u32Res2;
};

#pragma pack(pop)

