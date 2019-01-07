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

import java.util.ArrayList;
import java.util.concurrent.Semaphore;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;

import android.app.Activity;
import android.content.Intent;
import android.media.AudioManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;

public class ActivityPersonalRecorder extends AppCompatActivity implements AssetCallbackInterface, ToGuiUserInputInterface, ToGuiMessageInterface
{
	private static final String LOG_TAG = "PersonalRecorder:";

	public 	MyApp 						m_MyApp = null;
	private ActivityPersonalRecorderState m_ActivityState = null;
	private ChatMessageInputToolBox 	m_InputBox;
	private ListView 					m_ListView;
	private ChatMessageAdapter 			m_ChatAdapter;
		
	//private Semaphore 				m_oMutex = new Semaphore(1); 
	public final  ArrayList<String> 	m_oMessages 				= new  ArrayList<String>();
	private Button 						m_CloseButton 				= null;

	private TextView					m_StatusMsgLabel			= null;
	private TextView 					m_TotalCamClientsText 		= null;

	private AssetGuiInfo 				m_GalleryPickAsset			= null;
	private Handler 					m_MyEventHandler 			= null; 
	protected boolean					m_IsDestroyed				= false;
 	private boolean						m_NeedMoveToBottomOfList	= false;

	//========================================================================
	@Override
	public void onCreate(Bundle savedInstanceState) 
	{
		Log.i( LOG_TAG, "onCreate" );
 		m_MyApp 							= (MyApp) this.getApplication();

	    setContentView( R.layout.activity_personal_recorder ); 
	    super.onCreate(savedInstanceState);		
		ActionBar actionBar = getSupportActionBar();
		if( null != actionBar )
		{
			actionBar.hide();
		}
		
 		TextView titleText = (TextView)this.findViewById( R.id.label_title );
 		if( null != titleText )
 		{
 			titleText.setText( R.string.activity_personal_recorder_title ); 			
 		}
  		
        this.setVolumeControlStream(AudioManager.STREAM_MUSIC);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        this.getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN); // keep keyboard from popping up
 
        m_TotalCamClientsText 				= (TextView)this.findViewById( R.id.total_cam_clients_text );
        m_StatusMsgLabel 					= (TextView)this.findViewById( R.id.status_msg_label );
 
 		m_ActivityState						= m_MyApp.getPersonalRecorderState();
 		m_ActivityState.setIsPersonalRecorder(  true );
 		m_ActivityState.m_Activity = this;
     
		initMessageInputToolBox();
		initListView();
		 			
		Log.i(LOG_TAG, "onCreateCalled");
        m_CloseButton = (Button)this.findViewById(R.id.button_close);
        if( null != m_CloseButton )
        {
 	        m_CloseButton.setOnClickListener( new OnClickListener() 
 	        {
 	        	public void onClick(View v) 
 			 	{
 	  			   	m_MyApp.playButtonClick();
			 		finish();
 			 	}
 	        });	
        }
   
        setToGuiMessageReadyState( this );
    	setActivityReadyState( this );
    	NativeTxTo.fromGuiQuerySessionHistory( m_ActivityState.getFriendId().getOnlineIdHiPart(), m_ActivityState.getFriendId().getOnlineIdLoPart() );

    	if( null != m_MyApp.getCamCaptureMgr() )
    	{
    		m_MyApp.getCamCaptureMgr().setCamActivity( ActivityPersonalRecorder.this, R.id.cam_preview_frame, R.id.no_preview_image );
    	}
    	
		m_InputBox.setupInputMode( Constants.eChatInputSelectMode ); // force turn off request for video feed
		m_InputBox.setCanSend( true );// personal recorder never actually sends but we need to set flag so buttons are enabled
		m_MyEventHandler = new Handler() 
		{
		    @Override
		    public void handleMessage(Message msg) 
		    {
		    	switch(msg.what)
		    	{
		    	case Constants.MY_EVENT_ONCE_PER_SEC:
		    		//Log.i( LOG_TAG, "Rxed MY_EVENT_ONCE_PER_SEC" );
		    		//onOncePerSecond();
		    		//if( ( false == m_MyApp.getIsAppShuttingDown() )
		    		//	&& ( false == m_IsDestroyed ) )
		    		//{
		    		//	m_MyEventHandler.sendEmptyMessageDelayed( Constants.MY_EVENT_ONCE_PER_SEC, 1000 );
		    		//}
		    		
		    		break;    		
		    		
		    	case Constants.MY_EVENT_ONCE_PER_500MS:
		    		//Log.i( LOG_TAG, "Rxed MY_EVENT_ONCE_PER_500MS" );
		    		if( ( false == m_MyApp.getIsAppShuttingDown() )
		    			&& ( false == m_IsDestroyed ) )
		    		{
		    			onOncePer500ms();
			    			
		    			m_MyEventHandler.sendEmptyMessageDelayed( Constants.MY_EVENT_ONCE_PER_500MS, 500 );
		    		}
		    		
		    		break;    		
		    	}
		    	
		    	super.handleMessage(msg);
		    }
		};

		m_MyEventHandler.sendEmptyMessageDelayed( Constants.MY_EVENT_ONCE_PER_500MS, 500 );
	}
    
	//========================================================================
	public void onOncePer500ms() 
	{
		if( null != m_InputBox )
		{
			m_InputBox.onOncePer500ms();
		}
		
		if( m_NeedMoveToBottomOfList )
		{
	    	if( 0 != m_ListView.getBottom() )
	    	{
	    		Log.e( LOG_TAG, "ListView Bottom " + m_ListView.getBottom() );
	    		m_NeedMoveToBottomOfList = false;
	    		m_ListView.setSelection( m_ListView.getBottom() ); 
	    	}				
		}
    };

	//============================================================================
	boolean checkForSendAccess( boolean sendOfferIfPossible )
	{
		return true; // personal recorder never actually sends
	}
	 
	//========================================================================
    @Override
    protected void onPause() 
    {
    	m_InputBox.setupInputMode( Constants.eChatInputSelectMode ); // force turn off request for video feed and stop vid recodings
    	//setActivityReadyState( null );
     	super.onPause();    	
        m_MyApp.setActivityPause( true );
    }
	 
	//========================================================================
    @Override
    protected void onResume() 
    {
        //m_MyApp.setActivityPause( false );
        super.onResume();    	
    	setActivityReadyState( this );
    }
    
	//========================================================================
    @Override
    protected void onStop() 
    {
    	VxGUID myId = m_MyApp.getMyOnlineId();
    	NativeTxTo.fromGuiWantMediaInput( myId.m_u64IdHiPart, myId.m_u64IdLoPart, Constants.eMediaInputVideoJpgSmall, false );
    	setToGuiMessageReadyState( null );
    	setActivityReadyState( null );
    	m_ChatAdapter.activityOnStop();
     	super.onStop();    	
    }   
   
 	//========================================================================
    public void toGuiPlayVideoFrame( VxGUID guidId, byte[] pu8Jpg, int jpgDataLen, int motion0to100000 )
    {
    	
    }
    
 	//========================================================================
    protected void setToGuiMessageReadyState( Activity curActivity )
    {
		try 
		{
			if( ( null == curActivity ) || ( null == m_StatusMsgLabel ) )
			{
				NativeRxFrom.wantToGuiMessageClient( this, false );
			}
			else
			{
				NativeRxFrom.wantToGuiMessageClient( this, true );
			}
		} 
		catch (InterruptedException e) 
		{
			e.printStackTrace();
		}
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
		
 		m_MyApp.m_ActivityPersonalRecorder = (ActivityPersonalRecorder) curActivity;
    }
  
	//========================================================================
    @Override
    public void onDestroy() 
    {
    	m_IsDestroyed = true;
		m_MyApp.m_ActivityPersonalRecorder = null;
  		Log.d(LOG_TAG, "onDestroy ");  
    	super.onDestroy();    	
    }
    
	//========================================================================
	private void initMessageInputToolBox()
	{
		m_InputBox = (ChatMessageInputToolBox) findViewById(R.id.chatMessageInputToolBox);
		m_InputBox.setOnOperationListener( new ChatOnOperationListener() 
		{			
			@Override
			public void chatSend( String content ) 
			{				
				System.out.println("===============" + content);	
				AssetGuiInfo assetInfo = createAndFillNewAssetGuiInfo();
				assetInfo.setChatText( content );
				NativeTxTo.fromGuiAssetAction( m_ActivityState.getIsPersonalRecorder() ? Constants.eAssetActionAddToAssetMgr : Constants.eAssetActionAddAssetAndSend, assetInfo, 0 );
				m_InputBox.setupInputMode( Constants.eChatInputSelectMode );
				m_ListView.setSelection(m_ListView.getBottom());
			}
			
			@Override
			public void chatSelectedFace(String content) 
			{	
				System.out.println("===============" + content);
				AssetGuiInfo assetInfo = createAndFillNewAssetGuiInfo();
				assetInfo.setChatFace( content );				
				NativeTxTo.fromGuiAssetAction( m_ActivityState.getIsPersonalRecorder() ? Constants.eAssetActionAddToAssetMgr : Constants.eAssetActionAddAssetAndSend, assetInfo, 0 );
				m_InputBox.setupInputMode( Constants.eChatInputSelectMode );
				m_ListView.setSelection(m_ListView.getBottom());
			}
						
			@Override
			public void chatSelectedFuncation(int index) 
			{	
				System.out.println("===============" + index);
				
				switch (index) {
				case 0:
					//do some thing
					break;
				case 1:
					//do some thing
					break;
					
				default:
					break;
				}
				
				Toast.makeText(ActivityPersonalRecorder.this, "Do some thing here, index :" + index, 1000).show();				
			}
			
		});
		
		
		ArrayList<String> faceNameList = new ArrayList<String>();
		for( int x = 1; x <= 9; x++ )
		{
			faceNameList.add("face"+x);
		}
		
		ArrayList<String> faceNameList1 = new ArrayList<String>();
		for(int x = 10; x <= 19; x++)
		{
			faceNameList1.add("face"+x);
		}
		
		
		ArrayList<String> faceNameList2 = new ArrayList<String>();
		for(int x = 20; x <= 32; x++)
		{
			faceNameList2.add("face"+x);
		}
		
		Map<Integer, ArrayList<String>> faceData = new HashMap<Integer, ArrayList<String>>();
		faceData.put(R.drawable.face_catagory3, faceNameList1);
		faceData.put(R.drawable.face_catagory2, faceNameList2 );
		faceData.put(R.drawable.face_catagory1, faceNameList );
		m_InputBox.setFaceData(faceData);
		
		
		List<ChatOption> functionData = new ArrayList<ChatOption>();
		for(int x = 0; x < 5; x++)
		{
			ChatOption takePhotoOption = new ChatOption(this, "Take", R.drawable.take_photo);
			ChatOption galleryOption = new ChatOption(this, "Gallery", R.drawable.gallery);
			functionData.add(galleryOption);
			functionData.add(takePhotoOption);
		}
		
		m_InputBox.setFunctionData( functionData );
		m_InputBox.setInputState( m_ActivityState );
		//m_InputBox.setupInputMode( Constants.eChatInputVideo );
		m_InputBox.setupInputMode( Constants.eChatInputSelectMode );
	}
	
	//========================================================================
	private AssetGuiInfo createAndFillNewAssetGuiInfo()
	{
		AssetGuiInfo assetInfo = new AssetGuiInfo();
		fillAssetGuiInfo( assetInfo );
		return assetInfo;
	}
	
	//========================================================================
	private void fillAssetGuiInfo( AssetGuiInfo assetInfo )
	{
		assetInfo.m_CreationTime = VxTimeUtil.getCurrentTime();
		assetInfo.setHistoryId( m_ActivityState.getFriendId() );
		assetInfo.setCreatorId( m_ActivityState.getMyId() );
		assetInfo.generateNewUniqueId();
	}
	
	//========================================================================
	private void addChatMessage( ChatMessage message )
	{		
		final Semaphore addChatMsgListMutex = new Semaphore(1); 
		final  ArrayList<ChatMessage> messageList = new  ArrayList<ChatMessage>();
		try 
		{
			addChatMsgListMutex.acquire();
		} 
		catch( InterruptedException e ) 
		{
			e.printStackTrace();
		}	

		messageList.add( message );
		addChatMsgListMutex.release();
		
		try 
		{
			runOnUiThread(new Runnable() 
			{	
				@Override
				public void run() 
				{
					try 
					{
						addChatMsgListMutex.acquire();
					} 
					catch( InterruptedException e ) 
					{
						e.printStackTrace();
					}	
					
			    	for( ChatMessage chatMsg:  messageList )
			    	{
			    		m_ChatAdapter.addChatMsg(chatMsg);
			    	}

			    	messageList.clear();
			    	addChatMsgListMutex.release();
			    	if( 0 != m_ListView.getBottom() )
			    	{
			    		Log.e( LOG_TAG, "ListView Bottom " + m_ListView.getBottom() );
			    		m_ListView.setSelection( m_ListView.getBottom() ); 
			    	}
			    	else
			    	{
			    		m_NeedMoveToBottomOfList = true;
			    	}
				}
			});
		} 
		catch (Exception e) 
		{
			e.printStackTrace();
		}
	}
	
	//========================================================================
	private void removeChatMessage( VxGUID messageId )
	{		
		final Semaphore removeChatMsgListMutex = new Semaphore(1); 
		final  ArrayList<VxGUID> messageIdList = new  ArrayList<VxGUID>();
		try 
		{
			removeChatMsgListMutex.acquire();
		} 
		catch( InterruptedException e ) 
		{
			e.printStackTrace();
		}	

		messageIdList.add( messageId );
		removeChatMsgListMutex.release();
		
		new Thread(new Runnable() 
		{			
			@Override
			public void run() 
			{
				try 
				{
					runOnUiThread(new Runnable() 
					{	
						@Override
						public void run() 
						{
							try 
							{
								removeChatMsgListMutex.acquire();
							} 
							catch( InterruptedException e ) 
							{
								e.printStackTrace();
							}	
							
					    	for( VxGUID chatMsgId:  messageIdList )
					    	{
					    		m_ChatAdapter.removeChatMessageById(chatMsgId);
					    	}

					    	removeChatMsgListMutex.release();
							m_ChatAdapter.notifyDataSetChanged();
						}
					});
				} 
				catch (Exception e) 
				{
					e.printStackTrace();
				}
			}
		}).start();
	}
	
	//========================================================================
	private void initListView()
	{
		m_ListView = (ListView) findViewById(R.id.chatMessageListview);		
		List<ChatMessage> messageList = new ArrayList<ChatMessage>();		
		m_ChatAdapter = new ChatMessageAdapter( m_MyApp, this, messageList);
		m_ListView.setAdapter(m_ChatAdapter);
		m_ListView.setOnTouchListener(new OnTouchListener() 
		{
			@Override
			public boolean onTouch(View v, MotionEvent event) 
			{
				m_InputBox.hide();
				return false;
			}
		});	
		
		m_ChatAdapter.notifyDataSetChanged();
	}

	//========================================================================
	@Override
	public void toGuiAssetAdded( AssetGuiInfo assetInfo ) 
	{
		if( null == m_ActivityState )
			return;
		if( assetInfo.getHistoryId().equals(m_ActivityState.getFriendIdent().getMyOnlineId() ) )
		{
			ChatMessage message = new ChatMessage( m_ActivityState, assetInfo, m_ChatAdapter );
			message.setIsSend( assetInfo.getCreatorId().equals( m_ActivityState.getMyId() ) );
			addChatMessage( message );
		}	
	}

	//========================================================================
	@Override
	public void toGuiSessionHistory( AssetGuiInfo assetInfo ) 
	{
		if( null == m_ActivityState )
			return;
		if( assetInfo.getHistoryId().equals( m_ActivityState.getFriendIdent().getMyOnlineId() ) )
		{
			ChatMessage message = new ChatMessage( m_ActivityState, assetInfo, m_ChatAdapter );
			message.setIsSend( assetInfo.getCreatorId().equals( m_ActivityState.getMyId() ) );
			addChatMessage( message );
		}			
	}

	//========================================================================
	@Override
	public void toGuiAssetAction( int assetAction, VxGUID assetId, int actionParam ) 
	{
		try 
		{
			final int assetActionFinal 		= assetAction;
			final VxGUID assetIdFinal 		= assetId;
			final int actionParamFinal 		= actionParam;
			
			runOnUiThread(new Runnable() 
			{	
				@Override
				public void run() 
				{
					if( ( Constants.eAssetActionShreadFile == assetActionFinal )
							|| ( Constants.eAssetActionRemoveFromAssetMgr == assetActionFinal )
							|| ( Constants.eAssetActionRemoveFromHistory == assetActionFinal ) )
					{
						removeChatMessage( assetIdFinal );
						m_ChatAdapter.notifyDataSetChanged();
					}
					else
					{
						m_ChatAdapter.doToGuiAssetAction( assetActionFinal, assetIdFinal, actionParamFinal );
					}
				}
			});
		} 
		catch (Exception e) 
		{
			e.printStackTrace();
		}
	}
	

 	//========================================================================
	@Override
	public void toGuiUserInputButtonClicked()
	{
	}

 	//========================================================================
	@Override
	public void toGuiGalleryButtonClicked( AssetGuiInfo assetGuiInfo )
	{
		m_GalleryPickAsset = assetGuiInfo;
    	Intent myIntent = new Intent( this, ActivityPickImage.class );
    	myIntent.putExtra( Constants.PARAM_FILE_NAME, m_GalleryPickAsset.getAssetName() ); 	
    	startActivityForResult( myIntent, Constants.ACTIVITY_PICK_IMAGE );
	}

	//========================================================================
	@Override
	public void onActivityResult(int requestCode, int resultCode, Intent data) 
	{
		super.onActivityResult(requestCode, resultCode, data);
		Log.d(LOG_TAG, "onActivityResult result code " + resultCode);
			
		switch (requestCode) 
		{
		case Constants.ACTIVITY_PICK_IMAGE:
			if (resultCode == Activity.RESULT_OK) 
		    {
				Log.d( LOG_TAG, "onActivityResult ACTIVITY_PICK_IMAGE" );
				Bundle extras = data.getExtras(); 
		        if( null != extras ) 
		        { 
		        	String fileName 	= extras.getString( Constants.PARAM_FILE_NAME );
		        	long fileLen		= VxFileUtil.getFileLen( fileName );
		        	if( 0 != fileLen )
		        	{
		        		if( null != m_GalleryPickAsset )
		        		{
		        			Log.d(LOG_TAG, "Choose Image " +  fileName + " len " + fileLen );
		        			m_GalleryPickAsset.setAssetName( fileName );
		        			m_GalleryPickAsset.setAssetLength( fileLen );	        			
							NativeTxTo.fromGuiAssetAction( Constants.eAssetActionAddToAssetMgr, m_GalleryPickAsset, 0 );
		        		}
		        		else
		        		{
		        			Log.d(LOG_TAG, "NULL m_GalleryPickAsset in Choose Image " +  fileName);
				        	Toast.makeText( this, R.string.error_bad_activity_param, Toast.LENGTH_LONG ).show();
		        		}
		        	}
			        else
			        {
			        	Log.d(LOG_TAG, "0 File Len in Choose Image " +  fileName);
			        	Toast.makeText( this, R.string.error_file_does_not_exist, Toast.LENGTH_LONG ).show();
			        }
		        }
		        else
		        {
					Log.d(LOG_TAG, "NULL EXTRA in Choose Image" );
		        	Toast.makeText( this, R.string.error_bad_activity_param, Toast.LENGTH_LONG ).show();
		        }
		    }
			else
			{
				Log.d(LOG_TAG, "Choose Image Canceled By User" );
				Toast.makeText( this, R.string.choose_image_canceled_by_user, Toast.LENGTH_SHORT ).show();
			}
			
			break;
		default:
			break;
		}
		
		setCamCaptureActivity( this );
	}
	   
	//========================================================================
    protected void setCamCaptureActivity( Activity curActivity )
    {
       	if( null != m_MyApp.getCamCaptureMgr() )
    	{
       		m_MyApp.getCamCaptureMgr().setCamActivity( curActivity, R.id.cam_preview_frame, R.id.no_preview_image );
    	}
    }


	//========================================================================
	void setStatusMessage( String strMsgIn ) 
	{
		if( null != m_StatusMsgLabel )
		{
			final String strMsg = strMsgIn;
			runOnUiThread(new Runnable() {
				public void run() 
				{
					m_StatusMsgLabel.setText(strMsg);
				}
			});
		}
	}
	
  	//========================================================================
	@Override
	public void toGuiStatusMessage( String statusMsg )
	{
		setStatusMessage( statusMsg );
	}

  	//========================================================================
	@Override
	public void toGuiUserMessage( String userMsg )
	{
		if( null != m_StatusMsgLabel )
		{
			m_StatusMsgLabel.setText( userMsg );
		}		
	}

  	//========================================================================
	@Override
	public void toGuiUserMessage( int stringResId )
	{
		if( null != m_StatusMsgLabel )
		{
			m_StatusMsgLabel.setText( stringResId );
		}		
	}

  	//========================================================================
	@Override
	public void doToGuiPluginStatus( int ePluginType, int statusType, int statusValue )
	{
		if( ( Constants.ePluginTypeCamServer == ePluginType )
			&& ( 1 == statusType )
			&& ( null != m_TotalCamClientsText ) )
		{
			if( statusValue < 0 )
			{
				m_TotalCamClientsText.setText( "" );
			}
			else
			{
				String valueAsText = String.format( Locale.getDefault(), "%d", statusValue ); 
				m_TotalCamClientsText.setText( valueAsText );
			}		
		}	
	}

  	//========================================================================
	@Override
	public void toGuiPluginLogMessage( int ePluginType, String strLogMsg )
	{
	}

};