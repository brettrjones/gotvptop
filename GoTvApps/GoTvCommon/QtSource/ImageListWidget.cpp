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

#include "ImageListEntry.h"
#include "ImageListWidget.h"
#include "ImageListRow.h"

#include "MyIcons.h"
#include "PopupMenu.h"
#include "AppGlobals.h"
#include "AppCommon.h"
#include "GuiParams.h"
#include <CoreLib/VxDebug.h>

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>
#include <GoTvCore/GoTvP2P/AssetMgr/AssetMgr.h>
#include <GoTvCore/GoTvP2P/AssetMgr/AssetInfo.h>

#include <CoreLib/VxDebug.h>

#include <QResizeEvent>

 
//============================================================================
ImageListWidget::ImageListWidget( QWidget * parent )
: QListWidget( parent )
, m_MyApp( GetAppInstance() )
, m_Engine( m_MyApp.getEngine() )
, m_AssetMgr( m_MyApp.getEngine().getAssetMgr() )
{
    connect( this, SIGNAL(itemClicked(QListWidgetItem *)),
                          this, SLOT(slotItemClicked(QListWidgetItem *))) ;

    connect( this, SIGNAL(itemDoubleClicked(QListWidgetItem *)),
                          this, SLOT(slotItemClicked(QListWidgetItem *))) ;
}

//============================================================================
void ImageListWidget::resizeEvent( QResizeEvent * ev )
{
    QListWidget::resizeEvent( ev );
    LogMsg( LOG_DEBUG, "ImageListWidget Resize w %d h %d\n", ev->size().width(), ev->size().height() );
}

//============================================================================
void ImageListWidget::addAsset( AssetInfo * asset )
{
    int curWidth = width();
    if( asset && ( eAssetTypeThumbnail == asset->getAssetType() ) )
    {
        ImageListRow * listRow = getRowWithRoomForThumbnail();
        if( listRow )
        {
            ThumbnailViewWidget * thumbnail = new ThumbnailViewWidget( listRow );
            thumbnail->loadFromAsset( asset );
            connect( thumbnail, SIGNAL( signalImageClicked( ThumbnailViewWidget * ) ), this, SLOT( slotImageClicked( ThumbnailViewWidget * ) ) );
            listRow->addThumbnail( thumbnail );
        }
    }
}

//============================================================================
ImageListRow * ImageListWidget::getRowWithRoomForThumbnail( void )
{
    ImageListRow * listRow;
    int iIdx = 0;
    while( iIdx < this->count() )
    {
        listRow = dynamic_cast< ImageListRow * >( this->item( iIdx ) );
        if( listRow && listRow->hasRoomForThumbnail() )
        {
            return listRow;
        }

        iIdx++;
    }

    listRow = new ImageListRow( this );
    listRow->setSizeHint( QSize( ( int )( m_MyApp.getAppDisplay().getDisplayScale() * 200 ),
        ( int )( GuiParams::getThumbnailSize().height() * m_MyApp.getAppDisplay().getDisplayScale() ) ) );
    addItem( listRow );
    listRow->setRowNum( count() );
    return listRow;
}

//============================================================================
void ImageListWidget::slotItemClicked(QListWidgetItem * item )
{
	if( 300 < m_ClickEventTimer.elapsedMs()  ) // avoid duplicate clicks
	{
		//slotImageListItemClicked( (ImageListEntry *) item );
	}
}

//============================================================================
void ImageListWidget::slotImageClicked( ThumbnailViewWidget * thumb )
{
	if( 300 > m_ClickEventTimer.elapsedMs()  ) // avoid duplicate clicks
	{
		return;
	}

	m_ClickEventTimer.startTimer();
    emit signalImageClicked( thumb );
    /*
	m_SelectedImage = widgetToImage( item );
	if( m_SelectedImage )
	{
		if( m_SelectedImage->isMyAccessAllowedFromHim( ePluginTypeMessenger ) )
		{
			QWidget * parent2 = 0;
			QWidget * parent1 = (QWidget *)this->parent();
			if( parent1 )
			{
				parent2 = (QWidget *)parent1->parent();
			}

			m_MyApp.offerToImagePluginSession( m_SelectedImage, ePluginTypeMessenger, parent2 ? parent2 : parent1 );
			emit signalImageClicked( m_SelectedImage );
		}
		else
		{
			QString warnTitle = QObject::tr("Insufficient Permission Level");
			QString warmPermission = warnTitle + QObject::tr(" To Access Plugin ") + DescribePluginType( ePluginTypeMessenger );
			QMessageBox::warning(this, QObject::tr("Insufficient Permission Level "), warmPermission );
		}
	}*/
}

/*

//============================================================================
void ImageListWidget::slotUpdateImage( VxNetIdent * netIdent, bool sessionTimeChange ) 
{
	LogMsg( LOG_INFO, "ImageListWidget::slotUpdateImage  %d\n", this->count() );
	ImageListEntry * poWidget = findImageListEntry( netIdent );
	if( poWidget )
	{
		LogMsg( LOG_INFO, "ImageListWidget::onImageUpdated %s online ? %d widget exists\n", netIdent->getOnlineName(), netIdent->isOnline() );
		updateImageListEntry( poWidget, netIdent );
	}
	else
	{
		ImageListEntry * poImageItem = friendToWidget( netIdent ); 
		int64_t hisSessionTime = netIdent->getLastSessionTimeMs();
		if( 0 == this->count() )
		{
			insertItem( this->count(), poImageItem );
			LogMsg( LOG_INFO, "ImageListWidget::onImageUpdated %s First Item online ? %d inserted %d time %d\n", netIdent->getOnlineName(), netIdent->isOnline(), this->count() - 1, hisSessionTime );
			//addItem( poImageItem );
		}
		else
		{
			bool wasInserted = false;
			int rowIdx = 0;
			ImageListEntry * listEntryWidget;
			while( rowIdx < this->count() )
			{
				listEntryWidget = (ImageListEntry *)this->item( rowIdx );
				if( listEntryWidget )
				{
					Image * listEntryImage = (Image *)listEntryWidget->data( Qt::UserRole + 2 ).toULongLong();
					if( listEntryImage )
					{
						int64_t listSessionTime = listEntryImage->getLastSessionTimeMs();
						if( listSessionTime < hisSessionTime )
						{
							LogMsg( LOG_INFO, "ImageListWidget::onImageUpdated %s Insert Item online ? %d inserted %d time %d\n", netIdent->getOnlineName(), netIdent->isOnline(), rowIdx, hisSessionTime  );
							insertItem( rowIdx, poImageItem );
							wasInserted = true;
							break;
						}
					}
				}

				rowIdx++;
			}

			if( false == wasInserted )
			{
				//addItem( poImageItem );
				LogMsg( LOG_INFO, "ImageListWidget::onImageUpdated %s Add Item online ? %d inserted %d time %d\n", netIdent->getOnlineName(), netIdent->isOnline(), this->count(), hisSessionTime );
				insertItem( this->count(), poImageItem );
			}
		}

		poImageItem->setSizeHint( poImageItem->getSubWidget()->size() );

		setItemWidget( poImageItem, poImageItem->getSubWidget() );

		updateImageListEntry( poImageItem, netIdent );
	}
}
*/

//============================================================================
//!	fill friend into new QListWidgetItem *
/*
ImageListEntry * ImageListWidget::friendToWidget( VxNetIdent * poImage )
{
	ImageListEntry * item = new ImageListEntry( this );
    item->setData( Qt::UserRole + 1, QVariant((quint64)(item->getSubWidget())) );
    item->setData( Qt::UserRole + 2, QVariant((quint64)(poImage)) );
    connect( item, SIGNAL(listButtonClicked(ImageListEntry*)), this, SLOT(slotImageListItemClicked(ImageListEntry*)));

    connect( item, SIGNAL(signalMenuButtonClicked(ImageListEntry*)), this, SLOT(slotImageMenuButtonClicked(ImageListEntry*)));

	return item;
}*/
/*
//============================================================================
//!	get friend from QListWidgetItem data
Image * ImageListWidget::widgetToImage( ImageListEntry * item )
{
	return (Image *)item->data( Qt::UserRole + 2 ).toULongLong();
}*/
