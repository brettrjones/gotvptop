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

#include "NlcPingResponseServer.h"

#include <NetLib/VxSktBase.h>

namespace
{
	void NlcPingResponseCallbackHandler( VxSktBase *  sktBase, void * pvUserCallbackData )
	{
        NlcPingResponseServer * peerMgr = ( NlcPingResponseServer * )pvUserCallbackData;
		if( peerMgr )
		{
			peerMgr->handleTcpSktCallback( sktBase );
		}
	}
}

//============================================================================
NlcPingResponseServer::NlcPingResponseServer( AppLogic& appLogic )
: m_AppLogic( appLogic )
{
	setReceiveCallback( NlcPingResponseCallbackHandler, this );
}

//============================================================================
bool NlcPingResponseServer::startListening( uint16_t u16ListenPort, const char * ip )
{
    if( ip && strlen(ip) )
    {
        LogMsg( LOG_DEBUG, "startListening on port %d ip %d", u16ListenPort, ip );
        return VxServerMgr::startListening( ip, u16ListenPort );
    }
    else
    {
        LogMsg( LOG_DEBUG, "startListening port %d", u16ListenPort );
        return VxServerMgr::startListening( u16ListenPort );
    }
}

//============================================================================
RCODE NlcPingResponseServer::stopListening( void )
{
    if( isListening() )
    {
        LogMsg( LOG_DEBUG, "stopListening on port %d", getListenPort() );
    }
    else
    {
        LogMsg( LOG_DEBUG, "stopListening.. not currently listening" );
    }

   return  VxServerMgr::stopListening();
}


//============================================================================
void NlcPingResponseServer::handleTcpSktCallback( VxSktBase * sktBase )
{
    if( sktBase )
    {
        LogMsg( LOG_DEBUG, "handleTcpSktCallback reason %d", sktBase->getCallbackReason() );
        switch( sktBase->getCallbackReason() )
        {
        case eSktCallbackReasonData:
            handleTcpPingData( sktBase );
            break;
        case eSktCallbackReasonConnectError:
        case eSktCallbackReasonConnected:
        case eSktCallbackReasonClosed:
        case eSktCallbackReasonError:
        case eSktCallbackReasonClosing:
        case eSktCallbackReasonConnecting:
        default:
            break;
        }
    }
    else
    {
        LogMsg( LOG_DEBUG, "handleTcpSktCallback null sktBase");
    }
}

//============================================================================
void NlcPingResponseServer::handleTcpPingData( VxSktBase * sktBase )
{
    if( sktBase )
    {
        LogMsg( LOG_DEBUG, "handleTcpSktCallback data avail %d", sktBase->getRxCallbackUserData());
        switch( sktBase->getCallbackReason() )
        {
        case eSktCallbackReasonData:
            handleTcpPingData( sktBase );
            break;
        case eSktCallbackReasonConnectError:
        case eSktCallbackReasonConnected:
        case eSktCallbackReasonClosed:
        case eSktCallbackReasonError:
        case eSktCallbackReasonClosing:
        case eSktCallbackReasonConnecting:
        default:
            break;
        }
    }
    else
    {
        LogMsg( LOG_DEBUG, "handleTcpSktCallback null sktBase" );
    }
}
