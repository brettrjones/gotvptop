#pragma once
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

#include "RenderGlLogic.h"
#include "RenderShaderQt.h"
#include "EventsQtToGoTv.h"
#include "GoTvInterface/IGoTvRender.h"
#include "GoTvInterface/IGoTvEvents.h"

class GoTvRenderFrame;
class CRenderBuffer;
class QKeyEvent;
class QMouseEvent;

class RenderGlWidget : public QOpenGLWidget, public IGoTvRender, public QOpenGLFunctions
{
	Q_OBJECT
public:
    static const int MAX_RENDER_PLANES = 3;
    static const int MAX_VISIBLE_OVERLAYS = 4;

    typedef struct
    {
        GLenum                  m_Target;
        GLint                   m_InternalFormat;
        GLenum                  m_Format;
        GLenum                  m_Type;
    } GlTextureDescriptor;

    typedef struct
    {
        GLsizei                 m_Width;
        GLsizei                 m_Height;
    } GlTextureSize;

    RenderGlWidget( QWidget *parent=0 );
    virtual ~RenderGlWidget( ) override;

#ifdef DEBUG
    void VerifyGLStateQtDbg( const char* szfile, const char* szfunction, int lineno );
#  define VerifyGLStateQt() VerifyGLStateQtDbg(__FILE__, __FUNCTION__, __LINE__)
#else
    void VerifyGLStateQt();
#endif

    AppCommon&				    getMyApp() { return  m_MyApp; }
    QOpenGLFunctions *          getGlFunctions() { return m_GlWidgetFunctions; }

    //! take a snapshot of current render
    void                        takeSnapshot();

    virtual void                initializeGL( void ) override;
    virtual void                paintGL( void ) override;
    virtual void                resizeGL(  int w, int h  ) override;

    //! ignore from kodi
    void                        initialiseShaders() override;
    //! ignore from kodi
    void                        releaseShaders() override;

    bool                        enableShader( ESHADERMETHOD method ) override;
    bool                        isShaderValid( ESHADERMETHOD method ) override;
    void                        disableShader( ESHADERMETHOD method ) override;
    void                        disableGUIShader() override;

    int                         shaderGetPos()  override;
    int                         shaderGetCol()  override;
    int                         shaderGetModel()  override;
    int                         shaderGetCoord0()  override;
    int                         shaderGetCoord1()  override;
    int                         shaderGetUniCol()  override;

    // yuv shader
    virtual void                shaderSetField( ESHADERMETHOD shader, int field )   override;
    virtual void                shaderSetWidth( ESHADERMETHOD shader, int w )   override;
    virtual void                shaderSetHeight( ESHADERMETHOD shader, int h )  override;

    virtual void                shaderSetBlack( ESHADERMETHOD shader, float black ) override;
    virtual void                shaderSetContrast( ESHADERMETHOD shader, float contrast ) override;
    virtual void                shaderSetConvertFullColorRange( ESHADERMETHOD shader, bool convertFullRange ) override;

    virtual int                 shaderGetVertexLoc( ESHADERMETHOD shader ) override;
    virtual int                 shaderGetYcoordLoc( ESHADERMETHOD shader ) override;
    virtual int                 shaderGetUcoordLoc( ESHADERMETHOD shader ) override;
    virtual int                 shaderGetVcoordLoc( ESHADERMETHOD shader ) override;

    virtual void                shaderSetMatrices( ESHADERMETHOD shader, const float *p, const float *m ) override;
    virtual void                shaderSetAlpha( ESHADERMETHOD shader, float alpha ) override;

    virtual void                shaderSetFlags( ESHADERMETHOD shader, unsigned int flags ) override;
    virtual void                shaderSetFormat( ESHADERMETHOD shader, EShaderFormat format ) override;
    virtual void                shaderSourceTexture( ESHADERMETHOD shader, int ytex ) override;
    virtual void                shaderSetStepX( ESHADERMETHOD shader, float stepX ) override;
    virtual void                shaderSetStepY( ESHADERMETHOD shader, float stepY )  override;

    // filter shader
    virtual bool                shaderGetTextureFilter( ESHADERMETHOD shader, int& filter ) override;
    virtual int                 shaderGetcoordLoc( ESHADERMETHOD shader ) override;

    // renderqt
    virtual int                 shaderVertexAttribPointer( ESHADERMETHOD shader, unsigned int index, int size, int type, bool normalized, int stride, const void * pointer ) override;
    virtual void                shaderEnableVertexAttribArray( ESHADERMETHOD shader, int arrayId ) override;
    virtual void                shaderDisableVertexAttribArray( ESHADERMETHOD shader, int arrayId ) override;

	// resizing window
	virtual void				onResizeBegin( QSize& newSize );
	virtual void				onResizeEvent( QSize& newSize );
	virtual void				onResizeEnd( QSize& newSize );

	void						onModuleState( EAppModule moduleNum, EModuleState moduleState );


    //============================================================================
    //=== to gui media/render ===//
    //============================================================================

    //=== textures ===//
    void                        setActiveGlTexture( unsigned int activeTextureNum = 0 /* 0 == GL_TEXTURE0 , 1 == GL_TEXTURE1 etc*/ ) override;

    void                        createTextureObject( CQtTexture * texture ) override;
    void                        destroyTextureObject( CQtTexture * texture ) override;
    bool                        loadToGPU( CQtTexture * texture ) override;
    void                        bindToUnit( CQtTexture * texture, unsigned int unit ) override;

    void                        beginGuiTexture( CGUITextureQt * guiTexture, GoTvColor color ) override;
    void                        drawGuiTexture( CGUITextureQt * textrue, float * x, float * y, float * z, const GoTvRect& texture, const GoTvRect& diffuse, int orientation ) override;
    void                        endGuiTexture( CGUITextureQt * guiTexture ) override;
    void                        drawQuad( const GoTvRect &rect, GoTvColor color, CBaseTexture * texture, const GoTvRect * texCoords ) override;

    bool                        firstBegin( CGUIFontTTFQt * font )  override;
    void                        lastEnd( CGUIFontTTFQt * font ) override;
    CVertexBuffer               createVertexBuffer( CGUIFontTTFQt * font, const std::vector<SVertex>& vertices )  override;
    void                        destroyVertexBuffer( CGUIFontTTFQt * font, CVertexBuffer& vertBuffer )  override;

    virtual void                deleteHardwareTexture( CGUIFontTTFQt * font )  override;
    virtual void                createStaticVertexBuffers( CGUIFontTTFQt * font )   override;
    virtual void                destroyStaticVertexBuffers( CGUIFontTTFQt * font )  override;

    //=== remder ===//
    void                        captureScreen( CScreenshotSurface * screenCaptrue, GoTvRect& captureArea ) override;

    void                        toGuiRenderVideoFrame( int textureIdx, CRenderBuffer* videoBuffer );
    bool                        initRenderSystem() override;
    bool                        destroyRenderSystem() override;
    bool                        resetRenderSystem( int width, int height ) override;

    int                         getMaxTextureSize( void ) override { return m_MaxTextureSize; }

    bool                        beginRender() override;
    bool                        endRender() override;
    void                        presentRender( bool rendered, bool videoLayer ) override;

    bool                        clearBuffers( GoTvColor color ) override;
    bool                        isExtSupported( const char* extension ) override;

    void                        setVSync( bool vsync ) override;
    void                        resetVSync() override {  }

    void                        setViewPort( const GoTvRect& viewPort ) override;
    void                        getViewPort( GoTvRect& viewPort ) override;

    bool                        scissorsCanEffectClipping() override;
    GoTvRect                    clipRectToScissorRect( const GoTvRect &rect ) override;
    void                        setScissors( const GoTvRect& rect ) override;
    void                        resetScissors() override;

    void                        captureStateBlock() override;
    void                        applyStateBlock() override;

    void                        setCameraPosition( const GoTvPoint &camera, int screenWidth, int screenHeight, float stereoFactor = 0.0f ) override;

    void                        applyHardwareTransform( const TransformMatrix &matrix ) override;
    void                        restoreHardwareTransform() override;
    bool                        supportsStereo( RENDER_STEREO_MODE /*mode*/ ) const override { return false; }

    bool                        testRender() override;

    void                        project( float &x, float &y, float &z ) override;



    // frame buffers
    virtual void                frameBufferGen( int bufCount, unsigned int* fboId ) override;
    virtual void                frameBufferDelete( int bufCount, unsigned int* fboId ) override;
    virtual void                frameBufferTexture2D( int target, unsigned int texureId )  override;
    virtual void                frameBufferBind( unsigned int fboId ) override;
    virtual bool                frameBufferStatus() override;

    void                        onThreadFrameRendered() { emit signalFrameRendered(); }

signals:
    void                        signalFrameRendered();

public slots:
	void						slotResizeWindowTimeout();
    void                        slotOnFrameRendered();

protected:
    //void                        paintEvent(QPaintEvent *) override { }

    virtual void				showEvent( QShowEvent * ev ) override;
    virtual void				hideEvent( QHideEvent * ev ) override;
    virtual void				closeEvent( QCloseEvent * ev ) override;
    virtual void                resizeEvent( QResizeEvent * ev ) override;

    virtual void				mousePressEvent( QMouseEvent * ev ) override;
    virtual void				mouseReleaseEvent( QMouseEvent * ev ) override;
    virtual void                mouseMoveEvent( QMouseEvent * ev ) override;

    virtual void                keyPressEvent( QKeyEvent * ev ) override;
    virtual void                keyReleaseEvent( QKeyEvent * ev ) override;

    void                        initTextures();
    void                        initColorMatrix();
    void                        initYv12();

    //=== vars ===//
    AppCommon&				    m_MyApp;
    EventsQtToGoTv              m_QtToKodi;
    RenderGlLogic               m_RenderLogic;

    bool                        m_RenderWidgetInited;
    GLuint                      m_TextureIds[ MAX_RENDER_PLANES ];
    GlTextureSize               m_TexSize[ MAX_RENDER_PLANES ];
    bool                        m_TexturesInited = false;
    GlTextureDescriptor         m_TexDescriptor;
    int                         m_MaxTextureSize = 2048;

    GoTvRenderFrame *            m_Frame = nullptr;

    // render
    int                         m_SrcWidth = 320;
    int                         m_SrcHeight = 240;
    GLint                       m_viewPort[ 4 ];

	// sizing window
    QSize                       m_ScreenSize;
    QSize						m_ResizingWindowSize;

    QTimer *					m_ResizingTimer = nullptr;
	bool						m_IsResizing = false;

    QOpenGLFunctions *          m_GlWidgetFunctions = nullptr;
    QOpenGLFunctions *          m_GlThreadFunctions = nullptr;

    QMatrix4x4                  m_ColorMatrix;
};
