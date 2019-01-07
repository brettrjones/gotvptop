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
import android.app.ListActivity;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.media.AudioManager;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.view.WindowManager;
import android.view.View.OnClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;


public class ActivityListBase extends ListActivity implements ToGuiMessageInterface
{
	//=== constants ===//
	private static final String 		LOG_TAG = "ActivityListBase:";
		
	//=== vars ===//
	public 	MyApp 						m_MyApp 				= null;
    private boolean						m_bIsVisible 			= false;
    public boolean						m_IsMainContactList 	= false;
    private	Button 						m_TitleBarHelpButton 	= null;
    private	String 						m_TitleBarHelpUrl 		= "http://www.gotvp2p.net";
	public	Button 						m_CloseButton 			= null;
	public 	TextView            		m_TitleText 			= null;	
	private TextView 					m_StatusMsgLabel 		= null;
	private TextView 					m_TotalCamClientsText 	= null;
 	
 	// sound
	protected Button            		m_MuteMicrophoneBut 	= null;
    protected Button              		m_MuteSpeakerBut 		= null;
 	
	public ImageView            		m_HisIdentIcon 			= null;	
	public TextView            			m_HisIdentName 			= null;	
	public TextView            			m_HisIdentMoodMsg 		= null;	
	public TextView            			m_HisIdentTruths 		= null;	

	public VxNetIdent					m_poFriendIdent 		= null;
	//private CpuMonitor 					m_CpuMonitor		= null;
 	//private Handler 					m_UpdateCpuTimerHandler = new Handler(); 
	private OfferBarWidget				m_OfferBarWidget		= null;
	private Handler 					m_MyEventHandler 		= null; 
	private boolean						m_OncePerSecStarted 	= false;
	//private int							m_DieCountdown			= 10;
	boolean								m_NeedFinishCreation 	= false;
	
    //========================================================================
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        m_MyApp = (MyApp) this.getApplication();
        
        //Connect Hardware volume buttons to adjust STREAM_MUSIC used for both sound effects and voice over IP
        this.setVolumeControlStream(AudioManager.STREAM_MUSIC);
        m_TotalCamClientsText 	= (TextView)this.findViewById( R.id.total_cam_clients_text );
        m_StatusMsgLabel = (TextView)this.findViewById( R.id.status_msg_label );
    	m_TitleBarHelpButton = (Button)this.findViewById(R.id.button_title_bar_help);
        if( null != m_TitleBarHelpButton )
        {
        	m_TitleBarHelpButton.setOnClickListener(new OnClickListener() 
 	        {
 	        	public void onClick(View v) 
 			 	{
 				    m_MyApp.playButtonClick();
 				    onTitleBarHelpClick();
 			 	}
 			});	
        }

        m_CloseButton = (Button)this.findViewById(R.id.button_close);
        if( null != m_CloseButton )
        {
 	        m_CloseButton.setOnClickListener(new OnClickListener() 
 	        {
 	        	public void onClick(View v) 
 			 	{
 				    m_MyApp.playButtonClick();
			 		onBackButtonPressed();
 			 	}
 			});	
        }
       
        m_TitleText = (TextView)this.findViewById( R.id.label_title );
        if( null == m_TitleText )
        {
     	   Log.e(LOG_TAG, "Failed to get title label" );
        }
        
       	setToGuiMessageReadyState( this );    

        m_HisIdentIcon = (ImageView)this.findViewById( R.id.friend_icon );
        if( null != m_HisIdentIcon )
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
        if( null != m_HisIdentName )
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
        if( null != m_HisIdentMoodMsg )
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
        if( null != m_HisIdentTruths )
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
 	    if( false == m_IsMainContactList )
 	    {
 	    	setupSoundAndOfferBar();
 	    }
 	    
		m_MyEventHandler = new Handler() 
		{
		    @Override
		    public void handleMessage(Message msg) 
		    {
		    	switch(msg.what)
		    	{
		    	case Constants.MY_EVENT_ONCE_PER_SEC:
		    		//Log.i( LOG_TAG, "Rxed MY_EVENT_ONCE_PER_SEC" );
		    		onOncePerSecond();
		    		if( false == m_MyApp.getIsAppShuttingDown() )
		    		{
		    			m_MyEventHandler.sendEmptyMessageDelayed( Constants.MY_EVENT_ONCE_PER_SEC, 1000 );
		    		}
		    		
		    		break;    		
		    	}
		    	
		    	super.handleMessage(msg);
		    }
		};
    }
	
    //========================================================================
	public void startOncePerSecondEvent()
	{
		if( false == m_OncePerSecStarted )
		{
			m_OncePerSecStarted = true;
	     	m_MyEventHandler.sendEmptyMessageDelayed( Constants.MY_EVENT_ONCE_PER_SEC, 1000 );			
		}
	}
	    
	//========================================================================
	protected void onOncePerSecond()
	{  
		Log.d( LOG_TAG,  "ActivityListBase:onOncePerSecond" );
	}
    
	//========================================================================
	public void setupSoundAndOfferBar() 
	{
 	    setupSound();
 	    setCamCaptureActivity( this );
	    //if( m_MyApp.getIsCpuMonitorEnabled() )
        //{
    	//   	m_CpuMonitor = new CpuMonitor(this);
        //}

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
	public void setTitleBarHelpUrl( String helpUrl ) 
	{
		m_TitleBarHelpUrl = helpUrl;
		if( !m_TitleBarHelpUrl.isEmpty() )
		{
			if( null != m_TitleBarHelpButton )
			{
				m_TitleBarHelpButton.setVisibility( View.VISIBLE );
			}
		}		
	}

	//========================================================================
	private void onTitleBarHelpClick() 
	{
		if( !m_TitleBarHelpUrl.isEmpty() )
		{
			Intent launchBrowser = new Intent(Intent.ACTION_VIEW, Uri.parse( m_TitleBarHelpUrl ) );
			startActivity( launchBrowser );				
		}		
	}
    
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
    public void updateSoundControls()
    {
    	if( NativeTxTo.fromGuiIsPluginInSession( Constants.ePluginTypeCamServer, m_MyApp.getMyOnlineId().m_u64IdHiPart, m_MyApp.getMyOnlineId().m_u64IdLoPart, 
				0, 0, 0 ) )
		{
    		if( null != m_MuteMicrophoneBut )
    		{
    			m_MuteMicrophoneBut.setVisibility( View.VISIBLE );
    		}
		}
    	else
    	{
    		if( null != m_MuteMicrophoneBut )
    		{
    			m_MuteMicrophoneBut.setVisibility( View.GONE );
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
 	private void onMuteSpeakerButClick( View v ) 
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
	@Override
	public void onListItemClick(ListView parent, View v, int position, long id) 
	{
	}
    
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
    
        int iIconResource = Constants.getFriendIconResource(iMyFriendshipToHim);

   	    Log.i(LOG_TAG, "icon " + m_HisIdentIcon.toString() );
   	    m_HisIdentIcon.setImageResource(iIconResource);	
	}
  
	//========================================================================
    @Override
    protected void onPause() 
    {
    	if( null != m_MyApp.getCamCaptureMgr() )
    	{
       		Log.d( Constants.LIFETIME, "&& ActivityListBase doing onPause" );
       		setToGuiMessageReadyState( null );    
    		setCamCaptureActivity( null );
    		m_bIsVisible = false;
    		m_MyApp.setActivityPause( true );
    	}
    	//else
    	//{
    	//	Log.d( Constants.LIFETIME, "&& ActivityListBase skipping onPause" );
    	//}
    	
     	super.onPause();
    }
	 
	//========================================================================
    @Override
    protected void onResume() 
    {
		super.onResume();    	
    	if( null != m_MyApp.getCamCaptureMgr() )
    	{
     		Log.d( Constants.LIFETIME, "&& ActivityListBase doing onResume" );
		  	m_MyApp.setActivityPause( false );
		  	setCamCaptureActivity( this );
		  	setToGuiMessageReadyState( this );    
    	}
    	//else
    	//{
    	//	Log.d( Constants.LIFETIME, "&& ActivityListBase skipping onResume" );
    	//}
    }
    
	//========================================================================
	@Override
	protected void onDestroy() 
	{
    	if( null != m_MyApp.getCamCaptureMgr() )
    	{
			if( null != m_OfferBarWidget )
			{
				m_OfferBarWidget.shudownOfferBarWidget();
			}
			
		 	setToGuiMessageReadyState( null );
    	}
    	
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
 				else if( ( Constants.VXFILE_TYPE_AUDIO == fileInfo.getFileType() ) && fileInfo.isMyP2PWebAudioFile() )
 				{
 					m_MyApp.setCurrentFileInfo( fileInfo );
 					Intent myIntent = new Intent( activity, ActivityViewAudioFile.class );
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
    public void setCamCaptureActivity( Activity curActivity )
    {
    	if( null != m_MyApp.getCamCaptureMgr() )
    	{
    		m_MyApp.getCamCaptureMgr().setCamActivity( curActivity, R.id.cam_preview_frame, R.id.no_preview_image );
    	}
    	
    	 updateSoundControls();
    }
    
   	//========================================================================
    boolean isVisible()
    {
       	return m_bIsVisible; 
    }
  
 	//========================================================================
    public void onBackButtonPressed() 
    {
 		m_bIsVisible = false; 
 		finish();
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
    // Avoid that the screen getting turned off by the system.
	public void disableScreenTurnOff() 
	{
    	getWindow().setFlags( WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON, WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON );
    }    
    
	//========================================================================
    // Maximize the application.
    public void setFullscreen()  
    {
    	setNoTitle();
        getWindow().setFlags( WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN );
    }
   
	//========================================================================
    public void setNoTitle() 
    {
    	// this crashes
        //requestWindowFeature(Window.FEATURE_NO_TITLE);
    } 
	
	//============================================================================
	//! show message box to user
	void errMsgBox( boolean bExitWhenClicked, String strMsg )
	{
		final boolean exitWhenClicked = bExitWhenClicked;
		AlertDialog.Builder builder = new AlertDialog.Builder(this); 
		builder.setMessage(strMsg) 
		       .setPositiveButton("Ok", new DialogInterface.OnClickListener() 
		       { 
		           public void onClick(DialogInterface dialog, int id) 
		           { 
	     			   m_MyApp.playButtonClick();
		               // Handle Ok 
		        	   if( exitWhenClicked )
		        	   {
		        		   onBackButtonPressed();
		        	   }
		           } 
		       }) 
		       /*
		       .setNegativeButton("Cancel", new DialogInterface.OnClickListener() 
		       { 
		           public void onClick(DialogInterface dialog, int id) 
		           { 
		               // Handle Cancel 
     			   		m_MyApp.playButtonClick();
		           } 
		       }) 
		       */
		       .create().show(); 	
	}
	
	//============================================================================
	//! show message box to user
	void chooseMsgBox( boolean bExitWhenClicked, String strMsg )
	{
		final boolean exitWhenClicked = bExitWhenClicked;
		AlertDialog.Builder dlgAlert = new AlertDialog.Builder(this); 
	    dlgAlert.setTitle("Choice");  
	    dlgAlert.setMessage( strMsg );  
	    dlgAlert.setPositiveButton("OK",new DialogInterface.OnClickListener() 
	    { 
	        public void onClick(DialogInterface dialog, int whichButton) 
	        { 
        	   if( exitWhenClicked )
        	   {
        		   onBackButtonPressed();
        	   }
        	   else
        	   {
     			   	m_MyApp.playButtonClick();
     			   	onOkButtonClicked();
        	   }
	        } 
	    }); 
	    
	    dlgAlert.setNegativeButton("Cancel",new DialogInterface.OnClickListener() 
	    { 
	        public void onClick(DialogInterface dialog, int whichButton) 
	        { 
  			   	m_MyApp.playButtonClick();
        	   if( exitWhenClicked )
        	   {
        		   onBackButtonPressed();
        	   }
        	   else
        	   {
        		   onCancelButtonClicked();
        	   }
	        } 
	    }); 
	    
	    dlgAlert.setCancelable(true); 
	    dlgAlert.create().show(); 
	}
	
	//========================================================================
	void onOkButtonClicked()
	{
		
	}
	
	//========================================================================
	void onCancelButtonClicked()
	{
		
	}

	//========================================================================
	void setStatusMessage( String strMsgIn ) 
	{
		if( null != m_StatusMsgLabel )
		{
			final String strMsg = strMsgIn;
			runOnUiThread(new Runnable() {
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

	@Override
	public void toGuiPluginLogMessage( int ePluginType, String strLogMsg )
	{
		// TODO Auto-generated method stub
		
	}
}

