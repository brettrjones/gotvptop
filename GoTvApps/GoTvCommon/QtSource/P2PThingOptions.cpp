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

#include "PopupMenu.h"
#include "AppCommon.h"
#include "MyIcons.h"
#include "AppGlobals.h"
#include "ActivityAbout.h"
#include "ActivityEditAccount.h"
#include "ActivitySoundOptions.h"
#include "ActivityPermissions.h"
#include "ActivityPermissionsRelay.h"
#include "ActivityNetworkSettings.h"
#include "ActivityDebugSettings.h"
#include "ActivityNetServiceTest.h"
#include "ActivityVideoOptions.h"
#include "ActivityToFriendMultiSession.h"
#include "ActivitySelectFileToSend.h"
#include "GuiHelpers.h"

#include <GoTvInterface/IFromGui.h>

#include <CoreLib/VxGlobals.h>

//============================================================================
void AppCommon::slotOptionsButtonClick( void )
{
	PopupMenu popupMenu( *this, this );
	popupMenu.setTitle( "Options");
	QString aboutText = QObject::tr( "About " );
	aboutText += m_Engine.fromGuiGetAppName();
	popupMenu.addMenuItem( 1, getMyIcons().getIcon( eMyIconPermissions),  QObject::tr( "Edit Plugin Permissions" ) );
	popupMenu.addMenuItem( 2, getMyIcons().getIcon( eMyIconApp ),  QObject::tr( "Edit My Account" ) );
	popupMenu.addMenuItem( 3, getMyIcons().getIcon( eMyIconRelay ),  QObject::tr( "Network Settings" ) );
	popupMenu.addMenuItem( 4, getMyIcons().getIcon( eMyIconSpeakerOn ),  QObject::tr( "Sound Options" ) );
	popupMenu.addMenuItem( 5, getMyIcons().getIcon( eMyIconVideo ),  QObject::tr( "Video Options" ) );
	popupMenu.addMenuItem( 6, getMyIcons().getIcon( eMyIconApp ), aboutText );
	//popupMenu.addMenuItem( 6, getMyIcons().getIcon( eMyIconDebug ),  QObject::tr( "Debug Only" ) );
	//popupMenu.addMenuItem( 8, getMyIcons().getIcon( eMyIconFolder ), "Setup file share" );
	//popupMenu.addMenuItem( 12, getMyIcons().getIcon( eMyIconDebug ), "Debug Settings" );

	connect( &popupMenu, SIGNAL(menuItemClicked(int, QWidget *)), this, SLOT(onMenuOptionsSelected(int, QWidget *)));
	popupMenu.exec();
}

//============================================================================
void AppCommon::addPermissionMenuEntry(	PopupMenu *		poPopupMenu, 
											EPluginType		ePluginType, 
											EMyIcons		eIconType, 
											const char *	pText )
{
	int iPluginPermission = m_Engine.getPluginPermission( (int)ePluginType );
	
	char as8Buf[255];
	sprintf(as8Buf, pText, GuiHelpers::describePluginPermission( (EFriendState) iPluginPermission ) );
	poPopupMenu->addMenuItem( ePluginType, getMyIcons().getIcon(eIconType), as8Buf );
}

//============================================================================
void AppCommon::onMenuOptionsSelected( int iMenuId, QWidget * senderPopupMenu )
{
	std::string strTmp;
	PopupMenu popupMenu( *this, this );
	switch( iMenuId )
	{

	case 1: // edit permissions
		{
			popupMenu.setTitle( "Edit Access Permissions");
			// file share plugin
			addPermissionMenuEntry( &popupMenu, ePluginTypeFileServer, eMyIconShareFilesNormal, "(%s) Who can access shared files" );
			// file offer plugin
			addPermissionMenuEntry( &popupMenu, ePluginTypeFileOffer, eMyIconSendFileNormal, "(%s) Who can offer to send a file" );
			// web cam broadcast plugin
			addPermissionMenuEntry( &popupMenu, ePluginTypeCamServer, eMyIconWebCamServer, "(%s) Who can access web cam broadcast" );
			// instant message p2p plugin
			addPermissionMenuEntry( &popupMenu, ePluginTypeMultiSession, eMyIconMultiSession, "(%s) Who can offer chat session" );
			// VOIP p2p plugin
			addPermissionMenuEntry( &popupMenu, ePluginTypeVoicePhone, eMyIconVoicePhoneNormal, "(%s) Who can offer voice phone call" );
			// Video phone p2p plugin
			addPermissionMenuEntry( &popupMenu, ePluginTypeVideoPhone, eMyIconVideoPhoneNormal, "(%s) Who can offer video chat" );
			// Web Cam Truth Or Dare game p2p plugin
			addPermissionMenuEntry( &popupMenu, ePluginTypeTruthOrDare, eMyIconTruthOrDareNormal, "(%s) Who can offer to play truth or dare" );
			// Relay
			addPermissionMenuEntry( &popupMenu, ePluginTypeRelay, eMyIconRelay, "(%s) Who can use my device as a relay" );
			// Profile 
			addPermissionMenuEntry( &popupMenu, ePluginTypeWebServer, eMyIconProfile, "(%s) Who can view my profile" );
			// Storyboard
			addPermissionMenuEntry( &popupMenu, ePluginTypeStoryBoard, eMyIconStoryBoardNormal, "(%s) Who can view my storyboard" );
			if( false == connect( &popupMenu, SIGNAL(menuItemClicked(int, QWidget *)), this, SLOT(onEditPermissionsSelected(int, QWidget *))) )
			{
				LogMsg( LOG_ERROR, "could not connect to onEditPermissionsSelected\n" );
			}
			popupMenu.exec();
			break;
		}


	case 2: // edit account
		{
			ActivityEditAccount oDlg( *this, this );
			oDlg.exec();
			break;
		}


	case 3: //Network settings
		{
			ActivityNetworkSettings oDlg( *this, this );
			oDlg.exec();
			break;
		}

	case 4: //Sound Options
		{
			ActivitySoundOptions oDlg( *this, this );
			oDlg.exec();
			break;
		}

	//case 5: //Video Options
	//	{
	//		ActivityVideoOptions * poDlg = new ActivityVideoOptions(	*this,
	//			getAppGlobals().getUserIdent(),
	//																	true, 
	//																	getCentralWidget() );
	//		break;
	//	}

	case 6: // about
		{
			ActivityAbout oDlg( *this, this );
			oDlg.exec();
			break;
		}

	//case 7: //eTestParamSoundDelayTest
	//	{
	//		m_Engine.fromGuiTestCmd( IFromGui::eTestParamSoundDelayTest );
	//	}
	//	break;

	//case 12: //Debug settings
	//	{
	//		//m_DebugSettingsDlg->show();
	//		senderPopupMenu->setVisible( false );
	//		ActivitySelectFileToSend selectFileDlg(	*this,
	//												GetAppGlobals()->getUserIdent(), 
	//												getCentralWidget() );
	//		selectFileDlg.exec();
	//	}
	//	break;

	default: 
		LogMsg( LOG_INFO, "onMenuServerSelected: unknown id %d\n", iMenuId );
	}
}

//============================================================================
//! user selected permission to edit
void AppCommon::onEditPermissionsSelected( int iMenuId, QWidget * senderPopupMenu )
{
	Q_UNUSED( senderPopupMenu );
	if( iMenuId > 0 )
	{
		if( ePluginTypeRelay == iMenuId )
		{
			ActivityPermissionsRelay oDlg( *this, this );
			oDlg.setPluginType( (EPluginType) iMenuId );
			oDlg.exec();
		}
		else
		{
			ActivityPermissions oDlg( *this, this );
			oDlg.setPluginType( (EPluginType) iMenuId );
			oDlg.exec();
		}
	}
}