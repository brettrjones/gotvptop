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
// http://www.gotvptop.com
//============================================================================


#include <CoreLib/VxGUID.h>
#include <QObject>

class QWidget;
class VxGuidQt : public QObject, public VxGUID
{
	Q_OBJECT
public:
	VxGuidQt(QWidget *parent = 0 );
	VxGuidQt( const VxGUID& rhs );
	VxGuidQt( const VxGuidQt& rhs );
	VxGuidQt( uint64_t u64HiPart, uint64_t u64LoPart );
	virtual ~VxGuidQt();

	VxGuidQt&					operator =( const VxGUID& a );
	VxGuidQt&					operator =( const VxGuidQt& a );
	bool						operator == ( const VxGuidQt& a ) const;
	bool						operator == ( const VxGUID& a ) const;
	bool						operator != ( const VxGuidQt& a ) const;
	bool						operator < ( const VxGuidQt& b ) const;
	bool						operator <= ( const VxGuidQt& b ) const;
	bool						operator > ( const VxGuidQt& b ) const;
	bool						operator >= ( const VxGuidQt& b ) const;
};

