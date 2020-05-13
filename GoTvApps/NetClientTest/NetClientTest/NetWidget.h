//============================================================================
// Copyright (C) 2020 Brett R. Jones
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
#pragma once

#include "AppLogic.h"
#include "PingResponseServer.h"
#include "PingSend.h"

#include "ui_NetWidget.h"

#include <QPlainTextEdit>
#include <QFile>
#include <QMutex>
#include <QTimer>
    

#include <CoreLib/VxDebug.h>

class NetWidget : public QWidget, public ILogCallbackInterface
{
    Q_OBJECT
public:
    NetWidget( QWidget * parent );
    ~NetWidget() override = default;

    void                        initNetWidget();

    void                        onLogEvent( uint32_t u32LogFlags, const char * logMsg ) override;

    void                        clear()                 { getLogWidget()->clear(); }

//signals:
//    void                        signalLogMsg( const QString& logMsg );

protected slots:
    void                        slotConnectButtonClicked( void );
    void                        slotDisconnectButtonClicked( void );
    void                        slotListenButtonClicked( void );
    void                        slotStopListenButtonClicked( void );

    void                        slotConnectTimeout( void );
    void                        slotListenTimeout( void );

protected:
    LogWidget *                 getLogWidget( void )                { return ui.m_LogWidget;  }
    QPushButton *               getConnectButton( void )            { return ui.m_ConnectButton; }
    QPushButton *               getDisconnectButton( void )         { return ui.m_DisconnectButton; }
    QPushButton *               getListenButton( void )             { return ui.m_ListenButton; }
    QPushButton *               getStopListenButton( void )         { return ui.m_StopListenButton; }

    void                        loadFromSettings( void );
    void                        saveToSettings( void );

    void                        setConnectionStatus( bool isConnected );
    void                        setListenStatus( bool isListening );

    bool                        isUrlValid( std::string& url );
    bool                        isIpValid( std::string& ipAddr );
    bool                        isPortValid( uint16_t ipPort );


    Ui::NetWidgetClass	        ui;
    AppLogic&                   m_AppLogic;
    PingResponseServer			m_PingResponseServer;
    PingSend		            m_PingSend;

    std::string                 m_ConnectUrl;
    QTimer *                    m_ConnectTimer{ nullptr };
    uint16_t                    m_ListenPort{ 0 };
    std::string                 m_AdapterIp;
    QTimer *                    m_ListenTimer{ nullptr };

    QString                     m_ConnectIp;
    uint16_t                    m_ConnectPort;
    QString                     m_ListenIp;
    uint16_t                    m_ListenPort;
};
