#pragma once
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

#include "NetActionBase.h"
#include "NetServiceDefs.h"

#include <GoTvCore/GoTvP2P/Anchor/AnchorDefs.h>

#include <string>

class VxSktBase;
class NetServicesMgr;
class NetServiceHdr;
class VxSktConnectSimple;
class AnchorList;

class NetActionAnnounce : public NetActionBase
{
public:
	NetActionAnnounce( NetServicesMgr& netServicesMgr, std::string& anchorIp, uint16_t u16AnchorPort, EAnchorAction eAnchorAction );
	virtual ~NetActionAnnounce();

	virtual ENetActionType		getNetActionType( void )			{ return eNetActionAnnounce; }
	void						doAction( void );

protected:
	int							buildAnnounceCmd( std::string& strNetCmdHdr, uint16_t clientPort, AnchorList& anchorList, EAnchorAction anchorAction );
	int							getAnnounceData( VxSktConnectSimple * netServConn, char * pRxBuf, int bufLen );
	bool						decryptAnchorList( char * content, int contentDataLen, uint16_t clientPort );

	EAnchorAction				m_eAnchorAction;
};



