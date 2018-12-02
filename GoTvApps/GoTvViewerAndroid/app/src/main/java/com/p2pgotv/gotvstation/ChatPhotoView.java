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
public class ChatPhotoView extends CamViewBase implements SurfaceHolder.Callback
{
	private static final String LOG_TAG = "ChatPhotoView:";
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
		if( null == m_ChatMessage  )
		{
			return;
		}
	
		VxImageUtil.setImageViewFromPath( this, m_ChatMessage.getAssetName() );
	}

	//============================================================================
	public ChatPhotoView( Context context ) 
	{
		super(context);
		//Log.i(LOG_TAG, "ChatPhotoView create" );
	}

	//============================================================================
	public ChatPhotoView( Context context, AttributeSet attrs ) 
	{
		super(context, attrs);
		//Log.i(LOG_TAG, "ChatPhotoView create" );
	}

	//============================================================================
	public ChatPhotoView( Context context, AttributeSet attrs, int defStyle ) 
	{
		super(context, attrs, defStyle);
		//Log.i(LOG_TAG, "ChatPhotoView create" );
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
			applyState();
		}
		else
		{
			m_IsVisible = false;
		}
		
    }

	//============================================================================
	@Override
	public void surfaceCreated(SurfaceHolder holder) 
	{
		// TODO Auto-generated method stub		
		Log.i(LOG_TAG, "ChatPhotoView surfaceCreated" );
	}

	//============================================================================
	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) 
	{
		// TODO Auto-generated method stub	
		Log.i(LOG_TAG, "ChatPhotoView surfaceChanged" );
	}

	//============================================================================
	@Override
	public void surfaceDestroyed(SurfaceHolder holder) 
	{
		// TODO Auto-generated method stub		
		Log.i(LOG_TAG, "ChatPhotoView surfaceDestroyed" );
	}	
}


