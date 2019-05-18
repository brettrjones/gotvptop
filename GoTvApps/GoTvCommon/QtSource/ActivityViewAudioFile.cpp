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
// http://www.gotvptop.net
//============================================================================

#include "AppCommon.h"
#include "ActivityViewAudioFile.h"
#include "AppGlobals.h"

#include <CoreLib/VxGlobals.h>

#include <QMessageBox>

//============================================================================
ActivityViewAudioFile::ActivityViewAudioFile(	AppCommon&			app,
												QWidget *				parent )
: ActivityBase( OBJNAME_ACTIVITY_VIEW_AUDIO_FILE, app, parent, eAppletMessenger, Qt::SubWindow )
, m_HisIdent( &app.getEngine().getMyPktAnnounce() )
, m_bIsMyself( true )
{
	ui.setupUi( this );
	slotRepositionToParent();

	//ui.m_AudioWidget->setAudioFeedId( m_HisIdent->getMyOnlineId() );

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
ActivityViewAudioFile::~ActivityViewAudioFile()
{
}

//============================================================================
void ActivityViewAudioFile::onStopButClick( void )
{
	close();
}

//============================================================================
void ActivityViewAudioFile::onLibraryButtonClick( void )
{
}

//============================================================================
void ActivityViewAudioFile::onShareButtonClick( void )
{
}

//============================================================================
void ActivityViewAudioFile::playAudioFrame( VxGUID& feedId, unsigned char * pu8Jpg, unsigned long u32JpgLen, int motion0To100000 )
{
	//ui.m_AudioWidget->playAudioFrame( feedId, pu8Jpg, u32JpgLen, motion0To100000 );
}

//============================================================================
void ActivityViewAudioFile::webCamSourceOffline()
{
}
