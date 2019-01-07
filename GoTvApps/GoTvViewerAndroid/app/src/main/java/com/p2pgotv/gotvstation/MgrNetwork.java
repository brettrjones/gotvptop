//============================================================================
// Copyright (C) 2010 Brett R. Jones 
// All Rights Reserved ( After My Death I Brett R. Jones Issue this source code to Public Domain )
//
// You may not redistribute and/or modify for non commercial and commercial uses 
// provided this copyright notice remains in place and is not modified
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// brett1900@usa.com
// http://www.gotvp2p.net
//============================================================================
package com.p2pgotv.gotvstation;

import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.nio.ByteOrder;
import java.util.Enumeration;
import java.util.Locale;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.util.Log;

public class MgrNetwork 
{
	private static final String LOG_TAG = "NetworkMgr: ";
	
	private MyApp 					m_MyApp					= null;
	private Context 				m_oApplicationContext	= null;
	
	private WifiManager 			m_oWifiManager			= null;
	private int						m_iDefaultIp 			= 0;
	private boolean					m_IsCellularIpAddress	= false;
	private static int 				m_iSecondCnt 			= 5;	

	//========================================================================
    public MgrNetwork( MyApp oMyApp ) 
    {
    	m_MyApp = oMyApp;
    }
    
	//========================================================================
    public void startupMgrNetwork(Context applicationContext) 
    {
    	Log.i(LOG_TAG, "MgrNetwork: Startup start");
    	//Log.i(LOG_TAG, "SoundMgr: Startup")
    	m_oApplicationContext = applicationContext;
    	//ConnectivityManager connMgr	= (ConnectivityManager)m_oApplicationContext.getSystemService(Context.CONNECTIVITY_SERVICE);
    	m_oWifiManager = (WifiManager)m_oApplicationContext.getSystemService(Context.WIFI_SERVICE);
	
    	Log.i(LOG_TAG, "MgrNetwork: Startup done");
    }
    
	//========================================================================
    public void shutdownMgrNetwork() 
    {
    	Log.i(LOG_TAG, "MgrNetwork: Shutdown start");
     	m_oWifiManager = null;
    	NativeTxTo.fromGuiNetworkLost();
    	Log.i(LOG_TAG, "MgrNetwork: Shutdown done");
    }
    
	//========================================================================
	public String getDefaultIpAddress() 
	{    
		try 
		{        
			for (Enumeration<NetworkInterface> en = NetworkInterface.getNetworkInterfaces(); en.hasMoreElements();) 
			{            
				NetworkInterface intf = en.nextElement();            
				for (Enumeration<InetAddress> enumIpAddr = intf.getInetAddresses(); enumIpAddr.hasMoreElements();) 
				{                
					InetAddress inetAddress = enumIpAddr.nextElement();                
					if (!inetAddress.isLoopbackAddress()) 
					{                    
						String addr = inetAddress.getHostAddress().toString();
						if(0 <= addr.indexOf(':') )
						{
							// its ipv6
							//Log.i(LOG_TAG, "getDefaultIpAddress found IPv6 addr " + addr);
						}
						else
						{
							//Log.i(LOG_TAG, "getDefaultIpAddress found IPv4 addr " + addr);
							return addr;
						}
					}            
				}        
			}    
		} 
		catch (SocketException ex) 
		{
			Log.e(LOG_TAG, "getDefaultIpAddress SocketException " + ex.getMessage() );
		}   
		
		Log.e(LOG_TAG, "NO DEFAULT IP ADDRESS FOUND" );
		return null;
	}
	
	//========================================================================
	public int IpStringToInt( String strIp )
	{
		int iIp = 0;
		String strDelimiter = "\\.";
		String[] octets = strIp.split( strDelimiter );
		for( int i = 0; i < octets.length; i++ )
		{
			iIp = iIp << 8;
			iIp |= Integer.parseInt( octets[i] );
		}
		
		return iIp;
	}
	
	//========================================================================
	public String IpIntToString( int ipAddress )
	{
		return String.format(Locale.getDefault(), "%d.%d.%d.%d",
						(ipAddress >> 24 & 0xff),
						(ipAddress >> 16 & 0xff),
						(ipAddress >> 8 & 0xff),
						(ipAddress & 0xff) );
		
/*		return ((iIp >> 24 ) & 0xFF) + "." +
	        ((iIp >> 16 ) & 0xFF) + "." +
	        ((iIp >>  8 ) & 0xFF) + "." +
	        ( iIp        & 0xFF);*/
	}
	
	//========================================================================
	public int getDefaultIp()
	{
		m_IsCellularIpAddress = false;
		int iDefaultIp = getWifiIp(); // try less expensive operation first
		if( 0 == iDefaultIp )
		{
			m_IsCellularIpAddress = true;
			String strIp = getDefaultIpAddress();
			//Log.d( LOG_TAG, " Get DefaultIp " + strIp );
			if( strIp != null )
			{
				iDefaultIp = IpStringToInt( strIp );
			}
		}
		
		return iDefaultIp;
	}
	
	//========================================================================
	public int getWifiIp()
	{
		WifiInfo wifiInfo = m_oWifiManager.getConnectionInfo();
		int ipAddress = wifiInfo.getIpAddress();
		if( ByteOrder.nativeOrder().equals(ByteOrder.LITTLE_ENDIAN) )
		{
			// crazy android returns default ip in net order but WifiIp in host order
			ipAddress =  Integer.reverseBytes( ipAddress );
		}	
		
		return ipAddress;
	}
	
	//========================================================================
	public boolean getIsCellNetworkConnection()
	{
		return m_IsCellularIpAddress;
	}
		
	//========================================================================
	public void onDefaultIpChange( int defaultIp )
	{
		String strDefaultIp = IpIntToString( defaultIp );
		Log.d( LOG_TAG, " Ip Changed to " + strDefaultIp );	
		if( 0 == defaultIp )
		{
			NativeRxFrom.toGuiNetworkState( Constants.eNetworkStateTypeNoInternetConnection, "" );
			NativeTxTo.fromGuiNetworkLost();
		}
		else
		{	
			NativeTxTo.fromGuiNetworkLost();
			NativeTxTo.fromGuiNetworkAvailable( strDefaultIp, m_IsCellularIpAddress);
		}
	}

	//========================================================================
	void onOncePerSecond()
	{ 
		if( null == m_oWifiManager )
		{
			return;
		}
		
		m_iSecondCnt++;
		if(m_iSecondCnt > 5 )
		{
			m_iSecondCnt = 0;
			int iDefaultIp = getDefaultIp();
			if( iDefaultIp != m_iDefaultIp )
			{
				m_iDefaultIp = iDefaultIp;
				onDefaultIpChange( m_iDefaultIp );		
			}
		}
	}

	//========================================================================
	public String describeDataNetwork()
	{
		return m_IsCellularIpAddress ? "(Cellular)" : "(Wireless)";
	}
}
