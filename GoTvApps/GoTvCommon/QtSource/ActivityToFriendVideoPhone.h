#pragma once
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

#include "ActivityToFriendBase.h"

#include "ui_ActivityToFriendVideoPhone.h"

class P2PEngine;
class GuiOfferSession;

class ActivityToFriendVideoPhone : public ActivityToFriendBase
{
	Q_OBJECT

public:
	ActivityToFriendVideoPhone(	AppCommon&			app,
								VxNetIdent *			netIdent, 
								QWidget *				parent = NULL );

	ActivityToFriendVideoPhone(	AppCommon&			app,
								GuiOfferSession *		poOffer, 
								QWidget *				parent = NULL );

	virtual ~ActivityToFriendVideoPhone() override = default;

    // overrides required for dialogs with there own title bar and bottom bar widgets
    virtual TitleBarWidget *	getTitleBarWidget( void ) override { return ui.m_TitleBarWidget; }
    virtual BottomBarWidget *	getBottomBarWidget( void ) override { return ui.m_BottomBarWidget; }

	//! called by base class with in session state
	virtual void				onInSession( bool isInSession );

protected:
	// override of ToGuiActivityInterface
	virtual void				doToGuiRxedPluginOffer( void * callbackData, GuiOfferSession * offer );
	virtual void				doToGuiRxedOfferReply( void * callbackData, GuiOfferSession * offer );

	void						setupActivityVideoPhone();
	void						toGuiInstMsg( void * callbackData, VxNetIdent * friendIdent, EPluginType ePluginType, QString instMsg );

	//=== vars ===//
	Ui::ToFriendVideoPhoneDialog	ui;
};

