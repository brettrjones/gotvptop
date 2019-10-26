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
// http://www.gotvptop.com
//============================================================================

#include "AppletServiceConnectionTest.h"
#include "AppCommon.h"
#include "AppSettings.h"
#include "MyIcons.h"

#include <CoreLib/VxDebug.h>

//============================================================================
AppletServiceConnectionTest::AppletServiceConnectionTest( AppCommon& app, QWidget * parent )
: AppletServiceBase( OBJNAME_APPLET_SERVICE_CONNECT_TEST, app, parent )
{
	setAppletType( eAppletServiceConnectionTest );
	setTitleBarText( DescribeApplet( m_EAppletType ) );

	m_MyApp.activityStateChange( this, true );
}

//============================================================================
AppletServiceConnectionTest::~AppletServiceConnectionTest()
{
    m_MyApp.activityStateChange( this, false );
}