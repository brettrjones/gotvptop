//============================================================================
// Copyright (C) 2013 Brett R. Jones
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
import java.util.concurrent.Semaphore;

import android.hardware.SensorListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;

public class ActivityPhoneShake extends ActivityFriendListBase implements ToGuiSearchInterface, SensorListener
{
	// === constants ===//
	private static final String LOG_TAG = "ActivityPhoneShake:";

	// === activity vars ===//	
	public Button 				m_SimulateShakeBut = null;
	public TextView 			m_ShakeStatusLabel = null;
	
	private Semaphore 				m_oMutex = new Semaphore(1); 
	public final  ArrayList<String> m_oMessages = new  ArrayList<String>();
	
	private static final int 	FORCE_THRESHOLD 	= 250;
	 private static final int 	TIME_THRESHOLD 		= 100;
	 private static final int 	SHAKE_TIMEOUT 		= 600;
	 private static final int 	SHAKE_DURATION 		= 700;
	 private static final int 	SHAKE_COUNT 		= 2;
	
	 private SensorManager 		mSensorMgr;
	 private float 				mLastX				= -1.0f;
	 private float 				mLastY				= -1.0f;
	 private float 				mLastZ				= -1.0f;
	 private long 				mLastTime =			 0;
	 //private OnShakeListener mShakeListener;
	 private int 				mShakeCount 		= 0;
	 private long 				mLastShake 			= 0;
	 private long 				mLastForce 			= 0;

	//========================================================================
	@Override
	public void onCreate(Bundle savedInstanceState) 
	{
        setContentView( R.layout.activity_phone_shake );
		super.onCreate(savedInstanceState);		
        
		this.m_SimulateShakeBut = (Button)this.findViewById( R.id.phone_shake_but );
	 	this.m_SimulateShakeBut.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
  			   	//m_MyApp.playButtonClick();
	 			onSimulateShakeButClick();
	 		}
	 	});	
 	 	
		this.m_ShakeStatusLabel = (TextView)this.findViewById( R.id.status_msg_label );	
		
    	setPageTitle(  R.string.activity_phone_shake_title );
		 			
		Log.i(LOG_TAG, "onCreateCalled");
		enableToGuiCallbacks( true );
		onSimulateShakeButClick();
    	registerAccelerometer();
	}
    
	//========================================================================
    @Override
    public void onDestroy() 
    {
    	enableToGuiCallbacks( false );
  		Log.d(LOG_TAG, "onDestroy ");  
    	super.onDestroy();    	
    }
    
	//========================================================================
	void enableToGuiCallbacks( boolean enable )
	{
		try
		{
			if( enable )
			{
				NativeRxFrom.wantToGuiSearchClient( this, true );
			}
			else
			{
				NativeRxFrom.wantToGuiSearchClient( this, false );
			}
		}
		catch( InterruptedException e )
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
  
    //============================================================================
    void setStatusLabel( String strMsg )
    {
    	m_ShakeStatusLabel.setText( strMsg );
    }
    
	//========================================================================      
    private void onSimulateShakeButClick() 
    {
   		Log.d(LOG_TAG, "** onSimulateShakeButClick ");  
		m_MyApp.playSound( ESndDef.eSndDefSending );
		m_oContactsAdapter.clearList();
		Log.i(LOG_TAG, "notifyDataSetChanged ");
		m_oContactsAdapter.notifyDataSetChanged();
   		setStatusLabel( "Contacting Anchor" );
   		NativeTxTo.fromGuiStartScan( Constants.eScanTypePhoneShake, 0, 0, "" );
    }  

	//========================================================================
	public void	toGuiSearchResultPhoneShake( VxNetIdent netIdent )
	{
		m_MyApp.playSound( ESndDef.eSndDefUserBellMessage );
		Log.i( LOG_TAG, "toGuiSearchResultPhoneShake "  + netIdent.m_as8OnlineName );
		setStatusMessage( getString( R.string.search_found ) + netIdent.m_as8OnlineName );
		UpdateFriend( netIdent, false );
	}
   
	//========================================================================
	@Override
	public void	toGuiPhoneShakeStatus( String strMsgIn )
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
						setStatusMessage(strMsg);  
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
	@Override
	public void onListItemClick(ListView parent, View v, int position, long id) 
	{
		VxNetIdent friend = m_oContactsAdapter.getFriendByPosition(position);
		if( null != friend ) 
		{
			Log.i(LOG_TAG, "onListItemClick " + friend.m_as8OnlineName + friend.describeMyId());
			m_MyApp.setCurrentFriend(friend);
			m_MyApp.ShowPopupMenu(Constants.MENU_FRIEND);
		}
	}

	//========================================================================
	@Override
	public void toGuiScanSearchResultSuccess( int eScanType, VxNetIdent netIdent )
	{
		if( Constants.eScanTypePhoneShake == eScanType )
		{
			Log.i( LOG_TAG, "toGuiSearchResultPhoneShake "  + netIdent.m_as8OnlineName );
			setStatusMessage( getString( R.string.search_found ) + netIdent.m_as8OnlineName );
			UpdateFriend( netIdent, false );			
		}
	}

	//========================================================================
	@Override
	public void toGuiScanSearchResultError( int eScanType, VxNetIdent netIdent,
			int errCode )
	{
	}

	//========================================================================
	@Override
	public void toGuiSearchResultProfilePic( VxNetIdent netIdent,
			byte[] jpgData, int jpgDataLen )
	{
	}

	//========================================================================
	@Override
	public void toGuiScanSearchComplete( int eScanType )
	{
	}

	//========================================================================
	@Override
	public void toGuiSearchResultFileSearch( 	VxNetIdent 	netIdent,
												VxGUID 		fileInstanceId, 
												int 		u8FileType, 
												long 		u64FileLen,
												String 		pFileName )
	{
	}

	//========================================================================
	@Override
	public void onSensorChanged( int sensor, float[] values )
	{
	    if (sensor != SensorManager.SENSOR_ACCELEROMETER) return;
	    long now = System.currentTimeMillis();

	    if ((now - mLastForce) > SHAKE_TIMEOUT) 
	    {
	    	mShakeCount = 0;
	    }

	    if( ( now - mLastTime ) > TIME_THRESHOLD ) 
	    {
	    	long diff = now - mLastTime;
	    	float speed = Math.abs( (values[SensorManager.DATA_X] + values[SensorManager.DATA_Y] + values[SensorManager.DATA_Z]) - (mLastX + mLastY + mLastZ)) / diff * 1000;
	    	//Log.d( LOG_TAG, "Total Accel Force " +  speed );
	    	if (speed > FORCE_THRESHOLD) 
	    	{
	    		if ((++mShakeCount >= SHAKE_COUNT) && (now - mLastShake > SHAKE_DURATION)) 
	    		{
	    			mLastShake = now;
	    			mShakeCount = 0;

	    			onSimulateShakeButClick(); 
	    		}
	        }
	    	
	        mLastForce = now;
		    mLastTime = now;
		    mLastX = values[SensorManager.DATA_X];
		    mLastY = values[SensorManager.DATA_Y];
			mLastZ = values[SensorManager.DATA_Z];
	    }    
	}

	//========================================================================
	@Override
	public void onAccuracyChanged( int sensor, int accuracy )
	{
		// empty
	}	
	

	//========================================================================
    @Override
    protected void onPause() 
    {
        if( mSensorMgr != null ) 
        {
            mSensorMgr.unregisterListener( this, SensorManager.SENSOR_ACCELEROMETER );
            mSensorMgr = null;
        }
        
    	super.onPause();    	
    }

	//========================================================================
    @Override
    protected void onResume() 
    {
    	registerAccelerometer();
    	super.onResume();
    }

	//========================================================================
    void registerAccelerometer()
    {
    	boolean accelAvail = true;
        mSensorMgr = (SensorManager)this.getSystemService( this.SENSOR_SERVICE );
        if( mSensorMgr == null ) 
        {
        	Log.e( LOG_TAG, "Accel sensors not supported" );
        	accelAvail = false;
        }
        
        if( accelAvail )
        {	
	        boolean supported = mSensorMgr.registerListener(this, SensorManager.SENSOR_ACCELEROMETER, SensorManager.SENSOR_DELAY_GAME);
	        if (!supported) 
	        {
	        	mSensorMgr.unregisterListener(this, SensorManager.SENSOR_ACCELEROMETER);
	        	Log.e( LOG_TAG, "Accel sensors not supported" );
	        	accelAvail = false;
	        }   	
        }
        
        if( false == accelAvail )
        {
        	NativeRxFrom.toGuiUserMessage( R.string.press_simulate_phone_shake );
        }
    }
};