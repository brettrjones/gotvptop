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
// http://www.gotvptop.com
//============================================================================

#include "VxAppStyle.h"
#include "AppCommon.h"
#include "VxAppTheme.h"

#include <QPainter>
#include <QStyleOption>
#include <QPushButton>
#include <QAbstractSpinBox>
#include <QFocusFrame>
#include <QPalette>
#include <QEvent>
#include <QPaintEvent>
#include <QApplication>
#include <QFocusFrame>
#include <QPointer>
#include <QPaintEvent>
#include <QPixmap>
#include <QBitmap>

#include <qdrawutil.h>

class AppFocusFrame;

namespace
{
	QPointer<AppFocusFrame>		g_FocusFrame;
	const int					g_FocusFrameWidth = 2;
}

//============================================================================
class AppFocusFrame : public QFocusFrame
{
public:
	AppFocusFrame( VxAppStyle& appStyle, QWidget* parent ) 
	: QFocusFrame( parent )
	, m_AppStyle( appStyle )
	{
	}


protected:
	virtual void paintEvent( QPaintEvent* ev ) override
	{
		QPainter painter( this );
        painter.save();
		m_AppStyle.drawFocusFrame( painter, ev->rect() );
        painter.restore();
	}

	VxAppStyle&					m_AppStyle;
};

//============================================================================
VxAppStyle::VxAppStyle( AppCommon& appCommon, VxAppTheme& appTheme)
: m_MyApp( appCommon )
, m_AppTheme( appTheme )
{
}

//============================================================================
VxAppStyle::~VxAppStyle()
{
}

//============================================================================
int VxAppStyle::focusFrameWidth()
{
	return g_FocusFrameWidth;
}

//============================================================================
bool VxAppStyle::event( QEvent* e )
{
    bool result = QCommonStyle::event( e );

	if ( e->type() == QEvent::FocusIn )
	{
		QWidget* focusedWidget = QApplication::focusWidget();

		if ( focusedWidget 
			&& !( focusedWidget->property( "NoFocusFrame" ) == true ) )
		{
			if( true == focusedWidget->property("GoTvIcon") )
			{
				m_MyApp.switchWindowFocus( focusedWidget );
			}
			if( true == focusedWidget->property( "GoTvFrame" ) )
			{
				focusedWidget->nextInFocusChain();
			}
			else
			{
				if( g_FocusFrame == NULL )
				{
					g_FocusFrame = new AppFocusFrame( *this, focusedWidget );
				}

				g_FocusFrame->setWidget( focusedWidget );
			}
		}
		else
		{
			if( g_FocusFrame )
			{
				g_FocusFrame->setWidget( NULL );
			}
		}
	}
	else if ( e->type() == QEvent::FocusOut )
	{
		if ( g_FocusFrame )
		{
			g_FocusFrame->setWidget( NULL );
		}
	}

    return result;
}

//============================================================================
void VxAppStyle::drawFocusFrame( QPainter& painter, const QRect& focusRect )
{
	m_AppTheme.drawFocusRect( painter, focusRect, focusFrameWidth() );
}

//============================================================================
void VxAppStyle::drawPrimitive( PrimitiveElement element, const QStyleOption *option,
                                 QPainter *painter, const QWidget *widget ) const
{
  //      PE_IndicatorArrowLeft,
 //       PE_IndicatorArrowRight,

    if( element == PE_IndicatorArrowUp || element == PE_IndicatorArrowDown ) 
    {
        QPolygon points( 3 );
        int x = option->rect.x();
        int y = option->rect.y();
        int w = option->rect.width() / 2;
        int h = option->rect.height() / 2;
        x += ( option->rect.width() - w ) / 2;
        y += ( option->rect.height() - h ) / 2;

        if( element == PE_IndicatorArrowUp ) 
        {
            points[ 0 ] = QPoint( x, y + h );
            points[ 1 ] = QPoint( x + w, y + h );
            points[ 2 ] = QPoint( x + w / 2, y );
        }
        else 
        { // PE_SpinBoxDown
            points[ 0 ] = QPoint( x, y );
            points[ 1 ] = QPoint( x + w, y );
            points[ 2 ] = QPoint( x + w / 2, y + h );
        }

       // painter->save();
        if( option->state & State_Enabled ) 
        {
            painter->setPen( option->palette.mid().color() );
            painter->setBrush( option->palette.buttonText() );
        }
        else 
        {
            painter->setPen( option->palette.buttonText().color() );
            painter->setBrush( option->palette.mid() );
        }
      
        //painter->setPen( QColor(COLOR_BLUE) );
        //painter->setBrush( QBrush( QColor(COLOR_RED) ) );

        painter->drawPolygon( points );
        //painter->restore();
    }
    else if( element == PE_IndicatorSpinUp || element == PE_IndicatorSpinDown ) 
    {
        painter->save();
        QPolygon points( 3 );
        int x = option->rect.x();
        int y = option->rect.y();
        int w = option->rect.width() / 2;
        int h = option->rect.height() / 2;
        x += ( option->rect.width() - w ) / 2;
        y += ( option->rect.height() - h ) / 2;

        if( element == PE_IndicatorSpinUp ) 
        {
            points[ 0 ] = QPoint( x, y + h );
            points[ 1 ] = QPoint( x + w, y + h );
            points[ 2 ] = QPoint( x + w / 2, y );
        }
        else 
        { // PE_SpinBoxDown
            points[ 0 ] = QPoint( x, y );
            points[ 1 ] = QPoint( x + w, y );
            points[ 2 ] = QPoint( x + w / 2, y + h );
        }

        /*
        if( option->state & State_Enabled ) 
        {
            painter->setPen( option->palette.mid().color() );
            painter->setBrush( option->palette.buttonText() );
        }
        else 
        {
            painter->setPen( option->palette.buttonText().color() );
            painter->setBrush( option->palette.mid() );
        }
        */
        painter->setPen( QColor(COLOR_BLUE) );
        painter->setBrush( QBrush( QColor(COLOR_RED) ) );

        painter->drawPolygon( points );
        painter->restore();
  }
    else 
    {
        QCommonStyle::drawPrimitive( element, option, painter, widget );
    }
}

