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
#pragma once

#include <GoTvInterface/IDefs.h>
#include <CoreLib/VxGUID.h>
#include <CoreLib/StringListBinary.h>

#include <string>

#define MAX_PLUGIN_SETTING_STORAGE_LEN      (MAX_STRINGLIST_TOTAL_STORAGE + 1000)
#define PLUGIN_SETTING_STORAGE_VERSION 1
#define PLUGIN_SETTING_BINARY_HDR_SIZE 4
#define MAX_PLUGIN_SETTING_DATA_STORAGE ( MAX_PLUGIN_SETTING_STORAGE_LEN - PLUGIN_SETTING_BINARY_HDR_SIZE )

class PluginSetting;

class PluginSettingBinary
{
public:
    PluginSettingBinary();

    uint8_t *                   getStorageHdr( void )                                   { return m_StorageData; }
    uint8_t *                   getStorageData( void )                                  { return &m_StorageData[ PLUGIN_SETTING_BINARY_HDR_SIZE ]; }
    uint16_t                    getStorageVersion( void )                               { return *m_StorageVersion; }
    void                        setSettingTotalStorgeLength( int strStoreLen )          { *m_StorageTotalLen = htons(( uint16_t)(strStoreLen + PLUGIN_SETTING_BINARY_HDR_SIZE)); }
    uint16_t                    getSettingTotalStorgeLength( void )                     { return ntohs(*m_StorageTotalLen); }

    void                        initPluginSettingBinary();
    bool                        isPluginSettingBinaryValid( void );

protected:
    uint16_t *                  m_StorageTotalLen = nullptr;
    uint8_t *                   m_StorageVersion = nullptr;
    uint8_t *                   m_StorageReserved1 = nullptr;

    uint16_t *                  m_StringCount = nullptr;
    StringListBinary *          m_StringDataPtr = nullptr;

    uint8_t                     m_StorageData[ MAX_PLUGIN_SETTING_STORAGE_LEN ];
};