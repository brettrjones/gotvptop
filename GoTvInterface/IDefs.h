#pragma once
//============================================================================
// Copyright (C) 2013 Brett R. Jones 
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

#include "IScan.h"

#include <NetLib/VxXferDefs.h>


//! \public Enumerated plugins
enum EPluginType
{
	//! NOTE: don't handle packets for ePluginTypeInvalid or ePluginTypeWebServer
	ePluginTypeInvalid			= 0,	//!< unknown or disabled

	ePluginTypeAdmin			= 1,	//!< Administration ( not currently used )
	ePluginTypeRelay			= 2,	//!< Relay services plugin
	ePluginTypeWebServer		= 3,	//!< Web server plugin ( for About Me and Story Board web pages )
	ePluginTypeCamServer		= 4,	//!< Web cam broadcast plugin
	ePluginTypeMultiSession		= 5,	//!< Text, voice and video message texting with voice phone, video chat and truth or dare game available in session
	ePluginTypeVoicePhone		= 6,	//!< VOIP audio only phone call
	ePluginTypeVideoPhone		= 7,	//!< Video Chat with motion detect and stream recording
	ePluginTypeTruthOrDare		= 8,	//!< Video Chat Truth Or Dare game  
	ePluginTypeFileOffer		= 9,	//!< Offer/accept send a file person to person
	ePluginTypeFileServer		= 10,	//!< Shared files server
	ePluginTypeStoryBoard		= 11,	//!< User editable story board web page server
    ePluginTypeAvatarImage      = 12,	//!< handle users avatar image
    ePluginTypeGroupUser        = 13,	//!< group user
    ePluginTypeGroupHost		= 14,	//!< group host
    ePluginTypeGroupAnchor		= 15,	//!< group list host
    ePluginTypeNetworkHost		= 16,	//!< master group list host
    ePluginTypeGroupTier2		= 17,	//!< group end user
	// NOTE: plugin types 18 - 47 not implemented .. reserved for future use
	eMaxUserPluginType			= 18, 
	// plugins 0-47 are part of PktAnnounce
	// plugins after 47 are system plugins and do not go out in announcement pkt
	eAppPluginsBegin			= 48,
	ePluginTypeNetServices,	
	ePluginTypeSearch,	
	ePluginTypeSndWriter,
	ePluginTypeSndReader,
	ePluginTypeMJPEGWriter,	
	ePluginTypeMJPEGReader,	
	ePluginTypeCameraService,
	ePluginTypePersonalRecorder,

	eMaxPluginType	
};

//! \public Enumeration of plugin accessibility
enum EPluginAccessState
{
	ePluginAccessOk				= 0,		//!< Plugin access allowed
	ePluginAccessLocked			= 1,		//!< Insufficient Friend permission level
	ePluginAccessDisabled		= 2,		//!< Plugin disabled or no files shared or no web cam broadcast
	ePluginAccessIgnored		= 3,		//!< Access denied because you are being ignored
	ePluginAccessInactive		= 4,		//!< Enabled and have access but no shared files or web cam
	ePluginAccessBusy			= 5,		//!< Sufficient permission but cannot accept any more sessions
	ePluginAccessRequiresDirectConnect = 6,	//!< Plugin access requires contact have direct connection
	ePluginAccessRequiresOnline		= 7		//!< Plugin access requires contact to be online
};

//! \public Enumeration of friendship type. NOTE: also used as plugin permission type
enum EFriendState
{
	eFriendStateIgnore		= 0,	//!< Unknown or disabled or ignore
	eFriendStateAnonymous	= 1,	//!< Anonymous contact
	eFriendStateGuest		= 2,	//!< Guest contact
	eFriendStateFriend		= 3,	//!< Friend contact
	eFriendStateAdmin		= 4		//!< Administrator contact
};

//! \public Enumeration of session offer response
enum EOfferResponse
{
	eOfferResponseNotSet		= 0,	//!< Unknown or not set offer response from contact
	eOfferResponseAccept		= 1,	//!< Contact accepted offer
	eOfferResponseReject		= 2,	//!< Contact rejected offer
	eOfferResponseBusy			= 3,	//!< Contact cannot accept session because already in session
	eOfferResponseCancelSession	= 4,	//!< Contact exited session
	eOfferResponseEndSession	= 5,	//!< Session end because of any reason
	eOfferResponseUserOffline	= 6		//!< Session end because contact is not online
};

//! \public In Text Chat Session Actions
enum EMSessionAction
{
	eMSessionActionNone,
	eMSessionActionChatSessionReq,
	eMSessionActionChatSessionAccept,
	eMSessionActionChatSessionReject,
	eMSessionActionOffer,
	eMSessionActionAccept,
	eMSessionActionReject,
	eMSessionActionHangup,

	eMaxMSessionAction
};

//! \public Session Types
enum EMSessionType
{
	eMSessionTypePhone 						= 0,
	eMSessionTypeVidChat 					= 1,
	eMSessionTypeTruthOrDare 				= 2,

	eMaxMSessionType
};

//! \public Enumeration of which contacts to show in contact list
enum EFriendViewType
{
	eFriendViewEverybody		= 0,
	eFriendViewAdministrators   = 1,
	eFriendViewFriendsAndGuests = 2,
	eFriendViewAnonymous		= 3,
	eFriendViewIgnored			= 4,
	eFriendViewMyProxies		= 5,
	eFriendViewAllProxies		= 6,
	eFriendViewRefresh			= 7,

	eMaxFriendViewType // must be last
};

//! \public Enumeration of relay status
enum ERelayStatus
{
	eRelayStatusUnknown			= -1,	//!< Unknown
	eRelayStatusOk				= 0,	//!< Relay enabled and access accepted 
	eRelayStatusPermissionErr	= 1,	//!< Insufficient permission
	eRelayStatusBusy			= 2,	//!< Relay cannot accept any more session

	eMaxRelayStatus
};


//! \public Connect by shaking phone ( or press simulate phone shake ) status
enum EPhoneShakeStatus
{
	ePhoneShakeStatusUnknown						= 0,
	ePhoneShakeStatusContactAnchorFail				= 1,
	ePhoneShakeStatusFoundFriend					= 2,
	ePhoneShakeStatusEmptyList						= 3,
	ePhoneShakeStatusSendRequestFail				= 4,
	ePhoneShakeStatusInvalidResponse				= 5,
	ePhoneShakeStatusDecryptError					= 6,
	ePhoneShakeStatusSearchComplete					= 7,

	eMaxPhoneShakeStatusType
};
