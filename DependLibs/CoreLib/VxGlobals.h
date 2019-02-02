#pragma once
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

#include "VxTime.h" // time stamp and other time functions
#include <string>

#define DEFAULT_ONLINE_LISTEN_PORT		45654
#define DEFAULT_GUEST_UDP_PORT			45653

class VxGUID;

//============================================================================
void			            VxSetAppIsShuttingDown( bool bIsShuttingDown );
bool			            VxIsAppShuttingDown( void );

const char *	            VxGetCompanyDomain( void );
const char *	            VxGetCompanyWebsite( void );

void			            VxSetApplicationName( const char * pAppName );
const char *	            VxGetApplicationName( void );
void			            VxSetApplicationNameNoSpaces( const char * pAppName );
const char *	            VxGetApplicationNameNoSpaces( void );
void			            VxSetIsApplicationCommercial( bool isCommercial );
bool			            VxGetIsApplicationCommercial( void );

void			            VxSetAppVersion( uint16_t u16AppVersion );
uint16_t				    VxGetAppVersion( void );
const char *	            VxGetAppVersionString( void );

//============================================================================
void			            VxSetAssetsDirectory( const char * assetsDir  );
std::string&	            VxGetAssetsDirectory( void );

void			            VxSetRootDataDirectory( const char * rootDataDir );
std::string&	            VxGetRootDataDirectory( void );
std::string&	            VxGetAppDataDirectory( void );
std::string&	            VxGetKodiDataDirectory( void );

void			            VxSetUserSpecificDataDirectory( const char * userDataDir  );
std::string&	            VxGetUserSpecificDataDirectory( void  );
std::string&	            VxGetSettingsDirectory( void );
std::string&	            VxGetUserProfileDirectory( void );

// storyboard is same as profile directory
//std::string&	VxGetStoryboardDirectory( void );

void			            VxSetRootXferDirectory( const char * rootXferDir  );
std::string&	            VxGetRootXferDirectory( void ) ;

void			            VxSetUserXferDirectory( const char * userXferDir  );
std::string&	            VxGetUserXferDirectory( void  );
std::string&	            VxGetDownloadsDirectory( void );
std::string&	            VxGetUploadsDirectory( void );
std::string&	            VxGetIncompleteDirectory( void );
std::string&	            VxGetPersonalRecordDirectory( void );

void			            VxSetAppTempDirectory(const char * assetsDir);
std::string&	            VxGetAppTempDirectory( void );
//============================================================================
//=== miscellaneous ===//
//============================================================================
void			VxSetNetworkLoopbackAllowed( bool bIsLoopbackAllowed );
bool			VxIsNetworkLoopbackAllowed( void );

uint16_t		VxGetP2PDefaultTcpPort();
uint16_t		VxGetP2PDefaultUdpPort();

void			VxSetDebugEnable( bool enableDebug );
bool			VxIsDebugEnabled( void );

int 			VxGlobalAccessLock( void );
int 			VxGlobalAccessUnlock( void );

void			VxSetMyOnlineId( VxGUID& onlineId );
const VxGUID&	VxGetMyOnlineId( void );

void			VxSetLclIpAddress( const char * lclIpAddress );
std::string		VxGetLclIpAddress( void );
