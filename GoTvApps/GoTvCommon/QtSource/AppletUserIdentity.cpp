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

#include "AppletUserIdentity.h"
#include "AppCommon.h"
#include "AppSettings.h"
#include "MyIcons.h"
#include "ActivitySnapShot.h"
#include "AppGlobals.h"
#include "AppCommon.h"
#include "VxDataHelper.h"
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
AppletUserIdentity::AppletUserIdentity( AppCommon& app, QWidget * parent )
: AppletBase( OBJNAME_APPLET_USER_IDENTITY, app, parent )
, m_bUserPickedImage( false )
, m_bUsingDefaultImage( true )
{
    setAppletType( eAppletUserIdentity );
    ui.setupUi( getContentItemsFrame() );
	setTitleBarText( DescribeApplet( m_EAppletType ) );
    ui.m_PermissionWidget->setPluginType( ePluginTypeAboutMePage, 0 );
    GuiHelpers::fillGender( ui.m_GenderComboBox );
    GuiHelpers::fillLanguage( ui.m_LanguageComboBox );
    GuiHelpers::fillContentRating( ui.m_ContentComboBox );

    m_MyIdent = m_MyApp.getAppGlobals().getUserIdent();
    m_strOrigOnlineName = m_MyIdent->getOnlineName();
    m_strOrigMoodMessage = m_MyIdent->getOnlineDescription();

    GuiHelpers::setValuesFromIdentity( this, m_MyIdent, ui.m_AgeEdit, ui.m_GenderComboBox, ui.m_LanguageComboBox, ui.m_ContentComboBox );


    m_strUserSepecificDataDir = VxGetUserSpecificDataDirectory();
    m_strDefaultPicPath = m_strUserSepecificDataDir + "profile/";
    VxFileUtil::makeDirectory( m_strDefaultPicPath.c_str() );
    m_strDefaultPicPath += "me.jpg";
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
        if( false == oBitmap.load( ":/AppRes/Resources/me.png" ) )
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

    connect( ui.m_ApplyNameButton, SIGNAL( clicked() ), this, SLOT( onApplyNameClick() ) );
    connect( ui.m_ApplyMoodButton, SIGNAL( clicked() ), this, SLOT( onApplyMoodMsgClick() ) );
    connect( ui.m_ApplyAgeButton, SIGNAL( clicked() ), this, SLOT( onApplyAgeClick() ) );
    connect( ui.m_ApplyGenderButton, SIGNAL( clicked() ), this, SLOT( onApplyGenderClick() ) );

    connect( ui.m_BrowsePictureButton, SIGNAL( clicked() ), this, SLOT( onBrowseButClick() ) );
    connect( ui.m_TakeSnapshotButton, SIGNAL( clicked() ), this, SLOT( onSnapshotButClick() ) );
    connect( ui.m_ApplyAboutMeButton, SIGNAL( clicked() ), this, SLOT( onApplyAboutMeButClick() ) );

    loadIdentityFromDb();
    loadContentFromDb();

	m_MyApp.activityStateChange( this, true );
}

//============================================================================
void AppletUserIdentity::loadIdentityFromDb()
{
    QString strOnlineName = m_MyIdent->getOnlineName();
    ui.m_OnlineNameEdit->setText( strOnlineName );

    QString strMoodMessage = m_MyIdent->getOnlineDescription();
    ui.m_MoodMessageEdit->setText( strMoodMessage );
}

//============================================================================
//! apply name change
void AppletUserIdentity::onApplyNameClick( void )
{
    if( false == validateUserName() )
    {
        return;
    }

    QString onlineName = ui.m_OnlineNameEdit->text();

    if( onlineName != m_strOrigOnlineName )
    {
        std::string strOnlineName = onlineName.toUtf8().constData();
        // TODO apply name change to user specific data directory

        m_MyIdent->setOnlineName( strOnlineName.c_str() );
        m_MyApp.getDataHelper().updateAccount( *m_MyIdent );
        m_Engine.fromGuiOnlineNameChanged( strOnlineName.c_str() );
        QString msgText = QObject::tr( "Applied Online Name Change " );
        QMessageBox::information( this, QObject::tr( "Online Name Change Success" ), msgText );
    }
}

//============================================================================
//! apply mood message change
void AppletUserIdentity::onApplyMoodMsgClick( void )
{
    if( false == validateMoodMessage() )
    {
        return;
    }

    QString moodMsg = ui.m_MoodMessageEdit->text();

    if( moodMsg != m_strOrigMoodMessage )
    {
        std::string strOnlineDesc = moodMsg.toUtf8().constData();
        m_MyIdent->setOnlineDescription( strOnlineDesc.c_str() );
        m_MyApp.getDataHelper().updateAccount( *m_MyIdent );
        m_Engine.fromGuiMoodMessageChanged( strOnlineDesc.c_str() );
        QString msgText = QObject::tr( "Applied Mood Message Change " );
        QMessageBox::information( this, QObject::tr( "Mood Message Change Success" ), msgText );
    }
}

//============================================================================
void AppletUserIdentity::onApplyAgeClick( void )
{
    if( GuiHelpers::validateAge( this, ui.m_AgeEdit->text().toInt() ) )
    {
        m_MyIdent = m_MyApp.getAppGlobals().getUserIdent();
        GuiHelpers::setIdentityFromValues( this, m_MyIdent, ui.m_AgeEdit, ui.m_GenderComboBox, ui.m_LanguageComboBox, ui.m_ContentComboBox );

        m_MyApp.getDataHelper().updateAccount( *m_MyIdent );
        m_Engine.fromGuiIdentPersonalInfoChanged( m_MyIdent->getAge(), m_MyIdent->getGender(), m_MyIdent->getPrimaryLanguage(), m_MyIdent->getPreferredContent() );

        QString msgText = QObject::tr( "Applied Age and Preferred Content Change " );
        QMessageBox::information( this, QObject::tr( "Age and Preferred Content Success" ), msgText );
    }
}
//============================================================================
void AppletUserIdentity::onApplyContentClick( void )
{
    if( GuiHelpers::validateAge( this, ui.m_AgeEdit->text().toInt() ) )
    {
        m_MyIdent = m_MyApp.getAppGlobals().getUserIdent();
        GuiHelpers::setIdentityFromValues( this, m_MyIdent, ui.m_AgeEdit, ui.m_GenderComboBox, ui.m_LanguageComboBox, ui.m_ContentComboBox );

        m_MyApp.getDataHelper().updateAccount( *m_MyIdent );
        m_Engine.fromGuiIdentPersonalInfoChanged( m_MyIdent->getAge(), m_MyIdent->getGender(), m_MyIdent->getPrimaryLanguage(), m_MyIdent->getPreferredContent() );

        QString msgText = QObject::tr( "Applied Mood Message Change " );
        QMessageBox::information( this, QObject::tr( "Mood Message Change Success" ), msgText );
    }
}

//============================================================================
//! browse for picture of me
void AppletUserIdentity::onBrowseButClick( void )
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
void AppletUserIdentity::onSnapshotButClick( void )
{
    ActivitySnapShot oDlg( m_MyApp, this );
    connect( &oDlg, SIGNAL( signalJpgSnapshot( uint8_t*, uint32_t, int, int ) ), this, SLOT( onSnapshot( uint8_t*, uint32_t, int, int ) ) );
    oDlg.exec();
}

//============================================================================
//! Implement the OnClickListener callback    
void AppletUserIdentity::onApplyAboutMeButClick( void )
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
            picPath += "me.jpg";

            bool isOk = bitmap->save( picPath, "JPG" );
            if( !isOk )
            {
                QString msgText = QObject::tr( "Failed to write into " ) + picPath;
                QMessageBox::critical( this, QObject::tr( "Error Writing" ), msgText );
            }
            if( true != m_MyApp.getAppGlobals().getUserIdent()->hasProfilePicture() )
            {
                m_MyApp.getAppGlobals().getUserIdent()->setHasProfilePicture( true );
                m_MyApp.getDataHelper().updateAccount( *m_MyApp.getAppGlobals().getUserIdent() );
                m_Engine.setHasPicture( true );
            }
        }
        else
        {
            LogMsg( LOG_ERROR, "Failed to save picture of me\n" );
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
void AppletUserIdentity::onSnapshot( uint8_t* pu8JpgData, uint32_t u32DataLen, int iWidth, int iHeight )
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
void AppletUserIdentity::updateSnapShot( QPixmap& pixmap )
{
    QPixmap scaledPixmap = pixmap.scaled( QSize( 320, 200 ) );
    ui.m_PictureOfMeFrame->setPixmap( scaledPixmap );
    m_bUserPickedImage = true;
}

//============================================================================
//! validate user input
QString AppletUserIdentity::validateString( QString charSeq )
{
    //return charSeq.toString();    	
    return charSeq;
}

//============================================================================
//! load user profile data from database
void AppletUserIdentity::loadContentFromDb( void )
{
    m_MyApp.getDataHelper().getUserProfile( *m_MyApp.getAppGlobals().getUserIdent(), m_UserProfile );
    ui.m_AboutMeEdit->setPlainText( m_UserProfile.m_strAboutMe );
    ui.m_GreetingEdit->setText( m_UserProfile.m_strGreeting );
    ui.m_FavoriteWebsite1Edit->setText( m_UserProfile.m_strUrl1 );
    ui.m_FavoriteWebsite2Edit->setText( m_UserProfile.m_strUrl2 );
    ui.m_FavoriteWebsite3Edit->setText( m_UserProfile.m_strUrl3 );
    ui.m_DonationEdit->setPlainText( m_UserProfile.m_strDonation );
}

//============================================================================
//! save user profile data to database
void AppletUserIdentity::saveContentToDb( void )
{
    m_UserProfile.m_strAboutMe = ui.m_AboutMeEdit->toPlainText();
    m_UserProfile.m_strGreeting = ui.m_GreetingEdit->text();
    m_UserProfile.m_strUrl1 = ui.m_FavoriteWebsite1Edit->text();
    m_UserProfile.m_strUrl2 = ui.m_FavoriteWebsite2Edit->text();
    m_UserProfile.m_strUrl3 = ui.m_FavoriteWebsite3Edit->text();
    m_UserProfile.m_strDonation = ui.m_DonationEdit->toPlainText();
    m_MyApp.getDataHelper().updateUserProfile( *m_MyApp.getAppGlobals().getUserIdent(), m_UserProfile );
}

//============================================================================
bool AppletUserIdentity::validateUserName( void )
{
    QString strUserName = ui.m_OnlineNameEdit->text();
    return GuiHelpers::validateUserName( this, strUserName );
}

//============================================================================
bool AppletUserIdentity::validateMoodMessage( void )
{
    QString strMoodMsg = ui.m_MoodMessageEdit->text();
    return GuiHelpers::validateMoodMessage( this, strMoodMsg );
}
