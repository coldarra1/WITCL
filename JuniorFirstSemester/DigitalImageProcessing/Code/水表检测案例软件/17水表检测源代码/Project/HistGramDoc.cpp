// HistGramDoc.cpp : implementation file
//

#include "stdafx.h"
#include "Project.h"
#include "HistGramDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHistGramDoc

IMPLEMENT_DYNCREATE(CHistGramDoc, CDocument)

CHistGramDoc::CHistGramDoc()
{
	bIsLoaded = FALSE;
	pHist = NULL;
}


BOOL CHistGramDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CHistGramDoc::~CHistGramDoc()
{
	if(pHist != NULL)
	{
		LocalFree(pHist);
	}
}


BEGIN_MESSAGE_MAP(CHistGramDoc, CDocument)
	//{{AFX_MSG_MAP(CHistGramDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHistGramDoc diagnostics

#ifdef _DEBUG
void CHistGramDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHistGramDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHistGramDoc serialization

void CHistGramDoc::Serialize(CArchive& ar)
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
// CHistGramDoc commands
void CHistGramDoc::SetDocument(CProjectDoc *pDoc)
{
	int i, j;
	int nWidth;

	BitCount = pDoc->BitCount;

	if (BitCount == 8)
	{
		//分配256字节的空间
		pHist=(long *)LocalAlloc(LMEM_FIXED, 256 * sizeof(long));
		memset(pHist, 0, 256 * sizeof(long));
		/*
		for(i = 0; i<256; i++)
		{
			pHist[i] = 0;
		}
		*/
		if (pDoc->BmpWidth % 4 == 0)
		{
			nWidth = pDoc->BmpWidth;
		}
		else
		{
			nWidth = (pDoc->BmpWidth / 4 + 1) * 4;
		}
		for (i = 0; i < pDoc->BmpHeight; i ++)
			for(j = 0; j < pDoc->BmpWidth; j ++)
			{
				pHist[pDoc->pImage[i * nWidth + j]] ++;
			}
	}
	else if (BitCount == 24)
	{
		pHist=(long *)LocalAlloc(LMEM_FIXED, 256 * 3 * sizeof(long));
		memset(pHist, 0, 256 * 3 * sizeof(long));

		/*
		for(i = 0; i< 256 * 3; i++)
		{
			pHist[i] = 0;
		}
		*/

		if (pDoc->BmpWidth % 4 == 0)
		{
			nWidth = pDoc->BmpWidth * 3;
		}
		else
		{
			nWidth = (pDoc->BmpWidth * 3 / 4 + 1) * 4;
		}

		for (i = 0; i < pDoc->BmpHeight; i ++)
			for(j = 0; j < pDoc->BmpWidth; j ++)
			{
				pHist[pDoc->pImage[i * nWidth + j * 3]] ++;//blue
				pHist[256 + pDoc->pImage[i * nWidth + j * 3 + 1]] ++;//green
				pHist[512 + pDoc->pImage[i * nWidth + j * 3 + 2]] ++;//red
			}
	}

	//SetModifiedFlag(TRUE);

}


BOOL CHistGramDoc::SaveModified() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (IsModified())
	{
		if (AfxMessageBox("要将直方图保存为bmp文件吗?", MB_YESNO) == IDNO)
		{
			return TRUE;
		}
	}
	else
	{
		return TRUE;
	}
	CString strSaveFileType = "位图文件 (*.bmp)|*.bmp|所有文件 (*.*)|*.*||";
	CFileDialog FileDlg(TRUE, "*.bmp", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		strSaveFileType);

	if (FileDlg.DoModal() == IDOK)
	{
		//OpenDocumentFile(FileDlg.m_ofn.lpstrFile);
		OnSaveDocument(FileDlg.m_ofn.lpstrFile);
		return TRUE;
	}
	else
		return FALSE;
	
	//return CDocument::SaveModified();
	return TRUE;
}

BOOL CHistGramDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	AfxMessageBox("asdasdasd");
	//return CDocument::OnSaveDocument(lpszPathName);
	return TRUE;
}
