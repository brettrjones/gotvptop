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
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.WindowManager;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.Toast;

public class ActivityDownloads  extends ActivityListBase implements ToGuiFileXferInterface
{
	//=== constants ===//
	public static final String LOG_TAG = "ActivityDownloads:";
	   
	//=== vars ===//
	private FileXferAdapter		m_FileXferAdapter			= null;
	private ListView			m_FileListView				= null;
	private boolean				m_FetchInProgress			= false;		
	
    //========================================================================
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        setContentView(R.layout.activity_downloads);
        super.onCreate(savedInstanceState);
        setPageTitle( R.string.activity_downloads_title );
        // keep keyboard from popping up
        this.getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN); 
        
        m_FileXferAdapter = m_MyApp.getDownloadsAdapter();
   	 	setListAdapter( m_FileXferAdapter );
   	 	m_FileListView = getListView();
		setActivityReadyState( this );
		checkDiskSpace();
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

    //============================================================================
    void setActionEnable( boolean enable )
    {
    	m_FetchInProgress = enable ? false : true;
    	Log.i( LOG_TAG, "Fetch In Progress " + m_FetchInProgress );
    }
    
	//========================================================================
	@Override
	public void onListItemClick(ListView parent, View v, int position, long id) 
	{
    	Log.i( LOG_TAG,  " onListItemClick " );
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
    			return m_FileXferAdapter.getFileByPosition( i );
    		}
         }

		return null;
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
				if( null != vertLayout )
				{
					int position = m_FileListView.getPositionForView( (View) vertLayout.getParent() );
					if( position >= 0 )
					{
						m_FileXferAdapter.lockFileXferAdapter();
						GuiFileXferSession fileInfo = m_FileXferAdapter.getFileByPosition( position );
						m_FileXferAdapter.unlockFileXferAdapter();
						return fileInfo;
					}
				}
			}	
		}
		
		return null;
	}
	
	
	//========================================================================
	public void onFileXferFileIconButClick( View v )
	{
		m_MyApp.playButtonClick() ;
		int position = m_FileListView.getPositionForView( (View) v.getParent() );
		if( position >= 0 )
		{
			m_FileXferAdapter.lockFileXferAdapter();
			GuiFileXferSession fileInfo = m_FileXferAdapter.getFileByPosition( position );
			m_FileXferAdapter.unlockFileXferAdapter();
			if( null != fileInfo )
			{
				if( fileInfo.isDirectory() )
				{
				}
				else
				{
					if( fileInfo.getIsCompleted() )
					{
						playFile( this, fileInfo );
					}
					//if( m_IsSelectAFileMode )
					//{
					//	m_MyApp.setCurrentFileInfo( fileInfo );
					//	Intent resultIntent = getIntent();
					//	setResult(Activity.RESULT_OK, resultIntent);
					//	finish();					
					//}
					//else
					//{
					//	playFile( fileInfo );
					//}
				}
			}
		}
	}
	
	//========================================================================
	@Override
	public void onFileXferAcceptButClick( View v )
	{
		m_MyApp.playButtonClick() ;
		m_FileXferAdapter.lockFileXferAdapter();
		int position = m_FileListView.getPositionForView( (View) v.getParent() );
		if( position >= 0 )
		{
			GuiFileXferSession xferSession = m_FileXferAdapter.getFileByPosition( position );
			m_FileXferAdapter.unlockFileXferAdapter();
			if( null != xferSession )
			{
				if( xferSession.isDirectory() )
				{
				}
				else
				{
					switch( xferSession.getXferState() )
					{
					case Constants.eXferStateUploadNotStarted:
						//beginUpload( xferSession, position );
						//break;
						
					case Constants.eXferStateDownloadNotStarted:
						//beginDownload( xferSession, position );
						//break;

					case Constants.eXferStateCompletedUpload:
					case Constants.eXferStateCompletedDownload:
					case Constants.eXferStateUnknown:						
						removeDownload( xferSession, position );
						break;
					case Constants.eXferStateWaitingOfferResponse:
					case Constants.eXferStateInUploadQue:
					case Constants.eXferStateInDownloadQue:
					case Constants.eXferStateBeginUpload:
					case Constants.eXferStateBeginDownload:
					case Constants.eXferStateInUploadXfer:
					case Constants.eXferStateInDownloadXfer:
					case Constants.eXferStateUserCanceledUpload:
					case Constants.eXferStateUserCanceledDownload:
					case Constants.eXferStateUploadOfferRejected:
					case Constants.eXferStateUploadError:
					case Constants.eXferStateDownloadError:
						cancelDownload( xferSession, position );					
						break;
						
					default:
						break;
					}				
				}
			}
		}
		else
		{
			m_FileXferAdapter.unlockFileXferAdapter();			
		}
	}
	
	//========================================================================
	public void removeDownload( GuiFileXferSession xferSession, int position )
	{
		m_FileXferAdapter.removeXferItem( position );
	}
	
	//========================================================================
	public void cancelDownload( GuiFileXferSession xferSession, int position )
	{
		xferSession.setXferState( Constants.eXferStateUserCanceledDownload, 0, 0 );
		NativeTxTo.fromGuiCancelDownload( xferSession.getLclSessionId().m_u64IdHiPart, xferSession.getLclSessionId().m_u64IdLoPart );
		removeDownload( xferSession, position );		
	}
	
	//========================================================================
	public void onFileXferLibraryButClick( View v )
	{
		if( false == m_FetchInProgress )
		{
	    	Log.i(LOG_TAG, "onFileXferLibraryButClick" );
			m_MyApp.playButtonClick() ;
			VxFileInfo fileInfo = getActionButtonFileInfo( v );
			if( null != fileInfo )
			{
				if( Constants.VXFILE_TYPE_DIRECTORY == fileInfo.getFileType() )
				{
					//browseToDirectory( fileInfo );
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
					m_FileXferAdapter.notifyDataSetChanged();
				}
			}
		}
	}
	
	//========================================================================
	public void onFileXferShareButClick( View v )
	{
		if( false == m_FetchInProgress )
		{
			Log.i(LOG_TAG, "onFileXferLibraryButClick" );
			m_MyApp.playButtonClick() ;
			VxFileInfo fileInfo = getActionButtonFileInfo( v );
			if( null != fileInfo )
			{
				if( Constants.VXFILE_TYPE_DIRECTORY == fileInfo.getFileType() )
				{
					//browseToDirectory( fileInfo );
				}
				else
				{
					// is file
					// toggle is in library state
					boolean isShared = !fileInfo.getIsShared();
					fileInfo.setIsShared( isShared );
					NativeTxTo.fromGuiSetFileIsShared( fileInfo.getFullFileName(), fileInfo.getIsShared(), fileInfo.getFileHashData() );
					m_FileXferAdapter.notifyDataSetChanged();
				}
			}	
		}
	}
	
	//========================================================================
	public void onFileXferPlayButClick( View v )
	{
		if( false == m_FetchInProgress )
		{
			Log.i(LOG_TAG, "onFileXferPlayButClick" );
			m_MyApp.playButtonClick() ;
			VxFileInfo fileInfo = getActionButtonFileInfo( v );
			if( null != fileInfo )
			{
				if( Constants.VXFILE_TYPE_DIRECTORY == fileInfo.getFileType() )
				{
					//browseToDirectory( fileInfo );
				}
				else
				{
					playFile( this, fileInfo );
				}	
			}
		}
	}
	
	//========================================================================
	public void onFileXferShredButClick( View v )
	{
		if( false == m_FetchInProgress )
		{
			Log.i(LOG_TAG, "onFileXferShredButClick" );
			m_MyApp.playButtonClick() ;
			final VxFileInfo fileInfo = getActionButtonFileInfo( v );
			if( null != fileInfo )
			{
				if( Constants.VXFILE_TYPE_DIRECTORY == fileInfo.getFileType() )
				{
					//browseToDirectory( fileInfo );
				}
				else
				{
					m_MyApp.playButtonClick() ;
					final int position = m_FileListView.getPositionForView( (View) v.getParent() );
					final Activity thisActivity = this;
					if( position >= 0 )
					{
						if( null != fileInfo )
						{
							if( Constants.VXFILE_TYPE_DIRECTORY == fileInfo.getFileType() )
							{
								//browseToDirectory( fileInfo );
							}
							else
							{
								new AlertDialog.Builder( this )	 
							 	.setIcon(R.drawable.button_shredder_normal)	 
							 	.setTitle("Delete File Confirm")	 
							 	.setMessage("Press SHRED to write random data to file then delete file.\n Press REMOVE to just remove file from list")	 
							 	.setPositiveButton("SHRED", new DialogInterface.OnClickListener()
								 {
								 	@Override
								 	public void onClick(DialogInterface dialog, int which) 
								 	{
								 		m_MyApp.playSound( ESndDef.eSndDefPaperShredder );
										Log.d( LOG_TAG, "onShredMediaButClick Shredding file " + fileInfo.getFullFileName() );
										NativeTxTo.fromGuiSetFileIsShared( fileInfo.getFullFileName(), false, fileInfo.getFileHashData() );
										NativeTxTo.fromGuiAddFileToLibrary( fileInfo.getFullFileName(), false, fileInfo.getFileHashData() );
										m_FileXferAdapter.removeItem( position );
										NativeTxTo.fromGuiDeleteFile( fileInfo.getFullFileName(), true );
								 	}
								 })
								 .setNegativeButton("Cancel", new DialogInterface.OnClickListener()
								 {
									 @Override
									 public void onClick(DialogInterface dialog, int which) 
									 {
										 m_MyApp.playButtonClick();
										 Toast.makeText( thisActivity, "Operation Canceled", Toast.LENGTH_SHORT).show();
									 }
								 })
								 .setNeutralButton("REMOVE", new DialogInterface.OnClickListener()
								 {
									 @Override
									 public void onClick(DialogInterface dialog, int which) 
									 {
										 Log.d( LOG_TAG, "onShredMediaButClick Removing file " + fileInfo.getFullFileName() );
										 m_MyApp.playSound( ESndDef.eSndDefNeckSnap );
										 m_FileXferAdapter.removeItem( position );
									 }
								 })
								 .show();
							}	
						}
					}
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
				/*
				VxFileInfo fileInfo = m_MyApp.getCurrentFileInfo();
				if( null != fileInfo )
				{
					m_MyApp.playSound( ESndDef.eSndDefPaperShredder );
					String fullFileName = fileInfo.getFullFileName();
					m_FileXferAdapter.lockFileXferAdapter();
					m_FileXferAdapter.removeFile( fileInfo );
					m_FileXferAdapter.unlockFileXferAdapter();
					m_FileXferAdapter.notifyDataSetChanged();
					NativeTxTo.fromGuiDeleteFile( fullFileName, true );
				}*/			
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
					m_FileXferAdapter.lockFileXferAdapter();
					m_FileXferAdapter.removeFile( fileInfo );
					m_FileXferAdapter.unlockFileXferAdapter();
					m_FileXferAdapter.notifyDataSetChanged();
				}
			}				
		}
		
		setCamCaptureActivity( this );
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
	public void toGuiFileList(VxFileInfo fileInfo) 
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
}
