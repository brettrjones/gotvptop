#include "RenderGlShaders.h"
#include "RenderShaderQt.h"

#include <VxDebug.h>

#include <QDebug>
#include <QTimer>
#include <QFile>

#include <GL/glu.h>

#define SHADERS_INCLUDE 
#include "RenderShaderDefsGl.cpp"
//#include "RenderShaderDefsGlES.cpp"
 
//============================================================================
RenderGlShaders::RenderGlShaders( RenderGlLogic& renderGlWidget )
: m_RenderGlWidget( renderGlWidget )
{
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
    GLenum err = m_Glf->glGetError();
    if( err == GL_NO_ERROR )
        return;
    LogMsg( LOG_ERROR, "GL ERROR: %s\n", gluErrorString( err ) );
}
#endif

//============================================================================
void RenderGlShaders::compileShader( int shaderIdx )
{
    EShaderType shaderType = eShaderGui;
    ESHADERMETHOD shaderMethod = (ESHADERMETHOD)shaderIdx;

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
void RenderGlShaders::initShaders( QOpenGLFunctions * glf )
{
    m_Glf = glf;
    if( m_ShadersInited )
    {
        return;
    }

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
void RenderGlShaders::initialiseShaders()
{
    // ignore from kodi
}

//============================================================================
void RenderGlShaders::releaseShaders()
{
    // ignore from kodi
}

//============================================================================
bool RenderGlShaders::enableShader( ESHADERMETHOD method )
{
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


