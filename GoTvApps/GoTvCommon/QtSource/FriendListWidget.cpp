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
// brett.jones@engineer.com
// http://www.gotvptop.net
//============================================================================

#include "ListEntryWidget.h"
#include "FriendListWidget.h"

#include "MyIcons.h"
#include "PopupMenu.h"
#include "AppGlobals.h"
#include "AppCommon.h"

#include <CoreLib/VxDebug.h>
 
//============================================================================
FriendListWidget::FriendListWidget( QWidget * parent )
: QListWidget( parent )
, m_MyApp( GetAppInstance() )
, m_Engine( m_MyApp.getEngine() )
, m_eFriendViewType( eFriendViewEverybody )
, m_SelectedFriend( NULL )
, m_ViewingOnlineId()
, m_IsCurrentlyViewing( false )
{
	QListWidget::setSortingEnabled( true );
	sortItems( Qt::DescendingOrder );
	connect( this, SIGNAL(signalRefreshFriendList(EFriendViewType)), 
             this, SLOT(slotRefreshFriendList(EFriendViewType)), Qt::QueuedConnection );

	if( false == connect( this, SIGNAL(itemClicked(QListWidgetItem *)), 
                          this, SLOT(slotItemClicked(QListWidgetItem *))) )
	{
		LogMsg( LOG_INFO, "FriendListWidget could not connect to slotItemClicked\n");
	}

	if( false == connect( this, SIGNAL(itemDoubleClicked(QListWidgetItem *)), 
                          this, SLOT(slotItemClicked(QListWidgetItem *))) )
	{
		LogMsg( LOG_INFO, "FriendListWidget could not connect to slotItemClicked\n");
	}

	if( false == connect( this, SIGNAL(signalUpdateFriend( VxNetIdent *,bool)), 
                          this, SLOT(slotUpdateFriend( VxNetIdent *,bool))), Qt::QueuedConnection )
	{
		LogMsg( LOG_INFO, "FriendListWidget could not connect to slotUpdateFriend\n");
	}

	if( false == connect( &m_MyApp, SIGNAL(signalRefreshFriend(VxGuidQt)), 
                          this, SLOT(slotRefreshFriend(VxGuidQt))), Qt::QueuedConnection )
	{
		LogMsg( LOG_INFO, "FriendListWidget could not connect to slotRefreshFriend\n");
	}

	if( false == connect( &m_MyApp, SIGNAL(signalAssetViewMsgAction(EAssetAction,VxGuidQt,int)), 
                          this, SLOT(slotAssetViewMsgAction(EAssetAction,VxGuidQt,int))), Qt::QueuedConnection )
	{
		LogMsg( LOG_INFO, "FriendListWidget could not connect to slotAssetViewMsgAction\n");
	}
}

//============================================================================
MyIcons&  FriendListWidget::getMyIcons( void )
{
	return m_MyApp.getMyIcons();
}

//============================================================================
void FriendListWidget::slotAssetViewMsgAction( EAssetAction eAssetAction, VxGuidQt onlineIdIn, int pos0to100000 )
{
	VxGUID onlineId;
	uint64_t hiPart = onlineIdIn.getVxGUIDHiPart();
	uint64_t loPart = onlineIdIn.getVxGUIDLoPart();
	onlineId.setVxGUID( hiPart, loPart );

	if( eAssetActionRxViewingMsg == eAssetAction )
	{
		m_IsCurrentlyViewing = pos0to100000 ? true : false;
		if( m_IsCurrentlyViewing )
		{
			m_ViewingOnlineId = onlineId;
			setFriendHasUnviewedTextMessages( m_ViewingOnlineId, false );
		}

		return;
	}

	if( eAssetActionRxNotifyNewMsg == eAssetAction )
	{
		if( m_IsCurrentlyViewing 
			&& ( onlineId == m_ViewingOnlineId ) )
		{
			// user is viewing messages from this contact
			setFriendHasUnviewedTextMessages( onlineId, false );
			return;
		}

		setFriendHasUnviewedTextMessages( onlineId, true );
	}
}

//============================================================================
void FriendListWidget::setFriendHasUnviewedTextMessages( VxGUID& onlineId, bool hasTextMsgs )
{
	ListEntryWidget * poWidget;
	int iIdx = 0;
	while( iIdx < this->count() )
	{
		poWidget = (ListEntryWidget *)this->item(iIdx);
		if( poWidget )
		{
			Friend * poFriend = (Friend *)poWidget->data( Qt::UserRole + 2 ).toULongLong();
			if( poFriend
				&& ( poFriend->getMyOnlineId() == onlineId ) )
			{
				// found the widget
				poFriend->setHasTextOffers( hasTextMsgs );
				updateListEntryWidget( poWidget, poFriend );
				return;
			}
		}

		iIdx++;
	}
}

//============================================================================
void FriendListWidget::setFriendViewType( EFriendViewType eWhichFriendsToShow )
{
	m_eFriendViewType = eWhichFriendsToShow;
}

//============================================================================
EFriendViewType FriendListWidget::getFriendViewType( void )
{
	return m_eFriendViewType;
}

//============================================================================
void FriendListWidget::refreshFriendList( EFriendViewType eWhichFriendsToShow )
{
	this->clear();
	emit signalRefreshFriendList( eWhichFriendsToShow );
}

//============================================================================
void FriendListWidget::slotRefreshFriendList( EFriendViewType eWhichFriendsToShow )
{
	this->clear();
	this->setFriendViewType( eWhichFriendsToShow );
	m_Engine.fromGuiSendContactList( eWhichFriendsToShow, 500 );
}

//============================================================================
void FriendListWidget::updateFriend( VxNetIdent * netIdent, bool sessionTimeChange ) 
{
	emit signalUpdateFriend( netIdent, sessionTimeChange );
}

//============================================================================
void FriendListWidget::slotItemClicked(QListWidgetItem * item )
{
	if( 300 < m_ClickEventTimer.elapsedMs()  ) // avoid duplicate clicks
	{
		slotFriendListItemClicked( (ListEntryWidget *) item );
	}
}

//============================================================================
void FriendListWidget::slotFriendListItemClicked( ListEntryWidget* item )
{
	if( 300 > m_ClickEventTimer.elapsedMs()  ) // avoid duplicate clicks
	{
		return;
	}

	m_ClickEventTimer.startTimer();
	m_SelectedFriend = widgetToFriend( item );
	if( m_SelectedFriend )
	{
		if( m_SelectedFriend->isMyAccessAllowedFromHim( ePluginTypeMultiSession ) )
		{
			QWidget * parent2 = 0;
			QWidget * parent1 = (QWidget *)this->parent();
			if( parent1 )
			{
				parent2 = (QWidget *)parent1->parent();
			}

			m_MyApp.offerToFriendPluginSession( m_SelectedFriend, ePluginTypeMultiSession, parent2 ? parent2 : parent1 );
			emit signalFriendClicked( m_SelectedFriend );
		}
		else
		{
			QString warnTitle = QObject::tr("Insufficient Permission Level");
			QString warmPermission = warnTitle + QObject::tr(" To Access Plugin ") + DescribePluginType( ePluginTypeMultiSession );
			QMessageBox::warning(this, QObject::tr("Insufficient Permission Level "), warmPermission );
		}
	}
}

//============================================================================
void FriendListWidget::slotFriendMenuButtonClicked( ListEntryWidget* item )
{
	if( 300 > m_ClickEventTimer.elapsedMs()  ) // avoid duplicate clicks
	{
		return;
	}

	m_ClickEventTimer.startTimer();
	m_SelectedFriend = widgetToFriend( item );
	if( m_SelectedFriend )
	{
		emit signalFriendClicked( m_SelectedFriend );

		PopupMenu oPopupMenu( m_MyApp, (QWidget *)this->parent() );
		if( false == connect( &oPopupMenu, SIGNAL(menuItemClicked(int, QWidget *)), &oPopupMenu, SLOT(onFriendActionSelected(int, QWidget *)) ) )
		{
			LogMsg( LOG_ERROR, "FriendListWidget::findListEntryWidget failed connect\n" );
		}

		oPopupMenu.showFriendMenu( m_SelectedFriend );
	}
}

//============================================================================
void FriendListWidget::slotUpdateFriend( VxNetIdent * netIdent, bool sessionTimeChange ) 
{
	LogMsg( LOG_INFO, "FriendListWidget::slotUpdateFriend  %d\n", this->count() );
	ListEntryWidget * poWidget = findListEntryWidget( netIdent );
	if( poWidget )
	{
		LogMsg( LOG_INFO, "FriendListWidget::onFriendUpdated %s online ? %d widget exists\n", netIdent->getOnlineName(), netIdent->isOnline() );
		updateListEntryWidget( poWidget, netIdent );
	}
	else
	{
		ListEntryWidget * poFriendItem = friendToWidget( netIdent ); 
		int64_t hisSessionTime = netIdent->getLastSessionTimeMs();
		if( 0 == this->count() )
		{
			insertItem( this->count(), poFriendItem );
			LogMsg( LOG_INFO, "FriendListWidget::onFriendUpdated %s First Item online ? %d inserted %d time %d\n", netIdent->getOnlineName(), netIdent->isOnline(), this->count() - 1, hisSessionTime );
			//addItem( poFriendItem );
		}
		else
		{
			bool wasInserted = false;
			int rowIdx = 0;
			ListEntryWidget * listEntryWidget;
			while( rowIdx < this->count() )
			{
				listEntryWidget = (ListEntryWidget *)this->item( rowIdx );
				if( listEntryWidget )
				{
					Friend * listEntryFriend = (Friend *)listEntryWidget->data( Qt::UserRole + 2 ).toULongLong();
					if( listEntryFriend )
					{
						int64_t listSessionTime = listEntryFriend->getLastSessionTimeMs();
						if( listSessionTime < hisSessionTime )
						{
							LogMsg( LOG_INFO, "FriendListWidget::onFriendUpdated %s Insert Item online ? %d inserted %d time %d\n", netIdent->getOnlineName(), netIdent->isOnline(), rowIdx, hisSessionTime  );
							insertItem( rowIdx, poFriendItem );
							wasInserted = true;
							break;
						}
					}
				}

				rowIdx++;
			}

			if( false == wasInserted )
			{
				//addItem( poFriendItem );
				LogMsg( LOG_INFO, "FriendListWidget::onFriendUpdated %s Add Item online ? %d inserted %d time %d\n", netIdent->getOnlineName(), netIdent->isOnline(), this->count(), hisSessionTime );
				insertItem( this->count(), poFriendItem );
			}
		}

		poFriendItem->setSizeHint( poFriendItem->getSubWidget()->size() );

		setItemWidget( poFriendItem, poFriendItem->getSubWidget() );

		updateListEntryWidget( poFriendItem, netIdent );
	}
}

//============================================================================
void FriendListWidget::slotRefreshFriend( VxGuidQt friendId )
{
	int iIdx = 0;
	ListEntryWidget * poWidget;
	while( iIdx < this->count() )
	{
		poWidget = (ListEntryWidget *)this->item(iIdx);
		if( poWidget )
		{
			Friend * poFriend = (Friend *)poWidget->data( Qt::UserRole + 2 ).toULongLong();
			if( poFriend
				&& ( poFriend->getMyOnlineId().getVxGUIDHiPart() == friendId.getVxGUIDHiPart() )
				&& ( poFriend->getMyOnlineId().getVxGUIDLoPart() == friendId.getVxGUIDLoPart() ) )
			{
				// found the widget
				updateListEntryWidget( poWidget, poFriend );
				return;
			}
		}

		iIdx++;
	}
}

//============================================================================
//! called when friend in list is removed
void FriendListWidget::removeFriend( VxNetIdent * netIdent )
{
	int iIdx = 0;
	ListEntryWidget * poWidget;
	while( iIdx < this->count() )
	{
		poWidget = (ListEntryWidget *)this->item(iIdx);
		if( poWidget )
		{
			Friend * poFriend = (Friend *)poWidget->data( Qt::UserRole + 2 ).toULongLong();
			if( poFriend && ( poFriend->getMyOnlineId() == netIdent->getMyOnlineId() ) )
			{
				LogMsg( LOG_INFO, "AppCommon::onFriendRemoved %s removing widget idx %d\n", netIdent->getOnlineName(), iIdx );
				takeItem( iIdx );
				return;
			}
		}

		iIdx++;
	}
}

//============================================================================
void FriendListWidget::updateListEntryBackgroundColor( VxNetIdent * netIdent, ListEntryWidget * poWidget )
{
	if( netIdent->isNearby() )
	{
		poWidget->getSubWidget()->setStyleSheet("border-image: 0; background-color: rgb(21, 21, 255); color: rgb(0, 0, 0); font: 14px;\n");
		poWidget->getMenuButton()->setIcon( getMyIcons().getIcon( eMyIconMenuNormal ) );
	}
	else if(  netIdent->isOnline() )
	{
		poWidget->getSubWidget()->setStyleSheet("border-image: 0; background-color: rgb(184, 231, 249); color: rgb(0, 0, 0); font: 14px;\n");
		poWidget->getMenuButton()->setIcon( getMyIcons().getIcon( eMyIconMenuNormal ) );
	}
	else
	{
		poWidget->getSubWidget()->setStyleSheet("border-image: 0; background-color: rgb(192, 192, 192); color: rgb(0, 0, 0); font: 14px;\n");
		poWidget->getMenuButton()->setIcon( getMyIcons().getIcon( eMyIconMenuDisabled ) );
	}
}

//============================================================================
//!	fill friend into new QListWidgetItem *
ListEntryWidget * FriendListWidget::friendToWidget( VxNetIdent * poFriend )
{
	ListEntryWidget * item = new ListEntryWidget( this );
	item->setData( Qt::UserRole + 1, QVariant((uint64_t)(item->getSubWidget())) );
	item->setData( Qt::UserRole + 2, QVariant((uint64_t)(poFriend)) );
	if( false == connect( item, SIGNAL(listButtonClicked(ListEntryWidget*)), this, SLOT(slotFriendListItemClicked(ListEntryWidget*))) )
	{
		LogMsg( LOG_ERROR, "AppCommon::friendToWidget: connect failed\n");
	}

	if( false == connect( item, SIGNAL(signalMenuButtonClicked(ListEntryWidget*)), this, SLOT(slotFriendMenuButtonClicked(ListEntryWidget*))) )
	{
		LogMsg( LOG_ERROR, "AppCommon::friendToWidget: connect failed\n");
	}

	return item;
}

//============================================================================
void FriendListWidget::updateListEntryWidget( ListEntryWidget * item, VxNetIdent * netIdent )
{
	QString strName = netIdent->getOnlineName();
	strName += " - ";
	QString strDesc = netIdent->getOnlineDescription();
    // display in seconds
	QVariant dispValue( (uint)( netIdent->getLastSessionTimeMs() / 1000 ) );
	item->setData( Qt::DisplayRole, dispValue );

	updateListEntryBackgroundColor( netIdent, item );

	item->ui.m_IconButton->setIcon( getMyIcons().getFriendshipIcon( netIdent->getMyFriendshipToHim() ) );
	QPalette pal = item->ui.m_IconButton->palette();
	pal.setColor(QPalette::Button, QColor( netIdent->getHasTextOffers() ? Qt::yellow : Qt::white ));
	item->ui.m_IconButton->setAutoFillBackground(true);
	item->ui.m_IconButton->setPalette(pal);
	item->ui.m_IconButton->update();
	item->ui.TitlePart1->setText( strName );
	item->ui.TitlePart2->setText( netIdent->describeMyFriendshipToHim() );
	item->ui.DescPart2->setText( strDesc );
	item->ui.TodLabel->setText( QString("Truths: %1 Dares: %2").arg(netIdent->getTruthCount()).arg(netIdent->getDareCount()) );
}

//============================================================================
//!	get friend from QListWidgetItem data
Friend * FriendListWidget::widgetToFriend( ListEntryWidget * item )
{
	return (Friend *)item->data( Qt::UserRole + 2 ).toULongLong();
}

//============================================================================
ListEntryWidget * FriendListWidget::findListEntryWidget( VxNetIdent * netIdent )
{
	int iIdx = 0;
	ListEntryWidget * poWidget;
	while( iIdx < this->count() )
	{
		poWidget = (ListEntryWidget *)this->item(iIdx);
		if( poWidget )
		{
			Friend * poFriend = (Friend *)poWidget->data( Qt::UserRole + 2 ).toULongLong();
			if( poFriend && ( poFriend->getMyOnlineId() == netIdent->getMyOnlineId() ) )
			{
				return poWidget;
			}
		}

		iIdx++;
	}

	return NULL;
}
