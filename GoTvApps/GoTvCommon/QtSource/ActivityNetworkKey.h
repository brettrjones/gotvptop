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
// http://www.gotvptop.com
//============================================================================

#include "ActivityBase.h"
#include "ui_ActivityNetworkKey.h"

#include <GoTvCore/GoTvP2P/P2PEngine/EngineSettings.h>

#include <QDialog>

class VxNetIdent;

class ActivityNetworkKey : public ActivityBase
{
	Q_OBJECT

public:
	ActivityNetworkKey(	AppCommon& app,
								QWidget * parent = NULL );
	virtual ~ActivityNetworkKey() override = default;

    // overrides required for dialogs with there own title bar and bottom bar widgets
    virtual TitleBarWidget *	getTitleBarWidget( void ) override { return ui.m_TitleBarWidget; }
    virtual BottomBarWidget *	getBottomBarWidget( void ) override { return ui.m_BottomBarWidget; }

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
