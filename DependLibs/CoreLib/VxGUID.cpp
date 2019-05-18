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
// http://www.gotvptop.net
//============================================================================
#include "config_corelib.h"

#include "VxGUID.h"

#include <CoreLib/VxParse.h>
#include <CoreLib/VxDebug.h>

#include <libcrossguid/guid.h>

#ifdef TARGET_OS_ANDROID
# include "VxJava.h"
#endif //TARGET_OS_ANDROID

//#ifdef TARGET_OS_WINDOWS
//	#include <Rpc.h>
//#else
//	//#ifdef TARGET_OS_ANDROID
//		// android has no uuid.h.. get from java
//        //#include <GoTvInterface/AndroidInterface/NativeToJava.h>
//	//#else
//		#include <uuid/uuid.h>
//	//#endif
//#endif

#include <string.h>
#include <stdio.h>

//============================================================================
VxGUID::VxGUID()
: m_u64HiPart(0)
, m_u64LoPart(0)
{
}

//============================================================================
VxGUID::VxGUID( const VxGUID &rhs )
{
    *this = rhs;
}

//============================================================================
VxGUID::VxGUID( uint64_t u64HiPart, uint64_t u64LoPart )
: m_u64HiPart(u64HiPart)
, m_u64LoPart(u64LoPart)
{
}

//============================================================================
VxGUID & VxGUID::operator =( const VxGUID &rhs )
{
	if( this != &rhs )   
	{
		m_u64HiPart = rhs.m_u64HiPart;
		m_u64LoPart = rhs.m_u64LoPart;
	}

	return *this;
}

//============================================================================
bool VxGUID::operator == ( const VxGUID &a ) const
{
	return ((m_u64LoPart == a.m_u64LoPart ) && (m_u64HiPart == a.m_u64HiPart ));
}

//============================================================================
bool VxGUID::operator != ( const VxGUID &a ) const
{
	return !(*this == a);
}

//============================================================================
bool VxGUID::operator < ( const VxGUID &b ) const
{
	if( m_u64HiPart < b.m_u64HiPart )
		return true;
	if( m_u64HiPart == b.m_u64HiPart )
		if( m_u64LoPart < b.m_u64LoPart )
			return true;
	return false;
}

//============================================================================
bool VxGUID::operator <= ( const VxGUID &b ) const
{
	if( *this == b )
	{
		return true;
	}

	if( m_u64HiPart < b.m_u64HiPart )
		return true;
	if( m_u64HiPart == b.m_u64HiPart )
		if( m_u64LoPart < b.m_u64LoPart )
			return true;

	return false;
}

//============================================================================
bool VxGUID::operator > ( const VxGUID &b ) const
{
	if( m_u64HiPart > b.m_u64HiPart )
		return true;
	if( m_u64HiPart == b.m_u64HiPart )
		if( m_u64LoPart > b.m_u64LoPart )
			return true;
	return false;
}

//============================================================================
bool VxGUID::operator >= ( const VxGUID &b ) const
{
	if( *this == b )
	{
		return true;
	}

	if( m_u64HiPart > b.m_u64HiPart )
		return true;
	if( m_u64HiPart == b.m_u64HiPart )
		if( m_u64LoPart > b.m_u64LoPart )
			return true;

	return false;
}

//============================================================================
// returns 0 if equal else -1 if less or 1 if greater
int VxGUID::compareTo( VxGUID& guid )
{
	if( m_u64HiPart < guid.m_u64HiPart )
		return -1;
	if( m_u64HiPart > guid.m_u64HiPart )
		return 1;
	if( m_u64LoPart < guid.m_u64LoPart )
		return -1;
	if( m_u64LoPart > guid.m_u64LoPart )
		return 1;
	return 0;
}

//============================================================================
// returns true if guids are same value
bool VxGUID::isEqualTo( VxGUID& guid )
{
	return ( ( m_u64LoPart == guid.m_u64LoPart ) && ( m_u64HiPart == guid.m_u64HiPart ) );
}

#include <libcrossguid/guid.h>

//============================================================================
void VxGUID::generateNewVxGUID( VxGUID& retNewGUID )
{
#if 1
    // use library cross guid
#ifdef TARGET_OS_ANDROID
    GuidGenerator guidGen( VxJava::getJavaEnv() );
#else
    GuidGenerator guidGen;
#endif //TARGET_OS_ANDROID

    Guid crossGuid = guidGen.newGuid();
    if( (int)(sizeof( uint64_t ) * 2) <= crossGuid.guidByteCount() )
    {
        std::vector<unsigned char>& guidBytes = crossGuid.getGuidBytes();
        unsigned char * guidData = &guidBytes[0];
        memcpy( &retNewGUID.m_u64HiPart, guidData, sizeof( uint64_t ) );
        guidData +=  sizeof( uint64_t );
        memcpy( &retNewGUID.m_u64LoPart, guidData, sizeof( uint64_t ) );
    }
    else
    {
        LogMsg( LOG_ERROR, "VxGUID::generateNewVxGUID Failed to generate" );
    }
#else
    // custom.. have to link os specific libraries
# ifdef TARGET_OS_WINDOWS
	UuidCreate( (UUID *)&retNewGUID );
# else
	#ifdef TARGET_OS_ANDROID
		// android has no uuid.h.. get from java
		JavaToGuiGenerateGuid( retNewGUID );
	#else
		uuid_t * pUuid = (uuid_t *)&retNewGUID;
        uuid_generate_random( *pUuid );
    #endif
# endif
#endif
}

//============================================================================
VxGUID& VxGUID::nullVxGUID( void )
{
static VxGUID nullGuid;
	return nullGuid;
}

//============================================================================
std::string VxGUID::toGUIDStandardFormatedString( void )
{
#ifdef TARGET_OS_WINDOWS
	unsigned char * str;
	UuidToStringA ( (UUID *)this, &str );
	std::string strFormatedUuid( ( char* )str );
	RpcStringFreeA ( &str );
	return strFormatedUuid;
#else
    #if defined(TARGET_OS_ANDROID) || defined(TARGET_OS_LINUX)
		// format string into something like 79ECEFE6-D91C-457B-B17D-3FEDD63F3F73),
		char formatedStrBuf[37];
		sprintf( formatedStrBuf, "%2.2X%2.2X%2.2X%2.2X-%2.2X%2.2X-%2.2X%2.2X-%2.2X%2.2X%2.2X%2.2X%2.2X%2.2X",
			(unsigned int)((m_u64HiPart >> 56) & 0xff),
			(unsigned int)((m_u64HiPart >> 48) & 0xff),
			(unsigned int)((m_u64HiPart >> 32) & 0xff),
			(unsigned int)((m_u64HiPart >> 24) & 0xff),
			(unsigned int)((m_u64HiPart >> 16) & 0xff),
			(unsigned int)((m_u64HiPart >> 8) & 0xff),
			(unsigned int)((m_u64HiPart ) & 0xff),
			(unsigned int)((m_u64LoPart >> 56) & 0xff),
			(unsigned int)((m_u64LoPart >> 48) & 0xff),
			(unsigned int)((m_u64LoPart >> 32) & 0xff),
			(unsigned int)((m_u64LoPart >> 24) & 0xff),
			(unsigned int)((m_u64LoPart >> 16) & 0xff),
			(unsigned int)((m_u64LoPart >> 8) & 0xff),
			(unsigned int)((m_u64LoPart ) & 0xff) );
		return formatedStrBuf;
	#else
		uuid_t * pUuid = (uuid_t *)this;
		char formatedStrBuf[37];
		uuid_unparse ( *pUuid, formatedStrBuf );
		return formatedStrBuf;
	#endif // TARGET_OS_ANDROID
#endif
}

//============================================================================
void VxGUID::initializeWithNewVxGUID( void )
{
	generateNewVxGUID( *this );
}

//============================================================================
bool VxGUID::isVxGUIDValid() const 
{ 
	return ((m_u64LoPart != 0 ) || (m_u64HiPart != 0 ));
}

//============================================================================
void VxGUID::toVxGUIDHexString( std::string& strRetId )	
{ 
	char lclBuf[ 64 ];
	sprintf( lclBuf, "%llX%llX", m_u64HiPart, m_u64LoPart );
	strRetId = lclBuf; 
} 

//============================================================================
std::string VxGUID::toVxGUIDHexString( void )	
{ 
	char lclBuf[ 64 ];
	sprintf( lclBuf, "%llX%llX", m_u64HiPart, m_u64LoPart );
	return lclBuf; 
} 

//============================================================================
static uint8_t charToHex( char cVal )
{
	if( cVal >= '0' && cVal <= '9' )
	{
		return cVal & 0x0f;
	}
	else if( cVal >= 'A' && cVal <= 'F' )
	{
		return cVal - 55;
	}
	else if( cVal >= 'a' && cVal <= 'f' )
	{
		return cVal - 87;
	}
	else
	{
		LogMsg( LOG_ERROR, "VxGUID::charToHex invalid char 0x%2.2x\n", cVal );
		return 0;
	}
}

//============================================================================
//! set online id by converting hex string into U128
bool VxGUID::fromVxGUIDHexString( const char * pHexString )
{
	if( false == isVxGUIDHexStringValid( pHexString ) )
	{
		return false;
	}

	uint8_t u8Byte;
	uint64_t u64Part = 0;
	for( int i = 0; i < 8; i++ )
	{
		u64Part = u64Part << 8;
		u8Byte = (charToHex(*pHexString))<<4;
		pHexString++;
		u8Byte |= charToHex(*pHexString);
		pHexString++;
		u64Part |= u8Byte;
	}

	m_u64HiPart = u64Part;
	u64Part = 0;
	for( int i = 0; i < 8; i++ )
	{
		u64Part = u64Part << 8;
		u8Byte = (charToHex(*pHexString))<<4;
		pHexString++;
		u8Byte |= charToHex(*pHexString);
		pHexString++;
		u64Part |= u8Byte;
	}

	m_u64LoPart = u64Part;
	return true;
}

//============================================================================
bool VxGUID::isVxGUIDHexStringValid( const char * pId )
{
	if( NULL == pId )
	{
		return false;
	}

	for( int i = 0; i < 32; i++ )
	{
		char ch = pId[ i ];
		if( false == ( (('0' <= ch) && ('9' >= ch)) 
					|| (('a' <= ch) && ('f' >= ch)) 
					|| (('A' <= ch) && ('F' >= ch)) ) )
		{
			return false;
		}
	}

	return true;
}


//============================================================================
//! get low part of online id
uint64_t		VxGUID::getVxGUIDLoPart() const								{ return m_u64LoPart; }

//============================================================================
//! get high part of online id
uint64_t		VxGUID::getVxGUIDHiPart() const								{ return m_u64HiPart; }

//============================================================================
//! return users online id
VxGUID&	VxGUID::getVxGUID( void )								{ return *this; }

//============================================================================
//! return users online id as string
void VxGUID::getVxGUID( std::string& strRetId )			{ return this->toVxGUIDHexString( strRetId ); }

//============================================================================
//! set users online id
void VxGUID::setVxGUID( VxGUID& oId )					{ *this = oId; }

//============================================================================
//! set users online id
void VxGUID::setVxGUID( uint64_t& u64HiPart, uint64_t& u64LoPart )	{ m_u64HiPart = u64HiPart; m_u64LoPart = u64LoPart; }

//============================================================================
//! get users online as 2 parts
void VxGUID::getVxGUID( uint64_t& u64HiPart, uint64_t& u64LoPart )	{  u64HiPart = m_u64HiPart; u64LoPart = m_u64LoPart; }

//============================================================================
void VxGUID::setVxGUID( const char * pId )					{ this->fromVxGUIDHexString( pId ); }

//============================================================================
void VxGUID::clearVxGUID( void )
{
	m_u64LoPart = 0;
	m_u64HiPart = 0;
}

//============================================================================
std::string	VxGUID::describeVxGUID( void )
{
	std::string strId;
	StdStringFormat( strId, " 0x%llX 0x%llX ", m_u64HiPart, m_u64LoPart);
	return strId;
}
