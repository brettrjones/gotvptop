#pragma once

#include <QThread>
#include <QOpenGLContext>
#include <QOffscreenSurface>

class RenderGlOffScreenSurface;

class KodiThread : public QThread //, protected QOpenGLFunctions
{
public:
    // the background thread's context and surface
    QOpenGLContext *            m_Context = nullptr;
    RenderGlOffScreenSurface *  m_Surface = nullptr;
    QOpenGLFramebufferObject *  m_renderFbo;
    QOpenGLFramebufferObject *  m_displayFbo;

    //LogoRenderer *m_logoRenderer;
    QSize                       m_size;


    KodiThread()
    {
        m_Context = new QOpenGLContext();
        //m_Surface = new QOffscreenSurface();
    }

    void resize( int width, int height )
    {
        //m_Context->makeCurrent( m_Surface );
    }

    void makeCurrent()
    {
        m_Context->makeCurrent( m_Surface );
    }

    void initializeGL()
    {
    //    initializeOpenGLFunctions();
    }
};
