// HistogramDlg.cpp : implementation file
//

#include "stdafx.h"
#include "cell.h"
#include "HistogramDlg.h"

#include "HSI.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern RGB*		g_pImgBuffer;
extern int		g_nMapHeight;
extern int		g_nMapWidth;
extern FLAGS*	g_pFlags;
/////////////////////////////////////////////////////////////////////////////
// CHistogramDlg dialog


CHistogramDlg::CHistogramDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHistogramDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHistogramDlg)
	m_Thresh_B = 0;
	m_Thresh_G = 0;
	m_Thresh_R = 0;
	m_Thresh_BMax = 0;
	m_Thresh_GMax = 0;
	m_Thresh_RMax = 0;
	m_nMag = 0;
	//}}AFX_DATA_INIT
	m_bUserRatio = false;
}


void CHistogramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHistogramDlg)
	DDX_Text(pDX, IDC_THRESH_B, m_Thresh_B);
	DDX_Text(pDX, IDC_THRESH_G, m_Thresh_G);
	DDX_Text(pDX, IDC_THRESH_R, m_Thresh_R);
	DDX_Text(pDX, IDC_THRESH_BMAX, m_Thresh_BMax);
	DDX_Text(pDX, IDC_THRESH_GMAX, m_Thresh_GMax);
	DDX_Text(pDX, IDC_THRESH_RMAX, m_Thresh_RMax);
	DDX_Text(pDX, IDC_HISTOGRAM_MAGNIFY, m_nMag);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHistogramDlg, CDialog)
	//{{AFX_MSG_MAP(CHistogramDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RED, OnRed)
	ON_BN_CLICKED(IDC_GREEN, OnGreen)
	ON_BN_CLICKED(IDC_BLUE, OnBlue)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_HISTOGRAM_SAME, OnHistogramSame)
	ON_EN_CHANGE(IDC_HISTOGRAM_MAGNIFY, OnChangeHistogramMagnify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
// CHistogramDlg message handlers
BEGIN_EVENTSINK_MAP(CHistogramDlg, CDialog)
//{{AFX_EVENTSINK_MAP(CHistogramDlg)
//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

BOOL CHistogramDlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	if(!g_hBitmap)
		MessageBox("图像文件错误!无法生成柱状图.");
	else
	{
		GenHistogramData();
		((CButton *) GetDlgItem(IDC_RED))->SetCheck(true);

		CWnd	*Chart;
		Chart = GetDlgItem(IDC_HISTOGRAM_CHART);
		Chart->GetWindowRect(&m_ChartRect);
		ScreenToClient(&m_ChartRect);

		m_Thresh_R = m_Thresh_G = m_Thresh_B = 0;
		m_Thresh_RMax = m_Thresh_GMax = m_Thresh_BMax = 255;
		m_nMag = ratior;
		UpdateData(FALSE);

		InvalidateRect(0, TRUE);
	}

	return TRUE;	// return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CHistogramDlg::OnChangeHistogramMagnify(void)
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	// TODO: Add your control notification handler code here
	MessageBox("a");
	UpdateData(TRUE);
	m_bUserRatio = true;
	GenHistogramData();
	m_bUserRatio = false;
	InvalidateRect(0, TRUE);
}


void CHistogramDlg::GenHistogramData(void)
{
	RGB *cur=g_pImgBuffer;
	FLAGS *cur_flag=g_pFlags;
	memset(m_Histogram, 0, sizeof(m_Histogram));
	for(int j = 0; j < g_nMapHeight; j++)
	{
		for(int i = 0; i < g_nMapWidth; i++)
		{
			if(!cur_flag->marked)
			{
				m_Histogram[0][cur->r]++;
				m_Histogram[1][cur->g]++;
				m_Histogram[2][cur->b]++;
			}
			cur_flag++;
			cur++;
		}
	}

	DWORD	maxr = 0, maxg = 0, maxb = 0;
	double	tot_pixel = g_nMapWidth * g_nMapHeight;
	for(int i = 0; i < 256; i++)
	{
		if(maxr < m_Histogram[0][i]) maxr = m_Histogram[0][i];
		if(maxg < m_Histogram[1][i]) maxg = m_Histogram[1][i];
		if(maxb < m_Histogram[2][i]) maxb = m_Histogram[2][i];
	}

	if(m_bUserRatio)
		ratior = ratiog = ratiob = m_nMag;
	else
	{
		ratior = tot_pixel / maxr;
		ratiog = tot_pixel / maxg;
		ratiob = tot_pixel / maxb;
	}

	for(i = 0; i < 256; i++)
	{
		m_Histogram[0][i] = (long) ((m_Histogram[0][i] * 100.0 * ratior) / tot_pixel);
		m_Histogram[1][i] = (long) ((m_Histogram[1][i] * 100.0 * ratiog) / tot_pixel);
		m_Histogram[2][i] = (long) ((m_Histogram[2][i] * 100.0 * ratiob) / tot_pixel);
		if(m_Histogram[0][i] > 101) m_Histogram[0][i] = 101;
		if(m_Histogram[1][i] > 101) m_Histogram[1][i] = 101;
		if(m_Histogram[2][i] > 101) m_Histogram[2][i] = 101;
	}
}


void CHistogramDlg::OnPaint(void)
{
	CPaintDC	dc(this);	// device context for painting

	// TODO: Add your message handler code here
	if(((CButton *) GetDlgItem(IDC_RED))->GetCheck())
	{
		DrawData(&dc, 0);	// red
		DrawFrame(&dc, 0);
	}
	else if(((CButton *) GetDlgItem(IDC_GREEN))->GetCheck())
	{
		DrawData(&dc, 1);	// green
		DrawFrame(&dc, 1);
	}
	else if(((CButton *) GetDlgItem(IDC_BLUE))->GetCheck())
	{
		DrawData(&dc, 2);	// blue
		DrawFrame(&dc, 2);
	}
	else
		MessageBox("unknown error");

	// Do not call CDialog::OnPaint() for painting messages
}

void CHistogramDlg::DrawFrame(CDC *dc, char type)
{
	CPen	pen;
	int		i;
	m_ChartRect.left++;
	switch(type)
	{
	case 0:
		for(i = 0; i < 256; i++)
		{
			pen.CreatePen(PS_SOLID, 1, RGB(i, 0, 0));
			dc->SelectObject(pen);
			dc->MoveTo(m_ChartRect.left + i, m_ChartRect.bottom + 5);
			dc->LineTo(m_ChartRect.left + i, m_ChartRect.bottom + 15);
			pen.DeleteObject();
		}
		break;
	case 1:
		for(i = 0; i < 256; i++)
		{
			pen.CreatePen(PS_SOLID, 1, RGB(0, i, 0));
			dc->SelectObject(pen);
			dc->MoveTo(m_ChartRect.left + i, m_ChartRect.bottom + 5);
			dc->LineTo(m_ChartRect.left + i, m_ChartRect.bottom + 15);
			pen.DeleteObject();
		}
		break;
	case 2:
		for(i = 0; i < 256; i++)
		{
			pen.CreatePen(PS_SOLID, 1, RGB(0, 0, i));
			dc->SelectObject(pen);
			dc->MoveTo(m_ChartRect.left + i, m_ChartRect.bottom + 5);
			dc->LineTo(m_ChartRect.left + i, m_ChartRect.bottom + 15);
			pen.DeleteObject();
		}
		break;
	}

	pen.CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
	dc->SelectObject(pen);
	for(i = 1; i < 8; i++)
	{
		dc->MoveTo(m_ChartRect.left + i * 32, m_ChartRect.top + 1);
		dc->LineTo(m_ChartRect.left + i * 32, m_ChartRect.bottom - 1);
	}

	pen.DeleteObject();

	pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
	dc->SelectObject(pen);
	switch(type)
	{
	case 0:
		dc->MoveTo(m_ChartRect.left + m_Thresh_R, m_ChartRect.top + 1);
		dc->LineTo(m_ChartRect.left + m_Thresh_R, m_ChartRect.bottom - 1);
		break;
	case 1:
		dc->MoveTo(m_ChartRect.left + m_Thresh_G, m_ChartRect.top + 1);
		dc->LineTo(m_ChartRect.left + m_Thresh_G, m_ChartRect.bottom - 1);
		break;
	case 2:
		dc->MoveTo(m_ChartRect.left + m_Thresh_B, m_ChartRect.top + 1);
		dc->LineTo(m_ChartRect.left + m_Thresh_B, m_ChartRect.bottom - 1);
		break;
	}

	pen.DeleteObject();

	pen.CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
	dc->SelectObject(pen);
	switch(type)
	{
	case 0:
		dc->MoveTo(m_ChartRect.left + m_Thresh_RMax, m_ChartRect.top + 1);
		dc->LineTo(m_ChartRect.left + m_Thresh_RMax, m_ChartRect.bottom - 1);
		break;
	case 1:
		dc->MoveTo(m_ChartRect.left + m_Thresh_GMax, m_ChartRect.top + 1);
		dc->LineTo(m_ChartRect.left + m_Thresh_GMax, m_ChartRect.bottom - 1);
		break;
	case 2:
		dc->MoveTo(m_ChartRect.left + m_Thresh_BMax, m_ChartRect.top + 1);
		dc->LineTo(m_ChartRect.left + m_Thresh_BMax, m_ChartRect.bottom - 1);
		break;
	}

	pen.DeleteObject();

	m_ChartRect.left--;
}

void CHistogramDlg::DrawData(CDC *dc, char type)
{
	int		i;
	CPen	pen;
	m_ChartRect.left++;
	m_ChartRect.bottom--;
	switch(type)
	{
	case 0:
		pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		dc->SelectObject(pen);
		for(i = 0; i < 256; i++)
		{
			dc->MoveTo(m_ChartRect.left + i, m_ChartRect.bottom);
			dc->LineTo(m_ChartRect.left + i, m_ChartRect.bottom - m_Histogram[0][i] * 2);
		}

		DeleteObject(pen);
		break;
	case 1:
		pen.CreatePen(PS_SOLID, 1, RGB(0, 140, 0));
		dc->SelectObject(pen);
		for(i = 0; i < 256; i++)
		{
			dc->MoveTo(m_ChartRect.left + i, m_ChartRect.bottom);
			dc->LineTo(m_ChartRect.left + i, m_ChartRect.bottom - m_Histogram[1][i] * 2);
		}

		DeleteObject(pen);
		break;
	case 2:
		pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		dc->SelectObject(pen);
		for(i = 0; i < 256; i++)
		{
			dc->MoveTo(m_ChartRect.left + i, m_ChartRect.bottom);
			dc->LineTo(m_ChartRect.left + i, m_ChartRect.bottom - m_Histogram[2][i] * 2);
		}

		DeleteObject(pen);
		break;
	}

	m_ChartRect.left--;
	m_ChartRect.bottom++;
}

void CHistogramDlg::OnRed(void)
{
	// TODO: Add your control notification handler code here
	m_nMag = ratior;
	UpdateData(FALSE);
	InvalidateRect(0, TRUE);
}

void CHistogramDlg::OnGreen(void)
{
	// TODO: Add your control notification handler code here
	m_nMag = ratiog;
	UpdateData(FALSE);
	InvalidateRect(0, TRUE);
}

void CHistogramDlg::OnBlue(void)
{
	// TODO: Add your control notification handler code here
	m_nMag = ratiob;
	UpdateData(FALSE);
	InvalidateRect(0, TRUE);
}

void CHistogramDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if
	(
		point.x > m_ChartRect.left
	&&	point.x < m_ChartRect.right - 1
	&&	point.y > m_ChartRect.top
	&&	point.y < m_ChartRect.bottom
	)
	{
		if(((CButton *) GetDlgItem(IDC_RED))->GetCheck())
		{
			m_Thresh_R = point.x - m_ChartRect.left - 1;
		}
		else if(((CButton *) GetDlgItem(IDC_GREEN))->GetCheck())
		{
			m_Thresh_G = point.x - m_ChartRect.left - 1;
		}
		else if(((CButton *) GetDlgItem(IDC_BLUE))->GetCheck())
		{
			m_Thresh_B = point.x - m_ChartRect.left - 1;
		}
		else
		{
			MessageBox("unknown error");
			return;
		}

		UpdateData(FALSE);
		InvalidateRect(&m_ChartRect, TRUE);
	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CHistogramDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if
	(
		point.x > m_ChartRect.left
	&&	point.x < m_ChartRect.right - 1
	&&	point.y > m_ChartRect.top
	&&	point.y < m_ChartRect.bottom
	)
	{
		if(((CButton *) GetDlgItem(IDC_RED))->GetCheck())
		{
			m_Thresh_RMax = point.x - m_ChartRect.left - 1;
		}
		else if(((CButton *) GetDlgItem(IDC_GREEN))->GetCheck())
		{
			m_Thresh_GMax = point.x - m_ChartRect.left - 1;
		}
		else if(((CButton *) GetDlgItem(IDC_BLUE))->GetCheck())
		{
			m_Thresh_BMax = point.x - m_ChartRect.left - 1;
		}
		else
		{
			MessageBox("unknown error");
			return;
		}

		UpdateData(FALSE);
		InvalidateRect(&m_ChartRect, TRUE);
	}

	CDialog::OnRButtonDown(nFlags, point);
}

void CHistogramDlg::OnExclusivePressed(void)
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CHistogramDlg::OnOK(void)
{
	// TODO: Add extra validation here
	if(m_Thresh_R > m_Thresh_RMax || m_Thresh_G > m_Thresh_GMax || m_Thresh_B > m_Thresh_BMax)
	{
		MessageBox("阈值最大值不应小于最小值");
		return;
	}

	CDialog::OnOK();
}

void CHistogramDlg::OnHistogramSame(void)
{
	// TODO: Add your control notification handler code here
	m_Thresh_GMax = m_Thresh_BMax = m_Thresh_RMax;
	m_Thresh_G = m_Thresh_B = m_Thresh_R;
	UpdateData(FALSE);
	InvalidateRect(0, TRUE);
}
/////////////////////////////////////////////////////////////////////////////
// CHistogramDlg message handlers
