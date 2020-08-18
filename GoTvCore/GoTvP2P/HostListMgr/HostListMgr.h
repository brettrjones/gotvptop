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

#include "HostListMgrBase.h"

#include <CoreLib/VxThread.h>
#include <CoreLib/VxSemaphore.h>
#include <CoreLib/VxMutex.h>

class PktFileListReply;

class HostListInfo;
class HostListInfoDb;
class HostListHistoryMgr;

class HostListMgr : public HostListMgrBase
{
public:
	HostListMgr( P2PEngine& engine );
	virtual ~HostListMgr();

	bool						isHostListListInitialized( void )				{ return m_HostListListInitialized; }
	// startup when user specific directory has been set after user logs on
	void						fromGuiUserLoggedOn( void );
	void						assetInfoMgrStartup( VxThread * startupThread );
	void						assetInfoMgrShutdown( void );

	virtual bool				fromGuiGetHostListInfo( uint8_t fileTypeFilter );
	virtual bool				fromGuiSetFileIsShared( std::string fileName, bool shareFile, uint8_t * fileHashId );

	bool						isSharedFileHostList( std::string& fileName );
	bool						isSharedFileHostList( VxSha1Hash& fileHashId );
	bool						getFileHashId( std::string& fileFullName, VxSha1Hash& retFileHashId );
	bool						getFileFullName( VxSha1Hash& fileHashId, std::string& retFileFullName );


	std::vector<HostListInfo*>&	getHostListInfoList( void )				{ return m_HostListInfoList; }
	HostListInfo *					findHostList( std::string& fileName );
	HostListInfo *					findHostList( VxSha1Hash& fileHashId );
	HostListInfo *					findHostList( VxGUID& assetId );

	uint16_t					getHostListFileTypes( void )				{ return m_u16HostListFileTypes; }
	void						updateHostListFileTypes( void );

	void						lockFileListPackets( void )				{ m_FileListPacketsMutex.lock(); }
	void						unlockFileListPackets( void )			{ m_FileListPacketsMutex.unlock(); }
	std::vector<PktFileListReply*>&	getFileListPackets( void )			{ return m_FileListPackets; }
	void						updateFileListPackets( void );

	void						fileWasShredded( const char * fileName );

    HostListInfo * 				addHostListFile( const char * fileName, uint64_t fileLen, uint8_t fileType );

	bool						addHostListFile(	const char *	fileName, 
												VxGUID&			assetId,  
												uint8_t *		hashId = 0, 
												EHostListLocation	locationFlags = eHostListLocUnknown, 
												const char *	assetTag = "", 
												int64_t		    timestamp = 0 );

	bool						addHostListFile(	const char *	fileName, 
												VxGUID&			assetId,  
												VxGUID&		    creatorId, 
												VxGUID&		    historyId, 
												uint8_t *		hashId = 0, 
												EHostListLocation	locationFlags = eHostListLocUnknown, 
												const char *	assetTag = "", 
                                                int64_t			timestamp = 0 );

	bool						addHostList( HostListInfo& assetInfo );
	bool						removeHostList( std::string fileName );
	bool						removeHostList( VxGUID& assetUniqueId );
	void						queryHistoryHostLists( VxGUID& historyId );

	void						generateHashForFile( std::string fileName );
	void						updateHostListXferState( VxGUID& assetUniqueId, EHostListSendState assetSendState, int param = 0 );
	void						announceHostListXferState( VxGUID& assetUniqueId, EHostListSendState assetSendState, int param );

protected:
	void						updateHostListListFromDb( VxThread * thread );
	void						generateHashIds( VxThread * thread );
	void						clearHostListFileListPackets( void );
	void						clearHostListInfoList( void );
    HostListInfo *                 createHostListInfo( const char * fileName, uint64_t fileLen, uint8_t fileType );
	HostListInfo *					createHostListInfo(	const char *	fileName, 
													VxGUID&			assetId,  
													uint8_t *		hashId, 
													EHostListLocation	locationFlags = eHostListLocUnknown, 
													const char *	assetTag = "", 
													int64_t			timestamp = 0 );
	bool						insertNewInfo( HostListInfo * assetInfo );
	void						updateDatabase( HostListInfo * assetInfo );
	void						updateHostListDatabaseSendState( VxGUID& assetUniqueId, EHostListSendState sendState );
	void						announceHostListAdded( HostListInfo * assetInfo );
	void						announceHostListRemoved( HostListInfo * assetInfo );
	void						insertHostListInTimeOrder( HostListInfo * assetInfo );

	//=== vars ===//
	bool						m_Initialized;
	bool						m_HostListListInitialized;
	HostListInfoDb&				m_HostListInfoDb;
	std::vector<HostListInfo*>	m_HostListInfoList;

	std::vector<HostListInfo*>	m_WaitingForHastList;
	std::vector<std::string>	m_GenHashList;
	VxMutex						m_GenHashMutex;
	VxThread					m_GenHashThread;
	VxSemaphore					m_GenHashSemaphore;

	uint16_t					m_u16HostListFileTypes;
	VxMutex						m_FileListPacketsMutex;
	std::vector<PktFileListReply*> m_FileListPackets;
};

