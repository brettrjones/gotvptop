#pragma once
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

#include "AppletBase.h"
#include <GoTvInterface/IToGui.h>

#include "ui_AppletServiceBaseSettings.h"

class AppletServiceBaseSettings : public AppletBase
{
	Q_OBJECT
public:
    AppletServiceBaseSettings( const char * objName, AppCommon& app, QWidget * parent );
	virtual ~AppletServiceBaseSettings() = default;

    // override so we do initialization after applet type is set
    //void						setAppletType( EApplet applet )	override;
    void						setPluginType( EPluginType pluginType );

    virtual QLabel *            getServiceTitle() { return ui.m_ServiceTitleLabel; }
    //virtual QLabel *            getStatusLabel() { return ui.m_StatusLabel; }
    //virtual QLabel *            getServiceStatusLabel() { return ui.m_ServiceStatusLabel; }

    virtual QLabel *            getServiceUrlLabel() { return ui.m_UrlDescriptionLabel; }
    virtual QLineEdit *         getServiceUrlEdit() { return ui.m_UrlEdit; }

    virtual QLabel *            getServiceNameLabel() { return ui.m_UserDisplayedNameLabel; }
    virtual QLabel *            getServiceDescriptionLabel() { return ui.m_DescriptionLabel; }

    virtual QLineEdit *         getServiceNameEdit() { return ui.m_NameEdit; }
    virtual QPlainTextEdit *    getServiceDescriptionEdit() { return ui.m_DescriptionEdit; }

    virtual QPushButton *       getStartButton() { return ui.m_StartButton; }
    virtual QPushButton *       getStopButton() { return ui.m_StopButton; }

    virtual PermissionWidget *  getPermissionWidget() { return ui.m_PermissionWidget; }
    virtual InformationWidget * getInformationWidget() { return ui.m_InfoWidget; }
    virtual LogWidget *         getLogWidget() { return ui.m_LogWidget; }

protected:
    virtual void                setupServiceApplet();
    virtual void                connectServiceWidgets();
    virtual void                loadServiceFromSettings();
    virtual void                saveServiceToSettings();



    Ui::AppletServiceBaseSettingsUi ui;

    QWidget *                   m_HostServiceWidget;
    EPluginType                 m_PluginType = ePluginTypeInvalid;
};


