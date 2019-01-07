//============================================================================
// Copyright (C) 2014 Brett R. Jones
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

import java.util.ArrayList;
import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.Semaphore;

import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;


public class ActivityTestNetwork extends ActivityBase 
{
	// === constants ===//
	public static final String LOG_TAG = "ActivityTestNetwork:";

	// === vars ===//

	public Button 					m_oTestBut = null;
	public Button 					m_VxFileUtil = null;
	public Button 					m_oDontUseAsRelayBut = null;

	public EditText 				m_LogText = null;
	public boolean 					m_isConnected = false;

	public boolean 					m_isStartupTest = true;
	
	private Semaphore 				m_oMutex = new Semaphore(1); 
	public final  ArrayList<String> m_oMessages = new  ArrayList<String>();
	public Timer 					m_Timer = new Timer();
	public VxSktUtil 				m_oVxSktUtil;	

	//========================================================================
	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) 
	{
		Log.d(LOG_TAG, "onCreate");
		setContentView(R.layout.activity_test_network);
		super.onCreate(savedInstanceState);
		setPageTitle( R.string.activitity_test_network_name );

		m_MyApp.m_oActTestNetwork = this;
		m_oVxSktUtil = m_MyApp.getVxSktUtil();

		String value = getIntent().getExtras().getString("IsStartupTest");
		Log.d(LOG_TAG, "extra value " + value);
		if (value.equals("startup")) 
		{
			m_isStartupTest = true;
		} 
		else 
		{
			m_isStartupTest = false;
		}

		Log.d(LOG_TAG, "m_LogText");
		this.m_LogText = (EditText) this.findViewById(R.id.proxy_test_log);

		Log.d(LOG_TAG, "m_oTestBut");
		this.m_oTestBut = (Button) this.findViewById(R.id.test_button);
		this.m_oTestBut.setOnClickListener(new OnClickListener() 
		{
			public void onClick(View v) 
			{
  			   	m_MyApp.playButtonClick();
				onTestButClick();
			}
		});

		this.m_CloseButton = (Button) this.findViewById(R.id.button_close);
		this.m_CloseButton.setOnClickListener(new OnClickListener() 
		{
			public void onClick(View v) 
			{
  			   	m_MyApp.playButtonClick();
				onCloseButClick();
			}
		});
		
		//Log.d(LOG_TAG, "onCreate Done");
			
		m_Timer = new Timer();
        m_Timer.schedule( new startupTask(), 300 );	

		appendLogMsg("Testing Network\n");
		
	}
	
	//========================================================================	
	//tells activity to run on ui thread
	class startupTask extends TimerTask 
	{
        @Override
        public void run() 
        {
        	ActivityTestNetwork.this.runOnUiThread(new Runnable() {
                public void run() 
                {
            		onTestButClick();
                }
            });
        }
    };
    
    /*
	//========================================================================
	public InetAddress getLocalIpAddress() 
	{
		try 
		{
			for (Enumeration<NetworkInterface> en = NetworkInterface
					.getNetworkInterfaces(); en.hasMoreElements();) 
			{
				NetworkInterface intf = en.nextElement();
				for (Enumeration<InetAddress> enumIpAddr = intf
						.getInetAddresses(); enumIpAddr.hasMoreElements();) 
				{
					InetAddress inetAddress = enumIpAddr.nextElement();
					if (!inetAddress.isLoopbackAddress()) 
					{
						appendLogMsg("Network Interface " + intf.getName());
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
	*/
    

	//========================================================================
	public boolean isWifiConnected() 
	{
		WifiManager wifiMgr = (WifiManager) getSystemService(WIFI_SERVICE);
		WifiInfo wifiInfo = wifiMgr.getConnectionInfo();
		return (-1 != wifiInfo.getNetworkId());
	}

	//========================================================================
	public void onTestButClick() 
	{
		Log.i(LOG_TAG, "onTestButClick result ");

		if (isWifiConnected()) 
		{
			appendLogMsg("Connected to WIFI network\n");
		} 
		else 
		{
			appendLogMsg("Connected to Phone Provider network\n");
		}

		String strIPv4 = m_oVxSktUtil.getLocalIPv4();
		String strIPv6 = m_oVxSktUtil.getLocalIPv6();
		
		appendLogMsg("Local IPv4 Address " + strIPv4 );

		startNetworkTest( strIPv4, strIPv6 );
	}

	//========================================================================
	public void appendLogMsg(String strMsg) 
	{
		Log.i(LOG_TAG, "appendLogMsg " + strMsg);
		m_LogText.append(strMsg);
	}

	//========================================================================
	public void onCloseButClick() 
	{
		onBackButtonPressed();
	}

	//========================================================================
	@Override
	public void onBackButtonPressed() 
	{
		Log.d( LOG_TAG, "Closing Dialog\n" );
		m_MyApp.m_oActTestNetwork = null; 
		super.onBackButtonPressed();
	}

	//========================================================================
	@Override
	protected void onDestroy() 
	{
		m_MyApp.m_oActTestNetwork = null; 
		Log.d(LOG_TAG, "onDestroy");
		super.onDestroy();
	}

	//========================================================================
	// network
	//========================================================================
	//========================================================================
	public void fromNetworkTesterTestLog(String strMsgIn) 
	{
		try 
		{
			Log.d( LOG_TAG, "fromNetworkTesterTestLog acquire" );
			m_oMutex.acquire();
			//Log.d( LOG_TAG, "fromNetworkTesterTestLog adding " + strMsgIn );
			m_oMessages.add(strMsgIn);
			//Log.d( LOG_TAG, "fromNetworkTesterTestLog release" );
			m_oMutex.release();
		} 
		catch (InterruptedException e) 
		{
			e.printStackTrace();
		}

		runOnUiThread(new Runnable() 
		{    
			public void run() 
			{   
	            final String orgName = Thread.currentThread().getName();
	            Thread.currentThread().setName(orgName + " fromNetworkTesterTestLog");		

				try 
				{
					//Log.d( LOG_TAG, "fromNetworkTesterTestLog run aquire " );
					m_oMutex.acquire();
					if( 0 != m_oMessages.size() )
					{
						//Log.d( LOG_TAG, "fromNetworkTesterTestLog run getting string " );
						String strMsg = m_oMessages.get(0);			
						//Log.d( LOG_TAG, "fromNetworkTesterTestLog run appending " + strMsg );
						appendLogMsg(strMsg);  
						//Log.d( LOG_TAG, "fromNetworkTesterTestLog run removing " + strMsg );
						m_oMessages.remove(0);
					}
					//Log.d( LOG_TAG, "fromNetworkTesterTestLog run release " );		
					m_oMutex.release();
					//Log.d( LOG_TAG, "fromNetworkTesterTestLog run done " );	
				} 
				catch (InterruptedException e) 
				{
					e.printStackTrace();
				}
			}  
		});		
	}

	//========================================================================
	public void fromNetworkTesterTestComplete( boolean bRelayRequiredIn ) 
	{
		final boolean bRelayRequired = bRelayRequiredIn;
		if( m_isStartupTest ) 
		{
			Log.d( LOG_TAG, "fromNetworkTesterTestComplete\n" );
	    	runOnUiThread(new Runnable() 
	    	{
	        	public void run() 
	        	{
		            final String orgName = Thread.currentThread().getName();
		            Thread.currentThread().setName(orgName + " fromNetworkTesterTestComplete");		

	    			Log.d( LOG_TAG, "setting proxy required\n" );
	        		appendLogMsg("Network Test Complete RELAY  "
	        				+ (bRelayRequired ? "REQUIRED" : "NOT REQUIRED"));
	    			Log.d( LOG_TAG, "handleRelayRequired\n" );	
					try 
					{
						m_oMutex.acquire();
						handleRelayRequired(bRelayRequired); 
						m_oMutex.release();
					}
					catch (InterruptedException e) 
					{
						e.printStackTrace();
					}					
	        	}
	    	});			
		}
	}

	//========================================================================
	public void handleRelayRequired(boolean bRelayRequired) 
	{
		if( m_isStartupTest ) 
		{
			m_MyApp.m_bRelayRequired = bRelayRequired;
	        onCloseButClick();
		}
	}

	//========================================================================
	public void startNetworkTest( String strIPv4, String strIPv6 ) 
	{
		Log.d(LOG_TAG, "startTestNetwork");
		MySettings mySettings = m_MyApp.getMySettings();
		Log.d( LOG_TAG, "toNetworkTesterTestNetwork port " +  mySettings.getMyTcpInPort() );
/*
		NativeTxTo.toNetworkTesterTestNetwork(
				0, // verbose log
				mySettings.getNetworkName(),
				mySettings.getConnectionTestWebsiteUrl(),
				mySettings.getAltConnectionTestWebsiteUrl(),
				mySettings.getWhatsMyIPWebsiteUrl(),
				mySettings.getAltWhatsMyIPWebsiteUrl(),
				mySettings.getUseUpnpPortForward(),
				mySettings.getTcpIpPort(),
				strIPv4,
				strIPv6 );
	*/	
		Log.d(LOG_TAG, "startTestNetwork done");
	}

}
