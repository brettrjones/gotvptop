/*
 * Copyright (C) 2015 Emanuel Moecklin
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
//============================================================================
// modified for MyP2PWeb by Brett R. Jones
// brett1900@usa.com
// http://www.gotvp2p.net
//============================================================================

package com.p2pgotv.gotvstation.rteditor.spans;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Rect;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.util.Log;

import com.p2pgotv.gotvstation.VxFileUtil;
import com.p2pgotv.gotvstation.VxImageUtil;
import com.p2pgotv.gotvstation.rteditor.api.RTApi;
import com.p2pgotv.gotvstation.rteditor.api.format.RTFormat;
import com.p2pgotv.gotvstation.rteditor.api.media.RTMedia;
import com.p2pgotv.gotvstation.rteditor.media.MediaUtils;

/**
 * A wrapper around android.text.style.ImageSpan that holds
 * the RTMedia object and whether the media was saved or not.
 */
public abstract class MediaSpan extends android.text.style.ImageSpan 
{
	public static final String 		LOG_TAG 	= "MediaSpan:";
    final protected 	RTMedia 	mMedia;

    // when saving the text delete the Media if the MediaSpan was removed from the text
    // when dismissing the text delete the Media if the MediaSpan was removed from the text and if the Media wasn't saved
    final private boolean 		m_IsSaved;
    private boolean 			m_IsRelativePath	= false;
    private Drawable			m_RelativeDrawable	= null;
    private String				m_RootDir			= "";
    private String				m_MediaPath			= "";
    private Context				m_AppContext		= null;

    //============================================================================
    public MediaSpan( RTMedia media, boolean isSaved, boolean isRelativePath, String rootPath ) 
    {
    	super( RTApi.getApplicationContext(), isRelativePath ? MediaUtils.createFileUri( rootPath + media.getFilePath( RTFormat.SPANNED ) ) : MediaUtils.createFileUri( media.getFilePath( RTFormat.SPANNED ) ) ); 
        m_AppContext		= RTApi.getApplicationContext();
        m_RootDir 			= rootPath;
        m_MediaPath			= media.getFilePath( RTFormat.SPANNED );
        mMedia 				= media;
        m_IsSaved 			= isSaved;
        m_IsRelativePath 	= isRelativePath;
    	if( ( null == m_RootDir ) || m_RootDir.isEmpty() )
    	{
    		Log.e( LOG_TAG, "ERROR NULL ROOT DIR" );
    	}
    }

    //============================================================================
    public RTMedia getMedia() 
    {
        return mMedia;
    }

   //============================================================================
    public boolean isSaved() 
    {
        return m_IsSaved;
    }

    //============================================================================
	public boolean isRelativePath()
	{
		if( m_IsRelativePath )
		{
			return true;
		}
		
		if( ( null != m_RootDir ) && ( null != m_MediaPath ) )
		{
			if( VxFileUtil.fileExists( m_RootDir + m_MediaPath ) )
			{
				m_IsRelativePath = true;
			}			
		}
		
		return m_IsRelativePath;
	}
	
    //============================================================================
	public String getRelativePath()
	{
		return m_RootDir;
	}
	
    //============================================================================
    public Drawable	getDrawable()
    {
    	if( isRelativePath() )
    	{
    		return getDrawableFromRelativePath();
    	}
    	else
    	{
    		return super.getDrawable();
    	}
    }
	
    //============================================================================
    //@SuppressWarnings("deprecation")
	private Drawable getDrawableFromRelativePath()
    {
    	if( null == m_RelativeDrawable )
    	{
           	if( ( null == m_RootDir ) || m_RootDir.isEmpty() )
        	{
        		Log.e( LOG_TAG, "ERROR NULL ROOT DIR" );
        		return null;
        	}
           	
           	if( ( null == m_MediaPath ) || m_MediaPath.isEmpty() )
        	{
        		Log.e( LOG_TAG, "ERROR NULL m_MediaPath" );
        		return null;
        	}
           	
           	String fileName = m_RootDir + m_MediaPath;
           	if( false == VxFileUtil.fileExists( fileName ) )
           	{
           		Log.e( LOG_TAG, "getDrawableFromRelativePath file does not exist " + fileName );
        		return null;
           	}
 
    		Bitmap bmp = VxImageUtil.getStdSizeBitmapFromFile( fileName );
    		if( null != bmp )
    		{
    			m_RelativeDrawable = new BitmapDrawable( m_AppContext.getResources(), bmp );  
        		if( null != m_RelativeDrawable )
        		{
        			Rect bmpRect = new Rect( 0, 0, bmp.getWidth(), bmp.getHeight() );
        			m_RelativeDrawable.setBounds( bmpRect );
        		}
        		else
        		{
        			Log.e( LOG_TAG, "getDrawableFromRelativePath failed decode bmp from file " + fileName );        			
        		}
    		}
    		else
    		{
    			Log.e( LOG_TAG, "getDrawableFromRelativePath null bmp from file " + fileName );
    		}
    	}
    	
    	return m_RelativeDrawable;
    }
}
