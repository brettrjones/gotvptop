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

#include "ActivityBase.h"

#include <QString>
#include <QDialog>
#include <QListWidgetItem>
#include <QTimer>
#include "ui_ActivityScanProfiles.h"

#include <GoTvInterface/IDefs.h>
#include <CoreLib/VxDefs.h>

class ScanProfilePair
{
public:
	ScanProfilePair()
		: m_Ident( 0 ){}
	ScanProfilePair( VxNetIdent * netIdent, QImage& image )
		: m_Ident( netIdent )
		, m_Image( image )
	{
	}
	~ScanProfilePair(){};
	ScanProfilePair( const ScanProfilePair& rhs ){ *this = rhs; }
	ScanProfilePair& operator=( const ScanProfilePair& rhs )
	{
		if( this != &rhs )
		{
			m_Ident					= rhs.m_Ident;
			m_Image					= rhs.m_Image;
		}
		return *this;
	}

	//=== vars ===//
	VxNetIdent *				m_Ident;
	QImage						m_Image;

};

class VxNetIdent;
	
class ActivityScanProfiles : public ActivityBase
{
	Q_OBJECT
public:
	ActivityScanProfiles(	AppCommon& app, 
							QWidget *		parent = NULL );
	virtual ~ActivityScanProfiles() override = default;

    // overrides required for dialogs with there own title bar and bottom bar widgets
    virtual TitleBarWidget *	getTitleBarWidget( void ) override { return ui.m_TitleBarWidget; }
    virtual BottomBarWidget *	getBottomBarWidget( void ) override { return ui.m_BottomBarWidget; }

public:
    virtual void				toGuiClientScanSearchComplete( void * userData, EScanType eScanType ) override;
    virtual void				toGuiSearchResultProfilePic( void * userData, VxNetIdent * netIdent, uint8_t * pu8JpgData, uint32_t u32JpgDataLen ) override;

signals:
	 void						signalSearchResultProfilePic( VxNetIdent * netIdent, QImage oPicBitmap );
	 void						signalSearchComplete();

protected slots:
	void						slotSearchComplete();

	void						slotSearchResultProfilePic( VxNetIdent * netIdent, QImage oPicBitmap ); 

    void						slotHomeButtonClicked( void ) override;
	void						slotPauseScanClicked( void );
	void						slotStartScanClicked( void );
	void						slotNextScanClicked( void );

	void						onCountdownTimer( void );
	void						slotFriendClicked( void );

protected:
    void						showEvent( QShowEvent * ev ) override;
    void						hideEvent( QHideEvent * ev ) override;

	void						startStopScan( bool startScan );
	void						startCountdown();
	void						updateCountdownGui();
	void						showNextImage( void ); 
	void						showMatchedPair( VxNetIdent * netIdent, QImage& oPicBitmap ); 

	void						setTitle( QString strTitle );
	void						setScanStatusText( QString strMsg );
	void						setupIdentWidget( VxNetIdent * netIdent );


	//=== vars ===//
	Ui::ScanProfilesDialog		ui;

	VxNetIdent *				m_Ident;
	int							m_iCountdownCnt;
	bool						m_bPaused;

	QTimer *					m_CountdownTimer;
	EScanType					m_eScanType;
	bool						m_bIconConnected;
	bool						m_bSearchComplete;
	QVector<ScanProfilePair>	m_ScanList;
    bool						m_ShowNextImage;
    bool						m_IsScanning;
};
