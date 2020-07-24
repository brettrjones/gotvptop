#pragma once
//============================================================================
// Copyright (C) 2015 Brett R. Jones
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
// http://www.nolimitconnect.com
//============================================================================

#include <config_gotvcore.h>

enum EHostListType
{
// the first 8 bits MUST match VxFileInfo 
//#define VXFILE_TYPE_PHOTO					0x01		
//#define VXFILE_TYPE_AUDIO					0x02		
//#define VXFILE_TYPE_VIDEO					0x04		
//#define VXFILE_TYPE_DOC					0x08
//#define VXFILE_TYPE_ARCHIVE_OR_CDIMAGE	0x10
//#define VXFILE_TYPE_EXECUTABLE			0x20	
//#define VXFILE_TYPE_OTHER					0x40
//#define VXFILE_TYPE_DIRECTORY				0x80

	eHostListTypeUnknown				= 0x00,
	eHostListTypePhoto					= 0x01,
	eHostListTypeAudio					= 0x02,
	eHostListTypeVideo					= 0x04,
	eHostListTypeDocument				= 0x08,
	eHostListTypeArchives				= 0x10,
	eHostListTypeExe					= 0x20,
	eHostListTypeOtherFiles			    = 0x40,
	eHostListTypeDirectory				= 0x80,
	// these are specific to my p2p web
	eHostListTypeChatText				= 0x100,
	eHostListTypeChatFace				= 0x200,
	eHostListTypeChatStockAvatar		= 0x400,
	eHostListTypeChatCustomAvatar		= 0x800,
    eHostListTypeThumbnail             = 0x1000,
    eHostListTypeCamRecord             = 0x2000
};

enum EHostListLocation
{
	eHostListLocUnknown				= 0x00,
	eHostListLocLibrary				= 0x01,
	eHostListLocShared					= 0x02,
	eHostListLocPersonalRec			= 0x04,
    eHostListLocThumbDirectory         = 0x08,
    eHostListLocCamRecord              = 0x10
};

enum EHostListAction
{
	eHostListActionUnknown				= 0,
	eHostListActionDeleteFile			= 1,
	eHostListActionShreadFile			= 2,
	eHostListActionAddToHostListMgr		= 3,
	eHostListActionRemoveFromHostListMgr	= 4,	
	eHostListActionUpdateHostList			= 5,
	eHostListActionAddHostListAndSend		= 6,
	eHostListActionHostListResend			= 7,

	eHostListActionAddToShare			= 8,
	eHostListActionRemoveFromShare		= 9,
	eHostListActionAddToLibrary		= 10,
	eHostListActionRemoveFromLibrary	= 11,
	eHostListActionAddToHistory		= 12,
	eHostListActionRemoveFromHistory	= 13,

	eHostListActionRecordBegin			= 14,
	eHostListActionRecordPause			= 15,
	eHostListActionRecordResume		= 16,
	eHostListActionRecordProgress		= 17,
	eHostListActionRecordEnd			= 18,
	eHostListActionRecordCancel		= 19,

	eHostListActionPlayBegin			= 20,
	eHostListActionPlayOneFrame		= 21,
	eHostListActionPlayPause			= 22,
	eHostListActionPlayResume			= 23,
	eHostListActionPlayProgress		= 24,
	eHostListActionPlayEnd				= 25,
	eHostListActionPlayCancel			= 26,

	eHostListActionTxBegin				= 27,
	eHostListActionTxProgress			= 28,
	eHostListActionTxSuccess			= 29,
	eHostListActionTxError				= 30,
	eHostListActionTxCancel			= 31,
	eHostListActionTxPermission		= 32,

	eHostListActionRxBegin				= 33,
	eHostListActionRxProgress			= 34,
	eHostListActionRxSuccess			= 35,
	eHostListActionRxError				= 36,
	eHostListActionRxCancel			= 37,
	eHostListActionRxPermission		= 38,

	eHostListActionRxNotifyNewMsg		= 39,
	eHostListActionRxViewingMsg		= 40,
};

enum EHostListSendState
{
	eHostListSendStateNone     = 0,
	eHostListSendStateTxProgress,
	eHostListSendStateRxProgress,
	eHostListSendStateTxSuccess,
	eHostListSendStateTxFail,
	eHostListSendStateRxSuccess,
	eHostListSendStateRxFail,
	eHostListSendStateTxPermissionErr,
	eHostListSendStateRxPermissionErr,
	
	eMaxHostListSendState	
};

