//============================================================================
// Copyright (C) 2011 Brett R. Jones
// All Rights Reserved ( After My Death I Brett R. Jones Issue this source code to Public Domain )
//
// You may not modify or redistribute this code for any reason
// without written consent of Brett R. Jones
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// brett1900@usa.com
// http://www.gotvp2p.net
//============================================================================
package com.p2pgotv.gotvstation;

import android.util.Log;

//! implements MySettings
public class MySettings
{
	//=== constants ===//
	public static final String LOG_TAG = "MySettings";   
	public static final String MY_SETTINGS_KEY = "RCKEY"; 
	public static final int DEFAULT_MAX_UPLOADING_FILES = 3;
	public static final int DEFAULT_MAX_DOWNLOADING_FILES = 5;	
	//=== vars ===//

	private VxSettings 		m_oSettingsDb;

	//=== constructor ===//
	MySettings(MyApp myApp)
	{
		m_oSettingsDb = new VxSettings(myApp);
	}

	//=== methods ===//	
	//========================================================================
	public VxSettings getVxSettings()
	{
		return m_oSettingsDb;
	}

	//========================================================================
	public int getWhichContactsToView()
	{
		int eViewType = m_oSettingsDb.getIniValueInt( MY_SETTINGS_KEY, "WhichContactsToView", Constants.eFriendViewEverybody );
		Log.i(LOG_TAG, "getWhichContactsToView " + eViewType );
		return eViewType;
	}
	
	//========================================================================
	public void setWhichContactsToView( int eViewType )
	{
		Log.i(LOG_TAG, "setWhichContactsToView " + eViewType );
		m_oSettingsDb.setIniValue( MY_SETTINGS_KEY, "WhichContactsToView", eViewType );
	}

	//========================================================================
	public String getIpAddress()
	{
		return m_oSettingsDb.getIniValueString( MY_SETTINGS_KEY, "IpAddress", "" );
	}
	
	//========================================================================
	public void setIpAddress( String strIpAddress )
	{
		m_oSettingsDb.setIniValue( MY_SETTINGS_KEY, "IpAddress", strIpAddress );
	}
	
	//========================================================================
	public int getMyTcpInPort()
	{
		int defaultValue = 0;
		int ipPort = m_oSettingsDb.getIniValueInt( MY_SETTINGS_KEY, "TcpIpPort", defaultValue );
		if( 0 == ipPort )
		{
			ipPort = NativeTxTo.fromGuiGetRandomTcpPort();
			Log.d( LOG_TAG, "TcpPort from Random " + ipPort );
			setMyTcpInPort( ipPort );
		}
		
		//Log.d( LOG_TAG, "TcpPort from settings " + ipPort );		
		return ipPort;	
	}
	
	//========================================================================
	public void setMyTcpInPort( int ipPort )
	{
		m_oSettingsDb.setIniValue( MY_SETTINGS_KEY, "TcpIpPort", ipPort );
	}
	
	//========================================================================
	public short getMyMulticastPort()
	{
		return m_oSettingsDb.getIniValueShort( MY_SETTINGS_KEY, "MulticastPort", Constants.DEFAULT_UDP_PORT );
	}
	
	//========================================================================
	public void setMyMulticastPort( int ipPort )
	{
		m_oSettingsDb.setIniValue( MY_SETTINGS_KEY, "MulticastPort", ipPort );
	}
	
	//========================================================================
	public void setMulticastEnable( boolean multicastEnable )
	{
		m_oSettingsDb.setIniValue( MY_SETTINGS_KEY, "MulticastEnable", multicastEnable ? 1 : 0 );
	}

	//========================================================================
	public boolean getMulticastEnable()
	{
		return ( 1 ==  m_oSettingsDb.getIniValueInt( MY_SETTINGS_KEY, "MulticastEnable", 0 ) );
	}

	//========================================================================
	public String getConnectionTestWebsiteUrl()
	{
		if( NativeTxTo.fromGuiGetIsAppCommercial() )
		{
			return m_oSettingsDb.getIniValueString( MY_SETTINGS_KEY, "ConnectionTestUrl", Constants.DEFAULT_TESTAPP_CONNECTION_TEST_URL );
		}
		
		return m_oSettingsDb.getIniValueString( MY_SETTINGS_KEY, "ConnectionTestUrl", Constants.DEFAULT_CONNECTION_TEST_URL );
	}	
	
	//========================================================================
	public void setConnectionTestWebsiteUrl( String strWebsiteUrl )
	{
		if( ( null != strWebsiteUrl ) && ( 0 != strWebsiteUrl.length() ) )
		{
			m_oSettingsDb.setIniValue( MY_SETTINGS_KEY, "ConnectionTestUrl", strWebsiteUrl );
		}
	}

	//========================================================================
	public void setLastBrowseDir( int eFileFilterType, String lastDir )
	{
		if( ( null != lastDir ) && ( 0 != lastDir.length() ) )
		{
			String strKey = new String( "BrowseDir" + String.valueOf( eFileFilterType ) );
			m_oSettingsDb.setIniValue( MY_SETTINGS_KEY, strKey, lastDir );			
		}
	}

	//========================================================================
	public String getLastBrowseDir( int eFileFilterType )
	{
		String strKey = new String( "BrowseDir" + String.valueOf( eFileFilterType ) );
		return m_oSettingsDb.getIniValueString( MY_SETTINGS_KEY, strKey, "" );
	}

	//========================================================================
	public String getAnchorWebsiteUrl()
	{
		if( NativeTxTo.fromGuiGetIsAppCommercial() )
		{
			return m_oSettingsDb.getIniValueString( MY_SETTINGS_KEY, "AnnounceUrl", Constants.DEFAULT_TESTAPP_ANNOUNCE_URL );
		}
		
		return m_oSettingsDb.getIniValueString( MY_SETTINGS_KEY, "AnnounceUrl", Constants.DEFAULT_ANNOUNCE_URL );
	}

	//========================================================================
	public void setAnchorWebsiteUrl( String strWebsiteUrl )
	{
		if( ( null != strWebsiteUrl ) && ( 0 != strWebsiteUrl.length() ) )
		{
			m_oSettingsDb.setIniValue( MY_SETTINGS_KEY, "AnnounceUrl", strWebsiteUrl );			
		}
	}

	//========================================================================
	public void setNetworkAdapterIp( String ipAddr )
	{
		m_oSettingsDb.setIniValue( MY_SETTINGS_KEY, "NetworkAdapterIp", ipAddr );
	}
	
	//========================================================================
	public String getNetworkAdapterIp()
	{
		return m_oSettingsDb.getIniValueString( MY_SETTINGS_KEY, "NetworkAdapterIp", Constants.DEFAULT_NETWORK_ADAPTER_IP );
	}

	//========================================================================
	public void setExternalIp( String ipAddr )
	{
		m_oSettingsDb.setIniValue( MY_SETTINGS_KEY, "ExternalIp", ipAddr );
	}
	
	//========================================================================
	public String getExternalIp()
	{
		return m_oSettingsDb.getIniValueString( MY_SETTINGS_KEY, "ExternalIp", "" );
	}
	
	//========================================================================
	public void setNetworkName( String strNetworkName )
	{
		if( ( null != strNetworkName ) && ( 0 != strNetworkName.length() ) )
		{
			m_oSettingsDb.setIniValue( MY_SETTINGS_KEY, "NetworkName", strNetworkName );
		}
	}

	//========================================================================
	public String getNetworkName()
	{
		if( NativeTxTo.fromGuiGetIsAppCommercial() )
		{
			return m_oSettingsDb.getIniValueString( MY_SETTINGS_KEY, "NetworkName", Constants.DEFAULT_TESTAPP_NETWORK_NAME );
		}
		
		return m_oSettingsDb.getIniValueString( MY_SETTINGS_KEY, "NetworkName", Constants.DEFAULT_NETWORK_NAME );
	}
	
	//========================================================================
	public void setIsDeviceAnAnchor( boolean isAnchor )
	{
		m_oSettingsDb.setIniValue( MY_SETTINGS_KEY, "IsDeviceAnAnchor", isAnchor ? 1 : 0 );
	}

	//========================================================================
	public boolean getIsDeviceAnAnchor()
	{
		return ( 1 ==  m_oSettingsDb.getIniValueInt( MY_SETTINGS_KEY, "IsDeviceAnAnchor", 0 ) );
	}
	
	//========================================================================
	public void setUseUpnpPortForward( boolean bUseUpnpPortForward )
	{
		m_oSettingsDb.setIniValue( MY_SETTINGS_KEY, "UseUpnp", bUseUpnpPortForward ? 1 : 0 );
	}

	//========================================================================
	public boolean getUseUpnpPortForward()
	{
		return ( 1 == m_oSettingsDb.getIniValueInt( MY_SETTINGS_KEY, "UseUpnp", 1 ));
	}

	//========================================================================
	public void setUseNatPortForward( int bUseNatPortForward )
	{
		m_oSettingsDb.setIniValue( MY_SETTINGS_KEY, "UseNat", bUseNatPortForward );
	}

	//========================================================================
	public int getUseNatPortForward()
	{
		return m_oSettingsDb.getIniValueInt( MY_SETTINGS_KEY, "UseNat", 1 );
	}

	//========================================================================
	public void setFirewallTestSetting( int u16ProxyDetectSetting )
	{
		m_oSettingsDb.setIniValue( MY_SETTINGS_KEY, "FirewallTest", u16ProxyDetectSetting );
	}

	//========================================================================
	public int getFirewallTestSetting()
	{
		return m_oSettingsDb.getIniValueInt( MY_SETTINGS_KEY, "FirewallTest", 0 );
	}

	//========================================================================
	public void setMutePhoneRing( boolean bPhoneRing )
	{
		int u32Value = 0;
		if( bPhoneRing )
		{
			u32Value = 1;
		}
		m_oSettingsDb.setIniValue( MY_SETTINGS_KEY, "MutePhoneRing", u32Value );
	}

	//========================================================================
	public boolean getMutePhoneRing()
	{
		int u32Value = m_oSettingsDb.getIniValueInt( MY_SETTINGS_KEY, "MutePhoneRing", 0 );

		if( 0 != u32Value )
			return true;
		return false;
	}

	//========================================================================
	public void setMuteNotifySound( boolean bNotifySound )
	{
		int u32Value = 0;
		if( bNotifySound )
		{
			u32Value = 1;
		}
		m_oSettingsDb.setIniValue( MY_SETTINGS_KEY, "MuteNotifySound", u32Value );
	}

	//========================================================================
	public boolean getMuteNotifySound()
	{
		int u32Value = m_oSettingsDb.getIniValueInt( MY_SETTINGS_KEY, "MuteNotifySound", 0 );

		if( 0 != u32Value )
			return true;
		return false;
	}
	
	//========================================================================
	public void setActiveCamSourceId( int camSourceId /*0=front cam 1=back cam*/ )
	{
		m_oSettingsDb.setIniValue( MY_SETTINGS_KEY, "ActiveCamSourceId", camSourceId );	
	}

	//========================================================================
	public int getActiveCamSourceId()
	{
		return m_oSettingsDb.getIniValueInt( MY_SETTINGS_KEY, "ActiveCamSourceId", 0 );
	}

	//========================================================================
	public void setCamRotation( int camId, int orientation /*0-90-180-270*/ )
	{
		String settingName = "CamServerOrientation";
		settingName += camId;
		m_oSettingsDb.setIniValue( MY_SETTINGS_KEY, settingName, orientation );	
	}
	
	//========================================================================
	public int getCamRotation( int camId )
	{
		String settingName = "CamServerOrientation";
		settingName += camId;
		return m_oSettingsDb.getIniValueInt( MY_SETTINGS_KEY, settingName, 0 );
	}

	//========================================================================
	public void setVidFeedRotation( int orientation /*0-90-180-270*/ )
	{
		m_oSettingsDb.setIniValue( MY_SETTINGS_KEY, "VidFeedRotation", orientation );	
	}
	
	//========================================================================
	public int getVidFeedRotation( )
	{
		return m_oSettingsDb.getIniValueInt( MY_SETTINGS_KEY, "VidFeedRotation", 0 );
	}
	
	//========================================================================
	public boolean getCamShowPreview()
	{
		int val = m_oSettingsDb.getIniValueInt( MY_SETTINGS_KEY, "CamShowPreview", 1 );
		return ( 0 == val ) ? false : true;
	}

	//========================================================================
	public void setCamShowPreview( boolean showPreview )
	{
		int val = showPreview ? 1 : 0;
		m_oSettingsDb.setIniValue( MY_SETTINGS_KEY, "CamShowPreview", val );	
	}
	
	//========================================================================
	public int getCamMotionSensitivity()
	{
		return m_oSettingsDb.getIniValueInt( MY_SETTINGS_KEY, "CamSensitivity", 1000 );
	}

	//========================================================================
	public void setCamMotionSensitivity( int val )
	{
		m_oSettingsDb.setIniValue( MY_SETTINGS_KEY, "CamSensitivity", val );	
	}
	
	//========================================================================
	public void setUserRelayPermissionCount( int userPermittedCount )
	{
		m_oSettingsDb.setIniValue( MY_SETTINGS_KEY, "UserRelayCnt", userPermittedCount );	
	}
	
	//========================================================================
	public int getUserRelayPermissionCount()
	{
		return m_oSettingsDb.getIniValueInt( MY_SETTINGS_KEY, "UserRelayCnt", 2 );
	}
	
	
	//========================================================================
	public void setSystemRelayPermissionCount( int anonymousCount )
	{
		m_oSettingsDb.setIniValue( MY_SETTINGS_KEY, "AnonRelayCnt", anonymousCount );	
	}
	
	//========================================================================
	public int getSystemRelayPermissionCount()
	{
		return m_oSettingsDb.getIniValueInt( MY_SETTINGS_KEY, "AnonRelayCnt", 2 );
	}
};
