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

#include "AppletStoryboard.h"
#include "AppCommon.h"
#include "AppSettings.h"
#include "MyIcons.h"

#include <CoreLib/VxDebug.h>

//============================================================================
AppletStoryboard::AppletStoryboard( AppCommon& app, QWidget * parent )
: AppletBase( OBJNAME_APPLET_STORYBOARD, app, parent )
{
	m_EAppletType = eAppletStoryboard;
	setTitleBarText( DescribeApplet( m_EAppletType ) );
	connect( this, SIGNAL(signalBackButtonClicked()), this, SLOT(close()) );

	m_MyApp.activityStateChange( this, true );
}

//============================================================================
AppletStoryboard::~AppletStoryboard()
{
    m_MyApp.activityStateChange( this, false );
}
