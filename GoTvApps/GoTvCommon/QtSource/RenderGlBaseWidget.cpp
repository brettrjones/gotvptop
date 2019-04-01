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

#include "RenderGlBaseWidget.h"
#include "AppCommon.h"
#include "AppGlobals.h"
#include "AppSettings.h"
#include "MyIcons.h"
#include "GuiHelpers.h"
#include "MyIcons.h"
#include "KodiThread.h"
#include "GoTvDebugConfig.h"
#include "RenderGlOffScreenSurface.h"

#include "GoTvInterface/GoTvRenderFrame.h"

#include <QOpenGLFramebufferObjectFormat>
#include <QOpenGLPaintDevice>


#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>
#include <CoreLib/VxTimeUtil.h>

#include <QDebug>
#include <QTimer>
#include <QThread>

#include <time.h>


//============================================================================
RenderGlBaseWidget::RenderGlBaseWidget(QWidget *parent)
: QOpenGLWidget(parent)
, m_MyApp( GetAppInstance() )
{
}

//============================================================================
bool RenderGlBaseWidget::isReadyForRender() const
{ 
	return m_RenderWidgetInited && m_KodiSurface && m_KodiSurface->isReadyForRender(); 
}

//============================================================================
void RenderGlBaseWidget::initializeGL( void )
{
    // create 2 fbos
    const QRect drawRect( geometry() );
    const QSize drawRectSize = drawRect.size();

    m_WidgetContext = this->context();
//#ifndef DEBUG_OPENGL
//    m_Context = m_KodiContext;
//    m_Context->makeCurrent( m_KodiSurface );
// #else
//    m_Context = m_WidgetContext;
//#endif // DEBUG_OPENGL

    m_Gl = m_WidgetContext->functions();
#if QT_VERSION < 0x050300
# if defined(QT_OPENGL_ES_2)
    m_GlF = m_WidgetContext->versionFunctions<QOpenGLFunctions_ES2>();
# else
    m_GlF = m_WidgetContext->versionFunctions<QOpenGLFunctions_1_1>();
# endif
#else
    m_GlF = m_Gl;
#endif
    Q_ASSERT( m_GlF );
    m_GlF->initializeOpenGLFunctions();

    GLint maxTextureSize = 0;
    m_GlF->glGetIntegerv( GL_MAX_TEXTURE_SIZE, &maxTextureSize );
    if( maxTextureSize )
    {
        m_MaxTextureSize = maxTextureSize;
    }

    m_GlF->glDisable( GL_DEPTH_TEST );
    m_GlF->glClearColor( 0.2, 0.2, 0.2, 1 );


#ifndef DEBUG_OPENGL

    // done with current (QOpenglWidget's) context
    //doneCurrent(); // not sure if needed

    m_KodiThread = new KodiThread( m_MyApp, this );

    m_KodiContext = new QOpenGLContext();
    m_KodiContext->setShareContext( m_WidgetContext );

    m_KodiContext->setFormat( m_WidgetContext->format() );
//    m_KodiContext->setFormat( this->requestedFormat() );
    m_KodiContext->create();

     // sigh.. must move the thread to itself
//#ifdef TARGET_OS_WINDOWS
//    m_KodiThread->moveToThread( m_KodiThread );
//#endif // TARGET_OS_WINDOWS

    // setup the background thread's surface
    // the surface must be created here in the qt qui thread
    m_KodiSurface = new RenderGlOffScreenSurface( m_KodiThread, this, m_KodiContext, nullptr,  drawRectSize );

    m_KodiSurface->setFormat( m_KodiContext->format() );
    m_KodiSurface->create();
    //m_KodiSurface->setRenderFunctions( m_GlF );

    //m_KodiThread->moveToThread( m_KodiThread );

    m_KodiThread->setRenderWidget( this );
    m_KodiThread->setGlContext( m_KodiContext );
    m_KodiThread->setGlSurface( m_KodiSurface );

    m_KodiContext->moveToThread( m_KodiThread );
    m_KodiSurface->moveToThread( m_KodiThread );

	//initShaders();

    // sigh.. must move the thread to itself
//#ifdef TARGET_OS_WINDOWS
//    m_KodiThread->moveToThread( m_KodiThread );
//#endif // TARGET_OS_WINDOWS

    connect( this, SIGNAL(signalGlResized( int, int )), m_KodiSurface, SLOT(slotGlResized( int, int )) );

    m_RenderWidgetInited = true;

    connect( this, SIGNAL(signalStartKodiThread()), this, SLOT(slotStartKodiThread()) );
    emit signalStartKodiThread();



#else
    doInitializeGL();
#endif // DEBUG_OPENGL
}

//============================================================================
void  RenderGlBaseWidget::slotStartKodiThread()
{
    m_KodiThread->start();
}

//============================================================================
#ifdef DEBUG
void  RenderGlBaseWidget::VerifyGLStateQtDbg( const char* szfile, const char* szfunction, int lineno )
{
    GLenum err = glGetError();
    if( err == GL_NO_ERROR )
        return;
    LogMsg( LOG_ERROR, "GL ERROR: %d\n", err );
    if( szfile && szfunction )
    {
       LogMsg( LOG_ERROR, "In file:%s function:%s line:%d", szfile, szfunction, lineno );
    }

}
#else
void RenderGlBaseWidget::VerifyGLStateQt()
{
    GLenum err = glGetError();
    if( err == GL_NO_ERROR )
        return;
    LogMsg( LOG_ERROR, "GL ERROR: %s\n", gluErrorString( err ) );
}
#endif 

//============================================================================
void RenderGlBaseWidget::doInitializeGL( void )
{
    /*
#ifndef DEBUG_OPENGL
    m_Context = m_KodiContext;
    m_Context->makeCurrent( m_KodiSurface );
 #else
    m_Context = m_WidgetContext;
#endif // DEBUG_OPENGL

    m_Gl = m_Context->functions();
#if QT_VERSION < 0x050300
# if defined(QT_OPENGL_ES_2)
    m_GlF = m_Context->versionFunctions<QOpenGLFunctions_ES2>();
# else
    m_GlF = m_Context->versionFunctions<QOpenGLFunctions_1_1>();
# endif
#else
    m_GlF = m_Gl;
#endif

    Q_ASSERT( m_GlF );
    m_GlF->initializeOpenGLFunctions();

    GLint maxTextureSize = 0;
    m_GlF->glGetIntegerv( GL_MAX_TEXTURE_SIZE, &maxTextureSize );
    if( maxTextureSize )
    {
        m_MaxTextureSize = maxTextureSize;
    }

    onInitializeGL();

    m_bRenderCreated = true;
    */
}

//============================================================================
void RenderGlBaseWidget::paintGL( void )
{
#ifndef DEBUG_OPENGL
    if( !isReadyForRender() )
    {
        // not ready yet
        return;
    }

//    LogMsg( LOG_DEBUG, " RenderGlBaseWidget::paintGL Surface size x(%d) y(%d)", surfaceSize.width(), surfaceSize.height() );
    m_WidgetContext->makeCurrent( m_KodiSurface );
    QOpenGLPaintDevice fboPaintDev( width(), height() );
    QPainter painter( &fboPaintDev );
    painter.setRenderHints( QPainter::Antialiasing | QPainter::TextAntialiasing );
    QImage frameImage = m_KodiSurface->getLastRenderedImage();
    if( !frameImage.isNull() )
    {
        painter.drawImage( 0, 0, frameImage );
    }

    painter.end();
#endif // DEBUG_OPENGL
    doPaintGL();
}

//============================================================================
void RenderGlBaseWidget::doPaintGL( void )
{
    onPaintGL();
}

//============================================================================
void RenderGlBaseWidget::resizeGL( int w, int h )
{
    LogMsg( LOG_DEBUG, "resizeGL x(%d) y(%d)", w, h );
    QOpenGLWidget::resizeGL( w, h );
    m_ScreenSize = QSize( w, h );

    doResizeGL( w, h );

    emit signalGlResized( w, h );
}

//============================================================================
void RenderGlBaseWidget::doResizeGL( int w, int h )
{
    if( m_RenderWidgetInited )
    {
        m_GlF->glViewport( 0, 0, w, h );
        onResizeGL( w, h );
    }
}

//============================================================================
void RenderGlBaseWidget::initYv12()
{
    Q_ASSERT( MAX_RENDER_PLANES== 3 );

    m_TexDescriptor.m_Target            = GL_TEXTURE_2D;
    m_TexDescriptor.m_InternalFormat    = GL_LUMINANCE;
    m_TexDescriptor.m_Format            = GL_LUMINANCE;
    m_TexDescriptor.m_Type              = GL_UNSIGNED_BYTE;
}

//============================================================================
void RenderGlBaseWidget::initColorMatrix()
{
    m_ColorMatrix = QMatrix4x4( 1.0, 0.0, 0.0, 0.0,
                                0.0, 1.0, 0.0, 0.0,
                                0.0, 0.0, 1.0, 0.0,
                                0.0, 0.0, 0.0, 1.0 );
    QMatrix4x4 colorSpaceMatrix;
//    if( m_Frame->height > 576 )
        colorSpaceMatrix =
        QMatrix4x4(
            1.164383561643836, 0.000000000000000, 1.792741071428571, -0.972945075016308,
            1.164383561643836, -0.213248614273730, -0.532909328559444, 0.301482665475862,
            1.164383561643836, 2.112401785714286, 0.000000000000000, -1.133402217873451,
            0.000000000000000, 0.000000000000000, 0.000000000000000, 1.000000000000000 );
    //else
    //    colorSpaceMatrix =
    //    QMatrix4x4(
    //        1.164383561643836, 0.000000000000000, 1.596026785714286, -0.874202217873451,
    //        1.164383561643836, -0.391762290094914, -0.812967647237771, 0.531667823499146,
    //        1.164383561643836, 2.017232142857142, 0.000000000000000, -1.085630789302022,
    //        0.000000000000000, 0.000000000000000, 0.000000000000000, 1.000000000000000 );
    m_ColorMatrix = m_ColorMatrix * colorSpaceMatrix;
}
