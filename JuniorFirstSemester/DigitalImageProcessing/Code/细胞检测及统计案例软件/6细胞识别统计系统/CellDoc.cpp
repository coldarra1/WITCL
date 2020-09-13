// CellDoc.cpp : implementation of the CCellDoc class
//

#include "stdafx.h"
#include "Cell.h"

#include "CellDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCellDoc

IMPLEMENT_DYNCREATE(CCellDoc, CDocument)

BEGIN_MESSAGE_MAP(CCellDoc, CDocument)
	//{{AFX_MSG_MAP(CCellDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCellDoc construction/destruction

CCellDoc::CCellDoc()
{
	// TODO: add one-time construction code here

}

CCellDoc::~CCellDoc()
{
}

BOOL CCellDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCellDoc serialization

void CCellDoc::Serialize(CArchive& ar)
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
// CCellDoc diagnostics

#ifdef _DEBUG
void CCellDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCellDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCellDoc commands
