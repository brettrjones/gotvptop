#include "NetClientLogic.h"
#include "NetClientWidget.h"

#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QRandomGenerator>
#include <QSurface>
#include <qmath.h>
#include <QTimer>

//============================================================================
NetClientLogic::NetClientLogic( const QSurfaceFormat &format )
: m_format(format)
{
    m_context = new QOpenGLContext(this);
    m_context->setFormat(format);
    m_context->create();

    m_backgroundColor = QColor::fromRgbF(0.1f, 0.1f, 0.2f, 1.0f);
    m_backgroundColor.setRed(QRandomGenerator::global()->bounded(64));
    m_backgroundColor.setGreen(QRandomGenerator::global()->bounded(128));
    m_backgroundColor.setBlue(QRandomGenerator::global()->bounded(256));
}

//============================================================================
void NetClientLogic::setRenderThreadShouldRun( bool shouldRun )
{
    if( m_RenderThread )
    {
        m_RenderThread->setRenderThreadShouldRun( shouldRun );
    }
}

//============================================================================
//! called from gui thread when ready for opengl rendering
void NetClientLogic::glWidgetInitialized( QOpenGLContext * widgetGlContext )
{

}

//============================================================================
void NetClientLogic::setAnimating( NetClientWidget* window, bool animating )
{
    QMutexLocker locker(&m_renderMutex);
    if (m_windows.contains(window) == animating)
        return;

    if (animating) {
        m_windows << window;
        if (m_windows.size() == 1)
            QTimer::singleShot(0, this, &NetClientLogic::render);
    } else {
        m_currentWindow = 0;
        m_windows.removeOne(window);
    }
}

//============================================================================
void NetClientLogic::render()
{
    QMutexLocker locker(&m_renderMutex);

    if (m_windows.isEmpty())
        return;

    QOpenGLContext * renderContext = nullptr;
    QSurface * surface = nullptr;
    NetClientWidget * renderWidget = m_windows.at(m_currentWindow);
    if( renderWidget )
    {
        renderContext = renderWidget->getContext();
        if( renderContext )
        {
            surface = renderContext->surface();
        }
    }

    if( !renderWidget || !renderContext || !surface )
    {
        qWarning() << "NULL SURFACE";
        return;
    }


    QColor color = renderWidget->color();

    m_currentWindow = (m_currentWindow + 1) % m_windows.size();

    if (!m_context->makeCurrent(surface))
        return;

    QSize viewSize = surface->size();

    locker.unlock();

    if (!m_initialized) {
        initialize();
        m_initialized = true;
    }

    QOpenGLFunctions *f = m_context->functions();
    f->glViewport( 0, 0, viewSize.width(), viewSize.height() );
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    f->glClearColor(m_backgroundColor.redF(), m_backgroundColor.greenF(), m_backgroundColor.blueF(), m_backgroundColor.alphaF());
    f->glFrontFace(GL_CW);
    f->glCullFace(GL_FRONT);
    f->glEnable(GL_CULL_FACE);
    f->glEnable(GL_DEPTH_TEST);

    m_program->bind();
    m_vbo.bind();

    m_program->enableAttributeArray(vertexAttr);
    m_program->enableAttributeArray(normalAttr);
    m_program->setAttributeBuffer(vertexAttr, GL_FLOAT, 0, 3);
    const int verticesSize = vertices.count() * 3 * sizeof(GLfloat);
    m_program->setAttributeBuffer(normalAttr, GL_FLOAT, verticesSize, 3);

    QMatrix4x4 modelview;
    modelview.rotate(m_fAngle, 0.0f, 1.0f, 0.0f);
    modelview.rotate(m_fAngle, 1.0f, 0.0f, 0.0f);
    modelview.rotate(m_fAngle, 0.0f, 0.0f, 1.0f);
    modelview.translate(0.0f, -0.2f, 0.0f);

    m_program->setUniformValue(matrixUniform, modelview);
    m_program->setUniformValue(colorUniform, color);

    m_context->functions()->glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    m_context->swapBuffers(surface);

    m_fAngle += 1.0f;

    QTimer::singleShot(0, this, &NetClientLogic::render);
}

Q_GLOBAL_STATIC(QMutex, initMutex)

void NetClientLogic::initialize()
{
    // Threaded shader compilation can confuse some drivers. Avoid it.
    QMutexLocker lock(initMutex());

    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vshader->compileSourceCode(
        "attribute highp vec4 vertex;"
        "attribute mediump vec3 normal;"
        "uniform mediump mat4 matrix;"
        "uniform lowp vec4 sourceColor;"
        "varying mediump vec4 color;"
        "void main(void)"
        "{"
        "    vec3 toLight = normalize(vec3(0.0, 0.3, 1.0));"
        "    float angle = max(dot(normal, toLight), 0.0);"
        "    vec3 col = sourceColor.rgb;"
        "    color = vec4(col * 0.2 + col * 0.8 * angle, 1.0);"
        "    color = clamp(color, 0.0, 1.0);"
        "    gl_Position = matrix * vertex;"
        "}");

    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fshader->compileSourceCode(
        "varying mediump vec4 color;"
        "void main(void)"
        "{"
        "    gl_FragColor = color;"
        "}");

    m_program = new QOpenGLShaderProgram(this);
    m_program->addShader(vshader);
    m_program->addShader(fshader);
    m_program->link();
    m_program->bind();

    vertexAttr = m_program->attributeLocation("vertex");
    normalAttr = m_program->attributeLocation("normal");
    matrixUniform = m_program->uniformLocation("matrix");
    colorUniform = m_program->uniformLocation("sourceColor");

    m_fAngle = 0;
    createGeometry();

    m_vbo.create();
    m_vbo.bind();
    const int verticesSize = vertices.count() * 3 * sizeof(GLfloat);
    m_vbo.allocate(verticesSize * 2);
    m_vbo.write(0, vertices.constData(), verticesSize);
    m_vbo.write(verticesSize, normals.constData(), verticesSize);
}

void NetClientLogic::createGeometry()
{
    vertices.clear();
    normals.clear();

    qreal x1 = +0.06f;
    qreal y1 = -0.14f;
    qreal x2 = +0.14f;
    qreal y2 = -0.06f;
    qreal x3 = +0.08f;
    qreal y3 = +0.00f;
    qreal x4 = +0.30f;
    qreal y4 = +0.22f;

    quad(x1, y1, x2, y2, y2, x2, y1, x1);
    quad(x3, y3, x4, y4, y4, x4, y3, x3);

    extrude(x1, y1, x2, y2);
    extrude(x2, y2, y2, x2);
    extrude(y2, x2, y1, x1);
    extrude(y1, x1, x1, y1);
    extrude(x3, y3, x4, y4);
    extrude(x4, y4, y4, x4);
    extrude(y4, x4, y3, x3);

    const int NumSectors = 100;
    const qreal sectorAngle = 2 * qreal(M_PI) / NumSectors;
    for (int i = 0; i < NumSectors; ++i) {
        qreal angle = i * sectorAngle;
        qreal x5 = 0.30 * qSin(angle);
        qreal y5 = 0.30 * qCos(angle);
        qreal x6 = 0.20 * qSin(angle);
        qreal y6 = 0.20 * qCos(angle);

        angle += sectorAngle;
        qreal x7 = 0.20 * qSin(angle);
        qreal y7 = 0.20 * qCos(angle);
        qreal x8 = 0.30 * qSin(angle);
        qreal y8 = 0.30 * qCos(angle);

        quad(x5, y5, x6, y6, x7, y7, x8, y8);

        extrude(x6, y6, x7, y7);
        extrude(x8, y8, x5, y5);
    }

    for (int i = 0;i < vertices.size();i++)
        vertices[i] *= 2.0f;
}

void NetClientLogic::quad(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3, qreal x4, qreal y4)
{
    vertices << QVector3D(x1, y1, -0.05f);
    vertices << QVector3D(x2, y2, -0.05f);
    vertices << QVector3D(x4, y4, -0.05f);

    vertices << QVector3D(x3, y3, -0.05f);
    vertices << QVector3D(x4, y4, -0.05f);
    vertices << QVector3D(x2, y2, -0.05f);

    QVector3D n = QVector3D::normal
        (QVector3D(x2 - x1, y2 - y1, 0.0f), QVector3D(x4 - x1, y4 - y1, 0.0f));

    normals << n;
    normals << n;
    normals << n;

    normals << n;
    normals << n;
    normals << n;

    vertices << QVector3D(x4, y4, 0.05f);
    vertices << QVector3D(x2, y2, 0.05f);
    vertices << QVector3D(x1, y1, 0.05f);

    vertices << QVector3D(x2, y2, 0.05f);
    vertices << QVector3D(x4, y4, 0.05f);
    vertices << QVector3D(x3, y3, 0.05f);

    n = QVector3D::normal
        (QVector3D(x2 - x4, y2 - y4, 0.0f), QVector3D(x1 - x4, y1 - y4, 0.0f));

    normals << n;
    normals << n;
    normals << n;

    normals << n;
    normals << n;
    normals << n;
}

void NetClientLogic::extrude(qreal x1, qreal y1, qreal x2, qreal y2)
{
    vertices << QVector3D(x1, y1, +0.05f);
    vertices << QVector3D(x2, y2, +0.05f);
    vertices << QVector3D(x1, y1, -0.05f);

    vertices << QVector3D(x2, y2, -0.05f);
    vertices << QVector3D(x1, y1, -0.05f);
    vertices << QVector3D(x2, y2, +0.05f);

    QVector3D n = QVector3D::normal
        (QVector3D(x2 - x1, y2 - y1, 0.0f), QVector3D(0.0f, 0.0f, -0.1f));

    normals << n;
    normals << n;
    normals << n;

    normals << n;
    normals << n;
    normals << n;
}


//============================================================================
bool NetClientLogic::initRenderSystem()
{
    return false;
}

//============================================================================
bool NetClientLogic::destroyRenderSystem()
{
    return false;
}

//============================================================================
bool NetClientLogic::resetRenderSystem( int width, int height )
{
    return false;
}

//============================================================================
bool NetClientLogic::beginRender()
{
    return false;
}

//============================================================================
bool NetClientLogic::endRender()
{
    return false;
}

//============================================================================
void NetClientLogic::presentRender( bool rendered, bool videoLayer )
{

}
