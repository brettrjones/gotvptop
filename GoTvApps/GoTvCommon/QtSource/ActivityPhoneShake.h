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

#include <GoTvInterface/IDefs.h>
#include <GoTvInterface/IToGui.h>
#include <QString>
#include <QDialog>
#include "ui_ActivityPhoneShake.h"

class VxNetIdent;

class ActivityPhoneShake : public ActivityBase
{
	Q_OBJECT
public:
	ActivityPhoneShake(	AppCommon& app, EScanType	eSearchType, QWidget * parent = NULL );
	virtual ~ActivityPhoneShake() override = default;

    // overrides required for dialogs with there own title bar and bottom bar widgets
    virtual TitleBarWidget *	getTitleBarWidget( void ) override { return ui.m_TitleBarWidget; }
    virtual BottomBarWidget *	getBottomBarWidget( void ) override { return ui.m_BottomBarWidget; }

	EScanType					getScanType() { return m_eScanType; }
	void						searchResult( VxNetIdent * netIdent );
	void						setTitle( QString strTitle );

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
	Ui::PhoneShakeDlgClass		ui;
	EScanType					m_eScanType;
};
