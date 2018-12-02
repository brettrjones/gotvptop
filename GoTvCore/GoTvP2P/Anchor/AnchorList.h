#ifndef ANCHOR_LIST_H
#define ANCHOR_LIST_H

//============================================================================
// Copyright (C) 2014 Brett R. Jones 
// Issued to MIT style license by Brett R. Jones in 2017
//
// You may use, copy, modify, merge, publish, distribute, sub-license, and/or sell this software 
// provided this Copyright is not modified or removed and is included all copies or substantial portions of the Software
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// brett.jones@engineer.com
// http://www.gotvptop.net
//============================================================================

#include "AnchorDefs.h"
#include "AnchorListEntry.h"

#define MAX_ANCHOR_ENTRIES ( 16000 / sizeof( AnchorListEntry ) )

#pragma pack(push) 
#pragma pack(1)

class PktAnnounce;

class AnchorList
{
public:
	AnchorList();

	bool						addEntry( PktAnnounce * pktAnn );
	uint16_t							calculateLength( void );

	uint16_t							m_TotalLen;		// length including this rounded to 16 bytes
	uint16_t							m_EntryCount;
	uint16_t							m_Version;
	EAnchorAction				m_AnchorAction;
	uint32_t							m_u32Flags;
	double						m_Latitude;
	double						m_Longitude;
	char						m_SearchParam[ MAX_ONLINE_DESC_LEN ];
	AnchorListEntry				m_List[ MAX_ANCHOR_ENTRIES ]; // VxConnectIdent 152 bytes * MAX_ANCHOR_ENTRIES
	char						m_Padding[16];
};

#pragma pack(pop)

#endif // ANCHOR_LIST_H
