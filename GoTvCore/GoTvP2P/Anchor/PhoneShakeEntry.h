#ifndef PHONE_SHAKE_ENTRY_H
#define PHONE_SHAKE_ENTRY_H

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

#include "AnchorListEntry.h"

class PhoneShakeEntry : public AnchorListEntry
{
public:
	PhoneShakeEntry();
	PhoneShakeEntry( const PhoneShakeEntry& rhs );
	PhoneShakeEntry( const AnchorListEntry& anchorEntry, int64_t postTime );
	~PhoneShakeEntry();

	PhoneShakeEntry& operator=( const PhoneShakeEntry& rhs );

	void						setAnchorListEntry( AnchorListEntry& entry );
	void						setPostTimeMs( int64_t postTimeMs )			{ m_PostTimeMs = postTimeMs; }
	int64_t							getPostTimeMs( void )					{ return m_PostTimeMs; }
	AnchorListEntry *			getAnchorListEntry( void )				{ return (AnchorListEntry *)this; }

private:
	int64_t							m_PostTimeMs;
};

#endif // PHONE_SHAKE_ENTRY_H
