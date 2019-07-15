#pragma once
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
// bjones.engineer@gmail.com
// http://www.gotvptop.com
//============================================================================

#include "IVxWaveOut.h"

#include <CoreLib/VxMutex.h>

#include <QObject>

class MySndMgr;
class AppCommon;
class P2PEngine;

class MyQtSoundOutput : public QObject, public VxWaveOutCallback
{
    Q_OBJECT
public:
	MyQtSoundOutput( MySndMgr& sndMgr, int sampleRate, QObject *parent);
	virtual ~MyQtSoundOutput();

	void						start();
	void						stop();

	void						recieveAudioData( const char * buf, int dataLen );

protected:
	virtual void				waveOutSpaceAvail( int freeSpaceLen, void * userData );


	//=== vars ===//
	MySndMgr&					m_SndMgr;
	AppCommon&				    m_MyApp;
	P2PEngine&					m_Engine;
	int							m_SampleRate;
};
