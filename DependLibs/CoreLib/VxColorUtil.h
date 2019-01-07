#ifndef VX_COLOR_UTIL_H
#define VX_COLOR_UTIL_H
#include <CoreLib/config_corelib.h>

//============================================================================
//! blend 2 colors using alpha of src color to determine how much of src color is added to dest color
uint32_t VxBlendColors(	uint32_t u32DecalColor,	// color of upper layer ( decal or overlay )
					uint32_t u32DestColor );	// color of lower layer ( background )

#endif // VX_COLOR_UTIL_H
