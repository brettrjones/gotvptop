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

#include "AssetInfoDb.h"
#include "AssetMgr.h"
#include "AssetInfo.h"

//#include <time.h>

namespace
{
	std::string 		TABLE_ASSETS	 				= "tblAssets";

	std::string 		CREATE_COLUMNS_ASSETS			= " (unique_id TEXT PRIMARY KEY, creatorId TEXT, historyId TEXT, assetName TEXT, length BIGINT, type INTEGER, hashId BLOB, locFlags INTEGER, assetTag TEXT, creationTime BIGINT, sendState INTEGER) ";

	const int			COLUMN_ASSET_UNIQUE_ID			= 0;
	const int			COLUMN_ASSET_CREATOR_ID			= 1;
	const int			COLUMN_ASSET_HISTORY_ID			= 2;
	const int			COLUMN_ASSET_NAME				= 3;
	const int			COLUMN_ASSET_LEN				= 4;
	const int			COLUMN_ASSET_TYPE				= 5;
	const int			COLUMN_ASSET_HASH_ID			= 6;
	const int			COLUMN_LOCATION_FLAGS			= 7;
	const int			COLUMN_ASSET_TAG				= 8;
	const int			COLUMN_CREATION_TIME			= 9;
	const int			COLUMN_ASSET_SEND_STATE			= 10;
}

//============================================================================
AssetInfoDb::AssetInfoDb( AssetMgr& assetInfoMgr )
: DbBase( "AssetInfoDb" )
, m_AssetMgr( assetInfoMgr )
{
}

//============================================================================
AssetInfoDb::~AssetInfoDb()
{
}

//============================================================================
//! create tables in database 
RCODE AssetInfoDb::onCreateTables( int iDbVersion )
{
	lockAssetInfoDb();
	std::string strCmd = "CREATE TABLE " + TABLE_ASSETS + CREATE_COLUMNS_ASSETS;
	RCODE rc = sqlExec(strCmd);
	unlockAssetInfoDb();
	return rc;
}

//============================================================================
// delete tables in database
RCODE AssetInfoDb::onDeleteTables( int iOldVersion ) 
{
	lockAssetInfoDb();
	std::string strCmd = "DROP TABLE IF EXISTS " + TABLE_ASSETS;
	RCODE rc = sqlExec(strCmd);
	unlockAssetInfoDb();
	return rc;
}

//============================================================================
void AssetInfoDb::purgeAllAssets( void ) 
{
	lockAssetInfoDb();
	std::string strCmd = "DELETE FROM " + TABLE_ASSETS;
	RCODE rc = sqlExec( strCmd );
	unlockAssetInfoDb();
	if( rc )
	{
		LogMsg( LOG_ERROR, "AssetInfoDb::purgeAllAssets error %d\n", rc );
	}
	else
	{
		LogMsg( LOG_INFO, "AssetInfoDb::purgeAllAssets success\n" );
	}
}

//============================================================================
void AssetInfoDb::removeAsset( const char * assetName )
{
	DbBindList bindList( assetName );
	sqlExec( "DELETE FROM tblAssets WHERE assetName=?", bindList );
}

//============================================================================
void AssetInfoDb::removeAsset( VxGUID& assetId )
{
	std::string assetStr = assetId.toVxGUIDHexString();
	DbBindList bindList( assetStr.c_str() );
	sqlExec( "DELETE FROM tblAssets WHERE unique_id=?", bindList );
}

//============================================================================
void AssetInfoDb::removeAsset( AssetInfo * assetInfo )
{
	// the bind string is not copied so must be in memory until sql is executed
	//DbBindList bindList( assetInfo->getAssetUniqueId().toVxGUIDHexString().c_str() );
	std::string hexId = assetInfo->getAssetUniqueId().toVxGUIDHexString();
	DbBindList bindList( hexId.c_str() );
	sqlExec( "DELETE FROM tblAssets WHERE unique_id=?", bindList );
}

//============================================================================
void AssetInfoDb::addAsset( VxGUID&			assetId, 
							VxGUID&			creatorId, 
							VxGUID&			historyId, 
							const char *	assetName, 
							int64_t				assetLen, 
							uint32_t				assetType, 							
							VxSha1Hash&		hashId, 
							uint32_t				locationFlags, 
							const char *	assetTag, 
							time_t			creationTimeStamp,
                            EAssetSendState sendState )
{
	removeAsset( assetId );

	std::string assetIdStr		= assetId.toVxGUIDHexString();
	std::string creatorIdStr	= creatorId.toVxGUIDHexString();
	std::string historyIdStr	= historyId.toVxGUIDHexString();

	DbBindList bindList( assetIdStr.c_str() );
	bindList.add( creatorIdStr.c_str() );
	bindList.add( historyIdStr.c_str() );
	bindList.add( assetName );	 
	bindList.add( assetLen );
	bindList.add( (int)assetType );
	bindList.add( (void *)hashId.getHashData(), 20 );
	bindList.add( locationFlags );
	bindList.add( assetTag );
	bindList.add( (uint64_t)creationTimeStamp );
	bindList.add( (int)sendState );

	RCODE rc  = sqlExec( "INSERT INTO tblAssets (unique_id,creatorId,historyId,assetName,length,type,hashId,locFlags,assetTag,creationTime,sendState) values(?,?,?,?,?,?,?,?,?,?,?)",
		bindList );
	if( rc )
	{
		LogMsg( LOG_ERROR, "AssetInfoDb::addAsset error %d\n", rc );
	}
}

//============================================================================
void AssetInfoDb::updateAssetSendState( VxGUID& assetId, EAssetSendState sendState )
{
	std::string assetIdStr		= assetId.toVxGUIDHexString();
	DbBindList bindList(  (int)sendState );
	bindList.add( assetIdStr.c_str() );
	RCODE rc  = sqlExec( "UPDATE tblAssets SET sendState=? WHERE unique_id=?",
		bindList );
	if( rc )
	{
		LogMsg( LOG_ERROR, "AssetInfoDb::addAsset error %d\n", rc );
	}
}

//============================================================================
void AssetInfoDb::addAsset( AssetInfo* assetInfo )
{
	addAsset(	assetInfo->getAssetUniqueId(),
				assetInfo->getCreatorId(),
				assetInfo->getHistoryId(),
				assetInfo->getAssetName().c_str(),
				assetInfo->getAssetLength(),
				(uint32_t)assetInfo->getAssetType(),				
				assetInfo->getAssetHashId(),
				assetInfo->getLocationFlags(),
				assetInfo->getAssetTag().length() ? assetInfo->getAssetTag().c_str() : "",
				assetInfo->getCreationTime(),
				assetInfo->getAssetSendState() );
}

//============================================================================
void AssetInfoDb::getAllAssets( std::vector<AssetInfo*>& AssetAssetList )
{
	std::string assetName;
	uint16_t assetType;
	uint64_t assetLen;
	std::string destasset;
	std::string consoleId;
	lockAssetInfoDb();
	DbCursor * cursor = startQuery( "SELECT * FROM tblAssets" ); // ORDER BY unique_id DESC  // BRJ don't know why ORDER BY quit working on android.. do in code
	if( NULL != cursor )
	{
		while( cursor->getNextRow() )
		{
			assetName = cursor->getString( COLUMN_ASSET_NAME );
			assetLen =  (uint64_t)cursor->getS64( COLUMN_ASSET_LEN );
			assetType = (uint16_t)cursor->getS32( COLUMN_ASSET_TYPE );

			AssetInfo * assetInfo = new AssetInfo( assetName, assetLen, assetType );
			assetInfo->setAssetUniqueId( cursor->getString( COLUMN_ASSET_UNIQUE_ID ) );
			assetInfo->setCreatorId( cursor->getString( COLUMN_ASSET_CREATOR_ID ) );
			assetInfo->setHistoryId( cursor->getString( COLUMN_ASSET_HISTORY_ID ) );
			assetInfo->setAssetHashId( (uint8_t *)cursor->getBlob( COLUMN_ASSET_HASH_ID ) );
			assetInfo->setLocationFlags( cursor->getS32( COLUMN_LOCATION_FLAGS ) );
			assetInfo->setAssetTag( cursor->getString( COLUMN_ASSET_TAG ) );
			assetInfo->setCreationTime(  (time_t)cursor->getS64( COLUMN_CREATION_TIME ) );
			assetInfo->setAssetSendState( ( EAssetSendState )cursor->getS32( COLUMN_ASSET_SEND_STATE ) );
			
			insertAssetInTimeOrder( assetInfo, AssetAssetList );
		}

		cursor->close();
	}

	unlockAssetInfoDb();
} 

//============================================================================
void AssetInfoDb::insertAssetInTimeOrder( AssetInfo *assetInfo, std::vector<AssetInfo*>& assetList )
{
	std::vector<AssetInfo*>::iterator iter;
	for( iter = assetList.begin(); iter != assetList.end(); ++iter )
	{
		if( (*iter)->getCreationTime() > assetInfo->getCreationTime() )
		{
			assetList.insert( iter, assetInfo );
			return;
		}
	}

	assetList.push_back( assetInfo );
}

