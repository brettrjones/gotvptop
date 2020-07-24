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

#include "HostListInfoDb.h"
#include "HostListMgr.h"
#include "HostListInfo.h"

//#include <time.h>

namespace
{
	std::string 		TABLE_ASSETS	 				= "tblHostLists";

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
HostListInfoDb::HostListInfoDb( HostListMgr& assetInfoMgr )
: DbBase( "HostListInfoDb" )
, m_HostListMgr( assetInfoMgr )
{
}

//============================================================================
HostListInfoDb::~HostListInfoDb()
{
}

//============================================================================
//! create tables in database 
RCODE HostListInfoDb::onCreateTables( int iDbVersion )
{
	lockHostListInfoDb();
	std::string strCmd = "CREATE TABLE " + TABLE_ASSETS + CREATE_COLUMNS_ASSETS;
	RCODE rc = sqlExec(strCmd);
	unlockHostListInfoDb();
	return rc;
}

//============================================================================
// delete tables in database
RCODE HostListInfoDb::onDeleteTables( int iOldVersion ) 
{
	lockHostListInfoDb();
	std::string strCmd = "DROP TABLE IF EXISTS " + TABLE_ASSETS;
	RCODE rc = sqlExec(strCmd);
	unlockHostListInfoDb();
	return rc;
}

//============================================================================
void HostListInfoDb::purgeAllHostLists( void ) 
{
	lockHostListInfoDb();
	std::string strCmd = "DELETE FROM " + TABLE_ASSETS;
	RCODE rc = sqlExec( strCmd );
	unlockHostListInfoDb();
	if( rc )
	{
		LogMsg( LOG_ERROR, "HostListInfoDb::purgeAllHostLists error %d\n", rc );
	}
	else
	{
		LogMsg( LOG_INFO, "HostListInfoDb::purgeAllHostLists success\n" );
	}
}

//============================================================================
void HostListInfoDb::removeHostList( const char * assetName )
{
	DbBindList bindList( assetName );
	sqlExec( "DELETE FROM tblHostLists WHERE assetName=?", bindList );
}

//============================================================================
void HostListInfoDb::removeHostList( VxGUID& assetId )
{
	std::string assetStr = assetId.toHexString();
	DbBindList bindList( assetStr.c_str() );
	sqlExec( "DELETE FROM tblHostLists WHERE unique_id=?", bindList );
}

//============================================================================
void HostListInfoDb::removeHostList( HostListInfo * assetInfo )
{
	// the bind string is not copied so must be in memory until sql is executed
	//DbBindList bindList( assetInfo->getHostListUniqueId().toHexString().c_str() );
	std::string hexId = assetInfo->getHostListUniqueId().toHexString();
	DbBindList bindList( hexId.c_str() );
	sqlExec( "DELETE FROM tblHostLists WHERE unique_id=?", bindList );
}

//============================================================================
void HostListInfoDb::addHostList( VxGUID&			assetId, 
							VxGUID&			creatorId, 
							VxGUID&			historyId, 
							const char *	assetName, 
							int64_t			assetLen, 
							uint32_t		assetType, 							
							VxSha1Hash&		hashId, 
							uint32_t		locationFlags, 
							const char *	assetTag, 
							time_t			creationTimeStamp,
                            EHostListSendState sendState )
{
	removeHostList( assetId );

	std::string assetIdStr		= assetId.toHexString();
	std::string creatorIdStr	= creatorId.toHexString();
	std::string historyIdStr	= historyId.toHexString();

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

	RCODE rc  = sqlExec( "INSERT INTO tblHostLists (unique_id,creatorId,historyId,assetName,length,type,hashId,locFlags,assetTag,creationTime,sendState) values(?,?,?,?,?,?,?,?,?,?,?)",
		bindList );
	if( rc )
	{
		LogMsg( LOG_ERROR, "HostListInfoDb::addHostList error %d\n", rc );
	}
}

//============================================================================
void HostListInfoDb::updateHostListSendState( VxGUID& assetId, EHostListSendState sendState )
{
	std::string assetIdStr		= assetId.toHexString();
	DbBindList bindList(  (int)sendState );
	bindList.add( assetIdStr.c_str() );
	RCODE rc  = sqlExec( "UPDATE tblHostLists SET sendState=? WHERE unique_id=?",
		bindList );
	if( rc )
	{
		LogMsg( LOG_ERROR, "HostListInfoDb::addHostList error %d\n", rc );
	}
}

//============================================================================
void HostListInfoDb::addHostList( HostListInfo* assetInfo )
{
	addHostList(	assetInfo->getHostListUniqueId(),
				assetInfo->getCreatorId(),
				assetInfo->getHistoryId(),
				assetInfo->getHostListName().c_str(),
				assetInfo->getHostListLength(),
				(uint32_t)assetInfo->getHostListType(),				
				assetInfo->getHostListHashId(),
				assetInfo->getLocationFlags(),
				assetInfo->getHostListTag().length() ? assetInfo->getHostListTag().c_str() : "",
				assetInfo->getCreationTime(),
				assetInfo->getHostListSendState() );
}

//============================================================================
void HostListInfoDb::getAllHostLists( std::vector<HostListInfo*>& HostListHostListList )
{
	std::string assetName;
	uint16_t assetType;
	uint64_t assetLen;
	std::string destasset;
	std::string consoleId;
	lockHostListInfoDb();
	DbCursor * cursor = startQuery( "SELECT * FROM tblHostLists" ); // ORDER BY unique_id DESC  // BRJ don't know why ORDER BY quit working on android.. do in code
	if( NULL != cursor )
	{
		while( cursor->getNextRow() )
		{
			assetName = cursor->getString( COLUMN_ASSET_NAME );
			assetLen =  (uint64_t)cursor->getS64( COLUMN_ASSET_LEN );
			assetType = (uint16_t)cursor->getS32( COLUMN_ASSET_TYPE );

			HostListInfo * assetInfo = new HostListInfo( assetName.c_str(), assetLen, assetType );
			assetInfo->setHostListUniqueId( cursor->getString( COLUMN_ASSET_UNIQUE_ID ) );
			assetInfo->setCreatorId( cursor->getString( COLUMN_ASSET_CREATOR_ID ) );
			assetInfo->setHistoryId( cursor->getString( COLUMN_ASSET_HISTORY_ID ) );
			assetInfo->setHostListHashId( (uint8_t *)cursor->getBlob( COLUMN_ASSET_HASH_ID ) );
			assetInfo->setLocationFlags( cursor->getS32( COLUMN_LOCATION_FLAGS ) );
			assetInfo->setHostListTag( cursor->getString( COLUMN_ASSET_TAG ) );
			assetInfo->setCreationTime(  (time_t)cursor->getS64( COLUMN_CREATION_TIME ) );
			assetInfo->setHostListSendState( ( EHostListSendState )cursor->getS32( COLUMN_ASSET_SEND_STATE ) );
			
			insertHostListInTimeOrder( assetInfo, HostListHostListList );
		}

		cursor->close();
	}

	unlockHostListInfoDb();
} 

//============================================================================
void HostListInfoDb::insertHostListInTimeOrder( HostListInfo *assetInfo, std::vector<HostListInfo*>& assetList )
{
	std::vector<HostListInfo*>::iterator iter;
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

