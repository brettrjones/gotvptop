// Derivative of Android Chat Widget https://github.com/ijarobot/ ( Apache License )
package com.p2pgotv.gotvstation;

import java.util.Date;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.Toast;

public class ChatMessage implements AssetCallbackInterface
{
	private static final String LOG_TAG = "ChatMessage:";
	
	public final static int 	MSG_STATE_SENDING 		= 0;
	public final static int 	MSG_STATE_SUCCESS 		= 1;
	public final static int 	MSG_STATE_FAIL 			= 2;
	
	public ChatSessionState 	m_SessionState			= null;
	public AssetGuiInfo 		m_AssetGuiInfo			= null;
	public int 					m_AssetSendProgress 	= 0;
	private boolean 			m_IsSend				= false;
	
	private Button 				m_CamPlayButton			= null;
	private SeekBar 			m_CamPlayPosSlider		= null;
	
	private Button 				m_AudioPlayButton		= null;
	private SeekBar 			m_AudioPlayPosSlider	= null;
	
	private Button 				m_ShredAssetButton		= null;
	private Button 				m_AssetResendButton		= null;

	private boolean				m_SliderIsPressed   	= false;
	private boolean				m_IsPlaying   			= false;
	private ChatMessageAdapter 	m_ChatAdapter			= null;
	public	Activity			m_Activity				= null;
	public boolean				m_XferProgressIsVisible   		= false;
	public boolean				m_XferProgressShouldBeVisible   = false;
	ChatPhotoView 				m_PhotoView						= null;
	ChatCamPlaybackView 		m_VidPlaybackView				= null;
	ImageView 					m_MicImageView					= null;
	


	//========================================================================
	public ChatMessage( ChatSessionState 		sessionState,
						AssetGuiInfo 			assetInfo,
						ChatMessageAdapter 		chatAdapter )
	{
		super();
		m_SessionState 			= sessionState;
		m_Activity				= sessionState.m_Activity;
		m_ChatAdapter			= chatAdapter;
		setAssetGuiInfo( assetInfo );
		m_IsSend	= true;
		if( getAssetGuiInfo().getHistoryId() == m_SessionState.getMyId() )
		{
			m_IsSend = false;
		}
	}
	
	//========================================================================
	public long getCreationTime()
	{
		return m_AssetGuiInfo.getCreationTime();
	}
	
	//========================================================================
	public void setAudioControls( Button audioPlayButton, SeekBar audioSeekBar, ImageView micImageView )
	{
		m_AudioPlayButton		= audioPlayButton;
		this.m_AudioPlayButton.setOnClickListener(new OnClickListener() {
			public void onClick(View v) 
			{
	        	//m_MyApp.playButtonClick();
				onPlayButClick(v);
			}
		});
		
		m_AudioPlayPosSlider = audioSeekBar;
		m_AudioPlayPosSlider.setOnSeekBarChangeListener(new OnSeekBarChangeListener() 
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
		
		m_MicImageView = micImageView;
		if( null != m_MicImageView )
		{
			this.m_MicImageView.setOnClickListener(new OnClickListener() 
			{
				public void onClick(View v) 
				{
					m_ChatAdapter.onAudioPlaybackViewClick( m_AssetGuiInfo );
				}
			});
		}
		
		setReadyForCallbacks( true );		
	}
	
	//========================================================================
	public void setPhotoVideoControls( ChatPhotoView photoView, ChatCamPlaybackView vidPlaybackView )
	{
		if( Constants.eAssetTypePhoto == getAssetGuiInfo().getAssetType() )
		{
			m_PhotoView = photoView;
			if( null != m_PhotoView )
			{
				this.m_PhotoView.setOnClickListener(new OnClickListener() 
				{
					public void onClick(View v) 
					{
						m_ChatAdapter.onPhotoViewClick( m_AssetGuiInfo );
					}
				});
			}
		}
		
		
		if( Constants.eAssetTypeVideo == getAssetGuiInfo().getAssetType() )
		{
			m_VidPlaybackView = vidPlaybackView;
			if( null != m_VidPlaybackView )
			{
				this.m_VidPlaybackView.setOnClickListener(new OnClickListener() 
				{
					public void onClick(View v) 
					{
						m_ChatAdapter.onVidPlaybackViewClick( m_AssetGuiInfo );
					}
				});
			}
		}		
	}
	
	//========================================================================
	public void setCamControls( Button camPlayButton, SeekBar camSeekBar )
	{
		m_CamPlayButton		= camPlayButton;
		this.m_CamPlayButton.setOnClickListener(new OnClickListener() {
			public void onClick(View v) 
			{
	        	//m_MyApp.playButtonClick();
				onPlayButClick(v);
			}
		});
		
		m_CamPlayPosSlider = camSeekBar;
		m_CamPlayPosSlider.setOnSeekBarChangeListener(new OnSeekBarChangeListener() 
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
		
		setReadyForCallbacks( true );	
	}
	
	//========================================================================
	public void setShredAssetButton( Button shredButton )
	{
		m_ShredAssetButton = shredButton;
		this.m_ShredAssetButton.setOnClickListener(new OnClickListener() 
		{
			public void onClick(View v) 
			{
				onShredAssetButClick(v);
			}
		});			
	}
	
	//========================================================================
	public void setAssetResendButton( Button resendButton )
	{
		m_AssetResendButton = resendButton;
		this.m_AssetResendButton.setOnClickListener(new OnClickListener() 
		{
			public void onClick(View v) 
			{
				onAssetResendButClick(v);
			}
		});			
	}
	
	//========================================================================
	public VxGUID getAssetId() 
	{
		return getAssetGuiInfo().getAssetUniqueId();
	}

	//========================================================================
	public short getAssetType() 
	{
		return getAssetGuiInfo().getAssetType();
	}

	//========================================================================
	public void setAssetType( short assetType )
	{
		this.getAssetGuiInfo().setAssetType( assetType );
	}

	//========================================================================
	public String getAssetName() 
	{
		return getAssetGuiInfo().getAssetName();
	}

	//========================================================================
	public void setSendState( int sendState ) 
	{
		getAssetGuiInfo().setAssetSendState( sendState );
	}

	//========================================================================
	public int getSendState() 
	{
		return getAssetGuiInfo().getAssetSendState();
	}

	//========================================================================
	public String getFromUserName() 
	{
		if( m_IsSend )
		{
			return m_SessionState.getMyIdent().getOnlineName();			
		}
		else
		{
			return m_SessionState.getFriendIdent().getOnlineName();						
		}
	}

	//========================================================================
	public String getFromUserAvatar() 
	{
		if( m_IsSend )
		{
			return m_SessionState.getMyAvatar();			
		}
		else
		{
			return m_SessionState.getFriendAvatar();						
		}
	}

	//========================================================================
	public String getToUserName() 
	{
		if( m_IsSend )
		{
			return m_SessionState.getFriendIdent().getOnlineName();						
		}
		else
		{
			return m_SessionState.getMyIdent().getOnlineName();			
		}
	}

	//========================================================================
	public String getToUserAvatar() 
	{
		if( m_IsSend )
		{
			return m_SessionState.getFriendAvatar();						
		}
		else
		{
			return m_SessionState.getMyAvatar();			
		}
	}

	//========================================================================
	public void setChatText( String text ) 
	{
		getAssetGuiInfo().setChatText( text );
	}

	//========================================================================
	public String getChatText() 
	{
		return getAssetGuiInfo().getChatText();
	}

	//========================================================================
	public void setChatFace( String faceName ) 
	{
		getAssetGuiInfo().setChatFace( faceName );
	}

	//========================================================================
	public String getChatFace() 
	{
		return getAssetGuiInfo().getChatFace();
	}

	//========================================================================
	public void setContent( String content ) 
	{
		getAssetGuiInfo().setContent( content );
	}

	//========================================================================
	public String getContent() 
	{
		return getAssetGuiInfo().getContent();
	}
	
	//========================================================================
	public String getAssetTag() 
	{
		return getAssetGuiInfo().getAssetTag();
	}

	//========================================================================
	public void setAssetTag(String content) 
	{
		this.getAssetGuiInfo().setAssetTag( content );
		NativeTxTo.fromGuiAssetAction( Constants.eAssetActionUpdateAsset, getAssetGuiInfo(), 0 );
	}

	//========================================================================
	public boolean getIsSend() 
	{
		return m_IsSend;
	}

	//========================================================================
	public void setIsSend(boolean isSend) 
	{
		this.m_IsSend = isSend;
	}

	//========================================================================
	public Date getDate() 
	{
		return new Date( getAssetGuiInfo().getCreationTime() );
	}

	//========================================================================
	public void setDate(Date time) 
	{
		this.getAssetGuiInfo().setCreationTime( time.getTime() );
	}

	//========================================================================
	public void setCreationTime( long timeMs ) 
	{
		this.getAssetGuiInfo().setCreationTime( timeMs );
	}

	//========================================================================
	public AssetGuiInfo getAssetGuiInfo() 
	{
		return m_AssetGuiInfo;
	}

	//========================================================================
	public void setAssetGuiInfo( AssetGuiInfo assetGuiInfo ) 
	{
		this.m_AssetGuiInfo = assetGuiInfo;
	}

	//========================================================================
	public void setReadyForCallbacks( boolean isReady ) 
	{
		if( isReady )
		{
			try 
			{
				NativeRxFrom.wantAssetCallbackClient( ChatMessage.this, true );
			} 
			catch (InterruptedException e) 
			{
				e.printStackTrace();
			}	
		}
		else
		{
			try 
			{
				NativeRxFrom.wantAssetCallbackClient( ChatMessage.this, false );
			} 
			catch (InterruptedException e) 
			{
				e.printStackTrace();
			}	
		}
	}

	//========================================================================
	@Override
	public void toGuiAssetAdded(AssetGuiInfo assetInfo) 
	{	
	}

	//========================================================================
	@Override
	public void toGuiSessionHistory(AssetGuiInfo assetInfo) 
	{
	}

	//========================================================================
	@Override
	public void toGuiAssetAction(int assetAction, VxGUID assetId, int actionParam) 
	{
		// empty.. using onToGuiAssetAction instead
	}
	
	//========================================================================
	// called on ui thread and already checked if correct asset id
	public boolean onToGuiAssetAction( int assetAction, int actionParam )
	{
		boolean needUpdate = false;
		switch( assetAction )
		{
		case Constants.eAssetActionPlayProgress:
			m_XferProgressShouldBeVisible = false;
			if( false == m_SliderIsPressed )
			{
				if( m_AssetGuiInfo.isVideoAsset() )
				{
					updateGuiPlayControls( true );
					m_CamPlayPosSlider.setProgress( actionParam  );
					//needUpdate = true;
				}
				else if( m_AssetGuiInfo.isAudioAsset() )
				{
					updateGuiPlayControls( true );
					m_AudioPlayPosSlider.setProgress( actionParam  );
					//needUpdate = true;
				}				
			}
			
			break;

		case Constants.eAssetActionPlayEnd:
			m_XferProgressShouldBeVisible = false;
			updateGuiPlayControls( false );
			needUpdate = true;			
			break;				

		case Constants.eAssetActionTxBegin:
			if( Constants.eAssetSendStateTxProgress != getSendState() )
			{
				setSendState( Constants.eAssetSendStateTxProgress );
			}

			m_XferProgressShouldBeVisible = true;
			if( m_AssetSendProgress != actionParam )
			{
				m_AssetSendProgress = actionParam;
			}

			needUpdate = true;
			break;

		case Constants.eAssetActionTxProgress:
			m_XferProgressShouldBeVisible = true;
			m_AssetSendProgress = actionParam;
			if( Constants.eAssetSendStateTxProgress != getSendState() )
			{
				setSendState( Constants.eAssetSendStateTxProgress );
			}
			
			if( m_AssetSendProgress != actionParam )
			{
				m_AssetSendProgress = actionParam;
			}
			
			needUpdate = true;
			break;
			
		case Constants.eAssetActionRxBegin:
			if( Constants.eAssetSendStateRxProgress != getSendState() )
			{
				setSendState( Constants.eAssetSendStateRxProgress );
			}

			m_XferProgressShouldBeVisible = true;
			if( m_AssetSendProgress != actionParam )
			{
				m_AssetSendProgress = actionParam;
			}

			needUpdate = true;
			break;
			
		case Constants.eAssetActionRxProgress:
			m_XferProgressShouldBeVisible = true;
			m_AssetSendProgress = actionParam;
			if( Constants.eAssetSendStateRxProgress != getSendState() )
			{
				setSendState( Constants.eAssetSendStateRxProgress );
			}
			
			if( m_AssetSendProgress != actionParam )
			{
				m_AssetSendProgress = actionParam;
			}
			
			needUpdate = true;
			break;
			
		case Constants.eAssetActionTxSuccess:
			m_XferProgressShouldBeVisible = false;
			if( Constants.eAssetSendStateTxSuccess != getSendState() )
			{
				setSendState( Constants.eAssetSendStateTxSuccess );
			}
			
			needUpdate = true;
			break;
			
		case Constants.eAssetActionRxSuccess:
			m_XferProgressShouldBeVisible = false;
			if( Constants.eAssetSendStateRxSuccess != getSendState() )
			{
				setSendState( Constants.eAssetSendStateRxSuccess );
			}
			
			needUpdate = true;
			break;
			
		case Constants.eAssetActionTxError:
		case Constants.eAssetActionTxCancel:
			m_XferProgressShouldBeVisible = true;
			if( Constants.eAssetSendStateTxFail != getSendState() )
			{
				setSendState( Constants.eAssetSendStateTxFail );
			}
			
			needUpdate = true;
			break;	
		

		case Constants.eAssetActionRxError:
		case Constants.eAssetActionRxCancel:
			m_XferProgressShouldBeVisible = true;
			if( Constants.eAssetSendStateRxFail != getSendState() )
			{
				setSendState( Constants.eAssetSendStateRxFail );
			}
			
			needUpdate = true;
			break;	
			
		case Constants.eAssetActionTxPermission:
			m_XferProgressShouldBeVisible = true;
			if( Constants.eAssetActionTxPermission != getSendState() )
			{
				setSendState( Constants.eAssetActionTxPermission );
			}
			
			needUpdate = true;
			break;				
		
		case Constants.eAssetActionRxPermission:
			m_XferProgressShouldBeVisible = false;
			if( Constants.eAssetActionRxPermission != getSendState() )
			{
				setSendState( Constants.eAssetActionRxPermission );
			}
			
			needUpdate = true;
			break;	
		
		default:
			m_XferProgressShouldBeVisible = false;
			break;
		}
		
		if( m_XferProgressShouldBeVisible != m_XferProgressIsVisible )
		{
			needUpdate = true;
		}
		 
		return needUpdate;
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
				if( m_AssetGuiInfo.isVideoAsset() )
				{
					m_CamPlayButton.setBackgroundResource( R.drawable.button_play_normal );
					m_CamPlayPosSlider.setProgress( 0 );
				}
				else if( m_AssetGuiInfo.isAudioAsset() )
				{
					m_AudioPlayButton.setBackgroundResource( R.drawable.button_play_normal );
					m_AudioPlayPosSlider.setProgress( 0 );
				}
			}
			else
			{
				Log.i( LOG_TAG, "updateGuiPlayControls playing" );
				if( m_AssetGuiInfo.isVideoAsset() )
				{
					m_CamPlayButton.setBackgroundResource( R.drawable.button_pause_normal );
				}
				else if( m_AssetGuiInfo.isAudioAsset() )
				{
					m_AudioPlayButton.setBackgroundResource( R.drawable.button_pause_normal );
				}				
			}
		}
	}
	
	//========================================================================
	public void doStop()
	{
		setReadyForCallbacks( false );
		stopMediaIfPlaying();
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
			startMediaPlay( 0 );
		}		
	}
	
	//========================================================================
	private void stopMediaIfPlaying()
	{
		if( m_AssetGuiInfo.isVideoAsset() || m_AssetGuiInfo.isAudioAsset() )
		{
			if( m_IsPlaying )
			{
				Log.i( LOG_TAG, "Chat Sending Play End" );
				NativeTxTo.fromGuiAssetAction( Constants.eAssetActionPlayEnd, m_AssetGuiInfo, 0 );
			}
			
			updateGuiPlayControls( false );
		}				
	}
	
	//========================================================================
	private void startMediaPlay( int position )
	{
		if( m_AssetGuiInfo.isVideoAsset() || m_AssetGuiInfo.isAudioAsset() )
		{
			Log.i( LOG_TAG, "Chat Play Begin " + position + " time " + System.currentTimeMillis() );
			NativeTxTo.fromGuiMuteSpeaker( false );
			boolean playStarted = NativeTxTo.fromGuiAssetAction( Constants.eAssetActionPlayBegin, m_AssetGuiInfo, position );
			if( false == playStarted )
			{
				Log.i( LOG_TAG, "Play FAILED TO Begin" );
			}
			
			updateGuiPlayControls( playStarted );
		}
	}

	//========================================================================
	private void onUserChangedPlayPosition( int position )
	{
		Log.d( LOG_TAG, "onUserChangedPlayPosition " + position );	
		startMediaPlay( position );
	}

	//========================================================================
	private void onShredAssetButClick(View v) 
	{
		if( null == m_AssetGuiInfo )
		{
			return;
		}
		
		if( m_AssetGuiInfo.isFileAsset() )
		{
			stopMediaIfPlaying();
			m_ChatAdapter.getMyApp().playButtonClick();
			onShredMediaButClick(v);
		}
		else
		{
			// no media file
			m_ChatAdapter.getMyApp().playButtonClick();
			Log.d( LOG_TAG, "onShredAssetButClick no media file " + m_AssetGuiInfo.getAssetUniqueId().toOnlineIdHexString() );
			new AlertDialog.Builder( m_Activity )	 
		 	.setIcon(R.drawable.button_trash_normal)	 
		 	.setTitle("Remove Message Confirm")	 
		 	.setMessage("Press REMOVE to remove message from history")	 
		 	.setPositiveButton("REMOVE", new DialogInterface.OnClickListener()
			 {
			 	@Override
			 	public void onClick(DialogInterface dialog, int which) 
			 	{
			 		//Toast.makeText(m_Activity, "You Clicked REMOVE", Toast.LENGTH_SHORT).show();
			 		stopMediaIfPlaying();
			 		m_ChatAdapter.getMyApp().playSound( ESndDef.eSndDefNeckSnap );
					NativeTxTo.fromGuiAssetAction( Constants.eAssetActionRemoveFromAssetMgr, m_AssetGuiInfo, 0 );
			 	}
			 })
			 .setNegativeButton("Cancel", new DialogInterface.OnClickListener()
			 {
				 @Override
				 public void onClick(DialogInterface dialog, int which) 
				 {
					 m_ChatAdapter.getMyApp().playButtonClick();
					 Toast.makeText(m_Activity, "Operation Canceled", Toast.LENGTH_SHORT).show();
				 }
			 })
			 .show();
		}
	}

	//========================================================================
	private void onAssetResendButClick(View v) 
	{
		if( null == m_AssetGuiInfo )
		{
			return;
		}
		
		m_ChatAdapter.getMyApp().playButtonClick();
		Log.d( LOG_TAG, "onAssetResendButClick " + m_AssetGuiInfo.getAssetUniqueId().toOnlineIdHexString() );
		NativeTxTo.fromGuiAssetAction( Constants.eAssetActionAssetResend, m_AssetGuiInfo, 0 );
	}
	
	//========================================================================
	private void onShredMediaButClick(View v) 
	{
		stopMediaIfPlaying();
		new AlertDialog.Builder( m_Activity )	 
		 	.setIcon(R.drawable.button_shredder_normal)	 
		 	.setTitle("Delete File Confirm")	 
		 	.setMessage("Press SHRED to write random data to file then delete file and remove message.\n Press REMOVE to just remove message from history")	 
		 	.setPositiveButton("SHRED", new DialogInterface.OnClickListener()
			 {
			 	@Override
			 	public void onClick(DialogInterface dialog, int which) 
			 	{
			 		//Toast.makeText(m_Activity, "You Clicked SHRED", Toast.LENGTH_SHORT).show();		 		
			 		m_ChatAdapter.getMyApp().playSound( ESndDef.eSndDefPaperShredder );
					Log.d( LOG_TAG, "onShredMediaButClick Shredding file " + m_AssetGuiInfo.getAssetName() + " Unique Id " + m_AssetGuiInfo.getAssetUniqueId().toOnlineIdHexString() );
					NativeTxTo.fromGuiAssetAction( Constants.eAssetActionShreadFile, m_AssetGuiInfo, 0 );
			 	}
			 })
			 .setNegativeButton("Cancel", new DialogInterface.OnClickListener()
			 {
				 @Override
				 public void onClick(DialogInterface dialog, int which) 
				 {
					 m_ChatAdapter.getMyApp().playButtonClick();
					 Toast.makeText(m_Activity, "Operation Canceled", Toast.LENGTH_SHORT).show();
				 }
			 })
			 .setNeutralButton("REMOVE", new DialogInterface.OnClickListener()
			 {
				 @Override
				 public void onClick(DialogInterface dialog, int which) 
				 {
					 //Toast.makeText(m_Activity, "You Clicked on NO", Toast.LENGTH_SHORT).show();
					 Log.d( LOG_TAG, "onShredMediaButClick Removing file " + m_AssetGuiInfo.getAssetName() + " Unique Id " + m_AssetGuiInfo.getAssetUniqueId().toOnlineIdHexString() );
					 m_ChatAdapter.getMyApp().playSound( ESndDef.eSndDefNeckSnap );
					 NativeTxTo.fromGuiAssetAction( Constants.eAssetActionRemoveFromAssetMgr, m_AssetGuiInfo, 0 );
				 }
			 })
			 .show();
	}
}

