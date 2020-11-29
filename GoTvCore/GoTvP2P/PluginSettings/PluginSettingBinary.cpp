//============================================================================
// Copyright (C) 2019 Brett R. Jones
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

#include "PluginSettingBinary.h"

#define PLUGIN_SETTING_BINARY_HDR_SIZE 4

//============================================================================
PluginSettingBinary::PluginSettingBinary()
{
    initPluginSettingBinary();
}

//============================================================================
void PluginSettingBinary::initPluginSettingBinary()
{
    m_StorageTotalLen = ( uint16_t * )( &m_StorageData[ 0 ] );
    m_StorageVersion = ( uint8_t * )( &m_StorageData[ 2 ] );
    m_StorageReserved1 = ( uint8_t * )( &m_StorageData[ 3 ] );
    m_StringDataPtr = ( StringListBinary * )( &m_StorageData[ PLUGIN_SETTING_BINARY_HDR_SIZE ] );
    setSettingTotalStorgeLength( 0 );
    *m_StorageVersion = PLUGIN_SETTING_STORAGE_VERSION;
    *m_StorageReserved1 = 0;
    m_StringDataPtr->initStringStorage();
}

//============================================================================
bool PluginSettingBinary::isPluginSettingBinaryValid( void )
{
    int binaryLen = *m_StorageTotalLen;
    return ( *m_StorageVersion == PLUGIN_SETTING_STORAGE_VERSION )
        && ( *m_StorageReserved1 == 0 )
        && ( binaryLen <= MAX_PLUGIN_SETTING_STORAGE_LEN )
        && ( binaryLen >= PLUGIN_SETTING_BINARY_HDR_SIZE );
}
