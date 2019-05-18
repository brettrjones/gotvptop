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

#include "ActivityEditAccount.h"
#include "AppCommon.h"
#include "AppGlobals.h"
#include "VxDataHelper.h"

#include <GoTvCore/GoTvP2P/P2PEngine/EngineSettings.h>
#include <NetLib/VxGetRandomPort.h>

#include <QMessageBox>

//============================================================================
ActivityEditAccount::ActivityEditAccount( AppCommon& app, QWidget * parent )
	: ActivityBase( "ActivityEditAccount", app, parent, eAppletMessenger, Qt::SubWindow )
{

	ui.setupUi(this);

	slotRepositionToParent();
	connect( ui.AcceptButton, SIGNAL(clicked()), this, SLOT(slotApplyResults()));
	connect( ui.CancelButton, SIGNAL(clicked()), this, SLOT(reject()) );
	connect( ui.m_TitleBarWidget, SIGNAL(signalBackButtonClicked()), this, SLOT(reject()) );

	updateValuesFromDatabase();
}

//============================================================================
ActivityEditAccount::~ActivityEditAccount()
{
}

//============================================================================
void ActivityEditAccount::updateValuesFromDatabase()
{
	m_MyIdent = m_MyApp.getAppGlobals().getUserIdent();

	QString strMoodMessage = m_MyIdent->getOnlineDescription();

	ui.AccountNameEdit->setText( strMoodMessage );
	static bool firstTime = true;
	if( firstTime )
	{
		m_strMoodMessage = strMoodMessage;
	}
}


//============================================================================
void ActivityEditAccount::slotApplyResults()
{
	/*
	if( false == validateUserName() )
	{
		return;
	}
	
	QString moodMsg = ui.AccountNameEdit->text();
	if( moodMsg.contains("'") )
	{
		QMessageBox::warning(this, QObject::tr("Invalid Mood Message"), QObject::tr("Mood Message cannot have special character quote." ) );
		return;   		 
	}

	if( moodMsg.contains("(") || moodMsg.contains(")") )
	{
		QMessageBox::warning(this, QObject::tr("Invalid Mood Message"), QObject::tr( "Mood Message cannot have special character parentheses." ) );
		return;   		 
	}

	if( moodMsg.contains("/") || moodMsg.contains("\\") )
	{
		QMessageBox::warning(this, QObject::tr("Invalid Mood Message"), QObject::tr("Mood Message cannot have special character slashes." ) );
		return;   		 
	}

	if( moodMsg.length() > ( MAX_ONLINE_NAME_LEN - 1 ) )
	{
		QMessageBox::warning(this, QObject::tr("Invalid Mood Message"), QObject::tr("Mood Message is too long (maximum 23 chars)." ) );
		return;
	}

	if( moodMsg.length() < 4 )
	{
		QMessageBox::warning(this, QObject::tr("Invalid Mood Message"), QObject::tr("Mood Message is too short (minimum 4 chars)." ) );
		return;
	}

	if( moodMsg.length() 
		&& ( moodMsg != m_strOnlineName ) )
	{
		std::string strOnlineName = ui.AccountNameEdit->text().toUtf8().constData();
		m_MyIdent->setOnlineName( strOnlineName.c_str() );
		g_oDataHelper.updateAccount( *m_MyIdent );
		m_Engine.getEngineSettings().setIniValue( "App", "LastLogin", strOnlineName );
		m_Engine.fromGuiOnlineNameChanged( strOnlineName.c_str() );
		QMessageBox::warning(this, tr("Application"), tr("You must restart the application" ) );
	}
	*/

	if( false == validateMoodMessage() )
	{
		return;
	}

	QString moodMsg = ui.AccountNameEdit->text();


	if( moodMsg.length() 
		&& ( moodMsg != m_strMoodMessage ) )
	{
		std::string strOnlineDesc = ui.AccountNameEdit->text().toUtf8().constData();
		m_MyIdent->setOnlineDescription( strOnlineDesc.c_str() );
		m_MyApp.getDataHelper().updateAccount( *m_MyIdent );
		m_Engine.fromGuiMoodMessageChanged( strOnlineDesc.c_str() );
	}

	accept();
}

//============================================================================
//! validate user input
bool ActivityEditAccount::validateMoodMessage( void )
{
	QString strUserName = ui.AccountNameEdit->text();
	if( strUserName.contains("'") )
	{
		QMessageBox::warning(this, tr("Application"), tr("Mood Message cannot have special character quote." ) );
		return false;   		 
	}

	if( strUserName.contains("(") || strUserName.contains(")") )
	{
		QMessageBox::warning(this, tr("Application"), tr( "Mood Message cannot have special character parentheses." ) );
		return false;   		 
	}

	if( strUserName.contains("/") || strUserName.contains("\\") )
	{
		QMessageBox::warning(this, tr("Application"), tr("Mood Message cannot have special character slashes." ) );
		return false;   		 
	}

	if( strUserName.length() >  ( MAX_ONLINE_DESC_LEN - 1 ) )
	{
		QMessageBox::warning(this, tr("Application"), tr("Mood Message is too long (maximum 27 chars)." ) );
		return false;
	}

	return true;
}


