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
import android.view.View.MeasureSpec;

//============================================================================
public class VideoFilePlaybackView extends CamViewBase
{
	private static final String LOG_TAG = "VideoFilePlaybackView:";
	
	private String					m_FileName 						= "";
	private VxGUID					m_AssetGuid						= null;
	private AssetGuiInfo			m_AssetGuiInfo					= null;
	private boolean					m_IsVisible						= false;
	
	//========================================================================
	public void setFileNameAndId( String fileName, VxGUID assetGuid )
	{
		m_FileName 		= fileName;
		m_AssetGuid		= assetGuid;
		m_AssetGuiInfo = new AssetGuiInfo();
		m_AssetGuiInfo.setAssetType( Constants.eAssetTypeVideo );
		m_AssetGuiInfo.setAssetName( m_FileName );
		m_AssetGuiInfo.setAssetUniqueId( assetGuid );
		
		
		if( m_IsVisible )
		{
			applyState();
		}
	}
	
	//========================================================================
	public void applyState()
	{
		if( ( m_FileName.isEmpty() ) 
			|| ( 0 == m_iFinalWidth )
			|| ( 0 == m_iFinalHeight ) )
		{
			return;
		}
		
		
		setFeedMediaType( Constants.eMediaInputVideoJpgSmall );
		setVideoFeedId( m_AssetGuid );
		if( m_IsVisible )
		{
			Log.i(LOG_TAG, "VideoFilePlaybackView applyState requestVideoFeed" );
			requestVideoFeed();
			NativeTxTo.fromGuiAssetAction( Constants.eAssetActionPlayOneFrame, m_AssetGuiInfo, 0 );
		}
		else
		{
			Log.i(LOG_TAG, "VideoFilePlaybackView applyState stopVideoFeed" );
			stopVideoFeed();
		}
	}

	//============================================================================
	public VideoFilePlaybackView( Context context ) 
	{
		super(context);
		Log.i(LOG_TAG, "VideoFilePlaybackView create" );
	}

	//============================================================================
	public VideoFilePlaybackView( Context context, AttributeSet attrs ) 
	{
		super(context, attrs);
		Log.i(LOG_TAG, "VideoFilePlaybackView create" );
	}

	//============================================================================
	public VideoFilePlaybackView( Context context, AttributeSet attrs, int defStyle ) 
	{
		super(context, attrs, defStyle);
		Log.i(LOG_TAG, "VideoFilePlaybackView create" );
	}
    
	//============================================================================
	@Override
	protected void onWindowVisibilityChanged( int visiblity ) 
    {
        super.onWindowVisibilityChanged(visiblity);
		Log.i( LOG_TAG, "ChatMessageInputToolBox onWindowVisibilityChanged " + visiblity );
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
    	// keep aspect ratio
    	int width = MeasureSpec.getSize(widthMeasureSpec);	
    	int height = (int)( width * m_f32AspectRatio ); 
        this.setMeasuredDimension( width, height );  
        if( ( width != m_iFinalWidth )
        	|| ( height != m_iFinalHeight ) )
        {
        	if( ( 0 != width ) && ( 0 != height ) )
        	{
               	m_iFinalHeight 		= height;
            	m_iFinalWidth 		= width;
            	Log.i(LOG_TAG, "VideoFilePlaybackView onMeasure" );
            	applyState();
        	}
        }
   }
	
	//========================================================================	
	@Override
	protected void onFinishInflate() 
	{
		super.onFinishInflate();
		applyState();
		Log.i(LOG_TAG, "VideoFilePlaybackView onFinishInflate" );
	}
	
	//============================================================================
	@Override
    protected void onAttachedToWindow() 
    {
        super.onAttachedToWindow();
		Log.i(LOG_TAG, "VideoFilePlaybackView onAttachedToWindow" );
		applyState();
    }

	//============================================================================
    @Override
    protected void onDetachedFromWindow() 
    {
        super.onDetachedFromWindow();
		Log.i(LOG_TAG, "VideoFilePlaybackView onDetachedFromWindow" );
    }
}


