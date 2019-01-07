#pragma once
//============================================================================
// Copyright (C) 2003 Brett R. Jones 
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

class VxWaveOutCallback
{
public:
	virtual void				waveOutSpaceAvail( int freeSpaceLen, void * userData ) = 0;
};

class IVxWaveOut
{
public:
	IVxWaveOut(){};
	virtual ~IVxWaveOut(){};

	virtual int 				waveOutStartup( void ) = 0;
	virtual void				waveOutShutdown( void ) = 0;

	virtual int					startWaveOutput( void ) = 0;
	virtual bool				stopWaveOutput( void ) = 0;	//shuts down wave out and returns true if was active

	virtual void				setWaveOutCallback( VxWaveOutCallback * waveOutCallback, void * userData = 0 ) = 0;
};

#ifdef TARGET_OS_WINDOWS
#include "VxWaveOut.h"
#else
#include "VxWaveOutLinux.h"
#endif
