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

import java.util.ArrayList;
import java.util.concurrent.Semaphore;
import android.content.Context;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ProgressBar;
import android.widget.TextView;

class FileXferAdapter extends ArrayAdapter<GuiFileXferSession> 
{	
	//=== constants ===//
	private static final String LOG_TAG 					= "FileXferAdapter:";  
	
	//=== vars ===//
	private Semaphore m_oMutex 								= new Semaphore(1);
	public ArrayList<GuiFileXferSession> m_FileXferItems 	= new  ArrayList<GuiFileXferSession>();
	final int FILE_XFER_RED_COLOR 							= 0xffff0000;
	final int FILE_XFER_BLACK_COLOR 						= 0xff000000;
	private 	Handler 				m_MessageHandler 	= null;

	//======================================================================== 
	public FileXferAdapter( Context context, int textViewResourceId, ArrayList<GuiFileXferSession> items ) 
    {
		super(context, textViewResourceId, items);
		lockFileXferAdapter();
        this.m_FileXferItems = items;
        unlockFileXferAdapter();
        
		m_MessageHandler = new Handler() 
		{
		    @Override
		    public void handleMessage(Message msg) 
		    {
		    	switch(msg.what)
		    	{
		    	case Constants.MSG_TYPE_UPDATE_FILEINFO:
		    		//Log.i(LOG_TAG, "Rxed MSG_UPDATE_FILEINFO");
		    		doUpdateFileInfo( (GuiFileXferSession) msg.obj );
		    		notifyDataSetChanged();
		    		break;
		    		
		    	case Constants.MSG_TYPE_REFRESH_FILELIST:
		    		//Log.i(LOG_TAG, "Rxed MSG_REFRESH_FILELIST");
		    		clearList();
					notifyDataSetChanged();
					//NativeTxTo.fromGuiSendContactList( m_iWhoToViewInList );		    		
		    		break;

		    	case Constants.MSG_TYPE_CLEAR_FILELIST:
		    		//Log.i(LOG_TAG, "Rxed MSG_TYPE_CLEAR_FILELIST");
		    		clearList();
					notifyDataSetChanged();
		    		break;
		    		
		    	case Constants.MSG_TYPE_NOTIFY_FILELIST_CHANGED:
		    		//Log.i(LOG_TAG, "Rxed MSG_TYPE_NOTIFY_FILELIST_CHANGED");
					notifyDataSetChanged();
		    		break;
		    	}
		    	
		    	super.handleMessage(msg);
		    }
		};
    }
	
	//======================================================================== 
	public void lockFileXferAdapter()
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
	public void unlockFileXferAdapter()
	{
        m_oMutex.release();		
	}
	
	//========================================================================
	public void sendMsgRefreshFileList() 
	{
		Message msg; 
		msg = Message.obtain(); 
		msg.what = Constants.MSG_TYPE_REFRESH_FILELIST;   
		m_MessageHandler.sendMessage(msg); 
	}	  
    
	//========================================================================
	public void sendMsgUpdateFileInfo( GuiFileXferSession fileInfoIn ) 
	{
		Message msg; 
		msg = Message.obtain(); 
		msg.what = Constants.MSG_TYPE_UPDATE_FILEINFO;   
		msg.obj = fileInfoIn;
		m_MessageHandler.sendMessage(msg); 
	}
    
	//========================================================================
	public void sendMsgClearList() 
	{
		Message msg; 
		msg = Message.obtain();
		msg.what = Constants.MSG_TYPE_CLEAR_FILELIST;   
		msg.obj = null;
		m_MessageHandler.sendMessage(msg); 
	}
  
	//========================================================================
	public void sendMsgFileListChanged() 
	{
		Message msg; 
		msg = Message.obtain();
		msg.what = Constants.MSG_TYPE_NOTIFY_FILELIST_CHANGED;   
		msg.obj = null;
		m_MessageHandler.sendMessage(msg); 
	}
	
	//======================================================================== 
	public void clearList()
	{
		lockFileXferAdapter();
		this.m_FileXferItems.clear();
		unlockFileXferAdapter();
	}
	
	//======================================================================== 
	public void removeItem( int itemPosition )
	{
		lockFileXferAdapter();
		if( ( itemPosition >= 0 ) && ( itemPosition < m_FileXferItems.size() ) )
		{
			m_FileXferItems.remove( itemPosition );
		}
		
		unlockFileXferAdapter();	
		notifyDataSetChanged();
	}
	
	//======================================================================== 
    @Override
    public View getView(int position, View convertView, ViewGroup parent) 
    {
    	View fileItemView = convertView;
        if( null == fileItemView ) 
        {
        	LayoutInflater vi = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        	fileItemView = vi.inflate( R.layout.file_xfer_item, null );
        }
        
        lockFileXferAdapter();
        GuiFileXferSession xferSession = m_FileXferItems.get( position );
        if( null != xferSession ) 
        {
            int iIconResource 		= xferSession.getFileIconResource();
            ImageView fileIconButton 	= (ImageView)fileItemView.findViewById( R.id.file_xfer_icon_button );
    		fileIconButton.setImageResource( iIconResource );
    		ImageView cancelButton 	= (ImageView)fileItemView.findViewById( R.id.file_xfer_cancel_button );

            TextView fileNameText 				= (TextView) fileItemView.findViewById( R.id.file_xfer_filename );
            fileNameText.setTextColor( FILE_XFER_BLACK_COLOR );
            TextView fileStatusText 			= (TextView) fileItemView.findViewById( R.id.file_xfer_filestatus );
            fileStatusText.setTextColor( FILE_XFER_BLACK_COLOR );
            
            LinearLayout actionButtonsLayout 	= (LinearLayout) fileItemView.findViewById( R.id.file_xfer_action_layout );
            Button libraryButton 				= (Button) fileItemView.findViewById( R.id.file_xfer_library_button );
            Button shareFileButton 				= (Button) fileItemView.findViewById( R.id.file_xfer_share_button );
            ProgressBar progressBar				= (ProgressBar) fileItemView.findViewById( R.id.file_xfer_progress ); 
            
            boolean isDirectory		= false;
            if( Constants.VXFILE_TYPE_DIRECTORY == xferSession.getFileType() )
            {
            	isDirectory = true;
            	fileNameText.setText( xferSession.getFilePath() ); 
            	//fileSizeText.setVisibility( View.GONE );
            	fileStatusText.setVisibility( View.GONE );
            	//filePathText.setVisibility( View.GONE );            	
            	actionButtonsLayout.setVisibility( View.GONE );
            }
            else
            {
  	            fileNameText.setText( xferSession.getJustFileName() );                            
	            //fileSizeText.setText( xferSession.describeFileLength() );
	   			fileStatusText.setText( xferSession.describeFileLength() + " - " + xferSession.describeXferState() );
            	//fileNameText.setVisibility( View.VISIBLE );
            	//fileSizeText.setVisibility( View.VISIBLE );
            	//fileStatusText.setVisibility( View.VISIBLE );
	           	//filePathText.setText( xferSession.getFilePath() );        	
            	//filePathText.setVisibility( View.VISIBLE );            	
            }
             
   		   	boolean enableAccept		= false;
    		boolean enablePlay			= false;
    		boolean enableProgress		= false;
    		
    		switch( xferSession.getXferState() )
    		{
    		case Constants.eXferStateInUploadXfer:
    		case Constants.eXferStateInDownloadXfer:
    			enableProgress = true;
    			progressBar.setProgress( xferSession.getXferProgress() );
    			break;

       		case Constants.eXferStateUploadError:
       		case Constants.eXferStateDownloadError:
     			fileStatusText.setTextColor( FILE_XFER_RED_COLOR );
    			if( 0 != xferSession.getXferStateParam2() )
    			{
    				fileStatusText.setText( GuiHelpers.describeEXferError( xferSession.getXferStateParam2() ) );
     			}
    			break;

    		case Constants.eXferStateCompletedUpload:
    		case Constants.eXferStateCompletedDownload:
    			if( 0 != xferSession.getXferStateParam2() )
    			{
    				fileStatusText.setText( GuiHelpers.describeEXferError( xferSession.getXferStateParam2() ) );
    				fileStatusText.setTextColor( FILE_XFER_BLACK_COLOR );
    			}
    			else
    			{
    				enableAccept = true;
    				enablePlay = true;
    			}
    			break;

    		case Constants.eXferStateUserCanceledUpload:
    		case Constants.eXferStateUploadOfferRejected:
       		case Constants.eXferStateUserCanceledDownload:
       			enableAccept = true;
    			break;

    		case Constants.eXferStateBeginUpload:
    		case Constants.eXferStateBeginDownload:
    			enableProgress = true;
    			break;

    		case Constants.eXferStateUploadNotStarted:
    		case Constants.eXferStateDownloadNotStarted:
    		case Constants.eXferStateWaitingOfferResponse:
    		case Constants.eXferStateInUploadQue:
    		case Constants.eXferStateInDownloadQue:
    		default:
    			break;
    		}

    		if( enableAccept )
    		{
    			cancelButton.setImageResource( R.drawable.button_accept_normal );
    		}
    		else
    		{
    			if( ( Constants.eXferStateDownloadNotStarted == xferSession.getXferState() ) || ( Constants.eXferStateUploadNotStarted == xferSession.getXferState() ) )
    			{
    				if( Constants.eXferDirectionRx == xferSession.getXferDirection() )
    				{
    		   			cancelButton.setImageResource( R.drawable.button_file_download_normal );
    				}
    				else
    				{
    		   			cancelButton.setImageResource( R.drawable.button_file_send_normal );
    				}
    			}
    			else
    			{
    				if( Constants.eXferDirectionRx ==  xferSession.getXferDirection() )
    				{
       		   			cancelButton.setImageResource( R.drawable.button_file_download_cancel );
       		   		}
    				else
    				{
       		   			cancelButton.setImageResource( R.drawable.button_file_send_cancel );
       		   		}
    			}
    		}

    		if( enablePlay && !isDirectory )
    		{
    			actionButtonsLayout.setVisibility( View.VISIBLE );;
    			boolean isInLibaray = NativeTxTo.fromGuiGetIsFileInLibrary( xferSession.getFullFileName() );
    	   		if( isInLibaray )
        		{
        			libraryButton.setBackgroundResource( R.drawable.button_library_normal );
        		}
        		else
        		{
        			libraryButton.setBackgroundResource( R.drawable.button_library_cancel );   			
        		}
           		
    			boolean isShared = NativeTxTo.fromGuiGetIsFileShared( xferSession.getFullFileName() );
    			if( isShared )
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
       			actionButtonsLayout.setVisibility( View.GONE );;
    		}

    		if( enableProgress && !isDirectory )
    		{
    			progressBar.setVisibility( View.VISIBLE );;
    		}
    		else
    		{
    			progressBar.setVisibility( View.GONE );;
    		}    		
        }
        else
        {
            Log.e( LOG_TAG, "getView null ident at position " + position );      	
        }
        
        unlockFileXferAdapter();
        return fileItemView;
    }
    
	//========================================================================   
    public GuiFileXferSession getFileByPosition( int iPosition )
    {
    	if( iPosition < m_FileXferItems.size() )
    	{    
    		GuiFileXferSession fileInfo = m_FileXferItems.get( iPosition );
    		fileInfo.setListIndex( iPosition );
     		return fileInfo;
    	}
    	
  	    Log.i(LOG_TAG, "unable to get file browse info at " + iPosition );
		return null;
    }
    
	//========================================================================        
	public void doUpdateFileInfo( GuiFileXferSession fileIn )  
    {
		lockFileXferAdapter();
		boolean bFoundFile = false;
		Log.i(LOG_TAG, "doUpdateFileInfo " );  
		
		int iPosition = 0;
		for( GuiFileXferSession fileItem: m_FileXferItems )
		{
			if( ( fileItem.getFullFileName() == fileIn.getFullFileName() ) &&
				( fileItem.getFilePath() == fileIn.getFilePath() ) )
			{
				bFoundFile = true;
		   	    Log.i(LOG_TAG, "found file " + fileIn.getFullFileName() );    			
		   	    m_FileXferItems.set( iPosition, fileIn ); 
		   	    Log.i(LOG_TAG, "found file updating  " );    			
		   	    			
				break;  			
			}
			
			iPosition++; 
		}
		
		if( false == bFoundFile )
		{
		    Log.i(LOG_TAG, "adding file " + fileIn.getFullFileName() );    	
		    m_FileXferItems.add( fileIn );
		}
		
		Log.i(LOG_TAG, "list count " + m_FileXferItems.size() );
        unlockFileXferAdapter();
    }
    
	//========================================================================        
	public void removeFile( GuiFileXferSession fileIn )  
    {
		int iPosition = 0;
		for( GuiFileXferSession fileItem: m_FileXferItems )
		{
			if( fileItem.getFullFileName() == fileIn.getFullFileName() ) 
			{
		   	    Log.i(LOG_TAG, "removing file " + fileIn.getFullFileName() + " at " + iPosition  );    			
		   	    m_FileXferItems.remove( iPosition ); 
				break;  			
			}
			
			iPosition++;
		}
    }   
    
	//========================================================================        
	public void removeXferItem( int position )  
    {
		if( ( 0 <= position ) && ( position < m_FileXferItems.size() ) )
		{
			m_FileXferItems.remove( position ); 
	    	sendMsgFileListChanged();
		}
    }
	
	//========================================================================        
	public void removeFile( VxFileInfo fileIn )  
    {
		int iPosition = 0;
		for( GuiFileXferSession fileItem: m_FileXferItems )
		{
			if( fileItem.getFullFileName() == fileIn.getFullFileName() ) 
			{
		   	    Log.i(LOG_TAG, "removing file " + fileIn.getFullFileName() + " at " + iPosition  );    			
		   	    m_FileXferItems.remove( iPosition ); 
				break;  			
			}
			
			iPosition++;
		}
    }
		
	//========================================================================
	public void toGuiFileXferState( VxGUID lclSession, int eXferState, int param1, int param2 ) 
	{
		boolean shouldUpdate = true;
		lockFileXferAdapter();
		for( GuiFileXferSession fileItem: m_FileXferItems )
		{
			if( fileItem.getLclSessionId().equals( lclSession ) ) 
			{
				if( fileItem.getXferState() == eXferState )
				{
					// it seems we may overwhelm the device with updates.. if we are just updating progress then time it out
					if( ( ( eXferState == Constants.eXferStateInDownloadXfer ) || ( eXferState == Constants.eXferStateInUploadXfer ) )
						&& ( 0 == param2 ) // no error
						&& ( 0 < ( fileItem.getXferProgress() ) || ( 0 == param1 ) ) // already progress or the update will not advance progress bar
						&& ( 100 != param1 ) // don't want to miss the completed percent
						)					
					{
						long timeNowMs = System.currentTimeMillis();
						if( ( timeNowMs - fileItem.m_LastUpdateTimeMs ) < 2000 )
						{
							Log.d( LOG_TAG, "Skipping Progress " + String.valueOf( param1 ) + " time " + String.valueOf( timeNowMs - fileItem.m_LastUpdateTimeMs ) );
							shouldUpdate = false;
						}
						else
						{
							Log.d( LOG_TAG, "Progress Update " + String.valueOf( param1 ) + " time " + String.valueOf( timeNowMs - fileItem.m_LastUpdateTimeMs ) );
							fileItem.m_LastUpdateTimeMs = timeNowMs;
						}
					}					
				}
				
				fileItem.setXferState( eXferState, param1, param2 );
				break;  			
			}
		}
		
	    unlockFileXferAdapter();
	    if( shouldUpdate )
	    {
	    	sendMsgFileListChanged();
	    }
	}
	
	//============================================================================
	public void toGuiStartUpload( GuiFileXferSession xferSession ) 
	{
		VxGUID lclSessionId = xferSession.getLclSessionId();
		boolean foundSession = false;
		lockFileXferAdapter();
		for( GuiFileXferSession fileItem: m_FileXferItems )
		{
			if( fileItem.getLclSessionId().equals( lclSessionId ) ) 
			{
				foundSession = true;
				break;  			
			}
		}
		
		if( false == foundSession )
		{
			xferSession.setXferState( Constants.eXferStateInUploadXfer, 0, 0 );
			m_FileXferItems.add( xferSession );
		}
		
	    unlockFileXferAdapter();
	    sendMsgFileListChanged();
	}

	//============================================================================
	public void toGuiStartDownload( GuiFileXferSession xferSession ) 
	{
		VxGUID lclSessionId = xferSession.getLclSessionId();
		boolean foundSession = false;
		lockFileXferAdapter();
		for( GuiFileXferSession fileItem: m_FileXferItems )
		{
			if( fileItem.getLclSessionId().equals( lclSessionId ) ) 
			{
				foundSession = true;
				break;  			
			}
		}
		
		if( false == foundSession )
		{
			xferSession.setXferState( Constants.eXferStateInDownloadXfer, 0, 0 );
			m_FileXferItems.add( xferSession );
		}
		
	    unlockFileXferAdapter();
	    sendMsgFileListChanged();
	}

	//========================================================================
	public void toGuiFileDownloadComplete( VxGUID lclSession, String newFileName, int xferError ) 
	{
		lockFileXferAdapter();
		for( GuiFileXferSession fileItem: m_FileXferItems )
		{
			if( fileItem.getLclSessionId().equals( lclSession ) ) 
			{
				fileItem.setFullFileName( newFileName );
				fileItem.updateJustFileName();
				fileItem.setXferState( Constants.eXferStateCompletedDownload, 100, 0 );
				break;  			
			}
		}
		
	    unlockFileXferAdapter();
	    sendMsgFileListChanged();
	}

	//========================================================================
	public void toGuiFileUploadComplete( VxGUID lclSession, int xferError ) 
	{
		lockFileXferAdapter();
		for( GuiFileXferSession fileItem: m_FileXferItems )
		{
			if( fileItem.getLclSessionId().equals( lclSession ) ) 
			{
				fileItem.setXferState( Constants.eXferStateCompletedUpload, 100, 0 );
				break;  			
			}
		}
		
	    unlockFileXferAdapter();
	    sendMsgFileListChanged();
	}
}


