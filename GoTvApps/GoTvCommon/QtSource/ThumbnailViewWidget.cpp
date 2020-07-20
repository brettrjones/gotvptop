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

#include "ThumbnailViewWidget.h"
#include "AppCommon.h"
#include "AppSettings.h"
#include "GuiHelpers.h"
#include "GuiParams.h"

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>
#include <GoTvCore/GoTvP2P/AssetMgr/AssetMgr.h>
#include <GoTvCore/GoTvP2P/AssetMgr/AssetInfo.h>

#include <CoreLib/VxDebug.h>
#include <CoreLib/VxFileUtil.h>
#include <CoreLib/VxGlobals.h>

#include <QMessageBox>
#include <QUuid>
#include <QFileDialog>
#include <QResizeEvent>

//============================================================================
ThumbnailViewWidget::ThumbnailViewWidget( QWidget * parent )
    : QLabel( parent )
    , m_MyApp( GetAppInstance() )
{
    setFixedSize( GuiParams::getThumbnailSize() );
}

//============================================================================
void ThumbnailViewWidget::mousePressEvent( QMouseEvent * event )
{
    QWidget::mousePressEvent( event );
    emit clicked();
    emit signalImageClicked( this );
}

//============================================================================
bool ThumbnailViewWidget::loadFromAsset( AssetInfo * asset )
{
    if( asset && ( asset->isPhotoAsset() || asset->isThumbAsset() ) )
    {
        setThumbnailId( asset->getAssetUniqueId() );
        return loadFromFile( asset->getAssetName().c_str() );
    }

    return false;
}

//============================================================================
bool ThumbnailViewWidget::loadFromFile( QString fileName )
{
    QPixmap pixmap;
    bool result = pixmap.load( fileName );
    if( result )
    {
        cropAndUpdateImage( pixmap );
    }

    return result;
}

//============================================================================
void ThumbnailViewWidget::slotJpgSnapshot( uint8_t* pu8JpgData, uint32_t u32DataLen, int iWidth, int iHeight )
{
    QPixmap bitmap;
    if( bitmap.loadFromData( pu8JpgData, u32DataLen, "JPG" ) )
    {
        cropAndUpdateImage( bitmap );
        setIsUserPickedImage( true );
    }
    else
    {
        QString msgText = QObject::tr( "Failed to read snapshot " );
        QMessageBox::warning( this, QObject::tr( "Error Reading snapshot" ), msgText );
    }
}

//============================================================================
void ThumbnailViewWidget::cropAndUpdateImage( QPixmap& pixmap )
{
    QSize thumbSize = GuiParams::getThumbnailSize();
    QSize origSize = pixmap.size();

    if( thumbSize == origSize )
    {
        // no need to scale or crop image
        setPixmap( pixmap );
    }
    else if( !pixmap.isNull() )
    {
        int minSize = origSize.width() < origSize.height() ? origSize.width() : origSize.height();
        int leftMargin = ( origSize.width() - minSize ) / 2;
        int topMargin = ( origSize.height() - minSize ) / 2;
        QRect rect( leftMargin, topMargin, origSize.width() - leftMargin, origSize.height() - topMargin );
        QPixmap cropped = pixmap.copy( rect );
        QPixmap scaledPixmap = cropped.scaled( GuiParams::getThumbnailSize() );
        if( !scaledPixmap.isNull() )
        {
            setPixmap( scaledPixmap );
        }
        else
        {
            QString msgText = QObject::tr( "Failed to scale and crop image " );
            QMessageBox::warning( this, QObject::tr( "Error scaling image." ), msgText );
        }
    }
    else
    {
        QString msgText = QObject::tr( "Null image " );
        QMessageBox::warning( this, QObject::tr( "Null image." ), msgText );
    }
}

//============================================================================
void ThumbnailViewWidget::browseForImage( void )
{
    QString startPath = QDir::current().path();
    std::string lastGalleryPath;
    m_MyApp.getAppSettings().getLastGalleryDir( lastGalleryPath );
    if( ( 0 != lastGalleryPath.length() )
        && ( VxFileUtil::directoryExists( lastGalleryPath.c_str() ) ) )
    {
        startPath = lastGalleryPath.c_str();
    }

    // Get a filename from the file dialog.
    QString filename = QFileDialog::getOpenFileName( this,
                                                     QObject::tr( "Open Image" ),
                                                     startPath,
                                                     SUPPORTED_IMAGE_FILES );
    if( filename.length() > 0 )
    {
        QPixmap oBitmap;
        if( false == oBitmap.load( filename ) )
        {
            QString msgText = QObject::tr( "Failed To Read Image File " ) + filename;
            QMessageBox::critical( this, QObject::tr( "Error Reading Image" ), msgText );
        }
        else
        {
            std::string justFileName;
            VxFileUtil::seperatePathAndFile( filename.toUtf8().constData(), lastGalleryPath, justFileName );
            if( ( 0 != lastGalleryPath.length() )
                && ( VxFileUtil::directoryExists( lastGalleryPath.c_str() ) ) )
            {
                m_MyApp.getAppSettings().setLastGalleryDir( lastGalleryPath );
            }

            cropAndUpdateImage( oBitmap );
            setIsUserPickedImage( true );
        }
    }
}

//============================================================================
bool ThumbnailViewWidget::saveToPngFile( QString pngFileName )
{
    bool isOk = false;
    const QPixmap * bitmap = pixmap();
    if( bitmap )
    {
        isOk = bitmap->save( pngFileName, "PNG" );
        if( !isOk )
        {
            QString msgText = QObject::tr( "Failed to write into " ) + pngFileName;
            QMessageBox::warning( this, QObject::tr( "Error Writing" ), msgText );
        }
    }
    else
    {
        QString msgText = QObject::tr( "Failed to save to file " ) + pngFileName;
        QMessageBox::warning( this, QObject::tr( "Error Writing" ), msgText );
    }

    return isOk;
}
