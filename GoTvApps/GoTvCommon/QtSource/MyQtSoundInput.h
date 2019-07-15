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

#include "config_gotvapps.h"

#include <QObject>

class MySndMgr;
class AppCommon;
class P2PEngine;

class MyQtSoundInput : public QObject
{
	Q_OBJECT

public:
    MyQtSoundInput( MySndMgr *parent) ;
	virtual ~MyQtSoundInput();

	void						start();
	void						stop();

	void						sendAudioData( const char * buf, int dataLen );

	qint64						readData(char *data, qint64 maxlen);
	qint64						writeData(const char *data, qint64 len);

signals:
	void						update();

protected:
	//=== vars ===//
	MySndMgr *					m_SndMgr;
	AppCommon&				    m_MyApp;
	P2PEngine&					m_Engine;
	quint16						m_maxAmplitude;

	int							m_iSndInBufferIdx;
	char						m_as8SndInBuffer[4096];


};
