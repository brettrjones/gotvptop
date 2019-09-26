#pragma once
//============================================================================
// Copyright (C) 2010 Brett R. Jones
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

#include "ui_AppletNetworkSettings.h"

#include "AppletBase.h"
#include "AppDefs.h"


class AppletNetworkSettings : public AppletBase
{
	Q_OBJECT
public:
	AppletNetworkSettings( AppCommon& app, QWidget * parent );
	virtual ~AppletNetworkSettings(){};

    // override default behavior of closing dialog when back button is clicked
    virtual void				onBackButtonClicked( void );


protected slots:
	void						slotNetworkSettingsSelectionChanged( int idx );
	void						slotNetworkSettingsAccepted( void );
	void						slotNetworkSettingsCanceled( void );
    void				        slotCheckBoxClicked( int checkedState );

protected:
	void						fillNetworkSettingsCombo( void );
    void                        fillExampleCombo( void );

	void						saveCurrentNetworkSettings( void );
	void						applyNetworkSettings( void );
	void						restoreSavedNetworkSettings( void );

	Ui::AppletNetworkSettingsWidget		ui;
	//ENetworkSettingsType					m_SavedNetworkSettings;
	//ENetworkSettingsType					m_CurNetworkSettings;
};


