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
import android.content.Intent;
import android.os.Bundle;

import android.util.Log;
import android.view.View;
import android.view.WindowManager;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;

public class ActivitySelectFileToSend extends ActivityBase 
{
	//=== constants ===//
	public static final String LOG_TAG = "ActivitySelectFileToSend:";
	   
	//=== vars ===//
	private Spinner  			m_FileFilterSpinner 		= null;
	private Button 				m_ChooseFromLibraryBut 		= null;
	private Button  			m_BrowseDeviceFilesBut 		= null;
	private Button  			m_GalleryFilesBut 			= null;
	private Button  			m_SnapshotBut 				= null;
	private EditText  			m_OfferMsgEdit 				= null;
	private Button  			m_SendFileBut 				= null;
	
	private int  				m_FileFilterType 			= 0;
	private VxFileInfo 			m_SelectedFileInfo 			= null;
	private ReuseFileDisplayLogic  	m_FileDisplayLogic 		= new ReuseFileDisplayLogic();
	private ReuseFriendDisplayLogic m_FriendDisplayLogic 	= new ReuseFriendDisplayLogic();
	private VxNetIdent			m_HisIdent					= null;
	private VxGUID				m_LclSessionId				= new VxGUID();
	
    //========================================================================
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        setContentView(R.layout.activity_select_file_to_send);
        super.onCreate(savedInstanceState);
        setPageTitle( R.string.activity_select_file_to_send_title );
        // keep keyboard from popping up
        this.getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN); 
        m_LclSessionId.initializeWithNewGUID();
        
	 	this.m_FileFilterSpinner 	= (Spinner)this.findViewById( R.id.select_file_filter_spinner );	 	
		if( null != m_FileFilterSpinner )
		{
			fillFileFilterSpinner( m_FileFilterSpinner );
		 	m_FileFilterSpinner.setOnItemSelectedListener( new OnItemSelectedListener()
		 	{
				@Override
				public void onItemSelected(AdapterView<?> parent, View view, int position, long id) 
				{
					onFileFilterSelected( position );
				}
	
				@Override
				public void onNothingSelected(AdapterView<?> parent) 
				{
				}	 		
		 	});
		}
		
		m_ChooseFromLibraryBut = (Button)this.findViewById( R.id.select_file_from_library_button );
		if( null != m_ChooseFromLibraryBut )
		{
		 	m_ChooseFromLibraryBut.setOnClickListener(new OnClickListener() 
		 	{
		 		public void onClick(View v) 
		 		{
	  			   	onBrowseLibraryFiles_click( v );
		 		}
		 	});	
		}
 	 	
		m_BrowseDeviceFilesBut = (Button)this.findViewById(R.id.select_file_from_device_button);
		if( null != m_BrowseDeviceFilesBut )
		{
		 	this.m_BrowseDeviceFilesBut.setOnClickListener(new OnClickListener() 
		 	{
		 		public void onClick(View v) 
		 		{
	  			   	onBrowseDeviceFiles_click( v );
		 		}
		 	});	
		}
 	 	
		m_GalleryFilesBut = (Button)this.findViewById( R.id.select_file_from_gallery_button );
		if( null != m_GalleryFilesBut )
		{
		 	this.m_GalleryFilesBut.setOnClickListener(new OnClickListener() 
		 	{
		 		public void onClick(View v) 
		 		{
		 			onBrowseGalleryFiles_click( v );
		 		}
		 	});	
		}
 	 	
		m_SnapshotBut = (Button)this.findViewById( R.id.select_file_take_snapshot_button );
		if( null != m_SnapshotBut )
		{
		 	this.m_SnapshotBut.setOnClickListener(new OnClickListener() 
		 	{
		 		public void onClick(View v) 
		 		{
		 			onTakeSnapshot_click( v );
		 		}
		 	});	
		}
		
	    this.m_OfferMsgEdit 	= (EditText)this.findViewById( R.id.select_file_offer_msg_edit );		        
		this.m_SendFileBut 		= (Button)this.findViewById( R.id.select_file_send_button );
	 	this.m_SendFileBut.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
  			   	m_MyApp.playButtonClick();
	 			onSendFileClick();
	 		}
	 	});	
	 	
	 	m_HisIdent = m_MyApp.getCurrentFriend();
	 	if( null != m_HisIdent )
	 	{
	 		m_FriendDisplayLogic.fillFriendDisplayGui( this, m_HisIdent );
	 	}	 	
    }
	
	//========================================================================
	public void onFileFilterSelected( int eFileFilterType ) 
	{
		m_FileFilterType = eFileFilterType;
	}
	
	//========================================================================
	public void onBrowseLibraryFiles_click(View v) 
	{
		m_MyApp.playButtonClick();
		Intent myIntent = new Intent( ActivitySelectFileToSend.this, ActivityViewLibraryFiles.class );
		myIntent.putExtra(  Constants.PARAM_SELECT_FILE_MODE, true );
		myIntent.putExtra(  Constants.PARAM_FILE_FILTER_TYPE, m_FileFilterType );
		ActivitySelectFileToSend.this.startActivityForResult( myIntent, Constants.ACTIVITY_VIEW_LIBRARY_FILES );
	}

	//========================================================================
	public void onBrowseDeviceFiles_click(View v) 
	{
		m_MyApp.playButtonClick();
		Intent myIntent = new Intent( ActivitySelectFileToSend.this, ActivityBrowseFiles.class );
		myIntent.putExtra(  Constants.PARAM_SELECT_FILE_MODE, true );
		myIntent.putExtra(  Constants.PARAM_FILE_FILTER_TYPE, m_FileFilterType );
		ActivitySelectFileToSend.this.startActivityForResult( myIntent, Constants.ACTIVITY_BROWSE_DEVICE_FILES );
	}

	//========================================================================
	public void onBrowseGalleryFiles_click(View v) 
	{
		m_MyApp.playButtonClick();
	   	Intent myIntent = new Intent( ActivitySelectFileToSend.this, ActivityPickImage.class );
    	startActivityForResult( myIntent, Constants.ACTIVITY_PICK_IMAGE );
	}

	//========================================================================
	public void onTakeSnapshot_click(View v) 
	{
		m_MyApp.playButtonClick();
    	Intent myIntent = new Intent( ActivitySelectFileToSend.this, ActivityCameraSnapshot.class );   	
    	startActivityForResult( myIntent, Constants.ACTIVITY_CAMERA_SNAPSHOT );
	}

	//========================================================================
	public void onSendFileClick() 
	{
		String fileName = "";
		if( null != m_SelectedFileInfo )
		{
			fileName = m_SelectedFileInfo.getFullFileName();
		}
		
		if( fileName.isEmpty() )
		{
			errMsgBox( false, "No File Selected" );		
		}
		else
		{
			if( false == NativeTxTo.fromGuiMakePluginOffer(	Constants.ePluginTypeFileOffer, 
					m_HisIdent.m_u64IdHiPart,
					m_HisIdent.m_u64IdLoPart, 
	        		0, 
	        		"File Offer", 
	        		m_SelectedFileInfo.getFullFileName(),
	        		m_LclSessionId.m_u64IdHiPart,
	        		m_LclSessionId.m_u64IdLoPart ) )
			{
				showOfflineMsg();
			}
			else
			{
				finish();
			}
		}
	}
	
	//========================================================================
	void showOfflineMsg()
	{
        Toast.makeText(ActivitySelectFileToSend.this, m_HisIdent.m_as8OnlineName + " Is Offline.",
                Toast.LENGTH_SHORT).show();		
	}

	//========================================================================
	@Override
	public void onActivityResult(int requestCode, int resultCode, Intent data) 
	{
		super.onActivityResult(requestCode, resultCode, data);
		Log.d(LOG_TAG, "onActivityResult result code " + resultCode);
			
		switch (requestCode) 
		{
		case Constants.ACTIVITY_VIEW_LIBRARY_FILES:
			Log.d( LOG_TAG, "onActivityResult ACTIVITY_VIEW_LIBRARY_FILES" );
			if( resultCode == Activity.RESULT_OK ) 
			{
				m_SelectedFileInfo = m_MyApp.getCurrentFileInfo();
				if( null != m_SelectedFileInfo )
				{
					m_FileDisplayLogic.fillFileDisplayGui( this, m_SelectedFileInfo );
				}							
			}
			
			break;

		case Constants.ACTIVITY_BROWSE_DEVICE_FILES:
			Log.d( LOG_TAG, "onActivityResult ACTIVITY_BROWSE_DEVICE_FILES" );
			if( resultCode == Activity.RESULT_OK ) 
			{
				m_SelectedFileInfo = m_MyApp.getCurrentFileInfo();
				if( null != m_SelectedFileInfo )
				{
					m_FileDisplayLogic.fillFileDisplayGui( this, m_SelectedFileInfo );
				}				
			}
			
			break;
			
		case Constants.ACTIVITY_TO_FRIEND_OFFER_FILE:
			Log.d( LOG_TAG, "onActivityResult ACTIVITY_TO_FRIEND_OFFER_FILE" );
			if( resultCode == Activity.RESULT_OK ) 
			{
				
			}
			
		case Constants.ACTIVITY_PICK_IMAGE:
			if (resultCode == Activity.RESULT_OK) 
		    {
				Log.d( LOG_TAG, "onActivityResult ACTIVITY_PICK_IMAGE" );
				Bundle extras = data.getExtras(); 
		        if( null != extras ) 
		        { 
		        	String fileName 	= extras.getString( Constants.PARAM_FILE_NAME );
		        	long fileLen		= VxFileUtil.getFileLen( fileName );
		        	if( 0 != fileLen )
		        	{
		        		applyPickedPhotoFile( fileName );
		        	}
			        else
			        {
			        	Log.d(LOG_TAG, "0 File Len in Choose Image " +  fileName);
			        	Toast.makeText( this, R.string.error_file_does_not_exist, Toast.LENGTH_LONG ).show();
			        }
		        }
		        else
		        {
					Log.d(LOG_TAG, "NULL EXTRA in Choose Image" );
		        	Toast.makeText( this, R.string.error_bad_activity_param, Toast.LENGTH_LONG ).show();
		        }
		    }
			else
			{
				Log.d(LOG_TAG, "Choose Image Canceled By User" );
				Toast.makeText( this, R.string.choose_image_canceled_by_user, Toast.LENGTH_SHORT ).show();
			}
			
			break;

			case Constants.ACTIVITY_CAMERA_SNAPSHOT:
	 		{
	  			if( Activity.RESULT_OK == resultCode ) 
	      	    {
	       	        Bundle extras = data.getExtras();
			        if( null != extras ) 
			        { 
			        	String fileName 	= extras.getString( Constants.PARAM_FILE_NAME );
			        	long fileLen		= VxFileUtil.getFileLen( fileName );
			        	if( 0 != fileLen )
			        	{
			        		applyPickedPhotoFile( fileName );
			        	}
				        else
				        {
				        	Log.d(LOG_TAG, "0 File Len in Camera Snap Shot " +  fileName);
				        	Toast.makeText( this, R.string.error_file_does_not_exist, Toast.LENGTH_LONG ).show();
				        }
			        }
			        else
			        {
						Log.d(LOG_TAG, "NULL EXTRA in Camera Snap Shot" );
			        	Toast.makeText( this, R.string.error_bad_activity_param, Toast.LENGTH_LONG ).show();
			        }
	      	    }
				else
				{
					Log.d(LOG_TAG, "Take Snapshot Canceled By User" );
					Toast.makeText( this, R.string.take_snapshot_canceled_by_user, Toast.LENGTH_SHORT ).show();
				}
	 		}
			
			break;

		default:
			break;			
		}		
	}
	
	//========================================================================
	private void applyPickedPhotoFile( String fileName )
	{
    	long fileLen		= VxFileUtil.getFileLen( fileName );
    	if( 0 == fileLen )
    	{	
    		return;
    	}
    	
    	if( null == m_SelectedFileInfo )
		{
			m_SelectedFileInfo = new VxFileInfo();
		}
    	
    	m_SelectedFileInfo.setFullFileName( fileName );
    	m_SelectedFileInfo.setFileType( Constants.VXFILE_TYPE_PHOTO );
    	m_SelectedFileInfo.setFileLength( fileLen );
    	m_SelectedFileInfo.updateJustFileName();
    	m_FileDisplayLogic.fillFileDisplayGui( this, m_SelectedFileInfo );
 	}	
}
