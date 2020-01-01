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
// http://www.nolimitconnect.com
//============================================================================

#include "ActivityBase.h"

#include "ui_ActivityDebugSettings.h"

#include <GoTvCore/GoTvP2P/P2PEngine/EngineSettings.h>
#include <CoreLib/AppErr.h>

class AppCommon;
class P2PEngine;

class ActivityDebugSettings : public ActivityBase
{
	Q_OBJECT

public:

	ActivityDebugSettings( AppCommon& app, QWidget * parent = NULL );
	virtual ~ActivityDebugSettings() override = default;

    // overrides required for dialogs with there own title bar and bottom bar widgets
    virtual TitleBarWidget *	getTitleBarWidget( void ) override { return ui.m_TitleBarWidget; }
    virtual BottomBarWidget *	getBottomBarWidget( void ) override { return ui.m_BottomBarWidget; }

	void						updateDialogFromProfile();
	void						updateProfileFromSettings();

protected slots:

	void						slotLog( int iPluginNum, QString strMsg );
    void						slotHomeButtonClicked( void ) override;
	void						onFullLogButtonClicked( void );
	void						onErrorLogButtonClicked( void );
	void						onStatusLogButtonClicked( void );

	void						slotLogToFileCheckBox();

protected:
	void						updateCheckBoxes();

	//=== vars ===//
	Ui::DebugSettingsDialog		ui;
	bool						m_bLogToFile;
	uint32_t					m_u32LogFlags;
};
