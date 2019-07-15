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
#include "ui_ActivityAnchorSettings.h"

#include <GoTvCore/GoTvP2P/P2PEngine/EngineSettings.h>
#include <GoTvInterface/IToGui.h>

#include <QDialog>

class VxNetIdent;

class ActivityAnchorSettings : public ActivityBase
{
	Q_OBJECT

public:
	ActivityAnchorSettings(	AppCommon& app,
							QWidget * parent = NULL );
	virtual ~ActivityAnchorSettings();

public slots:
	void						slotHomeButtonClicked();
	void						onVerifySettingsButtonClick( void );
	void						onComboBoxSelectionChange(const QString& anchorSettingName);
	void						onManageSettingsButtonClick( void );
	void						onAttemptedSettingsChangeClick( void );

protected:
	void						closeEvent(QCloseEvent *event);
	void						connectSignals( void );
	void						updateDlgFromSettings( void );
	void						updateSettingsFromDlg( void );
	void						populateDlgFromAnchorSetting( AnchorSetting& anchorSetting );

	//=== vars ===//
	Ui::AnchorSettingsDlg		ui; 
	NetSettings					m_NetSettings;

	std::string					m_OrigAnchorUrl;
	std::string					m_OrigNetworkName;
	std::string					m_OrigConnectionTestUrl;
};
