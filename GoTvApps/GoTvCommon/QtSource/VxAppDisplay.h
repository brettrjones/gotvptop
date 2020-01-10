#pragma once
//============================================================================
// Copyright (C) 2017 Brett R. Jones
// Issued to MIT style license by Brett R. Jones in 2017
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

#include <QWidget>

class AppCommon;

class VxAppDisplay : public QWidget
{
    Q_OBJECT

public:
    VxAppDisplay( AppCommon& appCommon, QWidget * parent = 0 );
    virtual ~VxAppDisplay() {};

    bool						isVerticalOrientation( void )                   { return ( m_Orientation == Qt::Orientation::Vertical ); }

    Qt::Orientation             getNativeOrientation( void );
    Qt::Orientation             getCurrentOrientation( void );
    Qt::Orientation             forceOrientationUpdate( void );

signals:
    void						signalDeviceOrientationChanged( int qtOrientation );

protected slots:
    void						slotCheckOrientationTimer( void );

protected:
    void                        initializeAppDisplay( void );

    AppCommon &					m_MyApp;
    bool                        m_Initialized{ false };
    float                       m_StdDisplayWidth{ 1920.0f };
    float                       m_StdDisplayHeight{ 1080.0f };
    float                       m_DisplayWidthScale{ 1.0f };
    float                       m_DisplayHeightScale{ 1.0f };
    QTimer *                    m_OrientationCheckTimer{ nullptr };
    Qt::Orientation				m_Orientation{ Qt::Orientation::Horizontal };
    Qt::Orientation				m_LastOrientation{ Qt::Orientation::Horizontal };
};


