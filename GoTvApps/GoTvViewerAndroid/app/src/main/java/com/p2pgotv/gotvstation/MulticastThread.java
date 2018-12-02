//============================================================================
// Copyright (C) 2010 Brett R. Jones
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

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.net.UnknownHostException;

import android.util.Log;

public class MulticastThread implements Runnable
{
	static final String LOG_TAG = "Multicast Thread";
	InetAddress m_MulticastAddress = null;
	String text;
	@Override
	public void run() 
	{
	    final String orgName = Thread.currentThread().getName();
	    Thread.currentThread().setName(orgName + " MulticastThread");		

		try 
		{
			m_MulticastAddress = InetAddress.getByName("224.255.255.33");
		} 
		catch (UnknownHostException e1) 
		{
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	// TODO Auto-generated method stub
		try
		{
			MulticastSocket socket_multicast = null;
			try 
			{
				socket_multicast = new MulticastSocket(65000);
			} 
			catch (IOException e) 
			{
				e.printStackTrace();
			}
			
			try 
			{
				socket_multicast.joinGroup(m_MulticastAddress);
			} 
			catch (IOException e) 
			{
				e.printStackTrace();
			}
			Log.i(LOG_TAG, "Multicast Thread Waiting for multicast");

			byte[] bmessage = new byte[1500];
			DatagramPacket p = new DatagramPacket(bmessage, bmessage.length);
			socket_multicast.receive(p);
			//if( NativeTxTo.getMyApp().getIsNetworkAvailable() )
			//{
				Log.i( LOG_TAG, "GOT MULTICAST OF LEN " + p.getLength() );
				//Get the message
				NativeTxTo.fromGuiMulitcastPkt( p.getData(), p.getLength() );			
			//}
			
			socket_multicast.close();
		 
		} 
		catch (Exception e) 
		{
			Log.e(LOG_TAG, "MulticastThread Exception " + e.toString() );		 
		}
	}
}
