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

#include <GoTvCore/GoTvP2P/Anchor/AnchorDb.h>
#include <CoreLib/VxDefs.h>

class NetServicesMgr;
class NetServiceUtils;
class VxSktBase;
class VxGUID;
class P2PEngine;
class NetServiceHdr;

class NetServiceAnchor
{
public:
	NetServiceAnchor( P2PEngine& engine, NetServicesMgr& netServicesMgr, NetServiceUtils& netServiceUtils );
	virtual ~NetServiceAnchor();

	void						netServiceAnchorStartup( void );
	void						netServiceAnchorShutdown( void );

	AnchorDb&					getAnchorDb( void )						{ return m_AnchorDb; }

	RCODE						handleNetCmdAnchorReq( VxSktBase * sktBase, NetServiceHdr& netServiceHdr );
	RCODE						handleNetCmdAnchorReply( VxSktBase * sktBase, NetServiceHdr& netServiceHdr );

protected:
	bool						verifyAnchorList( AnchorList * anchorList, int contentDataLen );

	P2PEngine&					m_Engine;
	NetServicesMgr&				m_NetServicesMgr;
	NetServiceUtils&			m_NetServiceUtils;
	AnchorDb					m_AnchorDb;

private:
	NetServiceAnchor(); // don't allow default constructor
	NetServiceAnchor(const NetServiceAnchor&); // don't allow copy constructor
};
