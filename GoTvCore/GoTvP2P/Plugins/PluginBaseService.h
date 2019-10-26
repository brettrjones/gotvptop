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
// http://www.gotvptop.com
//============================================================================

#include "PluginBase.h"

class PluginBaseService : public PluginBase
{
public:

    PluginBaseService(	P2PEngine& engine, PluginMgr& pluginMgr, VxNetIdent * myIdent );
	virtual ~PluginBaseService() override = default;


protected:

};