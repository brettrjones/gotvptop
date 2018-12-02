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
import android.graphics.Bitmap;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.TextView;

public class ReuseFileDisplayLogic 
{
	Activity					m_Activity 				= null;
	VxFileInfo					m_FileInfo				= null;
	ImageButton						m_FileIconBut			= null;
 	TextView					m_FileNameTextView		= null;
 	TextView					m_FileSizeTextView		= null;
 	TextView					m_FilePathTextView		= null;
 	
 	public	ImageButton getFileIconBut() 					{ return m_FileIconBut; }
	
	public void fillFileDisplayGui( Activity activity, VxFileInfo fileInfo )
	{
		m_Activity = activity;
		m_FileInfo = fileInfo;
		if( ( null != m_Activity ) && ( null != m_FileInfo ) )
		{
			m_FileIconBut 		= (ImageButton)m_Activity.findViewById(R.id.file_display_icon_button);
			m_FileNameTextView	= (TextView)m_Activity.findViewById(R.id.file_display_filename);
			m_FileSizeTextView	= (TextView)m_Activity.findViewById(R.id.file_display_filesize);
			m_FilePathTextView	= (TextView)m_Activity.findViewById(R.id.file_display_path);
			if( null != m_FileIconBut )
			{
	            boolean photoIsSet = false;
	            if( m_FileInfo.isPhoto() )
	            {
	            	int imageSize =  VxImageUtil.dpToPixels( activity, 43 );
	           		Bitmap bmp = VxImageUtil.getSizedImageFromFile( m_FileInfo.getFullFileName(), imageSize, imageSize );
	            	if( ( null != bmp )
	            		&& ( 0 != bmp.getWidth() )
	            		&& ( 0 != bmp.getHeight() ) )
	            	{
	            		m_FileIconBut.setImageBitmap( bmp );
	            		photoIsSet = true;
	            	}           	
	            }
	            	
	            if( false == photoIsSet )
	            {
	      			int iIconResource = m_FileInfo.getFileIconResource();
	      			m_FileIconBut.setImageDrawable( m_Activity.getDrawable(  iIconResource ) ); 	
	            }
			}
	
			if( null != m_FileNameTextView )
			{
				m_FileNameTextView.setText( m_FileInfo.getJustFileName() );
			}
			
			if( null != m_FileSizeTextView )
			{
				m_FileSizeTextView.setText( m_FileInfo.describeFileLength() );
			}
			
			if( null != m_FilePathTextView )
			{
				m_FilePathTextView.setText( m_FileInfo.getFilePath() );
			}
		}		
	}
}
