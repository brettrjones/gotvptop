
#include "GoTvAppConfig.h"
#ifdef BUILD_GOTV_APP

#include <GoTvCommon/QtSource/AppCommon.h>
#include <GoTvCommon/QtSource/HomeWindow.h>

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QStringList>
#include <QStandardPaths>
#ifndef QT_NO_OPENGL
#include <QGLFormat>
#endif

#include <CoreLib/VxGlobals.h>
#include <CoreLib/VxFileUtil.h>
#include "AccountMgr.h"
#include <NetLib/VxPeerMgr.h>
#include <GoTvInterface/IGoTv.h>

namespace{
    void setupRootStorageDirectory()
    {
        std::string strRootUserDataDir;

        //=== determine root path to store all application data and settings etc ===//

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
        QString dataPath = QDesktopServices::storageLocation( QDesktopServices::DataLocation );
#else
        QString dataPath = QStandardPaths::writableLocation( QStandardPaths::AppDataLocation );
#endif //TARGET_OS_WINDOWS
        strRootUserDataDir = dataPath.toUtf8().constData();

#ifdef DEBUG
        // remove the D from the end so release and debug builds use the same storage directory
        if( !strRootUserDataDir.empty() && ( strRootUserDataDir.c_str()[ strRootUserDataDir.length() - 1 ] == 'D' ) )
        {
            strRootUserDataDir = strRootUserDataDir.substr( 0, strRootUserDataDir.length() - 1 );
        }
#endif // DEBUG

        VxFileUtil::makeForwardSlashPath( strRootUserDataDir );
        strRootUserDataDir += "/";
        // No need to put application in path because when call QCoreApplication::setApplicationName("MyP2PWeb")
        // it made it a sub directory of DataLocation
        VxSetRootDataStorageDirectory( strRootUserDataDir.c_str() );
    }
}

int main(int argc, char **argv)
{
    QApplication::setAttribute( Qt::AA_ShareOpenGLContexts );
    QApplication::setAttribute( Qt::AA_DontCheckOpenGLContextThreadAffinity );
    //QCoreApplication::setAttribute( Qt::AA_EnableHighDpiScaling );

	// for some reason QApplication must be newed or does not initialize 
	QApplication* myApp = new QApplication( argc, argv );

    // chicken and egg kind of thing.. we need the storage path here
    QGuiApplication::setApplicationDisplayName( VxGetApplicationTitle() );
    QCoreApplication::setOrganizationDomain( VxGetCompanyDomain() );
    // NOTE OrganizationName and ApplicationName become part of data storage location path
    QCoreApplication::setOrganizationName( "" ); // leave blank or will become part of data storage path
    QCoreApplication::setApplicationName( VxGetApplicationNameNoSpaces() );
    QCoreApplication::setApplicationVersion( VxGetAppVersionString() );

    // is this needed ? Q_INIT_RESOURCE( gotvcommon );

    // TODO allow user to change where the data is stored
    setupRootStorageDirectory();

    IGoTv& gotv = IGoTv::getIGoTv();
    gotv.doPreStartup();

    AppCommon& appCommon = CreateAppInstance( gotv, myApp );

	// create a thread to do application init and loading .. causes issues with QThreadDataStorage on linux so just load directly
#if 0
	//QThread * loaderThread = new QThread();
	//appCommon.moveToThread( loaderThread );
	//QObject::connect( loaderThread, SIGNAL( started() ), &appCommon, SLOT( slotStartLoadingFromThread() ) );
	//loaderThread->start();
#else
    appCommon.loadWithoutThread();
#endif // 0

    // send command line parameters to Kodi
	static CAppParamParser appParamParser;
    appParamParser.Parse( argv, argc );
    GetIGoTv().initRun( appParamParser );

	int result = 0;

	//homePage.startup();
	//homePage.show();
	//if( false == homePage.userCanceled() )
	{
		result = myApp->exec();
	}

    //gotv.doPreShutdown();
	//delete myApp;
	return result;
}

#endif // BUILD_GOTV_APP
