#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
#ifdef USE_GLES_ONLY
    QApplication::setAttribute( Qt::AA_UseOpenGLES ); // force use of gles so can use gles shaders
#endif // USE_GLES_ONLY
    QApplication::setAttribute( Qt::AA_ShareOpenGLContexts );
    QApplication::setAttribute( Qt::AA_DontCheckOpenGLContextThreadAffinity );

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
