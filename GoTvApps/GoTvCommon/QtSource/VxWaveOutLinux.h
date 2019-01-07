#pragma once
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
// brett.jones@engineer.com
// http://www.gotvptop.net
//============================================================================

#include "IVxWaveOut.h"

class VxWaveOut : public IVxWaveOut
{
public:
	VxWaveOut(){};
	virtual ~VxWaveOut(){};

	int 						waveOutStartup( void ){ return 0; };
	void						waveOutShutdown( void ){};

	int							startWaveOutput( void ){return 0; }
	bool						stopWaveOutput( void ){ return false; };	//shuts down wave out and returns TRUE if was active

	void						sendAudioDataToSpeaker( const char * data, int dataLen ){};
};

