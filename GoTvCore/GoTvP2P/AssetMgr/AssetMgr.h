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
// http://www.gotvptop.com
//============================================================================

#include <config_gotvcore.h>

#include "AssetMgrBase.h"

#include <CoreLib/VxThread.h>
#include <CoreLib/VxSemaphore.h>
#include <CoreLib/VxMutex.h>

class PktFileListReply;

class AssetInfo;
class AssetInfoDb;
class AssetHistoryMgr;

class AssetMgr : public AssetMgrBase
{
public:
	AssetMgr( P2PEngine& engine );
	virtual ~AssetMgr();

	bool						isAssetListInitialized( void )				{ return m_AssetListInitialized; }
	// startup when user specific directory has been set after user logs on
	void						fromGuiUserLoggedOn( void );
	void						assetInfoMgrStartup( VxThread * startupThread );
	void						assetInfoMgrShutdown( void );

	virtual bool				fromGuiGetAssetInfo( uint8_t fileTypeFilter );
	virtual bool				fromGuiSetFileIsShared( std::string fileName, bool shareFile, uint8_t * fileHashId );

	bool						isSharedFileAsset( std::string& fileName );
	bool						isSharedFileAsset( VxSha1Hash& fileHashId );
	bool						getFileHashId( std::string& fileFullName, VxSha1Hash& retFileHashId );
	bool						getFileFullName( VxSha1Hash& fileHashId, std::string& retFileFullName );


	std::vector<AssetInfo*>&	getAssetInfoList( void )				{ return m_AssetInfoList; }
	AssetInfo *					findAsset( std::string& fileName );
	AssetInfo *					findAsset( VxSha1Hash& fileHashId );
	AssetInfo *					findAsset( VxGUID& assetId );

	uint16_t					getAssetFileTypes( void )				{ return m_u16AssetFileTypes; }
	void						updateAssetFileTypes( void );

	void						lockFileListPackets( void )				{ m_FileListPacketsMutex.lock(); }
	void						unlockFileListPackets( void )			{ m_FileListPacketsMutex.unlock(); }
	std::vector<PktFileListReply*>&	getFileListPackets( void )			{ return m_FileListPackets; }
	void						updateFileListPackets( void );

	void						fileWasShredded( const char * fileName );

    AssetInfo * 				addAssetFile( const char * fileName, uint64_t fileLen, uint8_t fileType );

	bool						addAssetFile(	const char *	fileName, 
												VxGUID&			assetId,  
												uint8_t *		hashId = 0, 
												EAssetLocation	locationFlags = eAssetLocUnknown, 
												const char *	assetTag = "", 
												time_t			timestamp = 0 );

	bool						addAssetFile(	const char *	fileName, 
												VxGUID&			assetId,  
												VxGUID&		    creatorId, 
												VxGUID&		    historyId, 
												uint8_t *		hashId = 0, 
												EAssetLocation	locationFlags = eAssetLocUnknown, 
												const char *	assetTag = "", 
												time_t			timestamp = 0 );

	bool						addAsset( AssetInfo& assetInfo );
	bool						removeAsset( std::string fileName );
	bool						removeAsset( VxGUID& assetUniqueId );
	void						queryHistoryAssets( VxGUID& historyId );

	void						generateHashForFile( std::string fileName );
	void						updateAssetXferState( VxGUID& assetUniqueId, EAssetSendState assetSendState, int param = 0 );
	void						announceAssetXferState( VxGUID& assetUniqueId, EAssetSendState assetSendState, int param );

protected:
	void						updateAssetListFromDb( VxThread * thread );
	void						generateHashIds( VxThread * thread );
	void						clearAssetFileListPackets( void );
	void						clearAssetInfoList( void );
    AssetInfo *                 createAssetInfo( const char * fileName, uint64_t fileLen, uint8_t fileType );
	AssetInfo *					createAssetInfo(	const char *	fileName, 
													VxGUID&			assetId,  
													uint8_t *		hashId, 
													EAssetLocation	locationFlags = eAssetLocUnknown, 
													const char *	assetTag = "", 
													time_t			timestamp = 0 );
	bool						insertNewInfo( AssetInfo * assetInfo );
	void						updateDatabase( AssetInfo * assetInfo );
	void						updateAssetDatabaseSendState( VxGUID& assetUniqueId, EAssetSendState sendState );
	void						announceAssetAdded( AssetInfo * assetInfo );
	void						announceAssetRemoved( AssetInfo * assetInfo );
	void						insertAssetInTimeOrder( AssetInfo * assetInfo );

	//=== vars ===//
	bool						m_Initialized;
	bool						m_AssetListInitialized;
	AssetInfoDb&				m_AssetInfoDb;
	std::vector<AssetInfo*>		m_AssetInfoList;

	std::vector<AssetInfo*>		m_WaitingForHastList;
	std::vector<std::string>	m_GenHashList;
	VxMutex						m_GenHashMutex;
	VxThread					m_GenHashThread;
	VxSemaphore					m_GenHashSemaphore;

	uint16_t							m_u16AssetFileTypes;
	VxMutex						m_FileListPacketsMutex;
	std::vector<PktFileListReply*>m_FileListPackets;
};

