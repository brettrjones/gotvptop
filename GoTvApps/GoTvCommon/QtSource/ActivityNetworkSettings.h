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
#include "ui_ActivityNetworkSettings.h"

#include <GoTvCore/GoTvP2P/P2PEngine/EngineSettings.h>

#include <QDialog>

class VxNetIdent;

class ActivityNetworkSettings : public ActivityBase
{
	Q_OBJECT

public:
	ActivityNetworkSettings(	AppCommon& app,
								QWidget * parent = NULL );
	virtual ~ActivityNetworkSettings();

public slots:
	void						slotExitButtonClick( void );
	void						slotGoToAnchorSettingsButtonClick( void );
	void						slotRandomPortButtonClick( void );
	void						slotRunIsPortOpenButtonClick( void );
	void						slotExternIpHelpButtonClick( void );

	void						slotAutoDetectProxyClick( void );
	void						slotNoProxyClick( void );
	void						slotYesProxyClick( void );
	void						slotUseUpnpCheckBoxClick( void );

protected:
	void						SetFirewallTest( EngineSettings::EFirewallTestType eFirewallType );

	void						connectSignals( void );
	void						updateDlgFromSettings( void );
	void						updateSettingsFromDlg( void );

	//=== vars ===//
	Ui::NetworkSettingsDlg		ui; 
	NetSettings					m_NetSettings;
};
