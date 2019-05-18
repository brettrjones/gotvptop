//============================================================================
// Copyright (C) 2014 Brett R. Jones
// Issued to MIT style license by Brett R. Jones in 2017
//
// You may use, copy, modify, merge, publish, distribute, sub-license, and/or sell this software
// provided this Copyright is not modified or removed and is included all copies or substantial portions of the Software
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// bjones.engineer@gmail.com
// http://www.gotvptop.net
//============================================================================

#include "AppSettings.h"

#include <GoTvCore/GoTvP2P/P2PEngine/EngineSettingsDefaultValues.h>

#include <NetLib/VxGetRandomPort.h>
#include <CoreLib/VxParse.h>

#include <QString>

namespace
{
	#define APP_SETTINGS_DBVERSION		1
	#define SELECTED_THEME_TYPE			"SELECTED_THEME_TYPE"
	#define HOME_LAYOUT_TYPE			"HOME_LAYOUT_TYPE"
}

//============================================================================
AppSettings::AppSettings()
: VxSettings( "AppSettingsDb" )
{
	// mark all values as not cached
	memset( m_AppFeatureIsCached, 0, sizeof( m_AppFeatureIsCached ) );
}

//============================================================================
AppSettings::~AppSettings()
{
}

//============================================================================
RCODE AppSettings::appSettingStartup( const char * dbSettingsFile, EDefaultAppMode appDefaultMode )
{
	RCODE rc = dbStartup( APP_SETTINGS_DBVERSION, dbSettingsFile );
	if( ( 0 == rc )
		&& ( false == appModeSettingsAreInitialize() ) )
	{
		setupAppModeSettings( appDefaultMode );
	}

	return rc;
}

//============================================================================
void AppSettings::appSettingShutdown( void )
{
	dbShutdown();
}

//============================================================================
void AppSettings::setIsMessengerFullScreen( bool isFullScreen )
{
	setIniValue( getAppShortName(), "MessangerFullScreen", isFullScreen );
}

//============================================================================
bool AppSettings::getIsMessengerFullScreen( void )
{
	bool fullScreen;
	getIniValue( getAppShortName(), "MessangerFullScreen", fullScreen, false );
	return fullScreen;
}

//============================================================================
void AppSettings::setFeatureEnable( EAppFeatures appFeature, bool enable )
{
	setIniValue( getAppShortName(), DescribeAppFeature( appFeature ), enable );
	m_AppFeatureValue[appFeature] = enable;
	m_AppFeatureIsCached[appFeature] = true;
}

//============================================================================
bool AppSettings::getFeatureEnable( EAppFeatures appFeature )
{
	if( m_AppFeatureIsCached[appFeature] )
	{
		// pull from cache
		return m_AppFeatureValue[ appFeature ];
	}
	
	// get feature from db
	bool featureValue = false;
	getIniValue( getAppShortName(), DescribeAppFeature( appFeature ), featureValue, 0 );
	m_AppFeatureValue[appFeature] = featureValue;
	m_AppFeatureIsCached[appFeature] = true;
	return m_AppFeatureValue[appFeature];
}

//============================================================================
void AppSettings::setLastSelectedTheme( EThemeType selectedTheme )
{
	uint32_t themeType = (uint32_t)selectedTheme;
	setIniValue( getAppShortName(), SELECTED_THEME_TYPE, themeType );
}

//============================================================================
EThemeType AppSettings::getLastSelectedTheme( void )
{
	uint32_t themeType = 1;
	getIniValue( getAppShortName(), SELECTED_THEME_TYPE, themeType, (uint32_t)eThemeTypeDark );
	return (EThemeType)themeType;
}

//============================================================================
void AppSettings::setHomePageLayout( EHomeLayout homeLayout )
{
	uint32_t homeLayoutType = (uint32_t)homeLayout;
	setIniValue( getAppShortName(), HOME_LAYOUT_TYPE, homeLayoutType );
}

//============================================================================
EHomeLayout AppSettings::getHomePageLayout( void )
{
	uint32_t homeLayoutType = 1;
	getIniValue( getAppShortName(), HOME_LAYOUT_TYPE, homeLayoutType, 1 );
	return (EHomeLayout)homeLayoutType;
}

//============================================================================
void AppSettings::setLastBrowseDir( EFileFilterType eFileFilterType, std::string& browseDir )
{
	if( 0 != browseDir.length() )
	{
		QString keyStr = QString("BrowseDir%1").arg( (int)eFileFilterType );
		setIniValue( getAppShortName(), keyStr.toUtf8().constData(), browseDir );
	}
}

//============================================================================
void AppSettings::getLastBrowseDir( EFileFilterType eFileFilterType, std::string& browseDir )
{
	QString keyStr = QString("BrowseDir%1").arg( (int)eFileFilterType );
	getIniValue( getAppShortName(), keyStr.toUtf8().constData(), browseDir, "" );
}

//============================================================================
void AppSettings::setLastGalleryDir( std::string& galleryDir )
{
	setIniValue( getAppShortName(), "GalleryDir", galleryDir );
}

//============================================================================
void AppSettings::getLastGalleryDir( std::string& galleryDir )
{
	getIniValue( getAppShortName(), "GalleryDir", galleryDir, "" );
}

//============================================================================
void AppSettings::setLastBrowseShareDir( std::string& browseDir )
{
	setIniValue( getAppShortName(), "ShareBrowseDir", browseDir );
}

//============================================================================
void AppSettings::getLastBrowseShareDir( std::string& browseDir )
{
	getIniValue( getAppShortName(), "ShareBrowseDir", browseDir, "" );
}

//============================================================================
void AppSettings::setCamRotation( uint32_t camId, uint32_t camRotation )
{
	std::string camKey;
	StdStringFormat( camKey, "CamRotation%d", camId );
	setIniValue( getAppShortName(), camKey.c_str(), camRotation );
}

//============================================================================
uint32_t AppSettings::getCamRotation( uint32_t camId )
{
	uint32_t camRotation = 0;
	std::string camKey;
	StdStringFormat( camKey, "CamRotation%d", camId );
	getIniValue( getAppShortName(), camKey.c_str(), camRotation, 0 );
	return camRotation;
}

//============================================================================
void AppSettings::setCamSourceId( uint32_t camId )
{
	setIniValue( getAppShortName(), "CamSourceId", camId );
}

//============================================================================
uint32_t AppSettings::getCamSourceId( void )
{
	uint32_t camSourceId = 0;
	getIniValue( getAppShortName(), "CamSourceId", camSourceId, 0 );
	return camSourceId;
}

//============================================================================
void AppSettings::setCamShowPreview( bool showPreview )
{
	uint32_t showPreviewVal = showPreview ? 1 : 0;
	setIniValue( getAppShortName(), "CamShowPreview", showPreviewVal );
}

//============================================================================
bool AppSettings::getCamShowPreview( void )
{
	uint32_t showPreview = 0;
	getIniValue( getAppShortName(), "CamShowPreview", showPreview, 0 );
	return showPreview ? true : false;
}

//============================================================================
void AppSettings::setVidFeedRotation( uint32_t feedRotation )
{
	setIniValue( getAppShortName(), "VidFeedRotation", feedRotation );
}

//============================================================================
uint32_t AppSettings::getVidFeedRotation( void )
{
	uint32_t feedRotation = 0;
	getIniValue( getAppShortName(), "VidFeedRotation", feedRotation, 0 );
	return feedRotation;
}

//============================================================================
void AppSettings::setLastAppletLaunched( EApplet applet )
{
     uint32_t appletVal = (EApplet)applet;
    setIniValue( getAppShortName(), "LastAppletLaunched", appletVal );
}

//============================================================================
EApplet AppSettings::getLastAppletLaunched( void )
{
    uint32_t appletVal = 0;
    getIniValue( getAppShortName(), "LastAppletLaunched", appletVal, 0 );
    return (EApplet)appletVal;
}

//============================================================================
bool AppSettings::getMutePhoneRing( void )
{
	bool bMute;
	getIniValue( getAppShortName(), "MutePhoneRing", bMute, false );

	return bMute;
}

//============================================================================
void AppSettings::setMutePhoneRing( bool bMutePhoneRing )
{
	setIniValue( getAppShortName(), "MutePhoneRing", bMutePhoneRing );
}

//============================================================================
bool AppSettings::getMuteNotifySound( void )
{
	bool bMute;
	getIniValue( getAppShortName(), "MuteNotifySound", bMute, false );

	return bMute;
}

//============================================================================
void AppSettings::setMuteNotifySound( bool bNotifySound )
{
	uint32_t u32Value = bNotifySound;
	setIniValue( getAppShortName(), "MuteNotifySound", u32Value );
}

//============================================================================
void AppSettings::setIsConfirmDeleteDisabled( bool confirmIsDisabled )
{
	uint32_t u32Value = confirmIsDisabled;
	setIniValue( getAppShortName(), "ConfirmDeleteDisable", u32Value );
}

//============================================================================
bool AppSettings::getIsConfirmDeleteDisabled( void )
{
	bool confirmIsDisabled;
	getIniValue( getAppShortName(), "ConfirmDeleteDisable", confirmIsDisabled, false );
	return confirmIsDisabled;
}

//============================================================================
bool AppSettings::appModeSettingsAreInitialize( void )
{
	bool confirmIsInitialized = false;
	getIniValue( getAppShortName(), "AppDefaultInited", confirmIsInitialized, false );
	return confirmIsInitialized;
}

//============================================================================
void AppSettings::setupAppModeSettings( EDefaultAppMode appDefaultMode )
{
	// set all features to false
	for( int i = 0; i < eMaxAppFeatures; i++ )
	{
		setFeatureEnable( (EAppFeatures)i, false );
	}

	// enable app mode specific features
	switch( appDefaultMode )
	{
	case eAppFeatureViewer:
		setFeatureEnable( eAppFeatureViewer, true );
		break;
	case eAppFeatureProvider:
		setFeatureEnable( eAppFeatureProvider, true );
		break;
	case eAppFeatureStation:
		setFeatureEnable( eAppFeatureStation, true );
		break;
	case eAppFeatureNetworkHost:
		setFeatureEnable( eAppFeatureNetworkHost, true );
		break;
	}

	// mare database as intialized with app mode settings
	uint32_t u32Value = 1;
	setIniValue( getAppShortName(), "AppDefaultInited", u32Value );
}
