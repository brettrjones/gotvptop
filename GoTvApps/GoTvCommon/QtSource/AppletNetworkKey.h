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

#include "ui_AppletNetworkKey.h"

#include "AppletBase.h"
#include "AppDefs.h"


class AppletNetworkKey : public AppletBase
{
	Q_OBJECT
public:
	AppletNetworkKey( AppCommon& app, QWidget * parent );
	virtual ~AppletNetworkKey(){};

    // override default behavior of closing dialog when back button is clicked
    virtual void				onBackButtonClicked( void );


protected slots:
	void						slotNetworkKeySelectionChanged( int idx );
	void						slotNetworkKeyAccepted( void );
	void						slotNetworkKeyCanceled( void );
    void				        slotCheckBoxClicked( int checkedState );

protected:
	void						fillNetworkKeyCombo( void );
    void                        fillExampleCombo( void );

	void						saveCurrentNetworkKey( void );
	void						applyNetworkKey( void );
	void						restoreSavedNetworkKey( void );

	Ui::AppletNetworkKeyWidget	ui;
	QString					    m_SavedNetworkKey;
    QString					    m_CurNetworkKey;
};


