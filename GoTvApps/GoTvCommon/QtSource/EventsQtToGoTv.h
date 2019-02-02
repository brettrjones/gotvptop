#pragma once

class AppCommon;

class EventsQtToGoTv
{
public:
    EventsQtToGoTv(  AppCommon& myApp );
    virtual ~EventsQtToGoTv() = default;

    bool                        fromGuiKeyPressEvent( int key );
    bool                        fromGuiKeyReleaseEvent( int key );

    bool                        fromGuiMousePressEvent( int mouseXPos, int mouseYPos, int mouseButton );
    bool                        fromGuiMouseReleaseEvent( int mouseXPos, int mouseYPos, int mouseButton );
    bool                        fromGuiMouseMoveEvent( int mouseXPos, int mouseYPos );

    void                        fromGuiResizeEvent( int winWidth, int winHeight );
    void                        fromGuiCloseEvent( );
    void                        fromGuiVisibleEvent( bool isVisible );

    AppCommon&				    m_MyApp;
};
