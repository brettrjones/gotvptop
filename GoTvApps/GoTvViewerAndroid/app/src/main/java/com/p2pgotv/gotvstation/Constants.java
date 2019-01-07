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

public class Constants
{	
	public static final int	eMediaSrcUnknown								= 0;
	public static final int	eMediaSrcCamera									= 1;
	public static final int	eMediaSrcLibrary								= 2;
	public static final int	eMediaSrcDeviceFiles							= 3;
	public static final int	eMediaSrcGallery								= 4;

	//=== must match IFromGui EVideoRecordState ===//
	public static final int	eVideoRecordStateDisabled						= 0;
	public static final int	eVideoRecordStateStopRecording					= 1;
	public static final int	eVideoRecordStateStartRecording					= 2;
	public static final int	eVideoRecordStateStartRecordingInPausedState	= 3;
	public static final int	eVideoRecordStatePauseRecording					= 4;
	public static final int	eVideoRecordStateResumeRecording				= 5;
	public static final int	eVideoRecordStateCancelRecording				= 6;
	public static final int	eVideoRecordStateError							= 7;
	public static final int	eMaxVideoRecordState							= 8;
	
	//=== must match IFromGui ESndRecordState ===//
	public static final int	eSndRecordStateDisabled							= 0;
	public static final int	eSndRecordStateStopRecording					= 1;
	public static final int	eSndRecordStateStartRecording					= 2;
	public static final int	eSndRecordStateStartRecordingInPausedState		= 3;
	public static final int	eSndRecordStatePauseRecording					= 4;
	public static final int	eSndRecordStateResumeRecording					= 5;
	public static final int	eSndRecordStateCancelRecording					= 6;
	public static final int	eSndRecordStateError							= 7;
	public static final int	eMaxSndRecordState								= 8;

	//=== must match IFromGui EMediaInputType ===//
	public static final int	eMediaInputNone									= 0;
	public static final int	eMediaInputAudioPkts							= 1;
	public static final int	eMediaInputAudioOpus							= 2;
	public static final int	eMediaInputAudioPcm								= 3;
	public static final int	eMediaInputVideoPkts							= 4;
	public static final int	eMediaInputVideoJpgSmall						= 5;
	public static final int	eMediaInputVideoJpgBig							= 6;
	public static final int	eMediaInputMixer								= 7;
	public static final int	eMaxMediaInputType								= 8;
	
	public static final int	eCamVideoModeAny								= 1;
	public static final int	eCamVideoModePhotoOnly							= 2;
	public static final int	eCamVideoModeVideoOnly							= 3;
	
	//=== must match IFromGui EMediaDevice ===//
	public static final int	eMediaDeviceNone								= 0;
	public static final int	eMediaDeviceMicrophone							= 1;
	public static final int	eMediaDeviceSpeaker								= 2;
	public static final int	eMaxMediaDevice									= 3;
	
	public static final int	eChatInputSelectMode							= 0;
	public static final int	eChatInputText									= 1;
	public static final int	eChatInputCamera								= 2;
	public static final int	eChatInputAudio									= 3;
	public static final int	eChatInputVideo									= 4;
	public static final int	eChatInputFace									= 5;
	public static final int	eChatInputGallery								= 6;
	
	public static final int	eMSessionModeText								= 0;
	public static final int	eMSessionModeAudioPhone							= 1;
	public static final int	eMSessionModeVideoChat							= 2;
	public static final int	eMSessionModeTruthOrDare						= 3;

	public static final int	eMResponseModeNone								= 0;
	public static final int	eMResponseModeAudio								= 1;
	public static final int	eMResponseModeVideoChat							= 2;
	public static final int	eMResponseModeTruthOrDare						= 3;
	
	//=== Xfer direction enum ===//
	public static final int	eXferToMe								= 0;
	public static final int	eXferToHim								= 1;
	
	//=== Xfer file state enum ===//
	public static final int	eXferFileStateUnknown					= 0;
		    
	public static final int	eXferFileStateDnloadNoSpace				= 101;
	public static final int	eXferFileStateDnloadWait				= 102;
	public static final int	eXferFileStateDnloadProgress			= 103;
	public static final int	eXferFileStateDnloadComplete			= 104;
	public static final int	eXferFileStateDnloadError				= 105;
      
	public static final int	eXferFileStateUploadNoSpace				= 201;
	public static final int	eXferFileStateUploadWait				= 202;
	public static final int	eXferFileStateUploadProgress			= 203;
	public static final int	eXferFileStateUploadComplete			= 204;
	public static final int	eXferFileStateUploadError				= 205;
    
	public static final int	eXferFileStateDeletedFromDevice			= 301;
		
	static final int MSG_TYPE_UPDATE_FILEINFO						= 1;
	static final int MSG_TYPE_REFRESH_FILELIST						= 2;
	static final int MSG_TYPE_CLEAR_FILELIST						= 3;
	static final int MSG_TYPE_NOTIFY_FILELIST_CHANGED				= 4;

	public static final String DEFAULT_ANNOUNCE_URL					= "http://www.myp2panchor.com:45124";
	public static final String DEFAULT_CONNECTION_TEST_URL			= "http://www.myp2pconnect.com:45124";
	public static final String DEFAULT_TESTAPP_ANNOUNCE_URL			= "http://www.p2pthing.com:45124";
	public static final String DEFAULT_TESTAPP_CONNECTION_TEST_URL	= "http://www.p2pthing.com:45124";
	public static final String DEFAULT_NETWORK_NAME					= "MyP2PWeb";
	public static final String DEFAULT_TESTAPP_NETWORK_NAME			= "TestNet";
	
	public static final String DEFAULT_NETWORK_ADAPTER_IP			= "default";
	
	public static final String PARAM_FILE_NAME						= "PARM_FILE_NAME";	
	public static final String PARAM_SOURCE_CAMERA					= "PARM_SOURCE_CAMERA";	
	public static final String PARAM_FILE_FILTER_TYPE				= "FILE_FILTER_TYPE";	
	public static final String PARAM_SELECT_FILE_MODE				= "SELECT_FILE_MODE";
	public static final String PARAM_FILE_TYPE_MASK					= "PARAM_FILE_TYPE_MASK";	
	public static final String PARAM_MEDIA_SRC						= "PARAM_MEDIA_SRC";	
	public static final String PARAM_HIDE_ACCEPT_REJECT				= "PARAM_HIDE_ACCEPT_REJECT";	
	
	static final int eFileFilterTypeAny								= 0;
	static final int eFileFilterTypePhoto							= 1;
	static final int eFileFilterTypeAudio							= 2;
	static final int eFileFilterTypeVideo							= 3; 
	static final int eFileFilterTypeDocument						= 4; 
	static final int eFileFilterTypeArchive							= 5; 
	static final int eFileFilterTypeOther							= 6; 
	
	public static final short DEFAULT_TCP_PORT 						= (short)45123;
	public static final short DEFAULT_UDP_PORT 						= (short)45124;
	
	static final int MSG_TYPE_UPDATE_FRIEND							= 1;
	static final int MSG_TYPE_UPDATE_CONTACT_SESSION_TIME			= 2;
	static final int MSG_TYPE_STATUS_MESSAGE						= 3;
	static final int MSG_TYPE_REFRESH_CONTACTS						= 4; 
	static final int MSG_TYPE_CLEAR_CONTACTS						= 5; 
	
	static final int MSG_TYPE_UPDATE_HISTORY_LIST					= 1;
	static final int MSG_TYPE_HISTORY_LIST_MESSAGE					= 2;
	static final int MSG_TYPE_REFRESH_HISTORY_LIST					= 3; 
	static final int MSG_TYPE_CLEAR_HISTORY_LIST					= 4; 

	static final int MY_EVENT_ONCE_PER_SEC							= 1; 
	static final int MY_EVENT_ONCE_PER_500MS						= 2; 

	static final int OFFLINE_TEXT_COLOR 							= 0xff969696;
	static final int ONLINE_TEXT_COLOR 								= 0xff007f00;
	static final int NEARBY_TEXT_COLOR 								= 0xff1515ff;
	
	static final int OFFLINE_BKG_COLOR 								= 0xA0909090;
	static final int ONLINE_BKG_COLOR 								= 0xA0907f90;
	static final int NEARBY_BKG_COLOR 								= 0xff1515ff;
	
	static final byte PERMISSION_IGNORE 							= 0x00;
	static final byte PERMISSION_ANONYMOUS 							= 0x01;
	static final byte PERMISSION_GUEST 								= 0x02;
	static final byte PERMISSION_FRIEND 							= 0x03;
	static final byte PERMISSION_ADMIN 								= 0x04; 
	
	static public final int eFriendStateIgnore						= 0;	// unknown or disabled or ignore
	static public final int eFriendStateAnonymous					= 1;	// anonymous user
	static public final int eFriendStateGuest						= 2;	// guest user
	static public final int eFriendStateFriend						= 3;	// friend user
	static public final int eFriendStateAdministrator				= 4;	// super user rights
	
	static public final int ePluginAccessOk							= 0;	// plugin access allowed
	static public final int ePluginAccessLocked						= 1;	// insufficient Friend permission level
	static public final int ePluginAccessDisabled					= 2;	// plugin disabled or no files shared or no web cam broadcast
	static public final int ePluginAccessIgnored					= 3;	// access denied because you are being ignored
	static public final int ePluginAccessInactive					= 4;	// enabled and have access but no shared files or web cam
	static public final int ePluginAccessBusy						= 5;	// sufficient permission but cannot accept any more sessions
	static public final int ePluginAccessRequiresDirectConnect		= 6;	// plugin requires direct connection
	static public final int ePluginAccessRequiresOnline				= 7;	// plugin requires user to be online

	static public final int eRelayStatusOk							= 0;	// relay enabled and access accepted 
	static public final int eRelayStatusPermissionErr				= 1;	// insufficient permission
	static public final int eRelayStatusBusy						= 2;	// relay cannot accept any more session
	
	static public final int ePluginTypeInvalid						= 0;	// unknown or disabled
	static public final int ePluginTypeAdmin						= 1;	// administration
	static public final int ePluginTypeRelay						= 2;	// Relay plugin
	static public final int ePluginTypeWebServer					= 3;	// web server plugin ( for profile web page )
	static public final int ePluginTypeCamServer					= 4;	// web cam broadcast plugin
	static public final int ePluginTypeMultiSession					= 5;	// chat plugin
	static public final int ePluginTypeVoicePhone					= 6;	// VOIP p2p plugin
	static public final int ePluginTypeVideoPhone					= 7;	// Video phone p2p plugin
	static public final int ePluginTypeTruthOrDare		    		= 8;	// Web Cam Truth Or Dare game p2p plugin
	static public final int ePluginTypeFileOffer					= 9;	// file xfer plugin
	static public final int ePluginTypeFileServer					= 10;	// file share plugin
	static public final int ePluginTypeStoryBoard					= 11;	// Story board
	
	static public final int eMaxPluginType 							= 12;   // must be last.. maximum plugin types
	static public final int eStoryBoardWritePermission  			= 15;	// only story board plugin read permission
			
	// fake plugin types without a actual plugin
	static public final int ePluginTypeSearch						= 17;	
	
	static public final int ePluginServerStateDisabled 				= 0;
	static public final int ePluginServerStateStarted				= 1;
	static public final int ePluginServerStateStopped				= 2;

	static public final int eFirewallTestUrlConnectionTest 			= 0;	// unknown or disabled or ignore	
	static public final int eFirewallTestAssumeFirewalled			= 1;	// anonymous user
	static public final int eFirewallTestAssumeNoFirewall			= 2;	// guest user
	
	static public final int eFriendViewEverybody					= 0;
	static public final int eFriendViewAdministrators				= 1;
	static public final int eFriendViewFriendsAndGuests				= 2;
	static public final int eFriendViewAnonymous					= 3;
	static public final int eFriendViewIgnored						= 4;
	static public final int eFriendViewMyProxies					= 5;
	static public final int eFriendViewAllProxies					= 6;
	static public final int eFriendViewRefresh						= 7;
	
	static public final int eScanTypeNone							= 0;
	static public final int eScanTypePhoneShake						= 1;
	static public final int eScanTypePeopleSearch					= 2;
	static public final int eScanTypeMoodMsgSearch					= 3;
	static public final int eScanTypeProfilePic						= 4;
	static public final int eScanTypeCamServer						= 5;
	static public final int eScanTypeFileSearch						= 6;
	static public final int eScanTypeStoryBoard						= 7;
	
	static public final int eOfferResponseNotSet					= 0;
	static public final int eOfferResponseAccept					= 1;
	static public final int eOfferResponseReject					= 2;
	static public final int eOfferResponseBusy						= 3;
	static public final int eOfferResponseCancelSession				= 4;
	static public final int eOfferResponseEndSession				= 5;
	static public final int eOfferResponseUserOffline				= 6;
	
	static public final int eSessionStateUnknown					= 0;
	static public final int eSessionStateWaitingResponse			= 1;
	static public final int eSessionStateRejected					= 2;
	static public final int eSessionStateInSession					= 3;
	static public final int eSessionStateSessionEnded				= 4;
	static public final int eSessionContactOffline					= 5;
	static public final int eSessionUserExitedSession				= 6;

	static public final int IMAGE_DESIRED_WIDTH 					= 320;
	static public final int IMAGE_DESIRED_HEIGHT 					= 240;	
	
	static public final int ACTIVITY_PEOPLE 						= 1;
	static public final int ACTIVITY_SEARCH 						= 2;
	static public final int ACTIVITY_SERVERS 						= 3;
	static public final int ACTIVITY_OPTIONS 						= 4;
	static public final int ACTIVITY_CREATE_PROFILE 				= 5;
	static public final int ACTIVITY_EDIT_PROFILE 					= 6;
	static public final int ACTIVITY_CAMERA_SNAPSHOT 				= 7;
	static public final int ACTIVITY_SDCARD 						= 8;
	static public final int ACTIVITY_CAM_SERVER 					= 9;
	static public final int ACTIVITY_EDIT_PERMISSION 				= 10;
	static public final int ACTIVITY_ABOUT 							= 11;
	static public final int ACTIVITY_TO_FRIEND_CHANGE_FRIENDSHIP 	= 12;
	static public final int ACTIVITY_TO_FRIEND_SHARED_FILES 		= 13;
	static public final int ACTIVITY_TO_FRIEND_REQUEST_PROXY 		= 14;
	static public final int ACTIVITY_TO_FRIEND_VOICE_PHONE 			= 15;
	static public final int ACTIVITY_TO_FRIEND_VIDEO_PHONE 			= 16;
	static public final int ACTIVITY_TO_FRIEND_TOD_GAME 			= 17;
	static public final int ACTIVITY_TO_FRIEND_MULTISESSION 		= 18;
	static public final int ACTIVITY_TO_FRIEND_OFFER_FILE 			= 19;
	static public final int ACTIVITY_OFFERS 						= 20;
	static public final int ACTIVITY_NETWORK_SETTINGS 				= 21;
	static public final int ACTIVITY_NETWORK_STATUS	 				= 22;
	static public final int ACTIVITY_CAMERA_SETTINGS 				= 23;
	static public final int ACTIVITY_TEST_NETWORK 					= 24;
	static public final int ACTIVITY_CAM_CLIENT 					= 25;	
	static public final int ACTIVITY_MAIN 							= 26;
	static public final int ACTIVITY_ANCHOR_SETTINGS 				= 27;
	static public final int ACTIVITY_VERIFY_ANCHOR_SETTINGS 		= 28;
	static public final int ACTIVITY_MANAGE_ANCHOR_SETTINGS 		= 29;
	static public final int ACTIVITY_TEST_ANCHOR_SETTINGS 			= 30;
	static public final int ACTIVITY_TEST_IS_PORT_OPEN	 			= 31;
	
	static public final int ACTIVITY_PHONE_SHAKE 					= 31;
	static public final int ACTIVITY_SCAN_PEOPLE_BY_NAME 			= 32;
	static public final int ACTIVITY_SCAN_PEOPLE_BY_MOOD_MSG 		= 33;
	static public final int ACTIVITY_SCAN_PROFILES 					= 34;
	static public final int ACTIVITY_SCAN_WEB_CAMS 					= 35;

	static public final int ACTIVITY_EDIT_ACCOUNT 					= 36;
	static public final int ACTIVITY_EDIT_STORYBOARD 				= 37;
	static public final int ACTIVITY_EDIT_CONTACT_INFO 				= 38;
	static public final int ACTIVITY_CALL_PHONE_NUM 				= 39;
	static public final int ACTIVITY_SMS_TEXT_MESSAGE 				= 40;
	
	static public final int ACTIVITY_PERSONAL_RECORDER 				= 41;
	static public final int ACTIVITY_CAM_TEST 						= 42;
	static public final int ACTIVITY_SELECT_FILE_TO_SEND 			= 43;
	static public final int ACTIVITY_BROWSE_DEVICE_FILES 			= 44;
	static public final int ACTIVITY_VIEW_LIBRARY_FILES 			= 45;
	static public final int ACTIVITY_VIEW_SHARED_FILES 				= 46;
	static public final int ACTIVITY_DOWNLOADS 						= 47;
	static public final int ACTIVITY_UPLOADS 						= 48;
	
	static public final int ACTIVITY_CONFIRM_SHRED_FILE 			= 49;
	static public final int ACTIVITY_VIEW_PHOTO 					= 50;
	static public final int ACTIVITY_PICK_IMAGE 					= 51;
	static public final int ACTIVITY_VIEW_VIDEO_FILE 				= 52;
	static public final int ACTIVITY_VIEW_AUDIO_FILE 				= 53;
	
	static public final int ACTIVITY_MENU_PEOPLE 					= 100;
	static public final int ACTIVITY_MENU_SEARCH 					= 200;
	static public final int ACTIVITY_MENU_SERVERS 					= 300;
	static public final int ACTIVITY_MENU_OPTIONS 					= 400;
	static public final int ACTIVITY_MENU_NOTIFY 					= 500;
	static public final int ACTIVITY_MENU_FRIEND 					= 600;

	static public final int ACTIVITY_ANDROID_USER_PERMISSIONS 		= 333666;

	static public final int MENU_CANCELED 							= 0;
	
	static public final int MENU_PEOPLE 							= 100;
	static public final int MENU_PEOPLE_VIEW_EVERYBODY 				= 101;
	static public final int MENU_PEOPLE_VIEW_GUESTS_AND_FRIENDS 	= 102;
	static public final int MENU_PEOPLE_VIEW_ANONYMOUS 				= 103;
	static public final int MENU_PEOPLE_VIEW_ADMINISTRATORS 		= 104;
	static public final int MENU_PEOPLE_VIEW_IGNORED 				= 105;
	static public final int MENU_PEOPLE_VIEW_MY_PROXIES 			= 106;
	static public final int MENU_PEOPLE_VIEW_ALL_PROXIES 			= 107;	
	static public final int MENU_PEOPLE_VIEW_REFRESH 				= 108;
	
	static public final int MENU_SEARCH 							= 200;
	static public final int MENU_SEARCH_BY_PHONE_SHAKE 				= 201;
	static public final int MENU_SEARCH_BY_NAME 					= 202;
	static public final int MENU_SEARCH_BY_MOOD_MSG 				= 203;
	static public final int MENU_SEARCH_SCAN_PROFILES 				= 204;
	static public final int MENU_SEARCH_SCAN_WEBCAMS 				= 205;
	static public final int MENU_SEARCH_SHARED_FILES 				= 206;
	
	static public final int MENU_SERVERS 							= 300;
	static public final int MENU_SERVERS_STARTSTOP_WEBCAM 			= 301;
	static public final int MENU_SERVERS_EDIT_MY_PROFILE 			= 302;
	static public final int MENU_SERVERS_VIEW_MY_PROFILE 			= 303;
	static public final int MENU_SERVERS_EDIT_MY_STORYBOARD 		= 304;
	static public final int MENU_SERVERS_VIEW_MY_STORYBOARD 		= 305;
	static public final int MENU_SERVERS_SETUP_FILE_SHARE 			= 306;
	
	static public final int MENU_OPTIONS 							= 400;
	static public final int MENU_OPTIONS_ABOUT 						= 401;
	static public final int MENU_OPTIONS_EDIT_ACCOUNT 				= 402;
	static public final int MENU_OPTIONS_EDIT_PERMISSIONS			= 407;
	static public final int MENU_OPTIONS_SETUP_FILE_SHARE 			= 408;
	static public final int MENU_OPTIONS_NETWORK_SETTINGS 			= 409;
	static public final int MENU_OPTIONS_SOUND_SETTINGS 			= 410;
	static public final int MENU_OPTIONS_DEBUG_SETTINGS 			= 411;
	static public final int MENU_OPTIONS_CAMERA_TEST 				= 412;
	
	static public final int MENU_NOTIFY 							= 500;
		
	static public final int MENU_FRIEND 							= 600;
	static public final int MENU_FRIEND_VIEW_PROFILE 				= 601;
	static public final int MENU_FRIEND_VIEW_STORYBOARD 			= 602;
	static public final int MENU_FRIEND_OFFER_VIDPHONE 				= 603;
	static public final int MENU_FRIEND_OFFER_VOIP 					= 604;
	static public final int MENU_FRIEND_OFFER_MULTISESSION			= 605;
	static public final int MENU_FRIEND_OFFER_TRUTHORDARE			= 606;
	static public final int MENU_FRIEND_VIEW_SHARED_WEBCAM 			= 607;
	static public final int MENU_FRIEND_VIEW_SHARED_FILES 			= 608;
	static public final int MENU_FRIEND_SEND_FILE 					= 609;
	static public final int MENU_FRIEND_CHANGE_FRIENDSHIP 			= 610;
	static public final int MENU_FRIEND_PROXY 						= 611;
	//static public final int MENU_FRIEND_EDIT_CONTACT_INFO 			= 612;
	//static public final int MENU_FRIEND_CALL_USING_PHONE_NUM 		= 613;
	//static public final int MENU_FRIEND_SEND_TEXT_USING_SMS 		= 614;

		   
	static public final int MENU_FILEINFO 							= 700;

	
	static public final int MENU_PLUGIN_PERMISSIONS					= 700;
	static public final int MENU_PLUGIN_PROFILE_PERMISSION 			= 701;
	static public final int MENU_PLUGIN_CHAT_PERMISSION 			= 702;
	static public final int MENU_PLUGIN_VOICE_PERMISSION 			= 703;
	static public final int MENU_PLUGIN_VIDPHONE_PERMISSION 		= 704;
	static public final int MENU_PLUGIN_WEBCAM_PERMISSION 			= 705;
	static public final int MENU_PLUGIN_FILE_SHARE_PERMISSION 		= 706;
	static public final int MENU_PLUGIN_FILE_XFER_PERMISSION 		= 707;
	static public final int MENU_PLUGIN_TRUTH_OR_DARE_PERMISSION 	= 708;	
	static public final int MENU_PLUGIN_STORYBOARD_PERMISSION 		= 709;
	static public final int MENU_PLUGIN_PROXY_PERMISSION 			= 710;	
	
	static public final int MENU_FILES 								= 800;
	static public final int MENU_FILES_PERSONAL_RECORDER 			= 801;
	static public final int MENU_FILES_BROWSE_FILES 				= 803;
	static public final int MENU_FILES_VIEW_MY_LIBRARY_FILES 		= 804;	
	static public final int MENU_FILES_VIEW_SHARED_FILES 			= 805;	
	static public final int MENU_FILES_VIEW_DOWNLOADS 				= 806;	
	static public final int MENU_FILES_VIEW_UPLOADS 				= 807;	

	
	
	static public final int eMyIconUnknown							= 0; // Icon with question mark
	static public final int eMyIconApp								= 1;
	static public final int eMyIconPeople							= 2;
	static public final int eMyIconSearch							= 3;
	static public final int eMyIconServers							= 4;
	static public final int eMyIconOptions							= 5;
	static public final int eMyIconFileServer						= 6;

	static public final int eMyIconAdministrator					= 7;
	static public final int eMyIconFriend							= 8;
	static public final int eMyIconGuest							= 9;
	static public final int eMyIconAnonymous						= 10;
	static public final int eMyIconIgnored							= 11;

	static public final int eMyIconWebCamClient						= 12;

	static public final int eMyIconRelay							= 13;
	static public final int eMyIconRelayLocked						= 14;
	static public final int eMyIconRelayDisabled					= 15;
	static public final int eMyIconRelayIgnored						= 16;
	
	static public final int eMyIconProfile							= 17;
	static public final int eMyIconProfileLocked					= 18;
	static public final int eMyIconProfileDisabled					= 19;
	static public final int eMyIconProfileIgnored					= 20;
	
	static public final int eMyIconWebCamServer						= 21;
	static public final int eMyIconWebCamServerLocked				= 22;
	static public final int eMyIconWebCamServerDisabled 			= 23;
	static public final int eMyIconWebCamServerIgnored				= 24;
	
	static public final int eMyIconFolder							= 25;
	static public final int eMyIconFolderDisabled					= 26;
	
	static public final int eMyIconFilesShareNormal					= 27;
	static public final int eMyIconFilesShareLocked					= 28;
	static public final int eMyIconFilesShareDisabled				= 29;
	static public final int eMyIconFilesShareIgnored				= 30;
	static public final int eMyIconFilesShareCancel					= 31;
	static public final int eMyIconFilesShareRed					= 32;
	static public final int eMyIconFilesShareYellow					= 33;
	
	static public final int eMyIconMultiSessionNormal				= 34;
	static public final int eMyIconMultiSessionLocked				= 35;
	static public final int eMyIconMultiSessionDisabled				= 36;
	static public final int eMyIconMultiSessionIgnored				= 37;
	static public final int eMyIconMultiSessionCancel				= 38;
	
	static public final int eMyIconVoicePhoneNormal					= 39;
	static public final int eMyIconVoicePhoneLocked					= 40;
	static public final int eMyIconVoicePhoneDisabled				= 41;
	static public final int eMyIconVoicePhoneIgnored				= 42;
	static public final int eMyIconVoicePhoneCancel					= 43;
	static public final int eMyIconVoicePhoneRed					= 44;
	static public final int eMyIconVoicePhoneYellow					= 45;
	
	static public final int eMyIconVideoPhoneNormal					= 46;
	static public final int eMyIconVideoPhoneLocked					= 47;
	static public final int eMyIconVideoPhoneDisabled				= 48;
	static public final int eMyIconVideoPhoneIgnored				= 49;
	static public final int eMyIconVideoPhoneCancel					= 50;
	static public final int eMyIconVideoPhoneRed					= 51;
	static public final int eMyIconVideoPhoneYellow					= 52;
	
	static public final int eMyIconTruthOrDareNormal				= 53;
	static public final int eMyIconTruthOrDareLocked				= 54;
	static public final int eMyIconTruthOrDareDisabled				= 55;
	static public final int eMyIconTruthOrDareIgnored				= 56;
	static public final int eMyIconTruthOrDareCancel				= 57;
	static public final int eMyIconTruthOrDareRed					= 58;
	static public final int eMyIconTruthOrDareYellow				= 59;

	static public final int eMyIconPermissions						= 60;

	static public final int eMyIconNotifyStarWhite					= 61;
	static public final int eMyIconNotifyStarGreen					= 62;

	static public final int eMyIconRefresh							= 63;
	
	static public final int eMyIconContactInfo						= 64;
	
	static public final int eMyIconFileBrowseNormal					= 65;
	static public final int eMyIconFileBrowseDisabled				= 66;
	static public final int eMyIconFileBrowseCancel					= 67;

	static public final int eMyIconMoveUpDirNormal					= 68;
	static public final int eMyIconMoveUpDirDisabled				= 69;
	static public final int eMyIconMoveUpDirCancel					= 70;
	
	static public final int eMyIconSendFileDisabled					= 71;
	static public final int eMyIconSendFileCancel					= 72;
	static public final int eMyIconSendFileNormal					= 73;
	static public final int eMyIconSendFileRed						= 74;
	static public final int eMyIconSendFileYellow					= 75;
	
	static public final int eMyIconStoryBoardNormal					= 76;
	static public final int eMyIconStoryBoardLocked					= 77;
	static public final int eMyIconStoryBoardDisabled				= 78;
	static public final int eMyIconStoryBoardIgnored				= 79;
	static public final int eMyIconPersonUnknownNormal				= 80;
	
	static public final int eMyIconAdministratorDisabled			= 81;
	
	static public final int eMaxMyIcon								= 82;	// must be last
	
	static public final int eCameraFront							= 1; // camera facing user
	static public final int eCameraBack								= 0; // normal camera facing away from display
	
	static public final int eCameraPreviewHide						= 0;
	static public final int eCameraPreviewShow						= 1;
	
	static public final int ASSET_LOC_FLAG_PERSONAL_RECORD			= 0x0001;
	static public final int ASSET_LOC_FLAG_LIBRARY					= 0x0002;
	static public final int ASSET_LOC_FLAG_SHARED					= 0x0004;

	// the first 8 bits of eAssetType MUST match VxFileInfo 
	static public final int VXFILE_TYPE_UNKNOWN						= 0x00;
	static public final int VXFILE_TYPE_MASK						= 0xff;		
	static public final int VXFILE_TYPE_PHOTO						= 0x01;		
	static public final int VXFILE_TYPE_AUDIO						= 0x02;		
	static public final int VXFILE_TYPE_VIDEO						= 0x04;		
	static public final int VXFILE_TYPE_DOC							= 0x08;
	static public final int VXFILE_TYPE_ARCHIVE_OR_ISO				= 0x10;
	static public final int VXFILE_TYPE_EXECUTABLE					= 0x20;	
	static public final int VXFILE_TYPE_OTHER						= 0x40;
	static public final int VXFILE_TYPE_DIRECTORY					= 0x80;

	// asset type
	static public final short eAssetTypeUnknown						= 0x00;
	static public final short eAssetTypePhoto						= 0x01;
	static public final short eAssetTypeAudio						= 0x02;
	static public final short eAssetTypeVideo						= 0x04;
	static public final short eAssetTypeDocument					= 0x08;
	static public final short eAssetTypeArchives					= 0x10;
	static public final short eAssetTypeExe							= 0x20;
	static public final short eAssetTypeOtherFiles					= 0x40;
	static public final short eAssetTypeDirectory					= 0x80;
	// these are specific to my p2p web
	static public final short eAssetTypeChatText					= 0x100;
	static public final short eAssetTypeChatFace					= 0x200;
	static public final short eAssetTypeChatStockAvatar				= 0x400;
	static public final short eAssetTypeChatCustomAvatar			= 0x800;

	// enum EAssetLocation
	static public final int eAssetLocUnknown						= 0x00;
	static public final int eAssetLocLibrary						= 0x01;
	static public final int eAssetLocShared							= 0x02;
	static public final int eAssetLocPersonalRec					= 0x04;

	// enum EAssetAction
	static public final int eAssetActionUnknown						= 0;
	static public final int eAssetActionDeleteFile					= 1;
	static public final int eAssetActionShreadFile					= 2;
	static public final int eAssetActionAddToAssetMgr				= 3;
	static public final int eAssetActionRemoveFromAssetMgr			= 4;	
	static public final int eAssetActionUpdateAsset					= 5;
	static public final int eAssetActionAddAssetAndSend				= 6;
	static public final int eAssetActionAssetResend					= 7;

	static public final int eAssetActionAddToShare					= 8;
	static public final int eAssetActionRemoveFromShare				= 9;
	static public final int eAssetActionAddToLibrary				= 10;
	static public final int eAssetActionRemoveFromLibrary			= 11;
	static public final int eAssetActionAddToHistory				= 12;
	static public final int eAssetActionRemoveFromHistory			= 13;

	static public final int eAssetActionRecordBegin					= 14;
	static public final int eAssetActionRecordPause					= 15;
	static public final int eAssetActionRecordResume				= 16;
	static public final int eAssetActionRecordProgress				= 17;
	static public final int eAssetActionRecordEnd					= 18;
	static public final int eAssetActionRecordCancel				= 19;

	static public final int eAssetActionPlayBegin					= 20;
	static public final int eAssetActionPlayOneFrame				= 21;
	static public final int eAssetActionPlayPause					= 22;
	static public final int eAssetActionPlayResume					= 23;
	static public final int eAssetActionPlayProgress				= 24;
	static public final int eAssetActionPlayEnd						= 25;
	static public final int eAssetActionPlayCancel					= 26;

	static public final int eAssetActionTxBegin						= 27;
	static public final int eAssetActionTxProgress					= 28;
	static public final int eAssetActionTxSuccess					= 29;
	static public final int eAssetActionTxError						= 30;
	static public final int eAssetActionTxCancel					= 31;
	static public final int eAssetActionTxPermission				= 32;

	static public final int eAssetActionRxBegin						= 33;
	static public final int eAssetActionRxProgress					= 34;
	static public final int eAssetActionRxSuccess					= 35;
	static public final int eAssetActionRxError						= 36;
	static public final int eAssetActionRxCancel					= 37;
	static public final int eAssetActionRxPermission				= 38;
	
	static public final int eAssetActionRxNotifyNewMsg				= 39;
	static public final int eAssetActionRxViewingMsg				= 40;

	static public final int eAssetSendStateNone						= 0;
	static public final int eAssetSendStateTxProgress				= 1;
	static public final int eAssetSendStateRxProgress				= 2;
	static public final int eAssetSendStateTxSuccess				= 3;
	static public final int eAssetSendStateTxFail					= 4;
	static public final int eAssetSendStateRxSuccess				= 5;
	static public final int eAssetSendStateRxFail					= 6;
	static public final int eAssetSendStateTxPermissionErr			= 7;
	static public final int eAssetSendStateRxPermissionErr			= 8;
		
	static public final int eXferStateUnknown						= 0;
	static public final int eXferStateUploadNotStarted				= 1;
	static public final int eXferStateWaitingOfferResponse			= 2;
	static public final int eXferStateInUploadQue					= 3;
	static public final int eXferStateBeginUpload					= 4;
	static public final int eXferStateInUploadXfer					= 5;
	static public final int eXferStateCompletedUpload				= 6;
	static public final int eXferStateUserCanceledUpload			= 7;
	static public final int eXferStateUploadOfferRejected			= 8;
	static public final int eXferStateUploadError					= 9;
		
	static public final int eXferStateDownloadNotStarted			= 10;
	static public final int eXferStateInDownloadQue					= 11;
	static public final int eXferStateBeginDownload					= 12;
	static public final int eXferStateInDownloadXfer				= 13;
	static public final int eXferStateCompletedDownload				= 14;
	static public final int eXferStateUserCanceledDownload			= 15;
	static public final int eXferStateDownloadError					= 16;
	

	// xfer error enum
	static public final int eXferErrorNone							= 0;
	static public final int eXferErrorDisconnected					= 1;
	static public final int eXferErrorPermission					= 2;
	static public final int eXferErrorFileNotFound					= 3;
	static public final int eXferErrorCanceled						= 4;
	static public final int eXferErrorBadParam						= 5;
	static public final int eXferErrorAtSrc							= 6;
	static public final int eXferErrorBusy							= 7;
	static public final int eXferErrorAlreadyDownloading			= 8;
	static public final int eXferErrorAlreadyDownloaded				= 9;
	static public final int eXferErrorAlreadyUploading				= 10;
	static public final int eXferErrorFileCreateError				= 11;
	static public final int eXferErrorFileOpenAppendError			= 12;
	static public final int eXferErrorFileOpenError					= 13;
	static public final int eXferErrorFileSeekError					= 14;
	static public final int eXferErrorFileReadError					= 15;
	static public final int eXferErrorFileWriteError				= 16;
	static public final int eXferErrorFileMoveError					= 17;

	static public final int eXferDirectionRx						= 0;
	static public final int eXferDirectionTx						= 1;

	//========================================================================
	static int getFriendIconResource( int iFriendshipType )
	{
		int iResourceId;
		switch( iFriendshipType )
		{
		case eFriendStateIgnore:
			iResourceId = R.drawable.ic_ignore;
			break;
			
		case eFriendStateAnonymous:
			iResourceId = R.drawable.button_person_unknown_normal;
			break;
			
		case eFriendStateGuest:
			iResourceId = R.drawable.ic_guest;
			break;
			
		case eFriendStateFriend:
			iResourceId = R.drawable.button_people_normal;
			break;
			
		case eFriendStateAdministrator:
			iResourceId = R.drawable.button_administrator_normal;
			break;
			
		default:
			iResourceId = R.drawable.ic_unknown;
		}
		
		return iResourceId;
	}
	
	//========================================================================
	//! describe friend state
	static final String[] 				g_aoFriendshipDescriptions = { "Ignore: ", "Anonymous: ",  "Guest: ", "Friend: ", "Admin: " };
	static public String describeFriendState( int eFriendState )
	{
		if( eFriendStateAdministrator >= eFriendState )
		{
			return g_aoFriendshipDescriptions[ eFriendState ];
		}
		else
		{
			return "Unknown Friendship: ";
		}
	}
	
	//========================================================================
	//enum EMyRelayStatus
	//{
	static public final int eMyRelayStatusDisconnected				= 0;
	static public final int eMyRelayStatusConnected					= 1;
	static public final int eMyRelayStatusSearching					= 2;
	static public final int eMyRelayStatusNoRelaysListed			= 3;
	static public final int eMyRelayStatusRelayListExhasted			= 4;
	static public final int eMyRelayStatusAssumeFirewalled			= 5;
	static public final int eMyRelayStatusAssumeCanDirectConnect	= 6;

	//	eMaxMyRelayStatus
	//};

	static public final String[] RelayStatusEnumStrings = 
	{ 
		"Relay Disconnected ",
		"Relay Connected ",
		"Searching For Relay ",
		"No Relays Listed ",
		"Relay Search ",
		"Relay List Exhausted ",
		"Relay Assume Firewalled ",
		"Relay Assume Can Direct Connect ",
		"Max Relay Status "
	};
	
	//========================================================================
	static public String describeRelayStatus( int eRelayStatus )
	{
		return RelayStatusEnumStrings[ eRelayStatus ];		
	}

	//========================================================================
	//enum ENetworkStateType
	//{
	static public final int eNetworkStateTypeUnknown				= 0;
	static public final int eNetworkStateTypeLost					= 1;
	static public final int eNetworkStateTypeAvail					= 2;
	static public final int eNetworkStateTypeTestConnection			= 3;
	static public final int eNetworkStateTypeRelaySearch			= 4;
	static public final int eNetworkStateTypeAnnounce				= 5;
	static public final int eNetworkStateTypeOnlineDirect			= 6;
	static public final int eNetworkStateTypeOnlineThroughRelay		= 7;
	static public final int eNetworkStateTypeGetRelayList			= 8;
	static public final int eNetworkStateTypeNoInternetConnection	= 9;
	static public final int eNetworkStateTypeFailedResolveAnchor	= 10;
	//	eMaxNetworkStateType
	//};
	
	static public final String[] NetworkStateEnumStrings = 
	{ 
		"Unknown Network",
		"Lost ",
		"Available ",
		"Testing Connection ",
		"Relay Search ",
		"Announce To Network ",
		"Online Direct Connect ",
		"Online Through Relay ",
		"Getting Relay List ",
		"No Internet Connection ",
		"Failed Resolve Anchor URL ",
		"Max Network State "
	};

	//========================================================================
	static public String describeNetworkState( int networkStateType )
	{
		return NetworkStateEnumStrings[ networkStateType ];	
	}
	
	//========================================================================
	//enum EAnchorTestStatus
	//{
	static public final int eAnchorTestStatusUnknown						= 0;
	static public final int eAnchorTestStatusLogMsg							= 1;

	static public final int eAnchorTestStatusAnchorOk						= 2;
	static public final int eAnchorTestStatusAnchorConnectFail				= 3;
	static public final int eAnchorTestStatusAnchorConnectionDropped		= 4;
	static public final int eAnchorTestStatusAnchorTestComplete				= 5;

	static public final int eAnchorTestStatusNetServiceOk					= 6;
	static public final int eAnchorTestStatusNetServiceConnectFail			= 7;
	static public final int eAnchorTestStatusNetServiceConnectionDropped	= 8;
	static public final int eAnchorTestStatusNetServiceTestComplete			= 9;
//		eMaxAnchorTestStatusType
//	};
	
	static public final String[] AnchorStatusEnumStrings = 
	{ 
		"Anchor Status Unknown",
		"Anchor LogMsg",

		"Anchor OK",
		"Anchor Connect Fail",
		"Anchor Connection Dropped",
		"Anchor TestComplete",

		"NetService OK",
		"NetService Connect Fail",
		"NetService Connection Dropped",
		"NetService Test Complete",

		"Max Anchor Status",
	};

	//========================================================================
	static public String describeAnchorStatus( int eAnchorStatus )
	{
		return AnchorStatusEnumStrings[ eAnchorStatus ];	
	}
	
	//========================================================================
//	enum EIsPortOpenStatus
//	{
	static public final int eIsPortOpenStatusUnknown						= 0;
	static public final int eIsPortOpenStatusLogMsg							= 1;

	static public final int eIsPortOpenStatusOpen							= 2;
	static public final int eIsPortOpenStatusClosed							= 3;
	static public final int eIsPortOpenStatusConnectFail					= 4;
	static public final int eIsPortOpenStatusConnectionDropped				= 5;
	static public final int eIsPortOpenStatusInvalidResponse				= 6;
	static public final int eIsPortOpenStatusTestComplete					= 7;
//		eMaxIsPortOpenStatusType
//	};

	static public final String[] PortOpenStatusEnumStrings = 
	{ 
		"Port Open Status Unknown",
		"Port Open LogMsg",

		"Port Open OK",
		"Port Open Closed",
		"Port Open Connect Fail",
		"Port Open Connection Dropped",
		"Port Open Invalid Response",
		"Port Open Test Complete",

		"Max Port Open Status"
	};

	//========================================================================
	static public String describePortOpenStatus( int ePortOpenStatus )
	{
		return PortOpenStatusEnumStrings[ ePortOpenStatus ];	
	}

	static public final String[] PhoneShakeStatusEnumStrings = 
	{ 
		"Phone Shake: Status Unknown ",
		"Phone Shake: Contact Anchor Failed ",

		"Phone Shake: Found Friend ",
		"Phone Shake: Empty List ",
		"Phone Shake: Send Request Fail ",
		"Phone Shake: Invalid Response ",
		"Phone Shake: Decrypt Error ",
		"Phone Shake: Search Complete ",

		"Max Phone Shake Status ",
	};

	//========================================================================
	static public String describePhoneShakeStatus( int ePhoneShakeStatus )
	{
		return PhoneShakeStatusEnumStrings[ ePhoneShakeStatus ];	
	}
	
	static public String LIFETIME = "LIFETIME";

	//========================================================================
	public static String describePluginType( int ePluginType )
	{
		String strPluginType;
		switch( ePluginType )
		{
		case ePluginTypeAdmin:	
			strPluginType ="Admin";
			break;

		case ePluginTypeRelay:	// proxy plugin
			strPluginType ="Relay";
			break;

		case ePluginTypeWebServer:	// web server plugin ( for profile web page )
			strPluginType ="About Me Web Page";
			break;

		case ePluginTypeFileOffer:	// file offer plugin
			strPluginType ="Send A File";
			break;

		case ePluginTypeFileServer:	// file share plugin
			strPluginType ="Shared Files";
			break;

		case ePluginTypeCamServer:	// web cam broadcast plugin
			strPluginType ="Shared Web Cam";
			break;

		case ePluginTypeMultiSession:	// multi session chat plugin
			strPluginType ="Chat Session";
			break;

		case ePluginTypeVoicePhone:	// VOIP p2p plugin
			strPluginType ="Voice Call";
			break;

		case ePluginTypeVideoPhone:
			strPluginType ="Video Chat";
			break;

		case ePluginTypeTruthOrDare:	// Web Cam Truth Or Dare game p2p plugin
			strPluginType ="Play Truth Or Dare";
			break;

		case ePluginTypeStoryBoard:	// story board plugin
			strPluginType ="Story Board";
			break;

		default:
			strPluginType ="Unknown Plugin";
			//LogMsg( LOG_ERROR, "DescribePluginAction: unrecognized plugin %d\n", ePluginType );
		}

		return strPluginType;
	}

	//============================================================================
	public static String describePluginAccess( int ePluginAccessState )
	{
		String strAccess = "";
		switch( ePluginAccessState )
		{
		case ePluginAccessOk:
			strAccess = "Access Ok";
			break;

		case ePluginAccessLocked:
			strAccess = "Insufficient Permission";
			break;

		case ePluginAccessDisabled:
			strAccess = "Plugin Disabled";
			break;

		case ePluginAccessIgnored:
			strAccess = "Contact Ignored";
			break;

		case ePluginAccessInactive:
			strAccess = "Plugin Inactive";
			break;

		case ePluginAccessBusy:
			strAccess = "Plugin Busy";
			break;

		case ePluginAccessRequiresDirectConnect:
			strAccess = "Requires Direct Connect";
			break;

		case ePluginAccessRequiresOnline:
			strAccess = "Requires User Be Online";
			break;

		default:
			strAccess = "Unknown Plugin Access";
		}

		return strAccess;
	}
};