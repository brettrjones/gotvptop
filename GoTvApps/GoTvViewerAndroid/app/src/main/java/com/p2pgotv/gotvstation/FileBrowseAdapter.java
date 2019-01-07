//============================================================================
// Copyright (C) 2011 Brett R. Jones
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

import java.util.ArrayList;
import java.util.concurrent.Semaphore;

import android.content.Context;
import android.graphics.Bitmap;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.TextView;

class FileBrowseAdapter extends ArrayAdapter<VxFileInfo> 
{	
	//=== constants ===//
	private static final String LOG_TAG = "FileBrowsedAdapter:";  
	
	//=== vars ===//
	private Semaphore m_oMutex = new Semaphore(1);
	public ArrayList<VxFileInfo> m_FileInfoItems = new  ArrayList<VxFileInfo>();

	//======================================================================== 
	public FileBrowseAdapter( Context context, int textViewResourceId, ArrayList<VxFileInfo> items ) 
    {
		super(context, textViewResourceId, items);
		lockBrowseAdapter();
        this.m_FileInfoItems = items;
        unlockBrowseAdapter();
    }
	
	//======================================================================== 
	public void lockBrowseAdapter()
	{
		try 
		{
			m_oMutex.acquire();
		} 
		catch (InterruptedException e) 
		{
			e.printStackTrace();
		}	
	}
	
	//======================================================================== 
	public void unlockBrowseAdapter()
	{
        m_oMutex.release();		
	}
	
	//======================================================================== 
	public void clearList()
	{
		lockBrowseAdapter();
		this.m_FileInfoItems.clear();
		unlockBrowseAdapter();
	}
	
	//======================================================================== 
    @Override
    public View getView(int position, View convertView, ViewGroup parent) 
    {
    	View fileItemView = convertView;
        if( null == fileItemView ) 
        {
        	LayoutInflater vi = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        	fileItemView = vi.inflate( R.layout.file_browse_item, null );
        }
        
        lockBrowseAdapter();
        VxFileInfo fileInfo = m_FileInfoItems.get( position );
        if( null != fileInfo ) 
        {
            TextView fileNameText 		= (TextView) fileItemView.findViewById( R.id.file_browse_filename );
            TextView fileSizeText 		= (TextView) fileItemView.findViewById( R.id.file_browse_filesize );
            Button libraryButton 		= (Button) fileItemView.findViewById( R.id.file_browse_library_button );
            Button shareFileButton 		= (Button) fileItemView.findViewById( R.id.file_browse_share_button );
       	 	LinearLayout actionButtonsLayout = (LinearLayout) fileItemView.findViewById( R.id.file_browse_action_layout );
         
            if( Constants.VXFILE_TYPE_DIRECTORY == fileInfo.getFileType() )
            {
            	 fileNameText.setText( fileInfo.getFilePath() );  
            	 actionButtonsLayout.setVisibility( View.GONE );
            }
            else
            {
           	 	actionButtonsLayout.setVisibility( View.VISIBLE );
	            fileNameText.setText( fileInfo.getJustFileName() );                            
	            fileSizeText.setText( fileInfo.describeFileLength() );
            }
         
            ImageButton fileIconButton = (ImageButton)fileItemView.findViewById(R.id.file_browse_icon_button);
            boolean photoIsSet = false;
            if( fileInfo.isPhoto() )
            {
            	int imageSize =  VxImageUtil.dpToPixels( getContext(), 43 );
           		Bitmap bmp = VxImageUtil.getSizedImageFromFile( fileInfo.getFullFileName(), imageSize, imageSize );
            	if( ( null != bmp )
            		&& ( 0 != bmp.getWidth() )
            		&& ( 0 != bmp.getHeight() ) )
            	{
            		fileIconButton.setImageBitmap( bmp );
            		photoIsSet = true;
            	}           	
            }
            	
            if( false == photoIsSet )
            {
      			int iIconResource = fileInfo.getFileIconResource();
      			fileIconButton.setImageDrawable( getContext().getResources().getDrawable(  iIconResource ) ); 
            }
     		
            boolean isInLibrary = NativeTxTo.fromGuiGetIsFileInLibrary( fileInfo.getFullFileName() );
            boolean isShared = NativeTxTo.fromGuiGetIsFileShared( fileInfo.getFullFileName() );
            fileInfo.setIsInLibrary( isInLibrary );
            fileInfo.setIsShared( isShared );
            
    		if( fileInfo.getIsInLibrary() )
    		{
    			libraryButton.setBackgroundResource( R.drawable.button_library_normal );
    		}
    		else
    		{
    			libraryButton.setBackgroundResource( R.drawable.button_library_cancel );   			
    		}
       		
    		if( fileInfo.getIsShared() )
    		{
    			shareFileButton.setBackgroundResource( R.drawable.button_share_files_normal );
    		}
    		else
    		{
    			shareFileButton.setBackgroundResource( R.drawable.button_share_files_cancel );   			
    		}
        }
        else
        {
            Log.e( LOG_TAG, "getView null ident at position " + position );      	
        }
        
        unlockBrowseAdapter();
        return fileItemView;
    }
    
	//========================================================================   
    public VxFileInfo getFileByPosition( int iPosition )
    {
    	if( iPosition < m_FileInfoItems.size() )
    	{    
    		VxFileInfo fileInfo = m_FileInfoItems.get( iPosition );
    		fileInfo.setListIndex( iPosition );
     		return fileInfo;
    	}
    	
  	    Log.i(LOG_TAG, "unable to get file browse info at " + iPosition );
		return null;
    }
    
	//========================================================================        
	public void doUpdateFileInfo( VxFileInfo fileIn )  
    {
		lockBrowseAdapter();
		boolean bFoundFile = false;
		Log.i(LOG_TAG, "doUpdateFileInfo " );  
		
		int iPosition = 0;
		for( VxFileInfo fileItem: m_FileInfoItems )
		{
			if( ( fileItem.getFullFileName() == fileIn.getFullFileName() ) &&
				( fileItem.getFilePath() == fileIn.getFilePath() ) )
			{
				bFoundFile = true;
		   	    Log.i(LOG_TAG, "found file " + fileIn.getFullFileName() );    			
		   	    m_FileInfoItems.set( iPosition, fileIn ); 
		   	    Log.i(LOG_TAG, "found file updating  " );    			
		   	    			
				break;  			
			}
			
			iPosition++; 
		}
		
		if( false == bFoundFile )
		{
		    Log.i(LOG_TAG, "adding file " + fileIn.getFullFileName() );    	
		    m_FileInfoItems.add( fileIn );
		}
		
		Log.i(LOG_TAG, "friend list count " + m_FileInfoItems.size() );
        unlockBrowseAdapter();
    }
    
	//========================================================================        
	public void removeFile( VxFileInfo fileIn )  
    {
		int iPosition = 0;
		for( VxFileInfo fileItem: m_FileInfoItems )
		{
			if( fileItem.getFullFileName() == fileIn.getFullFileName() ) 
			{
		   	    Log.i(LOG_TAG, "removing file " + fileIn.getFullFileName() + " at " + iPosition  );    			
		   	    m_FileInfoItems.remove( iPosition ); 
				break;  			
			}
			
			iPosition++;
		}
    }
}
