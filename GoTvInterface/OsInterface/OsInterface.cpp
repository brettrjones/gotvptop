
#include "OsInterface.h"

#include "GoTvInterface/IGoTv.h"

#include "CompileInfo.h"
#include "threads/Thread.h"
#include "platform/xbmc.h"
#include "settings/AdvancedSettings.h"
#include "utils/CPUInfo.h"
#include "platform/Environment.h"
#include "utils/CharsetConverter.h" // Required to initialize converters before usage

#if defined(TARGET_OS_WINDOWS)
#include "threads/platform/win/Win32Exception.h"
#include "platform/win32/CharsetConverter.h"

#include <dbghelp.h>
#include <mmsystem.h>
#include <Objbase.h>
#include <shellapi.h>
#include <WinSock2.h>
#endif //defined(TARGET_OS_WINDOWS)

#include "filesystem/Directory.h"
#include "filesystem/SpecialProtocol.h"
#include "utils/log.h"
#include "utils/URIUtils.h"
#include "GoTvCoreUtil.h"
#include "platform/win32/WIN32Util.h"

#include "ServiceBroker.h"
#include "settings/SettingsComponent.h"

#include <CoreLib/VxGlobals.h>

using namespace XFILE;


extern "C" int XBMC_Run( bool renderGUI, const CAppParamParser &params );


OsInterface::OsInterface( IGoTv& gotv )
    : m_IGoTv( gotv )
    , m_RunResultCode( 0 )
{
}

bool OsInterface::initRun( const CAppParamParser& cmdLineParams )
{
    m_CmdLineParams = cmdLineParams;
    return true;
}

bool OsInterface::doRun( EAppModule appModule )
{
    if( !m_IGoTv.getIsAppModuleRunning( appModule ) )
    {
        m_IGoTv.setIsAppModuleRunning( appModule, true );
        if( eAppModuleKodi == appModule )
        {
            int runExitCode = XBMC_Run( true, m_CmdLineParams );
            setRunResultCode( runExitCode );
        }
    }

    return true;
}
//=== utilities ===//
//============================================================================

bool OsInterface::initDirectories()
{
    std::string xbmcPath = CUtil::GetHomePath(); //F:/GoTvCode/bin/Resources /xbmc or /gotvptop
    //std::string xbmcPath = CUtil::GetExecutablePath();

    CEnvironment::setenv( CCompileInfo::GetHomeEnvName(), xbmcPath );
    CSpecialProtocol::SetXBMCBinPath( xbmcPath );
    CSpecialProtocol::SetXBMCPath( xbmcPath );
    CSpecialProtocol::SetXBMCBinAddonPath( xbmcPath + "/addons" );

    std::string strKodiDataFolder = VxGetKodiDataDirectory();

    CSpecialProtocol::SetLogPath( strKodiDataFolder );
    CSpecialProtocol::SetHomePath( strKodiDataFolder );
    CSpecialProtocol::SetMasterProfilePath( URIUtils::AddFileToFolder( strKodiDataFolder, "userdata" ) );
    CSpecialProtocol::SetTempPath( URIUtils::AddFileToFolder( strKodiDataFolder, "cache" ) );

    // For P2P
    CSpecialProtocol::SetAppDataPath( URIUtils::AddFileToFolder( strKodiDataFolder, "appdata" ) );
    CSpecialProtocol::SetAppAssetsPath( URIUtils::AddFileToFolder( strKodiDataFolder, "appassets" ) );
    CSpecialProtocol::SetAccountsPath( URIUtils::AddFileToFolder( strKodiDataFolder, "accounts" ) );
    CSpecialProtocol::SetUserXferPath( URIUtils::AddFileToFolder( strKodiDataFolder, "userxfer" ) );
    CSpecialProtocol::SetUserGroupPath( URIUtils::AddFileToFolder( strKodiDataFolder, "usergroup" ) );

    CEnvironment::setenv( CCompileInfo::GetUserProfileEnvName(), CSpecialProtocol::TranslatePath( "special://masterprofile/" ) );

    m_IGoTv.createUserDirs();

    return true;
}
