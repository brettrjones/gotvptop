
#include "OsInterface.h"

#include "GoTvInterface/IGoTv.h"


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
