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
#pragma once

#include "AppletBase.h"

#include "ui_AppletCreateAccount.h"

class AppletCreateAccount : public AppletBase
{
	Q_OBJECT
public:
    AppletCreateAccount( AppCommon& app, QWidget * parent );
	virtual ~AppletCreateAccount();

    void						setRootUserDataDirectory( const char * userDir ) { m_strRootUserDataDir = userDir; };
    //! validate user input
    bool						wasLoginNameEntered( void );

private slots:
    //! login was clicked
    void						buttonLoginClicked( void );

protected:
    bool						accountValidate( void );

    //=== vars ===//
    Ui::AppletCreateAccountClass		ui;
    VxNetIdent					m_UserAccount;
    std::string					m_strRootUserDataDir;
};


