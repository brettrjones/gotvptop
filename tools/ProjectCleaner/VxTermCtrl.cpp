// VxTermCtrl.cpp : implementation file
//

#include "stdafx.h"
//#include "VxGui\VxMsg.h"
#include "VxTermCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// VxTermCtrl

VxTermCtrl::VxTermCtrl()
{
	m_iMaxLines=500;
	m_bCopyToTrace = TRUE;
}

VxTermCtrl::~VxTermCtrl()
{
}


BEGIN_MESSAGE_MAP(VxTermCtrl, CEdit)
	//{{AFX_MSG_MAP(VxTermCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// VxTermCtrl message handlers




void VxTermCtrl::Print( char * pStr, ...) 
{
    char szBuffer[256];
    va_list arg_ptr;
    va_start(arg_ptr, pStr );
    vsprintf(szBuffer, pStr,( char * ) arg_ptr);
    va_end(arg_ptr);
	
	if( m_bCopyToTrace )
	{
//		VxMsg( "%s\n", szBuffer );
	}
 
	CString csMsg;
	csMsg = szBuffer;
	csMsg += "\r\n";

	//display message in Msg Edit Window
	int nLength = GetWindowTextLength ();
	SetSel ( nLength, nLength );
	ReplaceSel ( csMsg );

	int nLineCount = GetLineCount ();
	if ( nLineCount > m_iMaxLines ) //limit window test to m_iMaxLines lines
	{
		int nRemoveLines = nLineCount - 10;
		int nChar = LineIndex ( nRemoveLines );
		SetSel ( 0, nChar );
		ReplaceSel ( "" );
	}
	LineScroll ( nLineCount );
}

void VxTermCtrl::HexDump( char * pBuf, long s32DataLen )
{
	long lCount = s32DataLen;
	unsigned char acValue[10];
	unsigned char acString[256];
	long l16Cnt;
	long l16Remander;
	l16Cnt = lCount/16;
	l16Remander = lCount % 16;
	int i;
	//=== first dump the full 16 byte rows ===//
	for(i = 0; i < l16Cnt; i++)
	{
//		strcpy((char *)acString, "\r\n");
		acString[0] = 0;

		int j;
		for(j = 0; j < 16; j++)
		{
			unsigned char ucValue = pBuf[(i * 16) + j];
			sprintf((char *)acValue, "%02x ",ucValue);
			strcat((char *)acString, (char *)acValue);
		}
		strcat((char *)acString, "  ");
		for(j = 0; j < 16; j++)
		{
			unsigned char ucValue = pBuf[(i * 16) + j];
			if(ucValue >= 0x20 && ucValue < 128 && ucValue != '%' && ucValue != '\\')
				sprintf((char *)acValue, "%c",ucValue);
			else
				sprintf((char *)acValue, ".");
			strcat((char *)acString, (char *)acValue);
		}
		Print((char *)acString);
	}
	//=== now dump partial row if any ===//
	if(l16Remander)
	{
//		strcpy((char *)acString, "\r\n");
		acString[0] = 0;
		int j;
		for(j = 0; j < 16; j++)
		{
			if(j < l16Remander)
			{
				unsigned char ucValue = pBuf[(i * 16) + j];
				sprintf((char *)acValue, "%02x ",ucValue);
				strcat((char *)acString, (char *)acValue);
			}
			else
				strcat((char *)acString, "   ");
		}
		strcat((char *)acString, "  ");
		for(j = 0; j < 16; j++)
		{
			if(j < l16Remander)
			{
				unsigned char ucValue = pBuf[(i * 16) + j];
				if(ucValue >= 0x20 && ucValue < 128 && ucValue != '%' && ucValue != '\\')
					sprintf((char *)acValue, "%c",ucValue);
				else
					sprintf((char *)acValue, ".");
				strcat((char *)acString, (char *)acValue);
			}
			else
				strcat((char *)acString, " ");
		}
		Print((char *)acString);
	}
}

void VxTermCtrl::HexDumpToFile( char * pFileName, char * pBuf, long lCount)
{	
	
	unsigned char acValue[10];
	unsigned char acString[256];
	long l16Cnt;
	long l16Remander;
	l16Cnt = lCount/16;
	l16Remander = lCount % 16;
	int i;
	FILE * pgFile;
	if( 0 == ( pgFile = fopen( pFileName, "a+" ) ) )
	{ 
		Print("\nError opening file %s", pFileName);
		return;
	}
	fprintf( pgFile, "\nHex Dump\n" );
	//=== first dump the full 16 byte rows ===//
	for(i = 0; i < l16Cnt; i++)
	{
		strcpy((char *)acString, "\n");
		int j;
		for(j = 0; j < 16; j++)
		{
			unsigned char ucValue = pBuf[(i * 16) + j];
			sprintf((char *)acValue, "%02x ",ucValue);
			strcat((char *)acString, (char *)acValue);
		}
		strcat((char *)acString, "  ");
		for(j = 0; j < 16; j++)
		{
			unsigned char ucValue = pBuf[(i * 16) + j];
			if(ucValue >= 0x20 && ucValue < 128 && ucValue != '%' && ucValue != '\\')
				sprintf((char *)acValue, "%c",ucValue);
			else
				sprintf((char *)acValue, ".");
			strcat((char *)acString, (char *)acValue);
		}
		fprintf(pgFile, (char *)acString);
	}
	//=== now dump partial row if any ===//
	if(l16Remander)
	{
		strcpy((char *)acString, "\n");
		int j;
		for(j = 0; j < 16; j++)
		{
			if(j < l16Remander)
			{
				unsigned char ucValue = pBuf[(i * 16) + j];
				sprintf((char *)acValue, "%02x ",ucValue);
				strcat((char *)acString, (char *)acValue);
			}
			else
				strcat((char *)acString, "   ");
		}
		strcat((char *)acString, "  ");
		for(j = 0; j < 16; j++)
		{
			if(j < l16Remander)
			{
				unsigned char ucValue = pBuf[(i * 16) + j];
				if(ucValue >= 0x20 && ucValue < 128 && ucValue != '%' && ucValue != '\\')
					sprintf((char *)acValue, "%c",ucValue);
				else
					sprintf((char *)acValue, ".");
				strcat((char *)acString, (char *)acValue);
			}
			else
				strcat((char *)acString, " ");
		}
		fprintf(pgFile, (char *)acString);
	}
	fclose(pgFile);
}

