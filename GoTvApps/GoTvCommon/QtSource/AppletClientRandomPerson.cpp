//============================================================================
// Copyright (C) 2019 Brett R. Jones
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

#include "AppletClientRandomPerson.h"
#include "AppCommon.h"
#include "AppSettings.h"
#include "MyIcons.h"

#include <CoreLib/VxGlobals.h>
#include <CoreLib/VxDebug.h>

//============================================================================
AppletClientRandomPerson::AppletClientRandomPerson( AppCommon& app, QWidget * parent )
: AppletClientBase( OBJNAME_APPLET_CLIENT_RANDOM_PERSON, app, parent )
{
    setAppletType( eAppletClientRandomPerson );
    ui.setupUi( this );
	setTitleBarText( DescribeApplet( m_EAppletType ) );

    connectBarWidgets();

    connect( ui.m_SerchButton, SIGNAL( clicked() ), this, SLOT( slotSimulateShakeClicked() ) );
    connect( this, SIGNAL( signalSearchComplete() ), this, SLOT( slotSearchComplete() ) );
    connect( this, SIGNAL( signalSearchResult( VxNetIdent* ) ), this, SLOT( slotSearchResult( VxNetIdent* ) ) );
    connect( &app,
             SIGNAL( signalPhoneShakeStatus( EPhoneShakeStatus, QString ) ),
             this,
             SLOT( slotPhoneShakeStatus( EPhoneShakeStatus, QString ) ) );

	m_MyApp.activityStateChange( this, true );
}

//============================================================================
AppletClientRandomPerson::~AppletClientRandomPerson()
{
    m_MyApp.activityStateChange( this, false );
}

//============================================================================
void AppletClientRandomPerson::showEvent( QShowEvent * ev )
{
    ActivityBase::showEvent( ev );
    m_MyApp.wantToGuiActivityCallbacks( this, this, true );
}

//============================================================================
void AppletClientRandomPerson::hideEvent( QHideEvent * ev )
{
    m_MyApp.wantToGuiActivityCallbacks( this, this, false );
    ActivityBase::hideEvent( ev );
}

//============================================================================
void AppletClientRandomPerson::toGuiSearchResultSuccess( void * callbackData, EScanType eScanType, VxNetIdent * netIdent )
{
    Q_UNUSED( callbackData );
    if( VxIsAppShuttingDown() )
    {
        return;
    }

    if( eScanType == getScanType() )
    {
        emit signalSearchResult( netIdent );
    }
};

//============================================================================
void AppletClientRandomPerson::toGuiClientScanSearchComplete( void * callbackData, EScanType eScanType )
{
    Q_UNUSED( callbackData );
    if( VxIsAppShuttingDown() )
    {
        return;
    }

    if( eScanType == getScanType() )
    {
        emit signalSearchComplete();
    }
}

//============================================================================
void AppletClientRandomPerson::slotHomeButtonClicked( void )
{
}

//============================================================================
void AppletClientRandomPerson::slotSimulateShakeClicked( void )
{
    m_MyApp.playSound( eSndDefSending );
    ui.m_FriendListWidget->clear();
    m_MyApp.toGuiUserMessage( QObject::tr( "Contacting Network Host" ).toUtf8().constData() );
    m_FromGui.fromGuiStartScan( eScanTypeRandomPerson, 0, 0 );
}

//============================================================================
void AppletClientRandomPerson::slotSearchComplete( void )
{
    m_MyApp.toGuiUserMessage( QObject::tr( "Search Complete" ).toUtf8().constData() );
}

//============================================================================
void AppletClientRandomPerson::slotSearchResult( VxNetIdent * netIdent )
{
    m_MyApp.playSound( eSndDefUserBellMessage );
    QString foundMatch = QObject::tr( "Search Complete " );
    foundMatch += netIdent->getOnlineName();
    m_MyApp.toGuiUserMessage( foundMatch.toUtf8().constData(), netIdent->getOnlineName() );
    ui.m_FriendListWidget->updateFriend( netIdent, false );
}

//============================================================================
void AppletClientRandomPerson::slotPhoneShakeStatus( EPhoneShakeStatus eAnchorStatus, QString strMsg )
{
    m_MyApp.toGuiUserMessage( strMsg.toUtf8().constData() );
}
