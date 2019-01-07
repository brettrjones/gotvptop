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
// brett.jones@engineer.com
// http://www.gotvptop.net
//============================================================================

#include "GuiHelpers.h"

#include "AppCommon.h"

#include <CoreLib/VxFileIsTypeFunctions.h>
#include <CoreLib/VxParse.h>
#include <CoreLib/VxFileUtil.h>

#include <QFileDialog>
#include <QFileInfo>
#include <QFile>

#include <QDesktopServices>
#include <QUrl>
#include <QDebug>

//============================================================================
const char * GuiHelpers::describeResponse( EOfferResponse eOfferResponse )
{
	switch( eOfferResponse )
	{
	case eOfferResponseAccept:
		return "Offer Accepted";

	case eOfferResponseReject:
		return "Offer Rejected";

	case eOfferResponseBusy:
		return "Busy";

	case eOfferResponseCancelSession:
		return "Session Canceled";

	case eOfferResponseEndSession:
		return "User Ended Session";

	case eOfferResponseUserOffline:
		return "User Is Offline";

	default:
		return "Session Ended";
	}
}

//============================================================================
const char * GuiHelpers::describePluginPermission( EFriendState ePluginPermission )
{
	switch(ePluginPermission)
	{
	case eFriendStateIgnore:
		return "Disabled";
	case eFriendStateAnonymous:
		return "Anonymous";
	case eFriendStateGuest:
		return "Guest";
	case eFriendStateFriend:
		return "Friends";
	default:
		return "Unknown";
	}
}

//============================================================================
QString GuiHelpers::getJustFileName( QString& fileNameAndPath )
{
	QString justFileName("");
	if( !fileNameAndPath.isEmpty() )
	{
		int lastSlashIdx = fileNameAndPath.lastIndexOf('/');
		if( lastSlashIdx >= 0 )
		{
			justFileName = fileNameAndPath.right( fileNameAndPath.length() - ( lastSlashIdx + 1 ) );
		}

		if( justFileName.isEmpty() )
		{
			justFileName = fileNameAndPath;
		}
	}

	return justFileName;
}

//============================================================================
void GuiHelpers::splitPathAndFileName( QString& fileNameAndPath, QString& retFileName, QString& retPath )
{
	retFileName = "";
	retPath = "";
	if( !fileNameAndPath.isEmpty() )
	{
		int lastSlashIdx = fileNameAndPath.lastIndexOf('/');
		if( lastSlashIdx >= 0 )
		{
			retFileName = fileNameAndPath.right( fileNameAndPath.length() - ( lastSlashIdx + 1 ) );
		}

		if( retFileName.isEmpty() )
		{
			retPath = fileNameAndPath;
			retFileName = fileNameAndPath;
		}
		else
		{
			retPath = fileNameAndPath.left( lastSlashIdx );
		}
	}
}

//============================================================================
QString GuiHelpers::browseForDirectory( QString startDir, QWidget * parent )
{

	QString dir = QFileDialog::getExistingDirectory(
		parent, 
		QObject::tr("Open Directory"),
		startDir, 
		QFileDialog::ShowDirsOnly
		| QFileDialog::DontResolveSymlinks);
	if( false == dir.isEmpty() )
	{
		dir.replace( "\\", "/" );
		if( '/' != dir.at(dir.length() - 1) )
		{
			dir.append( "/" );
		}
	}

	return dir;
}

//============================================================================
bool GuiHelpers::copyResourceToOnDiskFile( QString resourcePath, QString fileNameAndPath )
{
	bool resourceCopied = false;
	//QFileInfo resPathInfo( resourceFile );
	QFile resfile( resourcePath );
	QFile onDiskFile( fileNameAndPath );
	if( resfile.open( QIODevice::ReadOnly ) )
	{
		if( onDiskFile.open( QIODevice::ReadWrite ) )
		{
			if( 0 == onDiskFile.write( resfile.readAll() ) )
			{
				qWarning() << "Could not write app resource file " << fileNameAndPath;
			}
			else
			{
				resourceCopied = true;
			}

			onDiskFile.close();
		}
		else
		{
			qWarning() << "Could not open app resource file for writing " << fileNameAndPath;
		}

		resfile.close();
	}
	else
	{
		qWarning() << "Could not open resource file " << resourcePath;
	}

	return resourceCopied;
}

//============================================================================
bool GuiHelpers::playFile( AppCommon& myApp, QString fullFileName, int pos0to100000 )
{
    if( fullFileName.isEmpty() )
    {
        myApp.toGuiUserMessage( "GuiHelpers::playFile Empty File Name" );
        return false;
    }

    uint8_t fileType;
    uint64_t fileLen;
    if( !VxFileUtil::getFileTypeAndLength( fullFileName.toUtf8().constData(), fileLen, fileType ) )
    {
        myApp.toGuiUserMessage( "File no longer available %s", fullFileName.toUtf8().constData() );
        return false;
    }

    if( VXFILE_TYPE_DIRECTORY & fileType )
    {
#ifdef TARGET_OS_WINDOWS
        ShellExecuteA( 0, 0, fullFileName.toUtf8().constData(), 0, 0, SW_SHOW );
#else
        QDesktopServices::openUrl( QUrl::fromLocalFile( fullFileName ) );
#endif // TARGET_OS_WINDOWS
    }
    else
    {
        // is file
        if( VxShouldOpenFile( fileType ) )
        {
            if( fileType & ( VXFILE_TYPE_AUDIO | VXFILE_TYPE_VIDEO ) )
            {
                // can be played
                return myApp.getFromGuiInterface().fromGuiPlayLocalMedia( fullFileName.toUtf8().constData(), fileLen, fileType, pos0to100000 );
            }

#ifdef TARGET_OS_WINDOWS
            ShellExecuteA( 0, 0, fullFileName.toUtf8().constData(), 0, 0, SW_SHOW );
#else
            QDesktopServices::openUrl( QUrl::fromLocalFile( fullFileName ) );
#endif // TARGET_OS_WINDOWS
        }
        else
        {
            myApp.toGuiUserMessage( "File Type Not Supported" );
            return false;
        }
    }

    return true;
}

//============================================================================
int GuiHelpers::calculateTextHeight( QFontMetrics& fontMetrics, QString textStr )
{
	int textHeight = 0;
	if( textStr.isEmpty() )
	{
		textHeight = fontMetrics.height();
	}
	else
	{
		int lineCount = textStr.count( QLatin1Char('\n') ) + 1;
		textHeight = lineCount * fontMetrics.height();
	}

	return textHeight;
}

//============================================================================
QString GuiHelpers::describeEXferError( EXferError xferError )
{
	switch( xferError )
	{
	case eXferErrorNone:
		return QObject::tr("No Error");
	case eXferErrorDisconnected:
		return QObject::tr("Disconnected");
	case eXferErrorPermission:
		return QObject::tr("Permission Error");
	case eXferErrorFileNotFound:
		return QObject::tr("File Not Found");
	case eXferErrorCanceled:
		return QObject::tr("Canceled");
	case eXferErrorBadParam:
		return QObject::tr("Bad Param");
	case eXferErrorAtSrc:
		return QObject::tr("Error At Source");
	case eXferErrorBusy:
		return QObject::tr("Busy");
	case eXferErrorAlreadyDownloading:
		return QObject::tr("Already Downloading");
	case eXferErrorAlreadyDownloaded:
		return QObject::tr("Already Downloaded");
	case eXferErrorAlreadyUploading:
		return QObject::tr("Already Uploading");
	case eXferErrorFileCreateError:
		return QObject::tr("File Create Error");
	case eXferErrorFileOpenAppendError:
		return QObject::tr("File Append Error");
	case eXferErrorFileOpenError:
		return QObject::tr("File Open Error");
	case eXferErrorFileSeekError:
		return QObject::tr("Seek Error");
	case eXferErrorFileReadError:
		return QObject::tr("Read Error");
	case eXferErrorFileWriteError:
		return QObject::tr("Write Error");
	case eXferErrorFileMoveError:
		return QObject::tr("Move File Error");
	default:
		return QObject::tr("Unknown Error");
	}
}

//============================================================================
QString GuiHelpers::describeEXferState( EXferState xferState )
{
	switch( xferState )
	{
	case eXferStateUploadNotStarted:
		return QObject::tr("Upload Not Started");
	case eXferStateWaitingOfferResponse:
		return QObject::tr("Waiting Response");
	case eXferStateInUploadQue:
		return QObject::tr("In Upload Que");
	case eXferStateBeginUpload:
		return QObject::tr("Start Upload");
	case eXferStateInUploadXfer:
		return QObject::tr("Uploading");
	case eXferStateCompletedUpload:
		return QObject::tr("Completed Upload");
	case eXferStateUserCanceledUpload:
		return QObject::tr("Upload Canceled");
	case eXferStateUploadOfferRejected:
		return QObject::tr("Offer Rejected");
	case eXferStateUploadError:
		return QObject::tr("ERROR");
	case eXferStateDownloadNotStarted:
		return QObject::tr("Download Not Started");
	case eXferStateInDownloadQue:
		return QObject::tr("In Download Que");
	case eXferStateBeginDownload:
		return QObject::tr("Start Download");
	case eXferStateInDownloadXfer:
		return QObject::tr("Downloading");
	case eXferStateCompletedDownload:
		return QObject::tr("Completed Download");
	case eXferStateUserCanceledDownload:
		return QObject::tr("Download Canceled");
	case eXferStateDownloadError:
		return QObject::tr("ERROR");
	case eXferStateUnknown:
	default:
		return QObject::tr("Unknown State");
	}
}

//============================================================================
QString GuiHelpers::describeFileLength( uint64_t fileLen )
{
	std::string strLen;
	if( fileLen >= 1000000000000ULL )
	{
		StdStringFormat( strLen, "%3.1fTB ", (double)(fileLen) / 1000000000000.0);
	}
	else if( fileLen >= 1000000000ULL )
	{
		StdStringFormat( strLen, "%3.1fGB ", (double)(fileLen) / 1000000000.0);
	}
	else if( fileLen >= 1000000 )
	{
		StdStringFormat( strLen, "%3.1fMB ", (double)(fileLen) / 1000000.0);
	}
	else if( fileLen >= 1000 )
	{
		StdStringFormat( strLen, "%3.1fKB ", (double)(fileLen) / 1000.0);
	}
	else
	{
		StdStringFormat( strLen, "%3.1fBytes ", (double)fileLen );
	}

	QString strFormatedLen = strLen.c_str();
	return strFormatedLen;
}

//============================================================================
bool GuiHelpers::isPluginSingleSession( EPluginType ePluginType )
{
    bool isSingleSessionPlugin = false;
	switch(ePluginType)
	{
	case ePluginTypeVoicePhone:
	case ePluginTypeVideoPhone:
	case ePluginTypeTruthOrDare:
	case ePluginTypeMultiSession:
	case ePluginTypeAdmin:
		isSingleSessionPlugin = true;
		break;
	case ePluginTypeWebServer:
	case ePluginTypeRelay:
	case ePluginTypeCamServer:
	case ePluginTypeStoryBoard: 
	case ePluginTypeFileServer:
	case ePluginTypeFileOffer:
	default:
		break;
	}

	return isSingleSessionPlugin;
}

//============================================================================
std::string GuiHelpers::describePlugin( EPluginType ePluginType, bool rmtInitiated )
{
    std::string strPluginDesc = "";

	switch(ePluginType)
	{
    case ePluginTypeAdmin:
		strPluginDesc = "Admin Server";
		break;
	case ePluginTypeWebServer:
		if( rmtInitiated )
		{
			strPluginDesc = "Profile Page";
		}
		else
		{
			strPluginDesc = "Web Server";       		
		}
		break;
	case ePluginTypeRelay:
		strPluginDesc = "Relay";
		break;
	case ePluginTypeCamServer:
		if( rmtInitiated )
		{
			strPluginDesc = "Cam Client";
		}
		else
		{
			strPluginDesc = "Cam Server";       		
		}

		break;

	case ePluginTypeMultiSession:
		strPluginDesc = "Text Chat";
		break;
	case ePluginTypeVoicePhone:
		strPluginDesc = "Voice Phone (VOIP)";
		break;
	case ePluginTypeVideoPhone:
		strPluginDesc = "Video Chat";
		break;
	case ePluginTypeTruthOrDare:
		strPluginDesc = "Truth or Dare";
		break;
	case ePluginTypeStoryBoard: 
		strPluginDesc = "Storyboard";
		break;	
	case ePluginTypeFileServer:
		strPluginDesc = "Share Files";
		break;
	case ePluginTypeFileOffer:
		strPluginDesc = "File Send";
		break;
    default:
        strPluginDesc = "UNKNOWN PLUGIN";
	}

	return strPluginDesc;
}
