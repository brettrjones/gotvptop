//============================================================================
// Copyright (C) 2009 Brett R. Jones 
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

#include "AppCommon.h"
#include "MyIcons.h"
#include "PopupMenu.h"
#include "AppGlobals.h"

#include "ActivityPermissions.h"
#include "ActivityEditProfile.h"
#include "ActivityStoryBoard.h"

#include <CoreLib/VxGlobals.h>


//============================================================================
void AppCommon::slotServerButtonClick( void )
{
	LogMsg( LOG_INFO, "AppCommon::slotServerButtonClick 1\n" );
	PopupMenu popupMenu( *this, this );
	popupMenu.setTitle( "Servers");

	LogMsg( LOG_INFO, "AppCommon::slotServerButtonClick 2\n" );
	switch( m_Engine.fromGuiGetPluginServerState( ePluginTypeCamServer ) )
	{
	case ePluginServerStateDisabled:	
		popupMenu.addMenuItem( 1, getMyIcons().getIcon(eMyIconWebCamServerDisabled), tr( "Web Cam Server Disabled" ) );
		break;
	case ePluginServerStateStarted:	
		popupMenu.addMenuItem( 1, getMyIcons().getIcon(eMyIconWebCamServer), tr( "Stop Web Cam Server" ) );
		break;
	case ePluginServerStateStopped:	
		popupMenu.addMenuItem( 1, getMyIcons().getIcon(eMyIconWebCamServer), tr( "Start Web Cam Server" ) );
		break;
	}

	popupMenu.addMenuItem( 2, getMyIcons().getIcon( eMyIconProfile ), "Edit My Profile" );
	popupMenu.addMenuItem( 3, getMyIcons().getIcon( eMyIconProfile ), "View My Profile" );
	popupMenu.addMenuItem( 4, getMyIcons().getIcon( eMyIconStoryBoardNormal ), "Edit My Story Board" );
	popupMenu.addMenuItem( 5, getMyIcons().getIcon( eMyIconStoryBoardNormal ), "View My Story Board" );

	connect( &popupMenu, SIGNAL(menuItemClicked(int, QWidget *)), this, SLOT(onMenuServerSelected(int, QWidget *)));
	LogMsg( LOG_INFO, "AppCommon::slotServerButtonClick 4\n" );
	popupMenu.exec();
	LogMsg( LOG_INFO, "AppCommon::slotServerButtonClick 5\n" );
}

//============================================================================
void AppCommon::onMenuServerSelected( int iMenuId, QWidget * )
{
	switch( iMenuId )
	{

	case 1: //Start/Stop Web Cam Server
		switch( m_Engine.fromGuiGetPluginServerState(ePluginTypeCamServer))
		{
		case ePluginServerStateStarted:	// app has started
			m_Engine.setHasSharedWebCam(false);
			m_Engine.fromGuiStopPluginSession( ePluginTypeCamServer, m_Engine.getMyPktAnnounce().getMyOnlineId(), NULL );
			break;
		case ePluginServerStateStopped:
			startActivity( ePluginTypeCamServer, &m_Engine.getMyPktAnnounce() );
			m_Engine.setHasSharedWebCam(true);
			break;
		case ePluginServerStateDisabled:	// disabled by permissions
			{
				ActivityPermissions * poDlg = new ActivityPermissions( *this, getCentralWidget() );
				poDlg->setPluginType(ePluginTypeCamServer);
				poDlg->exec();
			}
			break;
		}

		break;

	case 2: // edit profile
		{
			ActivityEditProfile oDlg( *this,  VxGetUserSpecificDataDirectory().c_str(), this );
			oDlg.exec();
			break;
		}

	case 3: // view my profile
		{
			viewWebServerPage( getAppGlobals().getUserIdent(), "index.htm" );
			break;
		}

	case 4: // edit storyboard
		{
			ActivityStoryBoard oDlg( *this, this );
			oDlg.exec();
			break;
		}

	case 5: // view my storyboard
		{
			viewWebServerPage( getAppGlobals().getUserIdent(), "story_board.htm" );
			break;
		}


	default: 
		LogMsg( LOG_ERROR, "onMenuServerSelected: ERROR unknown menu id %d\n", iMenuId );
		break;
	}
}
