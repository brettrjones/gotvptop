//============================================================================
// Copyright (C) 2015 Brett R. Jones
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

#include <config_gotvcore.h>
#include "AssetMgrBase.h"
#include <GoTvInterface/IToGui.h>

#include <CoreLib/VxFileIsTypeFunctions.h>

//============================================================================
AssetMgrBase::AssetMgrBase( P2PEngine& engine )
: m_Engine( engine )
{
}


//============================================================================
IToGui&	AssetMgrBase::getToGui()
{
    return IToGui::getToGui();
}

//============================================================================
void AssetMgrBase::addAssetMgrClient( AssetCallbackInterface * client, bool enable )
{
	AutoResourceLock( this );
	if( enable )
	{
		m_AssetClients.push_back( client );
	}
	else
	{
		std::vector<AssetCallbackInterface *>::iterator iter;
		for( iter = m_AssetClients.begin(); iter != m_AssetClients.end(); ++iter )
		{
			if( *iter == client )
			{
				m_AssetClients.erase( iter );
				return;
			}
		}
	}
}

//============================================================================
bool AssetMgrBase::isAllowedFileOrDir( std::string strFileName )
{
	if( VxIsExecutableFile( strFileName ) 
		|| VxIsShortcutFile( strFileName ) )
	{
		return false;
	}

	return true;
}
