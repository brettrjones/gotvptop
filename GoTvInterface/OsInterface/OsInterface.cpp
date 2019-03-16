
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
#include <CoreLib/VxFileUtil.h>

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

bool OsInterface::initUserPaths()
{
	std::string exePath = CUtil::ResolveExecutablePath();
#if defined(TARGET_OS_WINDOWS)
	std::string strHomePath = exePath;
	// strip off exe name
	size_t last_sep = strHomePath.find_last_of(PATH_SEPARATOR_CHAR);
	if (last_sep != std::string::npos)
		exePath = strHomePath.substr(0, last_sep);
	else
		exePath = strHomePath;
	// make into full path by removing relative ..
	if (exePath.find("..") != std::string::npos)
	{
		//expand potential relative path to full path
		std::wstring strPathW;
		g_charsetConverter.utf8ToW(exePath, strPathW, false);
		CWIN32Util::AddExtraLongPathPrefix(strPathW);
		const unsigned int bufSize = GetFullPathNameW(strPathW.c_str(), 0, NULL, NULL);
		if (bufSize != 0)
		{
			wchar_t * buf = new wchar_t[bufSize];
			if (GetFullPathNameW(strPathW.c_str(), bufSize, buf, NULL) <= bufSize - 1)
			{
				std::wstring expandedPathW(buf);
				CWIN32Util::RemoveExtraLongPathPrefix(expandedPathW);
				g_charsetConverter.wToUTF8(expandedPathW, exePath);
			}

			delete[] buf;
		}
	}
#endif // defined(TARGET_OS_WINDOWS)
	// for ptop use forward slash
	std::string ptopExePath = exePath;
	VxFileUtil::makeForwardSlashPath(ptopExePath);
	VxFileUtil::assureTrailingDirectorySlash(ptopExePath);

	VxSetExeDirectory( ptopExePath.c_str() );

	return true;
}

//============================================================================

bool OsInterface::initDirectories()
{
	//std::string xbmcBinPath = VxFileUtil::makeKodiPath( VxGetExeDirectory().c_str() ); //F:/GoTvCode/bin-OS
    std::string xbmcAssetsPath = CUtil::GetHomePath(); //F:/GoTvCode/bin-OS/assets/kodi 

    CEnvironment::setenv( CCompileInfo::GetHomeEnvName(), xbmcAssetsPath );
	CSpecialProtocol::SetXBMCBinPath( xbmcAssetsPath );

	CSpecialProtocol::SetXBMCPath( xbmcAssetsPath );
    CSpecialProtocol::SetXBMCBinAddonPath( xbmcAssetsPath + "/addons" );

    std::string strKodiDataFolder = VxFileUtil::makeKodiPath( VxGetAppKodiDataDirectory().c_str() );

    CSpecialProtocol::SetLogPath( VxFileUtil::makeKodiPath( VxGetAppLogsDirectory().c_str() ) );
    CSpecialProtocol::SetHomePath( strKodiDataFolder );
    CSpecialProtocol::SetMasterProfilePath( URIUtils::AddFileToFolder( strKodiDataFolder, "userdata" ) );
    CSpecialProtocol::SetTempPath( URIUtils::AddFileToFolder( strKodiDataFolder, "cache" ) );

    // For PtoP
	// BRJ FIXME
    //CSpecialProtocol::SetAppDataPath( URIUtils::AddFileToFolder( strKodiDataFolder, "appdata" ) );
    //CSpecialProtocol::SetAppAssetsPath( URIUtils::AddFileToFolder( strKodiDataFolder, "appassets" ) );
    //CSpecialProtocol::SetAccountsPath( URIUtils::AddFileToFolder( strKodiDataFolder, "accounts" ) );
    //CSpecialProtocol::SetUserXferPath( URIUtils::AddFileToFolder( strKodiDataFolder, "userxfer" ) );
    //CSpecialProtocol::SetUserGroupPath( URIUtils::AddFileToFolder( strKodiDataFolder, "usergroup" ) );

    CEnvironment::setenv( CCompileInfo::GetUserProfileEnvName(), CSpecialProtocol::TranslatePath( "special://masterprofile/" ) );

    m_IGoTv.createUserDirs();

    return true;
}
