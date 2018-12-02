//============================================================================
// Copyright (C) 2014 Brett R. Jones
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

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.widget.ListView;

public class ActivityFileListBase extends ActivityListBase
{
	private static final String LOG_TAG = "ActivityFileListBase:";

	//=== vars ===//
	private 	ArrayList<VxFileInfo> 	m_FileList 			= null;
	public 		FileListAdapter 		m_FileListAdapter 	= null;
	private 	Handler 				m_MessageHandler 	= null;

	//========================================================================
	@Override
	public void onCreate(Bundle savedInstanceState) 
	{
 		super.onCreate(savedInstanceState);
		Log.i(LOG_TAG, " onCreate");
		
		this.m_FileList = new ArrayList<VxFileInfo>();	
		this.m_FileListAdapter = new FileListAdapter( this, R.layout.file_list_item, m_FileList );
		setListAdapter( this.m_FileListAdapter );
		
		m_MessageHandler = new Handler() 
		{
		    @Override
		    public void handleMessage(Message msg) 
		    {
		    	switch(msg.what)
		    	{
		    	case Constants.MSG_TYPE_UPDATE_FILEINFO:
		    		//Log.i(LOG_TAG, "Rxed MSG_UPDATE_FILEINFO");
		    		m_FileListAdapter.doUpdateFileInfo( (VxFileInfo) msg.obj );
		    		m_FileListAdapter.notifyDataSetChanged();
		    		break;
		    		
		    	case Constants.MSG_TYPE_REFRESH_FILELIST:
		    		//Log.i(LOG_TAG, "Rxed MSG_REFRESH_FILELIST");
		    		m_FileListAdapter.clearList();
					//Log.i(LOG_TAG, "RefreshFiles: notifyDataSetChanged ");
					m_FileListAdapter.notifyDataSetChanged();
					//Log.i(LOG_TAG, "RefreshFiles: fromGuiSendContactList ");
					//NativeTxTo.fromGuiSendContactList( m_iWhoToViewInList );		    		
		    		break;

		    	case Constants.MSG_TYPE_CLEAR_FILELIST:
		    		//Log.i(LOG_TAG, "Rxed MSG_TYPE_CLEAR_FILELIST");
		    		m_FileListAdapter.clearList();
					//Log.i(LOG_TAG, "RefreshFiles: notifyDataSetChanged ");
					m_FileListAdapter.notifyDataSetChanged();
		    		break;
		    	}
		    	
		    	super.handleMessage(msg);
		    }
		};
	}
	
	//========================================================================
	@Override
	public void onDestroy() 
	{
		m_FileListAdapter.clearList();
		m_MessageHandler = null;
 		super.onDestroy();
	}

	//========================================================================
	public void refreshFileList() 
	{
		Message msg; 
		msg = Message.obtain(); 
		msg.what = Constants.MSG_TYPE_REFRESH_FILELIST;   
		m_MessageHandler.sendMessage(msg); 
	}	  
    
	//========================================================================
	public void updateFileInfo( VxFileInfo fileInfoIn ) 
	{
		Message msg; 
		msg = Message.obtain(); 
		msg.what = Constants.MSG_TYPE_UPDATE_FILEINFO;   
		msg.obj = fileInfoIn;
		m_MessageHandler.sendMessage(msg); 
	}
    
	//========================================================================
	public void clearContactList() 
	{
		Message msg; 
		msg = Message.obtain();
		msg.what = Constants.MSG_TYPE_CLEAR_FILELIST;   
		msg.obj = null;
		m_MessageHandler.sendMessage(msg); 
	}

	//========================================================================
	@Override
	public void onListItemClick(ListView parent, View v, int position, long id) 
	{
		VxFileInfo fileInfo = m_FileListAdapter.getFileByPosition(position);
		if( null != fileInfo ) 
		{
			Log.i(LOG_TAG, "onListItemClick " + fileInfo.getFullFileName() );
			//m_MyApp.setCurrentFileInfo( fileInfo );
			//m_MyApp.ShowPopupMenu(Constants.MENU_FILEINFO);
		}
	}
	
};
