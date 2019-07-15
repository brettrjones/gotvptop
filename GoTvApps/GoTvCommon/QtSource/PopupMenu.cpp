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

#include "PopupMenu.h"
#include "MyIcons.h"
#include "AppGlobals.h"
#include "AppCommon.h"

#include <PktLib/VxCommon.h>
#include <CoreLib/VxDebug.h>

//============================================================================
PopupMenu::PopupMenu( AppCommon& app, QWidget * parent )
: ActivityBase( OBJNAME_POPUP_MENU, app, parent, eAppletMessenger, Qt::SubWindow )
, m_iMenuItemHeight(34)
, m_SelectedFriend(NULL)
{
	m_MyApp.playSound( eSndDefButtonClick );
	ui.setupUi(this);
	// no need to call this.. base class will call it in showEvent()
	//repositionToParent();

    connect(ui.exitPopupButton, SIGNAL(clicked()), this, SLOT(slotHomeButtonClicked()));
    connect(ui.menuItemList, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(itemClicked(QListWidgetItem *)));
}

//============================================================================
PopupMenu::~PopupMenu()
{
}

//============================================================================
void PopupMenu::setTitle( QString strTitle )
{
	ui.popupTitleLabel->setText(strTitle);
}

//============================================================================
void PopupMenu::addMenuItem( int iItemId, QIcon& oIcon, QString strMenuItemText )
{
	QListWidgetItem * poMenuItem = new QListWidgetItem( strMenuItemText );
	poMenuItem->setIcon( oIcon );
	poMenuItem->setData( Qt::UserRole, iItemId );
	ui.menuItemList->addItem( poMenuItem );
}

//============================================================================
//! clicked the upper right x button
void PopupMenu::slotHomeButtonClicked( void )
{
	//m_MyApp.playSound( eSndDefButtonClick );
	//close();
	emit signalBackButtonClicked();
}

//============================================================================
void PopupMenu::itemClicked(QListWidgetItem *item)
{
	m_MyApp.playSound( eSndDefButtonClick );
	// resignal with id set by user
	int iItemId = item->data(Qt::UserRole).toInt();
	emit menuItemClicked( iItemId, this );
	close();
}

//============================================================================
void PopupMenu::showRefreshMenu()
{
	setTitle( "Who to show in list");
	addMenuItem( 0, getMyIcons().getIcon(eMyIconFriend),			tr("Everybody"));
	addMenuItem( 1, getMyIcons().getIcon(eMyIconFriend),			tr("Friends And Guests"));
	addMenuItem( 2, getMyIcons().getIcon(eMyIconAnonymous),		tr("Anonymous"));
	addMenuItem( 3, getMyIcons().getIcon(eMyIconAdministrator),	tr("Administrators"));
	addMenuItem( 4, getMyIcons().getIcon(eMyIconIgnored),			tr("Ignored"));
	addMenuItem( 5, getMyIcons().getIcon(eMyIconRelay),			tr("My Relays"));
	addMenuItem( 6, getMyIcons().getIcon(eMyIconRelay),			tr("All Possible Relays"));
	addMenuItem( 7, getMyIcons().getIcon(eMyIconRefreshNormal),	tr("Refresh List"));
	exec();
}

//============================================================================
void PopupMenu::showFriendMenu( VxNetIdent * poSelectedFriend )
{
	m_SelectedFriend = poSelectedFriend;
	// populate title
	QString strTitle = poSelectedFriend->describeMyFriendshipToHim();
	strTitle += ": ";
	strTitle += poSelectedFriend->getOnlineName();
	setTitle(strTitle );
	// populate menu
	EPluginAccessState ePluginAccess;
	QString strAction;

	addMenuItem( (int)eMaxPluginType + 1, getMyIcons().getIcon(eMyIconPermissions), QObject::tr( "Change Friendship") );

	ePluginAccess = poSelectedFriend->getMyAccessPermissionFromHim( ePluginTypeWebServer );
	strAction = DescribePluginAction( poSelectedFriend, ePluginTypeWebServer, ePluginAccess );
	addMenuItem( (int)ePluginTypeWebServer, getMyIcons().getIcon(getMyIcons().getPluginIcon( ePluginTypeWebServer, ePluginAccess )), strAction );

	ePluginAccess = poSelectedFriend->getMyAccessPermissionFromHim( ePluginTypeStoryBoard );
	strAction = DescribePluginAction( poSelectedFriend, ePluginTypeStoryBoard, ePluginAccess );
	addMenuItem( (int)ePluginTypeStoryBoard, getMyIcons().getIcon(getMyIcons().getPluginIcon( ePluginTypeStoryBoard, ePluginAccess ) ), strAction );

	ePluginAccess = poSelectedFriend->getMyAccessPermissionFromHim( ePluginTypeMultiSession );
	strAction = DescribePluginAction( poSelectedFriend, ePluginTypeMultiSession, ePluginAccess );
	addMenuItem( (int)ePluginTypeMultiSession, getMyIcons().getIcon(getMyIcons().getPluginIcon( ePluginTypeMultiSession, ePluginAccess ) ), strAction );

	ePluginAccess = poSelectedFriend->getMyAccessPermissionFromHim(ePluginTypeVideoPhone);
	strAction = DescribePluginAction( poSelectedFriend, ePluginTypeVideoPhone, ePluginAccess );
	addMenuItem( (int)ePluginTypeVideoPhone, getMyIcons().getIcon(getMyIcons().getPluginIcon( ePluginTypeVideoPhone, ePluginAccess ) ), strAction );

	ePluginAccess = poSelectedFriend->getMyAccessPermissionFromHim(ePluginTypeVoicePhone);
	strAction = DescribePluginAction( poSelectedFriend, ePluginTypeVoicePhone, ePluginAccess );
	addMenuItem( (int)ePluginTypeVoicePhone, getMyIcons().getIcon(getMyIcons().getPluginIcon( ePluginTypeVoicePhone, ePluginAccess ) ), strAction );

	ePluginAccess = poSelectedFriend->getMyAccessPermissionFromHim(ePluginTypeTruthOrDare);
	strAction = DescribePluginAction( poSelectedFriend, ePluginTypeTruthOrDare, ePluginAccess );
	addMenuItem( (int)ePluginTypeTruthOrDare, getMyIcons().getIcon(getMyIcons().getPluginIcon( ePluginTypeTruthOrDare, ePluginAccess ) ), strAction );

	ePluginAccess = poSelectedFriend->getMyAccessPermissionFromHim(ePluginTypeCamServer);
	strAction = DescribePluginAction( poSelectedFriend, ePluginTypeCamServer, ePluginAccess );
	addMenuItem( (int)ePluginTypeCamServer, getMyIcons().getIcon(getMyIcons().getPluginIcon( ePluginTypeCamServer, ePluginAccess ) ), strAction );

	ePluginAccess = poSelectedFriend->getMyAccessPermissionFromHim(ePluginTypeFileOffer);
	strAction = DescribePluginAction( poSelectedFriend, ePluginTypeFileOffer, ePluginAccess );
	addMenuItem( (int)ePluginTypeFileOffer, getMyIcons().getIcon(getMyIcons().getPluginIcon( ePluginTypeFileOffer, ePluginAccess ) ), strAction );

	ePluginAccess = poSelectedFriend->getMyAccessPermissionFromHim(ePluginTypeFileServer);
	strAction = DescribePluginAction( poSelectedFriend, ePluginTypeFileServer, ePluginAccess );
	addMenuItem( (int)ePluginTypeFileServer, getMyIcons().getIcon(getMyIcons().getPluginIcon(ePluginTypeFileServer, ePluginAccess) ), strAction );

	ePluginAccess = poSelectedFriend->getMyAccessPermissionFromHim(ePluginTypeRelay);
	strAction = DescribePluginAction( poSelectedFriend, ePluginTypeRelay, ePluginAccess );
	addMenuItem( (int)ePluginTypeRelay, getMyIcons().getIcon(getMyIcons().getPluginIcon(ePluginTypeRelay, ePluginAccess ) ), strAction );

	exec();
}

//============================================================================
//! user selected friend action
void PopupMenu::onFriendActionSelected( int iMenuId, QWidget * )
{
	switch( iMenuId )
	{
	case ePluginTypeWebServer: // view profile
		if( m_SelectedFriend->isMyAccessAllowedFromHim( ePluginTypeWebServer ) )
		{
			m_MyApp.offerToFriendViewProfile( m_SelectedFriend );
		}

		break;

	case ePluginTypeStoryBoard: 
		if( m_SelectedFriend->isMyAccessAllowedFromHim( ePluginTypeStoryBoard ) )
		{
			m_MyApp.offerToFriendViewStoryboard( m_SelectedFriend );
		}

		break;

	case ePluginTypeVideoPhone:	
	case ePluginTypeVoicePhone:	
	case ePluginTypeTruthOrDare: 
	case ePluginTypeCamServer: 
	case ePluginTypeMultiSession: 
		if( m_SelectedFriend->isMyAccessAllowedFromHim( (EPluginType)iMenuId ) )
		{
			m_MyApp.offerToFriendPluginSession( m_SelectedFriend, (EPluginType)iMenuId );
		}
		else
		{
			QString warnTitle = QObject::tr("Insufficient Permission Level");
			QString warmPermission = warnTitle + QObject::tr(" To Access Plugin ") + DescribePluginType( (EPluginType)iMenuId );
			QMessageBox::warning(this, QObject::tr("Insufficient Permission Level "), warmPermission );
		}

		break;

	case ePluginTypeFileServer: 
		if( m_SelectedFriend->isMyAccessAllowedFromHim( ePluginTypeFileServer ) )
		{
			m_MyApp.offerToFriendViewSharedFiles( m_SelectedFriend );
		}

		break;

	case ePluginTypeFileOffer:
		if( m_SelectedFriend->isMyAccessAllowedFromHim( ePluginTypeFileOffer ) )
		{
			m_MyApp.offerToFriendSendFile( m_SelectedFriend );
		}

		break;

	case ePluginTypeRelay: 
		if( m_SelectedFriend->isMyAccessAllowedFromHim( ePluginTypeRelay ) )
		{
			// see if user wants to change his preferred proxy
			m_MyApp.offerToFriendUseAsRelay( m_SelectedFriend );
		}

		break;

	case eMaxPluginType + 1: // change friendship
		m_MyApp.offerToFriendChangeFriendship( m_SelectedFriend );
		break;

	default:
		LogMsg( LOG_ERROR, "Unknown Menu id\n");
	}

	close();
}


