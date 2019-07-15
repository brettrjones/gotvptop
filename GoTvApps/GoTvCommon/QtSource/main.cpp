//============================================================================
// Copyright (C) 2014 Brett R. Jones
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

#include "AppCommon.h"
//#include <QtGui/QApplication>
#include <CoreLib/VxGlobals.h>


int main(int argc, char *argv[])
{
#ifdef TARGET_OS_WINDOWS
	//Initialize COM
	//HRESULT hr = CoInitialize(0);
	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
#endif // TARGET_OS_WINDOWS

	QApplication a(argc, argv);
	AppCommon w;
	QCoreApplication::setOrganizationDomain( VxGetCompanyDomain());
	// NOTE OrganizationName and ApplicationName become part of data storage location path
	QCoreApplication::setOrganizationName("free");
	QCoreApplication::setApplicationName( VxGetApplicationNameNoSpaces() );
	QCoreApplication::setApplicationVersion( VxGetAppVersionString() );

	g_App = &w;
	int result = 0;
	w.startup();
	w.show();
	if( false == w.userCanceled() )
	{
		result =  a.exec();
	}

	w.shutdown();
#ifdef TARGET_OS_WINDOWS
	//uninit
	CoUninitialize();
#endif // TARGET_OS_WINDOWS

	return result;
}
