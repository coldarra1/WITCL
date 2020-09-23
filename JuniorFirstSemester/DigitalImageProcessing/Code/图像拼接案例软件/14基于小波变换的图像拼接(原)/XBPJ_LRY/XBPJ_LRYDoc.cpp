// XBPJ_LRYDoc.cpp : implementation of the CXBPJ_LRYDoc class
//

#include "stdafx.h"
#include "XBPJ_LRY.h"

#include "XBPJ_LRYDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXBPJ_LRYDoc

IMPLEMENT_DYNCREATE(CXBPJ_LRYDoc, CDocument)

BEGIN_MESSAGE_MAP(CXBPJ_LRYDoc, CDocument)
	//{{AFX_MSG_MAP(CXBPJ_LRYDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXBPJ_LRYDoc construction/destruction

CXBPJ_LRYDoc::CXBPJ_LRYDoc()
{
	// TODO: add one-time construction code here

}

CXBPJ_LRYDoc::~CXBPJ_LRYDoc()
{
}

BOOL CXBPJ_LRYDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CXBPJ_LRYDoc serialization

void CXBPJ_LRYDoc::Serialize(CArchive& ar)
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
// CXBPJ_LRYDoc diagnostics

#ifdef _DEBUG
void CXBPJ_LRYDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CXBPJ_LRYDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXBPJ_LRYDoc commands
