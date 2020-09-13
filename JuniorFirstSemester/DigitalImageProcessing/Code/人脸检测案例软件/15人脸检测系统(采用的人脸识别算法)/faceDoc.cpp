// faceDoc.cpp : implementation of the CFaceDoc class
//

#include "stdafx.h"
#include "face.h"

#include "faceDoc.h"
#include "DIB.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern HANDLE hDIB;
extern HANDLE hDIBTemp;
extern class DIB gDib;
extern int gheight;
extern int gwidth;
extern WORD gwBytesPerLine;
/////////////////////////////////////////////////////////////////////////////
// CFaceDoc

IMPLEMENT_DYNCREATE(CFaceDoc, CDocument)

BEGIN_MESSAGE_MAP(CFaceDoc, CDocument)
	//{{AFX_MSG_MAP(CFaceDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFaceDoc construction/destruction

CFaceDoc::CFaceDoc()
{
	// TODO: add one-time construction code here

}

CFaceDoc::~CFaceDoc()
{
}

BOOL CFaceDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFaceDoc serialization

void CFaceDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFaceDoc diagnostics

#ifdef _DEBUG
void CFaceDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFaceDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFaceDoc commands

BOOL CFaceDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	if(hDIB)
		GlobalFree(hDIB);
	hDIB = gDib.LoadDIB(lpszPathName);
	ASSERT(hDIB != NULL);
	hDIBTemp = gDib.CopyHandle(hDIB);
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	gheight = lpbi->biHeight;
	gwidth = lpbi->biWidth;
	gwBytesPerLine = gDib.BytePerLine(hDIB);
	GlobalUnlock(hDIB);
	return TRUE;
}
