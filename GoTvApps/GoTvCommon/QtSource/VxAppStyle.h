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
// http://www.gotvptop.net
//============================================================================

#include <config_gotvapps.h>

#include <QtGlobal>
#include <QProxyStyle>
#include <QCommonStyle>

class AppCommon;
class VxAppTheme;
class AppFocusFrame;
class QRect;

class VxAppStyle : public QCommonStyle
{
public:
	VxAppStyle( AppCommon& appCommon, VxAppTheme& appTheme );
	virtual ~VxAppStyle();

    void drawPrimitive( PrimitiveElement element, const QStyleOption *option,
                        QPainter *painter, const QWidget *widget ) const;

	void						drawFocusFrame( QPainter& painter, const QRect& focusRect );
	static int					focusFrameWidth();

protected:
	virtual bool				event( QEvent* ) override;

private:
	AppCommon&					m_MyApp;
	VxAppTheme&					m_AppTheme;
};

