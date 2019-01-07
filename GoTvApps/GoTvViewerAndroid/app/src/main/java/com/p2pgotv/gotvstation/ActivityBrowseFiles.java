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

import java.io.File;
import java.util.ArrayList;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.WindowManager;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.AdapterView.OnItemSelectedListener;

public class ActivityBrowseFiles  extends ActivityListBase implements ToGuiFileXferInterface
{
	//=== constants ===//
	private static final String LOG_TAG = "ActivityBrowseFiles:";
	   
	//=== vars ===//
	private Spinner  			m_FileFilterSpinner 		= null;
	private TextView  			m_DoubleTapInstructTextView = null;
	private TextView  			m_CurDirTextView 			= null;
	private String 				m_CurBrowseDirectory		= "";
	private Button 				m_UpDirectoryButton 		= null;
	private TextView 			m_UpDirectoryText 			= null;
	ArrayList<VxFileInfo> 		m_FileInfoList 				= new  ArrayList<VxFileInfo>();
	private FileBrowseAdapter	m_FileListAdapter			= null;
	private ListView			m_FileListView				= null;
	
	private static final char 	m_PathSeparator 			= '/';
	
	private boolean				m_IsSelectAFileMode			= false;
	private boolean				m_FetchInProgress			= false;	
	private int					m_eFileFilterType			= 0;
	
    //========================================================================
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        setContentView(R.layout.activity_browse_files);
        super.onCreate(savedInstanceState);
        Bundle extras = getIntent().getExtras(); 
        if( null != extras ) 
        { 
        	m_IsSelectAFileMode 	= extras.getBoolean( Constants.PARAM_SELECT_FILE_MODE );
        	m_eFileFilterType 		= extras.getInt( Constants.PARAM_FILE_FILTER_TYPE );
        } 
        
        this.getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN); // keep keyboard from popping up
        m_DoubleTapInstructTextView		= (TextView)this.findViewById( R.id.browse_files_instruction_doubletap_label );
        if( m_IsSelectAFileMode )
        {
            setPageTitle( R.string.select_a_file );
            if( null != m_DoubleTapInstructTextView )
            {
            	m_DoubleTapInstructTextView.setVisibility( View.VISIBLE );
            }      	    	
        }
        else
        {
            setPageTitle( R.string.activity_browse_files_title );
        }
     
	 	m_FileListAdapter = new FileBrowseAdapter( this, R.layout.file_browse_item, m_FileInfoList );
	 	setListAdapter( m_FileListAdapter );
	 	m_FileListView = getListView();   	       
 	    m_CurDirTextView		= (TextView)this.findViewById( R.id.browse_files_cur_dir_text );
 	 	
	 	m_FileFilterSpinner 	= (Spinner)this.findViewById( R.id.browse_files_file_filter_spinner );
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
	 		        
		this.m_UpDirectoryButton 	= (Button)this.findViewById( R.id.browse_files_up_dir_button );
	 	this.m_UpDirectoryButton.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
 			    m_MyApp.playButtonClick();
	 			onUpADirClick();
	 		}
	 	});		 
	        
		this.m_UpDirectoryText	= (TextView)this.findViewById( R.id.browse_files_up_dir_label );
		this.m_UpDirectoryText.setOnClickListener(new OnClickListener() 
		{
			public void onClick(View v) 
			{
			    m_MyApp.playButtonClick();
				onUpADirClick();
			}
		});		 
	 		 	  	 	 	
        setActivityReadyState( this );
        
        setDefaultCurrentDir( m_eFileFilterType );
 
	 	m_FileFilterSpinner.setSelection( m_eFileFilterType );
    }
    
 	//========================================================================
    protected void setDefaultCurrentDir( int eFileFilterType )
    {
	    m_CurBrowseDirectory = m_MyApp.getMySettings().getLastBrowseDir( eFileFilterType );
    	if( m_CurBrowseDirectory.isEmpty() )
    	{
    		m_CurBrowseDirectory = getDefaultDir( eFileFilterType );
    	}
	    
    	if( m_CurBrowseDirectory.isEmpty() )
    	{
    		m_CurBrowseDirectory = m_MyApp.getAppRootStorageDir();
    	}
    	   	
   		m_MyApp.getMySettings().setLastBrowseDir( eFileFilterType, m_CurBrowseDirectory );
	    m_CurDirTextView.setText( m_MyApp.removeRootStorageDir( m_CurBrowseDirectory ) ); 	
    }
    
 	//========================================================================
    protected String getDefaultDir( int eFileFilterType )
    {
    	String defaultDir = "";
    	switch( eFileFilterType )
    	{
    	case Constants.eFileFilterTypePhoto:
	    	File cameraDir = android.os.Environment.getExternalStoragePublicDirectory( android.os.Environment.DIRECTORY_DCIM );
	    	if( cameraDir.exists() )
	    	{
	    		defaultDir = cameraDir.getPath();
	    	}
	    	else
	    	{
	    		cameraDir = android.os.Environment.getExternalStoragePublicDirectory( android.os.Environment.DIRECTORY_PICTURES );
		    	if( cameraDir.exists() )
		    	{
		    		defaultDir = cameraDir.getPath();
		    	}
	    	}   	
	    	
	    	break;
	    	
    	case Constants.eFileFilterTypeAudio:
	    	File musicDir = android.os.Environment.getExternalStoragePublicDirectory( android.os.Environment.DIRECTORY_MUSIC );
	    	if( musicDir.exists() )
	    	{
	    		defaultDir = musicDir.getPath();
	    	}
	    	
	    	break;
	    	
    	case Constants.eFileFilterTypeVideo:
	    	File videoDir = android.os.Environment.getExternalStoragePublicDirectory( android.os.Environment.DIRECTORY_MOVIES );
	    	if( videoDir.exists() )
	    	{
	    		defaultDir = videoDir.getPath();
	    	}
	
	    	/* BRJ requires API 19
    	case Constants.eFileFilterTypeDocument:
	    	File documentDir = android.os.Environment.getExternalStoragePublicDirectory( android.os.Environment.DIRECTORY_DOCUMENTS );
	    	if( documentDir.exists() )
	    	{
	    		defaultDir = documentDir.getPath();
	    	}
	    	
	    	break;*/
	    	
	    default:
	    	defaultDir = m_MyApp.getUserXferDir();
	    	if( defaultDir.isEmpty() )
	    	{
	    		defaultDir = m_MyApp.getAppRootStorageDir();
	    	}    	
    	}
    	
    	if( defaultDir.isEmpty() )
    	{
    		defaultDir = m_MyApp.getAppRootStorageDir();
    	}
    	
    	return defaultDir;
    }
  
	//========================================================================
    @Override
    protected void onPause() 
    {
        setActivityReadyState( null );
     	super.onPause();    	
    }

	//========================================================================
    @Override
    protected void onResume() 
    {
        setActivityReadyState( this );
    	super.onResume();    	
    }

	//========================================================================
    @Override
    protected void onDestroy() 
    {
        setActivityReadyState( null );
     	super.onDestroy();    	
    }
    
 	//========================================================================
    protected void setActivityReadyState( Activity curActivity )
    {
		try 
		{
			if( null == curActivity )
			{
				NativeRxFrom.wantToGuiFileXferClient( this, false );
			}
			else
			{
				NativeRxFrom.wantToGuiFileXferClient( this, true );
			}
		} 
		catch (InterruptedException e) 
		{
			e.printStackTrace();
		}
    }
	
	//========================================================================
    private void onFileFilterSelected( int eFileFilterType ) 
	{
    	if( m_eFileFilterType != eFileFilterType )
    	{
    		m_eFileFilterType = eFileFilterType;
    		setDefaultCurrentDir( eFileFilterType );
    	}
		
		doRequestFileList();
	}

	//========================================================================
    private void onUpADirClick() 
	{
		// move up one directory
    	boolean newDirSet = false;
		if( m_FetchInProgress || ( null == m_CurDirTextView ) )
		{
			return;
		}
		
		if( m_CurBrowseDirectory.length() > 1 )
		{	
			String newBrowseDir = m_CurBrowseDirectory;
			int sepIdx = newBrowseDir.lastIndexOf( m_PathSeparator );
			if( sepIdx > 0 )
			{
				if( sepIdx == ( newBrowseDir.length() - 1) && ( sepIdx > 1 ) )
				{
					newBrowseDir = newBrowseDir.substring( 0, sepIdx );
					sepIdx = newBrowseDir.lastIndexOf( m_PathSeparator );
					if( sepIdx > 0 )
					{
						newBrowseDir = newBrowseDir.substring( 0, sepIdx + 1 );
						String testIfRootDir = m_MyApp.removeRootStorageDir( newBrowseDir );
						if( testIfRootDir.matches( newBrowseDir ) )
						{
							// we are at root
							m_MyApp.playSound( ESndDef.eSndDefOfferRejected );
						}
						else
						{					
							m_CurBrowseDirectory = newBrowseDir;
							m_MyApp.getMySettings().setLastBrowseDir( m_eFileFilterType, m_CurBrowseDirectory );
							newDirSet = true;
							m_CurDirTextView.setText( testIfRootDir );
						}
					}
				}
			}
			
			if( newDirSet )
			{
				doRequestFileList();				
			}
		}
	}
    
    //============================================================================
    void moveToDirectory( String newDirName )
    {
		if( m_FetchInProgress || ( null == m_CurDirTextView ) )
		{
			return;
		}
   	
		m_CurBrowseDirectory = newDirName;
		m_MyApp.getMySettings().setLastBrowseDir( m_eFileFilterType, m_CurBrowseDirectory );
		doRequestFileList();
    }

    //============================================================================
    void setActionEnable( boolean enable )
    {
    	m_FetchInProgress = enable ? false : true;

    	Log.i( LOG_TAG, "Fetch In Progress " + m_FetchInProgress );
    	m_UpDirectoryButton.setEnabled( enable );
    }

	//============================================================================
	void setFileFilter( int eFileFilter )
	{
		m_eFileFilterType = eFileFilter;
	}

	//========================================================================
	private void doRequestFileList() 
	{
		if( m_FetchInProgress )
		{
			return;
		}
		
		setActionEnable( false );
		byte fileFilterMask = VxFileUtil.getMaskFromFileFilterType( m_eFileFilterType );
		clearFileList();
		m_CurDirTextView.setText( m_MyApp.removeRootStorageDir( m_CurBrowseDirectory ) );
		m_MyApp.getMySettings().setLastBrowseDir( m_eFileFilterType, m_CurBrowseDirectory );
		NativeTxTo.fromGuiBrowseFiles( m_CurBrowseDirectory, true, fileFilterMask | Constants.VXFILE_TYPE_DIRECTORY );
	}

	//========================================================================
	private void clearFileList() 
	{
		m_FileListAdapter.clearList();
		Log.i(LOG_TAG, "clearFileList: notifyDataSetChanged ");
		m_FileListAdapter.notifyDataSetChanged();
	}
	   
	//========================================================================
	public VxFileInfo getFileInfoForItemView( View v )
	{
		// Assumes lock has been done
	   	for( int i = 0; i < m_FileListView.getCount(); i++ ) 
    	{
    		View itemView = m_FileListView.getChildAt(i);
    		if( itemView == v )
    		{
    			return m_FileListAdapter.getFileByPosition( i );
    		}
         }

		return null;
	}
	
	//========================================================================
	public void onBrowseFileIconButClick( View v )
	{
		int position = m_FileListView.getPositionForView( (View) v.getParent() );
		if( position >= 0 )
		{
			m_FileListAdapter.lockBrowseAdapter();
			VxFileInfo fileInfo = m_FileListAdapter.getFileByPosition( position );
			m_FileListAdapter.unlockBrowseAdapter();
			if( null != fileInfo )
			{
				if( fileInfo.isDirectory() )
				{
					moveToDirectory( fileInfo.getFullFileName() );
				}
				else
				{
					if( m_IsSelectAFileMode )
					{
						m_MyApp.setCurrentFileInfo( fileInfo );
						Intent resultIntent = new Intent();
			        	String fileName = fileInfo.getFullFileName();
			        	if( !fileName.isEmpty() )
			        	{				        
				        	resultIntent.putExtra( Constants.PARAM_FILE_NAME, fileInfo.getFullFileName() );
				        	resultIntent.putExtra( Constants.PARAM_FILE_TYPE_MASK, fileInfo.getFileType() );
				        } 
				        
						setResult(Activity.RESULT_OK, resultIntent);
						finish();					
					}
					else
					{
						playFile( this, fileInfo );
					}
				}
			}
		}
	}
	
	//========================================================================
	public VxFileInfo getActionButtonFileInfo( View v )
	{
		LinearLayout buttonCenterLayout = (LinearLayout) v.getParent();
		if( null != buttonCenterLayout )
		{
			LinearLayout actionButtonsLayout = (LinearLayout)buttonCenterLayout.getParent();
			if( null != actionButtonsLayout )
			{
				LinearLayout vertLayout = (LinearLayout)actionButtonsLayout.getParent();
				if( null != actionButtonsLayout )
				{
					int position = m_FileListView.getPositionForView( (View) vertLayout.getParent() );
					if( position >= 0 )
					{
						m_FileListAdapter.lockBrowseAdapter();
						VxFileInfo fileInfo = m_FileListAdapter.getFileByPosition( position );
						m_FileListAdapter.unlockBrowseAdapter();
						return fileInfo;
					}
				}
			}	
		}
		
		return null;
	}
	
	//========================================================================
	public void browseToDirectory( VxFileInfo fileInfo )
	{
		if( false == m_FetchInProgress )
		{
			String strDir = fileInfo.getFullFileName();
			if( 0 != strDir.length() )
			{
				m_CurBrowseDirectory = VxFileUtil.assureTrailingDirectorySlash( strDir );
				setActionEnable( false );
				doRequestFileList();
			}
		}		
	}
	
	//========================================================================
	public void onBrowseLibraryButClick( View v )
	{
		if( false == m_FetchInProgress )
		{
	    	Log.i(LOG_TAG, "onBrowseLibraryButClick" );
			m_MyApp.playButtonClick() ;
			VxFileInfo fileInfo = getActionButtonFileInfo( v );
			if( null != fileInfo )
			{
				if( Constants.VXFILE_TYPE_DIRECTORY == fileInfo.getFileType() )
				{
					browseToDirectory( fileInfo );
				}
				else
				{
					// is file
					// toggle is in library state
					boolean isInLib = !fileInfo.getIsInLibrary();
					fileInfo.setIsInLibrary( isInLib );
					NativeTxTo.fromGuiAddFileToLibrary(	fileInfo.getFullFileName(), 
														fileInfo.getIsInLibrary(),
														fileInfo.getFileHashId().getHashData() );
					m_FileListAdapter.notifyDataSetChanged();
					if( fileInfo.getIsInLibrary() )
					{
						m_MyApp.toGuiUserMessage( R.string.file_is_in_library );
						Toast.makeText( this, R.string.file_is_in_library, Toast.LENGTH_SHORT ).show();
					}
					else
					{
						m_MyApp.toGuiUserMessage( R.string.file_is_not_in_library );
						Toast.makeText( this, R.string.file_is_not_in_library, Toast.LENGTH_SHORT ).show();
					}
				}
			}
		}
	}
	
	//========================================================================
	public void onBrowseShareButClick( View v )
	{
		if( false == m_FetchInProgress )
		{
			Log.i(LOG_TAG, "onBrowseLibraryButClick" );
			m_MyApp.playButtonClick() ;
			VxFileInfo fileInfo = getActionButtonFileInfo( v );
			if( null != fileInfo )
			{
				if( Constants.VXFILE_TYPE_DIRECTORY == fileInfo.getFileType() )
				{
					browseToDirectory( fileInfo );
				}
				else
				{
					// is file
					// toggle is in library state
					boolean isShared = !fileInfo.getIsShared();
					fileInfo.setIsShared( isShared );
					NativeTxTo.fromGuiSetFileIsShared( fileInfo.getFullFileName(), fileInfo.getIsShared(), fileInfo.getFileHashData() );
					m_FileListAdapter.notifyDataSetChanged();
					if( fileInfo.getIsShared() )
					{
						m_MyApp.toGuiUserMessage( R.string.file_is_shared );
						Toast.makeText( this, R.string.file_is_in_shared_list, Toast.LENGTH_SHORT ).show();
					}
					else
					{
						m_MyApp.toGuiUserMessage( R.string.file_is_not_shared );
						Toast.makeText( this, R.string.file_is_not_shared, Toast.LENGTH_SHORT ).show();
					}
				}
			}	
		}
	}
	
	//========================================================================
	public void onBrowsePlayButClick( View v )
	{
		if( false == m_FetchInProgress )
		{
			Log.i(LOG_TAG, "onBrowsePlayButClick" );
			m_MyApp.playButtonClick() ;
			VxFileInfo fileInfo = getActionButtonFileInfo( v );
			if( null != fileInfo )
			{
				if( Constants.VXFILE_TYPE_DIRECTORY == fileInfo.getFileType() )
				{
					browseToDirectory( fileInfo );
				}
				else
				{
					playFile( this, fileInfo );
				}	
			}
		}
	}
	
	//========================================================================
	public void onBrowseShredButClick( View v )
	{
		if( false == m_FetchInProgress )
		{
			Log.i(LOG_TAG, "onBrowseShredButClick" );
			m_MyApp.playButtonClick() ;
			VxFileInfo fileInfo = getActionButtonFileInfo( v );
			if( null != fileInfo )
			{
				if( Constants.VXFILE_TYPE_DIRECTORY == fileInfo.getFileType() )
				{
					browseToDirectory( fileInfo );
				}
				else
				{
					m_MyApp.setCurrentFileInfo( fileInfo );
					Intent myIntent = new Intent( ActivityBrowseFiles.this, ActivityConfirmShredFile.class );
					ActivityBrowseFiles.this.startActivityForResult( myIntent, Constants.ACTIVITY_CONFIRM_SHRED_FILE );
				}	
			}
		}
	}

	//========================================================================
	@Override
	public void onActivityResult(int requestCode, int resultCode, Intent data) 
	{
		super.onActivityResult(requestCode, resultCode, data);
		Log.d(LOG_TAG, "onActivityResult result code " + resultCode);
			
		switch (requestCode) 
		{
		case Constants.ACTIVITY_CONFIRM_SHRED_FILE:
			Log.d( LOG_TAG, "onActivityResult ACTIVITY_CONFIRM_SHRED_FILE" );
			if( resultCode == Activity.RESULT_OK ) 
			{
				VxFileInfo fileInfo = m_MyApp.getCurrentFileInfo();
				if( null != fileInfo )
				{
					m_MyApp.playSound( ESndDef.eSndDefPaperShredder );
					String fullFileName = fileInfo.getFullFileName();
					m_FileListAdapter.lockBrowseAdapter();
					m_FileListAdapter.removeFile( fileInfo );
					m_FileListAdapter.unlockBrowseAdapter();
					m_FileListAdapter.notifyDataSetChanged();
					NativeTxTo.fromGuiDeleteFile( fullFileName, true );
				}				
			}
			
			break;
			
		case Constants.ACTIVITY_VIEW_VIDEO_FILE:
			Log.d( LOG_TAG, "onActivityResult ACTIVITY_VIEW_VIDEO_FILE" );
			VxFileInfo fileInfo = m_MyApp.getCurrentFileInfo();
			if( null != fileInfo )
			{
				String fullFileName = fileInfo.getFullFileName();
				if( 0 == VxFileUtil.getFileLen(  fullFileName ) )
				{
					// file was shredded in view video file
					m_FileListAdapter.lockBrowseAdapter();
					m_FileListAdapter.removeFile( fileInfo );
					m_FileListAdapter.unlockBrowseAdapter();
					m_FileListAdapter.notifyDataSetChanged();
				}
			}				
			
			break;
		}
		
		setCamCaptureActivity( this );
	}

		 
	//============================================================================
	@Override
	public void toGuiFileList( VxFileInfo fileInfo )
	{
		if( false == m_MyApp.getIsAppShuttingDown() )
		{
			if( fileInfo.getFullFileName().isEmpty() )
			{
				setActionEnable( true );
				m_FileListAdapter.notifyDataSetChanged();
			}
			else
			{
				m_FileListAdapter.doUpdateFileInfo( fileInfo );
			}
		}
	}
	 
	//============================================================================
	@Override
	public void toGuiFileListReply( GuiFileXferSession xferSession ) 
	{
	}

	//============================================================================
	@Override
	public void toGuiStartUpload( GuiFileXferSession xferSession ) 
	{
	}

	//============================================================================
	@Override
	public void toGuiStartDownload( GuiFileXferSession xferSession ) 
	{
	}

	//============================================================================
	@Override
	public void toGuiFileUploadComplete( VxGUID lclSession, int xferError ) 
	{
	}

	//============================================================================
	@Override
	public void toGuiFileXferState(VxGUID lclSession, int eXferError, int param1, int param2) 
	{
	}

	//============================================================================
	@Override
	public void toGuiFileDownloadComplete(VxGUID lclSession, String newFileName, int xferError) 
	{
	}

	@Override
	public void onFileXferFileIconButClick( View v )
	{
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onFileXferAcceptButClick( View v )
	{
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onFileXferPlayButClick( View v )
	{
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onFileXferLibraryButClick( View v )
	{
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onFileXferShareButClick( View v )
	{
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onFileXferShredButClick( View v )
	{
		// TODO Auto-generated method stub
		
	}
}
