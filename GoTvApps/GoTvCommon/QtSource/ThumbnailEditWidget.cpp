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
#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>
#include <VxVideoLib/VxVideoLib.h>

#include <QMessageBox>

//============================================================================
ThumbnailEditWidget::ThumbnailEditWidget( QWidget * parent )
    : QWidget( parent )
    , m_MyApp( GetAppInstance() )
{
    m_CameraSourceAvail = GuiHelpers::isCameraSourceAvailable();
    ui.setupUi( this );

    connect( ui.m_TakeSnapshotButton, SIGNAL( clicked() ), this, SLOT( slotSnapShotButClick() ) );
    connect( ui.m_BrowsePictureButton, SIGNAL( clicked() ), this, SLOT( slotBrowseButClick() ) );
}

//============================================================================
//! take picture for me
void ThumbnailEditWidget::slotSnapShotButClick( void )
{
    if( m_CameraSourceAvail )
    {
        ActivitySnapShot oDlg( m_MyApp, this );
        connect( &oDlg, SIGNAL( signalJpgSnapshot( uint8_t*, uint32_t, int, int ) ), ui.m_ThumbnailViewWidget, SLOT( slotJpgSnapshot( uint8_t*, uint32_t, int, int ) ) );
        oDlg.exec();
    }
    else
    {
        QMessageBox::warning( this, QObject::tr( "Camera Capture" ), QObject::tr( "No Camera Source Available." ) );
    }
}

//============================================================================
//! take picture for me
void ThumbnailEditWidget::slotBrowseButClick( void )
{
    ui.m_ThumbnailViewWidget->browseForImage();
}
