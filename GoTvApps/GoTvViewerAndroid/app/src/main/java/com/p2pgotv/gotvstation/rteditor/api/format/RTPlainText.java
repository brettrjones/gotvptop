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

import android.text.SpannedString;

import com.p2pgotv.gotvstation.rteditor.api.RTMediaFactory;
import com.p2pgotv.gotvstation.rteditor.api.media.RTAudio;
import com.p2pgotv.gotvstation.rteditor.api.media.RTImage;
import com.p2pgotv.gotvstation.rteditor.api.media.RTVideo;
import com.p2pgotv.gotvstation.rteditor.converter.ConverterTextToHtml;

/**
 * RTText representing plain text (no formatting).
 */
public final class RTPlainText extends RTText {

    public RTPlainText(CharSequence text) {
        super(RTFormat.PLAIN_TEXT, text);
    }

    @Override
    public String getText() 
    {
        CharSequence text = super.getText();
        return text != null ? text.toString() : "";
    }

    @Override
    public RTText convertTo( String rootPath, RTFormat destFormat, RTMediaFactory<RTImage, RTAudio, RTVideo> mediaFactory) 
    {
        if (destFormat instanceof RTFormat.Html) 
        {
            return ConverterTextToHtml.convert( rootPath, this );
        } 
        else if (destFormat instanceof RTFormat.Spanned) 
        {
            return new RTSpanned(new SpannedString(getText()));
        }

        return super.convertTo( rootPath, destFormat, mediaFactory);
    }
}