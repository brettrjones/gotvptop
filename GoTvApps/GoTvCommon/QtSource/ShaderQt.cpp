/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "ShaderQt.h"
#include "RenderGlWidget.h"

#include "ServiceBroker.h"
#include "utils/log.h"
#include "rendering/RenderSystem.h"
#include "rendering/MatrixGL.h"
#include "windowing/GraphicContext.h"
#include "cores/VideoPlayer/VideoRenderers/VideoShaders/YUVMatrix.h"
#include "cores/VideoPlayer/VideoRenderers/VideoShaders/ConvolutionKernels.h"

#include <CoreLib/VxDebug.h>

 //============================================================================
static void CalculateYUVMatrixGLES( GLfloat      res[ 4 ][ 4 ]
                                    , unsigned int flags
                                    , EShaderFormat format
                                    , float        black
                                    , float         contrast
                                    , bool          limited )
{
    TransformMatrix matrix;
    CalculateYUVMatrix( matrix, flags, format, black, contrast, limited );

    for( int row = 0; row < 3; row++ )
        for( int col = 0; col < 4; col++ )
            res[ col ][ row ] = matrix.m[ row ][ col ];

    res[ 0 ][ 3 ] = 0.0f;
    res[ 1 ][ 3 ] = 0.0f;
    res[ 2 ][ 3 ] = 0.0f;
    res[ 3 ][ 3 ] = 1.0f;
}

//============================================================================
ShaderQt::ShaderQt(  ESHADERMETHOD shaderMethod, EShaderType shaderType, QString& shaderName, RenderGlWidget * renderWidget )
    : QOpenGLShaderProgram()
    , m_ShaderMethod( shaderMethod )
    , m_ScalingMethod( VS_SCALINGMETHOD_LINEAR )
    , m_ShaderType( shaderType )
    , m_ShaderName( shaderName )
    , m_RenderWidget( renderWidget )
    , m_validated( false )
    , m_proj( nullptr )
    , m_model( nullptr )
    , m_clipPossible( false )
{
 #ifdef GL_RGBA16F_EXT
    if( CServiceBroker::GetRenderSystem()->IsExtSupported( "GL_EXT_color_buffer_float" ) )
    {
        m_floattex = true;
        m_internalformat = GL_RGBA16F_EXT;
    }
    else
    {
        m_floattex = false;
        m_internalformat = GL_RGBA;
    }
#else
    m_floattex = false;
    m_internalformat = GL_RGBA;
#endif // GL_RGBA16F_EXT
}

//============================================================================
bool ShaderQt::compileAndLink( const char * vertexShaderCode, const char *fragmentShaderCode )
{
    bool result = true;
    m_proj = nullptr;
    m_model = nullptr;
    m_clipPossible = false;
    m_RenderWidget->VerifyGLStateQt();

    if( vertexShaderCode )
    {
        if( !addShaderFromSourceCode( QOpenGLShader::Vertex, vertexShaderCode ) )
        {
            LogMsg( LOG_ERROR, "could not add vertex shader" );
            result = false;
        }
    }
    
    if( result && !addShaderFromSourceCode( QOpenGLShader::Fragment, fragmentShaderCode ) )
    {
        LogMsg( LOG_ERROR, "could not add fragment shader" );
        result = false;
    }
    
    if( result && !link() )
    {
        LogMsg( LOG_ERROR, "could not link shader" );
    }

    m_RenderWidget->VerifyGLStateQt();
    
    if( result )
    {
        // success
        m_validated = true;
        onCompiledAndLinked();
    }

    m_RenderWidget->VerifyGLStateQt();

    return result;
}

//============================================================================
void ShaderQt::onCompiledAndLinked()
{
    // This is called after CompileAndLink()

    if( !m_RenderWidget || !m_RenderWidget->getGlFunctions() )
    {
        LogMsg( LOG_ERROR, "onCompiledAndLinked has no render widget" );
        return;
    }

     QOpenGLFunctions * glf = m_RenderWidget->getGlFunctions();
     if( !glf )
     {
         LogMsg( LOG_ERROR, "onCompiledAndLinked could not get gl functions" );
         return;
     }

     switch( m_ShaderType )
     {
     case eShaderVideoFilter:
         onCompiledAndLinkedVideoFilter( glf );
         break;

     case eShaderVideoFormat:
         onCompiledAndLinkedVideoFormat( glf );
         break;

     case eShaderGui:
     default:
         onCompiledAndLinkedGui( glf );
         break;
     }
}

//============================================================================
void ShaderQt::onCompiledAndLinkedGui( QOpenGLFunctions * glf )
{
    // Variables passed directly to the Fragment shader
    m_hTex0         = glf->glGetUniformLocation( programId(), "m_samp0" );
    m_hTex1         = glf->glGetUniformLocation( programId(), "m_samp1" );
    m_hUniCol       = glf->glGetUniformLocation( programId(), "m_unicol" );
    m_hField        = glf->glGetUniformLocation( programId(), "m_field" );
    m_hStep         = glf->glGetUniformLocation( programId(), "m_step" );
    m_hContrast     = glf->glGetUniformLocation( programId(), "m_contrast" );
    m_hBrightness   = glf->glGetUniformLocation( programId(), "m_brightness" );

    // Variables passed directly to the Vertex shader
    m_hProj         = glf->glGetUniformLocation( programId(), "m_proj" );
    m_hModel        = glf->glGetUniformLocation( programId(), "m_model" );
    m_hCoord0Matrix = glf->glGetUniformLocation( programId(), "m_coord0Matrix" );

    // Vertex attributes
    m_hPos          = glf->glGetAttribLocation( programId(), "m_attrpos" );
    m_hCol          = glf->glGetAttribLocation( programId(), "m_attrcol" );
    m_hCord0        = glf->glGetAttribLocation( programId(), "m_attrcord0" );
    m_hCord1        = glf->glGetAttribLocation( programId(), "m_attrcord1" );

    // It's okay to do this only one time. Textures units never change.
    glf->glUseProgram( programId() );
    glf->glUniform1i( m_hTex0, 0 );
    glf->glUniform1i( m_hTex1, 1 );
    glf->glUniform4f( m_hUniCol, 1.0, 1.0, 1.0, 1.0 );

    static const float identity[ 16 ] = {
      1.0f, 0.0f, 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f
    };

    glf->glUniformMatrix4fv( m_hCoord0Matrix, 1, GL_FALSE, identity );

    glf->glUseProgram( 0 );
}

//============================================================================
void ShaderQt::onCompiledAndLinkedVideoFormat( QOpenGLFunctions * glf )
{
    if( SM_VIDEO_YV12_BASIC == m_ShaderMethod )
    {
        LogMsg( LOG_ERROR, "onShaderVideoFormatEnabled %s", describeShader( m_ShaderMethod ) );
    }

    /*
    "#define XBMC_YV12\n"
        "attribute vec4 m_attrpos;\n"
        "attribute vec2 m_attrcordY;\n"
        "attribute vec2 m_attrcordU;\n"
        "attribute vec2 m_attrcordV;\n"
        "varying vec2 m_cordY;\n"
        "varying vec2 m_cordU;\n"
        "varying vec2 m_cordV;\n"
        "uniform mat4 m_proj;\n"
        "uniform mat4 m_model;\n"
        */
    /*
    "precision mediump float;\n"
        "uniform sampler2D m_sampY;\n"
        "uniform sampler2D m_sampU;\n"
        "uniform sampler2D m_sampV;\n"
        "varying vec2      m_cordY;\n"
        "varying vec2      m_cordU;\n"
        "varying vec2      m_cordV;\n"
        "uniform vec2      m_step;\n"
        "uniform mat4      m_yuvmat;\n"
        "uniform float     m_alpha;\n"
        */

     // Variables passed directly to the Vertex shader
    m_hVertex   = glf->glGetAttribLocation( programId(), "m_attrpos" );
    m_hYcoord   = glf->glGetAttribLocation( programId(), "m_attrcordY" );
    m_hUcoord   = glf->glGetAttribLocation( programId(), "m_attrcordU" );
    m_hVcoord   = glf->glGetAttribLocation( programId(), "m_attrcordV" );
    m_hProj     = glf->glGetUniformLocation( programId(), "m_proj" );
    m_hModel    = glf->glGetUniformLocation( programId(), "m_model" );

    // Variables passed directly to the Fragment shader
    m_hAlpha    = glf->glGetUniformLocation( programId(), "m_alpha" );
    m_hYTex     = glf->glGetUniformLocation( programId(), "m_sampY" );
    m_hUTex     = glf->glGetUniformLocation( programId(), "m_sampU" );
    m_hVTex     = glf->glGetUniformLocation( programId(), "m_sampV" );
    m_hMatrix   = glf->glGetUniformLocation( programId(), "m_yuvmat" );
    m_hStep     = glf->glGetUniformLocation( programId(), "m_step" );
    //VerifyGLStateQt();

    switch( m_ShaderMethod )
    {
    case SM_VIDEO_YV12_BOB:
    case SM_VIDEO_NV12_BOB:
    case SM_VIDEO_YUY2_BOB:
    case SM_VIDEO_UYVY_BOB:
    case SM_VIDEO_NV12_RGB_BOB:
        m_hStepX = glf->glGetUniformLocation( programId(), "m_stepX" );
        m_hStepY = glf->glGetUniformLocation( programId(), "m_stepY" );
        m_hField = glf->glGetUniformLocation( programId(), "m_field" );
       // VerifyGLStateQt();
        break;
    default:
        break;
    }

}

//============================================================================
void ShaderQt::onCompiledAndLinkedVideoFilter( QOpenGLFunctions * glf )
{
    m_hVertex = glf->glGetAttribLocation( programId(), "m_attrpos" );
    m_hcoord = glf->glGetAttribLocation( programId(), "m_attrcord" );
    m_hAlpha = glf->glGetUniformLocation( programId(), "m_alpha" );
    m_hProj = glf->glGetUniformLocation( programId(), "m_proj" );
    m_hModel = glf->glGetUniformLocation( programId(), "m_model" );

    switch( m_ShaderMethod )
    {
    case SM_VID_FILTER_CONVOLUTION_4X4_RGBA:
    case SM_VID_FILTER_CONVOLUTION_4X4_FLOAT:
    case SM_VID_FILTER_CONVOLUTION_6X6_RGBA:
    case SM_VID_FILTER_CONVOLUTION_6X6_FLOAT:
    {
        m_RenderWidget->VerifyGLStateQt();

        // obtain shader attribute handles on successful compilation
        m_hSourceTex    = glf->glGetUniformLocation( programId(), "img" );
        m_hStepXY       = glf->glGetUniformLocation( programId(), "stepxy" );
        m_hKernTex      = glf->glGetUniformLocation( programId(), "kernelTex" );

        m_RenderWidget->VerifyGLStateQt();
        CConvolutionKernel kernel( m_ScalingMethod, 256 );
        m_RenderWidget->VerifyGLStateQt();

        if( m_kernelTex1 )
        {
            glf->glDeleteTextures( 1, &m_kernelTex1 );
            m_kernelTex1 = 0;
        }

        m_RenderWidget->VerifyGLStateQt();

        glf->glGenTextures( 1, &m_kernelTex1 );
        m_RenderWidget->VerifyGLStateQt();

        if( ( m_kernelTex1 <= 0 ) )
        {
            CLog::Log( LOGERROR, "GL: ConvolutionFilterShader: Error creating kernel texture" );
            return;
        }

        m_RenderWidget->VerifyGLStateQt();

        //make a kernel texture on GL_TEXTURE2 and set clamping and interpolation
        glf-> glActiveTexture( GL_TEXTURE2 );
        glf->glBindTexture( GL_TEXTURE_2D, m_kernelTex1 );
        glf->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glf->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glf->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glf->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

        //if float textures are supported, we can load the kernel as a float texture
        //if not we load it as 8 bit unsigned which gets converted back to float in the shader
        GLenum  format;
        GLvoid* data;
        if( m_floattex )
        {
            format = GL_FLOAT;
            data = ( GLvoid* )kernel.GetFloatPixels();
        }
        else
        {
            format = GL_UNSIGNED_BYTE;
            data = ( GLvoid* )kernel.GetUint8Pixels();
        }
        m_RenderWidget->VerifyGLStateQt();

        //upload as 2D texture with height of 1
        glf->glTexImage2D( GL_TEXTURE_2D, 0, m_internalformat, kernel.GetSize(), 1, 0, GL_RGBA, format, data );

        glf->glActiveTexture( GL_TEXTURE0 );

        m_RenderWidget->VerifyGLStateQt();
        break;
    }

    default:
        break;
    }
}

//============================================================================
bool ShaderQt::onEnabled()
{
    // This is called after glUseProgram()

    if( !m_RenderWidget || !m_RenderWidget->getGlFunctions() )
    {
        LogMsg( LOG_ERROR, "onEnabled has no render widget" );
        return false;
    }

    QOpenGLFunctions * glf = m_RenderWidget->getGlFunctions();

    switch( m_ShaderType )
    {
    case eShaderVideoFilter:
        return onShaderVideoFilterEnabled( glf );
        break;

    case eShaderVideoFormat:
        return onShaderVideoFormatEnabled( glf );
        break;

    case eShaderGui:
    default:
        return onShaderGuiEnabled( glf );
        break;
    }
}
    
//============================================================================
bool ShaderQt::onShaderGuiEnabled( QOpenGLFunctions * glf )
{

    const GLfloat *projMatrix = glMatrixProject.Get();
    const GLfloat *modelMatrix = glMatrixModview.Get();
    glf->glUniformMatrix4fv( m_hProj, 1, GL_FALSE, projMatrix );
    glf->glUniformMatrix4fv( m_hModel, 1, GL_FALSE, modelMatrix );

    const TransformMatrix &guiMatrix = CServiceBroker::GetWinSystem()->GetGfxContext().GetGUIMatrix();
    CRect viewPort; // absolute positions of corners
    CServiceBroker::GetRenderSystem()->GetViewPort( viewPort );

    /* glScissor operates in window coordinates. In order that we can use it to
     * perform clipping, we must ensure that there is an independent linear
     * transformation from the coordinate system used by CGraphicContext::ClipRect
     * to window coordinates, separately for X and Y (in other words, no
     * rotation or shear is introduced at any stage). To do, this, we need to
     * check that zeros are present in the following locations:
     *
     * GUI matrix:
     * / * 0 * * \
     * | 0 * * * |
     * \ 0 0 * * /
     *       ^ TransformMatrix::TransformX/Y/ZCoord are only ever called with
     *         input z = 0, so this column doesn't matter
     * Model-view matrix:
     * / * 0 0 * \
     * | 0 * 0 * |
     * | 0 0 * * |
     * \ * * * * /  <- eye w has no influence on window x/y (last column below
     *                                                       is either 0 or ignored)
     * Projection matrix:
     * / * 0 0 0 \
     * | 0 * 0 0 |
     * | * * * * |  <- normalised device coordinate z has no influence on window x/y
     * \ 0 0 * 0 /
     *
     * Some of these zeros are not strictly required to ensure this, but they tend
     * to be zeroed in the common case, so by checking for zeros here, we simplify
     * the calculation of the window x/y coordinates further down the line.
     *
     * (Minor detail: we don't quite deal in window coordinates as defined by
     * OpenGL, because CRenderSystemGLES::SetScissors flips the Y axis. But all
     * that's needed to handle that is an effective negation at the stage where
     * Y is in normalized device coordinates.)
     */
    m_clipPossible = guiMatrix.m[ 0 ][ 1 ] == 0 &&
        guiMatrix.m[ 1 ][ 0 ] == 0 &&
        guiMatrix.m[ 2 ][ 0 ] == 0 &&
        guiMatrix.m[ 2 ][ 1 ] == 0 &&
        modelMatrix[ 0 + 1 * 4 ] == 0 &&
        modelMatrix[ 0 + 2 * 4 ] == 0 &&
        modelMatrix[ 1 + 0 * 4 ] == 0 &&
        modelMatrix[ 1 + 2 * 4 ] == 0 &&
        modelMatrix[ 2 + 0 * 4 ] == 0 &&
        modelMatrix[ 2 + 1 * 4 ] == 0 &&
        projMatrix[ 0 + 1 * 4 ] == 0 &&
        projMatrix[ 0 + 2 * 4 ] == 0 &&
        projMatrix[ 0 + 3 * 4 ] == 0 &&
        projMatrix[ 1 + 0 * 4 ] == 0 &&
        projMatrix[ 1 + 2 * 4 ] == 0 &&
        projMatrix[ 1 + 3 * 4 ] == 0 &&
        projMatrix[ 3 + 0 * 4 ] == 0 &&
        projMatrix[ 3 + 1 * 4 ] == 0 &&
        projMatrix[ 3 + 3 * 4 ] == 0;

    m_clipXFactor = 0.0;
    m_clipXOffset = 0.0;
    m_clipYFactor = 0.0;
    m_clipYOffset = 0.0;

    if( m_clipPossible )
    {
        m_clipXFactor = guiMatrix.m[ 0 ][ 0 ] * modelMatrix[ 0 + 0 * 4 ] * projMatrix[ 0 + 0 * 4 ];
        m_clipXOffset = ( guiMatrix.m[ 0 ][ 3 ] * modelMatrix[ 0 + 0 * 4 ] + modelMatrix[ 0 + 3 * 4 ] ) * projMatrix[ 0 + 0 * 4 ];
        m_clipYFactor = guiMatrix.m[ 1 ][ 1 ] * modelMatrix[ 1 + 1 * 4 ] * projMatrix[ 1 + 1 * 4 ];
        m_clipYOffset = ( guiMatrix.m[ 1 ][ 3 ] * modelMatrix[ 1 + 1 * 4 ] + modelMatrix[ 1 + 3 * 4 ] ) * projMatrix[ 1 + 1 * 4 ];
        float clipW = ( guiMatrix.m[ 2 ][ 3 ] * modelMatrix[ 2 + 2 * 4 ] + modelMatrix[ 2 + 3 * 4 ] ) * projMatrix[ 3 + 2 * 4 ];
        float xMult = ( viewPort.x2 - viewPort.x1 ) / ( 2 * clipW );
        float yMult = ( viewPort.y1 - viewPort.y2 ) / ( 2 * clipW ); // correct for inverted window coordinate scheme
        m_clipXFactor = m_clipXFactor * xMult;
        m_clipXOffset = m_clipXOffset * xMult + ( viewPort.x2 + viewPort.x1 ) / 2;
        m_clipYFactor = m_clipYFactor * yMult;
        m_clipYOffset = m_clipYOffset * yMult + ( viewPort.y2 + viewPort.y1 ) / 2;
    }

    glf->glUniform1f( m_hBrightness, 0.0f );
    glf->glUniform1f( m_hContrast, 1.0f );

    return true;
}

//============================================================================
bool ShaderQt::onShaderVideoFormatEnabled( QOpenGLFunctions * glf )
{
    //LogMsg( LOG_ERROR, "onShaderVideoFormatEnabled %s", describeShader( m_ShaderMethod ) );

    // set shader attributes once enabled
    m_RenderWidget->VerifyGLStateQt();
    glf->glUniform1i( m_hYTex, 0 );
    glf->glUniform1i( m_hUTex, 1 );
    glf->glUniform1i( m_hVTex, 2 );
    glf->glUniform2f( m_hStep, 1.0 / m_width, 1.0 / m_height );

    GLfloat matrix[ 4 ][ 4 ];
    // keep video levels
    CalculateYUVMatrixGLES( matrix, m_flags, m_format, m_black, m_contrast, !m_convertFullRange );

    glf->glUniformMatrix4fv( m_hMatrix, 1, GL_FALSE, ( GLfloat* )matrix );
    glf->glUniformMatrix4fv( m_hProj, 1, GL_FALSE, m_proj );
    glf->glUniformMatrix4fv( m_hModel, 1, GL_FALSE, m_model );
    glf->glUniform1f( m_hAlpha, m_alpha );
    m_RenderWidget->VerifyGLStateQt();

    switch( m_ShaderMethod )
    {
    case SM_VIDEO_YV12_BOB:
    case SM_VIDEO_NV12_BOB:
    case SM_VIDEO_YUY2_BOB:
    case SM_VIDEO_UYVY_BOB:
    case SM_VIDEO_NV12_RGB_BOB:
        glf->glUniform1i( m_hField, m_field );
        glf->glUniform1f( m_hStepX, 1.0f / ( float )m_width );
        glf->glUniform1f( m_hStepY, 1.0f / ( float )m_height );
        m_RenderWidget->VerifyGLStateQt();
        break;

    default:
        break;
    }

    return true;
}

//============================================================================
bool ShaderQt::onShaderVideoFilterEnabled( QOpenGLFunctions * glf )
{
    LogMsg( LOG_ERROR, "onShaderVideoFormatEnabled %s", describeShader( m_ShaderMethod ) );

    m_RenderWidget->VerifyGLStateQt();
    glf->glUniformMatrix4fv( m_hProj, 1, GL_FALSE, m_proj );
    glf->glUniformMatrix4fv( m_hModel, 1, GL_FALSE, m_model );
    glf->glUniform1f( m_hAlpha, m_alpha );

    switch( m_ShaderMethod )
    {
    case SM_VID_FILTER_CONVOLUTION_4X4_RGBA:
    case SM_VID_FILTER_CONVOLUTION_4X4_FLOAT:
    case SM_VID_FILTER_CONVOLUTION_6X6_RGBA:
    case SM_VID_FILTER_CONVOLUTION_6X6_FLOAT:
    {
        // set shader attributes once enabled
        glf->glActiveTexture( GL_TEXTURE2 );
        glf->glBindTexture( GL_TEXTURE_2D, m_kernelTex1 );

        glf->glActiveTexture( GL_TEXTURE0 );
        glf->glUniform1i( m_hSourceTex, m_sourceTexUnit );
        glf->glUniform1i( m_hKernTex, 2 );
        glf->glUniform2f( m_hStepXY, m_stepX, m_stepY );
        m_RenderWidget->VerifyGLStateQt();
        break;
    }

    default:
        break;
    }

    return true;
}

//============================================================================
const char * ShaderQt::describeShader( ESHADERMETHOD shaderType )
{
    switch( shaderType )
    {
    case SM_DEFAULT:
        return "SM_DEFAULT";
    case SM_TEXTURE:
        return "SM_TEXTURE";
    case SM_MULTI:
        return "SM_MULTI";
    case SM_FONTS:
        return "SM_FONTS";
    case SM_TEXTURE_NOBLEND:
        return "SM_TEXTURE_NOBLEND";
    case SM_MULTI_BLENDCOLOR:
        return "SM_MULTI_BLENDCOLOR";
    case SM_TEXTURE_RGBA:
        return "SM_TEXTURE_RGBA";
    case SM_TEXTURE_RGBA_OES:
        return "SM_TEXTURE_RGBA_OES";
    case SM_TEXTURE_RGBA_BLENDCOLOR:
        return "SM_TEXTURE_RGBA_BLENDCOLOR";
    case SM_TEXTURE_RGBA_BOB:
        return "SM_TEXTURE_RGBA_BOB";
    case SM_TEXTURE_RGBA_BOB_OES:
        return "SM_TEXTURE_RGBA_BOB_OES";
    case SM_VIDEO_YV12_BASIC:
        return "SM_VIDEO_YV12_BASIC";
    case SM_VIDEO_NV12_BASIC:
        return "SM_VIDEO_NV12_BASIC";
    case SM_VIDEO_YUY2_BASIC:
        return "SM_VIDEO_YUY2_BASIC";
    case SM_VIDEO_UYVY_BASIC:
        return "SM_VIDEO_UYVY_BASIC";
    case SM_VIDEO_NV12_RGB_BASIC:
        return "SM_VIDEO_NV12_RGB_BASIC";
    case SM_VIDEO_YV12_BOB:
        return "SM_VIDEO_YV12_BOB";
    case SM_VIDEO_NV12_BOB:
        return "SM_VIDEO_NV12_BOB";
    case SM_VIDEO_YUY2_BOB:
        return "SM_VIDEO_YUY2_BOB";
    case SM_VIDEO_UYVY_BOB:
        return "SM_VIDEO_UYVY_BOB";
    case SM_VIDEO_NV12_RGB_BOB:
        return "SM_VIDEO_NV12_RGB_BOB";
    case SM_VID_FILTER_DEFAULT:
        return "SM_VID_FILTER_DEFAULT";
    case SM_VID_FILTER_CONVOLUTION_4X4_RGBA:
        return "SM_VID_FILTER_CONVOLUTION_4X4_RGBA";
    case SM_VID_FILTER_CONVOLUTION_4X4_FLOAT:
        return "SM_VID_FILTER_CONVOLUTION_4X4_FLOAT";
    case SM_VID_FILTER_CONVOLUTION_6X6_RGBA:
        return "SM_VID_FILTER_CONVOLUTION_6X6_RGBA";
    case SM_VID_FILTER_CONVOLUTION_6X6_FLOAT:
        return "SM_VID_FILTER_CONVOLUTION_6X6_FLOAT";
    case SM_SHADER_NONE:
        return "SM_SHADER_NONE";
    default:
        return "SM_UNKNOWN";
    }
}

//============================================================================
void ShaderQt::onDisabled()
{
}

//============================================================================
void ShaderQt::onFree()
{
    if( m_kernelTex1 )
    {
        glDeleteTextures( 1, &m_kernelTex1 );
    }

    m_kernelTex1 = 0;

    removeAllShaders();
    deleteLater();
}

//============================================================================
bool ShaderQt::enableShader()
{
    QOpenGLFunctions * glf = m_RenderWidget->getGlFunctions();
    glf->glUseProgram( programId() );
    if( onEnabled() )
    {
        if( !m_validated )
        {
            // validate the program
            GLint params[ 4 ];
            glf->glValidateProgram( programId() );
            glf->glGetProgramiv( programId(), GL_VALIDATE_STATUS, params );
            if( params[ 0 ] != GL_TRUE )
            {
                #define LOG_SIZE 1024

                GLchar log[ LOG_SIZE ];
                LogMsg( LOG_ERROR, "GL: Error validating shader" );
                glf->glGetProgramInfoLog( programId(), LOG_SIZE, NULL, log );
                LogMsg( LOG_ERROR, "%s", log );
            }

            m_validated = true;
        }

        //VerifyGLStateQt();
        return true;
    }
    else
    {
        glf->glUseProgram( 0 );
        return false;
    }

    return true;
}

//============================================================================
bool ShaderQt::disableShader()
{
    switch( m_ShaderMethod )
    {
    case SM_VID_FILTER_CONVOLUTION_4X4_RGBA:
    case SM_VID_FILTER_CONVOLUTION_4X4_FLOAT:
    case SM_VID_FILTER_CONVOLUTION_6X6_RGBA:
    case SM_VID_FILTER_CONVOLUTION_6X6_FLOAT:
        return true; 
    }

    QOpenGLFunctions * glf = m_RenderWidget->getGlFunctions();
    glf->glUseProgram( 0 );
    onDisabled();
    return true;
}

// yuv shader
//============================================================================
void ShaderQt::shaderSetField( int field )
{
    m_field = field;
    //VerifyGLStateQt();
}

//============================================================================
void ShaderQt::shaderSetWidth( int w )
{
    m_width = w;
    //VerifyGLStateQt();
}

//============================================================================
void ShaderQt::shaderSetHeight( int h )
{
    m_height = h;

   // VerifyGLStateQt();
}

//============================================================================
void ShaderQt::shaderSetBlack( float black )
{
    m_black = black;

    //VerifyGLStateQt();
}

//============================================================================
void ShaderQt::shaderSetContrast( float contrast )
{
    m_contrast = contrast;
    //VerifyGLStateQt();
}

//============================================================================
void ShaderQt::shaderSetConvertFullColorRange( bool convertFullRange )
{
    m_convertFullRange = convertFullRange;
    //VerifyGLStateQt();
}

//============================================================================
int ShaderQt::shaderGetVertexLoc(  )
{
    //VerifyGLStateQt();
    return m_hVertex;
}

//============================================================================
int ShaderQt::shaderGetYcoordLoc(  )
{
    //VerifyGLStateQt();
    return m_hYcoord;
}

//============================================================================
int ShaderQt::shaderGetUcoordLoc(  )
{
    //VerifyGLStateQt();
    return m_hUcoord;
}

//============================================================================
int ShaderQt::shaderGetVcoordLoc(  )
{
    //VerifyGLStateQt();
    return m_hVcoord;
}

//============================================================================
void ShaderQt::shaderSetMatrices( const float *p, const float *m )
{
    m_proj = p; 
    m_model = m;
}

//============================================================================
void ShaderQt::shaderSetAlpha( float alpha )
{
    m_alpha = alpha;
}

//============================================================================
void ShaderQt::shaderSetFlags( unsigned int flags )
{
    m_flags = flags;
}

//============================================================================
void ShaderQt::shaderSetFormat(  EShaderFormat format )
{
    m_format = format;
}

//============================================================================
void ShaderQt::shaderSourceTexture( int ytex )
{
    m_sourceTexUnit = ytex;
}

//============================================================================
void ShaderQt::shaderSetStepX( float stepX )
{
    m_stepX = stepX;
}

//============================================================================
void ShaderQt::shaderSetStepY( float stepY )
{
    m_stepY = stepY;
}

//============================================================================
// filter shader
bool ShaderQt::shaderGetTextureFilter(  int& filter )
{
    return false;
}

//============================================================================
int ShaderQt::shaderGetcoordLoc(  )
{
    //VerifyGLStateQt();
    return m_hcoord;
}

//============================================================================
int ShaderQt::shaderVertexAttribPointer( unsigned int index, int size, int type, bool normalized, int stride, const void * pointer )
{
    QOpenGLFunctions * glf = m_RenderWidget->getGlFunctions();
    glf->glVertexAttribPointer( index, size, type, normalized, stride, pointer );
    //VerifyGLStateQt();
    return 0; // return value not needed .. should be void
}

//============================================================================
void ShaderQt::shaderEnableVertexAttribArray( int arrayId )
{
    QOpenGLFunctions * glf = m_RenderWidget->getGlFunctions();
    glf->glEnableVertexAttribArray( arrayId );
    //VerifyGLStateQt();
}

//============================================================================
void ShaderQt::shaderDisableVertexAttribArray( int arrayId )
{
    QOpenGLFunctions * glf = m_RenderWidget->getGlFunctions();
    glf->glDisableVertexAttribArray( arrayId );
    //VerifyGLStateQt();
}


