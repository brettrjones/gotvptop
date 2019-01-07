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
// brett.jones@engineer.com
// http://www.gotvptop.net
//============================================================================

#include "ActivityBase.h"

#include <PktLib/VxCommon.h>
#include <QDialog>
#include "ui_ActivityToFriendChangeFriendship.h"

class Friend;


class ActivityToFriendChangeFriendship : public ActivityBase
{
	Q_OBJECT
public:

	ActivityToFriendChangeFriendship( AppCommon& app, QWidget * parent = NULL );
	virtual ~ActivityToFriendChangeFriendship();

	//=== helpers ===//
	//! set friend to change your permission to him   
	void						setFriend( VxNetIdent * poFriend );
	//! get current permission selection
	EFriendState				getPermissionSelection( void );
	//! set which radio button is checked
	void						setCheckedPermission( EFriendState eMyFriendshipToHim );

public slots:
	void						onOkButClick( void );
	void						onCancelButClick( void ); 
	void						onPermissionClick( void );

protected:
	void						setHisPermissionToMe( EFriendState hisFriendshipToMe );
	void						setMyPermissionToHim( EFriendState myFriendshipToHim );

	//=== vars ===//
	Ui::ToFriendChangeFriendshipDlg	ui;
	VxNetIdent *				m_Friend;					
};