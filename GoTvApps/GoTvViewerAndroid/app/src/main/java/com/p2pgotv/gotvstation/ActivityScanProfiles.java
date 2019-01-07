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

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

public class ActivityScanProfiles extends ActivityBase implements ToGuiSearchInterface
{
	// === constants ===//
	private static final String LOG_TAG = "ActivityScanProfiles:";

	// === activity vars ===//
	private Button 				m_StartScanButton 		= null;
	private Button 				m_PauseScanButton 		= null;
	private Button 				m_NextScanButton 		= null;
	private TextView 			m_ScanAvailableText		= null;
	private TextView 			m_oScanCountdownText 	= null;
	
	private ImageViewWithSizer	m_oPicMe 				= null;

	public int					m_eScanType 			= Constants.eScanTypeProfilePic;
	public int					m_iCountdownCnt 		= 0;
	public int 					SCAN_INTERVAL_SEC 		= 10;
	private boolean 			m_bIsPaused 			= false;
	private boolean 			m_bSearchComplete 		= false;
 	
	private boolean 			m_ShowNextImage 		= false;
	private Handler 			m_oMessageHandler 		= null;
 	private ArrayList<IdentImagePair> 	m_ScanList 		= new ArrayList<IdentImagePair>();
	private boolean 			m_IsScanning			= false;
	private int 				RC_FLAG_HAS_SHARED_WEBCAM	= 0x02;	

 	
	//========================================================================
	@Override
	public void onCreate(Bundle savedInstanceState) 
	{
        setContentView( R.layout.activity_scan_profiles );
		super.onCreate(savedInstanceState);
		setPageTitle( R.string.activity_scan_profiles_title );

		Log.i(LOG_TAG, "onCreateCalled");
		
		this.m_StartScanButton = (Button)this.findViewById( R.id.scan_start_but );
	 	this.m_StartScanButton.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
  			   	m_MyApp.playButtonClick();
	 			onScanStartButClick();
	 		}
	 	});	
	    
		this.m_PauseScanButton = (Button)this.findViewById( R.id.scan_pause_but );
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
	 	
	 	this.m_oPicMe = (ImageViewWithSizer)this.findViewById( R.id.pic_me );
	 	
		m_oMessageHandler = new Handler() 
		{
		    @Override
		    public void handleMessage(Message msg) 
		    {
		    	switch(msg.what)
		    	{
		    	case Constants.MSG_TYPE_UPDATE_FRIEND:
		    		//Log.i(LOG_TAG, "Rxed MSG_UPDATE_FRIEND");
		    		m_ScanList.add( (IdentImagePair) msg.obj );
		    		showNextImage();
		    		break;
		    	}
		    	
		    	super.handleMessage(msg);
		    }
		};

		enableToGuiCallbacks( true );
		startStopScan( true );
	}

	//============================================================================
	void setScanStatusText( int strResourceId )
	{
		NativeRxFrom.toGuiStatusMessage( getString( strResourceId ) );
	}

	//============================================================================
	void setScanStatusText( String strMsg )
	{
		NativeRxFrom.toGuiStatusMessage( strMsg );
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
    @Override
    public void	onFriendClicked( VxNetIdent poFriendIdent )
	{  
    	startStopScan( false );
		m_MyApp.setCurrentFriend( poFriendIdent );
		m_MyApp.ShowPopupMenu( Constants.MENU_FRIEND );		
	}
  
	//========================================================================
    @Override
    protected void onDestroy() 
    {
		NativeTxTo.fromGuiStopScan( m_eScanType );
		enableToGuiCallbacks( false );
 		Log.d(LOG_TAG, "onDestroy");  
    	super.onDestroy();    	
    }
    
	//========================================================================      
    public void toGuiScanSearchComplete( int eScanType )
    {
    	if( eScanType == m_eScanType )
    	{
	    	m_bSearchComplete = true;
	    	setScanStatusText( R.string.search_complete );
    	}
    }
 	
	//========================================================================
	public void	showNextImage()
	{
		if( m_bSearchComplete 
			&& ( 0 == m_ScanList.size() ) )
		{
			startStopScan( false );
			return;
		}

		if( m_ShowNextImage && ( 0 != m_ScanList.size() ) )
		{
			m_ShowNextImage = false;
			IdentImagePair identImagePair = m_ScanList.get( 0 );
			m_ScanList.remove( 0 );		
			if( null != identImagePair )
			{
				showMatchedPair( identImagePair.getNetIdent(), identImagePair.getImage() );
			}			
		}	
		
		updateAvailableGui();
	}

	//============================================================================
	public void updateAvailableGui()
	{
		String strCountdown = "Available About Me Pictures: " + m_ScanList.size();
		m_ScanAvailableText.setText( strCountdown );
	}

	//============================================================================
	public void startCountdown()
	{
		m_iCountdownCnt = SCAN_INTERVAL_SEC;
		updateCountdownGui();
	}
    
	//========================================================================
	@Override
	public void onOncePerSecond() 
	{
		if( false == m_bIsPaused )
		{
			if( 0 < m_iCountdownCnt )
			{
				m_iCountdownCnt--;
	
				if( 0 == m_iCountdownCnt )
				{
					m_iCountdownCnt = SCAN_INTERVAL_SEC;
					m_ShowNextImage = true;
					showNextImage();
				}
	
				updateCountdownGui();
			}
		}
	}

	//============================================================================
	public void updateCountdownGui()
	{
		String strCountdown = "Next About Me Picture: " + m_iCountdownCnt;
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
  		m_bIsPaused = false;
  		if( m_IsScanning != startScan )
	  	{
	  		m_IsScanning = startScan;
	  		if( false == m_IsScanning )
	  		{
	  			m_ShowNextImage = false;
	  			setScanStatusText( "Scan For About Me Pictures Stopped" );
	  			m_StartScanButton.setText( "Start Scan" );
	  			m_PauseScanButton.setEnabled( false );
	  			m_iCountdownCnt = 0; // this stops countdown
	  			m_oScanCountdownText.setText("");
	  			m_ScanAvailableText.setText( "" );
	
	  			NativeTxTo.fromGuiStopScan( m_eScanType );
	  		}
	  		else
	  		{
	  			setScanStatusText( "Scan For About Me Pictures Started" );
	  			m_StartScanButton.setText( "Stop Scan" );
	  			m_PauseScanButton.setEnabled( true );
	  			m_bSearchComplete = false;
	  			m_ShowNextImage = true;
	  			startCountdown();
	  			NativeTxTo.fromGuiStartScan( m_eScanType, RC_FLAG_HAS_SHARED_WEBCAM, 0, "");
	  			showNextImage();
	  		}
	  	}
	}
	
	//============================================================================
	void onScanNextButClick()
	{
  		m_bIsPaused = false;
  		if( 0 == m_ScanList.size() )
	  	{
	  		setScanStatusText( "No About Me Pictures To Show" );
	  	}
	  	else
	  	{
	  		startCountdown();
	  		m_iCountdownCnt = 1;
	  		m_ShowNextImage = true;
	  	}
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
   
	//========================================================================
	public void	toGuiSearchResultProfilePic( 	VxNetIdent		netIdent, 
												byte[]			pu8JpgData, 
												int				u32JpgDataLen )
	{
		
		//setStatusMessage( getString( R.string.search_found ) + netIdent.m_as8OnlineName );
		//Log.i( LOG_TAG, "toGuiSearchResultProfilePic" );
    	final Bitmap myBitmap = BitmapFactory.decodeByteArray(pu8JpgData, 0, u32JpgDataLen);
	    if( null != myBitmap )
	    {
	    	//Log.d(LOG_TAG, "bitmap width " + myBitmap.getWidth() + " height " + myBitmap.getHeight()); 
			Message msg; 
			msg 		= Message.obtain(); 
			msg.what 	= Constants.MSG_TYPE_UPDATE_FRIEND;   
			msg.obj 	= new IdentImagePair( netIdent, myBitmap );
			m_oMessageHandler.sendMessage(msg); 
	    }
	    else
	    {
	    	Log.d(LOG_TAG, "toGuiSearchResultProfilePic null bitmap"); 
	    }
	}
	
	//========================================================================
	private void showMatchedPair( VxNetIdent netIdent, Bitmap profilePic )
	{	
		fillFriend( netIdent );
		m_oPicMe.scaleAndRotateToView( profilePic ); 		
	}

	//========================================================================
	@Override
	public void toGuiScanSearchResultSuccess( int eScanType, VxNetIdent netIdent )
	{
		// TODO Auto-generated method stub
		
	}

	//========================================================================
	@Override
	public void toGuiScanSearchResultError( int eScanType, VxNetIdent netIdent,
			int errCode )
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

