#pragma once
//============================================================================
// Copyright (C) 2015 Brett R. Jones 
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

#include <config_gotvcore.h>

#include <CoreLib/HostListDefs.h>
#include <CoreLib/VxSha1Hash.h>
#include <CoreLib/VxGUID.h>

#include <string>

#define ASSET_LOC_FLAG_PERSONAL_RECORD			0x0001
#define ASSET_LOC_FLAG_LIBRARY					0x0002
#define ASSET_LOC_FLAG_SHARED_FILE				0x0004

class VxThread;

class HostListInfo 
{
public:
	HostListInfo();
	HostListInfo( const HostListInfo& rhs );
	HostListInfo( const std::string& fileName );
    HostListInfo( const char * fileName, uint64_t fileLen, uint16_t assetType );

	HostListInfo&					operator=( const HostListInfo& rhs ); 

	bool						isValid( void );
	bool						isMine( void );

	bool						isDirectory( void );
	bool						isUnknownHostList( void )						{ return ( 0 == m_u16HostListType) ? true : false; }
	bool						isChatTextHostList( void )						{ return ( eHostListTypeChatText & m_u16HostListType) ? true : false; }
	bool						isChatFaceHostList( void )						{ return ( ( eHostListTypeChatFace ) & m_u16HostListType ) ? true : false; }
	bool						isChatAvatarHostList( void )					{ return ( ( eHostListTypeChatStockAvatar | eHostListTypeChatCustomAvatar ) & m_u16HostListType ) ? true : false; }
	bool						isPhotoHostList( void )						{ return ( eHostListTypePhoto & m_u16HostListType ) ? true : false; }
    bool						isThumbHostList( void )						{ return ( eHostListTypeThumbnail & m_u16HostListType ) ? true : false; }
	bool						isAudioHostList( void )						{ return ( eHostListTypeAudio & m_u16HostListType ) ? true : false; }
	bool						isVideoHostList( void )						{ return ( eHostListTypeVideo & m_u16HostListType ) ? true : false; }
	bool						getIsFileHostList( void );
	bool						hasFileName( void );

	void						setIsPersonalRecord( bool isRecord )		{ if(isRecord) m_LocationFlags|=ASSET_LOC_FLAG_PERSONAL_RECORD;else m_LocationFlags&=~ASSET_LOC_FLAG_PERSONAL_RECORD; }
	bool						getIsPersonalRecord( void )					{ return m_LocationFlags&ASSET_LOC_FLAG_PERSONAL_RECORD?true:false; }
	void						setIsInLibary( bool isInLibrary )			{ if(isInLibrary) m_LocationFlags|=ASSET_LOC_FLAG_LIBRARY;else m_LocationFlags&=~ASSET_LOC_FLAG_LIBRARY; }
	bool						getIsInLibary( void )						{ return m_LocationFlags&ASSET_LOC_FLAG_LIBRARY?true:false; }
	void						setIsSharedFileHostList( bool isSharedHostList )	{ if(isSharedHostList) m_LocationFlags|=ASSET_LOC_FLAG_SHARED_FILE;else m_LocationFlags&=~ASSET_LOC_FLAG_SHARED_FILE; }
	bool						getIsSharedFileHostList( void )				{ return m_LocationFlags&ASSET_LOC_FLAG_SHARED_FILE?true:false; }

	void						setHostListName( const char * assetName );
	void						setHostListName( std::string& assetName )		{ m_HostListName = assetName; }
	std::string&				getHostListName( void )						{ return m_HostListName; }
	std::string					getRemoteHostListName( void );

	void						setHostListTag( const char * assetTag );
	std::string&				getHostListTag( void )							{ return m_HostListTag; }

	void						setHostListType( EHostListType assetType )		{ m_u16HostListType = (uint16_t)assetType; }
	EHostListType					getHostListType( void )						{ return (EHostListType)m_u16HostListType; }

	void						setHostListLength( int64_t assetLength )		{ m_s64HostListLen = assetLength; }
	int64_t						getHostListLength( void )						{ return m_s64HostListLen; }

	void						setHostListHashId( VxSha1Hash& id )			{ m_HostListHash = id; }
	void						setHostListHashId( uint8_t * id )				{ m_HostListHash.setHashData( id ); }
	VxSha1Hash&					getHostListHashId( void )						{ return m_HostListHash; }

	void						setHostListUniqueId( VxGUID& uniqueId )		{ m_UniqueId = uniqueId; }
	void						setHostListUniqueId( const char * guid )		{ m_UniqueId.fromVxGUIDHexString( guid ); }
	VxGUID&						getHostListUniqueId( void )					{ return m_UniqueId; }
	VxGUID&						generateNewUniqueId( void ); // generates unique id, assigns it to asset and returns reference to it

	void						setCreatorId( VxGUID& creatorId )			{ m_CreatorId = creatorId; }
	void						setCreatorId( const char * creatorId )		{ m_CreatorId.fromVxGUIDHexString( creatorId ); }
	VxGUID&						getCreatorId( void )						{ return m_CreatorId; }

	void						setHistoryId( VxGUID& historyId )			{ m_HistoryId = historyId; }
	void						setHistoryId( const char * historyId )		{ m_HistoryId.fromVxGUIDHexString( historyId ); }
	VxGUID&						getHistoryId( void )						{ return m_HistoryId; }

	void						setLocationFlags( uint32_t locFlags )		{ m_LocationFlags = locFlags; }
	uint32_t					getLocationFlags( void )					{ return m_LocationFlags; }

	void						setHostListSendState( EHostListSendState sendState )	{ m_HostListSendState = sendState; }
	EHostListSendState				getHostListSendState( void )					{ return m_HostListSendState; }
	
	void						setCreationTime( time_t timestamp )			{ m_CreationTime = timestamp; }
	time_t						getCreationTime( void )						{ return m_CreationTime; }

    void						setPlayPosition( int pos0to100000 )         { m_PlayPosition0to100000 = pos0to100000; }
    int						    getPlayPosition( void )                     { return m_PlayPosition0to100000; }

	static const char *			getDefaultFileExtension( EHostListType assetType );
	static const char *			getSubDirectoryName( EHostListType assetType );
	void						updateHostListInfo( VxThread * callingThread );
	bool						needsHashGenerated( void );

private:
	void						determineHostListDir( void );

public:
	//=== vars ===//
	std::string					m_HostListName; // usually file name
	std::string					m_HostListTag;
	VxGUID						m_UniqueId;
	VxGUID						m_CreatorId;
	VxGUID						m_HistoryId; 
	VxSha1Hash					m_HostListHash;
	int64_t						m_s64HostListLen;
	uint16_t					m_u16HostListType;
	uint32_t					m_LocationFlags;
	EHostListSendState				m_HostListSendState;
	time_t						m_CreationTime;
    int						    m_PlayPosition0to100000;
};
