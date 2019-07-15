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

#include "VxFileShredderDb.h"
#include "VxThread.h"

class VxFileShredder
{
public:
	VxFileShredder();
	virtual ~VxFileShredder();
	void						initShredder( std::string& dataDirectory );

	void						shredFile( std::string& fileName );

	void						shredFiles( void );
protected:
	void						startThreadIfNotStarted( void );

	//=== vars ===//
	VxFileShredderDb			m_ShredderDb;
	VxMutex						m_ShredListMutex;
	VxThread					m_ShredThread;
	std::vector<std::string>	m_ShredList;
};

VxFileShredder& GetVxFileShredder( void );
