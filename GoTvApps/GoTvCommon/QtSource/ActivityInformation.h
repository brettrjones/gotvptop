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

#include "ActivityBase.h"
#include <GoTvInterface/IDefs.h>

#include "ui_ActivityInformation.h"

enum EInfoType
{
    eInfoTypeInvalid,
    eInfoTypePlugin,
    eInfoTypePermission,
    eInfoTypeNetworkKey,
    eInfoTypeNetworkHost,


    eMaxInfoType // must be last
};

class AppCommon;

class ActivityInformation : public ActivityBase
{
	Q_OBJECT

public:

    ActivityInformation( AppCommon& app, QWidget * parent, EPluginType pluginType );
    ActivityInformation( AppCommon& app, QWidget * parent, EInfoType infoType );

	virtual ~ActivityInformation() override = default;

    // overrides required for dialogs with there own title bar and bottom bar widgets
    virtual TitleBarWidget *	getTitleBarWidget( void ) override { return ui.m_TitleBarWidget; }
    virtual BottomBarWidget *	getBottomBarWidget( void ) override { return ui.m_BottomBarWidget; }

    void						setPluginType( EPluginType pluginType ) { m_InfoType = eInfoTypePlugin; m_PluginType = pluginType; updateInformation(); }
    void						setInformationType( EInfoType infoType ) { m_InfoType = infoType; updateInformation(); }

    EPluginType                 getPluginType() { return m_PluginType; }

protected slots:
	void						slotCopyToClipboardButtonClicked( void );

protected:
    virtual void				showEvent( QShowEvent * ev ) override;

    void						initActivityInformation( void );
    void						updateInformation( void );
    QString                     getInfoText( void );

	//=== vars ===//
	Ui::InformationDialog		ui;
    EInfoType                   m_InfoType = eInfoTypeInvalid;
    EPluginType                 m_PluginType = ePluginTypeInvalid;

    static QString              m_NoInfoAvailable;
    static QString              m_NetworkDesign;
    static QString              m_PluginDefinitions;
    static QString              m_Permissions;
    static QString              m_NetworkKey;
    static QString              m_NetworkHost;
};