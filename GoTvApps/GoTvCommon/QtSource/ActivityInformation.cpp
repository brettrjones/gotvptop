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

#include "ActivityInformation.h"
#include "AppCommon.h"
#include "AppSettings.h"

#include <CoreLib/VxDebug.h>

namespace
{
	const int MAX_LOG_EDIT_BLOCK_CNT = 1000;
}

//============================================================================
ActivityInformation::ActivityInformation( AppCommon& app, QWidget * parent, EPluginType pluginType )
: ActivityBase( OBJNAME_ACTIVITY_INFORMATION, app, parent, eAppletMessenger, Qt::SubWindow )
, m_PluginType( pluginType )
{
    initActivityInformation();
}

//============================================================================
void ActivityInformation::initActivityInformation( void )
{
    ui.setupUi( this );

    //connect( ui.LogToFileCheckBox, SIGNAL(clicked()), this, SLOT(slotLogToFileCheckBox()));

    //connect( ui.m_FullLogButton,	SIGNAL(clicked()),						this, SLOT(onFullLogButtonClicked()) );
    //connect( ui.m_ErrorLogButton,	SIGNAL(clicked()),						this, SLOT(onErrorLogButtonClicked()) );
    //connect( ui.m_StatusLogButton,	SIGNAL(clicked()),						this, SLOT(onStatusLogButtonClicked()) );
    //BRJ.. seems if logs too fast then get read violation error
    //connect( &m_MyApp,				SIGNAL(signalLog(int,QString)),			this, SLOT(slotLog(int,QString)) );

    //ui.m_LogEdit->setMaximumBlockCount( MAX_LOG_EDIT_BLOCK_CNT );

    updateDialogFromProfile();
    updateInformation();
}

//============================================================================
void ActivityInformation::updateInformation( void )
{
    if( m_PluginType == ePluginTypeInvalid )
    {
        return;
    }

    ui.m_ServiceInfoButton->setIcon( m_MyApp.getMyIcons().getPluginIcon( m_PluginType ) );
    switch( m_PluginType )
    {
    case ePluginTypeGroupUser:
    case ePluginTypeGroupHost:
    case ePluginTypeGroupAnchor:
    case ePluginTypeNetworkHost:
        ui.m_PictureLabel->setResourceImage( ":/AppRes/Resources/NetworkDesign.png" );
        ui.m_PictureLabel->setVisible( true );
        break;
    default:
        ui.m_PictureLabel->setVisible( false );
        break;
    }
   
    ui.m_InfoText->appendPlainText( getInfoText() );
}

//============================================================================
QString ActivityInformation::getInfoText( void )
{
    return QString( QObject::tr( "Test Text" ) );
}

//============================================================================
void ActivityInformation::slotLogToFileCheckBox( void )
{
	//m_bLogToFile = ui.LogToFileCheckBox->isChecked();
}

//============================================================================
void ActivityInformation::slotHomeButtonClicked( void )
{
	hide();
}

//============================================================================
void ActivityInformation::onFullLogButtonClicked( void )
{
	//ui.m_LogEdit->clear();
	//m_MyApp.getEngine().fromGuiSendLog( m_u32LogFlags );
}

//============================================================================
void ActivityInformation::onErrorLogButtonClicked( void )
{
	//ui.m_LogEdit->clear();
	//m_MyApp.getEngine().fromGuiSendLog( m_u32LogFlags );
}

//============================================================================
void ActivityInformation::onStatusLogButtonClicked( void )
{
	//ui.m_LogEdit->clear();
	//m_MyApp.getEngine().fromGuiSendLog( m_u32LogFlags );
}

//============================================================================
/////////////////////////////////////////////////////////////////////////////
//============================================================================
void ActivityInformation::updateDialogFromProfile( void )
{
	//m_bLogToFile	= (bool)m_MyApp.getAppSettings().m_strDebugFileName.length() ? true : false;
	//m_u32LogFlags	= m_MyApp.getAppSettings().m_u32LogFlags;
	//updateCheckBoxes();
}

//============================================================================
void ActivityInformation::updateCheckBoxes( void )
{
	//ui.DisableUdpCheckBox->setChecked( m_bDisableUdp );
	//ui.LogToFileCheckBox->setChecked( m_bLogToFile );
}

//============================================================================
void ActivityInformation::updateProfileFromSettings( void )
{
	//m_MyApp.getAppSettings().m_u32LogFlags		= m_u32LogFlags;
	//m_MyApp.getAppSettings().m_u32LogToFile		= m_bLogToFile;

	//m_MyApp.getAppSettings().saveDebugSettings();
}

//============================================================================
void ActivityInformation::slotLog( int logFlags, QString strMsg )
{
	//strMsg.remove(QRegExp("[\\n\\r]"));
	//if( m_u32LogFlags & logFlags )
	//{
	//	ui.m_LogEdit->appendPlainText( strMsg );
	//}
}
