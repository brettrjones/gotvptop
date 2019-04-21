
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
#include "GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h"
#include "GoTvApps/GoTvCommon/QtSource/AppCommon.h"

#include <CoreLib/VxGlobals.h>
#include <NetLib/VxPeerMgr.h>

using namespace XFILE;

//============================================================================
VxPeerMgr& GetVxPeerMgr( void )
{
    static VxPeerMgr g_VxPeerMgr;
    return  g_VxPeerMgr;
}

//============================================================================
BigListMgr& GetBigListMgr( void )
{
    static BigListMgr g_BigListMgr;
    return  g_BigListMgr;
}

//============================================================================
P2PEngine& GetPtoPEngine()
{
    static P2PEngine g_P2PEngine( GetVxPeerMgr(), GetBigListMgr() );
    return g_P2PEngine;
}

//============================================================================
P2PEngine& IGoTv::getPtoP()
{
    return GetPtoPEngine();
}

//============================================================================
IGoTv& IGoTv::getIGoTv()
{
    static IGoTv g_IGoTv;
    return g_IGoTv;
}

//============================================================================
IToGui& IToGui::getToGui()
{
    return IGoTv::getIGoTv();
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

    if( logLevel > GetILog().getFfmpegLogLevel() )
    {
        return;
    }

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

	// for PtoP
    CDirectory::Create( "special://gotvassets" );
    CDirectory::Create( "special://gotvassets/gui" );
    CDirectory::Create( "special://gotvassets/shaders" );
    CDirectory::Create( "special://gotvassets/profile" );

	CDirectory::Create( "special://gotvdata" );
	CDirectory::Create( "special://gotvaccounts" );
    CDirectory::Create( "special://gotvsettings" );

    CDirectory::Create( "special://gotvxfer" );
	CDirectory::Create( "special://gotvxfer/downloads" );
	CDirectory::Create( "special://gotvxfer/uploads" );
	CDirectory::Create( "special://gotvxfer/incomplete" );
	CDirectory::Create( "special://gotvxfer/me" );


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
    bool result = m_OsInterface.doPreStartup();
	result &= m_OsInterface.initUserPaths();
	return result;
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
void IGoTv::fromGuiKeyPressEvent( int moduleNum, int key, int mod )
{
    getKodi().fromGuiKeyPressEvent( moduleNum, key, mod );
}

//============================================================================
void IGoTv::fromGuiKeyReleaseEvent( int moduleNum, int key, int mod )
{
    getKodi().fromGuiKeyReleaseEvent( moduleNum, key, mod );
}

//============================================================================
void IGoTv::fromGuiMousePressEvent( int moduleNum, int mouseXPos, int mouseYPos, int mouseButton )
{
    getKodi().fromGuiMousePressEvent( moduleNum, mouseXPos, mouseYPos, mouseButton );
}

//============================================================================
void IGoTv::fromGuiMouseReleaseEvent( int moduleNum, int mouseXPos, int mouseYPos, int mouseButton )
{
    getKodi().fromGuiMouseReleaseEvent( moduleNum, mouseXPos, mouseYPos, mouseButton );
}

//============================================================================
void IGoTv::fromGuiMouseMoveEvent( int moduleNum, int mouseXPos, int mouseYPos )
{
    getKodi().fromGuiMouseMoveEvent( moduleNum, mouseXPos, mouseYPos );
}

//============================================================================
void IGoTv::fromGuiResizeBegin( int moduleNum, int winWidth, int winHeight )
{
	getKodi().fromGuiResizeBegin( moduleNum, winWidth, winHeight );
}

//============================================================================
void IGoTv::fromGuiResizeEvent( int moduleNum, int winWidth, int winHeight )
{
    getKodi().fromGuiResizeEvent( moduleNum, winWidth, winHeight );
}

//============================================================================
void IGoTv::fromGuiResizeEnd( int moduleNum, int winWidth, int winHeight )
{
	getKodi().fromGuiResizeEnd( moduleNum, winWidth, winHeight );
}

//============================================================================
void IGoTv::fromGuiCloseEvent( int moduleNum )
{
    getKodi().fromGuiCloseEvent( moduleNum );
}

//============================================================================
void IGoTv::fromGuiVisibleEvent( int moduleNum, bool isVisible )
{
    getKodi().fromGuiVisibleEvent( moduleNum, isVisible );
}
