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


public class ChatSessionState
{
	private static final String LOG_TAG = "ChatSessionState:";
	
	MyApp 								m_MyApp								= null;
	public  Activity					m_Activity							= null;
	private int							m_ChatInputType  					= Constants.eChatInputSelectMode;
	private int							m_RequestMediaType  				= Constants.eMediaInputVideoJpgSmall;
	private VxGUID 						m_VidFeedId							= null;
	private VxGUID						m_MyId 								= null; // same as vid feed id for vid recording
	private VxNetIdent					m_MyIdent 							= null; 
	private String						m_MyAvatar							= "avatar";
	private VxGUID						m_FriendId 							= null; 
	private VxNetIdent					m_FriendIdent 						= null; 
	private String						m_FriendAvatar						= "avatar";
	public boolean						m_IsPersonalRecorder 				= false;
	public boolean 						m_IsInVidRecording 					= false;
	public boolean 						m_IsInSndRecording 					= false;
	public AssetGuiInfo					m_AssetGuiInfo						= null;
	public String						m_FileName							= "";
	public VxTimer 						m_RecordTimer						= new VxTimer();
	public long							m_TimeRecStart						= 0;

	//============================================================================
	ChatSessionState( MyApp myApp )
	{
		m_MyApp 							= myApp;
		m_MyIdent							= m_MyApp.getMyIdentity();
		m_MyId 								= m_MyIdent.getMyOnlineId();
		m_FriendIdent						= m_MyApp.getMyIdentity();
		m_FriendId							= m_MyId;
		m_VidFeedId							= m_MyId;
	}

	//============================================================================
	void setChatInputType( int chatInputType )
	{
		m_ChatInputType = chatInputType;
	}
	
	//============================================================================
	int getChatInputType()
	{
		return m_ChatInputType;
	}

	//============================================================================
	public void setIsPersonalRecorder( boolean isPersonal )
	{
		m_IsPersonalRecorder = isPersonal;
	}

	//============================================================================
	public boolean getIsPersonalRecorder()
	{
		return m_IsPersonalRecorder;
	}

	//============================================================================
	void setIsAudioRecording( boolean isRecording )
	{
		m_IsInSndRecording = isRecording;
	}

	//============================================================================
	boolean getIsAudioRecording()
	{
		return m_IsInSndRecording;
	}

	//============================================================================
	void setIsVideoRecording( boolean isRecording )
	{
		m_IsInVidRecording = isRecording;
	}

	//============================================================================
	boolean getIsVideoRecording()
	{
		return m_IsInVidRecording;
	}

	//============================================================================
	void setFriendIdent( VxNetIdent	friendIdent )
	{
		m_FriendIdent = friendIdent;
	}
	
	//============================================================================
	VxNetIdent getFriendIdent()
	{
		return m_FriendIdent;
	}
	
	//============================================================================
	VxNetIdent getMyIdent()
	{
		return m_MyIdent;
	}
	
	//============================================================================
	String getMyAvatar()
	{
		return m_MyAvatar;
	}
	
	//============================================================================
	String getFriendAvatar()
	{
		return m_FriendAvatar;
	}
	
	//============================================================================
	void setFeedMediaType( int reqestMediaType )
	{
		m_RequestMediaType = reqestMediaType;
	}
	
	//============================================================================
	int getFeedMediaType()
	{
		return m_RequestMediaType;
	}
	
	//============================================================================
	void setVideoFeedId( VxGUID feedId )
	{
		m_VidFeedId = feedId;
	}
	
	//============================================================================
	VxGUID getVideoFeedId()
	{
		return m_VidFeedId;
	}

	//============================================================================
	void setMyId( VxGUID id )
	{
		m_MyId = id;
	}
	
	//============================================================================
	VxGUID getMyId()
	{
		return m_MyId;
	}

	//============================================================================
	void setFriendId( VxGUID id )
	{
		m_FriendId = id;
	}
	
	//============================================================================
	VxGUID getFriendId()
	{
		return m_FriendId;
	}

};

