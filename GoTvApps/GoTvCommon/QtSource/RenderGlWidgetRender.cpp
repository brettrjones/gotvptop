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
#include "RenderKodiThread.h"
#include "RenderGlOffScreenSurface.h"
#include "GoTvDebugConfig.h"

#include "GoTvInterface/GoTvRenderFrame.h"

#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>
#include <CoreLib/VxTimeUtil.h>
#include <CoreLib/VxThread.h>

#include "rendering/MatrixGL.h"
#include <GL/GLU.h>


//============================================================================
//=== to gui media/render ===//
//============================================================================

//============================================================================
// called from kodi thread when initializing kodi
// if never gets called then kodi failed to initialize and is a fatal error
bool RenderGlWidget::initRenderSystem()
{
#ifdef DEBUG_RENDER_THREADS
    setRenderThreadId( VxGetCurrentThreadId() );
#endif // DEBUG_RENDER_THREADS

    m_RenderLogic.initRenderGlSystem();

    return m_RenderWidgetInited;
}

//============================================================================
bool RenderGlWidget::destroyRenderSystem()
{
	m_RenderWidgetInited = false;
    m_RenderLogic.destroyRenderGlSystem();

    return true;
}


//============================================================================
void RenderGlWidget::captureScreen( CScreenshotSurface * screenCaptrue, GoTvRect& captureArea )
{

}

//============================================================================
void RenderGlWidget::toGuiRenderVideoFrame( int textureIdx, CRenderBuffer* videoBuffer )
{
}

//============================================================================
bool RenderGlWidget::resetRenderSystem( int width, int height )
{
    m_SrcWidth = width;
    m_SrcHeight = height;

    GoTvRect rect( 0, 0, width, height );
    setViewPort( rect );

    //m_GlThreadFunctions->glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    //m_GlThreadFunctions->glClearColor( 0.5f, 0.1f, 0.2f, 1.0f );
    m_GlThreadFunctions->glClearColor( 0.1f, 0.0f, 0.2f, 1.0f );

    m_GlThreadFunctions->glEnable( GL_SCISSOR_TEST );

    glMatrixProject.Clear();
    glMatrixProject->LoadIdentity();
    glMatrixProject->Ortho( 0.0f, width - 1, height - 1, 0.0f, -1.0f, 1.0f );
    glMatrixProject.Load();

    glMatrixModview.Clear();
    glMatrixModview->LoadIdentity();
    glMatrixModview.Load();

    glMatrixTexture.Clear();
    glMatrixTexture->LoadIdentity();
    glMatrixTexture.Load();

    m_GlThreadFunctions->glBlendFunc( GL_SRC_ALPHA, GL_ONE );
    m_GlThreadFunctions->glEnable( GL_BLEND );          // Turn Blending On
    m_GlThreadFunctions->glDisable( GL_DEPTH_TEST );

    return true;
}

//============================================================================
bool RenderGlWidget::clearBuffers( GoTvColor color )
{
	if( !m_RenderWidgetInited )
	{
		return false;
	}

    float r = GET_R( color ) / 255.0f;
    float g = GET_G( color ) / 255.0f;
    float b = GET_B( color ) / 255.0f;
    float a = GET_A( color ) / 255.0f;

    //m_GlThreadFunctions->glClearColor( r, g, b, a );
    //glClearColor( 0.1f, 0.1f, 0.2f, 1.0f );

    GLbitfield flags = GL_COLOR_BUFFER_BIT;
    m_GlThreadFunctions->glClear( flags );

    return true;
}

//============================================================================
bool RenderGlWidget::isExtSupported( const char* extension )
{
    if( strcmp( extension, "GL_EXT_framebuffer_object" ) == 0 )
    {
        // GLES has FBO as a core element, not an extension!
        return true;
    }
    else if( strcmp( extension, "GL_TEXTURE_NPOT" ) == 0 )
    {
        // GLES supports non-power-of-two textures as standard.
        return true;
        /* Note: The wrap mode can only be GL_CLAMP_TO_EDGE and the minification filter can only be
         * GL_NEAREST or GL_LINEAR (in other words, not mipmapped). The extension GL_OES_texture_npot
         * relaxes these restrictions and allows wrap modes of GL_REPEAT and GL_MIRRORED_REPEAT and
         * also	allows npot textures to be mipmapped with the full set of minification filters
         */
    }

    return false;
}

//============================================================================
void RenderGlWidget::setVSync( bool vsync )
{
}

//============================================================================
void RenderGlWidget::setViewPort( const GoTvRect& viewPort )
{
    m_GlThreadFunctions->glScissor( ( GLint )viewPort.x1, ( GLint )( m_SrcHeight - viewPort.y1 - viewPort.Height() ), ( GLsizei )viewPort.Width(), ( GLsizei )viewPort.Height() );
    m_GlThreadFunctions->glViewport( ( GLint )viewPort.x1, ( GLint )( m_SrcHeight - viewPort.y1 - viewPort.Height() ), ( GLsizei )viewPort.Width(), ( GLsizei )viewPort.Height() );
    m_viewPort[ 0 ] = viewPort.x1;
    m_viewPort[ 1 ] = m_SrcHeight - viewPort.y1 - viewPort.Height();
    m_viewPort[ 2 ] = viewPort.Width();
    m_viewPort[ 3 ] = viewPort.Height();
/*
    m_GlThreadFunctions->glScissor( (GLint)viewPort.x1, (GLint)( viewPort.y1 ), (GLsizei)viewPort.Width(), (GLsizei)viewPort.Height() );
    m_GlThreadFunctions->glViewport( (GLint)viewPort.x1, (GLint)( viewPort.y1 ), (GLsizei)viewPort.Width(), (GLsizei)viewPort.Height() );
    glScissor( (GLint)viewPort.x1, (GLint)( viewPort.y1 ), (GLsizei)viewPort.Width(), (GLsizei)viewPort.Height() );
    glViewport( (GLint)viewPort.x1, (GLint)( viewPort.y1 ), (GLsizei)viewPort.Width(), (GLsizei)viewPort.Height() );

    m_viewPort[ 0 ] = viewPort.x1;
    m_viewPort[ 1 ] = viewPort.y1;
    m_viewPort[ 2 ] = viewPort.Width();
    m_viewPort[ 3 ] = viewPort.Height();
    */
}

//============================================================================
void RenderGlWidget::getViewPort( GoTvRect& viewPort )
{
    viewPort.x1 = 0;
    viewPort.y1 = 0;
    viewPort.x2 = width();
    viewPort.y2 = height();
}

//============================================================================
bool RenderGlWidget::scissorsCanEffectClipping()
{
    return true;
}

//============================================================================
GoTvRect RenderGlWidget::clipRectToScissorRect( const GoTvRect &rect )
{
    return rect;
}

//============================================================================
void RenderGlWidget::setScissors( const GoTvRect& rect )
{
}

//============================================================================
void RenderGlWidget::resetScissors()
{
}

//============================================================================
void RenderGlWidget::captureStateBlock()
{
    glMatrixProject.Push();
    glMatrixModview.Push();
    glMatrixTexture.Push();

    m_GlThreadFunctions->glDisable( GL_SCISSOR_TEST ); // fixes FBO corruption on Macs
    m_GlThreadFunctions->glActiveTexture( GL_TEXTURE0 );
}

//============================================================================
void RenderGlWidget::applyStateBlock()
{
    glMatrixProject.PopLoad();
    glMatrixModview.PopLoad();
    glMatrixTexture.PopLoad();
    m_GlThreadFunctions->glActiveTexture( GL_TEXTURE0 );
    m_GlThreadFunctions->glEnable( GL_BLEND );
    m_GlThreadFunctions->glEnable( GL_SCISSOR_TEST );
    m_GlThreadFunctions->glClear( GL_DEPTH_BUFFER_BIT );
}

//============================================================================
void RenderGlWidget::setCameraPosition( const GoTvPoint& camera, int screenWidth, int screenHeight, float stereoFactor )
{
	if( !m_RenderWidgetInited )
	{
		return;
	}

    GoTvPoint offset = camera - GoTvPoint( screenWidth*0.5f, screenHeight*0.5f );

    float w = ( float )m_viewPort[ 2 ] * 0.5f;
    float h = ( float )m_viewPort[ 3 ] * 0.5f;

    glMatrixModview->LoadIdentity();
    glMatrixModview->Translatef( -( w + offset.x - stereoFactor ), +( h + offset.y ), 0 );
    glMatrixModview->LookAt( 0.0, 0.0, -2.0*h, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0 );
    glMatrixModview.Load();

    glMatrixProject->LoadIdentity();
    glMatrixProject->Frustum( ( -w - offset.x )*0.5f, ( w - offset.x )*0.5f, ( -h + offset.y )*0.5f, ( h + offset.y )*0.5f, h, 100 * h );
    glMatrixProject.Load();
}

//============================================================================
void RenderGlWidget::applyHardwareTransform( const TransformMatrix& finalMatrix )
{
    if( !m_RenderWidgetInited )
        return;

    glMatrixModview.Push();
    glMatrixModview->MultMatrixf( finalMatrix );
    glMatrixModview.Load();
}

//============================================================================
void RenderGlWidget::restoreHardwareTransform()
{
    if( !m_RenderWidgetInited )
        return;

    glMatrixModview.PopLoad();
}

//============================================================================
bool RenderGlWidget::testRender()
{
    static float theta = 0.0;

    //RESOLUTION_INFO resInfo = CDisplaySettings::GetInstance().GetCurrentResolutionInfo();
    //glViewport(0, 0, resInfo.iWidth, resInfo.iHeight);

    glMatrixModview.Push();
    glMatrixModview->Rotatef( theta, 0.0f, 0.0f, 1.0f );

    enableShader( SM_DEFAULT );

    GLfloat col[ 4 ] = { 1.0f, 0.0f, 0.0f, 1.0f };
    GLfloat ver[ 3 ][ 2 ];
    GLint   posLoc = shaderGetPos();
    GLint   colLoc = shaderGetCol();

    m_GlThreadFunctions->glVertexAttribPointer( posLoc, 2, GL_FLOAT, 0, 0, ver );
    m_GlThreadFunctions->glVertexAttribPointer( colLoc, 4, GL_FLOAT, 0, 0, col );

    m_GlThreadFunctions->glEnableVertexAttribArray( posLoc );
    m_GlThreadFunctions->glEnableVertexAttribArray( colLoc );

    // Setup vertex position values
    ver[ 0 ][ 0 ] = 0.0f;
    ver[ 0 ][ 1 ] = 1.0f;
    ver[ 1 ][ 0 ] = 0.87f;
    ver[ 1 ][ 1 ] = -0.5f;
    ver[ 2 ][ 0 ] = -0.87f;
    ver[ 2 ][ 1 ] = -0.5f;

    m_GlThreadFunctions->glDrawArrays( GL_TRIANGLES, 0, 3 );

    m_GlThreadFunctions->glDisableVertexAttribArray( posLoc );
    m_GlThreadFunctions->glDisableVertexAttribArray( colLoc );

    disableGUIShader();

    glMatrixModview.Pop();

    theta += 1.0f;

    return true;
}

//============================================================================
void RenderGlWidget::project( float &x, float &y, float &z )
{
    /*
    GLfloat coordX, coordY, coordZ;
    if( CMatrixGL::Project( x, y, z, glMatrixModview.Get(), glMatrixProject.Get(), m_viewPort, &coordX, &coordY, &coordZ ) )
    {
        x = coordX;
        y = ( float )( m_viewPort[ 1 ] + m_viewPort[ 3 ] - coordY );
        z = 0;
    }*/
}

// frame buffers
//============================================================================
void RenderGlWidget::frameBufferGen( int bufCount, unsigned int* fboId )
{
    m_GlThreadFunctions->glGenFramebuffers( bufCount, fboId );
}

//============================================================================
void RenderGlWidget::frameBufferDelete( int bufCount, unsigned int* fboId )
{
    m_GlThreadFunctions->glDeleteFramebuffers( bufCount, fboId );
}

//============================================================================
void RenderGlWidget::frameBufferTexture2D( int target, unsigned int texureId )
{
    m_GlThreadFunctions->glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, target, texureId, 0 );
}

//============================================================================
void RenderGlWidget::frameBufferBind( unsigned int fboId )
{
    m_GlThreadFunctions->glBindFramebuffer( GL_FRAMEBUFFER, fboId );
}

//============================================================================
bool RenderGlWidget::frameBufferStatus()
{
    GLenum status = m_GlThreadFunctions->glCheckFramebufferStatus( GL_FRAMEBUFFER );
    return ( status == GL_FRAMEBUFFER_COMPLETE );
}

//============================================================================
#ifdef DEBUG
void  RenderGlWidget::VerifyGLStateQtDbg( const char* szfile, const char* szfunction, int lineno )
{
    GLenum err = glGetError();
    if( err == GL_NO_ERROR )
        return;
    LogMsg( LOG_ERROR, "GL ERROR: %d thread %d %s\n", err, VxGetCurrentThreadId(), gluErrorString( err ) );
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
void RenderGlWidget::verifyGlState( const char * msg ) // show gl error if any
{
#ifdef DEBUG_RENDER_THREADS
    if( msg && getRenderThreadId() && ( getRenderThreadId() != VxGetCurrentThreadId() ) )
    {
        LogMsg( LOG_ERROR, "ERROR %s render thread 0x%X != current thread %d ", msg, getRenderThreadId(), VxGetCurrentThreadId() );
    }
#endif // DEBUG_RENDER_THREADS

#ifdef DEBUG_LOG_RENDER_CALLS
    if( msg && getRenderThreadId() && ( getRenderThreadId() != VxGetCurrentThreadId() ) )
    {
        LogMsg( LOG_ERROR, "ERROR %s render thread 0x%X != thread %d ", msg, getRenderThreadId(), VxGetCurrentThreadId() );
    }
    else if( msg )
    {
        LogMsg( LOG_ERROR, "gl func %s render thread %d ", msg, getRenderThreadId() );
    }

#endif // DEBUG_RENDER_THREADS

    VerifyGLStateQt();
}
