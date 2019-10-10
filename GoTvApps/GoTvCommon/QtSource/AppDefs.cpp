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

#include "AppDefs.h"
#include <QObject>

//============================================================================
// returns feature name ( never translated )
const char * DescribeAppFeature( EAppFeatures appFeature )
{
	// do NOT translate
	switch( appFeature )
	{
	case eAppFeatureViewer:
		return "FeatureViewer";
	case eAppFeatureProvider:
		return "FeatureProvider";
	case eAppFeatureStation:
		return "FeatureStation";
	case eAppFeatureNetworkHost:
		return "FeatureNetworkHost";

	case eAppFeatureUnknown:
	default:
		return "FeatureUnknown";
	}
}

//============================================================================
EMyIcons GetAppletIcon( EApplet applet )
{
	switch( applet )
	{
    case eAppletAboutGoTvPtoP:			return eMyIconApp;
    case eAppletCreateAccount:			return eMyIconUserIdentity;
    case eAppletGroupUser:              return eMyIconGroupUser;
    case eAppletGroupHost:              return eMyIconGroupHost;
    case eAppletGroupAnchor:            return eMyIconGroupListingHost;
    case eAppletGoTvPtoPNetworkHost:    return eMyIconNetHosting;
    case eAppletHomePage:				return eMyIconHome;
    case eAppletKodi:				    return eMyIconKodi;
    case eAppletLibrary:				return eMyIconLibraryNormal;
    case eAppletMessenger:				return eMyIconMessenger;
    case eAppletNetHostingPage:         return eMyIconNetHosting;
    case eAppletNetworkSettings:	    return eMyIconNetworkSettings;
    case eAppletPlayerVideo:			return eMyIconVideoPhoneNormal;
    case eAppletPersonalRecorder:		return eMyIconNotepadNormal;
    case eAppletSettings:				return eMyIconSettings;
    case eAppletShareServicesPage:      return eMyIconShareServices;
    case eAppletStoryboard:             return eMyIconStoryBoardNormal;
    case eAppletSharedWebCam:           return eMyIconCamStreamProvider;
    case eAppletSharedContent:			return eMyIconSharedContent;

    case eAppletSearchPage:	            return eMyIconSearch;
    case eAppletSearchPersons:	        return eMyIconSearchPerson;
    case eAppletSearchMood:	            return eMyIconSearchHeart;
    case eAppletScanAboutMe:	        return eMyIconSearchImage;
    case eAppletScanStoryboard:	        return eMyIconSearchStoryboard;
    case eAppletScanSharedFiles:	    return eMyIconSearchFolder;
    case eAppletScanWebCam:	            return eMyIconSearchWebCam;

    case eAppletRandomPerson:	        return eMyIconSearchRandomPerson;
    case eAppletTheme:					return eMyIconTheme;

	case ePluginAppletCamProvider:		return eMyIconCamStreamProvider;
	case ePluginAppletGoTvStation:		return eMyIconGoTvStation;
	case ePluginAppletGoTvNetworkHost:	return eMyIconGoTvNetworkHost;
    case eAppletUserIdentity:			return eMyIconUserIdentity;

        //	case eAppletPlayerMusic:			return eMyIconMusic;
        //	case eAppletPlayerPhoto:			return eMyIconGallery;
        //	case eAppletStreamViewerVideo:		return eMyIconVideoStreamViewer;
        //	case eAppletStreamViewerCam:		return eMyIconCamStreamViewer;
        //	case eAppletStreamViewerMusic:		return eMyIconMusicStreamPlayer;
            //case eAppletRemoteControl:			return eMyIconRemoteControl;
            //case eAppletPlugins:				return eMyIconPlugins;

	case eAppletUnknown:
	default:
		return eMyIconUnknown;
	}
}

//============================================================================
QString DescribeApplet( EApplet applet )
{
	switch( applet )
	{
	case eAppletHomePage:				return QObject::tr( "Home" );
    case eAppletAboutGoTvPtoP:		    return QObject::tr( "About GoTv Person to Person" );
    case eAppletCreateAccount:			return QObject::tr( "Create Account" );
    case eAppletKodi:				    return QObject::tr( "Kodi (TM)" );
    case eAppletUserIdentity:			return QObject::tr( "User Identity" );
	case eAppletMessenger:				return QObject::tr( "Messenger" );
	case eAppletPlayerVideo:			return QObject::tr( "Video Player" );
    case eAppletPersonalRecorder:		return QObject::tr( "Personal Notes And Records" );
    case eAppletLibrary:				return QObject::tr( "My Library Of Media" );

	case eAppletTheme:					return QObject::tr( "Theme" );
    case eAppletNetworkSettings:		return QObject::tr( "Network Settings" );

    case eAppletSettings:				return QObject::tr( "Settings" );

    case eAppletSearchPage:				return QObject::tr( "Search" );
    case eAppletSearchPersons:			return QObject::tr( "Search Group For Person Name" );
    case eAppletSearchMood:			    return QObject::tr( "Search Group For Mood Message" );
    case eAppletScanAboutMe:			return QObject::tr( "Search Group For About Me Pictures" );
    case eAppletScanStoryboard:			return QObject::tr( "Search Group For Story Boards" );
    case eAppletScanSharedFiles:		return QObject::tr( "Search Group For Shared Files" );
    case eAppletScanWebCam:				return QObject::tr( "Search Group For Shared Web Cams" );
    case eAppletRandomPerson:		    return QObject::tr( "Connect With Random Person" );

    case eAppletGroupUser:              return QObject::tr( "Join Group" );
    case eAppletNetHostingPage:         return QObject::tr( "Group And Network Hosting" );
    case eAppletGroupHost:              return QObject::tr( "Host A Group" );
    case eAppletGroupAnchor:            return QObject::tr( "Host List Of Groups" );
    case eAppletGoTvPtoPNetworkHost:    return QObject::tr( "Host A GoTvPtoP Network" );

    case eAppletShareServicesPage:      return QObject::tr( "Share with others sevices" );
    case eAppletStoryboard:             return QObject::tr( "Share story (Blog)" );
    case eAppletSharedWebCam:           return QObject::tr( "Share your web cam" );
    case eAppletSharedContent:			return QObject::tr( "Share Media Files" );

	case ePluginAppletCamProvider:		return QObject::tr( "Provide Cam Stream" );
	case ePluginAppletGoTvStation:		return QObject::tr( "Manage Station" );
	case ePluginAppletGoTvNetworkHost:	return QObject::tr( "Manage Network Host" );

        //case eAppletPlayerMusic:			return QObject::tr( "Music Player" );
//case eAppletPlayerPhoto:			return QObject::tr( "Image Gallery" );
//case eAppletStreamViewerVideo:		return QObject::tr( "Video Streams" );
//	case eAppletStreamViewerCam:		return QObject::tr( "Search Cam Streams" );
    //case eAppletStreamViewerMusic:		return QObject::tr( "Music Streams" );
    //case eAppletRemoteControl:			return QObject::tr( "Remote Control" );
     //case eAppletNetworkKey:				return QObject::tr( "Network Key" );

	case eMaxBasicApplets:
	case eAppletUnknown:
	default:
		return QObject::tr( "Unknown" );
	}
}
