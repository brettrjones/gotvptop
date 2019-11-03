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
// http://www.nolimitconnect.com
//============================================================================
#pragma once

#include "AppCommon.h"

#include "ui_LogWidget.h"

#include <QPlainTextEdit>
#include <QFile>
#include <QMutex>

class LogWidget : public QWidget
{
    Q_OBJECT
public:
    LogWidget( QWidget * parent );
    ~LogWidget() override;


    void                        toGuiLog( uint32_t u32LogFlags, char * logMsg );

    void                        clear()                 { getLogEdit()->clear(); }

signals:
    void                        signalLogMsg( const QString& logMsg );

protected slots:
    void                        slotLogMsg( const QString& text );
    void                        slotVerboseCheckBoxClicked( void );
    void                        slotCopyToClipboardClicked( void );

protected:
    QPlainTextEdit *            getLogEdit( void )  { return ui.m_LogPlainTextEdit;  }

    Ui::LogWidgetClass	        ui;
    AppCommon&                  m_MyApp;
    QFile                       m_LogFile;
    QMutex                      m_LogMutex;
    LOG_FUNCTION                m_OldLogFunction = nullptr;
    void *                      m_OldLogUserData = nullptr;
    bool                        m_VerboseLog = false;
};
