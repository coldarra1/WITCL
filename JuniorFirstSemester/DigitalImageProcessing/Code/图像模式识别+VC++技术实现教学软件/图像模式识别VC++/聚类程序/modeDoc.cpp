// modeDoc.cpp : implementation of the CModeDoc class
//

#include "stdafx.h"
#include "mode.h"

#include "modeDoc.h"

//#include "Cluster.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModeDoc

IMPLEMENT_DYNCREATE(CModeDoc, CDocument)

BEGIN_MESSAGE_MAP(CModeDoc, CDocument)
	//{{AFX_MSG_MAP(CModeDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModeDoc construction/destruction

CModeDoc::CModeDoc()
{
	state=0;
}

CModeDoc::~CModeDoc()
{
}

BOOL CModeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CModeDoc serialization

void CModeDoc::Serialize(CArchive& ar)
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
// CModeDoc diagnostics

#ifdef _DEBUG
void CModeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CModeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CModeDoc commands

//DEL void CModeDoc::OnFileNew() 
//DEL {
//DEL 	mCluster.LoadFile("blank.bmp");	//解决路径问题！！！！！？？？？？
//DEL 	state=2;
//DEL //	AfxMessageBox("打开空白图片成功");
//DEL 	
//DEL }

//DEL void CModeDoc::OnFileOpen() 
//DEL {
//DEL 	CString filename;
//DEL 	CFileDialog dlg(TRUE,_T("BMP"),_T("*.BMP"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("位图文件(*.BMP)|*.BMP|"));	
//DEL 
//DEL     if(IDOK==dlg.DoModal ())
//DEL 	{
//DEL 		filename.Format ("%s",dlg.GetPathName() );    
//DEL 		mCluster.LoadFile(filename);
//DEL 		state=1;//打开一幅图片
//DEL //		AfxMessageBox("打开成功");
//DEL //		data=true;
//DEL //		standardnum=false;
//DEL 	}	
//DEL }




