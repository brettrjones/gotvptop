#pragma once

#include "config_gotvapps.h"
#include "AppDefs.h"

#include "ui_HomeWindow.h"
#include <QDialog>
#include <QQueue>

class AppCommon;
class VxAppDisplay;
class AppletLaunchPage;
class PageMediaPlayer;
class MessengerPage;
class VxFrame;

class QDialogButtonBox;
class QGroupBox;
class QComboBox;
class QSettings;

class HomeWindow : public QDialog 
{
	Q_OBJECT
public:
	HomeWindow( AppCommon&	appCommon, QString title );
    virtual ~HomeWindow() override = default;

	AppCommon&					getMyApp( void ) { return m_MyApp; }
	MyIcons&					getMyIcons( void );

	void						initializeHomePage( void );

	void						launchApplet( EApplet applet );
	void						switchWindowFocus( QWidget * goTvButton );

    void						setIsMaxScreenSize( bool isMessagerFrame, bool isFullSizeWindow );
    bool						getIsMaxScreenSize( bool isMessagerFrame );

	QFrame *					getAppletFrame( EApplet applet );
	QFrame *					getMessengerParentFrame( void );

signals:
	void						signalMainWindowResized( void );
	void						signalDeviceOrientationChanged( int qtOrientation ); // pass on signal that orientation has changed

private slots:
	void						slotDeviceOrientationChanged( int qtOrientation ); // from m_AppDisplay
	void						help( void );
	void						slotHomeButtonClicked( void );
	void						slotFrameResized( void );
    void                        accept() override;
    void                        reject() override;

protected:
    void                        showEvent( QShowEvent * ev ) override;
    void						resizeEvent( QResizeEvent * ) override;
    void						closeEvent( QCloseEvent * ) override;

	void						initializeGoTvDynamicLayout( void );
	void						createAppletLaunchPage( void );
	void						createMessengerPage( void );

	//=== vars ===//
	Ui::HomeWindowClass			ui;
	AppCommon&					m_MyApp;
    VxAppDisplay&               m_AppDisplay;
	QString						m_AppTitle;
    QSettings *                 m_WindowSettings;

    Qt::Orientation				m_Orientation;
	EHomeLayout					m_LastHomeLayout;
	QGridLayout *				m_MainLayout;
	VxFrame *					m_HomeFrameUpperLeft;
	VxFrame *					m_HomeFrameRight;
	VxFrame *					m_HomeFrameBottom;

	PageMediaPlayer *			m_MediaPlayerPage;
	AppletLaunchPage *			m_AppletLaunchPage;
	QWidget *					m_MessengerParent;
	MessengerPage *				m_MessengerPage;

	bool						m_MessengerIsFullSize;
	bool						m_HomeFrameFullSize;

	//=== demo mode vars ===//
	QGroupBox *					rotableGroupBox;
	QQueue<QWidget *>			rotableWidgets;

	QGroupBox *					optionsGroupBox;
	QLabel *					buttonsOrientationLabel;
	QComboBox *					buttonsOrientationComboBox;

	QDialogButtonBox *			buttonBox;
	QPushButton *				closeButton;
	QPushButton *				helpButton;
	QPushButton *				rotateWidgetsButton;

	QGridLayout *				rotableLayout;
	QGridLayout *				optionsLayout;
    bool                        m_EngineInitialized;

};

