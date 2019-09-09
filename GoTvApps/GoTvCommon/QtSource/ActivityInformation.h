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

class AppCommon;

class ActivityInformation : public ActivityBase
{
	Q_OBJECT

public:

    ActivityInformation( AppCommon& app, QWidget * parent, EPluginType pluginType );
	virtual ~ActivityInformation() = default;

    void						setPluginType( EPluginType pluginType ) { m_PluginType = pluginType; updateInformation(); }
    EPluginType                 getPluginType() { return m_PluginType; }

	void						updateDialogFromProfile();
	void						updateProfileFromSettings();

protected slots:

	void						slotLog( int iPluginNum, QString strMsg );
	void						slotHomeButtonClicked( void );
	void						onFullLogButtonClicked( void );
	void						onErrorLogButtonClicked( void );
	void						onStatusLogButtonClicked( void );

	void						slotLogToFileCheckBox();

protected:
    void						initActivityInformation( void );
    void						updateInformation( void );
    QString                     getInfoText( void );
    
    void						updateCheckBoxes();

	//=== vars ===//
	Ui::InformationDialog		ui;
    EPluginType                 m_PluginType = ePluginTypeInvalid;
};
