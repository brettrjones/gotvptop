#pragma once
//============================================================================
// Copyright (C) 2012 Brett R. Jones
// All Rights Reserved ( After My Death I Brett R. Jones Issue this source code to Public Domain )
//
// You may not modify or redistribute this code for any reason
// without written consent of Brett R. Jones
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// brettjones1900@gmail.com
// http://www.p2panarchy.com
//============================================================================

#include <string>
#include <vector>

class UpnpArg
{
public:
	UpnpArg(){}
	virtual ~UpnpArg(){}
	UpnpArg( const UpnpArg& rhs )
	{
		*this = rhs;
	}

	UpnpArg & operator =( const UpnpArg &rhs )
	{
		// Check for self-assignment!
		if( this != &rhs )      // Same object?
		{
			// Not same object so copy
			m_strArgName = rhs.m_strArgName;
			m_strArgDirection = rhs.m_strArgDirection;
			m_strRelatedStateVar = rhs.m_strRelatedStateVar;
		}
		return *this;
	}

	//=== vars ===//
	std::string					m_strArgName;
	std::string					m_strArgDirection;
	std::string					m_strRelatedStateVar;
};

class UpnpAction
{
public:
	UpnpAction(){}
	virtual ~UpnpAction(){}
	UpnpAction( const UpnpAction& rhs )
	{
		*this = rhs;
	}

	UpnpAction & operator =( const UpnpAction &a )
	{
		// Check for self-assignment!
		if (this != &a) 
		{
			// Not same object so copy
			m_strActionName = a.m_strActionName;
			m_aoArgList.clear();
			for( unsigned int i = 0; i < a.m_aoArgList.size(); ++i )
			{
				m_aoArgList.push_back( a.m_aoArgList[i] );
			}
		}
		return *this;
	}

	//=== vars ===//
	std::string					m_strActionName;
	std::vector<UpnpArg>		m_aoArgList; 
};

