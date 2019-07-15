#pragma once
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

#include "FriendList.h"
#include "VxGuidQt.h"

#include <CoreLib/VxTimer.h>

#include <CoreLib/VxTimer.h>
#include <CoreLib/AssetDefs.h>

#include <QListWidget>

class ListEntryWidget;
class VxNetIdent;
class AppCommon;
class MyIcons;
class P2PEngine;

class FriendListWidget : public QListWidget
{
	Q_OBJECT

public:
	FriendListWidget( QWidget * parent );

	AppCommon&					getMyApp( void ) { return m_MyApp; }
	MyIcons&					getMyIcons( void );

	void						setFriendViewType( EFriendViewType eWhichFriendsToShow );
	EFriendViewType				getFriendViewType( void );

	void						setFriendHasUnviewedTextMessages( VxGUID& onlineId, bool hasTextMsgs );
	//! update friend in list
	void						updateFriend( VxNetIdent * netIdent, bool sessionTimeChange = false );
	void						removeFriend( VxNetIdent * netIdent );
	void						refreshFriendList( EFriendViewType eWhichFriendsToShow );

signals:
	void						signalUpdateFriend( VxNetIdent * netIdent, bool sessionTimeChange );
	void						signalFriendClicked( VxNetIdent * netIdent );
	void						signalRefreshFriendList( EFriendViewType eWhichFriendsToShow );

private slots:
	void						slotUpdateFriend( VxNetIdent * netIdent, bool sessionTimeChange );
	void						slotRefreshFriend( VxGuidQt friendId );
	void						slotAssetViewMsgAction( EAssetAction eAssetAction, VxGuidQt onlineId, int pos );
	void						slotItemClicked(QListWidgetItem *);
	void						slotRefreshFriendList( EFriendViewType eWhichFriendsToShow );
	void						slotFriendListItemClicked( ListEntryWidget* widget );
	void						slotFriendMenuButtonClicked( ListEntryWidget* widget );

protected:
	//!	fill friend into new QListWidgetItem *
	ListEntryWidget *			friendToWidget( VxNetIdent * poFriend );
	//!	get friend from QListWidgetItem data
	Friend *					widgetToFriend( ListEntryWidget * item );

	void						updateListEntryWidget( ListEntryWidget * item, VxNetIdent * netIdent );

	ListEntryWidget *			findListEntryWidget( VxNetIdent * netIdent );

	void						updateListEntryBackgroundColor( VxNetIdent * netIdent, ListEntryWidget * poWidget );

	//=== vars ===//
	AppCommon&					m_MyApp;
	P2PEngine&					m_Engine;
	EFriendViewType				m_eFriendViewType;
    Friend *					m_SelectedFriend;
	VxTimer						m_ClickEventTimer; // avoid duplicate clicks
	VxGUID						m_ViewingOnlineId;
	bool						m_IsCurrentlyViewing;
};

