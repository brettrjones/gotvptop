//============================================================================
// Copyright (C) 2019 Brett R. Jones
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

#include <QLabel>

class AppCommon;
class QPixmap;

class ThumbnailViewWidget : public QLabel
{
    Q_OBJECT
public:
    ThumbnailViewWidget( QWidget * parent );
    ~ThumbnailViewWidget() override = default;

    void                        setUserPickedImage( bool userPicked )       { m_bUserPickedImage = userPicked;  }
    bool                        getUserPickedImage( void )                  { return m_bUserPickedImage; }

    void                        browseForImage( void );
    bool                        saveToPngFile( QString pngFileName );

protected slots:
    void                        slotJpgSnapshot( uint8_t* pu8JpgData, uint32_t u32DataLen, int iWidth, int iHeight );

protected:
    void                        cropAndUpdateImage( QPixmap& pixmap );

    AppCommon&					m_MyApp;
    bool                        m_bUserPickedImage = false;

};
