//============================================================================
// Copyright (C) 2014 Brett R. Jones
// Issued to MIT style license by Brett R. Jones in 2017
//
// You may use, copy, modify, merge, publish, distribute, sub-license, and/or sell this software
// provided this Copyright is not modified or removed and is included all copies or substantial portions of the Software
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// brett.jones@engineer.com
// http://www.gotvptop.net
//============================================================================

#include "AnchorDb.h"
#include "AnchorList.h"

#include <CoreLib/VxGlobals.h>
#include <CoreLib/VxParse.h>
#include <CoreLib/sqlite3.h>

#include <memory.h>

namespace
{
	//const int			COLUMN_IDX_DATETIME				= 0;
	//const int			COLUMN_IDX_ANN_ID				= 1;
	//const int			COLUMN_IDX_ANN_BLOB				= 2;
	//const int			COLUMN_IDX_ANN_NAME				= 3;
	//const int			COLUMN_IDX_ANN_DESC				= 4;
	//const int			COLUMN_IDX_FIREWALLED			= 5;

	const int 			LIMIT_DATABASE_ROWS 			= 1000; // limit database size by limiting database table to this many rows

	const int			MAX_PHONE_SHAKE_IN_LIST_TIME_MS = 30000;
}

//============================================================================
AnchorDb::AnchorDb()
: DbBase( "AnchorDb" )
, m_iInseredEntryCount(0)
{
}

//============================================================================
AnchorDb::~AnchorDb()
{
}

//============================================================================
RCODE AnchorDb::onCreateTables( int iDbVersion )
{
	RCODE rc = sqlExec( "CREATE TABLE table_ann (ann_datetime BIGINT, ann_id TEXT, ann_blob BLOB, ann_name TEXT, ann_desc TEXT, firewalled INTEGER)" );
	vx_assert( 0 == rc );
	return rc;
}

//============================================================================
RCODE AnchorDb::onDeleteTables( int iOldVersion )
{
	RCODE rc = sqlExec( (char *)"DROP TABLE table_ann" );
	vx_assert( 0 == rc );
	return rc;
}

//============================================================================
void AnchorDb::addIgnoreId( VxGUID& onlineIdToIgnore )
{
	std::vector<VxGUID>::iterator iter;
	for( iter = m_IgnoreIdList.begin(); iter != m_IgnoreIdList.end(); ++iter )
	{
		if( (*iter) == onlineIdToIgnore )
		{
			// already in list
			return;
		}
	}

	m_IgnoreIdList.push_back( onlineIdToIgnore );
}

//============================================================================
RCODE AnchorDb::handleAnnounce(		AnchorList&			anchorListIn, 
									AnchorList&			anchorListOut,
									VxGUID				ignoreMe )
{
	RCODE rc = 0;
	std::vector<VxGUID>::iterator ignoreIter;

	anchorListOut.m_AnchorAction = anchorListIn.m_AnchorAction;
	anchorListOut.m_EntryCount = 0;
	if( 1 != anchorListIn.m_EntryCount )
	{
		LogMsg( LOG_ERROR, "AnchorDb::handleAnnounce: invalid anchorListIn count\n" );
		return -2;
	}

	AnchorListEntry * callerEntry		= &anchorListIn.m_List[0];
	int				isFireWalled		= callerEntry->requiresRelay();
	std::string		annId;
	callerEntry->getMyOnlineId( annId );
	int64_t s64PostTimeMs = GetGmtTimeMs();
	bool limitDatabaseEntries = false;
	int64_t s64RemoveEntriesOlderThanThisTime = 0;

	m_DbMutex.lock(); // make thread safe

	bool bExists = false;
    DbCursor * cursor = startQuery(  "SELECT * FROM table_ann WHERE ann_id=?", annId.c_str() );
	if( NULL != cursor )
    {
		if( cursor->getNextRow() )
		{
			bExists = true;
		}

		cursor->close();
	}

	DbBindList bindList( s64PostTimeMs );
	bindList.add( callerEntry, sizeof( AnchorListEntry ) );
	bindList.add( callerEntry->getOnlineName() );
	bindList.add( callerEntry->getOnlineDescription() );
	bindList.add( isFireWalled );
	bindList.add( annId.c_str() );

	if( bExists )
	{
		rc = sqlExec( "UPDATE table_ann SET ann_datetime=?,ann_blob=?,ann_name=?,ann_desc=?,firewalled=? WHERE ann_id=?", bindList );
	}
	else
	{
		// insert new record
		// first time startup and every 50 inserts check and limit number of database entries
		if( 0 == m_iInseredEntryCount )
		{
			limitDatabaseEntries = true;
		}

		m_iInseredEntryCount++;
		if( 50 == m_iInseredEntryCount )
		{
			m_iInseredEntryCount = 0;
		}

		rc = sqlExec( "INSERT INTO table_ann (ann_datetime, ann_blob, ann_name, ann_desc, firewalled, ann_id) VALUES(?,?,?,?,?,?)", bindList );
	}

	if( rc )
	{
		LogMsg( LOG_ERROR, "AnchorDb::handleAnnounce: ERROR %d updating user\n", rc );
	}

	if( eAnchorActionPhoneShake == anchorListIn.m_AnchorAction )
	{
		m_DbMutex.unlock();
		return handlePhoneShake( *callerEntry, anchorListOut, s64PostTimeMs );
	}
	else if( eAnchorActionRelaysOnly == anchorListIn.m_AnchorAction )
	{
		// get rows where user is not firewalled ( potential relays )
		cursor =  startQuery( "SELECT ann_datetime,ann_blob FROM table_ann WHERE firewalled=0" ); // ORDER BY ann_datetime DESC" ); // BRJ don't know why ORDER BY quit working on android.. do in code
	}
	else
	{
		// get all rows
		cursor =  startQuery( "SELECT ann_datetime,ann_blob FROM table_ann" ); // ORDER BY ann_datetime DESC" ); // BRJ don't know why ORDER BY quit working on android.. do in code
	}

	bool foundCallerContact = false;
#define MAX_ANN_MATCH_ENTRIES 500
	AnchorListEntry tmpEntries[MAX_ANN_MATCH_ENTRIES];
	int foundEntryIdx = 0;
	uint64_t minTimeFound = 0x7fffffffffffffff;

	if( NULL != cursor )
	{
		int rowIdx = 0;
		bool bShouldListRowToClient = true;
		while( cursor->getNextRow() )
		{
			if( bShouldListRowToClient )
			{
				bool ignoreThisEntry = false;
				int blobLen = 0;
				AnchorListEntry * listEntry = (AnchorListEntry *) cursor->getBlob( 1, &blobLen );
				if( blobLen != sizeof( AnchorListEntry ) )
				{
					LogMsg( LOG_ERROR, "AnchorDb::handleAnnounce: invalid blob len %d\n", blobLen );
				}
				else
				{
					if( false == foundCallerContact )
					{
						// don't send caller's entry back to him
						if( listEntry->getMyOnlineId() == callerEntry->getMyOnlineId() )
						{
							foundCallerContact = true;
							ignoreThisEntry = true;
						}
					}

					if( m_IgnoreIdList.size() && ( false == ignoreThisEntry ) )
					{
						for( ignoreIter = m_IgnoreIdList.begin(); ignoreIter != m_IgnoreIdList.end(); ignoreIter++ )
						{
							if( (*ignoreIter) == listEntry->getMyOnlineId() )
							{
								ignoreThisEntry = true;
								break;
							}
						}
					}

					if( listEntry->getMyOnlineId() == callerEntry->getMyOnlineId() )
					{
						ignoreThisEntry = true;
					}

					if( false == ignoreThisEntry ) 
					{
						uint64_t timeOfEntry = (uint64_t)cursor->getS64( 0 );
						if( timeOfEntry != 0 )
						{
							if( timeOfEntry < minTimeFound )
							{
								minTimeFound = timeOfEntry;
							}
						}

						listEntry->setTimeLastContact( timeOfEntry );
						memcpy( &tmpEntries[ foundEntryIdx ], listEntry, sizeof( AnchorListEntry ) );
						foundEntryIdx++;
						if( MAX_ANN_MATCH_ENTRIES == foundEntryIdx )
						{
							// found as many as allowed
							break;
						}
					}
				}
			}

			rowIdx++;
			if( LIMIT_DATABASE_ROWS <= rowIdx )
			{
				s64RemoveEntriesOlderThanThisTime = cursor->getS64( 0 );
				break;
			}
		}

		cursor->close();
	}

	// copy found entries to list in time descending order
	int toCopyCnt = MIN( foundEntryIdx, MAX_ANCHOR_ENTRIES );
    //uint64_t timeLastEntry = 0;
	for( int i = 0; i < toCopyCnt; i++ )
	{
		uint64_t timeThisEntry; 
		uint64_t timeMaxFound = 0;
		int timeFoundIdx = -1;
        for( int tmpIdx = 0; tmpIdx < foundEntryIdx; tmpIdx++ )
		{
			timeThisEntry = tmpEntries[tmpIdx].getTimeLastContact();
			if( ( 0 != timeThisEntry ) && ( timeThisEntry > timeMaxFound ) )
			{
				timeMaxFound = timeThisEntry;
				timeFoundIdx = tmpIdx;
			}
		}

		if( timeFoundIdx != -1 )
		{
			memcpy( &anchorListOut.m_List[ anchorListOut.m_EntryCount ], &tmpEntries[timeFoundIdx], sizeof( AnchorListEntry ) );
			anchorListOut.m_EntryCount++;
		}
		
		// clear time stamp so don't copy it again
		tmpEntries[timeFoundIdx].setTimeLastContact( 0 );
	}

	anchorListOut.calculateLength();

	if( MAX_ANN_MATCH_ENTRIES == foundEntryIdx )
	{
		DbBindList bindList( (int64_t)minTimeFound );
		rc = sqlExec( "DELETE FROM table_ann WHERE ann_datetime < ?", bindList );
		if( rc )
        {
			LogMsg( LOG_INFO, "Error %d limiting AnchorDb\n", rc );
		}
	}

	m_DbMutex.unlock();
	return rc;
}

//============================================================================
RCODE AnchorDb::handlePhoneShake(		AnchorListEntry&	callerEntry, 
										AnchorList&			anchorListOut,
										int64_t					s64PostTimeMs )
{
	RCODE rc = 0;
	m_PhoneShakeMutex.lock();
	// remove ourself and all that are to old
	int64_t toOldTime = s64PostTimeMs - MAX_PHONE_SHAKE_IN_LIST_TIME_MS;
    std::vector<PhoneShakeEntry>::iterator iter;
	iter = m_PhoneShakeList.begin();
	while( iter != m_PhoneShakeList.end() )
	{
		if( ( toOldTime > (*iter).getPostTimeMs() ) 
			|| ( (*iter).getMyOnlineId() == callerEntry.getMyOnlineId() ) )
		{
			iter = m_PhoneShakeList.erase( iter );
		}
		else
		{
			++iter;
		}
	}

	// put ourself in list for anybody else
	PhoneShakeEntry shakeEntry( callerEntry, s64PostTimeMs );
	m_PhoneShakeList.push_back( shakeEntry );
	m_PhoneShakeMutex.unlock();

	VxSleep( 1000 );

	// get list of anyone left in list
	int entryCnt = 0;
	AnchorListEntry * anchorEntry;
	m_PhoneShakeMutex.lock();
	for( iter = m_PhoneShakeList.begin(); iter != m_PhoneShakeList.end(); ++iter )
	{
		anchorEntry = (*iter).getAnchorListEntry();
		if( anchorEntry->getMyOnlineId() != callerEntry.getMyOnlineId() )
		{
			memcpy( &anchorListOut.m_List[entryCnt], (*iter).getAnchorListEntry(), sizeof( AnchorListEntry ) );
			entryCnt++;
		}
	}

	m_PhoneShakeMutex.unlock();
    anchorListOut.m_EntryCount = entryCnt;

	return rc;
}

//============================================================================
bool AnchorDb::validateId( std::string& onlineId )
{
	return true;
}

//============================================================================
bool AnchorDb::validatePort( std::string& port )
{
	return true;
}
//============================================================================
bool AnchorDb::validateIPv4( std::string& ipv4 )
{
	return true;
}
//============================================================================
bool AnchorDb::validateIPv6( std::string& ipv6 )
{
	return true;
}

