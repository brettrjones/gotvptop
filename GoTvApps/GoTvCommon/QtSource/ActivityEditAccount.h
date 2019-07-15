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

#include <QDialog>
#include "ui_ActivityEditAccount.h"
#include "ActivityEditAccount.h"

#include <GoTvCore/GoTvP2P/P2PEngine/EngineSettings.h>

class AppCommon;
class P2PEngine;

class ActivityEditAccount : public ActivityBase
{
	Q_OBJECT
public:
	ActivityEditAccount(AppCommon& app, QWidget * parent = NULL );
	virtual ~ActivityEditAccount();

	void						updateValuesFromDatabase();

protected slots:
	void						slotApplyResults();

protected:
	bool						validateMoodMessage( void );


	//=== vars ===//
	 Ui::EditAccountDialog		ui; 
	VxNetIdent *				m_MyIdent;
	QString						m_strMoodMessage;
};
