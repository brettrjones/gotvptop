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
#include <CoreLib/HostListDefs.h>

class HostListInfo;
class HostListMgr;
class VxGUID;
class VxSha1Hash;

class HostListInfoDb : public DbBase
{
public:
	HostListInfoDb( HostListMgr& mgr );
	virtual ~HostListInfoDb();

	void						lockHostListInfoDb( void )					{ m_HostListInfoDbMutex.lock(); }
	void						unlockHostListInfoDb( void )				{ m_HostListInfoDbMutex.unlock(); }

	void						addHostList(	VxGUID&			assetId, 
											VxGUID&			creatorId, 
											VxGUID&			historyId, 
											const char *	assetName, 
											int64_t			assetLen, 
											uint32_t		assetType, 							
											VxSha1Hash&		hashId, 
											uint32_t		locationFlags, 
											const char *	assetTag = "", 
											time_t			timestamp = 0,
											EHostListSendState sendState = eHostListSendStateNone );

	void 						addHostList( HostListInfo * assetInfo );
	void						removeHostList( const char * assetName );
	void						removeHostList( VxGUID& assetId );
	void						removeHostList( HostListInfo * assetInfo );

	void						getAllHostLists( std::vector<HostListInfo*>& HostListHostListList );
	void						purgeAllHostLists( void ); 
	void						updateHostListTypes( void );
	void						updateHostListSendState( VxGUID& assetId, EHostListSendState sendState );

protected:
	virtual RCODE				onCreateTables( int iDbVersion );
	virtual RCODE				onDeleteTables( int iOldVersion );
	void						insertHostListInTimeOrder( HostListInfo *assetInfo, std::vector<HostListInfo*>& assetList );

	HostListMgr&					m_HostListMgr;
	VxMutex						m_HostListInfoDbMutex;
};

