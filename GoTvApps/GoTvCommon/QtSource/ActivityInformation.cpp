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

#include "ActivityInformation.h"
#include "AppCommon.h"
#include "AppSettings.h"

#include <CoreLib/VxDebug.h>

namespace
{
	const int MAX_LOG_EDIT_BLOCK_CNT = 1000;
}

//============================================================================
ActivityInformation::ActivityInformation( AppCommon& app, QWidget * parent, EPluginType pluginType )
: ActivityBase( OBJNAME_ACTIVITY_INFORMATION, app, parent, eAppletActivityDialog )
, m_PluginType( pluginType )
{
    initActivityInformation();
}

//============================================================================
void ActivityInformation::initActivityInformation( void )
{
    ui.setupUi( this );
    ui.m_TitleBarWidget->setTitleBarText( QObject::tr( "Information " ) );
    ui.m_TitleBarWidget->setHomeButtonVisibility( false );

    connectBarWidgets();
}

//============================================================================
void ActivityInformation::showEvent( QShowEvent * ev )
{
    ActivityBase::showEvent( ev );
    updateInformation();
}

//============================================================================
void ActivityInformation::slotCopyToClipboardButtonClicked( void )
{
    // TODO implement me
}

//============================================================================
void ActivityInformation::updateInformation( void )
{
    if( m_PluginType == ePluginTypeInvalid )
    {
        return;
    }

    ui.m_ServiceInfoButton->setIcon( m_MyApp.getMyIcons().getPluginIcon( m_PluginType ) );

    switch( m_PluginType )
    {
    case ePluginTypeGroupUser:
    case ePluginTypeGroupHost:
    case ePluginTypeGroupAnchor:
    case ePluginTypeNetworkHost:
        ui.m_PictureLabel->setResourceImage( ":/AppRes/Resources/NetworkDesign.png", true );
        ui.m_PictureLabel->setVisible( true );
        break;
    default:
        ui.m_PictureLabel->setVisible( false );
        break;
    }
   
    ui.m_InfoText->clear();
    ui.m_InfoText->appendPlainText( getInfoText() );
}

QString ActivityInformation::m_NoInfoAvailable( QObject::tr( "No Information is local available. please visit http://wwww.gotvptop.com for latest infomation and help" ) );

QString ActivityInformation::m_NetworkDesign( QObject::tr(
"NOTE1: For anyone hosting services I suggest using good anti-virus/anti-malware and a service like PeerBlock to avoid bandwidth useage by those who make money spying on others.\n"
"NOTE2: For anyone not hosting a GoTvPtoP Network a VPN is also suggested ( A VPN is not recommended when hosting a GoTvPtoP Network because of the requirement of a fixed ip address )\n"
"\n"
"=== TIER 1: GOTVPTOP NETWORK SERVICE* ===\n"
"NOTE3: This service requires a fixed IP Address or a DNS url like http://www.gotvptop.net.\n"
"REQUIRED SERVICES* AND SUGGESTED PERMISSION LEVELS*\n"
" CONNECTION TEST SERVICE - ANONYMOUSE\n"
" GOTVPTOP NETWORK SERVICE - ANONYMOUSE\n"
"\n"
"SUGGESTED OPTIONAL SERVICES* AND SUGGESTED PERMISSION LEVELS*\n"
" PHONE SHAKE SERVICE - ANONYMOUSE\n"
" ABOUT PAGE SERVICE - GUEST\n"
" SEARCH AND SCAN SERVICES - GUEST\n"
" STORY BOARD PAGE SERVICE - GUEST\n"
"\n"
"OTHER OPTIONAL SERVICES* AND SUGGESTED PERMISSION LEVELS*\n"
" RELAY SERVICE - FRIEND\n"
"\n"
"\n"
"=== TIER 2: GROUP HOST LISTING HOST SERVICE* ===\n"
"REQUIRED SERVICES* AND SUGGESTED PERMISSION LEVELS*\n"
" GROUP HOST LISTING SERVICE - ANONYMOUSE\n"
"\n"
"SUGGESTED OPTIONAL SERVICES* AND SUGGESTED PERMISSION LEVELS*\n"
" CONNECTION TEST SERVICE - ANONYMOUSE\n"
" PHONE SHAKE SERVICE - ANONYMOUSE\n"
" PROFILE PAGE SERVICE - GUEST\n"
" SEARCH AND SCAN SERVICES - GUEST\n"
" STORY BOARD PAGE SERVICE - GUEST\n"
"\n"
"OTHER OPTIONAL SERVICES* AND SUGGESTED PERMISSION LEVELS*\n"
" RELAY SERVICE - FRIEND\n"
"\n"
"=== TIER 3: GROUP HOST SERVICE* ===\n"
" MEMEBERSHIP LEVEL means the permission level required to join the group - can be anonymous but suggest at least guest level\n"
" Members of a group will be automatically given guest permission level between users. Higher level permissions can be granted by individual users to another user.\n"
"REQUIRED SERVICES* AND SUGGESTED PERMISSION LEVELS*\n"
" GROUP HOST SERVICE - MEMEBERSHIP LEVEL\n"
" RELAY SERVICE - MEMEBERSHIP LEVEL\n"
"\n"
"SUGGESTED OPTIONAL SERVICES* AND SUGGESTED PERMISSION LEVELS*\n"
" CONNECTION TEST SERVICE - ANONYMOUSE\n"
" GROUP CHAT SERVICE - MEMEBERSHIP LEVEL\n"
" PHONE SHAKE SERVICE - ANONYMOUSE\n"
" ABOUT PAGE SERVICE - MEMEBERSHIP LEVEL\n"
" SEARCH AND SCAN SERVICES - MEMEBERSHIP LEVEL\n"
" STORY BOARD PAGE SERVICE - MEMEBERSHIP LEVEL\n"
"\n"
"OTHER OPTIONAL SERVICES* AND SUGGESTED PERMISSION LEVELS*\n"
"\n"
"\n"
"=== TIER 4: USERS ===\n"
" USERS should set their permission levels of services and/or streams to be as public or private as desired by user.\n"
"\n"
"DEFINITIONS:\n"
" *ABOUT PAGE SERVICE - Provide a information page about a host or person\n"
" *CAM STREAM SERVICE: A host or user can provide streaming video live from their device camera or cam\n"
" *CONNECTION TEST SERVICE: Service for devices to discover thier web IP Address and if they can have a open port for direct connection or require RELAY SERVICE*.\n"
" *FILE SHARE PLUGIN: Provides user or host file sharing with other users.\n"
" *FILE TRANSFER PLUGIN: Provides user file transfer to another person.\n"
" *GOTVPTOP NETWORK SERVICE: Provides Connection test and list of group host listing hosts for search for groups to join.\n"
" *GROUP CHAT PLUGIN: Provides group based text chat service.\n"
" *GROUP HOST LISTING SERVICE: Provides List of Group Hosts and thier address for users to connect to and search or join.\n"
" *GROUP HOST SERVICE: Provides connection and other services to members who have joined the Group Host.\n"
" *PERMISSION LEVELS: Friendship level required to be allowed to use a service or connect to a person.\n"
" *PHONE CALL PLUGIN: Provides user with voice phone calling to others using the GoTvPtoP app and internet.\n"
" *PHONE SHAKE SERVICE: Provides list of current persons using phone shake mode to discover and connect to others.\n"
" *RELAY SERVICE: Provides data transfer services for persons without a open port to accept incomming connections.\n"
" *SEARCH AND SCAN SERVICES: provide user a list of known persons with the desired search critera or service or stream or files\n"
" *STORY BOARD PAGE SERVICE - Provide a blog like page a host or person can post to for others to view/read\n"
" *TRUTH OR DARE PLUGIN: provides truth or dare video chat game between individuals\n"
" *VIDEO CHAT PLUGIN: Provides user video chat to others using the GoTvPtoP app and internet.\n"
) );

//============================================================================
QString& ActivityInformation::getInfoText( void )
{
    switch( m_PluginType )
    {
    case ePluginTypeGroupUser:
    case ePluginTypeGroupHost:
    case ePluginTypeGroupAnchor:
    case ePluginTypeNetworkHost:
        return m_NetworkDesign;
        break;
    default:
        return m_NoInfoAvailable;
        break;
    }

    return m_NoInfoAvailable;
}
