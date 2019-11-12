//============================================================================
// Copyright (C) 2018 Brett R. Jones
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

#include "AppletEditAvatarImage.h"
#include "AppCommon.h"
#include "AppSettings.h"
#include "MyIcons.h"
#include "ActivitySnapShot.h"
#include "AppGlobals.h"
#include "AppCommon.h"
#include "AccountMgr.h"
#include "GuiHelpers.h"

#include <QMessageBox>
#include <QUuid>
#include <QFileDialog>

#include <GoTvCore/GoTvP2P/P2PEngine/EngineSettings.h>
#include <GoTvCore/GoTvP2P/AssetMgr/AssetMgr.h>

#include <CoreLib/VxFileUtil.h>
#include <CoreLib/VxDebug.h>
#include <CoreLib/VxGlobals.h>

#define SUPPORTED_IMAGE_FILES "Image files (*.bmp *.gif *.jpg *.jpeg *.png *.pbm *.pgm *.ppm *.xbm *.xpm)"

//============================================================================
AppletEditAvatarImage::AppletEditAvatarImage( AppCommon& app, QWidget * parent )
: AppletBase( OBJNAME_APPLET_EDIT_AVATAR_IMAGE, app, parent )
, m_AssetMgr( app.getEngine().getAssetMgr() )
{
    setAppletType( eAppletEditAvatarImage );
    ui.setupUi( getContentItemsFrame() );
	setTitleBarText( DescribeApplet( m_EAppletType ) );
    ui.m_ServiceSettingsWidget->setPluginType( ePluginTypeAvatarImage );
    ui.m_ServiceSettingsWidget->setViewServiceVisible( false );

 
    m_MyIdent = m_MyApp.getAppGlobals().getUserIdent();
    m_strOrigOnlineName = m_MyIdent->getOnlineName();
    m_strOrigMoodMessage = m_MyIdent->getOnlineDescription();
    if( m_MyIdent->getAvatarGuid().isVxGUIDValid() )
    {
        AssetInfo * thumbAsset = m_AssetMgr.findAsset( m_MyIdent->getAvatarGuid() );
        ui.m_ThumbnailEditWidget->loadFromAsset( thumbAsset );
    }

    connect( ui.m_ApplyAboutMeButton, SIGNAL( clicked() ), this, SLOT( onApplyButClick() ) );

	m_MyApp.activityStateChange( this, true );
}

//============================================================================
//! Implement the OnClickListener callback    
void AppletEditAvatarImage::onApplyButClick( void )
{
    if( ui.m_ThumbnailEditWidget->getIsUserPickedImage() )
    {
        VxGUID assetGuid;
        VxGUID::generateNewVxGUID( assetGuid );
        QString fileName = VxGetAppDirectory( eAppDirThumbs ).c_str();
        fileName += assetGuid.toHexString().c_str();
        fileName += ".nlt"; // use extension not known as image so thumbs will not be scanned by android image gallery etc
        if( ui.m_ThumbnailEditWidget->saveToPngFile( fileName ) && VxFileUtil::fileExists( fileName.toUtf8().constData() ) )
        {
            AssetInfo assetInfo( (const char *)fileName.toUtf8().constData(), VxFileUtil::fileExists( fileName.toUtf8().constData() ), (uint16_t)eAssetTypeThumbnail );
            assetInfo.setAssetUniqueId( assetGuid );
            assetInfo.setCreatorId( m_MyIdent->getMyOnlineId() );
            if( m_MyApp.getEngine().getAssetMgr().addAsset( assetInfo ) )
            {
                // delete the old one if exists
                if( m_MyIdent->getAvatarGuid().isVxGUIDValid() )
                {
                    AssetInfo * oldAsset = m_MyApp.getEngine().getAssetMgr().findAsset( m_MyIdent->getAvatarGuid() );
                    if( oldAsset )
                    {
                        VxFileUtil::deleteFile( oldAsset->getAssetName().c_str() );
                        m_MyApp.getEngine().getAssetMgr().removeAsset( m_MyIdent->getAvatarGuid() );
                    }
                }

                // setup identity with new avatar image
                m_MyIdent->setAvatarGuid( assetGuid );
                m_MyApp.updateMyIdent( m_MyIdent );

                QString msgText = QObject::tr( "Applied Avatar Image Changes " );
                QMessageBox::information( this, QObject::tr( "Applied Avatar Image Success" ), msgText );
            }
            else
            {
                QString msgText = QObject::tr( "Could not create thumbnail asset" );
                QMessageBox::information( this, QObject::tr( "Error occured creating thumbnail asset " ) + fileName, msgText );
            }
        }
        else
        {
            QString msgText = QObject::tr( "Could not save avatar image" );
            QMessageBox::information( this, QObject::tr( "Error occured saving avatar to file " ) + fileName, msgText );
        }
    }
    else
    {
        QString msgText = QObject::tr( "No Avatar Changes" );
        QMessageBox::information( this, QObject::tr( "The Avatar Image was not changed" ), msgText );
    }
}
