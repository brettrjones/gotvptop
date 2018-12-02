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

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;

import com.p2pgotv.gotvstation.NativeTxTo;

public class ActivityTestAnchorSettings extends ActivityBase 
{
	// === constants ===//
	public static final String LOG_TAG = "ActivityTestAnchorSettings:";

	// === vars ===//
	public Button 					m_oTestBut = null;
	public Button 					m_VxFileUtil = null;

	public EditText 				m_LogText = null;
	
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
		setContentView(R.layout.activity_test_anchor_settings);
		super.onCreate(savedInstanceState);
		setPageTitle( R.string.activity_test_anchor_settings_title );

		Log.d(LOG_TAG, "m_LogText");
		this.m_LogText = (EditText) this.findViewById(R.id.anchor_settings_test_log);

		Log.d(LOG_TAG, "m_oTestBut");
		this.m_oTestBut = (Button) this.findViewById(R.id.anchor_settings_test_button);
		this.m_oTestBut.setOnClickListener(new OnClickListener() 
		{
			public void onClick(View v) 
			{
  			   	m_MyApp.playButtonClick();
				onTestButClick();
			}
		});
		
		//Log.d(LOG_TAG, "onCreate Done");

		m_MyApp.m_oActTestAnchorSettings = this;
		onTestButClick();
	}

	//========================================================================
	public void onTestButClick() 
	{
		m_LogText.setText("Testing Anchor Settings\n");
		NativeTxTo.fromGuiVerifyAnchorSettings();
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
		m_MyApp.m_oActTestAnchorSettings = null; 
		super.onBackButtonPressed();
	}

	//========================================================================
	@Override
	protected void onDestroy() 
	{
		m_MyApp.m_oActTestAnchorSettings = null; 
		Log.d(LOG_TAG, "onDestroy");
		super.onDestroy();
	}

	//========================================================================
	// network
	//========================================================================
	//========================================================================
	public void toGuiAnchorStatus(String strMsgIn) 
	{
		try 
		{
			//Log.d( LOG_TAG, "fromNetworkTesterTestLog acquire" );
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
				try 
				{
					//Log.d( LOG_TAG, "fromNetworkTesterTestLog run acquire " );
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
}
