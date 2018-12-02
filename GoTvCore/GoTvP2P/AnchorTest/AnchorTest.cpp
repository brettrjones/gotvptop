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
// brett.jones@engineer.com
// http://www.gotvptop.net
//============================================================================

#include "AnchorTest.h"

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>
#include <GoTvCore/GoTvP2P/NetServices/NetServicesMgr.h>
#include <GoTvInterface/IToGui.h>

#include <CoreLib/VxGlobals.h>
#include <NetLib/VxSktUtil.h>
#include <NetLib/VxResolveHost.h>
#include <NetLib/VxSktConnectSimple.h>

#include <stdio.h>
#include <stdarg.h>

namespace
{
	//============================================================================
	uint32_t AnchorUrlTestThreadFunc( void * pvContext )
	{
		VxThread * poThread = (VxThread *)pvContext;
		poThread->setIsThreadRunning( true );
		AnchorTest * anchorTest = (AnchorTest *)poThread->getThreadUserParam();
		if( false == poThread->isAborted() )
		{
			anchorTest->doAnchorUrlTest();
		}

		poThread->threadAboutToExit();
		return 0;
	}

	//============================================================================
	uint32_t NetServiceUrlTestThreadFunc( void * pvContext )
	{
		VxThread * poThread = (VxThread *)pvContext;
		poThread->setIsThreadRunning( true );
		AnchorTest * anchorTest = (AnchorTest *)poThread->getThreadUserParam();
		if( false == poThread->isAborted() )
		{
			anchorTest->doNetServiceUrlTest();
		}
		poThread->threadAboutToExit();
		return 0;
	}
}

//============================================================================
AnchorTest::AnchorTest( IToGui& toGui, EngineSettings& engineSettings, NetServicesMgr& netServicesMgr )
: m_ToGui( toGui )
, m_EngineSettings( engineSettings )
, m_NetServicesMgr( netServicesMgr )
{
}

//============================================================================
AnchorTest::~AnchorTest()
{
}

//============================================================================
const char * AnchorTest::getTestName( bool isAnchor )
{
	if( isAnchor )
	{
		return "ANCHOR TEST: ";
	}

	return "CONNECT TEST: ";
}

//============================================================================
void AnchorTest::fromGuiVerifyAnchorSettings( void )
{
	startAnchorUrlTest();
	startNetServiceUrlTest();
}

//============================================================================
void AnchorTest::startAnchorUrlTest( void )
{
	m_AnchorThread.abortThreadRun( true );
	while( m_AnchorThread.isThreadRunning() )
	{
		VxSleep( 200 );
	}

	m_AnchorThread.startThread( (VX_THREAD_FUNCTION_T)AnchorUrlTestThreadFunc, this, "AnchorUrlTestThread" );
}

//============================================================================
void AnchorTest::startNetServiceUrlTest( void )
{
	m_NetServiceThread.abortThreadRun( true );
	while( m_NetServiceThread.isThreadRunning() )
	{
		VxSleep( 200 );
	}

	m_NetServiceThread.startThread( (VX_THREAD_FUNCTION_T)NetServiceUrlTestThreadFunc, this, "NetServiceTestThread" );
}

//============================================================================
void AnchorTest::sendTestStatus( EAnchorTestStatus eStatus, const char * msg, ... )
{
	char as8Buf[ 1024 ];
	va_list argList;
	va_start( argList, msg );
	vsnprintf( as8Buf, sizeof( as8Buf ), msg, argList );
	as8Buf[sizeof( as8Buf ) - 1] = 0;
	va_end( argList );
	LogMsg( LOG_STATUS, "Test Status %s: %s\n", DescribeAnchorStatus( eStatus), as8Buf ); 
	m_ToGui.toGuiAnchorStatus( eStatus, as8Buf );
}

//============================================================================
void AnchorTest::sendTestLog( const char * msg, ... )
{
	char as8Buf[ 1024 ];
	va_list argList;
	va_start( argList, msg );
	vsnprintf( as8Buf, sizeof( as8Buf ), msg, argList );
	as8Buf[sizeof( as8Buf ) - 1] = 0;
	va_end( argList );
	LogMsg( LOG_STATUS, "Anchor Test Log %s\n", as8Buf ); 
	m_ToGui.toGuiAnchorStatus( eAnchorTestStatusLogMsg, as8Buf );
}

//============================================================================
void AnchorTest::doAnchorUrlTest( void )
{
	if( m_EngineSettings.getIsThisNodeAnAnchor() )
	{
		sendTestStatus( eAnchorTestStatusAnchorOk,
			":Skipped Anchor Test Because Is Anchor\n" );
		return;
	}

	std::string anchorUrl;
	m_EngineSettings.getAnchorWebsiteUrl( anchorUrl );
	doConnectionTest( anchorUrl, true );
}

//============================================================================
void AnchorTest::doNetServiceUrlTest( void )
{
	std::string netServiceUrl;
	m_EngineSettings.getNetServiceWebsiteUrl( netServiceUrl );
	doConnectionTest( netServiceUrl, false );
}

//============================================================================
bool AnchorTest::doConnectionTest( std::string& nodeUrl, bool isAnchor )
{
	sendTestLog( "%s test start using %s", getTestName( isAnchor ), nodeUrl.c_str() );

	VxSktConnectSimple sktSimple;
	VxTimer testTimer;
	std::string strHost;
	std::string strFile;
	uint16_t u16Port;

	if( false == sktSimple.connectToWebsite(	nodeUrl.c_str(), 
												strHost, 
												strFile, 
												u16Port, 
												ANCHOR_CONNECT_TIMEOUT ) )
	{
		sendTestStatus( isAnchor ? eAnchorTestStatusAnchorConnectFail : eAnchorTestStatusNetServiceConnectFail,
			"%s Could not connect to %s (%s)", getTestName( isAnchor ), nodeUrl.c_str(), sktSimple.getRemoteIpAddress()  );
		return doConnectTestFailed( isAnchor );
	}

	sktSimple.dumpConnectionInfo();

	std::string retPong;
	if( false == m_NetServicesMgr.sendAndRecievePing( testTimer, sktSimple, retPong, 5000 ) )
	{
		sendTestStatus( isAnchor ? eAnchorTestStatusAnchorConnectionDropped : eAnchorTestStatusNetServiceConnectionDropped,
			"%s Connected to %s but dropped connection (wrong network name ?)", getTestName( isAnchor ), nodeUrl.c_str() );
		sktSimple.closeSkt();
		return doConnectTestFailed( isAnchor );
	}

	sktSimple.closeSkt();
	return doConnectTestSuccess( isAnchor, retPong );
}

//============================================================================
bool AnchorTest::doConnectTestFailed( bool isAnchor )
{
	sendTestStatus( isAnchor ? eAnchorTestStatusAnchorTestComplete : eAnchorTestStatusNetServiceTestComplete,
		"%s Test Failed", getTestName( isAnchor ) );
	return false;
}

//============================================================================
bool AnchorTest::doConnectTestSuccess( bool isAnchor, std::string& pongResult )
{
	sendTestStatus( isAnchor ? eAnchorTestStatusAnchorTestComplete : eAnchorTestStatusNetServiceTestComplete,
		"%s Test Success %s", getTestName( isAnchor ), pongResult.c_str() );
	return true;
}


