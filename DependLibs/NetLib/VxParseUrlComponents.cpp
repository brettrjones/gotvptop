#include "VxParseUrlComponents.h"

#include <algorithm> // for std::find
#include <stdlib.h>

//============================================================================
bool VxParseUrlComponents(	std::string& strUrl,		// url to parse 
							std::string& strHostName,	// host name
							std::string& strAuth,		// user:pass
							std::string& strProtocol,	// http or https
							int&		 iPort,			// port 
							std::string& strPath
							)
{
	iPort = 80;

	std::string::iterator at;
	std::string::iterator colon;
	std::string::iterator port_pos;

	std::string::iterator start = strUrl.begin();
	// trim beginning white space
	while (start != strUrl.end() && (*start == ' ' || *start == '\t'))
	{
		++start;
	}

	std::string::iterator end = std::find( strUrl.begin(), strUrl.end(), ':' );
	strProtocol.assign(start, end);

	if( strProtocol == "https" ) 
	{
		iPort = 443;
	}

	if( end == strUrl.end() )
	{
		return false;
	}

	++end;
	if( end == strUrl.end() || *end != '/')
	{
		return false;
	}

	++end;
	if (end == strUrl.end() || *end != '/')
	{
		return false;
	}

	++end;
	start = end;

	at = std::find(start, strUrl.end(), '@');
	colon = std::find(start, strUrl.end(), ':');
	end = std::find(start, strUrl.end(), '/');

	if (at != strUrl.end()
		&& colon != strUrl.end()
		&& colon < at
		&& at < end)
	{
		strAuth.assign(start, at);
		start = at;
		++start;
	}

	// this is for IPv6 addresses
	if (start != strUrl.end() && *start == '[')
	{
		port_pos = std::find(start, strUrl.end(), ']');
		if (port_pos == strUrl.end())
		{
			return false;
		}
		port_pos = std::find(port_pos, strUrl.end(), ':');
	}
	else
	{
		port_pos = std::find(start, strUrl.end(), ':');
	}

	if (port_pos < end)
	{
		strHostName.assign( start, port_pos );
		++port_pos;
		iPort = atoi(std::string(port_pos, end).c_str());
	}
	else
	{
		strHostName.assign(start, end);
	}

	if( end != strUrl.end() )
	{
		strPath.assign( end, strUrl.end() );
	}

	return true;
}
