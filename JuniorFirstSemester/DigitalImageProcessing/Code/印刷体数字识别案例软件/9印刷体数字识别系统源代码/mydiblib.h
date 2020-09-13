#include "dibapi.h"
#include <iostream>
#include <deque>
#include <math.h>
using namespace std;

typedef deque<CRect> CRectLink;
typedef deque<HDIB>  HDIBLink;

//声明一些必要的全局变量
int w_sample=8;
int h_sample=16;
bool fileloaded;
bool gyhinfoinput;
bool gyhfinished;
int digicount;
int m_lianXuShu;
CRectLink m_charRectCopy;
CRectLink m_charRect;
HDIBLink  m_dibRect;
HDIBLink  m_dibRectCopy;
HDIB m_hDIB;
CString strPathName;
CString strPathNameSave;

/********************************function declaration*************************************/

//清楚屏幕
void ClearAll(CDC* pDC);
//在屏幕上显示位图
void DisplayDIB(CDC* pDC,HDIB hDIB);
//对分割后的位图进行尺寸标准归一化
void StdDIBbyRect(HDIB hDIB, int tarWidth, int tarHeight);
//整体斜率调整
void SlopeAdjust(HDIB hDIB);
//去除离散噪声点
void RemoveScatterNoise(HDIB hDIB);
//梯度锐化
void GradientSharp(HDIB hDIB);
//画框
void DrawFrame(CDC* pDC,HDIB hDIB, CRectLink charRect,unsigned int linewidth,COLORREF color);
//将灰度图二值化
void ConvertGrayToWhiteBlack(HDIB hDIB);
//将256色位图转为灰度图
void Convert256toGray(HDIB hDIB);
//细化
void Thinning(HDIB hDIB);
//对位图进行分割.返回一个存储着每块分割区域的链表
CRectLink CharSegment(HANDLE hDIB);
//紧缩、重排调整
HDIB AutoAlign(HDIB hDIB);
//判断是否是离散噪声点
bool DeleteScaterJudge(LPSTR lpDIBBits,WORD lLineBytes, LPBYTE lplab, int lWidth, int lHeight, int x, int y, CPoint lab[], int lianXuShu);
//对图像进行模板操作
HDIB Template(HDIB hDIB,double * tem ,int tem_w,int tem_h,double xishu);
//对图像进行中值滤波
HDIB MidFilter(HDIB hDIB,int tem_w,int tem_h);
//对图像进行直方图均衡
void Equalize(HDIB hDIB);
/***********************************implementation*************************************/

/*********************************** ************************************
函数名称：DisplayDIB
参数：
	CDC* pDC			-指向当前设备上下文（Divice Context）的指针
	HDIB hDIB			-要显示的位图的句柄
**********************************************************************/

void DisplayDIB(CDC* pDC,HDIB hDIB)
{
	BYTE* lpDIB=(BYTE*)::GlobalLock((HGLOBAL)hDIB);
	// 获取DIB宽度和高度
	int cxDIB =  ::DIBWidth((char*) lpDIB);
	int cyDIB =  ::DIBHeight((char*)lpDIB);
	CRect rcDIB,rcDest;
	rcDIB.top = rcDIB.left = 0;
	rcDIB.right = cxDIB;
	rcDIB.bottom = cyDIB;
	//设置目标客户区输出大小尺寸
	rcDest = rcDIB;
	//CDC* pDC=GetDC();
	ClearAll(pDC);
	//在客户区显示图像
	//for(int ii=0;ii<10;ii++)
		::PaintDIB(pDC->m_hDC,rcDest,hDIB,rcDIB,NULL);
	::GlobalUnlock((HGLOBAL)hDIB);
}

void ClearAll(CDC *pDC)
{
	CRect rect;
	//GetClientRect(&rect);
	rect.left =0;rect.top =0;rect.right =2000;rect.bottom =1000;
	CPen pen;
	pen.CreatePen (PS_SOLID,1,RGB(255,255,255));
	pDC->SelectObject (&pen);
	pDC->Rectangle (&rect);
	::DeleteObject (pen);
}
/*******************************************
*
*  函数名称：
*  AutoAlign()
*
*  参数：
*    HDIB   hDIB        －原图像的句柄
*
*  返回值   
*    HDIB               －紧缩排列后的新图像的句柄
*
*  功能：
*     将经过了标准化处理的字符进行规整的排列，以方便下一步的处理
*
*  说明：
*     紧缩排列的操作必须在标准化操作之后进行
*
********************************************************/


HDIB AutoAlign(HDIB hDIB)
{   
	
	//指向图像的指针
 	BYTE* lpDIB=(BYTE*)::GlobalLock ((HGLOBAL)hDIB);

	//指向象素起始位置的指针
	BYTE* lpDIBBits=(BYTE*)::FindDIBBits ((char*)lpDIB);

	//指向象素的指针
	BYTE* lpSrc;

	//获取图像的宽度
	LONG lWidth=::DIBWidth ((char*)lpDIB);

	//获取图像的高度
	LONG lHeight=::DIBHeight ((char*)lpDIB);

	//获取标准化的宽度
	int w=m_charRect.front ().Width() ;

	//获取标准化的高度
	int h=m_charRect.front ().Height() ;

	//建立一个新的图像正好能够将标准化的字符并排放置
	HDIB hNewDIB=::NewDIB (digicount*w,h,8);

	//指向新的图像的指针
	BYTE* lpNewDIB=(BYTE*) ::GlobalLock((HGLOBAL)hNewDIB);
	
	//指向象素起始位置的指针
	BYTE* lpNewDIBBits=(BYTE*)::FindDIBBits((char*)lpNewDIB);

	//指向象素的指针
	BYTE* lpDst=lpNewDIBBits;

	//计算原图像每行的字节数
	LONG lLineBytes=(lWidth+3)/4*4;

	//计算新图像每行的字节数
	LONG lLineBytesnew =(digicount*w+3)/4*4;

	//将新的图像初始化为白色
	memset(lpDst,(BYTE)255,lLineBytesnew * h);

	//映射操作的坐标变量
	int i_src,j_src;

	//循环变量
	int i,j;

	//统计字符个数的变量
	int counts=0;

	//存放位置信息的结构体
	CRect rect,rectnew;

	//清空一个新的链表来存放新的字符位置信息
	m_charRectCopy.clear ();

	//从头至尾逐个扫描原链表的各个结点
	while(!m_charRect.empty() )
	{   
		//从表头上得到一个矩形框
		rect=m_charRect.front ();

		//将这个矩形框从链表上删除
		m_charRect.pop_front ();

		//计算新的矩形框的位置信息

		//左边界
		rectnew.left =counts*w;

		//右边界
		rectnew.right =(counts+1)*w;

		//上边界
		rectnew.top =0;

		//下边界
		rectnew.bottom =h;

		//将获得的新的矩形框插入到新的链表中
		m_charRectCopy.push_back (rectnew);

		//将原矩形框内的象素映射到新的矩形框中
		for(i=0;i<h;i++)
		{  
			for(j=counts*w;j<(counts+1)*w;j++)
			{   

				//计算映射坐标
	          	i_src=rect.top +i;
				j_src=rect.left +j-counts*w;

				//进行象素的映射
				lpSrc=(BYTE *)lpDIBBits + lLineBytes *  i_src + j_src;
				lpDst=(BYTE *)lpNewDIBBits + lLineBytesnew * i + j;
				*lpDst=*lpSrc;
			}
		}

		//字符个数加1
		counts++;
		
	}

	//将获得的新的链表复制到原链表中，以方便下一次的调用
	m_charRect=m_charRectCopy;

	//解除锁定
	::GlobalUnlock (hDIB);


	::GlobalUnlock (hNewDIB);
	return hNewDIB;
}


/**************************************************
* 函数名称：
*     ThinnerHilditch
*
* 参数：
*   void*     image             －二值化图像矩阵前景色为1背景色为0
*   unsigned  longlx             －图像的宽度
*   unsigned  longly             －图像的高度
*
* 返回值
*       无
*
*函数功能：
*       对输入的图像进行细化，输出细化后的图像
***********************************************************/

void ThinnerHilditch(void *image, unsigned long lx, unsigned long ly)
{
    char *f, *g;
    char n[10];
    unsigned int counter;
    short k, shori, xx, nrn;
    unsigned long i, j;
    long kk, kk11, kk12, kk13, kk21, kk22, kk23, kk31, kk32, kk33, size;
    size = (long)lx * (long)ly;
    g = (char *)malloc(size);

    if(g == NULL)
    {
       // printf("error in allocating memory!\n");
        return;
    }

    f = (char *)image;
    for(i=0; i<lx; i++)
    {
        for(j=0; j<ly; j++)
        {
            kk=i*ly+j;
            if(f[kk]!=0)
            {
                f[kk]=1;
                g[kk]=f[kk];
            }
        }
    }

    counter = 1;

    do
    {
        
        counter++;
        shori = 0;

        for(i=0; i<lx; i++)
        {
            for(j=0; j<ly; j++)
            {
                kk = i*ly+j;
                if(f[kk]<0)
                    f[kk] = 0;
                g[kk]= f[kk];
            }
        }

        for(i=1; i<lx-1; i++)
        {
            for(j=1; j<ly-1; j++)
            {
                kk=i*ly+j;

                if(f[kk]!=1)
                    continue;

                kk11 = (i-1)*ly+j-1;
                kk12 = kk11 + 1;
                kk13 = kk12 + 1;
                kk21 = i*ly+j-1;
                kk22 = kk21 + 1;
                kk23 = kk22 + 1;
                kk31 = (i+1)*ly+j-1;
                kk32 = kk31 + 1;
                kk33 = kk32 + 1;

                if((g[kk12]&&g[kk21]&&g[kk23]&&g[kk32])!=0)
                    continue;

                nrn = g[kk11] + g[kk12] + g[kk13] + g[kk21] + g[kk23] + 
                    g[kk31] + g[kk32] + g[kk33];

                if(nrn <= 1)
                {
                    f[kk22] = 2;
                    continue;
                }

                n[4] = f[kk11];
                n[3] = f[kk12];
                n[2] = f[kk13];
                n[5] = f[kk21];
                n[1] = f[kk23];
                n[6] = f[kk31];
                n[7] = f[kk32];
                n[8] = f[kk33];
                n[9] = n[1];
                xx = 0;

                for(k=1; k<8; k=k+2)
                {
                    if((!n[k])&&(n[k+1]||n[k+2]))
                        xx++;
                }

                if(xx!=1)
                {
                    f[kk22] = 2;
                    continue;
                }

                if(f[kk12] == -1)
                {
                    f[kk12] = 0;
                    n[3] = 0;
                    xx = 0;

                    for(k=1; k<8; k=k+2)
                    {
                        if((!n[k])&&(n[k+1]||n[k+2]))
                            xx++;
                    }

                    if(xx != 1)
                    {
                        f[kk12] = -1;
                        continue;
                    }

                    f[kk12] = -1;
                    n[3] = -1;
                }

                if(f[kk21]!=-1)
                {
                    f[kk22] = -1;
                    shori = 1;
                    continue;
                }

                f[kk21] = 0;
                n[5] = 0;
                xx = 0;

                for(k=1; k<8; k=k+2)
                {
                    if((!n[k])&&(n[k+1]||n[k+2]))
                    {
                        xx++;
                    }
                }

                if(xx == 1)
                {
                    f[kk21] = -1;
                    f[kk22] = -1;
                    shori =1;
                }
                else
                    f[kk21] = -1;
            }
        }
    }while(shori);

    free(g);
}

/**************************************************
* 函数名称：
*     ThinnerRosenfeld
*
* 参数：
*   void*     image             －二值化图像矩阵前景色为1背景色为0
*   unsigned  longlx             －图像的宽度
*   unsigned  longly             －图像的高度
*
* 返回值
*       无
*
*函数功能：
*       对输入的图像进行细化，输出细化后的图像
***********************************************************/
void ThinnerRosenfeld(void *image, unsigned long lx, unsigned long ly)
{
    char *f, *g;
    char n[10];
    char a[5] = {0, -1, 1, 0, 0};
    char b[5] = {0, 0, 0, 1, -1};
    char nrnd, cond, n48, n26, n24, n46, n68, n82, n123, n345, n567, n781;
    short k, shori;
    unsigned long i, j;
    long ii, jj, kk, kk1, kk2, kk3, size;
    size = (long)lx * (long)ly;

    g = (char *)malloc(size);
    if(g==NULL)
    {
        printf("error in alocating mmeory!\n");
        return;
    }

    f = (char *)image;
    for(kk=0l; kk<size; kk++)
    {
        g[kk] = f[kk];
    }

    do
    {
        shori = 0;
        for(k=1; k<=4; k++)
        {
            for(i=1; i<lx-1; i++)
            {
                ii = i + a[k];

                for(j=1; j<ly-1; j++)
                {
                    kk = i*ly + j;

                    if(!f[kk])
                        continue;

                    jj = j + b[k];
                    kk1 = ii*ly + jj;

                    if(f[kk1])
                        continue;

                    kk1 = kk - ly -1;
                    kk2 = kk1 + 1;
                    kk3 = kk2 + 1;
                    n[3] = f[kk1];
                    n[2] = f[kk2];
                    n[1] = f[kk3];
                    kk1 = kk - 1;
                    kk3 = kk + 1;
                    n[4] = f[kk1];
                    n[8] = f[kk3];
                    kk1 = kk + ly - 1;
                    kk2 = kk1 + 1;
                    kk3 = kk2 + 1;
                    n[5] = f[kk1];
                    n[6] = f[kk2];
                    n[7] = f[kk3];

                    nrnd = n[1] + n[2] + n[3] + n[4]
                        +n[5] + n[6] + n[7] + n[8];
                    if(nrnd<=1)
                        continue;

                    cond = 0;
                    n48 = n[4] + n[8];
                    n26 = n[2] + n[6];
                    n24 = n[2] + n[4];
                    n46 = n[4] + n[6];
                    n68 = n[6] + n[8];
                    n82 = n[8] + n[2];
                    n123 = n[1] + n[2] + n[3];
                    n345 = n[3] + n[4] + n[5];
                    n567 = n[5] + n[6] + n[7];
                    n781 = n[7] + n[8] + n[1];

                    if(n[2]==1 && n48==0 && n567>0)
                    {
                        if(!cond)
                            continue;
                        g[kk] = 0;
                        shori = 1;
                        continue;
                    }

                    if(n[6]==1 && n48==0 && n123>0)
                    {
                        if(!cond)
                            continue;
                        g[kk] = 0;
                        shori = 1;
                        continue;
                    }

                    if(n[8]==1 && n26==0 && n345>0)
                    {
                        if(!cond)
                            continue;
                        g[kk] = 0;
                        shori = 1;
                        continue;
                    }

                    if(n[4]==1 && n26==0 && n781>0)
                    {
                        if(!cond)
                            continue;
                        g[kk] = 0;
                        shori = 1;
                        continue;
                    }

                    if(n[5]==1 && n46==0)
                    {
                        if(!cond)
                            continue;
                        g[kk] = 0;
                        shori = 1;
                        continue;
                    }

                    if(n[7]==1 && n68==0)
                    {
                        if(!cond)
                            continue;
                        g[kk] = 0;
                        shori = 1;
                        continue;
                    }

                    if(n[1]==1 && n82==0)
                    {
                        if(!cond)
                            continue;
                        g[kk] = 0;
                        shori = 1;
                        continue;
                    }

                    if(n[3]==1 && n24==0)
                    {
                        if(!cond)
                            continue;
                        g[kk] = 0;
                        shori = 1;
                        continue;
                    }

                    cond = 1;
                    if(!cond)
                        continue;
                    g[kk] = 0;
                    shori = 1;
                }
            }

            for(i=0; i<lx; i++)
            {
                for(j=0; j<ly; j++)
                {
                    kk = i*ly + j;
                    f[kk] = g[kk];
                }
            }
        }
    }while(shori);

    free(g);
}              


/*************************************************
*
* 函数名称：
*       CharSegment()
*
*  参数：
*      HDIB  hDIB      －原图像的句柄
*
*  返回值：
*     CRectLink        －存放被分割的各个字符位置信息的链表
*
* 功能：
*    将图像中待识别的字符逐个分离出来并返回存放各个字符的位置信息的链表
*
*  说明：
*    此函数只能对2值化后的图像进行处理
*
*********************************************************/


CRectLink CharSegment(HANDLE hDIB)
{
	
	//清空用来保存每个字符区域的链表
	CRectLink charRect1,charRect2;
	charRect1.clear();
	charRect2.clear();

	// 指向DIB的指针
	LPSTR lpDIB=(LPSTR) ::GlobalLock((HGLOBAL)hDIB);
	
	// 指向DIB象素指针
	LPSTR    lpDIBBits;	

	// 找到DIB图像象素起始位置
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	//指向象素的的指针
	BYTE* lpSrc;

	//图像的长度和宽度
	int height,width;

	//获取图像的宽度
	width=(int)::DIBWidth(lpDIB);

	//获取图像的长度
	height=(int)::DIBHeight(lpDIB);

	//计算图像每行的字节数
	LONG	lLineBytes = WIDTHBYTES(width * 8);

	//定义上下边界两个变量
	int top,bottom;

    //象素的灰度值
    int gray; 

	//设置循环变量
	int i,j;

	//用来统计图像中字符个数的计数器
	digicount=0;


	//从上往下扫描，找到上边界

	//行
	for (i=0;i<height;i++)
	{
         //列
  		for (j=0;j<width;j++)
		{
            // 指向图像第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * i + j;

			//获得该点的灰度值
			gray = *(lpSrc);

			//看是否为黑点
			if (gray == 0)
			{   
               //若为黑点，把此点作为字符大致的最高点
				top = i;

				//对i强行赋值以中断循环
				i=height;

				//跳出循环
				break;
			}

        //如果该点不是黑点，继续循环
		}
	}


    //从下往上扫描，找下边界

	//行
	for (i = height-1;i>=0;i--)
    {

		//列
		for (j=0;j<width;j++)
		{
			// 指向图像第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * i + j;

			//获取该点的灰度值
			gray = *(lpSrc);

			//判断是否为黑点
			if (gray == 0)
			{
				//若为黑点，把此点作为字符大致的最低点
				bottom = i;

				//对i强行赋值以中断循环
				i=-1;

				//跳出循环
				break;
			}

          //如果该点不是黑点，继续循环
		}
	
	}

	//lab 用作是否进入一个字符分割的标志
	bool lab = false;

	//表明扫描一列中是否发现黑色点
	bool black = false;

    //存放位置信息的结构体
	CRect rect;

	//计数器置零
	digicount=0;
   
	//行
	for (i=0;i<width;i++)
	{
		//开始扫描一列
		black=false;

		for (j=0;j<height;j++)
			{	
				// 指向图像第i行，第j个象素的指针
				lpSrc = (unsigned char*)lpDIBBits + lLineBytes * j + i;

				//获取该点的灰度值
				gray = *(lpSrc);

                //判断是否为黑点
				if (gray == 0)
				{
					//如果发现黑点，设置标志位
					black=true;

					//如果还没有进入一个字符的分割
					if(lab==false)
					{	
						//设置左侧边界
						rect.left = i;

						//字符分割开始
						lab = true;
					}

					//如果字符分割已经开始了
					else

                      //跳出循环
						break;
				}		
			}

		//如果已经扫到了最右边那列，说明整副图像扫描完毕。退出
           if(i==(width-1))
			   
		 //退出整个循环	   
		   break;

		//如果到此black仍为false，说明扫描了一列，都没有发现黑点。表明当前字符分割结束
		if(lab==true&&black==false)
		{   
           //将位置信息存入结构体中

           //设置右边界
			rect.right =i;

			//设置上边界
			rect.top =top;

			//设置下边界
			rect.bottom =bottom;

			//将框外括一个象素，以免压到字符
			rect.InflateRect (1,1);

            //将这个结构体插入存放位置信息的链表1的后面
			charRect1.push_back (rect);

			//设置标志位，开始下一次的字符分割
			lab=false;

			//字符个数统计计数器加1
			digicount++;
			
		}

		//进入下一列的扫描

	}

   //再将矩形轮廓矩形的top和bottom精确化

	//将链表1赋值给链表2
	charRect2=charRect1;

    //将链表2的内容清空
    charRect2.clear ();

	//建立一个新的存放位置信息的结构体
	CRect rectnew;

	//对于链表1从头至尾逐个进行扫描
	while(!charRect1.empty())
	{    
		//从链表1头上得到一个矩形
		rect= charRect1.front();

		//从链表1头上面删掉一个
		charRect1.pop_front();

		//计算更加精确的矩形区域

		//获得精确的左边界
		rectnew.left =rect.left-1 ;

		//获得精确的右边界
		rectnew.right =rect.right+1 ;

		//通过获得的精确左右边界对上下边境重新进行精确定位

		// 由下而上扫描计算上边界
		
		//行
		for(i=rect.top ;i<rect.bottom ;i++)
		{   
          //列
			for(j=rect.left ;j<rect.right ;j++)
			{   
                 // 指向图像第i行，第j个象素的指针
				lpSrc = (unsigned char*)lpDIBBits + lLineBytes * i + j;

				//如果这个象素是黑点
				if (*lpSrc == 0)
				{	
					//设置上边界
					rectnew.top = i-1;
					
					//对i进行强制定义以跳出循环
					i=rect.bottom  ;

					//跳出循环
					break;
				}	
			}
		}

		//由下而上扫描计算下边界
   
        //行
		for(i=rect.bottom-1 ;i>=rect.top  ;i--)
		{
			//列
			for(j=rect.left ;j<rect.right ;j++)
			{
				// 指向图像第i行，第j个象素的指针
				lpSrc = (unsigned char*)lpDIBBits + lLineBytes * i + j;

				//该点如果为黑点
				if (*lpSrc == 0)
				{	
					//设置下边界
					rectnew.bottom = i+1;

                    //对i进行强制定义以跳出循环
					i=-1;
                    //跳出循环
					break;
				}	
			}
		}

		//将得到的新的准确的位置信息从后面插到链表2的尾上
		charRect2.push_back (rectnew);
	}

	//将链表2 传递给链表1
	charRect1=charRect2;
	
	//解除锁定
	::GlobalUnlock(hDIB);

	//将链表1返回
	return charRect1;
}

/****************************************************************
* 函数名称：
*      Convert256toGray()
*
* 参数：
*     HDIB hDIB     －图像的句柄
*
*  返回值：
*        无
*
*  功能：
*     将256色位图转化为灰度图
*
***************************************************************/

void Convert256toGray(HDIB hDIB)
{
	LPSTR	lpDIB;
	
	// 由DIB句柄得到DIB指针并锁定DIB
lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)hDIB);
	
	// 指向DIB象素数据区的指针
	LPSTR   lpDIBBits;	

	// 指向DIB象素的指针
	BYTE *	lpSrc;	

	// 图像宽度
	LONG	lWidth;	
	// 图像高度
LONG  	lHeight;	

	// 图像每行的字节数
	LONG	lLineBytes;	

	// 指向BITMAPINFO结构的指针（Win3.0）
	LPBITMAPINFO lpbmi;	

	// 指向BITMAPCOREINFO结构的指针
	LPBITMAPCOREINFO lpbmc;
	
	// 获取指向BITMAPINFO结构的指针（Win3.0）
	lpbmi = (LPBITMAPINFO)lpDIB;	

	// 获取指向BITMAPCOREINFO结构的指针
	lpbmc = (LPBITMAPCOREINFO)lpDIB;	

	// 灰度映射表
	BYTE bMap[256];
	
	// 计算灰度映射表（保存各个颜色的灰度值），并更新DIB调色板
	int	i,j;
	for (i = 0; i < 256; i ++)
	{
		// 计算该颜色对应的灰度值
		bMap[i] = (BYTE)(0.299 * lpbmi->bmiColors[i].rgbRed +

					     0.587 * lpbmi->bmiColors[i].rgbGreen +

				         0.114 * lpbmi->bmiColors[i].rgbBlue + 0.5);			
		// 更新DIB调色板红色分量
		lpbmi->bmiColors[i].rgbRed = i;	
		
		// 更新DIB调色板绿色分量
		lpbmi->bmiColors[i].rgbGreen = i;	
		
		// 更新DIB调色板蓝色分量
		lpbmi->bmiColors[i].rgbBlue = i;
			
		// 更新DIB调色板保留位
		lpbmi->bmiColors[i].rgbReserved = 0;

	}
	// 找到DIB图像象素起始位置
	lpDIBBits = ::FindDIBBits(lpDIB);
		
	// 获取图像宽度
	lWidth = ::DIBWidth(lpDIB);	

	// 获取图像高度
	lHeight = ::DIBHeight(lpDIB);	

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);	

// 更换每个象素的颜色索引（即按照灰度映射表换成灰度值）

//逐行扫描
for(i = 0; i < lHeight; i++)
{

  //逐列扫描
for(j = 0; j < lWidth; j++)
{
	// 指向DIB第i行，第j个象素的指针
	lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
	// 变换
	*lpSrc = bMap[*lpSrc];
}
}

//解除锁定
::GlobalUnlock ((HGLOBAL)hDIB);
}

/******************************************************************
*
* 函数名称ConvertGrayToWhiteBlack()
*
* 参数 ：HDIB hDIB     －原图的句柄
*
* 返回值：无
*
* 功能: ConvertGrayToWhiteBlack函数采用硬阈值的方法，实现将图像二值化的功能。
* 
* 说明：
要求待处理的图片为256色
************************************************************************/

void ConvertGrayToWhiteBlack(HDIB hDIB)
{
	// 指向DIB的指针
	LPSTR	lpDIB;
	
	// 由DIB句柄得到DIB指针并锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)hDIB);
	
	// 指向DIB象素数据区的指针
	LPSTR   lpDIBBits;
	
	// 指向DIB象素的指针
	BYTE *	lpSrc;	

	// 图像宽度
	LONG	lWidth;	

	// 图像高度
	LONG	lHeight;	
	// 图像每行的字节数
	LONG	lLineBytes;	

	// 找到DIB图像象素起始位置
	lpDIBBits = ::FindDIBBits(lpDIB);	
	
	// 获取图像宽度
	lWidth = ::DIBWidth(lpDIB);	

	// 获取图像高度
	lHeight = ::DIBHeight(lpDIB);	

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);	

	// 更换每个象素的颜色索引（即按照灰度映射表换成灰度值）
	int i,j;

    //逐行扫描
	for(i = 0; i < lHeight; i++)
 {

   //逐列扫描
	for(j = 0; j < lWidth; j++)
	{

	// 指向DIB第i行，第j个象素的指针
	lpSrc = (unsigned char*)lpDIBBits + lLineBytes * i + j;

	// 二值化处理

   //大于220，设置为255，即白点
	if(*lpSrc>220) *lpSrc=255;

  //否则设置为0，即黑点
	else *lpSrc=0;

	}

}
	
 //解除锁定
::GlobalUnlock((HGLOBAL)hDIB);
}

/*****************************************************************
*
*  函数名称 
*       DeleteScaterJudge()
*
*  参数：
*     LPSTR   lpDIBBits      －指向象素起始位置的指针
*	  WORD    lLineBytes     －图像每行的字节数
*     LPBYTE  lplab          －标志位数组
*     int     lWidth         －图像的宽度
*	  int     lHeight        －图像的高度
*     int     x              －当前点的横坐标
*	  int     y              －当前点的纵坐标 
*     CPoint  lab[]          －存放议考察过的连续点坐标
*     int     lianXuShu      －离散点的判定长度
*
*  返回值：
*     Bool                   －是离散点返回false 不是离散点返回true
*	 
*  功能：
*     利用递归算法统计连续点的个数，通过阈值来判定是否为离散点
*
*  说明：
*     只能对2值图像进行处理
******************************************************************/     


bool DeleteScaterJudge(LPSTR lpDIBBits, WORD lLineBytes, LPBYTE lplab, int lWidth, int lHeight, int x, int y, CPoint lab[], int lianXuShu)
{
	
	//如果连续长度满足要求，说明不是离散点，返回
	if(m_lianXuShu>=lianXuShu)
		return TRUE;

	//长度加一
	m_lianXuShu++;

	//设定访问标志
	lplab[lWidth * y +x] = true;
	
	//保存访问点坐标
	lab[m_lianXuShu-1].x = x;
	lab[m_lianXuShu-1].y = y;

	//象素的灰度值
	int gray;
  
	//指向象素的指针
	LPSTR lpSrc;

	//长度判定
    //如果连续长度满足要求，说明不是离散点，返回
	if(m_lianXuShu>=lianXuShu)
		return TRUE;
	
	//下面进入递归
	else
	{	
		//考察上下左右以及左上、右上、左下、右下八个方向
		//如果是黑色点，则调用函数自身进行递归

		//考察下面点
		
		lpSrc=(char*)lpDIBBits + lLineBytes * (y-1) + x;

		//传递灰度值
		gray=*lpSrc;

		//如果点在图像内、颜色为黑色并且没有被访问过
		if(y-1 >=0 && gray == 0 && lplab[(y-1)*lWidth+x] == false)

		//进行递归处理		
		DeleteScaterJudge(lpDIBBits,lLineBytes,lplab,lWidth,lHeight,x,y-1,lab,lianXuShu);

		//判断长度
		//如果连续长度满足要求，说明不是离散点，返回
		if(m_lianXuShu>=lianXuShu)
		return TRUE;
		
		//左下点
		
		lpSrc=(char*)lpDIBBits + lLineBytes * (y-1) + x-1;

        //传递灰度值
		gray=*lpSrc;

        //如果点在图像内、颜色为黑色并且没有被访问过
		if(y-1 >=0 &&  x-1 >=0 && gray== 0 && lplab[(y-1)*lWidth+x-1] == false)

      	//进行递归处理		
		DeleteScaterJudge(lpDIBBits,lLineBytes,lplab,lWidth,lHeight,x-1,y-1,lab,lianXuShu);

        //判断长度
		//如果连续长度满足要求，说明不是离散点，返回
		if(m_lianXuShu>=lianXuShu)
		return TRUE;
		
		//左边
		
		lpSrc=(char*)lpDIBBits + lLineBytes * y + x-1;

		//传递灰度值
		gray=*lpSrc;

        //如果点在图像内、颜色为黑色并且没有被访问过
		if(x-1 >=0 &&  gray== 0 && lplab[y*lWidth+x-1] == false)

        //进行递归处理		
		DeleteScaterJudge(lpDIBBits,lLineBytes,lplab,lWidth,lHeight,x-1,y,lab,lianXuShu);

        //判断长度
		//如果连续长度满足要求，说明不是离散点，返回
		if(m_lianXuShu>=lianXuShu)
			return TRUE;
		
		//左上
		
		lpSrc=(char*)lpDIBBits + lLineBytes * (y+1) + x-1;

		//传递灰度值
		gray=*lpSrc;

        //如果点在图像内、颜色为黑色并且没有被访问过
		if(y+1 <lHeight && x-1 >= 0 && gray == 0 && lplab[(y+1)*lWidth+x-1] == false)

		//进行递归处理
		
		DeleteScaterJudge(lpDIBBits,lLineBytes,lplab,lWidth,lHeight,x-1,y+1,lab,lianXuShu);

        //判断长度
		//如果连续长度满足要求，说明不是离散点，返回
		if(m_lianXuShu>=lianXuShu)
			return TRUE;
		
		//上面
		
		lpSrc=(char*)lpDIBBits + lLineBytes * (y+1) + x;

        //传递灰度值
		gray=*lpSrc;

        //如果点在图像内、颜色为黑色并且没有被访问过
		if(y+1 < lHeight && gray == 0 && lplab[(y+1)*lWidth+x] == false)

        //进行递归处理
		
		DeleteScaterJudge(lpDIBBits,lLineBytes,lplab,lWidth,lHeight,x,y+1,lab,lianXuShu);

        //判断长度
		//如果连续长度满足要求，说明不是离散点，返回
		if(m_lianXuShu>=lianXuShu)
			return TRUE;
		
		//右上
		
		lpSrc=(char*)lpDIBBits + lLineBytes * (y+1) + x+1;
        
		//传递灰度值
		gray=*lpSrc;

        //如果点在图像内、颜色为黑色并且没有被访问过
		if(y+1 <lHeight && x+1 <lWidth &&  gray == 0 && lplab[(y+1)*lWidth+x+1] == false)

        //进行递归处理
		DeleteScaterJudge(lpDIBBits,lLineBytes,lplab,lWidth,lHeight,x+1,y+1,lab,lianXuShu);

        //判断长度
		//如果连续长度满足要求，说明不是离散点，返回
		if(m_lianXuShu>=lianXuShu)
			return TRUE;
		
		//右边
	
		lpSrc=(char*)lpDIBBits + lLineBytes * y + x+1;

        //传递灰度值
		gray=*lpSrc;

		//如果点在图像内、颜色为黑色并且没有被访问过
		if(x+1 <lWidth && gray==0 && lplab[y*lWidth+x+1] == false)

        //进行递归处理		
		DeleteScaterJudge(lpDIBBits,lLineBytes,lplab,lWidth,lHeight,x+1,y,lab,lianXuShu);

        //判断长度

		//如果连续长度满足要求，说明不是离散点，返回
		if(m_lianXuShu>=lianXuShu)
			return TRUE;
		
		//右下
		
		lpSrc=(char*)lpDIBBits + lLineBytes * (y-1) + x+1;

        //传递灰度值
		gray=*lpSrc;

        //如果点在图像内、颜色为黑色并且没有被访问过
		if(y-1 >=0 && x+1 <lWidth && gray == 0 && lplab[(y-1)*lWidth+x+1] == false)

       //进行递归处理		
	   DeleteScaterJudge(lpDIBBits,lLineBytes,lplab,lWidth,lHeight,x+1,y-1,lab,lianXuShu);

        //判断长度
		//如果连续长度满足要求，说明不是离散点，返回
		if(m_lianXuShu>=lianXuShu)
			return TRUE;
	}
	

	//如果递归结束，返回false，说明是离散点
	return FALSE;

}


/*****************绘制数字字符外面的矩形框*******************/
void DrawFrame(CDC* pDC,HDIB hDIB, CRectLink charRect,unsigned int linewidth,COLORREF color)
{	
	CPen pen;
	pen.CreatePen (PS_SOLID,linewidth,color);
	pDC->SelectObject (&pen);
	::SelectObject (*pDC,GetStockObject(NULL_BRUSH));
	CRect rect,rect2;
	BYTE* lpDIB=(BYTE*)::GlobalLock ((HGLOBAL)hDIB);
	while(!charRect.empty())
	{
		
		//从表头上得到一个矩形
		rect2=rect= charRect.front();
		//从链表头上面删掉一个
		charRect.pop_front();
		//注意，这里原先的rect是相对于图像原点(左下角)的，
		//而在屏幕上绘图时，要转换以客户区为原点的坐标
		rect.top =::DIBHeight ((char*)lpDIB)-rect2.bottom;
		rect.bottom =::DIBHeight ((char*)lpDIB)-rect2.top ;
		pDC->Rectangle (&rect);
	}
	::GlobalUnlock ((HGLOBAL)hDIB);
}
/***********************************************
*
* 函数名称：
*   GradientSharp() 
*
*参数 ：
*  HDIB hDIB    -待处理图像的句柄
*
* 返回值：
*       无
* 
*功能：
*    现图像的梯度锐化

*说明：
*    只能对2值图像进行处理，如果图像本身边缘较细，可能造成信息的损失
**********************************************************************/
void GradientSharp(HDIB hDIB)
{
	// 指向DIB的指针
	LPSTR lpDIB=(LPSTR) ::GlobalLock((HGLOBAL)hDIB);

	// 指向DIB象素指针
	LPSTR    lpDIBBits;	

	// 找到DIB图像象素起始位置
	lpDIBBits = ::FindDIBBits(lpDIB);	

    //获取图像的宽度
	LONG lWidth=::DIBWidth ((char*)lpDIB);

    //获取图像的长度
	LONG lHeight=::DIBHeight ((char*)lpDIB);

    // 阈值
	BYTE	bThre = 2;

	// 调用GradSharp()函数进行梯度板锐化

	// 指向源图像的指针
	unsigned char*	lpSrc;
	unsigned char*	lpSrc1;
	unsigned char*	lpSrc2;
	
	// 循环变量
	LONG	i;
	LONG	j;
	
	// 图像每行的字节数
	LONG	lLineBytes;
	
	// 中间变量
	BYTE	bTemp;
	
	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// 每行
   for(i = 0; i < lHeight; i++)
	{
		
     // 每列
	 for(j = 0; j < lWidth; j++)
		{
			
             // 指向DIB第i行，第j个象素的指针
			lpSrc  = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// 指向DIB第i+1行，第j个象素的指针
			lpSrc1 = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 2 - i) + j;
			
		     // 指向DIB第i行，第j+1个象素的指针
		     lpSrc2 = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j + 1;
			

              //计算梯度值
		     bTemp = abs((*lpSrc)-(*lpSrc1)) + abs((*lpSrc)-(*lpSrc2));
			
		    // 判断是否小于阈值
		    if (bTemp < 255)
			{  

		     // 判断是否大于阈值，对于小于情况，灰度值不变。
			   if (bTemp >= bThre)
			   {

			// 直接赋值为bTemp
			 *lpSrc = bTemp;

			   }

			}
			
           else
			{
				// 直接赋值为255
				*lpSrc = 255;
			}
	 }
   }

//最后还要处理一下图像中最下面那行
for(j = 0; j < lWidth; j++)
{   
	
 //指向最下边一行，第j个象素的指针
  lpSrc  = (unsigned char*)lpDIBBits + lLineBytes * 0 + j;

   //将此位置的象素设置为255，即白点
	*lpSrc=255;
}

   //解除锁定
	::GlobalUnlock ((HGLOBAL)hDIB);
}


/************************************************************
*
*  函数名称：
*       RemoveScatterNoise()
*
*  参数：
*     HDIB    hDIB     －原图像的句柄
*
*  返回值:
*       无
*
*  功能：
*     通过对连续点长度的统计来去除离散杂点
*
*  说明：
*      只能对2值图像进行处理
****************************************************************/
void RemoveScatterNoise(HDIB hDIB)
{
	
	// 指向DIB的指针
	LPSTR lpDIB=(LPSTR) ::GlobalLock((HGLOBAL)hDIB);
	
	// 指向DIB象素指针
	LPSTR    lpDIBBits;	

	// 找到DIB图像象素数据区的起始位置
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	//获得图像的长度
	LONG lWidth=::DIBWidth ((char*)lpDIB);

	//获得图像的高度
	LONG lHeight=::DIBHeight ((char*)lpDIB);

	//设置判定噪声的长度阈值为15
	//即如果与考察点相连接的黑点的数目小于15则认为考察点是噪声点
	int length=15;
	
	// 循环变量
	m_lianXuShu=0;
	LONG	i;
	LONG	j;	
	LONG    k;

	// 图像每行的字节数
	LONG	lLineBytes;

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

    
	LPSTR lpSrc;

	//开辟一块用来存放标志的内存数组
	LPBYTE lplab = new BYTE[lHeight * lWidth];

	//开辟一块用来保存离散判定结果的内存数组
	bool *lpTemp = new bool[lHeight * lWidth];

    //初始化标志数组
	for (i=0;i<lHeight*lWidth;i++)
    {

    //将所有的标志位设置为非
	lplab[i] = false;

	}

	//用来存放离散点的坐标的数组
	CPoint lab[21];
   
	//为循环变量赋初始值
	k=0;

	//扫描整个图像

	//逐行扫描
	for(i =0;i<lHeight;i++)
	{  
       
	   //逐行扫描
		for(j=0;j<lWidth;j++)
			{	
				//先把标志位置false
				for(k=0;k<m_lianXuShu;k++)
				lplab[lab[k].y * lWidth + lab[k].x] = false;

				//连续数置0
				m_lianXuShu =0;

			    //进行离散性判断
			    lpTemp[i*lWidth+j] = DeleteScaterJudge(lpDIBBits,(WORD)lLineBytes,lplab,lWidth,lHeight,j,i,lab,length);

			}
	}
			
	//扫描整个图像，把离散点填充成白色

	//逐行扫描
	for(i = 0;i<lHeight;i++)
	{

      //逐列扫描
		for(j=0;j<lWidth;j++)
		{       
			    //查看标志位,如果为非则将此点设为白点
				if(lpTemp[i*lWidth+j] == false)
				{	
                   //指向第i行第j个象素的指针
					lpSrc=(char*)lpDIBBits + lLineBytes * i + j;

					//将此象素设为白点
					*lpSrc=BYTE(255);
				}
			}
	}

	//解除锁定
	::GlobalUnlock ((HGLOBAL)hDIB);

}

/*********************************************************

* 函数名称：
*         SlopeAdjust()
*
* 参数：
*     HDIB   hDIB       －原图像的句柄
*
* 返回值：
*         无
*
* 功能：
*     通过对图像左右半边平均高度的统计来进行倾斜的调整
*
* 说明：
*      只能对2值图像进行处理
*
****************************************************************/
void SlopeAdjust(HDIB hDIB)
{
	// 指向DIB的指针
	LPSTR lpDIB=(LPSTR) ::GlobalLock((HGLOBAL)hDIB);
	
	// 指向DIB象素指针
	LPSTR    lpDIBBits;	

	// 找到DIB图像象素起始位置
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// 指向源图像的指针
	unsigned char*	lpSrc;

	// 循环变量
	LONG	i;
	LONG	j;
	
	// 图像每行的字节数
	LONG	lLineBytes;

	//图像的长度
	LONG    lWidth;

	//图像的宽度
	LONG	lHeight;

	//获取图像的长度
	lWidth=::DIBWidth ((char*)lpDIB);

	//获取图像的宽度
	lHeight=::DIBHeight ((char*)lpDIB);

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);
    
	//图像左半边的平均高度
	double leftaver=0.0;

   //图像右半边的平均高度
	double rightaver=0.0;

	//图像的倾斜度
	double slope;

	//统计循环变量
	LONG counts=0;
	
	//扫描左半边的图像，求黑色象素的平均高度

	//行
	for (i=0;i<lHeight;i++)
	{   

      //列
		for (j=0;j<lWidth/2;j++)
		{
		 
		 //指向第i行第j个象素的指针	
		 lpSrc=(unsigned char*)lpDIBBits + lLineBytes *  i + j;
      
		 //如果为黑点
		 if (*lpSrc == 0)
		 {
          
          //对其高度进行统计叠加
		  counts +=lWidth/2 -j;
		  leftaver += i*(lWidth/2 -j);

		 }

		}
	}

    //计算平均高度
	leftaver /= counts;
	
	//将统计循环变量重新赋值
	counts =0;

	//扫描右半边的图像，求黑色象素的平均高度

	//行
	for (i =0;i<lHeight;i++)
	{

       //列
		for (j=lWidth/2;j<lWidth;j++)
		{
			//指向第i行第j个象素的指针
			lpSrc=(unsigned char*)lpDIBBits + lLineBytes *  i + j;

            //如果为黑点
			if (*lpSrc == 0)
				{

				  //进行统计叠加
					counts +=lWidth -j;
					rightaver += i*(lWidth -j);
				}
			}
	}

	//计算右半边的平均高度
	rightaver /= counts;
	
	//计算斜率
	slope = (leftaver - rightaver) / (lWidth/2);

	//指向新的图像象素起始位置的指针
	LPSTR lpNewDIBBits;
   
	//指向新图像的指针
	LPSTR lpDst;
    
	//新图像的句柄
	HLOCAL nNewDIBBits=LocalAlloc(LHND,lLineBytes*lHeight);
    
	//锁定内存
	lpNewDIBBits=(char*)LocalLock(nNewDIBBits);
    
	//指向新图像象素的指针
	lpDst=(char*)lpNewDIBBits;
    
	//为新图像赋初始值
	memset(lpDst,(BYTE)255,lLineBytes*lHeight);
    
	//象素点的灰度值
	int gray;
    
	//位置映射值
	int i_src;

	//根据斜率，把当前新图像的点映射到源图像的点

	//行
	for (i=0;i<lHeight;i++)
	{
		//列
   		for (j=0;j<lWidth;j++)
		{	
		   //计算映射位置	
			i_src=int(i - (j-lWidth/2)*slope);

			//如果点在图像外，象素置白色
			if (i_src <0 || i_src >=lHeight )
				gray = 255;

			else
			{	
				//否则到源图像中找点，取得象素值

				//指向第i_src行第j个象素的指针
				lpSrc=(unsigned char *)lpDIBBits + lLineBytes *  i_src + j;
				gray = *lpSrc;
			}
			
			//把新图像的点用得到的象素值填充
            //指向第i行第j个象素的指针
			lpDst = (char *)lpNewDIBBits + lLineBytes * i + j;
			*lpDst=gray;
		}
	}

	// 将新的图像的内容拷贝到旧的图像中
	memcpy(lpDIBBits,lpNewDIBBits,lLineBytes*lHeight);

   // 解除锁定
	::GlobalUnlock ((HGLOBAL)hDIB);
}



/******************************************************************
*
*  函数名称：
*      StdDIBbyRect()
*
*  参数：
*     HDIB  hDIB          －图像的句柄
*     int   tarWidth      －标准化的宽度
*     int   tarHeight     －标准化的高度
*
*  返回值：
*         无
*
*  功能：
*     将经过分割的字符，进行缩放处理使他们的宽和高一直，以方便特征的提取
*
*  说明：
*     函数中用到了，每个字符的位置信息，所以必须在执行完分割操作之后才能执行标准化操作
*
******************************************************************/
void StdDIBbyRect(HDIB hDIB, int tarWidth, int tarHeight)
{	

	//指向图像的指针
	BYTE* lpDIB=(BYTE*)::GlobalLock ((HGLOBAL)hDIB);

	//指向象素起始位置的指针
	BYTE* lpDIBBits=(BYTE*)::FindDIBBits ((char*)lpDIB);
	
	//指向象素的指针
	BYTE* lpSrc;

	//获取图像的的宽度
	LONG lWidth=::DIBWidth ((char*)lpDIB);

	//获取图像的高度
	LONG lHeight=::DIBHeight ((char*)lpDIB);

	// 循环变量
	int	i;
	int	j;
	
	// 图像每行的字节数
	LONG	lLineBytes = WIDTHBYTES(lWidth * 8);

	//宽度、高度方向上的缩放因子
	double wscale,hscale;

	//开辟一块临时缓存区,来存放变化后的图像信息
	LPSTR lpNewDIBBits;
	LPSTR lpDst;
 
    //缓存区的大小和原图像的数据区大小一样
	HLOCAL nNewDIBBits=LocalAlloc(LHND,lLineBytes*lHeight);

	//指向缓存区开始位置的指针
	lpNewDIBBits=(char*)LocalLock(nNewDIBBits);

	//指向缓存内信息的指针
	lpDst=(char*)lpNewDIBBits;

	//将缓存区的内容赋初始值
	memset(lpDst,(BYTE)255,lLineBytes*lHeight);

	//进行映射操作的坐标变量
	int i_src,j_src;

	//存放字符位置信息的结构体
	CRect rect;
	CRect rectnew;

	//先清空一个新的矩形区域链表以便存储标准化后的矩形区域链表
	m_charRectCopy.clear ();

	//从头到尾逐个扫描各个结点
	while(!m_charRect.empty())
	{
		//从表头上得到一个矩形
		rect= m_charRect.front();

		//从链表头上面删掉一个
		m_charRect.pop_front();

		//计算缩放因子

		//横坐标方向的缩放因子
		wscale=(double)tarWidth/rect.Width ();

		//纵坐标方向的缩放因子
		hscale=(double)tarHeight/rect.Height ();

		//计算标准化矩形

		//上边界
		rectnew.top =rect.top ;

		//下边界
		rectnew.bottom =rect.top +tarHeight;

		//左边界
		rectnew.left =rect.left ;

		//右边界
		rectnew.right =rectnew.left +tarWidth;

		//将原矩形框内的象素映射到新的矩形框内
		for(i=rectnew.top ;i<rectnew.bottom ;i++)
		{
			for(j=rectnew.left ;j<rectnew.right ;j++)
			{   

				//计算映射坐标
				i_src=rectnew.top +int((i-rectnew.top )/hscale);
				j_src=rectnew.left +int((j-rectnew.left )/wscale);

				//将相对应的象素点进行映射操作
				lpSrc=(unsigned char *)lpDIBBits + lLineBytes *  i_src + j_src;
				lpDst = (char *)lpNewDIBBits + lLineBytes * i + j;
				*lpDst=*lpSrc;
			}
		}
		//将标准化后的矩形区域插入新的链表
		m_charRectCopy.push_back (rectnew);

	
	}

	//存储标准化后新的rect区域
    m_charRect=m_charRectCopy;

	//将缓存区的内容拷贝到图像的数据区内
	memcpy(lpDIBBits,lpNewDIBBits,lLineBytes*lHeight);

	//解除锁定
	::GlobalUnlock ((HGLOBAL)hDIB);
}


void Thinning(HDIB hDIB)
{
	// 指向DIB的指针
	LPSTR lpDIB=(LPSTR) ::GlobalLock((HGLOBAL)hDIB);
	
	// 指向DIB象素指针
	LPSTR    lpDIBBits;	

	// 找到DIB图像象素起始位置
	lpDIBBits = ::FindDIBBits(lpDIB);	
	
	// 指向源图像的指针
	LPSTR	lpSrc;

	//图像的高度和宽度
	LONG lWidth;
	LONG lHeight;

	//获取图像的宽度
	lWidth=::DIBWidth ((char*)lpDIB);

	//获取图像的高度
	lHeight=::DIBHeight ((char*)lpDIB);

    //计算每行的字节数
    LONG  lLineBytes = (lWidth+3)*4/4;

	//循环变量
    int i,j;

    //建立存储区存放2值矩阵
	BYTE *image = (BYTE*)malloc(lWidth*lHeight*sizeof(BYTE));

	//给2值矩阵赋值

	for(i=0;i<lHeight;i++)
	{
	    for(j=0;j<lWidth;j++)
		{
	      lpSrc=lpDIBBits+i*lLineBytes+j;
	    
	      if(*lpSrc==0)
	      image[i*lWidth+j]=1;

		  else
         image[i*lWidth+j]=0;
		}
	}

   //调用函数进行细化,两种函数可以选择

   ThinnerRosenfeld(image,lHeight,lWidth);

   //ThinnerHilditch(image,lHeight,lWidth);



   //将结果赋值到原图像中

   for(i=0;i<lHeight;i++)
   {
     for(j=0;j<lWidth;j++)
	 {
	   lpSrc=lpDIBBits+i*lLineBytes+j;

       if(image[i*lWidth+j]==1)
	   *lpSrc=(BYTE)0;

	   else
       *lpSrc=(BYTE)255;
	 }
   
   }


 //清空内存
   free(image);
   ::GlobalUnlock ((HGLOBAL)hDIB);

	return;
}

/*****************************************************
* 
*   函数名称：
*      Template：
*
*    参数：
*	   HDIB    hDIB         －图像的句柄
*      double  *tem         －指向模板的指针
*      int  tem_w           －模板的宽度
*      int  tem_h           －模板的高度
*      double xishu         －模板的系数
*         
*    功能：
*	   对图像进行模板操作
*
*    说明：
*	   为处理方便起见，模板的宽度和高度都应为奇数
*******************************************************/
 HDIB Template(HDIB hDIB,double * tem ,int tem_w,int tem_h,double xishu)
{

    //统计中间值
    double sum;

    //指向图像起始位置的指针
    BYTE *lpDIB=(BYTE*)::GlobalLock((HGLOBAL) hDIB);

	//指向象素起始位置的指针
	BYTE *pScrBuff =(BYTE*)::FindDIBBits((char*)lpDIB);
   
	//获取图像的颜色信息
    int numColors=(int) ::DIBNumColors((char *)lpDIB);

    //如果图像不是256色返回
     if (numColors!=256) 
	 {   
        //解除锁定
	  	::GlobalUnlock((HGLOBAL) hDIB);

		//返回
		return(hDIB);
	 }
    
    //将指向图像象素起始位置的指针，赋值给指针变量
    BYTE* oldbuf = pScrBuff;

    //循环变量
    int i,j,m,n;

	int w, h, dw;

	//获取图像的宽度
	w = (int) ::DIBWidth((char *)lpDIB);
	
	//获取图像的高度
	h = (int) ::DIBHeight((char *)lpDIB);
	
	//计算图像每行的字节数
	dw = (w+3)/4*4;      
	
	//建立一个和原图像大小相同的25色灰度位图
    HDIB newhDIB=NewDIB(w,h,8);  
    
	//指向新的位图的指针
	BYTE *newlpDIB=(BYTE*)::GlobalLock((HGLOBAL) newhDIB);

	//指向新的位图的象素起始位置的指针 
    BYTE *destBuf = (BYTE*)FindDIBBits((char *)newlpDIB);
    
   //将指向新图像象素起始位置的指针，赋值给指针变量
    BYTE *newbuf=destBuf; 
	
	//对图像进行扫描
   
	//行 
    for(i=0;i<h;i++)
    {  
		//列
	   for(j=0;j<w;j++)
	   {   

		   //为统计变量赋初始值
	       sum=0;

         //对于图像的4个边框的象素保持原灰度不变
	     if( j<((tem_w-1)/2) || j>(w-(tem_w+1)/2) || i<((tem_h-1)/2) || i>(h-(tem_h+1)/2) )
	      *(newbuf+i*dw+j)=*(oldbuf+i*dw+j);
		 
         //对于其他的象素进行模板操作
		 else 
         { 

          //将点（i,j）点作为模板的中心
          for(m=i-((tem_h-1)/2);m<=i+((tem_h-1)/2);m++)
          {
		     for(n=j-((tem_w-1)/2);n<=j+((tem_w-1)/2);n++)
		    
             //将以点（i，j）为中心，与模板大小相同的范围内的象素与模板对用位置的系数
			 //进行相乘并线形叠加
		     sum+=*(oldbuf+m*dw+n)* tem[(m-i+((tem_h-1)/2))*tem_w+n-j+((tem_w-1)/2)];
		  
		  }
          
		  //将结果乘上总的模板系数
          sum=(int)sum*xishu;

		  //计算绝对值
		  sum = fabs(sum);

		  //如果小于0，强制赋值为0
          if(sum<0)     
          sum=0;

		  //如果大于255，强制赋值为255
          if(sum>255)
		  sum=255;

		  //将计算的结果放到新的位图的相应位置
	      *(newbuf+i*dw+j)=sum;
		 }
	   }
	} 
   
	//解除锁定
	::GlobalUnlock((HGLOBAL)hDIB);
    
	//返回新的位图的句柄
    return(newhDIB);
}
/*****************************************************
* 
*   函数名称：
*      Template：
*
*    参数：
*	   HDIB    hDIB         －图像的句柄
*      int  tem_w           －模板的宽度
*      int  tem_h           －模板的高度
*      
*    功能：
*	   对图像进行中值
*
*    说明：
*	   为处理方便起见，模板的宽度和高度都应为奇数
*******************************************************/

HDIB MidFilter(HDIB hDIB,int tem_w,int tem_h)
{

    //统计中间值
    double mid;

	BYTE *temp=(BYTE*)malloc(tem_w*tem_h*sizeof(BYTE));

    //指向图像起始位置的指针
    BYTE *lpDIB=(BYTE*)::GlobalLock((HGLOBAL) hDIB);

	//指向象素起始位置的指针
	BYTE *pScrBuff =(BYTE*)::FindDIBBits((char*)lpDIB);
   
	//获取图像的颜色信息
    int numColors=(int) ::DIBNumColors((char *)lpDIB);

    //如果图像不是256色返回
     if (numColors!=256) 
	 {   
        //解除锁定
	  	::GlobalUnlock((HGLOBAL) hDIB);

		//返回
		return(hDIB);
	 }
    
    //将指向图像象素起始位置的指针，赋值给指针变量
    BYTE* oldbuf = pScrBuff;

    //循环变量
    int i,j,m,n;

	int w, h, dw;

	//获取图像的宽度
	w = (int) ::DIBWidth((char *)lpDIB);
	
	//获取图像的高度
	h = (int) ::DIBHeight((char *)lpDIB);
	
	//计算图像每行的字节数
	dw = (w+3)/4*4;      
	
	//建立一个和原图像大小相同的25色灰度位图
    HDIB newhDIB=NewDIB(w,h,8);  
    
	//指向新的位图的指针
	BYTE *newlpDIB=(BYTE*)::GlobalLock((HGLOBAL) newhDIB);

	//指向新的位图的象素起始位置的指针 
    BYTE *destBuf = (BYTE*)FindDIBBits((char *)newlpDIB);
    
   //将指向新图像象素起始位置的指针，赋值给指针变量
    BYTE *newbuf=destBuf; 
	
	//对图像进行扫描
   
	//行 
    for(i=0;i<h;i++)
    {  
		//列
	   for(j=0;j<w;j++)
	   {   

		   //为统计变量赋初始值
	       

         //对于图像的4个边框的象素保持原灰度不变
	     if( j<((tem_w-1)/2) || j>(w-(tem_w+1)/2) || i<((tem_h-1)/2) || i>(h-(tem_h+1)/2) )
	      *(newbuf+i*dw+j)=*(oldbuf+i*dw+j);
		 
         //对于其他的象素进行模板操作
		 else 
         { 

          //将点（i,j）点作为模板的中心
          for(m=i-((tem_h-1)/2);m<=i+((tem_h-1)/2);m++)
          {
		     for(n=j-((tem_w-1)/2);n<=j+((tem_w-1)/2);n++)
		    
             //将以点（i，j）为中心，与模板大小相同的范围内的象素传递到模板矩阵中
		     temp[(m-i+((tem_h-1)/2))*tem_w+n-j+((tem_w-1)/2)]=*(oldbuf+m*dw+n);
		  
		  }
          
		 //利用气泡法计算中值
           for(m=0;m<tem_w*tem_h-1;m++)
           {
		   
		      for(n=0;n<tem_w*tem_h-m-1;n++)
			  {
			    if(temp[n]>temp[n+1]) 
			    mid=temp[n];
                temp[n]=temp[n+1];
			    temp[n+1]=mid;
			  }
		   
		   } 

           //将计算的结果放到新的位图的相应位置
	      *(newbuf+i*dw+j)=temp[(tem_w*tem_h-1)/2];
		 }
	   }
	} 
   
	//解除锁定
	::GlobalUnlock((HGLOBAL)hDIB);
    
	//返回新的位图的句柄
    return(newhDIB);
}



/*************************************************************************
 *
 * 函数名称：
 *   Equalize()
 *
 * 参数:
 *   HDIB hDIB
 *
 *
 * 说明:
 *   该函数用来对图像进行直方图均衡。
 *
 ************************************************************************/
void Equalize(HDIB hDIB)
{
	BYTE* lpDIB=(BYTE*)::GlobalLock ((HGLOBAL)hDIB);
	BYTE* lpDIBBits=(BYTE*)::FindDIBBits((char*)lpDIB);
	LONG lHeight=::DIBHeight ((char*)lpDIB);
	LONG lWidth=::DIBWidth ((char*)lpDIB);
	// 指向源图像的指针
	unsigned char*	lpSrc;
	
	// 临时变量
	LONG	lTemp;
	
	// 循环变量
	LONG	i;
	LONG	j;
	
	// 灰度映射表
	BYTE	bMap[256];
	
	// 灰度映射表
	LONG	lCount[256];
	
	// 图像每行的字节数
	LONG	lLineBytes;
	
	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// 重置计数为0
	for (i = 0; i < 256; i ++)
	{
		// 清零
		lCount[i] = 0;
	}
	
	// 计算各个灰度值的计数
	for (i = 0; i < lHeight; i ++)
	{
		for (j = 0; j < lWidth; j ++)
		{
			lpSrc = (unsigned char *)lpDIBBits + lLineBytes * i + j;
			
			// 计数加1
			lCount[*(lpSrc)]++;
		}
	}
	
	// 计算灰度映射表
	for (i = 0; i < 256; i++)
	{
		// 初始为0
		lTemp = 0;
		
		for (j = 0; j <= i ; j++)
		{
			lTemp += lCount[j];
		}
		
		// 计算对应的新灰度值
		bMap[i] = (BYTE) (lTemp * 255 / lHeight / lWidth);
	}
	
	// 每行
	for(i = 0; i < lHeight; i++)
	{
		// 每列
		for(j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// 计算新的灰度值
			*lpSrc = bMap[*lpSrc];
		}
	}
	
	::GlobalUnlock ((HGLOBAL)hDIB);
}

