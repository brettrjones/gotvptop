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

import android.app.*;
import android.content.*;
import android.graphics.Bitmap;
import android.util.*;
import android.view.*;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;

import android.os.Bundle;
import android.net.Uri;

public class ActivityEditProfile extends ActivityBase 
{
	//=== constants ===//
	private static final String LOG_TAG = "ActivityEditProfile:";
	
	//=== activity vars ===//
	
	private DataHelper 			m_oDataHelper;  
	private	VxFileUtil			m_VxFileUtil;
	
	//=== vars ===//
	private UserProfile 		m_oUserProfile;
	
	private boolean				m_bUserChangedPic 	= false;
	private boolean				m_bUserPickedImage 	= false;
	
 	// buttons
 	Button 						m_AcceptBut 		= null;
 	Button 						m_CancelBut 		= null;
 	Button 						m_GalleryBut 		= null;
 	Button 						m_SnapshotBut 		= null;
 	
 	// edit text
 	EditText					m_oTextGreet 		= null;
 	EditText					m_oTextAbout 		= null; 	
 	EditText					m_oTextUrl1 		= null;
 	EditText					m_oTextUrl2 		= null;
 	EditText					m_oTextUrl3 		= null;	
 	
 	// images
 	ImageViewWithSizer			m_PicMeView 		= null;
 	
 	String						m_strDefaultPicPath;
 	Uri							m_uriPic;
 	Bitmap						m_OriginalBitmap;

    //============================================================================
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
    	requestWindowFeature(Window.FEATURE_NO_TITLE); 
        setContentView(R.layout.activity_edit_profile);
        super.onCreate(savedInstanceState);
        setPageTitle( R.string.activity_edit_profile_title );
 
        m_oDataHelper = m_MyApp.getDataHelper();
        m_VxFileUtil = m_MyApp.getVxFileUtil();

        Log.i(LOG_TAG, "onCreateCalled");
        if( null == m_MyApp.getUserProfileDir() )
        {
        	m_MyApp.myAppInitialize( this, getResources());
			String userXferDir 	= m_MyApp.getAppUsersDir() + m_MyApp.getUserAccount().m_as8OnlineName + "/";
			m_MyApp.setUserXferDirectory( userXferDir );					

			String userSpecificDir 	= m_MyApp.getAppAccountsDir() + m_MyApp.getUserAccount().m_as8OnlineName + "/";
			m_MyApp.setUserSpecificDirectory( userSpecificDir );					
        }
        
        m_strDefaultPicPath	= m_MyApp.getUserProfileDir() + "me.jpg";	 	
	 	
    	m_AcceptBut = (Button)this.findViewById( R.id.reuse_accept_but );
    	m_AcceptBut.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
			    m_MyApp.playButtonClick();
			    onAcceptButClick(v);
	 		}
	 	});
    	
	 	
    	m_CancelBut = (Button)this.findViewById( R.id.reuse_cancel_but );
    	m_CancelBut.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
			    m_MyApp.playButtonClick();
			    onCancelButClick(v);
	 		}
	 	});

	 	
    	this.m_SnapshotBut = (Button)this.findViewById( R.id.edit_profile_camera_button );
	 	this.m_SnapshotBut.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
			    m_MyApp.playButtonClick();
			    onSnapshotButClick(v);
	 		}
	 	});
	 	
	 	this.m_GalleryBut = (Button)this.findViewById( R.id.edit_profile_pick_image_button );
	 	this.m_GalleryBut.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
			    m_MyApp.playButtonClick();
			    onGalleryButClick(v);
	 		}
	 	});
	 	
	 	this.m_oTextGreet 	= (EditText)this.findViewById(R.id.txt_greet);
	 	this.m_oTextAbout 	= (EditText)this.findViewById(R.id.txt_about_me);
	 	this.m_oTextUrl1 	= (EditText)this.findViewById(R.id.txt_favorite_url1);
	 	this.m_oTextUrl2 	= (EditText)this.findViewById(R.id.txt_favorite_url2);
	 	this.m_oTextUrl3 	= (EditText)this.findViewById(R.id.txt_favorite_url3);
	 	
	 	this.m_PicMeView  		= (ImageViewWithSizer)this.findViewById(R.id.pic_me);
        
        m_oUserProfile = new UserProfile();
        m_oUserProfile.m_strPicturePath = m_strDefaultPicPath;
        if( true == m_oDataHelper.getUserProfile( m_MyApp.getUserAccount(), m_oUserProfile ) )
        {
        	// profile is already setup... set values from existing profile
			m_oTextGreet.setText( m_oUserProfile.m_strGreeting );
        	m_oTextAbout.setText( m_oUserProfile.m_strAboutMe );
        	m_oTextUrl1.setText( m_oUserProfile.m_strUrl1 );
        	m_oTextUrl2.setText( m_oUserProfile.m_strUrl2 );
        	m_oTextUrl3.setText( m_oUserProfile.m_strUrl3 );	
        	m_oUserProfile.m_strPicturePath = m_strDefaultPicPath;  	
        }

        m_OriginalBitmap = VxImageUtil.getStdSizeBitmapFromFile( m_strDefaultPicPath );
        if( null != m_OriginalBitmap )
        {
        	m_PicMeView.loadImageFromFile( m_strDefaultPicPath );
        }
    }
 
    //============================================================================
    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) 
    {
    	super.onActivityResult(requestCode, resultCode, data);
      	if( ( requestCode == Constants.ACTIVITY_PICK_IMAGE ) 
      		|| ( requestCode == Constants.ACTIVITY_CAMERA_SNAPSHOT ) )
      	{
      		if (resultCode == Activity.RESULT_OK) 
      	    {
    	        Bundle extras = data.getExtras();
    	        if( null != extras ) 
    	        {	        	
    	            String photoFileName = extras.getString( Constants.PARAM_FILE_NAME );
    	            
    	            if( ( null != photoFileName ) 
    	            	&& ( 0 != photoFileName.length() ) )
    	            {
    	            	boolean imageValid = false;
	    	            if( 0 != photoFileName.compareTo( m_strDefaultPicPath )  )
	    	            {
	    	            	Bitmap loadedBmp = VxImageUtil.getStdSizeBitmapFromFile( photoFileName );
	    	            	if( null != loadedBmp )
	    	            	{
	    	            		imageValid = VxImageUtil.saveStdSizeBitmapToFile( loadedBmp, m_strDefaultPicPath );
	    	            	}
	    	            }
	    	            else
	    	            {
	    	            	if( VxFileUtil.fileExists( m_strDefaultPicPath ) )
	    	            	{
	    	            		imageValid = true;
	    	            	}
	    	            }
	    	            
	    	            if( imageValid )
	    	            {
		    	            if( true == m_PicMeView.loadImageFromFile( m_strDefaultPicPath ) )
		    	            {	    	            	
			     	            m_bUserChangedPic = true;
			    	            m_bUserPickedImage = true;
			    	            m_MyApp.getUserAccount().setHasProfilePicture(true);
			    	            m_MyApp.saveUserAccountToDatabase( m_MyApp.getUserAccount() );	
			    	            NativeTxTo.fromGuiSetUserHasProfilePicture( true );
		    	            }
	    	            }
    	            }
    	        }
      	    }
        } 
       	
		setCamCaptureActivity( this );
    }

    //============================================================================
    public void onGalleryButClick(View v) 
    { 
    	Intent myIntent = new Intent( ActivityEditProfile.this, ActivityPickImage.class );
    	myIntent.putExtra( Constants.PARAM_FILE_NAME, m_strDefaultPicPath ); 	
    	startActivityForResult( myIntent, Constants.ACTIVITY_PICK_IMAGE );
    }
    
    //============================================================================
    public void onSnapshotButClick(View v) 
    {
    	Intent myIntent = new Intent( ActivityEditProfile.this, ActivityCameraSnapshot.class );   	
    	myIntent.putExtra( Constants.PARAM_FILE_NAME, m_strDefaultPicPath );
    	startActivityForResult( myIntent, Constants.ACTIVITY_CAMERA_SNAPSHOT );
    }
    
    //============================================================================
    public void onAcceptButClick(View v) 
    {  	
    	// update profile
    	m_oUserProfile.m_strGreeting = ValidateString( this.m_oTextGreet.getText() );
    	m_oUserProfile.m_strAboutMe =  ValidateString( this.m_oTextAbout.getText().toString() );
    	m_oUserProfile.m_strUrl1 = ValidateString( this.m_oTextUrl1.getText().toString() );
    	m_oUserProfile.m_strUrl2 = ValidateString( this.m_oTextUrl2.getText().toString() );
    	m_oUserProfile.m_strUrl3 = ValidateString( this.m_oTextUrl3.getText().toString() );
	
    	createWebPage();
    	
    	// update picture flag
    	if( m_bUserPickedImage || m_bUserChangedPic )
    	{
            m_MyApp.getUserAccount().setHasProfilePicture(true);
            m_MyApp.saveUserAccountToDatabase( m_MyApp.getUserAccount() );		 	    	            	
    	}
    	
    	m_oDataHelper.updateUserProfile( m_MyApp.getUserAccount(), m_oUserProfile );
  	
		// get intent for this activity
		Intent oThisIntent = getIntent();
		// return result of edit activity back to MainActivity
		setResult(RESULT_OK, oThisIntent);
		finish();
    }
 
    //============================================================================
    public void onCancelButClick(View v) 
    {
    	onBackButtonPressed();
    }   
    
  	//========================================================================
    @Override
    public void onBackButtonPressed() 
    {
        m_OriginalBitmap = VxImageUtil.getStdSizeBitmapFromFile( m_strDefaultPicPath );
        if( m_bUserChangedPic && ( null != m_OriginalBitmap ) )
        {
        	VxImageUtil.saveBitmapToJpgFile( m_OriginalBitmap, m_strDefaultPicPath );
        }
   	
    	Intent resultIntent = new Intent();
    	setResult( Activity.RESULT_CANCELED, resultIntent );
    	finish();
    } 
    
    //============================================================================
    public String ValidateString(CharSequence charSeq )
    {
    	return charSeq.toString();    	
    }
    
    //============================================================================    
    public void createWebPage()
    {
    	String strWebPageHdr = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\"><html><head><meta http-equiv=\"Content-Type\" content=\"text/html;charset=iso-8859-1\"><FONT COLOR=\"#0000FF\" font-size:22pt;><title>About Me MyP2PWeb Page</title></FONT></head><body bgcolor=\"#E3EFFF\"><p style=\"text-align: center; font-size:22pt;\">About Me MyP2PWeb Page</br>";
       	String strUserName = "<style=\"text-align: center; font-size:20pt;\">" + m_MyApp.getMyIdentity().getOnlineName() + "</p>";
       	String strGreeting = "<p style=\"text-align: center; font-size:20pt;\">Hi! Im a My P2P Web User</p>";
    	String strAbout = "";
    	String strPicLabel = "<p style=\"text-align: center; font-size:20pt;\">My Picture</br>";
    	String strPicture = "<p align=center><img src=\"me.jpg\" style=\"height:50%;\"></p>\n";
    	String strFavWebsites = "<p style=\"font-size:20pt;\">My Favorite Web Sites.<br><FONT font-size:20pt; COLOR=\"#0000FF\">";
    	String strUrl1  = "";
    	String strUrl2 = "";
    	String strUrl3 = "";
    	String strUrl4 = "<a href=\"http://www.gotvp2p.net\">http://www.gotvp2p.net</a><br></FONT></p>";
    	if( 0 !=  m_oUserProfile.m_strGreeting.length() )
    	{
    		 strGreeting = "<p style=\"text-align: center;font-size:20pt;\">" + m_oUserProfile.m_strGreeting + "</p>";    		
    	}
    	
    	if( 0 !=  m_oUserProfile.m_strAboutMe.length() )
    	{
    		strAbout =  "<p style=\"text-align: center;font-size:20pt;\">" + m_oUserProfile.m_strAboutMe + "</p>";
    	}
    	
    	if( 0 !=  m_oUserProfile.m_strUrl1.length() )
    	{
    		strUrl1 = VxParseUtil.makeHttpLink( m_oUserProfile.m_strUrl1 );    		
    	}
    	
    	if( 0 !=  m_oUserProfile.m_strUrl2.length() )
    	{
    		strUrl1 = VxParseUtil.makeHttpLink( m_oUserProfile.m_strUrl2 );    		
    	}
    	
    	if( 0 !=  m_oUserProfile.m_strUrl3.length() )
    	{
    		strUrl1 = VxParseUtil.makeHttpLink( m_oUserProfile.m_strUrl3 );    		
    	}
    			
     	String strTrailer = "</body></html>\r\r\r";
     	m_VxFileUtil.VxWriteExternFile( m_MyApp.getUserProfileDir() + "index.htm", 
     			strWebPageHdr + strUserName + strGreeting + strAbout + strPicLabel + strPicture + strFavWebsites + strUrl1 +strUrl2 + strUrl3 + strUrl4 + strTrailer );	
    } 
}
