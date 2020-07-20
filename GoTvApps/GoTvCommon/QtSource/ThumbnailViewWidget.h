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

#include <CoreLib/VxGUID.h>

#include <QLabel>

class AppCommon;
class QPixmap;
class AssetInfo;

class ThumbnailViewWidget : public QLabel
{
    Q_OBJECT
public:
    ThumbnailViewWidget( QWidget * parent );
    ~ThumbnailViewWidget() override = default;

    void                        setIsUserPickedImage( bool userPicked )     { m_bUserPickedImage = userPicked;  }
    bool                        getIsUserPickedImage( void )                { return m_bUserPickedImage; }

    void                        setThumbnailImage( QPixmap pixmap )         { cropAndUpdateImage( pixmap ); }
    const QPixmap *             getThumbnailImage( void )                   { return pixmap(); }

    void                        setThumbnailId( VxGUID& id )                { m_ThumbnailId = id; }
    VxGUID&                     getThumbnailId( void )                      { return m_ThumbnailId; }

    bool                        loadFromAsset( AssetInfo * asset );
    bool                        loadFromFile( QString fileName );

    bool                        saveToPngFile( QString pngFileName );
    void                        browseForImage( void );

signals:
    void                        clicked( void );
    void						signalImageClicked( ThumbnailViewWidget * widget );

protected slots:
    void                        slotJpgSnapshot( uint8_t* pu8JpgData, uint32_t u32DataLen, int iWidth, int iHeight );

protected:
    virtual void				mousePressEvent( QMouseEvent * ev ) override;
    void                        cropAndUpdateImage( QPixmap& pixmap );

    AppCommon&					m_MyApp;
    bool                        m_bUserPickedImage = false;
    VxGUID                      m_ThumbnailId;
};
