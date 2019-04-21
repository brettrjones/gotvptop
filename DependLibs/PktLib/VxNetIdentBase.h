#pragma once
//============================================================================
// Copyright (C) 2013 Brett R. Jones
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

#include "VxConnectInfo.h"
#include "VxOnlineStatusFlags.h"

#pragma pack(push) 
#pragma pack(1)

//! implements minimum to uniquely identify user as individual on the network
//! size
//!   176 bytes VxConnectInfo
// +    1 byte  VxOnlineStatusFlags
//	= 177 bytes inherited
// +    1 byte  m_u8Res
// +    1 byte  m_u8OfferCnt
// +    1 byte  m_u8ReplyCnt
// +    4 bytes m_u32TruthCnt;		
// +    4 bytes m_u32DareCnt;					
// +    4 bytes m_u32RejectedCnt;
// =  192 bytes
class VxNetIdentBase : public VxConnectInfo, public VxOnlineStatusFlags
{
public:
	VxNetIdentBase();
	VxNetIdentBase( const VxNetIdentBase &rhs );

	VxNetIdentBase& operator =( const VxNetIdentBase &rhs );
	bool operator ==( const VxNetIdentBase &rhs ) const;
	bool operator != ( const VxNetIdentBase &rhs ) const;

	VxConnectInfo&				getConnectInfo( void )					{ return *this; }

	void						setTruthCount( uint32_t truthCnt );
	uint32_t					getTruthCount( void );
	void						setDareCount( uint32_t dareCnt );
	uint32_t					getDareCount( void );
	void						setRejectedTruthCount( uint16_t rejectCnt );
	uint16_t					getRejectedTruthCount( void );
	void						setRejectedDareCount( uint16_t rejectCnt );
	uint16_t					getRejectedDareCount( void );

	bool						isVxNetIdentMatch( const VxNetIdentBase& oOtherIdent ) const;
	void						useAsRelay( VxNetIdentBase * poRelayIdent );
	void						getProfileUri( std::string& retUri, const char * myIp, const char * webFileName );

protected:
	//=== vars ===//
	uint8_t						m_u8Res;	
	uint8_t						m_u8OfferCnt;							// offer count ( used as part of rating )
	uint8_t						m_u8ReplyCnt;							// reply count ( used as part of rating )
	uint32_t					m_u32TruthCnt;					
	uint32_t					m_u32DareCnt;					
	uint16_t					m_u16RejectedTruthsCnt;				
	uint16_t					m_u16RejectedDaresCnt;		
};

#pragma pack(pop)
