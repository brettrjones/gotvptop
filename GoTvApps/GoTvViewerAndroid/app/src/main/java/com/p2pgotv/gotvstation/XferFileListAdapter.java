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

import java.io.File;
import java.util.ArrayList;
import java.util.concurrent.Semaphore;

import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.TextView;

public class XferFileListAdapter extends ArrayAdapter<XferFileItemInfo> 
{
	private static final String LOG_TAG = "NaveFileListAdapter: ";

	private ArrayList<XferFileItemInfo> 	m_oItems;
	private Context 						m_oContext = null;
	private	int								m_EXferDirection = Constants.eXferToMe;
	private Semaphore 						m_oListMutex = new Semaphore(1); 


	public XferFileListAdapter(Context context, int textViewResourceId, ArrayList<XferFileItemInfo> items) 
	{
		super(context, textViewResourceId, items);
		this.m_oItems = items;
		this.m_oContext = context;
	}
	/**
	* Code invoked when container notifies data set of change.
	*/
	@Override
	public View getView(int position, View convertView, ViewGroup parent) 
	{
		View view = convertView;
		if ( view == null ) 
		{
			LayoutInflater vi = (LayoutInflater)m_oContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
			view = vi.inflate(R.layout.xfer_file_row, null);
		}
		
		XferFileItemInfo fileInfo = m_oItems.get(position);
		
		updateInfoGui( view, fileInfo );

		return view;
	}
	
	private void updateInfoGui(View view, XferFileItemInfo fileInfo)
	{
		ImageView iconPos1 = null;
		ImageView iconPos2 = null;
		ImageView iconPos3 = null;
		TextView fileName = null;
		//TextView fileDesc = null;
		ProgressBar progressBar = null;

		if( null != fileInfo ) 
		{
			iconPos1 = (ImageView) view.findViewById(R.id.rowfile_pos1_icon);
			//iconPos2 = (ImageView) view.findViewById(R.id.rowfile_pos2_icon);
			//iconPos3 = (ImageView) view.findViewById(R.id.rowfile_pos3_icon);
			fileName = (TextView) view.findViewById(R.id.rowfile_name);
			//fileDesc = (TextView) view.findViewById(R.id.rowfile_desc);
			progressBar = (ProgressBar) view.findViewById(R.id.rowfile_progress);
		}
		else
		{
			Log.i(LOG_TAG, "NULL fileInfo");
			return;
		}
	
		if( null != fileName ) 
		{
			fileName.setText( fileInfo.getFileName() );
		}
		else
		{
			Log.i(LOG_TAG, "NULL fileName");
		}
	
		/*
		if( null != fileDesc ) 
		{
			if( null != fileInfo.getFileDesc() )
			{
				fileDesc.setText( fileInfo.getFileDesc() );
			}
		}
		else
		{
			Log.i(LOG_TAG, "NULL fileDesc");
		}*/
	
		if( null != iconPos1 ) 
		{
			iconPos1.setImageResource(fileInfo.getIconPos1());
		}
		else
		{
			Log.i(LOG_TAG, "NULL iconPos1");
		}
		
		/*
		if( null != iconPos2 ) 
		{
			iconPos2.setImageResource(fileInfo.getIconPos2());
		}
		else
		{
			Log.i(LOG_TAG, "NULL iconPos2");
		}
	
		if( null != iconPos3 ) 
		{
			iconPos3.setImageResource(fileInfo.getIconPos3());
		}
		else
		{
			Log.i(LOG_TAG, "NULL iconPos3");
		}	
		*/
		
		if( null != progressBar ) 
		{
			progressBar.setProgress(fileInfo.getProgress());
		}
		else
		{
			Log.i(LOG_TAG, "NULL progressBar");
		}		
	}
	
	public XferFileItemInfo getFileInfoAtPosition( int position )
	{
		return m_oItems.get(position);	
	}
	
	public int getXferDirection() 
	{
		return m_EXferDirection;
	}
	
	public void setXferDirection(int eXferDirection) 
	{
		this.m_EXferDirection = eXferDirection;
	}

	public XferFileItemInfo findFileInfo( String fileName )
	{
		XferFileItemInfo info;
		for( int i = 0; i < m_oItems.size(); ++i )
		{
			info = m_oItems.get(i);
			if( info.getFileName() == fileName )
			{
				info.m_Position = i;
				return info;
			}
		}
		return null;	
	}

	//========================================================================
	public void processFileStateInfo( FileStateInfo fileStateInfo )
	{
		try {
			m_oListMutex.acquire();
			XferFileItemInfo info = findFileInfo( fileStateInfo.getFileName() );
			if( null != info )
			{
				Log.i(LOG_TAG, "processFileStateInfo updating " + fileStateInfo.getFileName() );
				info.setPrevState( fileStateInfo.getPrevState() );
				info.setNewState( fileStateInfo.getNewState() );	
				notifyDataSetChanged();
			}
			else
			{
				Log.i(LOG_TAG, "processFileStateInfo adding " + fileStateInfo.getFileName() );
				info = new XferFileItemInfo();
				info.setFileName( fileStateInfo.getFileName() );
				info.setPrevState(fileStateInfo.getPrevState());
				info.setNewState(fileStateInfo.getNewState());
				
				m_oItems.add(info);
				notifyDataSetChanged();		
			}
			m_oListMutex.release();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
	//========================================================================
	public void processFileProgressInfo( XferFileProgressInfo fileProgressInfo )
	{
		XferFileItemInfo info = findFileInfo( fileProgressInfo.getFileName() );
		if( null != info )
		{
			Log.i(LOG_TAG, "processFileProgressInfo " + fileProgressInfo.getFileName() );
			info.setProgress( fileProgressInfo.getProgress() );
			notifyDataSetChanged();
		}
		else
		{
			Log.i(LOG_TAG, "processFileStateInfo NULL XferFileItemInfo");
		}
		
	}

}