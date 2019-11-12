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

#include "PluginSetting.h"
#include "PluginSettingBinary.h"

#include <CoreLib/StringListBinary.h>
#include <CoreLib/VxDebug.h>

#define PLUGIN_SETTINGS_STRING_COUNT 5

//============================================================================
bool PluginSetting::toBinary( PluginSettingBinary& binarySetting )
{
    bool result = false;
    binarySetting.initPluginSettingBinary();
    uint8_t * storageData = binarySetting.getStorageData();

    int totalLen = sizeof( PluginSettingHdr );
    PluginSettingHdr * settingHdr = dynamic_cast< PluginSettingHdr * >( this );
    if( settingHdr )
    {
        memcpy( storageData, settingHdr, sizeof( PluginSettingHdr ) );
        storageData += sizeof( PluginSettingHdr );
        StringListBinary * strBinaryList = ( StringListBinary * )storageData;
        strBinaryList->initStringStorage();

        std::vector<std::string> stringList;
        if( getStringList( stringList ) )
        {
            if( strBinaryList->addStrings( stringList ) )
            {
                totalLen += strBinaryList->getStringStorgeLength();
                binarySetting.setSettingTotalStorgeLength( totalLen );
                result = true;
            }
            else
            {
                LogMsg( LOG_WARNING, "PluginSetting::toBinary failed addStrings" );
            }
        }
        else
        {
            LogMsg( LOG_WARNING, "PluginSetting::toBinary failed getStringList" );
        }
    }
    else
    {
        LogMsg( LOG_WARNING, "PluginSetting::toBinary failed cast to PluginSettingHdr" );
    }


    return result;
}

//============================================================================
bool PluginSetting::fromBinary( PluginSettingBinary& binarySetting )
{
    bool result = binarySetting.isPluginSettingBinaryValid();
    if( result )
    {
        uint8_t * storageData = binarySetting.getStorageData();
        PluginSettingHdr * settingHdr = dynamic_cast< PluginSettingHdr * >( this );
        if( settingHdr )
        {
            memcpy( settingHdr, storageData, sizeof( PluginSettingHdr ) );
            storageData += sizeof( PluginSettingHdr );
            StringListBinary * strBinaryList = ( StringListBinary * )storageData;
            if( strBinaryList->isStringStorageValid() )
            {
                std::vector<std::string> stringList;
                if( strBinaryList->getStrings( stringList ) )
                {
                    if( PLUGIN_SETTINGS_STRING_COUNT == stringList.size() )
                    {
                        if( strBinaryList->addStrings( stringList ) )
                        {
                            setStringList( stringList );
                            result = true;
                        }
                    }
                    else
                    {
                        LogMsg( LOG_WARNING, "PluginSetting::toBinary invalid number of strings %d", stringList.size() );
                    }
                }
                else
                {
                    LogMsg( LOG_WARNING, "PluginSetting::toBinary failed getStringList" );
                }
            }
            else
            {
                LogMsg( LOG_WARNING, "PluginSetting::fromBinary invalid string storage" );
            }
        }
        else
        {
            LogMsg( LOG_WARNING, "PluginSetting::fromBinary failed cast to PluginSettingHdr" );
        }
    }

    return result;
}

//============================================================================
bool PluginSetting::setStringList( std::vector<std::string>& stringList )
{
    bool result = false;
    if( PLUGIN_SETTINGS_STRING_COUNT == stringList.size() )
    {
        m_PluginTitle = stringList[ 0 ];
        m_PluginDesc = stringList[ 1 ];
        m_SecondaryPluginTitle = stringList[ 2 ];
        m_SecondaryPluginDesc = stringList[ 3 ];
        m_SecondaryUrl = stringList[ 4 ];
        result = true;
    }

    return result;
}

//============================================================================
bool PluginSetting::getStringList( std::vector<std::string>& stringList )
{
    stringList.push_back( m_PluginTitle );
    stringList.push_back( m_PluginDesc );
    stringList.push_back( m_SecondaryPluginTitle );
    stringList.push_back( m_SecondaryPluginDesc );
    stringList.push_back( m_SecondaryUrl );

    return true;
}
