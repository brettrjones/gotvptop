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
// brett.jones@engineer.com
// http://www.gotvptop.net
//============================================================================

#include <QWidget>

class AppCommon;

class VxAppDisplay : public QWidget
{
    Q_OBJECT

public:
    VxAppDisplay( AppCommon& appCommon, QWidget * parent = 0 );
    virtual ~VxAppDisplay() {};

    float				        getDisplayScale( void );
    float				        getDisplayWidthScale( void )                    { return m_DisplayWidthScale; }
    float				        getDisplayHeightScale( void )                   { return m_DisplayHeightScale; }
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
    bool                        m_Initialized;
    float                       m_StdDisplayWidth;
    float                       m_StdDisplayHeight;
    float                       m_DisplayWidthScale;
    float                       m_DisplayHeightScale;
    QTimer *                    m_OrientationCheckTimer;
    Qt::Orientation				m_Orientation;
    Qt::Orientation				m_LastOrientation;
};


