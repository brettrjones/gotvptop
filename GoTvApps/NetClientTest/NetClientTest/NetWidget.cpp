//============================================================================
// Copyright (C) 2018 Brett R. Jones
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
// http://www.nolimitconnect.com
//============================================================================

#include "NetWidget.h"
#include "AppLogic.h"

#include <QScrollBar>
#include <QClipboard>
#include <QMessageBox>

//============================================================================
NetWidget::NetWidget( QWidget * parent )
    : QWidget( parent )
    , m_AppLogic( GetAppLogic() )
    , m_PingResponseServer( GetAppLogic() )
    , m_PingSend( GetAppLogic() )
    , m_ConnectTimer( new QTimer(this) )
    , m_ListenTimer( new QTimer( this ) )
{
    ui.setupUi( this );
    initNetWidget();
}

//============================================================================
void NetWidget::initNetWidget()
{
    ui.m_LogWidget->initLogCallback();
    LogMsg( LOG_DEBUG, "Log Initialized" );
    m_ConnectTimer->setInterval( 6000 );
    m_ListenTimer->setInterval( 6000 );

    connect( getConnectButton(), SIGNAL( clicked() ), this, SLOT( slotConnectButtonClicked() ) );
    connect( getDisconnectButton(), SIGNAL( clicked() ), this, SLOT( slotDisconnectButtonClicked() ) );
    connect( getListenButton(), SIGNAL( clicked() ), this, SLOT( slotListenButtonClicked() ) );
    connect( getStopListenButton(), SIGNAL( clicked() ), this, SLOT( slotStopListenButtonClicked() ) );

    connect( m_ConnectTimer, SIGNAL( timeout() ), this, SLOT( slotConnectTimeout() ) );
    connect( m_ListenTimer, SIGNAL( timeout() ), this, SLOT( slotListenTimeout() ) );

    setConnectionStatus( false );
    setListenStatus( false );
    loadFromSettings();
}
//============================================================================
void NetWidget::loadFromSettings()
{
}

//============================================================================
void NetWidget::saveToSettings()
{
}


//============================================================================
void NetWidget::slotConnectTimeout( void )
{

}

//============================================================================
void NetWidget::slotListenTimeout( void )
{

}

//============================================================================
void NetWidget::setConnectionStatus( bool isConnected )
{
    getConnectButton()->setEnabled( !isConnected );
    getDisconnectButton()->setEnabled( isConnected );
}

//============================================================================
void NetWidget::setListenStatus( bool isListening )
{
    getListenButton()->setEnabled( !isListening );
    getStopListenButton()->setEnabled( isListening );
}

//============================================================================
bool NetWidget::isUrlValid( std::string& url )
{
    bool isValid = false;

    return isValid;
}

//============================================================================
bool NetWidget::isIpValid( std::string& ipAddr )
{
    bool isValid = false;

    return isValid;
}

//============================================================================
bool NetWidget::isPortValid( uint16_t ipPort )
{
    bool isValid = false;

    return isValid;
}

//============================================================================
void NetWidget::onLogEvent( uint32_t u32LogFlags, const char * logMsg )
{
    getLogWidget()->onLogEvent( u32LogFlags,logMsg );
}

//============================================================================
void NetWidget::slotConnectButtonClicked( void )
{
    std::string connUrl = ui.m_ConnectTestUrlEdit->text().toUtf8().constData();
    if( connUrl.empty() )
    {
        QMessageBox::warning( this, QObject::tr( "Connection URL" ), QObject::tr( "Connection URL is empty." ) );
    }
    else if( !isUrlValid( connUrl ) )
    {
        QMessageBox::warning( this, QObject::tr( "Invalid Connection URL" ), QObject::tr( "URL is invalid" ) );
    }
    else
    {
        setConnectionStatus( true );
        m_ConnectTimer->start();
    }
}

//============================================================================
void NetWidget::slotDisconnectButtonClicked( void )
{
    m_ConnectTimer->stop();
    setConnectionStatus( false );
    LogMsg( LOG_DEBUG, "Connect attempts stopped" );
}

//============================================================================
void NetWidget::slotListenButtonClicked( void )
{
    //m_PingResponseServer.startListening( (uint16_t)port, )
    setListenStatus( true );
    m_ListenTimer->start();
}

//============================================================================
void NetWidget::slotStopListenButtonClicked( void )
{
    m_ListenTimer->stop();
    setListenStatus( false );

}
