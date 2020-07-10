//============================================================================
// Copyright (C) 2020 Brett R. Jones
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

#include "PermissionListItem.h"
#include "AppCommon.h"
#include "AppGlobals.h"
#include "ActivityInformation.h"
#include "GuiHelpers.h"
#include "GuiParams.h"

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>
#include <GoTvCore/GoTvP2P/P2PEngine/PluginSetting.h>

//============================================================================
PermissionListItem::PermissionListItem( QListWidget * parent )
: QWidget( parent )
, m_MyApp( GetAppInstance() )
, m_SizeHint( parent ? parent->geometry().width() : 200, GuiParams::getButtonSize() + 30 )
{
    ui.setupUi( this );
    setSizeHint( m_SizeHint );
}

//============================================================================
void PermissionListItem::initPermissionListItem( void )
{
    ui.m_PermissionInfoButton->setIcon( eMyIconInformation );
    fillPermissionComboBox();
    fillPluginInfo();
    if( m_PluginType != ePluginTypeInvalid )
    {
        updateUi();
    }
}

//============================================================================
void PermissionListItem::fillPermissionComboBox( void )
{
    ui.m_PermissionComboBox->addItem( DescribePermissionLevel( eFriendStateAdmin ) );
    ui.m_PermissionComboBox->addItem( DescribePermissionLevel( eFriendStateFriend ) );
    ui.m_PermissionComboBox->addItem( DescribePermissionLevel( eFriendStateGuest ) );
    ui.m_PermissionComboBox->addItem( DescribePermissionLevel( eFriendStateAnonymous ) );
    ui.m_PermissionComboBox->addItem( DescribePermissionLevel( eFriendStateIgnore ) );
    ui.m_PermissionComboBox->setCurrentIndex( 4 );
}

//============================================================================
void PermissionListItem::fillPluginInfo()
{
    if( m_PluginType != ePluginTypeInvalid )
    {
        QString pluginName = GuiHelpers::describePlugin( m_PluginType, false ).c_str();
        ui.m_ServiceNameLabel->setText( pluginName );
        PluginSetting pluginSetting;
        m_MyApp.getEngine().getPluginSetting( m_PluginType, pluginSetting );
        QString pluginDesc = pluginSetting.getDescription().c_str();
        ui.m_ServiceDescLabel->setText( pluginName );
    }
}

//============================================================================
void PermissionListItem::updateUi( void )
{
    if( m_PluginType == ePluginTypeInvalid )
    {
        return;
    }

    EFriendState pluginPermission = m_MyApp.getMyIdentity()->getPluginPermission( m_PluginType );
    if( !m_OrigPermissionIsSet )
    {
        m_OrigPermissionIsSet = true;
        m_OrigPermissionLevel = pluginPermission;
    }

    ui.m_PermissionComboBox->setCurrentIndex( GuiHelpers::friendStateToComboIdx( pluginPermission ) );
    if( !m_PermissionsConnected )
    {
        m_PermissionsConnected = true;
        connect( ui.m_PermissionInfoButton, SIGNAL( clicked() ), this, SLOT( slotShowPermissionInformation() ) );
        connect( ui.m_PermissionButton, SIGNAL( clicked() ), this, SLOT( slotShowPermissionInformation() ) );
        connect( ui.m_PermissionComboBox, SIGNAL( currentIndexChanged( int ) ), this, SLOT( slotHandleSelectionChanged( int ) ) );
        connect( ui.m_PluginInfoButton, SIGNAL( clicked() ), this, SLOT( slotShowPluginInformation() ) );
    }

    updatePermissionIcon();
}

//============================================================================
void PermissionListItem::setPluginType( EPluginType pluginType, int subType ) 
{ 
    if( pluginType == ePluginTypeInvalid )
    {
        return;
    }

    m_PluginType = pluginType;
    m_SubPluginType = subType;

    if( !m_OrigPermissionIsSet )
    {
        m_OrigPermissionIsSet = true;
        m_OrigPermissionLevel = m_MyApp.getMyIdentity()->getPluginPermission( m_PluginType );;
        setPermissionLevel( m_OrigPermissionLevel );
    }

    updateUi();  
    updatePermissionIcon(); 
}

//============================================================================
void PermissionListItem::updatePermissionIcon( void )
{
    if( m_PluginType == ePluginTypeInvalid )
    {
        return;
    }

    ui.m_PermissionButton->setIcon( m_MyApp.getMyIcons().getFriendshipIcon( GuiHelpers::comboIdxToFriendState( ui.m_PermissionComboBox->currentIndex() ) ) );
    ui.m_PluginInfoButton->setIcon( m_MyApp.getMyIcons().getPluginIcon( m_PluginType ) );
}

//============================================================================
void PermissionListItem::slotHandleSelectionChanged( int )
{
    if( m_PluginType == ePluginTypeInvalid )
    {
        return;
    }

    EFriendState pluginPermission = GuiHelpers::comboIdxToFriendState( ui.m_PermissionComboBox->currentIndex() );
    m_MyApp.getAppGlobals().updatePluginPermission( m_PluginType, pluginPermission );
    updatePermissionIcon();
}

//============================================================================
void PermissionListItem::slotShowPermissionInformation()
{
    ActivityInformation * activityInfo = new ActivityInformation( m_MyApp, this, eInfoTypePermission );
    activityInfo->show();
}

//============================================================================
void PermissionListItem::slotShowPluginInformation()
{
    ActivityInformation * activityInfo = new ActivityInformation( m_MyApp, this, m_PluginType );
    activityInfo->show();
}

//============================================================================
void PermissionListItem::setPermissionLevel( EFriendState permLevel )
{
    if( m_PluginType == ePluginTypeInvalid )
    {
        return;
    }

    ui.m_PermissionComboBox->setCurrentIndex( GuiHelpers::friendStateToComboIdx( permLevel ) );
}

//============================================================================
EFriendState PermissionListItem::getPermissionLevel( void )
{
    if( m_PluginType == ePluginTypeInvalid )
    {
        return eFriendStateIgnore;
    }

    return GuiHelpers::comboIdxToFriendState( ui.m_PermissionComboBox->currentIndex() );
}
