// ProjectCleanerDlg.h : header file
//

#if !defined(AFX_PROJECTCLEANERDLG_H__5B06FAE9_B103_11D5_88EA_00E098874FBE__INCLUDED_)
#define AFX_PROJECTCLEANERDLG_H__5B06FAE9_B103_11D5_88EA_00E098874FBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CProjectCleanerDlg dialog

class CProjectCleanerDlg : public CDialog
{
// Construction
public:
	CProjectCleanerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CProjectCleanerDlg)
	enum { IDD = IDD_PROJECTCLEANER_DIALOG };
	VxTermCtrl	m_gMsg;
	CString	m_csCurFile;
	CString	m_csCurDir;
	CString	m_csStartDir;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProjectCleanerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CProjectCleanerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowse();
    afx_msg LRESULT OnVxFoundFile( WPARAM wParam, LPARAM lParam);
	afx_msg void OnClean();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	VxFileFinder m_gFinder;
	CStringArray m_acsExtensions;
	ULONGLONG m_u64Bytes;
	int m_iFileCnt;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROJECTCLEANERDLG_H__5B06FAE9_B103_11D5_88EA_00E098874FBE__INCLUDED_)
