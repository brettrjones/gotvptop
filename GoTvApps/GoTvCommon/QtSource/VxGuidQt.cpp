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

#include "VxGuidQt.h"

#include <QWidget>

//============================================================================
VxGuidQt::VxGuidQt(QWidget *parent)
: QObject(parent)
, VxGUID()
{
    setObjectName( "VxGuidQt" );
}

//============================================================================
VxGuidQt::VxGuidQt( const VxGUID &rhs )
: QObject()
{
	*this = rhs;
}

//============================================================================
VxGuidQt::VxGuidQt( const VxGuidQt& rhs )
: QObject()
, VxGUID()
{
	*this = rhs;
}

//============================================================================
VxGuidQt::VxGuidQt( uint64_t u64HiPart, uint64_t u64LoPart )
: QObject()
{
	VxGuidQt::setVxGUID( u64HiPart, u64LoPart );
}

//============================================================================
VxGuidQt::~VxGuidQt()
{
}

//============================================================================
VxGuidQt& VxGuidQt::operator =( const VxGUID& rhs )
{
	m_u64HiPart = rhs.getVxGUIDHiPart();
	m_u64LoPart = rhs.getVxGUIDLoPart();

	return *this;
}

//============================================================================
VxGuidQt& VxGuidQt::operator =( const VxGuidQt &rhs )
{
	if( this != &rhs )   
	{
		m_u64HiPart = rhs.getVxGUIDHiPart();
		m_u64LoPart = rhs.getVxGUIDLoPart();
	}

	return *this;
}

//============================================================================
bool VxGuidQt::operator == ( const VxGuidQt &a ) const
{
	return ((m_u64LoPart == a.m_u64LoPart ) && (m_u64HiPart == a.m_u64HiPart ));
}

//============================================================================
bool VxGuidQt::operator == ( const VxGUID& a ) const
{
	return ((m_u64LoPart == a.getVxGUIDLoPart() ) && (m_u64HiPart == a.getVxGUIDHiPart() ));
}

//============================================================================
bool VxGuidQt::operator != ( const VxGuidQt &a ) const
{
	return !(*this == a);
}

//============================================================================
bool VxGuidQt::operator < ( const VxGuidQt &b ) const
{
	if( m_u64HiPart < b.m_u64HiPart )
		return true;
	if( m_u64HiPart == b.m_u64HiPart )
		if( m_u64LoPart < b.m_u64LoPart )
			return true;
	return false;
}

//============================================================================
bool VxGuidQt::operator <= ( const VxGuidQt &b ) const
{
	if( *this == b )
	{
		return true;
	}

	if( m_u64HiPart < b.m_u64HiPart )
		return true;
	if( m_u64HiPart == b.m_u64HiPart )
		if( m_u64LoPart < b.m_u64LoPart )
			return true;

	return false;
}

//============================================================================
bool VxGuidQt::operator > ( const VxGuidQt &b ) const
{
	if( m_u64HiPart > b.m_u64HiPart )
		return true;
	if( m_u64HiPart == b.m_u64HiPart )
		if( m_u64LoPart > b.m_u64LoPart )
			return true;
	return false;
}

//============================================================================
bool VxGuidQt::operator >= ( const VxGuidQt &b ) const
{
	if( *this == b )
	{
		return true;
	}

	if( m_u64HiPart > b.m_u64HiPart )
		return true;
	if( m_u64HiPart == b.m_u64HiPart )
		if( m_u64LoPart > b.m_u64LoPart )
			return true;

	return false;
}
