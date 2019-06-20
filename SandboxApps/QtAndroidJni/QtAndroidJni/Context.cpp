/*
 *      Copyright (C) 2013 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "Context.h"
#include "PackageManager.h"
//#include <qtandroid/log.h>
//#include "Intent.h"
#include "IntentFilter.h"
#include "ClassLoader.h"
#include "jutils-details.hpp"
//#include "BroadcastReceiver.h"
#include "JNIThreading.h"
#include "ApplicationInfo.h"
#include "JNIFile.h"
//#include "ContentResolver.h"
//#include "BaseColumns.h"
//#include "MediaStore.h"
//#include "PowerManager.h"
//#include "Cursor.h"
//#include "ConnectivityManager.h"
//#include "AudioFormat.h"
//#include "AudioAttributes.h"
//#include "AudioManager.h"
//#include "AudioTrack.h"
//#include "Surface.h"
//#include "MediaCodec.h"
//#include "MediaCodecInfo.h"
//#include "MediaFormat.h"
//#include "Window.h"
//#include "View.h"
#include "Build.h"
//#include "DisplayMetrics.h"
//#include "Intent.h"
//#include "KeyEvent.h"
//#include "Settings.h"
//#include "Environment.h"
//#include "Document.h"
//#include "RecognizerIntent.h"
//#include "AudioDeviceInfo.h"
//#include "MediaSync.h"

//#include <qtandroid/native_activity.h>
#include <QAndroidJniObject>
#include <QtAndroid>
#include <QApplication>
#include <QDebug>
//#include <qpa/qplatformnativeinterface.h>

using namespace jni;

jhobject CJNIContext::m_context(0);

CJNIContext * g_JniContext = nullptr;

JavaVM * CJNIContext::m_JniJvm = nullptr;
JNIEnv * CJNIContext::m_JniEnv = nullptr;
AAssetManager* CJNIContext::m_AssetManager = nullptr;

std::string CJNIContext::CONNECTIVITY_SERVICE;

// must be called before main
void CJNIContext::createJniContext( JavaVM * jvm, JNIEnv * env )
{
    if( !g_JniContext )
    {
        g_JniContext = new CJNIContext( jvm, env );
    }
}

CJNIContext& CJNIContext::getJniContext()
{
    return *g_JniContext;
}

void CJNIContext::destroyJniContext()
{
    if( g_JniContext )
    {
        delete g_JniContext;
        g_JniContext = nullptr;
    }
}

CJNIContext::CJNIContext( JavaVM * jvm, JNIEnv * env )
{
    m_JniJvm = jvm;
    m_JniEnv = env;
    // attach thread may be needed if created in different thread
    //m_JniJvm->AttachCurrentThread(&m_JniEnv, NULL);

    QAndroidJniObject mainActivity = QtAndroid::androidActivity();
    if ( mainActivity.isValid() )
    {
        jobject activityObj = mainActivity.object();
        if( activityObj )
        {
            jclass clazzObj = m_JniEnv->GetObjectClass(activityObj);
            if ( clazzObj )
            {
                jmethodID idNativeActivity_getAppContext = m_JniEnv->GetMethodID(clazzObj, "getApplicationContext", "()Landroid/content/Context;");
                //qWarning() << idNativeActivity_getAppContext;
                jobject appContextObj = m_JniEnv->CallObjectMethod(activityObj, idNativeActivity_getAppContext, "()Landroid/content/Context;");

                if( appContextObj )
                {
                    jclass clazzContextObj = m_JniEnv->GetObjectClass(appContextObj);
                    if ( clazzContextObj )
                    {
                        m_context.reset( appContextObj );

                        CJNIBase::SetSDKVersion( 21 );
                        PopulateStaticFields();

                        jmethodID idGetAssets = m_JniEnv->GetMethodID(clazzContextObj, "getAssets", "()Landroid/content/res/AssetManager;");
                        m_AssetManager = AAssetManager_fromJava(env, env->CallObjectMethod(appContextObj, idGetAssets));
                        if( !m_AssetManager )
                        {
                            qWarning() << "m_AssetManager is null";
                        }
                    }
                }              
            }
            else
            {
                qWarning() << "clazz obj is null";
            }
        }
        else
        {
            qWarning() << "activity object is invalid";
        }
    }
    else
    {
        qWarning()<<"main activity is invalid";
    }
}

void CJNIContext::mainWindowInialized()
{
    CJNIApplicationInfo appInfo = getApplicationInfo();
    std::string strExecutablePath = appInfo.nativeLibraryDir;
    qWarning() << strExecutablePath.c_str();
}


void CJNIContext::activityInialized()
{
    m_JniJvm->AttachCurrentThread(&m_JniEnv, NULL);

    QAndroidJniObject activity1 = QtAndroid::androidActivity();
    if ( activity1.isValid() )
    {
        jobject activityObj = activity1.object();
        if( activityObj )
        {
            jclass clsObj = m_JniEnv->GetObjectClass(activityObj);
            if ( clsObj == nullptr )
            {
                qDebug()<<"clazz obj is null";
            }

            m_context.reset( clsObj );

            CJNIBase::SetSDKVersion( 21 );
            PopulateStaticFields();

        }
    }
    else
    {
        qWarning()<<"main activity is invalid";
    }

    jobject activityObj = activity1.object();
    if( activityObj )
    {
        jclass clsObj = m_JniEnv->GetObjectClass(activityObj);
        if (clsObj == NULL)
        {
            printf("cls obj is null");
        }

        m_context.reset( clsObj );
        CJNIPackageManager::PopulateStaticFields();

         jobject objAppContext = nullptr; //activity.callObjectMethod<jobject>( "getApplicationContext", "()Landroid/content/Context;" );
        if ( objAppContext )
        {
            m_context.reset( objAppContext );
            CJNIPackageManager::PopulateStaticFields();
        }
    }



    //jobject objAppContext = activityObj.callObjectMethod<jobject>( "getApplicationContext", "()Landroid/content/Context;" );

    //jmethodID idNativeActivity_getAppContext = m_JniEnv->GetMethodID(activityObj, "getApplicationContext", "()Landroid/content/Context;");

    QAndroidJniObject activity2 = QAndroidJniObject::callStaticObjectMethod(
                    "org/qtproject/qt5/android/QtNative", "activity",
                    "()Landroid/app/Activity;");   //activity is valid
    if ( activity2.isValid() )
    {
        qDebug()<<"acitvity 2 Valid";
    }

    jhclass contextClassHandle = find_class("android/content/Context");
    jclass contextClass = m_JniEnv->FindClass("android/content/Context");
    jmethodID mid = m_JniEnv->GetStaticMethodID( contextClass,
                 "getApplicationContext","()Landroid/content/Context;");
    //jclass contextClassObj = m_JniEnv->GetObjectClass(contextClass);
    //jclass clsAct = m_JniEnv->FindClass("android/app/Activity"); // does not work
    //jclass activityClass = m_JniEnv->FindClass( "org/qtproject/qt5/android/bindings/QtActivity" ); // does not work
    //jclass classNativeActivity = m_JniEnv->FindClass("android/app/NativeActivity"); //does not work
    //if ( classNativeActivity )
    {
        //QPlatformNativeInterface *interface = QApplication::platformNativeInterface();
        //QAndroidJniObject activity = (jobject)interface->nativeResourceForIntegration("QtActivity");

        //if(!activity.isValid())
        //{
            qDebug()<<"CLASS NOT VALID!!!!!!!!";
        //}
        //else
        {

             jmethodID idNativeActivity_getAppContext = m_JniEnv->GetMethodID(contextClass, "getApplicationContext", "()Landroid/content/Context;");
             jobject objAppContext = nullptr; //activity.callObjectMethod<jobject>( "getApplicationContext", "()Landroid/content/Context;" );
             if ( objAppContext )
             {
                 m_context.reset( objAppContext );
             }
        }
    }




//    jmethodID mid = m_JniEnv->GetStaticMethodID( contextClass,
//             "getContext","()Landroid/content/Context;");

 //   jmethodID mid = m_JniEnv->GetStaticMethodID(contextClassHandle,
 //             "getContext","()Landroid/content/Context;");
//    jobject mainActivity =  m_JniEnv->CallStaticObjectMethod( contextClass, mid);

//    jclass activityClass = m_JniEnv->FindClass("android/content/Context");
//    jhclass activityClassHandle = find_class("android/app/Activity");
 //   jclass activityClass = (jclass)m_JniEnv->NewGlobalRef(contextClass);


  //m_ActivityClass = env->FindClass("local/ttt/Text2Bitmap");

  // retrieve the Java instance of the main activity
  //jobject activity = (jobject)SDL_AndroidGetActivity();

//   mActivityClass = (jclass)((*mEnv)->NewGlobalRef(mEnv, cls));

//  jmethodID mid = (*env)->GetStaticMethodID(env, mActivityClass,
//          "getContext","()Landroid/content/Context;");
  //jobject activity =  (*env)->CallStaticObjectMethod(env, mActivityClass, mid);

  // find the Java class of the activity.
  //jclass activityClass(env->GetObjectClass(activity));
  //m_context.reset( activityClass );

//  CJNIBase::SetSDKVersion( 21 );
//  PopulateStaticFields();

}

void CJNIContext::PopulateStaticFields()
{
  jhclass clazz = find_class("android/content/Context");
  CONNECTIVITY_SERVICE = jcast<std::string>(get_static_field<jhstring>(clazz,"CONNECTIVITY_SERVICE"));

//  CJNIBaseColumns::PopulateStaticFields();
//  CJNIMediaStoreMediaColumns::PopulateStaticFields();
//  CJNIPowerManager::PopulateStaticFields();
  CJNIPackageManager::PopulateStaticFields();
//  CJNIMediaStoreMediaColumns::PopulateStaticFields();
//  CJNICursor::PopulateStaticFields();
//  CJNIContentResolver::PopulateStaticFields();
//  CJNIConnectivityManager::PopulateStaticFields();
//  CJNIAudioFormat::PopulateStaticFields();
//  CJNIAudioAttributes::PopulateStaticFields();
//  CJNIAudioManager::PopulateStaticFields();
//  CJNIAudioTrack::PopulateStaticFields();
//  CJNISurface::PopulateStaticFields();
//  CJNIMediaCodec::PopulateStaticFields();
//  CJNIMediaCodecInfoCodecProfileLevel::PopulateStaticFields();
//  CJNIMediaCodecInfoCodecCapabilities::PopulateStaticFields();
//  CJNIMediaFormat::PopulateStaticFields();
//  CJNIView::PopulateStaticFields();
  CJNIBuild::PopulateStaticFields();
  //CJNIDisplayMetrics::PopulateStaticFields();
//  CJNIIntent::PopulateStaticFields();
//  CJNIKeyEvent::PopulateStaticFields();
//  CJNISettings::PopulateStaticFields();
//  CJNIEnvironment::PopulateStaticFields();
//  CJNIDocument::PopulateStaticFields();
//  CJNIRecognizerIntent::PopulateStaticFields();
//  CJNIAudioDeviceInfo::PopulateStaticFields();
//  CJNIViewInputDevice::PopulateStaticFields();
//  CJNIMediaSync::PopulateStaticFields();
}

CJNIPackageManager CJNIContext::GetPackageManager()
{
  return call_method<jhobject>(m_context,
    "getPackageManager", "()Landroid/content/pm/PackageManager;");
}

//void CJNIContext::startActivity(const CJNIIntent &intent)
//{
//  call_method<void>(jhobject(m_context),
//    "startActivity", "(Landroid/content/Intent;)V",
//    intent.get_raw());
//}

int CJNIContext::checkCallingOrSelfPermission(const std::string &permission)
{
  return call_method<int>(m_context,
    "checkCallingOrSelfPermission", "(Ljava/lang/String;)I",
    jcast<jhstring>(permission));
}

//jhobject CJNIContext::getSystemService(const std::string &service)
//{
//  return call_method<jhobject>(m_context,
//    "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;",
//    jcast<jhstring>(service));
//}

//CJNIIntent CJNIContext::registerReceiver(const CJNIBroadcastReceiver &receiver, const CJNIIntentFilter &filter)
//{
//  return call_method<jhobject>(m_context,
//    "registerReceiver", "(Landroid/content/BroadcastReceiver;Landroid/content/IntentFilter;)Landroid/content/Intent;",
//    receiver.get_raw(), filter.get_raw());
//}

//CJNIIntent CJNIContext::registerReceiver(const CJNIIntentFilter &filter)
//{
//  return call_method<jhobject>(m_context,
//    "registerReceiver", "(Landroid/content/BroadcastReceiver;Landroid/content/IntentFilter;)Landroid/content/Intent;",
//    (jobject)NULL, filter.get_raw());
//}

//void CJNIContext::unregisterReceiver(const CJNIBroadcastReceiver &receiver)
//{
//  call_method<void>(m_context,
//    "unregisterReceiver", "(Landroid/content/BroadcastReceiver;)V",
//    receiver.get_raw());
//}

//void CJNIContext::sendBroadcast(const CJNIIntent &intent)
//{
//  call_method<void>(m_context,
//    "sendBroadcast", "(Landroid/content/Intent;)V",
//    intent.get_raw());
//}

//CJNIIntent CJNIContext::getIntent()
//{
//  return call_method<jhobject>(m_context,
//    "getIntent", "()Landroid/content/Intent;");
//}

CJNIClassLoader CJNIContext::getClassLoader()
{
  return call_method<jhobject>(m_context,
    "getClassLoader", "()Ljava/lang/ClassLoader;");
}

CJNIApplicationInfo CJNIContext::getApplicationInfo()
{
  return call_method<jhobject>(m_context,
    "getApplicationInfo", "()Landroid/content/pm/ApplicationInfo;");
}

std::string CJNIContext::getPackageName()
{
  return jcast<std::string>(call_method<jhstring>(m_context,
    "getPackageName", "()Ljava/lang/String;"));
}

std::string CJNIContext::getPackageResourcePath()
{
  return jcast<std::string>(call_method<jhstring>(m_context,
    "getPackageResourcePath", "()Ljava/lang/String;"));
}

CJNIFile CJNIContext::getCacheDir()
{
  return call_method<jhobject>(m_context,
    "getCacheDir", "()Ljava/io/File;");
}

CJNIFile CJNIContext::getDir(const std::string &path, int mode)
{
  return call_method<jhobject>(m_context,
    "getDir", "(Ljava/lang/String;I)Ljava/io/File;",
    jcast<jhstring>(path), mode);
}

CJNIFile CJNIContext::getExternalFilesDir(const std::string &path)
{
  return call_method<jhobject>(m_context,
    "getExternalFilesDir", "(Ljava/lang/String;)Ljava/io/File;",
    jcast<jhstring>(path));
}

//CJNIContentResolver CJNIContext::getContentResolver()
//{
//  return call_method<jhobject>(m_context,
//    "getContentResolver", "()Landroid/content/ContentResolver;");
//}

//CJNIWindow CJNIContext::getWindow()
//{
//  return call_method<jhobject>(m_context,
//    "getWindow", "()Landroid/view/Window;");
//}
