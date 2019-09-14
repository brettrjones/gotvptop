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

#include "AppGlobals.h"
#include "PopupMenu.h"
#include "ActivityPhoneShake.h"
#include "AppCommon.h"

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>
#include <CoreLib/VxGlobals.h>

#include <QString>

//============================================================================
ActivityPhoneShake::ActivityPhoneShake(	AppCommon&		app, 
										EScanType			eSearchType,
										QWidget *			parent )
: ActivityBase( OBJNAME_ACTIVITY_PHONE_SHAKE, app, parent, eAppletMessenger, true )
, m_eScanType( eSearchType )
{
	ui.setupUi(this);

    connectBarWidgets();

    connect( ui.m_TitleBarWidget, SIGNAL(signalBackButtonClicked()), this, SLOT(close()));
	connect( this, SIGNAL(finished(int)), this, SLOT(slotHomeButtonClicked()));

	connect( ui.m_SimulateShakeButton, SIGNAL(clicked()), this, SLOT(slotSimulateShakeClicked()));
	connect( this,					SIGNAL(signalSearchComplete()),				this, SLOT(slotSearchComplete()) );
	connect( this,					SIGNAL(signalSearchResult(VxNetIdent*)),	this, SLOT(slotSearchResult(VxNetIdent*)) ); 
	connect(	&app, 
				SIGNAL(signalPhoneShakeStatus(EPhoneShakeStatus,QString)), 
				this, 
				SLOT(slotPhoneShakeStatus(EPhoneShakeStatus,QString)) );


	setTitle( "Add Friend By Shaking Phone" );
}

//============================================================================
void ActivityPhoneShake::setTitle( QString strTitle )
{
	ui.m_TitleBarWidget->setTitleBarText( strTitle );
}

//============================================================================
void ActivityPhoneShake::showEvent( QShowEvent * ev )
{
	ActivityBase::showEvent( ev );
	m_MyApp.wantToGuiActivityCallbacks( this, this, true );
}

//============================================================================
void ActivityPhoneShake::hideEvent( QHideEvent * ev )
{
	m_MyApp.wantToGuiActivityCallbacks( this, this, false );
	ActivityBase::hideEvent( ev );
}

//============================================================================
void ActivityPhoneShake::toGuiSearchResultSuccess( void * callbackData, EScanType eScanType, VxNetIdent * netIdent )
{
	Q_UNUSED( callbackData );
	if( VxIsAppShuttingDown() )
	{
		return;
	}

	if( eScanType == getScanType() )
	{
		emit signalSearchResult( netIdent );
	}
};

//============================================================================
void ActivityPhoneShake::toGuiClientScanSearchComplete( void * callbackData, EScanType eScanType )
{
	Q_UNUSED( callbackData );
	if( VxIsAppShuttingDown() )
	{
		return;
	}

	if( eScanType == getScanType() )
	{
		emit signalSearchComplete();
	}
}

//============================================================================
void ActivityPhoneShake::slotHomeButtonClicked( void )
{
}

//============================================================================
void ActivityPhoneShake::slotSimulateShakeClicked( void )
{
	m_MyApp.playSound( eSndDefSending );
	ui.friendListWidget->clear();
	m_MyApp.toGuiUserMessage( "Contacting Anchor" );
	m_FromGui.fromGuiStartScan( eScanTypePhoneShake, 0, 0 );
}

//============================================================================
void ActivityPhoneShake::slotSearchComplete( void )
{
	m_MyApp.toGuiUserMessage( "Search Complete" );
}

//============================================================================
void ActivityPhoneShake::slotSearchResult( VxNetIdent * netIdent )
{
	m_MyApp.playSound( eSndDefUserBellMessage );
	m_MyApp.toGuiUserMessage( "Found Match %s",  netIdent->getOnlineName()  );
	ui.friendListWidget->updateFriend( netIdent, false );
}

//============================================================================
void ActivityPhoneShake::slotPhoneShakeStatus( EPhoneShakeStatus eAnchorStatus, QString strMsg )
{
	m_MyApp.toGuiUserMessage( strMsg.toUtf8().constData() );
}
