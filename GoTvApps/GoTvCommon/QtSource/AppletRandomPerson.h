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

#include "ui_AppletRandomPerson.h"

#include "AppletBase.h"
#include <GoTvInterface/IDefs.h>
#include <GoTvInterface/IToGui.h>

class AppletRandomPerson : public AppletBase
{
	Q_OBJECT
public:
	AppletRandomPerson( AppCommon& app, QWidget * parent );
	virtual ~AppletRandomPerson() override;

    EScanType					getScanType() { return m_eScanType; }
    void						searchResult( VxNetIdent * netIdent );

    virtual void				toGuiSearchResultSuccess( void * callbackData, EScanType eScanType, VxNetIdent * netIdent );
    virtual void				toGuiClientScanSearchComplete( void * callbackData, EScanType eScanType );

signals:
    void						signalSearchResult( VxNetIdent * netIdent );
    void						signalSearchComplete( void );

private slots:
    void						slotSearchResult( VxNetIdent * netIdent );
    void						slotSearchComplete();

    void						slotHomeButtonClicked( void );
    void						slotSimulateShakeClicked( void );
    void						slotPhoneShakeStatus( EPhoneShakeStatus eAnchorStatus, QString strMsg );

protected:
    virtual void				showEvent( QShowEvent * ev );
    virtual void				hideEvent( QHideEvent * ev );

    //=== vars ===//
    Ui::RandomPersonDlgClass	ui;
    EScanType					m_eScanType = eScanTypeRandomPerson;
};


