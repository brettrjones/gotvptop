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

#include "AppletServiceBase.h"
#include "AppCommon.h"
#include "AppSettings.h"
#include "MyIcons.h"
#include "GuiHelpers.h"

#include <CoreLib/VxDebug.h>

//============================================================================
AppletServiceBase::AppletServiceBase( const char * objName, AppCommon& app, QWidget * parent )
    : AppletBase( objName, app, parent )
{
}

//============================================================================
void AppletServiceBase::setAppletType( EApplet applet )
{
    AppletBase::setAppletType( applet );
    setupServiceApplet();
}

//============================================================================
void AppletServiceBase::setupServiceApplet()
{
    ui.setupUi( getContentItemsFrame() );
    setTitleBarText( DescribeApplet( m_EAppletType ) );

    getServiceUrlLabel()->setVisible( false );
    getServiceUrlEdit()->setVisible( false );
    getStartButton()->setVisible( false );
    getStopButton()->setVisible( false );
    getInformationWidget()->setVisible( false );

    EPluginType pluginType = GuiHelpers::getAppletAssociatedPlugin( m_EAppletType );
    if( ePluginTypeInvalid != pluginType )
    {
        getPermissionWidget()->setPluginType( pluginType );
        getServiceTitle()->setText( GuiHelpers::describePlugin( pluginType, false ).c_str() );
    }

    connectServiceWidgets();
}

//============================================================================
void AppletServiceBase::connectServiceWidgets()
{
}

//============================================================================
void AppletServiceBase::loadServiceFromSettings()
{
}

//============================================================================
void AppletServiceBase::saveServiceToSettings()
{
}
