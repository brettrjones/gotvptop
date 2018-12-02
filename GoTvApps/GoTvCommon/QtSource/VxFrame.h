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

#include <QFrame>

class VxFrame : public QFrame
{
	Q_OBJECT
public:
	explicit VxFrame( QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags() );

	void						setFrameId( int frameId )		{ m_FrameId = frameId; }
	int							getFrameId( void )				{ return m_FrameId; }

signals:
	void						signalFrameResized();

protected:
	void						resizeEvent( QResizeEvent * ev );

	int							m_FrameId;
};