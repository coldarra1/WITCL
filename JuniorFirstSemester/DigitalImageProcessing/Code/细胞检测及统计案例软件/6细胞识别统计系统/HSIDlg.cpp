// HSIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Cell.h"
#include "HSIDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CHSIDlg dialog
int			g_nIntGap;
int			g_nSatGap;
int			g_nHueGap;

extern CPoint scroll_lefttop;
/////////////////////////////////////////////////////////////////////////////
// CHSIDlg dialog


CHSIDlg::CHSIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHSIDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHSIDlg)
	m_bEx = FALSE;
	//}}AFX_DATA_INIT
}

CHSIDlg::CHSIDlg(RECT *pSelectedRect, CWnd* pParent)
	: CDialog(CHSIDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHSIDlg)
	m_bEx = FALSE;
	//}}AFX_DATA_INIT
	memcpy(&SelectedRect,pSelectedRect,sizeof(RECT));
}

void CHSIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHSIDlg)
	DDX_Check(pDX, IDC_HSI_EX, m_bEx);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHSIDlg, CDialog)
	//{{AFX_MSG_MAP(CHSIDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHSIDlg message handlers

BOOL CHSIDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetDlgItemInt(IDC_HSIRANGE_HUE, 5);
	SetDlgItemInt(IDC_HSIRANGE_SAT, 8);
	SetDlgItemInt(IDC_HSIRANGE_INT, 8);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHSIDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	int width, height;
	width = SelectedRect.right - SelectedRect.left;
	height = SelectedRect.bottom - SelectedRect.top;

	char	title[128];
	sprintf(title, "预览 %d * %d", width, height);
	SetDlgItemText(IDC_HSIRANGE_PREVIEW, title);

	CWnd	*Pic;
	Pic = GetDlgItem(IDC_HSIRANGE_PIC);

	RECT	PicRect;
	Pic->GetWindowRect(&PicRect);
	ScreenToClient(&PicRect);

	CDC		*pdc = GetDC();
	HDC		hdc = pdc->m_hDC;
	HDC		memdc = ::CreateCompatibleDC(hdc);
	BITMAP	bmp;
	CBitmap::FromHandle(g_hBitmap)->GetBitmap(&bmp);
	::SelectObject(memdc, g_hBitmap);
	::StretchBlt
	(
		hdc,
		PicRect.left + 1,
		PicRect.top + 1,
		PicRect.right - PicRect.left - 2,
		PicRect.bottom - PicRect.top - 2,
		memdc,
		SelectedRect.left+scroll_lefttop.x,
		SelectedRect.top+scroll_lefttop.y,
		width,
		height,
		SRCCOPY
	);
	ReleaseDC(pdc);
	::DeleteDC(memdc);
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CHSIDlg::OnOK() 
{
	int Value;
	Value = GetDlgItemInt(IDC_HSIRANGE_HUE);
	if(Value < 0 || Value > 100)
	{
		MessageBox("HUE误差范围不正确。请重新输入!");
		GetDlgItem(IDC_HSIRANGE_HUE)->SetFocus();
		return;
	}
	else
		g_nHueGap = Value;

	Value = GetDlgItemInt(IDC_HSIRANGE_SAT);
	if(Value < 0 || Value > 100)
	{
		MessageBox("SAT误差范围不正确。请重新输入!");
		GetDlgItem(IDC_HSIRANGE_SAT)->SetFocus();
		return;
	}
	else
		g_nSatGap = Value;

	Value = GetDlgItemInt(IDC_HSIRANGE_INT);
	if(Value < 0 || Value > 100)
	{
		MessageBox("INT误差范围不正确。请重新输入!");
		GetDlgItem(IDC_HSIRANGE_INT)->SetFocus();
		return;
	}
	else
		g_nIntGap = Value;
	UpdateData(TRUE);

	CDialog::OnOK();
}
