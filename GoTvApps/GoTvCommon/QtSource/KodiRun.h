#pragma once

#include <QWidget>

class AppCommon;

class KodiRun : public QObject
{
    Q_OBJECT
public:
    KodiRun( AppCommon& app, QWidget * parent );
    virtual ~KodiRun() override = default;

private slots:
    void						slotStartKodiRunFromThread( void );
};
