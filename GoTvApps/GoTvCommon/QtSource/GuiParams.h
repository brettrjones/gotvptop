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
#pragma once

#include "config_gotvapps.h"
#include <QColor>

class GuiParams
{
public:
    GuiParams();
    virtual ~GuiParams() = default;

    /// @brief get scaling required to make icons etc. usable on high dpi screens
    int                         getGuiDpiScale() const { return m_DpiScale; }

protected:
    void                        initGuiParams();

    static QColor				m_OnlineBkgColor;
    static QColor				m_OfflineBkgColor;
    static QColor				m_NearbyBkgColor;

    int                         m_DpiScale{ 0 };
};
