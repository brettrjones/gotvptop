//============================================================================
// Copyright (C) 2013 Brett R. Jones
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
// http://www.gotvptop.com
//============================================================================

#include "VxAppDisplay.h"
#include "AppCommon.h"

#include <QScreen>
#include <QTimer>

//============================================================================
VxAppDisplay::VxAppDisplay( AppCommon& appCommon, QWidget * parent )
: QWidget( parent )
, m_MyApp( appCommon )
, m_Initialized( false )
, m_StdDisplayWidth( 1920.0f )
, m_StdDisplayHeight( 1080.0f )
, m_DisplayWidthScale( 1.0f )
, m_DisplayHeightScale( 1.0f )
, m_OrientationCheckTimer( new QTimer( this ) )
, m_Orientation( Qt::Orientation::Horizontal )
, m_LastOrientation( Qt::Orientation::Horizontal )
{
}

//============================================================================
void VxAppDisplay::initializeAppDisplay( void )
{
    if( !m_Initialized )
    {
        m_Initialized = true;
       QScreen * dispScreen = m_MyApp.getQApplication().primaryScreen();
        if( dispScreen->isPortrait( dispScreen->orientation() ) )
        {
            m_Orientation = Qt::Vertical;
        }
        else
        {
            m_Orientation = Qt::Horizontal;
        }

        QSize screenSize = dispScreen->availableSize();
        if( screenSize.width() > screenSize.height() )
        {
            m_DisplayWidthScale =  ( float ) screenSize.width() / m_StdDisplayWidth;
            m_DisplayHeightScale = ( float ) screenSize.height() / m_StdDisplayHeight;
        }
        else
        {
            m_DisplayWidthScale = ( float ) screenSize.height() / m_StdDisplayWidth;
            m_DisplayHeightScale = ( float ) screenSize.width() / m_StdDisplayHeight;        
        }

        connect( m_OrientationCheckTimer, SIGNAL(timeout()), this, SLOT(slotCheckOrientationTimer()) );
        m_OrientationCheckTimer->setInterval( 1500 );
        m_OrientationCheckTimer->start();
        forceOrientationUpdate();
    }
}

//============================================================================
void VxAppDisplay::slotCheckOrientationTimer( void )
{
    Qt::Orientation curOrientation = getCurrentOrientation();
    if( curOrientation != m_Orientation )
    {
        m_Orientation = curOrientation;
        emit signalDeviceOrientationChanged( (int) m_Orientation );
    }
}

//============================================================================
float VxAppDisplay::getDisplayScale( void ) 
{ 
    initializeAppDisplay();
    return m_DisplayHeightScale < m_DisplayWidthScale ? m_DisplayHeightScale : m_DisplayWidthScale; 
}

//============================================================================
Qt::Orientation VxAppDisplay::getNativeOrientation( void )
{
    initializeAppDisplay();
    QScreen * dispScreen = m_MyApp.getQApplication().primaryScreen();
    Qt::ScreenOrientation screenOrientation = dispScreen->orientation();
    if( dispScreen->isPortrait( screenOrientation ) )
    {
        return Qt::Vertical;
    }
    else
    {
        return Qt::Horizontal;
    }
}

//============================================================================
Qt::Orientation VxAppDisplay::getCurrentOrientation( void )
{
    initializeAppDisplay();
    QScreen * dispScreen = m_MyApp.getQApplication().primaryScreen();
    if( dispScreen->isPortrait( dispScreen->orientation() ) )
    {
        return Qt::Vertical;
    }
    else
    {
        return Qt::Horizontal;
    }
}

//============================================================================
Qt::Orientation VxAppDisplay::forceOrientationUpdate( void ) 
{ 
    emit signalDeviceOrientationChanged( ( int )m_Orientation ); 
    return m_Orientation; 
}




