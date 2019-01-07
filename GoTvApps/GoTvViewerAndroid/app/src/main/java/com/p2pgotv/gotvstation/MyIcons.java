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

class MyIcons
{
	static public int m_aoIcons[] = 
		{ 
		R.drawable.ic_unknown, 								// eMyIconUnknown			= 0; // Icon with question mark
		R.drawable.icon, 									// eMyIconApp				= 1;
		R.drawable.button_people_normal, 					// eMyIconPeople			= 2;
		R.drawable.ic_search_normal, 						// eMyIconSearch			= 3;
		R.drawable.ic_servers_normal, 						// eMyIconServers			= 4;
		R.drawable.button_setup_normal, 					// eMyIconOptions			= 5;
		R.drawable.ic_folder_disabled, 						// eMyIconFileServer		= 6;

		R.drawable.button_administrator_normal, 			// eMyIconAdministrator		= 7;
		R.drawable.button_people_normal, 						// eMyIconFriend			= 8;
		R.drawable.ic_guest, 								// eMyIconGuest				= 9;
		R.drawable.ic_unknown, 								// eMyIconAnonymous			= 10;
		R.drawable.ic_ignore, 								// eMyIconIgnored			= 11;

		R.drawable.button_webcam_client_normal, 			// eMyIconWebCamClient		= 12;

		R.drawable.button_proxy_normal, 					// eMyIconRelay				= 13;
		R.drawable.button_proxy_disabled, 					// eMyIconRelayLocked		= 14;
		R.drawable.button_proxy_disabled, 					// eMyIconRelayDisabled		= 15;
		R.drawable.button_proxy_disabled, 					// eMyIconRelayIgnored		= 16;
		
		R.drawable.button_profile_page_normal, 				// eMyIconProfile			= 17;
		R.drawable.button_profile_page_disabled, 			// eMyIconProfileLocked		= 18;
		R.drawable.button_profile_page_disabled, 			// eMyIconProfileDisabled	= 19;
		R.drawable.button_profile_page_disabled, 			// eMyIconProfileIgnored	= 20;

		R.drawable.button_webcam_server_normal, 			// eMyIconWebCamServer						= 21;
		R.drawable.button_webcam_server_disabled, 			// eMyIconWebCamServerLocked				= 22;
		R.drawable.button_webcam_server_disabled, 			// eMyIconWebCamServerDisabled 				= 23;
		R.drawable.button_webcam_server_disabled, 			// eMyIconWebCamServerIgnored				= 24;

		R.drawable.ic_folder, 								// eMyIconFolder							= 25;		
		R.drawable.ic_folder_disabled, 						// eMyIconFolderDisabled					= 26;
		
		R.drawable.button_share_files_normal, 				// eMyIconFilesShareNormal					= 27;
		R.drawable.button_share_files_disabled, 			// eMyIconFilesShareLocked					= 28;
		R.drawable.button_share_files_disabled, 			// eMyIconFilesShareDisabled				= 29;
		R.drawable.button_share_files_disabled, 			// eMyIconFilesShareIgnored					= 30;
		R.drawable.button_share_files_cancel, 				// eMyIconFilesShareCancel					= 31;
		R.drawable.button_share_files_red, 					// eMyIconFilesShareRed						= 32;
		R.drawable.button_share_files_yellow, 				// eMyIconFilesShareYellow					= 33;
		
		R.drawable.button_chat_normal, 						// eMyIconMultiSessionNormal				= 34;
		R.drawable.button_chat_disabled, 					// eMyIconMultiSessionLocked				= 35;
		R.drawable.button_chat_disabled, 					// eMyIconMultiSessionDisabled				= 36;
		R.drawable.button_chat_disabled, 					// eMyIconMultiSessionIgnored				= 37;
		R.drawable.button_chat_cancel, 						// eMyIconMultiSessionCancel				= 38;
		
		R.drawable.button_phone_normal, 					// eMyIconVoicePhoneNormal					= 39;
		R.drawable.button_phone_disabled, 					// eMyIconVoicePhoneLocked					= 40;
		R.drawable.button_phone_disabled, 					// eMyIconVoicePhoneDisabled				= 41;
		R.drawable.button_phone_disabled, 					// eMyIconVoicePhoneIgnored					= 42;
		R.drawable.button_phone_cancel, 					// eMyIconVoicePhoneCancel					= 43;
		R.drawable.button_phone_red, 						// eMyIconVoicePhoneRed						= 44;
		R.drawable.button_phone_yellow, 					// eMyIconVoicePhoneYellow					= 45;
		
		R.drawable.button_vidphone_normal, 					// eMyIconVideoPhoneNormal					= 46;
		R.drawable.button_vidphone_disabled, 				// eMyIconVideoPhoneLocked					= 47;
		R.drawable.button_vidphone_disabled, 				// eMyIconVideoPhoneDisabled				= 48;
		R.drawable.button_vidphone_disabled, 				// eMyIconVideoPhoneIgnored					= 49;
		R.drawable.button_vidphone_cancel, 					// eMyIconVideoPhoneCancel					= 50;
		R.drawable.button_vidphone_red, 					// eMyIconVideoPhoneRed						= 51;
		R.drawable.button_vidphone_yellow, 					// eMyIconVideoPhoneYellow					= 52;
		
		R.drawable.button_truth_or_dare_normal, 			// eMyIconTruthOrDareNormal					= 53;
		R.drawable.button_truth_or_dare_disabled, 			// eMyIconTruthOrDareLocked					= 54;
		R.drawable.button_truth_or_dare_disabled, 			// eMyIconTruthOrDareDisabled				= 55;
		R.drawable.button_truth_or_dare_disabled, 			// eMyIconTruthOrDareIgnored				= 56;
		R.drawable.button_truth_or_dare_cancel, 			// eMyIconTruthOrDareCancel					= 57;
		R.drawable.button_truth_or_dare_red, 				// eMyIconTruthOrDareRed					= 58;
		R.drawable.button_truth_or_dare_yellow, 			// eMyIconTruthOrDareYellow					= 59;

		R.drawable.button_permission_normal, 				// eMyIconPermissions						= 60;

		R.drawable.ic_unknown, 								// eMyIconNotifyStarWhite					= 61;
		R.drawable.ic_unknown, 								// eMyIconNotifyStarGreen					= 62;

		R.drawable.button_refresh_normal, 					// eMyIconRefresh							= 63;
		
		R.drawable.ic_profile,								// eMyIconContactInfo						= 64;
		
		R.drawable.button_file_browse_normal,				// eMyIconFileBrowseNormal					= 65;
		R.drawable.button_file_browse_disabled,				// eMyIconFileBrowseDisabled				= 66;
		R.drawable.button_file_browse_cancel,				// eMyIconFileBrowseCancel					= 67;

		R.drawable.button_move_up_dir_normal,				// eMyIconMoveUpDirNormal					= 68;
		R.drawable.button_move_up_dir_disabled,				// eMyIconMoveUpDirDisabled				    = 69;
		R.drawable.button_move_up_dir_cancel,				// eMyIconMoveUpDirCancel					= 70;
		
		R.drawable.button_file_send_disabled,				// eMyIconSendFileDisabled					= 71;
		R.drawable.button_file_send_cancel,					// eMyIconSendFileCancel					= 72;
		R.drawable.button_file_send_normal,					// eMyIconSendFileNormal					= 73;
		R.drawable.button_file_send_red,					// eMyIconSendFileRed						= 74;
		R.drawable.button_file_send_yellow,					// eMyIconSendFileYellow					= 75;
		
		R.drawable.button_storyboard_normal,				// eMyIconStoryBoardNormal					= 76;
		R.drawable.button_storyboard_disabled,				// eMyIconStoryBoardLocked					= 77;
		R.drawable.button_storyboard_disabled,				// eMyIconStoryBoardDisabled				= 78;
		R.drawable.button_storyboard_disabled,				// eMyIconStoryBoardIgnored					= 79;
		
		R.drawable.button_person_unknown_normal,			// eMyIconPersonUnknownNormal				= 80;
		R.drawable.button_administrator_disabled, 			// eMyIconAdministratorDisabled				= 81;
};
	
	//========================================================================
	//! get preloaded icon
	static public int getIcon( int eMyIcon )
	{
		return m_aoIcons[ eMyIcon ];
	}

	//========================================================================
	//! get icon for give friendship
	static public int getFriendshipIcon( int eFriendship )
	{
		switch( eFriendship )
		{
		case Constants.eFriendStateIgnore:	// unknown or disabled or ignore
			return getIcon( Constants.eMyIconIgnored );
		case Constants.eFriendStateAnonymous:	// anonymous user
			return getIcon( Constants.eMyIconPersonUnknownNormal );
		case Constants.eFriendStateGuest:	// guest user
			return getIcon( Constants.eMyIconGuest );
		case Constants.eFriendStateFriend:		// friend user
			return getIcon( Constants.eMyIconFriend );
		default:
			return getIcon( Constants.eMyIconUnknown );
		}
	}
	//========================================================================
	//! get icon for given plugin
	static public int getPluginIcon( int ePluginType, int ePluginAccess )
	{
		switch( ePluginType )
		{
		case Constants.ePluginTypeRelay:	// proxy plugin
			switch( ePluginAccess )
			{
			case Constants.ePluginAccessOk:
				return getIcon( Constants.eMyIconRelay );
			case Constants.ePluginAccessDisabled:
			case Constants.ePluginAccessInactive:
			case Constants.ePluginAccessRequiresDirectConnect:
			case Constants.ePluginAccessRequiresOnline:				
				return getIcon( Constants.eMyIconRelayDisabled );
			case Constants.ePluginAccessLocked:
				return getIcon( Constants.eMyIconRelayLocked );
			case Constants.ePluginAccessIgnored:
				return getIcon( Constants.eMyIconRelayIgnored );
			}
			
			break;
			
		case Constants.ePluginTypeWebServer:	// web server plugin ( for profile web page )
			switch( ePluginAccess )
			{
			case Constants.ePluginAccessOk:
				return getIcon( Constants.eMyIconProfile );
			case Constants.ePluginAccessDisabled:
			case Constants.ePluginAccessInactive:
			case Constants.ePluginAccessRequiresDirectConnect:
			case Constants.ePluginAccessRequiresOnline:				
				return getIcon( Constants.eMyIconProfileDisabled );
			case Constants.ePluginAccessLocked:
				return getIcon( Constants.eMyIconProfileLocked );
			case Constants.ePluginAccessIgnored:
				return getIcon( Constants.eMyIconProfileIgnored );
			}
			
			break;
			
		case Constants.ePluginTypeStoryBoard:	// web server plugin ( for story board web page )
			switch( ePluginAccess )
			{
			case Constants.ePluginAccessOk:
				return getIcon( Constants.eMyIconStoryBoardNormal );
			case Constants.ePluginAccessDisabled:
			case Constants.ePluginAccessInactive:
			case Constants.ePluginAccessRequiresDirectConnect:
			case Constants.ePluginAccessRequiresOnline:				
				return getIcon( Constants.eMyIconStoryBoardDisabled );
			case Constants.ePluginAccessLocked:
				return getIcon( Constants.eMyIconStoryBoardLocked );
			case Constants.ePluginAccessIgnored:
				return getIcon( Constants.eMyIconStoryBoardIgnored );
			}
			
			break;
			
		case  Constants.ePluginTypeFileOffer:	// file offer plugin
			switch(ePluginAccess )
			{
			case Constants.ePluginAccessOk:
				return getIcon( Constants.eMyIconSendFileNormal );
			case Constants.ePluginAccessDisabled:
			case Constants.ePluginAccessInactive:
			case Constants.ePluginAccessRequiresDirectConnect:
			case Constants.ePluginAccessRequiresOnline:				
				return getIcon( Constants.eMyIconSendFileDisabled );
			case Constants.ePluginAccessLocked:
				return getIcon( Constants.eMyIconSendFileDisabled );
			case Constants.ePluginAccessIgnored:
				return getIcon( Constants.eMyIconSendFileDisabled );
			}
			
			break;
			
		case  Constants.ePluginTypeFileServer:	// file share plugin
			switch( ePluginAccess )
			{
			case Constants.ePluginAccessOk:
				return getIcon( Constants.eMyIconFilesShareNormal );
			case Constants.ePluginAccessDisabled:
			case Constants.ePluginAccessInactive:
			case Constants.ePluginAccessRequiresDirectConnect:
			case Constants.ePluginAccessRequiresOnline:				
				return getIcon( Constants.eMyIconFilesShareDisabled );
			case Constants.ePluginAccessLocked:
				return getIcon( Constants.eMyIconFilesShareDisabled );
			case Constants.ePluginAccessIgnored:
				return getIcon( Constants.eMyIconFilesShareDisabled );
			}
			
			break;
			
		case  Constants.ePluginTypeCamServer:	// web cam broadcast plugin
			switch( ePluginAccess )
			{
			case Constants.ePluginAccessOk:
				return getIcon( Constants.eMyIconWebCamServer );
			case Constants.ePluginAccessDisabled:
			case Constants.ePluginAccessInactive:
			case Constants.ePluginAccessRequiresDirectConnect:
			case Constants.ePluginAccessRequiresOnline:				
				return getIcon( Constants.eMyIconWebCamServerDisabled );
			case Constants.ePluginAccessLocked:
				return getIcon( Constants.eMyIconWebCamServerLocked );
			case Constants.ePluginAccessIgnored:
				return getIcon( Constants.eMyIconWebCamServerIgnored );
			}
			
			break;
			
		case  Constants.ePluginTypeMultiSession:	// instant message p2p plugin
			switch( ePluginAccess )
			{
			case Constants.ePluginAccessOk:
				return getIcon( Constants.eMyIconMultiSessionNormal );
			case Constants.ePluginAccessDisabled:
			case Constants.ePluginAccessInactive:
			case Constants.ePluginAccessRequiresDirectConnect:
			case Constants.ePluginAccessRequiresOnline:				
				return getIcon( Constants.eMyIconMultiSessionDisabled );
			case Constants.ePluginAccessLocked:
				return getIcon( Constants.eMyIconMultiSessionDisabled );
			case Constants.ePluginAccessIgnored:
				return getIcon( Constants.eMyIconMultiSessionDisabled );
			}
			
			break;
			
		case  Constants.ePluginTypeVoicePhone:	// VOIP p2p plugin
			switch( ePluginAccess )
			{
			case Constants.ePluginAccessOk:
				return getIcon( Constants.eMyIconVoicePhoneNormal );
			case Constants.ePluginAccessDisabled:
			case Constants.ePluginAccessInactive:
			case Constants.ePluginAccessRequiresDirectConnect:
			case Constants.ePluginAccessRequiresOnline:				
				return getIcon( Constants.eMyIconVoicePhoneDisabled );
			case Constants.ePluginAccessLocked:
				return getIcon( Constants.eMyIconVoicePhoneLocked );
			case Constants.ePluginAccessIgnored:
				return getIcon( Constants.eMyIconVoicePhoneIgnored );
			}
			
			break;
			
		case  Constants.ePluginTypeVideoPhone:	// Video phone p2p plugin
			switch( ePluginAccess )
			{
			case Constants.ePluginAccessOk:
				return getIcon( Constants.eMyIconVideoPhoneNormal );
			case Constants.ePluginAccessDisabled:
			case Constants.ePluginAccessInactive:
			case Constants.ePluginAccessRequiresDirectConnect:
			case Constants.ePluginAccessRequiresOnline:				
				return getIcon( Constants.eMyIconVideoPhoneDisabled );
			case Constants.ePluginAccessLocked:
				return getIcon( Constants.eMyIconVideoPhoneLocked );
			case Constants.ePluginAccessIgnored:
				return getIcon( Constants.eMyIconVideoPhoneIgnored );
			}
			
			break;
			
		case  Constants.ePluginTypeTruthOrDare:	// Web Cam Truth Or Dare game p2p plugin
			switch( ePluginAccess )
			{
			case Constants.ePluginAccessOk:
				return getIcon( Constants.eMyIconTruthOrDareNormal );
			case Constants.ePluginAccessDisabled:
			case Constants.ePluginAccessInactive:
			case Constants.ePluginAccessRequiresDirectConnect:
			case Constants.ePluginAccessRequiresOnline:				
				return getIcon( Constants.eMyIconTruthOrDareDisabled );
			case Constants.ePluginAccessLocked:
				return getIcon( Constants.eMyIconTruthOrDareLocked );
			case Constants.ePluginAccessIgnored:
				return getIcon( Constants.eMyIconTruthOrDareIgnored );
			}
		}
		
		return getIcon( Constants.eMyIconUnknown );
	}
	
	//========================================================================
	//! get disabled plugin icon
	int getDisabledPluginIcon( int ePluginType )
	{
		switch( ePluginType )
		{
		case Constants.ePluginTypeWebServer:		// web server plugin ( for profile web page )
			return getIcon( Constants.eMyIconProfileDisabled );
		case  Constants.ePluginTypeFileOffer:		// file offer plugin
			return getIcon( Constants.eMyIconFolderDisabled );
		case  Constants.ePluginTypeFileServer:		// file share plugin
			return getIcon( Constants.eMyIconFilesShareDisabled );
		case  Constants.ePluginTypeCamServer:		// web cam broadcast plugin
			return getIcon( Constants.eMyIconWebCamServerDisabled );
		case  Constants.ePluginTypeMultiSession:	// instant message p2p plugin
			return getIcon( Constants.eMyIconMultiSessionDisabled );
		case  Constants.ePluginTypeVoicePhone:		// VOIP p2p plugin
			return getIcon( Constants.eMyIconVoicePhoneDisabled );
		case  Constants.ePluginTypeVideoPhone:		// Video phone p2p plugin
			return getIcon( Constants.eMyIconVideoPhoneDisabled );
		case  Constants.ePluginTypeTruthOrDare:			// Web Cam Truth Or Dare game p2p plugin
			return getIcon( Constants.eMyIconTruthOrDareDisabled );
		default:		
			return getIcon( Constants.eMyIconUnknown );
		}
	}
	
	//========================================================================
	//! get icon for given plugin.. return icon for friendship level
	int getLockedPluginIcon( int ePluginType )
	{
		switch( ePluginType )
		{
		case Constants.ePluginTypeWebServer:	// web server plugin ( for profile web page )
			return getIcon( Constants.eMyIconProfileLocked );
		case  Constants.ePluginTypeFileOffer:	// file offer plugin
			return getIcon( Constants.eMyIconFolderDisabled );
		case  Constants.ePluginTypeFileServer:	// file share plugin
			return getIcon( Constants.eMyIconFilesShareDisabled );
		case  Constants.ePluginTypeCamServer:	// web cam broadcast plugin
			return getIcon( Constants.eMyIconWebCamServerLocked );
		case  Constants.ePluginTypeMultiSession:	// instant message p2p plugin
			return getIcon( Constants.eMyIconMultiSessionLocked );
		case  Constants.ePluginTypeVoicePhone:	// VOIP p2p plugin
			return getIcon( Constants.eMyIconVoicePhoneLocked );
		case  Constants.ePluginTypeVideoPhone:	// Video phone p2p plugin
			return getIcon( Constants.eMyIconVideoPhoneLocked );
		case  Constants.ePluginTypeTruthOrDare:	// Web Cam Truth Or Dare game p2p plugin
			return getIcon( Constants.eMyIconTruthOrDareLocked );
		default:		
			return getIcon( Constants.eMyIconUnknown );
		}
	}
	
	//========================================================================
	//! get icon for given plugin.. return icon for friendship level
	int getIgnoredPluginIcon( int ePluginType )
	{
		switch( ePluginType )
		{
		case Constants.ePluginTypeWebServer:	// web server plugin ( for profile web page )
			return getIcon( Constants.eMyIconProfileIgnored );
		case  Constants.ePluginTypeFileOffer:	// file share plugin
			return getIcon( Constants.eMyIconFolderDisabled );
		case  Constants.ePluginTypeFileServer:	// file share plugin
			return getIcon( Constants.eMyIconFilesShareDisabled );
		case  Constants.ePluginTypeCamServer:	// web cam broadcast plugin
			return getIcon( Constants.eMyIconWebCamServerIgnored );
		case  Constants.ePluginTypeMultiSession:	// instant message p2p plugin
			return getIcon( Constants.eMyIconMultiSessionIgnored );
		case  Constants.ePluginTypeVoicePhone:	// VOIP p2p plugin
			return getIcon( Constants.eMyIconVoicePhoneIgnored );
		case  Constants.ePluginTypeVideoPhone:	// Video phone p2p plugin
			return getIcon( Constants.eMyIconVideoPhoneIgnored );
		case  Constants.ePluginTypeTruthOrDare:	// Web Cam Truth Or Dare game p2p plugin
			return getIcon( Constants.eMyIconTruthOrDareIgnored );
		default:		
			return getIcon( Constants.eMyIconUnknown );
		}
	}
}

