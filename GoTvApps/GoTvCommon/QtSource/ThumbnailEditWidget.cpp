//============================================================================
// Copyright (C) 2019 Brett R. Jones
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

#include "ThumbnailEditWidget.h"
#include "ActivitySnapShot.h"
#include "AppCommon.h"
#include "GuiHelpers.h"

#include <CoreLib/VxDebug.h>
#include <GoTvCore/GoTvP2P/AssetMgr/AssetInfo.h>
#include <GoTvCore/GoTvP2P/AssetMgr/AssetMgr.h>
#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>

#include <VxVideoLib/VxVideoLib.h>

#include <QMessageBox>
#include <QPainter>

//============================================================================
ThumbnailEditWidget::ThumbnailEditWidget( QWidget * parent )
    : QWidget( parent )
    , m_MyApp( GetAppInstance() )
{
    m_CameraSourceAvail = GuiHelpers::isCameraSourceAvailable();
    ui.setupUi( this );

    connect( ui.m_TakeSnapshotButton, SIGNAL( clicked() ), this, SLOT( slotSnapShotButClick() ) );
    connect( ui.m_BrowsePictureButton, SIGNAL( clicked() ), this, SLOT( slotBrowseButClick() ) );
    connect( ui.m_MakeCircleButton, SIGNAL( clicked() ), this, SLOT( slotMakeCircleButClick() ) );
    connect( ui.m_UndoCircleButton, SIGNAL( clicked() ), this, SLOT( slotUndoCircleClick() ) );

}

//============================================================================
bool ThumbnailEditWidget::loadFromAsset( AssetInfo * thumbAsset )
{
    bool loadOk = false;
    if( thumbAsset )
    {
        loadOk = ui.m_ThumbnailViewWidget->loadFromFile( thumbAsset->getAssetName().c_str() );
    }

    return loadOk;
}

//============================================================================
void ThumbnailEditWidget::slotSnapShotButClick( void )
{
    if( m_CameraSourceAvail )
    {
        ActivitySnapShot oDlg( m_MyApp, this );
        connect( &oDlg, SIGNAL( signalJpgSnapshot( uint8_t*, uint32_t, int, int ) ), ui.m_ThumbnailViewWidget, SLOT( slotJpgSnapshot( uint8_t*, uint32_t, int, int ) ) );
        oDlg.exec();
        m_IsCircle = !ui.m_ThumbnailViewWidget->getIsUserPickedImage();
    }
    else
    {
        QMessageBox::warning( this, QObject::tr( "Camera Capture" ), QObject::tr( "No Camera Source Available." ) );
    }
}

//============================================================================
void ThumbnailEditWidget::slotBrowseButClick( void )
{
    ui.m_ThumbnailViewWidget->browseForImage();
    m_IsCircle = !ui.m_ThumbnailViewWidget->getIsUserPickedImage();
}

//============================================================================
void ThumbnailEditWidget::slotMakeCircleButClick( void )
{
    if( !m_IsCircle )
    {
        m_SquarePixmap = *ui.m_ThumbnailViewWidget->getThumbnailImage();
        if( !m_SquarePixmap.isNull() )
        {
            m_IsCircle = true;
            ui.m_ThumbnailViewWidget->setThumbnailImage( makeCircleImage( m_SquarePixmap ) );
        }
    }
}

//============================================================================
void ThumbnailEditWidget::slotUndoCircleClick( void )
{
    if( m_IsCircle && !m_SquarePixmap.isNull() )
    {
        m_IsCircle = false;
        ui.m_ThumbnailViewWidget->setThumbnailImage( m_SquarePixmap );
    }
}

//============================================================================
QPixmap ThumbnailEditWidget::makeCircleImage( QPixmap& pixmap )
{
    QPixmap target( pixmap.width(), pixmap.height() );
    target.fill( Qt::transparent );

    QPainter painter( &target );

    // Set clipped region (circle) in the center of the target image
    QRegion clipRegion( QRect( 0, 0, pixmap.width(), pixmap.height() ), QRegion::Ellipse );
    painter.setClipRegion( clipRegion );

    painter.drawPixmap( 0, 0, pixmap );  
    return target;
}
