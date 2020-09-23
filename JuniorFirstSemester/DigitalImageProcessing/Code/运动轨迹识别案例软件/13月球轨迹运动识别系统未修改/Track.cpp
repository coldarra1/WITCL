// Track.cpp : implementation file
//

#include "stdafx.h"
#include "ydpd.h"
#include "Track.h"
#include "ydgj.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Track dialog


Track::Track(CWnd* pParent /*=NULL*/)
	: CDialog(Track::IDD, pParent)
{
	//{{AFX_DATA_INIT(Track)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	this->m_YDGJ.m_Len = 0;
}


void Track::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Track)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Track, CDialog)
	//{{AFX_MSG_MAP(Track)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Track message handlers
//下面的代码实现物体轨迹的绘制
void Track::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	int i;
	CPen Pen;
	//创建画笔
	Pen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	//选中画笔
	dc.SelectObject(&Pen);
	CWnd	*Chart;
	CRect m_ChartRect;
	//得到窗口指针
	Chart = GetDlgItem(IDC_STATIC_GUIJI);
    //得到窗口的矩形大小
	Chart->GetWindowRect(&m_ChartRect);
	//更改屏幕坐标，使之与客户区相对应
	ScreenToClient(&m_ChartRect);
	//画物体中心点
	for(i =0 ;i<this->m_YDGJ.m_Len;i++)
	{
		CPoint po;
		//得到物体中心点的横坐标、纵坐标
		po.x = m_YDGJ.m_Guiji[i].x+40;
		po.y = m_mapheight - m_YDGJ.m_Guiji[i].y+50;
		//画点
		dc.SetPixel(po,RGB(255,0,0));
	}
	//画物体的运动轨迹曲线
	for( i=0;i<this->m_YDGJ.m_Len-1;i++)
	{   //移动到起始点
		dc.MoveTo(m_YDGJ.m_Guiji[i].x+40,m_mapheight - m_YDGJ.m_Guiji[i].y+50);
		//画线
		dc.LineTo(m_YDGJ.m_Guiji[i+1].x+40,m_mapheight - m_YDGJ.m_Guiji[i+1].y+50);
	}
	
	Pen.DeleteObject();
	
}
