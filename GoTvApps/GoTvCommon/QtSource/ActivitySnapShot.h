#pragma once
//============================================================================
// Copyright (C) 2013 Brett R. Jones
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

#include "ActivityBase.h"

#include <QDialog>
#include "ui_ActivitySnapShot.h"

#include <CoreLib/VxDefs.h>

class IVxVidCap;

class ActivitySnapShot : public ActivityBase
{
	Q_OBJECT
public:
	ActivitySnapShot( AppCommon& app, QWidget * parent = NULL );
	virtual ~ActivitySnapShot();

public slots:
	void						onSnapShotButClick( void );
	void						onCancelButClick( void ); 

signals:
	void						signalJpgSnapshot(uint8_t* pu8JpgData,uint32_t u32DataLen,int iWidth,int iHeight );

protected:
	Ui::snapshotDialog			ui;
	IVxVidCap *					m_VidCap;

	uint8_t *						m_pu8BitmapData;	// snapshot bitmap
	uint32_t							m_u32BitmapLen;		// bitmap length
};