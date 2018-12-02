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

import android.content.*;
import android.util.*;
import android.view.*;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import java.util.*;
import android.os.Bundle;

public class ActivityCreateProfile extends ActivityBase 
{
	public static final String LOG_TAG = "ActivityCreateProfile:";
	
	//=== vars ===//
	private UserAccount			m_oUserAccount; 
	private DataHelper			m_oDataHelper;
	// buttons
	private Button 				m_oLoginBut = null;
	private Button 				m_oCancelBut = null;
	// edit text
	private EditText			m_oUserName = null;
	private EditText			m_oMoodMsg = null; 	
	
    //========================================================================
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        // launch Login activity
        Log.i(LOG_TAG, "onCreateCalled");
        
        setContentView(R.layout.activity_create_profile);
        super.onCreate(savedInstanceState);
        setPageTitle( R.string.activity_create_profile_name );
        
        m_oDataHelper = m_MyApp.getDataHelper();
        m_oUserAccount = m_MyApp.getUserAccount();
         
    	this.m_oLoginBut = (Button)this.findViewById(R.id.create_profile_login_button);
	 	this.m_oLoginBut.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
 			    m_MyApp.playButtonClick();
	 			OnLoginButClick(v);
	 		}
	 	});	 	
	 	
    	this.m_oCancelBut = (Button)this.findViewById(R.id.cancel_button);
	 	this.m_oCancelBut.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
 			    m_MyApp.playButtonClick();
	 			OnCancelButClick(v);
	 		}
	 	});	 	

	 	this.m_oMoodMsg = (EditText)this.findViewById(R.id.create_profile_mood_text);
	 	this.m_oUserName = (EditText)this.findViewById(R.id.create_profile_username_text);      
    }
    
    //========================================================================
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) 
    {
    	super.onActivityResult(requestCode, resultCode, data);
    	if( Constants.ACTIVITY_EDIT_PROFILE == requestCode )
    	{
    		// get intent for this activity
    		Intent oThisIntent = getIntent();
    		// return result of edit activity back to MainActivity
    		setResult(resultCode, oThisIntent);
    		m_MyApp.setUserAccount( this.m_oUserAccount );
    		finish();
    	}
    	
		setCamCaptureActivity( this );
    }
    
    //========================================================================
    //! Implement the OnClickListener callback    
	public void OnLoginButClick(View v) 
    {
    	if( true == AccountValidate() )
    	{
    		UUID uuidTmp = UUID.randomUUID(); 
       	 	m_oUserAccount.m_u64IdHiPart = uuidTmp.getMostSignificantBits();
       	 	m_oUserAccount.m_u64IdLoPart = uuidTmp.getLeastSignificantBits();
       	 	m_oUserAccount.m_as8OnlineName = m_oUserName.getText().toString();
       	 	m_oUserAccount.m_as8OnlineDesc = m_oMoodMsg.getText().toString();
       	 	m_oUserAccount.setDefaultPermissions();
       	 	int onlinePort = NativeTxTo.fromGuiGetRandomTcpPort();
       	 	m_oUserAccount.setOnlinePort( onlinePort );
       	 	m_MyApp.getMySettings().setMyTcpInPort( onlinePort );
       	 	Log.i(LOG_TAG, "created acct name " + m_oUserAccount.m_as8OnlineName + " UUID " + m_oUserAccount.m_u64IdHiPart + ", " + m_oUserAccount.m_u64IdLoPart);
       	 	if( true == m_MyApp.saveUserAccountToDatabase(m_oUserAccount))
       	 	{
           	 	if( true == m_oDataHelper.updateLastLogin(m_oUserAccount.m_as8OnlineName))
           	 	{
           	 		m_MyApp.setUserAccount( this.m_oUserAccount );
           	 		m_MyApp.myAppInitialize( this, getResources());
					String userXferDir 	= m_MyApp.getAppUsersDir() + m_oUserAccount.m_as8OnlineName + "/";
					m_MyApp.setUserXferDirectory( userXferDir );					

					String userSpecificDir 	= m_MyApp.getAppAccountsDir() + m_oUserAccount.m_as8OnlineName + "/";
					m_MyApp.setUserSpecificDirectory( userSpecificDir );
					NativeTxTo.fromGuiUpdateMyIdent( m_oUserAccount, false );
           	 		
           	 		// give user a chance to edit his/her profile
           	    	Intent myIntent = new Intent(ActivityCreateProfile.this, ActivityEditProfile.class);
           	    	ActivityCreateProfile.this.startActivityForResult(myIntent, Constants.ACTIVITY_EDIT_PROFILE );
           	 	}		
           	 	else
           	 	{
           	 		Toast.makeText(this, "Update New User into Database failed.", Toast.LENGTH_LONG).show();
           	 		Log.i(LOG_TAG, "Update New User into Database failed.");
           	 	}
       	 	}
       	 	else
       	 	{
       	 		Toast.makeText(this, "Insert New User into Database failed.", Toast.LENGTH_LONG).show();
       	 		Log.i(LOG_TAG, "Insert New User into Database failed.");
       	 	}
    	}   	
    }   
	
    //========================================================================
    public boolean AccountValidate()  
    {
	   	 String strUserName = m_oUserName.getText().toString();
	   	 if( strUserName.contains("'") )
	   	 {
			 Toast.makeText(this, "User Name cannot have special character quote.", Toast.LENGTH_LONG).show();;
			 return false;   		 
	   	 }
	   
	   	 /*
	 	if( strUserName.contains("My P2P Web") 
	 			||  strUserName.contains("MyP2PWeb")
	 			||  strUserName.contains("myp2pweb")
	 			||  strUserName.contains("my p2p web") )
	   	 {
			 Toast.makeText(this, "User Name cannot contain name My P2P Web.", Toast.LENGTH_LONG).show();;
			 return false;   		 
	   	 }*/
   	 
	   	 if( strUserName.contains("(") || strUserName.contains(")") )
	   	 {
			 Toast.makeText(this, "User Name cannot have special character parentheses.", Toast.LENGTH_LONG).show();;
			 return false;   		 
	   	 }
	   	 
	   	 if( strUserName.contains("/") || strUserName.contains("\\") )
	   	 {
			 Toast.makeText(this, "User Name cannot have special character slashes.", Toast.LENGTH_LONG).show();;
			 return false;   		 
	   	 }
	   	 
		 if( strUserName.length() > 23 )
		 {
			 Toast.makeText(this, "User Name is too long (max 23 chars).", Toast.LENGTH_LONG).show();;
			 return false;
		 }
		 
		 if( strUserName.length() < 4 )
		 {
			 Toast.makeText(this, "User Name is too short (min 4 chars).", Toast.LENGTH_LONG).show();;
			 return false;
		 }
		 
    	 String strMoodMsg = m_oMoodMsg.getText().toString();
	   	 if( strUserName.contains("'") )
	   	 {
			 Toast.makeText(this, "Mood Message cannot have special character quote.", Toast.LENGTH_LONG).show();;
			 return false;   		 
	   	 }
	   	 
	   	 int iLen = strMoodMsg.length();
	   	 if( iLen > 27 )
    	 {
    		 Toast.makeText(this, "Mood Message is too long (max 27 chars)", Toast.LENGTH_LONG).show();;
    		 return false;
    	 }
	   	 
    	 return true;
    }
    
    //========================================================================
 	public void OnCancelButClick(View v) 
    {
		onBackButtonPressed();
	}
    
 	//========================================================================
    @Override
    public void onBackButtonPressed() 
    {
		Intent intent = this.getIntent(); 
		//intent.putExtra("SOMETHING", "EXTRAS"); 
		this.setResult(RESULT_CANCELED, intent); 
		super.onBackButtonPressed();
	}
}
