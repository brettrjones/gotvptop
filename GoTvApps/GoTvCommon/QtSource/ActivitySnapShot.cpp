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

#include "ActivitySnapShot.h"
#include "AppCommon.h"

#include <QMessageBox>
#include <QUuid>

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>
#include <VxVideoLib/VxVideoLib.h>

//============================================================================
ActivitySnapShot::ActivitySnapShot( AppCommon& app, QWidget * parent )
: ActivityBase( OBJNAME_ACTIVITY_SNAP_SHOT, app, parent, eAppletMessenger, 0 )
, m_pu8BitmapData(0)
, m_u32BitmapLen(0)
{
	ui.setupUi(this);
	connect( ui.snapshotButton, SIGNAL(clicked()), this, SLOT(onSnapShotButClick()));
	connect( ui.cancelButton, SIGNAL(clicked()), this, SLOT(onCancelButClick()));
#ifdef TARGET_OS_WINDOWS
	m_VidCap = VxGetVidCapInterface();
#endif // TARGET_OS_WINDOWS
	if( 0 == m_VidCap->startupVidCap() )
	{
		QMessageBox::warning(this, tr("Video Capture"), tr("No Video Source Available.") );
		onCancelButClick();
	}
	else
	{
		// start preview
		QRect oWndRect = ui.imageScreen->geometry();
        m_VidCap->startPreview(	(void *)ui.imageScreen->winId(),
									0,
									oWndRect.left(),
									oWndRect.top(),
									oWndRect.width(),
									oWndRect.height() );
		
	}
}
//============================================================================
ActivitySnapShot::~ActivitySnapShot()
{
}

//============================================================================
//! browse for picture of me
void ActivitySnapShot::onSnapShotButClick( void )
{
#ifdef TARGET_OS_WINDOWS
	uint32_t u32Format;
    m_pu8BitmapData = m_VidCap->takeSnapShot( 0, m_u32BitmapLen, u32Format );
	m_VidCap->shutdownVidCap();
    BITMAPINFO * poBitmap = (BITMAPINFO *)m_pu8BitmapData;
	if( poBitmap  )
    {
		if( (0 == u32Format) &&
			(0 != poBitmap->bmiHeader.biSizeImage ) &&
			(poBitmap->bmiHeader.biSizeImage == (poBitmap->bmiHeader.biWidth * poBitmap->bmiHeader.biHeight * 3)))
		{
			// some cams do not place format in bitmap even though data is valid ie (Microsoft LifeCam VX-3000)
			u32Format = FOURCC_RGB;
		}
		uint32_t u32JpgDataLen = 0;
		uint8_t * pu8JpgData = VxConvertToJpg(	u32Format, // format
										(uint8_t *)&m_pu8BitmapData[poBitmap->bmiHeader.biSize], 
										poBitmap->bmiHeader.biSizeImage,
										poBitmap->bmiHeader.biWidth,
										poBitmap->bmiHeader.biHeight,
										u32JpgDataLen,
										320,
										240 );
		emit signalJpgSnapshot( pu8JpgData, u32JpgDataLen, 320, 240 );
		delete pu8JpgData;
		delete m_pu8BitmapData;
		m_pu8BitmapData = NULL; 
	}
	close();
#endif // TARGET_OS_WINDOWS
}

//============================================================================
//! Implement the OnClickListener callback    
void ActivitySnapShot::onCancelButClick( void ) 
{
	m_VidCap->shutdownVidCap();

	close();
}

