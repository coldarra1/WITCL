// DSPLITDoc.cpp : implementation of the CDSPLITDoc class
// 2005.1.13£­16£º02 By Superman 

#include "stdafx.h"
#include "DSPLIT.h"

#include "DSPLITDoc.h"
#include "DlgTemplate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDSPLITDoc

IMPLEMENT_DYNCREATE(CDSPLITDoc, CDocument)

BEGIN_MESSAGE_MAP(CDSPLITDoc, CDocument)
	//{{AFX_MSG_MAP(CDSPLITDoc)
	ON_COMMAND(ID_MENU_DESIGN, OnMenuDesign)
	ON_COMMAND(ID_BUTTON_OPEN, OnButtonOpen)
	ON_COMMAND(ID_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSPLITDoc construction/destruction

CDSPLITDoc::CDSPLITDoc()
{
	char curdir[256];
	::GetCurrentDirectory(256,curdir);
	curDir.Format("%s",curdir);

	classify.LoadFile("picture.bmp");

	CFile TheFile("template.dat",CFile::modeRead);
	CArchive ar(&TheFile,CArchive::load,40960);
	TheFile.SeekToBegin();

	for(int i=0;i<10;i++)
	{
		ar>>classify.pattern[i].number;
		for(int n=0;n<classify.pattern[i].number;n++)
		for(int j=0;j<25;j++)
		{
			ar>>classify.pattern[i].feature[n][j];
		}
	}
	ar.Close();
	TheFile.Close();	
}

CDSPLITDoc::~CDSPLITDoc()
{
}

BOOL CDSPLITDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDSPLITDoc serialization

void CDSPLITDoc::Serialize(CArchive& ar)
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
// CDSPLITDoc diagnostics

#ifdef _DEBUG
void CDSPLITDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDSPLITDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDSPLITDoc commands



void CDSPLITDoc::OnMenuDesign() 
{
	CDlgTemplate dlg;
	dlg.curDir=curDir;
	if (IDOK==dlg.DoModal())
	{	
		for(int i=0;i<10;i++)
		{
			classify.pattern[i].number=dlg.pattern[i].number;
			for(int n=0;n<classify.pattern[i].number;n++)
			for(int j=0;j<25;j++)
			{
				classify.pattern[i].feature[n][j]=dlg.pattern[i].feature[n][j];
			}
		}
	}

}

void CDSPLITDoc::OnButtonOpen() 
{
	// TODO: Add your command handler code here
	CFileDialog dlg(TRUE,_T("BMP"),_T("*.BMP"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("Î»Í¼ÎÄ¼þ(*.BMP)|*.BMP|"));	
    if(IDOK==dlg.DoModal ())
	{
		filename.Format ("%s",dlg.GetPathName() );    
		classify.LoadFile(filename);
	}

}

void CDSPLITDoc::OnHelp() 
{
	::WinExec("hh.exe help.chm",SW_SHOW);	
}
