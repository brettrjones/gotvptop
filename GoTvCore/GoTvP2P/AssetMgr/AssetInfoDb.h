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

#include <CoreLib/DbBase.h>
#include <CoreLib/VxGUID.h>
#include <CoreLib/AssetDefs.h>

class AssetInfo;
class AssetMgr;
class VxGUID;
class VxSha1Hash;

class AssetInfoDb : public DbBase
{
public:
	AssetInfoDb( AssetMgr& mgr );
	virtual ~AssetInfoDb();

	void						lockAssetInfoDb( void )					{ m_AssetInfoDbMutex.lock(); }
	void						unlockAssetInfoDb( void )				{ m_AssetInfoDbMutex.unlock(); }

	void						addAsset(	VxGUID&			assetId, 
											VxGUID&			creatorId, 
											VxGUID&			historyId, 
											const char *	assetName, 
											int64_t			assetLen, 
											uint32_t		assetType, 							
											VxSha1Hash&		hashId, 
											uint32_t		locationFlags, 
											const char *	assetTag = "", 
											time_t			timestamp = 0,
											EAssetSendState sendState = eAssetSendStateNone );

	void 						addAsset( AssetInfo * assetInfo );
	void						removeAsset( const char * assetName );
	void						removeAsset( VxGUID& assetId );
	void						removeAsset( AssetInfo * assetInfo );

	void						getAllAssets( std::vector<AssetInfo*>& AssetAssetList );
	void						purgeAllAssets( void ); 
	void						updateAssetTypes( void );
	void						updateAssetSendState( VxGUID& assetId, EAssetSendState sendState );

protected:
	virtual RCODE				onCreateTables( int iDbVersion );
	virtual RCODE				onDeleteTables( int iOldVersion );
	void						insertAssetInTimeOrder( AssetInfo *assetInfo, std::vector<AssetInfo*>& assetList );

	AssetMgr&					m_AssetMgr;
	VxMutex						m_AssetInfoDbMutex;
};

