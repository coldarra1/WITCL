// ydpdDoc.cpp : implementation of the CYdpdDoc class
//

#include "stdafx.h"
#include "ydpd.h"

#include "ydpdDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CYdpdDoc

IMPLEMENT_DYNCREATE(CYdpdDoc, CDocument)

BEGIN_MESSAGE_MAP(CYdpdDoc, CDocument)
	//{{AFX_MSG_MAP(CYdpdDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYdpdDoc construction/destruction

CYdpdDoc::CYdpdDoc()
{
	// TODO: add one-time construction code here

}

CYdpdDoc::~CYdpdDoc()
{
}

BOOL CYdpdDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CYdpdDoc serialization

void CYdpdDoc::Serialize(CArchive& ar)
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
// CYdpdDoc diagnostics

#ifdef _DEBUG
void CYdpdDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CYdpdDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CYdpdDoc commands
