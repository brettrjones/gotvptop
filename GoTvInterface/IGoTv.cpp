
#include "IGoTv.h"
#include <CoreLib/VxDebug.h>
#include <CoreLib/VxThread.h>
#include <GoTvCore/xbmc/xbmc/utils/StringUtils.h>
#include <libavutil/log.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavfilter/avfilter.h>

#ifdef TARGET_OS_WINDOWS
# include "GoTvInterface/OsWin32/IWin32.h"
#elif TARGET_OS_LINUX
# include "GoTvInterface/OsLinux/ILinux.h"
#elif TARGET_OS_ANDROID
# include "GoTvInterface/OsAndroid/IAndroid.h"
#else 
echo traget os is not defined
#endif 

#include "filesystem/Directory.h"
#include "filesystem/SpecialProtocol.h"
#include "utils/log.h"
#include "Application.h"
#include "GoTvP2P/P2PEngine/P2PEngine.h"
#include "GoTvApps/GoTvCommon/QtSource/AppCommon.h"

#include <CoreLib/VxGlobals.h>
#include <NetLib/VxPeerMgr.h>

using namespace XFILE;

namespace
{
    P2PEngine * g_EnginePtr = nullptr;
}

//============================================================================
VxPeerMgr& GetVxPeerMgr( void )
{
    static VxPeerMgr g_VxPeerMgr;
    return  g_VxPeerMgr;
}

//============================================================================
IGoTv& IGoTv::getIGoTv()
{
    static IGoTv g_IGoTv;
    // fix circular dependency.. P2PEngine requires IGoTv.. IGoTv requires P2PEngine..
    static P2PEngine g_P2PEngine( g_IGoTv, GetVxPeerMgr() );
    static bool firstCall = true;
    if( firstCall )
    {
        firstCall = false;
        g_EnginePtr = &g_P2PEngine;
    }

    return g_IGoTv;
}

//============================================================================
P2PEngine& IGoTv::getPtoP()
{
    return *g_EnginePtr;
}

//============================================================================
AppCommon& IGoTv::getAppCommon()
{
    return GetAppInstance();
}

//============================================================================
void ff_flush_avutil_log_buffers(void)
{
}

//============================================================================
void ff_avutil_log(void* ptr, int level, const char* format, va_list va)
{
    unsigned int threadId =	VxGetCurrentThreadId();
    AVClass* avc= ptr ? *(AVClass**)ptr : NULL;

    int logLevel = 0;
    int logType = 0;
    switch( level )
    {
    case AV_LOG_FATAL:
    case AV_LOG_PANIC:
        logLevel = ILOG_LEVEL_FATAL;
        logType = LOG_FATAL;
        break;

    case AV_LOG_ERROR:
        logLevel = ILOG_LEVEL_ERROR;
        logType = LOG_ERROR;
        break;

    case AV_LOG_WARNING:
        logLevel = ILOG_LEVEL_WARN;
        logType = LOG_WARN;
        break;

    case AV_LOG_INFO:
        logLevel = ILOG_LEVEL_INFO;
        logType = LOG_INFO;
        break;

    case AV_LOG_DEBUG:
        logLevel = LOG_LEVEL_DEBUG;
        logType = LOG_DEBUG;
        break;

    case AV_LOG_TRACE:
    case AV_LOG_VERBOSE:
        logLevel = ILOG_LEVEL_VERBOSE;
        logType = LOG_VERBOSE;
        break;

    case AV_LOG_QUIET:
    default:
        logLevel = LOG_LEVEL_NONE;
        return;
    }

    //if( logLevel > GetILog().getFfmpegLogLevel() )
    //{
    //    return;
    //}

    if( level > AV_LOG_DEBUG )
    {
        return;
    }

    std::string message = StringUtils::FormatV( format, va );
    if( message.empty() )
    {
        return;
    }

    static std::string buffer;
    std::string prefix = StringUtils::Format( "ffmpeg[%lX]: ", threadId );
    if( avc )
    {
        if( avc->item_name )
            prefix += std::string( "[" ) + avc->item_name( ptr ) + "] ";
        else if( avc->class_name )
            prefix += std::string( "[" ) + avc->class_name + "] ";
    }

    buffer += message;
    int pos, start = 0;
    while( ( pos = buffer.find_first_of( '\n', start ) ) >= 0 )
    {
        if( pos > start )
            LogMsg( logType, "%s%s", prefix.c_str(), buffer.substr( start, pos - start ).c_str() );
        start = pos + 1;
    }

    buffer.erase( 0, start );
}

//============================================================================
IGoTv::IGoTv()
: m_ILog()
#ifdef TARGET_OS_WINDOWS
, m_OsInterface( *new IWin32(*this) )
#elif TARGET_OS_LINUX
, m_OsInterface( *new ILinux( *this ) )
#elif TARGET_OS_ANDROID
, m_OsInterface( *new IAndroid( *this ) )
#endif 
, m_VxPeerMgr( GetVxPeerMgr() )
, m_Kodi( GetKodiInstance() )
{
    memset( m_IsRunning, 0, sizeof( m_IsRunning  ) );
}

//============================================================================
IGoTv::~IGoTv()
{
    delete &m_OsInterface;
}

//=== utilities ===//
//============================================================================
bool IGoTv::initDirectories()
{
    bool result = m_OsInterface.initDirectories();
    // ffmpeg needs early start so can finish the loading threads before kodi is started
    startupFfmpeg();
    return result;
}

//============================================================================
void IGoTv::createUserDirs() const
{
    CDirectory::Create( "special://home/" );
    CDirectory::Create( "special://home/addons" );
    CDirectory::Create( "special://home/addons/packages" );
    CDirectory::Create( "special://home/addons/temp" );
    CDirectory::Create( "special://home/media" );
    CDirectory::Create( "special://home/system" );
    CDirectory::Create( "special://masterprofile/" );
    CDirectory::Create( "special://temp/" );
    CDirectory::Create( "special://logpath" );
    CDirectory::Create( "special://temp/temp" ); // temp directory for python and dllGetTempPathA
    CDirectory::Create( "special://appdata" );
    CDirectory::Create( "special://appassets" );
    CDirectory::Create( "special://appassets/gui" );
    CDirectory::Create( "special://appassets/shaders" );
    CDirectory::Create( "special://appassets/profile" );
    CDirectory::Create( "special://accounts" );
    CDirectory::Create( "special://userxfer" );
    CDirectory::Create( "special://usergroup" );

    // P2P directories
    //                  /appdata/ShredFilesDb.db3 and app generated files
    //                  /appassets/gui/ gui assets
    //                            /shaders/ opengl shaders
    //                            /profile/ profile default files
    // user specific directories
    //                  /accounts/userId/settings/ databases
    //                  /accounts/userId/blog/ profile and story board user web pages
    // user xfer directories         
    //                  /userxfer/userId/downloads
    //                                 /uploads
    //                                 /incomplete
    //                                 /me/			personal recordings
    //                                 /contacts/	contact assets
    // user group directories
    //                 /usergroup/


      //Let's clear our archive cache before starting up anything more
    auto archiveCachePath = CSpecialProtocol::TranslatePath( "special://temp/archive_cache/" );
    if( CDirectory::Exists( archiveCachePath ) )
        if( !CDirectory::RemoveRecursive( archiveCachePath ) )
            CLog::Log( LOGWARNING, "Failed to remove the archive cache at %s", archiveCachePath.c_str() );
    CDirectory::Create( archiveCachePath );

}

//============================================================================
void IGoTv::playGoTvMedia( AssetInfo * assetInfo ) 
{ 
};

//=== ffmpeg ===//
//============================================================================
void IGoTv::startupFfmpeg()
{
    static bool ffmpegStarted = false;
    if( !ffmpegStarted )
    {
        ffmpegStarted = true;
        // register ffmpeg lockmanager callback
    //    av_lockmgr_register( &ffmpeg_lockmgr_cb );

        // set avutil callback
        av_log_set_callback( ff_avutil_log );
        // register avcodec
        avcodec_register_all();
#if CONFIG_AVDEVICE
        avdevice_register_all();
#endif
        // register avformat
        av_register_all();
        // register avfilter
        avfilter_register_all();
        // initialize network protocols
        avformat_network_init();

    }
}

//============================================================================
void IGoTv::shutdownFfmpeg()
{

}

//=== open ssl ===//
//============================================================================
void IGoTv::setSslCertFile( std::string certFile )
{
    m_SslCertFile = certFile;
    if( !m_SslCertFile.empty() )
    {

    }
}

//=== stages of create ===//
//============================================================================
bool IGoTv::doPreStartup()
{
    VxSetAppIsShuttingDown( false );
    return m_OsInterface.doPreStartup();
}

//============================================================================
bool IGoTv::doStartup()
{
    return m_OsInterface.doStartup();
}


//=== stages of run ===//
//============================================================================
bool IGoTv::initRun( const CAppParamParser& params )
{
    return m_OsInterface.initRun( params );
}

//============================================================================
bool IGoTv::doRun( EAppModule appModule )
{
    return m_OsInterface.doRun( appModule );
}

//=== stages of destroy ===//
//============================================================================
void IGoTv::doPreShutdown()
{
    m_OsInterface.doPreShutdown();
}

//============================================================================
void IGoTv::doShutdown()
{
    m_OsInterface.doShutdown();
}

//============================================================================
//=== to gotv events ===//
//============================================================================
//============================================================================
void IGoTv::keyPressEvent( int moduleNum, int key, int mod )
{
    getKodi().keyPressEvent( moduleNum, key, mod );
}

//============================================================================
void IGoTv::keyReleaseEvent( int moduleNum, int key, int mod )
{
    getKodi().keyReleaseEvent( moduleNum, key, mod );
}

//============================================================================
void IGoTv::mousePressEvent( int moduleNum, int mouseXPos, int mouseYPos, int mouseButton )
{
    getKodi().mousePressEvent( moduleNum, mouseXPos, mouseYPos, mouseButton );
}

//============================================================================
void IGoTv::mouseReleaseEvent( int moduleNum, int mouseXPos, int mouseYPos, int mouseButton )
{
    getKodi().mouseReleaseEvent( moduleNum, mouseXPos, mouseYPos, mouseButton );
}

//============================================================================
void IGoTv::mouseMoveEvent( int moduleNum, int mouseXPos, int mouseYPos )
{
    getKodi().mouseMoveEvent( moduleNum, mouseXPos, mouseYPos );
}

//============================================================================
void IGoTv::resizeEvent( int moduleNum, int winWidth, int winHeight )
{
    getKodi().resizeEvent( moduleNum, winWidth, winHeight );
}

//============================================================================
void IGoTv::closeEvent( int moduleNum )
{
    getKodi().closeEvent( moduleNum );
}

//============================================================================
void IGoTv::visibleEvent( int moduleNum, bool isVisible )
{
    getKodi().visibleEvent( moduleNum, isVisible );
}
