#pragma once
//============================================================================
// Copyright (C) 2015 Brett R. Jones
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
#include "ui_ActivityYesNo.h"

class AppCommon;

class ActivityYesNoMsgBox : public ActivityBase
{
	Q_OBJECT
public:
	ActivityYesNoMsgBox(	AppCommon&		app, 
							QWidget *		parent, 
							QString			title, 
							QString			bodyText ); 
	virtual ~ActivityYesNoMsgBox();

	void						setTitle( QString strTitle );
	void						setBodyText( QString strBodyText );
	void						hideCancelButton( void );
	void						makeNeverShowAgainVisible( bool makeVisible );
	bool						wasNeverShowAgainChecked( void );

private slots:
	void						slotHomeButtonClicked( void );

protected:

	//=== vars ===//
	Ui::YesNoMsgBoxClass		ui;
};


