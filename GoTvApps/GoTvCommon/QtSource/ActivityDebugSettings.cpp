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

#include "ActivityDebugSettings.h"
#include "AppCommon.h"
#include "AppSettings.h"

#include <CoreLib/VxDebug.h>

namespace
{
	const int MAX_LOG_EDIT_BLOCK_CNT = 1000;
}

//============================================================================
ActivityDebugSettings::ActivityDebugSettings( AppCommon& app, QWidget * parent )
: ActivityBase( OBJNAME_ACTIVITY_DEBUG_SETTINGS, app, parent, eAppletMessenger, true )
, m_bLogToFile(false)
, m_u32LogFlags( 0xff )
{
	ui.setupUi(this);
    connectBarWidgets();

	//connect( ui.LogToFileCheckBox, SIGNAL(clicked()), this, SLOT(slotLogToFileCheckBox()));

	connect( ui.m_TitleBarWidget,	SIGNAL(signalBackButtonClicked()),		this, SLOT(slotHomeButtonClicked()) );
	connect( ui.m_FullLogButton,	SIGNAL(clicked()),						this, SLOT(onFullLogButtonClicked()) );
	connect( ui.m_ErrorLogButton,	SIGNAL(clicked()),						this, SLOT(onErrorLogButtonClicked()) );
	connect( ui.m_StatusLogButton,	SIGNAL(clicked()),						this, SLOT(onStatusLogButtonClicked()) );
	//BRJ.. seems if logs too fast then get read violation error
	//connect( &m_MyApp,				SIGNAL(signalLog(int,QString)),			this, SLOT(slotLog(int,QString)) );

	ui.m_LogEdit->setMaximumBlockCount( MAX_LOG_EDIT_BLOCK_CNT );

	updateDialogFromProfile();
}

//============================================================================
void ActivityDebugSettings::slotLogToFileCheckBox( void )
{
	//m_bLogToFile = ui.LogToFileCheckBox->isChecked();
}

//============================================================================
void ActivityDebugSettings::slotHomeButtonClicked( void )
{
	hide();
}

//============================================================================
void ActivityDebugSettings::onFullLogButtonClicked( void )
{
	m_u32LogFlags = 0xff;
	ui.m_LogEdit->clear();
	m_MyApp.getEngine().fromGuiSendLog( m_u32LogFlags );
}

//============================================================================
void ActivityDebugSettings::onErrorLogButtonClicked( void )
{
	m_u32LogFlags = LOG_ERROR;
	ui.m_LogEdit->clear();
	m_MyApp.getEngine().fromGuiSendLog( m_u32LogFlags );
}

//============================================================================
void ActivityDebugSettings::onStatusLogButtonClicked( void )
{
	m_u32LogFlags = LOG_STATUS;
	ui.m_LogEdit->clear();
	m_MyApp.getEngine().fromGuiSendLog( m_u32LogFlags );
}

//============================================================================
/////////////////////////////////////////////////////////////////////////////
//============================================================================
void ActivityDebugSettings::updateDialogFromProfile( void )
{
	m_bLogToFile	= (bool)m_MyApp.getAppSettings().m_strDebugFileName.length() ? true : false;
	//m_u32LogFlags	= m_MyApp.getAppSettings().m_u32LogFlags;
	updateCheckBoxes();
}

//============================================================================
void ActivityDebugSettings::updateCheckBoxes( void )
{
	//ui.DisableUdpCheckBox->setChecked( m_bDisableUdp );
	//ui.LogToFileCheckBox->setChecked( m_bLogToFile );
}

//============================================================================
void ActivityDebugSettings::updateProfileFromSettings( void )
{
	//m_MyApp.getAppSettings().m_u32LogFlags		= m_u32LogFlags;
	m_MyApp.getAppSettings().m_u32LogToFile		= m_bLogToFile;

	m_MyApp.getAppSettings().saveDebugSettings();
}

//============================================================================
void ActivityDebugSettings::slotLog( int logFlags, QString strMsg )
{
	//strMsg.remove(QRegExp("[\\n\\r]"));
	if( m_u32LogFlags & logFlags )
	{
		ui.m_LogEdit->appendPlainText( strMsg );
	}
}
