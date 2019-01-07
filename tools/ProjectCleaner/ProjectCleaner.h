// ProjectCleaner.h : main header file for the PROJECTCLEANER application
//

#if !defined(AFX_PROJECTCLEANER_H__5B06FAE7_B103_11D5_88EA_00E098874FBE__INCLUDED_)
#define AFX_PROJECTCLEANER_H__5B06FAE7_B103_11D5_88EA_00E098874FBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CProjectCleanerApp:
// See ProjectCleaner.cpp for the implementation of this class
//

class CProjectCleanerApp : public CWinApp
{
public:
	CProjectCleanerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProjectCleanerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CProjectCleanerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROJECTCLEANER_H__5B06FAE7_B103_11D5_88EA_00E098874FBE__INCLUDED_)
