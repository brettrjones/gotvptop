#pragma once
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

#include "HostListInfo.h"

#include <NetLib/VxFileXferInfo.h>

#include <vector>

class VxSktBase;
class VxNetIdent;
class P2PEngine;

class HostListXferSession
{
public:
	HostListXferSession( P2PEngine& engine );
	HostListXferSession( P2PEngine& engine, VxSktBase * sktBase, VxNetIdent * netIdent );
	HostListXferSession( P2PEngine& engine, VxGUID& lclSessionId, VxSktBase * sktBase, VxNetIdent * netIdent );
	virtual ~HostListXferSession();

	void						setIdent( VxNetIdent * ident )				{ m_Ident = ident; }
	VxNetIdent *				getIdent( void )							{ return m_Ident; }

	void						setHostListInfo( HostListInfo& assetInfo )	{ m_HostListInfo = assetInfo; }
	HostListInfo&				getHostListInfo( void )						{ return m_HostListInfo; }

	void						setSkt( VxSktBase * skt )					{ m_Skt = skt; }
	VxSktBase *					getSkt( void )								{ return m_Skt; }

	void						setLclSessionId( VxGUID& lclId )			{ m_FileXferInfo.setLclSessionId( lclId ); }
	VxGUID&						getLclSessionId( void )						{ return m_FileXferInfo.getLclSessionId(); }
	void						setRmtSessionId( VxGUID& rmtId )			{ m_FileXferInfo.setRmtSessionId( rmtId ); }
	VxGUID&						getRmtSessionId( void )						{ return m_FileXferInfo.getRmtSessionId(); }

	void						setFileHashId( uint8_t * fileHashId )		{ m_FileXferInfo.setFileHashId( fileHashId ); }
	void						setFileHashId( VxSha1Hash& fileHashId )		{ m_FileXferInfo.setFileHashId( fileHashId ); }
	VxSha1Hash&					getFileHashId( void )						{ return m_FileXferInfo.getFileHashId(); }

	VxFileXferInfo&				getXferInfo( void )							{ return m_FileXferInfo; }
	void						setXferDirection( EXferDirection dir )		{ m_FileXferInfo.setXferDirection( dir ); }
	EXferDirection				getXferDirection( void )					{ return m_FileXferInfo.getXferDirection(); }

	void						reset( void );
	bool						isXferingFile( void );

	void						setErrorCode( RCODE error )						{ if( error ) m_Error = error; } 
	RCODE						getErrorCode( void )							{ return m_Error; }
	void						clearErrorCode( void )							{ m_Error = 0; }

	void						setHostListStateSendBegin( void );
	void						setHostListStateSendProgress( int progress );
	void						setHostListStateSendFail( void );
	void						setHostListStateSendCanceled( void );
	void						setHostListStateSendSuccess( void );

	//=== vars ===//
protected:
	P2PEngine&					m_Engine; 
	VxFileXferInfo				m_FileXferInfo;		// file being transmitted
	int							m_iPercentComplete;
	VxSktBase *					m_Skt;
	VxNetIdent *				m_Ident;
	uint32_t					m_Error;
	HostListInfo				m_HostListInfo;

private:
	void						initLclSessionId( void );
};
