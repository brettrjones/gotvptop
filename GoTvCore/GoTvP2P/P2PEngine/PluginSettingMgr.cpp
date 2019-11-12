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

#include "PluginSettingMgr.h"
#include "PluginSettingDb.h"
#include <CoreLib/VxGlobals.h>


//============================================================================
PluginSettingMgr& GetPluginSettingMgrInstance()
{
    static PluginSettingMgr g_PluginSettingMgr;
    return g_PluginSettingMgr;
}

//============================================================================
PluginSettingMgr::PluginSettingMgr()
    : m_PluginSettingDb( GetPluginSettingDbInstance() )
{
}

//============================================================================
bool PluginSettingMgr::initPluginSettingMgr( void )
{
    bool result = m_SettingMgrInitied;
    if( !m_SettingMgrInitied )
    {
        std::string dbFileName = VxGetAppDirectory( eAppDirThumbs );
        if( !dbFileName.empty() )
        {
            dbFileName += "thumbs.db";
            if( 0 == m_PluginSettingDb.dbStartup( 1, dbFileName ) )
            {
                m_PluginSettingDb.getAllPluginSettings( m_SettingList );
                m_SettingMgrInitied = true;
            }
        }
    }

    return result;
}


//============================================================================
bool PluginSettingMgr::setPluginSetting( PluginSetting& pluginSetting )
{
    bool result = initPluginSettingMgr();
    if( result )
    {
        if( pluginSetting.getPluginType() != ePluginTypeInvalid )
        {
            for( PluginSetting& setting : m_SettingList )
            {
                if( setting.getPluginType() == pluginSetting.getPluginType() )
                {
                    setting = pluginSetting;
                    return m_PluginSettingDb.updatePluginSetting( setting.getPluginType(), setting );
                }
            }

            m_SettingList.push_back( pluginSetting );
            return m_PluginSettingDb.updatePluginSetting( pluginSetting.getPluginType(), pluginSetting );
        }
        else
        {
            LogMsg( LOG_ERROR, "setPluginSetting invalid plugin type " );
            result = false;
        }
    }

    return result;
}

//============================================================================
bool PluginSettingMgr::getPluginSetting( EPluginType pluginType, PluginSetting& pluginSetting )
{
    bool result = initPluginSettingMgr();
    if( pluginSetting.getPluginType() != ePluginTypeInvalid )
    {
        for( PluginSetting& setting : m_SettingList )
        {
            if( setting.getPluginType() == pluginType )
            {
                pluginSetting = setting;
                return true;
            }
        }

        PluginSetting setting;
        setting.setPluginType( pluginType );
        m_SettingList.push_back( setting );
        pluginSetting = setting;
        return true;
    }
    else
    {
        LogMsg( LOG_ERROR, "getPluginSetting invalid plugin type " );
        result = false;
    }

    return result;
}
