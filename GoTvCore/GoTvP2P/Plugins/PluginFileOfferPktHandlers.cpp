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
// http://www.gotvptop.com
//============================================================================

#include <PktLib/VxCommon.h>

#ifdef USE_PLUGIN_FILE_OFFER

#include "PluginFileOffer.h"
#include "PluginMgr.h"

#include <GoTvInterface/IToGui.h>


//============================================================================
void PluginFileOffer::onPktFileGetReq( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileXferMgr.onPktFileGetReq( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileOffer::onPktFileGetReply( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileXferMgr.onPktFileGetReply( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileOffer::onPktFileSendReq( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileXferMgr.onPktFileSendReq( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileOffer::onPktFileSendReply( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileXferMgr.onPktFileSendReply( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileOffer::onPktFileChunkReq( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileXferMgr.onPktFileChunkReq( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileOffer::onPktFileChunkReply( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileXferMgr.onPktFileChunkReply( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileOffer::onPktFileGetCompleteReq( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileXferMgr.onPktFileGetCompleteReq( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileOffer::onPktFileGetCompleteReply( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileXferMgr.onPktFileGetCompleteReply( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileOffer::onPktFileSendCompleteReq( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileXferMgr.onPktFileSendCompleteReq( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileOffer::onPktFileSendCompleteReply( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileXferMgr.onPktFileSendCompleteReply( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileOffer::onPktFindFileReq( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileXferMgr.onPktFindFileReq( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileOffer::onPktFindFileReply( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileXferMgr.onPktFindFileReply( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileOffer::onPktFileListReq( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileXferMgr.onPktFileListReq( sktBase, pktHdr, netIdent );
}

//============================================================================
void PluginFileOffer::onPktFileListReply( VxSktBase * sktBase, VxPktHdr * pktHdr, VxNetIdent * netIdent )
{
	m_FileXferMgr.onPktFileListReply( sktBase, pktHdr, netIdent );
}

#endif // USE_PLUGIN_FILE_OFFER