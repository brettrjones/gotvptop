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
// http://www.nolimitconnect.com
//============================================================================
#pragma once

#include <QColor>
#include <QSize>

class GuiParams
{
public:
    GuiParams();
    virtual ~GuiParams() = default;

    /// @brief initialize gui scaling etc
    static void                 initGuiParams();

    /// @brief get scaling required to make icons etc. usable on high dpi screens
    static int                  getGuiScale( void )  { return m_DisplayScale; }
    
    static int                  getControlIndicatorWidth( void );
    /// @brief thumbnails are square so this is both width and height
    static QSize                getThumbnailSize( void );

protected:

    static QColor				m_OnlineBkgColor;
    static QColor				m_OfflineBkgColor;
    static QColor				m_NearbyBkgColor;

    static int                  m_DisplayScale;
};
