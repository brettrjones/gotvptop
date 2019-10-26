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

#include <config_gotvapps.h>

#include <QtGlobal>
#include <QProxyStyle>
#include <QCommonStyle>
#include <QProxyStyle>


class AppCommon;
class VxAppTheme;
class AppFocusFrame;
class QRect;

#ifdef TARGET_OS_WINDOWS
class VxAppStyle2 : public QProxyStyle
#else
class VxAppStyle2 : public QCommonStyle
#endif // TARGET_OS_WINDOWS
{
public:
    VxAppStyle2( AppCommon& appCommon, VxAppTheme& appTheme );
	virtual ~VxAppStyle2() override = default;

    enum GuiDrawDirection { eGuiDirUp, eGuiDirDown, eGuiDirLeft, eGuiDirRight };

    static int					focusFrameBoarderWidth(); // line width of focus frame

    void                        polish( QPalette &palette );

    void						drawFocusFrame( QPainter& painter, const QRect& focusRect ) const;
    void					    drawArrow( QPainter*, const QRect& rect, QColor arrowColor, GuiDrawDirection drawDir ) const;
    void					    drawComboBoxArrow( QPainter*, const QRect& rect, const QPalette& palette, bool enabled ) const;

    void                        drawControl( ControlElement	element, const QStyleOption* option,
                                             QPainter* painter, const QWidget* widget ) const override;

    virtual void				drawComplexControl( ComplexControl control,
                                                    const QStyleOptionComplex* option, QPainter* painter,
                                                    const QWidget* widget ) const override;

    virtual QPalette			standardPalette() const override;

    virtual int					styleHint( StyleHint hint, const QStyleOption* option,
                                           const QWidget* widget, QStyleHintReturn* returnData = nullptr ) const override;
protected:
    virtual bool				event( QEvent* ) override;

private:
	AppCommon&					m_MyApp;
	VxAppTheme&					m_AppTheme;
};

