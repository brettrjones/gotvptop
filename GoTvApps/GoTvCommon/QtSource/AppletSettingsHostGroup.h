#pragma once
//============================================================================
// Copyright (C) 2020 Brett R. Jones
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

#include "AppletBase.h"
#include "PluginSettingsWidget.h"
#include "PermissionWidget.h"

#include <GoTvInterface/IToGui.h>
#include <GoTvCore/GoTvP2P/PluginSettings/PluginSettingMgr.h>

#include "ui_AppletSettingsHostGroup.h"
 
class AppletSettingsHostGroup : public AppletBase
{
	Q_OBJECT
public:
    AppletSettingsHostGroup( AppCommon& app, QWidget * parent );
	virtual ~AppletSettingsHostGroup();

    PluginSettingsWidget*       getPluginSettingsWidget()           { return ui.m_PluginSettingsWidget; }
    PermissionWidget*           getRelayWidget()                    { return ui.m_RelayPermissionWidget; }
    PermissionWidget*           getConnectionTestWidget()           { return ui.m_ConnectTestPermissinWidget; }

protected slots:
    void                        slotApplyServiceSettings();

protected:
    void                        connectServiceWidgets();
    void                        loadPluginSetting();
    void                        savePluginSetting();
    void                        loadUiFromSetting();
    void                        saveUiToSetting();

    Ui::AppletSettingsHostGroupUi     ui;
    PluginSetting               m_PluginSetting;
    EFriendState                m_OrigPermissionLevel = eFriendStateIgnore;
    EFriendState                m_OrigRelayPermission = eFriendStateIgnore;
    EFriendState                m_OrigConnectTestPermission = eFriendStateIgnore;
};


