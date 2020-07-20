//============================================================================
// Copyright (C) 2020 Brett R. Jones
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

#include "AppletChooseThumbnail.h"
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

//============================================================================
AppletChooseThumbnail::AppletChooseThumbnail( AppCommon& app, QWidget * parent )
: AppletBase( OBJNAME_APPLET_CHOOSE_THUMBNAIL, app, parent )
{
    setAppletType( eAppletChooseThumbnail );
    ui.setupUi( getContentItemsFrame() );
	setTitleBarText( DescribeApplet( m_EAppletType ) );

    connect( ui.m_ThumbnailEditWidget, SIGNAL( signalImageChanged() ), this, SLOT( slotImageChanged() ) );

	m_MyApp.activityStateChange( this, true );
}

//============================================================================
AppletChooseThumbnail::~AppletChooseThumbnail()
{
    m_MyApp.activityStateChange( this, false );
}

//============================================================================
void AppletChooseThumbnail::slotImageChanged( void )
{
    emit signalThumbSelected( this, ui.m_ThumbnailEditWidget );
}
