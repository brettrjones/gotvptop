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
#include "GoTvDebugConfig.h"
#include "RenderGlOffScreenSurface.h"

#include "GoTvInterface/GoTvRenderFrame.h"

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>
#include <CoreLib/VxTimeUtil.h>

#include <QDebug>
#include <QTimer>
#include <QOpenGLFramebufferObjectFormat>
#include <QKeyEvent>

#include <time.h>
#include <GL/glu.h>

const int RESIZE_WINDOW_COMPLETED_TIMEOUT = 500;

//============================================================================
RenderGlWidget::RenderGlWidget(QWidget *parent)
: RenderGlBaseWidget(parent)
, m_QtToKodi( m_MyApp )
//, m_RenderWidgetInited( false )
, m_TexturesInited( false )
, m_Frame( 0 )
// shaders
, m_ShadersInited( false )
, m_CurShaderMethodType( SM_DEFAULT )
// render
, m_SrcWidth( 640 )
, m_SrcHeight( 480 )
, m_ResizingTimer( new QTimer( this ) )
{
	connect( m_ResizingTimer, SIGNAL( timeout() ), this, SLOT( slotResizeWindowTimeout() ) );
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
    /*
    m_RenderWidgetInited = true;

    m_GlF->glDisable( GL_DEPTH_TEST );
    m_GlF->glClearColor( 0.2, 0.2, 0.2, 1 );
#ifndef DEBUG_OPENGL
    m_KodiSurface->setRenderFunctions( m_GlF );
#else
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glEnable(GL_POLYGON_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif // DEBUG_OPENGL
*/
}

//============================================================================
void RenderGlWidget::onPaintGL( void )
{
    #ifdef DEBUG_OPENGL
    // paint something as visual test

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    glVertex2f(0,0);
    glVertex2f(100,500);
    glVertex2f(500,100);
    glEnd();

    update();
    #endif// DEBUG_OPENGL
}

//============================================================================
void RenderGlWidget::onResizeGL( int w, int h )
{

	m_ResizingWindowSize = QSize( w, h );
    m_GlF->glViewport( 0, 0, w, h );
    if( !m_IsResizing )
	{
		m_IsResizing = true;
		onResizeBegin( m_ResizingWindowSize );
	}

	onResizeEvent( m_ResizingWindowSize );
    m_ResizingTimer->stop();
	m_ResizingTimer->setSingleShot( true );
	m_ResizingTimer->start( RESIZE_WINDOW_COMPLETED_TIMEOUT );

	onResizeEvent( m_ResizingWindowSize );

    #ifdef DEBUG_OPENGL
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, w, 0, h); // set origin to bottom left corner
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    #endif// DEBUG_OPENGL
}


//============================================================================
void RenderGlWidget::onResizeBegin( QSize& newSize )
{
 #ifndef DEBUG_OPENGL
	m_QtToKodi.fromGuiResizeBegin( newSize.width(), newSize.height() );
 #endif // DEBUG_OPENGL
}

//============================================================================
void RenderGlWidget::onResizeEvent( QSize& newSize )
{
    #ifndef DEBUG_OPENGL
	m_QtToKodi.fromGuiResizeEvent( newSize.width(), newSize.height() );
     #endif // DEBUG_OPENGL
	// evedently the kodi surface does not respond to signals and slots.. must set it directly
	if( m_KodiSurface )
	{
		m_KodiSurface->glWidgetWasResized( m_ResizingWindowSize );
	}
}

//============================================================================
void RenderGlWidget::onResizeEnd( QSize& newSize )
{
    #ifndef DEBUG_OPENGL
	m_QtToKodi.fromGuiResizeEnd( newSize.width(), newSize.height() );
   #endif // DEBUG_OPENGL
}

//============================================================================
void RenderGlWidget::onModuleState( int moduleNum, int moduleState )
{
    #ifndef DEBUG_OPENGL
	if( ( moduleNum == eModuleKodi ) && ( moduleState == eModuleStateInitialized ) )
	{
		// send a resize message so kodi will resize to fit window
		m_QtToKodi.fromGuiResizeEnd( geometry().width(), geometry().height() );
	}
    #endif // DEBUG_OPENGL
}

//============================================================================
void RenderGlWidget::keyPressEvent( QKeyEvent * ev )
{
    if( ev->isAutoRepeat() )
        return;

    if( ! m_QtToKodi.fromGuiKeyPressEvent( ev->key() ) )
    {
        RenderGlBaseWidget::keyPressEvent( ev );
    }
}

//============================================================================
void RenderGlWidget::keyReleaseEvent( QKeyEvent * ev )
{
    if( ev->isAutoRepeat() )
        return;

    if( !m_QtToKodi.fromGuiKeyReleaseEvent( ev->key() ) )
    {
        RenderGlBaseWidget::keyReleaseEvent( ev );
    }
}

//============================================================================
void RenderGlWidget::mousePressEvent( QMouseEvent * ev )
{
    if( !m_QtToKodi.fromGuiMousePressEvent( ev->x(), ev->y(), ev->button() ) )
    {
        RenderGlBaseWidget::mousePressEvent( ev );
    }
}

//============================================================================
void RenderGlWidget::mouseReleaseEvent( QMouseEvent * ev )
{
    if( !m_QtToKodi.fromGuiMouseReleaseEvent( ev->x(), ev->y(), ev->button() ) )
    {
        RenderGlBaseWidget::mouseReleaseEvent( ev );
    }
}

//============================================================================
void RenderGlWidget::mouseMoveEvent( QMouseEvent * ev )
{
    if( !m_QtToKodi.fromGuiMouseMoveEvent( ev->x(), ev->y() ) )
    {
        RenderGlBaseWidget::mouseMoveEvent( ev );
    }
}

//============================================================================
void RenderGlWidget::slotResizeWindowTimeout()
{
	if( m_IsResizing )
	{
		m_IsResizing = false;
		onResizeEnd( m_ResizingWindowSize );
	}
}
