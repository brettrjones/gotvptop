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
#include "HostListInfo.h"

#include <PktLib/VxSearchDefs.h>

#include <CoreLib/VxFileLists.h>
#include <CoreLib/VxFileIsTypeFunctions.h>
#include <CoreLib/VxFileUtil.h>
#include <CoreLib/VxDebug.h>
#include <CoreLib/VxGlobals.h>

#include <sys/types.h>
#include <sys/stat.h>

//============================================================================
HostListInfo::HostListInfo()
: m_HostListName( "" )
, m_HostListTag( "" )
, m_s64HostListLen( 0 )
, m_u16HostListType( VXFILE_TYPE_UNKNOWN )
, m_LocationFlags( 0 )
, m_HostListSendState( eHostListSendStateNone )
, m_CreationTime( 0 )
, m_PlayPosition0to100000( 0 )
{ 
}

//============================================================================
HostListInfo::HostListInfo( const HostListInfo& rhs )
{
	*this = rhs;
}

//============================================================================
HostListInfo::HostListInfo( const std::string& fileName )
: m_HostListName( fileName )
, m_HostListTag( "" )
, m_s64HostListLen(0)
, m_u16HostListType(VXFILE_TYPE_UNKNOWN)
, m_LocationFlags( 0 )
, m_HostListSendState( eHostListSendStateNone )
, m_CreationTime( 0 )
, m_PlayPosition0to100000( 0 )
{ 
}

//============================================================================
HostListInfo::HostListInfo( const char * fileName, uint64_t fileLen, uint16_t assetType )
: m_HostListName( fileName )
, m_HostListTag( "" )
, m_s64HostListLen( fileLen )
, m_u16HostListType( assetType )
, m_LocationFlags( 0 )
, m_HostListSendState( eHostListSendStateNone )
, m_CreationTime( GetTimeStampMs() )
, m_PlayPosition0to100000( 0 )
{
}

//============================================================================
HostListInfo& HostListInfo::operator=( const HostListInfo& rhs ) 
{	
	if( this != &rhs )
	{
		m_HostListName					= rhs.m_HostListName;
		m_UniqueId					= rhs.m_UniqueId;
		m_CreatorId					= rhs.m_CreatorId;
		m_HistoryId					= rhs.m_HistoryId; 
		m_HostListHash					= rhs.m_HostListHash;
		m_s64HostListLen				= rhs.m_s64HostListLen;
		m_u16HostListType				= rhs.m_u16HostListType;
		m_LocationFlags				= rhs.m_LocationFlags;
		m_CreationTime				= rhs.m_CreationTime;
		m_HostListTag					= rhs.m_HostListTag;
		m_HostListSendState			= rhs.m_HostListSendState;
        m_PlayPosition0to100000     = rhs.m_PlayPosition0to100000;
	}

	return *this;
}

//============================================================================
bool HostListInfo::isValid( void )
{
	return ( VXFILE_TYPE_UNKNOWN != m_u16HostListType );
}

//============================================================================
bool HostListInfo::isMine( void )
{
	return isValid() && ( m_CreatorId == VxGetMyOnlineId() );
}

//============================================================================
// generates unique id, assigns it to asset and returns reference to it
VxGUID& HostListInfo::generateNewUniqueId( void )
{
	VxGUID::generateNewVxGUID( m_UniqueId );
	return m_UniqueId;
}

//============================================================================
bool HostListInfo::getIsFileHostList( void )
{
	return (0 != (m_u16HostListType & ( eHostListTypePhoto | eHostListTypeAudio | eHostListTypeVideo | eHostListTypeDocument | eHostListTypeArchives | eHostListTypeExe | eHostListTypeOtherFiles	)) );
}

//============================================================================
bool HostListInfo::hasFileName( void )
{
	return ( 0 != m_HostListName.length() ) && getIsFileHostList();
}

//============================================================================
bool HostListInfo::needsHashGenerated( void )
{
	if( ( false == m_HostListHash.isHashValid() )
		&& hasFileName() )
	{
		return true;
	}

	return false;
}

//============================================================================
bool HostListInfo::isDirectory( void )
{
	return ( VXFILE_TYPE_DIRECTORY & m_u16HostListType ) ? true : false;
}

//============================================================================
void HostListInfo::setHostListName( const char * assetName )
{
	if (assetName)
		m_HostListName = assetName;
	else
		m_HostListName = "";
}

//============================================================================
void HostListInfo::setHostListTag( const char * assetTag )
{
	if( assetTag )
		m_HostListTag = assetTag;
	else
		m_HostListTag = "";
}

//============================================================================
std::string HostListInfo::getRemoteHostListName( void )
{
	std::string rmtHostListName("");
	std::string 	assetPath;
	RCODE rc = VxFileUtil::seperatePathAndFile(	getHostListName(),					
		assetPath,		
		rmtHostListName );	
	if( 0 != rc )
	{
		LogMsg( LOG_ERROR, "HostListInfo::getRemoteHostListName failed error %d asset %s\n", rc, getHostListName().c_str() );
	}

	return rmtHostListName;
}

//============================================================================
const char * HostListInfo::getDefaultFileExtension( EHostListType assetType )
{
	const char * extension = ".txt";
	switch( assetType )
	{
	case eHostListTypePhoto:
		extension = ".jpg";
		break;

	case eHostListTypeAudio:
		extension = ".opus";
		break;

	case eHostListTypeVideo:
		extension = ".avi";
		break;

	default:
		break;
	}

	return extension;
}

//============================================================================
const char * HostListInfo::getSubDirectoryName( EHostListType assetType )
{
	const char * subDir = "asset/";
	switch( assetType )
	{
	case eHostListTypeDocument:
		subDir = "documents/";
		break;

	case eHostListTypeArchives:
		subDir = "archives/";
		break;

	case eHostListTypeOtherFiles:
		subDir = "other_files/";
		break;

	case eHostListTypePhoto:
		subDir = "photos/";
		break;

	case eHostListTypeAudio:
		subDir = "audio/";
		break;

	case eHostListTypeVideo:
		subDir = "video/";
		break;

	default:
		break;
	}

	return subDir;
}

//============================================================================
void HostListInfo::updateHostListInfo( VxThread * callingThread )
{
	return;
}
