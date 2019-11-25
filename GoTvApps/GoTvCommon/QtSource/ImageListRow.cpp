//============================================================================
// Copyright (C) 2009 Brett R. Jones 
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

#include "ImageListRow.h"
#include "ThumbnailViewWidget.h"
#include "GuiParams.h"

#include <CoreLib/VxDebug.h>

#include <QResizeEvent>

//============================================================================
ImageListRow::ImageListRow( QListWidget * parent  )
: QWidget( parent )
{
    ui.setupUi( this );
}

//============================================================================
void ImageListRow::resizeEvent( QResizeEvent * ev )
{
    QWidget::resizeEvent( ev );
    LogMsg( LOG_DEBUG, "ImageListRow Resize w %d h %d\n", ev->size().width(), ev->size().height() );
}

//============================================================================
void ImageListRow::addThumbnail( ThumbnailViewWidget * thumbnail )
{
    layout()->addWidget( thumbnail );
    m_ThumbnailCnt++;
}

//============================================================================
void ImageListRow::setRowNum( int rowNum )
{
    ui.m_RowLabel->setText( QString::number( rowNum ) );
}

//============================================================================
bool ImageListRow::hasRoomForThumbnail( void )
{
    int curWidth = width();
    int curHeight = height();
    LogMsg( LOG_DEBUG, "ImageListRow Resize w %d h %d\n", curWidth, curHeight );
    int requiredWidth = ( ( m_ThumbnailCnt + 1 ) * ( GuiParams::getThumbnailSize().width() + 20 ) + 20 );
    return requiredWidth < curWidth;
}
