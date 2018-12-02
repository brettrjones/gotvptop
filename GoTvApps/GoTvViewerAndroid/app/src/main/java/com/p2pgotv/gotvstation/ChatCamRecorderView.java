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

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.SurfaceHolder;

//============================================================================
public class ChatCamRecorderView extends CamViewBase implements SurfaceHolder.Callback
{
	private static final String LOG_TAG = "CHAT:";
	ChatSessionState 					m_ChatState 						= null;
	private boolean						m_IsVisible							= false;
	private int							m_WindowWidth						= 0;
	private int							m_WindowHeight						= 0;
	
	//========================================================================
	public void setInputState( ChatSessionState chatState )
	{
		m_ChatState = chatState;
		if( m_IsVisible )
		{
			applyState();
		}
	}
	
	//========================================================================
	public void applyState()
	{
		if( null == m_ChatState )
		{
			return;
		}
		
		setFeedMediaType( m_ChatState.getFeedMediaType() );
		setVideoFeedId( m_ChatState.getVideoFeedId() );
		if( m_IsVisible && ( m_WindowWidth > 10 ) && ( m_WindowHeight > 10 ) && ( Constants.eChatInputVideo == m_ChatState.getChatInputType() ) )
		{
			requestVideoFeed();
		}
		else
		{
			stopVideoFeed();
		}
	}

	//============================================================================
	public ChatCamRecorderView( Context context ) 
	{
		super(context);
		Log.i(LOG_TAG, "ChatCamRecorderView create" );
	}

	//============================================================================
	public ChatCamRecorderView( Context context, AttributeSet attrs ) 
	{
		super(context, attrs);
		Log.i(LOG_TAG, "ChatCamRecorderView create" );
	}

	//============================================================================
	public ChatCamRecorderView( Context context, AttributeSet attrs, int defStyle ) 
	{
		super(context, attrs, defStyle);
		Log.i(LOG_TAG, "ChatCamRecorderView create" );
	}
    
	//============================================================================
	@Override
	protected void onWindowVisibilityChanged( int visiblity ) 
    {
        super.onWindowVisibilityChanged(visiblity);
		Log.i( LOG_TAG, "ChatCamRecorderView onWindowVisibilityChanged " + visiblity );
		if( 0 == visiblity )
		{
			// now visible
			m_IsVisible = true;
		}
		else
		{
			m_IsVisible = false;
		}
		
		applyState();
    }
	
	//============================================================================
	@Override
    protected void onAttachedToWindow() 
    {
        super.onAttachedToWindow();
		Log.i(LOG_TAG, "ChatCamRecorderView onAttachedToWindow" );
    }

	//============================================================================
    @Override
    protected void onDetachedFromWindow() 
    {
        super.onDetachedFromWindow();
		Log.i(LOG_TAG, "ChatCamRecorderView onDetachedFromWindow" );
    }

	//============================================================================
	@Override
	public void surfaceCreated(SurfaceHolder holder) 
	{
		// TODO Auto-generated method stub		
		Log.i(LOG_TAG, "ChatCamRecorderView surfaceCreated" );
	}

	//============================================================================
	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) 
	{
		m_WindowWidth 	= width;
		m_WindowHeight 	= height;
		applyState();
	}

	//============================================================================
	@Override
	public void surfaceDestroyed(SurfaceHolder holder) 
	{
		m_WindowWidth 	= 0;
		m_WindowHeight 	= 0;
		applyState();
	}
		
}


