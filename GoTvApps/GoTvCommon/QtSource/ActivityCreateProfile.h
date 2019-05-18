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

#include <QDialog>
#include "ui_ActivityCreateProfile.h"

class AppCommon;
class P2PEngine;

class ActivityCreateProfile : public ActivityBase
{
	Q_OBJECT
public:
	ActivityCreateProfile( AppCommon& app, QWidget * parent = NULL );
	virtual ~ActivityCreateProfile();

	void						setRootUserDataDirectory( const char * userDir ) { m_strRootUserDataDir = userDir; };
	//! validate user input
	bool						accountValidate( void );
    bool						wasLoginNameEntered( void );

private slots:
	//! login was clicked
	void						buttonLoginClicked( void );

protected:
	//=== vars ===//
	Ui::createProfileDialog		ui;
	VxNetIdent					m_UserAccount;
	std::string					m_strRootUserDataDir;
};


