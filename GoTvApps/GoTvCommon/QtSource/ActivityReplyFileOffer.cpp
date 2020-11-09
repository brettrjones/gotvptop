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
// http://www.nolimitconnect.com
//============================================================================
#include <app_precompiled_hdr.h>
#include "ActivityReplyFileOffer.h"

#include "GuiOfferSession.h"

//============================================================================
ActivityReplyFileOffer::ActivityReplyFileOffer(	AppCommon& app, 
												GuiOfferSession * poOffer, 
												QWidget * parent )
: ActivityToFriendBase( OBJNAME_ACTIVITY_REPLY_FILE_OFFER, app, ePluginTypeFileXfer, poOffer, parent, eAppletMessenger, true )
{
	ui.setupUi(this);
	ui.m_TitleBarWidget->setTitleBarText( QObject::tr("Reply File Offer" ) );

    connectBarWidgets();

	setupStyledDlg( 	
		poOffer->getHisIdent(), 
		ui.FriendIdentWidget,
		m_ePluginType,
		ui.PermissionButton, 
		ui.PermissionLabel );

	QString strRxFile = "Receive File";
	ui.PermissionLabel->setText( strRxFile );

	ui.FileNameEdit->setText( poOffer->getFileName().c_str() );
	ui.OfferMsgEdit->setPlainText( poOffer->getOfferMsg().c_str() );

	connect( ui.AcceptButton, SIGNAL(clicked()), this, SLOT(onReceiveFileButClick()) );
	connect( ui.CancelButton, SIGNAL(clicked()), this, SLOT(onCancelButClick()) );
}

//============================================================================
//! Implement the OnClickListener callback    
void ActivityReplyFileOffer::onReceiveFileButClick()
{
	//setOfferResponse( eOfferResponseAccept );
	m_OfferSessionLogic.sendOfferReply( eOfferResponseAccept );
	accept();
}

//============================================================================
//! Implement the OnClickListener callback    
void ActivityReplyFileOffer::onCancelButClick()
{
	m_OfferSessionLogic.sendOfferReply( eOfferResponseReject );
	reject();
}

