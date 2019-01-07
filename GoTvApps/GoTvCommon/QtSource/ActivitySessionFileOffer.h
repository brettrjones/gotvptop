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
// brett.jones@engineer.com
// http://www.gotvptop.net
//============================================================================

#include "ActivityBase.h"

#include <PktLib/VxCommon.h>


#include <QDialog>
#include "Friend.h"
#include "ActivityBase.h"
#include "ui_ActivitySessionFileOffer.h"

class GuiOfferSession;

class ActivitySessionFileOffer : public ActivityBase
{
	Q_OBJECT

public:
	ActivitySessionFileOffer(	AppCommon& app, 
								GuiOfferSession * poOffer, 
								QWidget * parent = NULL );
	virtual ~ActivitySessionFileOffer();

	void						setPluginType( EPluginType ePluginType );

public slots:
	void						onAcceptButClick();
	void						onCancelButClick(); 

protected:
	//! Set plugin icon based on permission level
	void						setPluginIcon( EPluginType ePluginType, EFriendState ePluginPermission );

	//=== vars ===//
	Ui::SessionFileOfferDialog	ui;
	EPluginType					m_ePluginType;
	GuiOfferSession *			m_Offer;
};
