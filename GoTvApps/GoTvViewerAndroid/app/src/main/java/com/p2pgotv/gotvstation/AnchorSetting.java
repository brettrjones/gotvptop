package com.p2pgotv.gotvstation;

public class AnchorSetting 
{	
	//=== vars ===//
	String						m_AnchorSettingName;
	String						m_NetworkName;

	String						m_NetServiceWebsiteUrl;
	String						m_AnchorWebsiteUrl;
	boolean						m_ThisDeviceIsAnAnchor;

	public void					setAnchorSettingName( String name )						{ m_AnchorSettingName = name; }
	public String				getAnchorSettingName()									{ return m_AnchorSettingName; }

	public void					setNetworkName( String networkName )					{ m_NetworkName = networkName; }
	public String				getNetworkName()										{ return m_NetworkName; }

	public void					setAnchorWebsiteUrl( String anchorUrl )					{ m_AnchorWebsiteUrl = anchorUrl; }
	public String				getAnchorWebsiteUrl()									{ return m_AnchorWebsiteUrl; }

	public void					setIsDeviceAnAnchor( boolean isAnchor )					{ m_ThisDeviceIsAnAnchor = isAnchor; }
	public boolean				getIsDeviceAnAnchor()									{ return m_ThisDeviceIsAnAnchor; }

	public void					setNetServiceWebsiteUrl( String netServiceUrl )			{ m_NetServiceWebsiteUrl = netServiceUrl; }
	public String				getNetServiceWebsiteUrl()								{ return m_NetServiceWebsiteUrl; }
}
