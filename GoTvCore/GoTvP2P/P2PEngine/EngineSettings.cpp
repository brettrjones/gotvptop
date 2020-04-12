//============================================================================
// Copyright (C) 2013 Brett R. Jones
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
// http://www.nolimitconnect.com
//============================================================================
#include "EngineSettings.h"
#include "EngineSettingsDefaultValues.h"
#include <NetLib/VxGetRandomPort.h>

#define MY_SETTINGS_DBVERSION 1
#define MY_SETTINGS_KEY "RCKEY"

//============================================================================
EngineSettings::EngineSettings()
: VxSettings( "EngineSettingsDb" )
, m_Initialized( false )
, m_CachedNetworkName("")
{
}

//============================================================================
EngineSettings::~EngineSettings()
{
	engineSettingsShutdown();
}

//============================================================================
RCODE EngineSettings::engineSettingsStartup( std::string& strDbFileName )
{
	if( m_Initialized )
	{
		engineSettingsShutdown();
	}

	RCODE rc = dbStartup(MY_SETTINGS_DBVERSION, strDbFileName.c_str());
	if( 0 == rc )
	{
		m_Initialized = true;
	}

	return rc;
}

//============================================================================
void EngineSettings::engineSettingsShutdown( void )
{
	if( m_Initialized )
	{
		dbShutdown();
		m_Initialized = false;
	}
}

//============================================================================
void EngineSettings::getNetSettings( NetSettings& netSettings )
{
	std::string strValue;
	getNetworkKey( strValue );
	netSettings.setNetworkKey( strValue.c_str() );
	
	getNetHostWebsiteUrl( strValue );
	netSettings.setNetHostWebsiteUrl( strValue.c_str() );

	getNetServiceWebsiteUrl( strValue );
	netSettings.setNetServiceWebsiteUrl( strValue.c_str() );

	uint16_t u16Port = getTcpIpPort();
	netSettings.setMyTcpInPort( u16Port );

	getMulticastPort( u16Port );
	netSettings.setMyMulticastPort( u16Port );

	uint32_t usrCnt;
	uint32_t sysCnt;
	getMaxRelaysInUse( usrCnt, sysCnt );
	netSettings.setUserRelayPermissionCount( (int)usrCnt );
	netSettings.setSystemRelayPermissionCount( (int)sysCnt );
	netSettings.setAllowMulticastBroadcast( getAllowMulticastBroadcast() );
	netSettings.setAllowUserLocation( getAllowMulticastBroadcast() );
}

//============================================================================
void EngineSettings::setNetSettings( NetSettings& netSettings )
{
	setNetworkKey( netSettings.getNetworkKey() );
	setNetHostWebsiteUrl( netSettings.getNetHostWebsiteUrl() );
	setNetServiceWebsiteUrl( netSettings.getNetServiceWebsiteUrl() );

	setTcpIpPort( netSettings.getMyTcpInPort() );
	setMulticastPort( netSettings.getMyMulticastPort() );
	setMulticastEnable( netSettings.getMulticastEnable() );
	setUseUpnpPortForward( netSettings.getUseUpnpPortForward() );
	
	setMaxRelaysInUse( netSettings.getUserRelayPermissionCount(), netSettings.getSystemRelayPermissionCount() );
}

//============================================================================
EFriendViewType EngineSettings::getWhichContactsToView( void )
{
	int32_t whichContactView = eFriendViewEverybody;
	getIniValue( MY_SETTINGS_KEY, "WhichContactsToView", whichContactView, eFriendViewEverybody );
	return (EFriendViewType)whichContactView;
}

//============================================================================
void EngineSettings::setWhichContactsToView( EFriendViewType eViewType )
{
	int32_t whichContactView = (int32_t)eViewType;
	setIniValue( MY_SETTINGS_KEY, "WhichContactsToView", whichContactView );
}

//============================================================================
void EngineSettings::getExternalIp( std::string& strIpAddress )
{
	getIniValue( MY_SETTINGS_KEY, "ExternalIp", strIpAddress, "" );
}

//============================================================================
void EngineSettings::setExternalIp( std::string& strIpAddress )
{
	setIniValue( MY_SETTINGS_KEY, "ExternalIp", strIpAddress );
}

//============================================================================
uint16_t EngineSettings::getTcpIpPort( bool bGetRandomIfDoesntExist )
{
    uint16_t u16IpPort;
	getIniValue( MY_SETTINGS_KEY, "TcpIpPort", u16IpPort, 0 );
	if( 0 == u16IpPort )
	{
        if( bGetRandomIfDoesntExist )
        {
            u16IpPort = VxGetRandomTcpPort();
        }
        else
        {
            u16IpPort = NET_DEFAULT_NETSERVICE_PORT;
        }

		setTcpIpPort( u16IpPort );
	}

    return u16IpPort;
}

//============================================================================
void EngineSettings::setTcpIpPort( uint16_t u16IpPort )
{
	setIniValue( MY_SETTINGS_KEY, "TcpIpPort", u16IpPort );
}

//============================================================================
void EngineSettings::getMulticastPort( uint16_t& u16IpPort )
{
	getIniValue( MY_SETTINGS_KEY, "UdpIpPort", u16IpPort, DEFAULT_UDP_PORT );
}

//============================================================================
void EngineSettings::setMulticastPort( uint16_t u16IpPort )
{
	setIniValue( MY_SETTINGS_KEY, "UdpIpPort", u16IpPort );
}

//============================================================================
void EngineSettings::setMulticastEnable( bool enableMulticast )
{
	setIniValue( MY_SETTINGS_KEY, "MulticastEnable", enableMulticast );
}

//============================================================================
void EngineSettings::getMulticastEnable( bool& enableMulticast )
{
	getIniValue( MY_SETTINGS_KEY, "MulticastEnable", enableMulticast, false );
}

//============================================================================
void EngineSettings::getNetServiceWebsiteUrl( std::string& strWebsiteUrl )
{
	getIniValue( MY_SETTINGS_KEY, "NetServiceUrl", strWebsiteUrl, NET_DEFAULT_NETSERVICE_URL );
}

//============================================================================
void EngineSettings::setNetServiceWebsiteUrl( std::string& strWebsiteUrl )
{
	setIniValue( MY_SETTINGS_KEY, "NetServiceUrl", strWebsiteUrl );
}

//============================================================================
void EngineSettings::getNetHostWebsiteUrl( std::string& strWebsiteUrl )
{
	getIniValue( MY_SETTINGS_KEY, "HostUrl", strWebsiteUrl, NET_DEFAULT_NET_HOST_URL );
}

//============================================================================
void EngineSettings::setNetHostWebsiteUrl( std::string& strWebsiteUrl )
{
	setIniValue( MY_SETTINGS_KEY, "HostUrl", strWebsiteUrl );
}

//============================================================================
void EngineSettings::setIsThisNodeAnNetHostOld( bool isHost )
{
	setIniValue( MY_SETTINGS_KEY, "IsNodeHost", isHost );
}

//============================================================================
bool EngineSettings::getIsThisNodeAnNetHostOld( void )
{
	bool isHost = false;
	getIniValue( MY_SETTINGS_KEY, "IsNodeHost", isHost, false );
	return isHost;
}

//============================================================================
void EngineSettings::setExcludeMeFromNetHostList( bool excludeFromHostList )
{
	setIniValue( MY_SETTINGS_KEY, "ExcludeFromHostList", excludeFromHostList );
}

//============================================================================
bool EngineSettings::getExcludeMeFromNetHostList( void )
{
	bool excludeMe = false;
	getIniValue( MY_SETTINGS_KEY, "ExcludeFromHostList", excludeMe, false );
	return excludeMe;
}

//============================================================================
void EngineSettings::getNetworkKey( std::string& strNetworkName )
{
	if( m_CachedNetworkName.length() )
	{
		strNetworkName = m_CachedNetworkName;
	}
	else
	{
		getIniValue( MY_SETTINGS_KEY, "NetworkName", strNetworkName, NET_DEFAULT_NETWORK_NAME );
		m_CachedNetworkName = strNetworkName;
	}
}

//============================================================================
void EngineSettings::setNetworkKey( std::string& strNetworkName )
{
	m_CachedNetworkName = strNetworkName;
	setIniValue( MY_SETTINGS_KEY, "NetworkName", strNetworkName );
}

//============================================================================
bool EngineSettings::getUseUpnpPortForward( void )
{
	bool bUseUpnp = true;
	getIniValue( MY_SETTINGS_KEY, "UseUpnp", bUseUpnp, false );
	return bUseUpnp;
}

//============================================================================
void EngineSettings::setUseUpnpPortForward( bool bUseUpnpPortForward )
{
	setIniValue( MY_SETTINGS_KEY, "UseUpnp", bUseUpnpPortForward );
}

//============================================================================
bool EngineSettings::getUseNatPortForward( void )
{
	bool bUseNat = true;
	getIniValue( MY_SETTINGS_KEY, "UseNat", bUseNat, false );
	return bUseNat;
}

//============================================================================
void EngineSettings::setUseNatPortForward( bool bUseNatPortForward )
{
	setIniValue( MY_SETTINGS_KEY, "UseNat", bUseNatPortForward );
}

//============================================================================
EngineSettings::EFirewallTestType EngineSettings::getFirewallTestSetting( void )
{
	uint16_t u16Setting;
	getIniValue( MY_SETTINGS_KEY, "FirewallTest", u16Setting, 0 );
	return (EngineSettings::EFirewallTestType)u16Setting;
}

//============================================================================
void EngineSettings::setFirewallTestSetting( EngineSettings::EFirewallTestType eFirewallTestType )
{
	uint16_t u16Setting = (uint16_t)eFirewallTestType;
	setIniValue( MY_SETTINGS_KEY, "FirewallTest", u16Setting );
}

//=========================================================================
//=== file share settings ===//
//============================================================================
void EngineSettings::getCompletedDnldsDir( std::string& strCompletedDir )
{
	getIniValue( MY_SETTINGS_KEY, "CompletedDnldsDir", strCompletedDir, "" );
}

//============================================================================
void EngineSettings::setCompletedDnldsDir( std::string& strCompletedDir )
{
	setIniValue( MY_SETTINGS_KEY, "CompletedDnldsDir", strCompletedDir );
}

//============================================================================
void EngineSettings::getIncompleteDnldsDir( std::string& strIncompleteDir )
{
	getIniValue( MY_SETTINGS_KEY, "IncompleteDnldsDir", strIncompleteDir, "" );
}

//============================================================================
void EngineSettings::setIncompleteDnldsDir( std::string& strIncompleteDir )
{
	setIniValue( MY_SETTINGS_KEY, "IncompleteDnldsDir", strIncompleteDir );
}

//============================================================================
void EngineSettings::getDnldsBandwidth( uint32_t& u32Bandwidth )
{
	getIniValue( MY_SETTINGS_KEY, "DnldsBandwidth", u32Bandwidth, 0 );
}

//============================================================================
void EngineSettings::setDnldsBandwidth( uint32_t& u32Bandwidth )
{
	setIniValue( MY_SETTINGS_KEY, "DnldsBandwidth", u32Bandwidth );
}

//============================================================================
void EngineSettings::getMaxDownloadingFiles( uint32_t& u32MaxDownloadingFiles )
{
	getIniValue( MY_SETTINGS_KEY, "MaxDownloadingFiles", u32MaxDownloadingFiles, DEFAULT_MAX_DOWNLOADING_FILES );
}

//============================================================================
void EngineSettings::setMaxDownloadingFiles( uint32_t& u32MaxDownloadingFiles )
{
	setIniValue( MY_SETTINGS_KEY, "MaxDownloadingFiles", u32MaxDownloadingFiles );
}

//============================================================================
void EngineSettings::getSharedFilesDirs( std::vector<std::string>& strSharedDirs )
{
	getIniValue( MY_SETTINGS_KEY, "SharedDirs", strSharedDirs );
}

//============================================================================
void EngineSettings::setSharedFilesDirs( std::vector<std::string>& strSharedDirs )
{
	setIniValue( MY_SETTINGS_KEY, "SharedDirs", strSharedDirs );
}

//============================================================================
void EngineSettings::getUpldsBandwidth( uint32_t& u32Bandwidth )
{
	getIniValue( MY_SETTINGS_KEY, "UpldsBandwidth", u32Bandwidth, 0 );
}

//============================================================================
void EngineSettings::setUpldsBandwidth( uint32_t& u32Bandwidth )
{
	setIniValue( MY_SETTINGS_KEY, "UpldsBandwidth", u32Bandwidth );
}

//============================================================================
void EngineSettings::getMaxUploadingFiles( uint32_t& u32MaxUploadingFiles )
{
	getIniValue( MY_SETTINGS_KEY, "MaxUploadingFiles", u32MaxUploadingFiles, DEFAULT_MAX_UPLOADING_FILES );
}

//============================================================================
void EngineSettings::setMaxUploadingFiles( uint32_t& u32MaxUploadingFiles )
{
	setIniValue( MY_SETTINGS_KEY, "MaxUploadingFiles", u32MaxUploadingFiles );
}

//============================================================================
void EngineSettings::setMaxRelaysInUse( uint32_t userRelays, uint32_t anonRelays )
{
	setIniValue( MY_SETTINGS_KEY, "MaxUserRelays", userRelays );
	setIniValue( MY_SETTINGS_KEY, "MaxSystemRelays", anonRelays );
}

//============================================================================
void EngineSettings::getMaxRelaysInUse( uint32_t& userRelays, uint32_t& anonRelays )
{
	getIniValue( MY_SETTINGS_KEY, "MaxUserRelays", userRelays, DEFAULT_USER_RELAYS );
	getIniValue( MY_SETTINGS_KEY, "MaxSystemRelays", anonRelays, DEFAULT_ANON_RELAYS );
}

//============================================================================
void EngineSettings::setAllowUserLocation( bool allowUserLocation )
{
	setIniValue( MY_SETTINGS_KEY, "AllowUserLocation", allowUserLocation );
}

//============================================================================
bool EngineSettings::getAllowUserLocation( void )
{
	bool allowUserLocation = true;
	getIniValue( MY_SETTINGS_KEY, "AllowUserLocation", allowUserLocation, true );
	return allowUserLocation;
}

//============================================================================
void EngineSettings::setAllowMulticastBroadcast( bool allowBroadcast )
{
	setIniValue( MY_SETTINGS_KEY, "AllowBroadcast", allowBroadcast );
}

//============================================================================
bool EngineSettings::getAllowMulticastBroadcast( void )
{
	bool allowBroadcast = true;
	getIniValue( MY_SETTINGS_KEY, "AllowBroadcast", allowBroadcast, false );
	return allowBroadcast;
}

//============================================================================
void EngineSettings::setPreferredNetworkAdapterIp( const char * wirelessIpAddress )
{
	std::string strVal = "";
	if( wirelessIpAddress )
	{
		strVal = wirelessIpAddress;
	}

	setIniValue( MY_SETTINGS_KEY, "AdapterIp", wirelessIpAddress );
}

//============================================================================
std::string EngineSettings::getPreferredNetworkAdapterIp( void )
{
	std::string strVal;
	getIniValue( MY_SETTINGS_KEY, "AdapterIp", strVal, "" );
	return strVal;
}

//============================================================================
void EngineSettings::setLastFirewallPort( uint16_t u16IpPort )
{
	setIniValue( MY_SETTINGS_KEY, "firewallPort", u16IpPort );
}

//============================================================================
uint16_t EngineSettings::getLastFirewallPort( void )
{
	uint16_t u16IpPort;
	getIniValue( MY_SETTINGS_KEY, "firewallPort", u16IpPort, 0 );
	return u16IpPort;
}


