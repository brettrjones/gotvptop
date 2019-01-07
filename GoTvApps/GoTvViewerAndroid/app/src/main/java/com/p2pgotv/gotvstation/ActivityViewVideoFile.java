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
import android.widget.SeekBar;
import android.widget.Toast;
import android.widget.SeekBar.OnSeekBarChangeListener;

public class ActivityViewVideoFile  extends ActivityBase implements AssetCallbackInterface
{
	//=== constants ===//
	public static final String LOG_TAG = "ActivityViewSingleFile:";
	   
	//=== vars ===//
	private ReuseFileDisplayLogic  	m_FileDisplayLogic 				= null;
	
	private String					m_FileName						= "";
	private VxGUID					m_AssetGuid						= null;
	private AssetGuiInfo			m_AssetGuiInfo					= null;

	private VideoFilePlaybackView 	m_VideoFilePlaybackView;
	private Button 					m_CamPlayButton;
	private SeekBar 				m_PlayPosSlider;
	private Button 					m_CamShredButton;
	private boolean					m_SliderIsPressed   			= false;
	private boolean					m_IsPlaying   					= false;
	
	private VxFileInfo				m_VxFileInfo					= null;
	private Button 					m_IsSharedButton				= null;
	private Button 					m_IsInLibraryButton				= null;
	
    //========================================================================
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        setContentView(R.layout.activity_view_video_file);
        super.onCreate(savedInstanceState);
        setPageTitle( R.string.activity_view_video_file_title );
        Intent activityIntent = getIntent();
        Bundle extras = activityIntent.getExtras(); 
        if( null != extras ) 
        { 
        	m_FileName 	= extras.getString( Constants.PARAM_FILE_NAME );
        } 
 
        // keep keyboard from popping up
        this.getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN); 
        
		m_VideoFilePlaybackView 	= (VideoFilePlaybackView) findViewById( R.id.videoPlaybackView );	
		m_CamPlayButton 			= (Button) findViewById( R.id.vid_playplayback_button );	
		m_PlayPosSlider 			= (SeekBar) findViewById( R.id.vid_playback_seekbar );
		m_CamShredButton 			= (Button) findViewById( R.id.vid_shred_button );	
		setMediaPlaybackControls( m_CamPlayButton, m_PlayPosSlider, m_CamShredButton );
		m_CamShredButton.setVisibility( View.GONE );
		
		long			fileLen = VxFileUtil.getFileLen( m_FileName );
		m_VxFileInfo = new VxFileInfo( m_FileName, fileLen, Constants.VXFILE_TYPE_VIDEO, null );
		boolean isInLib = NativeTxTo.fromGuiGetIsFileInLibrary( m_FileName );
		m_VxFileInfo.setIsInLibrary( isInLib );
		boolean isShared = NativeTxTo.fromGuiGetIsFileShared( m_FileName );
		m_VxFileInfo.setIsShared( isShared );

		m_FileDisplayLogic = new ReuseFileDisplayLogic();
		m_FileDisplayLogic.fillFileDisplayGui( this, m_VxFileInfo );
		if( null != m_FileDisplayLogic.getFileIconBut() )
		{
			m_FileDisplayLogic.getFileIconBut().setVisibility( View.GONE );
		}
		
		m_IsSharedButton	= (Button) findViewById(R.id.vid_share_button);
	 	this.m_IsSharedButton.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
	        	m_MyApp.playButtonClick();
	        	onFileShareButClick(v);
	 		}
	 	});
	 	
		m_IsInLibraryButton	= (Button) findViewById(R.id.vid_library_button);
	 	this.m_IsInLibraryButton.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
	        	m_MyApp.playButtonClick();
	        	onFileLibraryButClick(v);
	 		}
	 	});

		m_AssetGuid		= new VxGUID();
		m_AssetGuid.initializeWithNewGUID();	
		m_AssetGuiInfo = new AssetGuiInfo();
		m_AssetGuiInfo.setAssetType( Constants.eAssetTypeVideo );
		m_AssetGuiInfo.setAssetName( m_FileName );
		m_AssetGuiInfo.setAssetUniqueId( m_AssetGuid );
		m_AssetGuiInfo.setAssetLength( fileLen );

		m_VideoFilePlaybackView.setFileNameAndId( m_FileName, m_AssetGuid );
		
	
	    setActivityReadyState( this );
	    updateFileIcons();
	    checkVolumeLevel();
    }
	
	//========================================================================
	public void setMediaPlaybackControls( Button camPlayButton, SeekBar camSeekBar, Button camShredButton )
	{
		camPlayButton.setOnClickListener(new OnClickListener() {
			public void onClick(View v) 
			{
	        	//m_MyApp.playButtonClick();
				onPlayButClick(v);
			}
		});
		
		camShredButton.setOnClickListener(new OnClickListener() 
		{
			public void onClick(View v) 
			{
	        	//m_MyApp.playButtonClick();
				onShredButClick(v);
			}
		});	
		
		camSeekBar.setOnSeekBarChangeListener(new OnSeekBarChangeListener() 
		{
			int progress = 0;
			@Override
			public void onProgressChanged(SeekBar seekBar, int progresValue, boolean fromUser) 
			{
				progress = progresValue;
			}
		 
			@Override
			public void onStartTrackingTouch(SeekBar seekBar) 
			{
				m_SliderIsPressed = true;
			}
		 
			@Override
			public void onStopTrackingTouch(SeekBar seekBar) 
			{
				m_SliderIsPressed = false;
				onUserChangedPlayPosition( progress );
			}
	   });
	}
	
	//========================================================================
	private void updateFileIcons()
	{
		m_IsInLibraryButton.setBackgroundResource( m_VxFileInfo.getIsInLibrary() ? R.drawable.button_library_normal : R.drawable.button_library_cancel );
		m_IsSharedButton.setBackgroundResource( m_VxFileInfo.getIsShared() ? R.drawable.button_share_files_normal : R.drawable.button_share_files_cancel );	
	}

	//========================================================================
	public void onFileLibraryButClick( View v )
	{
		Log.i(LOG_TAG, "onFileLibraryButClick" );
		m_MyApp.playButtonClick() ;
		// toggle is in library state
		m_VxFileInfo.setIsInLibrary( !m_VxFileInfo.getIsInLibrary() );
		NativeTxTo.fromGuiAddFileToLibrary(	m_VxFileInfo.getFullFileName(), 
												m_VxFileInfo.getIsInLibrary(),
												m_VxFileInfo.getFileHashId().getHashData() );
		updateFileIcons();
		if( m_VxFileInfo.getIsInLibrary() )
		{
			m_MyApp.toGuiUserMessage( R.string.file_is_in_library );
			Toast.makeText( this, R.string.file_is_in_library, Toast.LENGTH_SHORT ).show();
		}
		else
		{
			m_MyApp.toGuiUserMessage( R.string.file_is_not_in_library );
			Toast.makeText( this, R.string.file_is_not_in_library, Toast.LENGTH_SHORT ).show();
		}
	}
	
	//========================================================================
	public void onFileShareButClick( View v )
	{
		Log.i(LOG_TAG, "onFileShareButClick" );
		m_MyApp.playButtonClick() ;
		// toggle is in library state
		m_VxFileInfo.setIsShared( !m_VxFileInfo.getIsShared() );
		NativeTxTo.fromGuiSetFileIsShared(	m_VxFileInfo.getFullFileName(), 
												m_VxFileInfo.getIsShared(),
												m_VxFileInfo.getFileHashId().getHashData() );
		updateFileIcons();
		if( m_VxFileInfo.getIsShared() )
		{
			m_MyApp.toGuiUserMessage( R.string.file_is_shared );
			Toast.makeText( this, R.string.file_is_in_shared_list, Toast.LENGTH_SHORT ).show();
		}
		else
		{
			m_MyApp.toGuiUserMessage( R.string.file_is_not_shared );
			Toast.makeText( this, R.string.file_is_not_shared, Toast.LENGTH_SHORT ).show();
		}
	}

	//========================================================================
	private void onPlayButClick(View v) 
	{
		if( null == m_AssetGuiInfo )
		{
			return;
		}
		
		if( m_IsPlaying )
		{
			stopMediaIfPlaying();
		}
		else
		{
			setActivityReadyState( this );
			startMediaPlay( 0 );
		}
	}
	
	//========================================================================
	private void startMediaPlay( int position )
	{
		Log.i( LOG_TAG, "Chat Sending Play Begin" );
		boolean playStarted = NativeTxTo.fromGuiAssetAction( Constants.eAssetActionPlayBegin, m_AssetGuiInfo, position );
		if( false == playStarted )
		{
			Log.i( LOG_TAG, "Play FAILED TO Begin" );
		}
		
		updateGuiPlayControls( playStarted );
	}
	
	//========================================================================
	private void stopMediaIfPlaying()
	{
		if( m_IsPlaying )
		{
			Log.i( LOG_TAG, "Chat Sending Play End" );
			NativeTxTo.fromGuiAssetAction( Constants.eAssetActionPlayEnd, m_AssetGuiInfo, 0 );
		}
		
		updateGuiPlayControls( false );
	}

	//========================================================================
	private void updateGuiPlayControls( boolean isPlaying )
	{	
		if( m_IsPlaying != isPlaying )
		{
			m_IsPlaying = isPlaying;
			if( false == m_IsPlaying )
			{
				Log.i( LOG_TAG, "updateGuiPlayControls NOT playing" );
				m_CamPlayButton.setBackgroundResource( R.drawable.button_play_normal );
				m_PlayPosSlider.setProgress( 0 );
			}
			else
			{
				Log.i( LOG_TAG, "updateGuiPlayControls playing" );
				m_CamPlayButton.setBackgroundResource( R.drawable.button_pause_normal );
			}
		}
	}
	
	//========================================================================
	private void onUserChangedPlayPosition( int position )
	{
		Log.d( LOG_TAG, "onUserChangedPlayPosition " + position );
		startMediaPlay( position );
	}
	
	//========================================================================
	private void onShredButClick(View v) 
	{
		if( m_IsPlaying )
		{
			stopMediaIfPlaying();
		}
		
		m_MyApp.playSound( ESndDef.eSndDefPaperShredder );
		runOnUiThread(new Runnable() 
		{
			@Override
			public void run() 
			{
				m_CamPlayButton.setBackgroundResource( R.drawable.button_play_disabled );
				m_CamPlayButton.setEnabled(false);
				m_PlayPosSlider.setProgress( 0 );
				m_PlayPosSlider.setEnabled(false);
				NativeTxTo.fromGuiAssetAction( Constants.eAssetActionShreadFile, m_AssetGuiInfo, 0 );
				finish();
			}
		});		
	}
	
   
 	//========================================================================
    protected void setActivityReadyState( Activity curActivity )
    {
		try 
		{
			if( null == curActivity )
			{
				NativeRxFrom.wantAssetCallbackClient( this, false );
			}
			else
			{
				NativeRxFrom.wantAssetCallbackClient( this, true );
			}
		} 
		catch (InterruptedException e) 
		{
			e.printStackTrace();
		}
    }

	//========================================================================
	@Override
	public void onActivityResult(int requestCode, int resultCode, Intent data) 
	{
		super.onActivityResult(requestCode, resultCode, data);
		Log.d(LOG_TAG, "onActivityResult result code " + resultCode);
		setActivityReadyState( this );
			
		switch (requestCode) 
		{
		case Constants.ACTIVITY_CONFIRM_SHRED_FILE:
			Log.d( LOG_TAG, "onActivityResult ACTIVITY_CONFIRM_SHRED_FILE" );
			if( resultCode == Activity.RESULT_OK ) 
			{
				VxFileInfo fileInfo = m_MyApp.getCurrentFileInfo();
				if( null != fileInfo )
				{
					m_MyApp.playSound( ESndDef.eSndDefPaperShredder );
					String fullFileName = fileInfo.getFullFileName();
					NativeTxTo.fromGuiDeleteFile( fullFileName, true );
					finish();
					return;
				}				
			}
			
			break;
		case Constants.ACTIVITY_BROWSE_DEVICE_FILES:
			Log.d( LOG_TAG, "onActivityResult ACTIVITY_BROWSE_DEVICE_FILES" );
			//doRequestFileList(); // refresh list.. may be more files
			break;
		}
		
		setCamCaptureActivity( this );
	}
		 

	//============================================================================
	@Override
	protected void onPause() 
	{
		Log.d(LOG_TAG, "onPause");
		//setActivityReadyState( null );
		super.onPause();
	}

	//============================================================================
	@Override
	protected void onResume() 
	{
		Log.d(LOG_TAG, "onResume");
		super.onResume();
	    //setActivityReadyState( this );
	}

	//============================================================================
	@Override
	protected void onDestroy() 
	{
		Log.d(LOG_TAG, "onDestroy");
        setActivityReadyState( null );
        stopMediaIfPlaying();
		super.onDestroy();
	}

	//============================================================================
	@Override
	protected void onStop() 
	{
		Log.d(LOG_TAG, "onStop");
		stopMediaIfPlaying();
		super.onStop();
	}

	//========================================================================
	@Override
	public void toGuiAssetAdded( AssetGuiInfo assetInfo )
	{
	}

	//========================================================================
	@Override
	public void toGuiSessionHistory( AssetGuiInfo assetInfo )
	{
	}

	//========================================================================
	@Override
	public void toGuiAssetAction( int assetAction, VxGUID assetId, int actionParam )
	{
		if( assetId.equals( m_AssetGuiInfo.getAssetUniqueId() ) )
		{
			switch( assetAction )
			{
			case Constants.eAssetActionPlayProgress:
				if( m_IsPlaying && ( false == m_SliderIsPressed ) )
				{
					final int actionParamSave = actionParam;
					runOnUiThread(new Runnable() 
					{	
						@Override
						public void run() 
						{		
							m_PlayPosSlider.setProgress( actionParamSave  );
						}
					});
				}
				break;

			case Constants.eAssetActionPlayEnd:
				runOnUiThread(new Runnable() 
				{	
					@Override
					public void run() 
					{		
						updateGuiPlayControls( false );
					}
				});
				
				break;

			default:
				break;
			}
		}				
	}
}
