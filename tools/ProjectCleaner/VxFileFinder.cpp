#include "stdafx.h"
#include "AppAll.h"
#include <sys/stat.h>


long DoFinderThreadFunc(void * pvContext)
{
	VxThread * poVxThread = (VxThread *)pvContext;
	poVxThread->setIsThreadRunning(true);
	VxFileFinder * finder = (VxFileFinder *)poVxThread->getThreadUserParam();
    if( finder && false == poThread->isAborted() )
    {
        finder->doFinderOperation();
        //LogMsg(LOG_INFO, "Zipper::zipFiles compress in thread DoZipThreadFunc done\n");
    }

	poVxThread->threadAboutToExit();
	return 0;
}


//============================================================================
VxFileFinder::VxFileFinder()
{
	m_bAbort = FALSE;
	m_bFinding = FALSE;
	//m_pgThread = NULL;
}

//============================================================================
VxFileFinder::~VxFileFinder()
{
	Abort();
	int iTimeout = 0;
	while( m_bFinding )
	{
		Sleep( 100 );
		iTimeout++;
		if( 10 == iTimeout )
		{
			break;
		}
	}
}

////bunch of crap to fool the compiler
//typedef RCODE ( VxFileFinder::*PFN_WORKER_THREAD_FUNCTION) ( void );
//typedef UINT (__cdecl * PFN_FAKEOUT)( LPVOID );
//union MakeMeWork
//{
//	PFN_WORKER_THREAD_FUNCTION pfuncRealFunc;
//	PFN_FAKEOUT pfuncFakeFunc;
//};

//============================================================================
RCODE VxFileFinder::FindFiles(	HWND hWnd, //window to recieve VX_FILEFOUND message
								CString csStartPath,	//start path to search in
								CString csMatch, //wild name match
								BOOL bRecurse ) // if true recurse sub dirs
{
	if( m_bFinding )
	{
		//already busy
		ASSERT( FALSE );
		return -1;
	}
	m_bFinding = TRUE;
	m_bAbort = FALSE;

	m_hWnd = hWnd;
	m_csStartPath = csStartPath;
	m_csMatch = m_csMatch;
	m_bRecurse = bRecurse;

	//sanity checks
	ASSERT( hWnd );
	ASSERT( csStartPath.GetLength() );
	ASSERT( csMatch.GetLength() );
	//make sure start path exists

	char acBuf[ MAX_PATH ];
	BOOL bIsDir = TRUE;
	struct _stat gFileStatus;
	strcpy( acBuf, (const char *)csStartPath );

	if( strlen( acBuf ) > 3 )
	{
		//if not root of drive remove the trailing backslash
		if( '\\' == acBuf[ strlen( acBuf ) - 1 ] )
		{
			acBuf[ strlen( acBuf ) - 1 ] = 0;
		}
	}
	memset( &gFileStatus, 0, sizeof( struct _stat ) );
	gFileStatus.st_mode = _S_IFDIR; //check for dir not file
	if( 0 == _stat( acBuf, &gFileStatus ) )
	{
		if( FALSE == ( gFileStatus.st_mode & _S_IFDIR ))
		{
			//path is not valid directory
			bIsDir = FALSE;
		}
	}
	else
	{
		bIsDir = FALSE;
	}
	if( FALSE == bIsDir )
	{
		//not a valid directory
		return -1;
	}

	//fool thread into using our class member function
	//MakeMeWork gWorker;

	//gWorker.pfuncRealFunc = (PFN_WORKER_THREAD_FUNCTION)&VxFileFinder::ThreadedFinder;
	//
	//m_pgThread = AfxBeginThread( ( AFX_THREADPROC )gWorker.pfuncFakeFunc, (void *)this );
	//if( ! m_pgThread )
	//{
	//	MessageBox( m_hWnd, "VxFileFinder Error", "Could not create Thread", MB_OK );
	//	return -1;
	//}

	if( m_WorkThread.isThreadRunning() )
	{
		// already running
	}
	else
	{
		m_WorkThread.startThread((VX_THREAD_FUNCTION_T)DoFinderThreadFunc, this, "ProjectClean");
	}
	
	return 0;
}

//============================================================================
RCODE VxFileFinder::doFinderOperation( void )
{
	m_bFinding = TRUE;
	RCODE rc = RecursiveFindFiles( m_csStartPath );
	m_bFinding = FALSE;
	::SendMessage( m_hWnd, WM_VX_FOUNDFILE, NULL, NULL );
	return rc;
}


//============================================================================
RCODE VxFileFinder::RecursiveFindFiles(	CString csPath )
{
	if( m_bAbort )
	{
		return -1;
	}
    CString csCurrentNode;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA sFindData;
    RCODE rc = 0;
	ASSERT( csPath.GetLength() );

    if( 0 != csPath.GetLength ( ) )
    {
        if ( '\\' == csPath.GetAt ( csPath.GetLength( ) - 1 ) )
        {
            csCurrentNode = csPath + "*.*";
        }
        else
        {
            csCurrentNode = csPath + '\\' + "*.*";
        }
        hFind = FindFirstFile ( csCurrentNode,
                                &sFindData );
        if( INVALID_HANDLE_VALUE != hFind )
        {
            do
            {
                if ( '\\' == csPath.GetAt ( csPath.GetLength( ) - 1 ) )
                {
                    csCurrentNode = csPath + sFindData.cFileName;
                }
                else
                {
                    csCurrentNode = csPath + '\\' + sFindData.cFileName;
                }
                if ( ( 0 != (sFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) )
                {
				    if ( ( m_bRecurse ) &&
						( 0 != ( strcmp ( ".", sFindData.cFileName ) ) ) &&
				         ( 0 != ( strcmp ( "..", sFindData.cFileName ) ) ) ) //recurse or not
				    {
						::SendMessage( m_hWnd, WM_VX_FOUNDFILE, (WPARAM)(const char *)csPath, (LPARAM)&sFindData );
					    RecursiveFindFiles( csCurrentNode );
				    }
                }
			    else
			    {
					::SendMessage( m_hWnd, WM_VX_FOUNDFILE, (WPARAM)(const char *)csPath, (LPARAM)&sFindData );
			    }
            }
            while( ( FALSE == m_bAbort ) &&
                    ( FindNextFile ( hFind, &sFindData ) ) );
            if( TRUE == m_bAbort )
            {
                rc = VXFILEFIND_OPERATION_ABORTED;
            }
            FindClose ( hFind );
        }
    }
    return rc;
}

//============================================================================
BOOL VxFileFinder::HasSameExtension(	CString & csFileName,
										CStringArray & acsExtensionList )
{
    CString csFilterExt;
	CString csNodeExt;
	int iLen = csFileName.GetLength ( );
	iLen = iLen - csFileName.ReverseFind ( '.' ) - 1;

	csNodeExt = csFileName.Right( (csFileName.GetLength ( ) - csFileName.ReverseFind ( '.' ) - 1) );
	csNodeExt.MakeUpper();

	int iListCnt = acsExtensionList.GetSize();
	for( int iIdx = 0; iIdx < iListCnt; iIdx++ )
	{
        csFilterExt = acsExtensionList[ iIdx ];
		csFilterExt.MakeUpper();

        if( csFilterExt == csNodeExt )
        {
            return TRUE;
        }
    }
    return FALSE;
}
