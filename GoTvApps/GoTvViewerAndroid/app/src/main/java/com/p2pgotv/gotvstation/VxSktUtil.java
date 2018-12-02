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

import java.net.Inet4Address;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.Iterator;

import android.util.Log;

//import android.text.format.Formatter;

public class VxSktUtil 
{
	// === constants ===//
	public static final String LOG_TAG = "TodActivityTestNetwork:";

	// === vars ===//
	
	//========================================================================
	public int getLocalIpAddressCount()
	{
		ArrayList<InetAddress> retAddresses = new ArrayList<InetAddress>();
		return getLocalIpAddress( retAddresses );
	}
	
	//========================================================================
	public String getLocalIPv4()
	{	
		String retIPv4 = "";
		
		ArrayList<InetAddress> retAddresses  = new  ArrayList<InetAddress>();
		getLocalIpAddress( retAddresses );
		
		Iterator<InetAddress> iter = retAddresses.iterator();
		//use hasNext() and next() methods of Iterator to iterate through the elements
		while( iter.hasNext() )
		{
			InetAddress addr = iter.next();
			//String strAddr = addr.toString();
			if( isIPv4( addr ) )
			{
				if( 0 == retIPv4.length() )
				{
					retIPv4 = addr.getHostAddress();
					break;					
				}
			}
		}
		
		return retIPv4;
	}	
	
	//========================================================================
	public String getLocalIPv6()
	{	
		String retIPv6 = "";
		
		ArrayList<InetAddress> retAddresses  = new  ArrayList<InetAddress>();
		getLocalIpAddress( retAddresses );
		
		Iterator<InetAddress> iter = retAddresses.iterator();
		//use hasNext() and next() methods of Iterator to iterate through the elements
		while( iter.hasNext() )
		{
			InetAddress addr = iter.next();
			//String strAddr = addr.toString();
			if( false == isIPv4( addr ) )
			{
				retIPv6 = addr.getHostAddress();
				break;
			}
		}
		return retIPv6;
	}
	
	//========================================================================
	public static boolean isIPv4( InetAddress address ) 
	{
		return address instanceof Inet4Address;
	}
	
	//========================================================================
	public static boolean trimIPAddr( String address ) 
	{
		return false;
	}
	
	//========================================================================
	public int getLocalIpAddress( ArrayList<InetAddress> retAddresses ) 
	{
		retAddresses.clear();
		try 
		{
			for (Enumeration<NetworkInterface> en = NetworkInterface
					.getNetworkInterfaces(); en.hasMoreElements();) 
			{
				NetworkInterface intf = en.nextElement();
				for (Enumeration<InetAddress> enumIpAddr = intf.getInetAddresses(); enumIpAddr.hasMoreElements();) 
				{
					InetAddress inetAddress = enumIpAddr.nextElement();
					if( !inetAddress.isLoopbackAddress() ) 
					{
						//appendLogMsg("Network Interface " + intf.getName());
						retAddresses.add( inetAddress );
					}
				}
			}
		} 
		catch (SocketException ex) 
		{
			Log.e(LOG_TAG, ex.toString());
		}
		
		return retAddresses.size();
	}
	
	//========================================================================
	public int getLocalIPv4Addresses( ArrayList<InetAddress> retAddresses ) 
	{
		retAddresses.clear();
		try 
		{
			for (Enumeration<NetworkInterface> en = NetworkInterface
					.getNetworkInterfaces(); en.hasMoreElements();) 
			{
				NetworkInterface intf = en.nextElement();
				for (Enumeration<InetAddress> enumIpAddr = intf.getInetAddresses(); enumIpAddr.hasMoreElements();) 
				{
					InetAddress inetAddress = enumIpAddr.nextElement();
					if( !inetAddress.isLoopbackAddress() 
						&& isIPv4( inetAddress ) ) 
					{
						//appendLogMsg("Network Interface " + intf.getName());
						retAddresses.add( inetAddress );
					}
				}
			}
		} 
		catch (SocketException ex) 
		{
			Log.e(LOG_TAG, ex.toString());
		}
		
		return retAddresses.size();
	}
	
	//========================================================================
	public InetAddress getLocalIpAddress() 
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
						return inetAddress;
					}
				}
			}
		} 
		catch (SocketException ex) 
		{
			Log.e(LOG_TAG, ex.toString());
		}
		return null;
	}

	//========================================================================
	public static String VxIpAddressToString( int ipAddress )
	{
		// IP Address is in reverse order
		// return Formatter.formatIpAddress(ipAddress);
		
		return ((ipAddress >> 24 ) & 0xFF) + "." +
        ((ipAddress >> 16 ) & 0xFF) + "." +
        ((ipAddress >>  8 ) & 0xFF) + "." +
        ( ipAddress        & 0xFF);
	}	
	
	//========================================================================
	public static int IpAddressToInt( String strAddress )
	{
       String[] addrArray = strAddress.split("\\.");

        long iAddress = 0;
        for (int i=0;i<addrArray.length;i++) 
        {
            int power = 3-i;

            iAddress += ((Integer.parseInt(addrArray[i])%256 * Math.pow(256,power)));
        }
        
        return (int)iAddress;	
	}	
}


