
#include "HomeWindow.h"
#include "AppCommon.h"
#include "AppSettings.h"
#include "VxAppTheme.h"
#include "VxAppDisplay.h"

#include "AppletLaunchPage.h"
#include "MessengerPage.h"
#include "GuiParams.h"

#include "VxFrame.h"

#include <CoreLib/VxAppInfo.h>

#include <QScreen>
#include <QtWidgets>

//============================================================================
HomeWindow::HomeWindow( AppCommon&	appCommon, QString title )
: QDialog( )
, m_MyApp( appCommon )
, m_AppDisplay( m_MyApp.getAppDisplay() )
, m_AppTitle( title )
, m_WindowSettings( 0 )
, m_LastHomeLayout( eHomeLayoutPlayerPlusMessenger )
, m_MainLayout( 0 )
, m_HomeFrameUpperLeft( new VxFrame( this ) )
, m_HomeFrameRight( new VxFrame( this ) )
, m_HomeFrameBottom( new VxFrame( this ) )
, m_MediaPlayerPage( 0 )
, m_AppletLaunchPage( 0 )
, m_MessengerParent( 0 )
, m_MessengerPage( 0 )
, m_MessengerIsFullSize( false )
, m_HomeFrameFullSize( false )
, m_EngineInitialized( false )
{
    setObjectName( "HomeWindow" );
    m_HomeFrameUpperLeft->setObjectName( OBJNAME_FRAME_LAUNCH_PAGE );
    // messenger can be in right frame or bottom frame depending on layout orientation
    m_HomeFrameRight->setObjectName( OBJNAME_FRAME_MESSAGER_PAGE );
    m_HomeFrameBottom->setObjectName( OBJNAME_FRAME_MESSAGER_PAGE );

    VxAppInfo appInfo;
    m_WindowSettings = new QSettings( appInfo.getCompanyDomain(), appInfo.getAppNameNoSpaces(), this );
}

//============================================================================
void HomeWindow::accept()
{
    // user has clicked the X to exit application.. prompt if really wants to exit
    QMessageBox::StandardButton resBtn = QMessageBox::Yes;
    bool changes = true;
    if( changes ) {
        resBtn = QMessageBox::question( this, "Close Application",
            tr( "Are you sure?\n" ),
            QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
            QMessageBox::Yes );
    }

    if( resBtn == QMessageBox::Yes )
    {
        QDialog::reject();
    }
}

//============================================================================
void HomeWindow::reject()
{
    QMessageBox::StandardButton resBtn = QMessageBox::Yes;
    bool changes = true;
    if( changes ) {
        resBtn = QMessageBox::question( this, QObject::tr("Close Application"),
            tr( "Are you sure you want to exit?\n" ),
            QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
            QMessageBox::Yes );
    }

    if( resBtn == QMessageBox::Yes ) 
    {
        GetAppInstance().shutdownAppCommon();
        QDialog::reject();
    }
}

//============================================================================
void HomeWindow::resizeEvent( QResizeEvent * )
{
	emit signalMainWindowResized();
}

//============================================================================
void HomeWindow::moveEvent( QMoveEvent * )
{
    emit signalMainWindowMoved();
}

//============================================================================
void HomeWindow::showEvent( QShowEvent * ev )
{
    QDialog::showEvent( ev );
    m_MyApp.startupAppCommon( getAppletFrame( eAppletHomePage ), getAppletFrame( eAppletMessenger ) );

    m_MyApp.getAppTheme().selectTheme( m_MyApp.getAppSettings().getLastSelectedTheme() );
}

//============================================================================
void HomeWindow::initializeHomePage()
{
#if !defined(TARGET_OS_ANDROID)
    QByteArray restoreGeom = m_WindowSettings->value( "mainWindowGeometry" ).toByteArray();
    if( restoreGeom.isEmpty() )
    {
        const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2,
             (availableGeometry.height() - height()) / 2);
    }
    else
    {
        restoreGeometry(restoreGeom);
    }
#else
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->availableGeometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width() - 10;
    resize(width, height);
    move( screenGeometry.left() + 5, screenGeometry.top() );
    LogMsg( LOG_DEBUG, "Home Screen Size %d %d", width, height);

#endif // !defined(TARGET_OS_ANDROID)

	initializeGoTvDynamicLayout();
	connect( &m_AppDisplay, SIGNAL( signalDeviceOrientationChanged( int ) ), this, SLOT( slotDeviceOrientationChanged( int ) ) );
    connect( this, SIGNAL( signalMainWindowResized() ), &m_MyApp, SLOT( slotMainWindowResized() ) );
    connect( this, SIGNAL( signalMainWindowMoved() ), &m_MyApp, SLOT( slotMainWindowMoved() ) );
	m_AppDisplay.forceOrientationUpdate();
}

//============================================================================
void HomeWindow::initializeGoTvDynamicLayout( void )
{
#if !defined(TARGET_OS_ANDROID)
    setMinimumSize( (int)( 400.0f * GuiParams::getGuiScale() ), (int)( 400.0f * GuiParams::getGuiScale()     ) );
#endif // !defined(TARGET_OS_ANDROID)

	m_MainLayout = new QGridLayout();
	m_MainLayout->setSizeConstraint( QLayout::SetNoConstraint );
	m_MainLayout->setSpacing( 1 );
	m_MainLayout->setMargin( 0 );

	// make a frame for each possible layout area and we will show/hide/ re-parent based on the layout type
	m_HomeFrameUpperLeft->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
	m_HomeFrameUpperLeft->setFrameShape( QFrame::Shape::Box );
	m_HomeFrameUpperLeft->setLineWidth( 1 );
	m_HomeFrameUpperLeft->setProperty( "GoTvFrame", true );
	//m_HomeFrameUpperLeft->setFocusPolicy( Qt::FocusPolicy::TabFocus );
	m_HomeFrameUpperLeft->setProperty( "FrameFocus", true );
	m_MainLayout->addWidget( m_HomeFrameUpperLeft, 0, 0 );

	m_HomeFrameRight->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
	m_HomeFrameRight->setFrameShape( QFrame::Shape::Box );
	m_HomeFrameRight->setLineWidth( 1 );
	m_HomeFrameRight->setProperty( "GoTvFrame", true );
	//m_HomeFrameRight->setFocusPolicy( Qt::FocusPolicy::TabFocus );
	m_MainLayout->addWidget( m_HomeFrameRight, 0, 1 );

	m_HomeFrameBottom->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
	m_HomeFrameBottom->setFrameShape( QFrame::Shape::Box );
	m_HomeFrameBottom->setLineWidth( 1 );
	m_HomeFrameBottom->setProperty( "GoTvFrame", true );
	//m_HomeFrameBottom->setFocusPolicy( Qt::FocusPolicy::TabFocus );
	m_MainLayout->addWidget( m_HomeFrameBottom, 1, 0 );

	connect( m_HomeFrameUpperLeft,	SIGNAL( signalFrameResized() ), this, SLOT( slotFrameResized() ) );
	connect( m_HomeFrameRight,		SIGNAL( signalFrameResized( ) ), this, SLOT( slotFrameResized() ) );
	connect( m_HomeFrameBottom,		SIGNAL( signalFrameResized() ), this, SLOT( slotFrameResized() ) );
	setLayout( m_MainLayout );

    createAppletLaunchPage();
    createMessengerPage();
    m_HomeFrameRight->setVisible( false );
    m_HomeFrameBottom->setVisible( false );
}

//============================================================================
void HomeWindow::switchWindowFocus(  QWidget * goTvButton )
{
	if( ( false == m_HomeFrameUpperLeft->isVisible() )
		|| ( false == getMessengerParentFrame()->isVisible() ) )
	{
		// no window to switch to
		goTvButton->nextInFocusChain();
		return;
	}
	else
	{
		if( true == goTvButton->property( "FocusNext" ) )
		{
			//LogMsg( LOG_DEBUG, "GoTv Button %d focus next true\n", goTvButton );
			goTvButton->setProperty( "FocusNext", false );
			goTvButton->nextInFocusChain();
			goTvButton->clearFocus();
			if( true == m_HomeFrameUpperLeft->property( "FrameFocus" ) )
			{
				m_HomeFrameUpperLeft->setProperty( "FrameFocus", false );
				m_HomeFrameUpperLeft->clearFocus();
				getMessengerParentFrame()->setProperty( "FrameFocus", true );
				getMessengerParentFrame()->activateWindow();
				m_MessengerPage->getAppIconPushButton()->setFocus();
			}
			else
			{
				m_HomeFrameUpperLeft->setProperty( "FrameFocus", true );
				getMessengerParentFrame()->setProperty( "FrameFocus", false );
				getMessengerParentFrame()->clearFocus();
				m_HomeFrameUpperLeft->activateWindow();
				m_AppletLaunchPage->getAppIconPushButton()->setFocus();
			}
		}
		else
		{
			//LogMsg( LOG_DEBUG, "GoTv Button %d focus next false\n", goTvButton );
			goTvButton->setProperty( "FocusNext", true );
			goTvButton->nextInFocusChain();
		}
	}
}

//============================================================================
QFrame *  HomeWindow::getAppletFrame( EApplet applet )
{
	if( eAppletMessenger == applet )
	{
		return getMessengerParentFrame();
	}
	else
	{
		return m_HomeFrameUpperLeft;
	}
}

//============================================================================
QFrame * HomeWindow::getMessengerParentFrame( void )
{
	if( Qt::Vertical == m_Orientation )
	{
		return m_HomeFrameBottom;
	}
	else
	{
		return m_HomeFrameRight;
	}
}

//============================================================================
QFrame * HomeWindow::getLaunchPageFrame( void )
{ 
    return m_HomeFrameUpperLeft;
}

//============================================================================
void HomeWindow::slotDeviceOrientationChanged( int qtOrientation )
{
    m_Orientation = (Qt::Orientation)qtOrientation;
	if( 0 == m_MessengerPage )
	{
		LogMsg( LOG_ERROR, "m_MessengerPage is null\n" );
		return;
	}

    getMessengerParentFrame()->setVisible( false );
	if( Qt::Vertical == m_Orientation )
	{
		m_MessengerPage->setNewParent( m_HomeFrameBottom );
	}
	else
	{
		m_MessengerPage->setNewParent( m_HomeFrameRight );
	}

    if( ! getIsMaxScreenSize( false ) )
    {
        // if not home frame max size ( messenger is not visible )
        getMessengerParentFrame()->setVisible( true );
    }

    emit signalDeviceOrientationChanged( m_Orientation );
	emit signalMainWindowResized( );
}

//============================================================================
void HomeWindow::setIsMaxScreenSize( bool isMessagerFrame, bool isFullSizeWindow )
{	
	if( isMessagerFrame )
	{
        if( isFullSizeWindow )
        {
            // full screen messenger
            m_HomeFrameFullSize = false;
            m_MessengerIsFullSize = true;
            m_HomeFrameUpperLeft->setVisible( false );
            getMessengerParentFrame()->setVisible( true );
        }
        else
        {
            m_HomeFrameFullSize = false;
            m_MessengerIsFullSize = false;
            m_HomeFrameUpperLeft->setVisible( true );
            getMessengerParentFrame()->setVisible( true );
        }
	}
	else
	{
        if( isFullSizeWindow )
        {
            // full screen applet page
            m_HomeFrameFullSize = true;
            m_MessengerIsFullSize = false;
            m_HomeFrameUpperLeft->setVisible( true );
            getMessengerParentFrame()->setVisible( false );
        }
        else
        {
            m_HomeFrameFullSize = false;
            m_MessengerIsFullSize = false;
            m_HomeFrameUpperLeft->setVisible( true );
            getMessengerParentFrame()->setVisible( true );
        }
	}

    emit signalMainWindowResized( );
}

//============================================================================
bool HomeWindow::getIsMaxScreenSize( bool isMessagerFrame )
{
    return isMessagerFrame ? m_MessengerIsFullSize : m_HomeFrameFullSize;
}

//============================================================================
void HomeWindow::help( void )
{
	//QMessageBox::information( this, tr( "Dynamic Layouts Help" ),
	//	tr( "This example shows how to change layouts "
	//		"dynamically." ) );
}

//============================================================================
void HomeWindow::createAppletLaunchPage( void )
{
	m_AppletLaunchPage = new AppletLaunchPage( getMyApp(), m_HomeFrameUpperLeft, eAppletHomePage, OBJNAME_APPLET_LAUNCH_PAGE );
	connect( m_AppletLaunchPage, SIGNAL( signalBackButtonClicked() ), this, SLOT( help() ) );
}

//============================================================================
void HomeWindow::createMessengerPage( void )
{
	m_MessengerPage = new MessengerPage( getMyApp(), m_HomeFrameRight );
	connect( m_MessengerPage, SIGNAL( signalBackButtonClicked() ), this, SLOT( help() ) );
}

//============================================================================
void HomeWindow::slotHomeButtonClicked( void )
{

}

//============================================================================
void HomeWindow::slotFrameResized( void )
{
    emit signalMainWindowResized();
}

//============================================================================
MyIcons& HomeWindow::getMyIcons( void )
{
	return m_MyApp.getMyIcons();
}

//============================================================================
void HomeWindow::closeEvent(QCloseEvent *event)
{
    if( !QWidget::isMaximized() && !QWidget::isMinimized() )
    {
        QByteArray saveGeom = saveGeometry();
        m_WindowSettings->setValue( "mainWindowGeometry", saveGeom );
    }

    //settings.setValue( "mainWindowState", saveState() );
	QDialog::closeEvent( event );
}
