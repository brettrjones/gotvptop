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

#include "config_gotvapps.h"
#include "MyQtSoundOutput.h"
#include "VxWaveOut.h"
#include "MySndMgr.h"
#include "AppCommon.h"

#include <CoreLib/VxDebug.h>
#include <QtCore/qmath.h>
#include <QtCore/qendian.h>
#include <CoreLib/VxTimer.h>
//#define USE_VX_WAVE_FOR_OUTPUT 1

//============================================================================
MyQtSoundOutput::MyQtSoundOutput( MySndMgr& sndMgr, int sampleRate, QObject *parent)
: QObject( parent )
, m_SndMgr( sndMgr )
, m_MyApp( sndMgr.getApp() )
, m_Engine( sndMgr.getApp().getEngine() )
, m_SampleRate( sampleRate )
{
#ifdef USE_VX_WAVE_FOR_OUTPUT
	//g_poWave->set
#endif // USE_VX_WAVE_FOR_OUTPUT
}

//============================================================================
MyQtSoundOutput::~MyQtSoundOutput()
{
}

//============================================================================
void MyQtSoundOutput::start()
{
#ifdef USE_VX_WAVE_FOR_OUTPUT
	if( g_poWave )
	{
		g_poWave->setWaveOutCallback( this );
	}
#endif // TARGET_OS_WINDOWS
}

//============================================================================
void MyQtSoundOutput::stop()
{
#ifdef USE_VX_WAVE_FOR_OUTPUT
	if( g_poWave )
	{
		g_poWave->stopWaveOutput();
	}
#endif // TARGET_OS_WINDOWS
}

//============================================================================
void MyQtSoundOutput::recieveAudioData( const char * buf, int dataLen )
{

}

//============================================================================
void MyQtSoundOutput::waveOutSpaceAvail( int freeSpaceLen, void * userData )
{

}
