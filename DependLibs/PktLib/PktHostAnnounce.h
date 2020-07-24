#pragma once
//============================================================================
// Copyright (C) 2003 Brett R. Jones 
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

#include "PktAnnounce.h"


#define PKT_HOST_ANNOUNCE_VERSION 1

#pragma pack(push) 
#pragma pack(1)
class PktHostAnnounce :  public PktAnnounce
{
public:
    PktHostAnnounce();

	bool						isValidPktHostAnn( void );

    PktHostAnnounce *			makeHostAnnCopy( void );
    PktHostAnnounce *			makeHostAnnReverseCopy( void );
	void						DebugHostDump( void );
};

#pragma pack(pop)

