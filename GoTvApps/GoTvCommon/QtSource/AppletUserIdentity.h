#pragma once
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
// http://www.gotvptop.com
//============================================================================

#include "AppletBase.h"
#include "UserProfile.h"

#include "ui_AppletIdentity.h"

class AppletUserIdentity : public AppletBase
{
	Q_OBJECT
public:
	AppletUserIdentity( AppCommon& app, QWidget * parent );
	virtual ~AppletUserIdentity() = default;

public slots:
    //! apply name change
    void						onApplyNameClick( void );
    //! apply name change
    void						onApplyMoodMsgClick( void );
    void						onApplyAgeClick( void );
    void						onApplyContentClick( void );

    //! browse for picture of me
    void						onBrowseButClick( void );
    //! Implement the OnClickListener callback    
    void						onSnapshotButClick( void );
    //! Implement the OnClickListener callback    
    void						onApplyAboutMeButClick( void );
    //! slot called when user takes snapshot
    void						onSnapshot( uint8_t* pu8JpgData, uint32_t u32DataLen, int iWidth, int iHeight );

protected:
    void                        loadIdentityFromDb();
 
    //! load user profile data from database
    void						loadContentFromDb( void );

    void						updateSnapShot( QPixmap& pixmap );
    //! validate user input
    QString						validateString( QString charSeq );
    //! save user profile data to database
    void						saveContentToDb( void );

    bool                        validateUserName( void );
    bool                        validateMoodMessage( void );

    //=== constants ===//
    static const int SELECT_IMAGE = 0; // selector for image gallery call
    static const int CAMERA_SNAPSHOT = 1; // selector for image gallery call

    //=== vars ===//
    Ui::AppletIdentityClass		ui;
    UserProfile 				m_UserProfile;
    VxNetIdent *				m_MyIdent = nullptr;
    QString                     m_strOrigOnlineName;
    QString                     m_strOrigMoodMessage;

    std::string					m_strDefaultPicPath;
    std::string					m_strUserSepecificDataDir;
    bool						m_bUserPickedImage = false;
    bool						m_bUsingDefaultImage = true;
};


