//============================================================================
// Copyright (C) 2013 Brett R. Jones
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
#include "config_corelib.h"

#include "VxGlobals.h"
#include "VxFileUtil.h"
#include "VxMutex.h"
#include "VxFileShredder.h"
#include "VxGUID.h"

#include <time.h>
#include <string>
#include <stdio.h>

#ifndef TARGET_OS_WINDOWS
    #include <sys/time.h>
#endif // TARGET_OS_WINDOWS

//============================================================================
// globals
//============================================================================
//int32_t						g_s32GmtTimeOffs	= 0;		// offset in seconds to turn local time to gmt time

namespace
{
	VxMutex				g_GlobalAccessMutex;

	uint16_t			g_u16AppVersion					= 0x104;
#ifdef DEBUG
    std::string			g_strApplicationName			= "GoTv PtoP Test App";
    std::string			g_strApplicationNameNoSpaces	= "GoTvPtoPTestApp";
    std::string			g_strNetworkName				= "GoTvPtoPTestNet";
	std::string			g_strCompanyWebsite				= "http://www.gotvptop.net";
	std::string			g_strCompanyDomain				= "www.gotvptop.net";
	bool				g_IsAppCommercial				= false;
#else
    std::string			g_strApplicationName			= "GoTv PtoP";
    std::string			g_strApplicationNameNoSpaces	= "GoTvPtoP";
    std::string			g_strNetworkName				= "GoTvPtoPNet";
	std::string			g_strCompanyWebsite				= "http://www.gotvptop.net";
	std::string			g_strCompanyDomain				= "www.gotvptop.net";
	bool				g_IsAppCommercial				= false;
#endif // APP_MYP2PWEB

	std::string			g_strRootXferDir				= "";
	std::string			g_strRootDataDir				= "";
    std::string			g_strUserProfileDir             = "";
	std::string			g_strAppDataDir					= "";
    std::string			g_strKodiDataDir				= "";
    std::string			g_strSettingsDir				= "";
	std::string			g_strAssetsDir					= "";

	std::string			g_strUploadsDir					= "";
	std::string			g_strDownloadsDir				= "";
	std::string			g_strIncompleteDir				= "";
	std::string			g_strPersonalRecordDir			= "";

	std::string			g_strUserSpecificDataDir		= "";
	std::string			g_strUserXferDir				= "";
	std::string			g_strAppTempDir					= "";

	bool				g_bIsAppShuttingDown			= false;
	bool				g_bIsNetLoopbackAllowed			= false;
	bool				g_bIsDebugEnabled				= true;
	VxGUID				g_MyOnlineId;
	std::string			g_LclIpAddress					= "";
}

// directory structure on disk
// /storage/GoTvPtoP/appdata/ShredFilesDb.db3 and app generated files
//                  /kodidata/ kodi plugins and writable data directory
//                  /appassets/gui/ gui assets
//                            /shaders/ opengl shaders
//                            /profile/ profile default files
// user specific directories
//                  /accounts/userId/settings/ databases
//                  /accounts/userId/profile/ profile and story board user web pages
// user xfer directories         
//                  /userdata/userId/downloads
//                                  /uploads
//                                  /incomplete
//                                  /me/			personal recordings
//                                  /contacts/	contact assets

//============================================================================
void VxSetAppIsShuttingDown( bool bIsShuttingDown )
{
	g_bIsAppShuttingDown = bIsShuttingDown;
}

//============================================================================
bool VxIsAppShuttingDown( void )
{
	return g_bIsAppShuttingDown;
}

//============================================================================
void VxSetMyOnlineId( VxGUID& onlineId )
{
	g_MyOnlineId = onlineId;
}

//============================================================================
const VxGUID& VxGetMyOnlineId( void )
{
	return g_MyOnlineId;
}


//============================================================================
void VxSetLclIpAddress( const char * lclIpAddress )
{
	if( 0 != lclIpAddress )
	{
		g_LclIpAddress = lclIpAddress;
	}
	else
	{
		g_LclIpAddress = "";
	}
}

//============================================================================
std::string VxGetLclIpAddress( void )
{
	return g_LclIpAddress;
}

//============================================================================
const char * VxGetCompanyDomain( void )
{
	return g_strCompanyDomain.c_str();
}

//============================================================================
const char * VxGetCompanyWebsite( void )
{
	return g_strCompanyWebsite.c_str();
}

//============================================================================
//! set application name
void VxSetApplicationName( const char * pAppName )
{
	g_strApplicationName = pAppName;
}

//============================================================================
const char * VxGetApplicationName( void )
{
	return g_strApplicationName.c_str();
}

//============================================================================
//! set application name
void VxSetApplicationNameNoSpaces( const char * pAppName )
{
	g_strApplicationNameNoSpaces = pAppName;
}

//============================================================================
const char * VxGetApplicationNameNoSpaces( void )
{
	return g_strApplicationNameNoSpaces.c_str();
}

//============================================================================
void VxSetAppVersion( uint16_t u16AppVersion )
{
	g_u16AppVersion = u16AppVersion;
}

//============================================================================
uint16_t VxGetAppVersion( void )
{
	return g_u16AppVersion;
}

//============================================================================
const char * VxGetAppVersionString( void )
{
	static std::string strAppVersion;
	static bool isSet = false;
	if( false == isSet )
	{
		uint32_t u16AppVersion = VxGetAppVersion();
		char as8Buf[32];
		sprintf( as8Buf, "%d.%d",
			(u16AppVersion & 0xff00) >> 8,
			(u16AppVersion & 0x00ff)
			);
		strAppVersion = as8Buf;
	}

	return strAppVersion.c_str();
}

//============================================================================
void VxSetIsApplicationCommercial( bool isCommercial )
{
	g_IsAppCommercial = isCommercial;
}

//============================================================================
bool VxGetIsApplicationCommercial( void )
{
	return g_IsAppCommercial;
}

//============================================================================
void VxSetDebugEnable( bool enableDebug )
{
	g_bIsDebugEnabled = enableDebug;
}

//============================================================================
bool VxIsDebugEnabled( void )
{
	#ifndef	_DEBUG
		return false; // dont do logging in release mode
	#endif //	_DEBUG

	return g_bIsDebugEnabled;
}


//============================================================================
//=== miscellaneous ===//
//============================================================================

//============================================================================
const char * VxGetP2PNetworkName()
{
	return g_strNetworkName.c_str();
}

//============================================================================
void VxSetP2PNetworkName( const char * pNetName )
{
	g_strNetworkName = pNetName;
}

//============================================================================
//! set true if loop back is allowed ( default is false )
void VxSetNetworkLoopbackAllowed( bool bIsLoopbackAllowed )
{
	g_bIsNetLoopbackAllowed = bIsLoopbackAllowed;
}

//============================================================================
//! return true if loop back is allowed
bool VxIsNetworkLoopbackAllowed( void )
{
	return g_bIsNetLoopbackAllowed;
}

//============================================================================
//=== directories ===//
//============================================================================

//============================================================================
void VxSetAssetsDirectory( const char * assetsDir  )
{ 
	g_strAssetsDir = assetsDir;
	VxFileUtil::makeDirectory( assetsDir );
}

//============================================================================
std::string& VxGetAssetsDirectory( void ) 
{ 
	return g_strAssetsDir; 
}

//============================================================================
void VxSetRootDataDirectory( const char * rootDataDir  )
{ 
	g_strRootDataDir	= rootDataDir; 
	VxFileUtil::makeDirectory( rootDataDir );

	g_strAppTempDir		= g_strRootDataDir + "temp/";
	VxFileUtil::makeDirectory(g_strAppTempDir.c_str());

    g_strAppDataDir		= g_strRootDataDir + "appdata/";
	VxFileUtil::makeDirectory( g_strAppDataDir.c_str() );

    g_strKodiDataDir		= g_strRootDataDir + "kodidata/";
    VxFileUtil::makeDirectory( g_strKodiDataDir.c_str() );

	GetVxFileShredder().initShredder( g_strAppDataDir );
}

//============================================================================
std::string& VxGetRootDataDirectory( void )
{
	return g_strRootDataDir; 
}

//============================================================================
std::string& VxGetAppDataDirectory( void )
{
	return g_strAppDataDir; 
}

//============================================================================
void VxSetUserSpecificDataDirectory( const char * userDataDir  )
{ 
	g_strUserSpecificDataDir = userDataDir;
	VxFileUtil::makeDirectory( userDataDir );

	g_strSettingsDir = g_strUserSpecificDataDir + "settings/";
	VxFileUtil::makeDirectory( g_strSettingsDir.c_str() );

    g_strUserProfileDir = g_strUserSpecificDataDir + "profile/";
    VxFileUtil::makeDirectory( g_strUserProfileDir.c_str() );
}

//============================================================================
std::string& VxGetUserSpecificDataDirectory( void )
{
	return g_strUserSpecificDataDir; 
}

//============================================================================
std::string& VxGetSettingsDirectory( void ) 
{ 
	return g_strSettingsDir; 
}

//============================================================================
std::string& VxGetUserProfileDirectory( void )
{ 
    return g_strUserProfileDir;
}

//============================================================================
void VxSetRootXferDirectory( const char * rootXferDir  )
{ 
	g_strRootXferDir = rootXferDir; 
}

//============================================================================
std::string& VxGetRootXferDirectory( void ) 
{ 
	return g_strRootXferDir; 
}

//============================================================================
void VxSetUserXferDirectory( const char * userXferDir  )
{
	g_strUserXferDir		= userXferDir;
	VxFileUtil::makeDirectory( g_strUserXferDir.c_str() );

	g_strDownloadsDir		= g_strUserXferDir + "downloads/";
	VxFileUtil::makeDirectory( g_strDownloadsDir.c_str() );

	g_strUploadsDir			= g_strUserXferDir + "uploads/";
	VxFileUtil::makeDirectory( g_strUploadsDir.c_str() );

	g_strIncompleteDir		= g_strUserXferDir + "incomplete/";
	VxFileUtil::makeDirectory( g_strIncompleteDir.c_str() );

	g_strPersonalRecordDir	= g_strUserXferDir + "me/";
	VxFileUtil::makeDirectory( g_strPersonalRecordDir.c_str() );
}

//============================================================================
std::string& VxGetUserXferDirectory( void  )
{
	return g_strUserXferDir;
}

//============================================================================
std::string& VxGetDownloadsDirectory( void ) 
{ 
	return g_strDownloadsDir; 
}

//============================================================================
std::string& VxGetUploadsDirectory( void ) 
{ 
	return g_strUploadsDir; 
}

//============================================================================
std::string& VxGetIncompleteDirectory( void ) 
{ 
	return g_strIncompleteDir; 
}

//============================================================================
std::string& VxGetPersonalRecordDirectory( void )
{
	return g_strPersonalRecordDir; 
}

//============================================================================
void VxSetAppTempDir(std::string strDir)
{
	g_strAppTempDir = strDir;
	VxFileUtil::makeDirectory( g_strAppTempDir.c_str() );
}

//============================================================================
std::string VxGetAppTempDir(void)
{
	return g_strAppTempDir;
}

//============================================================================
int VxGlobalAccessLock( void )
{
	return g_GlobalAccessMutex.lock();
}

//============================================================================
int VxGlobalAccessUnlock( void )
{
	return g_GlobalAccessMutex.unlock();
}
