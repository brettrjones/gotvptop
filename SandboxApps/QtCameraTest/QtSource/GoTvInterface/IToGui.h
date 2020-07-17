#pragma once

#include <stdint.h>

class VxGUID;

//! IToGui is an abstract interface for calls to GUI from native C++/C code
class IToGui
{
public:
    static IToGui&              getToGui();

    virtual void				toGuiWantVideoCapture( bool wantVidCapture ) = 0;
    virtual void				toGuiPlayVideoFrame( VxGUID& onlineId, uint8_t * pu8Jpg, uint32_t u32JpgDataLen, int motion0To100000 ) = 0;
    virtual int				    toGuiPlayVideoFrame( VxGUID& onlineId, uint8_t * picBuf, uint32_t picBufLen, int picWidth, int picHeight ) = 0;
};
