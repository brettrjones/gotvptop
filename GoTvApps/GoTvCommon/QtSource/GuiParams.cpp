//============================================================================
// Copyright (C) 2019 Brett R. Jones
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

#include "GuiParams.h"
#include <QApplication>
#include <QDesktopWidget>

//============================================================================
QColor GuiParams::m_OnlineBkgColor( 176, 255, 176 );
QColor GuiParams::m_OfflineBkgColor( 192, 192, 192 );
QColor GuiParams::m_NearbyBkgColor( 176, 176, 255 );


//============================================================================
GuiParams::GuiParams()
{
    initGuiParams();    
}

//============================================================================
void GuiParams::initGuiParams()
{
    m_DpiScale = qApp->desktop()->devicePixelRatio();
    if( m_DpiScale < 1 || m_DpiScale > 5 )
    {
        m_DpiScale = 1;
    }
}
