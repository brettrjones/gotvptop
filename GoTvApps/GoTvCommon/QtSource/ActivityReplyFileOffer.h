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

#include "ActivityToFriendBase.h"

#include <PktLib/VxCommon.h>

#include <QDialog>
#include "Friend.h"
#include "ui_ActivityReplyFileOffer.h"

class AppCommon;
class P2PEngine;
class GuiOfferSession;

class ActivityReplyFileOffer : public ActivityToFriendBase
{
	Q_OBJECT

public:
	ActivityReplyFileOffer(	AppCommon& app, 
							GuiOfferSession * poOffer, 
							QWidget * parent = NULL );
	virtual ~ActivityReplyFileOffer();

public slots:
	void						onReceiveFileButClick();
	void						onCancelButClick(); 

protected:
	//! Set plugin icon based on permission level
	void						setPluginIcon( EPluginType ePluginType, EFriendState ePluginPermission );

	//=== vars ===//
	Ui::ReplyFileOfferDialog	ui;
	EPluginType					m_ePluginType;
	GuiOfferSession *			m_Offer;
};
