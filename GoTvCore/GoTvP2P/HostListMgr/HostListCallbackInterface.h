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

#include <CoreLib/HostListDefs.h>
#include <CoreLib/VxGUID.h>
#include <CoreLib/VxSha1Hash.h>

class HostListInfo;

class HostListCallbackInterface
{
public:
	virtual void				callbackFileWasShredded( std::string& fileName ){};

	virtual void				callbackHashIdGenerated( std::string& fileName, VxSha1Hash& hashId ){};
	virtual void				callbackHostListAdded( HostListInfo * assetInfo ){};
	virtual void				callbackHostListRemoved( HostListInfo * assetInfo ){};
	virtual void				callbackHostListSendState( VxGUID& assetUniqueId, EHostListSendState assetSendState, int param ){};

	virtual void				callbackHostListFileTypesChanged( uint16_t fileTypes ){};
	virtual void				callbackHostListPktFileListUpdated( void ){};

	virtual void				callbackHostListHistory( void * userData, HostListInfo * assetInfo ){};
};

