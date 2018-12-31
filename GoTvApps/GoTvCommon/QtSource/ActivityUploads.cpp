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
// brett.jones@engineer.com
// http://www.gotvptop.net
//============================================================================

#include "AppCommon.h"	
#include "AppSettings.h"

#include "ActivityUploads.h"
#include "ActivityYesNoMsgBox.h"

#include "FileXferWidget.h"
#include "GuiFileXferSession.h"
#include "MyIcons.h"
#include "GuiHelpers.h"	

#include <PktLib/VxSearchDefs.h>
#include <CoreLib/VxFileInfo.h>

//============================================================================
ActivityUploads::ActivityUploads(	AppCommon&	app, 
									QWidget *		parent )
: ActivityBase( OBJNAME_ACTIVITY_UPLOADS, app, parent, eAppletMessenger, Qt::SubWindow ) //Qt::Popup ) //
{
	ui.setupUi(this);
	ui.m_TitleBarWidget->setTitleBarText( QObject::tr( "Uploads" ) );
	connect( &m_MyApp,				SIGNAL(signalStatusMsg(QString)),		ui.m_TitleBarWidget,	SLOT(slotTitleStatusBarMsg(QString)) );
	connect( ui.m_TitleBarWidget,			SIGNAL(signalBackButtonClicked()),			this,	SLOT(slotHomeButtonClicked()) );


	slotRepositionToParent();

	if( false == connect(ui.m_FileItemList,	SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(slotFileXferItemClicked(QListWidgetItem *))) )
	{
		LogMsg( LOG_INFO, "ActivityUploads could not connect to slotItemClicked\n");
	}
	if( false == connect(ui.m_FileItemList, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(slotFileXferItemClicked(QListWidgetItem *))) )
	{
		LogMsg( LOG_INFO, "ActivityUploads could not connect to slotItemClicked\n");
	}

	connect( this, SIGNAL(signalToGuiStartUpload(GuiFileXferSession *)),			this, SLOT(slotToGuiStartUpload(GuiFileXferSession *)) );
	connect( this, SIGNAL(signalToGuiFileXferState(VxGuidQt,EXferState,int,int)),	this, SLOT(slotToGuiFileXferState(VxGuidQt,EXferState,int,int)) );
	connect( this, SIGNAL(signalToGuiFileUploadComplete(VxGuidQt,int)),				this, SLOT(slotToGuiFileUploadComplete(VxGuidQt,int)) );
	m_MyApp.wantToGuiFileXferCallbacks( this, this, true );
	checkDiskSpace();
}

//============================================================================
ActivityUploads::~ActivityUploads()
{
	m_MyApp.wantToGuiActivityCallbacks( this, this, false );
}

//============================================================================
void ActivityUploads::showEvent( QShowEvent * ev )
{
	ActivityBase::showEvent( ev );
}

//============================================================================
void ActivityUploads::hideEvent( QHideEvent * ev )
{
	ActivityBase::hideEvent( ev );
}

//============================================================================
void ActivityUploads::slotHomeButtonClicked( void )
{
	hide();
}

//============================================================================
FileXferWidget * ActivityUploads::sessionToWidget( GuiFileXferSession * poSession )
{
	FileXferWidget * item = new FileXferWidget(ui.m_FileItemList);
    item->setSizeHint( QSize( ( int )( m_MyApp.getAppDisplay().getDisplayScale() * 200 ),
        ( int )( 62 * m_MyApp.getAppDisplay().getDisplayScale() ) ) );

    item->QListWidgetItem::setData( Qt::UserRole + 1, QVariant((quint64)poSession) );

	if( false == connect( item, SIGNAL(signalFileXferItemClicked(QListWidgetItem*)), this, SLOT(slotFileXferItemClicked(QListWidgetItem*))) )
	{
		LogMsg( LOG_ERROR, "AppCommon::fileToWidget: connect failed\n");
	}

	if( false == connect( item, SIGNAL(signalCancelButtonClicked(QListWidgetItem*)), this, SLOT(slotCancelButtonClicked(QListWidgetItem*))) )
	{
		LogMsg( LOG_ERROR, "AppCommon::fileToWidget: connect failed\n");
	}

	updateListEntryWidget( item, poSession );
	return item;
}

//============================================================================
void ActivityUploads::updateListEntryWidget( FileXferWidget * item, GuiFileXferSession * poSession )
{
	poSession->setWidget( item );
	item->updateWidgetFromInfo();
}

//============================================================================
GuiFileXferSession * ActivityUploads::widgetToSession( FileXferWidget * item )
{
	return (GuiFileXferSession *)item->QListWidgetItem::data( Qt::UserRole + 1 ).toULongLong();
}

//============================================================================
GuiFileXferSession * ActivityUploads::findSession( VxGuidQt lclSessionId )
{
	int iCnt = ui.m_FileItemList->count();
	for( int iRow = 0; iRow < iCnt; iRow++ )
	{
		QListWidgetItem * item =  ui.m_FileItemList->item( iRow );
		GuiFileXferSession * poCurInfo = (GuiFileXferSession *)item->data( Qt::UserRole ).toULongLong();
		if( poCurInfo->getLclSessionId() == lclSessionId )
		{
			return poCurInfo;
		}
	}

	return NULL;
}

//============================================================================
FileXferWidget * ActivityUploads::findListEntryWidget( VxGuidQt lclSessionId )
{
	int iCnt = ui.m_FileItemList->count();
	for( int iRow = 0; iRow < iCnt; iRow++ )
	{
		QListWidgetItem * item =  ui.m_FileItemList->item( iRow );
		GuiFileXferSession * poCurInfo = (GuiFileXferSession *)item->data( Qt::UserRole + 1 ).toULongLong();
		if( poCurInfo->getLclSessionId() == lclSessionId )
		{
			return (FileXferWidget *)item;
		}
	}

	return NULL;
}

//============================================================================
FileXferWidget * ActivityUploads::addUpload( GuiFileXferSession * poSession )
{
	FileXferWidget * item = sessionToWidget( poSession );

	ui.m_FileItemList->addItem( item );
	ui.m_FileItemList->setItemWidget( item, item );
	return item;
}

//============================================================================
bool ActivityUploads::isUploadInProgress( VxGuidQt fileInstance )
{
	if( findSession( fileInstance ) )
	{
		return true;
	}

	return false;
}

//============================================================================
void ActivityUploads::slotToGuiStartUpload( GuiFileXferSession * poSession )
{
	GuiFileXferSession * newSession = new GuiFileXferSession( *poSession );
	newSession->setXferDirection( eXferDirectionTx );

	FileXferWidget * item = addUpload( newSession );
	item->setXferState( eXferStateInUploadXfer, 0, 0 );
}

//============================================================================
void ActivityUploads::slotToGuiFileXferState(	VxGuidQt		lclSessionId, 
												EXferState		eXferState, 
												int				param1, 
												int				param2  )
{
	FileXferWidget * item = findListEntryWidget( lclSessionId );
	if( item )
	{
		item->setXferState( eXferState, param1, param2 );
	}
}

//============================================================================
void ActivityUploads::slotToGuiFileUploadComplete(	VxGuidQt		lclSessionId, 
													int				xferError )
{
	FileXferWidget * item = findListEntryWidget( lclSessionId );
	if( item )
	{
		item->setXferState( eXferStateCompletedUpload, xferError, xferError );
	}
}

//============================================================================
void ActivityUploads::toGuiStartUpload( void * userData, GuiFileXferSession * xferSession )
{
	Q_UNUSED( userData );
	emit signalToGuiStartUpload( xferSession );
}


//============================================================================
void ActivityUploads::toGuiFileXferState( void * userData, VxGUID& lclSessionId, EXferState eXferState, int param1, int param2 )
{
	Q_UNUSED( userData );
	VxGuidQt myLclSession( lclSessionId );
	emit signalToGuiFileXferState( myLclSession, eXferState, param1, param2 );
}

//============================================================================
void ActivityUploads::toGuiFileUploadComplete( void * userData, VxGUID& lclSession, EXferError xferError )
{
	Q_UNUSED( userData );
	VxGuidQt myLclSession( lclSession );
	emit signalToGuiFileUploadComplete( myLclSession, (int)xferError );
}

//============================================================================
void ActivityUploads::slotFileXferItemClicked(QListWidgetItem * item)
{
}

//============================================================================
void ActivityUploads::slotFileIconButtonClicked( QListWidgetItem * item )
{
	GuiFileXferSession * xferSession = (GuiFileXferSession *)item->QListWidgetItem::data( Qt::UserRole + 1).toULongLong();
	if( xferSession )
	{

	}	
}

//============================================================================
void ActivityUploads::slotCancelButtonClicked( QListWidgetItem * item )
{
	GuiFileXferSession * xferSession = (GuiFileXferSession *)item->QListWidgetItem::data( Qt::UserRole + 1).toULongLong();
	if( xferSession )
	{
		if( eXferStateCompletedUpload != xferSession->getXferState() )
		{
			xferSession->setXferState( eXferStateUserCanceledUpload, 0, 0 );
			((FileXferWidget *)item)->setXferState( eXferStateUserCanceledUpload, 0, 0 );
			m_Engine.fromGuiCancelUpload( xferSession->getLclSessionId() );
		}
	}

	ui.m_FileItemList->removeItemWidget( item );
}

//============================================================================
void ActivityUploads::slotPlayButtonClicked( QListWidgetItem * item )
{
	GuiFileXferSession * xferSession = (GuiFileXferSession *)item->QListWidgetItem::data( Qt::UserRole + 1).toULongLong();
	if( xferSession )
	{
		this->playFile( xferSession->getFullFileName() );
	}
}

//============================================================================
void ActivityUploads::slotLibraryButtonClicked( QListWidgetItem * item )
{
	GuiFileXferSession * xferSession = (GuiFileXferSession *)item->QListWidgetItem::data( Qt::UserRole + 1).toULongLong();
	if( xferSession )
	{
		bool inLibary = xferSession->getIsInLibrary();
		inLibary = !inLibary;
		xferSession->setIsInLibrary( inLibary );
		m_Engine.fromGuiAddFileToLibrary( xferSession->getFullFileName().toUtf8().constData(), inLibary, xferSession->getFileHashId().getHashData() );
		((FileXferWidget *)item)->updateWidgetFromInfo();
	}	
}

//============================================================================
void ActivityUploads::slotFileShareButtonClicked( QListWidgetItem * item )
{
	GuiFileXferSession * xferSession = (GuiFileXferSession *)item->QListWidgetItem::data( Qt::UserRole + 1).toULongLong();
	if( xferSession )
	{
		bool isShared = xferSession->getIsShared();
		isShared = !isShared;
		xferSession->setIsShared( isShared );
		m_Engine.fromGuiSetFileIsShared( xferSession->getFullFileName().toUtf8().constData(), isShared, xferSession->getFileHashId().getHashData() );
		((FileXferWidget *)item)->updateWidgetFromInfo();
	}	
}

//============================================================================
void ActivityUploads::slotShredButtonClicked( QListWidgetItem * item )
{
	GuiFileXferSession * xferSession = (GuiFileXferSession *)item->QListWidgetItem::data( Qt::UserRole + 1).toULongLong();
	if( xferSession )
	{
		QString fileName = xferSession->getFullFileName();
		if( confirmDeleteFile( true ) )
		{
			ui.m_FileItemList->removeItemWidget( item );
			m_Engine.fromGuiDeleteFile( fileName.toUtf8().constData(), true );
		}
	}	
}

//============================================================================
bool ActivityUploads::confirmDeleteFile( bool shredFile )
{
	bool acceptAction = true;
	bool isConfirmDisabled = m_MyApp.getAppSettings().getIsConfirmDeleteDisabled();
	if( false == isConfirmDisabled )
	{
		QString title = shredFile ?  "Confirm Shred File" : "Confirm Delete File";
		QString bodyText = "";
		if( shredFile )
		{
			bodyText = "Are You Sure You Want To Write Random Data Into The File Then Delete From The Device?";
		}
		else
		{
			bodyText = "Are You Sure To Delete The File From The Device?";
		}

		ActivityYesNoMsgBox dlg( m_MyApp, &m_MyApp, title, bodyText );
		dlg.makeNeverShowAgainVisible( true );
		if( false == (QDialog::Accepted == dlg.exec()))
		{
			acceptAction = false;
		}

		if( dlg.wasNeverShowAgainChecked() )
		{
			m_MyApp.getAppSettings().setIsConfirmDeleteDisabled( true );
		}
	}

	return acceptAction;
}

