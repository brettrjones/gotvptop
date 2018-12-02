// Derivative of Android Chat Widget https://github.com/ijarobot/ ( Apache License )
package com.p2pgotv.gotvstation;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import android.app.Activity;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.support.v4.view.PagerAdapter;
import android.support.v4.view.ViewPager;
import android.support.v4.view.ViewPager.OnPageChangeListener;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.AttributeSet;
import android.util.Log;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.inputmethod.InputMethodManager;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.GridView;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

public class ChatMessageInputToolBox extends RelativeLayout 
{	
	private static final String LOG_TAG = "CHAT:";
	private ChatOnOperationListener 	m_OnOperationListener;
	
	private Map<Integer, ArrayList<String>> m_FaceData;
	private List<ChatOption> 			m_FunctionData;
	
	// input box
	private EditText 					m_MessageEditText	= null;
	private Button 						m_FaceButton		= null;
	private Button 						m_SendButton		= null;	
	private Button 						m_MoreTypeButton	= null;
	private Button 						m_CameraButton		= null;
	private Button 						m_GalleryButton		= null;	
	private Button 						m_VideoButton		= null;
	private Button 						m_AudioButton		= null;

	// input audio
	private LinearLayout 				m_AudioInputLayout;
	private TextView					m_SndRecordLabel;
	private Button 						m_SndRecordButton;
	private Button 						m_SndCancelButton;

	// input video
	private ChatCamRecorderView			m_VidCamView;
	private Button 						m_VidRecordButton;
	private Button 						m_VidSourceButton;
	private Button 						m_VidRotateButton;
	private Button 						m_VidCancelButton;

	/** face box **/
	private RelativeLayout 				m_BottomHideLayout;
	private static RelativeLayout 		m_FaceLayout;
	private ViewPager 					m_FaceCategroyViewPager;
	private ChatPagerSlidingTabStrip 	m_FaceCategroyTabs;
	
	/** other function box **/
	private LinearLayout 				m_MoreTypeLayout;
	private ViewPager 					m_FuctionViewPager;
	private LinearLayout 				m_PagePointLayout;
	
	private RelativeLayout 				m_VideoInputLayout;
	
	List<View> 							m_FunctionGridViewList;
	List<ImageView> 					m_PointViews;
	
	ChatFaceCategroyAdapter 			m_FaceCategroyAdapter;
	
	private Context 					m_Context;
	private MyApp						m_MyApp;
	private FragmentManager 			m_FragmentManager;
	
	ChatSessionState 					m_ChatState 						= null;
	boolean								m_CanSend							= false;
	ToGuiUserInputInterface 			m_ToGuiUserInputInterface			= null;
	int									m_ECamVideoMode						= Constants.eCamVideoModeAny;	
	int									m_500msTickTock						= 0;	

	//========================================================================
	public void setInputState( ChatSessionState chatState )
	{
		m_ChatState = chatState;
		applyState();
	}

	//========================================================================
	public void applyState()
	{
		if( null != m_VidCamView )
		{
			m_VidCamView.setInputState( m_ChatState );
		}
	}
	
	//========================================================================
	public ChatMessageInputToolBox( Context context ) 
	{
		super(context);
		this.m_Context 						= context;
		initializeChatMessageInput();
		Log.i(LOG_TAG, "ChatMessageInputToolBox create" );
	}
	
	//========================================================================
	public ChatMessageInputToolBox( Context context, AttributeSet attrs ) 
	{
		super(context, attrs);
		this.m_Context 						= context;
		initializeChatMessageInput();
		Log.i(LOG_TAG, "ChatMessageInputToolBox create" );
	}

	//========================================================================
	public ChatMessageInputToolBox( Context context, AttributeSet attrs, int defStyle ) 
	{
		super(context, attrs, defStyle);
		this.m_Context 						= context;
		initializeChatMessageInput();
		Log.i(LOG_TAG, "ChatMessageInputToolBox create" );
	}
	
	//========================================================================	
	protected void initializeChatMessageInput() 
	{
		m_MyApp								= NativeRxFrom.getMyApp();
		FragmentActivity fragmentActivity 	= (FragmentActivity) m_Context;
		this.m_FragmentManager 				= fragmentActivity.getSupportFragmentManager();
		LayoutInflater.from(m_Context).inflate( R.layout.chat_message_input_tool_box, this );
	}
	
	//========================================================================	
	@Override
	protected void onFinishInflate() 
	{
		super.onFinishInflate();
		this.initView();
		setupInputMode( Constants.eChatInputSelectMode );
		Log.i(LOG_TAG, "ChatMessageInputToolBox onFinishInflate" );
	}
	
	//========================================================================	
	private void initView()
	{
		// input visible strip
		m_MessageEditText 			= (EditText) findViewById(R.id.messageEditText);
		m_SendButton 				= (Button) findViewById(R.id.sendButton);
		m_FaceButton				= (Button) findViewById(R.id.faceButton);
		m_MoreTypeButton			= (Button) findViewById(R.id.moreTypeButton);
		m_MoreTypeButton.setVisibility(View.GONE); // for now don't need array of gallery/cam/demo but don't want to erase in case need later
		m_CameraButton				= (Button) findViewById( R.id.chat_input_photo_button );
		m_GalleryButton				= (Button) findViewById( R.id.chat_input_gallery_button );
		m_VideoButton				= (Button) findViewById( R.id.chat_input_video_button );
		m_AudioButton				= (Button) findViewById( R.id.chat_input_audio_button );
		// 
		m_VidCamView				= (ChatCamRecorderView) findViewById( R.id.vid_cam_recorder_view );
		m_VidRecordButton			= (Button) findViewById( R.id.vid_record_button );
		m_VidSourceButton			= (Button) findViewById( R.id.vid_source_select_button );
		m_VidRotateButton			= (Button) findViewById( R.id.vid_rotate_button );
		m_VidCancelButton			= (Button) findViewById( R.id.vid_cancel_button );

		m_BottomHideLayout			= (RelativeLayout) findViewById(R.id.bottomHideLayout);
		m_MoreTypeLayout			= (LinearLayout) findViewById(R.id.moreTypeLayout);
		
		m_FaceLayout				= (RelativeLayout) findViewById(R.id.faceLayout);
		m_FaceCategroyViewPager 	= (ViewPager) findViewById(R.id.faceCategroyViewPager);
		m_FaceCategroyTabs 			= (ChatPagerSlidingTabStrip) findViewById(R.id.faceCategroyTabs);	
		
		m_FuctionViewPager 			= (ViewPager) findViewById(R.id.fuctionViewPager);
		m_PagePointLayout 			= (LinearLayout) findViewById(R.id.pagePointLayout);
		m_VideoInputLayout 			= (RelativeLayout) findViewById(R.id.cam_view_layout);
		m_AudioInputLayout 			= (LinearLayout) findViewById(R.id.audio_control_layout);
		m_SndRecordButton 			= (Button) findViewById(R.id.snd_record_button);
		m_SndRecordLabel 			= (TextView) findViewById(R.id.snd_record_begin_label);
		m_SndCancelButton 			= (Button) findViewById(R.id.snd_cancel_button);

		m_FuctionViewPager.setOnPageChangeListener(new OnPageChangeListener() 
		{
			@Override
			public void onPageSelected(int arg0) 
			{
				for (int i = 0; i < m_PointViews.size(); i++) 
				{
					if (arg0 == i) 
					{
						m_PointViews.get(i).setBackgroundResource(R.drawable.point_selected);
					} 
					else 
					{
						m_PointViews.get(i).setBackgroundResource(R.drawable.point_normal);
					}
				}
			}

			@Override
			public void onPageScrolled(int arg0, float arg1, int arg2) 
			{
			}

			@Override
			public void onPageScrollStateChanged(int arg0) 
			{
			}
		});
		
		m_FaceCategroyAdapter = new ChatFaceCategroyAdapter( m_FragmentManager );	
		
	
		//========================================================================	
		m_SendButton.setOnClickListener(new OnClickListener() 
		{
			@Override
			public void onClick(View v) 
			{
	        	m_MyApp.playButtonClick();
	        	onInputButtonClicked();
	        	if( m_CanSend )
	        	{        	
					if( m_OnOperationListener != null && !"".equals( m_MessageEditText.getText().toString().trim()) )
					{
						String content = m_MessageEditText.getText().toString();
						m_OnOperationListener.chatSend(content);
						m_MessageEditText.setText("");
						showNoneTextButtons( true );
					}
				}
			}
		});
		
		//========================================================================	
		m_FaceButton.setOnClickListener(new OnClickListener() 
		{
			@Override
			public void onClick(View v) 
			{
	        	m_MyApp.playButtonClick();
	        	onInputButtonClicked();
	        	if( m_CanSend )
	        	{        
	        		setupInputMode( Constants.eChatInputFace );
	        	}
			}
		});
		
		//========================================================================	
		m_GalleryButton.setOnClickListener(new OnClickListener() 
		{
			@Override
			public void onClick(View v) 
			{
	        	m_MyApp.playButtonClick();
	        	onInputButtonClicked();
	        	if( m_CanSend )
	        	{        
	        		setupInputMode( Constants.eChatInputGallery );	        		
	        	}
			}
		});
		
		//========================================================================	
		m_MessageEditText.setOnClickListener(new OnClickListener() 
		{
			@Override
			public void onClick(View v) 
			{
	        	m_MyApp.playButtonClick();
	        	onInputButtonClicked();
	        	if( m_CanSend )
	        	{        		        	
	        		hideFaceLayout();
	        	}
			}
		});	
		
		//========================================================================	
		m_MessageEditText.addTextChangedListener(new TextWatcher() 
		{		
			@Override
			public void onTextChanged(CharSequence s, int start, int before, int count) 
			{
				if(s != null && !"".equals(s.toString().trim()))
				{
					m_MoreTypeButton.setVisibility(View.GONE);
					m_SendButton.setEnabled(true);
					m_SendButton.setVisibility(View.VISIBLE);
					showNoneTextButtons( false );
				}
				else
				{
					m_SendButton.setVisibility(View.GONE);
					showNoneTextButtons( true );
				}
			}
			
			@Override
			public void beforeTextChanged(CharSequence s, int start, int count,
					int after) 
			{			
			}
			
			@Override
			public void afterTextChanged(Editable s) 
			{			
			}
		});
				
		//========================================================================	
		m_MoreTypeButton.setOnClickListener(new OnClickListener() 
		{
			@Override
			public void onClick(View v) 
			{
	        	m_MyApp.playButtonClick();
	        	onInputButtonClicked();
	        	if( m_CanSend )
	        	{        		        	
					hideKeyboard( m_Context );		
					postDelayed(new Runnable() 
					{
						@Override
						public void run() 
						{
							m_MoreTypeLayout.setVisibility(View.VISIBLE);
							m_FaceLayout.setVisibility(View.GONE);
							m_BottomHideLayout.setVisibility(View.VISIBLE);
						}
					}, 50);
	        	}
			}
		});

		//========================================================================
		m_CameraButton.setOnClickListener(new OnClickListener()
		{
			@Override
			public void onClick(View v) 
			{
	        	m_MyApp.playButtonClick();
	        	onInputButtonClicked();
	        	if( m_CanSend )
	        	{        		        	
					hideKeyboard( m_Context );		
					postDelayed(new Runnable() 
					{
						@Override
						public void run() 
						{
							setupInputMode( Constants.eChatInputCamera );
						}
					}, 50);
	        	}
			}
		});

		//========================================================================
		m_GalleryButton.setOnClickListener(new OnClickListener()
		{
			@Override
			public void onClick(View v) 
			{
	        	m_MyApp.playButtonClick();
	        	onInputButtonClicked();
	        	if( m_CanSend && ( null != m_ToGuiUserInputInterface ) )
	        	{        		        	
					hideKeyboard( m_Context );		
					postDelayed(new Runnable() 
					{
						@Override
						public void run() 
						{
							setupInputMode( Constants.eChatInputGallery );
							onGalleryButtonClicked();
						}
					}, 50);
	        	}
			}
		});

	
		//========================================================================
		m_VideoButton.setOnClickListener(new OnClickListener()
		{
			@Override
			public void onClick(View v) 
			{
	        	m_MyApp.playButtonClick();
	        	onInputButtonClicked();
	        	if( m_CanSend )
	        	{        		        	
					hideKeyboard( m_Context );		
					postDelayed(new Runnable() 
					{
						@Override
						public void run() 
						{
							setupInputMode( Constants.eChatInputVideo );
						}
					}, 50);
	        	}
			}
		});

		//========================================================================
		m_AudioButton.setOnClickListener(new OnClickListener()
		{
			@Override
			public void onClick(View v) 
			{
	        	m_MyApp.playButtonClick();
				hideKeyboard( m_Context );
	        	onInputButtonClicked();
	        	if( m_CanSend )
	        	{        		        	
					postDelayed(new Runnable() 
					{
						@Override
						public void run() 
						{
							setupInputMode( Constants.eChatInputAudio );
						}
					}, 50);
	        	}
			}
		});		
		
		//========================================================================	
		m_VidRecordButton.setOnClickListener(new OnClickListener() 
		{
			@Override
			public void onClick(View v) 
			{
	        	m_MyApp.playButtonClick();
	        	onInputButtonClicked();
				if( null != m_ChatState )
				{
	        		if( Constants.eCamVideoModePhotoOnly == m_ECamVideoMode )
	        		{
						if( m_CanSend )
						{
							onCameraPhotoButtonClicked();
						}
						else
						{
							NativeRxFrom.toGuiUserMessage( "User unavailable to send Photo" );
						}
	        		}
	        		else
	        		{
						if( m_ChatState.getIsVideoRecording() )
						{
							if( videoRecord( Constants.eAssetActionRecordEnd ) )
							{
								moveAssetToCompleted();
							}
							
							m_ChatState.setIsVideoRecording( false );
							m_VidRecordButton.setBackgroundResource( R.drawable.button_camcorder_normal );
						}
						else
						{
							if( m_CanSend )
							{
								if( videoRecord( Constants.eAssetActionRecordBegin ) )
								{
									m_ChatState.setIsVideoRecording( true );
									m_VidRecordButton.setBackgroundResource( R.drawable.button_camcorder_red );								
								}
								else
								{
									NativeRxFrom.toGuiUserMessage( "Could not start Video Record" );
								}
							}									
							else
							{
								NativeRxFrom.toGuiUserMessage( "User unavailable to send Video" );
							}
						}	        		
					}
	        	}
			}
		});		
		
		//========================================================================	
		m_VidSourceButton.setOnClickListener(new OnClickListener() 
		{
			@Override
			public void onClick(View v) 
			{
		       	if( null != m_MyApp.getCamCaptureMgr() )
		    	{
		        	m_MyApp.playButtonClick();
		        	onInputButtonClicked();
		        	m_MyApp.getCamCaptureMgr().switchCameras();
		    	}
			}
		});	
		
		//========================================================================	
		m_VidRotateButton.setOnClickListener(new OnClickListener() 
		{
			@Override
			public void onClick(View v) 
			{
		       	if( null != m_MyApp.getCamCaptureMgr() )
		    	{
		       		m_MyApp.playButtonClick();
		       		onInputButtonClicked();
		       		m_MyApp.getCamCaptureMgr().incrementRotation();
		    	}
			}
		});	
		
		//========================================================================	
		m_VidCancelButton.setOnClickListener(new OnClickListener() 
		{
			@Override
			public void onClick(View v) 
			{
		       	if( null != m_MyApp.getCamCaptureMgr() )
		    	{
		        	m_MyApp.playButtonClick();
		        	onInputButtonClicked();
	        		if( Constants.eCamVideoModePhotoOnly == m_ECamVideoMode )
	        		{
	        			onCameraPhotoCancelButtonClicked();
	        		}
	        		else
	        		{
	        			videoRecord( Constants.eAssetActionRecordCancel );
	        		}
		    	}
			}
		});		

		//========================================================================	
		m_SndRecordButton.setOnClickListener(new OnClickListener() 
		{
			@Override
			public void onClick(View v) 
			{
	        	m_MyApp.playButtonClick();
	        	onInputButtonClicked();
				if( null != m_ChatState  )
				{
					if( m_ChatState.getIsAudioRecording() )
					{
						if( audioRecord( Constants.eAssetActionRecordEnd ) )
						{
							moveAssetToCompleted();
						}
						
						m_ChatState.setIsAudioRecording( false );
						m_SndRecordButton.setBackgroundResource( R.drawable.button_microphone_normal );
						if( null != m_SndRecordLabel )
						{
							m_SndRecordLabel.setText( R.string.begin_record );								
						}
						
					}
					else 
					{
						if( m_CanSend )
						{
							if( audioRecord( Constants.eAssetActionRecordBegin ) )
							{
								m_ChatState.setIsVideoRecording( true );
								m_SndRecordButton.setBackgroundResource( R.drawable.button_microphone_red );
								if( null != m_SndRecordLabel )
								{
									m_SndRecordLabel.setText( R.string.stop_record );								
								}															
							}
							else
							{
								NativeRxFrom.toGuiUserMessage( "Could not start Audio Record" );
							}
						}
						else
						{
							NativeRxFrom.toGuiUserMessage( "Did NOT start Audio Record because user unavailable" );								
						}
					}									
				}
			}
		});		

		//========================================================================	
		m_SndCancelButton.setOnClickListener(new OnClickListener() 
		{
			@Override
			public void onClick(View v) 
			{
	        	m_MyApp.playButtonClick();
	        	onInputButtonClicked();
				audioRecord( Constants.eAssetActionRecordCancel );
			}
		});		
	}
	   
	//========================================================================
	public void onOncePer500ms() 
	{
		if( 0 != m_500msTickTock )
		{
			m_500msTickTock = 0;
		}
		else
		{
			m_500msTickTock = 1;
		}

		if( null != m_ChatState )
		{
			if( m_ChatState.getIsVideoRecording() )
			{
				if( null != m_VidRecordButton )
				{
					m_VidRecordButton.setBackgroundResource( ( 0 == m_500msTickTock ) ? R.drawable.button_camcorder_red : R.drawable.button_camcorder_yellow );
				}
			}
			
			if( m_ChatState.getIsAudioRecording() )
			{
				if( null != m_SndRecordButton )
				{
					m_SndRecordButton.setBackgroundResource( ( 0 == m_500msTickTock ) ? R.drawable.button_microphone_red : R.drawable.button_microphone_yellow );
				}
			}
		}	        		
	}
	
	//========================================================================	
	private void onInputButtonClicked()
	{
		if( null != m_ToGuiUserInputInterface )
		{
			m_ToGuiUserInputInterface.toGuiUserInputButtonClicked();			
		}
	}
	
	//========================================================================	
	private void onGalleryButtonClicked()
	{
		AssetGuiInfo assetGuiInfo = generateAssetGuiInfo( Constants.eAssetTypePhoto );
		m_ChatState.setIsVideoRecording( false );		
		if( null != m_ToGuiUserInputInterface )
		{
			m_ToGuiUserInputInterface.toGuiGalleryButtonClicked( assetGuiInfo );			
		}
		
		setupInputMode( Constants.eChatInputSelectMode );
	}
	
	//========================================================================	
	private void onCameraPhotoButtonClicked()
	{
		AssetGuiInfo assetGuiInfo = generateAssetGuiInfo( Constants.eAssetTypePhoto );
		m_ChatState.setIsVideoRecording( false );
		Bitmap snapshotBitmap = m_VidCamView.getLastBitmap();
		if( null != snapshotBitmap )
		{
			if( true == VxImageUtil.saveStdSizeBitmapToFile( snapshotBitmap, assetGuiInfo.getAssetName() ) )
			{
				NativeTxTo.fromGuiAssetAction( getIsPersonalRecorder() ? Constants.eAssetActionAddToAssetMgr : Constants.eAssetActionAddAssetAndSend, assetGuiInfo, 0 );
		 	}
			else
			{
				Toast.makeText( m_Context, R.string.failed_to_create_snapshot, Toast.LENGTH_LONG ).show();
			}
		}
		else
		{
			Toast.makeText( m_Context, R.string.failed_to_create_snapshot, Toast.LENGTH_LONG ).show();
		}
		
		setupInputMode( Constants.eChatInputSelectMode );
	}
	
	//========================================================================	
	private void onCameraPhotoCancelButtonClicked()
	{
		setupInputMode( Constants.eChatInputSelectMode );
	}
	
	//========================================================================	
	public void setUserInputCallback( ToGuiUserInputInterface inputInterface )
	{
		m_ToGuiUserInputInterface = inputInterface;
	}
	
	//========================================================================	
	public void setCanSend( boolean canSend )
	{
		m_CanSend = canSend;
		if( false == canSend )
		{
			setupInputMode( Constants.eChatInputSelectMode );
		}
		
		enableInputSelection( canSend );
	}
	
	//========================================================================	
	void enableInputSelection( boolean enable )
	{
		m_SendButton.setBackgroundResource( 	enable ? R.drawable.green_button_pressed 	: R.drawable.green_button_disabled );
		m_FaceButton.setBackgroundResource( 	enable ? R.drawable.face_btn_normal 		: R.drawable.face_btn_disabled );
		m_CameraButton.setBackgroundResource( 	enable ? R.drawable.button_camera_normal  	: R.drawable.button_camera_disabled );
		m_GalleryButton.setBackgroundResource( 	enable ? R.drawable.button_gallery_normal  	: R.drawable.button_gallery_disabled );		
		m_VideoButton.setBackgroundResource( 	enable ? R.drawable.button_camcorder_normal  : R.drawable.button_camcorder_disabled );
		m_AudioButton.setBackgroundResource( 	enable ? R.drawable.button_microphone_normal  : R.drawable.button_microphone_disabled );	
	}
	
	//========================================================================	
	void showNoneTextButtons( boolean show )
	{
		int visible = show ? View.VISIBLE : View.GONE;
		if( false == show )
		{
			// user started entering text.. check if need to start session
			onInputButtonClicked();
		}
		
		if( null != m_CameraButton )
		{
			m_CameraButton.setVisibility( visible );
		}
		
		if( null != m_VideoButton )
		{
			m_VideoButton.setVisibility( visible );
		}
		
		if( null != m_AudioButton )
		{
			m_AudioButton.setVisibility( visible );
		}
		
		if( null != m_FaceButton )
		{
			m_FaceButton.setVisibility( visible );
		}
	}

	//========================================================================	
	boolean videoRecord( int assetAction )
	{
		if( null == m_ChatState )
		{
			return false;
		}
		
		boolean actionResult = true;
		switch( assetAction )
		{
		case Constants.eAssetActionRecordBegin:
			AssetGuiInfo assetGuiInfo = generateAssetGuiInfo( Constants.eAssetTypeVideo );
			m_ChatState.m_RecordTimer.startTimer();
	    	NativeTxTo.fromGuiMuteMicrophone( false );
			actionResult = NativeTxTo.fromGuiVideoRecord( 	Constants.eVideoRecordStateStartRecording, 
															assetGuiInfo.getCreatorId().m_u64IdHiPart,
															assetGuiInfo.getCreatorId().m_u64IdLoPart,
															m_ChatState.m_FileName );
			m_ChatState.setIsVideoRecording( actionResult );
			if( false == actionResult )
			{
				NativeRxFrom.toGuiUserMessage( "Video Record Failed To Start" );
			}
			
			break;

		case Constants.eAssetActionRecordEnd:
			{
				if( m_ChatState.getIsVideoRecording() )
				{
					m_ChatState.setIsVideoRecording( false );
					double elapsedMs = m_ChatState.m_RecordTimer.elapsedMilliSec();
					if( 1000 > elapsedMs )
					{
						// if only pressed for a second then ignore
						NativeRxFrom.toGuiUserMessage( "Video Record cancel because less than 1 second" );
						NativeTxTo.fromGuiVideoRecord( Constants.eVideoRecordStateCancelRecording,
								m_ChatState.m_AssetGuiInfo.getCreatorId().m_u64IdHiPart,
								m_ChatState.m_AssetGuiInfo.getCreatorId().m_u64IdLoPart,
								m_ChatState.m_FileName );
						actionResult = false;
					}
					else
					{
						NativeTxTo.fromGuiVideoRecord(  Constants.eVideoRecordStateStopRecording,
								m_ChatState.m_AssetGuiInfo.getCreatorId().m_u64IdHiPart,
								m_ChatState.m_AssetGuiInfo.getCreatorId().m_u64IdLoPart,
								m_ChatState.m_FileName );
						long fileLen = VxFileUtil.getFileLen( m_ChatState.m_FileName );
						if( 7000 > fileLen )
						{
							// not long enough to be a recording
							NativeRxFrom.toGuiUserMessage( "Video Record cancel file " + m_ChatState.m_FileName + " too short len " + fileLen );
							VxFileUtil.deleteFile( m_ChatState.m_FileName );
							actionResult = false;
						}
						else
						{	
							m_ChatState.m_AssetGuiInfo.setAssetLength( fileLen );
							m_ChatState.m_AssetGuiInfo.setAssetName( m_ChatState.m_FileName );
							NativeTxTo.fromGuiAssetAction( getIsPersonalRecorder() ? Constants.eAssetActionAddToAssetMgr : Constants.eAssetActionAddAssetAndSend, m_ChatState.m_AssetGuiInfo, 0 );
							actionResult = true;
						}
					}
				}

				setupInputMode( Constants.eChatInputSelectMode );
			}

			break;

		case Constants.eAssetActionRecordCancel:
			hideVideoLayout();
			Toast.makeText( m_Context, R.string.use_camcorder_button_on_left, Toast.LENGTH_LONG ).show();
			setupInputMode( Constants.eChatInputSelectMode );
			actionResult = false;
			break;
		}
		
		return actionResult;
	}
	

	//========================================================================	
	boolean audioRecord( int assetAction )
	{
		if( null == m_ChatState )
		{
			return false;
		}
		
		boolean actionResult = true;
		switch( assetAction )
		{
		case Constants.eAssetActionRecordBegin:
			AssetGuiInfo assetGuiInfo = generateAssetGuiInfo( Constants.eAssetTypeAudio );
			m_ChatState.m_RecordTimer.startTimer();
	    	NativeTxTo.fromGuiMuteMicrophone( false );
			actionResult = NativeTxTo.fromGuiSndRecord( 	Constants.eSndRecordStateStartRecording,
															assetGuiInfo.getCreatorId().m_u64IdHiPart,
															assetGuiInfo.getCreatorId().m_u64IdLoPart,
															m_ChatState.m_FileName );
			m_ChatState.setIsAudioRecording( actionResult );
			if( false == actionResult )
			{
				NativeRxFrom.toGuiUserMessage( "Audio Record Failed To Start" );
			}

			break;

		case Constants.eAssetActionRecordEnd:
			{
				if( m_ChatState.getIsAudioRecording() )
				{
					m_ChatState.setIsAudioRecording( false );
					if( 1000 > m_ChatState.m_RecordTimer.elapsedMilliSec() )
					{
						// if only pressed for a second then ignore
						NativeTxTo.fromGuiSndRecord( Constants.eSndRecordStateCancelRecording, 
								m_ChatState.m_AssetGuiInfo.getCreatorId().m_u64IdHiPart,
								m_ChatState.m_AssetGuiInfo.getCreatorId().m_u64IdLoPart,
								m_ChatState.m_FileName );		
						actionResult = false;
					}
					else
					{
						NativeTxTo.fromGuiSndRecord(  Constants.eSndRecordStateStopRecording, 
								m_ChatState.m_AssetGuiInfo.getCreatorId().m_u64IdHiPart,
								m_ChatState.m_AssetGuiInfo.getCreatorId().m_u64IdLoPart,
								m_ChatState.m_FileName );
						long fileLen = VxFileUtil.getFileLen( m_ChatState.m_FileName );
						if( 2700 > fileLen )
						{
							// not long enough to be a recording
							NativeRxFrom.toGuiUserMessage( "Audio Record Cancel file " + m_ChatState.m_FileName + " too short len " + fileLen );
							VxFileUtil.deleteFile( m_ChatState.m_FileName );
							actionResult = false;
						}
						else
						{
							m_ChatState.m_AssetGuiInfo.setAssetLength( fileLen );
							NativeTxTo.fromGuiAssetAction( m_ChatState.getIsPersonalRecorder() ? Constants.eAssetActionAddToAssetMgr : Constants.eAssetActionAddAssetAndSend, m_ChatState.m_AssetGuiInfo, 0 );
							actionResult = true;
						}
					}
					
					m_SndRecordButton.setBackgroundResource( R.drawable.button_microphone_normal );
					m_SndRecordLabel.setText( R.string.begin_record );								
				}				
					
				setupInputMode( Constants.eChatInputSelectMode );
			}
			
			break;

		case Constants.eAssetActionRecordCancel:
			if( m_ChatState.getIsAudioRecording() )
			{
				m_ChatState.setIsAudioRecording( false );
				NativeTxTo.fromGuiSndRecord( Constants.eSndRecordStateCancelRecording,
						m_ChatState.m_AssetGuiInfo.getCreatorId().m_u64IdHiPart,
						m_ChatState.m_AssetGuiInfo.getCreatorId().m_u64IdLoPart,
						m_ChatState.m_FileName );
			}
			
			m_SndRecordButton.setBackgroundResource( R.drawable.button_microphone_normal );
			m_SndRecordLabel.setText( R.string.begin_record );								
			setupInputMode( Constants.eChatInputSelectMode );
			actionResult = false;
			break;
		}
		
		return actionResult;
	}
	
	//========================================================================	
	AssetGuiInfo generateAssetGuiInfo( short eAssetType )
	{
		m_ChatState.m_AssetGuiInfo = new AssetGuiInfo();
		m_ChatState.m_AssetGuiInfo.generateNewUniqueId();
		m_ChatState.m_AssetGuiInfo.setAssetType( eAssetType );
		m_ChatState.m_AssetGuiInfo.setCreatorId( m_ChatState.getMyId() );
		m_ChatState.m_AssetGuiInfo.setHistoryId( m_ChatState.getFriendId() );
		m_ChatState.m_TimeRecStart = VxTimeUtil.getCurrentTime();
		m_ChatState.m_AssetGuiInfo.setCreationTime( m_ChatState.m_TimeRecStart );
		generateFileName( eAssetType, m_ChatState.m_AssetGuiInfo.getAssetUniqueId(), m_ChatState.m_TimeRecStart );
		m_ChatState.m_AssetGuiInfo.setAssetName( m_ChatState.m_FileName );
		return m_ChatState.m_AssetGuiInfo;
	}

	//========================================================================	
	void generateFileName( int assetType, VxGUID uniqueId, long currentTime )
	{
		//m_FileName = VxGetUserSpecificDataDirectory() + hisOnlineId + "/" + AssetGuiInfo::getSubDirectoryName( assetType );
		String mediaSubDir = "users/";
		if( m_ChatState.getMyId().equals( m_ChatState.getFriendId() ) )
		{
			mediaSubDir = "me/";
		}

		m_ChatState.m_FileName = m_MyApp.getUserXferDir() + mediaSubDir;
		VxFileUtil.createDirectory( m_ChatState.m_FileName );
		m_ChatState.m_FileName += m_ChatState.getMyIdent().getOnlineName();
		m_ChatState.m_FileName += "_";
		m_ChatState.m_FileName += VxTimeUtil.getFileNameCompatibleDateAndTime( VxTimeUtil.getCurrentTime() );
		m_ChatState.m_FileName += "#";
		m_ChatState.m_FileName += uniqueId.toOnlineIdHexString();
		m_ChatState.m_FileName += m_ChatState.m_AssetGuiInfo.getDefaultFileExtension( assetType );	
	}
	
	//========================================================================	
	void moveAssetToCompleted()
	{
	}
	
	//========================================================================	
	public void setIsPersonalRecorder( boolean isPersonalRecorder ) 
	{
		m_ChatState.m_IsPersonalRecorder = isPersonalRecorder;
	}
	
	//========================================================================	
	public boolean getIsPersonalRecorder() 
	{
		return m_ChatState.m_IsPersonalRecorder;
	}
	
	//========================================================================	
	public void setupInputMode( int inputMode ) 
	{
		if( ( Constants.eChatInputSelectMode == inputMode )
			|| ( Constants.eChatInputGallery == inputMode ) )
		{
			showFaceLayout( false );
			m_FaceButton.setVisibility(View.VISIBLE);
			//m_MoreTypeButton.setVisibility(View.VISIBLE); // for now don't need array of gallery/cam/demo but don't want to erase in case need later
			m_CameraButton.setVisibility(View.VISIBLE);
			m_GalleryButton.setVisibility(View.VISIBLE);
			m_VideoButton.setVisibility(View.VISIBLE);
			m_AudioButton.setVisibility(View.VISIBLE);
			hideAudioLayout();
			hideVideoLayout();
		}
		else if( inputMode == Constants.eChatInputText )
		{
			showFaceLayout( false );
			m_FaceButton.setVisibility(View.VISIBLE);		
			//m_MoreTypeButton.setVisibility(View.VISIBLE); // for now don't need array of gallery/cam/demo but don't want to erase in case need later
			m_CameraButton.setVisibility(View.GONE);
			m_GalleryButton.setVisibility(View.GONE);
			m_VideoButton.setVisibility(View.GONE);
			m_AudioButton.setVisibility(View.GONE);		
			hideAudioLayout();
			hideVideoLayout();
		}
		else if( inputMode == Constants.eChatInputCamera )
		{
			showFaceLayout( false );
			m_MoreTypeLayout.setVisibility(View.GONE);
			m_FaceLayout.setVisibility(View.GONE);
			m_BottomHideLayout.setVisibility(View.GONE);
			m_FaceButton.setVisibility(View.GONE);
			//m_MoreTypeButton.setVisibility(View.GONE);
			m_CameraButton.setVisibility(View.GONE);
			m_GalleryButton.setVisibility(View.GONE);
			m_VideoButton.setVisibility(View.GONE);
			m_AudioButton.setVisibility(View.GONE);	
			hideAudioLayout();
			m_VideoInputLayout.setVisibility(View.GONE);
			m_VidCamView.setVisibility(View.VISIBLE);
			m_VideoInputLayout.setVisibility(View.VISIBLE);
			m_VidCamView.setVideoFeedId( m_ChatState.getVideoFeedId() );
			m_VidCamView.setFeedMediaType( Constants.eMediaInputVideoJpgSmall );
			setCamVideoMode( Constants.eCamVideoModePhotoOnly );
			m_VidCamView.requestVideoFeed();
		}
		else if( inputMode == Constants.eChatInputAudio )
		{
			showFaceLayout( false );
			m_MoreTypeLayout.setVisibility(View.GONE);
			m_FaceLayout.setVisibility(View.GONE);
			m_BottomHideLayout.setVisibility(View.GONE);
			m_FaceButton.setVisibility(View.GONE);
			//m_MoreTypeButton.setVisibility(View.GONE);
			m_CameraButton.setVisibility(View.GONE);
			m_GalleryButton.setVisibility(View.GONE);
			m_VideoButton.setVisibility(View.GONE);
			m_AudioButton.setVisibility(View.GONE);					
			m_AudioInputLayout.setVisibility(View.VISIBLE);
			hideVideoLayout();
		}
		else if( inputMode == Constants.eChatInputVideo )
		{
			showFaceLayout( false );
			m_MoreTypeLayout.setVisibility(View.GONE);
			m_FaceLayout.setVisibility(View.GONE);
			m_BottomHideLayout.setVisibility(View.GONE);
			m_FaceButton.setVisibility(View.GONE);
			//m_MoreTypeButton.setVisibility(View.GONE);
			m_CameraButton.setVisibility(View.GONE);
			m_GalleryButton.setVisibility(View.GONE);
			m_VideoButton.setVisibility(View.GONE);
			m_AudioButton.setVisibility(View.GONE);					
			hideAudioLayout();
			m_VidCamView.setVisibility(View.VISIBLE);
			m_VideoInputLayout.setVisibility(View.VISIBLE);
			m_VidCamView.setVideoFeedId( m_ChatState.getVideoFeedId() );
			m_VidCamView.setFeedMediaType( Constants.eMediaInputVideoJpgSmall );
			setCamVideoMode( Constants.eCamVideoModeVideoOnly );
			m_VidCamView.requestVideoFeed();
		}		
		else if( inputMode == Constants.eChatInputFace )
		{
			showFaceLayout( true );
			m_MoreTypeLayout.setVisibility(View.GONE);
			m_FaceLayout.setVisibility(View.GONE);
			m_BottomHideLayout.setVisibility(View.GONE);
			m_FaceButton.setVisibility(View.GONE);
			//m_MoreTypeButton.setVisibility(View.GONE);
			m_CameraButton.setVisibility(View.GONE);
			m_GalleryButton.setVisibility(View.GONE);
			m_VideoButton.setVisibility(View.GONE);
			m_AudioButton.setVisibility(View.GONE);					
			hideAudioLayout();
			hideVideoLayout();
		}		
	}
	
	//========================================================================	
	private void hideVideoLayout()
	{
		if( ( null != m_ChatState ) && m_ChatState.getIsVideoRecording() )
		{
			m_ChatState.setIsVideoRecording( false );
			NativeTxTo.fromGuiVideoRecord(		Constants.eVideoRecordStateCancelRecording,
												m_ChatState.m_AssetGuiInfo.getCreatorId().m_u64IdHiPart,
												m_ChatState.m_AssetGuiInfo.getCreatorId().m_u64IdLoPart,
												m_ChatState.m_FileName );
		}

		m_VideoInputLayout.setVisibility(View.GONE);
		m_VidCamView.setVisibility(View.GONE);
		m_VidCamView.stopVideoFeed();
	}
	
	//========================================================================	
	private void hideAudioLayout()
	{
		if( ( null != m_ChatState ) && m_ChatState.getIsAudioRecording() )
		{
			m_ChatState.setIsAudioRecording( false );
			NativeTxTo.fromGuiSndRecord( Constants.eSndRecordStateCancelRecording,
					m_ChatState.m_AssetGuiInfo.getCreatorId().m_u64IdHiPart,
					m_ChatState.m_AssetGuiInfo.getCreatorId().m_u64IdLoPart,
					m_ChatState.m_FileName );
		}

		m_AudioInputLayout.setVisibility(View.GONE);
	}

	//========================================================================	
	private void setCamVideoMode( int eCamVideoMode )
	{
		m_ECamVideoMode = eCamVideoMode;
		if( Constants.eCamVideoModePhotoOnly == m_ECamVideoMode )
		{
			m_VidRecordButton.setBackgroundResource( R.drawable.button_camera_normal );
			m_VidCancelButton.setBackgroundResource( R.drawable.button_camera_cancel );	
		}
		else
		{
			m_VidRecordButton.setBackgroundResource( R.drawable.button_camcorder_normal );
			m_VidCancelButton.setBackgroundResource( R.drawable.button_camcorder_cancel );	
		}
	}
	
	//========================================================================	
	public void showFaceLayout( boolean show ) 
	{
		hideKeyboard( this.m_Context );

		final boolean showFinal = show;
		postDelayed( new Runnable() 
		{
			@Override
			public void run() 
			{
				//m_MoreTypeLayout.setVisibility(View.GONE);
				m_FaceLayout.setVisibility( showFinal ? View.VISIBLE : View.GONE );
				m_BottomHideLayout.setVisibility( showFinal ? View.VISIBLE : View.GONE );
			}
		}, 50);
	}
	
	//========================================================================	
	public void hideFaceLayout()
	{
		//m_MoreTypeLayout.setVisibility(View.GONE);
		m_FaceLayout.setVisibility(View.GONE);
		m_BottomHideLayout.setVisibility(View.GONE);
	}
	
	//========================================================================	
	public void hide()
	{
		m_BottomHideLayout.setVisibility(View.GONE);
		hideKeyboard( m_Context );
	}
	
	//========================================================================	
	public static void hideKeyboard(Context context)
	{
		Activity activity = (Activity) context;
		if(activity != null)
		{
			InputMethodManager imm = (InputMethodManager) activity.getSystemService( Context.INPUT_METHOD_SERVICE );
			if( imm.isActive() && activity.getCurrentFocus() != null )
			{
				imm.hideSoftInputFromWindow( activity.getCurrentFocus().getWindowToken(), 0 );
			}
		}
	}

	//========================================================================	
	public static void showKeyboard(Context context) 
	{
		Activity activity = (Activity) context;
		if( activity != null )
		{
			InputMethodManager imm = (InputMethodManager) activity.getSystemService( Context.INPUT_METHOD_SERVICE );
			imm.showSoftInputFromInputMethod(activity.getCurrentFocus().getWindowToken(), 0);
			imm.toggleSoftInput(0, InputMethodManager.HIDE_NOT_ALWAYS);
		}
	}

	//========================================================================	
	public ChatOnOperationListener getOnOperationListener() 
	{
		return m_OnOperationListener;
	}

	//========================================================================	
	public void setOnOperationListener( ChatOnOperationListener onOperationListener ) 
	{
		this.m_OnOperationListener = onOperationListener;
		m_FaceCategroyAdapter.setOnOperationListener( onOperationListener );
	}

	//========================================================================	
	public Map<Integer, ArrayList<String>> getFaceData() 
	{
		return m_FaceData;
	}

	//========================================================================	
	public void setFaceData(Map<Integer, ArrayList<String>> faceData) 
	{
		this.m_FaceData = faceData;
		m_FaceCategroyAdapter.setData(faceData);
		m_FaceCategroyViewPager.setAdapter( m_FaceCategroyAdapter );
		m_FaceCategroyTabs.setViewPager(m_FaceCategroyViewPager);
		if( faceData.size() < 2 )
		{
			m_FaceCategroyTabs.setVisibility(GONE);
		}
	}

	//========================================================================	
	public List<ChatOption> getFunctionData() 
	{
		return m_FunctionData;
	}

	//========================================================================	
	public void setFunctionData(List<ChatOption> functionData) 
	{
		this.m_FunctionData 	= functionData;
		m_PointViews 			= new ArrayList<ImageView>();
		m_FunctionGridViewList 	= new ArrayList<View>(); 
		
		for (int x = 0; x < (functionData.size() % 8 == 0 ? functionData.size() / 8 : (functionData.size() / 8) + 1); x++) 
		{
			GridView view = new GridView(m_Context);
			ChatFunctionAdapter functionAdapter = new ChatFunctionAdapter(m_Context, 
					functionData.subList(x * 8, 
							((x + 1) * 8) > functionData.size() ? functionData.size() : ((x + 1) * 8)));
			view.setAdapter(functionAdapter);
			// faceAdapters.add(emojiAdapter);

			view.setOnItemClickListener(new OnItemClickListener() 
			{
				@Override
				public void onItemClick(AdapterView<?> parent, View view,
						int position, long id) 
				{
					if( m_OnOperationListener != null ) 
					{
						m_OnOperationListener.chatSelectedFuncation(position);
					}
				}
			});
			
			view.setNumColumns(4);

			view.setBackgroundColor(Color.TRANSPARENT);
			view.setHorizontalSpacing(1);
			view.setVerticalSpacing(1);
			view.setStretchMode(GridView.STRETCH_COLUMN_WIDTH);
			view.setCacheColorHint(0);
			view.setPadding(5, 0, 5, 0);
			view.setSelector(new ColorDrawable(Color.TRANSPARENT));
			view.setLayoutParams(new LayoutParams(LayoutParams.MATCH_PARENT,
					LayoutParams.WRAP_CONTENT));
			view.setGravity(Gravity.CENTER);

			m_FunctionGridViewList.add(view);

			ImageView imageView = new ImageView( m_Context );
			imageView.setBackgroundResource(R.drawable.point_normal);
			LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(
					new ViewGroup.LayoutParams(LayoutParams.WRAP_CONTENT,
					LayoutParams.WRAP_CONTENT));
			layoutParams.leftMargin = 10;
			layoutParams.rightMargin = 10;
			layoutParams.width = 8;
			layoutParams.height = 8;
			m_PagePointLayout.addView(imageView, layoutParams);
			if (x == 0) 
			{
				imageView.setBackgroundResource(R.drawable.point_selected);
			}
			
			m_PointViews.add(imageView);
		}

//		PagerAdapter facePagerAdapter = new FacePagerAdapter(functionGridViewList);
		m_FuctionViewPager.setAdapter(new PagerAdapter() 
		{
			@Override
			public int getCount() 
			{
				return m_FunctionGridViewList.size();
			}

			@Override
			public boolean isViewFromObject(View arg0, Object arg1) 
			{
				return arg0 == arg1;
			}

			@Override
			public int getItemPosition(Object object) 
			{
				return super.getItemPosition(object);
			}

			@Override
			public void destroyItem(View arg0, int arg1, Object arg2) 
			{
				System.out.println(arg0 + "  " + arg1 + "  " + arg2);
				((ViewPager) arg0).removeView(m_FunctionGridViewList.get(arg1));
			}

			@Override
			public Object instantiateItem(View arg0, int arg1) 
			{
				((ViewPager) arg0).addView(m_FunctionGridViewList.get(arg1));
				return m_FunctionGridViewList.get(arg1);
			}			
		});		
	}
}
