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

#include "AppletServiceBaseSettings.h"
#include "AppCommon.h"
#include "AppSettings.h"
#include "MyIcons.h"
#include "GuiHelpers.h"


#include <CoreLib/VxDebug.h>

//============================================================================
AppletServiceBaseSettings::AppletServiceBaseSettings( const char * objName, AppCommon& app, QWidget * parent )
    : AppletBase( objName, app, parent )
{
    setAppletType( eAppletServiceSettings );
    ui.setupUi( this );
    setTitleBarText( DescribeApplet( m_EAppletType ) );
}

////============================================================================
//void AppletServiceBaseSettings::setAppletType( EApplet applet )
//{
//    AppletBase::setAppletType( applet );
//    setupServiceApplet();
//}

//============================================================================
void AppletServiceBaseSettings::setPluginType( EPluginType pluginType )
{
    m_PluginType = pluginType;
    //AppletBase::setAppletType( applet );
    setupServiceApplet();
}

//============================================================================
void AppletServiceBaseSettings::setupServiceApplet()
{
    ui.setupUi( getContentItemsFrame() );
    setTitleBarText( DescribeApplet( m_EAppletType ) );

    getServiceUrlLabel()->setVisible( false );
    getServiceUrlEdit()->setVisible( false );
    getStartButton()->setVisible( false );
    getStopButton()->setVisible( false );
    getInformationWidget()->setVisible( false );

    //EPluginType pluginType = GuiHelpers::getAppletAssociatedPlugin( m_EAppletType );
    if( ePluginTypeInvalid != m_PluginType )
    {
        getPermissionWidget()->setPluginType( m_PluginType );
        getServiceTitle()->setText( GuiHelpers::describePlugin( m_PluginType, false ).c_str() );
    }

    connectServiceWidgets();
}

//============================================================================
void AppletServiceBaseSettings::connectServiceWidgets()
{
}

//============================================================================
void AppletServiceBaseSettings::loadServiceFromSettings()
{
}

//============================================================================
void AppletServiceBaseSettings::saveServiceToSettings()
{
}
