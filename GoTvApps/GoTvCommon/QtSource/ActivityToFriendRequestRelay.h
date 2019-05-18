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
// http://www.gotvptop.net
//============================================================================

#include "ActivityBase.h"

#include "ActivityBase.h"
#include "ui_ActivityToFriendRequestRelay.h"

class ActivityToFriendRequestRelay : public ActivityBase
{
	Q_OBJECT
public:
	ActivityToFriendRequestRelay(	AppCommon&	app, 
									VxNetIdent *	poFriend, 
									QWidget *		parent = NULL );
	virtual ~ActivityToFriendRequestRelay();

	void						setPluginType( EPluginType ePluginType );

public slots:
	void						onTestButClick(); 
	void						onAcceptButClick();
	void						onCancelButClick(); 
	void						slotLog( int iPluginNum, QString strMsg );


protected:
	//! Set plugin icon based on permission level
	void						setPluginIcon( EPluginType ePluginType, EFriendState ePluginPermission );
	bool						verifyUserInput( void );
	void						setHisPermissionToMe( EFriendState hisFriendshipToMe );
	void						setMyPermissionToHim( EFriendState myFriendshipToHim );

	//=== vars ===//
	Ui::ToFriendRequestRelayDialog ui;
	EPluginType					m_ePluginType;
	VxNetIdent *				m_Friend;

};
