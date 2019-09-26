//============================================================================
// Copyright (C) 2010 Brett R. Jones
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
// http://www.gotvptop.com
//============================================================================

#include "AppletNetworkSettings.h"
#include "AppCommon.h"
#include "AppSettings.h"
#include "MyIcons.h"

#include <CoreLib/VxDebug.h>

//============================================================================
AppletNetworkSettings::AppletNetworkSettings( AppCommon& app, QWidget * parent )
: AppletBase( OBJNAME_APPLET_NETWORK_SETTINGS, app, parent )
//, m_SavedNetworkSettings( eNetworkSettingsTypeUnknown )
//, m_CurNetworkSettings( eNetworkSettingsTypeUnknown )
{
	setAppletType( eAppletNetworkSettings );
	ui.setupUi( getContentItemsFrame() );
	setTitleBarText( DescribeApplet( m_EAppletType ) );
	//ui.m_NetworkSettingsExampleButton->setIcon( eMyIconPeople );
	//fillNetworkSettingsCombo();
 //   fillExampleCombo();

	//connect( ui.m_AcceptCancelFrame, SIGNAL( signalAccepted() ), this, SLOT( slotNetworkSettingsAccepted() ) );
	//connect( this, SIGNAL( signalBackButtonClicked() ), this, SLOT( slotNetworkSettingsCanceled() ) );
	//connect( ui.m_AcceptCancelFrame, SIGNAL( signalCanceled() ), this, SLOT( slotNetworkSettingsCanceled() ) );
 //   connect( ui.m_ExampleCheckBox, SIGNAL( stateChanged(int) ), this, SLOT( slotCheckBoxClicked(int) ) );

	m_MyApp.activityStateChange( this, true );
}

//============================================================================
void AppletNetworkSettings::slotNetworkSettingsAccepted( void )
{
	//m_MyApp.getAppSettings().setLastSelectedNetworkSettings( m_CurNetworkSettings );
 //   getMyApp().getAppNetworkSettings().selectNetworkSettings( m_CurNetworkSettings );
 //   m_MyApp.activityStateChange( this, false );
    close();
}

//============================================================================
void AppletNetworkSettings::onBackButtonClicked( void )
{
    slotNetworkSettingsCanceled();
}

//============================================================================
void AppletNetworkSettings::slotNetworkSettingsCanceled( void )
{
	//restoreSavedNetworkSettings();
    m_MyApp.activityStateChange( this, false );
    close();
}

//============================================================================
void AppletNetworkSettings::slotCheckBoxClicked( int checkedState )
{
    LogMsg( LOG_DEBUG,  "check box state %d", checkedState );
}

//============================================================================
void AppletNetworkSettings::fillNetworkSettingsCombo( void )
{
	//VxAppNetworkSettings& appNetworkSettings = getMyApp().getAppNetworkSettings();
	//for( int i = (int)(eNetworkSettingsTypeUnknown + 1); i < eMaxNetworkSettingsType; ++i )
	//{
	//	ui.m_NetworkSettingsComboBox->addItem( appNetworkSettings.describeNetworkSettings( ( ENetworkSettingsType )i ) );
	//}

	//m_SavedNetworkSettings = getMyApp().getAppSettings().getLastSelectedNetworkSettings();
	//m_CurNetworkSettings = m_SavedNetworkSettings;
	//if( ( eNetworkSettingsTypeUnknown < m_CurNetworkSettings )
	//	&& ( eMaxNetworkSettingsType > m_CurNetworkSettings ) )
	//{
	//	ui.m_NetworkSettingsComboBox->setCurrentIndex( (int)(m_CurNetworkSettings - 1) );
	//}

	//connect( ui.m_NetworkSettingsComboBox, SIGNAL( currentIndexChanged( int ) ), this, SLOT( slotNetworkSettingsSelectionChanged( int ) ) );
}

//============================================================================
void AppletNetworkSettings::fillExampleCombo( void )
{
    //ui.m_ExampleComboBox->addItem( QObject::tr( "Selection 1" ) );
    //ui.m_ExampleComboBox->addItem( QObject::tr( "Selection 2" ) );
    //ui.m_ExampleComboBox->addItem( QObject::tr( "Selection 3" ) );
    //ui.m_ExampleComboBox->addItem( QObject::tr( "Selection 4" ) );
    //ui.m_ExampleComboBox->addItem( QObject::tr( "Selection 5" ) );
    //ui.m_ExampleComboBox->setCurrentIndex( 0 );
}

//============================================================================
void AppletNetworkSettings::slotNetworkSettingsSelectionChanged( int idx )
{
	//applyNetworkSettings( ( ENetworkSettingsType )( idx + 1 ) );
}

//============================================================================
void AppletNetworkSettings::saveCurrentNetworkSettings( void )
{
	
}

//============================================================================
void AppletNetworkSettings::applyNetworkSettings( void )
{
	//m_CurNetworkSettings = themeType;
	//getMyApp().getAppNetworkSettings().selectNetworkSettings( m_CurNetworkSettings );
}

//============================================================================
void AppletNetworkSettings::restoreSavedNetworkSettings( void )
{
	//getMyApp().getAppNetworkSettings().selectNetworkSettings( m_SavedNetworkSettings );
}
