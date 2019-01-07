package com.p2pgotv.gotvstation;

public class NetSettings extends AnchorSetting
{	
	//=== vars ===//
	int							m_MyTcpInPort;
	int							m_MyMulticastPort;
	boolean						m_MulticastEnable;
	boolean						m_UseUpnpPortForward;
	int							m_UserRelayPermissionCount;
	int							m_SystemRelayPermissionCount;
	boolean						m_AllowUserLocation;
	boolean						m_AllowMulticastBroadcast;
	
	public void					setMyTcpInPort( int port )								{ m_MyTcpInPort = port; }
	public int					getMyTcpInPort()										{ return m_MyTcpInPort; }
	public void					setMyMulticastPort( int port )							{ m_MyMulticastPort = port; }
	public int					getMyMulticastPort()									{ return m_MyMulticastPort; }

	public void					setMulticastEnable( boolean enable )					{ m_MulticastEnable = enable; }
	public boolean				getMulticastEnable()									{ return m_MulticastEnable; }
	public void					setUseUpnpPortForward( boolean enable )					{ m_UseUpnpPortForward = enable; }
	public boolean				getUseUpnpPortForward()									{ return m_UseUpnpPortForward; }
	public void					setUserRelayPermissionCount( int count )				{ m_UserRelayPermissionCount = count; }
	public int					getUserRelayPermissionCount()							{ return m_UserRelayPermissionCount; }
	public void					setSystemRelayPermissionCount( int count )				{ m_SystemRelayPermissionCount = count; }
	public int					getSystemRelayPermissionCount()							{ return m_SystemRelayPermissionCount; }

}
