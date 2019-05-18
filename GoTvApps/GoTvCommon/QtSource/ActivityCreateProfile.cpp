//============================================================================
// Copyright (C) 2010 Brett R. Jones
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

#include "ActivityCreateProfile.h"
#include "ActivityEditProfile.h"
#include "AppGlobals.h"
#include "AppCommon.h"
#include "VxDataHelper.h"
#include "AppSettings.h"

#include <GoTvCore/GoTvP2P/P2PEngine/EngineSettings.h>
#include <CoreLib/VxFileUtil.h>
#include <CoreLib/VxGlobals.h>

#include <QMessageBox>
#include <QUuid>

//============================================================================
ActivityCreateProfile::ActivityCreateProfile( AppCommon& app, QWidget * parent )
: ActivityBase( OBJNAME_ACTIVITY_CREATE_PROFILE, app, parent, eActivityCreateProfile )
{
	ui.setupUi( getContentItemsFrame() );
	connect( ui.loginButton, SIGNAL(clicked()), this, SLOT(buttonLoginClicked()));
}

//============================================================================
ActivityCreateProfile::~ActivityCreateProfile()
{
}

//============================================================================
//! button clicked
void ActivityCreateProfile::buttonLoginClicked( void )
{
	if( true == accountValidate() )
	{
		std::string strUserName = ui.userNameEdit->text().toUtf8().data();

		m_MyApp.loadAccountSpecificSettings( strUserName.c_str() );
		m_MyApp.createAccountForUser( strUserName, m_UserAccount, (const char *) ui.moodMessageEdit->text().toUtf8().data() );
		m_MyApp.setAccountUserName( strUserName.c_str() );

		// save ident to global
		memcpy( m_MyApp.getAppGlobals().getUserIdent(), &m_UserAccount, sizeof( VxNetIdent ));

		// fill in database info
		LogMsg( LOG_VERBOSE, "created acct name %s UUID 0x%llX 0x%llX\n", m_UserAccount.getOnlineName(), m_UserAccount.getMyOnlineIdLoPart(), m_UserAccount.getMyOnlineIdHiPart());
		if( true == m_MyApp.getDataHelper().insertAccount( m_UserAccount ) )
		{
			m_MyApp.getDataHelper().updateLastLogin( m_UserAccount.getOnlineName() );

			// give user a chance to edit his/her profile
			ActivityEditProfile oDlg( m_MyApp, VxGetUserSpecificDataDirectory().c_str(), 0 );
			if( QDialog::Rejected == oDlg.exec() )
			{
				reject();
			}
			else
			{
				accept();
			}
		}
		else
		{
			LogMsg( LOG_ERROR, "Insert New User into Database failed.");
			QMessageBox::warning(this, tr("Application"), tr("Insert New User into Database failed." ) );
			reject();
		}
	}   	
}

//============================================================================
//! validate user input
bool ActivityCreateProfile::accountValidate( void )
{
	QString strUserName = ui.userNameEdit->text();
	if( strUserName.contains("GoTv PtoP Web") 
		|| strUserName.contains("GoTvPtoPWeb")
		|| strUserName.contains("gotvptopweb")
		|| strUserName.contains("gotv ptop web")
        || strUserName.contains( "GoTv PtoP Web" )
        || strUserName.contains( "GoTvPtoPWeb" )
        || strUserName.contains( "gotvptopweb" )
        || strUserName.contains( "gotv ptop web" ) )
	{
		QMessageBox::warning(this, QObject::tr("Invalid User Name"), QObject::tr("User Name cannot have GoTv PtoP Web in name." ) );
		return false;   		 
	}

	if( strUserName.contains("'") ||  strUserName.contains("\"") )
	{
		QMessageBox::warning(this, QObject::tr("Invalid User Name"), QObject::tr("User Name cannot have special character quote." ) );
		return false;   		 
	}

	if( strUserName.contains(",") )
	{
		QMessageBox::warning(this, QObject::tr("Invalid User Name"), QObject::tr("User Name cannot have comma." ) );
		return false;   		 
	}

	if( strUserName.contains("(") || strUserName.contains(")") )
	{
		QMessageBox::warning(this, QObject::tr("Invalid User Name"), QObject::tr( "User Name cannot have special character parentheses." ) );
		return false;   		 
	}

	if( strUserName.contains("/") || strUserName.contains("\\") )
	{
		QMessageBox::warning(this, QObject::tr("Invalid User Name"), QObject::tr("User Name cannot have special character slashes." ) );
		return false;   		 
	}

	if( strUserName.length() > 23 )
	{
		QMessageBox::warning(this, QObject::tr("Invalid User Name"), QObject::tr("User Name is too long (maximum 23 chars)." ) );
		return false;
	}

	if( strUserName.length() < 4 )
	{
		QMessageBox::warning(this, QObject::tr("Invalid User Name"), QObject::tr("User Name is too short (minimum 4 chars)." ) );
		return false;
	}

	QString strMoodMsg = ui.moodMessageEdit->text();
	if( strUserName.contains("'") )
	{
		QMessageBox::warning(this, QObject::tr("Application"), QObject::tr("Mood Message cannot have special character quote." ) );
		return false;   		 
	}

	int iLen = strMoodMsg.length();
	if( iLen > 27 )
	{
		QMessageBox::warning(this, QObject::tr("Application"), QObject::tr("Mood Message is too long (maximum 27 chars)" ) );
		return false;
	}

	return true;
}

//============================================================================
bool ActivityCreateProfile::wasLoginNameEntered( void )
{
    QString strUserName = ui.userNameEdit->text();
    return strUserName.length() > 0 ? true : false;
}

