
#include "VxThread.h"

#define VX_FOUNDDIR WM_APP + 737

#define VXFILEFIND_OPERATION_ABORTED	8928670

#ifndef RCODE
	#define RCODE long
#endif

#define WM_VX_FOUNDFILE WM_APP + 736
//TO ADD msg handler to your window add as shown below (*s are to keep compiler from compiling this example)
//Add to your dialog class in header
/*
class CMyDlg : public CDialog
{
protected:
	// Generated message map functions
	//{{A*FX_MSG(CMyDlg)
    afx_msg LRESULT OnVxFoundFile( WPARAM wParam, LPARAM lParam);
	//}}A*FX_MSG
	D*ECLARE_MESSAGE_MAP()
};
*/
//Add to your dialog implementation
/*
B*EGIN_MESSAGE_MAP(CMyDlg, CDialog)
	//{{A*FX_MSG_MAP(CMyDlg)
	//}}A*FX_MSG_MAP
	ON_MESSAGE( WM_VX_FOUNDFILE, OnVxFoundFile )
E*ND_MESSAGE_MAP()
*/
//Also Add the function 
/*
LRESULT CMyDlg::OnVxFoundFile( WPARAM wParam, LPARAM lParam )
{
	//wParam has file attributes lParam has WIN32_FIND_DATA *
	WIN32_FIND_DATA * pgFileData = (WIN32_FIND_DATA *)lParam;
	char * pPath = (char *)wParam; //path to file
	if( pgFileData )
	{
		ASSERT( pPath );
		if( pgFileData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
		{
			//directory found
		}
		else
		{
			//file found
			char * pFile = pgFileData->cFileName;
			//do stuff here
		}
	}
	else
	{
		//end of find files
	}	
	return TRUE;
}
*/



class VxFileFinder
{
public:
	//=== constructor / destructor ===//
	VxFileFinder();
	~VxFileFinder();

	//=== helpers ===//
	void Abort( void ){ m_bAbort = TRUE; }
	BOOL WasAborted( void ){ return m_bAbort; }
	BOOL IsDone( void ){ return m_bFinding ? 0:1; }


	//=== methods ===//
	RCODE FindFiles(	HWND hWnd, //window to recieve VX_FILEFOUND message
						CString csStartPath,	//start path to search in
						CString csMatch, //wild name match
						BOOL bRecurse ); // if true recurse sub dirs

	BOOL HasSameExtension(	CString & csFileName,
							CStringArray &acsExtensionList );

	RCODE doFinderOperation( void );

protected:
	RCODE RecursiveFindFiles(	CString csPath );

	BOOL						m_bAbort;
	BOOL						m_bFinding;
	//CWinThread* m_pgThread;
	VxThread					m_WorkThread;

	BOOL						m_bRecurse;
	HWND						m_hWnd;
	CString						m_csStartPath;
	CString						m_csMatch;


};
