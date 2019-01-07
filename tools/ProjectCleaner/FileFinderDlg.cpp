// FileFinderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AppAll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// FileFinderDlg dialog


FileFinderDlg::FileFinderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(FileFinderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(FileFinderDlg)
	m_csCurFile = _T("");
	//}}AFX_DATA_INIT
}


void FileFinderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FileFinderDlg)
	DDX_Text(pDX, IDC_CUR_FILE, m_csCurFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FileFinderDlg, CDialog)
	//{{AFX_MSG_MAP(FileFinderDlg)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FileFinderDlg message handlers

BOOL FileFinderDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void FileFinderDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void FileFinderDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
