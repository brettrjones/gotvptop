//============================================================================
// Copyright (C) 2010 Brett R. Jones
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

#include "PluginServiceAboutMe.h"
#include "PluginMgr.h"

#include <PktLib/PktsStoryBoard.h>

//============================================================================
PluginServiceAboutMe::PluginServiceAboutMe( P2PEngine& engine, PluginMgr& pluginMgr, VxNetIdent * myIdent )
: PluginBase( engine, pluginMgr, myIdent )
{
	setPluginType( ePluginTypeAboutMePage );
}

//============================================================================
//! return true if is plugin session
bool PluginServiceAboutMe::fromGuiIsPluginInSession( VxNetIdent * netIdent, void * pvUserData )
{
	return true;
}

//============================================================================
void PluginServiceAboutMe::replaceConnection( VxNetIdent * netIdent, VxSktBase * poOldSkt, VxSktBase * poNewSkt )
{
	//m_PluginSessionMgr.replaceConnection( netIdent, poOldSkt, poNewSkt );
}

//============================================================================
void PluginServiceAboutMe::onConnectionLost( VxSktBase * sktBase )
{
	//m_PluginSessionMgr.onConnectionLost( sktBase );
}

//============================================================================
void PluginServiceAboutMe::onContactWentOffline( VxNetIdent * netIdent, VxSktBase * sktBase )
{
	//m_PluginSessionMgr.onContactWentOffline( netIdent, sktBase );
}