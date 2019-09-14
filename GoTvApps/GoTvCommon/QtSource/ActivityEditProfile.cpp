//============================================================================
// Copyright (C) 2010 Brett R. Jones
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
// http://www.gotvptop.com
//============================================================================

#include "AppSettings.h"

#include "ActivityEditProfile.h"
#include "ActivitySnapShot.h"
#include "AppGlobals.h"
#include "AppCommon.h"
#include "VxDataHelper.h"

#include <QMessageBox>
#include <QUuid>
#include <QFileDialog>

#include <GoTvCore/GoTvP2P/P2PEngine/EngineSettings.h>
#include <CoreLib/VxFileUtil.h>

#define SUPPORTED_IMAGE_FILES "Image files (*.bmp *.gif *.jpg *.jpeg *.png *.pbm *.pgm *.ppm *.xbm *.xpm)"

#ifdef _MSC_VER
# pragma warning(disable: 4003) //not enough actual parameters for macro 'mkdir'
#endif

//============================================================================
ActivityEditProfile::ActivityEditProfile( AppCommon& app, const char * pUserSpecificDataDir, QWidget * parent )
: ActivityBase( OBJNAME_ACTIVITY_EDIT_PROFILE, app, parent, eAppletMessenger, true )
, m_bUserPickedImage( false)
, m_bUsingDefaultImage(true)
, m_strUserSepecificDataDir(pUserSpecificDataDir)
{
    ui.setupUi( this );
    connectBarWidgets();

    setTitleBarText( QObject::tr( "Edit My Profile" ) );

	VxFileUtil::makeDirectory( m_strUserSepecificDataDir.c_str() );
	m_strDefaultPicPath = m_strUserSepecificDataDir + "profile/";
	VxFileUtil::makeDirectory( m_strDefaultPicPath.c_str() );
	m_strDefaultPicPath += "me.jpg";
	uint32_t u32FileLen = VxFileUtil::getFileLen(m_strDefaultPicPath.c_str());
	if( u32FileLen > 0 )
	{
		QString filename = m_strDefaultPicPath.c_str();
		QPixmap oBitmap;
		if( false == oBitmap.load(filename) )
		{
			QString msgText = tr("Failed To Read Image File ") + filename;
			QMessageBox::critical( this, tr("Error Reading Image"), msgText );
		}
		else
		{
			ui.pictureOfMeFrame->setPixmap( oBitmap );
		}
	}
	else
	{
		QPixmap oBitmap;
		if( false == oBitmap.load(":/AppRes/Resources/me.png") )
		{

			QString msgText = tr("Failed To Read Image File ");
			QMessageBox::critical( this, tr("Error Reading Image"), msgText );
		}
		else
		{
			ui.pictureOfMeFrame->setPixmap( oBitmap );
		}

		m_bUsingDefaultImage = true;
	}

	connect( ui.browsePictureButton, SIGNAL(clicked()), this, SLOT(onBrowseButClick()));
	connect( ui.takeSnapshotButton, SIGNAL(clicked()), this, SLOT(onSnapshotButClick()));
	connect( ui.m_DoneButton, SIGNAL(clicked()), this, SLOT(onDoneButClick()));

	loadContentFromDb();
}

//============================================================================
//! browse for picture of me
void ActivityEditProfile::onBrowseButClick( void )
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
	QString filename = QFileDialog::getOpenFileName(	this,
														tr("Open Image"),
														startPath,
														SUPPORTED_IMAGE_FILES);
	if( filename.length() > 0 )
	{
		QPixmap oBitmap;
		if( false == oBitmap.load(filename) )
		{
			QString msgText = tr("Failed To Read Image File ") + filename;
			QMessageBox::critical( this, tr("Error Reading Image"), msgText );
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
void ActivityEditProfile::onSnapshotButClick( void ) 
{
	ActivitySnapShot oDlg( m_MyApp, this );
	connect( &oDlg, SIGNAL(signalJpgSnapshot(uint8_t*,uint32_t,int,int)), this, SLOT(onSnapshot(uint8_t*,uint32_t,int,int)) );
	oDlg.exec();
}

//============================================================================
//! Implement the OnClickListener callback    
void ActivityEditProfile::onDoneButClick( void ) 
{ 
	VxFileUtil::makeDirectory( m_strUserSepecificDataDir.c_str() );
	std::string strUserProfileDir = m_strUserSepecificDataDir + "profile/";
	VxFileUtil::makeDirectory( strUserProfileDir.c_str() );

	saveContentToDb();

	if( m_bUserPickedImage || m_bUsingDefaultImage )
	{
		// save image to web page
		const QPixmap * bitmap = ui.pictureOfMeFrame->pixmap();
		if( bitmap )
		{
			QString picPath = strUserProfileDir.c_str();
			picPath += "me.jpg";
		
			bool isOk = bitmap->save( picPath, "JPG" );
			if(!isOk)
			{                            
				QString msgText = tr("Failed to write into ") + picPath;
				QMessageBox::critical(this, tr("Error Writing"), msgText);
			}
			if( true != m_MyApp.getAppGlobals().getUserIdent()->hasProfilePicture() )
			{
				m_MyApp.getAppGlobals().getUserIdent()->setHasProfilePicture(true);
				m_MyApp.getDataHelper().updateAccount( *m_MyApp.getAppGlobals().getUserIdent() );
				m_Engine.setHasPicture(true);
			}
		}
		else
		{
			LogMsg( LOG_ERROR, "Failed to save picture of me\n");
		}
	}

	m_Engine.fromGuiUpdateWebPageProfile(	strUserProfileDir.c_str(),
												m_UserProfile.m_strGreeting.toLatin1(),
												m_UserProfile.m_strAboutMe.toLatin1(),
												m_UserProfile.m_strUrl1.toLatin1(),
												m_UserProfile.m_strUrl2.toLatin1(),
												m_UserProfile.m_strUrl3.toLatin1() );
	accept();
}

//============================================================================
//! slot called when user takes snapshot
void ActivityEditProfile::onSnapshot(uint8_t* pu8JpgData, uint32_t u32DataLen, int iWidth, int iHeight )
{
	QPixmap bitmap;
	if( bitmap.loadFromData( pu8JpgData, u32DataLen, "JPG" ) )
	{
		updateSnapShot( bitmap );
	}
	else
	{
		QString msgText = tr("Failed to read snapshot ");
		QMessageBox::critical(this, tr("Error Reading snapshot"), msgText);
	}
}

//============================================================================
void ActivityEditProfile::updateSnapShot( QPixmap& pixmap )
{
	QPixmap scaledPixmap = pixmap.scaled( QSize(320, 200));
	ui.pictureOfMeFrame->setPixmap( scaledPixmap );
	m_bUserPickedImage = true;
}

//============================================================================
//! validate user input
QString ActivityEditProfile::validateString(QString charSeq )
{
	//return charSeq.toString();    	
	return charSeq;
}

//============================================================================
//! load user profile data from database
void ActivityEditProfile::loadContentFromDb( void )
{
	m_MyApp.getDataHelper().getUserProfile( *m_MyApp.getAppGlobals().getUserIdent(), m_UserProfile );
	ui.aboutMeEdit->setPlainText( m_UserProfile.m_strAboutMe );
	ui.greetingEdit->setText( m_UserProfile.m_strGreeting );
	ui.favoriteWebsite1Edit->setText( m_UserProfile.m_strUrl1 );
	ui.favoriteWebsite2Edit->setText( m_UserProfile.m_strUrl2 );
	ui.favoriteWebsite3Edit->setText( m_UserProfile.m_strUrl3 );
}

//============================================================================
//! save user profile data to database
void ActivityEditProfile::saveContentToDb( void )
{
	m_UserProfile.m_strAboutMe = ui.aboutMeEdit->toPlainText();
	m_UserProfile.m_strGreeting = ui.greetingEdit->text();
	m_UserProfile.m_strUrl1 = ui.favoriteWebsite1Edit->text();
	m_UserProfile.m_strUrl2 = ui.favoriteWebsite2Edit->text();
	m_UserProfile.m_strUrl3 = ui.favoriteWebsite3Edit->text();
	m_MyApp.getDataHelper().updateUserProfile( *m_MyApp.getAppGlobals().getUserIdent(), m_UserProfile );
}

