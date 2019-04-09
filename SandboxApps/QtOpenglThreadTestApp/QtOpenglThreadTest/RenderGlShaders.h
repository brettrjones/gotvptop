#ifndef RENDERGLSHADERS_H
#define RENDERGLSHADERS_H

#include <QtGui/qopenglshaderprogram.h>
#include <QtGui/qopenglfunctions.h>

class RenderGlShaders : protected QOpenGLFunctions
{
public:
    RenderGlShaders();

    // must be called from gui thread (required for linux)
    bool initShaders();

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

#endif // RENDERGLSHADERS_H
