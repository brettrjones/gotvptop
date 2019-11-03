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


#include "PluginNetServices.h"

class PluginBaseHostService : public PluginNetServices
{
public:

    PluginBaseHostService( P2PEngine& engine, PluginMgr& pluginMgr, VxNetIdent * myIdent );
    virtual ~PluginBaseHostService() override = default;

protected:
    virtual void				onContactWentOffline( VxNetIdent * netIdent, VxSktBase * sktBase ) override;
    virtual void				onConnectionLost( VxSktBase * sktBase ) override;
    virtual void				replaceConnection( VxNetIdent * netIdent, VxSktBase * poOldSkt, VxSktBase * poNewSkt ) override;

};

