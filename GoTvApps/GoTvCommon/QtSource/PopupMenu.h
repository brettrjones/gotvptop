#pragma once
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
// http://www.nolimitconnect.com
//============================================================================

#include "ActivityBase.h"
#include "ui_PopupMenuWidget.h"

class VxNetIdent;
class AppCommon;
class TitleBarWidget;
class BottomBarWidget;


class PopupMenu : public ActivityBase
{
	Q_OBJECT
public:
	PopupMenu( AppCommon& app, QWidget * parent );
	virtual ~PopupMenu() override = default;

    virtual void	            setTitleBarWidget( TitleBarWidget * titleWidget ) { m_TitleBarWidget = titleWidget; }
    virtual void	            setBottomBarWidget( BottomBarWidget * bottomWidget ) { m_BottomBarWidget = bottomWidget; }
    // overrides required for dialogs with there own title bar and bottom bar widgets
    virtual TitleBarWidget *	getTitleBarWidget( void ) override { return m_TitleBarWidget; }
    virtual BottomBarWidget *	getBottomBarWidget( void ) override { return m_BottomBarWidget; }

	void						setTitle( QString strTitle );
	void						addMenuItem( int iItemId, QIcon& oIcon, QString strMenuItemText );

	void						showRefreshMenu();
	void						showFriendMenu( VxNetIdent * poSelectedFriend );
    void						showAppSystemMenu( void );

signals:
	void						menuItemClicked( int iItemId, QWidget * popupMenu );

public slots:
	void						onFriendActionSelected( int iMenuId, QWidget * popupMenu );

private slots:
	//! user clicked the upper right x button
    void						slotHomeButtonClicked( void ) override;
	//! user checked or unchecked menu item
	//void			userCheckedOrUncheckedAnItem( QListWidgetItem * item );
	//! user selected menu item
	void						itemClicked(QListWidgetItem *item);

protected:
	//=== vars ===//
	Ui::popupMenu				ui;
    int							m_iMenuItemHeight{ 48 };
    VxNetIdent *				m_SelectedFriend{ nullptr };
    TitleBarWidget *			m_TitleBarWidget{ nullptr };
    BottomBarWidget *			m_BottomBarWidget{ nullptr };
};


