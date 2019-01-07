package com.p2pgotv.gotvstation;

import android.app.Activity;
import android.content.Intent;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.ProgressBar;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.TextView;

public class VidCamCtrlLogic implements OnSeekBarChangeListener 
{
	private static final String LOG_TAG = "VidCamCtrlLogic:";
	
	final int					MOTION_ALARM_EXPIRE_MS			= 5000;
	final int					MOTION_RECORD_EXPIRE_MS			= 30000;

	MyApp						m_MyApp							= null;
	MySettings					m_AppSettings					= null;
	Activity 					m_Activity						= null;
	ImageViewWithSizer 			m_VidCamView					= null;
	ImageViewWithSizer 			m_VidCamThumbnail				= null;
	
	LinearLayout				m_CamAllLayout					= null;
	LinearLayout				m_AllCtrlsLayout				= null;
	
	LinearLayout				m_CamImageCtrlLayout			= null;
	boolean						m_CamImageCtrlsVisible 			= false;
    Button						m_CamSourceButton				= null;
    Button						m_CamPreviewButton				= null;
    Button						m_CamRotateButton				= null;
    Button						m_FeedRotateButton				= null;
    
    LinearLayout				m_RecordCtrlLayout				= null;
	boolean						m_RecordCtrlsVisible 			= false;
    Button						m_PictureSnapshotButton 		= null;
    ButtonPro					m_NormalRecordButton			= null;
    ButtonPro					m_MotionRecordButton			= null;
    ButtonPro					m_MotionAlarmButton				= null;
    ButtonPro					m_VidFilesButton				= null;    
   
    LinearLayout				m_MotionLayout					= null;
	boolean						m_MotionSesitivityVisible 		= true;
    TextView					m_SesitivityLabel				= null;
    ProgressBar 				m_MotionBar						= null;
    SeekBar 					m_MotionSlider					= null;

	
	boolean						m_DisablePreview				= false;
	boolean						m_InPlay						= false;
	boolean						m_InNormalRecord				= false;
	boolean						m_MotionRecordOn				= false;
	boolean						m_MotionRecordDetected			= false;
	boolean						m_MotionAlarmOn					= false;
	boolean						m_MotionAlarmDetected			= false;
	TimerPro 					m_MotionAlarmExpireTimer		= new TimerPro( MOTION_ALARM_EXPIRE_MS );
	TimerPro 					m_MotionRecordExpireTimer		= new TimerPro( MOTION_RECORD_EXPIRE_MS );
	
	boolean						m_NeedPictureSnapshot 			= false;
	int 						m_CurMotion0to100000			= 0;
	int 						m_LastMotion0to100000			= 0;
	
	//private int					m_RequestMediaType  				= Constants.eMediaInputVideoJpgSmall;
	private VxGUID 				m_VideoFeedId						= null;
	private VxGUID				m_MyOnlineId 						= null; // same as vid feed id for vid recording
	private VxNetIdent			m_MyIdent 							= null; 
	private VxGUID				m_FriendId 							= null; 
	private VxNetIdent			m_FriendIdent 						= null; 
	public boolean				m_IsPersonalRecorder 				= false;
	public AssetGuiInfo			m_AssetGuiInfo						= null;
	public String				m_FileName							= "";
	public VxTimer 				m_RecordTimer						= new VxTimer();
	public long					m_TimeRecStart						= 0;
	public boolean 				m_IsInVideoRecording 				= false;
	public boolean 				m_IsMyPreviewVidFeedRequested 		= false;

	//========================================================================
	public VidCamCtrlLogic( MyApp myApp, Activity activity, VxNetIdent hisIdent, ImageViewWithSizer vidCamView, ImageViewWithSizer vidCamThumbnail ) 
	{
		m_MyApp								= myApp;
		m_AppSettings						= m_MyApp.getMySettings();
		m_Activity 							= activity;
		m_VidCamView						= vidCamView;
		m_VidCamThumbnail					= vidCamThumbnail;
		
		m_MyIdent							= m_MyApp.getMyIdentity();
		m_MyOnlineId 						= m_MyIdent.getMyOnlineId();
		m_FriendIdent						= hisIdent;
		m_FriendId							= hisIdent.getMyOnlineId();
		m_VideoFeedId						= m_MyOnlineId;

        if( null != m_VidCamView )
        {
        	m_VideoFeedId = m_VidCamView.getVideoFeedId();
        	if( null == m_VideoFeedId )
        	{
        		m_VideoFeedId = m_FriendIdent.getMyOnlineId();
        		m_VidCamView.setVideoFeedId( m_VideoFeedId );
        	}
        	
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
     	    	        onCamViewClick();
     	    	        break;
     	    	    default:
     	    	        break;
     	    	    }
     	    	   
     	    	    return true;
         	    } 
        	}); 
        }

        if(null != m_VidCamThumbnail)
        {
 	        m_VidCamThumbnail.m_IsThumbnail = true;
 	        m_VidCamThumbnail.setVideoFeedId( m_MyOnlineId );
    		m_VidCamThumbnail.setOnTouchListener(new OnTouchListener() 
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
    	    	        onCamViewClick();
    	    	        break;
    	    	    default:
    	    	        break;
    	    	    }
    	    	   
    	    	    return true;
        	    }  	    
        	});  
    		
            m_VidCamThumbnail.setViewScale( 0.25f );
        }	
	}

	//========================================================================
	public void initializeVidCamLogic() 
	{
		if( null == m_Activity )
		{
			return;
		}

		m_CamAllLayout			= (LinearLayout)m_Activity.findViewById( R.id.reuse_cam_all_layout );
	    m_AllCtrlsLayout 		= (LinearLayout)m_Activity.findViewById( R.id.reuse_cam_all_ctrls_frame );
	    m_CamImageCtrlLayout	= (LinearLayout)m_Activity.findViewById( R.id.reuse_cam_image_ctrls_frame );
	    m_RecordCtrlLayout		= (LinearLayout)m_Activity.findViewById( R.id.reuse_cam_record_ctrls_frame );
	    
	    m_CamSourceButton		= (Button)m_Activity.findViewById( R.id.reuse_cam_source_button );
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
	    
	    m_CamPreviewButton		= (Button)m_Activity.findViewById( R.id.reuse_cam_preview_button );
	    if( null != m_CamPreviewButton )
	    {
	    	m_CamPreviewButton.setOnClickListener(new OnClickListener() 
        	{
	            public void onClick(View v) 
	            {
	    	        m_MyApp.playButtonClick();
	    	        onCamPreviewButtonClicked();
	            }
	        });     	    	
	    }
	    
	    m_CamRotateButton		= (Button)m_Activity.findViewById( R.id.reuse_cam_rotate_button );
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
	    
	    m_FeedRotateButton		= (Button)m_Activity.findViewById( R.id.reuse_cam_screen_rotate_button );
	    if( null != m_FeedRotateButton )
	    {
	    	m_FeedRotateButton.setOnClickListener(new OnClickListener() 
        	{
	            public void onClick(View v) 
	            {
	    	        m_MyApp.playButtonClick();
	                onFeedRotateButtonClicked();
	            }
	        });     	    	
	    }
	    
	    m_PictureSnapshotButton = (Button)m_Activity.findViewById( R.id.reuse_cam_photo_snapshot_button );
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
	    
	    m_NormalRecordButton	= (ButtonPro)m_Activity.findViewById( R.id.reuse_cam_normal_record_button );
	    if( null != m_NormalRecordButton )
	    {
			m_NormalRecordButton.setIconResources( 	R.drawable.button_camcorder_normal, 
													R.drawable.button_camcorder_disabled,
													R.drawable.button_camcorder_cancel,
													R.drawable.button_camcorder_red,  
													R.drawable.button_camcorder_yellow );	    
			m_NormalRecordButton.setOnClickListener(new OnClickListener() 
        	{
	            public void onClick(View v) 
	            {
	    	        m_MyApp.playButtonClick();
	                onNormalRecordButtonClicked();
	            }
	        });     	    			
	    }
	    
	    m_MotionRecordButton	= (ButtonPro)m_Activity.findViewById( R.id.reuse_cam_motion_record_button );
	    if( null != m_MotionRecordButton )
	    {
			m_MotionRecordButton.setIconResources( 	R.drawable.button_record_motion_normal, 
					R.drawable.button_record_motion_disabled, 
					R.drawable.button_record_motion_cancel, 
					R.drawable.button_record_motion_red,
					R.drawable.button_record_motion_yellow );
	    	m_MotionRecordButton.setOnClickListener(new OnClickListener() 
        	{
	            public void onClick(View v) 
	            {
	    	        m_MyApp.playButtonClick();
	                onMotionRecordButtonClicked();
	            }
	        });     	    			
	    }
	    
	    m_MotionAlarmButton		= (ButtonPro)m_Activity.findViewById( R.id.reuse_cam_motion_alarm_button );
	    if( null != m_MotionAlarmButton )
	    {
			m_MotionAlarmButton.setIconResources( 	R.drawable.button_motion_alarm_normal, 
					R.drawable.button_motion_alarm_disabled, 
					R.drawable.button_motion_alarm_cancel,
					R.drawable.button_motion_alarm_red,  
					R.drawable.button_motion_alarm_yellow );
	    	m_MotionAlarmButton.setOnClickListener(new OnClickListener() 
        	{
	            public void onClick(View v) 
	            {
	    	        m_MyApp.playButtonClick();
	                onMotionAlarmButtonClicked();
	            }
	        });     	    			
	    }
	    
	    m_VidFilesButton		= (ButtonPro)m_Activity.findViewById( R.id.reuse_cam_vid_files_button );
	    if( null != m_VidFilesButton )
	    {
	    	m_VidFilesButton.setIconResources( 	R.drawable.button_file_browse_normal, 
												R.drawable.button_file_browse_disabled, 
												R.drawable.button_file_browse_cancel );
	    	m_VidFilesButton.setEnabled( false );
	    	m_VidFilesButton.setOnClickListener(new OnClickListener() 
        	{
	            public void onClick(View v) 
	            {
	    	        m_MyApp.playButtonClick();
	                onVidFilesButtonClicked();
	            }
	        });     	    			
	    }	 
	    
	    m_MotionLayout			= (LinearLayout)m_Activity.findViewById( R.id.reuse_cam_sesitivity_frame );
	    m_MotionBar				= (ProgressBar)m_Activity.findViewById( R.id.reuse_cam_motion_progress_bar );
	    m_MotionSlider			= (SeekBar)m_Activity.findViewById( R.id.reuse_cam_motion_slider );
    	if( null != m_MotionSlider )
    	{	      
    		m_MotionSlider.setProgress( m_MyApp.getMySettings().getCamMotionSensitivity() );
       	   	m_MotionSlider.setOnSeekBarChangeListener( this );
    	}	
  	        
        setPreviewVisibility();
        
       	if( null != m_MyApp.getCamCaptureMgr() )
    	{
       		if( m_MyApp.getCamCaptureMgr().getCameraListCount() < 2 )
	        {
	        	if( null != m_CamSourceButton )
	        	{
	        		m_CamSourceButton.setEnabled( false );
	        	}
	        }
    	}
    }
	
 	//========================================================================
    public void showCamAllLayout( boolean show )
    {
    	if( null != m_CamAllLayout )
    	{
    		if( show )
    		{
    			m_CamAllLayout.setVisibility( View.VISIBLE );   			
    		}
    		else
    		{
    			m_CamAllLayout.setVisibility( View.GONE );			
    		}
    	}
    }

    //============================================================================
    void setImageRotation( int Rotation )
    {
    	
    }  
    
 	 //========================================================================
    public void setCamViewImage( int drawableResourceId )
    {
    	m_VidCamView.setCamViewImage( drawableResourceId );
    }

    //============================================================================
    void activityHasResumed()
    {
    	if( !m_FileName.isEmpty() 
    		&& ( null != m_VidFilesButton ) )
    	{
    		// if resume check if recording has been deleted.. if has then disable view file button
    		long fileLen = VxFileUtil.getFileLen( m_FileName );
    		if( 0 == fileLen )
    		{
    			m_VidFilesButton.setEnabled(  false );
    		}
    	}
    }

    //============================================================================
    void activityOnDestroy()
    {
    	if( null != m_MyOnlineId )
    	{
    		NativeTxTo.fromGuiWantMediaInput( m_MyOnlineId.m_u64IdHiPart, m_MyOnlineId.m_u64IdLoPart, Constants.eMediaInputVideoJpgSmall, false );
    	}
    }
    
    //============================================================================
    void onVidFilesButtonClicked()
    {
    	if( ( null != m_AssetGuiInfo )
    		&& ( null != m_Activity )
    		&& ( false == m_FileName.isEmpty() ) )
    	{
    		Intent myIntent = new Intent( m_Activity, ActivityViewVideoFile.class );
    		myIntent.putExtra( Constants.PARAM_FILE_NAME, m_FileName );
    		m_Activity.startActivityForResult( myIntent, Constants.ACTIVITY_VIEW_VIDEO_FILE );
    	}
    }
    
	//========================================================================
	@Override
	public void onProgressChanged(SeekBar seekBar, int progresValue, boolean fromUser) 
	{
    }
          
	//========================================================================
	@Override
	public void onStartTrackingTouch(SeekBar seekBar) 
	{
    }

	//========================================================================
	@Override
    public void onStopTrackingTouch(SeekBar seekBar) 
	{
		m_MyApp.getMySettings().setCamMotionSensitivity( seekBar.getProgress() );
          //textView.setText("Covered: " + progress + "/" + seekBar.getMax());
          //Toast.makeText(getApplicationContext(), "Stopped tracking seekbar", Toast.LENGTH_SHORT).show();
	}
   
	//========================================================================
	public void onOncePer500ms() 
	{
    	if( 100 < Math.abs( m_CurMotion0to100000 - m_LastMotion0to100000 ) )
    	{
    		m_LastMotion0to100000 = m_CurMotion0to100000;
	        onVidFeedMotion( m_CurMotion0to100000 );
    	}

		if( null != m_NormalRecordButton ) 	{ m_NormalRecordButton.onOncePerBlink(); }
		if( null != m_MotionRecordButton ) 	{ m_MotionRecordButton.onOncePerBlink(); }
		if( null != m_MotionAlarmButton ) 	{ m_MotionAlarmButton.onOncePerBlink(); }
		if( m_MotionAlarmExpireTimer.checkForExpire() )
		{
			onMotionAlarmTimeout();
		}
		
		if( m_MotionRecordExpireTimer.checkForExpire() )
		{
			onMotionRecordTimeout();
		}			
    };
 	
	//========================================================================
	public void onCamViewClick()
	{	
	   	boolean visState = ! isFeedControlsVisible();
    	showFeedControls( visState );
    	showRecordControls( visState );	
	}		
	
	//========================================================================
    private void setPreviewVisibility()
    {
        if( null != m_VidCamThumbnail )
        {
 			if( ( false == m_DisablePreview )
 				&& m_MyApp.getMySettings().getCamShowPreview() )
        	{
        		m_VidCamThumbnail.setVisibility( View.VISIBLE );
				if( false == m_IsMyPreviewVidFeedRequested )
 				{
					m_IsMyPreviewVidFeedRequested = true;
		 			NativeTxTo.fromGuiWantMediaInput( m_MyOnlineId.m_u64IdHiPart, m_MyOnlineId.m_u64IdLoPart, Constants.eMediaInputVideoJpgSmall, true );
				}
 	        }
        	else
        	{
         		m_VidCamThumbnail.setVisibility( View.GONE );
				if( m_IsMyPreviewVidFeedRequested )
 				{
					m_IsMyPreviewVidFeedRequested = false;
					NativeTxTo.fromGuiWantMediaInput( m_MyOnlineId.m_u64IdHiPart, m_MyOnlineId.m_u64IdLoPart, Constants.eMediaInputVideoJpgSmall, false );
 				}
        	}
        }
    }		
  
    //============================================================================
    void setVideoFeedId( VxGUID feedOnlineId )				
    { 
    	if( ! feedOnlineId.equals( m_VideoFeedId ) )
    	{
    		if( m_VideoFeedId.isOnlineIdValid() )
    		{
    			// stop previous feed
    			NativeTxTo.fromGuiWantMediaInput( m_VideoFeedId.m_u64IdHiPart, m_VideoFeedId.m_u64IdLoPart, Constants.eMediaInputVideoJpgSmall, false );
    		}

    		m_VideoFeedId = feedOnlineId; 
    		if( m_VideoFeedId.equals( m_MyOnlineId ) )
    		{
    			disablePreview( true );
    		}
    		
    		if( m_VideoFeedId.isVxGUIDValid() )
    		{
    			NativeTxTo.fromGuiWantMediaInput( m_VideoFeedId.m_u64IdHiPart, m_VideoFeedId.m_u64IdLoPart, Constants.eMediaInputVideoJpgSmall, true );
    		}
    		else
    		{
    			showOfflineImage();
    		}
    	}
    }

    //============================================================================
    void showOfflineImage()
    {
    	setCamViewImage( R.drawable.ic_cam_black );
    }
	
    //============================================================================
    VxGUID getMyId()
    {
    	return m_MyOnlineId;
    }
    
    //============================================================================
    VxGUID getFriendId()
	{
		return m_FriendId;
	}

    //============================================================================
    void setIsVideoRecording( boolean isRecording )
    {
    	m_IsInVideoRecording = isRecording;
    }

    //============================================================================
    boolean getIsVideoRecording()
    {
    	return m_IsInVideoRecording;
    }
    
    //============================================================================
    void showAllCamControls( boolean showCtrls )
    {
    	showFeedControls( showCtrls );
    	showRecordControls( showCtrls );
    	showMotionSensitivityControls( showCtrls );
    	enableCamPreviewButton( true );
    }
    
	//========================================================================
    public void enableCamSourceControls( boolean enable )
    {
    	if( enable )
    	{
    		enableCamPreviewButton( true );
    		updatePreviewVisibility();
    		m_CamRotateButton.setEnabled( true );
    	    m_CamRotateButton.setBackgroundResource( R.drawable.button_cam_rotate_normal );
    	    m_CamSourceButton.setEnabled( true );
    	    m_CamSourceButton.setBackgroundResource( R.drawable.button_cam_select_normal );
    	}
    	else
    	{
    		enableCamPreviewButton( false );
    		m_CamRotateButton.setEnabled( false );
    	    m_CamRotateButton.setBackgroundResource( R.drawable.button_cam_rotate_disabled );
       	    m_CamSourceButton.setEnabled( false );
    	    m_CamSourceButton.setBackgroundResource( R.drawable.button_cam_select_disabled );
     	}
    }
    
    
 	//========================================================================
    public void enableCamPreviewButton( boolean enable )
    {
    	if( null != m_CamPreviewButton )
    	{
	    	if( enable && ( false == m_DisablePreview ) )
	    	{
	       		m_CamPreviewButton.setEnabled( true );
	    		m_CamPreviewButton.setBackgroundResource( R.drawable.button_cam_preview_normal );
	    	}
	    	else
	    	{
	    		m_CamPreviewButton.setEnabled( false );
	    		m_CamPreviewButton.setBackgroundResource( R.drawable.button_cam_preview_disabled );	    		
	    	}
    	}
    }
    
 	//========================================================================
    public void enableCamFeedControls( boolean enable )
    {
     	if( enable )
     	{
     		m_FeedRotateButton.setEnabled( true );
     		m_FeedRotateButton.setBackgroundResource( R.drawable.button_rotate_image_normal );
     	}
     	else
     	{
     		m_FeedRotateButton.setEnabled( false );
     		m_FeedRotateButton.setBackgroundResource( R.drawable.button_rotate_image_disabled );
      	}
    }  

    //============================================================================
    void showFeedControls( boolean showCtrls )
    {
    	if( null != m_CamImageCtrlLayout )
    	{
    		m_CamImageCtrlsVisible = showCtrls;
    		if( showCtrls )
    			m_CamImageCtrlLayout.setVisibility( View.VISIBLE );
    		else
       			m_CamImageCtrlLayout.setVisibility( View.GONE );
    	}   	
    }

    //============================================================================
    boolean isFeedControlsVisible()
    {
    	return m_CamImageCtrlsVisible;
    }

    //============================================================================
    void showRecordControls( boolean showCtrls )
    {
    	if( null != m_RecordCtrlLayout )
    	{
    		m_RecordCtrlsVisible = showCtrls;
    		if( showCtrls )
    			m_RecordCtrlLayout.setVisibility( View.VISIBLE );
    		else
    			m_RecordCtrlLayout.setVisibility( View.GONE );
    	} 
    	
    	showMotionSensitivityControls( showCtrls );
    }

    //============================================================================
    boolean isRecordControlsVisible()
    {
     	return m_RecordCtrlsVisible;
    }

    //============================================================================
    void showMotionSensitivityControls( boolean showCtrls )
    {
    	if( null != m_MotionLayout )
    	{
      		if( showCtrls )
    		{
    			m_MotionLayout.setVisibility( View.VISIBLE );
    			m_MotionSesitivityVisible = true;
    		}
    		/*
    		else
    		{
    			m_MotionLayout.setVisibility( View.GONE );
    			m_MotionSesitivityVisible = false;
    		}
    		*/
    	}  	
    }

    //============================================================================
    boolean isMotionSensitivityControlsVisible()
    {
     	return m_MotionSesitivityVisible;
    }

    //============================================================================
    void setVidImageRotation( int imageRotation )
    {
    	m_VidCamView.setVidImageRotation( imageRotation );
    }

    //============================================================================
    int getVidImageRotation()
    {
    	return m_VidCamView.getVidImageRotation();
    }

    //============================================================================
    void onCamPreviewButtonClicked()
    {
    	boolean isVisible = m_AppSettings.getCamShowPreview();
    	m_AppSettings.setCamShowPreview( !isVisible );
    	updatePreviewVisibility();
    }

    //============================================================================
    void updatePreviewVisibility()
    {
    	boolean showPreview = m_AppSettings.getCamShowPreview();
    	if( m_DisablePreview )
    	{
    		showPreview = false;
    	}

    	m_VidCamThumbnail.setVisible( showPreview );
    	if( showPreview )
    	{
    		m_CamPreviewButton.setBackgroundResource( R.drawable.button_cam_preview_cancel_normal );
    		m_MyApp.toGuiUserMessage( R.string.cam_preview_enabled );   		
    		if( m_MyOnlineId != m_VideoFeedId )
    		{
    			NativeTxTo.fromGuiWantMediaInput( m_MyOnlineId.m_u64IdHiPart, m_MyOnlineId.m_u64IdLoPart, Constants.eMediaInputVideoJpgSmall, true );
    		}
    	}
    	else
    	{
    		m_CamPreviewButton.setBackgroundResource( R.drawable.button_cam_preview_normal );
    		m_MyApp.toGuiUserMessage( R.string.cam_preview_disabled );   		
       		if( m_MyOnlineId != m_VideoFeedId )
    		{
       			NativeTxTo.fromGuiWantMediaInput( m_MyOnlineId.m_u64IdHiPart, m_MyOnlineId.m_u64IdLoPart, Constants.eMediaInputVideoJpgSmall, false );
    		}
    	}
    }

    //============================================================================
    void onFeedRotateButtonClicked()
    {
    	int feedRotation = m_AppSettings.getVidFeedRotation();
    	feedRotation += 90;
    	if( feedRotation >= 360 )
    	{
    		feedRotation = 0;
    	}

    	m_AppSettings.setVidFeedRotation( feedRotation );
    	updateFeedImageRotation();
    	m_MyApp.toGuiUserMessage( m_Activity.getString( R.string.rotated_contacts_video ) + " " + feedRotation + " degrees" );
    }

    //============================================================================
    void updateFeedImageRotation()
    {
    	int feedRotation = m_AppSettings.getVidFeedRotation();
    	setVidImageRotation( feedRotation );
    }
    
 	//========================================================================
 	public void onCamSourceButtonClicked()
 	{	
	    if( null != m_MyApp.getCamCaptureMgr() )
	    {
	 		if( 1 == m_MyApp.getCamCaptureMgr().getCameraListCount() )
	 		{
	 		   	m_MyApp.toGuiUserMessage( R.string.cannot_switch_cam_only_1 );	
	 		}
	 		else
	 		{
 	       		m_MyApp.getCamCaptureMgr().switchCameras();
 	       		m_MyApp.toGuiUserMessage( "Switched To Camera " + m_MyApp.getCamCaptureMgr().getWhichCamera() );	
 	    	}
 		}
  	}

    //============================================================================
    void onCamRotateButtonClicked()
    {
	    if( null != m_MyApp.getCamCaptureMgr() )
	    {
	    	m_MyApp.getCamCaptureMgr().incrementRotation();
	    	disablePreview( false );
	    	boolean isVisible = m_AppSettings.getCamShowPreview();
	    	if( false == isVisible )
	    	{
	    		m_AppSettings.setCamShowPreview( !isVisible );
	    		updatePreviewVisibility();
	    	}    		
	
	    	m_MyApp.toGuiUserMessage( m_Activity.getString( R.string.rotated_my_camera ) +  " " + m_MyApp.getCamCaptureMgr().getRotation() + " degrees" );
	    }
    }

    //============================================================================
    void disablePreview( boolean disable )
    {
    	m_DisablePreview = disable;
    	if( m_DisablePreview )
    	{
    		m_VidCamThumbnail.setVisible( false );
    		enableCamPreviewButton( false );
    	}
    	else
    	{
       		enableCamPreviewButton( true );
    		updatePreviewVisibility();
    	}
    }
    
  	//========================================================================
    public void toGuiPlayVideoFrame( VxGUID guidId, byte[] pu8Jpg, int jpgDataLen, int motion0to100000 )
    { 	 
    	if( guidId.equals( m_VideoFeedId ) )
    	{
    		m_CurMotion0to100000 = motion0to100000;
	    	if( null != m_VidCamView  )
	    	{
	    		//Log.i( LOG_TAG, "motion0to100000 " + motion0to100000 );
		    	m_VidCamView.toGuiPlayVideoFrame( guidId, pu8Jpg, jpgDataLen, motion0to100000 );
	    	}
	    	
	    	if( m_NeedPictureSnapshot )
	    	{
	    		m_NeedPictureSnapshot = false;
	    		// BRJ TODO save a snapshot
	    	}
    	}
    	else if( guidId.equals( m_MyOnlineId ) )
    	{
	    	if( null != m_VidCamThumbnail )
	    	{
		    	m_VidCamThumbnail.toGuiPlayVideoFrame( guidId, pu8Jpg, jpgDataLen, motion0to100000 );		
	     	}   
    	}
    }

    //============================================================================
    void onMotionAlarmTimeout()
    {
    	m_MotionAlarmExpireTimer.stop();
    	m_MotionAlarmDetected = false;
    	m_MotionAlarmButton.enableBlink( false );
    	m_MotionAlarmButton.setIcon( m_MotionAlarmDetected ? ButtonPro.eButtonIconRed : ButtonPro.eButtonIconNormal );

    	updateMotionBarColor();
    }

    //============================================================================
    void onMotionRecordTimeout()
    {
    	//m_MotionRecordExpireTimer.stop();
    	m_MotionRecordDetected = false;
    	m_MotionRecordButton.enableBlink( false );
    	
		m_MotionRecordButton.setIcon( m_MotionAlarmOn ? ButtonPro.eButtonIconRed : ButtonPro.eButtonIconNormal );
    	if( m_MotionRecordOn )
    	{
    		NativeTxTo.fromGuiVideoRecord( Constants.eVideoRecordStatePauseRecording,
    										getRecordFeedId().m_u64IdHiPart,
    										getRecordFeedId().m_u64IdLoPart,
						    				m_FileName );
    		m_MyApp.toGuiUserMessage( R.string.video_motion_rec_pause );
    	}

    	updateMotionBarColor();
    }
    
    //============================================================================
    private VxGUID getRecordFeedId()
    {
    	if( m_IsPersonalRecorder )
    	{
    		return m_MyOnlineId;
    	}
    	else
    	{
    		return m_VideoFeedId;
    	}
    }
 
    //============================================================================
    void onVidFeedMotion( int motion0To100000 )
    {
    	//qDebug() << "motion " << motion0To100000;
    	m_MotionBar.setProgress( motion0To100000 );
    	if( motion0To100000 >= m_MotionSlider.getProgress() )
    	{
    		if( m_MotionRecordOn )
    		{
    			m_MotionRecordExpireTimer.start( MOTION_RECORD_EXPIRE_MS );
    			if( !m_MotionRecordDetected )
    			{
    				m_MotionRecordDetected = true;
    				NativeTxTo.fromGuiVideoRecord( Constants.eVideoRecordStateResumeRecording, 
    						getRecordFeedId().m_u64IdHiPart,
    						getRecordFeedId().m_u64IdLoPart,
									    	    				m_FileName );
					updateMotionBarColor();
    				m_MotionRecordButton.enableBlink( true );
    				m_MyApp.toGuiUserMessage( R.string.video_motion_rec_resume );
    			}
    		}

    		if( m_MotionAlarmOn )
    		{
    			m_MotionAlarmExpireTimer.start( MOTION_ALARM_EXPIRE_MS );
    			if( !m_MotionAlarmDetected )
    			{
    				m_MotionAlarmDetected = true;
    				playMotionAlarm();
    				updateMotionBarColor();
    				m_MotionAlarmButton.enableBlink( true );
    			}
    		}
    	}
    }

    //============================================================================
    void updateMotionBarColor()
    {
    	if( m_MotionAlarmDetected || m_MotionRecordDetected )
    	{
    		m_MotionBar.setBackgroundResource( R.color.motion_detected );
    	}
    	else
    	{
    		m_MotionBar.setBackgroundResource( R.color.no_motion_detected );
    	}
    }

    //============================================================================
    void playMotionAlarm()
    {
    	m_MyApp.playSound( ESndDef.eSndDefMicrowaveBeep );
    }

    //============================================================================
    void onPictureSnapshotButtonClicked()
    {
    	m_NeedPictureSnapshot = true;
    	m_MyApp.playSound( ESndDef.eSndDefCameraClick );
    }

    //============================================================================
    void onMotionAlarmButtonClicked()
    {
    	if( m_MotionAlarmOn )
    	{
    		m_MotionAlarmExpireTimer.stop();
    		m_MotionAlarmDetected = false;
    		m_MyApp.toGuiUserMessage( R.string.video_motion_alarm_disable );
    	}
    	else
    	{
    		m_MyApp.toGuiUserMessage( R.string.video_motion_alarm_enable );
    	}

    	m_MotionAlarmOn = !m_MotionAlarmOn;
    	m_MotionAlarmButton.enableBlink( false );
    	m_MotionAlarmButton.setIcon(  m_MotionAlarmOn ? ButtonPro.eButtonIconRed : ButtonPro.eButtonIconNormal );

    	if( m_MotionAlarmOn )
    	{
    		showMotionSensitivityControls( true );
    	}
    	else
    	{
    		if( false == m_MotionRecordOn )
    		{
    			showMotionSensitivityControls( false );
    		}
    	}
    }

    //============================================================================
    void onMotionRecordButtonClicked()
    {
    	if( !m_InPlay
    		&& !m_InNormalRecord )
    	{
    		m_MotionRecordButton.enableBlink( false );
    		if( m_MotionRecordOn )
    		{
    			m_MyApp.toGuiUserMessage( R.string.video_motion_rec_stop );
    			videoRecord( Constants.eAssetActionRecordEnd, true );
    			m_MotionRecordButton.setIcon( ButtonPro.eButtonIconNormal );
    			m_MotionRecordOn = false;
      		}
    		else
    		{
    			m_MotionRecordDetected = false;
    			if( videoRecord( Constants.eAssetActionRecordBegin, true ) )
    			{
        			m_MotionRecordOn = true;
        			m_MotionRecordButton.setIcon( ButtonPro.eButtonIconRed );
    				m_MyApp.toGuiUserMessage( R.string.video_motion_rec_start );
    			}
    		}
    	}	
    	
    	if( m_MotionAlarmOn )
    	{
    		showMotionSensitivityControls( true );
    	}
    	else
    	{
    		if( false == m_MotionAlarmOn )
    		{
    			showMotionSensitivityControls( false );
    		}
    	}
    }

    //============================================================================
    void onNormalRecordButtonClicked()
    {
    	if( !m_InPlay
    		&& !m_MotionRecordOn )
    	{
    		if( m_InNormalRecord )
    		{
    			m_MyApp.toGuiUserMessage( R.string.video_rec_stop );
    			videoRecord( Constants.eAssetActionRecordEnd, false );
    			m_NormalRecordButton.setIcon( ButtonPro.eButtonIconNormal );
    			m_InNormalRecord = false;
    		}
    		else
    		{
       		    if( videoRecord( Constants.eAssetActionRecordBegin, false ) )
       		    {
       	   			m_InNormalRecord = true;
           			m_MyApp.toGuiUserMessage( R.string.video_rec_start );
            		m_NormalRecordButton.setIcon( ButtonPro.eButtonIconRed );
       		    }
    		}
    	}
    }  

	//========================================================================	
	boolean videoRecord( int assetAction, boolean motionRecord )
	{
		int assetType = Constants.eAssetTypeVideo;
		boolean actionResult = true;
		switch( assetAction )
		{
		case Constants.eAssetActionRecordBegin:
			if( ! getIsVideoRecording() )
			{			
				setIsVideoRecording( true );
				
				m_VidFilesButton.setEnabled( false );
				m_AssetGuiInfo = new AssetGuiInfo();
				m_AssetGuiInfo.generateNewUniqueId();
				m_AssetGuiInfo.setAssetType( Constants.eAssetTypeVideo );
				m_AssetGuiInfo.setCreatorId( getMyId() );
				m_AssetGuiInfo.setHistoryId( getRecordFeedId() );
				m_TimeRecStart = VxTimeUtil.getCurrentTime();
				m_AssetGuiInfo.setCreationTime( m_TimeRecStart );
				generateFileName( assetType, m_AssetGuiInfo.getAssetUniqueId(),m_TimeRecStart );
				m_AssetGuiInfo.setAssetName( m_FileName );

				if( motionRecord )
				{
					actionResult = NativeTxTo.fromGuiVideoRecord( 	Constants.eVideoRecordStateStartRecordingInPausedState, 
																	getRecordFeedId().m_u64IdHiPart,
																	getRecordFeedId().m_u64IdLoPart,
																	m_FileName );				
				}
				else
				{
					actionResult = NativeTxTo.fromGuiVideoRecord( 	Constants.eVideoRecordStateStartRecording, 
																	getRecordFeedId().m_u64IdHiPart,
																	getRecordFeedId().m_u64IdLoPart,
																	m_FileName );
				}
				
				if( true == actionResult )
				{
					m_RecordTimer.startTimer();					
				}
				else
				{
					NativeRxFrom.toGuiUserMessage( "Could Not Start Video Record" );
				}
			}
			
			break;

		case Constants.eAssetActionRecordEnd:
			{
				if( getIsVideoRecording() )
				{
					setIsVideoRecording( false );
					double elapsedMs = m_RecordTimer.elapsedMilliSec();
					if( 1000 > elapsedMs )
					{
						// if only pressed for a second then ignore
						NativeRxFrom.toGuiUserMessage( "Video Record cancel because less than 1 second" );
						NativeTxTo.fromGuiVideoRecord(  Constants.eVideoRecordStateCancelRecording,
														getRecordFeedId().m_u64IdHiPart,
														getRecordFeedId().m_u64IdLoPart,
														m_FileName );
						actionResult = false;
					}
					else
					{
						NativeTxTo.fromGuiVideoRecord(  Constants.eVideoRecordStateStopRecording,
														getRecordFeedId().m_u64IdHiPart,
														getRecordFeedId().m_u64IdLoPart,
														m_FileName );
						long fileLen = VxFileUtil.getFileLen( m_FileName );
						if( 7000 > fileLen )
						{
							// not long enough to be a recording
							VxFileUtil.deleteFile( m_FileName );
							//Log.e( LOG_TAG, "InputBaseWidget::videoRecord file " + m_ChatState.m_FileName + " has to short len " + fileLen );
							m_MyApp.toGuiUserMessage( "Video file too short length " + fileLen + " " + m_FileName );
							actionResult = false;
						}
						else
						{
							m_AssetGuiInfo.setAssetLength( fileLen );
							m_AssetGuiInfo.setAssetName( m_FileName );
							//NativeTxTo.fromGuiAssetAction( Constants.eAssetActionAddToAssetMgr, m_ChatState.m_AssetGuiInfo, 0 );
							m_MyApp.toGuiUserMessage( "Video create success length " + VxFileUtil.describeFileLength( fileLen ) + " " + m_FileName );
							NativeTxTo.fromGuiAddFileToLibrary( m_FileName, true, null );
							if( null != m_VidFilesButton )
							{
								m_VidFilesButton.setEnabled( true );
							}
							
							actionResult = true;
						}
					}
				}
			}

			break;

		case Constants.eAssetActionRecordCancel:
			if( getIsVideoRecording() )
			{
				setIsVideoRecording( false );
				NativeTxTo.fromGuiVideoRecord( Constants.eVideoRecordStateCancelRecording,
						getRecordFeedId().m_u64IdHiPart,
						getRecordFeedId().m_u64IdLoPart,
												m_FileName);
			}

			actionResult = false;
			break;
		}
		
		return actionResult;
	}
	
	//========================================================================	
	void generateFileName( int assetType, VxGUID uniqueId, long currentTime )
	{
		//m_FileName = VxGetUserSpecificDataDirectory() + hisOnlineId + "/" + AssetGuiInfo::getSubDirectoryName( assetType );
		String mediaSubDir = "users/";
		if( getMyId().equals( getFriendId() ) )
		{
			mediaSubDir = "me/";
		}

		m_FileName = m_MyApp.getUserXferDir() + mediaSubDir;
		VxFileUtil.createDirectory( m_FileName );
		m_FileName += m_FriendIdent.getOnlineName();
		m_FileName += "_";
		m_FileName += VxTimeUtil.getFileNameCompatibleDateAndTime( VxTimeUtil.getCurrentTime() );
		m_FileName += "#";
		m_FileName += uniqueId.toOnlineIdHexString();
		m_FileName += m_AssetGuiInfo.getDefaultFileExtension( assetType );	
	}
}

