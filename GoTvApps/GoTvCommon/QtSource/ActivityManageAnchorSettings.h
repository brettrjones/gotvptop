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
#include "ui_ActivityManageAnchorSettings.h"

#include <GoTvCore/GoTvP2P/P2PEngine/EngineSettings.h>
#include <GoTvInterface/IToGui.h>

#include <QDialog>

class VxNetIdent;
class QCloseEvent;

class ActivityManageAnchorSettings : public ActivityBase
{
	Q_OBJECT

public:
	ActivityManageAnchorSettings(	AppCommon& app,
									QWidget * parent = NULL );
	virtual ~ActivityManageAnchorSettings();

public slots:
	void						slotHomeButtonClicked( void );
	void						onSaveButtonClick();
	void						onDeleteButtonClick( void );
	void						onBeAnAnchorCheckBoxClick( void );
	void						onExcludeMeFromAnchorListCheckBoxClick( void );
	void						onComboBoxSelectionChange(const QString& anchorSettingName);
	void						onComboBoxTextChanged ( const QString & text );

protected:
	void						connectSignals( void );
	void						updateDlgFromSettings( void );
	void						updateSettingsFromDlg( void );
	void						populateDlgFromAnchorSetting( AnchorSetting& anchorSetting );
	void						closeEvent(QCloseEvent *event);

	//=== vars ===//
	Ui::ManageAnchorSettingsDlg	ui; 
	AppCommon&				m_MyApp;
	NetSettings					m_NetSettings;
};
