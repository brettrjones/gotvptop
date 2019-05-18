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
// http://www.gotvptop.net
//============================================================================

#include "ActivityPermissionsRelay.h"
#include "MyIcons.h"
#include "AppGlobals.h"

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>

//============================================================================
ActivityPermissionsRelay::ActivityPermissionsRelay( AppCommon& app, QWidget * parent )
	: ActivityBase(  OBJNAME_ACTIVITY_PERMISSIONS_RELAY, app, parent, eAppletMessenger, Qt::SubWindow )
{
	ui.setupUi(this);
	ui.m_TitleBarWidget->setTitleBarText( QObject::tr("Relay Permissions" ) );

	slotRepositionToParent();

	connect( ui.AnybodyButton,				SIGNAL(clicked()), this, SLOT(onPermissionClick()) );
	connect( ui.FriendsOnlyButton,			SIGNAL(clicked()), this, SLOT(onPermissionClick()) );
	connect( ui.AdminsOnlyButton,			SIGNAL(clicked()), this, SLOT(onPermissionClick()) );
	connect( ui.GuestsAndFriendsButton,		SIGNAL(clicked()), this, SLOT(onPermissionClick()) );
	connect( ui.NobodyButton,				SIGNAL(clicked()), this, SLOT(onPermissionClick()) );
	connect( ui.OkButton,					SIGNAL(clicked()), this, SLOT(onOkButClick()) );
	connect( ui.CancelButton,				SIGNAL(clicked()), this, SLOT(onCancelButClick()) );
	connect( ui.m_TitleBarWidget,			SIGNAL(signalBackButtonClicked()), this, SLOT(onCancelButClick()) );

	uint32_t maxUserRelaysInUse = 0;
	uint32_t maxAnonRelaysInUse = 0;
	m_Engine.getEngineSettings().getMaxRelaysInUse( maxUserRelaysInUse, maxAnonRelaysInUse );
	ui.m_UserAllowCntSpinBox->setValue( maxUserRelaysInUse );
	ui.m_AnonAllowCntSpinBox->setValue( maxAnonRelaysInUse );
}

//============================================================================
ActivityPermissionsRelay::~ActivityPermissionsRelay()
{
}

//============================================================================
//! Set plugin to set permissions on    
void ActivityPermissionsRelay::setPluginType( EPluginType ePluginType )
{
	m_ePluginType = ePluginType;
	int iPluginPermission = m_Engine.getPluginPermission( m_ePluginType );
	setPluginIcon( m_ePluginType, (EFriendState)iPluginPermission );
	setCheckedPermission( (EFriendState)iPluginPermission );

	switch( ePluginType )
	{
	case ePluginTypeWebServer:	// web server plugin ( for profile web page )
		ui.AdminsOnlyButton->setEnabled( false );
		ui.FriendsOnlyButton->setEnabled( false );
		ui.GuestsAndFriendsButton->setEnabled( false );
		break;
	case ePluginTypeRelay:	// proxy plugin
		break;
	case ePluginTypeFileOffer:	
		break;
	case ePluginTypeFileServer:	
		break;
	case 	ePluginTypeCamServer:	
		break;
	case 	ePluginTypeMultiSession:	
		break;
	case 	ePluginTypeVoicePhone:	
		break;
	case 	ePluginTypeVideoPhone:	
		break;
	case 	ePluginTypeTruthOrDare:	
		break;
	case 	ePluginTypeStoryBoard:	
		break;
	//case 	eStoryBoardWritePermission:	
	//	ui.PermissionLabel->setText( "Who can add to my story board" );
	//	break;
    case 	ePluginTypeInvalid:
    default:
        break;
    }
}

//============================================================================
//! Set plugin icon based on permission level
void ActivityPermissionsRelay::setPluginIcon( EPluginType ePluginType, EFriendState ePluginPermission )
{
	if( eFriendStateIgnore == ePluginPermission )
	{
		ui.PermissionButton->setIcon( getMyIcons().getPluginIcon(ePluginType, ePluginAccessDisabled ) );
	}
	else
	{
		ui.PermissionButton->setIcon( getMyIcons().getPluginIcon(ePluginType, ePluginAccessOk ) );
	}
}

//============================================================================
//! get current permission selection
EFriendState ActivityPermissionsRelay::getPermissionSelection( void )
{
	EFriendState ePluginPermission = eFriendStateFriend;
	if( ui.NobodyButton->isChecked() )
	{
		ePluginPermission = eFriendStateIgnore;
	}
	else if( ui.AnybodyButton->isChecked() )
	{
		ePluginPermission = eFriendStateAnonymous;
	} 
	else if( ui.GuestsAndFriendsButton->isChecked() )
	{
		ePluginPermission = eFriendStateGuest;
	} 
	else if( ui.FriendsOnlyButton->isChecked() )
	{
		ePluginPermission = eFriendStateFriend;
	}
	else if( ui.AdminsOnlyButton->isChecked() )
	{
		ePluginPermission = eFriendStateAdmin;
	}

	return ePluginPermission;
}

//============================================================================
//! Implement the OnClickListener callback    
void ActivityPermissionsRelay::onOkButClick( void )
{
	UpdatePluginPermissions( m_Engine, m_ePluginType, getPermissionSelection() );
    //int userCnt = ui.m_UserAllowCntSpinBox->value();
    //int anonCnt = ui.m_AnonAllowCntSpinBox->value();
	NetSettings netSettings;
	m_Engine.getEngineSettings().getNetSettings( netSettings );
	m_Engine.fromGuiSetNetSettings( netSettings );

	accept();
}

//============================================================================
//! Implement the OnClickListener callback    
void ActivityPermissionsRelay::onCancelButClick( void )
{
	reject();
}

//============================================================================
//! Implement the OnClickListener callback    
void ActivityPermissionsRelay::onPermissionClick( void )
{
	EFriendState ePluginPermission = eFriendStateFriend;
	if( ui.NobodyButton->isChecked() )
	{
		ePluginPermission = eFriendStateIgnore;
	}
	else if( ui.AnybodyButton->isChecked() )
	{
		ePluginPermission = eFriendStateAnonymous;
	} 
	else if( ui.GuestsAndFriendsButton->isChecked() )
	{
		ePluginPermission = eFriendStateGuest;
	} 
	else if( ui.FriendsOnlyButton->isChecked() )
	{
		ePluginPermission = eFriendStateFriend;
	}
	else if( ui.AdminsOnlyButton->isChecked() )
	{
		ePluginPermission = eFriendStateAdmin;
	}

	setPluginIcon( m_ePluginType, ePluginPermission );
}

//============================================================================
//! set which radio button is checked
void ActivityPermissionsRelay::setCheckedPermission( EFriendState ePluginPermission )
{
	ui.AdminsOnlyButton->setChecked( false );
	ui.FriendsOnlyButton->setChecked( false );
	ui.GuestsAndFriendsButton->setChecked( false );
	ui.AnybodyButton->setChecked( false );
	ui.NobodyButton->setChecked( false );

	switch( ePluginPermission )
	{
	case eFriendStateAdmin:
		ui.AdminsOnlyButton->setChecked( true );
		break;
	case eFriendStateFriend:
		ui.FriendsOnlyButton->setChecked( true );
		break;
	case eFriendStateGuest:
		ui.GuestsAndFriendsButton->setChecked( true );
		break;
	case eFriendStateAnonymous:
		ui.AnybodyButton->setChecked( true );
		break;
	case eFriendStateIgnore:
		ui.NobodyButton->setChecked( true );
		break;
	}
}

