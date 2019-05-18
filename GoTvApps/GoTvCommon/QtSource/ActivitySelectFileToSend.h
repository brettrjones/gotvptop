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

#include <PktLib/VxCommon.h>

#include "ui_ActivitySelectFileToSend.h"

class ActivitySelectFileToSend : public ActivityBase
{
	Q_OBJECT
public:
	ActivitySelectFileToSend(	AppCommon&	app, 
								VxNetIdent *	hisIdent, 
								QWidget *		parent = NULL );

	virtual ~ActivitySelectFileToSend();

	void						setPluginType( EPluginType ePluginType );

protected slots:
	void						onBrowseLibraryButClick(); 
	void						onBrowseForFileButClick(); 
	void						onSendButClick();

protected:
	//! Set plugin icon based on permission level
	void						setPluginIcon( EPluginType ePluginType, EFriendState ePluginPermission );

	bool						verifyUserInput( void );

	//=== vars ===//
	Ui::SelectFileToSendDialog	ui;
	EPluginType					m_ePluginType;
	VxNetIdent *				m_HisIdent;
	VxGUID						m_LclSessionId;
};
