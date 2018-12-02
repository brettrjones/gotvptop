#if !defined(AFX_FILEFINDERDLG_H__5B06FAF1_B103_11D5_88EA_00E098874FBE__INCLUDED_)
#define AFX_FILEFINDERDLG_H__5B06FAF1_B103_11D5_88EA_00E098874FBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileFinderDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// FileFinderDlg dialog

class FileFinderDlg : public CDialog
{
// Construction
public:
	FileFinderDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(FileFinderDlg)
	enum { IDD = IDD_FILEFIND_DLG };
	CString	m_csCurFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FileFinderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(FileFinderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEFINDERDLG_H__5B06FAF1_B103_11D5_88EA_00E098874FBE__INCLUDED_)
