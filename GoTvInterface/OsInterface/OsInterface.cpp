
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

#if defined(TARGET_OS_ANDROID)
# include "platform/qt/qtandroid/jni/Context.h"
# include "platform/qt/qtandroid/jni/System.h"
# include "platform/qt/qtandroid/jni/ApplicationInfo.h"
# include "platform/qt/qtandroid/jni/File.h"
#endif // TARGET_OS_ANDROID

#include "filesystem/Directory.h"
#include "filesystem/File.h"
#include "filesystem/SpecialProtocol.h"
#include "utils/log.h"
#include "utils/URIUtils.h"
#include "GoTvCoreUtil.h"
#include "platform/win32/WIN32Util.h"

#include "ServiceBroker.h"
#include "settings/SettingsComponent.h"

#include <CoreLib/VxGlobals.h>
#include <CoreLib/VxFileUtil.h>
#include <CoreLib/VxDebug.h>

using namespace XFILE;


extern "C" int XBMC_Run( bool renderGUI, const CAppParamParser &params );


//============================================================================
OsInterface::OsInterface( IGoTv& gotv )
    : m_IGoTv( gotv )
    , m_RunResultCode( 0 )
{
}

//============================================================================
bool OsInterface::initRun( const CAppParamParser& cmdLineParams )
{
    m_CmdLineParams = &cmdLineParams;
    return true;
}

//============================================================================
bool OsInterface::doRun( EAppModule appModule )
{
    if( !m_IGoTv.getIsAppModuleRunning( appModule ) )
    {
        m_IGoTv.setIsAppModuleRunning( appModule, true );
        if( eAppModuleKodi == appModule )
        {
			if( m_CmdLineParams )
			{ 
				int runExitCode = XBMC_Run( true, *m_CmdLineParams );
				setRunResultCode( runExitCode );
			}
			else
			{
				LogMsg( LOG_SEVERE, "Command Line Params are not set" );
			}
        }
    }

    return true;
}
//=== utilities ===//
//============================================================================

bool OsInterface::initUserPaths()
{
    std::string exePath = CUtil::ResolveExecutablePath( true );
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
#elif defined(TARGET_OS_ANDROID)
    CJNIContext& jniContext = CJNIContext::getJniContext();
    std::string systemLibsDir = CJNISystem::getProperty("java.library.path");
    setenv("KODI_ANDROID_SYSTEM_LIBS", systemLibsDir.c_str(), 0);
    std::string nativeLibsDir = jniContext.getApplicationInfo().nativeLibraryDir;
    setenv("KODI_ANDROID_LIBS", nativeLibsDir.c_str(), 0);
    std::string apkResourceDir = jniContext.getPackageResourcePath();
    setenv("KODI_ANDROID_APK", apkResourceDir.c_str(), 0);
    LogMsg( LOG_DEBUG, "Sys (%s) native (%s) resource (%s)", systemLibsDir.c_str(), nativeLibsDir.c_str(), apkResourceDir.c_str() );

    std::string appName = CCompileInfo::GetAppName();
    StringUtils::ToLower(appName);
    std::string className = CCompileInfo::GetPackage();

    std::string cacheDir = jniContext.getCacheDir().getAbsolutePath();
    std::string xbmcHome = CJNISystem::getProperty("xbmc.home", "");
    std::string rootApkDir;
    if (xbmcHome.empty())
    {
        rootApkDir = cacheDir + "/apk";
    }
    else
    {
        rootApkDir = xbmcHome;
    }

    std::string kodiAssetsPath = rootApkDir + "/assets/kodi";
    std::string gotvAssetsDir = rootApkDir + "/assets/gotv";

    setenv("KODI_BIN_HOME", kodiAssetsPath.c_str(), 0);
    setenv("KODI_HOME", kodiAssetsPath.c_str(), 0);
    setenv("KODI_BINADDON_PATH", (cacheDir + "/libs").c_str(), 0);

    LogMsg( LOG_DEBUG, "Apk (%s) kodi home (%s) bin addon (%s)", rootApkDir.c_str(), gotvAssetsDir.c_str(), (cacheDir + "/libs").c_str() );

    std::string externalDir = CJNISystem::getProperty("xbmc.data", "");
    if (externalDir.empty())
    {
      CJNIFile androidPath = jniContext.getExternalFilesDir("");
      if (!androidPath)
        androidPath = jniContext.getDir(className.c_str(), 1);

      if (androidPath)
        externalDir = androidPath.getAbsolutePath();
    }

    if ( externalDir.empty() )
    {
        externalDir = getenv("KODI_TEMP");
    }

    std::string kodiHome = externalDir + "/assets/kodi";
    setenv("HOME", kodiHome.c_str(), 0);

    std::string pythonPath = getenv("KODI_ANDROID_APK");
    pythonPath += "/assets/kodi/python2.7";
    setenv("PYTHONHOME", pythonPath.c_str(), 1);
    setenv("PYTHONPATH", "", 1);
    setenv("PYTHONOPTIMIZE","", 1);
    setenv("PYTHONNOUSERSITE", "1", 1);

    LogMsg( LOG_DEBUG, "externalDir (%s) python home (%s) apk (%s)", externalDir.c_str(), pythonPath.c_str(), apkResourceDir.c_str() );

#endif // defined(TARGET_OS_WINDOWS)
    // for gotv use forward slash
	std::string ptopExePath = exePath;
	VxFileUtil::makeForwardSlashPath(ptopExePath);
	VxFileUtil::assureTrailingDirectorySlash(ptopExePath);

	VxSetExeDirectory( ptopExePath.c_str() );

#if defined(TARGET_OS_ANDROID)
    VxFileUtil::makeForwardSlashPath(kodiAssetsPath);
    VxFileUtil::assureTrailingDirectorySlash(kodiAssetsPath);
    VxSetExeKodiAssetsDirectory( kodiAssetsPath.c_str() );

    VxFileUtil::makeForwardSlashPath(gotvAssetsDir);
    VxFileUtil::assureTrailingDirectorySlash(gotvAssetsDir);
    VxSetExeGoTvAssetsDirectory( gotvAssetsDir.c_str() );

    VxFileUtil::makeForwardSlashPath(externalDir);
    VxFileUtil::assureTrailingDirectorySlash(externalDir);
    VxSetRootDataStorageDirectory( externalDir.c_str() );

    std::string pythonResPath = pythonPath + "/lib/python2.7";
    VxFileUtil::makeForwardSlashPath(pythonResPath);
    VxFileUtil::assureTrailingDirectorySlash(pythonResPath);
    VxSetPythonDllDirectory( pythonResPath.c_str() );
    VxSetPythonLibDirectory( pythonResPath.c_str() );

    // android only initi directories now so have path to settings.xml needed in startup
    initDirectories();
#endif // defined(TARGET_OS_ANDROID)
	return true;
}

//============================================================================

bool OsInterface::initDirectories()
{
	//=== relative to executable paths ===//
	//std::string xbmcBinPath = VxFileUtil::makeKodiPath( VxGetExeDirectory().c_str() ); //F:/GoTvCode/bin-OS
    std::string xbmcAssetsPath = CUtil::GetHomePath(); //F:/GoTvCode/bin-OS/assets/kodi 

    CEnvironment::setenv( CCompileInfo::GetHomeEnvName(), xbmcAssetsPath );
	CSpecialProtocol::SetXBMCBinPath( xbmcAssetsPath );

	CSpecialProtocol::SetXBMCPath( xbmcAssetsPath );
    CSpecialProtocol::SetXBMCBinAddonPath( xbmcAssetsPath + "/addons" );

	//=== relative to writable user data paths ===//
    std::string strKodiDataFolder = VxFileUtil::makeKodiPath( VxGetAppDirectory( eAppDirAppKodiData ).c_str() );

    CSpecialProtocol::SetLogPath( VxFileUtil::makeKodiPath( VxGetAppLogsDirectory().c_str() ) );
    CSpecialProtocol::SetHomePath( strKodiDataFolder );
    CSpecialProtocol::SetMasterProfilePath( URIUtils::AddFileToFolder( strKodiDataFolder, "userdata" ) );
    CSpecialProtocol::SetTempPath( URIUtils::AddFileToFolder( strKodiDataFolder, "cache" ) );

    // For PtoP
	std::string gotvDir = VxFileUtil::makeKodiPath( VxGetAppDirectory( eAppDirExeGoTvAssets ).c_str() );
	CSpecialProtocol::SetAppAssetsPath( URIUtils::AddFileToFolder( gotvDir, "gotvassets" ) );	// /exe/assets/gotv/	

	gotvDir = VxFileUtil::makeKodiPath( VxGetAppDirectory( eAppDirAppGoTvData ).c_str() );
	CSpecialProtocol::SetAppDataPath( URIUtils::AddFileToFolder( gotvDir, "gotvdata" ) );		// /storage/GoTvPtoP/gotv/	

	gotvDir = VxFileUtil::makeKodiPath( VxGetAppDirectory( eAppDirUserSpecific ).c_str() );
	CSpecialProtocol::SetAccountsPath( URIUtils::AddFileToFolder( gotvDir, "gotvaccount" ) );	// /storage/GoTvPtoP/hashnum/accounts/userId/

	gotvDir = VxFileUtil::makeKodiPath( VxGetAppDirectory( eAppDirSettings ).c_str() );
	CSpecialProtocol::SetUserGroupPath( URIUtils::AddFileToFolder( gotvDir, "gotvsettings" ) ); // /storage/GoTvPtoP/hashnum/accounts/userId/settings
   
	gotvDir = VxFileUtil::makeKodiPath( VxGetAppDirectory( eAppDirUserXfer ).c_str() ); // Documents Directory/GoTvPtoP/hashnum/userId/   where transfer directories are
	CSpecialProtocol::SetUserXferPath( URIUtils::AddFileToFolder( gotvDir, "gotvxfer" ) );
    

	// Python
	gotvDir = VxFileUtil::makeKodiPath( VxGetAppDirectory( eAppDirExePython ).c_str() );
	CSpecialProtocol::SetPath( "special://xbmc/system/python", gotvDir.c_str() );

	gotvDir = VxFileUtil::makeKodiPath( VxGetAppDirectory( eAppDirExePythonDlls ).c_str() );
	CSpecialProtocol::SetPath( "special://xbmc/system/python/DLLs", gotvDir.c_str() );

	gotvDir = VxFileUtil::makeKodiPath( VxGetAppDirectory( eAppDirExePythonLibs ).c_str() );
	CSpecialProtocol::SetPath( "special://xbmc/system/python/Lib", gotvDir.c_str() );

	// Kodi master profile path ( In Roaming pm windows )
    gotvDir = CSpecialProtocol::TranslatePath( "special://masterprofile/" );
    CEnvironment::setenv( CCompileInfo::GetUserProfileEnvName(), gotvDir.c_str() );

    m_IGoTv.createUserDirs();

    std::string cacert = CEnvironment::getenv( "SSL_CERT_FILE" );
    if( cacert.empty() || !XFILE::CFile::Exists( cacert ) )
    {
        cacert = CSpecialProtocol::TranslatePath( "special://xbmc/system/certs/cacert.pem" );
        IGoTv::getIGoTv().setSslCertFile( cacert );
    }

    return true;
}
