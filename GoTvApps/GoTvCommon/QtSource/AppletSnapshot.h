#pragma once
//============================================================================
// Copyright (C) 2020 Brett R. Jones
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

#include "AppletBase.h"
#include "ui_AppletSnapshot.h"


class ThumbnailViewWidget;
class AssetMgr;
class IVxVidCap;

class AppletSnapshot : public AppletBase
{
	Q_OBJECT
public:
	AppletSnapshot( AppCommon& app, QWidget * parent = NULL );
	virtual ~AppletSnapshot() override;

signals:
    void						signalJpgSnapshot( uint8_t* pu8JpgData, uint32_t u32DataLen, int iWidth, int iHeight );

public slots:
    void						onSnapShotButClick( void );
    void						onCancelButClick( void );

protected:
    Ui::AppletSnapshotUi		ui;
    IVxVidCap *					m_VidCap = nullptr;
    bool 					    m_CameraSourceAvail = false;
    QTimer *                    m_CloseDlgTimer = nullptr;

    uint8_t *					m_pu8BitmapData = nullptr;	// snapshot bitmap
    uint32_t					m_u32BitmapLen = 0;		// bitmap length
};
