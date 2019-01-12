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


#include "ILinux.h"
#ifdef TARGET_OS_LINUX
#include "GoTvInterface/IGoTv.h" 


#include "CompileInfo.h"
#include "threads/Thread.h"
#include "platform/xbmc.h"
#include "settings/AdvancedSettings.h"
#include "utils/CPUInfo.h"
#include "platform/Environment.h"
#include "utils/CharsetConverter.h" // Required to initialize converters before usage

#include "filesystem/Directory.h"
#include "filesystem/SpecialProtocol.h"
#include "utils/log.h"
#include "utils/URIUtils.h"
#include "GoTvCoreUtil.h"



using namespace XFILE;


//============================================================================
ILinux::ILinux( IGoTv& gotv )
    : OsInterface( gotv )
{
}

//=== stages of create ===//
//============================================================================
bool ILinux::doPreStartup()
{
    // this fixes crash if OPENSSL_CONF is set to existed openssl.cfg  
    // need to set it as soon as possible  
    CEnvironment::unsetenv( "OPENSSL_CONF" );
    //g_advancedSettings.Initialize();
    return true;
}

bool ILinux::doStartup()
{
    return true;
}

//=== stages of run ===//
//============================================================================

//bool  IWin32::doRun()

//=== stages of destroy ===//
//============================================================================
void ILinux::doPreShutdown( )
{


}

void ILinux::doShutdown( )
{

    // clear previously set timer resolution
//    timeEndPeriod( 1 );

}

//=== utilities ===//
//============================================================================

bool ILinux::initDirectories()
{
#ifdef TARGET_WINDOWS
    std::string xbmcPath = CUtil::GetHomePath(); //F:/GoTvCode/bin/Resources /xbmc or /gotvptop
    //std::string xbmcPath = CUtil::GetExecutablePath();

    CEnvironment::setenv( CCompileInfo::GetHomeEnvName(), xbmcPath );
    CSpecialProtocol::SetXBMCBinPath( xbmcPath );
    CSpecialProtocol::SetXBMCPath( xbmcPath );
    CSpecialProtocol::SetXBMCBinAddonPath( xbmcPath + "/addons" );

    std::string strWin32UserFolder = CWIN32Util::GetProfilePath();
    CSpecialProtocol::SetLogPath( strWin32UserFolder );
    CSpecialProtocol::SetHomePath( strWin32UserFolder );
    CSpecialProtocol::SetMasterProfilePath( URIUtils::AddFileToFolder( strWin32UserFolder, "userdata" ) );
    CSpecialProtocol::SetTempPath( URIUtils::AddFileToFolder( strWin32UserFolder, "cache" ) );

    // For P2P
    CSpecialProtocol::SetAppDataPath( URIUtils::AddFileToFolder( strWin32UserFolder, "appdata" ) );
    CSpecialProtocol::SetAppAssetsPath( URIUtils::AddFileToFolder( strWin32UserFolder, "appassets" ) );
    CSpecialProtocol::SetAccountsPath( URIUtils::AddFileToFolder( strWin32UserFolder, "accounts" ) );
    CSpecialProtocol::SetUserXferPath( URIUtils::AddFileToFolder( strWin32UserFolder, "userxfer" ) );
    CSpecialProtocol::SetUserGroupPath( URIUtils::AddFileToFolder( strWin32UserFolder, "usergroup" ) );

    CEnvironment::setenv( CCompileInfo::GetUserProfileEnvName(), CSpecialProtocol::TranslatePath( "special://masterprofile/" ) );

    m_IGoTv.createUserDirs();

    return true;
#else
    return false;
#endif
}

#endif // TARGET_OS_LINUX
