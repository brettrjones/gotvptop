#ifndef RENDERGLLOGIC_H
#define RENDERGLLOGIC_H


#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QVector3D>
#include <QMatrix4x4>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QElapsedTimer>

class NetClientWidget;
class NetClientThread;


class NetClientLogic : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit NetClientLogic( const QSurfaceFormat &format );

    void						setRenderThread( NetClientThread * renderThread ) { m_RenderThread = renderThread; }
    void						setRenderThreadShouldRun( bool shouldRun );
    //! called from gui thread when ready for opengl rendering
    void						glWidgetInitialized( QOpenGLContext * widgetGlContext );

    QSurfaceFormat              format() const { return m_format; }

    void                        lockRenderer() { m_renderMutex.lock(); }
    void                        unlockRenderer() { m_renderMutex.unlock(); }
    QMutex *                    grabMutex() { return &m_grabMutex; }
    QWaitCondition *            grabCond() { return &m_grabCond; }
    void                        prepareExit() { m_exiting = true; m_grabCond.wakeAll(); }


    void                        setAnimating( NetClientWidget* window, bool animating );

    virtual bool                initRenderSystem();
    virtual bool                destroyRenderSystem();
    virtual bool                resetRenderSystem( int width, int height );

    virtual int                 getMaxTextureSize() { return 2048; }

    virtual bool                beginRender();
    virtual bool                endRender();
    virtual void                presentRender( bool rendered, bool videoLayer );

	

public slots:
    void                        render();

private:
    void                        initialize();

    void                        createGeometry();
    void                        createBubbles(int number);
    void                        quad(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3, qreal x4, qreal y4);
    void                        extrude(qreal x1, qreal y1, qreal x2, qreal y2);

    qreal                       m_fAngle        = 0.0f;

    QVector<QVector3D>          vertices;
    QVector<QVector3D>          normals;
    int                         vertexAttr      = 0;
    int                         normalAttr      = 0;
    int                         matrixUniform   = 0;
    int                         colorUniform    = 0;

    bool                        m_initialized   = false;
    QSurfaceFormat              m_format;
    QOpenGLContext *            m_context       = nullptr;
    QOpenGLShaderProgram *      m_program       = nullptr;
    QOpenGLBuffer               m_vbo;

    QList<NetClientWidget *>     m_windows;
    int                         m_currentWindow = 0;

    QMutex                      m_renderMutex;
    QMutex                      m_grabMutex;
    QWaitCondition              m_grabCond;
    bool                        m_exiting = false;

    QColor                      m_backgroundColor;
	NetClientThread *			m_RenderThread = nullptr;
};

#endif // RENDERGLLOGIC_H
