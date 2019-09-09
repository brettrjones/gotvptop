#pragma once
//============================================================================
// Copyright (C) 2017 Brett R. Jones
// Issued to MIT style license by Brett R. Jones in 2017
//
// You may use, copy, modify, merge, publish, distribute, sub-license, and/or sell this software
// provided this Copyright is not modified or removed and is included all copies or substantial portions of the Software
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// bjones.engineer@gmail.com
// http://www.gotvptop.com
//============================================================================

#define OBJNAME_ACTIVITY_ABOUT							"ActivityAbout"
#define OBJNAME_ACTIVITY_ADD_REMOVE_LIB_FILES			"ActivityAddRemoveLibraryFiles"
#define OBJNAME_ACTIVITY_ANCHOR_SETTINGS				"ActivityAnchorSettings"
#define OBJNAME_ACTIVITY_BROWSE_FILES					"ActivityBrowseFiles"
#define OBJNAME_ACTIVITY_CHOOSE_IP_PORT					"ActivityChooseIpPort"
#define OBJNAME_ACTIVITY_CHOOSE_TEST_WEBSITE_URL		"ActivityChooseTestWebsiteUrl"
#define OBJNAME_ACTIVITY_CREATE_PROFILE		            "ActivityCreateProfile"
#define OBJNAME_ACTIVITY_DEBUG_SETTINGS					"ActivityDebugSettings"
#define OBJNAME_ACTIVITY_DOWNLOAD_ITEM_MENU				"ActivityDownloadItemMenu"
#define OBJNAME_ACTIVITY_DOWNLOADS						"ActivityDownloads"
#define OBJNAME_ACTIVITY_EDIT_ACCOUNT					"ActivityEditAccount"
#define OBJNAME_ACTIVITY_EDIT_PROFILE					"ActivityEditProfile"
#define OBJNAME_ACTIVITY_FILE_SEARCH					"ActivityFileSearch"
#define OBJNAME_ACTIVITY_IS_PORT_OPEN_TEST				"ActivityIsPortOpenTest"
#define OBJNAME_ACTIVITY_MANAGE_ANCHOR_SETTINGS			"ActivityManageAnchorSettings"
#define OBJNAME_ACTIVITY_MESSAGE_BOX					"ActivityMessageBox"
#define OBJNAME_ACTIVITY_NET_SERVICE_TEST				"ActivityNetServiceTest"
#define OBJNAME_ACTIVITY_NETWORK_SETTINGS				"ActivityNetworkSettings"
#define OBJNAME_ACTIVITY_NETWORK_STATE					"ActivityNetworkState"
#define OBJNAME_ACTIVITY_PERMISSIONS					"ActivityPermissions"
#define OBJNAME_ACTIVITY_PERMISSIONS_RELAY				"ActivityPermissionsRelay"
#define OBJNAME_ACTIVITY_PERSONAL_RECORDER				"ActivityPersonalRecorder"
#define OBJNAME_ACTIVITY_PHONE_SHAKE					"ActivityPhoneShake"
#define OBJNAME_ACTIVITY_PEOPLE_SEARCH					"ActivityScanPeopleSearch"
#define OBJNAME_ACTIVITY_SCAN_PROFILES					"ActivityScanProfiles"
#define OBJNAME_ACTIVITY_SCAN_STORYBOARDS				"ActivityScanStoryBoards"
#define OBJNAME_ACTIVITY_SCAN_WEB_CAMS					"ActivityScanWebCams"
#define OBJNAME_ACTIVITY_SELECT_FILE_TO_SEND			"ActivitySelectFileToSend"
#define OBJNAME_ACTIVITY_SESSION_FILE_OFFER				"ActivitySessionFileOffer"
#define OBJNAME_ACTIVITY_SESSION_OPTIONS				"ActivitySessionOptions"
#define OBJNAME_ACTIVITY_SHOW_HELP						"ActivityShowHelp"
#define OBJNAME_ACTIVITY_SNAP_SHOT						"ActivitySnapShot"
#define OBJNAME_ACTIVITY_SOUND_OPTIONS					"ActivitySoundOptions"
#define OBJNAME_ACTIVITY_STORYBOARD						"ActivityStoryBoard"
#define OBJNAME_ACTIVITY_REPLY_FILE_OFFER				"ActivityReplyFileOffer"
#define OBJNAME_ACTIVITY_TO_FRIEND_BASE					"ActivityToFriendBase"
#define OBJNAME_ACTIVITY_TO_FRIEND_CHANGE_FRIENDSHIP	"ActivityToFriendChangeFriendship"
#define OBJNAME_ACTIVITY_TO_FRIEND_MULTISESSION	        "ActivityToFriendMultiSession"
#define OBJNAME_ACTIVITY_TO_FRIEND_REQUEST_RELAY		"ActivityToFriendRequestRelay"
#define OBJNAME_ACTIVITY_TO_FRIEND_TOD_GAME		        "ActivityToFriendTodGame"
#define OBJNAME_ACTIVITY_TO_FRIEND_VIEW_SHARED_FILES	"ActivityToFriendViewSharedFiles"
#define OBJNAME_ACTIVITY_TO_FRIEND_VIDEO_PHONE	        "ActivityToFriendVideoPhone"
#define OBJNAME_ACTIVITY_TO_FRIEND_VOICE_PHONE	        "ActivityToFriendVoicePhone"
#define OBJNAME_ACTIVITY_UPLOADS						"ActivityUploads"
#define OBJNAME_ACTIVITY_VIDEO_OPTIONS	                "ActivityVideoOptions"
#define OBJNAME_ACTIVITY_VIEW_AUDIO_FILE				"ActivityViewAudioFile"
#define OBJNAME_ACTIVITY_VIEW_LIBRARY_FILES				"ActivityViewLibraryFiles"
#define OBJNAME_ACTIVITY_VIEW_MY_SHARED_FILES			"ActivityViewMySharedFiles"
#define OBJNAME_ACTIVITY_VIEW_VIDEO_FILE				"ActivityViewVideoFile"
#define OBJNAME_ACTIVITY_WEB_CAM_CLIENT				    "ActivityWebCamClient"
#define OBJNAME_ACTIVITY_YES_NO_MSG_BOX					"ActivityYesNoMsgBox"
#define OBJNAME_ACTIVITY_INFORMATION					"ActivityInformation"

#define OBJNAME_APPLET_BASE								"AppletBase"
#define OBJNAME_APPLET_KODI						        "AppletKodi"
#define OBJNAME_APPLET_LAUNCH_PAGE						"AppletLaunchPage"
#define OBJNAME_APPLET_NET_HOSTING						"AppletNetHosting"
#define OBJNAME_APPLET_LAUNCH_WIDGET					"AppletLaunchWidget"
#define OBJNAME_APPLET_PLAYER_VIDEO						"AppletPlayerVideo"
#define OBJNAME_APPLET_REMOTE_CONTROL					"AppletRemoteControl"
#define OBJNAME_APPLET_SETTINGS							"AppletSettings"
#define OBJNAME_APPLET_SHARED_CONTENT					"AppletSharedContent"
#define OBJNAME_APPLET_THEME							"AppletTheme"
#define OBJNAME_APPLET_USER_IDENTITY				    "AppletUserIdentity"
#define OBJNAME_APPLET_GROUP_USER						"AppletGroupUser"
#define OBJNAME_APPLET_GROUP_HOST						"AppletGroupHost"
#define OBJNAME_APPLET_GROUP_ANCHOR						"AppletGroupAnchor"
#define OBJNAME_APPLET_GOTVPTOP_NETWORK_HOST			"AppletGoTvPtoPNetworkHost"

#define OBJNAME_FILE_ACTION_MENU						"FileActionMenu"
#define OBJNAME_MESSAGER_PAGE							"MessengerPage"
#define OBJNAME_POPUP_MENU							    "AppletRemoteControl"

#define OBJNAME_UNKNOWN							        "OBJ_UNKNOW"

#include <string>

class ObjectCommon
{
public:
	ObjectCommon();
	ObjectCommon( std::string nameText );
	virtual ~ObjectCommon(){};

	void						setObjName( std::string nameText );
	const char *				getObjName( void )					    { return m_ObjectName.c_str(); }


protected:
	std::string					m_ObjectName;
};
