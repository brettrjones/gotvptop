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
// http://www.gotvptop.com
//============================================================================

#include "PermissionWidget.h"
#include "AppCommon.h"

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>

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

    connect( ui.m_PermissionComboBox, SIGNAL( currentIndexChanged( int ) ), this, SLOT( slotHandleSelectionChanged( int ) ) );


	//ui.m_PlayPauseButton->setIcons( eMyIconPlayNormal );
	//ui.m_PlayPauseButton->setPressedSound( eSndDefNone );
	//ui.m_PlayPosSlider->setRange( 0, 100000 );
	//ui.m_PlayPosSlider->setMinimum( 0 );
	//ui.m_PlayPosSlider->setMaximum( 100000 );
	//ui.m_TagFrame->setVisible( false );

	//connect( ui.m_PlayPauseButton, SIGNAL( clicked() ), this, SLOT( slotPlayButtonClicked() ) );
	//connect( ui.m_LeftAvatarBar, SIGNAL( signalShredAsset() ), this, SLOT( slotShredAsset() ) );
	//connect( ui.m_RightAvatarBar, SIGNAL( signalShredAsset() ), this, SLOT( slotShredAsset() ) );
	////connect( &m_MyApp, SIGNAL(signalAssetAction(EAssetAction, VxGuidQt, int)), this, SLOT(slotToGuiAssetAction(EAssetAction, VxGuidQt, int)) );
	//connect( ui.m_PlayPosSlider, SIGNAL( sliderPressed() ), this, SLOT( slotSliderPressed() ) );
	//connect( ui.m_PlayPosSlider, SIGNAL( sliderReleased() ), this, SLOT( slotSliderReleased() ) );
	//connect( ui.m_LeftAvatarBar, SIGNAL( signalResendAsset() ), this, SLOT( slotResendAsset() ) );
}

//============================================================================
void PermissionWidget::updatePermissions( void )
{
    if( m_PluginType == ePluginTypeInvalid )
    {
        return;
    }

}

//============================================================================
void PermissionWidget::slotHandleSelectionChanged( int )
{
    if( m_PluginType == ePluginTypeInvalid )
    {
        return;
    }

}