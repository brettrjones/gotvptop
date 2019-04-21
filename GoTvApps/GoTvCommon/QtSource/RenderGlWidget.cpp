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
#include <QtGui/qopenglfunctions.h>
#include <QPainter>

#include <time.h>
#include <GL/glu.h>

const int RESIZE_WINDOW_COMPLETED_TIMEOUT = 500;

//============================================================================
RenderGlWidget::RenderGlWidget(QWidget *parent)
: QOpenGLWidget(parent)
, m_MyApp( GetAppInstance() )
, m_QtToKodi( m_MyApp )
, m_RenderLogic( *this )
, m_ScreenSize( 1, 1 )
, m_ResizingWindowSize( 1, 1 )
, m_ResizingTimer( new QTimer( this ) )
{
    memset( m_viewPort, 0, sizeof( m_viewPort ) );
    memset( m_TextureIds, 0, sizeof( m_TextureIds ) );
    memset( m_TexSize, 0, sizeof( m_TexSize ) );

    //setMinimumSize(32, 32);
	connect( m_ResizingTimer, SIGNAL( timeout() ), this, SLOT( slotResizeWindowTimeout() ) );
    connect( &m_RenderLogic, SIGNAL( signalFrameRendered() ), this, SLOT( slotOnFrameRendered() ) );

//     connect(this, &QOpenGLWidget::aboutToCompose, this, &RenderGlWidget::onAboutToCompose);
//     connect(this, &QOpenGLWidget::frameSwapped, this, &RenderGlWidget::onFrameSwapped);
//     connect(this, &QOpenGLWidget::aboutToResize, this, &RenderGlWidget::onAboutToResize);
//     connect(this, &QOpenGLWidget::resized, this, &RenderGlWidget::onResized);
}

//============================================================================
RenderGlWidget::~RenderGlWidget()
{
    m_QtToKodi.fromGuiCloseEvent();
    m_RenderLogic.aboutToDestroy();
}

//============================================================================
void RenderGlWidget::takeSnapshot()
{
    if( m_RenderWidgetInited && m_RenderLogic.m_WidgetGlContext && m_RenderLogic.m_OffScreenSurface )
    {
        m_RenderLogic.lockRenderer();
        QImage frameImage = m_RenderLogic.m_OffScreenSurface->getLastRenderedImage();
        if( !frameImage.isNull() )
        {
            frameImage.save( QString( "F:\\GoTvPtoP_Image.png" ) );
        }

        m_RenderLogic.unlockRenderer();
    }
}

//============================================================================
void RenderGlWidget::initializeGL()
{
    initializeOpenGLFunctions();
    m_RenderLogic.m_WidgetGlContext = this->context();

    makeCurrent();
    m_GlWidgetFunctions = m_RenderLogic.m_WidgetGlContext->functions();
    Q_ASSERT( m_GlWidgetFunctions );
    m_GlWidgetFunctions->initializeOpenGLFunctions();

    m_RenderLogic.m_ThreadGlContext = new QOpenGLContext;
    m_RenderLogic.m_ThreadGlContext->setShareContext( m_RenderLogic.m_WidgetGlContext ); // required
    m_RenderLogic.m_ThreadGlContext->setFormat( m_RenderLogic.m_WidgetGlContext->format() );
    m_RenderLogic.m_ThreadGlContext->create();

    m_GlThreadFunctions = m_RenderLogic.m_ThreadGlContext->functions();
    Q_ASSERT( m_GlThreadFunctions );
    m_GlThreadFunctions->initializeOpenGLFunctions();


    m_RenderLogic.m_OffScreenSurface = new RenderGlOffScreenSurface( m_RenderLogic.m_RenderKodiThread, this, m_RenderLogic.m_WidgetGlContext, m_RenderLogic.m_ThreadGlContext ); // BRJ geometry not set at this point nullptr, geometry().size() );
    m_RenderLogic.m_OffScreenSurface->setFormat( m_RenderLogic.m_ThreadGlContext->format() );
    m_RenderLogic.m_OffScreenSurface->create();
    m_RenderLogic.m_OffScreenSurface->setRenderFunctions( m_GlThreadFunctions );

    m_RenderLogic.glWidgetInitialized();
    doneCurrent();
    m_RenderWidgetInited = true;
    m_RenderLogic.startRenderThread();
}

//============================================================================
void RenderGlWidget::paintGL()
{
    if( m_RenderWidgetInited && m_RenderLogic.m_WidgetGlContext && m_RenderLogic.m_OffScreenSurface )
    {

        m_RenderLogic.lockRenderer();
        QImage frameImage = m_RenderLogic.m_OffScreenSurface->getLastRenderedImage();
        m_RenderLogic.unlockRenderer();

        QPainter painter;
        painter.begin( this );

        painter.setRenderHints( QPainter::Antialiasing );
        painter.drawImage( 0, 0, frameImage );

        painter.end();


        /*
        m_RenderLogic.setSurfaceSize( geometry().size() );
        if( !m_RenderLogic.isRenderThreadStarted() )
        {
            m_RenderLogic.startRenderThread();
        }
        else
        {
            m_RenderLogic.lockRenderer();

            m_RenderLogic.m_WidgetGlContext->makeCurrent( m_RenderLogic.m_OffScreenSurface );
            QOpenGLPaintDevice fboPaintDev( width(), height() );
            QPainter painter( &fboPaintDev );
            painter.setRenderHints( QPainter::Antialiasing | QPainter::TextAntialiasing );
            QImage frameImage = m_RenderLogic.m_OffScreenSurface->getLastRenderedImage();
            if( !frameImage.isNull() )
            {
                painter.drawImage( 0, 0, frameImage );
            }

            painter.end();

           m_RenderLogic.unlockRenderer();
        }
    */
    }
}

//============================================================================
void RenderGlWidget::resizeGL( int width, int height )
{
    m_RenderLogic.setSurfaceSize( QSize( width, height ) );
}

//============================================================================
bool RenderGlWidget::beginRender()
{
    return m_RenderLogic.beginRenderGl();
}

//============================================================================
bool RenderGlWidget::endRender()
{
    return m_RenderLogic.endRenderGl();
}

//============================================================================
void RenderGlWidget::presentRender( bool rendered, bool videoLayer )
{
    m_RenderLogic.presentRenderGl( rendered, videoLayer );
}

//============================================================================
void RenderGlWidget::slotOnFrameRendered()
{
    update();
}

//============================================================================
void RenderGlWidget::showEvent( QShowEvent * ev )
{
    QOpenGLWidget::showEvent( ev );
    m_RenderLogic.setRenderWindowVisible( true );
}

//============================================================================
void RenderGlWidget::hideEvent( QHideEvent * ev )
{
    m_RenderLogic.setRenderWindowVisible( false );
    QOpenGLWidget::hideEvent( ev );
}

//============================================================================
void RenderGlWidget::closeEvent( QCloseEvent * ev )
{
    m_RenderLogic.setRenderThreadShouldRun(false);
    m_QtToKodi.fromGuiCloseEvent();
    QOpenGLWidget::closeEvent( ev );
}

//============================================================================
void RenderGlWidget::resizeEvent( QResizeEvent * ev )
{
    QOpenGLWidget::resizeEvent( ev );
    m_RenderLogic.setSurfaceSize( ev->size() );
    m_ResizingWindowSize = ev->size();
    if( !m_IsResizing )
	{
		m_IsResizing = true;
		onResizeBegin( m_ResizingWindowSize );
	}

	onResizeEvent( m_ResizingWindowSize );
    m_ResizingTimer->stop();
	m_ResizingTimer->setSingleShot( true );
	m_ResizingTimer->start( RESIZE_WINDOW_COMPLETED_TIMEOUT );
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
}

//============================================================================
void RenderGlWidget::onResizeEnd( QSize& newSize )
{
    #ifndef DEBUG_OPENGL
	m_QtToKodi.fromGuiResizeEnd( newSize.width(), newSize.height() );
   #endif // DEBUG_OPENGL
}

//============================================================================
void RenderGlWidget::onModuleState( EAppModule moduleNum, EModuleState moduleState )
{
    #ifndef DEBUG_OPENGL
	if( ( moduleNum == eAppModuleKodi ) && ( moduleState == eModuleStateInitialized ) )
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
        QOpenGLWidget::keyPressEvent( ev );
    }
}

//============================================================================
void RenderGlWidget::keyReleaseEvent( QKeyEvent * ev )
{
    if( ev->isAutoRepeat() )
        return;

    if( !m_QtToKodi.fromGuiKeyReleaseEvent( ev->key() ) )
    {
        QOpenGLWidget::keyReleaseEvent( ev );
    }
}

//============================================================================
void RenderGlWidget::mousePressEvent( QMouseEvent * ev )
{
    takeSnapshot();
    if( !m_QtToKodi.fromGuiMousePressEvent( ev->x(), ev->y(), ev->button() ) )
    {
        QOpenGLWidget::mousePressEvent( ev );
    }
}

//============================================================================
void RenderGlWidget::mouseReleaseEvent( QMouseEvent * ev )
{
    if( !m_QtToKodi.fromGuiMouseReleaseEvent( ev->x(), ev->y(), ev->button() ) )
    {
        QOpenGLWidget::mouseReleaseEvent( ev );
    }
}

//============================================================================
void RenderGlWidget::mouseMoveEvent( QMouseEvent * ev )
{
    if( !m_QtToKodi.fromGuiMouseMoveEvent( ev->x(), ev->y() ) )
    {
        QOpenGLWidget::mouseMoveEvent( ev );
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
