
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
# include "platform/qt/qtandroid/jni/JNIFile.h"
# include <android/asset_manager.h>
# include <android/asset_manager_jni.h>
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
                #if defined(TARGET_OS_ANDROID)
                 int attachedThreadState = CJNIContext::getJniContext().attachThread();
                #endif //  TARGET_OS_ANDROID
				int runExitCode = XBMC_Run( true, *m_CmdLineParams );
				setRunResultCode( runExitCode );
                #if defined(TARGET_OS_ANDROID)
                 CJNIContext::getJniContext().detachThread( attachedThreadState );
                #endif //  TARGET_OS_ANDROID
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

    /*
    setenv("KODI_ANDROID_SYSTEM_LIBS", CJNISystem::getProperty("java.library.path").c_str(), 0);
    setenv("KODI_ANDROID_LIBS", getApplicationInfo().nativeLibraryDir.c_str(), 0);
    setenv("KODI_ANDROID_APK", getPackageResourcePath().c_str(), 0);

    std::string appName = CCompileInfo::GetAppName();
    StringUtils::ToLower(appName);
    std::string className = CCompileInfo::GetPackage();
    */

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

    /*
    std::string cacheDir = getCacheDir().getAbsolutePath();
    std::string xbmcHome = CJNISystem::getProperty("xbmc.home", "");
    if (xbmcHome.empty())
    {
      setenv("KODI_BIN_HOME", (cacheDir + "/apk/assets").c_str(), 0);
      setenv("KODI_HOME", (cacheDir + "/apk/assets").c_str(), 0);
    }
    else
    {
      setenv("KODI_BIN_HOME", (xbmcHome + "/assets").c_str(), 0);
      setenv("KODI_HOME", (xbmcHome + "/assets").c_str(), 0);
    }
    setenv("KODI_BINADDON_PATH", (cacheDir + "/lib").c_str(), 0);
    */

    std::string externalDir = CJNISystem::getProperty("xbmc.data", "");
    if (externalDir.empty())
    {
      CJNIFile androidPath = jniContext.getExternalFilesDir("");
      if (!androidPath)
        androidPath = jniContext.getDir(className.c_str(), 1);

      if (androidPath)
        externalDir = androidPath.getAbsolutePath();
    }

    std::string kodiHome = externalDir + "/assets/kodi";

    if (!externalDir.empty())
    {
        setenv("HOME", kodiHome.c_str(), 0);
    }
    else
    {
        setenv("HOME", getenv("KODI_TEMP"), 0);
    }

    /*
    std::string externalDir = CJNISystem::getProperty("xbmc.data", "");
    if (externalDir.empty())
    {
      CJNIFile androidPath = getExternalFilesDir("");
      if (!androidPath)
        androidPath = getDir(className.c_str(), 1);

      if (androidPath)
        externalDir = androidPath.getAbsolutePath();
    }

    if (!externalDir.empty())
      setenv("HOME", externalDir.c_str(), 0);
    else
      setenv("HOME", getenv("KODI_TEMP"), 0);
      */


    std::string pythonPath = getenv("KODI_ANDROID_APK");
    pythonPath += "/assets/kodi/python2.7";
    setenv("PYTHONHOME", pythonPath.c_str(), 1);
    setenv("PYTHONPATH", "", 1);
    setenv("PYTHONOPTIMIZE","", 1);
    setenv("PYTHONNOUSERSITE", "1", 1);

    LogMsg( LOG_DEBUG, "externalDir (%s) python home (%s) apk (%s)", externalDir.c_str(), pythonPath.c_str(), apkResourceDir.c_str() );

    /*
    std::string apkPath = getenv("KODI_ANDROID_APK");
    apkPath += "/assets/python2.7";
    setenv("PYTHONHOME", apkPath.c_str(), 1);
    setenv("PYTHONPATH", "", 1);
    setenv("PYTHONOPTIMIZE","", 1);
    setenv("PYTHONNOUSERSITE", "1", 1);
    */


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
#if defined( TARGET_OS_ANDROID )

static AAssetManager* android_asset_manager = NULL;
void android_fopen_set_asset_manager(AAssetManager* manager) {
    android_asset_manager = manager;
}

// android:theme=”@android:style/Theme.NoTitleBar.Fullscreen”
bool CopyIfRequiredApkFile( std::string apkFileName, std::string destFile )
{
    bool result = false;
    if( !VxFileUtil::fileExists( destFile.c_str() ) )
    {
        std::string destDir = VxFileUtil::getJustPath( destFile );
        if( !VxFileUtil::directoryExists( destDir.c_str() ) )
        {
            VxFileUtil::makeDirectory( destDir.c_str() );
        }

        AAssetManager* mgr = android_asset_manager;
        assert(NULL != mgr);
        if( mgr )
        {
            AAsset* apkAssetFile = AAssetManager_open(mgr, apkFileName.c_str(), AASSET_MODE_UNKNOWN);
            assert( apkAssetFile );

            if ( apkAssetFile )
            {
                size_t assetLength = AAsset_getLength( apkAssetFile );

                __android_log_print(ANDROID_LOG_DEBUG, "Asset File", "Asset file size: %d\n", assetLength);

                char* buffer = (char*) malloc(assetLength + 1);
                AAsset_read( apkAssetFile, buffer, assetLength);
                buffer[ assetLength ] = 0;
                result = ( 0 == VxFileUtil::writeWholeFile( destFile.c_str(), buffer, assetLength ) );
                AAsset_close( apkAssetFile );
                free(buffer);
                if( !VxFileUtil::fileExists( destFile.c_str() ) )
                {
                    LogMsg( LOG_DEBUG, "Could not create file %s len %d", destFile.c_str(), assetLength );
                }
                else
                {
                    result = true;
                }
            }
            else
            {
                LogMsg( LOG_ERROR,  "Asset Manager Cannot open file %s", destFile.c_str() );
            }
        }
    }
    else
    {
        result = true;
    }

    return result;
}

bool CopyIfRequiredApkDirectory( std::string apkFileDir, std::string destDir )
{
    bool result = false;
    VxFileUtil::assureTrailingDirectorySlash( destDir );

    AAssetManager* assetMgr = android_asset_manager;
    AAssetDir* assetDir = AAssetManager_openDir( assetMgr, apkFileDir.c_str() );
    if( assetDir )
    {
        const char* fileName;
        while ((fileName = AAssetDir_getNextFileName(assetDir)) != NULL)
        {
            //__android_log_print(ANDROID_LOG_DEBUG, "Debug", filename);
            CopyIfRequiredApkFile( apkFileDir + "/" + fileName, destDir + fileName );
        }
    }
    else
    {
        LogMsg( LOG_DEBUG, "Could not open apk dir %s", apkFileDir.c_str() );
    }

    return result;
}
#endif // defined( TARGET_OS_ANDROID )


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

#if defined(TARGET_OS_ANDROID)
    // get user writable data directory
    CJNIContext& jniContext = CJNIContext::getJniContext();
    AAssetManager* assetManager = jniContext.getAssetManager();
    android_fopen_set_asset_manager( assetManager );

    std::string externalDir;
    std::string packageName = jniContext.getPackageName();
    CJNIFile androidPath = jniContext.getExternalFilesDir("");
    if (!androidPath)
      androidPath = jniContext.getDir(packageName.c_str(), 1);

    if (androidPath)
      externalDir = androidPath.getAbsolutePath();

#endif //  defined(TARGET_OS_ANDROID)

    m_IGoTv.createUserDirs();

    std::string cacert = CEnvironment::getenv( "SSL_CERT_FILE" );
    if( cacert.empty() || !XFILE::CFile::Exists( cacert ) )
    {        

#if defined(TARGET_OS_ANDROID)
        // android assumes the cert file has been cached.. force update of cached file
        std::string cacertFile = CSpecialProtocol::TranslatePath( "special://xbmc/system/certs/cacert.pem" );
        if( !XFILE::CFile::Exists( cacert ) )
        {
            CopyIfRequiredApkFile( "kodi/system/certs/cacert.pem", cacertFile );
        }
 #endif //  defined(TARGET_OS_ANDROID)

        if( !VxFileUtil::fileExists( cacertFile.c_str() ) )
        {
            LogMsg( LOG_ERROR, "ERROR could not open cert file %s", cacertFile.c_str() );
        }
        else if( cacert.empty() )
        {
            CEnvironment::setenv( "SSL_CERT_FILE", cacertFile );
        }
    }

    // cannot automagically cache files from apk until advanced setting is loaded for path substitution
    // advanced settings requires settings.xml
#if defined(TARGET_OS_ANDROID)
        std::string settingsXmlFile = CSpecialProtocol::TranslatePath( "special://xbmc/system/settings/settings.xml" );
        VxFileUtil::deleteFile( settingsXmlFile.c_str() );
 #endif // defined(TARGET_OS_ANDROID)

    std::string settingsXml = "special://xbmc/system/settings/settings.xml";
    if( !XFILE::CFile::Exists( settingsXml ) )
    {
#if defined(TARGET_OS_ANDROID)
        std::string settingsXmlFile = CSpecialProtocol::TranslatePath( "special://xbmc/system/settings/settings.xml" );
        VxFileUtil::deleteFile( settingsXmlFile.c_str() );
        CopyIfRequiredApkFile( "kodi/system/settings/settings.xml", settingsXmlFile );
#endif //  defined(TARGET_OS_ANDROID)

        if( !VxFileUtil::fileExists( settingsXmlFile.c_str() ) )
        {
            LogMsg( LOG_ERROR, "ERROR could not open settings file %s", settingsXmlFile.c_str() );
        }
    }

#if defined(TARGET_OS_ANDROID)
        std::string androidXmlFile = CSpecialProtocol::TranslatePath( "special://xbmc/system/settings/android.xml" );
        VxFileUtil::deleteFile( androidXmlFile.c_str() );
 #endif // defined(TARGET_OS_ANDROID)

#if defined(TARGET_OS_ANDROID)
    std::string androidXml = "special://xbmc/system/settings/android.xml";
    if( !XFILE::CFile::Exists( androidXml ) )
    {
        std::string androidXmlFile = CSpecialProtocol::TranslatePath( "special://xbmc/system/settings/android.xml" );
        VxFileUtil::deleteFile( androidXmlFile.c_str() );
        CopyIfRequiredApkFile( "kodi/system/settings/android.xml", androidXmlFile );

        if( !VxFileUtil::fileExists( androidXmlFile.c_str() ) )
        {
            LogMsg( LOG_ERROR, "ERROR could not open settings file %s", androidXmlFile.c_str() );
        }
    }

    CopyIfRequiredApkDirectory( "gotv/profile", externalDir + "/assets/gotv/profile" );
#endif //  defined(TARGET_OS_ANDROID)

    return true;
}
