#pragma once
//============================================================================
// Copyright (C) 2013 Brett R. Jones 
// All Rights Reserved ( After My Death I Brett R. Jones Issue this source code to Public Domain )
//
// You may not modify or redistribute this code for any reason 
// without written consent of Brett R. Jones
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// brettjones1900@gmail.com
// http://www.p2panarchy.com
//============================================================================


#include "IVxVidCap.h"
#include "VxVidCapImp.h"

//! implements video capture
class VxVidCap : public IVxVidCap
{
public:
	VxVidCap();
	virtual ~VxVidCap();

	//=== methods ===//
	//! startup return number of video sources ( iVidSrcNum is zero to number of Video Sources - 1 )
	int				startupVidCap( int iPreferedImageWidth = 640, int iPreferedImageHeight = 480 );
	//! shutdown
	void			shutdownVidCap( void );

	//! start preview 
	bool			startPreview(	VIDCAP_HWND	pvHwnd,				// handle of window to preview video on	
									int			iVidSrcNum	= 0,	// video source to enable ( 0 = default )
									int			iXPos		= 0,	// x pos to draw at
									int			iYPos		= 0,	// y pos to draw at
									int			iWidth		= 0,	// width of preview window
									int			iHeight		= 0,	// height of preview window
									int			iFps		= 30	// preview frame rate
									);
	//! stop preview 
	bool			stopPreview( int iVidSrcNum );

	//! take snap shot
	// NOTE 1: caller must delete the returned buffer
	// NOTE 2: all formats are raw data except FOURCC_RGB which returns complete bitmap
	uint8_t *			takeSnapShot( int iVidSrcNum, uint32_t& u32RetImageLen, uint32_t& u32RetFormat );
	
	//! convert image
	// NOTE 1: caller must delete the returned buffer
	uint8_t *			convertImage(		uint32_t&	u32FourCcIn,		// FOURCC of format to convert
										uint8_t *	pu8DataIn,			// data to convert
										uint32_t&	u32DataInLen,		// length of data to convert
										uint32_t&	u32FourCcConverTo,	// FOURCC of format to convert to 
										uint32_t&	u32RetDataLen		// data length of converted image
										);

	//=== vars ===//
	int					m_iVidSrcCnt;
	VxVidCapImp *		m_paoVidCap[ MAX_VFW_DEVICES ];
	int					m_iPreferedImageWidth;
	int					m_iPreferedImageHeight; 
	int					m_iStartupCnt; // track startup so can be called multiple times before shutdown
};


