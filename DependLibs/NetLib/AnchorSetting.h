#pragma once
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

#include <CoreLib/VxDefs.h>

#include <string>

//#ifdef APP_MYP2PWEB
	#define NET_DEFAULT_NETWORK_NAME			"GoTvPtoPWeb"
	#define NET_DEFAULT_ANNOUNCE_URL			"http://www.myp2panchor.com:45124"
	#define NET_DEFAULT_NETSERVICE_URL			"http://www.myp2pconnect.com:45124"
//#else
//	#define NET_DEFAULT_NETWORK_NAME			"TestNet"
//	#define NET_DEFAULT_ANNOUNCE_URL			"http://www.p2pthing.com:45124"
//	#define NET_DEFAULT_NETSERVICE_URL			"http://www.p2pthing.com:45124"
//#endif // APP_MYP2PWEB


class AnchorSetting
{
public:
	AnchorSetting();
	virtual ~AnchorSetting(){};

	AnchorSetting&				operator =( const AnchorSetting& rhs );

	void						setAnchorSettingName( const char * settingName )			{ m_AnchorSettingName = settingName; }
	std::string&				getAnchorSettingName( void )								{ return m_AnchorSettingName; }

	void						setNetworkName( const char * networkName )					{ m_NetworkName = networkName; }
	std::string&				getNetworkName( void )										{ return m_NetworkName; }

	void						setAnchorWebsiteUrl( const char * anchorUrl )				{ m_AnchorWebsiteUrl = anchorUrl; }
	std::string&				getAnchorWebsiteUrl( void )									{ return m_AnchorWebsiteUrl; }

	void						setIsThisNodeAnAnchor( bool isAnchor )						{ m_ThisNodeIsAnchor = isAnchor; }
	bool						getIsThisNodeAnAnchor( void )								{ return m_ThisNodeIsAnchor; }

	void						setExcludeMeFromAnchorList( bool excludeMe )				{ m_ExcludeMeFromAnchorList = excludeMe; }
	bool						getExcludeMeFromAnchorList( void )							{ return m_ExcludeMeFromAnchorList; }

	void						setNetServiceWebsiteUrl( const char * netServiceUrl )		{ m_NetServiceWebsiteUrl = netServiceUrl; }
	std::string&				getNetServiceWebsiteUrl( void )								{ return m_NetServiceWebsiteUrl; }

protected:
	//=== vars ===//
	std::string					m_AnchorSettingName;
	std::string					m_NetworkName;

	std::string					m_NetServiceWebsiteUrl;
	std::string					m_AnchorWebsiteUrl;
	bool						m_ThisNodeIsAnchor;
	bool						m_ExcludeMeFromAnchorList;
};
