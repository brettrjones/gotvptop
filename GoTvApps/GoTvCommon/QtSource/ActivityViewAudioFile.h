#pragma once
//============================================================================
// Copyright (C) 2013 Brett R. Jones
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

#include <PktLib/VxCommon.h>

#include <QDialog>
#include <QPixmap>
#include "ui_ActivityViewAudioFile.h"
#include "ActivityBase.h"
#include "VidWidget.h"

class AppCommon;
class P2PEngine;
class VxNetIdent;

class ActivityViewAudioFile : public ActivityBase
{
	Q_OBJECT
public:

	ActivityViewAudioFile(	AppCommon&			app,
							QWidget *				parent = NULL );

	virtual ~ActivityViewAudioFile() override = default;

    // overrides required for dialogs with there own title bar and bottom bar widgets
    virtual TitleBarWidget *	getTitleBarWidget( void ) override { return ui.m_TitleBarWidget; }
    virtual BottomBarWidget *	getBottomBarWidget( void ) override { return ui.m_BottomBarWidget; }

	void						playAudioFrame( VxGUID& feedId, unsigned char * pu8Jpg, unsigned long u32JpgLen, int motion0To100000 );

	void						webCamSourceOffline();

signals:
	void						signalWebCamClientDlgClosed( VxNetIdent * netIdent );
	void						signalPlayAudioFrame( QPixmap oPicBitmap, int iRotate );
	void						signalPlayAudio( unsigned short * pu16PcmData, unsigned short u16PcmDataLen );

protected slots:
	void						onStopButClick( void ); 
	void						onLibraryButtonClick( void ); 
	void						onShareButtonClick( void ); 

protected:
	void						resizeBitmapToFitScreen( QLabel * AudioScreen, QImage& oPicBitmap );

	//=== vars ===//
	Ui::ViewAudioFileDialogClass	ui;
	bool						m_bIsMyself;
	VxNetIdent *				m_HisIdent;
};

