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
// bjones.engineer@gmail.com
// http://www.gotvptop.com
//============================================================================

#include "AnchorList.h"

#include <PktLib/PktAnnounce.h>
#include <CoreLib/VxMacros.h>

#include <memory.h>
#include <string.h>

//============================================================================
AnchorList::AnchorList()
: m_TotalLen( 0 )
, m_EntryCount( 0 )
, m_Version( 1 )
, m_AnchorAction( eAnchorActionAnnounce )
, m_u32Flags( 0 )
, m_Latitude( 0 )
, m_Longitude( 0 )
{
}

//============================================================================
bool AnchorList::addEntry( PktAnnounce * pktAnn )
{
	if( MAX_ANCHOR_ENTRIES <= m_EntryCount )
	{
		LogMsg( LOG_ERROR, "ERROR AnchorList::addEntry: list is full %d\n", m_EntryCount );
		return false;
	}

	VxConnectIdent& baseInfo = *pktAnn;
	AnchorListEntry * entry = &m_List[m_EntryCount];
	memcpy( &entry->getConnectIdent(), &baseInfo, sizeof( VxConnectIdent ) );	
	m_EntryCount++;
	return true;
}

//============================================================================
uint16_t AnchorList::calculateLength( void )
{
	m_TotalLen = ROUND_TO_16BYTE_BOUNDRY((sizeof(AnchorList) - (sizeof(m_List) + sizeof(m_Padding))) + (m_EntryCount * sizeof(AnchorListEntry)));
	return m_TotalLen;
}
