#pragma once
//============================================================================
// Copyright (C) 2017 Brett R. Jones
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

#include "MyIconsDefs.h"

#include <QString>

enum EDefaultAppMode
{
	eAppModeUnknown,
	eAppModeDefault,
	eAppModeGoTvViewer,
	eAppModeGoTvProvider,
	eAppModeGoTvStation,
	eAppModeGoTvNetworkHost,

	eMaxAppModeGoTv
};

enum EAppFeatures
{
	eAppFeatureUnknown,
	eAppFeatureViewer,
	eAppFeatureProvider,
	eAppFeatureStation,
	eAppFeatureNetworkHost,

	eMaxAppFeatures
};

enum EHomeLayout
{
	eHomeLayoutPlayerPlusMessenger,	// player with messenger on side or bottom
	eHomeLayoutPlayerOnly,			// player/home page only
	eHomeLayoutMessengerOnly,		// messenger only

	eMaxHomeLayouts // must be last
};

enum EApplet
{
	eAppletUnknown = 0, // do not setup base class ui in the case of unknown
    eAppletActivityDialog,          // place dialog over home window.. do not setup base class ui in the case of dialog
    eAppletEditAboutMe,
    eAppletEditAvatarImage,
	eAppletHomePage,
    eAppletKodi,
    eAppletUserIdentity,
    eAppletMessenger,
    eAppletPersonalRecorder,
    eAppletLibrary,
    eAppletGroupUser,	
    eAppletSearchPage,
    eAppletShareServicesPage,   // page to setup share with others services

    eAppletSettings,
    eAppletNetworkSettings,
    eAppletNetHostingPage,	    // page to setup network/group hosts and services
    eAppletTheme,
    eAppletAboutGoTvPtoP,

	eMaxBasicApplets,           // marker.. past here is search applets

    eAppletSearchPersons,           // search for person in group by name
    eAppletSearchMood,              // search for mood message
    eAppletScanAboutMe,             // scan group for pictures in about me page
    eAppletScanStoryboard,          // scan group for pictures in about me page
    eAppletScanSharedFiles,         // searc group for shared files
    eAppletScanWebCam,              // scan group for shared web cams

    eAppletClientRandomConnect,      // connect to random person

    eMaxSearchApplets,          // marker.. past here is hosting applets

    eAppletServiceHostGroup,	    // hosts a group. provide search and relay services for group users
    eAppletServiceHostGroupListing, // group listing host service for group hosts. provide search for groups to join, provide ip address etc
    eAppletServiceHostNetwork,      // network host service for a gotvptop network.. requires fixed ip address, group list hosts announce to network host
    eAppletServiceConnectionTest,   // network test service for users to test if they have a open port
    eAppletServiceRelay,            // network relay service for users without a open port

    eAppletServiceRandomConnect,     // connect to random person service
    eAppletServiceRandomConnectRelay,   // connect to random person relay service for users without a open port

    eMaxHostApplets,            // marker.. past here is service applets for user share services

    eAppletServiceAvatarImage,
    eAppletServiceAboutMe,
    eAppletServiceStoryboard,
    eAppletServiceShareWebCam,
    eAppletServiceShareFiles,

    eMaxSharedServicesApplets,  // marker.. past here is applets not launched by user page icon

    // not launched from launch page icon
    eAppletPlayerVideo,

    eAppletClientAvatarImage,	    // get users avatar imaage from other user
    eAppletClientAboutMe,	        // users about me page
    eAppletClientGroupHost,	        // hosts a group. provide search and relay services for group users
    eAppletClientGroupListingHost,  // group listing host service for group hosts. provide search for groups to join, provide ip address etc
    eAppletClientNetworkHost,       // network host service for a gotvptop network.. requires fixed ip address, group list hosts announce to network host
    eAppletClientConnectionTest,    // network test service for users to test if they have a open port
    eAppletClientRelay,             // network relay service for users without a open port

    eAppletClientRandomConnectRelay, // connect to random person relay service for users without a open port
    eAppletClientShareFiles,
    eAppletClientShareWebCam,
    eAppletClientStoryboard,

    eAppletServiceSettings,

    eAppletSettingsAboutMe,
    eAppletSettingsAvatarImage,
    eAppletSettingsWebCamServer,
    eAppletSettingsConnectTest,
    eAppletSettingsShareFiles,
    eAppletSettingsFileXfer,
    eAppletSettingsHostGroup,
    eAppletSettingsHostGroupListing,
    eAppletSettingsHostNetwork,
    eAppletSettingsMessenger,
    eAppletSettingsRandomConnect,
    eAppletSettingsRandomConnectRelay,
    eAppletSettingsRelay,
    eAppletSettingsStoryboard,
    eAppletSettingsTruthOrDare,
    eAppletSettingsVideoPhone,
    eAppletSettingsVoicePhone,

	ePluginAppletCamProvider,
	ePluginAppletGoTvStation,
	ePluginAppletGoTvNetworkHost,

    // not lauched by user
    eAppletCreateAccount,

    //	eAppletPlayerMusic,
    //	eAppletPlayerPhoto,
    //	eAppletStreamViewerVideo,
    //	eAppletStreamViewerCam,
    //	eAppletStreamViewerMusic,
    //  eAppletRemoteControl,
        //eAppletPlugins,

	eMaxApplets // must be last
};

enum EThemeType
{
	eThemeTypeUnknown = 0,
	eThemeTypeLight = 1,
	eThemeTypeDark = 2,
	eThemeTypeBlueOnWhite = 3,
	eThemeTypeGreenOnWhite = 4,

	eMaxThemeType
};

// returns feature name ( never translated )
const char *					DescribeAppFeature( EAppFeatures appFeature );

// returns applet icon
EMyIcons						GetAppletIcon( EApplet applet );

// returns text to go under applet icon ( is translated )
QString							DescribeApplet( EApplet applet );
