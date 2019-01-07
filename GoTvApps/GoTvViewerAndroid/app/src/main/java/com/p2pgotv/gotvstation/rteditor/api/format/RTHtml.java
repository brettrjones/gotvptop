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

package com.p2pgotv.gotvstation.rteditor.api.format;

import android.util.Log;

import com.p2pgotv.gotvstation.rteditor.api.RTMediaFactory;
import com.p2pgotv.gotvstation.rteditor.api.media.RTAudio;
import com.p2pgotv.gotvstation.rteditor.api.media.RTImage;
import com.p2pgotv.gotvstation.rteditor.api.media.RTVideo;
import com.p2pgotv.gotvstation.rteditor.converter.ConverterHtmlToSpanned;
import com.p2pgotv.gotvstation.rteditor.converter.ConverterHtmlToText;

import java.util.ArrayList;
import java.util.List;

/**
 * RTText representing an html text.
 * <p>
 * The text may contain referenced images.
 * Audio and video files aren't supported yet.
 */
public class RTHtml<I extends RTImage, A extends RTAudio, V extends RTVideo> extends RTText {

	private static final String LOG_TAG = "RTHtml: ";

    private List<I> 			mImages;
    private String				m_RootDir 		= "";

    //============================================================================
    public RTHtml( String rootDir, CharSequence html ) 
    {
        this( rootDir, RTFormat.HTML, html);
    }

    //============================================================================
    public RTHtml( String rootDir, RTFormat.Html rtFormat, CharSequence html) 
    {
        this( rootDir, rtFormat, html, new ArrayList<I>());
    }

    //============================================================================
    public RTHtml( String rootDir, RTFormat.Html rtFormat, CharSequence html, List<I> images) 
    {
        super(rtFormat, html);
        m_RootDir		= rootDir;
    	if( ( null == m_RootDir ) || m_RootDir.isEmpty() )
    	{
    		Log.e( LOG_TAG, "ERROR NULL ROOT DIR" );
    	}

        mImages 		= images;
    }

    //============================================================================
    @Override
    public String getText() 
    {
        CharSequence text = super.getText();
        return text != null ? text.toString() : "";
    }

    //============================================================================
    public List<I> getImages() 
    {
        return mImages;
    }

    //============================================================================
    @Override
    public RTText convertTo( String rootDir, RTFormat destFormat, RTMediaFactory<RTImage, RTAudio, RTVideo> mediaFactory ) 
    {
    	m_RootDir = rootDir;
    	mediaFactory.setRootPath( m_RootDir );
    	if( ( null == m_RootDir ) || m_RootDir.isEmpty() )
    	{
    		Log.e( LOG_TAG, "ERROR NULL ROOT DIR" );
    	}
    	if( ( null == mediaFactory.getRootPath() ) || mediaFactory.getRootPath().isEmpty() )
    	{
    		Log.e( LOG_TAG, "ERROR NULL MEDIA FACTORY ROOT DIR" );
    	}

        if (destFormat instanceof RTFormat.PlainText) 
        {
            return ConverterHtmlToText.convert(this);
        } 
        else if (destFormat instanceof RTFormat.Spanned) 
        {
            return new ConverterHtmlToSpanned().convert( m_RootDir, this, mediaFactory);
        }

        return super.convertTo( rootDir, destFormat, mediaFactory );
    }
}
