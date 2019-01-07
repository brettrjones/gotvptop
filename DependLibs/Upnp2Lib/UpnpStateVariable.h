#pragma once
//============================================================================
// Copyright (C) 2013 Brett R. Jones
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

class UpnpStateVariable
{
public:
	std::string m_strVarName;
	std::string m_strDataType;
	bool m_bSendEvents;
	std::vector<std::string> m_aoAllowedVars;

	//char **AllowedValues;
	UpnpStateVariable()
		: m_bSendEvents( false )
	{
	}

	//! copy operator
	UpnpStateVariable & operator =( const UpnpStateVariable &a )
	{
		// Check for self-assignment!
		if (this != &a)      // Same object?
		{
			// Not same object so copy
			m_strVarName = a.m_strVarName;
			m_strDataType = a.m_strDataType;
			m_bSendEvents = a.m_bSendEvents;
			m_aoAllowedVars.clear();
			for( unsigned int i = 0; i < a.m_aoAllowedVars.size(); ++i )
			{
				m_aoAllowedVars.push_back( a.m_aoAllowedVars[i] );
			}
		}
		return *this;
	}
};