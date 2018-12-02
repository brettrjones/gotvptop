// Derivative of Android Chat Widget https://github.com/ijarobot/ ( Apache License )
package com.p2pgotv.gotvstation;

import java.util.Calendar;
import java.util.Date;
import java.util.List;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Intent;
import android.text.format.DateFormat;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.RelativeLayout;
import android.widget.SeekBar;
import android.widget.TextView;

public class ChatMessageAdapter extends BaseAdapter 
{
	private static final String LOG_TAG = "ChatAdapter:";

	//========================================================================
	static class ViewHolder 
	{	
		public ImageView			m_UserAvatarImageView;
		public TextView 			m_SendDateTextView;
		public TextView 			m_UserNameTextView;
		
		public TextView 			m_TextTextView;
		public ImageView 			m_FaceImageView;
		public ChatPhotoView 		m_PhotoImageView;
		public ImageView 			m_AudioImageView;
		public RelativeLayout 		m_AudioButtonLayout;
		public Button 				m_AudioPlayButton;
		public SeekBar 				m_AudioSeekBar;

		public ChatCamPlaybackView 	m_CamPlaybackView;
		public RelativeLayout 		m_CamButtonLayout;
		public Button 				m_CamPlayButton;
		public SeekBar 				m_CamSeekBar;
		
		public ProgressBar 			m_XferPercentProgress;
		public TextView 			m_SendTimeTextView;
		public ProgressBar 			m_SendingProgressBar;
		public ImageView 			m_FailImageView;
		public Button 				m_AssetShredButton;
		public Button 				m_AssetResendButton;
		
		public boolean 				m_IsSend = true;
		
		public void	setAssetView( int assetType )
		{
			boolean showTrashInsteadOfShred = false;
			switch( assetType ) 
			{
			case Constants.eAssetTypeChatText://text
				m_TextTextView.setVisibility(View.VISIBLE);
				m_PhotoImageView.setVisibility(View.GONE);
				m_FaceImageView.setVisibility(View.GONE);
				m_AudioImageView.setVisibility(View.GONE);
				m_AudioButtonLayout.setVisibility(View.GONE);
				m_CamPlaybackView.setVisibility(View.GONE);
				m_CamButtonLayout.setVisibility(View.GONE);
				showTrashInsteadOfShred = true;
				break;
				
			case Constants.eAssetTypePhoto:			
				m_TextTextView.setVisibility(View.GONE);
				m_PhotoImageView.setVisibility(View.VISIBLE);
				m_FaceImageView.setVisibility(View.GONE);
				m_AudioImageView.setVisibility(View.GONE);
				m_AudioButtonLayout.setVisibility(View.GONE);
				m_CamPlaybackView.setVisibility(View.GONE);
				m_CamButtonLayout.setVisibility(View.GONE);
				break;
				
			case Constants.eAssetTypeChatFace:			
				m_TextTextView.setVisibility(View.GONE);
				m_PhotoImageView.setVisibility(View.GONE);
				m_FaceImageView.setVisibility(View.VISIBLE);
				m_AudioImageView.setVisibility(View.GONE);
				m_AudioButtonLayout.setVisibility(View.GONE);
				m_CamPlaybackView.setVisibility(View.GONE);
				m_CamButtonLayout.setVisibility(View.GONE);
				showTrashInsteadOfShred = true;
				break;
				
			case Constants.eAssetTypeAudio:			
				m_TextTextView.setVisibility(View.GONE);
				m_PhotoImageView.setVisibility(View.GONE);
				m_FaceImageView.setVisibility(View.GONE);
				m_AudioImageView.setVisibility(View.VISIBLE);
				m_AudioButtonLayout.setVisibility(View.VISIBLE);
				m_CamPlaybackView.setVisibility(View.GONE);
				m_CamButtonLayout.setVisibility(View.GONE);
				break;
				
			case Constants.eAssetTypeVideo:			
				m_TextTextView.setVisibility(View.GONE);
				m_PhotoImageView.setVisibility(View.GONE);
				m_FaceImageView.setVisibility(View.GONE);
				m_AudioImageView.setVisibility(View.GONE);
				m_AudioButtonLayout.setVisibility(View.GONE);
				m_CamPlaybackView.setVisibility(View.VISIBLE);
				m_CamButtonLayout.setVisibility(View.VISIBLE);
				break;
			}
			
			m_AssetShredButton.setBackgroundResource( showTrashInsteadOfShred ? R.drawable.button_trash_normal :  R.drawable.button_shredder_normal );
		}
	}
	
	private Activity 			m_Activity;
	private List<ChatMessage> 	m_ChatMsgList = null;
	private MyApp 				m_MyApp = null;
	
	//========================================================================
	public ChatMessageAdapter( MyApp myApp, Activity activity, List<ChatMessage> list) 
	{
		super();
		this.m_Activity 		= activity;
		m_MyApp 				= myApp;
		this.m_ChatMsgList 		= list;
	}

	//========================================================================
	public MyApp getMyApp()
	{
		return m_MyApp;
	}
	
	//========================================================================
	@Override
	public int getCount() 
	{
		return m_ChatMsgList != null ? m_ChatMsgList.size() : 0;
	}

	//========================================================================
	@Override
	public Object getItem(int position) 
	{
		return m_ChatMsgList.get(position);
	}

	//========================================================================
	@Override
	public long getItemId(int position) 
	{	
		return position;
	}

	//========================================================================
	@Override
	public int getItemViewType(int position) 
	{
		return this.m_ChatMsgList.get(position).getIsSend() ? 1 : 0;
	}
	
	//========================================================================
	@Override
	public int getViewTypeCount() 
	{
		return 2;
	}

	//========================================================================	
	@SuppressLint("InflateParams")
	public View getView(int position, View convertView, ViewGroup parent) 
	{
		final ChatMessage message = m_ChatMsgList.get(position);
		boolean isSend = message.getIsSend();

		ViewHolder viewHolder = null;
		if (convertView == null) 
		{
			viewHolder = new ViewHolder();
			if (isSend) 
			{
				convertView = LayoutInflater.from( m_Activity ).inflate(R.layout.chat_msg_item_right, null);
			} 
			else 
			{
				convertView = LayoutInflater.from( m_Activity ).inflate(R.layout.chat_msg_item_left, null);
			}

			viewHolder.m_XferPercentProgress 	= (ProgressBar) convertView.findViewById(R.id.asset_xfer_progress_percent);
			viewHolder.m_SendDateTextView 		= (TextView) convertView.findViewById(R.id.sendDateTextView);
			viewHolder.m_SendTimeTextView 		= (TextView) convertView.findViewById(R.id.sendTimeTextView);
			viewHolder.m_UserAvatarImageView 	= (ImageView) convertView.findViewById(R.id.userAvatarImageView);
			viewHolder.m_UserNameTextView 		= (TextView) convertView.findViewById(R.id.userNameTextView);
			
			viewHolder.m_TextTextView 			= (TextView) convertView.findViewById(R.id.textTextView);
			viewHolder.m_FaceImageView 			= (ImageView) convertView.findViewById(R.id.faceImageView);
			viewHolder.m_AudioImageView 		= (ImageView) convertView.findViewById(R.id.audioImageView);
			viewHolder.m_AudioButtonLayout 		= (RelativeLayout) convertView.findViewById(R.id.audioPlaybackButtonsLayout);	
			viewHolder.m_AudioPlayButton 		= (Button) convertView.findViewById(R.id.audio_playplayback_button);	
			viewHolder.m_AudioSeekBar 			= (SeekBar) convertView.findViewById(R.id.audio_playback_seekbar);

			viewHolder.m_CamPlaybackView 		= (ChatCamPlaybackView) convertView.findViewById(R.id.camPlaybackView);	
			viewHolder.m_CamButtonLayout 		= (RelativeLayout) convertView.findViewById(R.id.camPlaybackButtonsLayout);	
			viewHolder.m_CamPlayButton 			= (Button) convertView.findViewById(R.id.vid_playplayback_button);	
			viewHolder.m_CamSeekBar 			= (SeekBar) convertView.findViewById(R.id.vid_playback_seekbar);

			viewHolder.m_PhotoImageView 		= (ChatPhotoView) convertView.findViewById(R.id.chatPhotoView );		
			
			viewHolder.m_FailImageView 			= (ImageView) convertView.findViewById(R.id.failImageView );
			viewHolder.m_SendingProgressBar 	= (ProgressBar) convertView.findViewById(R.id.sendingProgressBar );
			viewHolder.m_AssetShredButton 		= (Button) convertView.findViewById(R.id.asset_shred_button );
			viewHolder.m_AssetResendButton 		= (Button) convertView.findViewById(R.id.asset_resend_button );
			
			viewHolder.m_IsSend 				= isSend;
			convertView.setTag(viewHolder);		
		} 
		else 
		{
			viewHolder = (ViewHolder) convertView.getTag();
		}
		
		try 
		{
			message.setShredAssetButton( viewHolder.m_AssetShredButton );
			message.setAssetResendButton( viewHolder.m_AssetResendButton );
			message.setCamControls( viewHolder.m_CamPlayButton, viewHolder.m_CamSeekBar );
			message.setAudioControls( viewHolder.m_AudioPlayButton, viewHolder.m_AudioSeekBar, viewHolder.m_AudioImageView );
			message.setPhotoVideoControls( viewHolder.m_PhotoImageView, viewHolder.m_CamPlaybackView );
			
			String dateString = DateFormat.format("yyyy-MM-dd h:mmaa", message.getDate()).toString();
			String [] t = dateString.split(" ");
			viewHolder.m_SendDateTextView.setText(t[0]);
			viewHolder.m_SendTimeTextView.setText(t[1]);
			
			if( position == 0 )
			{
				viewHolder.m_SendDateTextView.setVisibility(View.VISIBLE);
			}
			else
			{
				//TODO is same day ?
				ChatMessage pmsg = m_ChatMsgList.get(position-1);
				if(inSameDay(pmsg.getDate(), message.getDate()))
				{
					viewHolder.m_SendDateTextView.setVisibility(View.GONE);
				}
				else
				{
					viewHolder.m_SendDateTextView.setVisibility(View.VISIBLE);
				}		
			}
		} 
		catch (Exception e) 
		{
		}
		
		String fromUserName     = message.getFromUserName();
		String assetContent     = message.getContent();
		String chatText         = message.getChatText();
		String packageName		= m_Activity.getPackageName();
		
		viewHolder.m_UserNameTextView.setText( fromUserName );
			
		switch( message.getAssetType() ) 
		{
		case Constants.eAssetTypeChatText://text
			viewHolder.m_TextTextView.setText( chatText );
			viewHolder.setAssetView( Constants.eAssetTypeChatText );
			setSendGuiStates( message, viewHolder, R.id.textTextView );			
			break;
			
		case Constants.eAssetTypeChatFace://face
			viewHolder.setAssetView( Constants.eAssetTypeChatFace );

			int resId = m_Activity.getResources().getIdentifier( assetContent, "drawable", packageName );
			viewHolder.m_FaceImageView.setImageResource(resId);
			setSendGuiStates( message, viewHolder, R.id.faceImageView );			
			break;
			
		case Constants.eAssetTypePhoto:
			viewHolder.setAssetView( Constants.eAssetTypePhoto );
			viewHolder.m_PhotoImageView.setChatMessage( message );
			setSendGuiStates( message, viewHolder, R.id.chatPhotoView );
			break;
			
		case Constants.eAssetTypeAudio:
			viewHolder.setAssetView( Constants.eAssetTypeAudio );
			setSendGuiStates( message, viewHolder, R.id.audioImageView );
			viewHolder.m_AudioImageView.setImageResource(R.drawable.ic_microphone_blue);
			break;
			
		case Constants.eAssetTypeVideo://video
			viewHolder.setAssetView( Constants.eAssetTypeVideo );
			setSendGuiStates( message, viewHolder, R.id.camPlaybackView );
			viewHolder.m_CamPlaybackView.setChatMessage( message );
			break;
			
		default:
			viewHolder.m_TextTextView.setText( assetContent );
			viewHolder.setAssetView( Constants.eAssetTypeChatText );
			break;
		}
		
		return convertView;
	}
	
	//========================================================================
	public void onPhotoViewClick( AssetGuiInfo assetGuiInfo )
	{
		String fileName = assetGuiInfo.getAssetName();
		long fileLen = VxFileUtil.getFileLen( fileName );
		if( 0 != fileLen )
		{
			VxFileInfo fileInfo = new VxFileInfo( fileName, fileLen, Constants.VXFILE_TYPE_PHOTO, null );
			m_MyApp.setCurrentFileInfo( fileInfo );
			Intent myIntent = new Intent( m_Activity, ActivityViewPhoto.class );
			myIntent.putExtra( Constants.PARAM_HIDE_ACCEPT_REJECT, Constants.PARAM_HIDE_ACCEPT_REJECT );
			m_Activity.startActivityForResult( myIntent, Constants.ACTIVITY_VIEW_PHOTO );							
		}
	}
	
	//========================================================================
	public void onVidPlaybackViewClick( AssetGuiInfo assetGuiInfo )
	{
		String fileName = assetGuiInfo.getAssetName();
		long fileLen = VxFileUtil.getFileLen( fileName );
		if( 0 != fileLen )
		{
			VxFileInfo fileInfo = new VxFileInfo( fileName, fileLen, Constants.VXFILE_TYPE_VIDEO, null );
			m_MyApp.setCurrentFileInfo( fileInfo );
			Intent myIntent = new Intent( m_Activity, ActivityViewVideoFile.class );
			myIntent.putExtra( Constants.PARAM_FILE_NAME, fileInfo.getFullFileName() );
			m_Activity.startActivityForResult( myIntent, Constants.ACTIVITY_VIEW_VIDEO_FILE );					
		}
	}
	
	//========================================================================
	public void onAudioPlaybackViewClick( AssetGuiInfo assetGuiInfo )
	{
		String fileName = assetGuiInfo.getAssetName();
		long fileLen = VxFileUtil.getFileLen( fileName );
		if( 0 != fileLen )
		{
			VxFileInfo fileInfo = new VxFileInfo( fileName, fileLen, Constants.VXFILE_TYPE_AUDIO, null );
			m_MyApp.setCurrentFileInfo( fileInfo );
			Intent myIntent = new Intent( m_Activity, ActivityViewAudioFile.class );
			myIntent.putExtra( Constants.PARAM_FILE_NAME, fileInfo.getFullFileName() );
			m_Activity.startActivityForResult( myIntent, Constants.ACTIVITY_VIEW_AUDIO_FILE );					
		}
	}

	//========================================================================
	public void doToGuiAssetAction( int assetAction, VxGUID assetId, int actionParam ) 
	{
		Log.d( LOG_TAG, "doToGuiAssetAction action=" + String.valueOf( assetAction ) + " param " + String.valueOf( actionParam ) );
		try 
		{
			boolean needUpdate = false;
	    	for( ChatMessage chatMsg:  m_ChatMsgList )
	    	{
	    		if( 0 == chatMsg.getAssetId().compareTo( assetId ) ) 
	    		{
	    			if( chatMsg.onToGuiAssetAction( assetAction, actionParam ) )
	    			{
	    				needUpdate = true;
	    			}
	    			
	    			//Log.d( LOG_TAG, "chatMsg.onToGuiAssetAction action=" + String.valueOf( assetAction ) + " param " + String.valueOf( actionParam ) + " needUpdate " + String.valueOf( needUpdate ) );
	    			break;
	    		}
//	    		else
//	    		{
//	    			Log.d( LOG_TAG, "doToGuiAssetAction no match " + assetId.toOnlineIdHexString() + " " + chatMsg.getAssetId().toOnlineIdHexString() );
//	    		}
	    	}
	    	
	    	if( needUpdate )
	    	{
	    		notifyDataSetChanged();
	    	}
		} 
		catch (Exception e) 
		{
			e.printStackTrace();
		}
	}	

	//========================================================================
	public void setSendGuiStates( ChatMessage message, ViewHolder viewHolder, int assetViewResourseId )
	{
		int sendState = message.getSendState();
		boolean xferProgressShouldBeVisible = false;
		switch( sendState )
		{
		case Constants.eAssetSendStateTxProgress:
		case Constants.eAssetSendStateRxProgress:
			xferProgressShouldBeVisible = true;
			viewHolder.m_SendingProgressBar.setVisibility(View.VISIBLE);
			viewHolder.m_FailImageView.setVisibility(View.GONE);
			viewHolder.m_AssetShredButton.setVisibility(View.GONE);
			viewHolder.m_AssetResendButton.setVisibility(View.GONE);
			break;
			
		case Constants.eAssetSendStateRxSuccess:
		case Constants.eAssetSendStateTxSuccess:
			viewHolder.m_SendingProgressBar.setVisibility(View.GONE);
			viewHolder.m_FailImageView.setVisibility(View.GONE);
			viewHolder.m_AssetShredButton.setVisibility(View.VISIBLE);
			viewHolder.m_AssetResendButton.setVisibility(View.GONE);
			break;
			
		case Constants.eAssetSendStateTxFail:
			xferProgressShouldBeVisible = true;
			viewHolder.m_SendingProgressBar.setVisibility(View.VISIBLE);
			viewHolder.m_FailImageView.setVisibility(View.VISIBLE);
			viewHolder.m_FailImageView.setImageResource( R.drawable.msg_state_fail_resend );
			viewHolder.m_AssetShredButton.setVisibility(View.VISIBLE);
			viewHolder.m_AssetResendButton.setVisibility(View.VISIBLE);
			break;
			
		case Constants.eAssetSendStateRxFail:
			xferProgressShouldBeVisible = true;
			viewHolder.m_SendingProgressBar.setVisibility(View.GONE);
			viewHolder.m_FailImageView.setVisibility(View.VISIBLE);
			viewHolder.m_FailImageView.setImageResource( R.drawable.msg_state_fail_resend );
			viewHolder.m_AssetShredButton.setVisibility(View.VISIBLE);
			viewHolder.m_AssetResendButton.setVisibility(View.GONE);
			break;
			
		case Constants.eAssetActionTxPermission:
			xferProgressShouldBeVisible = true;
			viewHolder.m_SendingProgressBar.setVisibility(View.VISIBLE);
			viewHolder.m_FailImageView.setVisibility(View.VISIBLE);
			viewHolder.m_FailImageView.setImageResource( R.drawable.msg_state_fail_permission );
			viewHolder.m_AssetShredButton.setVisibility(View.VISIBLE);
			viewHolder.m_AssetResendButton.setVisibility(View.GONE);
			break;
			
		case Constants.eAssetActionRxPermission:
			xferProgressShouldBeVisible = true;
			viewHolder.m_SendingProgressBar.setVisibility(View.GONE);
			viewHolder.m_FailImageView.setVisibility(View.VISIBLE);
			viewHolder.m_FailImageView.setImageResource( R.drawable.msg_state_fail_permission );
			viewHolder.m_AssetShredButton.setVisibility(View.VISIBLE);
			viewHolder.m_AssetResendButton.setVisibility(View.GONE);
			break;

		default:
			Log.i( LOG_TAG, "setSendGuiStates unknown send state "  );
			viewHolder.m_SendingProgressBar.setVisibility(View.GONE);
			viewHolder.m_FailImageView.setVisibility(View.GONE);
			viewHolder.m_AssetShredButton.setVisibility(View.VISIBLE);
			viewHolder.m_AssetResendButton.setVisibility(View.GONE);
			break;
		}
		
		if( null != viewHolder.m_XferPercentProgress )
		{
			if( xferProgressShouldBeVisible )
			{
				viewHolder.m_XferPercentProgress.setVisibility( View.VISIBLE );		
				viewHolder.m_XferPercentProgress.setProgress( message.m_AssetSendProgress );
			}
			else
			{
				viewHolder.m_XferPercentProgress.setVisibility( View.GONE );										
			}			
		}
	}

	//========================================================================
	public List<ChatMessage> getData() 
	{
		return m_ChatMsgList;
	}

	//========================================================================
	public void setData(List<ChatMessage> data) 
	{
		this.m_ChatMsgList = data;
	}

	//========================================================================
	public void removeChatMessageById( VxGUID assetId ) 
	{
		if( null != m_ChatMsgList )
		{
			int listPos = 0;
	    	for( ChatMessage chatMsg:  m_ChatMsgList )
	    	{
	    		if( chatMsg.getAssetId().equals( assetId ) ) 
	    		{
	    			m_ChatMsgList.remove(listPos);
	    			break;
	    		}
	    		
	    		listPos++;
	    	}			
		}
	}

	//========================================================================
	public static boolean inSameDay(Date date1, Date Date2) 
	{
		Calendar calendar = Calendar.getInstance();
		calendar.setTime(date1);
		int year1 	= calendar.get(Calendar.YEAR);
		int day1 	= calendar.get(Calendar.DAY_OF_YEAR);

		calendar.setTime(Date2);
		int year2 	= calendar.get(Calendar.YEAR);
		int day2 	= calendar.get(Calendar.DAY_OF_YEAR);

		if( ( year1 == year2 )
			&& ( day1 == day2 ) )
		{
			return true;
		}
		
		return false;
	}
	
	//========================================================================
	public int  getLastIndex()
	{
		return m_ChatMsgList.size() > 0 ? m_ChatMsgList.size() - 1 : 0;
	}
	
	//========================================================================
	public void addChatMsg( ChatMessage chatMsg )
	{
		VxGUID assetId = chatMsg.getAssetId();
		removeChatMessageById( assetId );
		boolean shouldAdd = true;
		if( chatMsg.getAssetGuiInfo().isFileAsset() )
		{
			if( false == VxFileUtil.fileExists( chatMsg.getAssetName() ) )
			{
				Log.e( LOG_TAG, "addChatMsg file does not exist " + chatMsg.getAssetName() );
				shouldAdd = false; // file does not exist anymore
			}
		}
			
		if( shouldAdd && ( null != m_ChatMsgList ) )
		{
			long addMsgTime = chatMsg.getCreationTime();
			int chatMsgIdx = 0;
	    	for( ChatMessage chatMsgInList:  m_ChatMsgList )
	    	{
	    		if( chatMsgInList.getCreationTime() > addMsgTime )
	    		{
	    			m_ChatMsgList.add( chatMsgIdx, chatMsg );
	    			notifyDataSetChanged();
	    			return;
	    		}
	    		
	    		chatMsgIdx++;
	    	}			
		
			m_ChatMsgList.add( chatMsg );
			notifyDataSetChanged();
		}	
	}

	//========================================================================
	public void activityOnStop()
	{
    	for( ChatMessage chatMsg:  m_ChatMsgList )
    	{
    		chatMsg.doStop();
    	}			
	}
}
