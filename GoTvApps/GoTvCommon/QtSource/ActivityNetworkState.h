#pragma once
//============================================================================
// Copyright (C) 2016 Brett R. Jones
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
#include <QDialog>
#include "ui_ActivityNetworkStatus.h"

#include <CoreLib/VxDefs.h>
#include <GoTvInterface/IToGui.h>

class AppCommon;
class P2PEngine;

class ActivityNetworkState : public ActivityBase
{
	Q_OBJECT
public:
	ActivityNetworkState( AppCommon& app, QWidget * parent = NULL );
    virtual ~ActivityNetworkState();

protected slots:
	void						gotoWebsite( void );
	void						slotNetworkStateChanged( ENetworkStateType eNetworkState );

protected:
	void						setupActivityNetworkState( void );

	void						showNoInternetHelp( void );
	void						showDiscoverNetworkHelp( void );
	void						showRelaySearchHelp( void );
	void						showDirectConnectMessage( void );
	void						showRelayConnectedHelp( void );
	void						showAnchorError( void );

	void						clearHelpLines( void );
	void						setHelpLine( int lineIdx, QString helpText );

	//=== vars ===//
	Ui::ActivityNetworkStatusClass	ui;

};
