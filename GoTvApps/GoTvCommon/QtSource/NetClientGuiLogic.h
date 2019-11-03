
//============================================================================
// Copyright (C) 2019 Brett R. Jones 
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
#pragma once

#include <QWidget>

class AppCommon;

class NetClientGuiLogic : public QWidget
{
    Q_OBJECT
public:
    NetClientGuiLogic( AppCommon& myApp, QWidget * parent );

protected:
    AppCommon&                  m_MyApp;
};
