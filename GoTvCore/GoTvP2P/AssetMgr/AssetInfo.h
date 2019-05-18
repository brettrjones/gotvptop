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
// http://www.gotvptop.net
//============================================================================

#include <config_gotvcore.h>

#include <CoreLib/AssetDefs.h>
#include <CoreLib/VxSha1Hash.h>
#include <CoreLib/VxGUID.h>

#include <string>

#define ASSET_LOC_FLAG_PERSONAL_RECORD			0x0001
#define ASSET_LOC_FLAG_LIBRARY					0x0002
#define ASSET_LOC_FLAG_SHARED_FILE				0x0004

class VxThread;

class AssetInfo 
{
public:
	AssetInfo();
	AssetInfo( const AssetInfo& rhs );
	AssetInfo( const std::string& fileName );
	AssetInfo( const std::string& fileName, uint64_t assetLen, uint16_t assetType );
    AssetInfo( const char * fileName, uint64_t fileLen, uint8_t fileType );

	AssetInfo&					operator=( const AssetInfo& rhs ); 

	bool						isValid( void );
	bool						isMine( void );

	bool						isDirectory( void );
	bool						isUnknownAsset( void )						{ return ( 0 == m_u16AssetType) ? true : false; }
	bool						isChatTextAsset( void )						{ return (eAssetTypeChatText & m_u16AssetType) ? true : false; }
	bool						isChatFaceAsset( void )						{ return ( ( eAssetTypeChatFace ) & m_u16AssetType ) ? true : false; }
	bool						isChatAvatarAsset( void )					{ return ( ( eAssetTypeChatStockAvatar | eAssetTypeChatCustomAvatar ) & m_u16AssetType ) ? true : false; }
	bool						isPhotoAsset( void )						{ return (eAssetTypePhoto & m_u16AssetType) ? true : false; }
	bool						isAudioAsset( void )						{ return (eAssetTypeAudio & m_u16AssetType) ? true : false; }
	bool						isVideoAsset( void )						{ return (eAssetTypeVideo & m_u16AssetType) ? true : false; }
	bool						getIsFileAsset( void );
	bool						hasFileName( void );

	void						setIsPersonalRecord( bool isRecord )		{ if(isRecord) m_LocationFlags|=ASSET_LOC_FLAG_PERSONAL_RECORD;else m_LocationFlags&=~ASSET_LOC_FLAG_PERSONAL_RECORD; }
	bool						getIsPersonalRecord( void )					{ return m_LocationFlags&ASSET_LOC_FLAG_PERSONAL_RECORD?true:false; }
	void						setIsInLibary( bool isInLibrary )			{ if(isInLibrary) m_LocationFlags|=ASSET_LOC_FLAG_LIBRARY;else m_LocationFlags&=~ASSET_LOC_FLAG_LIBRARY; }
	bool						getIsInLibary( void )						{ return m_LocationFlags&ASSET_LOC_FLAG_LIBRARY?true:false; }
	void						setIsSharedFileAsset( bool isSharedAsset )	{ if(isSharedAsset) m_LocationFlags|=ASSET_LOC_FLAG_SHARED_FILE;else m_LocationFlags&=~ASSET_LOC_FLAG_SHARED_FILE; }
	bool						getIsSharedFileAsset( void )				{ return m_LocationFlags&ASSET_LOC_FLAG_SHARED_FILE?true:false; }

	void						setAssetName( const char * assetName );
	void						setAssetName( std::string& assetName )		{ m_AssetName = assetName; }
	std::string&				getAssetName( void )						{ return m_AssetName; }
	std::string					getRemoteAssetName( void );

	void						setAssetTag( const char * assetTag );
	std::string&				getAssetTag( void )							{ return m_AssetTag; }

	void						setAssetType( EAssetType assetType )		{ m_u16AssetType = (uint16_t)assetType; }
	EAssetType					getAssetType( void )						{ return (EAssetType)m_u16AssetType; }

	void						setAssetLength( int64_t assetLength )		{ m_s64AssetLen = assetLength; }
	int64_t						getAssetLength( void )						{ return m_s64AssetLen; }

	void						setAssetHashId( VxSha1Hash& id )			{ m_AssetHash = id; }
	void						setAssetHashId( uint8_t * id )				{ m_AssetHash.setHashData( id ); }
	VxSha1Hash&					getAssetHashId( void )						{ return m_AssetHash; }

	void						setAssetUniqueId( VxGUID& uniqueId )		{ m_UniqueId = uniqueId; }
	void						setAssetUniqueId( const char * guid )		{ m_UniqueId.fromVxGUIDHexString( guid ); }
	VxGUID&						getAssetUniqueId( void )					{ return m_UniqueId; }
	VxGUID&						generateNewUniqueId( void ); // generates unique id, assigns it to asset and returns reference to it

	void						setCreatorId( VxGUID& creatorId )			{ m_CreatorId = creatorId; }
	void						setCreatorId( const char * creatorId )		{ m_CreatorId.fromVxGUIDHexString( creatorId ); }
	VxGUID&						getCreatorId( void )						{ return m_CreatorId; }

	void						setHistoryId( VxGUID& historyId )			{ m_HistoryId = historyId; }
	void						setHistoryId( const char * historyId )		{ m_HistoryId.fromVxGUIDHexString( historyId ); }
	VxGUID&						getHistoryId( void )						{ return m_HistoryId; }

	void						setLocationFlags( uint32_t locFlags )		{ m_LocationFlags = locFlags; }
	uint32_t					getLocationFlags( void )					{ return m_LocationFlags; }

	void						setAssetSendState( EAssetSendState sendState )	{ m_AssetSendState = sendState; }
	EAssetSendState				getAssetSendState( void )					{ return m_AssetSendState; }
	
	void						setCreationTime( time_t timestamp )			{ m_CreationTime = timestamp; }
	time_t						getCreationTime( void )						{ return m_CreationTime; }

    void						setPlayPosition( int pos0to100000 )         { m_PlayPosition0to100000 = pos0to100000; }
    int						    getPlayPosition( void )                     { return m_PlayPosition0to100000; }

	static const char *			getDefaultFileExtension( EAssetType assetType );
	static const char *			getSubDirectoryName( EAssetType assetType );
	void						updateAssetInfo( VxThread * callingThread );
	bool						needsHashGenerated( void );

private:
	void						determineAssetDir( void );

public:
	//=== vars ===//
	std::string					m_AssetName; // usually file name
	std::string					m_AssetTag;
	VxGUID						m_UniqueId;
	VxGUID						m_CreatorId;
	VxGUID						m_HistoryId; 
	VxSha1Hash					m_AssetHash;
	int64_t						m_s64AssetLen;
	uint16_t					m_u16AssetType;
	uint32_t					m_LocationFlags;
	EAssetSendState				m_AssetSendState;
	time_t						m_CreationTime;
    int						    m_PlayPosition0to100000;
};
