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

package com.p2pgotv.gotvstation.rteditor.api.media;

import com.p2pgotv.gotvstation.rteditor.api.format.RTFormat;

import java.io.Serializable;

/**
 * This is the base Interface describing a rich text media object. Currently
 * only absolute file path are supported for embedded media objects (images,
 * audio files, videos).
 * <p>
 * Note that every RTMedia object has to be Serializable.
 */
public abstract interface RTMedia extends Serializable 
{
	public void setFilePath(String fileNameAndPath);
    /**
     * Returns the file path of the media file (e.g. /data/.../image.png).
     * This can be any format used to locate the file (content://..., file://..., cid:...).
     */
    public String getFilePath(RTFormat format);

    /**
     * Returns the file name (e.g. image.png)
     */
    public String getFileName();

    /**
     * Returns the file extension (e.g. png)
     */
    public String getFileExtension();

    /**
     * @return True if the media file exists, False otherwise
     */
    public boolean exists( String rootPath );

    /**
     * Remove / delete the media file. This is used if the user removes the
     * object in the editor or if the content of the editor is dismissed (not
     * saved).
     */
    public void remove();

    /**
     * @return The width of the media
     */
    public int getWidth();

    /**
     * @return The height of the media
     */
    public int getHeight();

    /**
     * @return The size of the media in bytes
     */
    public long getSize( String rootPath );

}