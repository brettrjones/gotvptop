#pragma once
//============================================================================
// Copyright (C) 2018 Brett R. Jones
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

#include "IGoTvDefs.h"

class IGoTvEvents
{
public:

    virtual void                keyPressEvent( int moduleNum, int key, int mod ) = 0;
    virtual void                keyReleaseEvent( int moduleNum, int key, int mod ) = 0;

    virtual void                mousePressEvent( int moduleNum, int mouseXPos, int mouseYPos, int mouseButton ) = 0;
    virtual void                mouseReleaseEvent( int moduleNum, int mouseXPos, int mouseYPos, int mouseButton ) = 0;
    virtual void                mouseMoveEvent( int moduleNum, int mouseXPos, int mouseYPos ) = 0;

    virtual void                resizeEvent( int moduleNum, int winWidth, int winHeight ) = 0;
    virtual void                closeEvent( int moduleNum ) = 0;
    virtual void                visibleEvent( int moduleNum, bool isVisible ) = 0;

};
