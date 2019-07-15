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
// http://www.gotvptop.com
//============================================================================

#include "ActivityBase.h"

#include <QDialog>
#include "ui_ActivityEditProfile.h"
#include "UserProfile.h"

#include <CoreLib/VxDefs.h>

class P2PEngine;
class AppCommon;

//NOTE: must not inherit from ActivityBase 
class ActivityEditProfile : public ActivityBase
{
	Q_OBJECT
public:

	ActivityEditProfile( AppCommon& app, const char * pUserSpecificDataDir, QWidget * parent = NULL );
	virtual ~ActivityEditProfile();

private:
	//! validate user input
	QString						validateString(QString charSeq );
	//! load user profile data from database
	void						loadContentFromDb( void );
	//! save user profile data to database
	void						saveContentToDb( void );

public slots:
	//! browse for picture of me
	void						onBrowseButClick( void );
	//! Implement the OnClickListener callback    
	void						onSnapshotButClick( void );
	//! Implement the OnClickListener callback    
	void						onDoneButClick( void ); 
	//! slot called when user takes snapshot
	void						onSnapshot(uint8_t* pu8JpgData, uint32_t u32DataLen, int iWidth, int iHeight );

protected:
	void						updateSnapShot( QPixmap& pixmap );

	//=== constants ===//
	static const int SELECT_IMAGE = 0; // selector for image gallery call
	static const int CAMERA_SNAPSHOT = 1; // selector for image gallery call

	//=== vars ===//
	Ui::EditProfileDialog		ui;
	UserProfile 				m_UserProfile;

	std::string					m_strDefaultPicPath;
	bool						m_bUserPickedImage;
	bool						m_bUsingDefaultImage;
	std::string					m_strUserSepecificDataDir;
};

