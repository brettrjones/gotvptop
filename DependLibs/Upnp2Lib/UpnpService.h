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

#include "UpnpAction.h"
#include "UpnpStateVariable.h"

#include <string>
#include <vector>

class UpnpDevice;


class UpnpService
{
public:
	UpnpService( UpnpDevice& parentDevice );

	//=== vars ===//
	UpnpDevice&					m_ParentDevice;
	std::vector<UpnpAction>		m_aoActions;
	std::vector<UpnpStateVariable>		m_aoVariables;

	std::string					m_strServiceType;
	std::string					m_strServiceId;
	std::string					m_strSCPDURL;
	std::string					m_strControlURL;
	std::string					m_strEventSubURL;

	//std::string				m_strSubscriptionID;
	//std::string				m_strSubscriptionURL;

};
