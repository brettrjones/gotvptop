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

#include "AppletNetworkKey.h"
#include "AppCommon.h"
#include "AppSettings.h"
#include "MyIcons.h"

#include <CoreLib/VxDebug.h>

//============================================================================
AppletNetworkKey::AppletNetworkKey( AppCommon& app, QWidget * parent )
: AppletBase( OBJNAME_APPLET_NETWORK_KEY, app, parent )
, m_SavedNetworkKey( )
, m_CurNetworkKey()
{
	setAppletType( eAppletNetworkKey );
	ui.setupUi( getContentItemsFrame() );
	setTitleBarText( DescribeApplet( m_EAppletType ) );
	//ui.m_NetworkKeyExampleButton->setIcon( eMyIconPeople );
	//fillNetworkKeyCombo();
 //   fillExampleCombo();

	//connect( ui.m_AcceptCancelFrame, SIGNAL( signalAccepted() ), this, SLOT( slotNetworkKeyAccepted() ) );
	//connect( this, SIGNAL( signalBackButtonClicked() ), this, SLOT( slotNetworkKeyCanceled() ) );
	//connect( ui.m_AcceptCancelFrame, SIGNAL( signalCanceled() ), this, SLOT( slotNetworkKeyCanceled() ) );
 //   connect( ui.m_ExampleCheckBox, SIGNAL( stateChanged(int) ), this, SLOT( slotCheckBoxClicked(int) ) );

	m_MyApp.activityStateChange( this, true );
}

//============================================================================
void AppletNetworkKey::slotNetworkKeyAccepted( void )
{
	//m_MyApp.getAppSettings().setLastSelectedNetworkKey( m_CurNetworkKey );
    //getMyApp().getAppNetworkKey().selectNetworkKey( m_CurNetworkKey );
    m_MyApp.activityStateChange( this, false );
    close();
}

//============================================================================
void AppletNetworkKey::onBackButtonClicked( void )
{
    slotNetworkKeyCanceled();
}

//============================================================================
void AppletNetworkKey::slotNetworkKeyCanceled( void )
{
	restoreSavedNetworkKey();
    m_MyApp.activityStateChange( this, false );
    close();
}

//============================================================================
void AppletNetworkKey::slotCheckBoxClicked( int checkedState )
{
    LogMsg( LOG_DEBUG,  "check box state %d", checkedState );
}

//============================================================================
void AppletNetworkKey::fillNetworkKeyCombo( void )
{
	//VxAppNetworkKey& appNetworkKey = getMyApp().getAppNetworkKey();
	//for( int i = (int)(eNetworkKeyTypeUnknown + 1); i < eMaxNetworkKeyType; ++i )
	//{
	//	ui.m_NetworkKeyComboBox->addItem( appNetworkKey.describeNetworkKey( ( ENetworkKeyType )i ) );
	//}

	//m_SavedNetworkKey = getMyApp().getAppSettings().getLastSelectedNetworkKey();
	//m_CurNetworkKey = m_SavedNetworkKey;
	//if( ( eNetworkKeyTypeUnknown < m_CurNetworkKey )
	//	&& ( eMaxNetworkKeyType > m_CurNetworkKey ) )
	//{
	//	ui.m_NetworkKeyComboBox->setCurrentIndex( (int)(m_CurNetworkKey - 1) );
	//}

	//connect( ui.m_NetworkKeyComboBox, SIGNAL( currentIndexChanged( int ) ), this, SLOT( slotNetworkKeySelectionChanged( int ) ) );
}

//============================================================================
void AppletNetworkKey::fillExampleCombo( void )
{
    //ui.m_ExampleComboBox->addItem( QObject::tr( "Selection 1" ) );
    //ui.m_ExampleComboBox->addItem( QObject::tr( "Selection 2" ) );
    //ui.m_ExampleComboBox->addItem( QObject::tr( "Selection 3" ) );
    //ui.m_ExampleComboBox->addItem( QObject::tr( "Selection 4" ) );
    //ui.m_ExampleComboBox->addItem( QObject::tr( "Selection 5" ) );
    //ui.m_ExampleComboBox->setCurrentIndex( 0 );
}

//============================================================================
void AppletNetworkKey::slotNetworkKeySelectionChanged( int idx )
{
	//applyNetworkKey( ( ENetworkKeyType )( idx + 1 ) );
}

//============================================================================
void AppletNetworkKey::saveCurrentNetworkKey( void )
{
	
}

//============================================================================
void AppletNetworkKey::applyNetworkKey( void )
{
//	m_CurNetworkKey = themeType;
//	getMyApp().getAppNetworkKey().selectNetworkKey( m_CurNetworkKey );
}

//============================================================================
void AppletNetworkKey::restoreSavedNetworkKey( void )
{
	//getMyApp().getAppNetworkKey().selectNetworkKey( m_SavedNetworkKey );
}
