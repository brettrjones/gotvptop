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

#include "HostListMgr.h"
#include "HostListInfo.h"
#include "HostListInfoDb.h"

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>
#include <GoTvInterface/IToGui.h>

#include <PktLib/PktAnnounce.h>
#include <PktLib/PktsFileList.h>

#include <CoreLib/VxFileUtil.h>
#include <CoreLib/VxFileIsTypeFunctions.h>
#include <CoreLib/VxGlobals.h>
#include <CoreLib/VxTime.h>


#include <time.h>

namespace
{
	const char * ASSET_INFO_DB_NAME = "HostListInfoDb.db3";

	//============================================================================
    static void * HostListMgrGenHashIdsThreadFunc( void * pvContext )
	{
		VxThread * poThread = (VxThread *)pvContext;
		poThread->setIsThreadRunning( true );
		HostListMgr * poMgr = (HostListMgr *)poThread->getThreadUserParam();
        if( poMgr )
        {
            poMgr->assetInfoMgrStartup( poThread );
        }

		poThread->threadAboutToExit();
        return nullptr;
	}
}

//============================================================================
HostListMgr::HostListMgr( P2PEngine& engine )
: HostListMgrBase( engine )
, m_Initialized( false )
, m_HostListListInitialized( false )
, m_HostListInfoDb( * new HostListInfoDb( *this ) )
{
}

//============================================================================
HostListMgr::~HostListMgr()
{
	delete &m_HostListInfoDb;
}

//============================================================================
void HostListMgr::fromGuiUserLoggedOn( void )
{
	if( !m_Initialized )
	{
		m_Initialized = true;
		m_GenHashThread.startThread( (VX_THREAD_FUNCTION_T)HostListMgrGenHashIdsThreadFunc, this, "HostListMgrGenHash" );			
	}
}

//============================================================================
void HostListMgr::assetInfoMgrStartup( VxThread * startupThread )
{
	if( startupThread->isAborted() )
		return;
	// user specific directory should be set
	std::string dbName = VxGetSettingsDirectory();
	dbName += ASSET_INFO_DB_NAME; 
	lockResources();
	m_HostListInfoDb.dbShutdown();
	m_HostListInfoDb.dbStartup( 1, dbName );
	unlockResources();
	if( startupThread->isAborted() )
		return;
	updateHostListListFromDb( startupThread );
	m_HostListListInitialized = true;
	if( startupThread->isAborted() )
		return;
	generateHashIds( startupThread );
}

//============================================================================
void HostListMgr::assetInfoMgrShutdown( void )
{
	m_GenHashThread.abortThreadRun( true );
	m_GenHashSemaphore.signal();
	lockResources();
	clearHostListInfoList();
	clearHostListFileListPackets();
	m_HostListInfoDb.dbShutdown();
	unlockResources();
	m_HostListListInitialized = false;
	m_Initialized = false;
}

//============================================================================
void HostListMgr::generateHashForFile( std::string fileName )
{
	m_GenHashMutex.lock();
	m_GenHashList.push_back( fileName );
	m_GenHashMutex.unlock();
	m_GenHashSemaphore.signal();
}

//============================================================================
void HostListMgr::generateHashIds( VxThread * genHashThread )
{
	while( false == genHashThread->isAborted() )
	{
		m_GenHashSemaphore.wait(1000);
		if( genHashThread->isAborted() )
		{
			return;
		}

		while( m_GenHashList.size() )
		{
			if( genHashThread->isAborted() )
			{
				return;
			}

			VxSha1Hash fileHash;
			m_GenHashMutex.lock();
			std::string thisFile = m_GenHashList[0];
			m_GenHashList.erase( m_GenHashList.begin() );
			m_GenHashMutex.unlock();
			if( fileHash.generateHashFromFile( thisFile.c_str(), genHashThread ) )
			{
				if( genHashThread->isAborted() )
				{
					return;
				}

				std::vector<HostListInfo*>::iterator iter;
				HostListInfo * assetInfo = 0;
				lockResources();
				// move from waiting to completed
				for( iter = m_WaitingForHastList.begin(); iter != m_WaitingForHastList.end(); ++iter )
				{
					HostListInfo * inListHostListInfo = *iter;
					if( inListHostListInfo->getHostListName() == thisFile )
					{
						assetInfo = inListHostListInfo;
						m_WaitingForHastList.erase( iter );
						assetInfo->setHostListHashId( fileHash );
						m_HostListInfoList.push_back( assetInfo );
						break;
					}
				}

				unlockResources();
				std::vector<HostListCallbackInterface *>::iterator callbackIter;
				lockClientList();
				for( callbackIter = m_HostListClients.begin(); callbackIter != m_HostListClients.end(); ++callbackIter )
				{
					HostListCallbackInterface * client = *callbackIter;
					client->callbackHashIdGenerated( thisFile, fileHash );
				}

				unlockClientList();
				if( assetInfo )
				{
					m_HostListInfoDb.addHostList( assetInfo );
					announceHostListAdded( assetInfo );
				}
			}
		}
	}
}

//============================================================================
HostListInfo * HostListMgr::findHostList( std::string& fileName )
{
	std::vector<HostListInfo*>::iterator iter;
	for( iter = m_HostListInfoList.begin(); iter != m_HostListInfoList.end(); ++iter )
	{
		if( (*iter)->getHostListName() == fileName )
		{
			return (*iter);
		}
	}

	return 0;
}

//============================================================================
HostListInfo * HostListMgr::findHostList( VxSha1Hash& fileHashId )
{
	if( false == fileHashId.isHashValid() )
	{
		LogMsg( LOG_ERROR, "HostListMgr::findHostList: invalid file hash id\n" );
		return 0;
	}

	std::vector<HostListInfo*>::iterator iter;
	for( iter = m_HostListInfoList.begin(); iter != m_HostListInfoList.end(); ++iter )
	{
		if( (*iter)->getHostListHashId() == fileHashId )
		{
			return (*iter);
		}
	}

	return 0;
}

//============================================================================
HostListInfo * HostListMgr::findHostList( VxGUID& assetId )
{
	if( false == assetId.isVxGUIDValid() )
	{
		//LogMsg( LOG_ERROR, "HostListMgr::findHostList: invalid VxGUID asset id\n" );
        return nullptr;
	}

	std::vector<HostListInfo*>::iterator iter;
	for( HostListInfo * assetInfo : m_HostListInfoList )
	{
		if( assetInfo->getHostListUniqueId() == assetId )
		{
			return assetInfo;
		}
	}

	return nullptr;
}

//============================================================================
HostListInfo * HostListMgr::addHostListFile( const char * fileName, uint64_t fileLen, uint8_t fileType )
{
    HostListInfo * assetInfo = createHostListInfo( fileName, fileLen, fileType );
    if( assetInfo )
    {
        if( insertNewInfo( assetInfo ) )
        {
            return assetInfo;
        }
    }

    return NULL;
}

//============================================================================
bool HostListMgr::addHostListFile(	    const char *	fileName, 
									VxGUID&			assetId,  
									uint8_t *		hashId, 
									EHostListLocation	locationFlags, 
									const char *	assetTag, 
                                    int64_t			timestamp )
{
	HostListInfo * assetInfo = createHostListInfo( fileName, assetId, hashId, locationFlags, assetTag, timestamp );
	if( assetInfo )
	{
		return insertNewInfo( assetInfo );
	}
	
	return false;
}

//============================================================================
bool HostListMgr::addHostListFile(	    const char *	fileName, 
									VxGUID&			assetId,  
									VxGUID&		    creatorId, 
									VxGUID&		    historyId, 
									uint8_t *		hashId, 
									EHostListLocation	locationFlags, 
									const char *	assetTag, 
                                    int64_t			timestamp )
{
	HostListInfo * assetInfo = createHostListInfo( fileName, assetId, hashId, locationFlags, assetTag, timestamp );
	if( assetInfo )
	{
		assetInfo->setCreatorId( creatorId );
		assetInfo->setCreatorId( historyId );
		return insertNewInfo( assetInfo );
	}
	
	return false;
}

//============================================================================
bool HostListMgr::addHostList( HostListInfo& assetInfo )
{
	HostListInfo * newHostListInfo = new HostListInfo( assetInfo );
	LogMsg( LOG_INFO, "HostListMgr::addHostList\n" );
	return insertNewInfo( newHostListInfo );
}

//============================================================================
HostListInfo * HostListMgr::createHostListInfo( const char * fileName, uint64_t fileLen, uint8_t fileType )
{
    HostListInfo * assetInfo = new HostListInfo( fileName, fileLen, fileType );
    if( assetInfo )
    {
        assetInfo->getHostListUniqueId().initializeWithNewVxGUID();
    }

    return assetInfo;
}

//============================================================================
HostListInfo * HostListMgr::createHostListInfo( 	const char *	fileName, 
										VxGUID&			assetId,  
										uint8_t *	    hashId, 
										EHostListLocation	locationFlags, 
										const char *	assetTag, 
                                        int64_t			timestamp )
{
	uint64_t  fileLen = VxFileUtil::getFileLen( fileName );
	uint8_t	fileType = VxFileExtensionToFileTypeFlag( fileName );
	if( ( false == isAllowedFileOrDir( fileName ) )
		|| ( 0 == fileLen ) )
	{
		LogMsg( LOG_ERROR, "ERROR %d HostListMgr::createHostListInfo could not get file info %s\n", VxGetLastError(), fileName );
		return NULL;
	}

	HostListInfo * assetInfo = new HostListInfo( fileName, fileLen, fileType );
	assetInfo->setHostListUniqueId( assetId );
	if( false == assetInfo->getHostListUniqueId().isVxGUIDValid() )
	{
		assetInfo->getHostListUniqueId().initializeWithNewVxGUID();
	}

	assetInfo->getHostListHashId().setHashData( hashId );
	assetInfo->setLocationFlags( locationFlags );
	assetInfo->setHostListTag( assetTag );
	assetInfo->setCreationTime( timestamp ? timestamp : GetTimeStampMs() );

	return assetInfo;
}

//============================================================================
bool HostListMgr::insertNewInfo( HostListInfo * assetInfo )
{
	bool result = false;
	HostListInfo * assetInfoExisting = findHostList( assetInfo->getHostListUniqueId() );
	if( assetInfoExisting )
	{
		LogMsg( LOG_ERROR, "ERROR HostListMgr::insertNewInfo: duplicate assset %s\n", assetInfo->getHostListName().c_str() );
		if( assetInfoExisting != assetInfo )
		{
			*assetInfoExisting = *assetInfo;
			assetInfo = assetInfoExisting;
		}
	}

	if( 0 == assetInfo->getCreationTime() )
	{
		assetInfo->setCreationTime( GetTimeStampMs() );
	}

	//if( assetInfo->needsHashGenerated() )
	//{
	//	lockResources();
	//	m_WaitingForHastList.push_back( assetInfo );
	//	unlockResources();
	//	generateHashForFile( assetInfo->getHostListName() );
	//	result = true;
	//}
	//else
	//{
		if( 0 == assetInfoExisting )
		{
			lockResources();
			m_HostListInfoList.push_back( assetInfo );
			unlockResources();
			announceHostListAdded( assetInfo );
		}

		updateDatabase( assetInfo );
		result = true;
	//}

	return result;
}

//============================================================================
void HostListMgr::announceHostListAdded( HostListInfo * assetInfo )
{
	LogMsg( LOG_INFO, "HostListMgr::announceHostListAdded start\n" );
	if( assetInfo->getIsFileHostList() )
	{
		updateFileListPackets();
		updateHostListFileTypes();
	}
	
	lockClientList();
	std::vector<HostListCallbackInterface *>::iterator iter;
	for( iter = m_HostListClients.begin();	iter != m_HostListClients.end(); ++iter )
	{
		HostListCallbackInterface * client = *iter;
		client->callbackHostListAdded( assetInfo );
	}

	unlockClientList();
	LogMsg( LOG_INFO, "HostListMgr::announceHostListAdded done\n" );
}

//============================================================================
void HostListMgr::announceHostListRemoved( HostListInfo * assetInfo )
{
	//if( assetInfo->getIsHostList() )
	{
		updateFileListPackets();
		updateHostListFileTypes();
	}

	lockClientList();
	std::vector<HostListCallbackInterface *>::iterator iter;
	for( iter = m_HostListClients.begin();	iter != m_HostListClients.end(); ++iter )
	{
		HostListCallbackInterface * client = *iter;
		client->callbackHostListRemoved( assetInfo );
	}

	unlockClientList();
}

//============================================================================
void HostListMgr::announceHostListXferState( VxGUID& assetUniqueId, EHostListSendState assetSendState, int param )
{
	LogMsg( LOG_INFO, "HostListMgr::announceHostListXferState state %d start\n", assetSendState );
	lockClientList();
	std::vector<HostListCallbackInterface *>::iterator iter;
	for( iter = m_HostListClients.begin();	iter != m_HostListClients.end(); ++iter )
	{
		HostListCallbackInterface * client = *iter;
		client->callbackHostListSendState( assetUniqueId, assetSendState, param );
	}

	unlockClientList();
	LogMsg( LOG_INFO, "HostListMgr::announceHostListXferState state %d done\n", assetSendState );
}

//============================================================================
bool HostListMgr::removeHostList( std::string fileName )
{
	bool assetRemoved = false;
	std::vector<HostListInfo*>::iterator iter;
	for( iter = m_HostListInfoList.begin(); iter != m_HostListInfoList.end(); ++iter )
	{
		if( fileName == (*iter)->getHostListName() )
		{
			HostListInfo * assetInfo = *iter;
			m_HostListInfoList.erase( iter );
			m_HostListInfoDb.removeHostList( fileName.c_str() );
			announceHostListRemoved( assetInfo );
			delete assetInfo;
			assetRemoved = true;
			break;
		}
	}

	return assetRemoved;
}

//============================================================================
bool HostListMgr::removeHostList( VxGUID& assetUniqueId )
{
	bool assetRemoved = false;
	std::vector<HostListInfo*>::iterator iter;
	for ( iter = m_HostListInfoList.begin(); iter != m_HostListInfoList.end(); ++iter )
	{
		if( assetUniqueId == ( *iter )->getHostListUniqueId() )
		{
			HostListInfo * assetInfo = *iter;
			m_HostListInfoList.erase( iter );
			m_HostListInfoDb.removeHostList( assetInfo );
			announceHostListRemoved( assetInfo );
			delete assetInfo;
			assetRemoved = true;
			break;
		}
	}

	return assetRemoved;
}

//============================================================================
void HostListMgr::clearHostListInfoList( void )
{
	std::vector<HostListInfo*>::iterator iter;
	for( iter = m_HostListInfoList.begin(); iter != m_HostListInfoList.end(); ++iter )
	{
		delete (*iter);
	}

	m_HostListInfoList.clear();
}

//============================================================================
void HostListMgr::updateHostListListFromDb( VxThread * startupThread )
{
	std::vector<HostListInfo*>::iterator iter;
	lockResources();
	clearHostListInfoList();
	m_HostListInfoDb.getAllHostLists( m_HostListInfoList );
	bool movedToGenerateHash = true;
	while(	movedToGenerateHash 
			&& ( false == startupThread->isAborted() ) )
	{
		// there should not be any without valid hash but if is then generate it
		movedToGenerateHash = false;
		for( iter = m_HostListInfoList.begin(); iter != m_HostListInfoList.end(); ++iter )
		{
			HostListInfo* assetInfo = (*iter);
			EHostListSendState sendState = assetInfo->getHostListSendState();
			if( eHostListSendStateTxProgress == sendState ) 
			{
				assetInfo->setHostListSendState( eHostListSendStateTxFail );
				m_HostListInfoDb.updateHostListSendState( assetInfo->getHostListUniqueId(), eHostListSendStateTxFail );
			}
			else if(  eHostListSendStateRxProgress == sendState  )
			{
				assetInfo->setHostListSendState( eHostListSendStateRxFail );
				m_HostListInfoDb.updateHostListSendState( assetInfo->getHostListUniqueId(), eHostListSendStateRxFail );
			}

			if( assetInfo->needsHashGenerated() )
			{
				m_WaitingForHastList.push_back( assetInfo );
				m_HostListInfoList.erase( iter );
				generateHashForFile( assetInfo->getHostListName() );
				movedToGenerateHash = true;
				break;
			}
		}
	}

	unlockResources();
	updateFileListPackets();
	updateHostListFileTypes();
}

//============================================================================
void HostListMgr::updateHostListFileTypes( void )
{
	uint16_t u16FileTypes = 0;
	std::vector<HostListInfo*>::iterator iter;
	lockResources();
	for( iter = m_HostListInfoList.begin(); iter != m_HostListInfoList.end(); ++iter )
	{
		if( (*iter)->getIsFileHostList() )
		{
			u16FileTypes		|= (*iter)->getHostListType();
		}
	}

	unlockResources();
	// ignore extended types
	u16FileTypes = u16FileTypes & 0xff;
	m_u16HostListFileTypes = u16FileTypes;
	bool fileTypesChanged = false;

	m_Engine.lockAnnouncePktAccess();
	PktAnnounce& pktAnn = m_Engine.getMyPktAnnounce();
	if( pktAnn.getSharedFileTypes() != u16FileTypes )
	{
		fileTypesChanged = true;
		pktAnn.setSharedFileTypes( (uint8_t)u16FileTypes );
	}

	m_Engine.unlockAnnouncePktAccess();
	if( fileTypesChanged )
	{
		lockClientList();
		std::vector<HostListCallbackInterface *>::iterator iter;
		for( iter = m_HostListClients.begin();	iter != m_HostListClients.end(); ++iter )
		{
			HostListCallbackInterface * client = *iter;
			client->callbackHostListFileTypesChanged( u16FileTypes );
		}

		unlockClientList();
	}
}

//============================================================================
void HostListMgr::updateFileListPackets( void )
{
	bool hadHostListFiles = m_FileListPackets.size() ? true : false;
	PktFileListReply * pktFileList = 0;
	clearHostListFileListPackets();
	lockFileListPackets();
	lockResources();
	std::vector<HostListInfo*>::iterator iter;
	for( iter = m_HostListInfoList.begin(); iter != m_HostListInfoList.end(); ++iter )
	{
		HostListInfo * assetInfo = (*iter); 
		if( ( false == assetInfo->getIsFileHostList() ) || ( false == assetInfo->getHostListHashId().isHashValid() ) )
			continue;

		if( 0 == pktFileList )
		{
			pktFileList = new PktFileListReply();
			pktFileList->setListIndex( (uint32_t)m_FileListPackets.size() );
		}

		if( pktFileList->canAddFile( (uint32_t)(assetInfo->getRemoteHostListName().size() + 1) ) )
		{
			pktFileList->addFile(	assetInfo->getHostListHashId(),
									assetInfo->getHostListLength(),
									assetInfo->getHostListType(),
									assetInfo->getRemoteHostListName().c_str() );
		}
		else
		{
			m_FileListPackets.push_back( pktFileList );
			pktFileList = new PktFileListReply();
			pktFileList->setListIndex( (uint32_t)m_FileListPackets.size() );
			pktFileList->addFile(	assetInfo->getHostListHashId(),
									assetInfo->getHostListLength(),
									assetInfo->getHostListType(),
									assetInfo->getHostListName().c_str() );
		}
	}

	if( 0 != pktFileList )
	{
		if( pktFileList->getFileCount() )
		{
			pktFileList->setIsListCompleted( true ); // last pkt in list
			m_FileListPackets.push_back( pktFileList );
		}
		else
		{
			delete pktFileList;
		}
	}

	unlockResources();
	unlockFileListPackets();
	if( hadHostListFiles || m_FileListPackets.size() )
	{
		lockClientList();
		std::vector<HostListCallbackInterface *>::iterator iter;
		for( iter = m_HostListClients.begin();	iter != m_HostListClients.end(); ++iter )
		{
			HostListCallbackInterface * client = *iter;
			client->callbackHostListPktFileListUpdated();
		}

		unlockClientList();
	}
}

//============================================================================
void HostListMgr::clearHostListFileListPackets( void )
{
	lockFileListPackets();
	std::vector<PktFileListReply*>::iterator iter;
	for( iter = m_FileListPackets.begin(); iter != m_FileListPackets.end(); ++iter )
	{
		delete (*iter);
	}

	m_FileListPackets.clear();
	unlockFileListPackets();
}

//============================================================================
bool HostListMgr::fromGuiSetFileIsShared( std::string fileName, bool shareFile, uint8_t * fileHashId )
{
	lockResources();
	HostListInfo* assetInfo = findHostList( fileName );
	if( assetInfo )
	{
		if( ( false == shareFile ) && assetInfo->getIsSharedFileHostList() )
		{
			assetInfo->setIsSharedFileHostList( false );
			updateDatabase( assetInfo );
			unlockResources();
			updateHostListFileTypes();
			updateFileListPackets();
			return true;
		}
	}

	unlockResources();

	if( shareFile )
	{
		// file is not currently HostList and should be
		VxGUID guid;
		HostListInfo * assetInfo = createHostListInfo( fileName.c_str(), guid, fileHashId, eHostListLocShared );
		if( assetInfo )
		{
			insertNewInfo( assetInfo );
		}
	}
	else
	{
		return false;
	}

	return true;
}

/*
//============================================================================
bool HostListMgr::isFileHostList( std::string& fileName )
{
	bool isHostList = false;
	lockResources();
	HostListInfo * assetInfo = findHostList( fileName );
	if( assetInfo )
	{
		isHostList = assetInfo->getIsHostList();
	}

	unlockResources();
	return isHostList;
}

//============================================================================
bool HostListMgr::isFileHostList( VxSha1Hash& fileHashId )
{
	bool isHostList = false;
	lockResources();
	HostListInfo * assetInfo = findHostList( fileHashId );
	if( assetInfo )
	{
		isHostList = assetInfo->getIsHostList();
	}

	unlockResources();
	return isHostList;
}
*/

//============================================================================
bool HostListMgr::getFileHashId( std::string& fileFullName, VxSha1Hash& retFileHashId )
{
	bool foundHash = false;
	lockResources();
	std::vector<HostListInfo*>::iterator iter;
	for( iter = m_HostListInfoList.begin(); iter != m_HostListInfoList.end(); ++iter )
	{
		if( fileFullName == (*iter)->getHostListName() )
		{
			retFileHashId = (*iter)->getHostListHashId();
			foundHash = retFileHashId.isHashValid();
			break;
		}
	}

	unlockResources();
	return foundHash;
}

//============================================================================
bool HostListMgr::getFileFullName( VxSha1Hash& fileHashId, std::string& retFileFullName )
{
	bool isHostList = false;
	lockResources();
	std::vector<HostListInfo*>::iterator iter;
	for( iter = m_HostListInfoList.begin(); iter != m_HostListInfoList.end(); ++iter )
	{
		if( fileHashId == (*iter)->getHostListHashId() )
		{
			isHostList = true;
			retFileFullName = (*iter)->getHostListName();
			break;
		}
	}

	unlockResources();
	return isHostList;
}


//============================================================================
bool HostListMgr::fromGuiGetHostListInfo( uint8_t fileTypeFilter )
{
	lockResources();
	std::vector<HostListInfo*>::iterator iter;
	for( iter = m_HostListInfoList.begin(); iter != m_HostListInfoList.end(); ++iter )
	{
		HostListInfo* assetInfo = (*iter);
		if( 0 != ( fileTypeFilter & assetInfo->getHostListType() ) )
		{
			if( assetInfo->getIsSharedFileHostList() || assetInfo->getIsInLibary() )
			{
				IToGui::getToGui().toGuiFileList(	assetInfo->getHostListName().c_str(), 
										assetInfo->getHostListLength(), 
										assetInfo->getHostListType(), 
										assetInfo->getIsSharedFileHostList(),
										assetInfo->getIsInLibary(),
										assetInfo->getHostListHashId().getHashData() );
			}
		}
	}

	unlockResources();
	IToGui::getToGui().toGuiFileList( "", 0, 0, false, false );
	return true;
}

//============================================================================
void HostListMgr::updateDatabase( HostListInfo * assetInfo )
{
	m_HostListInfoDb.addHostList( assetInfo );
}

//============================================================================
void HostListMgr::updateHostListDatabaseSendState( VxGUID& assetUniqueId, EHostListSendState sendState )
{
	m_HostListInfoDb.updateHostListSendState( assetUniqueId, sendState );
}

//============================================================================
void HostListMgr::queryHistoryHostLists( VxGUID& historyId )
{
	std::vector<HostListInfo*>::iterator iter;
	HostListInfo * assetInfo;
	lockResources();
	for( iter = m_HostListInfoList.begin(); iter != m_HostListInfoList.end(); ++iter )
	{
		assetInfo = (*iter);
		if( assetInfo->getHistoryId() == historyId )
		{
			IToGui::getToGui().toGuiHostListSessionHistory( assetInfo );
		}
	}

	unlockResources();
}

//============================================================================
void HostListMgr::updateHostListXferState( VxGUID& assetUniqueId, EHostListSendState assetSendState, int param )
{
	LogMsg( LOG_INFO, "HostListMgr::updateHostListXferState state %d start\n", assetSendState );
	std::vector<HostListInfo*>::iterator iter;
	HostListInfo* assetInfo;
	bool assetSendStateChanged = false;
	lockResources();
	for( iter = m_HostListInfoList.begin(); iter != m_HostListInfoList.end(); ++iter )
	{
		assetInfo = (*iter);
		if( assetInfo->getHostListUniqueId() == assetUniqueId )
		{
			EHostListSendState oldSendState = assetInfo->getHostListSendState();
			if( oldSendState != assetSendState )
			{
				assetInfo->setHostListSendState( assetSendState );
				assetSendStateChanged = true;
				//updateDatabase( assetInfo );
				updateHostListDatabaseSendState( assetUniqueId, assetSendState );
				switch( assetSendState )
				{
				case eHostListSendStateTxProgress:
					if( eHostListSendStateNone == oldSendState )
					{
						IToGui::getToGui().toGuiHostListAction( eHostListActionTxBegin, assetUniqueId, param );
					}

					IToGui::getToGui().toGuiHostListAction( eHostListActionTxProgress, assetUniqueId, param );
					break;

				case eHostListSendStateRxProgress:
					if( eHostListSendStateNone == oldSendState )
					{
						IToGui::getToGui().toGuiHostListAction( eHostListActionRxBegin, assetUniqueId, param );
					}

					IToGui::getToGui().toGuiHostListAction( eHostListActionRxProgress, assetUniqueId, param );
					break;

				case eHostListSendStateRxSuccess:
					if( ( eHostListSendStateNone == oldSendState )
						|| ( eHostListSendStateRxProgress == oldSendState ) )
					{
						IToGui::getToGui().toGuiHostListAction( eHostListActionRxSuccess, assetUniqueId, param );
						IToGui::getToGui().toGuiHostListAction( eHostListActionRxNotifyNewMsg, assetInfo->getCreatorId(), 100 );
					}
					else 
					{
						IToGui::getToGui().toGuiHostListAction( eHostListActionRxSuccess, assetUniqueId, param );
					}

					break;

				case eHostListSendStateTxSuccess:
					IToGui::getToGui().toGuiHostListAction( eHostListActionTxSuccess, assetUniqueId, param );
					break;

				case eHostListSendStateRxFail:
					IToGui::getToGui().toGuiHostListAction( eHostListActionRxError, assetUniqueId, param );
					break;

				case eHostListSendStateTxFail:
					IToGui::getToGui().toGuiHostListAction( eHostListActionTxError, assetUniqueId, param );
					break;

				case eHostListSendStateTxPermissionErr:
					IToGui::getToGui().toGuiHostListAction( eHostListActionTxError, assetUniqueId, param );
					break;

				case eHostListSendStateRxPermissionErr:
					IToGui::getToGui().toGuiHostListAction( eHostListActionRxError, assetUniqueId, param );
					break;


				case eHostListSendStateNone:
				default:
					break;
				}
			}

			break;
		}
	}

	unlockResources();
	if( assetSendStateChanged )
	{
		announceHostListXferState( assetUniqueId, assetSendState, param );
	}

	LogMsg( LOG_INFO, "HostListMgr::updateHostListXferState state %d done\n", assetSendState );
}


/*
//============================================================================
RCODE HostListMgr::SendMatchList(	uint32_t			u32SktNum,		// Tronacom socket number
									CString &	csMatchString,	// Search Match name
									uint16_t			u16FileTypes,	// types of files to match
									uint16_t			u16LimitType,	// file size limit type
									uint64_t			u64SizeLimit,	// file size limit
									bool		bCloseAfterSend,// if true close the socket after send
									bool		bEncrypt )		// if true encrypt
{	
	int i;
	RCODE rc = 0;

	PktShareFileList gPktList;
	char as8FileName[ VX_MAX_PATH ];
	char as8TmpFileName[ VX_MAX_PATH ];
	long s32PktIdx = 0;
	unsigned long u32FileLen = 0;
	bool bFileOpen = false;
	FILE * pgFile = 0;
	CStringArray acsMatchTokens;
	bool bSendAll = false;
	ShareFileInfo * poInfo;

	if( 1 == csMatchString.GetLength() && 
		'*' == csMatchString[ 0 ] )
	{
		bSendAll = true; //send complete list
	}
	else
	{

		rc = ParseSearchString(	csMatchString,		//String of search tokens
							acsMatchTokens );	//return seperate token in each String
	}
	if( rc )
	{
		LogMsg( LOG_INFO, "HostListMgr::SendMatchList Error 0x%x occured parsing string\n", rc );
		ASSERT( false );
	}
	else
	{
		int	iCnt = m_List.GetSize();
		for( i = 0; i < iCnt; i++ )
		{
			poInfo = &m_List[ i ];
			if( 0 == ( u16FileTypes & poInfo->m_u32Flags ) )
			{
				//is not the file type we are searching for
				continue;
			}
			if( bSendAll ||
				Match( acsMatchTokens, poInfo->m_csDisplayName ) )
			{
				if( 0 == poInfo->m_s64FileLen )
				{
					LogMsg( LOG_INFO, "HostListMgr::Zero Length File %s\n", (const char *) poInfo->m_csDisplayName );
					continue;
				}
				//add file to PktFileList
				unsigned char * pu8Temp = poInfo->m_pu8ChoppedDisplayName;
				unsigned long u32ItemLen = * pu8Temp + sizeof( __int64 );
				if( gPktList.m_u16PktLen + u32ItemLen > sizeof( PktShareFileList ) )
				{
					//wont fit in this Pkt so store and start another
					gPktList.m_u16PktLen = (( gPktList.m_u16PktLen + 15 ) & ~15 );
					if( false == bFileOpen )
					{	
						tmpnam( as8TmpFileName );
						strcpy( as8FileName, g_oGlobals.m_csExeDir );
						strcat( as8FileName, "TcFileShareRes" );
						strcat( as8FileName, as8TmpFileName );
						strcat( as8FileName, "tmp" );
						pgFile = fopen( as8FileName, "wb+" );
						if( 0 == pgFile )
						{
							rc = FILE_OPEN_ERR;
							break;
						}
						bFileOpen = true;
					}

					if( (unsigned long)gPktList.m_u16PktLen != fwrite( &gPktList, 
																		1, 
																		(unsigned long)gPktList.m_u16PktLen, 
																		pgFile ) )
					{
						rc = FILE_WRITE_ERR;
					}
					u32FileLen += gPktList.m_u16PktLen;
					gPktList.m_u16PktLen = gPktList.emptyLen();
					s32PktIdx = 0;
					gPktList.m_u16ListCnt = 0;
				}
				//copy file length first
				*( ( __int64 *)&gPktList.m_au8List[ s32PktIdx ] ) = poInfo->m_s64FileLen;
				//copy chopped string that has display name
				memcpy( &gPktList.m_au8List[ s32PktIdx + sizeof( __int64 ) ], poInfo->m_pu8ChoppedDisplayName, u32ItemLen - sizeof( __int64 ) );

				//show trace of file we added to list
				char as8Buf[ 256 * 2 ];
				VxUnchopStr( poInfo->m_pu8ChoppedDisplayName, as8Buf );
				LogMsg( LOG_INFO, "Added to PktFileList file size %d file %s\n", 
						*( ( unsigned long *)&gPktList.m_au8List[ s32PktIdx ] ),
						as8Buf );


				//increment vars for next item
				s32PktIdx += u32ItemLen;
				gPktList.m_u16ListCnt++;
				gPktList.m_u16PktLen += (unsigned short)u32ItemLen;
			}	
		}
	}
	if( pgFile )
	{
		if( u32FileLen )
		{
			//we allready have at least one pkt in file
			//so add this one if has data
			if( s32PktIdx )
			{
				//we have a pkt with data
				gPktList.m_u16PktLen = (( gPktList.m_u16PktLen + 15 ) & ~15 );
			
				//flush Pkt to file
				if( (unsigned long)gPktList.m_u16PktLen != fwrite( &gPktList, 
																	1, 
																	(unsigned long)gPktList.m_u16PktLen, 
																	pgFile ) )
				{
					rc = FILE_WRITE_ERR;
				}
				u32FileLen += gPktList.m_u16PktLen;
				if( u32FileLen & 0x0f )
				{
					//file length is not on 16 byte boundery so fill in a little
					if( 16 - (u32FileLen & 0x0f) != fwrite( &gPktList, 
																		16 - (u32FileLen & 0x0f),
																		(unsigned long)gPktList.m_u16PktLen, 
																		pgFile ) )
					{
						rc = FILE_WRITE_ERR;
					}
				}
				fclose( pgFile );
			}
			//use threaded file send to send list
			//this uses a separate thread to send file containing packets
			rc = g_poApi->SktSendFile(	u32SktNum,// Socket to send on
							as8FileName,	// packet to be sent via tcp connection
							0,	//offset into file to start at
							4096, //size of pkt chunks
							-2,	// PktType to put in header 	
								// positive value..add header of u16PktType to each chunk sent
								//  -1 = use no headers..send file in chunks of u32PktSize in length
								//	-2 = file is file of packets add value in size of pkt chunks to pkt types
							0, //instance value if has header
							true,		// if true delete file after it is sent
							true,		// if true disconnect after send
							0, //user data for callback
							NULL );		// callback from thread with File Send status
		}
	}
	else
	{
		//we havent even written one pkt to file so
		//just send this one
		gPktList.m_u16PktLen = (( gPktList.m_u16PktLen + 15 ) & ~15 );
 
		g_poApi->SktSend( u32SktNum, &gPktList, bCloseAfterSend );
	}
	return rc;
}

//============================================================================
RCODE HostListMgr::AddDir( CString & csDirPath )
{
	HRESULT hr;
	char as8FullPath[ VX_MAX_PATH ];

	struct _stat gStat;
	int i;


    CArray<CString, CString&> acsWildNameList;//Extensions ( file extentions )
	acsWildNameList.Add( CString( "*.*" ) );
	CArray<HostListInfo, HostListInfo&> agHostListInfoList;//return FileInfo in array

	VxFindFilesByName(	csDirPath,				//start path to search in
						acsWildNameList,//Extensions ( file extentions )
						agHostListInfoList,//return FileInfo in array
						true,						//recurse subdirectories if TRUE
						false		//if TRUE dont return files matching filter else return files that do
 						);
	int iCnt = agHostListInfoList.GetSize();
	//expand list to include the new files
	int iCurListCnt = m_List.GetSize();
	m_List.SetSize( iCnt + iCurListCnt );
	int iResolvedListIdx = iCurListCnt;

	for( i = 0; i < iCnt; i++ )
	{
		CString cs = agHostListInfoList[ i ];
		__int64 s64FileLen = agHostListInfoList[ i ].m_s64Len;
		makeForwardSlashPath( cs );

		//get file extension
		CString csExt = getFileExtension( cs );
		char * pExt = (char *)((const char *)csExt);
		bool bIsLink = false;

		if( 0 == strcmp( pExt, "lnk" ) )
		{ 
			bIsLink = true; 
			as8FullPath[ 0 ] = 0;
			hr = VxResolveShortcut(	0,				//handle to window of caller
									cs,	//.lnk file
									as8FullPath );		//return path to target file
			if( FAILED( hr ) )
			{
				TRACE("Unable to resolve path in %s\n", (const char *)cs );
				continue;
			}
			else
			{
				cs = as8FullPath;	
				int iResult = ::_stat( (const char *)cs, &gStat );
				if( iResult != 0 )
				{
					TRACE( "Problem getting file information\n" );
					continue;
				}
				else
				{
					s64FileLen = gStat.st_size;
					csExt = getFileExtension( cs );
					pExt = (char *)((const char *)csExt);
				}
			}
		}
		//weve got a live one so

		unsigned long u32FileFlags = 0;

		if( VxIsPhotoFileExtention( pExt ) )
		{
			m_bHasImage = true;
			u32FileFlags |= FILE_TYPE_PHOTO;
			m_u32FileFlags |= FILE_TYPE_PHOTO;
		}
		else if( VxIsAudioFileExtention( pExt ) )
		{
			m_bHasAudio = true;
			u32FileFlags |= FILE_TYPE_AUDIO;
			m_u32FileFlags |= FILE_TYPE_AUDIO; 
		}
		else if( VxIsVideoFileExtention( pExt ) )
		{
			m_bHasVideo = true;
			u32FileFlags |= FILE_TYPE_VIDEO;
			m_u32FileFlags |= FILE_TYPE_VIDEO; 
		}
		else if( VxIsExecutableFileExtention( pExt ) )
		{
			m_bHasExecutable = true;
			u32FileFlags |= FILE_TYPE_EXECUTABLE;
			m_u32FileFlags |= FILE_TYPE_EXECUTABLE;
		}
		else if( VxIsArchiveOrDocFileExtention( pExt ) )
		{
			m_bHasArchiveOrDoc = true;
			u32FileFlags |= FILE_TYPE_ARCHIVE_OR_DOC;
			m_u32FileFlags |= FILE_TYPE_ARCHIVE_OR_DOC;
		}
		else if( VxIsArchiveOrDocFileExtention( pExt ) )
		{
			m_bHasCdImage = true;
			u32FileFlags |= FILE_TYPE_CD_IMAGE;
			m_u32FileFlags |= FILE_TYPE_CD_IMAGE;
		}
		else
		{
			m_bHasOther = true;
			u32FileFlags |= FILE_TYPE_OTHER;
			m_u32FileFlags |= FILE_TYPE_OTHER;
		}
		//fill in the data
		m_s64TotalByteCnt += s64FileLen;
		ShareFileInfo * poInfo = &m_List[ iResolvedListIdx ];
		poInfo->m_csPathAndName = cs;
		poInfo->m_s64FileLen = s64FileLen;
		poInfo->m_u32Flags = u32FileFlags;
		if( bIsLink )
		{
			//display name is the file name
			poInfo->m_csDisplayName = VxGetFileNameFromFullPath( cs );
		}
		else
		{
			//display name is full path - root path
			char * pTemp = (char *)(const char *)cs;
			int iRootLen =  csDirPath.GetLength();
			ASSERT( iRootLen < cs.GetLength() );
			if( iRootLen )
			{
				if( '\\' == pTemp[ iRootLen - 1 ] )
				{
					//root path has the slash
					poInfo->m_csDisplayName = &pTemp[ iRootLen ];
				}
				else
				{
					//root path doesnt has the slash so add 1 to length
					poInfo->m_csDisplayName = &pTemp[ iRootLen + 1 ];
				}

			}
		}

		unsigned char * pu8ChoppedStr = new unsigned char[ poInfo->m_csDisplayName.GetLength() + 10 ];
		VxChopStr( (char *)(const char *) poInfo->m_csDisplayName, pu8ChoppedStr );
		if( poInfo->m_pu8ChoppedDisplayName )
		{
			delete poInfo->m_pu8ChoppedDisplayName;
		}
		poInfo->m_pu8ChoppedDisplayName = pu8ChoppedStr;
		LogChoppedString( pu8ChoppedStr );
		poInfo = &m_List[0];
		const char * pTemp = (const char *)poInfo->m_csDisplayName;
		
		iResolvedListIdx++;

	}
	m_List.SetSize( iResolvedListIdx );//remove any unused entries
	return 0;
}
//============================================================================
//! make array of packets with matching files
RCODE HostListMgr::MakeMatchList(	CPtrArray * paoRetListPkts, // return list of packets of file lists
									CString &	csMatchString,	// Search Match name
									uint16_t			u16FileTypes,	// types of files to match
									uint16_t			u16LimitType,	// file size limit type
									uint64_t			u64SizeLimit )	// file size limit
{	
	int i;
	RCODE rc = 0;

	PktShareFileList gPktList;
	long s32PktIdx = 0;
	unsigned long u32FileLen = 0;
	bool bFileOpen = false;
	FILE * pgFile = 0;
	CStringArray acsMatchTokens;
	bool bSendAll = false;
	ShareFileInfo * poInfo;

	if( 1 == csMatchString.GetLength() && 
		'*' == csMatchString[ 0 ] )
	{
		bSendAll = true; //send complete list
	}
	else
	{

		rc = ParseSearchString(	csMatchString,		//String of search tokens
							acsMatchTokens );	//return seperate token in each String
	}
	if( rc )
	{
		LogMsg( LOG_INFO, "HostListMgr::SendMatchList Error 0x%x occured parsing string\n", rc );
		ASSERT( false );
	}
	else
	{
		int	iCnt = m_List.GetSize();
		for( i = 0; i < iCnt; i++ )
		{
			poInfo = &m_List[ i ];
			if( 0 == ( u16FileTypes & poInfo->m_u32Flags ) )
			{
				//is not the file type we are searching for
				continue;
			}
			if( bSendAll ||
				Match( acsMatchTokens, poInfo->m_csDisplayName ) )
			{
				if( 0 == poInfo->m_s64FileLen )
				{
					LogMsg( LOG_INFO, "HostListMgr::Zero Length File %s\n", (const char *) poInfo->m_csDisplayName );
					continue;
				}
				//add file to PktFileList
				unsigned char * pu8Temp = poInfo->m_pu8ChoppedDisplayName;
				unsigned long u32ItemLen = * pu8Temp + sizeof( __int64 );
				if( gPktList.m_u16PktLen + u32ItemLen > sizeof( PktShareFileList ) )
				{
					//wont fit in this Pkt so store and start another
					gPktList.m_u16PktLen = (( gPktList.m_u16PktLen + 15 ) & ~15 );
					u32FileLen += gPktList.m_u16PktLen;
					
					paoRetListPkts->Add( gPktList.makeCopy() );

					gPktList.m_u16PktLen = gPktList.emptyLen();
					s32PktIdx = 0;
					gPktList.m_u16ListCnt = 0;
				}
				//copy file length first
				*( ( __int64 *)&gPktList.m_au8List[ s32PktIdx ] ) = poInfo->m_s64FileLen;
				//copy chopped string that has display name
				memcpy( &gPktList.m_au8List[ s32PktIdx + sizeof( __int64 ) ], poInfo->m_pu8ChoppedDisplayName, u32ItemLen - sizeof( __int64 ) );

				//show trace of file we added to list
				char as8Buf[ 256 * 2 ];
				VxUnchopStr( poInfo->m_pu8ChoppedDisplayName, as8Buf );
				LogMsg( LOG_INFO, "Added to PktFileList file size %d file %s\n", 
						*( ( unsigned long *)&gPktList.m_au8List[ s32PktIdx ] ),
						as8Buf );


				//increment vars for next item
				s32PktIdx += u32ItemLen;
				gPktList.m_u16ListCnt++;
				gPktList.m_u16PktLen += (unsigned short)u32ItemLen;
			}	
		}
	}
	gPktList.m_u16PktLen = (( gPktList.m_u16PktLen + 15 ) & ~15 );
	paoRetListPkts->Add( gPktList.makeCopy() );
 	return 0;
}
*/
