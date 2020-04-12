//============================================================================
// Copyright (C) 2015 Brett R. Jones 
// Issued to MIT style license by Brett R. Jones in 2017
//
// You may use, copy, modify, merge, publish, distribute, sub-license, and/or sell this software 
// provided this Copyright is not modified or removed and is included all copies or substantial portions of the Software
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// bjones.engineer@gmail.com
// http://www.nolimitconnect.com
//============================================================================

#include "TitleBarWidget.h"
#include "MyIcons.h"
#include "AppCommon.h"

namespace
{
    const int MIN_CAM_PREVIEW_HEIGHT = 30;
    const int MIN_CAM_PREVIEW_WIDTH = 30;
}

//============================================================================
TitleBarWidget::TitleBarWidget( QWidget * parent )
: QWidget( parent )
, m_MyApp( GetAppInstance() )
, m_MuteMic( false )
, m_MuteSpeaker( false )
, m_EchoCancelEnabled( false )
{
	ui.setupUi( this );
	ui.m_StatusLabel->setVisible( false );
	ui.m_CamPreviewScreen->setImageFromFile( ":/AppRes/Resources/ic_cam_black.png" );
	m_MuteMic			= GetAppInstance().getEngine().fromGuiIsMicrophoneMuted();
	m_MuteSpeaker		= GetAppInstance().getEngine().fromGuiIsSpeakerMuted();
	m_EchoCancelEnabled = GetAppInstance().getEngine().fromGuiIsEchoCancelEnabled();

	ui.m_GoTvButton->setUseTheme( false );
	ui.m_GoTvButton->setProperty("GoTvIcon", true);
	ui.m_GoTvButton->setAppIcon( eMyIconApp, parent );
    if( parent )
    {
        connect( ui.m_GoTvButton, SIGNAL( signalAppIconSpecialClick() ), parent, SLOT( slotAppIconSpecialClick() ) );
    }

	setPowerButtonIcon();
	setHomeButtonIcon();
	setMicrophoneIcon( m_MuteMic ? eMyIconMicrophoneOff : eMyIconMicrophoneOn );
	setSpeakerIcon( m_MuteSpeaker ? eMyIconSpeakerOff : eMyIconSpeakerOn );
	setCameraIcon();
	setTrashButtonIcon();
	setShareButtonIcon();
	setTopMenuButtonIcon();
	setBackButtonIcon();

	enableAudioControls( false );
	enableVideoControls( false );

	setCameraButtonVisibility( false );
	setTrashButtonVisibility( false );
	setShareButtonVisibility( false );
	setMenuTopButtonVisibility( false );

	// everyone except home page has home button and back button but not power off button
	setPowerButtonVisibility( false );
	//setHomeButtonVisibility( true );
    setHomeButtonVisibility( false );
    setBackButtonVisibility( true );

	connect( ui.m_PowerOffButton,			SIGNAL(clicked()),		this, SLOT(slotPowerButtonClicked()) );
	connect( ui.m_HomeButton,				SIGNAL( clicked() ),	this, SLOT( slotHomeButtonClicked() ) );
	connect( ui.m_BackDlgButton,			SIGNAL( clicked() ),	this, SLOT( slotBackButtonClicked() ) );
	connect( ui.m_MuteMicButton,			SIGNAL(clicked()),		this, SLOT(slotMuteMicButtonClicked()) );
	connect( ui.m_MuteSpeakerButton,		SIGNAL(clicked()),		this, SLOT(slotMuteSpeakerButtonClicked()) );
	connect( ui.m_CameraButton,				SIGNAL(clicked()),		this, SLOT(slotCameraSnapshotButtonClicked()) );
	connect( ui.m_CamPreviewScreen,			SIGNAL(clicked()),		this, SLOT(slotCamPreviewClicked()) );
	connect( &m_MyApp,						SIGNAL(signalStatusMsg(QString)),	this, SLOT(slotTitleStatusBarMsg(QString)) );
	connect( &m_MyApp,						SIGNAL(signalToGuiPluginStatus(EPluginType,int,int)),	this, SLOT(slotToGuiPluginStatus(EPluginType,int,int)) );
    connect( &m_MyApp,                      SIGNAL( signalNetAvailStatus( ENetAvailStatus ) ), this, SLOT( slotToGuiNetAvailStatus( ENetAvailStatus ) ) );
}

//============================================================================
MyIcons&  TitleBarWidget::getMyIcons( void )
{
	return m_MyApp.getMyIcons();
}

//============================================================================
QLabel * TitleBarWidget::getTitleStatusBarLabel( void )
{
	return ui.m_StatusLabel;
}

//============================================================================
VxPushButton * TitleBarWidget::getAppIconPushButton( void )
{
	return ui.m_GoTvButton;
}

//============================================================================
void TitleBarWidget::setTitleBarText( QString titleText )
{
	ui.StyledDlgTitleLabel->setText( titleText );
}

//============================================================================
void TitleBarWidget::setTitleStatusBarMsg( QString statusMsg )
{
	slotTitleStatusBarMsg( statusMsg );
}

//============================================================================
void TitleBarWidget::slotTitleStatusBarMsg( QString msg )
{
	ui.m_StatusLabel->setText( msg );
}

//============================================================================
void TitleBarWidget::slotToGuiPluginStatus( EPluginType ePluginType, int statusType, int statusValue )
{
	if( ( ePluginTypeCamServer == ePluginType )
		&& ( 1 == statusType ) )
	{
		if( statusValue < 0 )
		{
			ui.m_CamClientCountLabel->setText("");
		}
		else
		{
			ui.m_CamClientCountLabel->setText( QString("%1").arg(statusValue) );
		}
	}
}

//============================================================================
void TitleBarWidget::enableVideoControls( bool enable )
{
	ui.m_CamPreviewScreen->setVisible( enable );
	ui.m_CamClientCountLabel->setVisible( enable );
}

//============================================================================
void TitleBarWidget::enableAudioControls( bool enable )
{
	ui.m_MuteMicButton->setVisible( enable );
	ui.m_MuteSpeakerButton->setVisible( enable );
}

//============================================================================
void TitleBarWidget::slotPowerButtonClicked( void )
{
	emit signalPowerButtonClicked();
}

//============================================================================
void TitleBarWidget::slotHomeButtonClicked( void )
{
	emit signalHomeButtonClicked();
}

//============================================================================
void TitleBarWidget::slotMuteMicButtonClicked( void )
{
	m_MuteMic = !m_MuteMic;
	setMicrophoneIcon( m_MuteMic ? eMyIconMicrophoneOff : eMyIconMicrophoneOn );
	emit signalMuteMicButtonClicked( m_MuteMic );
}

//============================================================================
void TitleBarWidget::slotMuteSpeakerButtonClicked( void )
{
	m_MuteSpeaker = !m_MuteSpeaker;
	setSpeakerIcon( m_MuteSpeaker ? eMyIconSpeakerOff : eMyIconSpeakerOn );
	emit signalMuteSpeakerButtonClicked( m_MuteSpeaker );
}

//============================================================================
void TitleBarWidget::slotCameraSnapshotButtonClicked( void )
{
	emit signalCameraSnapshotButtonClicked();
}

//============================================================================
void TitleBarWidget::slotCamPreviewClicked( void )
{
	emit signalCamPreviewClicked();
}

//============================================================================
void TitleBarWidget::slotTrashButtonClicked( void )
{
	emit signalTrashButtonClicked();
}

//============================================================================
void TitleBarWidget::slotShareButtonClicked( void )
{
	emit signalShareButtonClicked();
}

//============================================================================
void TitleBarWidget::slotMenuTopButtonClicked( void )
{
	emit signalMenuTopButtonClicked();
}

//============================================================================
void TitleBarWidget::slotBackButtonClicked( void )
{
	emit signalBackButtonClicked();
}

//======= button visibility ====//
//============================================================================
void TitleBarWidget::setBackButtonVisibility( bool visible )
{
    ui.m_BackDlgButton->setVisible( visible );
}

//============================================================================
void TitleBarWidget::setCamPreviewVisibility( bool visible )
{
	ui.m_CamPreviewScreen->setVisible( visible );
}

//============================================================================
void TitleBarWidget::setCamViewerCountVisibility( bool visible )
{
	ui.m_CamClientCountLabel->setVisible( visible );
}

//============================================================================
void TitleBarWidget::setPowerButtonVisibility( bool visible )
{
	ui.m_PowerOffButton->setVisible( visible );
}

//============================================================================
void TitleBarWidget::setHomeButtonVisibility( bool visible )
{
	ui.m_HomeButton->setVisible( visible );
}

//============================================================================
void TitleBarWidget::setTrashButtonVisibility( bool visible )
{
	ui.m_TrashButton->setVisible( visible );
}

//============================================================================
void TitleBarWidget::setShareButtonVisibility( bool visible )
{
	ui.m_ShareButton->setVisible( visible );
}

//============================================================================
void TitleBarWidget::setMenuTopButtonVisibility( bool visible )
{
	ui.m_MenuTopButton->setVisible( visible );
}

//============================================================================
void TitleBarWidget::setMuteSpeakerVisibility( bool visible )
{
	ui.m_MuteSpeakerButton->setVisible( visible );
}

//============================================================================
void TitleBarWidget::setMuteMicrophoneVisibility( bool visible )
{
	ui.m_MuteMicButton->setVisible( visible );
}

//============================================================================
void TitleBarWidget::setCameraButtonVisibility( bool visible )
{
	ui.m_CameraButton->setVisible( visible );
}

//============ set button icon ============//
//============================================================================
void TitleBarWidget::setPowerButtonIcon( EMyIcons myIcon )
{
	ui.m_PowerOffButton->setIcon( myIcon );
}

//============================================================================
void TitleBarWidget::setHomeButtonIcon( EMyIcons myIcon )
{
	ui.m_HomeButton->setIcon( myIcon );
}

//============================================================================
void TitleBarWidget::setMicrophoneIcon( EMyIcons myIcon )
{
	ui.m_MuteMicButton->setIcon( myIcon );
}

//============================================================================
void TitleBarWidget::setSpeakerIcon( EMyIcons myIcon )
{
	ui.m_MuteSpeakerButton->setIcon( myIcon );
}

//============================================================================
void TitleBarWidget::setCameraIcon( EMyIcons myIcon )
{
	ui.m_CameraButton->setIcon( myIcon );
}

//============================================================================
void TitleBarWidget::setTrashButtonIcon( EMyIcons myIcon )
{
	ui.m_TrashButton->setIcon( myIcon );
}

//============================================================================
void TitleBarWidget::setShareButtonIcon( EMyIcons myIcon )
{
	ui.m_ShareButton->setIcon( myIcon );
}

//============================================================================
void TitleBarWidget::setTopMenuButtonIcon( EMyIcons myIcon )
{
	ui.m_MenuTopButton->setIcon( myIcon );
}

//============================================================================
void TitleBarWidget::setBackButtonIcon( EMyIcons myIcon )
{
	ui.m_BackDlgButton->setIcon( myIcon );
}

//============ set button color ============//
//============================================================================
void TitleBarWidget::setPowerButtonColor( QColor iconColor )
{
	ui.m_PowerOffButton->setIconColor( iconColor );
}

//============================================================================
void TitleBarWidget::setHomeButtonColor( QColor iconColor )
{
	ui.m_HomeButton->setIconColor( iconColor );
}

//============================================================================
void TitleBarWidget::setMicrophoneColor( QColor iconColor )
{
	ui.m_BackDlgButton->setIconColor( iconColor );
}

//============================================================================
void TitleBarWidget::setSpeakerColor( QColor iconColor )
{
	ui.m_MuteMicButton->setIconColor( iconColor );
}

//============================================================================
void TitleBarWidget::setCameraColor( QColor iconColor )
{
	ui.m_CameraButton->setIconColor( iconColor );
}

//============================================================================
void TitleBarWidget::setTrashButtonColor( QColor iconColor )
{
	ui.m_TrashButton->setIconColor( iconColor );
}

//============================================================================
void TitleBarWidget::setShareButtonColor( QColor iconColor )
{
	ui.m_ShareButton->setIconColor( iconColor );
}

//============================================================================
void TitleBarWidget::setTopMenuButtonColor( QColor iconColor )
{
	ui.m_MenuTopButton->setIconColor( iconColor );
}

//============================================================================
void TitleBarWidget::setBackButtonColor( QColor iconColor )
{
	ui.m_BackDlgButton->setIconColor( iconColor );
}

//============================================================================
void TitleBarWidget::slotToGuiNetAvailStatus( ENetAvailStatus eNetAvailStatus )
{
    ui.m_NetAvailStatusWidget->toGuiNetAvailStatus( eNetAvailStatus );
}
