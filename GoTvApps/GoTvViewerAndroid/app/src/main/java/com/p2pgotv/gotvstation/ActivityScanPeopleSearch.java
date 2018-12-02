//============================================================================
// Copyright (C) 2013 Brett R. Jones
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

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;

public class ActivityScanPeopleSearch extends ActivityFriendListBase implements ToGuiSearchInterface
{
	// === constants ===//
	private static final String LOG_TAG = "ActivityScanPeopleSearch:";

	// === activity vars ===//
	public int					m_eScanType = Constants.eScanTypePeopleSearch;
	
	public Button 				m_oScanStartBut = null;
	public Button 				m_oScanPauseBut = null;
	public Button 				m_oScanAgainBut = null;
	public Button 				m_oScanCancelBut = null;
	public TextView 			m_oScanTextLabel = null;
	public EditText 			m_oScanTextEdit = null;


	//========================================================================
	@Override
	public void onCreate(Bundle savedInstanceState) 
	{
        setContentView( R.layout.activity_scan_people_search );
		super.onCreate(savedInstanceState);		
        Bundle extras = getIntent().getExtras(); 
        if (extras != null) 
        { 
        	m_eScanType = extras.getInt("PeopleSearchType"); 
        } 
        
		this.m_oScanStartBut = (Button)this.findViewById( R.id.scan_start_but );
	 	this.m_oScanStartBut.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
  			   	m_MyApp.playButtonClick();
	 			onScanStartButClick(v);
	 		}
	 	});	
        
		this.m_oScanPauseBut = (Button)this.findViewById( R.id.scan_pause_but );
	 	this.m_oScanPauseBut.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
  			   	m_MyApp.playButtonClick();
	 			onScanPauseButClick(v);
	 		}
	 	});	
	 	
		this.m_oScanTextLabel = (TextView)this.findViewById( R.id.text_search_label );	
		this.m_oScanTextEdit = (EditText)this.findViewById( R.id.edit_search_text );
	 	
        if( m_eScanType == Constants.eScanTypePeopleSearch )
        {
        	m_oScanTextLabel.setText( R.string.activity_scan_by_name_label );
        	m_oScanPauseBut.setText( R.string.button_scan_stop_scan_label );
    		setPageTitle( R.string.activity_scan_by_name_title );     	
        }
        else
        {
        	m_oScanTextLabel.setText( R.string.activity_scan_by_mood_msg_label );
    		setPageTitle( R.string.activity_scan_by_mood_msg_title );    	
        }		
		
		Log.i(LOG_TAG, "onCreateCalled");
		enableToGuiCallbacks( true );
	}
    
	//========================================================================
    @Override
    public void onDestroy() 
    {
		Log.d(LOG_TAG, "onDestroy stopping scan ");  
    	NativeTxTo.fromGuiStopScan( m_eScanType );
    	enableToGuiCallbacks( false );
 		Log.d(LOG_TAG, "onDestroy ");  
    	super.onDestroy();    	
    }
    
	//========================================================================
	void enableToGuiCallbacks( boolean enable )
	{
		try
		{
			if( enable )
			{
				NativeRxFrom.wantToGuiSearchClient( this, true );
			}
			else
			{
				NativeRxFrom.wantToGuiSearchClient( this, false );
			}
		}
		catch( InterruptedException e )
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
   
	//========================================================================  
	@Override
    public void toGuiScanSearchComplete( int eScanType )
    {
    	if( eScanType == m_eScanType )
    	{
	    	String strComplete = getString( R.string.search_complete );
	    	setStatusMessage( strComplete );
    	}
    }
    
	//========================================================================      
    private void searchStarted( String searchArg )
    {
    	String strStartScan = getString( R.string.search_started ) + searchArg;
    	setStatusMessage( strStartScan );
    }
    
	//========================================================================      
    private void searchStopped()
    {
    	String strStopScan = getString( R.string.search_stopped );
    	setStatusMessage( strStopScan );
    }
   
	//========================================================================      
    private void onScanStartButClick(View v) 
    {
    	ClearContactList();
    	String strSearch = m_oScanTextEdit.getText().toString();
    	if( 3 > strSearch.length() )
    	{
    		errMsgBox( false, "Search must have at least 3 characters" );
    	}
    	else
    	{
    		searchStarted( strSearch );
    		Log.d(LOG_TAG, "** onScanStartButClick starting scan ");  
    		NativeTxTo.fromGuiStartScan( m_eScanType, 0, 0, strSearch );
       		Log.d(LOG_TAG, "** onScanStartButClick done starting scan ");  
    	}
    }  
    
	//========================================================================      
    private void onScanPauseButClick(View v) 
    {
    	searchStopped();
   		Log.d(LOG_TAG, "** onScanPauseButClick stopping  scan ");  
    	NativeTxTo.fromGuiStopScan( m_eScanType );	
   		Log.d(LOG_TAG, "** onScanPauseButClick stopping scan done ");  
    }  

	//========================================================================
	@Override
	public void onListItemClick(ListView parent, View v, int position, long id) 
	{
		VxNetIdent friend = m_oContactsAdapter.getFriendByPosition(position);
		if( null != friend ) 
		{
			Log.i(LOG_TAG, "onListItemClick " + friend.m_as8OnlineName + friend.describeMyId());
			m_MyApp.setCurrentFriend(friend);
			m_MyApp.ShowPopupMenu(Constants.MENU_FRIEND);
		}
	}

	//========================================================================
	@Override
	public void toGuiScanSearchResultSuccess( int eScanType, VxNetIdent netIdent )
	{
    	if( eScanType == m_eScanType )
    	{
    		Log.i( LOG_TAG, "toGuiSearchResultPeopleSearch" );
    		setStatusMessage( getString( R.string.search_found ) + netIdent.m_as8OnlineName );
    		UpdateFriend( netIdent, false );
    	}
	}

	//========================================================================
	@Override
	public void toGuiScanSearchResultError( int eScanType, VxNetIdent netIdent,
			int errCode )
	{
		// TODO Auto-generated method stub
		
	}

	//========================================================================
	@Override
	public void toGuiSearchResultProfilePic( VxNetIdent netIdent,
			byte[] jpgData, int jpgDataLen )
	{
		// TODO Auto-generated method stub
		
	}

	//========================================================================
	@Override
	public void toGuiSearchResultFileSearch( VxNetIdent netIdent,
			VxGUID 		fileInstanceId, 
			int u8FileType, 
			long u64FileLen,
			String pFileName )
	{
		// TODO Auto-generated method stub
		
	}

	//========================================================================
	@Override
	public void toGuiPhoneShakeStatus( String formatedMsg )
	{
		// TODO Auto-generated method stub
		
	}
	
};