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

#include "TextChatLogic.h"
#include "AppCommon.h"
#include "MyIcons.h"
#include "AppGlobals.h"

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>
#include <GoTvCore/GoTvP2P/P2PEngine/EngineSettings.h>

namespace
{
	#define GAME_SETTINGS_KEY "TODGAME"
}

//============================================================================
TextChatLogic::TextChatLogic( AppCommon& myApp, P2PEngine& engine, EPluginType pluginType, QWidget * parent )
: QWidget( parent )
, m_MyApp( myApp )
, m_Engine( engine )
, m_ePluginType( pluginType )
{
}

//============================================================================
void TextChatLogic::setGuiWidgets(	VxNetIdent *	hisIdent )
{
	m_HisIdent			= hisIdent;
}

//============================================================================
void TextChatLogic::handleUserWentOffline( void )
{

}
