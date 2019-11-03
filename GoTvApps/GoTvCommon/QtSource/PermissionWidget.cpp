//============================================================================
// Copyright (C) 2019 Brett R. Jones
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

#include "PermissionWidget.h"
#include "AppCommon.h"
#include "AppGlobals.h"
#include "ActivityInformation.h"

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>

namespace
{
    EFriendState ComboIdxToFriendState( int comboIdx )
    {
        switch( comboIdx )
        {
        case 0:
            return eFriendStateAdmin;
        case 1:
            return eFriendStateFriend;
        case 2:
            return eFriendStateGuest;
        case 3:
            return eFriendStateAnonymous;
        default:
            return eFriendStateIgnore;
        }
    }

    int FriendStateToComboIdx( EFriendState friendState )
    {
        switch( friendState )
        {
        case eFriendStateAdmin:
            return 0;
        case eFriendStateFriend:
            return 1;
        case eFriendStateGuest:
            return 2;
        case eFriendStateAnonymous:
            return 3;
        default:
            return 4;
        }
    }

}

//============================================================================
PermissionWidget::PermissionWidget( QWidget * parent )
	: QWidget( parent )
    , m_MyApp( GetAppInstance() )
{
	initPermissionWidget();
}

//============================================================================
void PermissionWidget::initPermissionWidget( void )
{
	ui.setupUi( this );
    ui.m_PermissionInfoButton->setIcon( eMyIconInformation );
    fillPermissionComboBox();

    connect( ui.m_PermissionInfoButton, SIGNAL( clicked() ), this, SLOT( slotShowPermissionInformation() ) );
    connect( ui.m_PermissionButton, SIGNAL( clicked() ), this, SLOT( slotShowPermissionInformation() ) );
    connect( ui.m_PermissionComboBox, SIGNAL( currentIndexChanged( int ) ), this, SLOT( slotHandleSelectionChanged( int ) ) );
    connect( ui.m_PluginInfoButton, SIGNAL( clicked() ), this, SLOT( slotShowPluginInformation() ) );
}
//============================================================================
void PermissionWidget::fillPermissionComboBox( void )
{
    ui.m_PermissionComboBox->addItem( DescribePermissionLevel( eFriendStateAdmin ) );
    ui.m_PermissionComboBox->addItem( DescribePermissionLevel( eFriendStateFriend ) );
    ui.m_PermissionComboBox->addItem( DescribePermissionLevel( eFriendStateGuest ) );
    ui.m_PermissionComboBox->addItem( DescribePermissionLevel( eFriendStateAnonymous ) );
    ui.m_PermissionComboBox->addItem( DescribePermissionLevel( eFriendStateIgnore ) );
    ui.m_PermissionComboBox->setCurrentIndex( 4 );
}

//============================================================================
void PermissionWidget::updateUi( void )
{
    if( m_PluginType == ePluginTypeInvalid )
    {
        return;
    }

    EFriendState pluginPermission = m_MyApp.getMyIdentity()->getPluginPermission( m_PluginType );
    ui.m_PermissionComboBox->setCurrentIndex( FriendStateToComboIdx( pluginPermission ) );
    updatePermissionIcon();
}

//============================================================================
void PermissionWidget::updatePermissionIcon( void )
{
    if( m_PluginType == ePluginTypeInvalid )
    {
        return;
    }

    ui.m_PermissionButton->setIcon( m_MyApp.getMyIcons().getFriendshipIcon( ComboIdxToFriendState( ui.m_PermissionComboBox->currentIndex() ) ) );
    ui.m_PluginInfoButton->setIcon( m_MyApp.getMyIcons().getPluginIcon( m_PluginType ) );
}

//============================================================================
void PermissionWidget::slotHandleSelectionChanged( int )
{
    if( m_PluginType == ePluginTypeInvalid )
    {
        return;
    }

    EFriendState pluginPermission = ComboIdxToFriendState( ui.m_PermissionComboBox->currentIndex() );
    UpdatePluginPermissions( m_MyApp.getEngine(), m_PluginType, pluginPermission );
    updatePermissionIcon();
}

//============================================================================
void PermissionWidget::slotShowPermissionInformation()
{
    ActivityInformation * activityInfo = new ActivityInformation( m_MyApp, this, eInfoTypePermission );
    activityInfo->show();
}

//============================================================================
void PermissionWidget::slotShowPluginInformation()
{
    ActivityInformation * activityInfo = new ActivityInformation( m_MyApp, this, m_PluginType );
    activityInfo->show();
}
