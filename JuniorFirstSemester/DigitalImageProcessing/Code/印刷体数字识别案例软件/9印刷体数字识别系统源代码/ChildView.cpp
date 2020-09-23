// ChildView.cpp : implementation of the CChildView class
//
#include "stdafx.h"
#include "DigitRec.h"
#include "ChildView.h"
#include "INPUT1.h"
#include "mydiblib.h"
#include "Bp.h"
#include "DBpParamater.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
void ThiningDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight);
/////////////////////////////////////////////////////////////////////////////
// CChildView

CChildView::CChildView()
{
	fileloaded=false;
	gyhinfoinput=false;
	gyhfinished=false;
	m_hDIB=NULL;
}

CChildView::~CChildView()
{
}

BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	ON_COMMAND(IDmy_FILE_OPEN_BMP, OnFileOpenBmp)
	ON_COMMAND(IDmy_FILE_SAVE_BMP, OnFileSaveBmp)
	ON_COMMAND(IDmy_IMGPRC_SHRINK_ALIGN, OnImgprcShrinkAlign)
	ON_COMMAND(IDmy_IMGPRC_ALL, OnImgprcAll)
	ON_COMMAND(IDmy_IMGPRC_256ToGray, OnIMGPRC256ToGray)
	ON_COMMAND(IDmy_IMGPRC_DIVIDE, OnImgprcDivide)
	ON_COMMAND(IDmy_IMGPRC_TO_DIB_AND_SAVE, OnImgprcToDibAndSave)
	ON_COMMAND(IDmy_IMGPRC_REMOVE_NOISE, OnImgprcRemoveNoise)
	ON_COMMAND(IDmy_IMGPRC_STANDARIZE, OnImgprcStandarize)
	ON_COMMAND(IDmy_IMGPRC_THINNING, OnImgprcThinning)
	ON_COMMAND(IDmy_IMGPRC_ADJUST_SLOPE, OnImgprcAdjustSlope)
	ON_COMMAND(IDmy_IMGPRC_GrayToWhiteBlack, OnIMGPRCGrayToWhiteBlack)
	ON_COMMAND(IDmy_IMGPRC_SHARP, OnImgprcSharp)
	ON_COMMAND(IDmy_FILE_RE_LOAD_BMP, OnFileReLoadBmp)
	ON_COMMAND(ID_INPUT1, OnInputGuiyihuaInfo)
	ON_COMMAND(IDmy_BPNET_TRAIN, OnBpnetTrain)
	ON_COMMAND(IDmy_BPNET_RECOGNIZE, OnBpnetRecognize)
	ON_COMMAND(ID_aver, Onaver)
	ON_COMMAND(ID_Gass, OnGass)
	ON_COMMAND(ID_Mid, OnMid)
	ON_COMMAND(IDmy_IMGPRC_EQUALIZE, OnImgprcEqualize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	OnDraw(&dc);
	// Do not call CWnd::OnPaint() for painting messages
}

//打开256色位图文件
void CChildView::OnFileOpenBmp() 
{
	//创建一个打开文件对话框，并返回完整的文件路径
	static char BASED_CODE szFilter[] = "256色位图文件(*.bmp)|";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,NULL);
    if(dlg.DoModal() == IDOK)
	   strPathName = dlg.GetPathName();
	else return;
	//创建一个文件对象
   	CFile file;
	//以只读模式打开文件
	file.Open (strPathName,CFile::modeRead);
	//读取文件到HDIB句柄中. 注意:此时只是读取位图文件中文件头之后的部分,不含文件头
	m_hDIB=::ReadDIBFile (file);
	//HDIB句柄: 就是一块存储位图数据的内存区域的地址
	//HDIB句柄包含:位图信息头、调色板(如果有的话)、DIB图像数据
	//关闭文件
	file.Close ();
	//指向DIB的指针(指向位图信息头)
	BYTE* lpDIB=(BYTE*)::GlobalLock ((HGLOBAL)m_hDIB);
	// 获取DIB中颜色表中的颜色数目
	WORD wNumColors;	
	wNumColors = ::DIBNumColors((char*)lpDIB);	
	// 判断是否是256色位图
	if (wNumColors != 256)
	{
		// 提示用户
		MessageBox("非256色位图！", "系统提示" , MB_ICONINFORMATION | MB_OK);
		// 解除锁定
		::GlobalUnlock((HGLOBAL)m_hDIB);
		// 返回
		return;
	}
	//在屏幕上显示位图
	CDC* pDC=GetDC();
	DisplayDIB(pDC,m_hDIB);	
	//更改位图文件是否已加载的标志
	fileloaded=true;
    //gyhinfoinput=false;          //2004.4.26修改
	gyhfinished=false;
}

//取消一切更改，重新加载位图文件
void CChildView::OnFileReLoadBmp() 
{
	//判断位图文件是否已加载。如果尚未加载，则弹出文件打开对话框
	if(fileloaded==false)
	{
		OnFileOpenBmp();
		if(fileloaded==false)
			return;
	}
	//创建一个文件对象
   	CFile file;
	//以只读模式打开文件
	file.Open (strPathName,CFile::modeReadWrite);
	m_hDIB=::ReadDIBFile (file);
	//关闭文件
	file.Close ();
	//在屏幕上显示位图
	CDC* pDC=GetDC();
	DisplayDIB(pDC,m_hDIB);		
}


void CChildView::OnFileSaveBmp() 
{
	//创建一个保存文件对话框，并返回完整的文件路径
	static char BASED_CODE szFilter[] = "256色位图文件(*.bmp)|";
	CFileDialog dlg(FALSE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,NULL);
    if(dlg.DoModal() == IDOK)
	   strPathNameSave = dlg.GetPathName();
	else return;
	//在文件名后添加.bmp后缀
	//strPathNameSave+=".bmp";
	//以读写模式打开一个文件。如果文件不存在，则创建之
   	CFile file(strPathNameSave, CFile::modeReadWrite|CFile::modeCreate);
	::SaveDIB (m_hDIB,file);
	//关闭文件
	file.Close ();	
}

//一次性预处理
void CChildView::OnImgprcAll() 
{
	if(fileloaded==false)
	{
		if(::AfxMessageBox ("请先打开一个图像文件再进行此操作！",MB_YESNO|MB_ICONSTOP)==IDNO)
		   return;
	}
	//打开文件
	OnFileReLoadBmp();
	//判断用户是否已输入归一化高度和宽度信息
	if(gyhinfoinput==false) OnInputGuiyihuaInfo();
	//将256色图转换为灰度图
	OnIMGPRC256ToGray();
	//将灰度图二值化
	OnIMGPRCGrayToWhiteBlack();
	//梯度锐化
	//OnImgprcSharp();
	//去除离散杂点噪声
	OnImgprcRemoveNoise();
	//调整数字字符的整体倾斜
	OnImgprcAdjustSlope();
	//分割并画框标识
	OnImgprcDivide();
	//将分割后的数字字符宽、高标准化，以便于下一步与BP网络的输入兼容
	OnImgprcStandarize();
	ConvertGrayToWhiteBlack(m_hDIB);
	//紧缩重排数字字符
	OnImgprcShrinkAlign();
	//分别保存这些已经经过分割、标准后的单个的数字字符到bmp文件，以便后续过程使用
	//OnImgprcToDibAndSave();
	//OnPreprocThin();	
}

//图像预处理第1步：将256色图像转化为灰度图像
void CChildView::OnIMGPRC256ToGray() 
{	
	Convert256toGray(m_hDIB);	
	//在屏幕上显示位图
	CDC* pDC=GetDC();
	DisplayDIB(pDC,m_hDIB);	
}

//图像预处理第2步：将灰度图二值化
void CChildView::OnIMGPRCGrayToWhiteBlack()
{
	ConvertGrayToWhiteBlack(m_hDIB);
	//在屏幕上显示位图
	CDC* pDC=GetDC();
	DisplayDIB(pDC,m_hDIB);	
}

//图像预处理第3步：梯度锐化
void CChildView::OnImgprcSharp() 
{
	GradientSharp(m_hDIB);
	//在屏幕上显示位图
	CDC* pDC=GetDC();
	DisplayDIB(pDC,m_hDIB);		
}

//图像预处理第4步：去离散杂点噪声
void CChildView::OnImgprcRemoveNoise() 
{
	RemoveScatterNoise(m_hDIB);
	//在屏幕上显示位图
	CDC* pDC=GetDC();
	DisplayDIB(pDC,m_hDIB);	
}

//图像预处理第5步：倾斜度调整
void CChildView::OnImgprcAdjustSlope() 
{
    SlopeAdjust(m_hDIB);
	//在屏幕上显示位图
	CDC* pDC=GetDC();
	DisplayDIB(pDC,m_hDIB);	
}

//图像预处理第6步：分割，并在分割出来的字符外面画框以标识
void CChildView::OnImgprcDivide() 
{
	m_charRect=CharSegment(m_hDIB);
	//在屏幕上显示位图
	CDC* pDC=GetDC();
	DisplayDIB(pDC,m_hDIB);	
	DrawFrame(pDC,m_hDIB,m_charRect,2,RGB(20,60,200));
}

//图像预处理第7步：标准归一化
//将分割出来的各个不同宽、高的数字字符宽、高统一
void CChildView::OnImgprcStandarize() 
{
	StdDIBbyRect(m_hDIB,w_sample,h_sample);
	//在屏幕上显示位图
	CDC* pDC=GetDC();
	DisplayDIB(pDC,m_hDIB);	
	DrawFrame(pDC,m_hDIB,m_charRect,2,RGB(21,255,25));
	gyhfinished=true;
}

//图像预处理第8步：紧缩重排已经分割完毕的数字字符，并形成新的位图句柄
void CChildView::OnImgprcShrinkAlign() 
{
	m_hDIB=AutoAlign(m_hDIB);
	//在屏幕上显示位图
	CDC* pDC=GetDC();
	DisplayDIB(pDC,m_hDIB);	
	DrawFrame(pDC,m_hDIB,m_charRect,1,RGB(252,115,27));
}

//图像预处理第9步：将最终标准化后的字符图像分为单个单个的HDIB保存，并存为.bmp文件
void CChildView::OnImgprcToDibAndSave() 
{
	unsigned char* lpSrc;
	int w,h;
	w=m_charRect.front ().Width() ;
	h=m_charRect.front ().Height() ;
	m_dibRect.clear ();
	m_dibRectCopy.clear ();
	int i_src,j_src;
	int i,j;
	int counts=0;
	CRect rect,rectnew;
	BYTE* lpDIB=(BYTE*)::GlobalLock ((HGLOBAL)m_hDIB);
	BYTE* lpDIBBits=(BYTE*)::FindDIBBits ((char*)lpDIB);
	BYTE* lpNewDIBBits;
	BYTE* lpDst;
	LONG lLineBytes=(digicount*w+3)/4*4;
	LONG lLineBytesnew =(w+3)/4*4;
	HDIB hDIB=NULL;
	while(!m_charRect.empty ())
	{
		hDIB=::NewDIB (w,h,8);
		lpDIB=(BYTE*) ::GlobalLock((HGLOBAL)hDIB);	
		lpNewDIBBits = (BYTE*)::FindDIBBits((char*)lpDIB);
		lpDst=(BYTE*)lpNewDIBBits;
		memset(lpDst,(BYTE)255,lLineBytesnew * h);		
		rect=m_charRect.front ();
		m_charRect.pop_front ();
		for(i=0;i<h;i++)
			for(j=0;j<w;j++)
			{
				i_src=rect.top + i;
				j_src=j+counts*w;
				lpSrc=(BYTE *)lpDIBBits + lLineBytes *  i_src + j_src;
				lpDst=(BYTE *)lpNewDIBBits + lLineBytesnew * i + j;
				*lpDst=*lpSrc;
			}
		::GlobalUnlock (hDIB);
		m_dibRect.push_back (hDIB);
		counts++;
	}
	m_charRect=m_charRectCopy;
	m_dibRectCopy=m_dibRect;
	//输出为.bmp文件
	CString str;
	counts=1;
	while(!m_dibRect.empty ())
	{
		str.Format ("part%d.bmp",counts);
		//str=strPath+"\\"+str;
   		CFile file(str, CFile::modeReadWrite|CFile::modeCreate);
		hDIB=m_dibRect.front ();
		::SaveDIB (hDIB,file);
		m_dibRect.pop_front ();
		file.Close ();	
		counts++;
	}
	m_dibRect=m_dibRectCopy;
}

void CChildView::OnImgprcThinning() 
{
	 Thinning(m_hDIB);	
	//在屏幕上显示位图
	CDC* pDC=GetDC();
	DisplayDIB(pDC,m_hDIB);	
}



void CChildView::OnInputGuiyihuaInfo() 
{
	CINPUT1 input;
	input.w =8;
	input.h =16;
	if(input.DoModal ()!=IDOK) return;
	w_sample=input.w;
	h_sample=input.h;
	gyhinfoinput=true;
}

void CChildView::OnBpnetTrain() 
{
	OnImgprcAll();
	//判断是否经过了归一划的处理
	if(gyhfinished==false)
	{
		//如果没有进行提示错误并返回
		::MessageBox(NULL,"没有进行归一划预处理",NULL,MB_ICONSTOP);
		return;
	}
	
	//建立BP网络训练参数对话框
	
	CDBpParamater BpPa;
	
	//初始化变量
	BpPa.m_a=0;
	BpPa.m_eta=0.015;
	BpPa.m_ex=0.001;
	BpPa.m_hn=10;
	
	// 显示对话框
	if(BpPa.DoModal()!=IDOK)
	{
		//返回
		return;
	}
	//用户获得参数信息
	
	//相关系数
	double  momentum=BpPa.m_a; 
	//最小均方误差
	double  min_ex=BpPa.m_ex; 
	//隐层数目
	int  n_hidden=BpPa.m_hn; 
	//训练步长
	double eta=BpPa.m_eta;
	
	
	
	//获得指向DIB的指针
	BYTE *lpDIB=(BYTE*)::GlobalLock((HGLOBAL) m_hDIB);
	
	//获得指向DIB象素的指针，并指向象素的起始位置
	BYTE *lpDIBBits =(BYTE*)::FindDIBBits((char *)lpDIB);
	
	//获得颜色信息
	int numColors=(int) ::DIBNumColors((char *)lpDIB);
	//不是灰度图返回
    if (numColors!=256) 
	{
		::GlobalUnlock((HGLOBAL) m_hDIB);
		::MessageBox(NULL,"只能处理灰度图像",NULL,MB_ICONSTOP);
		return;
	}
	
	//获取图像的宽度
    LONG lWidth = (LONG) ::DIBWidth((char *)lpDIB); 
	
	//获取图像的高度
	LONG lHeight = (LONG) ::DIBHeight((char *)lpDIB);
	
	//计算图像每行的字节数
	LONG lLineByte = (lWidth+3)/4*4; 
	
	//归一化的宽度
	LONG lSwidth = w_sample;
	
	//归一化的高度
	LONG LSheight = h_sample;
	
	//指向输入样本的特征向量的指针  
	double **data_in;
	//从输入的训练样本中提取特征向量
	data_in = code ( lpDIBBits, digicount,  lLineByte, lSwidth, LSheight);
	
	//计算输入层结点的数目
	
	int n_in = LSheight*lSwidth;
	
	double out[][4]={      0.1,0.1,0.1,0.1,
		0.1,0.1,0.1,0.9,
		0.1,0.1,0.9,0.1,
		0.1,0.1,0.9,0.9,
		0.1,0.9,0.1,0.1,
		0.1,0.9,0.1,0.9,
		0.1,0.9,0.9,0.1,
		0.1,0.9,0.9,0.9,
		0.9,0.1,0.1,0.1,
		0.9,0.1,0.1,0.9};
	
	
	
	double **data_out;
	
	data_out = alloc_2d_dbl(digicount,4);
	
	for(int i=0;i<digicount;i++)
	{
		for(int j=0;j<4;j++)
			data_out[i][j]=out[i%10][j];
		
	}
	
	BpTrain( data_in, data_out, n_in,n_hidden,min_ex,momentum,eta,digicount);
	
	::GlobalUnlock(m_hDIB);
	
	CDC* pDC=GetDC();
	DisplayDIB(pDC,m_hDIB);
	
}



void CChildView::OnBpnetRecognize() 
{
	// TODO: Add your command handler code here
	OnImgprcAll();
	//判断是否经过了归一划的处理
	if(gyhfinished==false)
	{
		//如果没有进行提示错误并返回
		::MessageBox(NULL,"没有进行归一划预处理",NULL,MB_ICONSTOP);
		return;
	}
	//获得指向DIB的指针
	BYTE *lpDIB=(BYTE*)::GlobalLock((HGLOBAL) m_hDIB);
	
	//获得指向DIB象素的指针，并指向象素的起始位置
	BYTE *lpDIBBits =(BYTE*)::FindDIBBits((char *)lpDIB);
	
	//获得颜色信息
	int numColors=(int) ::DIBNumColors((char *)lpDIB);
	//不是灰度图返回
    if (numColors!=256) 
	{
		::GlobalUnlock((HGLOBAL) m_hDIB);
		::MessageBox(NULL,"只能处理256色图像",NULL,MB_ICONSTOP);
		return;
	}
	
	//获取图像的宽度
    LONG lWidth = (LONG) ::DIBWidth((char *)lpDIB); 
	
	//获取图像的高度
	LONG lHeight = (LONG) ::DIBHeight((char *)lpDIB);
	
	//计算图像每行的字节数
	LONG lLineByte = (lWidth+3)/4*4; 
	
	//归一化的宽度
	LONG lSwidth = w_sample;
	
	//归一化的高度
	LONG LSheight = h_sample;
	
	// 读取结点信息
	int n[3];
	if(r_num(n,"num")==false)
		return;
	//获得输入层结点数目
	int  n_in=n[0];
	//获得隐层结点数目
	int  n_hidden=n[1];
	//获得输出层结点数目
	int  n_out=n[2];  
	
	//判断待识别样本的归一划信息是否与训练时相同
	if(n_in!=lSwidth*LSheight)
	{
		//如果不相同提示错误并返回
		::MessageBox(NULL,"归一划尺寸与上一次训练时不一致",NULL,MB_ICONSTOP);
		return;
	}
	
	//指向输入样本的特征向量的指针  
	double **data_in;
	//从输入的训练样本中提取特征向量
	data_in = code ( lpDIBBits, digicount,  lLineByte, lSwidth, LSheight);
	
	//根据提取的特征进行样本识别
	CodeRecognize(data_in, digicount,n_in,n_hidden,n_out);
	::GlobalUnlock(m_hDIB);
	
	CDC* pDC=GetDC();
	DisplayDIB(pDC,m_hDIB);
	
}

void CChildView::OnDraw(CDC *pDC)
{
	if(m_hDIB!=NULL) 
		DisplayDIB(pDC,m_hDIB);
}


void CChildView::Onaver() 
{
	// TODO: Add your command handler code here
//设定模板参数
	double tem[9]={1,1,1,
		           1,1,1,
				   1,1,1};

    //设定模板系数
    double  xishu = 0.111111;   

    //进行模板操作
	m_hDIB =Template(m_hDIB,tem ,3,3, xishu);

	//显示图像
	CDC* pDC=GetDC();
	DisplayDIB(pDC,m_hDIB);
	
}

void CChildView::OnGass() 
{
	// TODO: Add your command handler code here
   
	//设定模板参数
	double tem[9]={1,2,1,
		           2,4,2,
				   1,2,1};

    //设定模板系数
    double  xishu = 0.0625;   

    //进行模板操作
	m_hDIB =Template(m_hDIB,tem ,3,3, xishu);

	//显示图像
	CDC* pDC=GetDC();
	DisplayDIB(pDC,m_hDIB);
}

void CChildView::OnMid() 
{
	// TODO: Add your command handler code here
	//进行中值滤波
	m_hDIB =MidFilter(m_hDIB,3,3);

	//显示图像
	CDC* pDC=GetDC();
	DisplayDIB(pDC,m_hDIB);
}

void CChildView::OnImgprcEqualize() 
{
	Equalize(m_hDIB);

	//显示图像
	CDC* pDC=GetDC();
	DisplayDIB(pDC,m_hDIB);
}
