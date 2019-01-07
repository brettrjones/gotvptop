#include "PhoneShakeEntry.h"

#include <memory.h>

//============================================================================
PhoneShakeEntry::PhoneShakeEntry()
: m_PostTimeMs(0)
{
}

//============================================================================
PhoneShakeEntry::PhoneShakeEntry( const PhoneShakeEntry& rhs )
{
	*this = rhs;
}

//============================================================================
PhoneShakeEntry::PhoneShakeEntry( const AnchorListEntry& anchorEntry, int64_t postTime )
{
	memcpy( this, &anchorEntry, sizeof( AnchorListEntry ) );
	m_PostTimeMs = postTime;
}

//============================================================================
PhoneShakeEntry::~PhoneShakeEntry()
{
}

//============================================================================
PhoneShakeEntry& PhoneShakeEntry::operator=( const PhoneShakeEntry& rhs )
{
	if( this != &rhs )
	{
		memcpy( this, &rhs, sizeof( PhoneShakeEntry ) );
	}

	return *this;
}

//============================================================================
void PhoneShakeEntry::setAnchorListEntry( AnchorListEntry& entry )
{
	memcpy( this, &entry, sizeof( AnchorListEntry ) );
}
