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
#include "ToGuiFileXferInterface.h"
#include "ui_ActivityUploads.h"

#include <PktLib/VxCommon.h>

class GuiFileXferSession;
class FileXferWidget;

class ActivityUploads : public ActivityBase, public ToGuiFileXferInterface
{
	Q_OBJECT
public:
	ActivityUploads(	AppCommon&	app, 
						QWidget *		parent = NULL );
	virtual ~ActivityUploads();

public:
	FileXferWidget *			addDownload( GuiFileXferSession * poFileInfo );

	bool						isUploadInProgress( VxGuidQt fileInstance );

	GuiFileXferSession *		findSession( VxGuidQt fileInstance );
	FileXferWidget *			findListEntryWidget( VxGuidQt fileInstance );
	FileXferWidget *			addUpload( GuiFileXferSession * poSession );

signals:
	void						signalToGuiStartUpload( GuiFileXferSession * xferSession );
	void						signalToGuiFileXferState( VxGuidQt lclSession, EXferState eXferState, int param1, int param2 );
	void						signalToGuiFileUploadComplete( VxGuidQt lclSession, int xferError );

private slots:
	void						slotToGuiStartUpload(	GuiFileXferSession * poSession );
	void						slotToGuiFileXferState( VxGuidQt lclSessionId, EXferState eXferState, int param1, int param2 );
	void						slotToGuiFileUploadComplete( VxGuidQt lclSessionId, int xferError );

	void						slotHomeButtonClicked( void );
	void						slotFileXferItemClicked( QListWidgetItem * item );

	void						slotFileIconButtonClicked( QListWidgetItem * item );
	void						slotCancelButtonClicked( QListWidgetItem * item );
	void						slotPlayButtonClicked( QListWidgetItem * item );
	void						slotLibraryButtonClicked( QListWidgetItem * item );
	void						slotFileShareButtonClicked( QListWidgetItem * item );
	void						slotShredButtonClicked( QListWidgetItem * item );

protected:
	virtual void				showEvent( QShowEvent * ev );
	virtual void				hideEvent( QHideEvent * ev );

	virtual void				toGuiStartUpload( void * userData, GuiFileXferSession * xferSession );
	virtual void				toGuiFileXferState( void * userData, VxGUID& lclSession, EXferState eXferState, int param1, int param2 );
	virtual void				toGuiFileUploadComplete( void * userData, VxGUID& lclSession, EXferError xferError );

	FileXferWidget *			sessionToWidget( GuiFileXferSession * poSession );
	void						updateListEntryWidget( FileXferWidget * item, GuiFileXferSession * poSession );
	GuiFileXferSession *		widgetToSession( FileXferWidget * item );
	bool						confirmDeleteFile( bool shredFile );

	//=== vars ===//
	Ui::UploadsDialog			ui;
};

