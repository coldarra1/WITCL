#include <afxwin.h>

class CMFCSample1Frame : public CFrameWnd
{
protected:
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CMFCSample1Frame,CFrameWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CMFCSample1Frame::OnPaint()
{
	CPaintDC dc(this);
	CPen Pen1;
	CPen* pOldPen;
	CBrush Brush1,Brush2;
	CBrush* pOldBrush;

	Pen1.CreatePen(PS_SOLID,2,RGB(0,0,255));
	Brush1.CreateSolidBrush(RGB(255,0,0));
	Brush2.CreateSolidBrush(RGB(0,255,0));

	pOldPen=dc.SelectObject(&Pen1);
	pOldBrush=dc.SelectObject(&Brush1);

	dc.Rectangle(100,100,199,199);

	dc.SelectObject(&Brush2);

	dc.Ellipse(300,100,399,199);

	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);
}

class CMFCSample1App : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

BOOL CMFCSample1App::InitInstance()
{
	CMFCSample1Frame* pMainWnd;

	pMainWnd=new CMFCSample1Frame;

	pMainWnd->Create(NULL,_T("MFC Sample 1"));
	pMainWnd->ShowWindow(this->m_nCmdShow);
	pMainWnd->UpdateWindow();

	this->m_pMainWnd=pMainWnd;

	return TRUE;
}

CMFCSample1App theApp;

