//============================================================================
// Copyright (C) 2018 Brett R. Jones
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

#include "ActivitySnapShot.h"
#include "AppletMgr.h"
#include "AppletUserIdentity.h"
#include "AppCommon.h"
#include "AppGlobals.h"
#include "AppSettings.h"
#include "GuiHelpers.h"
#include "MyIcons.h"
#include "VxDataHelper.h"

#include <QMessageBox>
#include <QUuid>
#include <QFileDialog>

#include <GoTvCore/GoTvP2P/P2PEngine/EngineSettings.h>
#include <CoreLib/VxFileUtil.h>
#include <CoreLib/VxDebug.h>
#include <CoreLib/VxGlobals.h>

#define SUPPORTED_IMAGE_FILES "Image files (*.bmp *.gif *.jpg *.jpeg *.png *.pbm *.pgm *.ppm *.xbm *.xpm)"

//============================================================================
AppletUserIdentity::AppletUserIdentity( AppCommon& app, QWidget * parent )
: AppletBase( OBJNAME_APPLET_USER_IDENTITY, app, parent )
, m_bUserPickedImage( false )
, m_bUsingDefaultImage( true )
{
    setAppletType( eAppletUserIdentity );
    ui.setupUi( getContentItemsFrame() );
	setTitleBarText( DescribeApplet( m_EAppletType ) );
    ui.m_EditAboutMeButton->setIcon( eMyIconServiceShareAboutMe );
    ui.m_EditAvatarImageButton->setIcon( eMyIconServiceAvatarImage );
    GuiHelpers::fillGender( ui.m_GenderComboBox );
    GuiHelpers::fillLanguage( ui.m_LanguageComboBox );
    GuiHelpers::fillContentRating( ui.m_ContentComboBox );

    m_MyIdent = m_MyApp.getAppGlobals().getUserIdent();
    m_strOrigOnlineName = m_MyIdent->getOnlineName();
    m_strOrigMoodMessage = m_MyIdent->getOnlineDescription();

    GuiHelpers::setValuesFromIdentity( this, m_MyIdent, ui.m_AgeEdit, ui.m_GenderComboBox, ui.m_LanguageComboBox, ui.m_ContentComboBox );

    connect( ui.m_ApplyNameButton, SIGNAL( clicked() ), this, SLOT( onApplyNameClick() ) );
    connect( ui.m_ApplyMoodButton, SIGNAL( clicked() ), this, SLOT( onApplyMoodMsgClick() ) );
    connect( ui.m_ApplyAgeButton, SIGNAL( clicked() ), this, SLOT( onApplyAgeClick() ) );
    connect( ui.m_ApplyGenderButton, SIGNAL( clicked() ), this, SLOT( onApplyGenderClick() ) );

    connect( ui.m_EditAboutMeButton, SIGNAL( clicked() ), this, SLOT( slotEditAboutMeButClick() ) );
    connect( ui.m_EditAvatarImageButton, SIGNAL( clicked() ), this, SLOT( slotEditAvatarButClick() ) );

    loadIdentityFromDb();

	m_MyApp.activityStateChange( this, true );
}

//============================================================================
void AppletUserIdentity::loadIdentityFromDb()
{
    QString strOnlineName = m_MyIdent->getOnlineName();
    ui.m_OnlineNameEdit->setText( strOnlineName );

    QString strMoodMessage = m_MyIdent->getOnlineDescription();
    ui.m_MoodMessageEdit->setText( strMoodMessage );
}

//============================================================================
//! apply name change
void AppletUserIdentity::onApplyNameClick( void )
{
    if( false == validateUserName() )
    {
        return;
    }

    QString onlineName = ui.m_OnlineNameEdit->text();

    if( onlineName != m_strOrigOnlineName )
    {
        std::string strOnlineName = onlineName.toUtf8().constData();
        // TODO apply name change to user specific data directory

        m_MyIdent->setOnlineName( strOnlineName.c_str() );
        m_MyApp.getDataHelper().updateAccount( *m_MyIdent );
        m_Engine.fromGuiOnlineNameChanged( strOnlineName.c_str() );
        QString msgText = QObject::tr( "Applied Online Name Change " );
        QMessageBox::information( this, QObject::tr( "Online Name Change Success" ), msgText );
    }
}

//============================================================================
//! apply mood message change
void AppletUserIdentity::onApplyMoodMsgClick( void )
{
    if( false == validateMoodMessage() )
    {
        return;
    }

    QString moodMsg = ui.m_MoodMessageEdit->text();

    if( moodMsg != m_strOrigMoodMessage )
    {
        std::string strOnlineDesc = moodMsg.toUtf8().constData();
        m_MyIdent->setOnlineDescription( strOnlineDesc.c_str() );
        m_MyApp.getDataHelper().updateAccount( *m_MyIdent );
        m_Engine.fromGuiMoodMessageChanged( strOnlineDesc.c_str() );
        QString msgText = QObject::tr( "Applied Mood Message Change " );
        QMessageBox::information( this, QObject::tr( "Mood Message Change Success" ), msgText );
    }
}

//============================================================================
void AppletUserIdentity::onApplyAgeClick( void )
{
    if( GuiHelpers::validateAge( this, ui.m_AgeEdit->text().toInt() ) )
    {
        m_MyIdent = m_MyApp.getAppGlobals().getUserIdent();
        GuiHelpers::setIdentityFromValues( this, m_MyIdent, ui.m_AgeEdit, ui.m_GenderComboBox, ui.m_LanguageComboBox, ui.m_ContentComboBox );

        m_MyApp.getDataHelper().updateAccount( *m_MyIdent );
        m_Engine.fromGuiIdentPersonalInfoChanged( m_MyIdent->getAge(), m_MyIdent->getGender(), m_MyIdent->getPrimaryLanguage(), m_MyIdent->getPreferredContent() );

        QString msgText = QObject::tr( "Applied Age and Preferred Content Change " );
        QMessageBox::information( this, QObject::tr( "Age and Preferred Content Success" ), msgText );
    }
}
//============================================================================
void AppletUserIdentity::onApplyContentClick( void )
{
    if( GuiHelpers::validateAge( this, ui.m_AgeEdit->text().toInt() ) )
    {
        m_MyIdent = m_MyApp.getAppGlobals().getUserIdent();
        GuiHelpers::setIdentityFromValues( this, m_MyIdent, ui.m_AgeEdit, ui.m_GenderComboBox, ui.m_LanguageComboBox, ui.m_ContentComboBox );

        m_MyApp.getDataHelper().updateAccount( *m_MyIdent );
        m_Engine.fromGuiIdentPersonalInfoChanged( m_MyIdent->getAge(), m_MyIdent->getGender(), m_MyIdent->getPrimaryLanguage(), m_MyIdent->getPreferredContent() );

        QString msgText = QObject::tr( "Applied Mood Message Change " );
        QMessageBox::information( this, QObject::tr( "Mood Message Change Success" ), msgText );
    }
}

//============================================================================
//! Implement the OnClickListener callback    
void AppletUserIdentity::slotEditAboutMeButClick( void )
{
    m_MyApp.getAppletMgr().launchApplet( eAppletEditAboutMe, this );
}

//============================================================================
//! Implement the OnClickListener callback    
void AppletUserIdentity::slotEditAvatarButClick( void )
{
    m_MyApp.getAppletMgr().launchApplet( eAppletEditAvatarImage, this );
}

//============================================================================
//! validate user input
QString AppletUserIdentity::validateString( QString charSeq )
{
    //return charSeq.toString();    	
    return charSeq;
}

//============================================================================
bool AppletUserIdentity::validateUserName( void )
{
    QString strUserName = ui.m_OnlineNameEdit->text();
    return GuiHelpers::validateUserName( this, strUserName );
}

//============================================================================
bool AppletUserIdentity::validateMoodMessage( void )
{
    QString strMoodMsg = ui.m_MoodMessageEdit->text();
    return GuiHelpers::validateMoodMessage( this, strMoodMsg );
}
