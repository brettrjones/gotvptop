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
//import java.util.Iterator;

//import android.app.ProgressDialog;
import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.TextView;

class FileListAdapter extends ArrayAdapter<VxFileInfo> 
{	
	//=== constants ===//
	private static final String LOG_TAG = "FileListAdapter:";  
	
	//=== vars ===//
	private ArrayList<VxFileInfo> 	items;

	private Semaphore m_oMutex = new Semaphore(1);
	public ArrayList<VxFileInfo> m_FilesToUpdate = new  ArrayList<VxFileInfo>();

	//======================================================================== 
	public FileListAdapter(Context context, int textViewResourceId, ArrayList<VxFileInfo> items) 
    {
		super(context, textViewResourceId, items);
		lockFileListAdapter();
        this.items = items;
        unlockFileListAdapter();
    }
	
	//======================================================================== 
	public void lockFileListAdapter()
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
	public void unlockFileListAdapter()
	{
        m_oMutex.release();		
	}
	
	//======================================================================== 
	public void clearList()
	{
		lockFileListAdapter();
		this.items.clear();
		unlockFileListAdapter();	
	}
	
	//======================================================================== 
    @Override
    public View getView(int position, View convertView, ViewGroup parent) 
    {
		try 
		{
			m_oMutex.acquire();
		} 
		catch (InterruptedException e) 
		{
			e.printStackTrace();
		}
		
		Log.i(LOG_TAG, "getView position " + position );
    	View friendView = convertView;
        if( null == friendView ) 
        {
        	LayoutInflater vi = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        	friendView = vi.inflate(R.layout.file_list_item, null);
        }
        
        VxFileInfo fileInfo = items.get(position);
        if( null != fileInfo ) 
        {
            TextView topText = (TextView) friendView.findViewById(R.id.toptext);
            TextView bottomText = (TextView) friendView.findViewById(R.id.bottomtext);
            TextView statsText = (TextView) friendView.findViewById(R.id.stats_text);
           
            //int iTextColor = Constants.OFFLINE_TEXT_COLOR;
            if( null != topText ) 
            {
            	//topText.setTextColor( iTextColor );
            	topText.setText( fileInfo.getJustFileName() );                            
            }
            
            if( null != bottomText ) 
            {
            	//bottomText.setTextColor(iTextColor);
            	bottomText.setText( fileInfo.getFilePath() );
            }

            if( null != statsText ) 
            {
            	//statsText.setTextColor(iTextColor);
            	statsText.setText( fileInfo.describeFileLength() );
            }
         
            int iIconResource = fileInfo.getFileIconResource();
 
    		ImageView view_icon = (ImageView)friendView.findViewById(R.id.file_icon);
       	    Log.i(LOG_TAG, "icon " + view_icon.toString() );
    		view_icon.setImageResource( iIconResource );
        }
        else
        {
            Log.e(LOG_TAG, "getView null ident at position " + position );      	
        }
        
        m_oMutex.release();
        return friendView;
    }
    
	//========================================================================   
    public VxFileInfo getFileByPosition( int iPosition )
    {
		try 
		{
			m_oMutex.acquire();
		} 
		catch (InterruptedException e) 
		{
			e.printStackTrace();
		}
		
    	if( iPosition < items.size() )
    	{    
    		VxFileInfo oFileInfo = items.get( iPosition );
            m_oMutex.release();		
    		return oFileInfo;
    	}
    	
        m_oMutex.release();
   	    Log.i(LOG_TAG, "unable to get friend at " + iPosition );
		return null;
    }
    
	//========================================================================        
	public void doUpdateFileInfo(VxFileInfo fileIn)  
    {
		try 
		{
			m_oMutex.acquire();
			boolean bFoundFile = false;
	   	    Log.i(LOG_TAG, "doUpdateFileInfo " );  
	    	
	   	    int iPosition = 0;
	    	for( VxFileInfo fileItem:  items )
	    	{
	    		if( ( fileItem.getFullFileName() == fileIn.getFullFileName() ) &&
	    			( fileItem.getFilePath() == fileIn.getFilePath() ) )
	    		{
	    			bFoundFile = true;
	       	   	    Log.i(LOG_TAG, "found file " + fileIn.getFullFileName() );    			
	       	   	    items.set(iPosition, fileIn ); 
	       	   	    Log.i(LOG_TAG, "found file updating  " );    			
	       	   	    			
	    			break;  			
	    		}
	    		iPosition++; 
	    	}
	    	
	    	if( false == bFoundFile )
	    	{
		   	    Log.i(LOG_TAG, "adding file " + fileIn.getFullFileName() );    	
	    		items.add( fileIn );
	    	}
	    	
	    	Log.i(LOG_TAG, "friend list count " + items.size() );
	        m_oMutex.release();  
		} 
		catch (InterruptedException e) 
		{
			e.printStackTrace();
		}
    }
}
