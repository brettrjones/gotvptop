#ifndef RENDER_LOGO_SHADERS_H
#define RENDER_LOGO_SHADERS_H

#include <QtGui/qopenglshaderprogram.h>
#include <QtGui/qopenglfunctions.h>

#include "RenderGlShaders.h"

class RenderGlWidget;
class RenderLogoShaders : protected QOpenGLFunctions
{
public:
    RenderLogoShaders( RenderGlWidget& renderWidget)
        : QOpenGLFunctions() {}

    // must be called from gui thread (required for linux)
    bool initLogoShaders();

    QOpenGLShaderProgram&       getShader()     { return program1; }
    int&                        getVertexAttr() { return vertexAttr1; }
    int&                        getNormalAttr() { return normalAttr1; }
    int&                        getMatrixAttr() { return matrixUniform1; }

protected:
    QOpenGLShaderProgram        program1;
    int                         vertexAttr1;
    int                         normalAttr1;
    int                         matrixUniform1;
};

#endif // RENDER_LOGO_SHADERS_H
