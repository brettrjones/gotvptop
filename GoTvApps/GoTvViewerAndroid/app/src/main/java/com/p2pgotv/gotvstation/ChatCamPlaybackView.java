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

//============================================================================
public class ChatCamPlaybackView extends CamViewBase
{
	private static final String LOG_TAG = "CHAT:";
	ChatMessage							m_ChatMessage 						= null;
	private boolean						m_IsVisible							= false;
	
	//========================================================================
	public void setChatMessage( ChatMessage chatMessage )
	{
		m_ChatMessage = chatMessage;
		if( m_IsVisible )
		{
			applyState();
		}
	}
	
	//========================================================================
	public void applyState()
	{
		if( ( null == m_ChatMessage ) 
			|| ( 0 == m_iFinalWidth )
			|| ( 0 == m_iFinalHeight ) )
		{
			return;
		}
		
		setFeedMediaType( Constants.eMediaInputNone );
		setVideoFeedId( m_ChatMessage.getAssetId() );
		if( m_IsVisible )
		{
			requestVideoFeed();
			NativeTxTo.fromGuiAssetAction( Constants.eAssetActionPlayOneFrame, m_ChatMessage.getAssetGuiInfo(), 0 );
		}
		else
		{
			stopVideoFeed();
		}
	}

	//============================================================================
	public ChatCamPlaybackView( Context context ) 
	{
		super(context);
		//Log.i(LOG_TAG, "ChatCamPlaybackView create" );
	}

	//============================================================================
	public ChatCamPlaybackView( Context context, AttributeSet attrs ) 
	{
		super(context, attrs);
		//Log.i(LOG_TAG, "ChatCamPlaybackView create" );
	}

	//============================================================================
	public ChatCamPlaybackView( Context context, AttributeSet attrs, int defStyle ) 
	{
		super(context, attrs, defStyle);
		//Log.i(LOG_TAG, "ChatCamPlaybackView create" );
	}
    
	//============================================================================
	@Override
	protected void onWindowVisibilityChanged( int visiblity ) 
    {
        super.onWindowVisibilityChanged(visiblity);
		//Log.i( LOG_TAG, "ChatMessageInputToolBox onWindowVisibilityChanged " + visiblity );
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
    protected void onMeasure( int widthMeasureSpec, int heightMeasureSpec )
    {  
    	// keep aspect ratio
    	//int width = MeasureSpec.getSize(widthMeasureSpec);	
    	//int height = (int)( width * m_f32AspectRatio ); 
        //this.setMeasuredDimension( width, height );  
    	
        super.onMeasure( widthMeasureSpec, heightMeasureSpec ); // Important !!!
        int width = getMeasuredWidth();
        int height = getMeasuredHeight();
        if( ( 0 != width ) && ( 0 != height ) && ( 200000 > width ) && ( 200000 > height ) )
        {
        	m_iFinalWidth = width;
        	m_iFinalHeight = height;
        	applyState();
        }
    }
	
	//========================================================================	
	@Override
	protected void onFinishInflate() 
	{
		super.onFinishInflate();
		applyState();
		//Log.i(LOG_TAG, "ChatCamPlaybackView onFinishInflate" );
	}
}


