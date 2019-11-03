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
// bjones.engineer@gmail.com
// http://www.nolimitconnect.com
//============================================================================

#include "VxSktCrypto.h"
#include "VxSktBase.h"
#include "VxSktConnectSimple.h"

#include <PktLib/VxConnectId.h>

#include <CoreLib/VxParse.h>
#include <CoreLib/VxGlobals.h>
#include <CoreLib/VxGlobals.h>

//=================================================================
// Key generation methods
//=================================================================
static unsigned char g_au8RandomData[ 256 ] =
{
	#include "VxSktRandomData.h"
};

//============================================================================
unsigned char * GetVxSktRandData( int iRandDataIdx )
{
	return &g_au8RandomData[ iRandDataIdx ];
}

//============================================================================
//! generate key from net identity and connection data and place int sockets m_RxKey and initialize its crypto
RCODE GenerateRxConnectionKey(	VxSktBase *				sktBase,			
								VxConnectId *			poConnectId,		
								const char *			networkName )
								
{
	RCODE rc = 0;
	sktBase->lockCryptoAccess();
	if( false == sktBase->m_RxKey.isKeySet() )
	{
		rc = GenerateConnectionKey(	&sktBase->m_RxKey, poConnectId, sktBase->getCryptoKeyPort(), networkName );
		if( 0 == rc )
		{
			sktBase->m_RxCrypto.importKey( &sktBase->m_RxKey );
		}

		vx_assert( 0 == rc );
	}

	sktBase->unlockCryptoAccess();
	return rc;
}

//============================================================================
//! generate key from net identity and connection data and place int sockets m_TxKey and initialize its crypto
RCODE GenerateTxConnectionKey(	VxSktBase *			sktBase,			
								VxConnectId *		poConnectId,		
								const char *		networkName )
{
	RCODE rc = 0;
	sktBase->lockCryptoAccess();
	if( false == sktBase->m_TxKey.isKeySet() )
	{
		rc = GenerateConnectionKey(	&sktBase->m_TxKey, poConnectId, sktBase->getCryptoKeyPort(), networkName );
		if( 0 == rc )
		{
			sktBase->m_TxCrypto.importKey( &sktBase->m_TxKey );
		}
		
		vx_assert( 0 == rc );
	}

	sktBase->unlockCryptoAccess();
	return rc;
}
