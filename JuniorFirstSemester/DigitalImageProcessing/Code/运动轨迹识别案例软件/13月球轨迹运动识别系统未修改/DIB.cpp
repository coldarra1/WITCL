// DIB.cpp: implementation of the DIB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DIB.h"
#include"math.h"
#define WIDTHBYTES(bits)  ((bits+31)/32*4)
#define RECTWIDTH(x) (x->right-x->left)
#define RECTHEIGHT(x) (x->bottom-x->top)
#define THRESHOLDCONTRAST  40
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#define PI 3.1415926
extern int locax,locay;
#define m_WIDTH 600
#define m_HEIGHT 600

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
/////////////////////////////////////////////////////////////////////
HDIB DIB::ReadDIBFile(HANDLE hFile)
{
	BITMAPFILEHEADER bmfHeader;
	DWORD dwBitsSize;
	HANDLE hDIB;
	HANDLE hDIBtmp;
	LPBITMAPINFOHEADER lpbi;
	DWORD dwRead;
    //得到文件大小
	dwBitsSize = GetFileSize(hFile,NULL);
	hDIB =  GlobalAlloc(GMEM_MOVEABLE,(DWORD)(sizeof(BITMAPINFOHEADER)));

	if(!hDIB)
		return NULL;

	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	if(!lpbi)
	{
		GlobalFree(hDIB);
		return NULL;
	}
	
	if(!ReadFile(hFile,(LPBYTE)&bmfHeader,sizeof(BITMAPFILEHEADER),&dwRead,NULL))
		goto ErrExit;
	if(sizeof(BITMAPFILEHEADER)!=dwRead)//读取文件出错
		goto ErrExit;
	if(bmfHeader.bfType != 0x4d42)//文件类型不匹配
		goto ErrExit;
	if(!ReadFile(hFile,(LPBYTE)lpbi,sizeof(BITMAPINFOHEADER),&dwRead,NULL))
		goto ErrExit;
	if(sizeof(BITMAPINFOHEADER)!= dwRead)//读取数据出错
		goto ErrExit;
	
	GlobalUnlock(hDIB);
	if(lpbi->biSizeImage==0)
		lpbi->biSizeImage = (this->BytePerLine(hDIB))*lpbi->biHeight;
	hDIBtmp = GlobalReAlloc(hDIB,lpbi->biSize+lpbi->biSizeImage,0);
	if(!hDIBtmp)
		goto ErrExitNoUnlock;
	else
		hDIB = hDIBtmp;
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	//根据情况设定文件指针
	if(bmfHeader.bfOffBits != 0L)
		SetFilePointer(hFile,bmfHeader.bfOffBits,NULL,FILE_BEGIN);
    //读取文件的象素颜色数据
	if(ReadFile(hFile,(LPBYTE)lpbi+lpbi->biSize,lpbi->biSizeImage,&dwRead,NULL))
			goto OKExit;
	
	ErrExit:
		GlobalUnlock(hDIB);
	
	ErrExitNoUnlock:
		GlobalFree(hDIB); //释放内存
		return NULL;

	OKExit:
		GlobalUnlock(hDIB);
		return hDIB;
		
}

HDIB DIB::LoadDIB(LPCTSTR lpFileName)
{
	HANDLE hDIB;
	HANDLE hFile;
	//创建文件句柄
	if((hFile = CreateFile(lpFileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN,NULL))!= INVALID_HANDLE_VALUE)
	{  
		//读取数据
		hDIB = ReadDIBFile(hFile);
		//关闭文件句柄
		CloseHandle(hFile);
		return hDIB;
	}
	return NULL;
}

BOOL DIB::PaintDIBTrue(HDC hDC,LPRECT lpDCRect,HANDLE hDIB,LPRECT lpDIBRect ,DWORD dwRop)
{
	LPBYTE lpDIBHdr;
	LPBYTE lpDIBBits;
	BOOL bSuccess = FALSE;

	if(!hDIB)
		return FALSE;
	lpDIBHdr = (LPBYTE)GlobalLock(hDIB);
	lpDIBBits = lpDIBHdr + sizeof(BITMAPINFOHEADER);
	bSuccess = StretchDIBits(hDC,lpDCRect->left,
								 lpDCRect->top,
								 RECTWIDTH(lpDCRect),
								 RECTHEIGHT(lpDCRect),
								 lpDIBRect->left,
								 ((LPBITMAPINFOHEADER)lpDIBHdr)->biHeight-lpDIBRect->top-RECTHEIGHT(lpDIBRect),
								 RECTWIDTH(lpDIBRect),
								 RECTHEIGHT(lpDIBRect),
								 lpDIBBits,
								 (LPBITMAPINFO)lpDIBHdr,
								 DIB_RGB_COLORS,
								 SRCCOPY);
	GlobalUnlock(hDIB);
	return bSuccess;
}

WORD DIB::BytePerLine(HANDLE hDIB)
{	
	WORD i;
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	i = WIDTHBYTES((lpbi->biWidth)*24);
	GlobalUnlock(hDIB);
	return i;	
}


//函数实现图片从彩色到黑白的转换
HDIB DIB::ToGray(HANDLE hDIB)
{
	HDIB hNewDIB = NULL;
	LPBITMAPINFOHEADER lpSrc,lpDest;
	LPBYTE lpS,lpD;
	DWORD dwBytesPerLine;
	DWORD dwImgSize;
	WORD wBytesPerLine;
	unsigned i ,j,height,width;
	if(!hDIB)
		return NULL;
	
	lpSrc = (LPBITMAPINFOHEADER)GlobalLock(hDIB);

	dwBytesPerLine = WIDTHBYTES(24*(lpSrc->biWidth));
	dwImgSize = lpSrc->biHeight * dwBytesPerLine;
	//申请新的内存，大小等于原来图象的大小
	hNewDIB = GlobalAlloc(GHND,sizeof(BITMAPINFOHEADER)+dwImgSize);

	lpDest = (LPBITMAPINFOHEADER)GlobalLock(hNewDIB);
	//保存图片的长宽、颜色深度等信息
	memcpy((void*)lpDest,(void*)lpSrc,sizeof(BITMAPINFOHEADER));
	DWORD dwSBytesPerLine;
	dwSBytesPerLine = (24*(lpSrc->biWidth)+31)/32*4;
	height = lpDest->biHeight;
	width = lpDest->biWidth;
	lpS = (LPBYTE)lpSrc;
	wBytesPerLine = this->BytePerLine(hDIB);
	lpD = (LPBYTE)lpDest;	
	lpS = lpS + sizeof(BITMAPINFOHEADER);
	lpD = lpD + sizeof(BITMAPINFOHEADER);
	unsigned  r , g ,b,gray ;
	//扫描整个图片，实现灰度化
	for(i = 0 ;i<height; i++)
	{
		for(j = 0 ;j<(unsigned )lpDest->biWidth;j++)
		{
	        //获得原来图片的颜色值
			r = *(lpS++);
			g = *(lpS++);
			b  = *(lpS++);
			//计算灰度值
			gray = (g*50+r*39+b*11)/100;
			//保存灰度值到目标图片
			*(lpD++)=gray;
			*(lpD++) = gray;
			*(lpD++) = gray;

			
		}
		//处理四字节对齐问题
	unsigned  k ;
		for(k=0;k<dwSBytesPerLine-lpSrc->biWidth*3;k++)
		{
			lpS++;
			lpD++;
		}
		
	}

	GlobalUnlock(hDIB);
	GlobalUnlock(hNewDIB);
   	return hNewDIB;
	
	

}



LPBYTE  DIB::FindDIBBits(HANDLE hDIB)
{
	LPBYTE lpDIB,lpDIBtmp;
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	lpDIBtmp = (LPBYTE)lpbi;
	lpDIB = lpDIBtmp + sizeof(BITMAPINFOHEADER);
	GlobalUnlock(hDIB);
	return lpDIB;
}

long DIB::PixelOffset(int i,int j,WORD wBytePerLine)
{
	long   Offset;
	Offset = i*wBytePerLine + j*3;
	return Offset;
}





int DIB::BOUND(int a ,int b ,int rgb)
{
	if(rgb<0)
		return BOUND(a,b,abs(rgb));
	if(rgb>b)
		return b;
	return rgb;
}
//函数实现对图片的中值滤波处理
void DIB::MedianFilterDIB(HANDLE hDIB)
{
	
	HDIB hNewDIB;
	LPBYTE  lpS,lpD;
	LPBITMAPINFOHEADER lpbi;
	int r,g,b;
	DWORD width,height;
	WORD wBytesPerLine;
	long lOffset;
	if(!hDIB)
		return;
	SetCursor(LoadCursor(NULL,IDC_WAIT));
	wBytesPerLine = this->BytePerLine(hDIB);
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	width = lpbi->biWidth;
	height = lpbi->biHeight;
	 //申请一块新的内存
	hNewDIB = GlobalAlloc(GHND,sizeof(BITMAPINFOHEADER)+lpbi->biSizeImage);
	lpD = (LPBYTE)GlobalLock(hNewDIB);
	lpS = (LPBYTE)lpbi;
	memcpy(lpD,lpS,sizeof(BITMAPINFOHEADER));
	lpS = lpS+sizeof(BITMAPINFOHEADER);
	lpD = lpD+sizeof(BITMAPINFOHEADER);
	//扫描整个图片
	for(WORD i=1;i<height-1;i++)
		for(WORD j=1;j<width-1;j++)
		{	//中值滤波
			this->DoMedianFilterDIB(&r,&g,&b,i,j,wBytesPerLine,lpS);
			lOffset = this->PixelOffset(i,j,wBytesPerLine);
			*(lpD+lOffset++) = r;
			*(lpD+lOffset++) = g;
			*(lpD+lOffset)   = b;

		}
		//把信息拷贝回原来的句柄
		for( i = 1;i<height-1;i++)
			for(WORD j = 1;j<width-1;j++)
			{
				lOffset = this->PixelOffset(i,j,wBytesPerLine);
				//活得新图片的颜色
				int color1 = *(lpD+lOffset++);
				int color2 = *(lpD+lOffset++);
				int color3 = *(lpD+lOffset++);
				//拷贝到原来图片中
						*(lpS+lOffset++) = color1;
						*(lpS+lOffset++) = color2;
						*(lpS+lOffset++) = color3;
			}
	SetCursor(LoadCursor(NULL,IDC_ARROW));
	GlobalUnlock(hDIB);
	GlobalUnlock(hNewDIB);
	GlobalFree(hNewDIB);
	
}



void DIB::DoMedianFilterDIB(int *r,int *g,int*b,WORD i,WORD j,WORD wBytesPerLine,LPBYTE lpDIBBits)
{
	long lOffset;
	int rgb[9][3];
	//把八个方位和当前位置得rgb值保存到数组rgb[9][3]中
	lOffset = this->PixelOffset( i-1, j-1, wBytesPerLine); 
	rgb[0][0] = *(lpDIBBits+lOffset++);
	rgb[0][1] = *(lpDIBBits+lOffset++);
	rgb[0][2] = *(lpDIBBits+lOffset++);

	lOffset = this->PixelOffset( i-1, j, wBytesPerLine);
	rgb[1][0] = *(lpDIBBits+lOffset++);
	rgb[1][1] = *(lpDIBBits+lOffset++);
	rgb[1][2] = *(lpDIBBits+lOffset++);
	lOffset = this->PixelOffset( i-1, j+1, wBytesPerLine);
	rgb[2][0] = *(lpDIBBits+lOffset++);
	rgb[2][1] = *(lpDIBBits+lOffset++);
	rgb[2][2] = *(lpDIBBits+lOffset++);
	lOffset = this->PixelOffset( i, j-1, wBytesPerLine);
	rgb[3][0] = *(lpDIBBits+lOffset++);
	rgb[3][1] = *(lpDIBBits+lOffset++);
	rgb[3][2] = *(lpDIBBits+lOffset++);
	lOffset = this->PixelOffset( i, j, wBytesPerLine);
	rgb[4][0] = *(lpDIBBits+lOffset++);
	rgb[4][1] = *(lpDIBBits+lOffset++);
	rgb[4][2] = *(lpDIBBits+lOffset++);
	lOffset = this->PixelOffset( i, j+1, wBytesPerLine);
	rgb[5][0] = *(lpDIBBits+lOffset++);
	rgb[5][1] = *(lpDIBBits+lOffset++);
	rgb[5][2] = *(lpDIBBits+lOffset++);
	lOffset = this->PixelOffset( i+1, j-1, wBytesPerLine);
	rgb[6][0] = *(lpDIBBits+lOffset++);
	rgb[6][1] = *(lpDIBBits+lOffset++);
	rgb[6][2] = *(lpDIBBits+lOffset++);
	lOffset = this->PixelOffset( i+1, j, wBytesPerLine);
	rgb[7][0] = *(lpDIBBits+lOffset++);
	rgb[7][1] = *(lpDIBBits+lOffset++);
	rgb[7][2] = *(lpDIBBits+lOffset++);
	lOffset = this->PixelOffset( i+1, j+1, wBytesPerLine);
	rgb[8][0] = *(lpDIBBits+lOffset++);
	rgb[8][1] = *(lpDIBBits+lOffset++);
	rgb[8][2] = *(lpDIBBits+lOffset++);
	 this->MedianSearch( rgb,9,b,g,r);
	

}


int DIB::MedianSearch(int a[9][3],int n,int *r,int *g,int *b)
{
	int result,i,j,temp;
	//冒泡法排序，找出rgb中间值
	for(i=0;i<9;i++)
		for(j = 0 ;j<n-i-1;j++)
		{	
			if(a[j][0]>a[j+1][0])
			{
				temp = a[j][0];
				a[j][0] = a[j+1][0];
				a[j+1][0]=temp;
			}
			if(a[j][1]>a[j+1][1])
			{
				temp = a[j][1];
				a[j][1] = a[j+1][1];
				a[j+1][1]=temp;
			}

			if(a[j][2]>a[j+1][2])
			{
				temp = a[j][2];
				a[j][2] = a[j+1][2];
				a[j+1][2]=temp;
			}


		}
		//得到rgb得中间值
		*b = a[5][0];
		*g = a[5][1];
		*r = a[5][2];
		//根据需要也可以选用灰度值
		result = (a[5][0]*39 +a[5][1]*50 + a[5][2]*11)/100;
		return result;
}
//实现图片的黑白二值化
void DIB::WhiteBlack(HANDLE hDIB,unsigned n)
{

	LPBITMAPINFOHEADER  lpbi;
	LPBYTE				lpS;
	int					width,height;
	long				lOffset;
	WORD                wBytesPerLine;

	if(!hDIB)
		return ;
	wBytesPerLine = this->BytePerLine(hDIB);
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
    //得到图片的长宽信息
	width = lpbi->biWidth;
	height = lpbi->biHeight;

	lpS = (LPBYTE)lpbi;
	//lps指向数据区
	lpS = lpS + sizeof(BITMAPINFOHEADER);
  	//扫描整个图片，实现二值化
	for(int i = 0;i<height;i++)
		for(int j = 0 ;j<width;j++)
		{   //得到象素数据在数据区中的偏移
			lOffset = this->PixelOffset(i,j,wBytesPerLine);
			if(*(lpS+lOffset)<n)//象素值小于临界值
			{   //把象素填充为黑色
				*(lpS+lOffset++) = 0;
				*(lpS+lOffset++) = 0;
				*(lpS+lOffset)   = 0;
			}
			else //象素值大于临界值
			{   
				//把象素填充为白色
				*(lpS+lOffset++) = 255;
				*(lpS+lOffset++) = 255;
				*(lpS+lOffset)   = 255;
			}
		}

		GlobalUnlock(hDIB);
		
}














DIB::DIB()
{	


}
DIB::~DIB()
{

}

CPoint DIB::NextBorderPoint(CPoint CurrentPoint,LPBYTE lpDIBBits,WORD wBytesPerLine)
{
	CPoint Pointtmp;
/*	Pointtmp.x=-1;
	Pointtmp.y=-1;
	

	if(CurrentPoint.x!=this->width-1)
	{
		Pointtmp.x=CurrentPoint.x+1;
		Pointtmp.y=CurrentPoint.y;
	
		if(this->IsBorderPoint(Pointtmp,lpDIBBits, wBytesPerLine))
		return Pointtmp;
	}
	if((CurrentPoint.y!=this->height-1)&&(CurrentPoint.x!=this->width-1))
	{
		Pointtmp.x=CurrentPoint.x+1;
		Pointtmp.y=CurrentPoint.y+1;
	
		if(this->IsBorderPoint(Pointtmp,lpDIBBits, wBytesPerLine))
		return Pointtmp;
	}
	if(CurrentPoint.y!=this->height-1)
	{
		Pointtmp.x=CurrentPoint.x;
		Pointtmp.y=CurrentPoint.y+1;
	
		if(this->IsBorderPoint(Pointtmp,lpDIBBits, wBytesPerLine))
		return Pointtmp;
	}
	if((CurrentPoint.x!=0)&&(CurrentPoint.y!=this->height-1))
	{
		Pointtmp.x=CurrentPoint.x-1;
		Pointtmp.y=CurrentPoint.y+1;
	
		if(this->IsBorderPoint(Pointtmp,lpDIBBits, wBytesPerLine))
		return Pointtmp;
	}
	if(CurrentPoint.x!=0)
	{
		Pointtmp.x=CurrentPoint.x-1;
		Pointtmp.y=CurrentPoint.y;
	
		if(this->IsBorderPoint(Pointtmp,lpDIBBits, wBytesPerLine))
		return Pointtmp;
	}
	if((CurrentPoint.x!=0)&&(CurrentPoint.y!=0))
	{
		Pointtmp.x=CurrentPoint.x-1;
		Pointtmp.y=CurrentPoint.y-1;
	
		if(this->IsBorderPoint(Pointtmp,lpDIBBits, wBytesPerLine))
		return Pointtmp;
	}
	
	if(CurrentPoint.y != 0)
	{
		Pointtmp.x = CurrentPoint.x;
		Pointtmp.y = CurrentPoint.y-1;
	
		if(this->IsBorderPoint(Pointtmp,lpDIBBits, wBytesPerLine))
			return Pointtmp;
	}
   	if((CurrentPoint.y!=0)&&(CurrentPoint.x!=this->width-1))
	{
		Pointtmp.y=CurrentPoint.y-1;
		Pointtmp.x=CurrentPoint.x+1;
	
		if(this->IsBorderPoint(Pointtmp,lpDIBBits, wBytesPerLine))
		return Pointtmp;
	}
	CPoint errorPoint;
	errorPoint.x=errorPoint.y=-2;
	return errorPoint;
	*/
	return Pointtmp;
}

BOOL DIB::IsBorderPoint(CPoint CurrentPoint ,LPBYTE lpDIBBits,WORD wBytesPerLine)
{
	long lOffset;
	lOffset = this->PixelOffset(CurrentPoint.y,CurrentPoint.x,wBytesPerLine);
	if(*(lpDIBBits+lOffset)!=0)
		return false;

	if(CurrentPoint.y!=0)
	{
		lOffset = this->PixelOffset(CurrentPoint.y-1,CurrentPoint.x,wBytesPerLine);
		if(*(lpDIBBits+lOffset)==255)
		return true;
	}

	if(CurrentPoint.x!=this->width-1)
	{
		lOffset = this->PixelOffset(CurrentPoint.y,CurrentPoint.x+1,wBytesPerLine);
		if(*(lpDIBBits+lOffset)==255)
		return true;
	}

	if(CurrentPoint.y!=this->height-1)
	{
		lOffset = this->PixelOffset(CurrentPoint.y+1,CurrentPoint.x,wBytesPerLine);
		if(*(lpDIBBits+lOffset)==255)
		return true;
	}


	if(CurrentPoint.x!=0)
	{
		lOffset = this->PixelOffset(CurrentPoint.y,CurrentPoint.x-1,wBytesPerLine);
		if(*(lpDIBBits+lOffset)==255)
		return true;
	}

	return false;
}



CPoint DIB::SearchInteriorPoint(CPoint Point,LPBYTE lpDIBBits,WORD wBytesPerLine)
{
	long lOffset;
	CPoint Pointtmp;
	Pointtmp.x=Pointtmp.y=-1;
	if((Point.x!=0)&&(Point.y!=this->height-1))
	{
		lOffset = this->PixelOffset(Point.y+1,Point.x-1,wBytesPerLine);
		if(*(lpDIBBits+lOffset)==0)
		{
			Pointtmp.x=Point.x-1;
			Pointtmp.y=Point.y+1;
			return Pointtmp;
		}
	}

	if(Point.y!=this->height-1)
	{
		lOffset = this->PixelOffset(Point.y+1,Point.x,wBytesPerLine);
		if(*(lpDIBBits+lOffset)==0)
		{
			Pointtmp.x=Point.x;
			Pointtmp.y=Point.y+1;
			return Pointtmp;
		}
	}

	if((Point.x!=this->width-1)&&(Point.y!=this->height-1))
	{
		lOffset = this->PixelOffset(Point.y+1,Point.x+1,wBytesPerLine);
		if(*(lpDIBBits+lOffset)==0)
		{
			Pointtmp.x=Point.x+1;
			Pointtmp.y=Point.y+1;
			return Pointtmp;
		}
	}

	if(Point.x!=this->width-1)
	{
		lOffset=this->PixelOffset(Point.y,Point.x+1,wBytesPerLine);
		if(*(lpDIBBits+lOffset)==0)
		{
			Pointtmp.x=Point.x+1;
			Pointtmp.y=Point.y;
			return Pointtmp;
		}
	}
	return Pointtmp;
}

//对图片中的图形进行细化操作
void DIB::ThinningDIB(HANDLE hDIB)
{
	
	LPBITMAPINFOHEADER lpbi;
	WORD wBytesPerLine;
	LPBYTE lpDIBBits;
	long lOffset;
	int width,height;
	//细化查询表
	static int erasetable[256]={
								0,0,1,1,0,0,1,1,
								1,1,0,1,1,1,0,1,
								1,1,0,0,1,1,1,1,
								0,0,0,0,0,0,0,1,
								
								0,0,1,1,0,0,1,1,
								1,1,0,1,1,1,0,1,
								1,1,0,0,1,1,1,1,
								0,0,0,0,0,0,0,1,
								
								1,1,0,0,1,1,0,0,
								0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,
								
								1,1,0,0,1,1,0,0,
								1,1,0,1,1,1,0,1,
								0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,

								0,0,1,1,0,0,1,1,
								1,1,0,1,1,1,0,1,
								1,1,0,0,1,1,1,1,
								0,0,0,0,0,0,0,1,
								
								0,0,1,1,0,0,1,1,
								1,1,0,1,1,1,0,1,
								1,1,0,0,1,1,1,1,
								0,0,0,0,0,0,0,0,
								
								1,1,0,0,1,1,0,0,
								0,0,0,0,0,0,0,0,
								1,1,0,0,1,1,1,1,
								0,0,0,0,0,0,0,0,

								1,1,0,0,1,1,0,0,
								1,1,0,1,1,1,0,0,
								1,1,0,0,1,1,1,0,
								1,1,0,0,1,0,0,0
						  };
	
		lpbi=(LPBITMAPINFOHEADER)GlobalLock(hDIB);
		//得到图片的长宽信息
		width = lpbi->biWidth;
		height = lpbi->biHeight;
		lpDIBBits = this->FindDIBBits(hDIB);
	
		wBytesPerLine = this->BytePerLine(hDIB);
		//执行细化，直到没有点可以被去掉为止
		int end =0;
		while(!end)
		{
			end =1;
			//扫描整个图片，从上往下
		for(int i=1;i<height-1;i++)
			for(int j=1;j<width-1;j++)
			{	
				//判定当前点的颜色
				lOffset = this->PixelOffset(i,j,wBytesPerLine);
				if(*(lpDIBBits+lOffset)==0)
					continue;//如果是黑色的，直接考虑下一个点
				else
				{
					int colorleft,colorright;
					lOffset =this->PixelOffset(i,j-1,wBytesPerLine);
					colorleft = *(lpDIBBits+lOffset);
					lOffset = this->PixelOffset(i,j+1,wBytesPerLine);
					colorright = *(lpDIBBits+lOffset);
					//如果当前点的的左边和右边的点的颜色都是白色
					if((colorleft==255)&&(colorright==255))
						continue;//直接进行下一个点的处理
					else
					{	
						//下面的一段代码考察当前点的周围八个方向上的点的颜色
						//并根据颜色设置标志位
						int k1,k2,k3,k4,k5,k6,k7,k8;
						//左下
						lOffset = this->PixelOffset(i+1,j-1,wBytesPerLine);
						if(*(lpDIBBits+lOffset)==0)
							k1=1;
						else
							k1 =0;
						//正下
						lOffset = this->PixelOffset(i+1,j,wBytesPerLine);
						if(*(lpDIBBits+lOffset)==0)
							k2=1;
						else
							k2 =0;
						//右下
						lOffset = this->PixelOffset(i+1,j+1,wBytesPerLine);
						if(*(lpDIBBits+lOffset)==0)
							k3=1;
						else
							k3 =0;
						//正左
						lOffset = this->PixelOffset(i,j-1,wBytesPerLine);
						if(*(lpDIBBits+lOffset)==0)
							k4=1;
						else
							k4 =0;
                        //正右
						lOffset = this->PixelOffset(i,j+1,wBytesPerLine);
						if(*(lpDIBBits+lOffset)==0)
							k5=1;
						else
							k5 =0;
                        //左上
						lOffset = this->PixelOffset(i-1,j-1,wBytesPerLine);
						if(*(lpDIBBits+lOffset)==0)
							k6=1;
						else
							k6 =0;
                        //正上
						lOffset = this->PixelOffset(i-1,j,wBytesPerLine);
						if(*(lpDIBBits+lOffset)==0)
							k7=1;
						else
							k7 =0;
						//右上
						lOffset = this->PixelOffset(i-1,j+1,wBytesPerLine);
						if(*(lpDIBBits+lOffset)==0)
							k8=1;
						else
							k8 =0;
						int judge;
						//计算得到细化查询表中的位置
						judge = k1+k2*2+k3*4+k4*8+k5*16+k6*32+k7*64+k8*128;
						if(erasetable[judge]==1)
						{   //删除
							lOffset = this->PixelOffset(i,j,wBytesPerLine);
							*(lpDIBBits+lOffset++)=0;
							*(lpDIBBits+lOffset++)=0;
							*(lpDIBBits+lOffset++)=0;
							j++;
							end =0;//继续循环
						}
					}
				}
			}
   //扫描整个图片，从左到右，代码类似
	for(int j=1;j<width-1;j++)
		for(int i=1;i<height-1;i++)
			{
				lOffset = this->PixelOffset(i,j,wBytesPerLine);
				if(*(lpDIBBits+lOffset)==0)
					continue;
				else
				{
					int colorleft,colorright;
					lOffset =this->PixelOffset(i,j-1,wBytesPerLine);
					colorleft = *(lpDIBBits+lOffset);
					lOffset = this->PixelOffset(i,j+1,wBytesPerLine);
					colorright = *(lpDIBBits+lOffset);
					if((colorleft==255)&&(colorright==255))
						continue;
					else
					{
						int k1,k2,k3,k4,k5,k6,k7,k8;
						lOffset = this->PixelOffset(i+1,j-1,wBytesPerLine);
						if(*(lpDIBBits+lOffset)==0)
							k1=1;
						else
							k1 =0;

						lOffset = this->PixelOffset(i+1,j,wBytesPerLine);
						if(*(lpDIBBits+lOffset)==0)
							k2=1;
						else
							k2 =0;
						
						lOffset = this->PixelOffset(i+1,j+1,wBytesPerLine);
						if(*(lpDIBBits+lOffset)==0)
							k3=1;
						else
							k3 =0;

						lOffset = this->PixelOffset(i,j-1,wBytesPerLine);
						if(*(lpDIBBits+lOffset)==0)
							k4=1;
						else
							k4 =0;

						lOffset = this->PixelOffset(i,j+1,wBytesPerLine);
						if(*(lpDIBBits+lOffset)==0)
							k5=1;
						else
							k5 =0;

						lOffset = this->PixelOffset(i-1,j-1,wBytesPerLine);
						if(*(lpDIBBits+lOffset)==0)
							k6=1;
						else
							k6 =0;

						lOffset = this->PixelOffset(i-1,j,wBytesPerLine);
						if(*(lpDIBBits+lOffset)==0)
							k7=1;
						else
							k7 =0;
						lOffset = this->PixelOffset(i-1,j+1,wBytesPerLine);
						if(*(lpDIBBits+lOffset)==0)
							k8=1;
						else
							k8 =0;
						int judge;
						judge = k1+k2*2+k3*4+k4*8+k5*16+k6*32+k7*64+k8*128;
						if(erasetable[judge]==1)
						{
							lOffset = this->PixelOffset(i,j,wBytesPerLine);
							*(lpDIBBits+lOffset++)=0;
							*(lpDIBBits+lOffset++)=0;
							*(lpDIBBits+lOffset++)=0;
							j++;
							end =0;
						}
					}
				}
			}

		}

}





BOOL DIB:: SaveDIB(HANDLE hDib, CFile& file)
{
	// Bitmap文件头
	BITMAPFILEHEADER bmfHdr;
	
	// 指向BITMAPINFOHEADER的指针
	LPBITMAPINFOHEADER lpBI;
	
	// DIB大小
	DWORD dwDIBSize =0;

	if (hDib == NULL)
	{
		// 如果DIB为空，返回FALSE
		return FALSE;
	}

	// 读取BITMAPINFO结构，并锁定
	lpBI = (LPBITMAPINFOHEADER) ::GlobalLock((HGLOBAL) hDib);
	
	if (lpBI == NULL)
	{
		// 为空，返回FALSE
		return FALSE;
	}
	
	// 判断是否是WIN3.0 DIB
//	if (!IS_WIN30_DIB(lpBI))
//	{
		// 不支持其它类型的DIB保存
		
		// 解除锁定
	//	::GlobalUnlock((HGLOBAL) hDib);
		
		// 返回FALSE
	//	return FALSE;
//	}

	// 填充文件头

	// 文件类型"BM"
	bmfHdr.bfType =  0x4d42; //DIB_HEADER_MARKER;

	// 计算DIB大小时，最简单的方法是调用GlobalSize()函数。但是全局内存大小并
	// 不是DIB真正的大小，它总是多几个字节。这样就需要计算一下DIB的真实大小。
	
	// 文件头大小＋颜色表大小
	// （BITMAPINFOHEADER和BITMAPCOREHEADER结构的第一个DWORD都是该结构的大小）
//	dwDIBSize = *(LPDWORD)lpBI; //+ ::PaletteSize((LPSTR)lpBI);
	dwDIBSize = sizeof(BITMAPINFOHEADER);//+lpBI->biSizeImage;	
	// 计算图像大小
	if ((lpBI->biCompression == BI_RLE8) || (lpBI->biCompression == BI_RLE4))
	{
		// 对于RLE位图，没法计算大小，只能信任biSizeImage内的值
		dwDIBSize += lpBI->biSizeImage;
	}
	else
	{
		// 象素的大小
		DWORD dwBmBitsSize;

		// 大小为Width * Height
		dwBmBitsSize = WIDTHBYTES((lpBI->biWidth)*24) * lpBI->biHeight;
		
		// 计算出DIB真正的大小
		dwDIBSize += dwBmBitsSize;

		// 更新biSizeImage（很多BMP文件头中biSizeImage的值是错误的）
		lpBI->biSizeImage = dwBmBitsSize;
	}


	// 计算文件大小：DIB大小＋BITMAPFILEHEADER结构大小
	bmfHdr.bfSize = dwDIBSize + sizeof(BITMAPFILEHEADER);
	
	// 两个保留字
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;

	// 计算偏移量bfOffBits，它的大小为Bitmap文件头大小＋DIB头大小＋颜色表大小
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + lpBI->biSize;
											 // + PaletteSize((LPSTR)lpBI);
	// 尝试写文件
//	TRY
	{
		// 写文件头
		file.Write((LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER));
		
		// 写DIB头和象素
		file.WriteHuge(lpBI, dwDIBSize);
	}
//	CATCH (CFileException, e)
//	{
		// 解除锁定
	//	::GlobalUnlock((HGLOBAL) hDib);
		
		// 抛出异常
///		THROW_LAST();
//	}
//	END_CATCH
	
	// 解除锁定
	::GlobalUnlock((HGLOBAL) hDib);
	
	// 返回TRUE
	return TRUE;
}




HANDLE DIB::ScaleDIB(HANDLE hDIB, float scal_x, float scal_y)
{
	if(scal_x<0 || scal_y <0)
		return NULL;

	LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER) GlobalLock(hDIB);
	int w = lpbi->biWidth;
	int h = lpbi->biHeight;
	BYTE  tempmess[40];
	LPBYTE Src = this->FindDIBBits(hDIB);
	memcpy(tempmess,(LPBYTE)lpbi,40);
	int wid = ((int)(w*scal_x+0.5f)*24+31)/32*4;
	int imgsize =(int) (wid*(int)(h*scal_y+0.5f));
	
	HDIB hDIB2 = GlobalAlloc(GMEM_MOVEABLE,(DWORD)(sizeof(BITMAPINFOHEADER)+imgsize));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB2);
	memcpy((LPBYTE)lpbi,tempmess,40);
	lpbi->biWidth =(int)(w*scal_x+0.5f);
	lpbi->biHeight = (int)(h*scal_y+0.5f);
	lpbi->biSizeImage = imgsize;
	LPBYTE lpData = this->FindDIBBits(hDIB2);
	int srcWidth = w;
	int srcHeight = h;
	int dstWidth = (int)(w*scal_x+0.5f);
	int dstHeight = (int)(h*scal_y+0.5f);

	for(int i=0; i<dstHeight;i++)
	{
		float y_inverse_map = (float)i/scal_y;
		int y_lt = (int)y_inverse_map;
		float v=y_inverse_map - y_lt;
		int indexBase = i *wid;
		for(int j=0;j<dstWidth;j++)
		{
			float x_inverse_map = (float)j/scal_x;
			int x_lt = (int) x_inverse_map;
			float u=x_inverse_map - x_lt;
			int index = indexBase + j*3;
			*(lpData+index) = Src[y_lt*((w*24+31)/32*4)+x_lt*3];
			*(lpData+index+1) = Src[y_lt*((w*24+31)/32*4)+x_lt*3+1];
			*(lpData+index+2) = Src[y_lt*((w*24+31)/32*4)+x_lt*3+2];
		//	int r,g,b;
			//((interPolate(Src,x_lt,y_lt,u,v,srcWidth,srcHeight,&r,&g,&b))) ;
		//	*(lpData+temp)   = b;
			//*(lpData+index++)   = (BYTE)((interPolate(Src,x_lt,y_lt,u,v,srcWidth,srcHeight)>>16)) & 0x000000ff;
		//	(interPolate(Src,x_lt,y_lt,u,v,srcWidth,srcHeight,&r,&g,&b));
		//	*(lpData+temp+1)   = g;
		  //  (interPolate(Src,x_lt,y_lt,u,v,srcWidth,srcHeight,&r,&g,&b));
		//	 *(lpData+temp+2)   =r;
			
		}
	}
	GlobalUnlock(hDIB);
	GlobalUnlock(hDIB2);
	return hDIB2;

}

//cwh 01.6.20
/*****************************************
卷积核心算法
*****************************************/
void DIB::interPolate(LPBYTE Src,int x,int y, float u,float v, int scanw, int scanh,int *r,int *g,int *b)
{
//	UINT r11,g11,b11;
	//r=g=b=0;
		int red1[2][2];
		int green1[2][2];
		int blue1[2][2];
		int xx1[2];
		int yy1[2];
		xx1[0]=x*3;xx1[1]=x*3+3;
		yy1[0]=y;yy1[1]=y+1;
		if(xx1[1]>scanw-1)
			xx1[1] = scanw-1;
		if(yy1[1]>scanh-1)
			yy1[1] = scanh-1;

		for(int i=0;i<2;i++)
		{
			int indexBase1 = yy1[i]*((scanw*24+31)/32*4);
			for(int j=0;j<2;j++)
			{
				int index1 = indexBase1 + xx1[j];
				blue1[j][i] = (*(Src+index1));
			    green1[j][i] = (*(Src+index1+1));
			    red1[j][i] =  (*(Src+index1+2));

			}
		}

		//r11 = ((1-u)*(1-v)*red1[0][0]+(1-u)*v*red1[0][1]+u*(1-v)*red1[1][0]+u*v*red1[1][1]);
	//	g11 = ((1-u)*(1-v)*green1[0][0]+(1-u)*v*green1[0][1]+u*(1-v)*green1[1][0]+u*v*green1[1][1]);
		//b11 = ((1-u)*(1-v)*blue1[0][0]+(1-u)*v*blue1[0][1]+u*(1-v)*blue1[1][0]+u*v*blue1[1][1]);
  
	//	*r=r11;
		//*g=g11;
	//	*b=b11;
//	return (0x00ffffff&((b<<16)|(g<<8)|r));
}

HANDLE DIB::CopyHandle( HANDLE hSrc)
{	
	HANDLE hDst;
	LPBITMAPINFOHEADER lpbi;
	int width,height;
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hSrc);
	width = lpbi->biWidth;
	height = lpbi->biHeight;
	hDst = GlobalAlloc(GMEM_MOVEABLE,lpbi->biSize+lpbi->biSizeImage);
	if(!hDst)
		return NULL;
	LPBYTE lpDest;
	lpDest = (LPBYTE)GlobalLock(hDst);
	memcpy(lpDest,(LPBYTE)lpbi,lpbi->biSize+lpbi->biSizeImage);
	GlobalUnlock(hSrc);
	GlobalUnlock(hDst);
	return hDst;

}
HANDLE  DIB::  Gradient(HANDLE hDIB)
{
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	int width = lpbi->biWidth;
	int height = lpbi->biHeight;
	long lOffset;
	LPBYTE lpS,lpD;
	WORD wBytesPerLine = this->BytePerLine(hDIB);
	HANDLE hNewDIB;
	hNewDIB = GlobalAlloc(GMEM_MOVEABLE,(DWORD)(lpbi->biSize+lpbi->biSizeImage));
	if(!hNewDIB)
	{
		AfxMessageBox("分配内存失败");
		return NULL;
	}
	lpS = (LPBYTE)lpbi;
	lpD =(LPBYTE) GlobalLock(hNewDIB);
	memcpy(lpD,lpS,sizeof(BITMAPINFOHEADER));
	lpS = this->FindDIBBits(hDIB);
	lpD = this->FindDIBBits(hNewDIB);
	int color1,color2;
	for(int i=1;i<height-1;i++)
		for(int j=1;j<width-1;j++)
		{
			lOffset = this->PixelOffset(i+1,j+1,wBytesPerLine);
			color1 = *(lpS+lOffset);
			lOffset = this->PixelOffset(i-1,j-1,wBytesPerLine);
			color2 = *(lpS+lOffset);
			lOffset = this->PixelOffset(i,j,wBytesPerLine);
			*(lpD+lOffset++) = abs(color2-color1)*3;
			*(lpD+lOffset++) = abs(color2-color1)*3;
			*(lpD+lOffset++) = abs(color2-color1)*3;

		}
		for(i =0;i<height;i++)
		{
			lOffset = this->PixelOffset(i,0,wBytesPerLine);
			*(lpD+lOffset++) =0;
			*(lpD+lOffset++) =0;
			*(lpD+lOffset++) =0;
		}

		for(i =0;i<height;i++)
		{
			lOffset = this->PixelOffset(i,width-1,wBytesPerLine);
			*(lpD+lOffset++) =0;
			*(lpD+lOffset++) =0;
			*(lpD+lOffset++) =0;
		}
		for(i =0;i<width;i++)
		{
			lOffset = this->PixelOffset(height-1,i,wBytesPerLine);
			*(lpD+lOffset++) =0;
			*(lpD+lOffset++) =0;
			*(lpD+lOffset++) =0;
		}
		for(i =0;i<width;i++)
		{
			lOffset = this->PixelOffset(0,i,wBytesPerLine);
			*(lpD+lOffset++) =0;
			*(lpD+lOffset++) =0;
			*(lpD+lOffset++) =0;
		}

		GlobalUnlock(hNewDIB);
		GlobalUnlock(hDIB);
		return hNewDIB;
}

//函数寻找图片中的特征区域的中心点
void DIB::LocateImporntPoint(HANDLE hDIB, int Radius, CPoint *pPoint)
{
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	int width ,height;
	width = lpbi->biWidth;
	height = lpbi->biHeight;
	WORD wBytesPerLine;
	wBytesPerLine = this->BytePerLine(hDIB);
	LPBYTE lpData;
	lpData = this->FindDIBBits(hDIB);
	int tempsum=0,sum=0;//定义两个变量用来记数
	long lOffset;
	//扫描整个图片（边缘点除外）寻找特征区域
	for(int i=Radius;i<height-Radius;i++)
		for(int j= Radius;j<width-Radius;j++)
		{	tempsum =0;
			//扫描以Radius×2＋1为边长的正方形区域
			for(int k1=-Radius;k1<=Radius;k1++)
				for(int k2 =-Radius;k2<=Radius;k2++)
				{	
					lOffset = this->PixelOffset(i+k1,j+k2,wBytesPerLine);
					int color = *(lpData+lOffset);
					tempsum +=color;//累加象素值
				}
				if(tempsum>sum)//如果得到的累计象素值大于已经得到的最大值
				{	
					//更改累计象素值大小
					sum = tempsum;
					//更改特征区域中心点
					(pPoint->x) = j;
					(pPoint->y) = i;
				   

				}
		}
	//下面的代码把特征区域的边框设置成白色
	for( i = -Radius;i<=Radius;i++)
	{
		lOffset = this->PixelOffset(pPoint->y-Radius,pPoint->x +i,wBytesPerLine);
		*(lpData+lOffset++) = 255;
		*(lpData+lOffset++) = 255;
		*(lpData+lOffset++) = 255;
	}
	for( i = -Radius;i<=Radius;i++)
	{
		lOffset = this->PixelOffset(pPoint->y+Radius,pPoint->x +i,wBytesPerLine);
		*(lpData+lOffset++) = 255;
		*(lpData+lOffset++) = 255;
		*(lpData+lOffset++) = 255;
	}
	for( i = -Radius;i<=Radius;i++)
	{
		lOffset = this->PixelOffset(pPoint->y+i,pPoint->x-Radius ,wBytesPerLine);
		*(lpData+lOffset++) = 255;
		*(lpData+lOffset++) = 255;
		*(lpData+lOffset++) = 255;
	}
	for( i = -Radius;i<=Radius;i++)
	{
		lOffset = this->PixelOffset(pPoint->y+i,pPoint->x+Radius,wBytesPerLine);
		*(lpData+lOffset++) = 255;
		*(lpData+lOffset++) = 255;
		*(lpData+lOffset++) = 255;
	}
	lOffset = this->PixelOffset(pPoint->y,pPoint->x ,wBytesPerLine);
	*(lpData+lOffset++) = 0;
	*(lpData+lOffset++) = 255;
	*(lpData+lOffset++) = 0;

		GlobalUnlock(hDIB);
}


#define THRESHOLD (RADIUS*2+1)*(RADIUS*2+1)*15
//函数在一幅图片中寻找匹配的中心点
BOOL DIB::MatchImportantPoint(HANDLE hDIB,int CharaterInfo[RADIUS*2+1][RADIUS*2+1][3],CPoint *ImPoint)
{
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	int width = lpbi->biWidth;
	int height = lpbi->biHeight;
	LPBYTE lpData = this->FindDIBBits(hDIB);
    WORD wBytesPerLine = this->BytePerLine(hDIB);
	long lOffset;
	long sum =100000,tempsum;
	//扫描整个图片（边缘点）除外
	for(int i=RADIUS ;i<height-RADIUS;i++)
		for(int j=RADIUS;j<width-RADIUS;j++)
		{	
			tempsum =0;
			//扫描以RADIUS*2+1为边长的正方形区域
			for(int k=-RADIUS;k<=RADIUS;k++)
				for(int kk=-RADIUS;kk<=RADIUS;kk++)
				{
					//计算当前正方形和已知特征区域的颜色差值

				lOffset = this->PixelOffset(i+k,j+kk,wBytesPerLine);
				int colorblue = abs(*(lpData+lOffset++)-CharaterInfo[k+RADIUS][kk+RADIUS][0]);
				int colorgreen = abs(*(lpData+lOffset++)-CharaterInfo[k+RADIUS][kk+RADIUS][1]);
				int colorred = abs(*(lpData+lOffset++)-CharaterInfo[k+RADIUS][kk+RADIUS][2]);
				tempsum +=colorgreen+colorblue+colorred;
				}
				if(tempsum<sum)
				{  //更新差值
					sum = tempsum;
					//更改特征坐标点
					ImPoint->x = j;
					ImPoint->y = i;
				}
		}

		if(sum <THRESHOLD){//找到满足条件的区域
		//下面的代码把找到的区域的边框设置成为白色
		for(i =-RADIUS;i<=RADIUS;i++)
		{
			lOffset = this->PixelOffset(ImPoint->y-RADIUS,ImPoint->x+i,wBytesPerLine);
			*(lpData+lOffset++) = 255;
			*(lpData+lOffset++) = 255;
			*(lpData+lOffset++) = 255;

		}

		for(i =-RADIUS;i<=RADIUS;i++)
		{
			lOffset = this->PixelOffset(ImPoint->y+RADIUS,ImPoint->x+i,wBytesPerLine);
			*(lpData+lOffset++) = 255;
			*(lpData+lOffset++) = 255;
			*(lpData+lOffset++) = 255;

		}
		for(i =-RADIUS;i<=RADIUS;i++)
		{
			lOffset = this->PixelOffset(ImPoint->y+i,ImPoint->x+RADIUS,wBytesPerLine);
			*(lpData+lOffset++) = 255;
			*(lpData+lOffset++) = 255;
			*(lpData+lOffset++) = 255;

		}
		for(i =-RADIUS;i<=RADIUS;i++)
		{
			lOffset = this->PixelOffset(ImPoint->y+i,ImPoint->x-RADIUS,wBytesPerLine);
			*(lpData+lOffset++) = 255;
			*(lpData+lOffset++) = 255;
			*(lpData+lOffset++) = 255;

		}
		GlobalUnlock(hDIB);
		return true;
		}
		else AfxMessageBox("Can't find the corresponding point!");
	GlobalUnlock(hDIB);
	return false;
}
//比较两张图片的相似度
BOOL DIB::ComPareImg(HANDLE hDIB1, HANDLE hDIB2 ,CPoint pt1,CPoint pt2)
{
	if(abs(pt1.x-pt2.x)>3 || abs(pt1.y -pt2.y)>3)//图象偏差过大
	{	
		AfxMessageBox("Imgs Offset are too big");
		return false;
	}
	LPBITMAPINFOHEADER lpbi1,lpbi2;
	lpbi1 = (LPBITMAPINFOHEADER)GlobalLock(hDIB1);
	int width1 = lpbi1->biWidth;
	int height1 = lpbi1->biHeight;
	lpbi2 = (LPBITMAPINFOHEADER)GlobalLock(hDIB2);
	int width2 = lpbi2->biWidth;
	int height2 = lpbi2->biHeight;
	if(width1 != width2 || height1 != height2)//图象长宽尺寸不同
	{
		GlobalUnlock(hDIB1);
		GlobalUnlock(hDIB2);
		AfxMessageBox("Img is not same size");
		return false;
	}
	LPBYTE lpData1,lpData2;
	lpData1 = this->FindDIBBits(hDIB1);
	lpData2 = this->FindDIBBits(hDIB2);
	WORD wBytesPerLine = this->BytePerLine(hDIB1);
	int xleft,xright,ytop,ybottom;
	//下面的一段代码实现图象对齐
	if(pt1.x>=pt2.x)//第一幅图得特征中心点比第二幅图偏右
	{	
	
		xleft = pt2.x;//要处理得左边得象素点个数
		xright =width-pt1.x-1;//要处理得右边得象素点个数
	}
			
	else//第一幅图得特征中心点比第二幅图偏左
	{	
	
		xleft = pt1.x;
		xright = width1-pt2.x-1;
	}
	
	if(pt1.y >=pt2.y)//第一幅图得特征中心点得位置偏上
	{	
	
		ytop = pt2.y;//要处理得中心点上面得象素个数
		ybottom = height1-pt1.y-1;//要处理得中心点下面得象素个数

	}

	else//第一幅图得特征中心点得位置偏下
	{	
		
		ytop = pt1.y;
		ybottom = height1-pt2.y-1;
	}
	long sum=0;
	long lOffset;
	//计算两幅图片交叉区域得象素差值
	for(int i=-ytop;i<=ybottom;i++)
		for(int j=-xleft;j<=xright;j++)
		{	
			//第一幅图
			lOffset = this->PixelOffset(i+pt1.y,j+pt1.x,wBytesPerLine);
			int c11 = *(lpData1+lOffset++);
			int c12 = *(lpData1+lOffset++);
			int c13 = *(lpData1+lOffset++);
			//第二幅图
			lOffset = this->PixelOffset(i+pt2.y,j+pt2.x,wBytesPerLine);
			int c21 = *(lpData2+lOffset++);
			int c22 = *(lpData2+lOffset++);
			int c23 = *(lpData2+lOffset++);
			//计算差值
			sum += abs(c11-c21)+abs(c12-c22)+abs(c13-c23);
		}
		GlobalUnlock(hDIB1);
		GlobalUnlock(hDIB2);
	if(sum>width1*height1*3*2)//判断是否相似
		return false;
	else 
		return true;

}

BOOL DIB::  CompareImg2(HANDLE hDIBBK,HANDLE hDIBCurrent,CPoint pt1,CPoint pt2)
{
	if(abs(pt1.x-pt2.x)>3 || abs(pt1.y -pt2.y)>3)
	{	
		AfxMessageBox("Imgs Offset are too big");
		return false;
	}
	LPBITMAPINFOHEADER lpbi1,lpbi2;
	lpbi1 = (LPBITMAPINFOHEADER)GlobalLock(hDIBBK);
	int width1 = lpbi1->biWidth;
	int height1 = lpbi1->biHeight;
	lpbi2 = (LPBITMAPINFOHEADER)GlobalLock(hDIBCurrent);
	int width2 = lpbi2->biWidth;
	int height2 = lpbi2->biHeight;
	if(width1 != width2 || height1 != height2)
	{
		GlobalUnlock(hDIBBK);
		GlobalUnlock(hDIBCurrent);
		AfxMessageBox("Img is not same size");
		return false;
	}
	LPBYTE lpData1,lpData2;
	lpData1 = this->FindDIBBits(hDIBBK);
	lpData2 = this->FindDIBBits(hDIBCurrent);
	WORD wBytesPerLine = this->BytePerLine(hDIBBK);
	int xleft,xright,ytop,ybottom;

	if(pt1.x>=pt2.x)
	{	
	
		xleft = pt2.x;
		xright =width1-pt1.x-1;
	}
			
	else
	{	
	
		xleft = pt1.x;
		xright = width1-pt2.x-1;
	}
	
	if(pt1.y >=pt2.y)
	{	
	
		ytop = pt2.y;
		ybottom = height1-pt1.y-1;

	}

	else
	{	
		
		ytop = pt1.y;
		ybottom = height1-pt2.y-1;
	}
	long sum=0;
	long lOffset;
	


	for(int i=-ytop;i<=ybottom;i++)
		for(int j=-xleft;j<=xright;j++)
		{	
		
			lOffset = this->PixelOffset(i+pt1.y,j+pt1.x,wBytesPerLine);
			int c11 = *(lpData1+lOffset++);
			int c12 = *(lpData1+lOffset++);
			int c13 = *(lpData1+lOffset++);
			lOffset = this->PixelOffset(i+pt2.y,j+pt2.x,wBytesPerLine);
			int c21 = *(lpData2+lOffset++);
			int c22 = *(lpData2+lOffset++);
			int c23 = *(lpData2+lOffset++);
			lOffset = this->PixelOffset(i+pt2.y,j+pt2.x,wBytesPerLine);
			*(lpData2+lOffset++) = abs(c11-c21);
			*(lpData2+lOffset++) = abs(c12-c22);
			*(lpData2+lOffset++) = abs(c13-c23);
		}
		for(i =0;i<height1;i++)
			for(int j=0;j<width1;j++)
			{
			if(i<pt2.y-ytop || i>pt2.y+ybottom||j<pt2.x-xleft || j >pt2.x+xright)
			{
				lOffset = this->PixelOffset(i,j,wBytesPerLine);
				*(lpData2+lOffset++) = 0;
				*(lpData2+lOffset++) = 0;
				*(lpData2+lOffset++) = 0;
			}
			}
		
		GlobalUnlock(hDIBBK);
		GlobalUnlock(hDIBCurrent);
		return true;
	
}



BOOL DIB::IsScaterPoint(int x, int y, int width, int height, LPBYTE lpData,WORD wBytesPerLine,  int threshold,bool lab[m_HEIGHT][m_WIDTH])
{
	long lOffset;
	lOffset = this->PixelOffset(y,x,wBytesPerLine);
	if(*(lpData+lOffset) == 255 && lab[y][x] == false)
	{
		this->lenth++;
		lab[y][x] = true;
	if(this->lenth >= threshold)
		return true;
	if(x+1<width && lab[y][x+1] == false)
	{	IsScaterPoint(x+1,y,width,height,lpData,wBytesPerLine,threshold,lab);
		if(this->lenth>=threshold)
			return true;
		
	}
	if(x-1>=0 && lab[y][x-1] == false)
	{
		(IsScaterPoint(x-1,y,width,height,lpData,wBytesPerLine,threshold,lab));
		if(this->lenth>=threshold)
			return true;
		
	}
	
	if(y-1>=0 && lab[y-1][x]==false)
	{
		(IsScaterPoint(x,y-1,width,height,lpData,wBytesPerLine,threshold,lab));
		if(this->lenth>=threshold)
			return true;
		
	}
	if(y+1<height && lab[y+1][x]==false)
	{	(IsScaterPoint(x,y+1,width,height,lpData,wBytesPerLine,threshold,lab));
			if(this->lenth>=threshold)
			return true;
			
	}
	if(y+1<height  && x+1 <width && lab[y+1][x+1]==false)
	{	(IsScaterPoint(x+1,y+1,width,height,lpData,wBytesPerLine,threshold,lab));
			if(this->lenth>=threshold)
			return true;
			
	}
	if(y+1<height && x-1 >=0 && lab[y+1][x-1]==false)
	{	(IsScaterPoint(x-1,y+1,width,height,lpData,wBytesPerLine,threshold,lab));
			if(this->lenth>=threshold)
			return true;
			
	}
	if(y-1>=0 && x-1 >=0 &&lab[y-1][x-1]==false)
	{	(IsScaterPoint(x-1,y-1,width,height,lpData,wBytesPerLine,threshold,lab));
			if(this->lenth>=threshold)
			return true;
			
	}
	if(y-1<height && x+1<width && lab[y+1][x]==false)
	{	(IsScaterPoint(x+1,y-1,width,height,lpData,wBytesPerLine,threshold,lab));
			if(this->lenth>=threshold)
			return true;
			
	}
	}
		return false;
}
//函数得到边界得中心点
CPoint DIB:: GetEdgeCenter(HANDLE hDIB)
{
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	int width = lpbi->biWidth;
	int height = lpbi->biHeight;
	WORD wBytesPerLine = this->BytePerLine(hDIB);
	LPBYTE lpData = this->FindDIBBits(hDIB);
	long lOffset;
	int x =0,y =0,num =0;
	//对整幅图片进行扫描
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
		{
			lOffset = this->PixelOffset(i,j,wBytesPerLine);
			if(*(lpData+lOffset) ==255)//如果是白色象素
			{
				x +=j;//中心点得横坐标和纵坐标加上当前得横坐标和纵坐标
				y +=i;
				num++;
			}
		}
		//得到结果坐标点
		CPoint result;
		result.x = x/num;
		result.y = y/num;
		//把中心点设置为绿色
		lOffset = this->PixelOffset(result.y,result.x,wBytesPerLine);
		*(lpData+lOffset++) = 0;
		*(lpData+lOffset++) = 255;
		*(lpData+lOffset++) = 0;
		return result;
}
