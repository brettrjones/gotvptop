//============================================================================
// Copyright (C) 2009 Brett R. Jones 
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

#include "AppCommon.h"	

#include <GoTvInterface/IGoTv.h>

//============================================================================
void AppCommon::keyPressEvent( int moduleNum, int key, int mod )
{
	m_GoTv.keyPressEvent( moduleNum, key, mod );
}

//============================================================================
void AppCommon::keyReleaseEvent( int moduleNum, int key, int mod )
{
    m_GoTv.keyReleaseEvent( moduleNum, key, mod );
}

//============================================================================
void AppCommon::mousePressEvent( int moduleNum, int mouseXPos, int mouseYPos, int mouseButton )
{
    m_GoTv.mousePressEvent( moduleNum, mouseXPos, mouseYPos, mouseButton );
}

//============================================================================
void AppCommon::mouseReleaseEvent( int moduleNum, int mouseXPos, int mouseYPos, int mouseButton )
{
    m_GoTv.mouseReleaseEvent( moduleNum, mouseXPos, mouseYPos, mouseButton );
}

//============================================================================
void AppCommon::mouseMoveEvent( int moduleNum, int mouseXPos, int mouseYPos )
{
    m_GoTv.mouseMoveEvent( moduleNum, mouseXPos, mouseYPos );
}

//============================================================================
void AppCommon::resizeEvent( int moduleNum, int winWidth, int winHeight )
{
    m_GoTv.resizeEvent( moduleNum, winWidth, winHeight );
}

//============================================================================
void AppCommon::closeEvent( int moduleNum )
{
    m_GoTv.closeEvent( moduleNum );
}

//============================================================================
void AppCommon::visibleEvent( int moduleNum, bool isVisible )
{
    m_GoTv.visibleEvent( moduleNum, isVisible );
}
