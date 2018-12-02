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
// brett.jones@engineer.com
// http://www.gotvptop.net
//============================================================================

#include <config_gotvcore.h>
#include "AssetXferSession.h"
#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>
#include <GoTvInterface/IToGui.h>

#include <CoreLib/VxGlobals.h>

//============================================================================
AssetXferSession::AssetXferSession( P2PEngine& engine )
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
AssetXferSession::AssetXferSession( P2PEngine& engine, VxSktBase * sktBase, VxNetIdent * netIdent )
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
AssetXferSession::AssetXferSession( P2PEngine& engine, VxGUID& lclSessionId, VxSktBase * sktBase, VxNetIdent * netIdent )
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
AssetXferSession::~AssetXferSession()
{
}

//============================================================================
void AssetXferSession::reset( void )
{
	m_iPercentComplete = 0;
}

//============================================================================
void AssetXferSession::initLclSessionId( void )
{
	if( false == m_FileXferInfo.getLclSessionId().isVxGUIDValid() )
	{
		m_FileXferInfo.getLclSessionId().initializeWithNewVxGUID();
	}
}

//============================================================================
bool AssetXferSession::isXferingFile( void )
{
	if( m_FileXferInfo.m_hFile )
	{
		return true;
	}

	return false;
}

//============================================================================
void AssetXferSession::setAssetStateSendBegin( void )
{
	if( eXferDirectionRx == getXferDirection() )
	{
		m_AssetInfo.setAssetSendState( eAssetSendStateRxProgress );
		m_Engine.getToGuiInterface().toGuiAssetAction( eAssetActionRxBegin, m_AssetInfo.getAssetUniqueId(), 0 );
	}
	else
	{
		m_AssetInfo.setAssetSendState( eAssetSendStateTxProgress );
		m_Engine.getToGuiInterface().toGuiAssetAction( eAssetActionTxBegin, m_AssetInfo.getAssetUniqueId(), 0 );
	}
}

//============================================================================
void AssetXferSession::setAssetStateSendCanceled( void )
{
	if( eXferDirectionRx == getXferDirection() )
	{
		m_AssetInfo.setAssetSendState( eAssetSendStateRxFail );
		m_Engine.getToGuiInterface().toGuiAssetAction( eAssetActionRxCancel, m_AssetInfo.getAssetUniqueId(), 0 );
	}
	else
	{
		m_AssetInfo.setAssetSendState( eAssetSendStateTxFail );
		m_Engine.getToGuiInterface().toGuiAssetAction( eAssetActionTxCancel, m_AssetInfo.getAssetUniqueId(), 0 );
	}
}

//============================================================================
void AssetXferSession::setAssetStateSendFail( void )
{
	if( eXferDirectionRx == getXferDirection() )
	{
		m_AssetInfo.setAssetSendState( eAssetSendStateRxFail );
		m_Engine.getToGuiInterface().toGuiAssetAction( eAssetActionRxError, m_AssetInfo.getAssetUniqueId(), 0 );
	}
	else
	{
		m_AssetInfo.setAssetSendState( eAssetSendStateTxFail );
		m_Engine.getToGuiInterface().toGuiAssetAction( eAssetActionTxError, m_AssetInfo.getAssetUniqueId(), 0 );
	}
}

//============================================================================
void AssetXferSession::setAssetStateSendProgress( int progress )
{
	if( eXferDirectionRx == getXferDirection() )
	{
		m_AssetInfo.setAssetSendState( eAssetSendStateRxProgress );
		m_Engine.getToGuiInterface().toGuiAssetAction( eAssetActionRxProgress, m_AssetInfo.getAssetUniqueId(), progress );
	}
	else
	{
		m_AssetInfo.setAssetSendState( eAssetSendStateTxProgress );
		m_Engine.getToGuiInterface().toGuiAssetAction( eAssetActionTxProgress, m_AssetInfo.getAssetUniqueId(), progress );
	}
}

//============================================================================
void AssetXferSession::setAssetStateSendSuccess( void )
{
	if( eXferDirectionRx == getXferDirection() )
	{
		m_AssetInfo.setAssetSendState( eAssetSendStateRxSuccess );
		m_Engine.getToGuiInterface().toGuiAssetAction( eAssetActionRxSuccess, m_AssetInfo.getAssetUniqueId(), 100 );
		m_Engine.getToGuiInterface().toGuiAssetAction( eAssetActionRxNotifyNewMsg, m_AssetInfo.getCreatorId(), 100 );
	}
	else
	{
		m_AssetInfo.setAssetSendState( eAssetSendStateRxSuccess );
		m_Engine.getToGuiInterface().toGuiAssetAction( eAssetActionTxSuccess, m_AssetInfo.getAssetUniqueId(), 100 );
	}
}
