// BmpBaseInfo.cpp : implementation file
//

#include "stdafx.h"
#include "Project.h"
#include "BmpBaseInfo.h"
#include "ProjectDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBmpBaseInfo dialog


CBmpBaseInfo::CBmpBaseInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CBmpBaseInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBmpBaseInfo)
	m_Style = _T("");
	m_FileSize = _T("");
	m_DataOff = _T("");
	m_SelfLen = _T("");
	m_Width = _T("");
	m_Height = _T("");
	m_DataSize = _T("");
	m_PixelDep = _T("");
	m_UsedColor = _T("");
	m_ImportColor = _T("");
	m_Compress = _T("");
	//}}AFX_DATA_INIT
}


void CBmpBaseInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBmpBaseInfo)
	DDX_Text(pDX, IDC_STYLE, m_Style);
	DDX_Text(pDX, IDC_FILESIZE, m_FileSize);
	DDX_Text(pDX, IDC_DATAOFF, m_DataOff);
	DDX_Text(pDX, IDC_SELFLEN, m_SelfLen);
	DDX_Text(pDX, IDC_WIDTH, m_Width);
	DDX_Text(pDX, IDC_HEIGHT, m_Height);
	DDX_Text(pDX, IDC_DATASIZE, m_DataSize);
	DDX_Text(pDX, IDC_PIXELDEP, m_PixelDep);
	DDX_Text(pDX, IDC_USEDCOLOR, m_UsedColor);
	DDX_Text(pDX, IDC_IMPORTCOLOR, m_ImportColor);
	DDX_Text(pDX, IDC_COMPRESS, m_Compress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBmpBaseInfo, CDialog)
	//{{AFX_MSG_MAP(CBmpBaseInfo)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBmpBaseInfo message handlers
CString CBmpBaseInfo::LongToString(long data)
{
	CString str;
	int dec,sign;
	str = _ecvt(data,10,&dec,&sign);
	//AfxMessageBox(str.Left(dec));
	if (data != 0)
		return str.Left(dec);
	else
		return "0";
}

void CBmpBaseInfo::SetInfo(CProjectDoc * pDoc)
{
	CString csTemp;

	if (pDoc->BitMapFileHeader.bfType == 0x4D42)
	{
			m_Style = "BMP";
	}
	csTemp = LongToString(pDoc->BitMapFileHeader.bfSize);
	m_FileSize = csTemp + "B";

	csTemp = LongToString(pDoc->BitMapFileHeader.bfOffBits);
	m_DataOff = csTemp + "-十进制";

	csTemp = LongToString(pDoc->pBitMapInfo->bmiHeader.biSize);
	m_SelfLen = csTemp + "-十进制";

	csTemp = LongToString(pDoc->pBitMapInfo->bmiHeader.biWidth);
	m_Width = csTemp + "像素";

	csTemp = LongToString(pDoc->pBitMapInfo->bmiHeader.biHeight);
	m_Height = csTemp + "像素";

	csTemp = LongToString(pDoc->pBitMapInfo->bmiHeader.biSizeImage);
	m_DataSize = csTemp + "B";

	csTemp = LongToString(pDoc->pBitMapInfo->bmiHeader.biBitCount);
	m_PixelDep = csTemp + "bit";

	csTemp = LongToString(pDoc->pBitMapInfo->bmiHeader.biClrUsed);
	m_UsedColor = csTemp + "种";

	csTemp = LongToString(pDoc->pBitMapInfo->bmiHeader.biClrImportant);
	m_ImportColor = csTemp + "种";

	if (pDoc->pBitMapInfo->bmiHeader.biCompression == BI_RGB)
	{
		m_Compress = "BI_RGB";
	}

}
