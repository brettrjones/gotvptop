#pragma once
//============================================================================
// Copyright (C) 2020 Brett R. Jones
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

#include <inttypes.h>
#include <string>
#include <vector>

// defines for blobs
#define BLOB_PLUGIN_SETTING_MAX_STORAGE_LEN 4096
#define BLOB_PLUGIN_SETTING_STORAGE_VERSION 1

class VxGUID;

class BinaryBlob
{
public:
    BinaryBlob() = default;
    BinaryBlob( int dataLen ){ if( dataLen ) m_BlobData = new uint8_t[ dataLen ]; m_MaxDataLen = dataLen; }
    ~BinaryBlob() { if( m_OwnBlob ) delete m_BlobData; }

    bool                        createStorage( int maxStorageLen, bool useNetworkOrder = false );

    void                        setBlobLen( int len ) { m_BlobLen = len; }
    int                         getBlobLen( void ) { return m_BlobLen; }

    bool                        setBlobData( uint8_t* blob, int len, bool deleteOnDestruct, bool copyTheData );                     
    uint8_t*                    getBlobData( void ) { return m_BlobData; }

    void                        setUseNetworkOrder( bool useNetOrder ) { m_UseNetworkOrder = useNetOrder; }
    bool                        getUseNetworkOrder( void ) { return m_UseNetworkOrder; }

    void                        resetWrite() { m_DataIdx = 0; m_PastEnd = 0; }
    bool                        haveRoom( size_t valSize );
    bool                        incDataWrite( size_t valSize );

    void                        resetRead() { m_DataIdx = m_BlobLen; m_PastEnd = 0; }
    bool                        haveData( size_t valSize );
    bool                        incDataRead( size_t valSize );

    bool                        isPastEnd() { return m_PastEnd; }

    //! set value 
    bool                        setValue( bool& bValue );
    bool                        setValue( int8_t& s8Value );
    bool                        setValue( uint8_t& u8Value );
    bool                        setValue( int16_t& s16Value );
    bool                        setValue( uint16_t& u16Value );
    bool                        setValue( int32_t& s32Value );
    bool                        setValue( uint32_t& u32Value );
    bool                        setValue( int64_t& s64Value );
    bool                        setValue( uint64_t& u64Value );
    bool                        setValue( float& f32Value );
    bool                        setValue( double& f64Value );
    bool                        setValue( std::string& strValue );
    bool                        setValue( const char * pRetBuf, int iBufLen );
    bool                        setValue( std::vector<std::string>& aoStrValues );
    bool                        setValue( void * pvRetBuf, int iBufLen );
    bool                        setValue( VxGUID& guid );

    //! get value 
    bool                        getValue( bool& bValue );
    bool                        getValue( int8_t& s8Value );
    bool                        getValue( uint8_t& u8Value );
    bool                        getValue( int16_t& s16Value );
    bool                        getValue( uint16_t& u16Value );
    bool                        getValue( int32_t& s32Value );
    bool                        getValue( uint32_t& u32Value );
    bool                        getValue( int64_t& s64Value );
    bool                        getValue( uint64_t& u64Value );
    bool                        getValue( float& f32Value );
    bool                        getValue( double& f64Value );
    bool                        getValue( std::string& strValue );
    bool                        getValue( char * pRetBuf, int& iBufLen );
    bool                        getValue( std::vector<std::string>& aoStrValues );
    bool                        getValue( void * pvRetBuf, int& iBufLen );
    bool                        getValue( VxGUID& guid );

protected:
    //=== vars ===//
    bool                        m_UseNetworkOrder{ false };

    bool                        m_OwnBlob{ false };
    int                         m_BlobLen{ 0 };
    uint8_t*                    m_BlobData{ nullptr };

    int                         m_MaxDataLen{ 0 };
    int                         m_DataIdx{ 0 };
    bool                        m_PastEnd{ false };
};