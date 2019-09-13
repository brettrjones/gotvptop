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
// http://www.gotvptop.com
//============================================================================

#include "config_gotvapps.h"

#include "AppDefs.h"
#include <QtSvg/QSvgRenderer>
#include <QPixmap>
#include <QIcon>
#include <QVector>
#include <QColor>
#include <QWidget>
#include <QPalette>

#define COLOR_TRANSPARENT						0,0,0,0
#define COLOR_BLACK								0,0,0,255
#define COLOR_WHITE								255,255,255,255
#define COLOR_ALMOST_WHITE						240,240,240,255

#define COLOR_RED								255,0,0,255
#define COLOR_GREEN								0,255,0,255
#define COLOR_LIME_GREEN						67,200,56,255
#define COLOR_BLUE								0,0,255,255
#define COLOR_MEDIUM_BLUE						0,195,203,255		// 
//#define COLOR_MEDIUM_BLUE						0,0,192,255
#define COLOR_YELLOW							255,255,0,255
#define COLOR_ORANGE							255,128,0,255
#define COLOR_PURPLE							128,0,128,255
#define COLOR_LAVENDER							230,230,250,255

#define COLOR_SEASHELL							255,245,238,255		// 
#define COLOR_LIGHT_PINK						254,195,203,255		//
#define COLOR_CREAM_WHITE						243,243,243,255		// 
#define COLOR_DISABLED_GREY						217,220,220,255		// 
#define COLOR_SILVER							192,192,192,255		// 
#define COLOR_MEDIUM_GREY						128,128,128,255		// 
#define COLOR_DARK_GREY							80,80,80,255		// 
#define COLOR_VERY_DARK_GREY					64,64,64,255		// 

#define COLOR_LIGHT_YELLOW						255,235,121,255		// 
#define COLOR_MEDIUM_YELLOW						255,215,0,255		// 
#define COLOR_BURNT_ORANGE						255,128,0,255		// 
#define COLOR_LIGHT_TAN							255,192,129,255		// 
#define COLOR_MEDIUM_ORANGE						242,148,0,255		// 
#define COLOR_DARK_RED							228,1,29,255		//  
#define COLOR_GOLDENROD							218,165,32,255		// 
#define COLOR_DARK_TAN							205,116,54,255		// 
#define COLOR_DARK_YELLOW						189,182,107,255		// 
#define COLOR_LIGHT_TURQUOISE					130,226,217,255		// 
#define COLOR_DARK_TURQUOISE					80,176,167,255		// 
#define COLOR_DARK_GREEN						66,166,42,255		// 
#define COLOR_LIGHT_BLUE						1,102,254,255		// 
#define COLOR_DARK_BLUE							1,108,180,255		// 
#define COLOR_DARK_PURPLE						0,0,153,255			// 

#define COLOR_UNKNOWN							254,153,254,254			// pink color to indicate has not been initialized

enum EThemeColorRole
{
	eFocusRect = 0,					

	eWindowBackground,
	eWindowTextColor,
	eWindowHighlightTextColor,

	eTitleBarBackground,
	eTitleBarTextText,

	// note: use button colors for icons also
	eButtonBackgroundNormal,
	eButtonBackgroundDisabled,
	eButtonBackgroundPressed,

	eButtonForegroundNormal,
	eButtonForegroundDisabled,
	eButtonForegroundPressed,

	eButtonTextNormal,
	eButtonTextDisabled,
	eButtonTextPressed,

	eLayerOverlayColor,
	eLayerNotifyColor, 
	
	eProgressBarColor,

	MaxThemeColorRole
};

enum EColorLayerType
{
	eColorLayerUnknown = 0,
	eColorLayerBackground,
	eColorLayerForeground,
	eColorLayerIcon,
	eColorLayerText,
	eColorLayerOverlay,
	eColorLayerNotify,

	eColorLayerCount // must be last
};

class AppCommon;
class VxFlatButton;
class VxProgressBar;
class QProgressBar;

class QWidget;
class QPalette;
class QBrush;
class QFrame;
class QLabel;
class QStyleOption;
class QPushButton;

class VxAppTheme : public QWidget
{
	Q_OBJECT
public:
	VxAppTheme( AppCommon& appCommon );

    virtual void                applyTheme( QWidget * widget );

	virtual void				selectTheme( EThemeType eThemeType );
	virtual QString				describeTheme( EThemeType eThemeType );

	virtual void				updateWindowTheme( void );
	virtual void				updateButton( QPushButton * button );
	virtual void				updateProgressBar( QProgressBar * progressBar );

	// draw background of button
	virtual	void				drawButton( QPushButton * button, QPainter& painter );
	// get button color for button layer depending on state ( pressed, hasFocus, etc. ) 
	virtual	QColor				getButtonColor( QPushButton * button, EColorLayerType colorLayer );
	// draw focus rectangle around widget
	virtual	void				drawFocusRect( QPainter& painter, const QRect& focusRect, int lineWidth );

	// render a svg resource into QPixmap of given size and color
	virtual QPixmap				svgRenderer( QString svgName, QSize imageSize, QColor iconColor );
	// render a svg resource into QPixmap of given size
	virtual QPixmap				svgRenderer( QString svgName, QSize imageSize );
	// draw a pixmap of equal width and height scaled to size of widget
	virtual void				drawBitmapOnWidget( QPainter& painter, QPixmap& widgetPixmap, QSize sizeOfWidget );
	// replace all non transparent pixels with newColor
	QPixmap						replaceImageColor( QPixmap srcImageIn, QColor newColor );

	virtual QPalette&			getBasePalette( void )						{ return m_BasePalette; }
	virtual QColor				getColor( EThemeColorRole colorRole );
	virtual bool				isValidColorRole( EThemeColorRole colorRole );
	// get color value as text suitable for Qt style sheets
	virtual QString				getColorValueAsText( const QColor& colorVal );
	// return true if colors are exactly equal ( including alpha channel )
	virtual bool				areColorsEqual( const QColor& colorVal1, const QColor& colorVal2 );

	virtual QColor&				getTransparentColor( void )					{ return m_TransparentColor; }
	virtual bool				isTransparentColor( const QColor& colorVal );
 
	// given a resource name and extension.. get the full path to that resource
	virtual QString				getResourceFullFileName( QString resourceName );

	// set highlight color ( mainly progress bar color )
	virtual void				setHighlightColor( QWidget* widget, const QColor highlightColor );
	// set background color of widget
	virtual void				setBackgroundColor( QWidget * widget, const QColor backgroundColor );
	// set background color of frame
	virtual void 				setBackgroundColor( QFrame * widget, const QColor backgroundColor );
	// set background color to transparent
	virtual void 				setWidgetBackgroundToTransparent( QWidget * widget );
	virtual void				setTextColor( const QColor& color, QWidget* widget );

	virtual void				setPainterPen( QPainter& painter, QColor penColor );
	virtual void				setPainterBrush( QPainter& painter, QColor brushColor );

	virtual QBrush				initBrush( const QColor& color );

protected:
	void						setWidgetPallette( QWidget* widget, QPalette & palette );
	QPalette					getWidgetPalette( QWidget* widget );

	AppCommon&					m_MyApp;
	QColor						m_TransparentColor;
	QColor						m_InvalidColor;

	QPalette					m_BasePalette;
	QSvgRenderer				m_SvgRenderer;
	QVector<QColor>				m_ThemeColors;
};
