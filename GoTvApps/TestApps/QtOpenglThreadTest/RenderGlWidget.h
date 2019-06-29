#ifndef RENDERGLWIDGET_H
#define RENDERGLWIDGET_H

#include "RenderGlThread.h"
#include "RenderGlLogic.h"

#include <QEvent>
#include <QOpenGLWidget>

class RenderGlWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit RenderGlWidget(QWidget *parent = nullptr);

    QColor                      color() const;
    void                        updateColor();

    QOpenGLContext *			getContext( void )              { return m_WidgetContext; }

signals:
    void                        renderRequested();

public slots:
    void                        grabContext();

private slots:
    void                        onAboutToCompose();
    void                        onFrameSwapped();
    void                        onAboutToResize();
    void                        onResized();

protected:
    void                        initializeGL() override;
    void                        paintGL() override;
    void                        resizeGL(int, int) override;

    void                        paintEvent(QPaintEvent *) override { }

    virtual void				showEvent( QShowEvent * ev );
    virtual void				hideEvent( QHideEvent * ev );
    virtual void				closeEvent( QCloseEvent * ev );
    virtual void				resizeEvent( QResizeEvent * ev );

    virtual void                mousePressEvent(QMouseEvent *) override;

    int                         m_colorIndex = 0;
    QColor                      m_color;
	RenderGlThread *            m_RendererGlThread = nullptr;
    RenderGlLogic *             m_RendererLogic = nullptr;
    mutable QMutex              m_colorLock;
    QOpenGLContext *            m_WidgetContext = nullptr;
};

#endif // RENDERGLWIDGET_H
