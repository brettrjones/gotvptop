/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

// some of this code is copied from Kodi


#include "IAndroid.h"
#ifdef TARGET_OS_ANDROID

#include "GoTvInterface/IGoTv.h" 


#include "CompileInfo.h"
#include "threads/Thread.h"
#include "threads/platform/win/Win32Exception.h"
#include "platform/win32/CharsetConverter.h"
#include "platform/xbmc.h"
#include "settings/AdvancedSettings.h"
#include "utils/CPUInfo.h"
#include "platform/Environment.h"
#include "utils/CharsetConverter.h" // Required to initialize converters before usage


#include <dbghelp.h>
#include <mmsystem.h>
#include <Objbase.h>
#include <shellapi.h>
#include <WinSock2.h>


#include "filesystem/Directory.h"
#include "filesystem/SpecialProtocol.h"
#include "utils/log.h"
#include "utils/URIUtils.h"
#include "GoTvCoreUtil.h"
#include "platform/win32/WIN32Util.h"



using namespace XFILE;



IAndroid::IAndroid( IGoTv& gotv )
    : OsInterface( gotv )
    , m_AppRunningMutex( 0 )
{
}

//=== stages of create ===//
//============================================================================
bool IAndroid::doPreStartup()
{
     // Initialize before CAppParamParser so it can set the log level
    g_advancedSettings.Initialize();
    return true;
}

bool IAndroid::doStartup()
{
    return true;
}

//=== stages of run ===//
//============================================================================

//bool  IAndroid::doRun()

//=== stages of destroy ===//
//============================================================================
void IAndroid::doPreShutdown( )
{


}

void IAndroid::doShutdown( )
{
}

//=== utilities ===//
//============================================================================

bool IAndroid::initDirectories()
{
    /*
       The following is the directory mapping for Platform Specific Mode:

       special://xbmc/          => [read-only] system directory (/usr/share/kodi)
       special://home/          => [read-write] user's directory that will override special://kodi/ system-wide
                                   installations like skins, screensavers, etc.
                                   ($HOME/.kodi)
                                   NOTE: XBMC will look in both special://xbmc/addons and special://home/addons for addons.
       special://masterprofile/ => [read-write] userdata of master profile. It will by default be
                                   mapped to special://home/userdata ($HOME/.kodi/userdata)
       special://profile/       => [read-write] current profile's userdata directory.
                                   Generally special://masterprofile for the master profile or
                                   special://masterprofile/profiles/<profile_name> for other profiles.

       NOTE: All these root directories are lowercase. Some of the sub-directories
             might be mixed case.
    */

#if defined(TARGET_POSIX) && !defined(TARGET_DARWIN)
    std::string userName;
    if( getenv( "USER" ) )
        userName = getenv( "USER" );
    else
        userName = "root";

    std::string userHome;
    if( getenv( "HOME" ) )
        userHome = getenv( "HOME" );
    else
        userHome = "/root";

    std::string binaddonAltDir;
    if( getenv( CCompileInfo::GetBinHomeEnvName() ) )
        binaddonAltDir = getenv( CCompileInfo::GetBinAddonEnvName() );

    std::string appPath;
    std::string appName = CCompileInfo::GetAppName();
    std::string dotLowerAppName = "." + appName;
    StringUtils::ToLower( dotLowerAppName );
    const char* envAppHome = CCompileInfo::GetHomeEnvName();
    const char* envAppBinHome = CCompileInfo::GetBinHomeEnvName();
    const char* envAppTemp = CCompileInfo::GetTempEnvName();

    auto appBinPath = CUtil::GetHomePath( envAppBinHome );
    // overridden by user
    if( getenv( envAppHome ) )
        appPath = getenv( envAppHome );
    else
    {
        // use build time default
        appPath = INSTALL_PATH;
        /* Check if binaries and arch independent data files are being kept in
         * separate locations. */
        if( !CDirectory::Exists( URIUtils::AddFileToFolder( appPath, "userdata" ) ) )
        {
            /* Attempt to locate arch independent data files. */
            appPath = CUtil::GetHomePath( appBinPath );
            if( !CDirectory::Exists( URIUtils::AddFileToFolder( appPath, "userdata" ) ) )
            {
                fprintf( stderr, "Unable to find path to %s data files!\n", appName.c_str() );
                exit( 1 );
            }
        }
    }

    /* Set some environment variables */
    setenv( envAppBinHome, appBinPath.c_str(), 0 );
    setenv( envAppHome, appPath.c_str(), 0 );

    if( m_bPlatformDirectories )
    {
        // map our special drives
        CSpecialProtocol::SetXBMCBinPath( appBinPath );
        CSpecialProtocol::SetXBMCAltBinAddonPath( binaddonAltDir );
        CSpecialProtocol::SetXBMCPath( appPath );
        CSpecialProtocol::SetHomePath( userHome + "/" + dotLowerAppName );
        CSpecialProtocol::SetMasterProfilePath( userHome + "/" + dotLowerAppName + "/userdata" );

        // For P2P
        CSpecialProtocol::SetAppDataPath( userHome + "/" + dotLowerAppName + "/appdata" );
        CSpecialProtocol::SetAppAssetsPath( userHome + "/" + dotLowerAppName + "/appassets" );
        CSpecialProtocol::SetAccountsPath( userHome + "/" + dotLowerAppName + "/accounts" );
        CSpecialProtocol::SetUserXferPath( userHome + "/" + dotLowerAppName + "/userxfer" );
        CSpecialProtocol::SetUserGroupPath( userHome + "/" + dotLowerAppName + "/usergroup" );

        std::string strTempPath = userHome;
        strTempPath = URIUtils::AddFileToFolder( strTempPath, dotLowerAppName + "/temp" );
        if( getenv( envAppTemp ) )
            strTempPath = getenv( envAppTemp );
        CSpecialProtocol::SetTempPath( strTempPath );
        CSpecialProtocol::SetLogPath( strTempPath );

        CreateUserDirs();

    }
    else
    {
        URIUtils::AddSlashAtEnd( appPath );

        CSpecialProtocol::SetXBMCBinPath( appBinPath );
        CSpecialProtocol::SetXBMCAltBinAddonPath( binaddonAltDir );
        CSpecialProtocol::SetXBMCPath( appPath );
        CSpecialProtocol::SetHomePath( URIUtils::AddFileToFolder( appPath, "portable_data" ) );
        CSpecialProtocol::SetMasterProfilePath( URIUtils::AddFileToFolder( appPath, "portable_data/userdata" ) );

        // For P2P
        CSpecialProtocol::SetAppDataPath( URIUtils::AddFileToFolder( appPath, "portable_data/appdata" );
        CSpecialProtocol::SetAppAssetsPath( URIUtils::AddFileToFolder( appPath, "portable_data/appassets" );
        CSpecialProtocol::SetAccountsPath( URIUtils::AddFileToFolder( appPath, "portable_data/accounts" );
        CSpecialProtocol::SetUserXferPath( URIUtils::AddFileToFolder( appPath, "portable_data/userxfer" );
        CSpecialProtocol::SetUserGroupPath( URIUtils::AddFileToFolder( appPath, "portable_data/usergroup" );

        std::string strTempPath = appPath;
        strTempPath = URIUtils::AddFileToFolder( strTempPath, "portable_data/temp" );
        if( getenv( envAppTemp ) )
            strTempPath = getenv( envAppTemp );
        CSpecialProtocol::SetTempPath( strTempPath );
        CSpecialProtocol::SetLogPath( strTempPath );
        CreateUserDirs();
    }
    CSpecialProtocol::SetXBMCBinAddonPath( appBinPath + "/addons" );

    //#if defined(TARGET_ANDROID)
    //    CXBMCApp::InitDirectories();
    //#endif

    return true;
#else
    return false;
#endif
}


#endif // TARGET_OS_ANDROID
