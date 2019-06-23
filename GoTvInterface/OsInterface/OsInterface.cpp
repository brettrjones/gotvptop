
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
# include "AssetDirectoryList.hh"
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
#include <CoreLib/VxTimer.h>

using namespace XFILE;


extern "C" int XBMC_Run( bool renderGUI, const CAppParamParser &params );

#if defined( TARGET_OS_ANDROID )

static AAssetManager* android_asset_manager = NULL;
void android_fopen_set_asset_manager(AAssetManager* manager) {
    android_asset_manager = manager;
}

// android:theme=”@android:style/Theme.NoTitleBar.Fullscreen”
bool CopyIfRequiredApkFile( std::string apkFileName, std::string destFile, bool replaceIfDifferent = true )
{
    bool result = false;
    AAssetManager* mgr = android_asset_manager;
    assert(NULL != mgr);
    if( mgr )
    {
        AAsset* apkAssetFile = AAssetManager_open(mgr, apkFileName.c_str(), AASSET_MODE_UNKNOWN);
        assert( apkAssetFile );

        if ( apkAssetFile )
        {
            size_t assetLength = AAsset_getLength( apkAssetFile );
            u_int64_t destFileLen = VxFileUtil::fileExists( destFile.c_str() );
            if( !destFileLen || ( replaceIfDifferent && ( assetLength != destFileLen ) ) )
            {
                std::string destDir = VxFileUtil::getJustPath( destFile );
                if( !VxFileUtil::directoryExists( destDir.c_str() ) )
                {
                    VxFileUtil::makeDirectory( destDir.c_str() );
                }

                char* buffer = (char*) malloc(assetLength + 1);
                AAsset_read( apkAssetFile, buffer, assetLength);
                buffer[ assetLength ] = 0;
                result = ( 0 == VxFileUtil::writeWholeFile( destFile.c_str(), buffer, assetLength ) );
                free(buffer);
            }

            if( ( 0 != assetLength ) && !VxFileUtil::fileExists( destFile.c_str() ) )
            {
                LogMsg( LOG_ERROR, "Could not create file %s len %d", destFile.c_str(), assetLength );
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

        AAsset_close( apkAssetFile );
    }
    else
    {
        LogMsg( LOG_ERROR,  "Asset Manager Cannot open apk file %s", apkFileName.c_str() );
    }

    return result;
}

bool CopyIfRequiredApkDirectory( std::string apkFileDir, std::string destDir, bool replaceIfDifferent = true )
{
    bool result = true;
    VxFileUtil::assureTrailingDirectorySlash( destDir );

    AAssetManager* assetMgr = android_asset_manager;
    AAssetDir* assetDir = AAssetManager_openDir( assetMgr, apkFileDir.c_str() );
    if( assetDir )
    {
        const char* fileName;
        while ((fileName = AAssetDir_getNextFileName(assetDir)) != NULL)
        {
            //__android_log_print(ANDROID_LOG_DEBUG, "Debug", filename);
            result &= CopyIfRequiredApkFile( apkFileDir + "/" + fileName, destDir + fileName, replaceIfDifferent );
        }
    }
    else
    {
        result = false;
        LogMsg( LOG_DEBUG, "Could not open apk dir %s", apkFileDir.c_str() );
    }

    return result;
}
#endif // defined( TARGET_OS_ANDROID )

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
#ifdef DEBUG
    VxTimer loadTimer;
#endif // DEBUG
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
    AAssetManager* assetMgr = jniContext.getAssetManager();
    android_fopen_set_asset_manager( assetMgr );

    std::string systemLibsDir = CJNISystem::getProperty("java.library.path");
    std::string nativeLibsDir = jniContext.getApplicationInfo().nativeLibraryDir;
    std::string apkResourceDir = jniContext.getPackageResourcePath();

    // normally kodi uses a caching of assets and libraries but that system is hard to work with
    // so just copy everthing needed to the external directory so can be accessed with normal file io

    // find root of where we can write files
    std::string className = CCompileInfo::GetPackage();
    std::string storageDir = CJNISystem::getProperty("xbmc.data", "");
    if (storageDir.empty())
    {
        CJNIFile androidPath = jniContext.getExternalFilesDir("");
        if (!androidPath)
        {
            androidPath = jniContext.getDir(className.c_str(), 1);
        }

        if (androidPath)
        {
            storageDir = androidPath.getAbsolutePath();
        }
    }

    std::string cachedAssetsPath =  storageDir + "/apk/assets";
    std::string kodiCachedAssetsPath = cachedAssetsPath + "/kodi";
    std::string kodiBinStoragePath = kodiCachedAssetsPath + "/libs";

    std::string kodiStoragePath = storageDir + "/kodi";
    std::string gotvStorageDir = storageDir + "/gotv";
    std::string tempDir = storageDir + "/temp";
    std::string logsDir = storageDir + "/logs";
    std::string pythonPath = kodiCachedAssetsPath + "/python2.7/lib/python2.7";

#ifdef DEBUG
    LogMsg( LOG_DEBUG, "storage (%s) resource (%s) sys (%s) native (%s) ", storageDir.c_str(), apkResourceDir.c_str(), systemLibsDir.c_str(), nativeLibsDir.c_str() );
#endif // DEBUG

    // copy profile files for gotv
    CopyIfRequiredApkDirectory( "gotv/profile", gotvStorageDir + "/profile", false );

    // unfortunately asset manager does not have something like sub directory detection so have to copy each directory individualy
    //dir "F:\gotvptop\bin-Android\assets" > "F:\gotvptop\bin-Android\assetList.txt"
    const char * IS_COPIED_FILE = "/ApkVer1_0.txt";
    if( !VxFileUtil::fileExists( ( kodiCachedAssetsPath + IS_COPIED_FILE ).c_str() ) )
    {
        bool result = true;
        std::vector<std::string> dirList;
        getAssetDirList( dirList );
        for( auto iter = dirList.begin(); iter != dirList.end(); ++iter )
        {
            result &= CopyIfRequiredApkDirectory( *iter, cachedAssetsPath + "/" + *iter );
        }

        if( result )
        {
            const char * junkText = "completed\n";
            VxFileUtil::writeWholeFile( ( kodiCachedAssetsPath + IS_COPIED_FILE ).c_str(), (void *)junkText, (uint32_t)strlen(junkText) );
        }
        else
        {
            #ifdef DEBUG
                LogMsg( LOG_DEBUG, "Copy kodi assets to cache failed " );
            #endif // DEBUG
        }
    }


    // asset manager will not copy native libs
    //setenv( "KODI_ANDROID_LIBS", cachedLibsPath.c_str(), 0 );
    //CopyIfRequiredApkDirectory( nativeLibsDir, cachedLibsPath );
    setenv( "KODI_ANDROID_LIBS", nativeLibsDir.c_str(), 0 );
    setenv( "KODI_ANDROID_SYSTEM_LIBS", systemLibsDir.c_str(), 0);
    setenv( "KODI_ANDROID_APK", apkResourceDir.c_str(), 0);

    // home of install distrubuted assets ( for android this is cached asset in storage/apk/assets/kodi )
    setenv( "KODI_HOME", kodiStoragePath.c_str(), 0);

    // normally this would be the execuatable binary path but in android there is no access
    setenv( "KODI_BIN_HOME", kodiBinStoragePath.c_str(), 0);

    // this is where downloaded binary extentions to kodi executable is put
    setenv( "KODI_BINADDON_PATH", kodiBinStoragePath.c_str(), 0);

    // writable storage root directory where downloaded addons and stuff goes
    setenv( "HOME", kodiStoragePath.c_str(), 0);

    // temporary files
    setenv( "KODI_TEMP", tempDir.c_str(), 0);

    // installed python path
    setenv( "PYTHONHOME", pythonPath.c_str(), 1);
    setenv( "PYTHONPATH", "", 1);
    setenv( "PYTHONOPTIMIZE","", 1);
    setenv( "PYTHONNOUSERSITE", "1", 1);

    // map our special drives
    CSpecialProtocol::SetXBMCPath( kodiCachedAssetsPath );

    CSpecialProtocol::SetXBMCBinPath( kodiBinStoragePath );
    CSpecialProtocol::SetXBMCBinAddonPath( kodiCachedAssetsPath + "/addons");
    CSpecialProtocol::SetXBMCAltBinAddonPath( kodiStoragePath + "/addons" );

    CSpecialProtocol::SetHomePath( kodiStoragePath );
    CSpecialProtocol::SetMasterProfilePath( kodiStoragePath + "/userdata" );

    CSpecialProtocol::SetTempPath( tempDir );
    CSpecialProtocol::SetLogPath( logsDir );

    // set paths so accessable outside of kodi
    VxFileUtil::makeForwardSlashPath( kodiBinStoragePath );
    VxFileUtil::assureTrailingDirectorySlash( kodiBinStoragePath );
    VxSetExeDirectory( kodiBinStoragePath.c_str() );

    VxFileUtil::makeForwardSlashPath( storageDir );
    VxFileUtil::assureTrailingDirectorySlash( storageDir );
    VxSetRootDataStorageDirectory( storageDir.c_str() );

    VxFileUtil::makeForwardSlashPath( kodiCachedAssetsPath );
    VxFileUtil::assureTrailingDirectorySlash( kodiCachedAssetsPath );
    VxSetExeKodiAssetsDirectory( kodiCachedAssetsPath.c_str() );

    VxFileUtil::makeForwardSlashPath( gotvStorageDir );
    VxFileUtil::assureTrailingDirectorySlash( gotvStorageDir );
    VxSetExeGoTvAssetsDirectory( gotvStorageDir.c_str() );

    std::string pythonResPath = pythonPath;
    VxFileUtil::makeForwardSlashPath(pythonResPath);
    VxFileUtil::assureTrailingDirectorySlash(pythonResPath);
    VxSetPythonDllDirectory( pythonResPath.c_str() );
    VxSetPythonLibDirectory( pythonResPath.c_str() );

    // move some requried files into place for initial startup

    // advanced settings requires settings.xml
    std::string settingsXmlFile = CSpecialProtocol::TranslatePath( "special://xbmc/system/settings/settings.xml" );
    if( !VxFileUtil::fileExists( settingsXmlFile.c_str() ) )
    {
        CopyIfRequiredApkFile( "kodi/system/settings/settings.xml", settingsXmlFile );
        if( !VxFileUtil::fileExists( settingsXmlFile.c_str() ) )
        {
            LogMsg( LOG_ERROR, "ERROR could not open settings file %s", settingsXmlFile.c_str() );
        }
    }

    std::string androidXmlFile = CSpecialProtocol::TranslatePath( "special://xbmc/system/settings/android.xml" );
    if( !VxFileUtil::fileExists( androidXmlFile.c_str() ) )
    {
        CopyIfRequiredApkFile( "kodi/system/settings/android.xml", androidXmlFile );

        if( !VxFileUtil::fileExists( androidXmlFile.c_str() ) )
        {
            LogMsg( LOG_ERROR, "ERROR could not open settings file %s", androidXmlFile.c_str() );
        }
    }

    std::string cacert = CEnvironment::getenv( "SSL_CERT_FILE" );
    if( cacert.empty() || !VxFileUtil::fileExists(( cacert.c_str()) ) )
    {

        // android assumes the cert file has been cached.. force update of cached file
        std::string cacertFile = CSpecialProtocol::TranslatePath( "special://xbmc/system/certs/cacert.pem" );
        if( !VxFileUtil::fileExists( cacertFile.c_str() ) )
        {
            CopyIfRequiredApkFile( "kodi/system/certs/cacert.pem", cacertFile );
        }

        if( !VxFileUtil::fileExists( cacertFile.c_str() ) )
        {
            LogMsg( LOG_ERROR, "ERROR could not open cert file %s", cacertFile.c_str() );
        }
        else if( cacert.empty() )
        {
            CEnvironment::setenv( "SSL_CERT_FILE", cacertFile );
        }
    }
#endif //  defined(TARGET_OS_ANDROID)

    // initialize all the directories we can without the user specific directory that can only be set after log in
    // For PtoP
    std::string gotvDir = VxFileUtil::makeKodiPath( VxGetAppDirectory( eAppDirExeGoTvAssets ).c_str() );
    CSpecialProtocol::SetAppAssetsPath( URIUtils::AddFileToFolder( gotvDir, "gotvassets" ) );	// /exe/assets/gotv/

    gotvDir = VxFileUtil::makeKodiPath( VxGetAppDirectory( eAppDirAppGoTvData ).c_str() );
    CSpecialProtocol::SetAppDataPath( URIUtils::AddFileToFolder( gotvDir, "gotvdata" ) );		// /storage/GoTvPtoP/gotv/

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

#ifdef DEBUG
    LogMsg( LOG_DEBUG, "Initalize directories took %3.3f sec", loadTimer.elapsedSec() );
#endif // DEBUG
	return true;
}


//============================================================================

bool OsInterface::initDirectories()
{
	//=== relative to executable paths ===//
    // do not call this until user logs on so that eAppDirUserSpecific is set

    //F:/GoTvCode/bin-OS/assets/kodi or for android storage/apk/assets/kodi
    std::string xbmcAssetsPath = CUtil::GetHomePath();
#if !defined(TARGET_OS_ANDROID)
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
#endif // !defined(TARGET_OS_ANDROID)


    std::string gotvDir = VxFileUtil::makeKodiPath( VxGetAppDirectory( eAppDirUserSpecific ).c_str() );
	CSpecialProtocol::SetAccountsPath( URIUtils::AddFileToFolder( gotvDir, "gotvaccount" ) );	// /storage/GoTvPtoP/hashnum/accounts/userId/

	gotvDir = VxFileUtil::makeKodiPath( VxGetAppDirectory( eAppDirSettings ).c_str() );
	CSpecialProtocol::SetUserGroupPath( URIUtils::AddFileToFolder( gotvDir, "gotvsettings" ) ); // /storage/GoTvPtoP/hashnum/accounts/userId/settings
   
	gotvDir = VxFileUtil::makeKodiPath( VxGetAppDirectory( eAppDirUserXfer ).c_str() ); // Documents Directory/GoTvPtoP/hashnum/userId/   where transfer directories are
	CSpecialProtocol::SetUserXferPath( URIUtils::AddFileToFolder( gotvDir, "gotvxfer" ) );
    

    m_IGoTv.createUserDirs();

    return true;
}
