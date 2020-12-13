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
// bjones.engineer@gmail.com
// http://www.nolimitconnect.com
//============================================================================
#include <app_precompiled_hdr.h>
#include "ActivityPersonalRecorder.h"
#include "GuiOfferSession.h"
#include "AppGlobals.h"
#include "MyIcons.h"
#include "AppCommon.h"

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>

//============================================================================
ActivityPersonalRecorder::ActivityPersonalRecorder(	AppCommon&			app,
													VxNetIdent *		ident, 
													QWidget *			parent )
: ActivityToFriendBase( OBJNAME_ACTIVITY_PERSONAL_RECORDER, app, ePluginTypePersonalRecorder, ident, parent, eAppletMessenger, true )
{
	setupMultiSessionActivity();
	m_MyApp.wantToGuiActivityCallbacks( this, this, true );
}

//============================================================================
ActivityPersonalRecorder::~ActivityPersonalRecorder()
{
	m_MyApp.wantToGuiActivityCallbacks( this, this, false );
}

//============================================================================
void ActivityPersonalRecorder::setupMultiSessionActivity( void )
{
	ui.setupUi( this );
	connect( ui.m_TitleBarWidget,	SIGNAL(signalBackButtonClicked()), this,	SLOT(accept()) );
    connectBarWidgets();
	ui.m_SessionWidget->setIsPersonalRecorder( true );
	ui.m_SessionWidget->setIdents( &m_Engine.getMyPktAnnounce(), &m_Engine.getMyPktAnnounce() );
	ui.m_SessionWidget->setEntryMode( eAssetTypeUnknown );
}

//============================================================================
void ActivityPersonalRecorder::onActivityFinish( void )
{
	ui.m_SessionWidget->onActivityStop();
	this->deleteLater();
}

//============================================================================
void ActivityPersonalRecorder::toGuiClientPlayVideoFrame(	void *			userData, 
															VxGUID&			onlineId, 
															uint8_t *		pu8Jpg, 
															uint32_t		u32JpgDataLen,
															int				motion0To100000 )
{
	ui.m_SessionWidget->playVideoFrame( onlineId, pu8Jpg, u32JpgDataLen, motion0To100000 );
}

