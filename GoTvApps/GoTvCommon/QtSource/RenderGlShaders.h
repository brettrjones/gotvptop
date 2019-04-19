#ifndef RENDERGLSHADERS_H
#define RENDERGLSHADERS_H

#include "RenderShaderQt.h"
#include "EventsQtToGoTv.h"
#include "GoTvInterface/IGoTvRender.h"
#include "GoTvInterface/IGoTvEvents.h"

#include <QtGui/qopenglshaderprogram.h>
#include <QtGui/qopenglfunctions.h>

class RenderGlWidget;

class RenderGlShaders : public QOpenGLFunctions
{
public:

#ifdef DEBUG
    void VerifyGLStateQtDbg( const char* szfile, const char* szfunction, int lineno );
#  define VerifyGLStateQt() VerifyGLStateQtDbg(__FILE__, __FUNCTION__, __LINE__)
#else
    void VerifyGLStateQt();
#endif

    RenderGlShaders( RenderGlWidget& renderGlWidget );
    virtual ~RenderGlShaders();

    // must be called from gui thread (required for linux)
    void initShaders();

    // cleanup shaders
    void destroyShaders();

    // shader method to string for debugging
    const char *                describeShaderMethod( ESHADERMETHOD method );

    //virtual void                initialiseShaders();
    //virtual void                releaseShaders();
    virtual bool                enableShader( ESHADERMETHOD method );
    virtual bool                isShaderValid( ESHADERMETHOD method );
    virtual void                disableShader( ESHADERMETHOD method );
    virtual void                disableGUIShader();

    virtual int                 shaderGetPos( );
    virtual int                 shaderGetCol( )  ;
    virtual int                 shaderGetModel( )  ;
    virtual int                 shaderGetCoord0( );
    virtual int                 shaderGetCoord1( );
    virtual int                 shaderGetUniCol( );

    // yuv shader
    virtual void                shaderSetField( ESHADERMETHOD shader, int field );
    virtual void                shaderSetWidth( ESHADERMETHOD shader, int w );
    virtual void                shaderSetHeight( ESHADERMETHOD shader, int h );

    virtual void                shaderSetBlack( ESHADERMETHOD shader, float black );
    virtual void                shaderSetContrast( ESHADERMETHOD shader, float contrast );
    virtual void                shaderSetConvertFullColorRange( ESHADERMETHOD shader, bool convertFullRange );

    virtual int                 shaderGetVertexLoc( ESHADERMETHOD shader );
    virtual int                 shaderGetYcoordLoc( ESHADERMETHOD shader );
    virtual int                 shaderGetUcoordLoc( ESHADERMETHOD shader );
    virtual int                 shaderGetVcoordLoc( ESHADERMETHOD shader );

    virtual void                shaderSetMatrices( ESHADERMETHOD shader, const float *p, const float *m );
    virtual void                shaderSetAlpha( ESHADERMETHOD shader, float alpha );

    virtual void                shaderSetFlags( ESHADERMETHOD shader, unsigned int flags );
    virtual void                shaderSetFormat( ESHADERMETHOD shader, EShaderFormat format );
    virtual void                shaderSourceTexture( ESHADERMETHOD shader, int ytex );
    virtual void                shaderSetStepX( ESHADERMETHOD shader, float stepX );
    virtual void                shaderSetStepY( ESHADERMETHOD shader, float stepY );


    // filter shader
    virtual bool                shaderGetTextureFilter( ESHADERMETHOD shader, int& filter );
    virtual int                 shaderGetcoordLoc( ESHADERMETHOD shader );

    // renderqt
    virtual int                 shaderVertexAttribPointer( ESHADERMETHOD shader, unsigned int index, int size, int type, bool normalized, int stride, const void * pointer );
    virtual void                shaderEnableVertexAttribArray( ESHADERMETHOD shader, int arrayId );
    virtual void                shaderDisableVertexAttribArray( ESHADERMETHOD shader, int arrayId );


protected:
    void                        getShaderSourceCode( int shaderIdx, EShaderType& shaderType, std::string& shaderName, std::string& vertexShaderCode, std::string& fragmentShaderCode );
    void                        compileShader( int shaderIdx );

    RenderGlWidget&             m_RenderGlWidget;
    // shaders
    RenderShaderQt *            m_Shaders[ SM_MAX ];
    bool                        m_ShadersInited = false;
    ESHADERMETHOD               m_CurShaderMethodType = SM_DEFAULT;
};

#endif // RENDERGLSHADERS_H
