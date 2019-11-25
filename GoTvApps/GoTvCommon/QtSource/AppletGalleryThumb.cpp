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

#include "AppCommon.h"	
#include "AppSettings.h"

#include "AppletGalleryThumb.h"

#include "FileShareItemWidget.h"
#include "MyIcons.h"
#include "ListEntryWidget.h"
#include "PopupMenu.h"
#include "AppGlobals.h"
#include "FileItemInfo.h"
#include "FileActionMenu.h"
#include "GuiHelpers.h"

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>
#include <GoTvCore/GoTvP2P/AssetMgr/AssetMgr.h>

#include <PktLib/VxSearchDefs.h>
#include <NetLib/VxFileXferInfo.h>
#include <CoreLib/VxFileInfo.h>

#include <QResizeEvent>

//============================================================================
AppletGalleryThumb::AppletGalleryThumb(	AppCommon& app, QWidget * parent )
: AppletBase( OBJNAME_APPLET_GALLERY_THUMB, app, parent )
, m_AssetMgr( app.getEngine().getAssetMgr() )
{
    setAppletType( eAppletGalleryThumb );
    ui.setupUi( getContentItemsFrame() );
    setTitleBarText( DescribeApplet( m_EAppletType ) );

    loadAssets();

    connect( ui.m_ImageListWidget, SIGNAL( signalImageClicked( ThumbnailViewWidget * ) ), this, SLOT( slotImageClicked( ThumbnailViewWidget * ) ) );

    m_MyApp.activityStateChange( this, true );
}

//============================================================================
void AppletGalleryThumb::resizeEvent( QResizeEvent * ev )
{
    AppletBase::resizeEvent( ev );
    LogMsg( LOG_DEBUG, "AppletGalleryThumb Resize w %d h %d\n", ev->size().width(), ev->size().height() );
}

//============================================================================
void AppletGalleryThumb::loadAssets( void )
{
    std::vector<AssetInfo*>& assetList = m_AssetMgr.getAssetInfoList();
    for( AssetInfo* assetInfo : assetList )
    {
        if( eAssetTypeThumbnail == assetInfo->getAssetType() )
        {
            ui.m_ImageListWidget->addAsset( assetInfo );
        }
    }
}

//============================================================================
void AppletGalleryThumb::slotImageClicked( ThumbnailViewWidget * imageEntry )
{

}