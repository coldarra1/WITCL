// recognise_yanDoc.cpp : implementation of the CRecognise_yanDoc class
//

#include "stdafx.h"
#include "recognise_yan.h"

#include "recognise_yanDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecognise_yanDoc

IMPLEMENT_DYNCREATE(CRecognise_yanDoc, CDocument)

BEGIN_MESSAGE_MAP(CRecognise_yanDoc, CDocument)
	//{{AFX_MSG_MAP(CRecognise_yanDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecognise_yanDoc construction/destruction

CRecognise_yanDoc::CRecognise_yanDoc()
{
	// TODO: add one-time construction code here

}

CRecognise_yanDoc::~CRecognise_yanDoc()
{
}

BOOL CRecognise_yanDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CRecognise_yanDoc serialization

void CRecognise_yanDoc::Serialize(CArchive& ar)
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
// CRecognise_yanDoc diagnostics

#ifdef _DEBUG
void CRecognise_yanDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRecognise_yanDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRecognise_yanDoc commands
