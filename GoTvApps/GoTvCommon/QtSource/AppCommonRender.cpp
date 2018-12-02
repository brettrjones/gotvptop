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

#include "AppCommon.h"	
#include "AppGlobals.h"
#include "VxAppDisplay.h"
#include "MyIcons.h"
#include "PopupMenu.h"
#include "ToGuiActivityInterface.h"
#include "OffersMgr.h"
#include "MySndMgr.h"
#include "MyIcons.h"
#include "VxAppTheme.h"
#include "VxAppStyle.h"
#include "VxTilePositioner.h"

#include "HomeWindow.h"


#include "GuiOfferSession.h"

#include "AppSettings.h"
#include "AppletMgr.h"

#include "VxDataHelper.h"
#include "FileListReplySession.h"
#include "RenderGlWidget.h"


#include <PktLib/VxCommon.h>

#include <CoreLib/VxFileUtil.h>
#include <CoreLib/VxParse.h>
#include <CoreLib/VxGlobals.h>
#include <CoreLib/IsBigEndianCpu.h>
#include <CoreLib/VxGUID.h>


#include "VxDataHelper.h"
#include <NetLib/VxPeerMgr.h>


#include <QApplication>
#include <QMainWindow>
#include <QCloseEvent>
#include <QDesktopServices>
#include <QDebug>
#include <QSettings>


//============================================================================
RenderGlWidget * AppCommon::getRenderConsumer( void )
{
    return m_AppletMgr.getRenderConsumer();
}


//============================================================================
//=== to gui media/render ===//
//============================================================================

//============================================================================
//=== textures ===//
//============================================================================

//============================================================================
void AppCommon::setActiveGlTexture( unsigned int activeTextureNum )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->setActiveGlTexture( activeTextureNum );
    }
}

//============================================================================
void AppCommon::createTextureObject( CQtTexture * texture )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->createTextureObject( texture );
    }
}

//============================================================================
void AppCommon::destroyTextureObject( CQtTexture * texture )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->destroyTextureObject( texture );
    }
}

//============================================================================
bool AppCommon::loadToGPU( CQtTexture * texture )
{
    bool result = false;
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        result = glWidget->loadToGPU( texture );
    }

    return result;
}

//============================================================================
void AppCommon::bindToUnit( CQtTexture * texture, unsigned int unit )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->bindToUnit( texture, unit );
    }
}

//============================================================================
void AppCommon::beginGuiTexture( CGUITextureQt * guiTexture, GoTvColor color )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->beginGuiTexture( guiTexture, color );
    }
}

//============================================================================
void AppCommon::drawGuiTexture( CGUITextureQt * guiTexture, float * x, float * y, float * z, const GoTvRect& textureRect, const GoTvRect& diffuse, int orientation )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->drawGuiTexture( guiTexture, x, y, z, textureRect, diffuse, orientation );
    }
}

//============================================================================
void AppCommon::endGuiTexture( CGUITextureQt * guiTexture )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->endGuiTexture( guiTexture );
    }
}

//============================================================================
void AppCommon::drawQuad( const GoTvRect& rect, GoTvColor color, CBaseTexture * texture, const GoTvRect * texCoords )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->drawQuad( rect, color, texture, texCoords );
    }
}

//============================================================================
bool AppCommon::firstBegin( CGUIFontTTFQt * font )
{
    bool result = false;
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        result = glWidget->firstBegin( font );
    }

    return result;
}

//============================================================================
void AppCommon::lastEnd( CGUIFontTTFQt * font )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->lastEnd( font );
    }
}

//============================================================================
CVertexBuffer AppCommon::createVertexBuffer( CGUIFontTTFQt * font, const std::vector<SVertex>& vertices )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        return glWidget->createVertexBuffer( font, vertices );
    }

    CVertexBuffer vertBuf;
    return vertBuf;
}

//============================================================================
void AppCommon::destroyVertexBuffer( CGUIFontTTFQt * font, CVertexBuffer & vertBuffer )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->destroyVertexBuffer( font, vertBuffer );
    }
}


//============================================================================
void AppCommon::deleteHardwareTexture( CGUIFontTTFQt * font )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->deleteHardwareTexture( font );
    }
}

//============================================================================
void AppCommon::createStaticVertexBuffers( CGUIFontTTFQt * font )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->createStaticVertexBuffers( font );
    }
}

//============================================================================
void AppCommon::destroyStaticVertexBuffers( CGUIFontTTFQt * font )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->destroyStaticVertexBuffers( font );
    }
}


//============================================================================
//=== remder ===//
//============================================================================

//============================================================================
void AppCommon::captureScreen( CScreenshotSurface * screenCaptrue, GoTvRect& captureArea )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->captureScreen( screenCaptrue, captureArea );
    }
}

//============================================================================
void AppCommon::toGuiRenderVideoFrame( int textureIdx, CRenderBuffer* videoBuffer )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->toGuiRenderVideoFrame( textureIdx, videoBuffer );
    }
}

//============================================================================
bool AppCommon::initRenderSystem()
{
    bool result = false;
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        result = glWidget->initRenderSystem( );
    }

    return result;
}

//============================================================================
bool AppCommon::destroyRenderSystem()
{
    bool result = false;
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        result = glWidget->destroyRenderSystem();
    }

    return result;
}

//============================================================================
bool AppCommon::resetRenderSystem( int width, int height )
{
    bool result = false;
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        result = glWidget->resetRenderSystem( width, height );
    }

    return result;
}

//============================================================================
int AppCommon::getMaxTextureSize()
{ 
    int result = 0;
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        result = glWidget->getMaxTextureSize( );
    }

    return result;
}

//============================================================================
bool AppCommon::beginRender()
{
    bool result = false;
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        result = glWidget->beginRender( );
    }

    return result;
}

//============================================================================
bool AppCommon::endRender()
{
    bool result = false;
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        result = glWidget->endRender();
    }

    return result;
}

//============================================================================
void AppCommon::presentRender( bool rendered, bool videoLayer )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->presentRender( rendered, videoLayer );
    }
}

//============================================================================
bool AppCommon::clearBuffers( GoTvColor color )
{
    bool result = false;
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        result = glWidget->clearBuffers( color );
    }

    return result;
}

//============================================================================
bool AppCommon::isExtSupported( const char* extension )
{
    bool result = false;
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        result = glWidget->isExtSupported( extension );
    }

    return result;
}

//============================================================================
void AppCommon::setVSync( bool vsync )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->setVSync( vsync );
    }
}

//============================================================================
void AppCommon::setViewPort( const GoTvRect& viewPort )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->setViewPort( viewPort );
    }
}

//============================================================================
void AppCommon::getViewPort( GoTvRect& viewPort )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->getViewPort( viewPort );
    }
}

//============================================================================
bool AppCommon::scissorsCanEffectClipping()
{
    bool result = false;
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        result = glWidget->scissorsCanEffectClipping();
    }

    return result;
}

//============================================================================
GoTvRect AppCommon::clipRectToScissorRect( const GoTvRect &rect )
{
    GoTvRect result;
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        result = glWidget->clipRectToScissorRect( rect );
    }

    return result;
}

//============================================================================
void AppCommon::setScissors( const GoTvRect& rect )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->setScissors( rect );
    }
}

//============================================================================
void AppCommon::resetScissors()
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->resetScissors();
    }
}

//============================================================================
void AppCommon::captureStateBlock()
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->captureStateBlock();
    }
}

//============================================================================
void AppCommon::applyStateBlock()
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->applyStateBlock();
    }
}

//============================================================================
void AppCommon::setCameraPosition( const GoTvPoint& camera, int screenWidth, int screenHeight, float stereoFactor )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->setCameraPosition( camera, screenWidth, screenHeight, stereoFactor );
    }
}

//============================================================================
void AppCommon::applyHardwareTransform( const TransformMatrix &matrix )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->applyHardwareTransform( matrix );
    }
}

//============================================================================
void AppCommon::restoreHardwareTransform()
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->restoreHardwareTransform();
    }
}

//============================================================================
bool AppCommon::testRender()
{
    bool result = false;
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        result = glWidget->testRender();
    }

    return result;
}

//============================================================================
void AppCommon::project( float &x, float &y, float &z )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->project( x, y, z );
    }
}

//============================================================================
//=== shaders ===//
//============================================================================

//============================================================================
void AppCommon::initialiseShaders()
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->initialiseShaders();
    }
}

//============================================================================
void AppCommon::releaseShaders()
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->releaseShaders();
    }
}

//============================================================================
bool AppCommon::enableShader( ESHADERMETHOD method )
{
    bool enabled = false;
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        enabled = glWidget->enableShader( method );
    }

    return enabled;
}

//============================================================================
bool AppCommon::isShaderValid( ESHADERMETHOD method )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        return glWidget->isShaderValid( method );
    }

    return false;
}

//============================================================================
void AppCommon::disableGUIShader()
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->disableGUIShader();
    }
}

//============================================================================
void AppCommon::disableShader( ESHADERMETHOD method )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->disableShader( method );
    }
}

//============================================================================
int AppCommon::shaderGetPos()
{
    int result = false;
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        result = glWidget->shaderGetPos();
    }

    return result;
}

//============================================================================
int AppCommon::shaderGetCol()
{
    int result = false;
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        result = glWidget->shaderGetCol();
    }

    return result;
}

//============================================================================
int AppCommon::shaderGetModel()
{
    int result = false;
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        result = glWidget->shaderGetModel();
    }

    return result;
}

//============================================================================
int AppCommon::shaderGetCoord0()
{
    int result = false;
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        result = glWidget->shaderGetCoord0();
    }

    return result;
}

//============================================================================
int AppCommon::shaderGetCoord1()
{
    int result = false;
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        result = glWidget->shaderGetCoord1();
    }

    return result;
}

//============================================================================
int AppCommon::shaderGetUniCol()
{
    int result = false;
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        result = glWidget->shaderGetUniCol();
    }

    return result;
}

// yuv shader
//============================================================================
void AppCommon::shaderSetField( ESHADERMETHOD shader, int field )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->shaderSetField( shader, field );
    }
}

//============================================================================
void AppCommon::shaderSetWidth( ESHADERMETHOD shader, int w )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->shaderSetWidth( shader, w );
    }
}

//============================================================================
void AppCommon::shaderSetHeight( ESHADERMETHOD shader, int h )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->shaderSetHeight( shader, h );
    }
}

//============================================================================
void AppCommon::shaderSetBlack( ESHADERMETHOD shader, float black )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->shaderSetBlack( shader, black );
    }
}

//============================================================================
void AppCommon::shaderSetContrast( ESHADERMETHOD shader, float contrast )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->shaderSetContrast( shader, contrast );
    }
}

//============================================================================
void AppCommon::shaderSetConvertFullColorRange( ESHADERMETHOD shader, bool convertFullRange )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->shaderSetConvertFullColorRange( shader, convertFullRange );
    }
}

//============================================================================
int AppCommon::shaderGetVertexLoc( ESHADERMETHOD shader )
{
    int result = false;
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        result = glWidget->shaderGetVertexLoc( shader );
    }

    return result;
}

//============================================================================
int AppCommon::shaderGetYcoordLoc( ESHADERMETHOD shader )
{
    int result = false;
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        result = glWidget->shaderGetYcoordLoc( shader );
    }

    return result;
}

//============================================================================
int AppCommon::shaderGetUcoordLoc( ESHADERMETHOD shader )
{
    int result = false;
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        result = glWidget->shaderGetUcoordLoc( shader );
    }

    return result;
}

//============================================================================
int AppCommon::shaderGetVcoordLoc( ESHADERMETHOD shader )
{
    int result = false;
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        result = glWidget->shaderGetVcoordLoc( shader );
    }

    return result;
}

//============================================================================
void AppCommon::shaderSetMatrices( ESHADERMETHOD shader, const float *p, const float *m )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->shaderSetMatrices( shader, p, m );
    }
}

//============================================================================
void AppCommon::shaderSetAlpha( ESHADERMETHOD shader, float alpha )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->shaderSetAlpha( shader, alpha );
    }
}

//============================================================================
void AppCommon::shaderSetFlags( ESHADERMETHOD shader, unsigned int flags )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->shaderSetFlags( shader, flags );
    }
}

//============================================================================
void AppCommon::shaderSetFormat( ESHADERMETHOD shader, EShaderFormat format )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->shaderSetFormat( shader, format );
    }
}

//============================================================================
void AppCommon::shaderSourceTexture( ESHADERMETHOD shader, int ytex )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->shaderSourceTexture( shader, ytex );
    }
}

//============================================================================
void AppCommon::shaderSetStepX( ESHADERMETHOD shader, float stepX )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->shaderSetStepX( shader, stepX );
    }
}

//============================================================================
void AppCommon::shaderSetStepY( ESHADERMETHOD shader, float stepY )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->shaderSetStepY( shader, stepY );
    }
}

//============================================================================
// filter shader
bool AppCommon::shaderGetTextureFilter( ESHADERMETHOD shader, int& filter )
{
    bool result = false;
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        result = glWidget->shaderGetTextureFilter( shader, filter );
    }

    return result;
}

//============================================================================
int AppCommon::shaderGetcoordLoc( ESHADERMETHOD shader )
{
    int result = false;
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        result = glWidget->shaderGetcoordLoc( shader );
    }

    return result;
}

//============================================================================
int AppCommon::shaderVertexAttribPointer( ESHADERMETHOD shader, unsigned int index, int size, int type, bool normalized, int stride, const void * pointer )
{
    int result = false;
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        result = glWidget->shaderVertexAttribPointer( shader, index, size, type, normalized, stride, pointer );
    }

    return result;
}

//============================================================================
void AppCommon::shaderEnableVertexAttribArray( ESHADERMETHOD shader, int arrayId )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->shaderEnableVertexAttribArray( shader, arrayId );
    }
}

//============================================================================
void AppCommon::shaderDisableVertexAttribArray( ESHADERMETHOD shader, int arrayId )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->shaderDisableVertexAttribArray( shader, arrayId );
    }
}

// frame buffers
//============================================================================
void AppCommon::frameBufferGen( int bufCount, unsigned int* fboId )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->frameBufferGen( bufCount, fboId );
    }
}

//============================================================================
void AppCommon::frameBufferDelete( int bufCount, unsigned int* fboId )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->frameBufferDelete( bufCount, fboId );
    }
}

//============================================================================
void AppCommon::frameBufferTexture2D( int target, unsigned int texureId )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->frameBufferTexture2D( target, texureId );
    }
}

//============================================================================
void AppCommon::frameBufferBind( unsigned int fboId )
{
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        glWidget->frameBufferBind( fboId );
    }
}

//============================================================================
bool AppCommon::frameBufferStatus()
{
    bool result = false;
    RenderGlWidget * glWidget = getRenderConsumer();
    if( glWidget )
    {
        result = glWidget->frameBufferStatus();
    }

    return result;
}
