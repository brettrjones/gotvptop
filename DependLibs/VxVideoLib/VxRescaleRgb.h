#pragma once
//============================================================================
// Copyright (C) 2003 Brett R. Jones 
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

//! resize rgb 24 bit image
// NOTE 1: caller must delete the returned buffer
uint8_t * VxResizeRgbImage(	uint8_t *	pu8VidData, 
						int		iImageWidthIn, 
						int		iImageHeightIn, 
						int		iResizeToWidth, 
						int		iResizeToHeight,
						int		iRotation );

// NOTE 1: caller must delete the returned buffer
uint8_t * VxRotateRgbImage(		uint8_t *	pu8VidData, 
							int		iImageWidthIn, 
							int		iImageHeightIn, 
							int		iRotateAngle );