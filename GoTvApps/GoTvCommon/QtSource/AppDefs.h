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
	eAppletUnknown = 0,
	eAppletHomePage,
    eAppletKodi,
    eAppletUserIdentity,
    eAppletSharedContent,
	eAppletMessenger,
	eAppletPlayerVideo,
	eAppletPlayerMusic,
	eAppletPlayerPhoto,
	eAppletStreamViewerVideo,
	eAppletStreamViewerCam,
	eAppletStreamViewerMusic,
	eAppletRemoteControl,

	eAppletPlugins,
	eAppletTheme,
	eAppletSettings,
	eAppletGroupUser,	// user who can join group
    eAppletNetHostingPage,	// page to setup group or group listing hosts
	eMaxBasicApplets, // marker.. past here is hosting applets

    eAppletGroupHost,	// user who hosts a group
    eAppletGroupAnchor, // network service for group hosts.. search, provide ip address etc
    eAppletGoTvPtoPNetworkHost, // network service for a gotvptop network.. privide fixed ip address, group anchor lists
    eMaxHostApplets, // marker.. past here is optional applets based on feature

	ePluginAppletCamProvider,
	ePluginAppletGoTvStation,
	ePluginAppletGoTvNetworkHost,

    // not lauched by user
    eActivityCreateProfile,

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
