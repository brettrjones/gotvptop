#include "RenderGlWidget.h"


//============================================================================
bool RenderGlWidget::enableShader( ESHADERMETHOD method )
{
    return m_RenderLogic.enableShader( method );
}

//============================================================================
bool RenderGlWidget::isShaderValid( ESHADERMETHOD method )
{
    return m_RenderLogic.isShaderValid( method );
}

//============================================================================
void RenderGlWidget::disableShader( ESHADERMETHOD method )
{
    m_RenderLogic.disableShader( method );
}

//============================================================================
void RenderGlWidget::disableGUIShader()
{
    m_RenderLogic.disableGUIShader();
}

//============================================================================
int RenderGlWidget::shaderGetPos( )
{
    return m_RenderLogic.shaderGetPos();
}

//============================================================================
int RenderGlWidget::shaderGetCol()
{
    return m_RenderLogic.shaderGetCol();
}

//============================================================================
int RenderGlWidget::shaderGetModel()
{
    return m_RenderLogic.shaderGetModel();
}

//============================================================================
int RenderGlWidget::shaderGetCoord0()
{
    return m_RenderLogic.shaderGetCoord0();
}

//============================================================================
int RenderGlWidget::shaderGetCoord1()
{
    return m_RenderLogic.shaderGetCoord1();
}

//============================================================================
int RenderGlWidget::shaderGetUniCol()
{
    return m_RenderLogic.shaderGetUniCol();
}

// yuv shader
//============================================================================
void RenderGlWidget::shaderSetField( ESHADERMETHOD shader, int field )
{
    m_RenderLogic.shaderSetField( shader, field );
}

//============================================================================
void RenderGlWidget::shaderSetWidth( ESHADERMETHOD shader, int w )
{
    m_RenderLogic.shaderSetWidth( shader, w );
}

//============================================================================
void RenderGlWidget::shaderSetHeight( ESHADERMETHOD shader, int h )
{
    m_RenderLogic.shaderSetHeight( shader, h );
}

//============================================================================
void RenderGlWidget::shaderSetBlack( ESHADERMETHOD shader, float black )
{
    m_RenderLogic.shaderSetBlack( shader, black );
}

//============================================================================
void RenderGlWidget::shaderSetContrast( ESHADERMETHOD shader, float contrast )
{
    m_RenderLogic.shaderSetContrast( shader, contrast );
}

//============================================================================
void RenderGlWidget::shaderSetConvertFullColorRange( ESHADERMETHOD shader, bool convertFullRange )
{
    m_RenderLogic.shaderSetConvertFullColorRange( shader, convertFullRange );
}

//============================================================================
int RenderGlWidget::shaderGetVertexLoc( ESHADERMETHOD shader )
{
    return m_RenderLogic.shaderGetVertexLoc( shader );
}

//============================================================================
int RenderGlWidget::shaderGetYcoordLoc( ESHADERMETHOD shader )
{
    return m_RenderLogic.shaderGetYcoordLoc( shader );
}

//============================================================================
int RenderGlWidget::shaderGetUcoordLoc( ESHADERMETHOD shader )
{
    return m_RenderLogic.shaderGetUcoordLoc( shader );
}

//============================================================================
int RenderGlWidget::shaderGetVcoordLoc( ESHADERMETHOD shader )
{
    return m_RenderLogic.shaderGetVcoordLoc( shader );
}

//============================================================================
void RenderGlWidget::shaderSetMatrices( ESHADERMETHOD shader, const float *p, const float *m )
{
    m_RenderLogic.shaderSetMatrices( shader, p, m );
}

//============================================================================
void RenderGlWidget::shaderSetAlpha( ESHADERMETHOD shader, float alpha )
{
    m_RenderLogic.shaderSetAlpha( shader, alpha );
}

//============================================================================
void RenderGlWidget::shaderSetFlags( ESHADERMETHOD shader, unsigned int flags )
{
    m_RenderLogic.shaderSetFlags( shader, flags );
}

//============================================================================
void RenderGlWidget::shaderSetFormat( ESHADERMETHOD shader, EShaderFormat format )
{
    m_RenderLogic.shaderSetFormat( shader, format );
}

//============================================================================
void RenderGlWidget::shaderSourceTexture( ESHADERMETHOD shader, int ytex )
{
    m_RenderLogic.shaderSourceTexture( shader, ytex );
}

//============================================================================
void RenderGlWidget::shaderSetStepX( ESHADERMETHOD shader, float stepX )
{
    m_RenderLogic.shaderSetStepX( shader, stepX );
}

//============================================================================
void RenderGlWidget::shaderSetStepY( ESHADERMETHOD shader, float stepY )
{
    m_RenderLogic.shaderSetStepY( shader, stepY );
}

//============================================================================
// filter shader
bool RenderGlWidget::shaderGetTextureFilter( ESHADERMETHOD shader, int& filter )
{
    return m_RenderLogic.shaderGetTextureFilter( shader, filter );
}

//============================================================================
int RenderGlWidget::shaderGetcoordLoc( ESHADERMETHOD shader )
{
    return m_RenderLogic.shaderGetVcoordLoc( shader );
}

//============================================================================
int RenderGlWidget::shaderVertexAttribPointer( ESHADERMETHOD shader, unsigned int index, int size, int type, bool normalized, int stride, const void * pointer )
{
    return m_RenderLogic.shaderVertexAttribPointer( shader, index, size, type, normalized, stride, pointer );
}

//============================================================================
void RenderGlWidget::shaderEnableVertexAttribArray( ESHADERMETHOD shader, int arrayId )
{
    m_RenderLogic.shaderEnableVertexAttribArray( shader, arrayId );
}

//============================================================================
void RenderGlWidget::shaderDisableVertexAttribArray( ESHADERMETHOD shader, int arrayId )
{
    m_RenderLogic.shaderDisableVertexAttribArray( shader, arrayId );
}

//! ignore from kodi
//============================================================================
void RenderGlWidget::initialiseShaders()
{
}

//! ignore from kodi
//============================================================================
void RenderGlWidget::releaseShaders()
{
}
