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
// http://www.gotvptop.com
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
#include <CoreLib/VxFileUtil.h>
#include <CoreLib/VxDebug.h>
#include <CoreLib/VxGlobals.h>

#define SUPPORTED_IMAGE_FILES "Image files (*.bmp *.gif *.jpg *.jpeg *.png *.pbm *.pgm *.ppm *.xbm *.xpm)"

//============================================================================
AppletEditAvatarImage::AppletEditAvatarImage( AppCommon& app, QWidget * parent )
: AppletBase( OBJNAME_APPLET_EDIT_AVATAR_IMAGE, app, parent )
, m_bUserPickedImage( false )
, m_bUsingDefaultImage( true )
{
    setAppletType( eAppletEditAvatarImage );
    ui.setupUi( getContentItemsFrame() );
	setTitleBarText( DescribeApplet( m_EAppletType ) );
    ui.m_ServiceSettingsWidget->setPluginType( ePluginTypeAvatarImage );
 
    m_MyIdent = m_MyApp.getAppGlobals().getUserIdent();
    m_strOrigOnlineName = m_MyIdent->getOnlineName();
    m_strOrigMoodMessage = m_MyIdent->getOnlineDescription();

    m_strUserSepecificDataDir = VxGetUserSpecificDataDirectory();
    m_strDefaultPicPath = m_strUserSepecificDataDir + "profile/";
    VxFileUtil::makeDirectory( m_strDefaultPicPath.c_str() );
    m_strDefaultPicPath += "avatar.png";
    uint32_t u32FileLen = VxFileUtil::getFileLen( m_strDefaultPicPath.c_str() );
    if( u32FileLen > 0 )
    {
        QString filename = m_strDefaultPicPath.c_str();
        QPixmap oBitmap;
        if( false == oBitmap.load( filename ) )
        {
            QString msgText = QObject::tr( "Failed To Read Image File " ) + filename;
            QMessageBox::critical( this, QObject::tr( "Error Reading Image" ), msgText );
        }
        else
        {
            ui.m_PictureOfMeFrame->setPixmap( oBitmap );
        }
    }
    else
    {
        QPixmap oBitmap;
        if( false == oBitmap.load( ":/AppRes/Resources/avatar.png" ) )
        {

            QString msgText = QObject::tr( "Failed To Read Image File " );
            QMessageBox::critical( this, QObject::tr( "Error Reading Image" ), msgText );
        }
        else
        {
            ui.m_PictureOfMeFrame->setPixmap( oBitmap );
        }

        m_bUsingDefaultImage = true;
    }

    connect( ui.m_BrowsePictureButton, SIGNAL( clicked() ), this, SLOT( onBrowseButClick() ) );
    connect( ui.m_TakeSnapshotButton, SIGNAL( clicked() ), this, SLOT( onSnapshotButClick() ) );
    connect( ui.m_ApplyAboutMeButton, SIGNAL( clicked() ), this, SLOT( onApplyButClick() ) );

	m_MyApp.activityStateChange( this, true );
}

//============================================================================
//! browse for picture of me
void AppletEditAvatarImage::onBrowseButClick( void )
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

            updateSnapShot( oBitmap );
        }
    }
}

//============================================================================
//! Implement the OnClickListener callback    
void AppletEditAvatarImage::onSnapshotButClick( void )
{
    ActivitySnapShot oDlg( m_MyApp, this );
    connect( &oDlg, SIGNAL( signalJpgSnapshot( uint8_t*, uint32_t, int, int ) ), this, SLOT( onSnapshot( uint8_t*, uint32_t, int, int ) ) );
    oDlg.exec();
}

//============================================================================
//! Implement the OnClickListener callback    
void AppletEditAvatarImage::onApplyButClick( void )
{
    VxFileUtil::makeDirectory( m_strUserSepecificDataDir.c_str() );
    std::string strUserProfileDir = m_strUserSepecificDataDir + "profile/";
    VxFileUtil::makeDirectory( strUserProfileDir.c_str() );

    saveContentToDb();

    if( m_bUserPickedImage || m_bUsingDefaultImage )
    {
        // save image to web page
        const QPixmap * bitmap = ui.m_PictureOfMeFrame->pixmap();
        if( bitmap )
        {
            QString picPath = strUserProfileDir.c_str();
            picPath += "avatar.png";

            bool isOk = bitmap->save( picPath, "PNG" );
            if( !isOk )
            {
                QString msgText = QObject::tr( "Failed to write into " ) + picPath;
                QMessageBox::critical( this, QObject::tr( "Error Writing" ), msgText );
            }
            if( true != m_MyApp.getAppGlobals().getUserIdent()->hasProfilePicture() )
            {
                m_MyApp.getAppGlobals().getUserIdent()->setHasProfilePicture( true );
                m_MyApp.getAccountMgr().updateAccount( *m_MyApp.getAppGlobals().getUserIdent() );
                m_Engine.setHasPicture( true );
            }
        }
        else
        {
            LogMsg( LOG_ERROR, "Failed to save picture of avatar\n" );
        }
    }

    m_Engine.fromGuiUpdateWebPageProfile( strUserProfileDir.c_str(),
                                          m_UserProfile.m_strGreeting.toUtf8(),
                                          m_UserProfile.m_strAboutMe.toUtf8(),
                                          m_UserProfile.m_strUrl1.toUtf8(),
                                          m_UserProfile.m_strUrl2.toUtf8(),
                                          m_UserProfile.m_strUrl3.toUtf8(),
                                          m_UserProfile.m_strDonation.toUtf8() );
    QString msgText = QObject::tr( "Applied About Me Changes " );
    QMessageBox::information( this, QObject::tr( "About Me Change Success" ), msgText );
}

//============================================================================
//! slot called when user takes snapshot
void AppletEditAvatarImage::onSnapshot( uint8_t* pu8JpgData, uint32_t u32DataLen, int iWidth, int iHeight )
{
    QPixmap bitmap;
    if( bitmap.loadFromData( pu8JpgData, u32DataLen, "JPG" ) )
    {
        updateSnapShot( bitmap );
    }
    else
    {
        QString msgText = QObject::tr( "Failed to read snapshot " );
        QMessageBox::critical( this, QObject::tr( "Error Reading snapshot" ), msgText );
    }
}

//============================================================================
void AppletEditAvatarImage::updateSnapShot( QPixmap& pixmap )
{
    QPixmap scaledPixmap = pixmap.scaled( QSize( 320, 200 ) );
    ui.m_PictureOfMeFrame->setPixmap( scaledPixmap );
    m_bUserPickedImage = true;
}

//============================================================================
//! validate user input
QString AppletEditAvatarImage::validateString( QString charSeq )
{
    //return charSeq.toString();    	
    return charSeq;
}

//============================================================================
//! load user profile data from database
void AppletEditAvatarImage::loadContentFromDb( void )
{
    m_MyApp.getAccountMgr().getUserProfile( *m_MyApp.getAppGlobals().getUserIdent(), m_UserProfile );
}

//============================================================================
//! save user profile data to database
void AppletEditAvatarImage::saveContentToDb( void )
{
    m_MyApp.getAccountMgr().updateUserProfile( *m_MyApp.getAppGlobals().getUserIdent(), m_UserProfile );
}
