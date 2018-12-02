//============================================================================
// Copyright (C) 2015 Brett R. Jones
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

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.WindowManager;
import android.view.View.OnClickListener;
import android.widget.Button;

public class ActivityCameraSnapshot extends ActivityBase implements MediaCallbackInterface 
{
	//=== constants ===//
	public static final String LOG_TAG = "ActivityCameraSnapshot:";
	
	private ImageViewWithSizer 	m_VidCamView = null;
	
	private Button				m_PictureSnapshotButton		= null;
	private Button				m_CamSourceButton			= null;
	private Button				m_CamRotateButton			= null;

	private boolean				m_NeedPictureSnapshot 		= false;
	private VxGUID				m_VideoFeedId;
	private int					m_RequestMediaType			= Constants.eMediaInputVideoJpgSmall;
	private String				m_PhotoFileName				= "";
	
	//======================================================================== 
	@Override
	public void onCreate(Bundle savedInstanceState) 
	{
		Log.d(LOG_TAG, "onCreateActivityCameraSnapshot");
		setContentView(R.layout.activity_camera_snapshot);
		super.onCreate(savedInstanceState);
		setPageTitle( R.string.activity_camera_snapshot_title );
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		Bundle extras = getIntent().getExtras(); 
        if( null != extras ) 
        { 
        	m_PhotoFileName = extras.getString( Constants.PARAM_FILE_NAME );
        } 
        
        if( m_PhotoFileName.isEmpty() )
        {
        	m_PhotoFileName = VxFileUtil.generatePersonalFileName( m_MyApp );
        	m_PhotoFileName += ".jpg";	
        }
		
		m_VideoFeedId = m_MyApp.getUserAccount().getMyOnlineId();
		m_VidCamView = (ImageViewWithSizer)this.findViewById( R.id.cam_snapshot_view );
		if( null != m_VidCamView )
		{	
			m_VidCamView.setRequestMediaType( m_RequestMediaType );
			m_VidCamView.setVideoFeedId( m_VideoFeedId );
			//m_VidCamView.requestVideoFeed();
		}
	    
	    m_PictureSnapshotButton = (Button)findViewById( R.id.reuse_cam_photo_snapshot_button );
	    if( null != m_PictureSnapshotButton )
	    {
	    	m_PictureSnapshotButton.setOnClickListener(new OnClickListener() 
        	{
	            public void onClick(View v) 
	            {
	    	        m_MyApp.playButtonClick();
	                onPictureSnapshotButtonClicked();
	            }
	        });     	    	
	    }
		
	    m_CamSourceButton		= (Button)findViewById( R.id.reuse_cam_source_button );
	    if( null != m_CamSourceButton )
	    {
	    	m_CamSourceButton.setOnClickListener(new OnClickListener() 
        	{
	            public void onClick(View v) 
	            {
	    	        m_MyApp.playButtonClick();
	    	        onCamSourceButtonClicked();
	            }
	        });     	    	
	    }
	    
	    m_CamRotateButton		= (Button)findViewById( R.id.reuse_cam_rotate_button );
	    if( null != m_CamRotateButton )
	    {
	    	m_CamRotateButton.setOnClickListener(new OnClickListener() 
        	{
	            public void onClick(View v) 
	            {
	    	        m_MyApp.playButtonClick();
	    	        onCamRotateButtonClicked();
	            }
	        });     	    	
	    }
	    
	    setActivityReady( true );
	}
	
  	//========================================================================
    public void setActivityReady( boolean isReady )
    { 
		NativeTxTo.fromGuiWantMediaInput( m_VideoFeedId.m_u64IdHiPart, m_VideoFeedId.m_u64IdLoPart, m_RequestMediaType, isReady );
		try 
		{
			if( isReady )
			{
				NativeRxFrom.wantMediaCallbackClient( this, true );
			}
			else
			{
				NativeRxFrom.wantMediaCallbackClient( this, false );				
			}			
		} 
		catch (InterruptedException e) 
		{
			e.printStackTrace();
		}
    }
    
  	//========================================================================
    public void toGuiPlayVideoFrame( VxGUID guidId, byte[] jpgData, int jpgDataLen, int motion0to100000 )
    { 	 
	   	if( guidId.equals( m_VideoFeedId ) )
	   	{
	    	if( null != m_VidCamView  )
	    	{
		    	m_VidCamView.toGuiPlayVideoFrame( guidId, jpgData, jpgDataLen, motion0to100000 );
	    	}
	    	
	    	if( m_NeedPictureSnapshot )
	    	{
	    		m_NeedPictureSnapshot = false;
	    		VxFileUtil.writeBytesToFile( m_PhotoFileName, jpgData, jpgDataLen );
				runOnUiThread(new Runnable() 
				{
					public void run() 
					{
						Intent resultIntent = new Intent();
				        resultIntent.putExtra( Constants.PARAM_FILE_NAME, m_PhotoFileName );
						setResult(Activity.RESULT_OK, resultIntent);
						finish();
					}
				});
	    	}
	   	}
    }

    //============================================================================
    void onPictureSnapshotButtonClicked()
    {
    	m_NeedPictureSnapshot = true;
    	m_MyApp.playSound( ESndDef.eSndDefCameraClick );
    }
   
 	//========================================================================
 	public void onCamSourceButtonClicked()
 	{	
    	if( null != m_MyApp.getCamCaptureMgr() )
    	{
    		m_MyApp.playSound( ESndDef.eSndDefCameraClick );
    		m_MyApp.getCamCaptureMgr().switchCameras();
    	}
 	}

    //============================================================================
    void onCamRotateButtonClicked()
    {
    	if( null != m_MyApp.getCamCaptureMgr() )
    	{
    		m_MyApp.playSound( ESndDef.eSndDefCameraClick );
    		m_MyApp.getCamCaptureMgr().incrementRotation();
    	}
    }

	//============================================================================
	@Override
	protected void onDestroy() 
	{
		Log.d(LOG_TAG, "onDestroy");
		super.onDestroy();
	}

	//============================================================================
	@Override
	protected void onPause() 
	{
		Log.d(LOG_TAG, "onPause");
		super.onPause();
	}

	//============================================================================
	@Override
	protected void onResume() 
	{
		Log.d(LOG_TAG, "onResume");
		super.onResume();
	}

	//============================================================================
	@Override
	protected void onStop() 
	{
		Log.d(LOG_TAG, "onStop");
	    setActivityReady( false );
		super.onStop();
	}
}