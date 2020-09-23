// PalmView.cpp : implementation of the CPalmView class
//

#include "stdafx.h"
#include "Palm.h"
#include "math.h"
#include "PalmDoc.h"
#include "PalmView.h"

#ifdef _DEBUG
#define new DEBUG_NEW

#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPalmView
double * mbys(double * im,int imW,int imH,double *tp,int tpW,int tpH)
{
	double * out=new double[imW*imH];
	memset(out, 0, imW*imH*sizeof(double));
	int i,j,m,n;
	#define im(ROW,COL) im[imW*(ROW)+(COL)]
	#define tp(ROW,COL) tp[tpW*(ROW)+(COL)]
	#define out(ROW,COL) out[imW*(ROW)+(COL)]
	double a;
	for(i=0;i<imH;i++)
		for(j=0;j<imW;j++)
		{
			a=0;
			//去掉靠近边界的行
			if(i>int(tpH/2) && i<imH-int(tpH/2) && j>int(tpW/2) && j<imW-int(tpW/2))
				for(m=0;m<tpH;m++)
					for(n=0;n<tpW;n++)
					{
						a+=im(i+m-int(tpH/2),j+n-int(tpW/2))*tp(m,n);
					}
			out(i,j)=a;
		}
	return out;
}


IMPLEMENT_DYNCREATE(CPalmView, CView)

BEGIN_MESSAGE_MAP(CPalmView, CView)
	//{{AFX_MSG_MAP(CPalmView)
	ON_COMMAND(ID_Gaosi, OnGaosi)
	ON_COMMAND(ID_WaveLet, OnWaveLet)
	ON_COMMAND(ID_ReWaveLet, OnReWaveLet)
	ON_COMMAND(ID_HARRIS, OnHarris)
	ON_COMMAND(ID_ImToBool, OnImToBool)
	ON_COMMAND(ID_Up, OnUp)
	ON_COMMAND(ID_down, Ondown)
	ON_COMMAND(ID_left, Onleft)
	ON_COMMAND(ID_right, Onright)
	ON_COMMAND(ID_Big, OnBig)
	ON_COMMAND(ID_Small, OnSmall)
	ON_COMMAND(ID_Front, OnFront)
	ON_COMMAND(ID_Back, OnBack)
	ON_COMMAND(ID_Average, OnAverage)
	ON_COMMAND(ID_Alog, OnAlog)
	ON_COMMAND(ID_Sobel_H, OnSobelH)
	ON_COMMAND(ID_Sobel_V, OnSobelV)
	ON_COMMAND(ID_Robert_H, OnRobertH)
	ON_COMMAND(ID_Prewiit_H, OnPrewiitH)
	ON_COMMAND(ID_IsotropicSobel_H, OnIsotropicSobelH)
	ON_COMMAND(ID_Palm_Cur, OnPalmCur)
	ON_COMMAND(ID_PalmROI, OnPalmROI)
	ON_COMMAND(ID_PalmBig, OnPalmBig)
	ON_COMMAND(ID_ROI_PRO, OnRoiPro)
	ON_COMMAND(ID_ROISave, OnROISave)
	ON_COMMAND(ID_Total, OnTotal)
	ON_COMMAND(ID_THIN, OnThin)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPalmView construction/destruction

CPalmView::CPalmView()
{
	// TODO: add construction code here
	value=15;
	corn_v=2;
}

CPalmView::~CPalmView()
{
}

BOOL CPalmView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPalmView drawing

void CPalmView::OnDraw(CDC* pDC)
{
	CPalmDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(pDoc->m_hDIB == NULL)
	return ;
	// TODO: add draw code for native data here
	int i,j;
    unsigned char *lpSrc;
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->m_hDIB);
	int cxDIB = (int) ::DIBWidth(lpDIB);         // Size of DIB - x
	int cyDIB = (int) ::DIBHeight(lpDIB);        // Size of DIB - y
	LPSTR lpDIBBits=::FindDIBBits (lpDIB);
	// 计算图像每行的字节数
	long lLineBytes = WIDTHBYTES(cxDIB * 8);
	// 每行
	for(i = 0; i < cyDIB; i++)
	{
		// 每列
		for(j = 0; j < cxDIB; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (cyDIB - 1 - i) + j;
			// 计算新的灰度值
			//*(lpSrc) = BYTE(255-*lpSrc);
		}
	}
	::GlobalUnlock((HGLOBAL) pDoc->m_hDIB);
	CRect rect(0,0,cxDIB,cyDIB), rcDIB(0,0,cxDIB,cyDIB);
	::PaintDIB(pDC->m_hDC, &rect, pDoc->m_hDIB, &rcDIB, pDoc->m_palDIB);

	
	#define corner(ROW,COL) corner[cxDIB*(ROW)+(COL)]
	
	CPen* pPenRed = new CPen;
	pPenRed->CreatePen(PS_SOLID,1,RGB(255,0,0));

	
	pDC->SelectObject(pPenRed);
	for(i = 0; i < cyDIB; i++)
	{
		for(j = 0; j < cxDIB; j++)
		{		if(pDoc->harris)
				{
					if(pDoc->corner(i,j))
					{
					//在角点处划十字叉以标注
					
					pDC->MoveTo (j-5,i);
					pDC->LineTo (j+6,i);
					pDC->MoveTo (j,i-5);
					pDC->LineTo (j,i+6);
					pDC->MoveTo (j-5,i+1);
					pDC->LineTo (j+6,i+1);
					pDC->MoveTo (j+1,i-5);
					pDC->LineTo (j+1,i+6);
					}
				}
		}
	}





	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CPalmView printing

BOOL CPalmView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPalmView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPalmView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPalmView diagnostics

#ifdef _DEBUG
void CPalmView::AssertValid() const
{
	CView::AssertValid();
}

void CPalmView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPalmDoc* CPalmView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPalmDoc)));
	return (CPalmDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPalmView message handlers

void CPalmView::OnGaosi() 
{
	// TODO: Add your command handler code here
	CPalmDoc* pDoc = GetDocument();

	//设定模板参数
	double tem[9]={1,2,1,
		           2,4,2,
				   1,2,1};

    //设定模板系数
    double  xishu = 0.0625;   

    //进行模板操作
	pDoc->m_hDIB =::Template(pDoc->m_hDIB,tem ,3,3, xishu);

	Invalidate(TRUE);
}



void CPalmView::OnWaveLet() 
{
	// TODO: Add your command handler code here
	  int i,j;
	int ii;
	unsigned char *lpSrc;
	CPalmDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(pDoc->m_hDIB == NULL)
		return ;
	double tmp;
	//copy image into imagematrix and then recopy it from imagematrix 
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->m_hDIB);
	LPSTR lpDIBBits=::FindDIBBits (lpDIB);
	int cxDIB = (int) ::DIBWidth(lpDIB);         // Size of DIB - x
	int cyDIB = (int) ::DIBHeight(lpDIB);        // Size of DIB - y
	long lLineBytes = WIDTHBYTES(cxDIB * 8);     // 计算图像每行的字节数
	double* imagematrix=new double[cyDIB*cxDIB];
	// 每行
	for(i = 0; i < cyDIB; i++)
	{
		// 每列
		for(j = 0; j < cxDIB; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (cyDIB - 1 - i) + j;
			
			imagematrix[i+cxDIB*j]=*lpSrc;
		}
	}
    
	//then we begin harr decompose in 1_D ,rowwisely////
	for(i=0;i<cyDIB;i++)
		decomposition(imagematrix+i*cxDIB,
		imagematrix+i*cxDIB, 
		imagematrix+i*cxDIB+cxDIB/2,
		cxDIB,1);
    //image transpose to make row transformation
    for (i = 1; i < cxDIB; i++) 
	{ 
		
		ii = i*cxDIB;
		
		for (j = 0; j < i; j++) 
		{
			
			tmp =imagematrix[ii+j];
			
			imagematrix[ii+j] = imagematrix[j*cxDIB+i];
			
			imagematrix[j*cxDIB+i] = tmp;
		}
	}
    
    //begining to rowwise transformation
	for (i = 0; i < cxDIB; i++)   /* columnwise reconstruction */
		decomposition(imagematrix+i*cxDIB,
		imagematrix+i*cxDIB, 
		imagematrix+i*cxDIB+cxDIB/2,
		cxDIB,1);
	
	//another transpose to restore the orginal configuration
	for (i = 1; i < cyDIB; i++) 
	{   		
		ii = i*cxDIB;
		
		for (j = 0; j < i; j++) 
		{
			
			tmp = imagematrix[ii+j];
			
			imagematrix[ii+j] = imagematrix[j*cxDIB+i];
			
			imagematrix[j*cxDIB+i] = tmp;
			
		}
		
	}
	
	//endowing values from imagematrix to lpSrc
	//the upperleft part of the image
    for(i = 0; i < cyDIB/2; i++)//每行
	{
		// 每列
		for(j = 0; j < cxDIB/2; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (cyDIB - 1 - i) + j;
            *lpSrc=(unsigned char)imagematrix[i+cxDIB*j];
		}
	}
	
	//the leftbottom part of the image
	for(i=cxDIB/2;i<cxDIB;i++)
		for(j=0;j<cyDIB/2;j++){
			lpSrc=(unsigned char*)lpDIBBits+lLineBytes*(cyDIB-1-i)+j;
			*lpSrc=int(imagematrix[i+cxDIB*j]+128);
		}
		
		//the right part of the image
		for(i=0;i<cxDIB;i++)
			for(j=cyDIB/2;j<cyDIB;j++)
			{
				lpSrc=(unsigned char*)lpDIBBits+lLineBytes*(cyDIB-1-i)+j;
				*lpSrc=int(imagematrix[i+cxDIB*j]+128);
			}	
			
			::GlobalUnlock((HGLOBAL) pDoc->m_hDIB);
			Invalidate(TRUE);
}

void CPalmView::OnReWaveLet() 
{
	// TODO: Add your command handler code here
	 int i,j;
    int ii;
    unsigned char *lpSrc;
    double tmp;
	CPalmDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(pDoc->m_hDIB == NULL)
		return ;
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->m_hDIB);
	LPSTR lpDIBBits=::FindDIBBits (lpDIB);
	int cxDIB = (int) ::DIBWidth(lpDIB);         // Size of DIB - x
	int cyDIB = (int) ::DIBHeight(lpDIB);
	const int N=cxDIB*cyDIB;
	long lLineBytes = WIDTHBYTES(cxDIB * 8);     // 计算图像每行的字节数
	double* imagematrix=new double[cyDIB*cxDIB];
	//endowing values from lpSrc to Imagematrix
	//the upperleft part of the image
    for(i = 0; i < cyDIB/2; i++)//每行
	{
		// 每列
		for(j = 0; j < cxDIB/2; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (cyDIB - 1 - i) + j;
			imagematrix[i+cxDIB*j]=*lpSrc;
		}
	}
	
	//the leftbottom part of the image
	for(i=cxDIB/2;i<cxDIB;i++)
		for(j=0;j<cyDIB/2;j++)
		{
			lpSrc=(unsigned char*)lpDIBBits+lLineBytes*(cyDIB-1-i)+j;
			imagematrix[i+cxDIB*j]=*lpSrc-128;
		}
		
		//the right part of the image
		for(i=0;i<cxDIB;i++)
			for(j=cyDIB/2;j<cyDIB;j++)
			{
				lpSrc=(unsigned char*)lpDIBBits+lLineBytes*(cyDIB-1-i)+j;
				imagematrix[i+cxDIB*j]=*lpSrc-128;
			}
			
			
			//beginning reconstruction
			//do wavelet reconstruction
			for (i = 0; i < cxDIB; i++)   // columnwise reconstruction /
				
				reconstruction(imagematrix+i*cxDIB,imagematrix+i*cxDIB, 
				imagematrix+i*cxDIB+cxDIB/2, cxDIB/2,1);
			
			//image transpose to make rowwise construction
			for (i = 1; i < cxDIB; i++) 
			{ 
				
				ii = i*cxDIB;
				
				for (j = 0; j < i; j++) 
				{
					
					tmp =imagematrix[ii+j];
					
					imagematrix[ii+j] = imagematrix[j*cxDIB+i];
					
					imagematrix[j*cxDIB+i] = tmp;
				}
			}
			
			//rowwise reconstruction
			for (i = 0; i < cxDIB; i++)   				
				reconstruction(imagematrix+i*cxDIB,imagematrix+i*cxDIB, 
				imagematrix+i*cxDIB+cxDIB/2, cxDIB/2,1);
			
			//transpose again then endowing values to the souce pointers
			for (i = 1; i < cxDIB; i++) 
			{ 
				
				ii = i*cxDIB;
				
				for (j = 0; j < i; j++) 
				{
					
					tmp =imagematrix[ii+j];
					
					imagematrix[ii+j] = imagematrix[j*cxDIB+i];
					
					imagematrix[j*cxDIB+i] = tmp;
				}
			}
			
            //mapping imagematrix from 0-255
			for(i = 0; i < cyDIB; i++)
				// 每列
				for(j = 0; j < cxDIB; j++)
				{
					if(imagematrix[i+cxDIB*j]<0)
						imagematrix[i+cxDIB*j]=0;
					else
						if(imagematrix[i+cxDIB*j]>255)
							imagematrix[i+cxDIB*j]=255;
				}
				
				//endowing values from imagematrix to lpSrc
				for(i = 0; i < cyDIB; i++)
					// 每列
					for(j = 0; j < cxDIB; j++)
					{
						// 指向DIB第i行，第j个象素的指针
						lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (cyDIB - 1 - i) + j;
						*lpSrc=int(imagematrix[i+cxDIB*j]);
						
					}
					
					::GlobalUnlock((HGLOBAL) pDoc->m_hDIB);
					Invalidate(TRUE);
}

void CPalmView::OnHarris() 
{
	// TODO: Add your command handler code here
	CPalmDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	MessageBox("front");
	if(pDoc->m_hDIB == NULL)
		return ;
	MessageBox("after");
    pDoc->harris=true;

	
	int i,j,m,n,size,thresh,gausswidth;
	double sigma;

	//输入四个参数
	
	gausswidth =5;
	sigma =0.8;
	size =5;
	thresh =700;
	
    unsigned char *lpSrc;//一个指向源、目的像素的移动指针
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->m_hDIB);
	int cxDIB = (int) ::DIBWidth(lpDIB);         // 图像宽度
	int cyDIB = (int) ::DIBHeight(lpDIB);        // 图像高度
	LPSTR lpDIBBits=::FindDIBBits (lpDIB);
	long lLineBytes = WIDTHBYTES(cxDIB * 8);     // 计算灰度图像每行的字节数

	//创建I、Ix、Ix2、Iy、Iy2、Ixy、cim、mx、corner数组
	double *I=new double[cxDIB*cyDIB];
	double *Ix=new double[cxDIB*cyDIB];
	double *Ix2=new double[cxDIB*cyDIB];
	double *Iy=new double[cxDIB*cyDIB];
	double *Iy2=new double[cxDIB*cyDIB];
	double *Ixy=new double[cxDIB*cyDIB];
	double *cim=new double[cxDIB*cyDIB];
	double *mx=new double[cxDIB*cyDIB];

	pDoc->corner=new bool[cxDIB*cyDIB];
	memset(pDoc->corner, 0, cxDIB*cyDIB*sizeof(bool));

	//定义宏以方便访问元素
	#define I(ROW,COL) I[cxDIB*(ROW)+(COL)]
	#define Ix(ROW,COL) Ix[cxDIB*(ROW)+(COL)]
	#define Ix2(ROW,COL) Ix2[cxDIB*(ROW)+(COL)]
	#define Iy(ROW,COL) Iy[cxDIB*(ROW)+(COL)]
	#define Iy2(ROW,COL) Iy2[cxDIB*(ROW)+(COL)]
	#define Ixy(ROW,COL) Ixy[cxDIB*(ROW)+(COL)]
	#define cim(ROW,COL) cim[cxDIB*(ROW)+(COL)]
	#define mx(ROW,COL) mx[cxDIB*(ROW)+(COL)]
	#define corner(ROW,COL) corner[cxDIB*(ROW)+(COL)]

	//将图像灰度值复制到I中，这步很重要！想想为什么？
	for(i = 0; i < cyDIB; i++)
	{
		for(j = 0; j < cxDIB; j++)
		{			
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (cyDIB - 1 - i) + j;
			//将256级灰度图像转化为double型
			I(i,j)=double(*lpSrc);
		}
	}


	//--------------------------------------------------------------------------
	//                     第一步：利用差分算子对图像进行滤波
	//--------------------------------------------------------------------------
	
	//定义水平方向差分算子并求Ix
	double dx[9]={-1,0,1,-1,0,1,-1,0,1};
	Ix=mbys(I,cxDIB,cyDIB,dx,3,3);

	//定义垂直方向差分算子并求Iy
	double dy[9]={-1,-1,-1,0,0,0,1,1,1};
	Iy=mbys(I,cxDIB,cyDIB,dy,3,3);

	
	//将中间结果Ix写入到文本文件以便后续分析
	FILE *fp;
	fp=fopen("Ix.txt","wr");
	for(i = 0; i < cyDIB; i++)
	{
		for(j = 0; j < cxDIB; j++)
			fprintf(fp,"%x ",Ix(i,j));
		fprintf(fp,"\n");
	}
	fp=fopen("Iy.txt","wr");
	for(i = 0; i < cyDIB; i++)
	{
		for(j = 0; j < cxDIB; j++)
			fprintf(fp,"%f ",Iy(i,j));
		fprintf(fp,"\n");
	}
	

	//计算Ix2、Iy2、Ixy
	for(i = 0; i < cyDIB; i++)
	{
		for(j = 0; j < cxDIB; j++)
		{	Ix2(i,j)=Ix(i,j)*Ix(i,j);
			Iy2(i,j)=Iy(i,j)*Iy(i,j);
			Ixy(i,j)=Ix(i,j)*Iy(i,j);
		}
	}


	//--------------------------------------------------------------------------
	//                  第二步：对Ix2/Iy2/Ixy进行高斯平滑，以去除噪声
	//--------------------------------------------------------------------------
	
	//本例中使用5×5的高斯模板
	//计算模板参数
	double *g=new double[gausswidth*gausswidth];
	for(i=0;i<gausswidth;i++)
		for(j=0;j<gausswidth;j++)
			g[i*gausswidth+j]=exp(-((i-int(gausswidth/2))*(i-int(gausswidth/2))+(j-int(gausswidth/2))*(j-int(gausswidth/2)))/(2*sigma));
	
	//归一化：使模板参数之和为1（其实此步可以省略）
	double total=0;
	for(i=0;i<gausswidth*gausswidth;i++)
		total+=g[i];
	for(i=0;i<gausswidth;i++)
		for(j=0;j<gausswidth;j++)
		{	g[i*gausswidth+j]/=total;}
	
	fp=fopen("g.txt","w+");
	for(i = 0; i < gausswidth; i++)
	{
		for(j = 0; j < gausswidth; j++)
			fprintf(fp,"%f ",g[i*gausswidth+j]);
		fprintf(fp,"\n");
	}
		
	//进行高斯平滑
	Ix2=mbys(Ix2,cxDIB,cyDIB,g,gausswidth,gausswidth);
	Iy2=mbys(Iy2,cxDIB,cyDIB,g,gausswidth,gausswidth);
	Ixy=mbys(Ixy,cxDIB,cyDIB,g,gausswidth,gausswidth);
	

	//--------------------------------------------------------------------------
	//                        第三步：计算角点量
	//--------------------------------------------------------------------------
	
	//计算cim：即cornerness of image，我们把它称做‘角点量’
	for(i = 0; i < cyDIB; i++)
	{
		for(j = 0; j < cxDIB; j++)
		{
			//注意：要在分母中加入一个极小量以防止除数为零溢出
			cim(i,j) = (Ix2(i,j)*Iy2(i,j) - Ixy(i,j)*Ixy(i,j))/(Ix2(i,j) + Iy2(i,j) + 0.000001); 
		}
	}
	fp=fopen("cim.txt","w+");
	for(i = 0; i < cyDIB; i++)
	{
		for(j = 0; j < cxDIB; j++)
			fprintf(fp,"%f ",cim(i,j));
		fprintf(fp,"\n");
	}	

	//--------------------------------------------------------------------------
	//                 第四步：进行局部非极大值抑制以获得最终角点
	//--------------------------------------------------------------------------
	
	//注意进行局部极大值抑制的思路

	//const double size=7;
	double max;
	//对每个点在邻域内做极大值滤波：即将该点的值设为邻域中最大的那个值（跟中值滤波有点类似）
	for(i = 0; i < cyDIB; i++)
	{
		for(j = 0; j < cxDIB; j++)
		{
			max=-1000000;
			if(i>int(size/2) && i<cyDIB-int(size/2) && j>int(size/2) && j<cxDIB-int(size/2))
				for(m=0;m<size;m++)
				{
					for(n=0;n<size;n++)
						{						
							if(cim(i+m-int(size/2),j+n-int(size/2))>max)
								max=cim(i+m-int(size/2),j+n-int(size/2));
						}
				}
			if(max>0)
				mx(i,j)=max;
			else
				mx(i,j)=0;
		}
	}

	//最终确定角点
	//const double thresh=4500;
	int temp_y=0,temp_x=0;
	double temp;
	
	for(i = 0; i < cyDIB; i++)	
	{
		for(j = 0; j < cxDIB; j++)
	
		{	
			if(cim(i,j)==mx(i,j))  //首先取得局部极大值
					if(mx(i,j)>thresh&&j>5)  //然后大于这个阈值
					{	
					 	temp=(j-temp_y)*(j-temp_y)+(i-temp_x)*(i-temp_x);
					//	if(temp>2000)
					//	{
						pDoc->corner(i,j)=1;   //满足上两个条件，才是角点！
					//	temp_y=j;
					//	temp_x=i;
					//	}
					}
		}
	}
	fp=fopen("corner.txt","w+");
	for(i = 0; i < cyDIB; i++)
	{
		for(j = 0; j < cxDIB; j++)
			fprintf(fp,"%d ",pDoc->corner(i,j));
		fprintf(fp,"\n");
	}
	

	::GlobalUnlock((HGLOBAL) pDoc->m_hDIB); 	
    //UpdateAllViews(NULL, 0, NULL);	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	#define corner(ROW,COL) corner[cxDIB*(ROW)+(COL)]





	
	
	
	





Invalidate(TRUE);
}

void CPalmView::OnImToBool() 
{
	// TODO: Add your command handler code here
	int i,j;
    unsigned char *lpSrc;
	CPalmDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(pDoc->m_hDIB == NULL)
		return ;
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->m_hDIB);
	LPSTR lpDIBBits=::FindDIBBits (lpDIB);
	int cxDIB = (int) ::DIBWidth(lpDIB);         // Size of DIB - x
	int cyDIB = (int) ::DIBHeight(lpDIB);        // Size of DIB - y
	long lLineBytes = WIDTHBYTES(cxDIB * 8);     // 计算图像每行的字节数
	const float c1=150,c2=2.5;
	// 每行
	for(i = 0; i < cyDIB; i++)
	{
		// 每列
		for(j = 0; j < cxDIB; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (cyDIB - 1 - i) + j;
			
			// 计算新的灰度值
			if(*lpSrc<100) *lpSrc=BYTE(0);
			else *lpSrc = BYTE(255);
		}
	}
	::GlobalUnlock((HGLOBAL) pDoc->m_hDIB);
    Invalidate(TRUE);
}

void CPalmView::OnUp() 
{
	// TODO: Add your command handler code here
		CPalmDoc* pDoc = GetDocument();
	
	// 指向DIB的指针
	LPSTR	lpDIB;

	// 指向DIB象素指针
	LPSTR   lpDIBBits;
	
	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->m_hDIB);
	
	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的平移，其它的可以类推）
	if (::DIBNumColors(lpDIB) != 256)
	{
		// 提示用户
		MessageBox("目前只支持256色位图的平移！", "系统提示" , MB_ICONINFORMATION | MB_OK);

		// 解除锁定
		::GlobalUnlock((HGLOBAL) pDoc->m_hDIB);
		
		// 返回
		return;
	}
	
	LONG lXOffset;
	LONG lYOffset;
	
		
	// 平移量
	lXOffset = -value;
	lYOffset = 0;

	
	// 更改光标形状
	BeginWaitCursor();

	// 找到DIB图像象素起始位置
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// 调用TranslationDIB()函数平移DIB
	if (TranslationDIB(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB), lXOffset, lYOffset))
	{
		
		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox("分配内存失败！", "系统提示" , MB_ICONINFORMATION | MB_OK);
	}
	
	// 解除锁定
	::GlobalUnlock((HGLOBAL) pDoc->m_hDIB);

	// 恢复光标
	EndWaitCursor();
}

void CPalmView::Ondown() 
{
	// TODO: Add your command handler code here
			CPalmDoc* pDoc = GetDocument();
	
	// 指向DIB的指针
	LPSTR	lpDIB;

	// 指向DIB象素指针
	LPSTR   lpDIBBits;
	
	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->m_hDIB);
	
	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的平移，其它的可以类推）
	if (::DIBNumColors(lpDIB) != 256)
	{
		// 提示用户
		MessageBox("目前只支持256色位图的平移！", "系统提示" , MB_ICONINFORMATION | MB_OK);

		// 解除锁定
		::GlobalUnlock((HGLOBAL) pDoc->m_hDIB);
		
		// 返回
		return;
	}
	
	LONG lXOffset;
	LONG lYOffset;
	
		
	// 平移量
	lXOffset = value;
	lYOffset = 0;

	
	// 更改光标形状
	BeginWaitCursor();

	// 找到DIB图像象素起始位置
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// 调用TranslationDIB()函数平移DIB
	if (TranslationDIB(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB), lXOffset, lYOffset))
	{
		
		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox("分配内存失败！", "系统提示" , MB_ICONINFORMATION | MB_OK);
	}
	
	// 解除锁定
	::GlobalUnlock((HGLOBAL) pDoc->m_hDIB);

	// 恢复光标
	EndWaitCursor();
}

void CPalmView::Onleft() 
{
	// TODO: Add your command handler code here
			CPalmDoc* pDoc = GetDocument();
	
	// 指向DIB的指针
	LPSTR	lpDIB;

	// 指向DIB象素指针
	LPSTR   lpDIBBits;
	
	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->m_hDIB);
	
	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的平移，其它的可以类推）
	if (::DIBNumColors(lpDIB) != 256)
	{
		// 提示用户
		MessageBox("目前只支持256色位图的平移！", "系统提示" , MB_ICONINFORMATION | MB_OK);

		// 解除锁定
		::GlobalUnlock((HGLOBAL) pDoc->m_hDIB);
		
		// 返回
		return;
	}
	
	LONG lXOffset;
	LONG lYOffset;
	
		
	// 平移量
	lXOffset = 0;
	lYOffset = -value;

	
	// 更改光标形状
	BeginWaitCursor();

	// 找到DIB图像象素起始位置
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// 调用TranslationDIB()函数平移DIB
	if (TranslationDIB(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB), lXOffset, lYOffset))
	{
		
		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox("分配内存失败！", "系统提示" , MB_ICONINFORMATION | MB_OK);
	}
	
	// 解除锁定
	::GlobalUnlock((HGLOBAL) pDoc->m_hDIB);

	// 恢复光标
	EndWaitCursor();
}

void CPalmView::Onright() 
{
	// TODO: Add your command handler code here
			CPalmDoc* pDoc = GetDocument();
	
	// 指向DIB的指针
	LPSTR	lpDIB;

	// 指向DIB象素指针
	LPSTR   lpDIBBits;
	
	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->m_hDIB);
	
	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的平移，其它的可以类推）
	if (::DIBNumColors(lpDIB) != 256)
	{
		// 提示用户
		MessageBox("目前只支持256色位图的平移！", "系统提示" , MB_ICONINFORMATION | MB_OK);

		// 解除锁定
		::GlobalUnlock((HGLOBAL) pDoc->m_hDIB);
		
		// 返回
		return;
	}
	
	LONG lXOffset;
	LONG lYOffset;
	
		
	// 平移量
	lXOffset = 0;
	lYOffset = value;

	
	// 更改光标形状
	BeginWaitCursor();

	// 找到DIB图像象素起始位置
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// 调用TranslationDIB()函数平移DIB
	if (TranslationDIB(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB), lXOffset, lYOffset))
	{
		
		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox("分配内存失败！", "系统提示" , MB_ICONINFORMATION | MB_OK);
	}
	
	// 解除锁定
	::GlobalUnlock((HGLOBAL) pDoc->m_hDIB);

	// 恢复光标
	EndWaitCursor();
}

void CPalmView::OnBig() 
{
	// TODO: Add your command handler code here
		CPalmDoc* pDoc = GetDocument();
	
	// 指向DIB的指针
	LPSTR lpDIB;
	
	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->m_hDIB);
	
	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的缩放，其它的可以类推）
	if (::DIBNumColors(lpDIB) != 256)
	{
		// 提示用户
		MessageBox("目前只支持256色位图的缩放！", "系统提示" , MB_ICONINFORMATION | MB_OK);

		// 解除锁定
		::GlobalUnlock((HGLOBAL) pDoc->m_hDIB);
		
		// 返回
		return;
	}
	
	// 缩放比率
	float fXZoomRatio;
	float fYZoomRatio;

	//缩放量
	fXZoomRatio = 1.25;
	fYZoomRatio = 1.25;

	
	// 创建新DIB
	HDIB hNewDIB = NULL;
	
	// 更改光标形状
	BeginWaitCursor();
	
	// 调用ZoomDIB()函数转置DIB
	hNewDIB = (HDIB) ZoomDIB(lpDIB, fXZoomRatio, fYZoomRatio);
	
	// 判断缩放是否成功
	if (hNewDIB != NULL)
	{
		
		// 替换DIB，同时释放旧DIB对象
		pDoc->ReplaceHDIB(hNewDIB);

		// 更新DIB大小和调色板
		pDoc->InitDIBData();
		
		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);
		
		// 重新设置滚动视图大小
//		SetScrollSizes(MM_TEXT, pDoc->GetDocSize());

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox("分配内存失败！", "系统提示" , MB_ICONINFORMATION | MB_OK);
	}
	
	// 解除锁定
	::GlobalUnlock((HGLOBAL) pDoc->m_hDIB);

	// 恢复光标
	EndWaitCursor();
}

void CPalmDoc::ReplaceHDIB(HDIB hDIB)
{
	// 替换DIB，在功能粘贴中用到该函数
	
	// 判断DIB是否为空
	if (m_hDIB != NULL)
	{
		// 非空，则清除
		::GlobalFree((HGLOBAL) m_hDIB);
	}

	// 替换成新的DIB对象
	m_hDIB = hDIB;
	
}

void CPalmView::OnSmall() 
{
	// TODO: Add your command handler code here
	CPalmDoc* pDoc = GetDocument();
	
	// 指向DIB的指针
	LPSTR lpDIB;
	
	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->m_hDIB);
	
	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的缩放，其它的可以类推）
	if (::DIBNumColors(lpDIB) != 256)
	{
		// 提示用户
		MessageBox("目前只支持256色位图的缩放！", "系统提示" , MB_ICONINFORMATION | MB_OK);

		// 解除锁定
		::GlobalUnlock((HGLOBAL) pDoc->m_hDIB);
		
		// 返回
		return;
	}
	
	// 缩放比率
	float fXZoomRatio;
	float fYZoomRatio;

	//缩放量
	fXZoomRatio = 0.8;
	fYZoomRatio = 0.8;

	
	// 创建新DIB
	HDIB hNewDIB = NULL;
	
	// 更改光标形状
	BeginWaitCursor();
	
	// 调用ZoomDIB()函数转置DIB
	hNewDIB = (HDIB) ZoomDIB(lpDIB, fXZoomRatio, fYZoomRatio);
	
	// 判断缩放是否成功
	if (hNewDIB != NULL)
	{
		
		// 替换DIB，同时释放旧DIB对象
		pDoc->ReplaceHDIB(hNewDIB);

		// 更新DIB大小和调色板
		pDoc->InitDIBData();
		
		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);
		
		// 重新设置滚动视图大小
//		SetScrollSizes(MM_TEXT, pDoc->GetDocSize());

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox("分配内存失败！", "系统提示" , MB_ICONINFORMATION | MB_OK);
	}
	
	// 解除锁定
	::GlobalUnlock((HGLOBAL) pDoc->m_hDIB);

	// 恢复光标
	EndWaitCursor();
}

void CPalmView::OnFront() 
{
	// TODO: Add your command handler code here
		CPalmDoc* pDoc = GetDocument();
	
	// 指向DIB的指针
	LPSTR lpDIB;
	
	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->m_hDIB);
	
	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的旋转，其它的可以类推）
	if (::DIBNumColors(lpDIB) != 256)
	{
		// 提示用户
		MessageBox("目前只支持256色位图的旋转！", "系统提示" , MB_ICONINFORMATION | MB_OK);

		// 解除锁定
		::GlobalUnlock((HGLOBAL)  pDoc->m_hDIB);
		
		// 返回
		return;
	}
	
	// 旋转角度
	int iRotateAngle;
	
	iRotateAngle=corn_v;
	
	// 创建新DIB
	HDIB hNewDIB = NULL;
	
	// 更改光标形状
	BeginWaitCursor();
	
	// 调用RotateDIB()函数旋转DIB
	hNewDIB = (HDIB) RotateDIB(lpDIB, iRotateAngle);
	
	// 判断旋转是否成功
	if (hNewDIB != NULL)
	{
		
		// 替换DIB，同时释放旧DIB对象
		pDoc->ReplaceHDIB(hNewDIB);

		// 更新DIB大小和调色板
		pDoc->InitDIBData();
		
		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);
		
		// 重新设置滚动视图大小
	//	SetScrollSizes(MM_TEXT, pDoc->GetDocSize());
		
		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox("分配内存失败！", "系统提示" , MB_ICONINFORMATION | MB_OK);
	}
	
	// 解除锁定
	::GlobalUnlock((HGLOBAL)  pDoc->m_hDIB);

	// 恢复光标
	EndWaitCursor();
}

void CPalmView::OnBack() 
{
	// TODO: Add your command handler code here
		CPalmDoc* pDoc = GetDocument();
	
	// 指向DIB的指针
	LPSTR lpDIB;
	
	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->m_hDIB);
	
	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的旋转，其它的可以类推）
	if (::DIBNumColors(lpDIB) != 256)
	{
		// 提示用户
		MessageBox("目前只支持256色位图的旋转！", "系统提示" , MB_ICONINFORMATION | MB_OK);

		// 解除锁定
		::GlobalUnlock((HGLOBAL)pDoc->m_hDIB);
		
		// 返回
		return;
	}
	
	// 旋转角度
	int iRotateAngle;
	
	iRotateAngle=-corn_v;
	
	// 创建新DIB
	HDIB hNewDIB = NULL;
	
	// 更改光标形状
	BeginWaitCursor();
	
	// 调用RotateDIB()函数旋转DIB
	hNewDIB = (HDIB) RotateDIB(lpDIB, iRotateAngle);
	
	// 判断旋转是否成功
	if (hNewDIB != NULL)
	{
		
		// 替换DIB，同时释放旧DIB对象
		pDoc->ReplaceHDIB(hNewDIB);

		// 更新DIB大小和调色板
		pDoc->InitDIBData();
		
		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);
		
		// 重新设置滚动视图大小
	//	SetScrollSizes(MM_TEXT, pDoc->GetDocSize());
		
		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox("分配内存失败！", "系统提示" , MB_ICONINFORMATION | MB_OK);
	}
	
	// 解除锁定
	::GlobalUnlock((HGLOBAL) pDoc->m_hDIB);

	// 恢复光标
	EndWaitCursor();
}

void CPalmView::OnAverage() 
{
	// TODO: Add your command handler code here
	CPalmDoc* pDoc = GetDocument();

	//进行中值滤波
	pDoc->m_hDIB =MidFilter(pDoc->m_hDIB,3,3);

	Invalidate(TRUE);
}

void CPalmView::OnAlog() 
{
	// TODO: Add your command handler code here
		CPalmDoc* pDoc = GetDocument();

	//设定模板参数
	double tem[9]={1,1,1,
		           1,1,1,
				   1,1,1};

    //设定模板系数
    double  xishu = 0.111;   

    //进行模板操作
	pDoc->m_hDIB =::Template(pDoc->m_hDIB,tem ,3,3, xishu);

	Invalidate(TRUE);
}

void CPalmView::OnSobelH() 
{
	// TODO: Add your command handler code here
		CPalmDoc* pDoc = GetDocument();

	//设定模板参数
	double tem[9]={-1.0f,-1.0f,-1.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f};

    //设定模板系数
    double  xishu = 1;   

    //进行模板操作
	pDoc->m_hDIB =::Template(pDoc->m_hDIB,tem ,3,3, xishu);

	Invalidate(TRUE);
}

void CPalmView::OnSobelV() 
{
	// TODO: Add your command handler code here
		//设定模板参数
CPalmDoc* pDoc = GetDocument();

	//设定模板参数
	double tem[9]={-1.0f,0.0f,1.0f,-2.0f,0.0f,2.0f,-1.0f,0.0f,1.0f};

    //设定模板系数
    double  xishu = 1;   

    //进行模板操作
	pDoc->m_hDIB =::Template(pDoc->m_hDIB,tem ,3,3, xishu);

	Invalidate(TRUE);
}

void CPalmView::OnRobertH() 
{
	// TODO: Add your command handler code here
	CPalmDoc* pDoc = GetDocument();

	//设定模板参数
	double tem[4]={0,1,-1,0};

    //设定模板系数
    double  xishu = 1;   

    //进行模板操作
	pDoc->m_hDIB =::Template(pDoc->m_hDIB,tem ,2,2, xishu);

	Invalidate(TRUE);	
}

void CPalmView::OnPrewiitH() 
{
	// TODO: Add your command handler code here
	CPalmDoc* pDoc = GetDocument();

	//设定模板参数
	double tem[9]={-1.0f,-1.0f,-1.0f,0,0.0f,0.0f,1.0f,1.0f,1.0f};

    //设定模板系数
    double  xishu = 1;   

    //进行模板操作
	pDoc->m_hDIB =::Template(pDoc->m_hDIB,tem ,3,3, xishu);

	Invalidate(TRUE);
}

void CPalmView::OnIsotropicSobelH() 
{
	// TODO: Add your command handler code here
	
		CPalmDoc* pDoc = GetDocument();

	//设定模板参数
	double tem[9]={-1.0f,-1.4142f,-1.0f,0.0f,0.0f,0.0f,1.0f,1.4142f,1.0f};

    //设定模板系数
    double  xishu = 1;   

    //进行模板操作
	pDoc->m_hDIB =::Template(pDoc->m_hDIB,tem ,3,3, xishu);

	Invalidate(TRUE);	

}

void CPalmView::OnPalmCur() 
{
	// TODO: Add your command handler code here
  //  this->OnGray();
	CPalmDoc* pDoc = GetDocument();
	pDoc->OnGray();

	this->OnGaosi();
	this->OnAverage();
	this->OnHarris();
}

void CPalmView::OnPalmROI() 
{
	// TODO: Add your command handler code here
		CPalmDoc* pDoc = GetDocument();
	
		
		unsigned char *lpSrc;//一个指向源、目的像素的移动指针
		LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->m_hDIB);
		int cxDIB = (int) ::DIBWidth(lpDIB);         // 图像宽度
		int cyDIB = (int) ::DIBHeight(lpDIB);        // 图像高度
		int i,j,k=0;
		CPoint temp[10];	
		
		CPen* pPenRed = new CPen;
		pPenRed->CreatePen(PS_SOLID,1,RGB(255,0,0));
		CDC *pDC=this->GetDC();
		pDC->SelectObject(pPenRed);
		
		for(i=0;i<cxDIB;i++)
			for(j=0;j<cyDIB;j++)
			{
			   if(pDoc->corner(i,j))
			   {
				temp[k].x=j;
				temp[k].y=i;
				k++;
			   }			
			
			}
		pDC->MoveTo(temp[1]);
	pDC->LineTo(temp[2]);
		
		double splot_x[10],splot_y[10];
		double k1,b1,k2,b2,a,b,c,O,k3,b3,k4,b4;
		splot_x[0]= temp[0].x;
		splot_x[1]= temp[1].x;//top
		splot_x[2]= temp[2].x;
		splot_y[0]= temp[0].y;
		splot_y[1]= temp[1].y;
		splot_y[2]= temp[2].y;
		
		k1=(splot_y[1]-splot_y[2])/(splot_x[1]-splot_x[2]);
		
		
		temp[1].x=(temp[1].x+temp[2].x)/2;
		temp[1].y=(temp[1].y+temp[2].y)/2;

		splot_x[3]=temp[1].x;
		splot_y[3]=temp[1].y;//middle splot

		pDC->MoveTo(temp[0]);
		pDC->LineTo(temp[1]);


        k2=(splot_y[3]-splot_y[0])/(splot_x[3]-splot_x[0]);
		b2=splot_y[3]-k2*splot_x[3];
		
		
		temp[2].y=cyDIB;
		temp[2].x=(temp[2].y-b2)/k2;
	//		pDC->MoveTo(temp[1]);
   //	pDC->LineTo(temp[2]);
		
		O=((splot_x[1]-splot_x[2])*(splot_x[1]-splot_x[2])+(splot_y[1]-splot_y[2])*(splot_y[1]-splot_y[2]));


		a=1+k2*k2;
		b=2*k2*(b2-splot_y[3])-2*splot_x[3];
		c=splot_x[3]*splot_x[3]+(b2-splot_y[3])*(b2-splot_y[3])-O/2;

		
		double delta;
		delta=b*b-4*a*c;
		double x1;
		double x2;
		if(delta==0)
		 {
		 x1=-b/(2*a);
		// cout<<"x1=x2="<<x1<<endl;
		}
		else if(delta>0)
		{
		x1=-b/(2*a)+sqrt(b*b-4*a*c)/(2*a);
		x2=-b/(2*a)-sqrt(b*b-4*a*c)/(2*a);
		}

		temp[2].x=int (x2);
		temp[2].y=k2*temp[2].x+b2;
		pDC->MoveTo(temp[0]);
		pDC->LineTo(temp[2]);

//做平行与连线的直线。

		k1=0.000001;
			b1=temp[2].y-k1*temp[2].x;
		temp[1].x=temp[2].x-90;
		temp[1].y=k1*temp[1].x+b1;
		temp[3].x=temp[2].x+90;
		temp[3].y=k1*temp[3].x+b1;
		pDC->MoveTo(temp[3]);
		pDC->LineTo(temp[1]);

		k3=-1/k1;
		b3=temp[1].y-k3*temp[1].x;
		
		k4=-1/k1;
		b4=temp[3].y-k4*temp[3].x;
		
		temp[5].y=temp[1].y+180;
		temp[5].x=(temp[5].y-b3)/k3;
		pDC->MoveTo(temp[1]);
		pDC->LineTo(temp[5]);


		temp[7].y=temp[3].y+180;
		temp[7].x=(temp[7].y-b4)/k4;
		pDC->MoveTo(temp[3]);
		pDC->LineTo(temp[7]);

		pDC->MoveTo(temp[5]);
		pDC->LineTo(temp[7]);
		this->squrt_b1=temp[1].x;
		this->squrt_b2=b3;
		this->squrt_k1=temp[1].y;
		this->squrt_k2=k3;
		this->squrt[0]=temp[1];
		this->squrt[1]=temp[3];
		this->squrt[2]=temp[5];
		this->squrt[3]=temp[7];

		::GlobalUnlock((HGLOBAL) pDoc->m_hDIB); 

}

void CPalmView::OnPalmBig() 
{
	// TODO: Add your command handler code here
	CPalmDoc* pDoc = GetDocument();	
	  unsigned char *lpSrc;//一个指向源、目的像素的移动指针
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->m_hDIB);
	int cxDIB = (int) ::DIBWidth(lpDIB);         // 图像宽度
	int cyDIB = (int) ::DIBHeight(lpDIB);        // 图像高度
	int i,j;
	int corn_x[50],corn_y[50],k=0;
	long min_R,min_L,temp;
		for(i = 0; i < cyDIB; i++)	
	{
		for(j = 0; j < cxDIB; j++)
	
		{	
			if(pDoc->corner(i,j))
			{
				corn_x[k]=j;
				corn_y[k]=i;
				k++;
				pDoc->corner(i,j)=false;
			
			}
		}	
	}	
		min_L=1000;
		min_R=1000;
		for(i=1;i<k+1;i++)
		{
			
			temp=abs(corn_x[i]-corn_x[0]);
			if(corn_x[i]<(corn_x[0]-10))
				{
					if(temp<min_L)
					{
					corn_x[1]=corn_x[i];
					corn_y[1]=corn_y[i];
					min_L=temp;
					}
				}
			else
				{
					if(temp<min_R)
					{
					corn_x[2]=corn_x[i];
					corn_y[2]=corn_y[i];
					min_R=temp;
					}
			
				}
		}
			for(i=0;i<3;i++)
			pDoc->corner(corn_y[i],corn_x[i])=true;
			
			CDC *pDC=this->GetDC();
			Invalidate(TRUE);
		//	pDC->MoveTo(corn_x[0],corn_y[0]);
		//	pDC->LineTo(273,245);
			
}
			
			

void CPalmView::OnRoiPro() 
{
	// TODO: Add your command handler code here
	
	CPalmDoc* pDoc = GetDocument();
	int h=180,w=180,dw;
	int i,j,old_x,old_y,v_x;
	double sum;

    //指向图像起始位置的指针
    BYTE *lpDIB=(BYTE*)::GlobalLock((HGLOBAL)pDoc->m_hDIB);

	//指向象素起始位置的指针
	BYTE *pScrBuff =(BYTE*)::FindDIBBits((char*)lpDIB);
   
   //将指向图像象素起始位置的指针，赋值给指针变量
    BYTE* oldbuf = pScrBuff;
	int width = (int) ::DIBWidth((char *)lpDIB);
    int height = (int) ::DIBHeight((char *)lpDIB);
    
	
//	arraylink.push_back (::FillDibToArray(pDoc->m_hDIB));


	//建立一个和原图像大小相同的25色灰度位图
    HDIB newhDIB=NewDIB(w,h,8);  
    
	//指向新的位图的指针
	BYTE *newlpDIB=(BYTE*)::GlobalLock((HGLOBAL) newhDIB);

	//指向新的位图的象素起始位置的指针 
    BYTE *destBuf = (BYTE*)FindDIBBits((char *)newlpDIB);
    
   //将指向新图像象素起始位置的指针，赋值给指针变量
    BYTE *newbuf=destBuf; 
	
	//对图像进行扫描
   
	//行 ''
	pDoc->harris=false;

	cur_x=width;
	cur_y=0;
	CDC *pDC=this->GetDC();
    for(i=0;i<h;i++)
    {  
		old_y=height-(squrt_k1+i);
		for(j=0;j<w;j++)
	   {   
			
		   //为统计变量赋初始值
		  //将计算的结果放到新的位图的相应位置
			old_x=squrt_b1+j;
		 *(newbuf+(h-i)*w+j)=*(oldbuf+old_y*width+old_x);
		//	::SetPixel(*pDC,cur_x+j,cur_y+i,RGB(*(oldbuf+old_y*width+old_x),*(oldbuf+old_y*width+old_x),*(oldbuf+old_y*width+old_x)));	 
	   }
	} 
   
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->m_hDIB);
    pDoc->m_hDIB=newhDIB;

//	::PaintDIB(newlpDIB, &rect, newhDIB, &rcDIB, pDoc->m_palDIB);
	Invalidate(TRUE);	

	//返回新的位图的句柄
    


}

void CPalmView::OnROISave() 
{
	// TODO: Add your command handler code here
	
}

void CPalmView::OnTotal() 
{
	// TODO: Add your command handler code here
			CPalmDoc* pDoc = GetDocument();

	//设定模板参数
	double tem[36]={//-1.0f,-1.0f,-1.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f
					-1,-2,-1,0,0,0,1,2,1,
					-1,0,1,-2,0,2,-1,0,1,
					2,1,0,1,0,-1,0,-1,-2,
					0,1,2,-1,0,1,-2,-1,0
					};
					
    //设定模板系数
    double  xishu = 1;   

    //进行模板操作
	pDoc->m_hDIB =::MaxTemplate(pDoc->m_hDIB,tem ,3,3, xishu,4);

	Invalidate(TRUE);		
}

void CPalmView::OnThin() 
{
	// TODO: Add your command handler code here
		CPalmDoc* pDoc = GetDocument();
	Thinning(pDoc->m_hDIB);	
	Invalidate(TRUE);
}
