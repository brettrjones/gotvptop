package com.p2pgotv.gotvstation;

import java.util.Hashtable;
import java.util.Timer;
import java.util.TimerTask;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.util.Log;

public class MyService extends Service 
{
	//=== constants ===//
	private static final String LOG_TAG = "MyService";
	private static final long ONLINE_UPDATE_INTERVAL = 10800000; // three minutes
	
	//=== static vars ===//
	private static 	MyP2PWeb			m_oMainActivity;
	private static 	ServiceUpdateUIListener m_oUpdateUIListener;

	//=== vars ===//
	
	private Timer m_oOnlineUpdateTimer = new Timer();
	
	//=== interfaces ===//
	public interface ServiceUpdateUIListener 
	{
		public void updateUI(Hashtable<String, Hashtable<String, String>> data);

	}//end interface ServiceUpdateUIListener


	//=== get/set ===//
	public static void setMainActivity( MyP2PWeb activity ) 
	{
		m_oMainActivity = activity;
	}

	public static void setUpdateListener(ServiceUpdateUIListener l) 
	{
		m_oUpdateUIListener = l;
	}
	//------------------------------------------------------------
	//=== overrides ===//
	//------------------------------------------------------------
	@Override
	public IBinder onBind(Intent intent) 
	{
		return null;
	}
	
	@Override
	public void onCreate() 
	{
		super.onCreate();
		//Toast.makeText(this, "My Service Created", Toast.LENGTH_LONG).show();
		Log.d(LOG_TAG, "onCreate");
		DoStartService();
	}

	@Override
	public void onDestroy() 
	{
		//Toast.makeText(this, "My Service Stopped", Toast.LENGTH_LONG).show();
		Log.d(LOG_TAG, "onDestroy");
		DoStopService();
	}
	
	@Override
	public void onStart(Intent intent, int startid) 
	{
		//Toast.makeText(this, "My Service Started", Toast.LENGTH_LONG).show();
		Log.d(LOG_TAG, "onStart");
		//player.start();
	}
	//------------------------------------------------------------
	//=== methods ===//
	//------------------------------------------------------------
	private void DoStartService() 
	{
		m_oOnlineUpdateTimer.scheduleAtFixedRate(
		      new TimerTask() 
		      {
		        public void run() 
		        {
				    final String orgName = Thread.currentThread().getName();
				    Thread.currentThread().setName(orgName + " MyService:DoStartService");		

		        	SendImOnlineUpdate();
		        }
		      },
		      0,
		      ONLINE_UPDATE_INTERVAL);
		Log.i(getClass().getSimpleName(), "Timer started!!!");
	}
	
	private void DoStopService() 
	{
		if (m_oOnlineUpdateTimer != null)
		{
			m_oOnlineUpdateTimer.cancel();
		}
		Log.i(getClass().getSimpleName(), "Timer stopped!!!");
	}
	private void SendImOnlineUpdate() 
	{
	}
	
}
