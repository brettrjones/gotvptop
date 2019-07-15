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

#include "ActivityAbout.h"
#include "AppCommon.h"

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>
#include <CoreLib/IsBigEndianCpu.h>
#include <CoreLib/VxGlobals.h>

#include <QDesktopServices>
#include <QUrl>

//============================================================================
ActivityAbout::ActivityAbout( AppCommon& app, QWidget * parent )
: ActivityBase( OBJNAME_ACTIVITY_ABOUT, app, parent, eAppletMessenger, Qt::SubWindow )
{
	ui.setupUi(this);
	ui.m_TitleBarWidget->setTitleBarText( QObject::tr("About ") );
	ui.m_AppNameLabel->setText( VxGetApplicationTitle() );
	ui.m_AppVersionLabel->setText( VxGetAppVersionString() );

	slotRepositionToParent();

	connect( ui.gotoWebsiteButton, SIGNAL(clicked()), this, SLOT(gotoWebsite()) );

	setupAboutMe();
}

//============================================================================
ActivityAbout::~ActivityAbout()
{
}

//============================================================================
void ActivityAbout::setupAboutMe( void )
{
    LogMsg( LOG_INFO, "htonl 4 = 0x%x\n", ntohl(4L) );
    VxNetIdent oMyIdent;
	m_FromGui.fromGuiQueryMyIdent( &oMyIdent );
	std::string strOnlineIp = oMyIdent.getOnlineIpAddress().toStdString();
	QString strText = QString("Online Name: %1").arg(oMyIdent.getOnlineName());
	ui.labelMeLine1->setText( QString("Online Name: %1").arg(oMyIdent.getOnlineName() ));
	std::string strMyId = oMyIdent.m_DirectConnectId.describeVxGUID();
	ui.labelMeLine2->setText( QString("Id: %1").arg( strMyId.c_str() ) );
	ui.labelMeLine3->setText( QString("My Node Url: http://%1:%2").arg( strOnlineIp.c_str() ).arg(oMyIdent.getOnlinePort()) );
	std::string strRelayId = oMyIdent.m_RelayConnectId.describeVxGUID();
	ui.labelMeLine4->setText( QString("Relay Id: %1").arg( strRelayId.c_str() ) );
	std::string strRelayIp = oMyIdent.getRelayIpAddress().toStdString();
	ui.labelMeLine5->setText( QString("Relay Ip: %1:%2").arg( strRelayIp.c_str() ).arg(oMyIdent.m_RelayConnectId.getPort() ) );
	ui.labelMeLine6->setText( QString("Requires Relay?: %1 Has Relay?: %2").arg( oMyIdent.requiresRelay()).arg( oMyIdent.hasRelay()) );
	ui.labelMeLine7->setText( QString("Has Profile Pic?: %1").arg( oMyIdent.hasProfilePicture()) );
    ui.labelMeLine9->setText( QString("Is Big Endian CPU ?: %1").arg( IsBigEndianCpu() ? "true" : "false" ) );
}

//============================================================================
void  ActivityAbout::gotoWebsite( void )
{
	QDesktopServices::openUrl(QUrl("http://www.gotvptop.com/"));
}
