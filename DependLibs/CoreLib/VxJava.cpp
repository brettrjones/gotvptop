#include "VxJava.h"

#include <CoreLib/VxThread.h>
#include <CoreLib/VxGlobals.h>

#define FROM_NATIVE_LOG_TAG "NativeFromJava:"

JavaVM *             VxJava::m_JavaVM = nullptr;
JNIEnv *             VxJava::m_JavaEnv = nullptr;

VxMutex						g_FromJavaAccessMutex;

namespace
{
    int							g_JniLoadCalledCnt	= 0;
    VxMutex						g_oJavaMutex;
    VxJava                      g_VxJava;
}

VxJava& GetJavaEnvCache()
{
    return g_VxJava;
}

//============================================================================
void ThreadStartCallbackFunction( unsigned int uiThreadId, const char * threadName )
{
    //MyAndroidPrint( ANDROID_LOG_INFO, FROM_NATIVE_LOG_TAG, "ThreadStartCallbackFunction Thread %d %s\n", uiThreadId, threadName );
}

//============================================================================
void ThreadExitCallbackFunction( unsigned int uiThreadId, bool isExitCallbackLocked, const char * threadName )
{
    if( false == isExitCallbackLocked )
    {
        g_FromJavaAccessMutex.lock();
    }

    //LogMsg( LOG_ERROR, "ThreadExitCallbackFunction Thread %d %s detaching\n", uiThreadId, threadName );

    GetJavaEnvCache().getJavaVM()->DetachCurrentThread();
    if ( false == isExitCallbackLocked )
    {
        g_FromJavaAccessMutex.unlock();
    }
}

VxJava::VxJava()
{

}

//============================================================================
jint JNI_OnLoad( JavaVM * vm, void * reserved )
{
    //__android_log_write( ANDROID_LOG_INFO, FROM_NATIVE_LOG_TAG, "JNI_OnLoad start" );
    g_JniLoadCalledCnt++;
    VxJava::m_JavaVM = vm;
    JNIEnv * env;
    if( vm->GetEnv( ( void** ) &env, JNI_VERSION_1_6 ) )
    {
        //__android_log_write( ANDROID_LOG_INFO, FROM_NATIVE_LOG_TAG, "JNI_OnLoad FAIL Get Env" );
        return -1;
    }

    VxJava::m_JavaEnv = env;
    if( 0 == env )
    {
        //__android_log_write( ANDROID_LOG_INFO, FROM_NATIVE_LOG_TAG, "JNI_OnLoad NULL Get Env" );
    }

    g_FromJavaAccessMutex.lock();
    // set up thread exit callback so we can attach thread to java
    VxThread::setThreadStartCallback( ThreadStartCallbackFunction );

    // set up thread exit callback so we can detach thread from java
    VxThread::setThreadExitCallback( ThreadExitCallbackFunction );

    //GetNativeToJavaClass(); // force register for this thread
    //LogMsg( LOG_WARN, "JJ JNI_OnLoad called JAVA VM 0x%x Load Count %d\n", g_poJavaVM, g_JniLoadCalledCnt );

    g_FromJavaAccessMutex.unlock();

    return JNI_VERSION_1_6;
}

//============================================================================
void JNI_OnUnload(JavaVM *vm, void *reserved)
{
    VxSetAppIsShuttingDown( true );
    //GetEngineImp().getEngine().getPeerMgr().stopListening();
    //__android_log_write( ANDROID_LOG_INFO, FROM_NATIVE_LOG_TAG, "JNI_OnUnload" );
}
