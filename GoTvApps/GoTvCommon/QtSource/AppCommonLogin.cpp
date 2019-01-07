//============================================================================
// Copyright (C) 2018 Brett R. Jones 
// Issued to MIT style license by Brett R. Jones
//
// You may use, copy, modify, merge, publish, distribute, sub-license, and/or sell this software 
// provided this Copyright is not modified or removed and is included all copies or substantial portions of the Software
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// brett.jones@engineer.com
// http://www.gotvptop.net
//============================================================================

#include "AppCommon.h"	
#include "AppSettings.h"
#include "AppletMgr.h"


#include "ActivityCreateProfile.h"

#include "VxDataHelper.h"

//============================================================================
void AppCommon::doLogin()
{

doover:
    bool bLastUserAccountLoaded = loadLastUserAccount();
    if( bLastUserAccountLoaded )
    {
        doAccountStartup();
    }
    else
    {
        applySoundSettings( true );
        // user needs to create login and profile
        m_CreateProfileDlg->setRootUserDataDirectory( m_AppSettings.m_strRootUserDataDir.c_str() );
        if( QDialog::Rejected == m_CreateProfileDlg->exec() )
        {
            m_bUserCanceledCreateProfile = true;
            close();
            return;
        }

        if( false == m_CreateProfileDlg->wasLoginNameEntered() )
        {
            goto doover;
        }
        else
        {
            doAccountStartup();
            return;
        }
    }
}

//============================================================================
void AppCommon::doAccountStartup( void )
{
    // tell engine were to load settings from
    loadAccountSpecificSettings( getAppGlobals().getUserIdent()->getOnlineName() );
    getAppGlobals().getUserIdent()->setHasSharedWebCam( false ); // user must restart cam server each startup.. assume no shared cam yet

    applySoundSettings();

    sendAppSettingsToEngine();

    startNetworkMonitor();

    completeLogin();
}

//============================================================================
void AppCommon::completeLogin( void )
{
    //showUserNameInTitle();

    VxNetIdent * netIdent = getAppGlobals().getUserIdent();
    m_Engine.fromGuiUserLoggedOn( netIdent );

    // get settings from engine
    m_eLastSelectedWhichContactsToView = m_Engine.getEngineSettings().getWhichContactsToView();
    //ui.m_ListViewTypeComboBox->setCurrentIndex( m_eLastSelectedWhichContactsToView );
    //connect( ui.m_ListViewTypeComboBox, SIGNAL(currentIndexChanged(int)),	this,	SLOT(slotListViewTypeChanged(int)) );
    slotListViewTypeChanged( m_eLastSelectedWhichContactsToView );


    //if( netIdent->requiresRelay() && (false == netIdent->hasValidRelay()) )
    //{	
    //	netIdent->setHasRelay( false );
    //	emit signalStatusMsg( "User must select a relay" );
    //	m_Engine.fromGuiSendContactList( eFriendViewAllProxies, 500 );
    //}
    //else
    //{
    //	m_Engine.fromGuiSendContactList( m_eLastSelectedWhichContactsToView, 500 );
    //}

    EApplet lastLaunchedApplet = getAppSettings().getLastAppletLaunched();
    if( eAppletKodi == lastLaunchedApplet )
    {
        m_AppletMgr.launchApplet( lastLaunchedApplet, m_AppletMgr.getAppletFrame( lastLaunchedApplet ) );
    }
}

//============================================================================
//! load last successful user account
bool AppCommon::loadLastUserAccount( void )
{
    m_strAccountUserName = m_DataHelper.getLastLogin();

    if( 0 != m_strAccountUserName.length() )
    {
        // get identity out of database
        if( true == m_DataHelper.getAccountByName( m_strAccountUserName.c_str(), *getAppGlobals().getUserIdent() ) )
        {
            return true;
        }
        else
        {
            // remove old missing or corrupted account 
            m_DataHelper.removeAccountByName( m_strAccountUserName.c_str() );
            LogMsg( LOG_INFO, "AppCommon:Could not retrieve user\n" );
        }
    }

    return false;
}
