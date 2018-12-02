// ProjectCleanerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AppAll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProjectCleanerDlg dialog

CProjectCleanerDlg::CProjectCleanerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProjectCleanerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProjectCleanerDlg)
	m_csCurFile = _T("");
	m_csCurDir = _T("");
	m_csStartDir = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProjectCleanerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProjectCleanerDlg)
	DDX_Control(pDX, IDC_MSG, m_gMsg);
	DDX_Text(pDX, IDC_CUR_FILE, m_csCurFile);
	DDX_Text(pDX, IDC_CUR_DIR, m_csCurDir);
	DDX_Text(pDX, IDC_START_DIR, m_csStartDir);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProjectCleanerDlg, CDialog)
	//{{AFX_MSG_MAP(CProjectCleanerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_CLEAN, OnClean)
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_VX_FOUNDFILE, OnVxFoundFile )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProjectCleanerDlg message handlers

BOOL CProjectCleanerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_acsExtensions.Add("OBJ");
	m_acsExtensions.Add("SYM");
	m_acsExtensions.Add("ILK");
	m_acsExtensions.Add("PCH");
	m_acsExtensions.Add("RES");
	m_acsExtensions.Add("IDB");
	m_acsExtensions.Add("PDB");
	m_acsExtensions.Add("NCB");
	m_acsExtensions.Add( "LOG" );
	m_acsExtensions.Add("TLOG");
	m_acsExtensions.Add("o");



	char as8StartDir[ MAX_PATH ];
	strcpy(as8StartDir, "C:\\");

	GetCurrentDirectory(MAX_PATH, as8StartDir);

	GetProfileString(	"Project Cleaner", 
						"Start Directory",
						as8StartDir, // starting directory
						as8StartDir,
						sizeof( as8StartDir ) );
	m_csStartDir = as8StartDir;
	UpdateData( FALSE );
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CProjectCleanerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CProjectCleanerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CProjectCleanerDlg::OnBrowse() 
{
	TCHAR acStartDir[ _MAX_PATH ];
	GetProfileString(	"Project Cleaner", 
						"Start Directory",
						m_csStartDir,
						acStartDir,
						sizeof( acStartDir ) );
	TCHAR acDisplayName[_MAX_PATH];
	strcpy( acDisplayName, acStartDir );
	BROWSEINFO bi;

	//FIXME.. figure out how to use this to set the root path ( pidlRoot )
//	ITEMIDLIST m_gItemIdList; 
	

	bi.hwndOwner = GetSafeHwnd();
	bi.pidlRoot = NULL;
	bi.pszDisplayName = acDisplayName;
	bi.lpszTitle = "Choose Path";
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;

	LPCITEMIDLIST pidl;
	pidl = SHBrowseForFolder( &bi );
	SHGetPathFromIDList(pidl, acDisplayName);	
	m_csStartDir = acDisplayName;
	WriteProfileString( "Project Cleaner", 
						"Start Directory", 
						m_csStartDir );
	UpdateData( FALSE );

	Invalidate();
}	




LRESULT CProjectCleanerDlg::OnVxFoundFile( WPARAM wParam, LPARAM lParam )
{
	//wParam has file attributes lParam has WIN32_FIND_DATA *
	WIN32_FIND_DATA * pgFileData = (WIN32_FIND_DATA *)lParam;
	char * pPath = (char *)wParam;
	if( pgFileData )
	{
		ASSERT( pPath );
		if( pgFileData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
		{
			//directory found
			m_csCurDir = pPath;
			UpdateData( FALSE );
		}
		else
		{
			//file found
			m_csCurFile = pPath;
			m_csCurFile += pgFileData->cFileName;
			if( m_gFinder.HasSameExtension( m_csCurFile, m_acsExtensions ) )
			{
//				_unlink( pgFileData->cFileName );
				m_gMsg.Print( "deleted file %s", (const char *)m_csCurFile );
			}
			m_iFileCnt++;
			m_u64Bytes += pgFileData->nFileSizeLow;
			UpdateData( FALSE );
		}
		//add file to found list if 
	}
	else
	{
		//end of find files
//		m_csCurFile = "Project Clean Complete";
		m_csCurFile.Format( "%d files containing %d kilo bytes deleted", 
					m_iFileCnt,
					(unsigned long)(m_u64Bytes / 1000) );
		m_gMsg.Print( "%d files containing %d kilo bytes deleted", 
					m_iFileCnt,
					(unsigned long)(m_u64Bytes / 1000) );
		UpdateData( FALSE );
	}	
	return TRUE;
}

void CProjectCleanerDlg::OnClean() 
{
	UpdateData();
	m_u64Bytes = 0;
	m_iFileCnt = 0;
	m_gFinder.FindFiles( GetSafeHwnd(), //window to recieve VX_FILEFOUND message
						m_csStartDir,	//start path to search in
						"*.*", //wild name match
						TRUE ); // if true recurse sub dirs

	

}
