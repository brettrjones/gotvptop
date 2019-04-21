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
// brett.jones@engineer.com
// http://www.gotvptop.net
//============================================================================

#include "PluginWebServer.h"
#include "PluginMgr.h"

#include <PktLib/PktsWebServer.h>
#include <PktLib/PktSearch.h>
#include <NetLib/VxSktBase.h>
#include <CoreLib/VxGlobals.h>

//============================================================================
PluginWebServer::PluginWebServer( P2PEngine& engine, PluginMgr& pluginMgr, VxNetIdent * myIdent )
: PluginBase( engine, pluginMgr, myIdent )
, m_File(NULL)
{
	m_ePluginType = ePluginTypeWebServer;
	setPluginWebServer(this);
	setWebServerEnable( true );
}

//============================================================================
PluginWebServer::~PluginWebServer()
{
}

//============================================================================
void PluginWebServer::pluginShutdown( void )
{
	AutoPluginLock( this );
	WebRxIter oMapRxIter;
	for( oMapRxIter = m_WebRxSessions.begin(); oMapRxIter != m_WebRxSessions.end(); ++oMapRxIter )
	{
		 WebRxSession * poRxSession = oMapRxIter->second;
		 //poRxSession->getSkt()->closeSkt( 78298 );
		 delete poRxSession;
	}

	WebTxIter oMapTxIter;
	for( oMapTxIter = m_WebTxSessions.begin(); oMapTxIter != m_WebTxSessions.end(); ++oMapTxIter )
	{
		WebTxSession * poTxSession = oMapTxIter->second;
		//poTxSession->getSkt()->closeSkt( 78299 );
		delete poTxSession;
	}

	WebProxyIter oMapProxyIter;
	for( oMapProxyIter = m_WebProxySessions.begin(); oMapProxyIter != m_WebProxySessions.end(); ++oMapProxyIter )
	{
		WebProxySession * poProxySession = oMapProxyIter->second;
		//poProxySession->getSkt()->closeSkt( 78300 );
		delete poProxySession;
	}

	PluginBase::pluginShutdown();
}

//============================================================================
//! this is called if incoming http connection (NOTE: only used by WebServer)
RCODE PluginWebServer::handleHttpConnection( VxSktBase * sktBase, VxNetIdent * netIdent )
{
	RCODE rc = 0;
	RcWebSkt * poWebSkt = NULL;
	static std::string strOffline = "User Offline \n\n";
	if( netIdent != m_MyIdent )
	{
		// see if can connect to user
		VxSktBase * poUserSkt =  NULL;
		if( true == m_PluginMgr.pluginApiSktConnectTo( m_ePluginType, netIdent, 0, &poUserSkt ))
		{
			rc = acceptRawLocalHttpConnection( sktBase, netIdent, &poWebSkt );
			if( 0 == rc )
			{
				poWebSkt->setUserExtraData( poUserSkt );
				WebProxySession * poSession = new WebProxySession( netIdent, sktBase, poWebSkt );

				m_PluginMutex.lock();
				m_WebProxySessions.insert( std::make_pair( netIdent, poSession ) );
				m_PluginMutex.unlock();
				
				startWebSktThreads( poWebSkt );
			}
		}
		else
		{
			// failed to connect.. just send Error
			sktBase->sendData(strOffline.c_str(), strOffline.length(), true);
		}
	}
	else
	{
		// view my own profile
		rc = acceptRawLocalHttpConnection( sktBase, netIdent, &poWebSkt );
		if( 0 == rc )
		{
			startWebSktThreads( poWebSkt );
		}
	}

	return rc;
}

//============================================================================
void PluginWebServer::fromGuiUserLoggedOn( void )
{
    std::string strProfileDir = VxGetUserProfileDirectory();
	setWebSiteDir( strProfileDir.c_str() );
}

//============================================================================
void PluginWebServer::getMyPicFileName( std::string& strRetFileName )
{
	strRetFileName = getWebSiteDir();
	strRetFileName += "me.jpg";
}

//============================================================================
WebRxSession * PluginWebServer::findRxSession( VxNetIdent * netIdent )
{
	WebRxIter oMapIter = m_WebRxSessions.find( netIdent );
	if( oMapIter != m_WebRxSessions.end() )
	{
		return oMapIter->second;
	}
	return NULL;
}

//============================================================================
WebRxSession * PluginWebServer::findOrCreateRxSession( VxNetIdent * netIdent, VxSktBase * sktBase )
{
	WebRxSession * poSession = findRxSession( netIdent );
	if( NULL == poSession )
	{
		poSession = new WebRxSession( netIdent, sktBase );

		AutoPluginLock(this);
		m_WebRxSessions.insert( std::make_pair( netIdent, poSession ) );
	}
	else
	{
		poSession->setSkt( sktBase );
	}
	return poSession;
}

//============================================================================
WebTxSession * PluginWebServer::findTxSession( VxNetIdent * netIdent )
{
	WebTxIter oMapIter = m_WebTxSessions.find( netIdent );
	if( oMapIter != m_WebTxSessions.end() )
	{
		return oMapIter->second;
	}
	return NULL;
}

//============================================================================
WebTxSession * PluginWebServer::findOrCreateTxSession( VxNetIdent * netIdent, VxSktBase * sktBase )
{
	WebTxSession * poSession = findTxSession( netIdent );
	if( NULL == poSession )
	{
		poSession = new WebTxSession( netIdent, sktBase );

		AutoPluginLock(this);
		m_WebTxSessions.insert( std::make_pair( netIdent, poSession ) );
	}
	else
	{
		poSession->setSkt( sktBase );
	}
	return poSession;
}

//============================================================================
WebProxySession * PluginWebServer::findWebProxySession( VxNetIdent * netIdent )
{
	WebProxyIter oMapIter = m_WebProxySessions.find( netIdent );
	if( oMapIter != m_WebProxySessions.end() )
	{
		return oMapIter->second;
	}
	return NULL;
}

//============================================================================
bool PluginWebServer::searchActionProfilePic( VxNetIdent * netIdent, VxSktBase * sktBase )
{
	PktMyPicSendReq oPkt;
	return txPacket( netIdent, sktBase, &oPkt );
}
