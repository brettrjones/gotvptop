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
// brett.jones@engineer.com
// http://www.gotvptop.net
//============================================================================

#include "NetworkStateOnlineThroughRelay.h"
#include "NetworkStateMachine.h"
#include <GoTvCore/GoTvP2P/NetServices/NetServicesMgr.h>

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>
#include <GoTvCore/GoTvP2P/Anchor/AnchorDb.h>
#include <GoTvCore/GoTvP2P/Anchor/AnchorList.h>

//============================================================================
NetworkStateOnlineThroughRelay::NetworkStateOnlineThroughRelay( NetworkStateMachine& stateMachine )
: NetworkStateBase( stateMachine )
{
	setNetworkStateType( eNetworkStateTypeOnlineThroughRelay );
}

//============================================================================
void NetworkStateOnlineThroughRelay::enterNetworkState( void )
{
	// force update of ourself in anchor db in case we are being used as anchor
	AnchorList			anchorListIn;
	anchorListIn.addEntry( &m_Engine.getMyPktAnnounce() );
	AnchorList			anchorListOut;

	m_Engine.getNetServicesMgr().getNetServiceAnchor().getAnchorDb().handleAnnounce( anchorListIn, anchorListOut );

	m_Engine.getToGui().toGuiNetworkState( eNetworkStateTypeOnlineThroughRelay );
}

//============================================================================
void NetworkStateOnlineThroughRelay::runNetworkState( void )
{
	//int loopCnt = 0;
	while( false == m_NetworkStateMachine.checkAndHandleNetworkEvents() )
	{
		if( m_PktAnn.requiresRelay() 
			&& ( false == m_NetworkStateMachine.isRelayServiceConnected() ) )
		{
			m_NetworkStateMachine.changeNetworkState( eNetworkStateTypeRelaySearch );
			return;
		}
		//else
		//{
		//	loopCnt++;
		//	if( loopCnt >= ((1000 * 60 * 10) / 2000) )
		//	{
		//		// every 10 minutes refresh UPNP
		//		loopCnt = 0;
		//		m_NetworkStateMachine.startUpnpOpenPort();
		//	}
		//}

		VxSleep( 2000 );
	}
}



