#pragma once

#include <QThread>
#include <QOpenGLContext>
#include <QOffscreenSurface>

class RenderGlOffScreenSurface;
class QOpenGLFramebufferObject;
class RenderGlBaseWidget;
class AppCommon;

class KodiThread : public QThread
{
    Q_OBJECT
public:
    KodiThread( AppCommon& app, QWidget * parent );
    virtual ~KodiThread() override = default;

    void                        setRenderWidget( RenderGlBaseWidget* renderWidget )     { m_RenderWidget = renderWidget; }
    RenderGlBaseWidget *        getRenderWidget()                                       { return m_RenderWidget; }

    void                        setGlContext( QOpenGLContext* kodiGlContext )           { m_KodiThreadContext = kodiGlContext; }
    QOpenGLContext*             getGlContext()                                          { return m_KodiThreadContext; }
    void                        setGlSurface( RenderGlOffScreenSurface* kodiSurface )   { m_KodiThreadSurface = kodiSurface; }
    RenderGlOffScreenSurface*   getGlSurface()                                          { return m_KodiThreadSurface; }

    //void                        resize( int width, int height );

    void                        makeCurrentGlContext();

    static bool                 isKodiRunning() { return m_IsKodiRunning; }

//private slots:
//    void						slotStartKodiRunFromThread( void );

protected:
    void                        run() override;

    AppCommon&                  m_MyApp;
    RenderGlBaseWidget *        m_RenderWidget = nullptr;

    static bool                 m_IsKodiRunning;

    // the background thread's context and surface
    QOpenGLContext *            m_KodiThreadContext = nullptr;
    RenderGlOffScreenSurface *  m_KodiThreadSurface = nullptr;
    QOpenGLFramebufferObject *  m_KodiThreadRenderFbo = nullptr;
    QOpenGLFramebufferObject *  m_KodiThreadDisplayFbo = nullptr;

    QSize                       m_KodiThreadSurfaceSize;
};
