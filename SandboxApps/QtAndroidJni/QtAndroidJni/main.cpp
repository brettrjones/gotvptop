#include "mainwindow.h"
#include <QApplication>
#include "VxDebug.h"
#ifdef TARGET_OS_ANDROID
# include <jni.h>
# include "Context.h"
# include "JNIThreading.h"
# include "VxJava.h"
#endif // TARGET_OS_ANDROID

int main(int argc, char *argv[])
{
#ifdef TARGET_OS_ANDROID
    LogMsg( LOG_DEBUG, "Initialize Java" );
    xbmc_jni_on_load( GetJavaEnvCache().getJavaVM(),  GetJavaEnvCache().getJavaEnv() );
#endif // TARGET_OS_ANDROID
    LogMsg( LOG_DEBUG, "Creating QApplication" );
    QApplication a(argc, argv);
    CJNIContext::createJniContext( GetJavaEnvCache().getJavaVM(),  GetJavaEnvCache().getJavaEnv() );
    MainWindow w; 
    LogMsg( LOG_DEBUG, "Showing Window" );
    w.show();
    LogMsg( LOG_DEBUG, "Running app.exec" );
    int exitCode = a.exec();
#ifdef TARGET_OS_ANDROID
    xbmc_jni_on_unload();
#endif // TARGET_OS_ANDROID
    return exitCode;
}

