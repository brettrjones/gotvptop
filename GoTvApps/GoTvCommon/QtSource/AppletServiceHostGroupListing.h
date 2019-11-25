#pragma once
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

#include "AppletServiceBase.h"


class AppletServiceHostGroupListing : public AppletServiceBase
{
	Q_OBJECT
public:
	AppletServiceHostGroupListing( AppCommon& app, QWidget * parent );
	virtual ~AppletServiceHostGroupListing() = default;

protected:
    void setupApplet();
    void loadFromSettings();
    void saveToSettings();


};


