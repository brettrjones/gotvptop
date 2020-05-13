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

#include "NlcPingSend.h"

#include <CoreLib/VxParse.h>
#include <NetLib/VxSktUtil.h>
#include <NetLib/VxPeerMgr.h>
#include <NetLib/VxSktConnectSimple.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _MSC_VER
# pragma warning(disable: 4355) //'this' : used in base member initializer list
#endif //_MSC_VER

namespace
{
	//============================================================================
    void * IsPortOpenTestThreadFunc( void * pvContext )
	{
		VxThread * poThread = (VxThread *)pvContext;
		poThread->setIsThreadRunning( true );
        NlcPingSend * anchorTest = ( NlcPingSend *)poThread->getThreadUserParam();
        if( anchorTest && false == poThread->isAborted() )
		{
			//anchorTest->doIsPortOpenTest();
		}

		poThread->threadAboutToExit();
        return nullptr;
	}
}

//============================================================================
NlcPingSend::NlcPingSend( AppLogic& appLogic )
: m_AppLogic( appLogic )
{
}

//============================================================================
void NlcPingSend::sendTestLog( const char * msg, ... )
{
	char as8Buf[ 1024 ];
	va_list argList;
	va_start( argList, msg );
	vsnprintf( as8Buf, sizeof( as8Buf ), msg, argList );
	as8Buf[sizeof( as8Buf ) - 1] = 0;
	va_end( argList );
	//IToGui::getToGui().toGuiIsPortOpenStatus( eIsPortOpenStatusLogMsg, as8Buf );
}

