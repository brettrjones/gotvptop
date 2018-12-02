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

import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.media.AudioManager;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.View;
import android.view.WindowManager;
import android.view.View.OnClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

public class ActivityBase extends Activity implements ToGuiMessageInterface, OfferSessionCallbackInterface 
{
	//=== constants ===//
	private static final String 		LOG_TAG = "ActivityBase:";
		
	//=== vars ===//
	public 	MyApp 						m_MyApp 				= null;
    private boolean						m_bIsVisible 			= false;
	public	Button 						m_CloseButton 			= null;
	public 	TextView            		m_TitleText 			= null;	
	private TextView 					m_StatusMsgLabel 		= null;
	private TextView 					m_TotalCamClientsText 	= null;
	private OfferBarWidget				m_OfferBarWidget		= null;
	
 	// sound
    protected Button            		m_MuteMicrophoneBut 	= null;
    protected Button              		m_MuteSpeakerBut 		= null;
 
	public ImageView            		m_HisIdentIcon 			= null;	
	public TextView            			m_HisIdentName 			= null;	
	public TextView            			m_HisIdentMoodMsg 		= null;	
	public TextView            			m_HisIdentTruths 		= null;	

	public VxNetIdent					m_poFriendIdent 		= null;
	//private CpuMonitor 					m_CpuMonitor			= null;
    private boolean						m_OnStopWasCalled		= false;
 	private Handler 					m_500msHandler 			= new Handler();
    private boolean						m_500msTickTock			= false;
	
    //========================================================================
	@Override
	public void onCreate(Bundle savedInstanceState) 
    {
       super.onCreate(savedInstanceState);
       m_MyApp = (MyApp) this.getApplication();
               
       m_CloseButton = (Button)this.findViewById(R.id.button_close);
       if(null != m_CloseButton)
       {
	        m_CloseButton.setOnClickListener(new OnClickListener() 
	        {
	        	public void onClick(View v) 
			 	{
	        		m_MyApp.playButtonClick();
			 		m_bIsVisible = false; 
			 		onBackButtonPressed();
			 	}
	        });	
       }
      
       m_TitleText = (TextView)this.findViewById( R.id.label_title );
       if( null == m_TitleText )
       {
    	   Log.e(LOG_TAG, "Failed to get title label" );
       }
       
       m_TotalCamClientsText 	= (TextView)this.findViewById( R.id.total_cam_clients_text );
       m_StatusMsgLabel 		= (TextView)this.findViewById( R.id.status_msg_label );
       setToGuiMessageReadyState( this );    

       m_HisIdentIcon = (ImageView)this.findViewById( R.id.friend_icon );
       if(null != m_HisIdentIcon)
       {
    	   m_HisIdentIcon.setOnClickListener(new OnClickListener() 
    	   {
		 	  	public void onClick(View v) 
		 	  	{
	        		m_MyApp.playButtonClick();
		 	  		if( null != m_poFriendIdent )
		 		  	{
		 	  			onFriendClicked( m_poFriendIdent );
		 		  	}
		 	  	}
    	   });	
       }
       
       m_HisIdentName = (TextView)this.findViewById( R.id.friend_name );
       if(null != m_HisIdentName)
       {
    	   m_HisIdentName.setOnClickListener(new OnClickListener() 
    	   {
    		   public void onClick(View v) 
    		   {
    			   m_MyApp.playButtonClick();
    			   if( null != m_poFriendIdent )
    			   {
    				   onFriendClicked( m_poFriendIdent );
    			   }
    		   }
    	   });	
       }
       
       m_HisIdentMoodMsg = (TextView)this.findViewById( R.id.friend_mood_msg );
       if(null != m_HisIdentMoodMsg)
       {
    	   m_HisIdentMoodMsg.setOnClickListener(new OnClickListener() 
    	   {
    		   public void onClick(View v) 
    		   {
    			   m_MyApp.playButtonClick();
    			   if( null != m_poFriendIdent )
    			   {
    				   onFriendClicked( m_poFriendIdent );
    			   }
    		   }
    	   });	
       }
       
       m_HisIdentTruths = (TextView)this.findViewById( R.id.friend_truths );
       if(null != m_HisIdentTruths)
       {
    	   m_HisIdentTruths.setOnClickListener(new OnClickListener() 
    	   {
    		   public void onClick(View v) 
    		   {
    			   m_MyApp.playButtonClick();
    			   if( null != m_poFriendIdent )
    			   {
    				   onFriendClicked( m_poFriendIdent );
    			   }
    		   }
    	   });	
       }
      
	   m_bIsVisible = true;
	   setupSound();
	   setCamCaptureActivity( this );
//	   if( m_MyApp.getIsCpuMonitorEnabled() )
//       {
//    	   	m_CpuMonitor = new CpuMonitor(this);
//       }
	   
 	   m_OfferBarWidget = new OfferBarWidget( 	m_MyApp, 
												this,
												(LinearLayout)findViewById( R.id.offer_bar_layout ),
												(TextView)findViewById( R.id.total_offers_text ),			   									
												(Button)findViewById( R.id.offer_bar_icon ),
												(Button)findViewById( R.id.offer_bar_accept_button ),
												(Button)findViewById( R.id.offer_bar_reject_button ),
												(TextView)findViewById( R.id.offer_bar_toptext ),
												(TextView)findViewById( R.id.offer_bar_missed_call_label ),
												(TextView)findViewById( R.id.offer_bar_missed_call_count ),
												(TextView)findViewById( R.id.offer_bar_bottomtext )
												);
 	   
		m_500msHandler.postDelayed(DoOncePer500msTask, 500);
    }
	
	//========================================================================
	public void checkVolumeLevel()
	{
		//Connect Hardware volume buttons to adjust STREAM_MUSIC used for both sound effects and voice over IP
	    this.setVolumeControlStream(AudioManager.STREAM_MUSIC);
	    final AudioManager audioManager = (AudioManager)getSystemService( Context.AUDIO_SERVICE );
	    int maxVolume 	= audioManager.getStreamMaxVolume( AudioManager.STREAM_MUSIC );
	    int curVolume	= audioManager.getStreamVolume( AudioManager.STREAM_MUSIC ); 
	    if( curVolume < ( maxVolume / 2 ) )
	    {    	
        	Toast.makeText( this, R.string.warning_low_volume, Toast.LENGTH_LONG ).show();
	    }    
	    
	    showSpeakerButton( true );
	}

	//========================================================================
	public void stopOnTimeEvents()
	{
		m_OnStopWasCalled = true;
	}
	
	//========================================================================
	private Runnable DoOncePer500msTask = new Runnable() 
	{
        public void run() 
        {
            //final String orgName = Thread.currentThread().getName();
            //Thread.currentThread().setName( orgName + " ToFriendGuiBase:DoOncePer500msTask" );		
        	onOncePer500ms();      	
        	if( m_500msTickTock )
        	{
        		m_500msTickTock = false;
        		onOncePerSecond();
        	}
        	else
        	{
        		m_500msTickTock = true;
        	}
        	
        	if( !m_OnStopWasCalled  )
        	{
        		m_500msHandler.postDelayed( this, 500 );
        	}
        }
    };
    
	//========================================================================
    protected void onOncePer500ms() 
	{
    };
    
	//========================================================================
    protected void onOncePerSecond() 
	{
    };
     
	//========================================================================
    private void setupSound()
    {    
    	setupSpeakerControl();
	    m_MuteMicrophoneBut = (Button)this.findViewById( R.id.button_mic_mute );
	    if( null != m_MuteMicrophoneBut )
	    {
	    	setMicrophoneMuteIcon( NativeTxTo.fromGuiIsMicrophoneMuted() );
	    	m_MuteMicrophoneBut.setOnClickListener(new OnClickListener() 
	    	{
	            public void onClick(View v) 
	            {
	  			   	m_MyApp.playButtonClick();
	  			   	onMuteMicrophoneButClick(v);
	            }
	        });   
	    	
	    	if( NativeTxTo.fromGuiIsPluginInSession( Constants.ePluginTypeCamServer, m_MyApp.getMyOnlineId().m_u64IdHiPart, m_MyApp.getMyOnlineId().m_u64IdLoPart, 
	    					0, 0, 0 ) )
	    	{
	    		m_MuteMicrophoneBut.setVisibility( View.VISIBLE );
	    	}
	    }    	    
	}

	//========================================================================      
    public void showMicrophoneButton( boolean showButton ) 
    {
    	if( null != m_MuteMicrophoneBut )
    	{
    		m_MuteMicrophoneBut.setVisibility( showButton ? View.VISIBLE : View.GONE );
    	}
    } 

	//========================================================================      
    private void onMuteMicrophoneButClick(View v) 
    {
    	boolean isMicrophoneMuted = !NativeTxTo.fromGuiIsMicrophoneMuted();
 
    	setStatusMessage( isMicrophoneMuted ? "Microphone is muted" :  "Microphone is unmuted" );
    	setMicrophoneMuteIcon( isMicrophoneMuted );
    	NativeTxTo.fromGuiMuteMicrophone( isMicrophoneMuted );
    } 
    
 	//======================================================================== 
     private void setMicrophoneMuteIcon( boolean bIsMicrophoneMuted )
     {
         if( null != m_MuteMicrophoneBut )
         {
         	m_MuteMicrophoneBut.setBackgroundResource( bIsMicrophoneMuted ? R.drawable.button_microphone_cancel_normal : R.drawable.button_microphone_normal );       	
         }
     }

  	//========================================================================      
     public void showSpeakerButton( boolean showButton ) 
     {
      	if( null != m_MuteSpeakerBut )
      	{
      		m_MuteSpeakerBut.setVisibility( showButton ? View.VISIBLE : View.GONE );
      	}
     } 
      
    //========================================================================
    private void setupSpeakerControl()
    {
    	m_MuteSpeakerBut = (Button)this.findViewById(R.id.button_speaker_mute);
        if( null != m_MuteSpeakerBut )
        {
         	 m_MuteSpeakerBut.setOnClickListener(new OnClickListener() 
          	{
  	            public void onClick(View v) 
  	            {
  	  			   	m_MyApp.playButtonClick();
  	            	onMuteSpeakerButClick(v);
  	            }
          	});     
         	 
         	setSpeakerIcon( NativeTxTo.fromGuiIsSpeakerMuted() );
        }
    }	
  	
  	//========================================================================      
  	private void onMuteSpeakerButClick(View v) 
  	{
 	   	boolean isSpeakerMuted = !NativeTxTo.fromGuiIsSpeakerMuted();
 	   	setSpeakerIcon( isSpeakerMuted );
	   	NativeTxTo.fromGuiMuteSpeaker( isSpeakerMuted );
  	}  
    
	//========================================================================      
	private void setSpeakerIcon( boolean isSpeakerMuted )
	{
	    if( null != m_MuteSpeakerBut )
	    {
	    	m_MuteSpeakerBut.setBackgroundResource( isSpeakerMuted ? R.drawable.button_speaker_off_normal : R.drawable.button_speaker_on_normal );       	
	    }
	}

	//============================================================================  
	void checkDiskSpace()
	{
		long diskFreeSpace = NativeTxTo.fromGuiGetDiskFreeSpace();
		if( ( 0 != diskFreeSpace ) && ( diskFreeSpace < 1000000000 ) )
		{
			m_MyApp.toGuiUserMessage( "Disk Space is low " + VxFileUtil.describeFileLength( diskFreeSpace ) );
		}
		else
		{
			m_MyApp.toGuiUserMessage( "Disk Space " + VxFileUtil.describeFileLength( diskFreeSpace ) );			
		}
	}
	
	//========================================================================
	protected  ArrayAdapter<String> fillFileFilterSpinner( Spinner fileFilterSpinner ) 
	{
	 	List<String> fileFilterTypeList = new ArrayList<String>();
	 	fileFilterTypeList.add( getString( R.string.file_filter_all_types ) );
	 	fileFilterTypeList.add( getString( R.string.photo ) );
	 	fileFilterTypeList.add( getString( R.string.music ) );
	 	fileFilterTypeList.add( getString( R.string.videos ) );
	 	fileFilterTypeList.add( getString( R.string.documents ) ); 
	 	fileFilterTypeList.add( getString( R.string.file_filter_archive ) );
	 	fileFilterTypeList.add( getString( R.string.file_filter_other_files ) ); 
	 	
	    ArrayAdapter<String> fileFilterAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, fileFilterTypeList );
	    fileFilterSpinner.setAdapter( fileFilterAdapter ); 
	    return fileFilterAdapter;
    };
	
    //========================================================================
	public void	onFriendClicked( VxNetIdent poFriendIdent )
	{  
		
	}
	
	//========================================================================
	public void	fillFriend( VxNetIdent oIdent )
	{
		m_poFriendIdent = oIdent;

        int iMyFriendshipToHim = oIdent.getMyFriendshipToHim();
        //Log.i(LOG_TAG, "friendship " + iMyFriendshipToHim + " raw " + oIdent.m_u8FriendMatch );
        Log.i(LOG_TAG, "getView online status " + oIdent.isOnline() + " online flags " + oIdent.m_u8OnlineStatusFlags + " " + oIdent.getOnlineName() + " permissions " + oIdent.m_au8Permissions ); 
      
        //int iTextColor = Constants.OFFLINE_COLOR;
        LinearLayout friendLayout = (LinearLayout)this.findViewById( R.id.reuse_friend_layout );
        if( null != friendLayout )
        {
	    	if( oIdent.isNearby() )
	    	{
	            Log.d(LOG_TAG, oIdent.getOnlineName() + " is nearby " ); 
	    		//iTextColor = Constants.NEARBY_COLOR;
	            friendLayout.setBackgroundResource( R.color.nearby_bkg_color );
	    	}
	    	else if( oIdent.isOnline() )
	    	{
	            Log.d(LOG_TAG, oIdent.getOnlineName() + " is online " ); 
	    		//iTextColor = Constants.ONLINE_COLOR;
	            friendLayout.setBackgroundResource( R.color.online_bkg_color );
	    	}
	    	else
	    	{
	            Log.d(LOG_TAG, oIdent.getOnlineName() + " is offline " );
	            friendLayout.setBackgroundResource( R.color.offline_bkg_color );
	    	}
        }

        if( null != m_HisIdentName ) 
        {
        	//m_HisIdentName.setTextColor( iTextColor );
        	if( ( 0 <= iMyFriendshipToHim )
        			&& ( 0 <= iMyFriendshipToHim ) )
        	{
            	m_HisIdentName.setText( oIdent.getOnlineName() + " - " + Constants.describeFriendState( iMyFriendshipToHim ) );                                   		
        	}
        	else
        	{
            	m_HisIdentName.setText( oIdent.getOnlineName()  + " - Unknown" );                                   		       		
        	}
        }
        
        if( null != m_HisIdentMoodMsg ) 
        {
        	//m_HisIdentMoodMsg.setTextColor(iTextColor);
        	m_HisIdentMoodMsg.setText( "Mood: " + oIdent.getOnlineDescription() );
        }

        if( null != m_HisIdentTruths ) 
        {
        	//truthStatsText.setTextColor(iTextColor);
        	String todText = "Truths: " + oIdent.getTruthCount() + " Dares: " + oIdent.getDareCount();
        	m_HisIdentTruths.setText( todText );
        }
    
        int iIconResource = Constants.getFriendIconResource( iMyFriendshipToHim );

   	    Log.i(LOG_TAG, "icon " + m_HisIdentIcon.toString() );
   	    m_HisIdentIcon.setImageResource( iIconResource );	
	}
  
	//========================================================================
    @Override
    protected void onPause() 
    {
       	setToGuiMessageReadyState( null );    
       	setCamCaptureActivity( null );
    	m_bIsVisible = false;
     	super.onPause();  
     	m_MyApp.setActivityPause( true );
//     	if( null != m_CpuMonitor )
//     	{
//     		m_CpuMonitor.pause();
//     	}
    }
	 
	//========================================================================
    @Override
    protected void onResume() 
    {
     	m_MyApp.setActivityPause( false );
		super.onResume();    	
	    setCamCaptureActivity( this );
//     	if( null != m_CpuMonitor )
//     	{
 //    		m_CpuMonitor.resume();
 //    	}
     	
       	setToGuiMessageReadyState( this );    
    }
    
	//========================================================================
    @Override
    protected void onStop() 
    {
    	m_OnStopWasCalled = true;
    	super.onStop();
    }
 
	//========================================================================
    @Override
    protected void onDestroy() 
    {
    	m_OnStopWasCalled = true;
		if( null != m_OfferBarWidget )
		{
			m_OfferBarWidget.shudownOfferBarWidget();
		}
   	
		setToGuiMessageReadyState( null );
//    	if( null != m_CpuMonitor )
//     	{     
//     		m_CpuMonitor.release();
//     	}
     	
     	super.onDestroy();
    }
    
	//============================================================================
    protected void playFile( Activity activity, VxFileInfo fileInfo )
	{
		if( null != fileInfo )
		{
			if( Constants.VXFILE_TYPE_DIRECTORY != fileInfo.getFileType() )
			{
				if( Constants.VXFILE_TYPE_PHOTO == fileInfo.getFileType() )
				{
					m_MyApp.setCurrentFileInfo( fileInfo );
					Intent myIntent = new Intent( activity, ActivityViewPhoto.class );
					activity.startActivityForResult( myIntent, Constants.ACTIVITY_VIEW_PHOTO );					
				}
				else if( ( Constants.VXFILE_TYPE_VIDEO == fileInfo.getFileType() ) && fileInfo.isMyP2PWebVideoFile() )
				{
					m_MyApp.setCurrentFileInfo( fileInfo );
					Intent myIntent = new Intent( activity, ActivityViewVideoFile.class );
					myIntent.putExtra( Constants.PARAM_FILE_NAME, fileInfo.getFullFileName() );
					activity.startActivityForResult( myIntent, Constants.ACTIVITY_VIEW_VIDEO_FILE );					
				}
				else
				{
					VxFileUtil.viewFileInDefaultApplication( activity, fileInfo.getFullFileName() );
				}
			}			
		}
	}

  	//========================================================================
    protected void setToGuiMessageReadyState( Activity curActivity )
    {
 		try 
 		{
 			if( ( null == curActivity ) || ( null == m_StatusMsgLabel ) )
 			{
 				NativeRxFrom.wantToGuiMessageClient( this, false );
 			}
 			else
 			{
 				NativeRxFrom.wantToGuiMessageClient( this, true );
 			}
 		} 
 		catch (InterruptedException e) 
 		{
 			e.printStackTrace();
 		}
    }
   
	//========================================================================
    protected void setCamCaptureActivity( Activity curActivity )
    {
    	if( null != m_MyApp.getCamCaptureMgr() )
    	{
    		m_MyApp.getCamCaptureMgr().setCamActivity( curActivity, R.id.cam_preview_frame, R.id.no_preview_image );
    	}
    }
    
   	//========================================================================
    boolean isVisible()
    {
       	return m_bIsVisible; 
    }
  
 	//========================================================================
    public void onBackButtonPressed() 
    {
    	Intent resultIntent = new Intent();
    	setResult(Activity.RESULT_CANCELED, resultIntent);
    	finish();
    }
    
  	//========================================================================
    @Override
    public void onBackPressed() 
    {
    	onBackButtonPressed();
    } 
    
  	//========================================================================
    public void setPageTitle( int stringIdTitle )
	{
    	if( null != m_TitleText )
        {
        	m_TitleText.setText( stringIdTitle );
        }
	}
    
   	//========================================================================
    public void setTitleText( String titleText )
 	{
     	if( null != m_TitleText )
        {
         	m_TitleText.setText( titleText );
        }
 	}
     
	//========================================================================
    // Avoid that the screen getting turned off by the system.
	public void disableScreenTurnOff() 
	{
    	getWindow().setFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON,
    			WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
    }    
    
	//========================================================================
    // Maximize the application.
    public void setFullscreen()  
    {
        getWindow().setFlags( WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN );
    }
    
	//============================================================================
    public void showOfflineMsg( VxNetIdent hisIdent )
    {
    	if( null != hisIdent )
    	{
    		Toast.makeText( this, hisIdent.m_as8OnlineName + " Is Offline.", Toast.LENGTH_SHORT).show();
    	}
    }
	
	//============================================================================
	//! show error message box to user
	void errMsgBox( boolean bExitWhenClicked, String strMsg )
	{
		final boolean exitWhenClicked = bExitWhenClicked;
		AlertDialog.Builder dialog = new AlertDialog.Builder(this); 
		dialog.setTitle("Error Message")
		.setMessage(strMsg) 
		       .setPositiveButton("Ok", new DialogInterface.OnClickListener() 
		       {
		    	   @Override
		           public void onClick(DialogInterface dialog, int id) 
		           { 
		               // Handle Ok 
	    			   m_MyApp.playButtonClick();
		        	   if( exitWhenClicked )
		        	   {
		        		   onBackButtonPressed();
		        	   }
		           } 
		       }); 
		       /*
		       .setNegativeButton("Cancel", new DialogInterface.OnClickListener() 
		       { 
		           public void onClick(DialogInterface dialog, int id) { 
		               // Handle Cancel 
	    			   m_MyApp.playButtonClick();
		           } 
		       }) 
		       */
		dialog.show(); 	
	}

	//========================================================================
	void setStatusMessage( String strMsgIn ) 
	{
		if( null != m_StatusMsgLabel )
		{
			final String strMsg = strMsgIn;
			runOnUiThread(new Runnable() 
			{
				public void run() 
				{
					m_StatusMsgLabel.setText(strMsg);
				}
			});
		}
	}

  	//========================================================================
    public void setStatusMessage( int stringId )
	{
        if( null != m_StatusMsgLabel )
        {
        	m_StatusMsgLabel.setText( stringId );	
        }
	}

  	//========================================================================
	@Override
	public void toGuiUserMessage( String userMsg )
	{
		if( null != m_StatusMsgLabel )
		{
			m_StatusMsgLabel.setText( userMsg );
		}		
	}

  	//========================================================================
	@Override
	public void toGuiUserMessage( int stringResId )
	{
		if( null != m_StatusMsgLabel )
		{
			m_StatusMsgLabel.setText( stringResId );
		}		
	}
	
  	//========================================================================
	@Override
	public void toGuiStatusMessage( String statusMsg )
	{
		setStatusMessage( statusMsg );
	}

  	//========================================================================
	@Override
	public void doToGuiPluginStatus( int ePluginType, int statusType, int statusValue )
	{
		if( ( Constants.ePluginTypeCamServer == ePluginType )
			&& ( 1 == statusType )
			&& ( null != m_TotalCamClientsText ) )
		{
			if( statusValue < 0 )
			{
				m_TotalCamClientsText.setText( "" );
			}
			else
			{
				String valueAsText = String.format( Locale.getDefault(), "%d", statusValue ); 
				m_TotalCamClientsText.setText( valueAsText );
			}		
		}	
	}

  	//========================================================================
	@Override
	public void onSessionStateChange( int eSessionState )
	{
	}

  	//========================================================================
	@Override
	public void onInSession( boolean isInSession )
	{
	}

  	//========================================================================
	@Override
	public void onContactOnline()
	{
	}

  	//========================================================================
	@Override
	public void onContactOffline()
	{
	}

  	//========================================================================
	@Override
	public void onSessionActivityShouldExit()
	{
		stopOnTimeEvents();
		onBackButtonPressed();				
	}

  	//========================================================================
	@Override
	public void toGuiPluginLogMessage( int ePluginType, String strLogMsg )
	{
	}
}

