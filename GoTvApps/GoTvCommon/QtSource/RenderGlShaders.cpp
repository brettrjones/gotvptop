#include "RenderGlShaders.h"
#include "RenderShaderQt.h"
#include "GoTvDebugConfig.h"

#include <CoreLib/VxDebug.h>

#include <QDebug>
#include <QTimer>
#include <QFile>

#define SHADERS_INCLUDE
#include "RenderShaderDefsGl.cpp"

//============================================================================
RenderGlShaders::RenderGlShaders( RenderGlWidget& renderGlWidget )
: m_RenderGlWidget( renderGlWidget )
{
}

//============================================================================
void RenderGlShaders::compileShader( int shaderIdx )
{
    EShaderType shaderType = eShaderGui;
    ESHADERMETHOD shaderMethod = static_cast<ESHADERMETHOD>(shaderIdx);

    std::string shaderName = "SM_UNKNOWN";
    std::string vertexShaderCode;
    std::string fragmentShaderCode;

    getShaderSourceCode( shaderIdx, shaderType, shaderName, vertexShaderCode, fragmentShaderCode );

    if( !vertexShaderCode.empty() && !fragmentShaderCode.empty() )
    {
        //LogMsg( LOG_INFO, "Compiling shader %s", shaderName.toUtf8().constData() );
        VerifyGLStateQt();

        RenderShaderQt * shader = new RenderShaderQt( shaderMethod, shaderType, shaderName.c_str(), &m_RenderGlWidget );

        if( shader->compileAndLink( vertexShaderCode.c_str(), fragmentShaderCode.c_str() ) )
        {
            // success
//            if( shaderIdx == 10 )
//            {
//               LogMsg( LOG_INFO, "Success compile shader %s", shaderName.c_str() );
//            }

            m_Shaders[ shaderIdx ] = shader;
        }
        else
        {
            LogMsg( LOG_ERROR, "Failed to compile shader %d %s", shaderIdx, shaderName.c_str() );
        }

        VerifyGLStateQt();
    }
}

//============================================================================
RenderGlShaders::~RenderGlShaders()
{
    destroyShaders();
}

//============================================================================
void RenderGlShaders::initShaders()
{
    if( m_ShadersInited )
    {
        return;
    }

    initializeOpenGLFunctions();

    memset( m_Shaders, 0, sizeof( m_Shaders ) );
    for( int i = 0; i < SM_MAX; i++ )
    {
        compileShader( i );
    }

    m_ShadersInited = true;
}

//============================================================================
void RenderGlShaders::destroyShaders()
{
    if( m_ShadersInited )
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

        m_ShadersInited = false;
    }
}

//============================================================================
bool RenderGlShaders::enableShader( ESHADERMETHOD method )
{
#ifdef DEBUG_KODI_SHADERS
    LogMsg( LOG_ERROR, "enableShader - %s", describeShaderMethod( method ) );
#endif // DEBUG
    bool eanbled = false;
    VerifyGLStateQt();
    if( ( method < SM_MAX) && m_Shaders[ method ] )
    {
        if( eShaderGui == m_Shaders[ method ]->getShaderType() )
        {
            m_CurShaderMethodType = method;
        }

        eanbled = m_Shaders[ method ]->enableShader();
    }
    else
    {
        LogMsg( LOG_ERROR, "Invalid GUI Shader selected - %d", method );
    }

    VerifyGLStateQt();
    return eanbled;
}

//============================================================================
bool RenderGlShaders::isShaderValid( ESHADERMETHOD method )
{
    bool shaderValid = false;
    if( ( method < SM_MAX ) && m_Shaders[ method ] )
    {
        //m_CurShaderMethodType = method;
        shaderValid = m_Shaders[ method ]->isShaderValid();
    }
    else
    {
        LogMsg( LOG_ERROR, "Invalid GUI isShaderValid selected - %d", method );
    }

    VerifyGLStateQt();
    return shaderValid;
}

//============================================================================
void RenderGlShaders::disableShader( ESHADERMETHOD method )
{
#ifdef DEBUG_QT_RENDER
    LogMsg( LOG_ERROR, "disableShader - %s", describeShaderMethod( method ) );
#endif // DEBUG

    if( m_Shaders[ method ] )
    {
        m_Shaders[ method ]->disableShader();
    }

    m_CurShaderMethodType = SM_DEFAULT;
    VerifyGLStateQt();
}

//============================================================================
void RenderGlShaders::disableGUIShader()
{
    if( m_Shaders[ m_CurShaderMethodType ] )
    {
        m_Shaders[ m_CurShaderMethodType ]->disableShader();
    }

    m_CurShaderMethodType = SM_DEFAULT;
    VerifyGLStateQt();
}

//============================================================================
int RenderGlShaders::shaderGetPos( )
{
    if( m_Shaders[ m_CurShaderMethodType ] )
        return m_Shaders[ m_CurShaderMethodType ]->GetPosLoc();

    return -1;
}

//============================================================================
int RenderGlShaders::shaderGetCol()
{
    if( m_Shaders[ m_CurShaderMethodType ] )
        return m_Shaders[ m_CurShaderMethodType ]->GetColLoc();

    return -1;
}

//============================================================================
int RenderGlShaders::shaderGetModel()
{
    if( m_Shaders[ m_CurShaderMethodType ] )
        return m_Shaders[ m_CurShaderMethodType ]->GetModelLoc();

    return -1;
}

//============================================================================
int RenderGlShaders::shaderGetCoord0()
{
    if( m_Shaders[ m_CurShaderMethodType ] )
        return m_Shaders[ m_CurShaderMethodType ]->GetCord0Loc();

    return -1;
}

//============================================================================
int RenderGlShaders::shaderGetCoord1()
{
    if( m_Shaders[ m_CurShaderMethodType ] )
        return m_Shaders[ m_CurShaderMethodType ]->GetCord1Loc();

    return -1;
}

//============================================================================
int RenderGlShaders::shaderGetUniCol()
{
    if( m_Shaders[ m_CurShaderMethodType ] )
        return m_Shaders[ m_CurShaderMethodType ]->GetUniColLoc();

    return -1;
}

// yuv shader
//============================================================================
void RenderGlShaders::shaderSetField( ESHADERMETHOD shader, int field )
{
    VerifyGLStateQt();
    if( m_Shaders[ shader ] )
    {
        m_Shaders[ shader ]->shaderSetField( field );
    }

    VerifyGLStateQt();
}

//============================================================================
void RenderGlShaders::shaderSetWidth( ESHADERMETHOD shader, int w )
{
    VerifyGLStateQt();
    if( m_Shaders[ shader ] )
    {
        m_Shaders[ shader ]->shaderSetWidth( w );
    }

    VerifyGLStateQt();
}

//============================================================================
void RenderGlShaders::shaderSetHeight( ESHADERMETHOD shader, int h )
{
    VerifyGLStateQt();
    if( m_Shaders[ shader ] )
    {
        m_Shaders[ shader ]->shaderSetHeight( h );
    }

    VerifyGLStateQt();
}

//============================================================================
void RenderGlShaders::shaderSetBlack( ESHADERMETHOD shader, float black )
{
    VerifyGLStateQt();
    if( m_Shaders[ shader ] )
    {
        m_Shaders[ shader ]->shaderSetBlack( black );
    }

    VerifyGLStateQt();
}

//============================================================================
void RenderGlShaders::shaderSetContrast( ESHADERMETHOD shader, float contrast )
{
    VerifyGLStateQt();
    if( m_Shaders[ shader ] )
    {
        m_Shaders[ shader ]->shaderSetContrast( contrast );
    }

    VerifyGLStateQt();
}

//============================================================================
void RenderGlShaders::shaderSetConvertFullColorRange( ESHADERMETHOD shader, bool convertFullRange )
{
    VerifyGLStateQt();
    if( m_Shaders[ shader ] )
    {
        m_Shaders[ shader ]->shaderSetConvertFullColorRange( convertFullRange );
    }

    VerifyGLStateQt();
}

//============================================================================
int RenderGlShaders::shaderGetVertexLoc( ESHADERMETHOD shader )
{
    VerifyGLStateQt();
    int result = false;
    if( m_Shaders[ shader ] )
    {
        result = m_Shaders[ shader ]->shaderGetVertexLoc();
    }

    VerifyGLStateQt();
    return result;
}

//============================================================================
int RenderGlShaders::shaderGetYcoordLoc( ESHADERMETHOD shader )
{
    VerifyGLStateQt();
    int result = false;
    if( m_Shaders[ shader ] )
    {
        result = m_Shaders[ shader ]->shaderGetYcoordLoc();
    }

    VerifyGLStateQt();
    return result;
}

//============================================================================
int RenderGlShaders::shaderGetUcoordLoc( ESHADERMETHOD shader )
{
    VerifyGLStateQt();
    int result = false;
    if( m_Shaders[ shader ] )
    {
        result = m_Shaders[ shader ]->shaderGetUcoordLoc();
    }

    VerifyGLStateQt();
    return result;
}

//============================================================================
int RenderGlShaders::shaderGetVcoordLoc( ESHADERMETHOD shader )
{
    VerifyGLStateQt();
    int result = false;
    if( m_Shaders[ shader ] )
    {
        result = m_Shaders[ shader ]->shaderGetVcoordLoc();
    }

    VerifyGLStateQt();
    return result;
}

//============================================================================
void RenderGlShaders::shaderSetMatrices( ESHADERMETHOD shader, const float *p, const float *m )
{
    if( m_Shaders[ shader ] )
    {
        m_Shaders[ shader ]->shaderSetMatrices( p, m );
    }
}

//============================================================================
void RenderGlShaders::shaderSetAlpha( ESHADERMETHOD shader, float alpha )
{
    if( m_Shaders[ shader ] )
    {
        m_Shaders[ shader ]->shaderSetAlpha( alpha );
    }
}

//============================================================================
void RenderGlShaders::shaderSetFlags( ESHADERMETHOD shader, unsigned int flags )
{
    if( m_Shaders[ shader ] )
    {
        m_Shaders[ shader ]->shaderSetFlags( flags );
    }
}

//============================================================================
void RenderGlShaders::shaderSetFormat( ESHADERMETHOD shader, EShaderFormat format )
{
    if( m_Shaders[ shader ] )
    {
        m_Shaders[ shader ]->shaderSetFormat( format );
    }
}

//============================================================================
void RenderGlShaders::shaderSourceTexture( ESHADERMETHOD shader, int ytex )
{
    if( m_Shaders[ shader ] )
    {
        m_Shaders[ shader ]->shaderSourceTexture( ytex );
    }
}

//============================================================================
void RenderGlShaders::shaderSetStepX( ESHADERMETHOD shader, float stepX )
{
    if( m_Shaders[ shader ] )
    {
        m_Shaders[ shader ]->shaderSetStepX( stepX );
    }
}

//============================================================================
void RenderGlShaders::shaderSetStepY( ESHADERMETHOD shader, float stepY )
{
    if( m_Shaders[ shader ] )
    {
        m_Shaders[ shader ]->shaderSetStepY( stepY );
    }
}

//============================================================================
// filter shader
bool RenderGlShaders::shaderGetTextureFilter( ESHADERMETHOD shader, int& filter )
{
    bool result = false;
    if( m_Shaders[ shader ] )
    {
        result = m_Shaders[ shader ]->shaderGetTextureFilter( filter );
    }

    return result;
}

//============================================================================
int RenderGlShaders::shaderGetcoordLoc( ESHADERMETHOD shader )
{
    VerifyGLStateQt();
    int result = false;
    if( m_Shaders[ shader ] )
    {
        result = m_Shaders[ shader ]->shaderGetVcoordLoc();
    }

    VerifyGLStateQt();
    return result;
}

//============================================================================
int RenderGlShaders::shaderVertexAttribPointer( ESHADERMETHOD shader, unsigned int index, int size, int type, bool normalized, int stride, const void * pointer )
{
    VerifyGLStateQt();
    int result = false;
    if( m_Shaders[ shader ] )
    {
        result = m_Shaders[ shader ]->shaderVertexAttribPointer( index, size, type, normalized, stride, pointer );
    }

    VerifyGLStateQt();
    return result;
}

//============================================================================
void RenderGlShaders::shaderEnableVertexAttribArray( ESHADERMETHOD shader, int arrayId )
{
    VerifyGLStateQt();
    if( m_Shaders[ shader ] )
    {
        m_Shaders[ shader ]->shaderEnableVertexAttribArray( arrayId );
    }

    VerifyGLStateQt();
}

//============================================================================
void RenderGlShaders::shaderDisableVertexAttribArray( ESHADERMETHOD shader, int arrayId )
{
    VerifyGLStateQt();
    if( m_Shaders[ shader ] )
    {
       m_Shaders[ shader ]->shaderDisableVertexAttribArray( arrayId );
    }

    VerifyGLStateQt();
}

//============================================================================
// shader method to string for debugging
const char * RenderGlShaders::describeShaderMethod( ESHADERMETHOD method )
{
    switch( method )
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

    default:
        return "UNKNOWN SHADER";
    }

}

//============================================================================
#ifdef DEBUG
void  RenderGlShaders::VerifyGLStateQtDbg( const char* szfile, const char* szfunction, int lineno )
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
void RenderGlShaders::VerifyGLStateQt()
{
    GLenum err = glGetError();
    if( err == GL_NO_ERROR )
        return;
    LogMsg( LOG_ERROR, "GL ERROR: %s\n", gluErrorString( err ) );
}
#endif

