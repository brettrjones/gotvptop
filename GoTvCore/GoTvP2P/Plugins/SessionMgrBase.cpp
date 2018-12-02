//============================================================================
// Copyright (C) 2014 Brett R. Jones
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

#include "SessionMgrBase.h"
#include "PluginBase.h"
#include "PluginMgr.h"

SessionMgrBase::SessionMgrBase( PluginBase& plugin, PluginMgr& pluginMgr, IToGui& toGui )
: m_Plugin( plugin )
, m_PluginMgr( pluginMgr )
, m_ToGui( toGui )
{
}

SessionMgrBase::~SessionMgrBase()
{
}

//============================================================================
bool SessionMgrBase::isPluginSingleSession( void )
{
	bool isSingleSessionPlugin = false;
	switch( m_Plugin.getPluginType() )
	{
	case ePluginTypeVoicePhone:
	case ePluginTypeVideoPhone:
	case ePluginTypeTruthOrDare:
	case ePluginTypeMultiSession:
	case ePluginTypeCamServer:
	case ePluginTypeAdmin:
		isSingleSessionPlugin = true;
		break;
	case ePluginTypeWebServer:
	case ePluginTypeRelay:
	case ePluginTypeStoryBoard: 
	case ePluginTypeFileServer:
	case ePluginTypeFileOffer:
	default:
		break;
	}

	return isSingleSessionPlugin;
}
