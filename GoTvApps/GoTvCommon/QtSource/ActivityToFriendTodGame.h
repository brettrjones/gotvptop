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
// http://www.nolimitconnect.com
//============================================================================

#include "ActivityToFriendBase.h"
#include "TodGameLogic.h"

#include "ui_ActivityToFriendTodGame.h"

class GuiOfferSession;

class ActivityToFriendTodGame : public ActivityToFriendBase
{
	Q_OBJECT

public:
	ActivityToFriendTodGame(	AppCommon&			app,
								VxNetIdent *			netIdent, 
								QWidget *				parent = NULL );

	ActivityToFriendTodGame(	AppCommon&			app,
								GuiOfferSession *		poOffer, 
								QWidget *				parent = NULL );

	virtual ~ActivityToFriendTodGame() override = default;

    // overrides required for dialogs with there own title bar and bottom bar widgets
    virtual TitleBarWidget *	getTitleBarWidget( void ) override { return ui.m_TitleBarWidget; }
    virtual BottomBarWidget *	getBottomBarWidget( void ) override { return ui.m_BottomBarWidget; }

	//! called by base class with in session state
    virtual void				onInSession( bool isInSession ) override;
	//! called after session end or dialog exit
	virtual void				onEndSession( void );

protected:
	// override of ToGuiActivityInterface
    virtual void				doToGuiRxedPluginOffer( void * callbackData, GuiOfferSession * offer ) override;
    virtual void				doToGuiRxedOfferReply( void * callbackData, GuiOfferSession * offer ) override;

	void						setupActivityToFriendTodGame( void );
    void						toGuiInstMsg( void * callbackData, VxNetIdent * friendIdent, EPluginType ePluginType, QString instMsg ) override;

	//=== vars ===//
	Ui::ToFriendTodGameDialog	ui;
	TodGameLogic				m_TodGameLogic;
};
