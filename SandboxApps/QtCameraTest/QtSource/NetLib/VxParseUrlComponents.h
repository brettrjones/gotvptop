#pragma once

#include <config_gotvcore.h>
#include <string>

//============================================================================
bool VxParseUrlComponents(	std::string& strUrl,		// url to parse 
							std::string& strHostName,	// host name
							std::string& strAuth,		// user:pass
							std::string& strProtocol,	// http or https
							int&		 iPort,			// port 
							std::string& strPath
							);
