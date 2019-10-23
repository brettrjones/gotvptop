//============================================================================
// Copyright (C) 2010 Brett R. Jones
// Issued to MIT style license by Brett R. Jones in 2017
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

#include "AppletNetworkSettings.h"
#include "ActivityIsPortOpenTest.h"
#include "ActivityNetworkState.h"
#include "ActivityInformation.h"

#include "AppGlobals.h"
#include "AppCommon.h"
#include "AppSettings.h"
#include "MyIcons.h"
#include "VxDataHelper.h"

#include <CoreLib/VxDebug.h>
#include <NetLib/NetHostSetting.h>
#include <NetLib/VxGetRandomPort.h>
#include <NetLib/VxSktUtil.h>


namespace
{
    QString				DEFAULT_ADAPTER_IP_CHOICE = "default";
}

//============================================================================
AppletNetworkSettings::AppletNetworkSettings( AppCommon& app, QWidget * parent )
: AppletBase( OBJNAME_APPLET_NETWORK_SETTINGS, app, parent )
{
	setAppletType( eAppletNetworkSettings );
	ui.setupUi( getContentItemsFrame() );
	setTitleBarText( DescribeApplet( m_EAppletType ) );

    ui.m_NetworkHostInfoButton->setIcon( eMyIconInformation );
    ui.m_NetworkHostButton->setIcon( eMyIconServiceHostNetwork );
    ui.m_NetworkKeyInfoButton->setIcon( eMyIconInformation );
    ui.m_NetworkKeyButton->setIcon( eMyIconNetworkKey );

    updateDlgFromSettings();

    connectSignals();

	m_MyApp.activityStateChange( this, true );
}

//============================================================================
AppletNetworkSettings::~AppletNetworkSettings()
{
    m_MyApp.activityStateChange( this, false );
}

//============================================================================
void AppletNetworkSettings::connectSignals( void )
{
    connect( ui.m_NetworkHostButton, SIGNAL( clicked() ), this, SLOT( slotShowNetworkHostInformation() ) );
    connect( ui.m_NetworkHostInfoButton, SIGNAL( clicked() ), this, SLOT( slotShowNetworkHostInformation() ) );
    connect( ui.m_NetworkKeyInfoButton, SIGNAL( clicked() ), this, SLOT( slotShowNetworkKeyInformation() ) );
    connect( ui.m_NetworkKeyButton, SIGNAL( clicked() ), this, SLOT( slotShowNetworkKeyInformation() ) );

    //connect( ui.m_GoToAnchortSettingsButton, SIGNAL( clicked() ), this, SLOT( slotGoToNetHostSettingsButtonClick() ) );

    connect( ui.AutoDetectProxyRadioButton, SIGNAL( clicked() ), this, SLOT( slotAutoDetectProxyClick() ) );
    connect( ui.AssumeNoProxyRadioButton, SIGNAL( clicked() ), this, SLOT( slotNoProxyClick() ) );
    connect( ui.AssumeProxyRadioButton, SIGNAL( clicked() ), this, SLOT( slotYesProxyClick() ) );

    connect( ui.RandomPortButton, SIGNAL( clicked() ), this, SLOT( slotRandomPortButtonClick() ) );
    connect( ui.m_UseUpnpCheckBox, SIGNAL( clicked() ), this, SLOT( slotUseUpnpCheckBoxClick() ) );
    connect( ui.m_ExternIpHelpButton, SIGNAL( clicked() ), this, SLOT( slotExternIpHelpButtonClick() ) );
    connect( ui.m_SaveSettingsButton, SIGNAL( clicked() ), this, SLOT( onSaveButtonClick() ) );
    connect( ui.m_DeleteSettingsButton, SIGNAL( clicked() ), this, SLOT( onDeleteButtonClick() ) );
    connect( ui.m_NetworkSettingsNameComboBox, SIGNAL( currentIndexChanged( const QString& ) ), this, SLOT( onComboBoxSelectionChange( const QString& ) ) );
    connect( ui.m_NetworkSettingsNameComboBox, SIGNAL( editTextChanged( const QString& ) ), this, SLOT( onComboBoxTextChanged( const QString& ) ) );
}

//============================================================================
void AppletNetworkSettings::slotNetworkSettingsSelectionChanged( int idx )
{
	//applyNetworkSettings( ( ENetworkSettingsType )( idx + 1 ) );
}

//============================================================================
void AppletNetworkSettings::updateDlgFromSettings()
{
    ui.m_NetworkSettingsNameComboBox->clear();

    bool validDbSettings = false;
    VxDataHelper& dataHelper = m_MyApp.getDataHelper();
    std::vector<NetHostSetting> anchorSettingList;
    std::string lastSettingsName = dataHelper.getLastNetHostSettingName();
    int selectedIdx = 0;
    int currentSettingIdx = 0;
    if( ( 0 != lastSettingsName.length() )
        && dataHelper.getAllNetHostSettings( anchorSettingList )
        && ( 0 != anchorSettingList.size() ) )
    {
        std::vector<NetHostSetting>::iterator iter;
        for( iter = anchorSettingList.begin(); iter != anchorSettingList.end(); ++iter )
        {
            NetHostSetting& anchorSetting = *iter;
            ui.m_NetworkSettingsNameComboBox->addItem( anchorSetting.getNetHostSettingName().c_str() );
            if( anchorSetting.getNetHostSettingName() == lastSettingsName )
            {
                // found last settings used
                selectedIdx = currentSettingIdx;
                validDbSettings = true;
                populateDlgFromNetHostSetting( anchorSetting );
            }

            currentSettingIdx++;
        }
    }

    if( validDbSettings )
    {
        ui.m_NetworkSettingsNameComboBox->setCurrentIndex( selectedIdx );
    }
    else if( anchorSettingList.size() )
    {
        ui.m_NetworkSettingsNameComboBox->addItem( anchorSettingList[ 0 ].getNetHostSettingName().c_str() );
        populateDlgFromNetHostSetting( anchorSettingList[ 0 ] );
        dataHelper.updateLastNetHostSettingName( anchorSettingList[ 0 ].getNetHostSettingName().c_str() );
    }
    else
    {
        ui.m_NetworkSettingsNameComboBox->addItem( "default" );
        std::string strValue;

        m_Engine.getEngineSettings().getNetHostWebsiteUrl( strValue );
        ui.m_NetworkHostUrlEdit->setText( strValue.c_str() );

        m_Engine.getEngineSettings().getNetworkKey( strValue );
        ui.m_NetworkKeyEdit->setText( strValue.c_str() );
    }

    uint16_t u16Port = m_Engine.getEngineSettings().getTcpIpPort();
    ui.PortEdit->setText( QString( "%1" ).arg( u16Port ) );

    ui.AutoDetectProxyRadioButton->setChecked( false );
    ui.AssumeNoProxyRadioButton->setChecked( false );
    ui.AssumeProxyRadioButton->setChecked( false );
    EngineSettings::EFirewallTestType iDetectProxySetting = m_Engine.getEngineSettings().getFirewallTestSetting();
    switch( iDetectProxySetting )
    {
    case EngineSettings::eFirewallTestAssumeNoFirewall:
        ui.AssumeNoProxyRadioButton->setChecked( true );
        break;

    case EngineSettings::eFirewallTestAssumeFirewalled:
        ui.AssumeProxyRadioButton->setChecked( true );
        break;

    case EngineSettings::eFirewallTestUrlConnectionTest:
    default:
        ui.AutoDetectProxyRadioButton->setChecked( true );
        break;
    }

    ui.m_UseUpnpCheckBox->setChecked( m_Engine.getEngineSettings().getUseUpnpPortForward() );
    ui.m_LclIpListComboBox->clear();
    ui.m_LclIpListComboBox->addItem( DEFAULT_ADAPTER_IP_CHOICE );

    std::string strPreferredIp = m_Engine.getEngineSettings().getPreferredNetworkAdapterIp();
    std::vector<InetAddress> lclIpAddresses;
    VxGetLocalIps( lclIpAddresses );
    std::vector<InetAddress>::iterator iter;
    std::string ipAddr;
    int preferredAddrIndex = 0;
    int currIdx = 0;
    for( iter = lclIpAddresses.begin(); iter != lclIpAddresses.end(); ++iter )
    {
        InetAddress& inetAddr = ( *iter );
        if( inetAddr.isIPv4()
            && ( false == inetAddr.isLoopBack() ) )
        {
            currIdx++;
            ipAddr = inetAddr.toStdString();
            if( ipAddr == strPreferredIp )
            {
                preferredAddrIndex = currIdx;
            }

            ui.m_LclIpListComboBox->addItem( ipAddr.c_str() );
        }
    }

    ui.m_LclIpListComboBox->setCurrentIndex( preferredAddrIndex );
    std::string externIP;
    m_Engine.getEngineSettings().getExternalIp( externIP );
    ui.m_ExternIpEdit->setText( externIP.c_str() );
}

//============================================================================
void AppletNetworkSettings::updateSettingsFromDlg()
{
    NetHostSetting anchorSetting;
    std::string anchorSettingsName;
    anchorSettingsName = ui.m_NetworkSettingsNameComboBox->currentText().toUtf8().constData();
    if( 0 == anchorSettingsName.length() )
    {
        anchorSettingsName = "default";
    }

    anchorSetting.setNetHostSettingName( anchorSettingsName.c_str() );

    std::string strValue;
    strValue = ui.m_NetworkHostUrlEdit->text().toUtf8().constData();

    // for now NetHost and NetService ( connection port open test ) urls are the same
    m_Engine.getEngineSettings().setNetHostWebsiteUrl( strValue );
    anchorSetting.setNetHostWebsiteUrl( strValue.c_str() );

    m_Engine.getEngineSettings().setNetServiceWebsiteUrl( strValue );
    anchorSetting.setNetServiceWebsiteUrl( strValue.c_str() );

    strValue = ui.m_NetworkKeyEdit->text().toUtf8().constData();
    m_Engine.getEngineSettings().setNetworkKey( strValue );
    anchorSetting.setNetworkKey( strValue.c_str() );

    m_MyApp.getDataHelper().updateNetHostSetting( anchorSetting );
    m_MyApp.getDataHelper().updateLastNetHostSettingName( anchorSettingsName.c_str() );

    std::string strPreferredIp = "";
    if( 0 != ui.m_LclIpListComboBox->currentIndex() )
    {
        strPreferredIp = ui.m_LclIpListComboBox->currentText().toUtf8().constData();
    }

    m_Engine.getEngineSettings().setPreferredNetworkAdapterIp( strPreferredIp.c_str() );

    uint16_t u16TcpPort = ui.PortEdit->text().toUShort();
    if( 0 != u16TcpPort )
    {
        m_Engine.getEngineSettings().setTcpIpPort( u16TcpPort );
        m_Engine.getMyPktAnnounce().setMyOnlinePort( u16TcpPort );
        m_MyApp.getAppGlobals().getUserIdent()->m_DirectConnectId.setPort( u16TcpPort );
    }

    std::string externIp = ui.m_ExternIpEdit->text().toUtf8().constData();
    if( externIp.length() )
    {
        m_Engine.getEngineSettings().setExternalIp( externIp );
    }

    EngineSettings::EFirewallTestType eFirewallTestType = EngineSettings::eFirewallTestUrlConnectionTest;
    if( ui.AssumeNoProxyRadioButton->isChecked() )
    {
        eFirewallTestType = EngineSettings::eFirewallTestAssumeNoFirewall;
        if( externIp.length() )
        {
            m_Engine.getMyPktAnnounce().setOnlineIpAddress( externIp.c_str() );
        }
    }
    else if( ui.AssumeProxyRadioButton->isChecked() )
    {
        eFirewallTestType = EngineSettings::eFirewallTestAssumeFirewalled;
    }

    m_Engine.getEngineSettings().setFirewallTestSetting( eFirewallTestType );
    m_Engine.getEngineSettings().setUseUpnpPortForward( ui.m_UseUpnpCheckBox->isChecked() );
}

//============================================================================
void AppletNetworkSettings::slotExitButtonClick()
{
    //updateSettingsFromDlg();
    //m_Engine.fromGuiNetworkSettingsChanged();
    close();
}

//============================================================================
void AppletNetworkSettings::slotGoToNetHostSettingsButtonClick()
{
    ActivityNetworkState * activityInfo = new ActivityNetworkState( m_MyApp, this );
    activityInfo->show();
}

//============================================================================
void AppletNetworkSettings::slotAutoDetectProxyClick( void )
{
    setFirewallTest( EngineSettings::eFirewallTestUrlConnectionTest );
}

//============================================================================
void AppletNetworkSettings::slotNoProxyClick( void )
{
    setFirewallTest( EngineSettings::eFirewallTestAssumeNoFirewall );
}

//============================================================================
void AppletNetworkSettings::slotYesProxyClick( void )
{
    setFirewallTest( EngineSettings::eFirewallTestAssumeFirewalled );
}

//============================================================================
void AppletNetworkSettings::setFirewallTest( EngineSettings::EFirewallTestType eFirewallType )
{
    ui.AutoDetectProxyRadioButton->setChecked( false );
    ui.AssumeNoProxyRadioButton->setChecked( false );
    ui.AssumeProxyRadioButton->setChecked( false );

    switch( eFirewallType )
    {
    case EngineSettings::eFirewallTestUrlConnectionTest:
        ui.AutoDetectProxyRadioButton->setChecked( true );
        break;

    case EngineSettings::eFirewallTestAssumeFirewalled:
        ui.AssumeProxyRadioButton->setChecked( true );
        break;

    case EngineSettings::eFirewallTestAssumeNoFirewall:
        ui.AssumeNoProxyRadioButton->setChecked( true );
        break;
    }
}

//============================================================================
void AppletNetworkSettings::slotRandomPortButtonClick( void )
{
    uint16_t u16TcpPort = VxGetRandomTcpPort();
    QString strPort;
    strPort.sprintf( "%d", u16TcpPort );
    ui.PortEdit->setText( strPort );
    updateSettingsFromDlg();
}

//============================================================================
void AppletNetworkSettings::slotRunIsPortOpenButtonClick( void )
{
    uint16_t u16Port = ui.PortEdit->text().toUShort();
    if( 0 != u16Port )
    {
        updateSettingsFromDlg();
        ActivityIsPortOpenTest * dlg = new ActivityIsPortOpenTest(
            m_MyApp,
            u16Port,
            this );
        dlg->exec();
    }
    else
    {
        QMessageBox::information( this, tr( "Error" ), tr( "TCP Port cannot be zero." ) );
    }
}

//============================================================================
void AppletNetworkSettings::slotUseUpnpCheckBoxClick( void )
{
}

//============================================================================
void AppletNetworkSettings::slotExternIpHelpButtonClick( void )
{
    QMessageBox::information( this, tr( "Information" ), tr( "You can determine your external IP Address by browsing to http://www.google.com and searching for 'what is my ip'." ) );
}

//============================================================================
void AppletNetworkSettings::onComboBoxTextChanged( const QString & text )
{
    //updateSettingsFromDlg();
}

//============================================================================
void AppletNetworkSettings::onComboBoxSelectionChange( const QString& anchorSettingName )
{
    VxDataHelper& dataHelper = m_MyApp.getDataHelper();
    NetHostSetting anchorSetting;
    if( dataHelper.getNetHostSettingByName( anchorSettingName.toUtf8(), anchorSetting ) )
    {
        populateDlgFromNetHostSetting( anchorSetting );
        updateSettingsFromDlg();
    }
}

//============================================================================
void AppletNetworkSettings::populateDlgFromNetHostSetting( NetHostSetting& anchorSetting )
{
    ui.m_NetworkHostUrlEdit->setText( anchorSetting.getNetHostWebsiteUrl().c_str() );
    ui.m_NetworkKeyEdit->setText( anchorSetting.getNetworkKey().c_str() );
}

//============================================================================
void AppletNetworkSettings::closeEvent( QCloseEvent * event )
{
    updateSettingsFromDlg();
    QWidget::closeEvent( event );
}

//============================================================================
void AppletNetworkSettings::onSaveButtonClick( void )
{
    QString keyVal = getNetworkKey();
    if( verifyNetworkKey( keyVal ) )
    {
        std::string anchorSettingsName;
        anchorSettingsName = ui.m_NetworkSettingsNameComboBox->currentText().toUtf8().constData();
        if( anchorSettingsName.empty() )
        {
            QMessageBox::information( this, QObject::tr( "Network Setting" ), QObject::tr( "Network setting name cannot be blank." ) );
            return;
        }

        std::string netHostUrl;
        netHostUrl = ui.m_NetworkHostUrlEdit->text().toUtf8().constData();
        if( netHostUrl.empty() )
        {
            QMessageBox::information( this, QObject::tr( "Network Setting" ), QObject::tr( "Network host URL cannot be blank." ) );
            return;
        }

        std::string keyString = keyVal.toUtf8().constData();
        if( keyString.empty() )
        {
            QMessageBox::information( this, QObject::tr( "Network Setting" ), QObject::tr( "Network key cannot be blank." ) );
            return;
        }

        NetHostSetting anchorSetting;
        if( m_MyApp.getDataHelper().getNetHostSettingByName( anchorSettingsName.c_str(), anchorSetting ) )
        {
            // setting exists.. check if user wants to change setting name
            if( QMessageBox::Yes != QMessageBox::question( this, QObject::tr( "Network Setting" ), 
                                                           QObject::tr( "Are you sure you want to overwrite existing network setting?.\n The network setting name can be changed in Select Network Setting." ),
                                                           QMessageBox::Yes | QMessageBox::No ) )
            {
                return;
            }
        }

        m_MyApp.getEngine().getEngineSettings().setNetworkKey( keyString );
        updateSettingsFromDlg();
        QMessageBox::information( this, QObject::tr( "Network Setting" ), QObject::tr( "Network setting was saved." ) );
        //QMessageBox::warning( this, QObject::tr( "Network Key" ), QObject::tr( "You may need to restart application to avoid connection problems." ) );
    }
}

//============================================================================
void AppletNetworkSettings::onDeleteButtonClick( void )
{
    updateSettingsFromDlg();
    if( 1 >= ui.m_NetworkSettingsNameComboBox->count() )
    {
        QMessageBox::warning( this, tr( "Network Settings" ), tr( "You cannot delete the last network setting." ) );
        return;
    }

    std::string anchorSettingsName;
    anchorSettingsName = ui.m_NetworkSettingsNameComboBox->currentText().toUtf8().constData();
    if( 0 != anchorSettingsName.length() )
    {
        m_MyApp.getDataHelper().removeNetHostSettingByName( anchorSettingsName.c_str() );
        updateDlgFromSettings();
    }
}

//============================================================================
void AppletNetworkSettings::slotShowNetworkHostInformation()
{
    ActivityInformation * activityInfo = new ActivityInformation( m_MyApp, this, eInfoTypeNetworkHost );
    activityInfo->show();
}

//============================================================================
void AppletNetworkSettings::slotShowNetworkKeyInformation()
{
    ActivityInformation * activityInfo = new ActivityInformation( m_MyApp, this, eInfoTypeNetworkKey );
    activityInfo->show();
}

//============================================================================
bool AppletNetworkSettings::verifyNetworkKey( QString& keyVal )
{
    bool isValid = true;
    if( keyVal.size() < 6 )
    {
        isValid = false;
        QMessageBox::warning( this, QObject::tr( "Network Key" ), QObject::tr( "Network Key must be at least 6 characters ( 8 or more characters recommended )." ) );
    }

    return isValid;
}