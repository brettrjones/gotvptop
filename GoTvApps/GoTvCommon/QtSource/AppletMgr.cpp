//============================================================================
// Copyright (C) 2017 Brett R. Jones 
//
// You may use, copy, modify, merge, publish, distribute, sub-license, and/or sell this software 
// provided this Copyright is not modified or removed and is included all copies or substantial portions of the Software
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// bjones.engineer@gmail.com
// http://www.gotvptop.com
//============================================================================

#include "AppletMgr.h"
#include "ActivityBase.h"
#include "AppCommon.h"
#include "AppSettings.h"

#include "AppletAboutApp.h"
#include "AppletKodi.h"
#include "AppletGroupUser.h"
#include "AppletGroupHost.h"
#include "AppletGroupAnchor.h"
#include "AppletGoTvPtoPNetworkHost.h"
#include "AppletLibrary.h"
#include "AppletNetHostingPage.h"
#include "AppletNetworkSettings.h"
#include "AppletPersonalRecorder.h"
#include "AppletPlayerVideo.h"
#include "AppletRandomPerson.h"
#include "AppletSettings.h"
#include "AppletShareServicesPage.h"
#include "AppletSharedContent.h"
#include "AppletSharedWebCam.h"
#include "AppletStoryboard.h"
#include "AppletTheme.h"
#include "AppletRemoteControl.h"
#include "AppletUserIdentity.h"

#include "HomeWindow.h"


//============================================================================
AppletMgr::AppletMgr( AppCommon& myMpp, QWidget * parent )
: QWidget( parent )
, m_MyApp( myMpp )
{
}

//============================================================================
RenderGlWidget * AppletMgr::getRenderConsumer( void )
{
    RenderGlWidget * renderConsumer = nullptr;
    for( auto iter = m_ActivityList.begin(); iter != m_ActivityList.end(); ++iter )
    {
        if( eAppletKodi == (*iter)->getAppletType()  )
        {
            if( (*iter)->isVisible() )
            {
                renderConsumer = ( ( AppletKodi * )( *iter ) )->getRenderConsumer();
            }

            break;
        }
    }

    return renderConsumer;
}


//============================================================================
void AppletMgr::launchApplet( EApplet applet )
{
	launchApplet( applet, getActiveWindow() );
}

//============================================================================
QWidget * AppletMgr::getActiveWindow( void )
{
	QWidget * activeWidget = QApplication::activeWindow();
	if( 0 == activeWidget )
	{
		activeWidget = &m_MyApp.getHomePage();
	}

	return activeWidget;
}

//============================================================================
QFrame *  AppletMgr::getAppletFrame( EApplet applet )
{
	return m_MyApp.getAppletFrame( applet );
}

//============================================================================
void AppletMgr::launchApplet( EApplet applet, QWidget * parent )
{
//    ActivityAbout * activity;
	ActivityBase * appletDialog = findAppletDialog( applet );
	if( appletDialog )
	{
		bringAppletToFront( appletDialog );
#ifdef DEBUG
        m_MyApp.errMessageBox2( QObject::tr( "AppletMgr::launchApplet" ).toUtf8().constData(), QObject::tr( "Applet enum %d already launched\n" ).toUtf8().constData(), applet );
#endif // DEBUG

		return;
	}

	if( 0 == parent )
	{
		parent = getActiveWindow();
	}

	QString appletMissingTitle = QObject::tr( "Applet Not Yet Implemented" );
	switch( applet )
	{
    case eAppletAboutGoTvPtoP:
        appletDialog = new AppletAboutApp( m_MyApp, parent );
        break;
    case eAppletKodi:
        appletDialog = new AppletKodi( m_MyApp, parent );
        break;
//	case eAppletPlayerVideo:
//		appletDialog = new AppletPlayerVideo( m_MyApp, parent );
//		break;
//	case eAppletPlayerMusic:
//		m_MyApp.errMessageBox( appletMissingTitle, "MusicPlayer Not Implemented" );
//		return;
//	case eAppletPlayerPhoto:
//		m_MyApp.errMessageBox( appletMissingTitle, "ImagePlayer Not Implemented" );
//		return;
	//case eAppletStreamViewerVideo:
	//	m_MyApp.errMessageBox( appletMissingTitle, "VideoStreamViewer Not Implemented" );
	//	return;
	//case eAppletStreamViewerCam:
	//	m_MyApp.errMessageBox( appletMissingTitle, "CamStreamViewer Not Implemented" );
	//	return;
	//case eAppletStreamViewerMusic:
	//	m_MyApp.errMessageBox( appletMissingTitle, "MusicStreamViewer Not Implemented" );
	//	return;
	//case eAppletRemoteControl:
	//	appletDialog = new AppletRemoteControl( m_MyApp, parent );
	//	break;
	//case eAppletPlugins:
	//	m_MyApp.errMessageBox( appletMissingTitle, "Applet Plugins Not Implemented" );
	//	return;
    case eAppletPersonalRecorder:
        appletDialog = new AppletPersonalRecorder( m_MyApp, parent );
        return;
    case eAppletLibrary:
        appletDialog = new AppletLibrary( m_MyApp, parent );
    	return;
	case eAppletTheme:
		appletDialog = new AppletTheme( m_MyApp, parent );
		break;
    case eAppletNetworkSettings:
        appletDialog = new AppletNetworkSettings( m_MyApp, parent );
        break;
    case eAppletRandomPerson:
        appletDialog = new AppletRandomPerson( m_MyApp, parent );
        break;
    case eAppletSettings:
		appletDialog = new AppletSettings( m_MyApp, parent );
		break;
    case eAppletGroupUser:
        appletDialog = new AppletGroupUser( m_MyApp, parent );
        break;
    case eAppletNetHostingPage:
        appletDialog = new AppletNetHostingPage( m_MyApp, parent );
        break;
    case eAppletShareServicesPage:
        appletDialog = new AppletShareServicesPage( m_MyApp, parent );
        break;
    case eAppletGroupHost:
        appletDialog = new AppletGroupHost( m_MyApp, parent );
        break;
    case eAppletGroupAnchor:
        appletDialog = new AppletGroupAnchor( m_MyApp, parent );
        break;
    case eAppletGoTvPtoPNetworkHost:
        appletDialog = new AppletGoTvPtoPNetworkHost( m_MyApp, parent );
        break;
//	case ePluginAppletCamProvider:
//		m_MyApp.errMessageBox( appletMissingTitle, "Cam Provider Not Implemented" );
//		return;
//	case ePluginAppletGoTvStation:
//		m_MyApp.errMessageBox( appletMissingTitle, "Video Player Not Implemented" );
//		return;
//	case ePluginAppletGoTvNetworkHost:
//		m_MyApp.errMessageBox( appletMissingTitle, "Network Host Not Implemented" );
//		return;
	case eAppletHomePage:
		m_MyApp.errMessageBox( appletMissingTitle, "Home Page Not Implemented" );
		return;
	case eAppletMessenger:
		m_MyApp.errMessageBox( appletMissingTitle, "Messenger Not Implemented" );
		return;
	case eAppletUnknown:
		m_MyApp.errMessageBox( appletMissingTitle, "Unknown Not Implemented" );
		return;
    case eAppletUserIdentity:
        appletDialog = new AppletUserIdentity( m_MyApp, parent );
        break;
    case eAppletSharedContent:
        appletDialog = new AppletSharedContent( m_MyApp, parent );
        break;
    case eAppletSharedWebCam:
        appletDialog = new AppletSharedWebCam( m_MyApp, parent );
        break;
    case eAppletStoryboard:
        appletDialog = new AppletStoryboard( m_MyApp, parent );
        break;
	default:
		m_MyApp.errMessageBox2( QObject::tr( "AppCommon::launchApplet").toUtf8().constData(), QObject::tr( "Invalid Applet enum %d\n" ).toUtf8().constData(), applet );
		return;
	}

	if( appletDialog )
	{
        AppSettings& appSettings = m_MyApp.getAppSettings();
        appSettings.setLastAppletLaunched( applet );

        appletDialog->aboutToLaunchApplet();
        appletDialog->show();
        if( !findAppletDialog( appletDialog ) )
        {
            m_ActivityList.push_back( appletDialog );
        }
    }
}

//============================================================================
void AppletMgr::activityStateChange( ActivityBase * activity, bool isCreated )
{
	if( !isCreated )
	{
		//removeApplet( activity->getAppletType() );
        removeApplet( activity );
	}
	else
	{
		addApplet( activity );
	}
}

//============================================================================
void AppletMgr::bringAppletToFront( ActivityBase * appletDialog )
{

}

//============================================================================
ActivityBase * AppletMgr::findAppletDialog( EApplet applet )
{
	QVector<ActivityBase *>::iterator iter;
	for( iter = m_ActivityList.begin(); iter != m_ActivityList.end(); ++iter )
	{
		if( applet == (*iter)->getAppletType() )
		{
			return *iter;
		}
	}
	
	return nullptr;
}

//============================================================================
ActivityBase * AppletMgr::findAppletDialog( ActivityBase * activity )
{
    if( activity )
    {
        QVector<ActivityBase *>::iterator iter;
        for( iter = m_ActivityList.begin(); iter != m_ActivityList.end(); ++iter )
        {
            if( activity == ( *iter ) )
            {
                return *iter;
            }
        }
    }

    return nullptr;
}

//============================================================================
void AppletMgr::addApplet( ActivityBase * activity )
{
	if( 0 == findAppletDialog( activity ) )
	{
        m_ActivityList.push_back( activity );
	}
	else 
	{
		LogMsg( LOG_ERROR, " AppletMgr::addApplet: adding already existing applet\n" );
	}
}

//============================================================================
void AppletMgr::removeApplet( EApplet applet )
{
	QVector<ActivityBase *>::iterator iter;
	for( iter = m_ActivityList.begin(); iter != m_ActivityList.end(); ++iter )
	{
		if( applet == ( *iter )->getAppletType() )
		{
            m_ActivityList.erase( iter );
			break;
		}
	}
}

//============================================================================
void AppletMgr::removeApplet( ActivityBase * activity )
{
    QVector<ActivityBase *>::iterator iter;
    for( iter = m_ActivityList.begin(); iter != m_ActivityList.end(); ++iter )
    {
        if( activity == ( *iter ) )
        {
            m_ActivityList.erase( iter );
            break;
        }
    }
}
