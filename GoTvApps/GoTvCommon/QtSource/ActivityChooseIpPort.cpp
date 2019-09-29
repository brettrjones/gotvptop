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

#include "ActivityChooseIpPort.h"
#include "AppCommon.h"
#include "AppGlobals.h"
#include "VxDataHelper.h"

#include <GoTvCore/GoTvP2P/P2PEngine/EngineSettings.h>
#include <NetLib/VxGetRandomPort.h>

#include <QMessageBox>

//============================================================================
ActivityChooseIpPort::ActivityChooseIpPort(	AppCommon& app, QWidget * parent )
: ActivityBase( OBJNAME_ACTIVITY_CHOOSE_IP_PORT, app, parent )
, m_MyApp( app )
, m_Engine( app.getEngine() )
{
	ui.setupUi(this);
    connectBarWidgets();

	connect( ui.m_TitleBarWidget, SIGNAL(signalBackButtonClicked()), this, SLOT(reject()) );
	connect( ui.CancelButton, SIGNAL(clicked()), this, SLOT(reject()) );
	connect( ui.OkButton, SIGNAL(clicked()), this, SLOT(applyResultsAndExit()) );
	connect( ui.RandomPortButton, SIGNAL(clicked()), this, SLOT(chooseRandomPort()) );

	updateValues();
}

//============================================================================
void ActivityChooseIpPort::updateValues()
{
	uint16_t u16TcpPort = m_Engine.getEngineSettings().getTcpIpPort();
	QString strPort;
	strPort.sprintf("%d", u16TcpPort);
	ui.IpPortEdit->setText(strPort);
}

//============================================================================
void ActivityChooseIpPort::applyResultsAndExit()
{
	QString strResult = ui.IpPortEdit->text();
	uint16_t u16TcpPort = (uint16_t)strResult.toLong();
	m_Engine.getEngineSettings().setTcpIpPort( u16TcpPort );
	m_Engine.getMyPktAnnounce().setMyOnlinePort( u16TcpPort );
	m_MyApp.getAppGlobals().getUserIdent()->m_DirectConnectId.setPort( u16TcpPort );
	m_MyApp.getDataHelper().updateAccount( * m_MyApp.getAppGlobals().getUserIdent() );

	accept();
}

//============================================================================
void ActivityChooseIpPort::chooseRandomPort()
{
	uint16_t u16TcpPort = VxGetRandomTcpPort();
	QString strPort;
	strPort.sprintf("%d", u16TcpPort);
	ui.IpPortEdit->setText(strPort);
}
