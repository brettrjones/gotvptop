#ifndef RENDERGLWIDGET_H
#define RENDERGLWIDGET_H

#include "RenderGlThread.h"
#include "RenderGlLogic.h"

#include <QEvent>
#include <QOpenGLWidget>
#include <QOpenGLFramebufferObject>

class RenderGlOffScreenSurface;

class RenderGlWidget : public RenderGlLogic
{
    Q_OBJECT
public:
    explicit RenderGlWidget(QWidget *parent = nullptr);
    virtual ~RenderGlWidget() override;

    void                        takeSnapshot();

signals:
    void                        renderRequested();

public slots:
    void                        slotOnFrameRendered();

protected:
 
    //void                        render();
    void                        paintEvent( QPaintEvent * ) override;

    virtual void				showEvent( QShowEvent * ev ) override;
    virtual void				hideEvent( QHideEvent * ev ) override;
    virtual void				closeEvent( QCloseEvent * ev ) override;
    virtual void				resizeEvent( QResizeEvent * ev ) override;

    virtual void                mousePressEvent(QMouseEvent *) override;

    bool                        m_WidgetGlInitialized = false;
};

#endif // RENDERGLWIDGET_H
