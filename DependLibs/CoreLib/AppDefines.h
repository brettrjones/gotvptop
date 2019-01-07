#pragma once
//============================================================================
// Created by Brett R. Jones in 2018 and issued to public domain
//============================================================================

enum ERootDir
{
    // root directories that all others are sub directories of
    eRootAppBinHome,        // where executable is located then up 2 directories

    eRootAppHome = 0,
    eRootAppMasterProfile,
    eRootAppProfile,
    eRootAppTemp,
    eRootAppXfer,

    eRootUserHome, 
    eRootUserMasterProfile,
    eRootUserProfile, 
    eRootUserTemp,               // root directory for temporary files
    eRootUserXfer,            // where read only assets are located
    
    eMaxRootDir // last
};

// directory structure on disk
// /storage/MyP2PWeb/appdata/ShredFilesDb.db3 and app generated files
//                  /appassets/gui/ gui assets
//                         /shaders/ opengl shaders
//                         /profile/ profile default files
// user specific directories
//                  /accounts/userId/settings/ databases
//                  /accounts/userId/profile/ profile and story board user web pages
// user xfer directories         
//                  /userxfer/userId/downloads
//                                 /uploads
//                                 /incomplete
//                                 /me/			personal recordings
//                                 /contacts/	contact assets
// user group directories
//                 /usergroup/userId/join	    groups user joined or wants to join
//                                  /grouphost  group hosted by user
//                                  /listhost   group listing hosted by user

/*
CopyUserDataIfNeeded( "special://masterprofile/", "RssFeeds.xml" );
CopyUserDataIfNeeded( "special://masterprofile/", "favourites.xml" );
CopyUserDataIfNeeded( "special://masterprofile/", "Lircmap.xml" );

special://xbmc/          => [read-only] system directory (/usr/share/kodi)
special://home/          => [read-write] user's directory that will override special://kodi/ system-wide
installations like skins, screensavers, etc.
( $HOME / .kodi )
NOTE : XBMC will look in both special ://xbmc/addons and special://home/addons for addons.
special://masterprofile/ => [read-write] userdata of master profile. It will by default be
mapped to special ://home/userdata ($HOME/.kodi/userdata)
special://profile/       => [read-write] current profile's userdata directory.
Generally special ://masterprofile for the master profile or
special://masterprofile/profiles/<profile_name> for other profiles.

NOTE: All these root directories are lowercase.Some of the sub - directories
    might be mixed case.

*/

/*
Debug Print : special://xbmc/ is mapped to: I:\KodiBuildsVS
Debug Print : special://xbmcbin/ is mapped to: I:\KodiBuildsVS
Debug Print : special://xbmcbinaddons/ is mapped to: I:\KodiBuildsVS/addons
Debug Print : special://masterprofile/ is mapped to: C:\Users\me\AppData\Roaming\Kodi\userdata
Debug Print : special://home/ is mapped to: C:\Users\me\AppData\Roaming\Kodi\
Debug Print: special://temp/ is mapped to: C:\Users\me\AppData\Roaming\Kodi\cache
Debug Print : special://logpath/ is mapped to: C:\Users\me\AppData\Roaming\Kodi\
Debug Print: The executable running is: I:\KodiBuildsVS\Debug\kodi.exe
*/

enum EDirMap
{
    eDirXbmc = 0,       // special://xbmc/ is mapped to: I:\KodiBuildsVS
    eDirXbmcBin,        //  special://xbmcbin/ is mapped to: I:\KodiBuildsVS
    eDirXbmcBinAddons,  // special://xbmcbinaddons/ is mapped to: I:\KodiBuildsVS/addons
    eDirMasterProfile,  // special://masterprofile/ is mapped to: C:\Users\me\AppData\Roaming\Kodi\userdata
    eDirHome,           // special://home/ is mapped to: C:\Users\me\AppData\Roaming\Kodi
    eDirTemp,           // special://temp/ is mapped to: C:\Users\me\AppData\Roaming\Kodi\cache
    eDirLog,            // special://logpath/ is mapped to: C:\Users\me\AppData\Roaming\Kodi
}

if( RootDir == "subtitles" )
translatedPath = URIUtils::AddFileToFolder( CServiceBroker::GetSettings().GetString( CSettings::SETTING_SUBTITLES_CUSTOMPATH ), FileName );
else if( RootDir == "userdata" && m_profileManager )
translatedPath = URIUtils::AddFileToFolder( m_profileManager->GetUserDataFolder(), FileName );
else if( RootDir == "database" && m_profileManager )
translatedPath = URIUtils::AddFileToFolder( m_profileManager->GetDatabaseFolder(), FileName );
else if( RootDir == "thumbnails" && m_profileManager )
translatedPath = URIUtils::AddFileToFolder( m_profileManager->GetThumbnailsFolder(), FileName );
else if( RootDir == "recordings" || RootDir == "cdrips" )
translatedPath = URIUtils::AddFileToFolder( CServiceBroker::GetSettings().GetString( CSettings::SETTING_AUDIOCDS_RECORDINGPATH ), FileName );
else if( RootDir == "screenshots" )
translatedPath = URIUtils::AddFileToFolder( CServiceBroker::GetSettings().GetString( CSettings::SETTING_DEBUG_SCREENSHOTPATH ), FileName );
else if( RootDir == "musicplaylists" )
translatedPath = URIUtils::AddFileToFolder( CUtil::MusicPlaylistsLocation(), FileName );
else if( RootDir == "videoplaylists" )
translatedPath = URIUtils::AddFileToFolder( CUtil::VideoPlaylistsLocation(), FileName );
else if( RootDir == "skin" )
translatedPath = URIUtils::AddFileToFolder( CServiceBroker::GetWinSystem()->GetGfxContext().GetMediaDir(), FileName );

// from here on, we have our "real" special paths
else if( RootDir == "xbmc" ||
         RootDir == "xbmcbin" ||
         RootDir == "xbmcbinaddons" ||
         RootDir == "xbmcaltbinaddons" ||
         RootDir == "home" ||
         RootDir == "envhome" ||
         RootDir == "userhome" ||
         RootDir == "temp" ||
         RootDir == "profile" ||
         RootDir == "masterprofile" ||
         RootDir == "frameworks" ||
         RootDir == "logpath" )
{