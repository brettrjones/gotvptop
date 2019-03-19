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

#include "config_gotvapps.h"
#include <CoreLib/VxGUID.h>
#include "RenderGlOffScreenSurface.h"

#include <QOpenGLWidget>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLContext>
#include <QtGui/QPainter>
#include <QtGui/QOpenGLShaderProgram>


#if QT_VERSION < 0x050300
#if defined(QT_OPENGL_ES_2)
#include <QtGui/QOpenGLFunctions_ES2>
#else
#include <QtGui/QOpenGLFunctions_1_1>
#endif
#else
#include <QtGui/QOpenGLFunctions>
#endif



class AppCommon;
class AppSettings;
class GoTvRenderFrame;
class QOffscreenSurface;
class QOpenGLFramebufferObject;

class RenderGlBaseWidget : public QOpenGLWidget
{
	Q_OBJECT
public:
    static const bool RENDER_FROM_THREAD = true;
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

	RenderGlBaseWidget( QWidget *parent=0 );
    virtual ~RenderGlBaseWidget( ) = default;


	AppCommon&					getMyApp( void )                { return m_MyApp; }
    QOpenGLContext *			getContext( void )              { return m_Context; }
    QOpenGLFunctions *			getGlFunctions( void )          { return m_GlF; }

    bool                        isReadyForRender() const        { return m_bRenderCreated && m_KodiSurface; }

    int                         getMaxTextureSize( void )       { return m_MaxTextureSize; }


    // these are call from gui thread
    virtual void                initShaders( void ) {};

    virtual void                initializeGL( void );
    virtual void                paintGL( void );
    virtual void                resizeGL(  int w, int h  );

    // if threaded call from thread else call from the functions above
    virtual void                doInitializeGL( void );
    virtual void                doPaintGL( void );
    virtual void                doResizeGL( int w, int h );

    // give derived widgets a chance to act on completion of function
    virtual void                onInitializeGL( void ) {};
    virtual void                onPaintGL( void ) {};
    virtual void                onResizeGL( int w, int h ) {};

#ifdef DEBUG
	void VerifyGLStateQtDbg( const char* szfile, const char* szfunction, int lineno );
#  define VerifyGLStateQt() VerifyGLStateQtDbg(__FILE__, __FUNCTION__, __LINE__)
#else
    void VerifyGLStateQt();
#endif 

signals:
    void                        signalGlResized( int w, int h );

protected:
    void                        initColorMatrix();
    void                        initYv12();

    //=== vars ===//
    AppCommon&				    m_MyApp;
    bool                        m_bRenderCreated;

    RenderGlOffScreenSurface *  m_KodiSurface = nullptr;

    QOpenGLFramebufferObject *  m_KodiFbo = nullptr;
    QOpenGLFramebufferObject *  m_WidgetFbo = nullptr;

    QOpenGLContext *            m_WidgetContext;
    QOpenGLContext *            m_KodiContext;
    QOpenGLContext *            m_Context; // current context.. either widget or kodi

    QOpenGLFunctions *          m_Gl;
#if QT_VERSION < 0x050300
# if defined(QT_OPENGL_ES_2)
    QOpenGLFunctions_ES2 *      m_GlF;
# else
    QOpenGLFunctions_1_1 *      m_GlF;
# endif
#else
    QOpenGLFunctions *          m_GlF;
#endif

    QMatrix4x4                  m_ColorMatrix;

    GlTextureDescriptor         m_TexDescriptor;
    bool                        m_TexturesInited;

    QSize                       m_ScreenSize;
    int                         m_MaxTextureSize;
};
