#pragma once

class AppCommon;

class EventsQtToGoTv
{
public:
    EventsQtToGoTv(  AppCommon& myApp );
    virtual ~EventsQtToGoTv() = default;

    bool                        keyPressEvent( int key );
    bool                        keyReleaseEvent( int key );

    bool                        mousePressEvent( int mouseXPos, int mouseYPos, int mouseButton );
    bool                        mouseReleaseEvent( int mouseXPos, int mouseYPos, int mouseButton );
    bool                        mouseMoveEvent( int mouseXPos, int mouseYPos );

    void                        resizeEvent( int winWidth, int winHeight );
    void                        closeEvent( );
    void                        visibleEvent( bool isVisible );

    AppCommon&				    m_MyApp;
};
