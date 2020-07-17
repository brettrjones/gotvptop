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

#include <CoreLib/VxDefs.h>
//! convert image to jpeg

//! convert image
// NOTE 1: caller must delete the returned buffer
uint8_t * VxConvertToJpg(	uint32_t	u32FourCcIn,		// FOURCC of format to convert
							uint8_t *	pu8DataIn,			// data to convert
							int			iDataLen,			// length of data 
							int 		iImageWidth,		// width of image in pixels
							int 		iImageHeight,		// height of image in pixels
							uint32_t&	u32RetDataLen,		// data length of jpg image
							int			iResizeToWidth = 0, // if not zero then resize to given length
							int			iResizeToHeight = 0 // if not zero then resize to given height
							);

//! convert image
// NOTE 1: caller must delete the returned buffer
uint8_t * VxConvertImage(	uint32_t		u32FourCcIn,		// FOURCC of format to convert
							uint8_t *		pu8DataIn,			// data to convert
							int 			iImageWidth,		// width of image in pixels
							int 			iImageHeight,		// height of image in pixels
							uint32_t		u32FourCcConverTo,	// FOURCC of format to convert to 
							uint32_t&		u32RetDataLen		// data length of converted image
							);

// calculate length of buffer required to hold image
uint32_t VxCalcImageDataLen(	uint32_t		u32FourCcIn,		// FOURCC of format
						int 	iImageWidth,		// width of image in pixels
						int 	iImageHeight );		// height of image in pixels

// calculate bytes per line of pixels.... assumes 4 byte boundary for RGB else pixels * bytes_per_pixels
uint32_t VxCalcImageStride(	uint32_t		u32FourCcIn,		// FOURCC of format
						int 	iImageWidth );		// width of image in pixels



