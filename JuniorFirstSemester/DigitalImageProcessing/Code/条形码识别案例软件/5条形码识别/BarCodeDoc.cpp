// BarCodeDoc.cpp : implementation of the CBarCodeDoc class
//

#include "stdafx.h"
#include "BarCode.h"

#include "BarCodeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBarCodeDoc

IMPLEMENT_DYNCREATE(CBarCodeDoc, CDocument)

BEGIN_MESSAGE_MAP(CBarCodeDoc, CDocument)
	//{{AFX_MSG_MAP(CBarCodeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBarCodeDoc construction/destruction

CBarCodeDoc::CBarCodeDoc()
{
	// TODO: add one-time construction code here

}

CBarCodeDoc::~CBarCodeDoc()
{
}

BOOL CBarCodeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBarCodeDoc serialization

void CBarCodeDoc::Serialize(CArchive& ar)
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
// CBarCodeDoc diagnostics

#ifdef _DEBUG
void CBarCodeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBarCodeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBarCodeDoc commands
