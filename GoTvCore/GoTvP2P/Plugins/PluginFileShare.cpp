//============================================================================
// Copyright (C) 2010 Brett R. Jones
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

#include "PluginFileShare.h"
#include "PluginMgr.h"
#include "SharedFileInfo.h"

#include "FileLibraryMgr.h"

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>
#include <GoTvInterface/IToGui.h>

#include <PktLib/PktsFileShare.h>
#include <PktLib/PktsPluginOffer.h>
#include <PktLib/VxSearchDefs.h>

#include <CoreLib/VxFileUtil.h>
#include <CoreLib/VxFileShredder.h>
#include <CoreLib/VxGlobals.h>

#ifdef _MSC_VER
# pragma warning(disable: 4355) //'this' : used in base member initializer list
#endif

//============================================================================
PluginFileShare::PluginFileShare( P2PEngine& engine, PluginMgr& pluginMgr, VxNetIdent * myIdent )
: PluginBase( engine, pluginMgr, myIdent ) 
, m_PluginSessionMgr( *this, pluginMgr)
, m_SharedFilesMgr( *this)
, m_FileLibraryMgr( *this, m_SharedFilesMgr )
, m_FileShareXferMgr( *this, m_SharedFilesMgr, m_FileLibraryMgr )
, m_FileShredder( GetVxFileShredder() )
{
	m_ePluginType = ePluginTypeFileServer;
}

//============================================================================
PluginFileShare::~PluginFileShare()
{
}

//============================================================================
void PluginFileShare::fromGuiUserLoggedOn( void )
{
	m_FileLibraryMgr.fromGuiUserLoggedOn();
	m_SharedFilesMgr.fromGuiUserLoggedOn();
	m_FileShareXferMgr.fromGuiUserLoggedOn();
}

//============================================================================
void PluginFileShare::fromGuiStartPluginSession( VxNetIdent * netIdent, int pvUserData, VxGUID lclSessionId )
{
	return m_FileShareXferMgr.fromGuiStartPluginSession( netIdent, pvUserData, lclSessionId );
}

//============================================================================
void PluginFileShare::fromGuiStopPluginSession( VxNetIdent * netIdent, int pvUserData, VxGUID lclSessionId)
{
	return m_FileShareXferMgr.fromGuiStopPluginSession( netIdent, pvUserData, lclSessionId );
}

//============================================================================
bool PluginFileShare::fromGuiIsPluginInSession( VxNetIdent * netIdent, int pvUserData, VxGUID lclSessionId )
{
	return m_FileShareXferMgr.fromGuiIsPluginInSession( netIdent, pvUserData, lclSessionId );
}

//============================================================================
void PluginFileShare::fromGuiGetFileShareSettings( FileShareSettings& fileShareSettings )
{
	m_FileShareXferMgr.fromGuiGetFileShareSettings( fileShareSettings );
}

//============================================================================
void PluginFileShare::fromGuiSetFileShareSettings( FileShareSettings& fileShareSettings )
{
	m_FileShareXferMgr.fromGuiSetFileShareSettings( fileShareSettings );
}

//============================================================================
void PluginFileShare::fromGuiCancelDownload( VxGUID& fileInstance )
{
	return m_FileShareXferMgr.fromGuiCancelDownload( fileInstance );
}

//============================================================================
void PluginFileShare::fromGuiCancelUpload( VxGUID& fileInstance )
{
	return m_FileShareXferMgr.fromGuiCancelUpload( fileInstance );
}

//============================================================================
bool PluginFileShare::fromGuiBrowseFiles( const char * dir, bool lookupShareStatus, uint8_t fileFilterMask )
{
	if( 0 == fileFilterMask )
	{
		fileFilterMask = VXFILE_TYPE_ALLNOTEXE | VXFILE_TYPE_DIRECTORY;
	}

	std::vector<VxFileInfo> fileList;
	RCODE rc = VxFileUtil::listFilesAndFolders( dir, fileList, fileFilterMask );
	if( rc )
	{
		LogMsg( LOG_ERROR, "PluginFileShare::fromGuiBrowseFiles error %d\n", rc );
		return false;
	}

	std::vector<VxFileInfo>::iterator iter;
	for( iter = fileList.begin(); iter != fileList.end(); ++iter )
	{
		VxFileInfo& fileInfo = *iter;
		if ( ( false == fileInfo.isExecutableFile() )
			&& ( false == fileInfo.isShortcutFile() ) )
		{
			if ( 0 != ( fileFilterMask & fileInfo.getFileType() ) )
			{
				LogMsg( LOG_INFO, "PluginFileShare::fromGuiBrowseFiles sending file %s\n", fileInfo.getFileName().c_str() );
				IToGui::getToGui().toGuiFileList(	fileInfo.getFileName().c_str(), 
					fileInfo.getFileLength(), 
					fileInfo.getFileType(), 
					isFileShared( fileInfo.getFileName() ),
					isFileInLibrary( fileInfo.getFileName() ),
					0 );
			}
			else
			{
				LogMsg( LOG_ERROR, "PluginFileShare::fromGuiBrowseFiles skip file type 0x%x because filter mask 0x%x file %s\n", fileInfo.getFileType(), fileFilterMask, fileInfo.getFileName().c_str() );
			}
		}
		else
		{
			if ( fileInfo.isExecutableFile() )
			{
				LogMsg( LOG_ERROR, "PluginFileShare::fromGuiBrowseFiles skip executeable file %s\n", fileInfo.getFileName().c_str() );
			}
			else
			{
				LogMsg( LOG_ERROR, "PluginFileShare::fromGuiBrowseFiles skip shortcut file %s\n", fileInfo.getFileName().c_str() );
			}
		}
	}

	IToGui::getToGui().toGuiFileList( "", 0, 0, false, false );
	return isPluginEnabled();
}

//============================================================================
bool PluginFileShare::fromGuiGetSharedFiles( uint8_t fileTypeFilter )
{
	m_SharedFilesMgr.fromGuiGetSharedFiles( fileTypeFilter );
	return isPluginEnabled();
}

//============================================================================
bool PluginFileShare::fromGuiSetFileIsShared(	const char * fileName, bool isShared, uint8_t * fileHashId )
{
	return m_SharedFilesMgr.fromGuiSetFileIsShared( fileName, isShared, fileHashId );
}

//============================================================================
bool PluginFileShare::fromGuiGetIsFileShared( const char * fileName )
{
	std::string strFileName = fileName;
	return isFileShared( strFileName );
}

//============================================================================
// returns -1 if unknown else percent downloaded
int PluginFileShare::fromGuiGetFileDownloadState( uint8_t * fileHashId )
{
	return -1;
	int result = m_FileLibraryMgr.fromGuiGetFileDownloadState( fileHashId );
	if( -1 == result )
	{
		result = m_FileShareXferMgr.fromGuiGetFileDownloadState( fileHashId );
	}

	return result;
}

//============================================================================
bool PluginFileShare::fromGuiAddFileToLibrary( const char * fileName, bool addFile, uint8_t * fileHashId )
{
	return m_FileLibraryMgr.fromGuiAddFileToLibrary( fileName, addFile, fileHashId );
}

//============================================================================
void PluginFileShare::fromGuiGetFileLibraryList( uint8_t fileTypeFilter )
{
	m_FileLibraryMgr.fromGuiGetFileLibraryList(	fileTypeFilter );
	m_SharedFilesMgr.fromGuiGetSharedFiles( fileTypeFilter );
}

//============================================================================
bool PluginFileShare::fromGuiGetIsFileInLibrary( const char * fileName )
{
	std::string strFileName = fileName;
	return isFileInLibrary( strFileName );
}

//============================================================================
bool PluginFileShare::isFileShared( std::string& fileName )
{
	return m_SharedFilesMgr.isFileShared( fileName );
}

//============================================================================
bool PluginFileShare::isFileInLibrary( std::string& fileName )
{
	return m_FileLibraryMgr.isFileInLibrary( fileName );
}

//============================================================================
bool PluginFileShare::isServingFiles( void )
{
	return ( m_MyIdent->hasSharedFiles() && isPluginEnabled() );
}

//============================================================================
void PluginFileShare::deleteFile( const char * fileName, bool shredFile )
{
	std::string strFileName = fileName;
	m_FileShareXferMgr.fileAboutToBeDeleted( strFileName );
	m_SharedFilesMgr.fromGuiSetFileIsShared( strFileName, false );
	m_FileLibraryMgr.removeFromLibrary( strFileName );
	if( shredFile )
	{
		m_FileShredder.shredFile( strFileName );
	}
	else
	{
		VxFileUtil::deleteFile( strFileName.c_str() );	
	}
}

//============================================================================
void PluginFileShare::onSharedFilesUpdated( uint16_t u16FileTypes )
{
	if( m_MyIdent->getSharedFileTypes() != u16FileTypes )
	{
		m_MyIdent->setSharedFileTypes( (uint8_t)u16FileTypes );
		m_Engine.doPktAnnHasChanged( false );
	}
}

//============================================================================
//! user wants to send offer to friend.. return false if cannot connect
bool PluginFileShare::fromGuiMakePluginOffer(	VxNetIdent *	netIdent,		
												int				pvUserData,
												const char *	pOfferMsg,		
												const char *	pFileName,
												uint8_t *			fileHashId,
												VxGUID			lclSessionId )		
{
	return m_FileShareXferMgr.fromGuiMakePluginOffer(	netIdent,		
														pvUserData,
														pOfferMsg,		
														pFileName,
														fileHashId,
														lclSessionId );
}

//============================================================================
int PluginFileShare::fromGuiPluginControl(	VxNetIdent *	netIdent,
											const char *	pControl, 
											const char *	pAction,
											uint32_t				u32ActionData,
											VxGUID&			lclSessionId,
											uint8_t *			fileHashId )
{
	return m_FileShareXferMgr.fromGuiPluginControl(		netIdent,		
														pControl, 
														pAction,
														u32ActionData,
														lclSessionId,
														fileHashId );
}

//============================================================================
void PluginFileShare::onPktPluginOfferReq( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileShareXferMgr.onPktPluginOfferReq( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileShare::onPktFileGetReq( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileShareXferMgr.onPktFileGetReq( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileShare::onPktFileGetReply( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileShareXferMgr.onPktFileGetReply( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileShare::onPktFileSendReq( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileShareXferMgr.onPktFileSendReq( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileShare::onPktFileSendReply( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileShareXferMgr.onPktFileSendReply( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileShare::onPktFileChunkReq( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileShareXferMgr.onPktFileChunkReq( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileShare::onPktFileChunkReply( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileShareXferMgr.onPktFileChunkReply( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileShare::onPktFileGetCompleteReq( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileShareXferMgr.onPktFileGetCompleteReq( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileShare::onPktFileGetCompleteReply( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileShareXferMgr.onPktFileGetCompleteReply( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileShare::onPktFileSendCompleteReq( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileShareXferMgr.onPktFileGetCompleteReq( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileShare::onPktFileSendCompleteReply( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileShareXferMgr.onPktFileGetCompleteReply( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileShare::onPktFindFileReq( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileShareXferMgr.onPktFindFileReq( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileShare::onPktFindFileReply( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileShareXferMgr.onPktFindFileReply( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileShare::onPktFileListReq( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileShareXferMgr.onPktFileListReq( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileShare::onPktFileListReply( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileShareXferMgr.onPktFileListReply( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileShare::onPktFileShareErr( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	//m_FileShareXferMgr.onPktFileShareErr( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileShare::replaceConnection( VxNetIdent * netIdent, VxSktBase * poOldSkt, VxSktBase * poNewSkt )
{
	m_PluginSessionMgr.replaceConnection( netIdent, poOldSkt, poNewSkt );
}

//============================================================================
void PluginFileShare::onConnectionLost( VxSktBase * sktBase )
{
	m_PluginSessionMgr.onConnectionLost( sktBase );
}

//============================================================================
void PluginFileShare::onContactWentOffline( VxNetIdent * netIdent, VxSktBase * sktBase )
{
	m_PluginSessionMgr.onContactWentOffline( netIdent, sktBase );
}
