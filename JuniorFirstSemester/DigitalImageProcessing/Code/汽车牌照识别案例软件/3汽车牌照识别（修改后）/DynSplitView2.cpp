// DynSplitView2.cpp : implementation file
//

#include "stdafx.h"
#include "DSplit.h"
#include "DynSplitView2.h"
#include "DlgZhiFangTu.h"
#include "DlgChuangkoubianhuan.h" 
#include "DlgZhexianbianhuan.h" 
#include "DlgGuDingFaZhi.h"
#include "DialogShuangYu.h" 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDynSplitView2

IMPLEMENT_DYNCREATE(CDynSplitView2, CView)

CDynSplitView2::CDynSplitView2()
{
	state2=0;
}


/*初始化图像数据*/
void CDynSplitView2::clearmem()
{
	CDSplitDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc ->statedoc=0;
    state2=1;
	CDibNew1=&pDoc->CDibNew;
    CDib1=&pDoc->CDib;
    long int  size=CDib1->GetHeight()*CDib1->GetWidth();
    memcpy(CDibNew1->m_pData,CDib1->m_pData,size);
}

CPalette * CDynSplitView2::CreateBitmapPalette(HuiDuBianHuanDib * pBitmap)
{
	struct
	{
		WORD Version;
		WORD NumberOfEntries;
		PALETTEENTRY aEntries[256];
	} palette = { 0x300, 256 };
	
	LPRGBQUAD pRGBTable = pBitmap->GetRGB();
	UINT numberOfColors = pBitmap->GetNumberOfColors();
	
	for(UINT x=0; x<numberOfColors; ++x)
	{
		palette.aEntries[x].peRed =
			pRGBTable[x].rgbRed;
		palette.aEntries[x].peGreen =
			pRGBTable[x].rgbGreen;
		palette.aEntries[x].peBlue =
			pRGBTable[x].rgbBlue;
		palette.aEntries[x].peFlags = 0;
	}
	
	hPalette.CreatePalette((LPLOGPALETTE)&palette);
	
	return &hPalette;
}

CDynSplitView2::~CDynSplitView2()
{
}
CDSplitDoc* CDynSplitView2::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDSplitDoc)));
	return (CDSplitDoc*)m_pDocument;
}


BEGIN_MESSAGE_MAP(CDynSplitView2, CView)
	//{{AFX_MSG_MAP(CDynSplitView2)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_FILESAVE, OnFilesave)
	ON_COMMAND(ID_Zhifangtutongji, OnZhifangtutongji)
	ON_COMMAND(ID_FanSeBianHuan, OnFanSeBianHuan)
	ON_COMMAND(ID_Chuangkoubianhuan, OnChuangkoubianhuan)
	ON_COMMAND(ID_ZheXianBianHuan, OnZheXianBianHuan)
	ON_COMMAND(ID_Fenbujunhenghua, OnFenbujunhenghua)
	ON_COMMAND(ID_Pipeibianhuan, OnPipeibianhuan)
	ON_COMMAND(ID_Yuantuzhifangtu, OnYuantuzhifangtu)
	ON_COMMAND(ID_Shuipingtouying, OnShuipingtouying)
	ON_COMMAND(ID_Chuizhitouying, OnChuizhitouying)
	ON_COMMAND(ID_Fei0, OnFei0)
	ON_COMMAND(ID_GUDING, OnGuding)
	ON_COMMAND(ID_ShuanGuDingFa, OnShuanGuDingFa)
	ON_COMMAND(ID_RedZhiFangtu, OnRedZhiFangtu)
	ON_COMMAND(ID_BlueZhiFangtu, OnBlueZhiFangtu)
	ON_COMMAND(ID_GreenZhifangtu, OnGreenZhifangtu)
	ON_COMMAND(ID_zishiyingFa, OnzishiyingFa)
	ON_COMMAND(ID_huiduchuli, Onhuiduchuli)
	ON_COMMAND(ID_bianyuantiqu, Onbianyuantiqu)
	ON_COMMAND(ID_jiequ, Onjiequ)
	ON_COMMAND(ID_tiquerzhihua, Ontiquerzhihua)
	ON_COMMAND(ID_chepaifenge, Onchepaifenge)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDynSplitView2 drawing

void CDynSplitView2::OnDraw(CDC* pDC)
{	
	CDSplitDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(!pDoc ->statedoc&&state2==1)
	{
        BYTE* pBitmapData = CDibNew1->GetData();
        LPBITMAPINFO pBitmapInfo = CDibNew1->GetInfo();
		int m_scale=1;
        int bitmapHeight = CDibNew1->GetHeight();
        int bitmapWidth = CDibNew1->GetWidth();
		int scaledWidth = (int)(bitmapWidth * m_scale);
		int scaledHeight = (int)(bitmapHeight * m_scale);
		if (CDibNew1->GetRGB()) // Has a color table
		{
			CPalette * hPalette=CreateBitmapPalette(CDibNew1);
            CPalette * hOldPalette =
                pDC->SelectPalette(hPalette, true);
            pDC->RealizePalette();
			::StretchDIBits(pDC->GetSafeHdc(),0, 0, bitmapWidth, bitmapHeight,
				0, 0, bitmapWidth, bitmapHeight,
				pBitmapData, pBitmapInfo,
				DIB_RGB_COLORS, SRCCOPY);
            pDC->SelectPalette(hOldPalette, true);
            ::DeleteObject(hPalette);
		}
		else
		{
			StretchDIBits(pDC->GetSafeHdc(),
                0, 0, scaledWidth, scaledHeight,
                0, 0, bitmapWidth, bitmapHeight,
				pBitmapData, pBitmapInfo,
				DIB_RGB_COLORS, SRCCOPY);
		}
	}
}


/////////////////////////////////////////////////////////////////////////////
// CDynSplitView2 diagnostics

#ifdef _DEBUG
void CDynSplitView2::AssertValid() const
{
	CView::AssertValid();
}

void CDynSplitView2::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDynSplitView2 message handlers

BOOL CDynSplitView2::OnEraseBkgnd(CDC* pDC) 
{
	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect,::GetSysColor(COLOR_WINDOW));
	return TRUE;
}

void CDynSplitView2::OnFilesave() 
{
	CFileDialog dlg(FALSE,_T("BMP"),_T("*.BMP"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("位图文件(*.BMP)|*.BMP|"));	
    if(IDOK==dlg.DoModal())
	CString  filename;
    filename.Format ("%s",dlg.GetPathName() );    
    CDibNew1->SaveFile(filename);
	state2=1;
	Invalidate();
}

//处理后直方图显示
void CDynSplitView2::OnZhifangtutongji() 
{
	int i;
	// 各颜色分量的灰度分布密度
    float midu[256];
	
	// 计算灰度分布密度
	CDSplitDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc ->statedoc=0;
    state2=1;
	
	CDibNew1->ZhiFangTu(midu);             //调用灰度统计处理函数
	
	// 创建对话框
	CDlgZhiFangTu*  dlg;	 
    dlg=new CDlgZhiFangTu(this);
    dlg->Create(IDD_DLG_zhifangtufenbu);
	// 传递灰度分布密度数据给面板类
	for (i = 0; i <256; i++)
		dlg->m_fIntensity[i] = midu[i];
	
	// 显示处理后的直方图
	dlg->ShowWindow(SW_RESTORE);
}

//反色变换消息映射
void CDynSplitView2::OnFanSeBianHuan() 
{
    clearmem();
	int i;
	state3=0;
	
	// 计算灰度分布密度
	CDibNew1->ZhiFangTu(midu2);									//调用灰度统计处理函数
	
	// 创建对话框
	CDlgZhiFangTu*  dlg2; 
    dlg2=new CDlgZhiFangTu(this);
    dlg2->Create(IDD_DLG_zhifangtufenbu);
	
	// 传递灰度分布密度数据给面板类
	for (i = 0; i <256; i++)
		dlg2->m_fIntensity[i] = midu2[i];
	if(CDibNew1->m_pBitmapInfoHeader->biBitCount<9)		//灰度图像
	{
		clearmem();
		CDibNew1->FanSeBianHuan();								//调用反色变换处理函数
		Invalidate();											//调用刷新函数
	}
	else		//24位彩色
	{
		clearmem2();
		CDibNew1->FanSeBianHuan();								//调用反色变换处理函数
		Invalidate();											//调用刷新函数
	}
}

//灰度窗口变换消息映射
void CDynSplitView2::OnChuangkoubianhuan() 
{
	clearmem();
	int i;
	state3=0;
	// 计算灰度分布密度
	CDibNew1->ZhiFangTu(midu2);									//调用灰度统计处理函数
	
	// 创建对话框
	CDlgZhiFangTu*  dlg2;	 
	dlg2=new CDlgZhiFangTu(this);
	dlg2->Create(IDD_DLG_zhifangtufenbu);
	
	// 传递灰度分布密度数据给面板类
	for (i = 0; i <256; i++)
		dlg2->m_fIntensity[i] = midu2[i];
	// 创建对话框
	CDlgChuangkoubianhuan  dlg;
	
	// 窗口下限
	BYTE	bLow;	
	// 窗口上限
	BYTE	bUp;
	
	// 初始化变量值
	dlg.m_bLow = 50;
	dlg.m_bUp = 200;
	
	// 显示对话框，提示用户设定窗口上下限
	if (dlg.DoModal() != IDOK)
	{
		// 返回
		return;
	}	
	// 获取用户设定的窗口上下限
	bLow = dlg.m_bLow;
	bUp = dlg.m_bUp;
	
	// 删除对话框
	delete dlg;			
	// 调用WindowTrans()函数进行窗口变换
	if(CDibNew1->m_pBitmapInfoHeader->biBitCount<9)		//灰度图像
	{
		clearmem();
		CDibNew1->Chuangkoubianhuan(  bLow,   bUp);             //调用窗口变换处理函数
		Invalidate();											//调用刷新函数 
	}
	else		//24位彩色
	{
		clearmem2();
		CDibNew1->Chuangkoubianhuan(  bLow,   bUp);             //调用窗口变换处理函数
		Invalidate();											//调用刷新函数 
	}
	
}


//折线变换消息映射
void CDynSplitView2::OnZheXianBianHuan() 
{
	clearmem();
	int i;
	state3=0;
	
	// 计算灰度分布密度
	CDibNew1->ZhiFangTu(midu2);             //调用灰度统计处理函数
	
	// 创建对话框
	CDlgZhiFangTu*  dlg2;
    dlg2=new CDlgZhiFangTu(this);
    dlg2->Create(IDD_DLG_zhifangtufenbu);
	
	// 传递灰度分布密度数据给面板类
	for (i = 0; i <256; i++)
		dlg2->m_fIntensity[i] = midu2[i];
	
	// 创建对话框
	CDlgZhexianbianhuan dlgPara;
	
	// 点1坐标
	BYTE	bX1;
	BYTE	bY1;	
	// 点2坐标
	BYTE	bX2;
	BYTE	bY2;
	
	// 初始化变量值
	dlgPara.m_bX1 = 50;
	dlgPara.m_bY1 = 30;
	dlgPara.m_bX2 = 200;
	dlgPara.m_bY2 = 220;
	
	// 显示对话框，提示用户设定拉伸位置
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}
	
	// 获取用户的设定
	bX1 = dlgPara.m_bX1;
	bY1 = dlgPara.m_bY1;
	bX2 = dlgPara.m_bX2;
	bY2 = dlgPara.m_bY2;
	
	// 删除对话框
	delete dlgPara;	
	if  (CDibNew1->m_pBitmapInfoHeader->biBitCount<9)		//灰度图像
	{
		// 调用Zhexianbianhuan()函数进行灰度拉伸	 
		clearmem();
		CDibNew1->Zhexianbianhuan( bX1,bY1,bX2,bY2);             //调用折线变换处理函数
		Invalidate();           //调用刷新函数
	}
	else		//24位彩色
	{
		// 调用Zhexianbianhuan()函数进行灰度拉伸	 
		clearmem2();
		CDibNew1->Zhexianbianhuan( bX1,bY1,bX2,bY2);             //调用折线变换处理函数
		Invalidate();           //调用刷新函数
	}
}

//图像灰度分布均衡化消息映射
void CDynSplitView2::OnFenbujunhenghua() 
{
	clearmem();
	int i;
	state3=0;
	// 计算灰度分布密度
	CDibNew1->ZhiFangTu(midu2);             //调用灰度统计处理函数
	
	// 创建对话框
	CDlgZhiFangTu*  dlg2; 
    dlg2=new CDlgZhiFangTu(this);
    dlg2->Create(IDD_DLG_zhifangtufenbu);
	
	// 传递灰度分布密度数据给面板类
	for (i = 0; i <256; i++)
		dlg2->m_fIntensity[i] = midu2[i];
    if(CDibNew1->m_pBitmapInfoHeader->biBitCount<9)		//灰度图像
	{
		clearmem();
		CDibNew1->Fenbujunhenghua();             //调用分布均衡化处理函数
		Invalidate();           //调用刷新函数
	}
	else		//24位彩色
	{
		clearmem2();
		CDibNew1->Fenbujunhenghua();             //调用分布均衡化处理函数
		Invalidate();           //调用刷新函数
	}
}

//匹配变换消息映射
void CDynSplitView2::OnPipeibianhuan() 
{
	
	clearmem();
	int n;
	state3=0;
	
	// 计算灰度分布密度
	CDibNew1->ZhiFangTu(midu2);             //调用灰度统计处理函数
	
	// 创建对话框
	CDlgZhiFangTu*  dlg2;
    dlg2=new CDlgZhiFangTu(this);
    dlg2->Create(IDD_DLG_zhifangtufenbu);
	
	// 传递灰度分布密度数据给面板类
	for (n = 0; n <256; n++)
		dlg2->m_fIntensity[n] = midu2[n];
	
	//--------直方图设置 开始------------------------------------------
	int nu[64];
	float pu[64];
	
	float a=1.0f/(32.0f*63.0f);
	for(int i=0;i<64;i++)
	{
		nu[i]=i*4;
		pu[i]=a*i;
	}
	//--------直方图设置 结束------------------------------------------
	if(CDibNew1->m_pBitmapInfoHeader->biBitCount<9)		//灰度图像
	{
		clearmem();
		CDibNew1->Pipeibianhuan(64,nu, pu);             //调用匹配变化处理函数
		Invalidate();           //调用刷新函数
	}
	else		//24位彩色
	{
		clearmem2();
		CDibNew1->Pipeibianhuan(64,nu, pu);             //调用匹配变化处理函数
		Invalidate();           //调用刷新函数
	}
}
 
//原图直方图显示
void CDynSplitView2::OnYuantuzhifangtu()  
{
	int i;
	clearmem();
	// 各颜色分量的灰度分布密度
	float midu[256];
	
	// 计算灰度分布密度 	 
	CDibNew1->ZhiFangTu(midu);             //调用灰度统计处理函数
	
	// 创建对话框
	CDlgZhiFangTu*  dlg3;
	dlg3=new CDlgZhiFangTu(this);
	dlg3->Create(IDD_DLG_zhifangtufenbu);
	
	// 传递灰度分布密度数据给面板类
	for (i = 0; i <256; i++)
		dlg3->m_fIntensity[i] = midu[i];
	
	// 显示对话框，由用户进行灰度折线变换
	dlg3->ShowWindow(SW_RESTORE);
}

//水平投影消息映射
void CDynSplitView2::OnShuipingtouying()
{
	clearmem();
	int i;
	state3=0;
	
	// 计算灰度分布密度
	CDibNew1->ZhiFangTu(midu2);             //调用灰度统计处理函数
	
	// 创建对话框
	CDlgZhiFangTu*  dlg2;
    dlg2=new CDlgZhiFangTu(this);
    dlg2->Create(IDD_DLG_zhifangtufenbu);
	
	// 传递灰度分布密度数据给面板类
	for (i = 0; i <256; i++)
		dlg2->m_fIntensity[i] = midu2[i];
    if(CDibNew1->m_pBitmapInfoHeader->biBitCount<9)		//灰度图像
	{
		clearmem();
		CDibNew1->Shuipingtouying();             //调用水平投影处理函数
		Invalidate();
	}
	else		//24位彩色
	{
		clearmem2();
		CDibNew1->Shuipingtouying();             //调用水平投影处理函数
		Invalidate();
	}
}


//垂直投影消息映射
void CDynSplitView2::OnChuizhitouying()  
{
	clearmem();
	int i;
	state3=0;
	
	// 计算灰度分布密度
	CDibNew1->ZhiFangTu(midu2);             //调用灰度统计处理函数
	
	// 创建对话框
	CDlgZhiFangTu*  dlg2;	 
    dlg2=new CDlgZhiFangTu(this);
    dlg2->Create(IDD_DLG_zhifangtufenbu);
	
	// 传递灰度分布密度数据给面板类
	for (i = 0; i <256; i++)
		dlg2->m_fIntensity[i] = midu2[i];
    if(CDibNew1->m_pBitmapInfoHeader->biBitCount<9)		//灰度图像
	{
		clearmem();
		CDibNew1->Chuizhitouying();             //调用垂直投影处理函数
		Invalidate();
	}
	else		//24位彩色
	{
		clearmem2();
		CDibNew1->Chuizhitouying();             //调用垂直投影处理函数
		Invalidate();
	}
}
 
//非零取一法灰度变换消息映射
void CDynSplitView2::OnFei0() 
{
	clearmem();
	int i;
	state3=0;
	// 计算灰度分布密度
	CDibNew1->ZhiFangTu(midu2);             //调用灰度统计处理函数
	
	// 创建对话框
	CDlgZhiFangTu*  dlg2;	 
    dlg2=new CDlgZhiFangTu(this);
    dlg2->Create(IDD_DLG_zhifangtufenbu);
	
	// 传递灰度分布密度数据给面板类
	for (i = 0; i <256; i++)
		dlg2->m_fIntensity[i] = midu2[i];
    if(CDibNew1->m_pBitmapInfoHeader->biBitCount<9)		//灰度图像
	{
		clearmem();
		CDibNew1->Fei0();             //调用非零取一处理函数
		Invalidate();
	}
	else		//24位彩色
	{
		clearmem2();
		CDibNew1->Fei0();             //调用非零取一处理函数
		Invalidate();
	}
}

//固定阀值灰度变换消息映射
void CDynSplitView2::OnGuding() 
{
	clearmem();
	int i;
	state3=0;
	
	// 计算灰度分布密度
	CDibNew1->ZhiFangTu(midu2);             //调用灰度统计处理函数
	
	// 创建对话框
	CDlgZhiFangTu*  dlg2;
    dlg2=new CDlgZhiFangTu(this);
    dlg2->Create(IDD_DLG_zhifangtufenbu);
	
	// 传递灰度分布密度数据给面板类
	for (i = 0; i <256; i++)
		dlg2->m_fIntensity[i] = midu2[i];
	if(CDibNew1->m_pBitmapInfoHeader->biBitCount<9)		//灰度图像
	{
		clearmem();
		CDlgGuDingFaZhi dlg;
		if(IDOK==dlg.DoModal())
		{
			CDibNew1->GuDing(dlg.m_Yuzhi);
			Invalidate();
		}
	}
	else		//24位彩色
	{
		clearmem2();
		CDlgGuDingFaZhi dlg;
		if(IDOK==dlg.DoModal())
		{
			CDibNew1->GuDing(dlg.m_Yuzhi);
			Invalidate();
		}
	}
}

void CDynSplitView2::OnShuanGuDingFa() 
{
	clearmem();
	int i;
	state3=0;
	
	// 计算灰度分布密度
	CDibNew1->ZhiFangTu(midu2);             //调用灰度统计处理函数
	
	// 创建对话框
	CDlgZhiFangTu*  dlg2;
    dlg2=new CDlgZhiFangTu(this);
    dlg2->Create(IDD_DLG_zhifangtufenbu);
	
	// 传递灰度分布密度数据给面板类
	for (i = 0; i <256; i++)
		dlg2->m_fIntensity[i] = midu2[i];
	if(CDibNew1->m_pBitmapInfoHeader->biBitCount<9)		//灰度图像
	{
		clearmem();
		CDialogShuangYu dlg;
		if(IDOK==dlg.DoModal())
		{
			CDibNew1->ShuangYu(dlg.m_ZhiYu1,dlg.m_ZhiYu2,dlg.m_mode);
			Invalidate();
		}
	}
	else		//24位彩色
	{
		clearmem2();
		CDialogShuangYu dlg;
		if(IDOK==dlg.DoModal())
		{
			CDibNew1->ShuangYu(dlg.m_ZhiYu1,dlg.m_ZhiYu2,dlg.m_mode);
			Invalidate();
		}
	}
}

void CDynSplitView2::clearmem2()
{
    CDSplitDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc ->statedoc=0;
    state2=1;
	CDibNew1=&pDoc->CDibNew;
    CDib1=&pDoc->CDib;
    long int  size=CDib1->GetHeight()*CDib1->GetDibWidthBytes();
    memcpy(CDibNew1->m_pData,CDib1->m_pData,size);
}

void CDynSplitView2::OnRedZhiFangtu() 
{
	int i;
	clearmem();
	// 各颜色分量的灰度分布密度
	float midu[256];
	
	// 计算灰度分布密度 	 
	CDibNew1->RedZhiFangTu(midu);             //调用灰度统计处理函数
	
	// 创建对话框
	CDlgZhiFangTu*  dlg3;
	dlg3=new CDlgZhiFangTu(this);
	dlg3->Create(IDD_DLG_zhifangtufenbu);
	
	// 传递灰度分布密度数据给面板类
	for (i = 0; i <256; i++)
		dlg3->m_fIntensity[i] = midu[i];
	
	// 显示对话框，由用户进行灰度折线变换
	dlg3->ShowWindow(SW_RESTORE);
}

void CDynSplitView2::OnBlueZhiFangtu() 
{
	int i;
	clearmem();
	// 各颜色分量的灰度分布密度
	float midu[256];
	
	// 计算灰度分布密度 	 
	CDibNew1->BlueZhiFangTu(midu);             //调用灰度统计处理函数
	
	// 创建对话框
	CDlgZhiFangTu*  dlg3;
	dlg3=new CDlgZhiFangTu(this);
	dlg3->Create(IDD_DLG_zhifangtufenbu);
	
	// 传递灰度分布密度数据给面板类
	for (i = 0; i <256; i++)
		dlg3->m_fIntensity[i] = midu[i];
	
	// 显示对话框，由用户进行灰度折线变换
	dlg3->ShowWindow(SW_RESTORE);
}

void CDynSplitView2::OnGreenZhifangtu() 
{
	int i;
	clearmem();
	// 各颜色分量的灰度分布密度
	float midu[256];
	
	// 计算灰度分布密度 	 
	CDibNew1->GreenZhiFangTu(midu);             //调用灰度统计处理函数
	
	// 创建对话框
	CDlgZhiFangTu*  dlg3;
	dlg3=new CDlgZhiFangTu(this);
	dlg3->Create(IDD_DLG_zhifangtufenbu);
	
	// 传递灰度分布密度数据给面板类
	for (i = 0; i <256; i++)
		dlg3->m_fIntensity[i] = midu[i];
	
	// 显示对话框，由用户进行灰度折线变换
	dlg3->ShowWindow(SW_RESTORE);
}

void CDynSplitView2::OnzishiyingFa() 
{
	// TODO: Add your command handler code here

	clearmem();
	
	state3=0;
	

	
	
	if(CDibNew1->m_pBitmapInfoHeader->biBitCount<9)		//灰度图像
	{
		clearmem();
		
			CDibNew1->zishiying();
			Invalidate();
		
	}
	else		//24位彩色
	{
		clearmem2();
		
		CDibNew1->MakegGray();
		CDibNew1->zishiying();
		Invalidate();
		
	}
	
}

void CDynSplitView2::Onhuiduchuli() 
{
	// TODO: Add your command handler code here
	
    clearmem();
	LPSTR  p_data;
	p_data=(char*)CDibNew1->GetData ();

	int wide,height;  
//	if(CDibNew1->m_pBitmapInfoHeader->biBitCount<9)		
		wide=CDibNew1->GetWidth ();
//	else
//		wide=CDibNew1->GetDibWidthBytes();
	height=CDibNew1->GetHeight ();

	long LB=CDibNew1->GetDibWidthBytes();

	// 滤波器的高度
	int iFilterH;
	
	// 滤波器的宽度
	int iFilterW;
	
	// 中心元素的X坐标
	int iFilterMX;
	
	// 中心元素的Y坐标
	int iFilterMY;

	// 初始化变量值
	iFilterH = 5;
	iFilterW = 1;
	iFilterMX = 0;
	iFilterMY = 2;

	CDibNew1->myMedianFilter(p_data, wide, height, 
		iFilterH, iFilterW, iFilterMX, iFilterMY,LB);

	Invalidate();
}

void CDynSplitView2::Onbianyuantiqu() 
{
	// TODO: Add your command handler code here
	clearmem();
	CDibNew1->bianyuanjiance();
	Invalidate();
}

void CDynSplitView2::Onjiequ() 
{
	// TODO: Add your command handler code here
	clearmem();
	LPSTR  p_data;
	p_data=(char*)CDibNew1->GetData ();
	int wide,height;  
//	if(CDibNew1->m_pBitmapInfoHeader->biBitCount<9)		
		wide=CDibNew1->GetWidth ()+1;
//	else
//		wide=CDibNew1->GetDibWidthBytes();
	height=CDibNew1->GetHeight ();
	CDibNew1->myHprojectDIB(p_data, wide, height,&m_ipzTop, &m_ipzBottom) ;
	CDibNew1->myVprojectDIB(p_data, wide, height,&m_ipzLeft, &m_ipzRight) ;
	int h=abs(m_ipzTop-m_ipzBottom);
	m_ipzRight=m_ipzLeft+3*h;
	int w=abs(m_ipzLeft-m_ipzRight);
//	int h=m_ipzBottom-m_ipzTop;
//	int w=m_ipzRight-m_ipzLeft;

//	AfxMessageBox(wide,MB_OK,0);

	BYTE *temp=new BYTE[w*h];
	memset(temp,0,sizeof(temp));

//	int fres;
	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
		{
			temp[w*j+i]=
			p_data[wide*(height-m_ipzBottom+j)+(wide-m_ipzRight+i)];
		}
	}

/*	for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < 10; i++)
		{
//			temp[w*j+i]=
			p_data[wide*(j)+(i)]=255;
		}
	}*/

//	memset(p_data,255,wide*height);

//	p_data=(char*)CDibNew1->GetData ();
//	int d,e;
/*	for( d=0;d < h;d++)
	{
		for( e=0;e < w;e++)
		{
			
			*p_data=temp[w*d+e];
			p_data++;
			
		}
	}*/
	*p_data=*temp;
	CDibNew1->m_pBitmapInfoHeader->biHeight=h;
	CDibNew1->m_pBitmapInfoHeader->biWidth=w;
	memcpy(p_data,temp,w*h);
	Invalidate();
}

void CDynSplitView2::Ontiquerzhihua() 
{
	// TODO: Add your command handler code here
	clearmem();
	LPSTR  p_data;
	p_data=(char*)CDibNew1->GetData ();
	int wide,height;
	wide=CDibNew1->GetWidth ();
	height=CDibNew1->GetHeight ();

	int h=abs(m_ipzTop-m_ipzBottom);
	m_ipzRight=m_ipzLeft+3*h;
	int w=abs(m_ipzLeft-m_ipzRight);

	long ll;
	w=w-0.5;
	BYTE *temp=new BYTE[w*h];
	memset(temp,0,sizeof(temp));

	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
		{
			temp[w*j+i]=
			p_data[wide*(height-m_ipzBottom+j)+(wide-m_ipzRight+i)+j];
		}
	}
	*p_data=*temp;
	CDibNew1->m_pBitmapInfoHeader->biHeight=h;
	CDibNew1->m_pBitmapInfoHeader->biWidth=w;
	memcpy(p_data,temp,w*h);
	Invalidate();
}

void CDynSplitView2::Onchepaifenge() 
{
	// TODO: Add your command handler code here
	clearmem();
	LPSTR  p_data;
	p_data=(char*)CDibNew1->GetData ();
	int wide,height;
	wide=CDibNew1->GetWidth ();
	height=CDibNew1->GetHeight ();
	CDibNew1->myHcut(p_data, wide, height,&m_ipzTop, &m_ipzBottom);
	CDibNew1->myVcut(p_data, wide, height,&r1, &l1,&r2, &l2,&r3, &l3,&r4, &l4,&r5, &l5,&r6, &l6,&r7, &l7);

	for (int i = 0; i < wide; i++)
	{
		p_data[wide*m_ipzBottom+i]=255;
		p_data[wide*m_ipzTop+i]=255;
	}
	for (int j = 0; j < height; j++)
	{
		p_data[wide*j+l1]=255;
		p_data[wide*j+r1]=255;
	    p_data[wide*j+l2]=255;
		p_data[wide*j+r2]=255;
		p_data[wide*j+l3]=255;
		p_data[wide*j+r3]=255;
		p_data[wide*j+l4]=255;
		p_data[wide*j+r4]=255;
		p_data[wide*j+l5]=255;
		p_data[wide*j+r5]=255;
		p_data[wide*j+l6]=255;
		p_data[wide*j+r6]=255;
		p_data[wide*j+l7]=255;
		p_data[wide*j+r7]=255;
	}


	Invalidate();
}
