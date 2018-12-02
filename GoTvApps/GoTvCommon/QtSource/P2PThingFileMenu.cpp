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
#include "PopupMenu.h"
#include "MyIcons.h"
#include "AppGlobals.h"

#include "ActivityUploads.h"
#include "ActivityDownloads.h"
#include "ActivityBrowseFiles.h"
#include "ActivityViewMySharedFiles.h"
#include "ActivityPersonalRecorder.h"
#include "ActivityViewLibraryFiles.h"
#include <GoTvCore/GoTvP2P/P2PEngine/FileShareSettings.h>
#include <GoTvCore/GoTvP2P/P2PEngine/EngineSettings.h>
#include <CoreLib/VxGlobals.h>

//============================================================================
void AppCommon::slotFileMenuButtonClick( void )
{
	PopupMenu oPopupMenu( *this, this );
	oPopupMenu.setTitle( QObject::tr( "File Menu" ) );
	oPopupMenu.addMenuItem( 1, getMyIcons().getIcon(eMyIconNotepadNormal),		QObject::tr( "Personal Recorder" ) );
	oPopupMenu.addMenuItem( 2, getMyIcons().getIcon(eMyIconFileBrowseNormal),		QObject::tr( "Browse Device Files" ) );
	oPopupMenu.addMenuItem( 3, getMyIcons().getIcon(eMyIconLibraryNormal),		QObject::tr( "View My Library Of Files" ) );
	oPopupMenu.addMenuItem( 4, getMyIcons().getIcon(eMyIconFileShareAddRemove),	QObject::tr( "View My Shared Files" ) );
	oPopupMenu.addMenuItem( 5, getMyIcons().getIcon(eMyIconFileDownload),			QObject::tr( "View Downloading Files" ) );
	oPopupMenu.addMenuItem( 6, getMyIcons().getIcon(eMyIconFileUpload),			QObject::tr( "View Uploading Files" ) );
	oPopupMenu.addMenuItem( 7, getMyIcons().getIcon(eMyIconFolder),				QObject::tr( "Open Download Folder" ) );
	//oPopupMenu.addMenuItem( 8, getMyIcons().getIcon(eMyIconFileShareOptions),		QObject::tr( "File Share Options" ) );

	connect( &oPopupMenu, SIGNAL(menuItemClicked(int, QWidget *)), this, SLOT(onMenuFileSelected(int, QWidget *)));
	oPopupMenu.exec();
}

//============================================================================
void AppCommon::onMenuFileSelected( int iMenuId, QWidget * senderPopupMenu )
{
	Q_UNUSED( senderPopupMenu );
	switch( iMenuId )
	{
	case 1:
		{
			ActivityPersonalRecorder * dlg = new ActivityPersonalRecorder(	*this,
				getAppGlobals().getUserIdent(),
				getCentralWidget() );
			dlg->show();
			break;
		}

	case 2: // 
		{
			ActivityBrowseFiles dlg( *this, eFileFilterAll, 0 );
			dlg.exec();
			break;
		}

	case 3: // My Library
		{
			ActivityViewLibraryFiles dlg( *this, this );
			dlg.exec();
			break;
		}

	case 4: // View My Shared Files
		{
			ActivityViewMySharedFiles dlg( *this, this );
			dlg.exec();
			break;
		}


		//case 3: //Start/Stop File Share Server
		//	switch( m_Engine.fromGuiGetPluginServerState( ePluginTypeFileServer ) )
		//	{
		//	case ePluginServerStateStarted:	
		//		m_Engine.enableFileShare(false);
		//		m_Engine.fromGuiStopPluginSession( ePluginTypeFileServer, m_Engine.getMyPktAnnounce().getMyOnlineId(), NULL );
		//		okMessageBox( tr("File Share Server"), tr("File sharing has been stopped") );
		//		break;

		//	case ePluginServerStateStopped:
		//		m_Engine.fromGuiStartPluginSession( ePluginTypeFileServer, m_Engine.getMyPktAnnounce().getMyOnlineId(), NULL );
		//		m_Engine.enableFileShare(true);
		//		okMessageBox( tr("File Share Server"), tr("File sharing has been started") );
		//		break;

		//	case ePluginServerStateDisabled:	// disabled by permissions
		//		{
		//			okMessageBox( tr("File Share Server"), tr("File sharing is disabled by permissions") );
		//			ActivityPermissions * poDlg = new ActivityPermissions( *this, getCentralWidget() );
		//			poDlg->setPluginType(ePluginTypeFileServer);
		//			poDlg->exec();
		//		}

		//		break;
		//	}
		//	break;

	case 5: // View Downloading Files
		m_Downloads->show();
		break;

	case 6: // View Uploading Files
		m_Uploads->show();
		break;

	case 7: // Open Download Folder
		{
			FileShareSettings fileShareSettings;
			m_Engine.fromGuiGetFileShareSettings( fileShareSettings );

			std::string strExploreCmd = "explorer ";
			strExploreCmd += VxGetDownloadsDirectory();
			system( strExploreCmd.c_str() );
			break;
		}

	case 8: // File Share Options
		{
			//ActivityShareFilesSetup dlg( *this, this );
			//dlg.exec();
			break;
		}

	default: 
		LogMsg( LOG_ERROR, "onMenuServerSelected: ERROR unknown menu id %d\n", iMenuId );
		break;
	}

}
