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
// http://www.gotvptop.com
//============================================================================

#include "ActivityNetworkKey.h"
#include "AppCommon.h"
#include "ActivityAnchorSettings.h"
#include "ActivityIsPortOpenTest.h"
#include "AppGlobals.h"

#include <GoTvCore/GoTvP2P/P2PEngine/EngineSettings.h>
#include <GoTvCore/GoTvP2P/P2PEngine/EngineSettingsDefaultValues.h>
#include <NetLib/VxGetRandomPort.h>
#include <NetLib/VxSktUtil.h>

#include <QMessageBox>

//============================================================================
ActivityNetworkKey::ActivityNetworkKey( AppCommon& app, QWidget * parent )
: ActivityBase( OBJNAME_ACTIVITY_NETWORK_SETTINGS, app, parent, eAppletMessenger, true )
{
	ui.setupUi(this);
	ui.m_TitleBarWidget->setTitleBarText( QObject::tr("Network Settings") );
    connectBarWidgets();

	connectSignals();
	updateDlgFromSettings();
}

//============================================================================
void ActivityNetworkKey::connectSignals( void )
{
	connect( ui.m_TitleBarWidget,					SIGNAL(signalBackButtonClicked()), this, SLOT( slotExitButtonClick() ) );
}

//============================================================================
void ActivityNetworkKey::updateDlgFromSettings()
{
}

//============================================================================
void ActivityNetworkKey::updateSettingsFromDlg()
{
}

//============================================================================
void ActivityNetworkKey::slotExitButtonClick()
{
	updateSettingsFromDlg();
	m_Engine.fromGuiNetworkSettingsChanged();
	accept();
}

//============================================================================
void ActivityNetworkKey::slotGoToAnchorSettingsButtonClick()
{

	ActivityAnchorSettings * dlg = new ActivityAnchorSettings( 
		m_MyApp,
		this			);
	dlg->exec();
}

//============================================================================
void ActivityNetworkKey::slotAutoDetectProxyClick( void )
{
	SetFirewallTest( EngineSettings::eFirewallTestUrlConnectionTest );
}

//============================================================================
void ActivityNetworkKey::slotNoProxyClick( void )
{
	SetFirewallTest( EngineSettings::eFirewallTestAssumeNoFirewall );
}

//============================================================================
void ActivityNetworkKey::slotYesProxyClick( void )
{
	SetFirewallTest( EngineSettings::eFirewallTestAssumeFirewalled );
}

//============================================================================
void ActivityNetworkKey::SetFirewallTest( EngineSettings::EFirewallTestType eFirewallType )
{
}

//============================================================================
void ActivityNetworkKey::slotRandomPortButtonClick( void )
{
	//uint16_t u16TcpPort = VxGetRandomTcpPort();
	//QString strPort;
	//strPort.sprintf("%d", u16TcpPort);
	//ui.PortEdit->setText(strPort);
	//updateSettingsFromDlg();
}

//============================================================================
void ActivityNetworkKey::slotRunIsPortOpenButtonClick( void )
{
	//uint16_t u16Port = ui.PortEdit->text().toUShort();
	//if( 0 != u16Port )
	//{
	//	updateSettingsFromDlg();
	//	ActivityIsPortOpenTest * dlg = new ActivityIsPortOpenTest( 
	//		m_MyApp,
	//		u16Port,
	//		this			);
	//	dlg->exec();
	//}
	//else
	//{
	//	QMessageBox::information(this, tr("Error"), tr("TCP Port cannot be zero." ) );
	//}
}

//============================================================================
void ActivityNetworkKey::slotUseUpnpCheckBoxClick( void )
{
}

//============================================================================
void ActivityNetworkKey::slotExternIpHelpButtonClick( void )
{
	QMessageBox::information(this, tr("Information"), tr("You can determine your external IP Address by browsing to http://www.google.com and searching for 'what is my ip'." ) );
}