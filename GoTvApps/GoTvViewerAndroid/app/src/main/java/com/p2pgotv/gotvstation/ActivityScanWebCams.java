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

import android.content.Intent;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.widget.Button;
import android.widget.TextView;

public class ActivityScanWebCams extends ActivityBase implements ToGuiSearchInterface
{
	// === constants ===//
	private static final String LOG_TAG = "ActivityScanWebCams:";

	// === activity vars ===//
	private Button 				m_StartScanButton 		= null;
	private Button 				m_PauseScanButton 		= null;
	private Button 				m_NextScanButton 		= null;
	private TextView 			m_ScanAvailableText		= null;
	private TextView 			m_oScanCountdownText 	= null;
	
	public int					m_eScanType 			= Constants.eScanTypeCamServer;
	public int					m_ePluginType 			= Constants.ePluginTypeCamServer;
	public int					m_iCountdownCnt 		= 0;
	public int 					SCAN_INTERVAL_SEC 		= 20;
	private boolean 			m_bIsPaused 			= false;
	private boolean 			m_bSearchComplete 		= false;
	
 	private Handler 			m_oSearchCompletHandler = new Handler(); 
 	
	// camera
	public ImageViewWithSizer	m_VidCamView 			= null;
	public ImageViewWithSizer	m_VidCamThumbnail 		= null;
	
 	private Handler 			m_oCamViewHandler 		= new Handler(); 
 	public boolean 				m_bCamViewHandlerBusy 	= false; 	
 
    public int					m_iImageRotation 		= 0;
    
	private boolean 			m_ShowNextCam 			= false;
	private Handler 			m_oMessageHandler 		= null;
 	private ArrayList<VxNetIdent> 	m_ScanList 			= new ArrayList<VxNetIdent>();
	private boolean 			m_IsScanning			= false;
	private VxNetIdent 			m_HisIdent				= null;
	private VxGUID 				m_LclSessionId			= new VxGUID();
	private int 				RC_FLAG_HAS_SHARED_CAM	= 0x01;	
	private	VxGUID				m_MyOnlineId			= null;


	//========================================================================
	@Override
	public void onCreate(Bundle savedInstanceState) 
	{
        setContentView( R.layout.activity_scan_web_cams );
		super.onCreate(savedInstanceState);
		setPageTitle( R.string.activity_scan_web_cams_title );
		m_MyOnlineId = m_MyApp.getMyOnlineId();

		Log.i(LOG_TAG, "onCreateCalled");

		this.m_StartScanButton 	= (Button)this.findViewById( R.id.scan_start_but );
	 	this.m_StartScanButton.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
  			   	m_MyApp.playButtonClick();
	 			onScanStartButClick();
	 		}
	 	});	
        
		this.m_PauseScanButton = (Button)this.findViewById( R.id.scan_pause_but );
		m_PauseScanButton.setText( R.string.pause_search );
	 	this.m_PauseScanButton.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
  			   	m_MyApp.playButtonClick();
	 			onScanPauseButClick();
	 		}
	 	});	
	    
		this.m_NextScanButton = (Button)this.findViewById( R.id.scan_next_but );
	 	this.m_NextScanButton.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
  			   	m_MyApp.playButtonClick();
	 			onScanNextButClick();
	 		}
	 	});	
	    	
	 	m_ScanAvailableText = (TextView)this.findViewById( R.id.scan_available_text );
	 	this.m_oScanCountdownText = (TextView)this.findViewById( R.id.scan_countdown_text );
 	 	
        setupCamView();	
        
		m_oMessageHandler = new Handler() 
		{
		    @Override
		    public void handleMessage(Message msg) 
		    {
		    	switch(msg.what)
		    	{
		    	case Constants.MSG_TYPE_UPDATE_FRIEND:
		    		//Log.i(LOG_TAG, "Rxed MSG_UPDATE_FRIEND");
		    		m_ScanList.add( (VxNetIdent) msg.obj );
		    		showNextCam();
		    		break;
		    	}
		    	
		    	super.handleMessage(msg);
		    }
		};


		m_iCountdownCnt = SCAN_INTERVAL_SEC;
		enableToGuiCallbacks( true );
		onScanStartButClick();	
		showSpeakerButton( true );
		checkVolumeLevel();
	}
    
	//========================================================================
    @Override
    protected void onDestroy() 
    {
    	NativeTxTo.fromGuiStopScan( m_eScanType );
    	enableToGuiCallbacks( false );
		if( null != m_HisIdent )
		{
			startWebCamSession( m_HisIdent.getMyOnlineId(), false );
		}
		
 		Log.d(LOG_TAG, "onDestroy");  
    	super.onDestroy();    	
    }
    
 	//========================================================================
 	void enableToGuiCallbacks( boolean enable )
 	{
 		try
 		{
 			NativeRxFrom.wantToGuiSearchClient( this, enable );
  		}
 		catch( InterruptedException e )
 		{
 			// TODO Auto-generated catch block
 			e.printStackTrace();
 		}
 	}
 	 
 	//========================================================================
    public void showOfflineImage()
    {
    	 if( null != m_VidCamView )
    	 {
    		 m_VidCamView.showOfflineImage();
    	 }
    }
	
    //========================================================================
    @Override
    public void	onFriendClicked( VxNetIdent poFriendIdent )
	{  
    	startStopScan( false );
		m_MyApp.setCurrentFriend( poFriendIdent );
		m_MyApp.ShowPopupMenu( Constants.MENU_FRIEND );		
	}
    	
	//========================================================================
	private void setupCamView()
    {
		m_VidCamThumbnail		= (ImageViewWithSizer)this.findViewById( R.id.reuse_cam_thumbnail );
		if( null != m_VidCamThumbnail )
		{
			m_VidCamThumbnail.setVideoFeedId( m_MyOnlineId );
			m_VidCamThumbnail.setVisibility( View.GONE );
		}

		m_VidCamView 			= (ImageViewWithSizer)this.findViewById(R.id.reuse_cam_view);
        if( null != m_VidCamView )
        {
        	m_VidCamView.setOnTouchListener(new OnTouchListener() 
        	{ 
        		//@Override
        	    public boolean onTouch(View v, MotionEvent event) 
        		{ 
        	    	switch (event.getAction()) 
        	    	{
				    case MotionEvent.ACTION_DOWN:
				        //some code....
				        break;
				    case MotionEvent.ACTION_UP:
				        v.performClick();
				        //showCameraSettings();
				        break;
				    default:
				        break;
				    }
				   
				    return true;
        	    } 
        	}); 
        }
    }

	//========================================================================
	@Override
	public void onActivityResult(int requestCode, int resultCode, Intent data) 
	{	
		super.onActivityResult(requestCode, resultCode, data);
		Log.d(LOG_TAG, "onActivityResult result code " + resultCode);
		switch (requestCode) 
		{
		case Constants.ACTIVITY_CAMERA_SETTINGS:
			Log.d( LOG_TAG, "onActivityResult ACTIVITY_CAMERA_SETTINGS" );
			break;
		}
		
		setCamCaptureActivity( this );
	}
 	
	//========================================================================
	public void	showNextCam()
	{
		if( m_bSearchComplete 
			&& ( 0 == m_ScanList.size() ) )
		{
			startStopScan( false );
			return;
		}

		if( m_ShowNextCam && ( 0 != m_ScanList.size() ) )
		{
			m_ShowNextCam = false;
			VxNetIdent netIdent = m_ScanList.get( 0 );
			m_ScanList.remove( 0 );	
			if( null != netIdent )
			{
				doCamConnect( netIdent );
			}			
		}	
		
		updateAvailableGui();
	}

	//============================================================================
	void doCamConnect( VxNetIdent netIdent )
	{
		if( null != m_HisIdent )
		{
			startWebCamSession( m_HisIdent.getMyOnlineId(), false );
		}

		m_HisIdent = netIdent;
		if( null != m_HisIdent )
		{
			fillFriend( m_HisIdent );
			startWebCamSession( m_HisIdent.getMyOnlineId(), true );
 		}
	}
	
	//============================================================================
	private void startWebCamSession( VxGUID onlineId, boolean startSession )
	{
		if( startSession )
		{
			m_LclSessionId.initializeWithNewGUID();
			NativeTxTo.fromGuiStartPluginSession( 	m_ePluginType, 
													onlineId.m_u64IdHiPart,  onlineId.m_u64IdLoPart,
													m_LclSessionId.m_u64IdHiPart, m_LclSessionId.m_u64IdLoPart, 
													0 );
	   		if( null != m_VidCamView )
    		{
    			m_VidCamView.requestVideoFeed( onlineId );    			
    		}
		}
		else
		{
	   		if( null != m_VidCamView )
    		{
				m_VidCamView.stopVideoFeed();
    		}
	   		
			NativeTxTo.fromGuiStopPluginSession( 	m_ePluginType, 
													onlineId.m_u64IdHiPart,  onlineId.m_u64IdLoPart,
													m_LclSessionId.m_u64IdHiPart, m_LclSessionId.m_u64IdLoPart, 
													0 );
		}		
	}

	//============================================================================
	public void updateAvailableGui()
	{
		String strCountdown = getString( R.string.available_shared_cams ) + m_ScanList.size();
		m_ScanAvailableText.setText( strCountdown );
	}

	//========================================================================
	@Override
	public void onOncePerSecond() 
	{
		if( 0 < m_iCountdownCnt )
		{
			m_iCountdownCnt--;

			if( 0 == m_iCountdownCnt )
			{
				m_iCountdownCnt = SCAN_INTERVAL_SEC;
				m_ShowNextCam = true;
				showNextCam();
			}

			updateCountdownGui();
		}
	}

	//============================================================================
	public void startCountdown()
	{
		m_iCountdownCnt = SCAN_INTERVAL_SEC;
		updateCountdownGui();
	}

	//============================================================================
	public void updateCountdownGui()
	{
		String strCountdown = "Next Web Cam: " + m_iCountdownCnt;
		m_oScanCountdownText.setText( strCountdown );
	}

	//========================================================================      
    private void onScanStartButClick() 
    {
    	startStopScan( !m_IsScanning );
    }  

	//============================================================================
	void startStopScan( boolean startScan )
	{
	  	if( m_IsScanning != startScan )
	  	{
	  		m_bIsPaused = false;
	  		m_IsScanning = startScan;
	  		if( false == m_IsScanning )
	  		{
	  			NativeTxTo.fromGuiStopScan( m_eScanType );
				if( null != m_HisIdent )
				{
					startWebCamSession(  m_HisIdent.getMyOnlineId(), false );
					m_HisIdent = null;
				}
				
	  			m_ShowNextCam = false;
	  			setScanStatusText( getString( R.string.scan_for_shared_cams_stopped ) );
	  			m_StartScanButton.setText( "Start Scan" );
	  			m_PauseScanButton.setEnabled( false );
	  			m_iCountdownCnt = 0; // this stops countdown
	  			m_oScanCountdownText.setText("");
	  			m_ScanAvailableText.setText( "" );
	
	  		}
	  		else
	  		{  			
	  			setScanStatusText( getString( R.string.scan_for_shared_cams_started ) );
	  			m_StartScanButton.setText( "Stop Scan" );
	  			m_PauseScanButton.setEnabled( true );
	  			m_bSearchComplete = false;
	  			m_ShowNextCam = true;
	  			startCountdown();
	  			NativeTxTo.fromGuiStartScan( m_eScanType, RC_FLAG_HAS_SHARED_CAM, 0, "");
	  			showNextCam();
	  		}
	  	}
	}
	
	//============================================================================
	private void setScanStatusText( String stringMsg )
	{
		NativeRxFrom.toGuiStatusMessage( stringMsg );
	}
	
	//========================================================================      
    private void onScanPauseButClick() 
    {
    	if( !m_IsScanning )
    	{
    		startStopScan( true );
    	}
    	else
    	{
    		m_bIsPaused = !m_bIsPaused;
	    	if( m_bIsPaused )
	    	{	
	    		m_PauseScanButton.setText( R.string.continue_text );
	    		setStatusMessage( getString( R.string.search_paused ) );
		    }
	    	else
	    	{
	    		if( m_bSearchComplete )
	    		{
	    			onScanStartButClick();
	    		}
	    		else
	    		{
	    			setStatusMessage( getString( R.string.search_continue ) );
	    			m_PauseScanButton.setText( R.string.pause_search );
	    			onScanNextButClick();
	    		}
	    	}
    	}
    }  

	//============================================================================
	void onScanNextButClick()
	{
  		m_bIsPaused = false;
	  	if( 0 == m_ScanList.size() )
	  	{
	  		setScanStatusText( getString( R.string.no_cams_to_show ) );
	  	}
	  	else
	  	{		
	  		startCountdown();
	  		m_iCountdownCnt = 1;
	  		m_ShowNextCam = true;
	  	}
	}
     	
	//============================================================================
	void fromPluginPlayVideoFrame( Bitmap myBitmap, int motion0to100000 )
	{
    	//Log.d(LOG_TAG, "fromPluginPlayVideoFrame " ); 
    	if( ( null != m_VidCamView ) && this.isVisible() )
    	{	
	    	final Bitmap thisBitmap = myBitmap;
	        m_oCamViewHandler.post(new Runnable() 
    		{ 
    			public void run() 
    			{
    				m_VidCamView.scaleAndRotateToView( thisBitmap );
     			}
    		});
	    }
	    else
	    {
	    	Log.d(LOG_TAG, "fromPluginPlayVideoFrame null bitmap"); 
	    }
	}
	   	    
	//========================================================================      
	@Override
	public void toGuiScanSearchComplete( int eScanType )
	{
		if( eScanType == m_eScanType )
		{
	    	m_bSearchComplete = true;
	    	m_oSearchCompletHandler.post(new Runnable() 
	    	{ 
	    		public void run() 
	    		{ 
	    	    	String strComplete = getString( R.string.search_complete );
	    	    	setStatusMessage( strComplete );
	    		} 
	    	});
		}
	}
    
	//======================================================================== 
	@Override
	public void toGuiScanSearchResultSuccess( int eScanType, VxNetIdent netIdent )
	{
		if( Constants.eScanTypeCamServer == eScanType )
		{
			//setStatusMessage( getString( R.string.search_found ) + netIdent.m_as8OnlineName );
		    if( null != netIdent )
		    {
				Message msg; 
				msg 		= Message.obtain(); 
				msg.what 	= Constants.MSG_TYPE_UPDATE_FRIEND;   
				msg.obj 	= netIdent;
				m_oMessageHandler.sendMessage(msg); 
		    }
		    else
		    {
		    	Log.d(LOG_TAG, "jniVideoFrame null bitmap"); 
		    }
		}
	}

	 //======================================================================== 
	@Override
	public void toGuiScanSearchResultError( int eScanType,
			VxNetIdent netIdent, int errCode )
	{
		// TODO Auto-generated method stub
		
	}

	 //======================================================================== 
	@Override
	public void toGuiSearchResultProfilePic( 	VxNetIdent 	netIdent,
												byte[] 		jpgData, 
												int 		jpgDataLen )
	{
		// TODO Auto-generated method stub
		
	}

	 //======================================================================== 
	@Override
	public void toGuiSearchResultFileSearch( 	VxNetIdent 		netIdent,
												VxGUID			fileInstanceId, 
												int 			fileType, 
												long 			fileLen,
												String 			fileName )
	{
		// TODO Auto-generated method stub
		
	}

	//========================================================================
	@Override
	public void toGuiPhoneShakeStatus( String formatedMsg )
	{
		// TODO Auto-generated method stub
		
	}

};

