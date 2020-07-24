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

class HostListInfo;

class HostListXferDb : public DbBase
{
public:
	HostListXferDb();
	virtual ~HostListXferDb();

	void						lockHostListXferDb( void )			{ m_HostListXferDbMutex.lock(); }
	void						unlockHostListXferDb( void )			{ m_HostListXferDbMutex.unlock(); }

	virtual RCODE				onCreateTables( int iDbVersion );
	virtual RCODE				onDeleteTables( int iOldVersion );

	void 						addHostList( VxGUID& assetUniqueId );
	void						removeHostList( VxGUID& assetUniqueId );

	void						getAllHostLists( std::vector<VxGUID>& assetList );
	void						purgeAllHostListXfer( void ); 

protected:
	VxMutex						m_HostListXferDbMutex;
};

