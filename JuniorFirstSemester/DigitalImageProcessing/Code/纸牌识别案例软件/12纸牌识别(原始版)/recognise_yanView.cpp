// recognise_yanView.cpp : implementation of the CRecognise_yanView class
//

#include "stdafx.h"
#include "recognise_yan.h"
#include "recognise_yanDoc.h"
#include "recognise_yanView.h"
#include "math.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecognise_yanView

IMPLEMENT_DYNCREATE(CRecognise_yanView, CView)

BEGIN_MESSAGE_MAP(CRecognise_yanView, CView)
	//{{AFX_MSG_MAP(CRecognise_yanView)
	ON_COMMAND(ID_OPEN_IMAGE, OnOpenImage)
	ON_COMMAND(ID_RECOGNISE_IMAGE, OnRecogniseImage)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecognise_yanView construction/destruction

CRecognise_yanView::CRecognise_yanView()
{
	// TODO: add construction code here

}

CRecognise_yanView::~CRecognise_yanView()
{
}

BOOL CRecognise_yanView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CRecognise_yanView drawing

void CRecognise_yanView::OnDraw(CDC* pDC)
{
	CRecognise_yanDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);    // TODO: add draw code for native data here
	if(m_dib.m_bLoaded==true)  //判断是否加载图像
	{
		//获取图像宽和高
		int nw=m_dib.GetDIBWidth();
		int nh=m_dib.GetDIBHeight();
		// 显示图像（具体的参数见CDIB类的该函数说明）
		m_dib.ShowDIB(pDC,10,10,nw,nh,m_dib.m_pDIBData,m_dib.m_pBMI);
		m_dib.ShowDIB(pDC,400,10,nw,nh,m_dib.m_pDumpDIBData,m_dib.m_pBMI);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRecognise_yanView printing

BOOL CRecognise_yanView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRecognise_yanView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRecognise_yanView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CRecognise_yanView diagnostics

#ifdef _DEBUG
void CRecognise_yanView::AssertValid() const
{
	CView::AssertValid();
}

void CRecognise_yanView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRecognise_yanDoc* CRecognise_yanView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRecognise_yanDoc)));
	return (CRecognise_yanDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRecognise_yanView message handlers

void CRecognise_yanView::OnOpenImage() 
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	static char szFilter[]="BMP文件(*.bmp)|*.bmp||";  //定义过滤文件的类型
	CFileDialog dlg(TRUE,"bmp",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);//定义文件对话框对象
	CString filename;
	int ret=dlg.DoModal();  //运行打开文件对方框
	 if(ret==IDOK)
	   {		
			filename=dlg.GetFileName();     //获取所选择图像的路径
			m_dib.LoadFromFile(filename);   //加载图像
			if(!m_dib.m_bLoaded)            //判断是否加载图像成功
			{
				AfxMessageBox("图像打不开");
				return;
			}
		}
	Invalidate(1);	//刷新屏幕
}

void CRecognise_yanView::OnRecogniseImage() 
{
	// TODO: Add your command handler code here
	if(!m_dib.m_bLoaded)                         //判断图像是否打开，打开失败，则弹出对话框并退出函数
	{
		AfxMessageBox("opening the image is not success!");
		return;
	}
	int w1=m_dib.GetDIBWidth();  //获取源图像的宽
	int h1=m_dib.GetDIBHeight(); //获取源图像的高
	BYTE* temp=new BYTE[w1*h1];   //开辟临时内存
	memcpy(temp,m_dib.m_pdata,w1*h1); //把源图像复制到临时开辟的temp中
	int thr=150; //定义阀值并赋值为150
	int i,j,k,q,n,m;
	//对原图像每一个像素进行二值化处理
	for(i=0;i<h1;i++) 
		for(j=0;j<w1;j++)
		{
			k=i*w1+j;  //图像第i行、第j列的象素
			if(temp[k]>thr)
				temp[k]=255;
			else
				temp[k]=0;
		}
	char sq[17][10]={"A","2","3","4","5","6","7","8","9","10","J","Q","K","方块","红桃","梅花","黑桃"};//定义每个元素最大可以有8个字节
 
	CString filenames0[17]={"A.bmp","2.bmp","3.bmp","4.bmp","5.bmp","6.bmp","7.bmp","8.bmp","9.bmp","10.bmp","J.bmp",
							"Q.bmp","K.bmp","方块.bmp","红桃.bmp","梅花.bmp","黑桃.bmp"}; //定义模板文件数组
	double MR[17]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};  //初始化最大相似度的值，并赋初值为0
	for(q=0;q<17;q++)
	{
		m_dib.LoadFromFile(filenames0[q]);   //加载图像
		if(!m_dib.m_bLoaded)  //判断模板打开是否成功，没打开则出现对话框，并退出函数
		{
			AfxMessageBox("open the image is error!");
			return;
		}
		int w2=m_dib.GetDIBWidth();  //获取模板图像的宽
		int h2=m_dib.GetDIBHeight(); //获取模板图像的高
		for(i=0;i<h2;i++)             //对原图像每一个像素进行二值化处理
			for(j=0;j<w2;j++)
			{
				k=i*w2+j;             //图像第i行、第j列的象素
				if(m_dib.m_pdata[k]>thr)
					m_dib.m_pdata[k]=255;
				else
					m_dib.m_pdata[k]=0;
			}
		double T=0;
		for(i=0;i<h2;i++)
			for(j=0;j<w2;j++)
			{
				k=i*w2+j;
				T=T+m_dib.m_pdata[k]*m_dib.m_pdata[k];  //计算模板象素的平方和
			}
		double R=0.0;
		for(i=0;i<(2*h1/5)+1-h2;i++)    //扫描行范围(边缘点除外)
		{
			for(j=w1/2;j<w1+1-w2;j++)  //扫描列范围(边缘点除外)
			{
				double ST=0;
				double S=0;
				for(n=0;n<h2;n++)
					for(m=0;m<w2;m++)
					{
						ST=ST+m_dib.m_pdata[n*w2+m]*temp[(i+n)*w1+(j+m)];
						S=S+temp[(i+n)*w1+(j+m)]*temp[(i+n)*w1+(j+m)];
					}
				R=ST/(sqrt(S)*sqrt(T));   //对每个模板计算相似性R
				if(R>MR[q])
					MR[q]=R;
			}
		}
	}
	double R1=0;
	int F;
	for(n=0;n<13;n++)   //判断出纸牌的点数
	{
		if(MR[n]>R1)
		{
			R1=MR[n];
			F=n;
		}
	}
	double R2=0;
	int G;
	for(m=13;m<17;m++)   //判断出纸牌的花式
	{
		if(MR[m]>R2)
		{
			R2=MR[m];
			G=m;
		}
	}
	MessageBox(sq[G],sq[F]); //弹出窗口，显示结果
	return;
	delete temp;
	delete m_dib.m_pdata;
}
