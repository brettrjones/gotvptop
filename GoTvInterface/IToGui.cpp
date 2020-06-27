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
// http://www.nolimitconnect.com
//============================================================================

#include "IToGui.h"

namespace
{
	const char * NetworkStateEnumStrings[] = 
	{ 
		"State Unknown ",
		"Init ",
		"Test ", // eNetworkStateTypeAvail
		"Testing Connection ",
		"Relay Search ",
		"Announce To Network ",
		"Online Direct Connect",
		"Online Through Relay",
		"Get Relay List ",
		"No Internet Connection ",
		"Failed Resolve Host URL ",
		"Max Network State "
	};

	const char * RelayStatusEnumStrings[] = 
	{ 
		"Relay Disconnected ",
		"Relay Connected ",
		"Searching For Relay ",
		"No Relays Listed ",
		"Relay Search ",
		"Relay List Exhausted ",
		"Relay Assume Firewalled ",
		"Relay Assume Can Direct Connect ",
		"Max Relay Status "
	};

	const char * HostStatusEnumStrings[] = 
	{ 
		"Host Status Unknown",
		"Host LogMsg",

		"Host OK",
		"Host Connect Fail",
		"Host Connection Dropped",
		"Host TestComplete",

		"NetService OK",
		"NetService Connect Fail",
		"NetService Connection Dropped",
		"NetService Test Complete",

		"Max Host Status",
	};

	const char * PortOpenStatusEnumStrings[] = 
	{ 
		"Port Open: Status Unknown",
		"Port Open: LogMsg",

		"Port Open: OK",
		"Port Open: Closed",
		"Port Open: Connect Fail",
		"Port Open: Connection Dropped",
		"Port Open: Invalid Response",
		"Port Open: Test Complete",

		"Max Port Open Status",
	};

	const char * RandomConnectStatusEnumStrings[] = 
	{ 
		"Phone Shake: Status Unknown ",
		"Phone Shake: Contact Host Failed ",

		"Phone Shake: Found Friend ",
		"Phone Shake: Empty List ",
		"Phone Shake: Send Request Fail ",
		"Phone Shake: Invalid Response ",
		"Phone Shake: Decrypt Error ",
		"Phone Shake: Search Complete ",

		"Max Phone Shake Status ",
	};

    const char * InternetStatusEnumStrings[] =
    {
        "Internet: No Internet ",
        "Internet: Internet Available ",
        "Internet: No Connection Test Host ",
        "Internet: Connection Test Host Available ",
        "Internet: Assume Direct Connect ",
        "Internet: Can Direct Connect ",
        "Internet: Relay ",
        "Internet: Max Internet Status ",
    };

    const char * NetAvailStatusEnumStrings[] =
    {
        "Net Avail: No Internet ",
        "Net Avail: Host Available ",
        "Net Avail: P2P Available ",
        "Net Avail: Group Host ",
        "Net Avail: Online With Relay ",
        "Net Avail: Online And Can Direct Connect ",
        "Net Avail: Max Net Avail Status ",
    };
}

//! Internet Status as text
const char * DescribeInternetStatus( EInternetStatus internetStatus )
{
    return InternetStatusEnumStrings[ internetStatus ];
}

//! Net Available Status as text
const char * DescribeNetAvailStatus( ENetAvailStatus netAvailStatus )
{
    return NetAvailStatusEnumStrings[ netAvailStatus ];
}

const char * DescribeNetworkState( ENetworkStateType networkStateType )
{
	return NetworkStateEnumStrings[ networkStateType ];
}

const char * DescribeRelayStatus( EMyRelayStatus eRelayStatus )
{
	return RelayStatusEnumStrings[ eRelayStatus ];
}

const char * DescribeHostStatus( EHostTestStatus eHostStatus )
{
	return HostStatusEnumStrings[ eHostStatus ];
}

const char * DescribePortOpenStatus( EIsPortOpenStatus ePortOpenStatus )
{
	return PortOpenStatusEnumStrings[ ePortOpenStatus ];
}

const char * DescribeRandomConnectStatus( ERandomConnectStatus eRandomConnectStatus )
{
	return RandomConnectStatusEnumStrings[ eRandomConnectStatus ];
}
