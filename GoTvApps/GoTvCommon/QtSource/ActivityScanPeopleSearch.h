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

#include <GoTvInterface/IDefs.h>
#include <QString>
#include <QDialog>
#include "ui_ActivityScanPeopleSearch.h"

class VxNetIdent;

class ActivityScanPeopleSearch : public ActivityBase
{
	Q_OBJECT
public:
	ActivityScanPeopleSearch(	AppCommon&		app, 
								EScanType			eSearchType,
								QWidget *			parent = NULL );
	//=== destructor ===//
	virtual ~ActivityScanPeopleSearch();

	EScanType					getScanType() { return m_eScanType; }
	void						searchResult( VxNetIdent * netIdent );
	void						setTitle( QString strTitle );
	void						setStatusLabel( QString strMsg );

	virtual void				toGuiSearchResultSuccess( void * callbackData, EScanType eScanType, VxNetIdent * netIdent );
	virtual void				toGuiClientScanSearchComplete( void * callbackData, EScanType eScanType );	

signals:
	void						signalSearchResult( VxNetIdent * netIdent );
	void						signalSearchComplete( void );

private slots:
	void						slotSearchResult( VxNetIdent * netIdent );
	void						slotSearchComplete( void );
	void						slotHomeButtonClicked( void );
	void						slotStartSearchClicked();
	void						slotStopSearchClicked();
	//void						slotFriendClicked( VxNetIdent * netIdent );

protected:
	void						showEvent( QShowEvent * ev );
	void						hideEvent( QHideEvent * ev );

	//=== vars ===//
	Ui::PeopleSearchDlg			ui;
	EScanType					m_eScanType;
};
