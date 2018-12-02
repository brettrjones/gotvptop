//============================================================================
// Copyright (C) 2018 Brett R. Jones
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

#include "RenderGlWidget.h"
#include "AppCommon.h"
#include "AppGlobals.h"
#include "AppSettings.h"
#include "MyIcons.h"
#include "GuiHelpers.h"
#include "MyIcons.h"

#include "GoTvInterface/GoTvRenderFrame.h"

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>
#include <CoreLib/VxTimeUtil.h>

#include <QDebug>
#include <QTimer>
#include <QOpenGLFramebufferObjectFormat>
#include <QKeyEvent>

#include <time.h>

//============================================================================
RenderGlWidget::RenderGlWidget(QWidget *parent)
: RenderGlBaseWidget(parent)
, m_QtToKodi( m_MyApp )
, m_RenderWidgetInited( false )
, m_TexturesInited( false )
, m_Frame( 0 )
// shaders
, m_ShadersInited( false )
, m_CurShaderMethodType( SM_DEFAULT )
// render
, m_SrcWidth( 640 )
, m_SrcHeight( 480 )
{
}

//============================================================================
RenderGlWidget::~RenderGlWidget()
{
    if( QOpenGLContext::currentContext() )
    {
        for( int i = 0; i < SM_MAX; i++ )
        {
            if( m_Shaders[ i ] )
            {
                m_Shaders[ i ]->onFree();
                m_Shaders[ i ] = nullptr;
            }
        }
    }
}

//============================================================================
void RenderGlWidget::onInitializeGL( void )
{
    m_RenderWidgetInited = true;

    m_GlF->glDisable( GL_DEPTH_TEST );
    m_GlF->glClearColor( 0.2, 0.2, 0.2, 1 );

    if( RENDER_FROM_THREAD && m_KodiSurface )
    {
        m_KodiSurface->setRenderFunctions( m_GlF );
    }
}

//============================================================================
void RenderGlWidget::onPaintGL( void )
{
}

//============================================================================
void RenderGlWidget::onResizeGL( int w, int h )
{
    m_GlF->glViewport( 0, 0, w, h );
    m_QtToKodi.resizeEvent(  w, h );
}

//============================================================================
void RenderGlWidget::keyPressEvent( QKeyEvent * ev )
{
    if( ev->isAutoRepeat() )
        return;

    if( ! m_QtToKodi.keyPressEvent( ev->key() ) )
    {
        RenderGlBaseWidget::keyPressEvent( ev );
    }
}

//============================================================================
void RenderGlWidget::keyReleaseEvent( QKeyEvent * ev )
{
    if( ev->isAutoRepeat() )
        return;

    if( !m_QtToKodi.keyReleaseEvent( ev->key() ) )
    {
        RenderGlBaseWidget::keyReleaseEvent( ev );
    }
}

//============================================================================
void RenderGlWidget::mousePressEvent( QMouseEvent * ev )
{
    if( !m_QtToKodi.mousePressEvent( ev->x(), ev->y(), ev->button() ) )
    {
        RenderGlBaseWidget::mousePressEvent( ev );
    }
}

//============================================================================
void RenderGlWidget::mouseReleaseEvent( QMouseEvent * ev )
{
    if( !m_QtToKodi.mouseReleaseEvent( ev->x(), ev->y(), ev->button() ) )
    {
        RenderGlBaseWidget::mouseReleaseEvent( ev );
    }
}

//============================================================================
void RenderGlWidget::mouseMoveEvent( QMouseEvent * ev )
{
    if( !m_QtToKodi.mouseMoveEvent( ev->x(), ev->y() ) )
    {
        RenderGlBaseWidget::mouseMoveEvent( ev );
    }
}
