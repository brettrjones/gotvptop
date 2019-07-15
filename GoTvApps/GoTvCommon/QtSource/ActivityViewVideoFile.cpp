//============================================================================
// Copyright (C) 2013 Brett R. Jones
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

#include "AppCommon.h"
#include "ActivityViewVideoFile.h"
#include "AppGlobals.h"

#include <CoreLib/VxGlobals.h>

#include <QMessageBox>

//============================================================================
ActivityViewVideoFile::ActivityViewVideoFile(	AppCommon&			app,
												QWidget *			parent )
: ActivityBase( OBJNAME_ACTIVITY_VIEW_VIDEO_FILE, app, parent, eAppletMessenger, Qt::SubWindow )
, m_HisIdent( &app.getEngine().getMyPktAnnounce() )
{
	ui.setupUi( this );
	slotRepositionToParent();

	//ui.m_VideoWidget->setVideoFeedId( m_HisIdent->getMyOnlineId() );

	//ui.m_FileNameLabel;
	//ui.m_StatusMsgLabel;
	//ui.m_FileSizeLabel;

	//ui.m_LibraryButton->setIcon( eMyIconLibraryNormal, eMyIconLibraryPressed, eMyIconLibraryDisabled );
	//ui.m_ShareButton->setIcons( eMyIconRefreshNormal, eMyIconRefreshPressed, eMyIconRefreshDisabled );

	connect( this, SIGNAL(finished(int)), this, SLOT(onStopButClick()));
	connect( ui.m_LibraryButton, SIGNAL(clicked()), this, SLOT(onLibraryButtonClick()));
	connect( ui.m_ShareButton, SIGNAL(clicked()), this, SLOT(onShareButtonClick()));
}

//============================================================================
ActivityViewVideoFile::~ActivityViewVideoFile()
{
}

//============================================================================
void ActivityViewVideoFile::onStopButClick( void )
{
	close();
}

//============================================================================
void ActivityViewVideoFile::onLibraryButtonClick( void )
{
}

//============================================================================
void ActivityViewVideoFile::onShareButtonClick( void )
{
}

//============================================================================
void ActivityViewVideoFile::playVideoFrame( VxGUID& feedId, unsigned char * pu8Jpg, unsigned long u32JpgLen, int motion0To100000 )
{
	//ui.m_VideoWidget->playVideoFrame( feedId, pu8Jpg, u32JpgLen, motion0To100000 );
}

//============================================================================
void ActivityViewVideoFile::webCamSourceOffline()
{
}
