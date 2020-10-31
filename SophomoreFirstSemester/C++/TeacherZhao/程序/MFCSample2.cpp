#include <afxwin.h>

class CShape
{
protected:
	int x1,y1,x2,y2;

public:
	CShape(int x1,int y1,int x2,int y2);
	virtual void Draw(CDC *pDC);
};

CShape::CShape(int x1,int y1,int x2,int y2)
{
	this->x1=x1;
	this->y1=y1;
	this->x2=x2;
	this->y2=y2;
}

void CShape::Draw(CDC *pDC)
{
}

class CLine : public CShape
{
public:
	CLine(int x1,int y1,int x2,int y2) : CShape(x1,y1,x2,y2) {}
	void Draw(CDC *pDC);
};

void CLine::Draw(CDC *pDC)
{
	pDC->MoveTo(x1,y1);
	pDC->LineTo(x2,y2);
}

class CRectangle : public CShape
{
public:
	CRectangle(int x1,int y1,int x2,int y2) : CShape(x1,y1,x2,y2) {}
	void Draw(CDC *pDC);
};

void CRectangle::Draw(CDC *pDC)
{
	pDC->Rectangle(x1,y1,x2,y2);
}

class CEllipse : public CShape
{
public:
	CEllipse(int x1,int y1,int x2,int y2) : CShape(x1,y1,x2,y2) {}
	void Draw(CDC *pDC);
};

void CEllipse::Draw(CDC *pDC)
{
	pDC->Ellipse(x1,y1,x2,y2);
}

class CMFCSample2Frame : public CFrameWnd
{
protected:
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CMFCSample2Frame,CFrameWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CMFCSample2Frame::OnPaint()
{
	CPaintDC dc(this);

	CShape *pShapes[3];

	pShapes[0]=new CLine(100,100,199,199);
	pShapes[1]=new CRectangle(300,100,399,199);
	pShapes[2]=new CEllipse(500,100,599,199);

	for(int i=0;i<3;i++)
	{
		pShapes[i]->Draw(&dc);
	}

	for(int j=0;j<3;j++)
	{
		delete pShapes[j];
	}
}

class CMFCSample2App : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

BOOL CMFCSample2App::InitInstance()
{
	CMFCSample2Frame* pMainWnd;

	pMainWnd=new CMFCSample2Frame;

	pMainWnd->Create(NULL,_T("MFC Sample 2"));
	pMainWnd->ShowWindow(this->m_nCmdShow);
	pMainWnd->UpdateWindow();

	this->m_pMainWnd=pMainWnd;

	return TRUE;
}

CMFCSample2App theApp;

