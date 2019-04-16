
#include "GoTvAppConfig.h"
#ifdef BUILD_GOTV_APP

#include "GoTvPlayerSettings.h"
#include <GoTvCommon/QtSource/AppCommon.h>
#include <GoTvCommon/QtSource/HomeWindow.h>

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QStringList>
#ifndef QT_NO_OPENGL
#include <QGLFormat>
#endif

#include "AnalogClock.h"
#include <CoreLib/VxGlobals.h>
#include "VxDataHelper.h"
#include <NetLib/VxPeerMgr.h>
#include <GoTvInterface/IGoTv.h>


int main(int argc, char **argv)
{
    //QApplication::setAttribute( Qt::AA_ShareOpenGLContexts );

	// for some reason QApplication must be newed or does not initialize 
    //QCoreApplication::setAttribute( Qt::AA_EnableHighDpiScaling );
	QApplication* myApp = new QApplication( argc, argv );

    IGoTv& gotv = IGoTv::getIGoTv();
    gotv.doPreStartup();

    static GoTvPlayerSettings playerSettings;
    AppCommon& appCommon = CreateAppInstance( gotv, myApp, playerSettings );

	//QGuiApplication::setApplicationDisplayName( QObject::tr("GoTvP2P Player") );
	//QCoreApplication::setOrganizationDomain( VxGetCompanyDomain() );
	// NOTE OrganizationName and ApplicationName become part of data storage location path
	//QCoreApplication::setOrganizationName( "" );
	//QCoreApplication::setApplicationName( VxGetApplicationNameNoSpaces() );
	//QCoreApplication::setApplicationVersion( VxGetAppVersionString() );

	//QCoreApplication::setOrganizationName( "QtProject" );
	//QCoreApplication::setApplicationVersion( QT_VERSION_STR );
	//MainWindow window;
//	if( !window.loadFile( parser.positionalArguments().value( 0, QLatin1String( ":/Resources/bubbles.svg" ) ) ) )
//		return -1;
	//window.show();


	// create a thread to do application init and loading
	QThread * loaderThread = new QThread();
	appCommon.moveToThread( loaderThread );
	QObject::connect( loaderThread, SIGNAL( started() ), &appCommon, SLOT( slotStartLoadingFromThread() ) );
	loaderThread->start();

    // send command line parameters to Kodi
	static CAppParamParser appParamParser;
    appParamParser.Parse( argv, argc );
    GetIGoTv().initRun( appParamParser );



	int result = 0;

	//homePage.startup();
	//homePage.show();
	//AnalogClockWindow clock;
	//clock.show();
	//if( false == homePage.userCanceled() )
	{
		result = myApp->exec();
	}

    //gotv.doPreShutdown();
	delete myApp;
	return result;

/*    Q_INIT_RESOURCE(gotvcommon);

    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("SVG Viewer");
    QGuiApplication::setApplicationDisplayName(QCoreApplication::applicationName());
    QCoreApplication::setOrganizationName("QtProject");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    QCommandLineParser parser;
    parser.setApplicationDescription("Qt SVG Viewer");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file", "The file to open.");
    parser.process(app);

    MainWindow window;
    if (!window.loadFile(parser.positionalArguments().value(0, QLatin1String(":/Resources/bubbles.svg"))))
        return -1;
    window.show();
    return app.exec();*/
}

#endif // BUILD_GOTV_APP
