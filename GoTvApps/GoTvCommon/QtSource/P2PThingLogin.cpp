//============================================================================
// Copyright (C) 2009 Brett R. Jones 
// Issued to MIT style license by Brett R. Jones in 2017
//
// You may use, copy, modify, merge, publish, distribute, sub-license, and/or sell this software 
// provided this Copyright is not modified or removed and is included all copies or substantial portions of the Software
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// brett.jones@engineer.com
// http://www.gotvptop.net
//============================================================================

#include "AppCommon.h"
#include "AppSettings.h"

#include "VxDataHelper.h"
#include "AppGlobals.h"
#include "GuiHelpers.h"

#include <GoTvCore/GoTvP2P/P2PEngine/EngineSettings.h>
#include <CoreLib/VxFileUtil.h>
#include <CoreLib/VxGlobals.h>
#include <CoreLib/VxParse.h>

#include <QUuid>

//============================================================================
static uint64_t getQuuidLoPart( QUuid& uuid )
{
	uint64_t u64LoPart;
	memcpy( &u64LoPart, &uuid, sizeof( uint64_t ) );
	return u64LoPart;
}

//============================================================================
static uint64_t getQuuidHiPart( QUuid& uuid )
{
	uint64_t u64HiPart;
	char * pTmp = (char *)&uuid;
	pTmp += 8;
	memcpy( &u64HiPart, pTmp, sizeof( uint64_t ) );
	return u64HiPart;
}

//============================================================================
void AppCommon::createAccountForUser( std::string& strUserName, VxNetIdent& userAccountIdent, const char * moodMsg )
{
	m_Engine.fromGuiSetUserXferDir( getUserXferDirectoryFromAccountUserName( strUserName.c_str() ).c_str() );
	m_Engine.fromGuiSetUserSpecificDir( getUserSpecificDataDirectoryFromAccountUserName( strUserName.c_str() ).c_str() );
	QUuid uuidTmp = QUuid::createUuid();
	uint64_t u64HiPart =  getQuuidHiPart( uuidTmp );
	uint64_t u64LoPart =  getQuuidLoPart( uuidTmp );
	userAccountIdent.m_DirectConnectId.setVxGUID( u64HiPart, u64LoPart );

	if( getAppSettings().m_strUserGuid.length() )
	{
		userAccountIdent.m_DirectConnectId.setVxGUID( getAppSettings().m_strUserGuid.c_str() );
	}

	SafeStrCopy( userAccountIdent.getOnlineName(), strUserName.c_str(), MAX_ONLINE_NAME_LEN );
	SafeStrCopy( userAccountIdent.getOnlineDescription(), moodMsg, MAX_ONLINE_DESC_LEN );

	userAccountIdent.setPluginPermissionsToDefaultValues();

	// get port to listen on 
	uint16_t tcpPort;
	m_Engine.getEngineSettings().getTcpIpPort( tcpPort );
	userAccountIdent.m_DirectConnectId.setPort( tcpPort );

	// get current default ips
	userAccountIdent.m_DirectConnectId.m_IPv4OnlineIp.setIp( getEngine().fromGuiGetMyIPv4Address().getIPv4AddressInHostOrder(), true );

	userAccountIdent.m_DirectConnectId.m_IPv6OnlineIp = getEngine().fromGuiGetMyIPv6Address();
	std::string myIPv4 = userAccountIdent.m_DirectConnectId.m_IPv4OnlineIp.toStdString();
	std::string myIPv6 = userAccountIdent.m_DirectConnectId.m_IPv6OnlineIp.toStdString();

	LogMsg( LOG_VERBOSE, "Account %s IPv4 %s IPv6 %s\n", strUserName.c_str(), myIPv4.c_str(), myIPv6.c_str() );

	std::string storyBoardFileName = VxGetProfileDirectory();
	storyBoardFileName += "story_board.htm";
	if( false == VxFileUtil::fileExists( storyBoardFileName.c_str() ) )
	{
		GuiHelpers::copyResourceToOnDiskFile( ":/AppRes/Resources/story_board.htm", storyBoardFileName.c_str() );
	}

	std::string storyBoardBackground = VxGetProfileDirectory();
	storyBoardBackground += "storyboard_background.png";
	if( false == VxFileUtil::fileExists( storyBoardBackground.c_str() ) )
	{
		GuiHelpers::copyResourceToOnDiskFile( ":/AppRes/Resources/storyboard_background.png", storyBoardBackground.c_str() );
	}
}

//============================================================================
std::string AppCommon::getUserXferDirectoryFromAccountUserName( const char * userName )
{
	std::string strUserDownloadDir = VxGetRootXferDirectory();
	strUserDownloadDir += userName;
	strUserDownloadDir += "/";	
	VxFileUtil::makeDirectory( strUserDownloadDir );
	return strUserDownloadDir;
}

//============================================================================
std::string AppCommon::getUserSpecificDataDirectoryFromAccountUserName( const char * userName )
{
	std::string strUserSpecificDir = VxGetRootDataDirectory();
	strUserSpecificDir += "accounts/";
	VxFileUtil::makeDirectory( strUserSpecificDir );

	strUserSpecificDir += userName;
	strUserSpecificDir += "/";	
	VxFileUtil::makeDirectory( strUserSpecificDir );
	return strUserSpecificDir;
}

//============================================================================
void AppCommon::loadAccountSpecificSettings( const char * userName )
{
	m_Engine.fromGuiSetUserXferDir( getUserXferDirectoryFromAccountUserName( userName ).c_str() );
	std::string strUserSpecificDir = getUserSpecificDataDirectoryFromAccountUserName( userName );
	m_Engine.fromGuiSetUserSpecificDir( strUserSpecificDir.c_str() );
	std::string userPicture = VxGetProfileDirectory();
    userPicture += "me.jpg";
    if( false == VxFileUtil::fileExists( userPicture.c_str() ) )
    {
        GuiHelpers::copyResourceToOnDiskFile( ":/AppRes/Resources/me.jpg", userPicture.c_str() );
    }

    std::string storyBoardFileName = VxGetProfileDirectory();
	storyBoardFileName += "story_board.htm";
	if( false == VxFileUtil::fileExists( storyBoardFileName.c_str() ) )
	{
		GuiHelpers::copyResourceToOnDiskFile( ":/AppRes/Resources/story_board.htm", storyBoardFileName.c_str() );
	}

	std::string storyBoardBackground = VxGetProfileDirectory();
	storyBoardBackground += "storyboard_background.png";
	if( false == VxFileUtil::fileExists( storyBoardBackground.c_str() ) )
	{
		GuiHelpers::copyResourceToOnDiskFile( ":/AppRes/Resources/storyboard_background.png", storyBoardBackground.c_str() );
	}

	std::string favIcon = VxGetProfileDirectory();
	favIcon += "favicon.ico";
	if( false == VxFileUtil::fileExists( favIcon.c_str() ) )
	{
		GuiHelpers::copyResourceToOnDiskFile( ":/AppRes/Resources/favicon.ico", favIcon.c_str() );
	}

	m_CamSourceId			= m_AppSettings.getCamSourceId();
	m_CamCaptureRotation	= m_AppSettings.getCamRotation( m_CamSourceId );

	// get port to listen on 
	uint16_t tcpPort;
	m_Engine.getEngineSettings().getTcpIpPort( tcpPort );
	getAppGlobals().getUserIdent()->m_DirectConnectId.setPort( tcpPort );
	getAppGlobals().getUserIdent()->m_DirectConnectId.m_IPv6OnlineIp = m_Engine.getFromGuiInterface().fromGuiGetMyIPv6Address();
}

//============================================================================
void AppCommon::sendAppSettingsToEngine( void )
{
	if( m_AppSettings.m_u32EnableDebug )
	{
		m_Engine.fromGuiDebugSettings(
			m_AppSettings.m_u32LogFlags,
			m_AppSettings.m_strDebugFileName.c_str() );
	}
}

//============================================================================
void AppCommon::slotListViewTypeChanged( int viewSelectedIdx )
{
	m_eLastSelectedWhichContactsToView = (EFriendViewType)viewSelectedIdx;

	EMyIcons whichIcon = eMyIconUnknown;
	QString statMsg = "Unknown List View";

	switch( m_eLastSelectedWhichContactsToView )
	{
	case eFriendViewEverybody: //Everybody
		whichIcon = eMyIconGuest;
		statMsg = QObject::tr( "List View Everybody Except Ignored" );
		break;
	case eFriendViewAdministrators: 
		whichIcon = eMyIconAdministrator;
		statMsg = QObject::tr( "List View Administrators" );
		break;
	case eFriendViewFriendsAndGuests: //Friends And Guests
		whichIcon = eMyIconFriend;
		statMsg = QObject::tr( "List View Friends And Guests" );
		break;
	case eFriendViewAnonymous: //Anonymous
		whichIcon = eMyIconAnonymous;
		statMsg = QObject::tr( "List View Anonymous" );
		break;
	case eFriendViewIgnored: //Ignored
		whichIcon = eMyIconIgnored;
		statMsg = QObject::tr( "List View People I Ignore" );
		break;
	case eFriendViewMyProxies: // my proxies
		whichIcon = eMyIconRelay;
		statMsg = QObject::tr( "List View My Preferred Relays" );
		break;
	case eFriendViewAllProxies: // all proxies
		whichIcon = eMyIconRelay;
		statMsg = QObject::tr( "List View All Possible Relays" );
		break;
	//case eFriendViewRefresh: // Refresh all
	//	break;
	//default:
	//	LogMsg( LOG_ERROR, "onMenuPeopleSelected: ERROR unknown menu id %d\n", iMenuId );
    default:
        break;
	}

	//ui.m_ListViewTypeButton->setIcon(  getMyIcons().getIcon( whichIcon ) );
	toGuiStatusMessage( statMsg.toUtf8().constData() );
	//ui.mainFriendList->refreshFriendList( m_eLastSelectedWhichContactsToView );
}

//============================================================================
void AppCommon::showUserNameInTitle()
{
	QString strTitle = VxGetApplicationName();
	strTitle += "-";
	strTitle += getAccountUserName().c_str();
	setWindowTitle( strTitle );
}

//============================================================================
void AppCommon::checkForIniSettings( VxNetIdent * netIdent, std::string& strNetworkName )
{
	if( m_AppSettings.m_u16TcpPort )
	{
		m_Engine.getEngineSettings().setTcpIpPort( m_AppSettings.m_u16TcpPort );
		netIdent->m_DirectConnectId.setPort( m_AppSettings.m_u16TcpPort );
	}

	if( 0 != m_AppSettings.m_strUserName.length() )
	{
		netIdent->setOnlineName( m_AppSettings.m_strUserName.c_str() );
	}

	if( 0 != m_AppSettings.m_strUserGuid.length() )
	{
		netIdent->m_DirectConnectId.setVxGUID( m_AppSettings.m_strUserGuid.c_str() );
	}

	if( 0 != m_AppSettings.m_strNetworkName.length() )
	{
		strNetworkName = m_AppSettings.m_strNetworkName;
	}
}
