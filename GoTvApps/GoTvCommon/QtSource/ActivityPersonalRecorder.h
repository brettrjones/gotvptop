#pragma once
//============================================================================
// Copyright (C) 2015 Brett R. Jones
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

#include "ActivityToFriendBase.h"

#include "ui_ActivityPersonalRecorder.h"

class P2PEngine;
class GuiOfferSession;

class ActivityPersonalRecorder : public ActivityToFriendBase
{
	Q_OBJECT

public:

	ActivityPersonalRecorder(	AppCommon&			app,
								VxNetIdent *			netIdent, 
								QWidget *				parent = NULL );

	virtual ~ActivityPersonalRecorder();

	virtual void				toGuiClientPlayVideoFrame(	void *			userData, 
															VxGUID&		onlineId, 
															uint8_t *			pu8Jpg, 
															uint32_t				u32JpgDataLen,
															int				motion0To100000 );

	virtual void				onActivityFinish( void );

protected:
	void						setupMultiSessionActivity( void );

	Ui::PersonalRecorderDialog	ui;
};

