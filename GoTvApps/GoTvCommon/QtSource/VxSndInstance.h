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
// bjones.engineer@gmail.com
// http://www.nolimitconnect.com
//============================================================================

#include "config_gotvapps.h"
#include "SoundDefs.h"

#include <QObject>

class QSound;
class QTimer;

class VxSndInstance : public QObject
{
	Q_OBJECT
public:
	VxSndInstance( ESndDef sndDef, QObject *parent = 0);
	virtual ~VxSndInstance();

	void						setSndDef( ESndDef sndDef )				{ m_SndDef = sndDef; }
	ESndDef						getSndDef( void )						{ return m_SndDef; }

	bool						isPlaying( void )						{ return m_IsPlaying; }
	
	void						startPlay( bool loopContinuous = false );
	void						stopPlay( void );

signals:
	void						sndFinished( VxSndInstance * thisInstance );

protected slots:
	void						slotCheckForFinish( void );

protected:
	virtual void				initSndInstance( void );

	//=== vars ===//
	ESndDef						m_SndDef;
	QSound *					m_QSound;
	QTimer *					m_CheckFinishTimer;
	bool						m_IsPlaying;
	bool						m_IsInitialized;
};

