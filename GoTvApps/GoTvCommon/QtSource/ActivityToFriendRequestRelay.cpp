//============================================================================
// Copyright (C) 2013 Brett R. Jones
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
#include "ActivityToFriendRequestRelay.h"
#include "ActivityMessageBox.h"

#include "AppGlobals.h"
#include "AppCommon.h"
#include "MyIcons.h"

#include <QFileDialog>

//============================================================================
ActivityToFriendRequestRelay::ActivityToFriendRequestRelay(	AppCommon&	app, 
															VxNetIdent * poFriend, 
															QWidget * parent )
	: ActivityBase( OBJNAME_ACTIVITY_TO_FRIEND_REQUEST_RELAY, app, parent, eAppletMessenger, true )
	, m_ePluginType(ePluginTypeRelay)
	, m_Friend( poFriend )
{ 
	ui.setupUi(this);
	ui.m_TitleBarWidget->setTitleBarText( QObject::tr("Request Relay Service") );

    connectBarWidgets();

	connect( ui.m_TitleBarWidget, SIGNAL(signalBackButtonClicked()), this, SLOT(accept()) );
	connect( ui.TestButton, SIGNAL(clicked()), this, SLOT(onTestButClick()) );
	connect( ui.AcceptButton, SIGNAL(clicked()), this, SLOT(onAcceptButClick()) );
	connect( ui.CancelButton, SIGNAL(clicked()), this, SLOT(onCancelButClick()) );
	connect( &m_MyApp, SIGNAL(signalLog(int,QString)), this, SLOT(slotLog(int,QString)) );

	EFriendState hisPermissionToMe = m_Friend->getHisFriendshipToMe();
	setHisPermissionToMe( hisPermissionToMe );
	EFriendState myPermissionToHim = m_Friend->getMyFriendshipToHim();
	setMyPermissionToHim( myPermissionToHim );
}

//============================================================================
void ActivityToFriendRequestRelay::setHisPermissionToMe( EFriendState hisFriendshipToMe )
{
	ui.m_HisPermissionButton->setIcon( getMyIcons().getFriendshipIcon( hisFriendshipToMe ) );
	QString strHisFriendship = m_Friend->getOnlineName();
	strHisFriendship += QObject::tr( "\'s Friendship To Me-" );
	strHisFriendship += DescribeFriendState( hisFriendshipToMe );
	ui.m_HisPermissionLabel->setText(strHisFriendship);
}

//============================================================================
void ActivityToFriendRequestRelay::setMyPermissionToHim( EFriendState myFriendshipToHim )
{
	ui.m_MyPermissionButton->setIcon( getMyIcons().getFriendshipIcon( myFriendshipToHim ) );
	QString strHisName = m_Friend->getOnlineName();
	QString strMyFriendship = QObject::tr( "My Friendship To " );
	strMyFriendship += strHisName + "-" + DescribeFriendState( myFriendshipToHim );
	ui.m_MyPermissionLabel->setText(strMyFriendship);
}

//============================================================================
bool ActivityToFriendRequestRelay::verifyUserInput( void )
{
	return false;
}

//============================================================================
void ActivityToFriendRequestRelay::onTestButClick()
{
	if( false == m_FromGui.fromGuiMakePluginOffer(	m_ePluginType, 
													m_Friend->getMyOnlineId(), 
													0,
													"ActionTest",
													"",
													0, m_Friend->getMyOnlineId() ) )
	{
		ActivityMessageBox errMsgBox( m_MyApp, this, LOG_INFO, "%s is offline", m_Friend->getOnlineName() );
		errMsgBox.exec();
	}
}

//============================================================================  
void ActivityToFriendRequestRelay::onAcceptButClick()
{
	m_Friend->setIsMyPreferedRelay( true );
	m_FromGui.fromGuiUseRelay( m_Friend->getMyOnlineId(), true ); 
	//VxNetIdent * poMyIdent = GetAppGlobals()->getUserIdent();
	//poMyIdent->useAsRelay( m_Friend );

	accept();
}

//============================================================================   
void ActivityToFriendRequestRelay::onCancelButClick()
{
	m_Friend->setIsMyPreferedRelay( false );
	m_FromGui.fromGuiUseRelay( m_Friend->getMyOnlineId(), false ); 
	reject();
}

//============================================================================   
void ActivityToFriendRequestRelay::slotLog( int logFlags, QString strMsg )
{
	if( ePluginTypeRelay == ( logFlags >> 16) )
	{
		ui.RelayLogEdit->append(strMsg);
	}
}

