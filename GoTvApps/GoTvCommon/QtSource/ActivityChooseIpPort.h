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

#include "ui_ActivityChooseIpPort.h"

#include <QDialog>

class AppCommon;
class P2PEngine;

class ActivityChooseIpPort : public ActivityBase
{
	Q_OBJECT
public:
	ActivityChooseIpPort( AppCommon& app, QWidget * parent = NULL );
	virtual ~ActivityChooseIpPort();


public slots:
	void		updateValues();
	void		applyResultsAndExit();
	void		chooseRandomPort();

protected:
	//=== vars ===//
	Ui::ChooseIpPortDlg			ui;
	AppCommon&				m_MyApp;
	P2PEngine&					m_Engine;
};
