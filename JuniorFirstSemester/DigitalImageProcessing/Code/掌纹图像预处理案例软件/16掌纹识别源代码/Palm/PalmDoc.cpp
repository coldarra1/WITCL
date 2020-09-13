// PalmDoc.cpp : implementation of the CPalmDoc class
//

#include "stdafx.h"
#include "Palm.h"

#include "PalmDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPalmDoc

IMPLEMENT_DYNCREATE(CPalmDoc, CDocument)

BEGIN_MESSAGE_MAP(CPalmDoc, CDocument)
	//{{AFX_MSG_MAP(CPalmDoc)
	ON_COMMAND(ID_Gray, OnGray)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPalmDoc construction/destruction

CPalmDoc::CPalmDoc()
{
	// TODO: add one-time construction code here
	m_sizeDoc.cx = 800;
	m_sizeDoc.cy = 600;

	m_palDIB = NULL;
	m_hDIB = NULL;
	harris=false;
}

CPalmDoc::~CPalmDoc()
{
		if (m_hDIB != NULL)
	{
		::GlobalFree((HGLOBAL) m_hDIB);
		m_hDIB=NULL;
	}	
	if (m_palDIB != NULL)
	{
		delete m_palDIB;
		m_palDIB=NULL;
	}

}

BOOL CPalmDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	m_hDIB = NewDIB(m_sizeDoc.cx, m_sizeDoc.cy,8);
	InitDIBData();
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPalmDoc serialization

void CPalmDoc::Serialize(CArchive& ar)
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
// CPalmDoc diagnostics

#ifdef _DEBUG
void CPalmDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPalmDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPalmDoc commands

BOOL CPalmDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	//*****************打开图象文件。lpszPathName为图象文件名
	BOOL b  = ReadImgFile(lpszPathName);		//ReadImgFile-<<dpiapi.h(api库中)
	if(b)
	{
		LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIB);
		m_sizeDoc.cx = (int) ::DIBWidth(lpDIB);         // Size of DIB - x
		m_sizeDoc.cy = (int) ::DIBHeight(lpDIB);        // Size of DIB - y
		::GlobalUnlock((HGLOBAL) m_hDIB);
	}
	POSITION pos;
	pos = GetFirstViewPosition();
    this->harris=false;
	return b;	
	return TRUE;
}

BOOL CPalmDoc::CanCloseFrame(CFrameWnd* pFrame) 
{
	// TODO: Add your specialized code here and/or call the base class
		
	return CDocument::CanCloseFrame(pFrame);
}

BOOL CPalmDoc::ReadImgFile(CString sName)
{
		if (m_hDIB != NULL)
	{
		::GlobalFree((HGLOBAL) m_hDIB);
		m_hDIB=NULL;
		}	
	if (m_palDIB != NULL)
	{
		delete m_palDIB;
		m_palDIB=NULL;
	}

	// replace calls to Serialize with ReadDIBFile function
	CFile nFile;
	if(!nFile.Open(sName,CFile::modeRead))
		return false;
	m_hDIB = ReadDIBFile(nFile);
	nFile.Close();
	InitDIBData();

	if (m_hDIB == NULL)
		return FALSE;
	return TRUE;	
}
BOOL CPalmDoc::InitDIBData()
{
	if (m_palDIB != NULL)
	{
		delete m_palDIB;
		m_palDIB = NULL;
	}
	if (m_hDIB == NULL)
	{
		return FALSE;
	}
	m_palDIB = new CPalette;
	if (m_palDIB == NULL)
	{
		// we must be really low on memory
		::GlobalFree((HGLOBAL) m_hDIB);
		m_hDIB = NULL;
		return FALSE;
	}

	if (::CreateDIBPalette(m_hDIB, m_palDIB) == NULL)
	{
		// DIB may not have a palette
		delete m_palDIB;
		m_palDIB = NULL;
	}
	return TRUE;
}	

BOOL CPalmDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
		CFile nFile;
	if(m_hDIB == NULL)
		return  false;
	nFile.Open(lpszPathName,CFile::modeWrite | CFile::modeCreate);
	SaveDIB(m_hDIB, nFile);
	nFile.Close();
	return true;
	return CDocument::OnSaveDocument(lpszPathName);
}

void CPalmDoc::OnGray() 
{
	// TODO: Add your command handler code here

			int i,j;
    unsigned char *lpSrc,*lpDst;//一个指向源、目的像素的移动指针

	//对源图像进行操作
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)m_hDIB);
	int cxDIB = (int) ::DIBWidth(lpDIB);         
	int cyDIB = (int) ::DIBHeight(lpDIB);        
	LPSTR lpDIBBits=::FindDIBBits (lpDIB);	//找到源图像中图像数据区起始位置
	long lLineBytesSrc = WIDTHBYTES(cxDIB * 8 * 3);// 计算源24位真彩图像每行的字节数

	int numColors=(int) ::DIBNumColors((char *)lpDIB);
    if (numColors!=0)  //如果numColors是0，则表示目前图像为24位真彩图
	{
		::GlobalUnlock((HGLOBAL) m_hDIB);
		return;
	}

	//新创建一个8位（256级灰度）的DIB句柄
	HDIB grayhDIB=NewDIB(cxDIB, cyDIB,8);
	LPSTR glpDIB=(LPSTR)::GlobalLock((HGLOBAL)grayhDIB);
	LPSTR glpDIBBits=::FindDIBBits (glpDIB);
	long lLineBytesDst = WIDTHBYTES(cxDIB * 8);// 计算目标8位灰度图像每行的字节数
	// 每行
	for(i = 0; i < cyDIB; i++)
	{
		//每列
		for(j = 0; j < cxDIB; j++)
		{
			// 指向DIB第i行，第j个象素的指针（这里的行为从上到下的）
			lpSrc = (unsigned char*)lpDIBBits + lLineBytesSrc * (cyDIB - 1 - i) + j*3;
			lpDst = (unsigned char*)glpDIBBits + lLineBytesDst * (cyDIB - 1 - i) + j;
			*lpDst=(*lpSrc)/3+(*(lpSrc+1))/3+(*(lpSrc+2))/3;
		}
	}
	m_hDIB=grayhDIB;
	::GlobalUnlock((HGLOBAL) m_hDIB);
	::GlobalUnlock((HGLOBAL) grayhDIB);
	UpdateAllViews(NULL, 0, NULL);	
}

void CPalmDoc::OnFileSaveAs() 
{
	// TODO: Add your command handler code here

}
