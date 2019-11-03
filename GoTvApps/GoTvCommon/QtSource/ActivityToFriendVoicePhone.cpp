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
// http://www.nolimitconnect.com
//============================================================================

#include "ActivityToFriendVoicePhone.h"
#include "GuiOfferSession.h"
#include "AppGlobals.h"
#include "MyIcons.h"

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>

//============================================================================
ActivityToFriendVoicePhone::ActivityToFriendVoicePhone(	AppCommon&			app,
														VxNetIdent *			hisIdent, 
														QWidget *				parent )
: ActivityToFriendBase( OBJNAME_ACTIVITY_TO_FRIEND_VOICE_PHONE, app, ePluginTypeVoicePhone, hisIdent, parent, eAppletMessenger, true )
{
	setupActivityVoicePhone();
	m_OfferSessionLogic.sendOfferOrResponse();
}

//============================================================================
ActivityToFriendVoicePhone::ActivityToFriendVoicePhone(	AppCommon&			app,
														GuiOfferSession *		offerSession, 
														QWidget *				parent )
: ActivityToFriendBase( OBJNAME_ACTIVITY_TO_FRIEND_VOICE_PHONE, app, ePluginTypeVoicePhone, offerSession, parent, eAppletMessenger, true )
{
	setupActivityVoicePhone();
	m_OfferSessionLogic.sendOfferOrResponse();
}

//============================================================================
void ActivityToFriendVoicePhone::setupActivityVoicePhone( void )
{
	ui.setupUi( this );
	setupBaseWidgets( ui.m_TitleBarWidget, ui.m_FriendIdentWidget, ui.m_PermissionButton, ui.m_PermissionLabel );
    QString titleText = QObject::tr("Voice Phone (VOIP) - ");
    titleText += m_HisIdent->getOnlineName();
    ui.m_TitleBarWidget->setTitleBarText( titleText );
	ui.m_TitleBarWidget->enableAudioControls( true );
    connectBarWidgets();
	ui.m_InstMsgWidget->setInstMsgWidgets( m_ePluginType, m_HisIdent );
	ui.m_HangUpButton->setIcon( eMyIconVoicePhoneCancel );
	connect( ui.m_HangUpButton, SIGNAL(clicked()), this, SLOT(reject()) );
}

//============================================================================
void ActivityToFriendVoicePhone::doToGuiRxedPluginOffer( void * callbackData, GuiOfferSession * offer )
{
	m_OfferSessionLogic.doToGuiRxedPluginOffer( offer );
}

//============================================================================
void ActivityToFriendVoicePhone::doToGuiRxedOfferReply( void * callbackData, GuiOfferSession * offerSession )
{
	m_OfferSessionLogic.doToGuiRxedOfferReply( offerSession );
}

//============================================================================
//! called by base class with in session state
void ActivityToFriendVoicePhone::onInSession( bool isInSession )
{
	if( isInSession )
	{
		setStatusText( QObject::tr( "In Voice Phone Session" ) );
	}
	else
	{
		setStatusText( QObject::tr( "Voice Phone Session Ended" ) );
	}
}

//============================================================================
void ActivityToFriendVoicePhone::toGuiInstMsg( void * callbackData, VxNetIdent * friendIdent, EPluginType ePluginType, QString instMsg )
{
	Q_UNUSED( callbackData );
	if( ( ePluginType == m_ePluginType )
		&& m_HisIdent 
		&& ( m_HisIdent->getMyOnlineId() == friendIdent->getMyOnlineId() ) )
	{
		ui.m_InstMsgWidget->toGuiInstMsg( instMsg );
	}
}; 

