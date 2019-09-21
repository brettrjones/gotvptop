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

#include "config_gotvapps.h"

#include <NetLib/VxXferDefs.h>
#include <PktLib/VxCommon.h>

#include <QString>

class AppCommon;
class QWidget;
class QFontMetrics;

class GuiHelpers
{
public:
	static QString				getJustFileName( QString& fileNameAndPath );
	static void					splitPathAndFileName( QString& fileNameAndPath, QString& retFileName, QString& retPath );
	static QString				browseForDirectory( QString startDir = "", QWidget * parent = 0 );
	static bool					copyResourceToOnDiskFile( QString resourcePath, QString fileNameAndPath );

	static bool				    playFile( AppCommon& myApp, QString fullFileName, int pos0to100000 );

    static int					calculateTextHeight( QFontMetrics& fontMetrics, QString textStr );

    static bool                 isPluginSingleSession( EPluginType ePluginType );

    static std::string			describePlugin( EPluginType ePluginType, bool rmtInitiated );
	static const char *			describeResponse( EOfferResponse eOfferResponse );
	static const char *			describePluginPermission( EFriendState ePluginPermission );
	static QString				describeEXferState( EXferState xferState );
	static QString				describeEXferError( EXferError xferError );
	static QString				describeFileLength( uint64_t fileLen );

    /// @brief get home or messenger topmost widget
    static QWidget *            getParentPageFrame( QWidget * curWidget );

};

