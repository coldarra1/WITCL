#include "stdafx.h"
#include "windowsx.h"
#include "math.h"
#include "HuiDuBianHuanDib.h"
#include "MainFrm.h"
#include "DynSplitView2.h"
 
HuiDuBianHuanDib::HuiDuBianHuanDib()
{
}
HuiDuBianHuanDib::~HuiDuBianHuanDib()
{
}

///***************************************************************/           
/*函数名称：FanSeBianHuan()                                        
/*函数类型：void                                           
/*功能：对图像进行反色变换                            
/***************************************************************/
void HuiDuBianHuanDib::FanSeBianHuan()//对图像进行反色变换
{
	LPBYTE  p_data;     //原图数据区指针
	int wide,height;    //原图长、宽
	p_data=this->GetData ();     //取得原图的数据区指针
	if(m_pBitmapInfoHeader->biBitCount<9)		
		wide=this->GetWidth ();
	else
		wide=this->GetDibWidthBytes();
	height=this->GetHeight ();
	for(int i=0;i<height*wide;i++)
	{
		unsigned char  temp;
		temp=*(p_data+i);
		*(p_data+i)=255- temp;
	}	
}

///***************************************************************/           
/*函数名称：Fei0()												*/
/*函数类型：void												*/
/*功能：对图像进行非零取一运算。								*/
/****************************************************************/
void HuiDuBianHuanDib::Fei0()//对图像进行非零取一运算
{
	LPBYTE p_data;     //原图数据区指针
	int wide,height;    //原图长、宽
	p_data=this->GetData ();     //取得原图的数据区指针
	if(m_pBitmapInfoHeader->biBitCount<9)		
		wide=this->GetWidth ();
	else
		wide=this->GetDibWidthBytes();
	height=this->GetHeight ();
	for(int j=0;j<height;j++)
	{
		for(int i=0;i<wide;i++)    //所有像素依次循环
		{
			if(*p_data!=0)          //若像素值不为0
				*p_data=255;         //将其置为255
			p_data++; 				 
		}
	}
}

/***************************************************************/           
/*函数名称：GuDing(int YuZhi)                                  */      
/*函数类型：void											   */	
/*参数说明：YuZhi 给定阈值                                     */       
/*功能：对图像进行固定阀值运算。                               */
/***************************************************************/
void HuiDuBianHuanDib::GuDing(int YuZhi)//对图像进行固定阀值运算
{
	LPBYTE  p_data;     //原图数据区指针
	int wide,height;    //原图长、宽
	p_data=this->GetData ();     //取得原图的数据区指针
	if(m_pBitmapInfoHeader->biBitCount<9)		
		wide=this->GetWidth ();
	else
		wide=this->GetDibWidthBytes();
	height=this->GetHeight ();
	for(int j=0;j<height;j++)
	{
		for(int i=0;i<wide;i++)
		{
			if(*p_data>YuZhi)          //灰度值大于给定阈值，置为255
				*p_data=255;
			else
				*p_data=0;             //不大于置为0
			p_data++;
		}
	}
}











//自适应法
void HuiDuBianHuanDib::zishiying()//对图像进行固定阀值运算
{
	LPBYTE  p_data;     //原图数据区指针
	int wide,height;    //原图长、宽
	p_data=this->GetData ();     //取得原图的数据区指针
/*	if(m_pBitmapInfoHeader->biBitCount<9)		
		wide=this->GetWidth ();
	else
		wide=this->GetDibWidthBytes();
	height=this->GetHeight ();*/

		// 循环变量
	int i;
	int j;
	// 灰度计数
	int huidu[256];    
	//int wide,height;    //原图长、宽
	wide=this->GetWidth ();	
	if(this->m_pBitmapInfoHeader->biBitCount<9)	{
		height=this->GetHeight ();
	}
	else
		height=(this->GetHeight ())*3;
	// 变量初始化
	memset(huidu,0,sizeof(huidu));
	LPBYTE  temp1=new BYTE[wide*height];    //新图像缓冲区
	//拷贝原图像到缓存图像
	memcpy(temp1,m_pData,wide*height );
	// 对各像素进行灰度统计
	for (j = 0; j < height; j ++)
	{
		for (i = 0; i <wide; i ++)
		{
			unsigned char  temp = temp1[wide* j + i] ;
			// 灰度统计计数
			huidu[temp]++;
		}
	}

	//求窗口变换的上限和下限
	//
	long temp[16];
	int k=0;
	int a;
	for(k=0;k<16;k++)
	{
		temp[k]=0;
		for(a=k*16;a<(k+1)*16;a++)
			temp[k]+=huidu[a];
	}
	
	long max=0;
	int t=0;
	for(k=15;k>=0;k--)
	{
		if(temp[k]>max)
		{
			max=temp[k];
			t=k;
		}
		
	}
	
	int bLow=0,bUp=0;
	bLow=(t-1)*16;
	//	bUp=(t+5)*16;
	
	//	bLow=100;
	bUp=255;
	// 阈值
	INT	bThre;
	
	bThre=(INT)((2*bUp+bLow)/3);
     
	int b,c;
	for( b=0;b<height;b++)
	{
		for( c=0;c<wide;c++)
		{
			if(*p_data>bThre)          //灰度值大于给定阈值，置为255
				*p_data=255;
			else
				*p_data=0;             //不大于置为0
			p_data++;
		}
	}
}
///////////////////////////////////////////////////////////////////
void HuiDuBianHuanDib::bianyuanjiance()//边缘检测
{
	LPBYTE  p_data;     //原图数据区指针
	int wide,height;    //原图长、宽
	p_data=this->GetData ();     //取得原图的数据区指针
	if(m_pBitmapInfoHeader->biBitCount<9)		
		wide=this->GetWidth ();
	else
		wide=this->GetDibWidthBytes();
//	if(this->m_pBitmapInfoHeader->biBitCount==9)	{
		height=this->GetHeight ();
//	}
//	else
//		height=(this->GetHeight ())*3;
	
	BYTE *temp=new BYTE[wide*height];
	memcpy(temp,p_data,wide*height);


	int fres;

	for(int j=0;j<height-1;j++)
	{
		for(int i=0;i<wide-1;i++)
		{
			fres = p_data[wide*j+i]-p_data[wide*j+i+1];
			if(fres<0)fres=-fres;
			if(fres>255)temp[wide*i+j]=255;
			else
			{temp[wide*j+i]=(int)(fres+0.5);}

		}
	}
	memcpy(p_data,temp,wide*height);
}

/***************************************************************/
/*函数名称：MakegGray()                                        */
/*函数类型：void                                               */
/*功能：真彩色转化成256色灰度图像。                            */
/***************************************************************/
void HuiDuBianHuanDib::MakegGray()    //灰度变化
{
	BYTE *p_data;     //原图数据区指针
	int wide,height,DibWidth;    //原图长、宽、字节宽
	p_data=this->GetData ();   //取得原图的数据区指针
    wide=this->GetWidth ();   //取得原图的数据区宽度
    height=this->GetHeight ();   //取得原图的数据区高度
	DibWidth=this->GetDibWidthBytes();   //取得原图的每行字节数
	for(int j=0;j<height;j++)	// 每行
		for(int i=0;i<DibWidth;i+=3)	// 每列
		{
			BYTE* pbyBlue = p_data++;   //得到蓝色值
			BYTE* pbyGreen = p_data++;  //得到绿色值
			BYTE* pbyRed = p_data++;    //得到红色值
			BYTE r = *pbyRed;
			BYTE g = *pbyGreen;
			BYTE b = *pbyBlue;
			//取到原r,g,b中的最大值作为像素三分量值的新值
			int gray;
		/*	if(r>g)
				gray=r;
			else 
				gray=g;
			if(gray<b)
				gray=b;	*/
			gray=(r)*0.299 + (g)*0.588 + (b)*0.114 ;
       		*pbyBlue = gray;     //将取到的最大值赋给像素的蓝分量
			*pbyGreen = gray;    //将取到的最大值赋给像素的绿分量
			*pbyRed = gray;	     //将取到的最大值赋给像素的红分量
		}
}

/*************************************************************************
*
* 函数名称：
*   MedianFilter()
*
* 参数:
*   LPSTR lpDIBBits		- 指向源DIB图像指针
*   LONG  lWidth			- 源图像宽度（象素数）
*   LONG  lHeight			- 源图像高度（象素数）
*   int   iFilterH			- 滤波器的高度
*   int   iFilterW			- 滤波器的宽度
*   int   iFilterMX		- 滤波器的中心元素X坐标
*   int   iFilterMY		- 滤波器的中心元素Y坐标
*
* 返回值:
*   BOOL					- 成功返回TRUE，否则返回FALSE。
*
* 说明:
*   该函数对DIB图像进行中值滤波。
*
************************************************************************/

BOOL HuiDuBianHuanDib::  myMedianFilter(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, 
						   int iFilterH, int iFilterW, 
						   int iFilterMX, int iFilterMY,long LB)
{
	
	// 指向源图像的指针
	unsigned char*	lpSrc;
	
	// 指向要复制区域的指针
	unsigned char*	lpDst;
	
	// 指向复制图像的指针
	LPSTR			lpNewDIBBits;
	HLOCAL			hNewDIBBits;
	
	// 指向滤波器数组的指针
	unsigned char	* aValue;
	HLOCAL			hArray;
	
	// 循环变量
	LONG			i;
	LONG			j;
	LONG			k;
	LONG			l;
	
	// 图像每行的字节数
	LONG			lLineBytes;
	
	// 计算图像每行的字节数
	lLineBytes = LB;
	
	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lLineBytes * lHeight);
	
	// 判断是否内存分配失败
	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}
	
	// 锁定内存
	lpNewDIBBits = (char * )LocalLock(hNewDIBBits);
	
	// 初始化图像为原始图像
	memcpy(lpNewDIBBits, lpDIBBits, lLineBytes * lHeight);
	
	// 暂时分配内存，以保存滤波器数组
	hArray = LocalAlloc(LHND, iFilterH * iFilterW);
	
	// 判断是否内存分配失败
	if (hArray == NULL)
	{
		// 释放内存
		LocalUnlock(hNewDIBBits);
		LocalFree(hNewDIBBits);
		
		// 分配内存失败
		return FALSE;
	}
	
	// 锁定内存
	aValue = (unsigned char * )LocalLock(hArray);
	
	// 开始中值滤波
	// 行(除去边缘几行)
	for(i = iFilterMY; i < lHeight - iFilterH + iFilterMY + 1; i++)
	{
		// 列(除去边缘几列)
		for(j = iFilterMX; j < lWidth - iFilterW + iFilterMX + 1; j++)
		{
			// 指向新DIB第i行，第j个象素的指针
			lpDst = (unsigned char*)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// 读取滤波器数组
			for (k = 0; k < iFilterH; k++)
			{
				for (l = 0; l < iFilterW; l++)
				{
					// 指向DIB第i - iFilterMY + k行，第j - iFilterMX + l个象素的指针
					lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i + iFilterMY - k) + j - iFilterMX + l;
					
					// 保存象素值
					aValue[k * iFilterW + l] = *lpSrc;
				}
			}
			
			// 获取中值
			* lpDst = myGetMedianNum(aValue, iFilterH * iFilterW);
		}
	}
	
	// 复制变换后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lLineBytes * lHeight);
	
	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);
	LocalUnlock(hArray);
	LocalFree(hArray);
	
	// 返回
	return TRUE;
}


/*************************************************************************
*
* 函数名称：
*   GetMedianNum()
*
* 参数:
*   unsigned char * bpArray	- 指向要获取中值的数组指针
*   int   iFilterLen			- 数组长度
*
* 返回值:
*   unsigned char      - 返回指定数组的中值。
*
* 说明:
*   该函数用冒泡法对一维数组进行排序，并返回数组元素的中值。
*
************************************************************************/

unsigned char HuiDuBianHuanDib:: myGetMedianNum(unsigned char * bArray, int iFilterLen)
{
	// 循环变量
	int		i;
	int		j;
	
	// 中间变量
	unsigned char bTemp;
	
	// 用冒泡法对数组进行排序
	for (j = 0; j < iFilterLen - 1; j ++)
	{
		for (i = 0; i < iFilterLen - j - 1; i ++)
		{
			if (bArray[i] > bArray[i + 1])
			{
				// 互换
				bTemp = bArray[i];
				bArray[i] = bArray[i + 1];
				bArray[i + 1] = bTemp;
			}
		}
	}
	
	// 计算中值
	if ((iFilterLen & 1) > 0)
	{
		// 数组有奇数个元素，返回中间一个元素
		bTemp = bArray[(iFilterLen + 1) / 2];
	}
	else
	{
		// 数组有偶数个元素，返回中间两个元素平均值
		bTemp = (bArray[iFilterLen / 2] + bArray[iFilterLen / 2 + 1]) / 2;
	}
	
	// 返回中值
	return bTemp;
}

/*************************************************************************
*
* 函数名称：
*   myHprojectDIB()
*
* 参数:
*   LPSTR lpDIBBits    - 指向源DIB图像指针
*   LONG  lWidth       - 源图像宽度（象素数）
*   LONG  lHeight      - 源图像高度（象素数）
*   INT*  iTop         - 车牌上边缘
*   INT*  iBottom      - 车牌下边缘
* 返回值:
*   BOOL               - 成功返回TRUE，否则返回FALSE。
*
* 说明:
*   该函数用于对含车牌图像进行水平投影运算，求取车牌子图像的上下边缘位置
*
************************************************************************/
BOOL HuiDuBianHuanDib:: myHprojectDIB(LPSTR lpDIB, LONG lWidth, LONG lHeight, 
						  int* iTop, int* iBottom) 
{
	LPSTR lpDIBBits;                   //指向DIB的象素的指针
	
    LONG lLineBytes;                   // 图像每行的字节数
	unsigned char * lpSrc;             //指向原图像象素点的指针
	
	unsigned char pixel;				//像素值
	
	int i,j;
	
	// 计算结果
	INT* iResult;
	
	INT pzBottom,pzTop;
	
	bool findPZ=false;
	
	// 找到DIB图像象素起始位置
	lpDIBBits = (char*)this->GetData ();
	
	// 计算图像每行的字节数
	lLineBytes =this->GetDibWidthBytes();
	
	iResult=new INT[lHeight];
	
	for(i=0;i<lHeight;i++)
		iResult[i]=0;
	
	for(j=lHeight/5;j<lHeight*0.8;j++)
	{
		iResult[j]=0;
		for(i=0;i<lWidth;i++)
		{
			lpSrc=(unsigned char*)lpDIBBits+lLineBytes*j+i;
			pixel=(unsigned char)(*lpSrc);
			if(pixel==255)
			{
				iResult[j]++;
			}
		}
		if((!findPZ)&&iResult[j]>12)
		{
			pzBottom=j;
			findPZ=true;
		}
		if(findPZ&&iResult[j]<12)
		{
			pzTop=j;
			break;
		}
		
	}
	pzTop=pzBottom+55;
	pzBottom=pzBottom-20;   //微量调整
	*iBottom=lHeight-pzBottom;
	*iTop=lHeight-pzTop;
	return true;
}
/*************************************************************************
*
* 函数名称：
*   myVprojectDIB()
*
* 参数:
*   LPSTR lpDIBBits    - 指向源DIB图像指针
*   LONG  lWidth       - 源图像宽度（象素数）
*   LONG  lHeight      - 源图像高度（象素数）
*   INT*  iLeft        - 车牌左边缘
*   INT*  iRight       - 车牌右边缘
* 返回值:
*   BOOL               - 成功返回TRUE，否则返回FALSE。
*
* 说明:
*   该函数用于对含车牌图像进行垂直投影运算，求取车牌子图像的左右边缘位置
*
************************************************************************/
BOOL HuiDuBianHuanDib:: myVprojectDIB(LPSTR lpDIB, LONG lWidth, LONG lHeight, 
						  int* iLeft, int* iRight) 
{
	LPSTR lpDIBBits;                   //指向DIB的象素的指针
	
    LONG lLineBytes;                   // 图像每行的字节数
	unsigned char * lpSrc;             //指向原图像象素点的指针
	
	unsigned char pixel;				//像素值
	
	int i,j;
	
	// 计算结果
	INT* iResult;
	
	INT pzLeft,pzRight;
	
	bool findPZ=false;
	
	// 找到DIB图像象素起始位置
	lpDIBBits =  (char*)this->GetData ();
	
	// 计算图像每行的字节数
	lLineBytes = this->GetDibWidthBytes();
	
	iResult=new INT[lWidth];
	
	for(i=0;i<lWidth;i++)
		iResult[i]=0;
	
	for(i=lWidth/5;i<lWidth*0.8;i++)
	{
		iResult[i]=0;
		for(j=0;j<lHeight;j++)
		{
			lpSrc=(unsigned char*)lpDIBBits+lLineBytes*j+i;
			pixel=(unsigned char)(*lpSrc);
			if(pixel==255)
			{
				iResult[i]++;
			}
		}
		if((!findPZ)&&iResult[i]>10)
		{
			pzLeft=i;
			findPZ=true;
		}
		pzRight=pzLeft+150;
	}
	
	*iLeft=pzLeft;
	*iRight=pzRight+10;
	return true;
}

//车牌分割//////////////////////水平投影

BOOL HuiDuBianHuanDib:: myHcut(LPSTR lpDIB, LONG lWidth, LONG lHeight, 
						  int* iTop, int* iBottom) 
{
	LPSTR lpDIBBits;                   //指向DIB的象素的指针
	
    LONG lLineBytes;                   // 图像每行的字节数
	unsigned char * lpSrc;             //指向原图像象素点的指针
	
	unsigned char pixel;				//像素值
	
	int i,j;
	
//	int r;                               //记录上一行投影值
	// 计算结果
	INT* iResult;
	
	INT pzBottom,pzTop;
	
	bool findPZ=false;
	
	// 找到DIB图像象素起始位置
	lpDIBBits = (char*)this->GetData ();
	
	// 计算图像每行的字节数
	lLineBytes =this->GetDibWidthBytes();
	
	iResult=new INT[lHeight];
	
	for(i=0;i<lHeight;i++)
		iResult[i]=0;
	
	for(j=0;j<lHeight;j++)
	{
		iResult[j]=0;
		for(i=0;i<lWidth;i++)
		{
			lpSrc=(unsigned char*)lpDIBBits+lLineBytes*j+i;
			pixel=(unsigned char)(*lpSrc);
			if(pixel==255)
			{
				iResult[j]++;
			}
		}
/*		if((!findPZ)&&iResult[j]>(lWidth/3)&&r>(lWidth/3))
		{
			pzBottom=j;
			findPZ=true;
		}
		if(findPZ&&iResult[j]<(lWidth/6)&&r>(lWidth/5))
		{
			pzTop=j;
			break;
		}*/
//		r=iResult[j];
	}
	for(j=0;j<lHeight;j++)
	{
		if((!findPZ)&&iResult[j]>(lWidth/3)&&iResult[j+1]>(lWidth/3)&&iResult[j+2]>(lWidth/3)&&iResult[j+3]>(lWidth/3))
		{
			pzBottom=j;
			findPZ=true;
		}
		if(findPZ&&iResult[j]>(lWidth/5)&&iResult[j+1]<(lWidth/6))
		{
			pzTop=j;
			break;
		}

	}

	pzTop=pzTop+1;
	pzBottom=pzBottom-2;   //微量调整
	*iBottom=pzBottom;
	*iTop=pzTop;
	return true;
}

//车牌分割//////////////////////垂直投影
BOOL HuiDuBianHuanDib:: myVcut(LPSTR lpDIB, LONG lWidth, LONG lHeight, 
						  int* r1, int* l1,int* r2, int* l2,int* r3, int* l3,int* r4, int* l4,int* r5, int* l5
						  ,int* r6, int* l6,int* r7, int* l7) 
{
	LPSTR lpDIBBits;                   //指向DIB的象素的指针
	
    LONG lLineBytes;                   // 图像每行的字节数
	unsigned char * lpSrc;             //指向原图像象素点的指针
	
	unsigned char pixel;				//像素值
	
	int i,j;
	
	// 计算结果
	INT* iResult;
	
	INT pzLeft,pzRight;
	
	bool findPZ=false;
	
	// 找到DIB图像象素起始位置
	lpDIBBits =  (char*)this->GetData ();
	
	// 计算图像每行的字节数
	lLineBytes = this->GetDibWidthBytes();
	
	iResult=new INT[lWidth];
	
	for(i=0;i<lWidth;i++)
		iResult[i]=0;
	
	for(i=0;i<lWidth;i++)
	{
		iResult[i]=0;
		for(j=0;j<lHeight;j++)
		{
			lpSrc=(unsigned char*)lpDIBBits+lLineBytes*j+i;
			pixel=(unsigned char)(*lpSrc);
			if(pixel==255)
			{
				iResult[i]++;
			}
		}

	}
	for(i=0;i<lWidth;i++)
	{
		if((!findPZ)&&iResult[i]>(lHeight/10)&&iResult[i+1]>(lHeight/10)&&iResult[i+2]>(lHeight/10)&&iResult[i+3]>(lHeight/10))
		{
			*l1=i;
			findPZ=true;
		}
		if(findPZ&&iResult[i]<(lHeight/11)&&iResult[i-1]>(lHeight/11)&&iResult[i-2]>(lHeight/11))
		{
			*r1=i;
			findPZ=false;
			break;
		}
	}
	for(;i<lWidth;i++)
	{
		if((!findPZ)&&iResult[i]>(lHeight/10)&&iResult[i+1]>(lHeight/10)&&iResult[i+2]>(lHeight/10)&&iResult[i+3]>(lHeight/10))
		{
			*l2=i;
			findPZ=true;
		}
		if(findPZ&&iResult[i]<(lHeight/10)&&iResult[i-1]>(lHeight/10)&&iResult[i-2]>(lHeight/10))
		{
			*r2=i;
			findPZ=false;
			break;
		}
	}
	for(;i<lWidth;i++)
	{
		if((!findPZ)&&iResult[i]>(lHeight/10)&&iResult[i+1]>(lHeight/10)&&iResult[i+2]>(lHeight/10)&&iResult[i+3]>(lHeight/10))
		{
			*l3=i;
			findPZ=true;
		}
		if(findPZ&&iResult[i]<(lHeight/10)&&iResult[i-1]>(lHeight/10)&&iResult[i-2]>(lHeight/10))
		{
			*r3=i;
			findPZ=false;
			break;
		}
	}
	for(;i<lWidth;i++)
	{
		if((!findPZ)&&iResult[i]>(lHeight/10)&&iResult[i+1]>(lHeight/10)&&iResult[i+2]>(lHeight/10)&&iResult[i+3]>(lHeight/10))
		{
			*l4=i;
			findPZ=true;
		}
		if(findPZ&&iResult[i]<(lHeight/10)&&iResult[i-1]>(lHeight/10)&&iResult[i-2]>(lHeight/10))
		{
			*r4=i;
			findPZ=false;
			break;
		}
	}
	for(;i<lWidth;i++)
	{
		if((!findPZ)&&iResult[i]>(lHeight/10)&&iResult[i+1]>(lHeight/10)&&iResult[i+2]>(lHeight/10)&&iResult[i+3]>(lHeight/10))
		{
			*l5=i;
			findPZ=true;
		}
		if(findPZ&&iResult[i]<(lHeight/10)&&iResult[i-1]>(lHeight/10)&&iResult[i-2]>(lHeight/10))
		{
			*r5=i;
			findPZ=false;
			break;
		}
	}
	for(;i<lWidth;i++)
	{
		if((!findPZ)&&iResult[i]>(lHeight/10)&&iResult[i+1]>(lHeight/10)&&iResult[i+2]>(lHeight/10)&&iResult[i+3]>(lHeight/10))
		{
			*l6=i;
			findPZ=true;
		}
		if(findPZ&&iResult[i]<(lHeight/10)&&iResult[i-1]>(lHeight/10)&&iResult[i-2]>(lHeight/10))
		{
			*r6=i;
			findPZ=false;
			break;
		}
	}
	for(;i<lWidth;i++)
	{
		if((!findPZ)&&iResult[i]>(lHeight/10)&&iResult[i+1]>(lHeight/10)&&iResult[i+2]>(lHeight/10)&&iResult[i+3]>(lHeight/10))
		{
			*l7=i;
			findPZ=true;
		}
		if(findPZ&&iResult[i]<(lHeight/11)&&iResult[i-1]>(lHeight/11)&&iResult[i-2]>(lHeight/11))
		{
			*r7=i;
			findPZ=false;
			break;
		}
	}

//	*iLeft=pzLeft;
//	*iRight=pzRight+10;
	return true;
}











/***************************************************************/           
/*函数名称：ShuangYu(int YuZhi1,int YuZhi2,int mode)          */
/*参数：int YuZhi1：阈值1；int YuZhi2：阈值2；int mode：处理方式*/
/*函数类型：void                                              */
/*功能：对图像使用双固定阈值法进行二值化。                     */
/***************************************************************/
void HuiDuBianHuanDib::ShuangYu(int YuZhi1,int YuZhi2,int mode)
{
	LPBYTE  p_data;     //原图数据区指针
	int wide,height;    //原图长、宽
	p_data=this->GetData ();
	if(m_pBitmapInfoHeader->biBitCount<9)		
		wide=this->GetWidth ();
	else
		wide=this->GetDibWidthBytes();
	height=this->GetHeight ();
	if(mode==0)    //0-255-0型
	{
		for(int j=0;j<height;j++)
			for(int i=0;i<wide;i++)
			{
				//若该像素的灰度值介于两个阈值之间，这将其置为255
				if(*p_data>=YuZhi1&&*p_data<=YuZhi2)
					*p_data=255;
				else
					*p_data=0;     //否则置0
				p_data++; 			 		
			}	
	}
	if(mode==1)    //255-0-255型
	{
		for(int j=0;j<height;j++)
			for(int i=0;i<wide;i++)
			{
				//若该像素的灰度值介于两个阈值之间，这将其置为0
				if(*p_data>=YuZhi1&&*p_data<=YuZhi2)
					*p_data=0;
				else
					*p_data=255;    //否则置255
				p_data++; 					
			}
	}			 
}

///***************************************************************/           
/*函数名称：ZhiFangTu(float *tongji)                               
/*函数类型：void                                         
/*变量说明：tongji  灰度分布密度统计                                                        
/*功能：对图像进行灰度直方图统计。                     
/***************************************************************/
void HuiDuBianHuanDib::ZhiFangTu(float *tongji)
{
	// 循环变量
	int i;
	int j;
	// 灰度计数
	int huidu[256];    
	int wide,height;    //原图长、宽
	wide=this->GetWidth ();		 
	height=this->GetHeight ();
	// 变量初始化
	memset(huidu,0,sizeof(huidu));
	LPBYTE  temp1=new BYTE[wide*height];    //新图像缓冲区
	//拷贝原图像到缓存图像
	memcpy(temp1,m_pData,wide*height );
	// 对各像素进行灰度统计
	for (j = 0; j < height; j ++)
	{
		for (i = 0; i <wide; i ++)
		{
			unsigned char  temp = temp1[wide* j + i] ;
			if(temp==255)
			// 灰度统计计数
			huidu[i]++;
		}
	}


	// 计算灰度分布密度
	for(i=0;i<256;i++)
		tongji[i] = huidu[i] / (height * wide *1.0f);	
}

///***************************************************************/           
/*函数名称：Zhexianbianhuan(BYTE bX1,BYTE bY1,BYTE bX2,BYTE bY2)                                           */
/*函数类型：void                                              */
/*变量说明：bX1折点一的原始灰度；bX2bY1折点二的原始灰度
/*          bY1折点一的变换灰度；bY2折点二的变换灰度                                                       
/*功能：对图像进行分段线性变换。                      */
/***************************************************************/ 
void HuiDuBianHuanDib::Zhexianbianhuan(BYTE bX1, BYTE bY1, BYTE bX2, BYTE bY2)
{ 
	// 循环变量
	int i;
	int j;
	int wide;
	int height;
	LPBYTE  p_data;
	p_data=this->GetData ();     //取得原图的数据区指针
	wide=this->GetWidth ();
	height=this->GetHeight ();
	LPBYTE temp=new BYTE[wide*height];    //新图像缓冲区
	//拷贝原图像到缓存图像
	memcpy(temp,p_data,wide*height);
	// 灰度映射表
	BYTE	bMap[256];
	// 计算灰度映射表
	for (i = 0; i <= bX1; i++)	//[0 —— X1]
	{
		// 判断bX1是否大于0（防止分母为0）
		if (bX1 > 0)
		{
			// 线性变换
			bMap[i] = (BYTE) bY1 * i / bX1;
		}
		else
		{
			// 直接赋值为0
			bMap[i] = 0;
		}
	}
	for (; i <= bX2; i++)		//(X1 —— X2]
	{
		// 判断bX1是否等于bX2（防止分母为0）
		if (bX2 != bX1)
		{
			// 线性变换
			bMap[i] = bY1 + (BYTE) ((bY2 - bY1) * (i - bX1) / (bX2 - bX1));
		}
		else
		{
			// 直接赋值为bY1
			bMap[i] = bY1;
		}
	}
	for (; i < 256; i++)		//(X2 —— 256)
	{
		// 判断bX2是否等于255（防止分母为0）
		if (bX2 != 255)
		{
			// 线性变换
			bMap[i] = bY2 + (BYTE) ((255 - bY2) * (i - bX2) / (255 - bX2));
		}
		else
		{
			// 直接赋值为255
			bMap[i] = 255;
		}
	}
	if  (m_pBitmapInfoHeader->biBitCount<9)		//灰度图像
	{
		// 对各像素进行灰度转换
		for (i = 0; i < height; i ++)
		{
			for (j = 0; j < wide; j ++)
			{
				// 对像素进行灰度映射处理
				unsigned char T = temp[ wide * i + j];
				temp[ wide * i + j] = bMap[T];			 
			}
		}
        memcpy(p_data, temp,height*wide); 
	}
	else		//24位彩色
	{
		wide=this->GetDibWidthBytes();
		temp=new BYTE[wide*height]; 
		memcpy(temp,p_data,wide*height);
		// 对各像素进行灰度转换
		for (i = 0; i < height; i ++)
		{
			for (j = 0; j < wide; j ++)
			{
				// 对像素进行灰度映射处理
				unsigned char T = temp[ wide * i + j];
				temp[ wide * i + j] = bMap[T];			 
			}
		}
		memcpy(p_data, temp,height*wide);
	}
}

///***************************************************************/           
/*函数名称：Chuangkoubianhuan(BYTE blow,BYTE bup)                                      
/*函数类型：void                                          
/*变量说明：blow窗口下界 bup窗口上界                                                               
/*功能：对图像进行窗口变换。                    
/***************************************************************/  
void HuiDuBianHuanDib::Chuangkoubianhuan(BYTE bLow, BYTE bUp)
{
    // 循环变量
	int i;
	int j;
	int wide,height;    //原图长、宽
	// 指向源图像的指针
	LPBYTE	lpSrc;
	// 指向DIB象素指针
	LPBYTE  p_data;
	p_data=this->GetData ();     //取得原图的数据区指针
	if (m_pBitmapInfoHeader->biBitCount<9)		
		wide=this->GetWidth ();
	else
		wide=this->GetDibWidthBytes();
	height=this->GetHeight ();
	// 对各像素进行灰度转换
	for(i = 0; i < height; i++)
	{
		// 每列
		for(j = 0; j < wide; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (LPBYTE)p_data + wide * (height- 1 - i) + j;
			// 判断是否超出范围
			if ((*lpSrc) < bLow)
			{
				// 直接赋值为0
				*lpSrc = 0;
			}
			else if ((*lpSrc) > bUp)
			{
				// 直接赋值为255
				*lpSrc = 255;
			}
		}
	}
}

///***************************************************************/           
/*函数名称：Fenbujunhenghua()                                           
/*函数类型：void                                          
/*变量说明：无                                                               
/*功能：对图像进行灰度分布均衡化处理。                   
/***************************************************************/  
void HuiDuBianHuanDib::Fenbujunhenghua( )
{	
	// 循环变量
	LONG i;
	LONG j;
	//图像的宽和高
	LONG wide;
	LONG height;
	// 灰度分布密度
	float fPs_R[256],fPs_G[256],fPs_B[256];
	// 中间变量
	float temp_r[256],temp_g[256],temp_b[256];
	int nNs_R[256],nNs_G[256],nNs_B[256];
	// 初始化
	memset(temp_r, 0, sizeof(temp_r));
	memset(temp_g, 0, sizeof(temp_g));
	memset(temp_b, 0, sizeof(temp_b));
	// 指向DIB象素指针
	LPBYTE p_data;
	// 找到DIB图像象素起始位置
	p_data = this->GetData();
	wide=this->GetWidth ();	
	// DIB的高度
	height = GetHeight();
	if(m_pBitmapInfoHeader->biBitCount<9)		//灰度图像
	{
		// 获取图像的灰度分布密度
		ZhiFangTu(fPs_R);
		// 进行均衡化处理 
		for(i = 0; i < 256; i++)
		{
			if(i == 0)
			{
				temp_r[0] = fPs_R[0];	 
			}
			else
			{
				temp_r[i] = temp_r[i-1] + fPs_R[i];	 
			}
			nNs_R[i] = (int)(255.0f * temp_r[i] + 0.5f);
		}
	}
	else		//24位彩色
	{
		// 获取图像的灰度分布密度
		ZhiFangTu(fPs_R,fPs_G,fPs_B);
		// 进行均衡化处理 
		for(i = 0; i < 256; i++)
		{
			if(i == 0)
			{
				temp_r[0] = fPs_R[0];
				temp_g[0] = fPs_G[0];
				temp_b[0] = fPs_B[0];
			}
			else
			{
				temp_r[i] = temp_r[i-1] + fPs_R[i];	
				temp_g[i] = temp_g[i-1] + fPs_G[i];	
				temp_b[i] = temp_b[i-1] + fPs_B[i];	
			}
			nNs_R[i] = (int)(255.0f * temp_r[i] + 0.5f);
			nNs_G[i] = (int)(255.0f * temp_g[i] + 0.5f);
			nNs_B[i] = (int)(255.0f * temp_b[i] + 0.5f);
		}
	}
	if (m_pBitmapInfoHeader->biBitCount<9)		//灰度图像
	{ 
		// 对各像素进行灰度转换
		for (j = 0; j < height; j ++)
		{
			for (i = 0; i < wide; i ++)
			{
				// 将转换后的灰度分布写入DIB图像
				unsigned char temp = *((unsigned char *)p_data + wide * j + i);
				*((unsigned char *)p_data + wide * j + i) = nNs_R[temp];			
			}
		}
	}
	else		//24位彩色
	{
		// 对各像素进行灰度转换
		for (j = 0; j < height; j ++)
		{
			for (i = 0; i < wide; i ++)
			{
				// 将转换后的灰度分布写入DIB图像
				unsigned char temp1= *((unsigned char *)p_data + wide * j*3 + i*3);
				*((unsigned char *)p_data + wide * j*3 + i*3) = nNs_R[temp1];
				unsigned char temp2 = *((unsigned char *)p_data + wide * j*3 + i*3+1);
				*((unsigned char *)p_data + wide * j*3 + i*3+1) = nNs_G[temp2];	
				unsigned char temp3 = *((unsigned char *)p_data + wide * j*3 + i*3+2);
				*((unsigned char *)p_data + wide * j*3 + i*3+2) = nNs_B[temp3];	
			}
		}
	}
}

int HuiDuBianHuanDib::GetWidth()
{
	return CDib::GetWidth();
}

///***************************************************************/           
/*函数名称：Pipeibianhuan(BYTE bNum,int *npNu,float*fpPu)                                            */
/*函数类型：void                                              */
/*变量说明：bNum规定直方图灰度级 npNu 直方图映射关系
/*          fpPu灰度分布概率                                                             
/*功能：对图像进行灰度匹配变换。                       */
/***************************************************************/  
void HuiDuBianHuanDib::Pipeibianhuan(BYTE bNum, int *npNu, float *fpPu)
{
	// 循环变量
	LONG i;
	LONG j;
    LONG wide;
	LONG height;
	// 灰度分布密度
	int midu[256],midu2[256],midu3[256];
	// 灰度分布概率
	float gailu[256],gailu2[256],gailu3[256];
	// 中间临时变量
	float temp[256],temp2[256],temp3[256];
	// 指向DIB象素指针
	LPBYTE p_data;
	// 找到DIB图像象素起始位置
	p_data = this->GetData();
	wide=this->GetWidth ();    
	// DIB的高度
	height = GetHeight(); 	
    if (m_pBitmapInfoHeader->biBitCount<9)		//灰度图像
	{   
		// 对灰度密度分布进行统计	
		Midufenbu(midu);
		// 对灰度分布概率进行统计
		ZhiFangTu(gailu);
		
		// 计算原始累计直方图
		for (i = 0; i < 256; i++)
		{
			if (i == 0)
			{
				temp[0] = gailu[0];			 
			}
			else
			{
				temp[i] = temp[i-1] + gailu[i];			 
			}
			gailu[i] = temp[i];
		}
		// 计算规定累计直方图
		for (i = 0; i < bNum; i++)
		{
			if (i == 0)
			{
				temp[0] = fpPu[0];
			}
			else
			{
				temp[i] = temp[i-1] + fpPu[i];
			}
			fpPu[i] = temp[i];
		}
		// 确定映射对应关系
		for (i = 0; i < 256; i++)
		{
			// 最接近的规定直方图灰度级
			int m_r = 0;
			// 最小差值
			float min_value_r = 1.0f;
			// 对规定直方图各灰度进行枚举
			for (j = 0; j < bNum; j++)
			{
				// 当前差值
				float now_value = 0.0f;
				//  计算差值
				if (gailu[i] - fpPu[j] >= 0.0f)
					now_value = gailu[i] - fpPu[j];
				else
					now_value = fpPu[j] - gailu[i];
				// 寻找最接近的规定直方图灰度级
				if (now_value < min_value_r)
				{
					// 最接近的灰度级
					m_r = j;
					// 暂存最小差值
					min_value_r = now_value;
				}
			}
			// 建立灰度映射表
			midu[i] = npNu[m_r];
		}
		// 对各像素进行处理
		for (j = 0; j < height; j ++)
		{
			for (i = 0; i < wide; i ++)
			{
				// 对像素进行单映射规则的直方图规定化映射处理
				unsigned char temp = *((unsigned char *)p_data + wide * j + i);
				*((unsigned char *)p_data + wide * j + i) = midu[temp];
			}
		}
	}
	else		//24位彩色
	{
		// 对灰度密度分布进行统计	
		Midufenbu(midu,midu2,midu3);
		// 对灰度分布概率进行统计
		ZhiFangTu(gailu,gailu2,gailu3);
		
		// 计算原始累计直方图
		for (i = 0; i < 256; i++)
		{
			if (i == 0)
			{
				temp[0] = gailu[0];	
				temp2[0] = gailu2[0];
				temp3[0] = gailu3[0];
			}
			else
			{
				temp[i] = temp[i-1] + gailu[i];
				temp2[i] = temp2[i-1] + gailu2[i];	
				temp3[i] = temp3[i-1] + gailu3[i];	
			}
			gailu[i] = temp[i];
			gailu2[i] = temp2[i];
			gailu3[i] = temp3[i];
			
		}
		// 计算规定累计直方图
		for (i = 0; i < bNum; i++)
		{
			if (i == 0)
			{
				temp[0] = fpPu[0];			
			}
			else
			{
				temp[i] = temp[i-1] + fpPu[i];
			}
			fpPu[i] = temp[i];
		}
		// 确定映射对应关系
		for (i = 0; i < 256; i++)
		{
			// 最接近的规定直方图灰度级
			int m_r = 0;
			int m_g = 0;
			int m_b = 0;		 		
			// 最小差值
			float min_value_r = 1.0f;
			float min_value_g = 1.0f;
			float min_value_b = 1.0f;
			// 对规定直方图各灰度进行枚举
			for (j = 0; j < bNum; j++)
			{
				// 当前差值
				float now_value = 0.0f;
				//  计算差值
				if (gailu[i] - fpPu[j] >= 0.0f)
					now_value = gailu[i] - fpPu[j];
				else
					now_value = fpPu[j] - gailu[i];
				// 寻找最接近的规定直方图灰度级
				if (now_value < min_value_r)
				{
					// 最接近的灰度级
					m_r = j;
					// 暂存最小差值
					min_value_r = now_value;
				}
				//  计算差值
				if (gailu2[i] - fpPu[j] >= 0.0f)
					now_value = gailu2[i] - fpPu[j];
				else
					now_value = fpPu[j] - gailu2[i];
				// 寻找最接近的规定直方图灰度级
				if (now_value < min_value_g)
				{
					// 最接近的灰度级
					m_g = j;
					// 暂存最小差值
					min_value_g = now_value;
				}
				//  计算差值
				if (gailu3[i] - fpPu[j] >= 0.0f)
					now_value = gailu3[i] - fpPu[j];
				else
					now_value = fpPu[j] - gailu3[i];
				// 寻找最接近的规定直方图灰度级
				if (now_value < min_value_b)
				{
					// 最接近的灰度级
					m_b = j;
					// 暂存最小差值
					min_value_b = now_value;
				}
			}
			// 建立灰度映射表
			midu[i] = npNu[m_r];
			midu2[i] = npNu[m_g];
			midu3[i] = npNu[m_b];
		}
		// 对各像素进行处理
		for (j = 0; j < height; j ++)
		{
			for (i = 0; i < wide; i ++)
			{
				// 对像素进行单映射规则的直方图规定化映射处理
				unsigned char temp = *((unsigned char *)p_data + wide * j*3 + i*3);
				*((unsigned char *)p_data + wide * j*3 + i*3) = midu[temp];
				unsigned char temp2 = *((unsigned char *)p_data + wide * j*3 + i*3+1);
				*((unsigned char *)p_data + wide * j*3 + i*3+1) = midu[temp2];
				unsigned char temp3 = *((unsigned char *)p_data + wide * j*3 + i*3+2);
				*((unsigned char *)p_data + wide * j*3 + i*3+2) = midu[temp3];
			}
		}
	}
}

///***************************************************************/           
/*函数名称：Midufenbu()                                        
/*函数类型：void                                      
/*功能：对图像进行密度分布变换。            
/***************************************************************/  
void HuiDuBianHuanDib::Midufenbu(int *nNs_R)
{
	// 循环变量
	LONG i;
	LONG j;
	
	LONG wide;
	LONG height;
	//变量初始化
	memset(nNs_R,0,sizeof(int) * 256);
	// 指向DIB象素指针
	LPBYTE p_data;
	// 找到DIB图像象素起始位置
	p_data = this->GetData();		
    wide=this->GetWidth ();
	// DIB的高度
	height = GetHeight();
	// 对各像素进行灰度转换
	for (j = 0; j < height; j ++)
	{
		for (i = 0; i <wide; i ++)
		{
			// 对各像素进行灰度统计
			unsigned char temp = *((unsigned char *)p_data + wide * j + i);
			nNs_R[temp]++;		
		}
	} 
}

///***************************************************************/           
/*函数名称：Shuipingtouying()                                        
/*函数类型：void                                      
/*功能：对图像进行水平投影。            
/***************************************************************/  
void HuiDuBianHuanDib::Shuipingtouying()
{
	LPBYTE  p_data, p_datatemp;     //原图数据区指针
	int wide,height;				//原图长、宽
	int i,j;						//循环变量
	int lBlackNum  ;
	p_datatemp=this->GetData();
	p_data=p_datatemp;
	if(m_pBitmapInfoHeader->biBitCount<9)		
		wide=this->GetWidth ();
	else
		wide=this->GetDibWidthBytes();
	height=this->GetHeight ();
	//对图像进行二值化
	for(j=0;j<height;j++)
	{
		for(i=0;i<wide;i++)
		{ 
			if (*p_data>128)
				*p_data=255;
			else *p_data=0;
			p_data++;
		}
	}
	p_data=p_datatemp; 
	LPBYTE   temp=new BYTE[wide*height];    //新图像缓冲区
	memset( temp,255,wide*height);			//设定新图像初值为255
	for(j=0;j<height;j++)
	{
		lBlackNum=0;
		for(i=0;i<wide;i++)
		{				 
			if(p_data[wide*j+i]==0)
				lBlackNum++;
		}
		for(i=0;i<lBlackNum;i++)
			temp[wide*j+i]=0;
	}
	memcpy(p_data, temp,wide*height);
	delete  temp;	
}

///***************************************************************/           
/*函数名称：Chuizhitouying()                                      
/*函数类型：void                                      
/*功能：对图像进行垂直投影。            
/***************************************************************/  
void HuiDuBianHuanDib::Chuizhitouying()
{
	LPBYTE  p_data, p_datatemp;     //原图数据区指针
	int wide,height;				//原图长、宽
	int i,j;						//循环变量
	long int lBlackNum;				//图像中每行内黑点的个数
	p_datatemp=this->GetData();
	p_data=p_datatemp;
	if(m_pBitmapInfoHeader->biBitCount<9)	
		wide=this->GetWidth ();
	else
		wide=this->GetDibWidthBytes();
	height=this->GetHeight ();
	//对图像进行二值化
	for(j=0;j<height;j++)
	{
		for(i=0;i<wide;i++)
		{ 
			if (*p_data>128)
				*p_data=255;
			else 
				*p_data=0;
			p_data++;
		}
	}
	p_data=p_datatemp;
	LPBYTE  temp=new BYTE[wide*height];		//新图像缓冲区
	memset( temp,255,wide*height);			//设定新图像初值为255
	for(i=0;i<wide;i++)
	{
		lBlackNum=0;
		for(j=0;j<height;j++)
		{
			
			if(p_data[wide*j+i]==0)
				lBlackNum++;
		}
		for(j=0;j<lBlackNum;j++)
			temp[wide*j+i]=0;
	}
	memcpy(p_data, temp,wide*height);
	delete  temp;		
}

void HuiDuBianHuanDib::RedZhiFangTu(float *tongji)
{
	// 循环变量
	int i;
	int j;
	// 灰度计数
	int huidu[256];    
	int wide,height;    //原图长、宽
	// 变量初始化
	memset(huidu,0,sizeof(huidu));
	wide=this->GetDibWidthBytes();
	height=this->GetHeight ();
	LPBYTE  temp1=new BYTE[wide*height];    //新图像缓冲区
	//拷贝原图像到缓存图像
	memcpy(temp1,m_pData,wide*height );
	// 对各像素进行灰度统计
	for (i = 0; i < height; i ++)
	{
		for (j = 0; j <wide; j=j +3)
		{
			unsigned char  temp = temp1[wide* i + j] ;
			// 灰度统计计数
			huidu[temp]++;		
		}
	}
	// 计算灰度分布密度
	for(i=0;i<256;i++)
		tongji[i] = huidu[i] / (height * wide *1.0f);
}

void HuiDuBianHuanDib::BlueZhiFangTu(float *tongji)
{
	// 循环变量
	int i;
	int j;
	// 灰度计数
	int huidu[256];    
	int wide,height;    //原图长、宽
	// 变量初始化
	memset(huidu,0,sizeof(huidu));
	wide=this->GetDibWidthBytes();
	height=this->GetHeight ();
	LPBYTE  temp1=new BYTE[wide*height];    //新图像缓冲区
	//拷贝原图像到缓存图像
	memcpy(temp1,m_pData,wide*height );
	// 对各像素进行灰度统计
	for (i = 0; i < height; i ++)
	{
		for (j = 2; j <wide; j=j +3)
		{
			unsigned char  temp = temp1[wide* i + j] ;
			// 灰度统计计数
			huidu[temp]++;		
		}
	}
	// 计算灰度分布密度
	for(i=0;i<256;i++)
		tongji[i] = huidu[i] / (height * wide *1.0f);
}

void HuiDuBianHuanDib::GreenZhiFangTu(float *tongji)
{
	// 循环变量
	int i;
	int j;
	// 灰度计数
	int huidu[256];    
	int wide,height;    //原图长、宽
	// 变量初始化
	memset(huidu,0,sizeof(huidu));
	wide=this->GetDibWidthBytes();
	height=this->GetHeight ();
	LPBYTE  temp1=new BYTE[wide*height];    //新图像缓冲区
	//拷贝原图像到缓存图像
	memcpy(temp1,m_pData,wide*height );
	// 对各像素进行灰度统计
	for (i = 0; i < height; i ++)
	{
		for (j = 1; j <wide; j=j +3)
		{
			unsigned char  temp = temp1[wide* i + j] ;
			// 灰度统计计数
			huidu[temp]++;		
		}
	}
	// 计算灰度分布密度
	for(i=0;i<256;i++)
		tongji[i] = huidu[i] / (height * wide *1.0f);
}

//对24位彩色图像进行灰度概率统计
void HuiDuBianHuanDib::ZhiFangTu(float *tongji1, float *tongji2, float *tongji3)
{
	// 循环变量
	int i;
	int j;
	// 灰度计数
	int huidu1[256],huidu2[256],huidu3[256];    
	int wide,height;    //原图长、宽
	wide=this->GetWidth ();		 
	height=this->GetHeight ();
	// 变量初始化
	memset(huidu1,0,sizeof(huidu1));
	memset(huidu2,0,sizeof(huidu2));
	memset(huidu3,0,sizeof(huidu3));		  
	LPBYTE  temp_pData=new BYTE[wide*height*3];    //新图像缓冲区
	//拷贝原图像到缓存图像
	memcpy(temp_pData,m_pData,wide*height*3);
	// 对各像素进行灰度统计
	for (j = 0; j < height; j ++)
	{
		for (i = 0; i <wide; i ++)
		{
			unsigned char  temp1 = temp_pData[wide*j*3 + i*3] ;
			unsigned char  temp2 = temp_pData[wide*j*3 + i*3+1] ;
			unsigned char  temp3 = temp_pData[wide*j *3+ i*3+2] ;
			// 灰度统计计数
			huidu1[temp1]++;
			huidu2[temp2]++;
			huidu3[temp3]++;
		}
	}
	// 计算灰度分布密度
	for(i=0;i<256;i++)
	{
		tongji1[i] = huidu1[i] / (height * wide *1.0f);	
		tongji2[i] = huidu2[i] / (height * wide *1.0f);	
		tongji3[i] = huidu3[i] / (height * wide *1.0f);	
	}
}

void HuiDuBianHuanDib::Midufenbu(int *nNs_R, int *nNs_G, int *nNs_B)
{
    // 循环变量
	LONG i;
	LONG j;
	LONG wide;
	LONG height;
	//变量初始化
	memset(nNs_R,0,sizeof(int) * 256);
	memset(nNs_G,0,sizeof(int) * 256);
	memset(nNs_B,0,sizeof(int) * 256);
	// 指向DIB象素指针
	LPBYTE p_data;
	// 找到DIB图像象素起始位置
	p_data = this->GetData();		
    wide=this->GetWidth ();
	// DIB的高度
	height = GetHeight();
	// 对各像素进行灰度转换
	for (j= 0;j < height;j ++)
	{
		for (i = 0; i <wide; i ++)
		{
			// 对各像素进行灰度统计
			unsigned char temp = *((unsigned char *)p_data + wide * j*3 + i*3);
			unsigned char temp2 = *((unsigned char *)p_data + wide * j*3 + i*3+1);
			unsigned char temp3 = *((unsigned char *)p_data + wide * j*3 + i*3+2);
			nNs_R[temp]++;		
			nNs_G[temp2]++;
			nNs_B[temp3]++;
		}
	} 
}
