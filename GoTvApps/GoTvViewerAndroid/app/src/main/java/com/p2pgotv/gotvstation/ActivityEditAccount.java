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

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class ActivityEditAccount extends ActivityBase
{
	private static final String LOG_TAG = "ActivityEditAccount:";
	
	//=== vars ===//	
	private EditText			m_MoodMessageEdit 	= null;
	private Button 				m_AcceptBut 			= null;
	private Button 				m_CancelBut 		= null;
 	
    //============================================================================
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        setContentView(R.layout.activity_edit_account);
        super.onCreate(savedInstanceState);
        setPageTitle( R.string.activity_edit_account_title );
       
		this.m_AcceptBut = (Button)this.findViewById(R.id.reuse_accept_but);
		if( null != m_AcceptBut )
		{
		 	this.m_AcceptBut.setOnClickListener(new OnClickListener() 
		 	{
		 		public void onClick(View v) 
		 		{
	 			    m_MyApp.playButtonClick();
		 			onAcceptButClick();
		 		}
		 	});			
		}
	 	
		this.m_CancelBut = (Button)this.findViewById(R.id.reuse_cancel_but);
		if( null != m_CancelBut )
		{
		 	this.m_CancelBut.setOnClickListener(new OnClickListener() 
		 	{
		 		public void onClick(View v) 
		 		{
	 			    m_MyApp.playButtonClick();
	 			    onCancelButClick();
		 		}
		 	});	
		}

	    this.m_MoodMessageEdit		= (EditText) this.findViewById( R.id.mood_message_edit );
	    updateValuesFromDatabase();	    
    }
    
    //============================================================================
    void onAcceptButClick()
	{
    	if( applyResults() )
    	{
    		onBackButtonPressed();
    	}
	}
    
    //============================================================================
    void onCancelButClick()
	{
    	onBackButtonPressed();
	}

    //============================================================================
    void updateValuesFromDatabase()
	{
    	m_MoodMessageEdit.setText( m_MyApp.getUserAccount().m_as8OnlineDesc );
	}
	
	//============================================================================
    public boolean applyResults()
	{
		if( false == validateMoodMessage() )
		{
			return false;
		}
		
		boolean actionResult = false;
		UserAccount myAcct 		= m_MyApp.getUserAccount();
		String newMoodMessage 	= m_MoodMessageEdit.getText().toString();
		if( 0 != myAcct.m_as8OnlineDesc.compareTo( newMoodMessage ) )
		{
			myAcct.m_as8OnlineDesc = newMoodMessage;
      	 	if( true == m_MyApp.saveUserAccountToDatabase( myAcct ) )
       	 	{
      	 		actionResult = true;
           	 	NativeTxTo.fromGuiMoodMessageChanged( newMoodMessage );	 		
       	 	}
      	 	else
      	 	{
       	 		Toast.makeText(this, "ActivityEditAccount Update User Account into Database failed.", Toast.LENGTH_LONG).show();
       	 		Log.i( LOG_TAG, "ActivityEditAccount Update User Account into Database failed." );     	 		
      	 	}
		}
		else
		{
   	 		Toast.makeText( this, "Edit Account.. Mood Message Is Same.", Toast.LENGTH_SHORT ).show();
   	 		Log.i( LOG_TAG, "Edit Account.. Mood Message Is Same." );     	 					
		}
		
		return actionResult;
	}
	
	//============================================================================
	boolean validateMoodMessage()
	{
		String newMoodMessage = m_MoodMessageEdit.getText().toString();

		if( newMoodMessage.contains("'") )
		{
			Toast.makeText( this, "Mood Message cannot have special character quote.", Toast.LENGTH_SHORT ).show();
			return false;   		 
		}
		
		if( newMoodMessage.contains(":") )
		{
			Toast.makeText( this, "Mood Message cannot have special character colon (:).", Toast.LENGTH_SHORT ).show();
			return false;   		 
		}
	
		if( newMoodMessage.contains("(") || newMoodMessage.contains(")") )
		{
			Toast.makeText( this, "Mood Message cannot have special character parentheses.", Toast.LENGTH_SHORT ).show();
			return false;   		 
		}
		
		if( newMoodMessage.contains("/") || newMoodMessage.contains("\\") )
		{
			Toast.makeText( this, "Mood Message cannot have special character slashes.", Toast.LENGTH_SHORT ).show();
			return false;   		 
		}
		
		if( newMoodMessage.length() > 27 )
		{
			Toast.makeText( this, "Mood Message is too long (max 27 chars).", Toast.LENGTH_SHORT ).show();
			return false;
		}
		
		return true;
	}
}

