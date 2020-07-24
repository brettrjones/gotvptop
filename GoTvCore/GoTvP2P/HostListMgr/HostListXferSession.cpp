//============================================================================
// Copyright (C) 2010 Brett R. Jones
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

#include <config_gotvcore.h>
#include "HostListXferSession.h"
#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>
#include <GoTvInterface/IToGui.h>

#include <CoreLib/VxGlobals.h>

//============================================================================
HostListXferSession::HostListXferSession( P2PEngine& engine )
: m_Engine( engine )
, m_FileXferInfo()
, m_iPercentComplete(0)
, m_Skt(NULL)
, m_Ident(NULL)
, m_Error( 0 )
{
	initLclSessionId();
}

//============================================================================
HostListXferSession::HostListXferSession( P2PEngine& engine, VxSktBase * sktBase, VxNetIdent * netIdent )
: m_Engine( engine )
, m_FileXferInfo()
, m_iPercentComplete(0)
, m_Skt( sktBase )
, m_Ident( netIdent )
, m_Error( 0 )
{
	initLclSessionId();
}

//============================================================================
HostListXferSession::HostListXferSession( P2PEngine& engine, VxGUID& lclSessionId, VxSktBase * sktBase, VxNetIdent * netIdent )
: m_Engine( engine )
, m_FileXferInfo( lclSessionId )
, m_iPercentComplete(0)
, m_Skt( sktBase )
, m_Ident( netIdent )
, m_Error( 0 )
{
	initLclSessionId();
}

//============================================================================
HostListXferSession::~HostListXferSession()
{
}

//============================================================================
void HostListXferSession::reset( void )
{
	m_iPercentComplete = 0;
}

//============================================================================
void HostListXferSession::initLclSessionId( void )
{
	if( false == m_FileXferInfo.getLclSessionId().isVxGUIDValid() )
	{
		m_FileXferInfo.getLclSessionId().initializeWithNewVxGUID();
	}
}

//============================================================================
bool HostListXferSession::isXferingFile( void )
{
	if( m_FileXferInfo.m_hFile )
	{
		return true;
	}

	return false;
}

//============================================================================
void HostListXferSession::setHostListStateSendBegin( void )
{
	if( eXferDirectionRx == getXferDirection() )
	{
		m_HostListInfo.setHostListSendState( eHostListSendStateRxProgress );
		m_Engine.getToGui().toGuiHostListAction( eHostListActionRxBegin, m_HostListInfo.getHostListUniqueId(), 0 );
	}
	else
	{
		m_HostListInfo.setHostListSendState( eHostListSendStateTxProgress );
		m_Engine.getToGui().toGuiHostListAction( eHostListActionTxBegin, m_HostListInfo.getHostListUniqueId(), 0 );
	}
}

//============================================================================
void HostListXferSession::setHostListStateSendCanceled( void )
{
	if( eXferDirectionRx == getXferDirection() )
	{
		m_HostListInfo.setHostListSendState( eHostListSendStateRxFail );
		m_Engine.getToGui().toGuiHostListAction( eHostListActionRxCancel, m_HostListInfo.getHostListUniqueId(), 0 );
	}
	else
	{
		m_HostListInfo.setHostListSendState( eHostListSendStateTxFail );
		m_Engine.getToGui().toGuiHostListAction( eHostListActionTxCancel, m_HostListInfo.getHostListUniqueId(), 0 );
	}
}

//============================================================================
void HostListXferSession::setHostListStateSendFail( void )
{
	if( eXferDirectionRx == getXferDirection() )
	{
		m_HostListInfo.setHostListSendState( eHostListSendStateRxFail );
		m_Engine.getToGui().toGuiHostListAction( eHostListActionRxError, m_HostListInfo.getHostListUniqueId(), 0 );
	}
	else
	{
		m_HostListInfo.setHostListSendState( eHostListSendStateTxFail );
		m_Engine.getToGui().toGuiHostListAction( eHostListActionTxError, m_HostListInfo.getHostListUniqueId(), 0 );
	}
}

//============================================================================
void HostListXferSession::setHostListStateSendProgress( int progress )
{
	if( eXferDirectionRx == getXferDirection() )
	{
		m_HostListInfo.setHostListSendState( eHostListSendStateRxProgress );
		m_Engine.getToGui().toGuiHostListAction( eHostListActionRxProgress, m_HostListInfo.getHostListUniqueId(), progress );
	}
	else
	{
		m_HostListInfo.setHostListSendState( eHostListSendStateTxProgress );
		m_Engine.getToGui().toGuiHostListAction( eHostListActionTxProgress, m_HostListInfo.getHostListUniqueId(), progress );
	}
}

//============================================================================
void HostListXferSession::setHostListStateSendSuccess( void )
{
	if( eXferDirectionRx == getXferDirection() )
	{
		m_HostListInfo.setHostListSendState( eHostListSendStateRxSuccess );
		m_Engine.getToGui().toGuiHostListAction( eHostListActionRxSuccess, m_HostListInfo.getHostListUniqueId(), 100 );
		m_Engine.getToGui().toGuiHostListAction( eHostListActionRxNotifyNewMsg, m_HostListInfo.getCreatorId(), 100 );
	}
	else
	{
		m_HostListInfo.setHostListSendState( eHostListSendStateRxSuccess );
		m_Engine.getToGui().toGuiHostListAction( eHostListActionTxSuccess, m_HostListInfo.getHostListUniqueId(), 100 );
	}
}
