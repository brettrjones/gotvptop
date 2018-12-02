//============================================================================
// Copyright (C) 2009 Brett R. Jones
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

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;

import android.os.Bundle;
import android.util.Log;

public class PopupMenu extends ActivityListBase 
{
	//=== constants ===//
	private static final String LOG_TAG = "PopupMenu:";

	//=== vars ===//
  	private List<PopupMenuItem> 	m_aoMenuItems;
 	
  	//============================================================================
	@Override
	public void onCreate(Bundle savedInstanceState) 
	{
    	requestWindowFeature(Window.FEATURE_NO_TITLE); 
        setContentView( R.layout.popup_menu );
	    super.onCreate(savedInstanceState);
	    Log.i(LOG_TAG, "onCreateCalled");
 	    
        m_aoMenuItems = getMenuItems( m_MyApp.getActiveMenu() );
	    setListAdapter(new CustomAdapter());
	    Log.i(LOG_TAG, "Custom Adapter made");
		m_MyApp.playButtonClick();
	}
	
  	//============================================================================
    private List<PopupMenuItem> getMenuItems( int iMenuId ) 
    {
	    //Log.i(LOG_TAG, "Getting menu items");	    
        List<PopupMenuItem> items = new ArrayList<PopupMenuItem>();
        if( iMenuId == Constants.MENU_PEOPLE )
        {
        	// title
        	this.setPageTitle( R.string.menu_people );
			items.add(new PopupMenuItem(iMenuId, Constants.MENU_PEOPLE_VIEW_EVERYBODY, 			R.drawable.button_people_normal, "EveryBody" ));
            items.add(new PopupMenuItem(iMenuId, Constants.MENU_PEOPLE_VIEW_GUESTS_AND_FRIENDS, R.drawable.button_people_normal, "Friends And Guests" ));
            items.add(new PopupMenuItem(iMenuId, Constants.MENU_PEOPLE_VIEW_ANONYMOUS, 			R.drawable.button_person_unknown_normal, "Anonymous" ));
            items.add(new PopupMenuItem(iMenuId, Constants.MENU_PEOPLE_VIEW_ADMINISTRATORS, 	R.drawable.button_administrator_normal, "Administrators" ));            
            items.add(new PopupMenuItem(iMenuId, Constants.MENU_PEOPLE_VIEW_IGNORED, 			R.drawable.ic_ignore, "Ignored" ));
            items.add(new PopupMenuItem(iMenuId, Constants.MENU_PEOPLE_VIEW_MY_PROXIES, 		R.drawable.button_proxy_normal, "My Relays" ));
            items.add(new PopupMenuItem(iMenuId, Constants.MENU_PEOPLE_VIEW_ALL_PROXIES, 		R.drawable.button_proxy_normal, "All Possible Relays" ));            
            items.add(new PopupMenuItem(iMenuId, Constants.MENU_PEOPLE_VIEW_REFRESH, 			R.drawable.button_refresh_normal, "Refresh List" ));
        }
        else if( iMenuId == Constants.MENU_FILES )
        {
        	this.setPageTitle( R.string.menu_files );
           	items.add(new PopupMenuItem(iMenuId, Constants.MENU_FILES_PERSONAL_RECORDER, 		R.drawable.button_notepad_normal, "Personal Recorder" ));
        	items.add(new PopupMenuItem(iMenuId, Constants.MENU_FILES_VIEW_MY_LIBRARY_FILES, 	R.drawable.button_library_normal, "View My Library Of Files" ) );
        	items.add(new PopupMenuItem(iMenuId, Constants.MENU_FILES_VIEW_SHARED_FILES, 		R.drawable.button_share_files_normal, "View My Shared Files" ) );
        	items.add(new PopupMenuItem(iMenuId, Constants.MENU_FILES_VIEW_DOWNLOADS, 			R.drawable.ic_files_download, "View Downloading Files" ) );
        	items.add(new PopupMenuItem(iMenuId, Constants.MENU_FILES_VIEW_UPLOADS, 			R.drawable.ic_files_upload, "View Uploading Files" ) );
            items.add(new PopupMenuItem(iMenuId, Constants.MENU_FILES_BROWSE_FILES, 			R.drawable.button_file_browse_normal, "Browse Device Files" ) );
                   }
        else if( iMenuId == Constants.MENU_SEARCH )
        {
        	this.setPageTitle( R.string.menu_search );
            items.add(new PopupMenuItem(iMenuId, Constants.MENU_SEARCH_BY_PHONE_SHAKE, 		R.drawable.button_people_normal, "Add Friend By Shaking Phone" ));
            items.add(new PopupMenuItem(iMenuId, Constants.MENU_SEARCH_BY_NAME, 			R.drawable.ic_guest, "Search For Person By Name" ));
            items.add(new PopupMenuItem(iMenuId, Constants.MENU_SEARCH_BY_MOOD_MSG, 		R.drawable.ic_guest, "Search For Person By Mood Message" ));
            items.add(new PopupMenuItem(iMenuId, Constants.MENU_SEARCH_SCAN_PROFILES, 		R.drawable.button_profile_page_normal, "Scan About Me Pictures" ));
            items.add(new PopupMenuItem(iMenuId, Constants.MENU_SEARCH_SCAN_WEBCAMS, 		R.drawable.button_webcam_server_normal, "Scan Shared Web Cams" ));
            //items.add(new PopupMenuItem(iMenuId, Constants.MENU_SEARCH_SHARED_FILES, 		R.drawable.ic_files, "Shared Files" ));
        }	
        else if( iMenuId == Constants.MENU_SERVERS )
        {
        	setPageTitle( R.string.menu_servers );
        	switch( NativeTxTo.fromGuiGetPluginServerState( Constants.ePluginTypeCamServer ) )
        	{
        	case Constants.ePluginServerStateDisabled:	
        		items.add(new PopupMenuItem(iMenuId, Constants.MENU_SERVERS_STARTSTOP_WEBCAM, R.drawable.button_webcam_server_disabled, "Web Cam Server Disabled" ) );
        		break;
        	case Constants.ePluginServerStateStarted:	
        		items.add(new PopupMenuItem(iMenuId, Constants.MENU_SERVERS_STARTSTOP_WEBCAM, R.drawable.button_webcam_server_normal, "Stop Web Cam Server" ) );
        		break;
        	case Constants.ePluginServerStateStopped:	
        		items.add(new PopupMenuItem(iMenuId, Constants.MENU_SERVERS_STARTSTOP_WEBCAM, R.drawable.button_webcam_server_normal, "Start Web Cam Server" ) );
        		break;
        	}
        	
            items.add(new PopupMenuItem(iMenuId, Constants.MENU_SERVERS_EDIT_MY_PROFILE, 		R.drawable.button_profile_page_normal, "Edit About Me Web Page" ));
            items.add(new PopupMenuItem(iMenuId, Constants.MENU_SERVERS_VIEW_MY_PROFILE, 		R.drawable.button_profile_page_normal, "View About Me Web Page" ));
            items.add(new PopupMenuItem(iMenuId, Constants.MENU_SERVERS_EDIT_MY_STORYBOARD, 	R.drawable.button_storyboard_normal, "Edit My Storyboard" ));
            items.add(new PopupMenuItem(iMenuId, Constants.MENU_SERVERS_VIEW_MY_STORYBOARD, 	R.drawable.button_storyboard_normal, "View My Storyboard" ));
      	
        		//items.add(new PopupMenuItem(iMenuId, Constants.MENU_SERVERS_SETUP_FILE_SHARE, R.drawable.ic_files_share_options, "File Share Options" ) );
        }	
        else if( iMenuId == Constants.MENU_OPTIONS )
        {
        	setPageTitle( R.string.menu_options );
            items.add(new PopupMenuItem(iMenuId, Constants.MENU_OPTIONS_EDIT_PERMISSIONS, 	R.drawable.button_permission_normal, "Edit Plugin Permissions" ));
            items.add(new PopupMenuItem(iMenuId, Constants.MENU_OPTIONS_EDIT_ACCOUNT, 		R.drawable.icon, "Change My Mood Message" ));
            //items.add(new PopupMenuItem(iMenuId, Constants.MENU_OPTIONS_SETUP_FILE_SHARE, R.drawable.ic_files_normal, "Setup file share" ));
            items.add(new PopupMenuItem(iMenuId, Constants.MENU_OPTIONS_NETWORK_SETTINGS, 	R.drawable.button_proxy_normal, "Network Settings" ));
            //items.add(new PopupMenuItem(iMenuId, Constants.MENU_OPTIONS_SOUND_SETTINGS, R.drawable.button_speaker_on_normal, "Sound Settings" ));
            //items.add(new PopupMenuItem(iMenuId, Constants.MENU_OPTIONS_CAMERA_TEST, 		R.drawable.ic_debug, "Camera Test" ));
            //items.add(new PopupMenuItem(iMenuId, Constants.MENU_OPTIONS_DEBUG_SETTINGS, 	R.drawable.ic_debug, "Debug" ));
            items.add(new PopupMenuItem(iMenuId, Constants.MENU_OPTIONS_ABOUT, 				R.drawable.icon, "About My P2P Web" ));
      }	
        else if( iMenuId == Constants.MENU_NOTIFY )
        {
        	setPageTitle( R.string.menu_notify );
            items.add(new PopupMenuItem(iMenuId, Constants.MENU_NOTIFY, R.drawable.ic_guest, "Edit About Me Web Page" ));
        }	
        else if( Constants.MENU_FRIEND == iMenuId )
        {
        	setPageTitle( R.string.menu_friend );
        	VxNetIdent oSelectedFriend = m_MyApp.getCurrentFriend();
        	oSelectedFriend.debugDumpIdent();
        	
        	// populate title
        	String strTitle =oSelectedFriend.describeMyFriendshipToHim();
        	strTitle += ": ";
        	strTitle +=oSelectedFriend.getOnlineName();
        	this.setTitle(strTitle );
        	// populate menu
           	items.add(new PopupMenuItem( iMenuId, Constants.MENU_FRIEND_CHANGE_FRIENDSHIP, MyIcons.getIcon(Constants.eMyIconPermissions), "Change Friendship"));

        	int ePluginAccess = oSelectedFriend.getPluginAccessState( Constants.ePluginTypeWebServer );
        	String strAction = oSelectedFriend.describePluginAction( Constants.ePluginTypeWebServer, ePluginAccess );
        	items.add(new PopupMenuItem( iMenuId, Constants.MENU_FRIEND_VIEW_PROFILE, MyIcons.getPluginIcon( Constants.ePluginTypeWebServer, ePluginAccess), strAction ));

        	ePluginAccess = oSelectedFriend.getPluginAccessState( Constants.ePluginTypeStoryBoard );
        	strAction = oSelectedFriend.describePluginAction( Constants.ePluginTypeStoryBoard, ePluginAccess );
        	items.add(new PopupMenuItem( iMenuId, Constants.MENU_FRIEND_VIEW_STORYBOARD, MyIcons.getPluginIcon( Constants.ePluginTypeStoryBoard, ePluginAccess ), strAction ) );
        	
        	ePluginAccess =oSelectedFriend.getPluginAccessState( Constants.ePluginTypeMultiSession );
        	strAction = oSelectedFriend.describePluginAction( Constants.ePluginTypeMultiSession, ePluginAccess );
        	items.add(new PopupMenuItem( iMenuId, Constants.MENU_FRIEND_OFFER_MULTISESSION, MyIcons.getPluginIcon(Constants.ePluginTypeMultiSession, ePluginAccess), strAction ));

        	ePluginAccess = oSelectedFriend.getPluginAccessState( Constants.ePluginTypeVideoPhone );
        	strAction = oSelectedFriend.describePluginAction( Constants.ePluginTypeVideoPhone, ePluginAccess );
        	items.add(new PopupMenuItem( iMenuId, Constants.MENU_FRIEND_OFFER_VIDPHONE, MyIcons.getPluginIcon( Constants.ePluginTypeVideoPhone, ePluginAccess), strAction ));

        	ePluginAccess =oSelectedFriend.getPluginAccessState( Constants.ePluginTypeVoicePhone );
        	strAction = oSelectedFriend.describePluginAction( Constants.ePluginTypeVoicePhone, ePluginAccess );
        	items.add(new PopupMenuItem( iMenuId, Constants.MENU_FRIEND_OFFER_VOIP, MyIcons.getPluginIcon( Constants.ePluginTypeVoicePhone, ePluginAccess), strAction ));

        	ePluginAccess =oSelectedFriend.getPluginAccessState( Constants.ePluginTypeTruthOrDare );
        	strAction = oSelectedFriend.describePluginAction( Constants.ePluginTypeTruthOrDare, ePluginAccess );
        	items.add(new PopupMenuItem( iMenuId, Constants.MENU_FRIEND_OFFER_TRUTHORDARE, MyIcons.getPluginIcon( Constants.ePluginTypeTruthOrDare, ePluginAccess), strAction ));

        	ePluginAccess = oSelectedFriend.getPluginAccessState( Constants.ePluginTypeCamServer );
        	strAction = oSelectedFriend.describePluginAction( Constants.ePluginTypeCamServer, ePluginAccess );
        	items.add(new PopupMenuItem( iMenuId, Constants.MENU_FRIEND_VIEW_SHARED_WEBCAM, MyIcons.getPluginIcon(Constants.ePluginTypeCamServer, ePluginAccess), strAction ));

        	ePluginAccess = oSelectedFriend.getPluginAccessState( Constants.ePluginTypeFileOffer );
            strAction = oSelectedFriend.describePluginAction( Constants.ePluginTypeFileOffer, ePluginAccess );
            items.add(new PopupMenuItem( iMenuId, Constants.MENU_FRIEND_SEND_FILE, MyIcons.getPluginIcon( Constants.ePluginTypeFileOffer, ePluginAccess), strAction ));

            ePluginAccess = oSelectedFriend.getPluginAccessState( Constants.ePluginTypeFileServer );
            strAction = oSelectedFriend.describePluginAction( Constants.ePluginTypeFileServer, ePluginAccess );
            items.add(new PopupMenuItem( iMenuId, Constants.MENU_FRIEND_VIEW_SHARED_FILES, MyIcons.getPluginIcon( Constants.ePluginTypeFileServer, ePluginAccess), strAction ));

        	ePluginAccess = oSelectedFriend.getPluginAccessState( Constants.ePluginTypeRelay );
        	strAction = oSelectedFriend.describePluginAction( Constants.ePluginTypeRelay, ePluginAccess );
        	items.add(new PopupMenuItem( iMenuId, Constants.MENU_FRIEND_PROXY, MyIcons.getPluginIcon( Constants.ePluginTypeRelay, ePluginAccess), strAction ));      	

        	//strAction = getResources().getString(R.string.edit_contact_info);
        	//items.add(new PopupMenuItem( iMenuId, Constants.MENU_FRIEND_EDIT_CONTACT_INFO, MyIcons.getIcon( Constants.eMyIconContactInfo ), strAction ));
      	
        	//strAction = getResources().getString(R.string.call_contacts_phone_number);
        	//items.add(new PopupMenuItem( iMenuId, Constants.MENU_FRIEND_CALL_USING_PHONE_NUM, MyIcons.getIcon( Constants.eMyIconVoicePhoneNormal ), strAction ));
        	
        	//strAction = getResources().getString(R.string.send_text_msg_using_sms);
        	//items.add(new PopupMenuItem( iMenuId, Constants.MENU_FRIEND_SEND_TEXT_USING_SMS, MyIcons.getIcon( Constants.eMyIconMultiSessionNormal ), strAction ));  	
        }	
        else if( Constants.MENU_PLUGIN_PERMISSIONS == iMenuId )
        {
        	setPageTitle( R.string.menu_plugin_permissions );
        	items.add(new PopupMenuItem( iMenuId, Constants.MENU_PLUGIN_PROFILE_PERMISSION, 
        			MyIcons.getPluginIcon( Constants.ePluginTypeWebServer,Constants.ePluginAccessOk), 
        			GuiHelpers.getWhoPermissionText( Constants.ePluginTypeWebServer) ) );
        	
        	items.add(new PopupMenuItem( iMenuId, Constants.MENU_PLUGIN_CHAT_PERMISSION, 
        			MyIcons.getPluginIcon( Constants.ePluginTypeMultiSession,Constants.ePluginAccessOk), 
        			GuiHelpers.getWhoPermissionText( Constants.ePluginTypeMultiSession) ) );
        	
        	items.add(new PopupMenuItem( iMenuId, Constants.MENU_PLUGIN_VOICE_PERMISSION, 
        			MyIcons.getPluginIcon( Constants.ePluginTypeVoicePhone,Constants.ePluginAccessOk), 
        			GuiHelpers.getWhoPermissionText( Constants.ePluginTypeVoicePhone) ) );
        	
        	items.add(new PopupMenuItem( iMenuId, Constants.MENU_PLUGIN_VIDPHONE_PERMISSION, 
        			MyIcons.getPluginIcon( Constants.ePluginTypeVideoPhone,Constants.ePluginAccessOk), 
        			GuiHelpers.getWhoPermissionText( Constants.ePluginTypeVideoPhone) ) );
        	
        	items.add(new PopupMenuItem( iMenuId, Constants.MENU_PLUGIN_TRUTH_OR_DARE_PERMISSION, 
        			MyIcons.getPluginIcon( Constants.ePluginTypeTruthOrDare,Constants.ePluginAccessOk), 
        			GuiHelpers.getWhoPermissionText( Constants.ePluginTypeTruthOrDare) ) );
        	
        	items.add(new PopupMenuItem( iMenuId, Constants.MENU_PLUGIN_WEBCAM_PERMISSION, 
        			MyIcons.getPluginIcon( Constants.ePluginTypeCamServer,Constants.ePluginAccessOk),
        			GuiHelpers.getWhoPermissionText( Constants.ePluginTypeCamServer) ) );
        	
        	items.add(new PopupMenuItem( iMenuId, Constants.MENU_PLUGIN_PROXY_PERMISSION, 
        			MyIcons.getPluginIcon( Constants.ePluginTypeRelay,Constants.ePluginAccessOk),
        			GuiHelpers.getWhoPermissionText( Constants.ePluginTypeRelay) ) );
     
            items.add(new PopupMenuItem( iMenuId, Constants.MENU_PLUGIN_FILE_SHARE_PERMISSION, 
            			MyIcons.getPluginIcon( Constants.ePluginTypeFileServer,Constants.ePluginAccessOk), 
            			GuiHelpers.getWhoPermissionText( Constants.ePluginTypeFileServer) ) );

            items.add(new PopupMenuItem( iMenuId, Constants.MENU_PLUGIN_FILE_XFER_PERMISSION, 
			        	MyIcons.getPluginIcon( Constants.ePluginTypeFileOffer,Constants.ePluginAccessOk), 
			        	GuiHelpers.getWhoPermissionText( Constants.ePluginTypeFileOffer) ) );
        			
            items.add(new PopupMenuItem( iMenuId, Constants.MENU_PLUGIN_STORYBOARD_PERMISSION, 
            			MyIcons.getPluginIcon( Constants.ePluginTypeStoryBoard,Constants.ePluginAccessOk), 
            			GuiHelpers.getWhoPermissionText( Constants.ePluginTypeStoryBoard) ) );    	
        }
        else
        {
        	//setPageTitle("MENU ERROR");
            items.add(new PopupMenuItem(iMenuId, Constants.MENU_NOTIFY, R.drawable.ic_unknown, "Unknown" ));
        }	
        
        return items;
    }

  	//============================================================================
    @Override
    public void onListItemClick(ListView parent, View v, int position, long id)
    {
    	m_MyApp.playButtonClick();
    	//mSelection.setText("Selection length is: " + mMonitorObjects.get(position).toString().length());
    	PopupMenuItem oMenuItem = m_aoMenuItems.get(position);
    	m_MyApp.onMenuSelected( oMenuItem );
    	finish();
    }

  	//============================================================================
    private class CustomAdapter extends ArrayAdapter<PopupMenuItem> 
    {
    	CustomAdapter()  
    	{
    		super(PopupMenu.this, R.layout.popup_row, R.id.popup_text, m_aoMenuItems);
    	    Log.i(LOG_TAG, "CustomAdapter constructed");
    	}

    	@Override
    	public View getView(int position, View convertView, ViewGroup parent) 
    	{     
       	    //Log.i(LOG_TAG, "CustomAdapter getView position " + position );
       	    View row = convertView;
    		if (row == null) 
    		{ 
           	    //Log.i(LOG_TAG, "CustomAdapter Layout inflater");
    			// This gives us a View object back which, in reality, is our LinearLayout with 
    			// an ImageView and a TextView, just as R.layout.row specifies.
    			LayoutInflater inflater = getLayoutInflater();      
    			row = inflater.inflate(R.layout.popup_row, parent, false);
    		}
       	   // Log.i(LOG_TAG, "getting item at position " + position );
    		PopupMenuItem oMenuItem = m_aoMenuItems.get(position);
       	    //Log.i(LOG_TAG, "menu item " + oMenuItem.toString() );
    		
    		TextView label = (TextView) row.findViewById(R.id.popup_text);
       	    //Log.i(LOG_TAG, "TextView " + label.toString() );
       	    //Log.i(LOG_TAG, "TextView text " + oMenuItem.m_strMenuText );
    		label.setText(oMenuItem.m_strMenuText);
    		
    		ImageView view_icon = (ImageView)row.findViewById(R.id.popup_icon);
       	    //Log.i(LOG_TAG, "icon " + view_icon.toString() );
    		view_icon.setImageResource(oMenuItem.m_iMenuIconId);

    		return row;       
    	}
    }
}


