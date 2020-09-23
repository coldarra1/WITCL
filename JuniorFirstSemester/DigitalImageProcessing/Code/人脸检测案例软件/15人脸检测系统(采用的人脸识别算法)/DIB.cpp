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
	for(int i=0;i<ImgRange; i++)
		for (int j=0; j<ImgRange; j++)
			this->lab[i][j] = false;

}
DIB::~DIB()
{

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


//函数寻找图片中的特征区域的中心点



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




BOOL DIB::IsScaterPoint(int x, int y, int width, int height, LPBYTE lpData,WORD wBytesPerLine,  int threshold,bool lab[m_HEIGHT][m_WIDTH])
{
	long lOffset;
	//得到数据的偏移
	lOffset = this->PixelOffset(y,x,wBytesPerLine);
	//判断该点是否为白色以及是否计算过了
	if(*(lpData+lOffset) == 255 && lab[y][x] == false)
	{	
		//链长度加一
		this->lenth++;
		//更改标志位
		lab[y][x] = true;
		//如果链长度达到临界值则返回真
	if(this->lenth >= threshold)
		return true;
	//对右边点的边界判断以及标志位判断
	if(x+1<width && lab[y][x+1] == false)
	{	
		//递归调用本函数，对右边的点进行判断
		IsScaterPoint(x+1,y,width,height,lpData,wBytesPerLine,threshold,lab);
		if(this->lenth>=threshold)
			return true;
		
	}
	//处理左边的点
	if(x-1>=0 && lab[y][x-1] == false)
	{
		(IsScaterPoint(x-1,y,width,height,lpData,wBytesPerLine,threshold,lab));
		if(this->lenth>=threshold)
			return true;
		
	}
	//处理上面的点
	if(y-1>=0 && lab[y-1][x]==false)
	{
		(IsScaterPoint(x,y-1,width,height,lpData,wBytesPerLine,threshold,lab));
		if(this->lenth>=threshold)
			return true;
		
	}
	//处理下面的点
	if(y+1<height && lab[y+1][x]==false)
	{	(IsScaterPoint(x,y+1,width,height,lpData,wBytesPerLine,threshold,lab));
			if(this->lenth>=threshold)
			return true;
			
	}
	//处理右下的点
	if(y+1<height  && x+1 <width && lab[y+1][x+1]==false)
	{	(IsScaterPoint(x+1,y+1,width,height,lpData,wBytesPerLine,threshold,lab));
			if(this->lenth>=threshold)
			return true;
			
	}
	//处理左下的点
	if(y+1<height && x-1 >=0 && lab[y+1][x-1]==false)
	{	(IsScaterPoint(x-1,y+1,width,height,lpData,wBytesPerLine,threshold,lab));
			if(this->lenth>=threshold)
			return true;
			
	}
	//处理左上的点
	if(y-1>=0 && x-1 >=0 &&lab[y-1][x-1]==false)
	{	(IsScaterPoint(x-1,y-1,width,height,lpData,wBytesPerLine,threshold,lab));
			if(this->lenth>=threshold)
			return true;
			
	}
	//处理右上的点
	if(y-1<height && x+1<width && lab[y+1][x]==false)
	{	(IsScaterPoint(x+1,y-1,width,height,lpData,wBytesPerLine,threshold,lab));
			if(this->lenth>=threshold)
			return true;
			
	}
	}	
		//如果递归结束，长度达不到临界值，返回假
		return false;
}



BOOL DIB::LightingCompensate(HANDLE hDIB)
{
	if(!hDIB)
		return FALSE;
	LPBITMAPINFOHEADER lpbi;
	int width,height;
	LPBYTE lpData;
	WORD wBytesPerLine;
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	//得到图片宽和高
	width = lpbi->biWidth;
	height = lpbi->biHeight;
	//得到图片数据区
	lpData = this->FindDIBBits(hDIB);
	//得到图片每行的象素所占字节个数
	wBytesPerLine = this->BytePerLine(hDIB);
	//比例系数
	const float thresholdco = 0.05;
	//象素个数的临界常数
	const int thresholdnum = 100;
	//灰度级数组
	int histogram[256];
	for(int i =0;i<256;i++)
		histogram[i] = 0;
	//对于过于小的图片的判断
	if(width*height*thresholdco < thresholdnum)
		return false;
	int colorr,colorg,colorb;
	long lOffset;
	//考察整个图片
	for( i=0;i<height;i++)
		for(int j=0;j<width;j++)
		{	
			//得到象素数据的偏移
			lOffset = this->PixelOffset(i,j,wBytesPerLine);
			//得到rgb值
			colorb = *(lpData+lOffset++);
			colorg = *(lpData+lOffset++);
			colorr = *(lpData+lOffset++);
			//计算灰度值
			int gray = (colorr * 299 + colorg * 587 + colorb * 114)/1000;
			histogram[gray]++;
		}
		int calnum =0;
		int total = width*height;
		int num;
		//下面的循环得到满足系数thresholdco的临界灰度级
		for(i =0;i<256;i++)
		{
			if((float)calnum/total < thresholdco)
			{
				calnum+= histogram[255-i];
				num = i;
			}
			else
				break;
		}
		int averagegray = 0;
		calnum =0;
		//得到满足条件的象素总的灰度值
		for(i = 255;i>=255-num;i--)
		{
			averagegray += histogram[i]*i;
			calnum += histogram[i];
		}
		averagegray /=calnum;
		//得到光线补偿的系数
		float co = 255.0/(float)averagegray;
		//下面的循环对图象进行光线补偿
		for(i =0;i<height;i++)
			for(int j=0;j<width;j++)
			{	
				//得到数据便宜
				lOffset = this->PixelOffset(i,j,wBytesPerLine);
				//得到蓝色分量
				colorb = *(lpData+lOffset);
				//调整
				colorb *=co;
				//临界判断
				if(colorb >255)
					colorb = 255;
				//保存
				*(lpData+lOffset) = colorb;
				//绿色分量
				colorb = *(lpData+lOffset+1);
				colorb *=co;
				if(colorb >255)
					colorb = 255;
				*(lpData+lOffset+1) = colorb;
				//红色分量
				colorb = *(lpData+lOffset+2);
				colorb *=co;
				if(colorb >255)
					colorb = 255;
				*(lpData+lOffset+2) = colorb;

			}
			return TRUE;
}

BOOL DIB::FaceModeling(int Cr,int Cb)
{	
	//Cb的系数常量
	const float cx = 114.38;
	//cr的系数常量
	const float cy = 160.02;
	//角度常量
	const float theta = 2.53;
	//x轴线和y轴线的两个常量
	const float ecx = 1.60;
	const float ecy = 2.41;
	//长轴
	const float a = 25.39;
	//短轴
	const float b = 14.03;
	//相似度常量
	const float judge = 0.5;
	//计算得到x轴数值
	float  x = cos(theta)*(Cb-cx)+sin(theta)*(Cr-cy);
	//y轴数值
	float  y = -sin(theta)*(Cb -cx)+cos(theta)*(Cr-cy);
	//计算离心率
	float temp = pow(x-ecx,2)/pow(a,2)+pow(y-ecy,2)/pow(b,2);
	//如果满足要求返回真，否则假
	if(fabs(temp-1.0)<judge)
		return TRUE;
	else
		return FALSE;

}

LPBYTE DIB::YcctoRgb(LPBYTE lpYcc,WORD wBytesPerLine,int height,int width)
{
	LPBYTE lpRGB;
	//申请内存
	lpRGB = new BYTE[wBytesPerLine*height];
	//检查内容分配
	if(lpRGB == NULL)
	{
		AfxMessageBox("not enought memory");
		return NULL;
	}
	long lOffset;
	//下面的循环实现从ycc到rgb的转换
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
		{	
			//得到数据便宜
			lOffset = PixelOffset(i,j,wBytesPerLine);
			//得到y，Cr，Cb的数值
			int Y = *(lpYcc+lOffset);
			int Cr = *(lpYcc+lOffset+1);
			int Cb = *(lpYcc+lOffset+2);
			//利用公式进行计算，并把结果保存到动态数组里面
			*(lpRGB+lOffset+2) = (1164*(Y-16)+1596*(Cr-128))/1000;
			*(lpRGB+lOffset+1) = (1164*(Y-16) - 813*(Cr-128) - 392*(Cb-128))/1000;
			*(lpRGB+lOffset)   = (1164*(Y-16) +2017*(Cb-128))/1000;
		}
	return lpRGB;
}


int DIB::_Cb(int Y)
{	
	int Cb;
	//如果亮度很小的情况
	if(Y<Kl)
		Cb = 108 + ((Kl-Y)*10)/(Kl-Ymin);
	//亮度很大的情况
	else if(Y>Kh)
		Cb = 108 + ((Y-Kh)*10)/(Ymax - Kh);
	else 
		Cb = -1;
	return Cb;
}

int DIB::_Cr(int Y)
{
	int Cr;
	//亮度很小的情况
	if(Y<Kl)
		Cr = 154 - ((Kl-Y)*10)/(Kl-Ymin);
	//亮度很大的情况
	else if(Y>Kh)
		Cr = 154 - ((Y-Kh)*22)/(Ymax - Kh);
	else
		Cr = -1;
	return Cr;
}
int DIB::_WCr(int Y)
{
	int WCr;
	if(Y<Kl)
		//亮度很小的情况
		WCr = WLcr + ((Y-Ymin)*(Wcr-WLcr))/(Kl-Ymin);
	else if(Y>Kh)
		//亮度很大的情况
		WCr = WHcr + ((Ymax-Y)*(Wcr-WHcr))/(Ymax-Kh);
	else WCr = -1;
	return WCr;
}

int DIB:: _WCb(int Y)
{
	int WCb;
	if(Y<Kl)
		//亮度很小的情况
		WCb = WLcb + ((Y-Ymin)*(Wcb-WLcb))/(Kl-Ymin);
	else if(Y>Kh)
		//亮度很大的情况
		WCb = WHcb + ((Ymax-Y)*(Wcb-WHcb))/(Ymax-Kh);
	else WCb = -1;
	return WCb;
}
void DIB::YccTransform(LPBYTE lpYcc,WORD wBytesPerLine,int height,int width)
{	
	int Y,Cr,Cb;
	long lOffset;
	//下面的循环实现ycc色彩空间的非线性转换
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
		{	
			//得到数据偏移
			lOffset = PixelOffset(i,j,wBytesPerLine);
			//得到y，Cr，Cb数值
			Y = *(lpYcc+lOffset);
			Cr = *(lpYcc+lOffset+1);
			Cb = *(lpYcc+lOffset+2);
			//如果y数值在两个临界值之间，保持不变
			if(Y>=Kl && Y<=Kh)
				continue;
			//调用非线性转换函数调整Cr，Cb的数值
			Cr = (Cr-_Cr(Y))*(Wcr/_WCr(Y))+_Cr(Kh);
			Cb = (Cb-_Cb(Y))*(Wcb/_WCb(Y))+_Cb(Kh);
			*(lpYcc+lOffset+1) = Cr;
			*(lpYcc+lOffset+2) = Cb;
		}
}

void DIB::faceear(LPBYTE lpYcc, WORD wBytesPerLine, int height,int width, bool flag[ImgRange][ImgRange])
{	
	//初始化标志位
	for (int i=0; i<ImgRange; i++)
		for (int j=0; j<ImgRange; j++)
		{
			flag[i][j] = false;
		}

	long lOffset;
	int Cr;
	int Cb;
	for (i=0; i<height; i++)
		for (int j=0; j<width; j++)
		{	
			//得到偏移
			lOffset = PixelOffset(i,j,wBytesPerLine);
			//得到Cr，Cb数值
			Cr = *(lpYcc+lOffset+1);
			Cb = *(lpYcc+lOffset+2);
			//人脸颜色建模
			if(FaceModeling(Cr,Cb))
			{	
				//修改标志位
				flag[i][j] = true;
			}
		}
	
}

void  DIB::FaceLocate(HANDLE hDIB, CRect faceLocation[10], int &faceNum)
{	

	HANDLE hDIBTemp;
	//保存当前数据
	hDIBTemp = this->CopyHandle(hDIB);
	LPBITMAPINFOHEADER lpbi;
	LPBYTE lpData;
	WORD wBytesPerLine;
	int height;
	int width;
	long lOffset;
	//得到图象的基本信息
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	height = lpbi->biHeight;
	width  = lpbi->biWidth;
	lpData = FindDIBBits(hDIB);
	wBytesPerLine = BytePerLine(hDIB);

	//人脸数目初始化为0
	faceNum =0;
	for(int k=0; k<10; k++)
	{	
		//初始化区域
		faceLocation[k].bottom = -1;
		faceLocation[k].top = height;
		faceLocation[k].right = -1;
		faceLocation[k].left = width;
	}

	for(int i=0; i<height; i++)
		for (int j=0; j<width; j++)
		{	
			//偏移
			lOffset = PixelOffset(i,j,wBytesPerLine);
			int num;
			//当前点的数值
			num = *(lpData + lOffset);
			if (num !=0)//不是黑色
			{	
				//递归计算
				RecursiveLocateRect(lpData, wBytesPerLine, i, j, num, faceLocation[faceNum]);
				faceNum++;
			}
		}
	GlobalUnlock(hDIB);
	GlobalFree(hDIB);
	//数值还原
	hDIB = this->CopyHandle(hDIBTemp);
	lpData = FindDIBBits(hDIB);
	wBytesPerLine = BytePerLine(hDIB);
	for (i=0; i<faceNum; i++)
		for (int j=faceLocation[i].top; j<faceLocation[i].bottom; j++)
		{	
			//把得到的人脸区域用绿色矩形标注，处理竖直的两条边
			lOffset = this->PixelOffset(j, faceLocation[i].left, wBytesPerLine);
			*(lpData + lOffset++) = 0;
			*(lpData + lOffset++) = 255;
			*(lpData + lOffset++) = 0;
			lOffset = this->PixelOffset(j, faceLocation[i].right, wBytesPerLine);
			*(lpData + lOffset++) = 0;
			*(lpData + lOffset++) = 255;
			*(lpData + lOffset++) = 0;

		}

		for (i=0; i<faceNum; i++)
		for (int j=faceLocation[i].left; j<faceLocation[i].right; j++)
		{	
			//处理水平的两天矩形边
			lOffset = this->PixelOffset(faceLocation[i].top, j, wBytesPerLine);
			*(lpData + lOffset++) = 0;
			*(lpData + lOffset++) = 255;
			*(lpData + lOffset++) = 0;
			lOffset = this->PixelOffset(faceLocation[i].bottom, j, wBytesPerLine);
			*(lpData + lOffset++) = 0;
			*(lpData + lOffset++) = 255;
			*(lpData + lOffset++) = 0;

		}
	
		
	
	GlobalFree(hDIBTemp);	
	GlobalUnlock(hDIB);
}

void DIB::RecursiveLocateRect(LPBYTE lpData,WORD wBytesPerLine, int y, int x, int num, CRect &faceRect)
{	
	long lOffset;
	//得到偏移
	lOffset = PixelOffset(y,x,wBytesPerLine);
	//数值判断
	if(*(lpData + lOffset) == num)
	{	
		//更改颜色为黑色
		*(lpData + lOffset++) = 0;
		*(lpData + lOffset++) = 0;
		*(lpData + lOffset++) = 0;
		//修改矩形的上下左右四个点位置
		if(faceRect.bottom < y)
		{
			faceRect.bottom = y;
		}

		if(faceRect.top > y)
		{
			faceRect.top = y;
		}

		if(faceRect.right < x)
		{
			faceRect.right = x;
		}

		if(faceRect.left > x)
		{
			faceRect.left = x;
		}
		//上下左右调用本函数进行区域判定
		RecursiveLocateRect(lpData, wBytesPerLine, y-1, x, num,faceRect);
		RecursiveLocateRect(lpData, wBytesPerLine, y+1, x, num, faceRect);
		RecursiveLocateRect(lpData, wBytesPerLine, y, x-1, num, faceRect);
		RecursiveLocateRect(lpData, wBytesPerLine, y, x+1, num, faceRect);
	}
	
}

void DIB::EyeMapC(LPBYTE lpRgb, const LPBYTE lpYcc,  WORD wBytesPerLine, CRect faceLocation)
{
	long lOffset;
	int cr;
	int cb;
	//根据传进来的矩形区域进行眼睛的色度匹配
	for(int i=faceLocation.top; i<=faceLocation.bottom; i++)
		for (int j=faceLocation.left; j<=faceLocation.right; j++)
		{	
			//得到Cr，Cb数值
			lOffset = PixelOffset(i, j, wBytesPerLine);
			cr = *(lpYcc + lOffset +1);
			cb = *(lpYcc + lOffset +2);
			//标志
			bool lab;
			//判断Cb分量的数值，并修改标志
			int cmap = cb -116 ;
			if(cmap >-1 && cmap <4)
				lab = true;
			else
				lab = false;
			//判断Cr分量的数值，并修改标志
			 cmap =  cr- 144  ;
			if(cmap <=-2 || cmap>= 2)
			{
				lab = false;
				
			}
			//根据标志设定图像颜色
			if(lab)
				cmap = 255;
			else
				cmap = 0;
			//保存图象颜色
			*(lpRgb + lOffset++) = cmap;
			*(lpRgb + lOffset++) = cmap;
			*(lpRgb + lOffset++) = cmap;
		}
	
}

void DIB::EyeMapb(LPBYTE lpRgb, const LPBYTE lpYcc,  WORD wBytesPerLine, CRect faceLocation)
{
	long lOffset;
	int cr;
	int cb;

	for(int i=faceLocation.top; i<=faceLocation.bottom; i++)
		for (int j=faceLocation.left; j<=faceLocation.right; j++)
		{
			lOffset = PixelOffset(i, j, wBytesPerLine);
			cb = *(lpYcc + lOffset +2);
		

			*(lpRgb + lOffset++) = cb;
			*(lpRgb + lOffset++) = cb;
			*(lpRgb + lOffset++) = cb;
		}
	
}

void DIB::EyeMapR(LPBYTE lpRgb, const LPBYTE lpYcc,  WORD wBytesPerLine, CRect faceLocation)
{
	long lOffset;
	int cr;
	int cb;

	for(int i=faceLocation.top; i<=faceLocation.bottom; i++)
		for (int j=faceLocation.left; j<=faceLocation.right; j++)
		{
			lOffset = PixelOffset(i, j, wBytesPerLine);
			cr = *(lpYcc + lOffset +1);
			cb = *(lpYcc + lOffset +2);
		
			
			*(lpRgb + lOffset++) = cr;
			*(lpRgb + lOffset++) = cr;
			*(lpRgb + lOffset++) = cr;
		}
	
}

void DIB::ErasionFalseArea(HANDLE hDIB)
{
	int PixelNum[255];
	LPBITMAPINFOHEADER lpbi;
	int width;
	int height;
	LPBYTE lpData;
	WORD wBytesPerLine;
	long lOffset;
	//得到长宽信息
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	height = lpbi->biHeight;
	width  = lpbi->biWidth;
	//得到数据区指针和每行字节数
	lpData = FindDIBBits(hDIB);
	wBytesPerLine = BytePerLine(hDIB);
	//初始化象素累计数组
	for (int i=0; i<255; i++)
	{
		PixelNum[i] = 0;
	}
	
	int calNum =1;
	for (i=0; i<height; i++)
		for (int j=0; j<width; j++)
		{
			lOffset = PixelOffset(i,j,wBytesPerLine);
			//如果象素为白色
			if (*(lpData + lOffset)==255)
			{	
				//递归统计该区域连续的白色点象素点个数
				RecursiveCal(lpData, i,j,wBytesPerLine, PixelNum[calNum],calNum);
				calNum++;
			}
		}
		
		for (i=0; i<calNum; i++)
		{	
			//如果象素点个数小于一定数目则把这个标志设置为0
			if (PixelNum[i] < AREAPIXEL)
			{
				PixelNum[i] = 0;
			}
		}
		//下面的循环根据标志数组来最终设定图象的颜色
		for(i=0; i<height; i++)
			for (int j=0; j<width; j++)
			{
				lOffset = PixelOffset( i,j,wBytesPerLine);
				int num = *(lpData + lOffset);
				//如果当前点不是黑色点
				if(num != 0)
				{	
					//如果标志数组为0，则设置为黑色
					if(PixelNum[num] == 0)
					{
						*(lpData+lOffset++) =0;
						*(lpData+lOffset++) =0;
						*(lpData+lOffset++) =0;
					}
					//否则设置为白色
					else
					{
						*(lpData+lOffset++) =255;
						*(lpData+lOffset++) =255;
						*(lpData+lOffset++) =255;
					}
				}
			}
}


void DIB::RecursiveCal(LPBYTE lpData, int y, int x, WORD wBytesPerLine, int &pixelNum, int num)
{	
	long lOffset;
	
	lOffset = PixelOffset(y,x,wBytesPerLine);
	//如果当前点为白色点
	if(*(lpData+lOffset) == 255)
	{	
		//把当前点大小设置成为序号值
		*(lpData+lOffset++) = num;
		*(lpData+lOffset++) = num;
		*(lpData+lOffset++) = num;
		//象素个数加一
		pixelNum++;
	
	int tempx;
	int tempy;
	
	//递归当前点上面的点
	tempy = y-1;
	tempx = x;
	RecursiveCal(lpData,tempy,tempx,wBytesPerLine,pixelNum,num);
	
	//下面的点
	tempy = y+1;
	tempx = x;
	RecursiveCal(lpData,tempy,tempx,wBytesPerLine,pixelNum,num);
	
	//左边的点
	tempy = y;
	tempx = x-1;
	RecursiveCal(lpData,tempy,tempx,wBytesPerLine,pixelNum,num);
	//右边的点
	tempy = y;
	tempx = x+1;
	RecursiveCal(lpData,tempy,tempx,wBytesPerLine,pixelNum,num);
	
	}

}

void DIB::eyeMap(LPBYTE lpResult, bool eyemapc[][ImgRange], bool eyemapl[][ImgRange], bool lab[][ImgRange], WORD wBytesPerLine, CRect faceLocation)
{	
	long lOffset;
	//根据得到的亮度和色度信息对眼睛进行综合匹配
	for(int i=faceLocation.top; i<=faceLocation.bottom; i++)
		for (int j=faceLocation.left; j<faceLocation.right; j++)
		{
			lOffset = PixelOffset(i, j, wBytesPerLine);
			//如果当前点的亮度和色度匹配都为真，并且在人脸区域内
			//就设置为白色，否则设置为黑色
			if((eyemapc[i][j]) && (eyemapl[i][j]) && lab[i][j])
			{
				*(lpResult + lOffset++) = 255;
				*(lpResult + lOffset++) = 255;
				*(lpResult + lOffset++) = 255;
			}

			else
			{
				*(lpResult + lOffset++) = 0;
				*(lpResult + lOffset++) = 0;
				*(lpResult + lOffset++) = 0;
			}
		}
}

void DIB::EyeMapL(LPBYTE lpRgb, WORD wBytesPerLine, CRect faceLocation)
{
	int r;
	int g;
	int b;
	int gray ;
	long lOffset;
	//下面的循环实现眼睛的亮度匹配
	for (int i=faceLocation.top; i<=faceLocation.bottom; i++)
		for (int j=faceLocation.left; j<=faceLocation.right; j++)
		{
			lOffset = PixelOffset(i, j, wBytesPerLine);
			//得到rgb值
			b = *(lpRgb + lOffset);
			g = *(lpRgb + lOffset+1);
			r = *(lpRgb + lOffset+2);
			//计算得到灰度
			gray = (r*10+g*30+b*60)/100;
			//根据眼睛的亮度区域来设定图象的数值
			if(100<gray && 125>gray)
				gray =255;
			else
				gray = 0;
			*(lpRgb + lOffset++) = gray;
			*(lpRgb + lOffset++) = gray;
			*(lpRgb + lOffset++) = gray;
		}
}

void  DIB::RgbtoYcb(HANDLE hDIB, LPBYTE lpYcb)
{
	LPBITMAPINFOHEADER lpbi;
	int width,height;
	WORD wBytesPerLine;
	LPBYTE lpData;
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	//得到图象的基本信息
	width = lpbi->biWidth;
	height = lpbi->biHeight;
	lpData = FindDIBBits(hDIB);
	wBytesPerLine = BytePerLine(hDIB);

	long lOffset;
	//下面的循环实现从rgb到ycc的转化
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
		{
				lOffset = PixelOffset(i,j,wBytesPerLine);
				//得到rgb数值
				int b = *(lpData + lOffset);
				int g = *(lpData + lOffset+1);
				int r = *(lpData + lOffset+2);
				//计算得到y，cr，cb的数值
				int Y = (257*r+504*g+98*b)/1000+16;
				int Cr = (439*r-368*g-71*b)/1000+128;
				int Cb = (-148*r-291*g+439*b)/1000+128;
				//保存计算得到的数值
				*(lpYcb+lOffset++) = Y;
				*(lpYcb+lOffset++) = Cr;
				*(lpYcb+lOffset++) = Cb;

		}
		GlobalUnlock(hDIB);

}

void DIB::Erasion(HANDLE hDIB)
{
	LPBITMAPINFOHEADER lpbi;
	LPBYTE lpData;
	WORD wBytesPerLine;
	long lOffset;
	long lOffsetJudge;
	int height;
	int width;
	
	//得到基本数据
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	height = lpbi->biHeight;
	width = lpbi->biWidth;
	wBytesPerLine = BytePerLine(hDIB);
	lpData = FindDIBBits(hDIB);
	
	HANDLE hTempDIB;
	LPBYTE lpTemp;
	//申请同样大小的内存
	hTempDIB =   GlobalAlloc(GMEM_MOVEABLE,(DWORD)(sizeof(BITMAPINFOHEADER) + wBytesPerLine*height));
	//判断内存情况
	if(!hTempDIB)
	{	
		GlobalFree(hTempDIB);
		GlobalFree(hDIB);
		return;
	}
	lpTemp = (LPBYTE)GlobalLock(hTempDIB);
	lpTemp+= sizeof(BITMAPINFOHEADER);
	//下面的循环实现腐蚀功能
	for (int i=1; i<height-1; i++)
		for (int j=1; j<width-1; j++)
		{
			lOffset = PixelOffset(i,j,wBytesPerLine);
			//如果为白色点
			if (*(lpData+lOffset) == 255)
			{	
				//考察上面的点
				lOffsetJudge = PixelOffset(i-1, j, wBytesPerLine);
				//如果是黑色就把原来的点设置为黑色，并接着循环
				if (*(lpData + lOffsetJudge) ==0)
				{
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					continue;
				}
				//考察下面的点
				lOffsetJudge = PixelOffset(i+1, j, wBytesPerLine);
				if (*(lpData + lOffsetJudge) ==0)
				{
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					continue;
				}
				//左面的点
				lOffsetJudge = PixelOffset(i, j-1, wBytesPerLine);
				if (*(lpData + lOffsetJudge) ==0)
				{
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					continue;
				}
				//右面的点
				lOffsetJudge = PixelOffset(i, j+1, wBytesPerLine);
				if (*(lpData + lOffsetJudge) ==0)
				{
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					continue;
				}
				//如果上下左右四个点都是白色，则设置为白色
				lOffset = this->PixelOffset(i, j, wBytesPerLine);
				*(lpTemp + lOffset)   = 255;
				*(lpTemp + lOffset+1) = 255;
				*(lpTemp + lOffset+2) = 255;
				
			}
			//如果当前点为黑色，则在暂时的目标区域中设置为黑色
			else
			{
				*(lpTemp + lOffset)   = 0;
				*(lpTemp + lOffset+1) = 0;
				*(lpTemp + lOffset+2) = 0;
			}
		}
		
		//把图象周边的点全部设置为黑色
		for(i=0; i<height; i++)
		{
			lOffset = PixelOffset(i, 0, wBytesPerLine);
				*(lpTemp + lOffset)   = 0;
				*(lpTemp + lOffset+1) = 0;
				*(lpTemp + lOffset+2) = 0;

		}
		
		for(i=0; i<height; i++)
		{
			lOffset = PixelOffset(i, width-1, wBytesPerLine);
				*(lpTemp + lOffset)   = 0;
				*(lpTemp + lOffset+1) = 0;
				*(lpTemp + lOffset+2) = 0;

		}

	for (i=0; i<width; i++)
		{
			lOffset = PixelOffset(0, i, wBytesPerLine);
				*(lpTemp + lOffset)   = 0;
				*(lpTemp + lOffset+1) = 0;
				*(lpTemp + lOffset+2) = 0;

		}
	
	for (i=0; i<width; i++)
		{
			lOffset = PixelOffset(height-1, i, wBytesPerLine);
				*(lpTemp + lOffset)   = 0;
				*(lpTemp + lOffset+1) = 0;
				*(lpTemp + lOffset+2) = 0;

		}
	//把暂时区域的数值拷贝到原来的句柄下面
	memcpy(lpData,lpTemp,wBytesPerLine*height);
	GlobalUnlock(hDIB);
	GlobalUnlock(hTempDIB);
	GlobalFree(hTempDIB);

}


void DIB::Erasion2(HANDLE hDIB)
{
	LPBITMAPINFOHEADER lpbi;
	LPBYTE lpData;
	WORD wBytesPerLine;
	long lOffset;
	long lOffsetJudge;
	int height;
	int width;

	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	height = lpbi->biHeight;
	width = lpbi->biWidth;
	wBytesPerLine = BytePerLine(hDIB);
	lpData = FindDIBBits(hDIB);
	
	HANDLE hTempDIB;
	LPBYTE lpTemp;
	//申请相同大小的内存
	hTempDIB =   GlobalAlloc(GMEM_MOVEABLE,(DWORD)(sizeof(BITMAPINFOHEADER) + wBytesPerLine*height));
	if(!hTempDIB)
	{	
		GlobalFree(hTempDIB);
		GlobalFree(hDIB);
		return;
	}
	lpTemp = (LPBYTE)GlobalLock(hTempDIB);
	lpTemp+= sizeof(BITMAPINFOHEADER);
	//下面的代码实现腐蚀功能
	for (int i=1; i<height-1; i++)
		for (int j=1; j<width-1; j++)
		{	
			//如果当前点为白色
			lOffset = PixelOffset(i,j,wBytesPerLine);
			if (*(lpData+lOffset) == 255)
			{
				
				//判断左边的带你，如果是黑色的就把暂时区域中的对应点设置为黑色
				lOffsetJudge = PixelOffset(i, j-1, wBytesPerLine);
				if (*(lpData + lOffsetJudge) ==0)
				{
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					continue;
				}
				//考察右边的点
				lOffsetJudge = PixelOffset(i, j+1, wBytesPerLine);
				if (*(lpData + lOffsetJudge) ==0)
				{
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					*(lpTemp + lOffset++) = 0;
					continue;
				}

				//如果左右两边的点都是白色把点设置为白色
				lOffset = this->PixelOffset(i, j, wBytesPerLine);
				*(lpTemp + lOffset)   = 255;
				*(lpTemp + lOffset+1) = 255;
				*(lpTemp + lOffset+2) = 255;
				
			}
			//如果当前点为黑色，则把暂时区域中对应点设置为黑色
			else
			{
				*(lpTemp + lOffset)   = 0;
				*(lpTemp + lOffset+1) = 0;
				*(lpTemp + lOffset+2) = 0;
			}
		}
		//把图象四周的点设置为黑色
		for(i=0; i<height; i++)
		{
			lOffset = PixelOffset(i, 0, wBytesPerLine);
				*(lpTemp + lOffset)   = 0;
				*(lpTemp + lOffset+1) = 0;
				*(lpTemp + lOffset+2) = 0;

		}
		
		for(i=0; i<height; i++)
		{
			lOffset = PixelOffset(i, width-1, wBytesPerLine);
				*(lpTemp + lOffset)   = 0;
				*(lpTemp + lOffset+1) = 0;
				*(lpTemp + lOffset+2) = 0;

		}

	for (i=0; i<width; i++)
		{
			lOffset = PixelOffset(0, i, wBytesPerLine);
				*(lpTemp + lOffset)   = 0;
				*(lpTemp + lOffset+1) = 0;
				*(lpTemp + lOffset+2) = 0;

		}
	
	for (i=0; i<width; i++)
		{
			lOffset = PixelOffset(height-1, i, wBytesPerLine);
				*(lpTemp + lOffset)   = 0;
				*(lpTemp + lOffset+1) = 0;
				*(lpTemp + lOffset+2) = 0;

		}
	//把暂时区域的点拷贝到原句柄下
	memcpy(lpData,lpTemp,wBytesPerLine*height);
	GlobalUnlock(hDIB);
	GlobalUnlock(hTempDIB);
	GlobalFree(hTempDIB);

}
void DIB::Dilation(HANDLE hDIB)
{
	LPBITMAPINFOHEADER lpbi;
	int height;
	int width;
	WORD wBytesPerLine;
	LPBYTE lpData;
	LPBYTE lpTemp;
	long lOffset;
	//得到图象的基本信息
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	height = lpbi->biHeight;
	width = lpbi->biWidth;
	wBytesPerLine = this->BytePerLine(hDIB);
	lpData = this->FindDIBBits(hDIB);
	//申请一块和数据区大小相同的内存
	lpTemp = (LPBYTE) new BYTE[wBytesPerLine * height];
	
	
	long lOffsetJudge;
	for (int i=1; i<height-1; i++)
		for (int j=1; j<width-1; j++)
		{	
			lOffset = this->PixelOffset(i, j, wBytesPerLine);
			//如果当前点为白色，接着循环
			if(*(lpData + lOffset) == 255)
			{
				*(lpTemp + lOffset++) = 255;
				*(lpTemp + lOffset++) = 255;
				*(lpTemp + lOffset++) = 255;
				continue;
			}
			//否则考察上下左右四个点
			else
			{	
				lOffsetJudge = this->PixelOffset(i-1, j, wBytesPerLine);
				//如果上面的点为白色
				if(*(lpData + lOffsetJudge) == 255)
				{	//设置为白色，并继续循环
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					continue;
				}

				//考察下面的点
				lOffsetJudge = this->PixelOffset(i+1,j, wBytesPerLine);
				if(*(lpData + lOffsetJudge) == 255)
				{
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					continue;
				}
				
				//考察左边的点
				lOffsetJudge = this->PixelOffset(i,j-1, wBytesPerLine);
				if(*(lpData + lOffsetJudge) == 255)
				{
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					continue;
				}
				//考察右边的点
				lOffsetJudge = this->PixelOffset(i,j+1, wBytesPerLine);
				if(*(lpData + lOffsetJudge) == 255)
				{
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					*(lpTemp + lOffset++) = 255;
					continue;
				}
				//如果上下左右都是黑色点，则把暂时区域的点设置为黑色
				lOffset = this->PixelOffset(i,j,wBytesPerLine);
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;

			}
				
		}
		//处理图象四周的点，设置为黑色
		for(i=0; i<height; i++)
		{
			lOffset = this->PixelOffset(i, 0, wBytesPerLine);
			{
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;
			}
		}

		for(i=0; i<height; i++)
		{
			lOffset = this->PixelOffset(i, width-1, wBytesPerLine);
			{
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;
			}
		}

		for(i=0; i<width; i++)
		{
			lOffset = this->PixelOffset(0, i, wBytesPerLine);
			{
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;
			}
		}

		for(i=0; i<width; i++)
		{
			lOffset = this->PixelOffset(height-1, i, wBytesPerLine);
			{
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;
				*(lpTemp + lOffset++) = 0;
			}
		}
		//把暂时区域的点拷贝到原句柄区域下面
		memcpy(lpData, lpTemp, wBytesPerLine*height);
		delete [] lpTemp;
		GlobalUnlock(hDIB);

}

void DIB::DeleteFasleEye(HANDLE hDIB, CRect facelocation)
{
	LPBYTE lpData;
	LPBITMAPINFOHEADER lpbi;
	int height;
	int width;
	long lOffset;
	WORD wBytesPerLine;

	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	height = lpbi->biHeight;
	width = lpbi->biWidth;
	lpData = this->FindDIBBits(hDIB);
	wBytesPerLine = this->BytePerLine(hDIB);
	for (int i=0; i<height; i++)
		for (int j=0; j<width; j++)
		{
			lOffset = this->PixelOffset(i, j, wBytesPerLine);
			if(*(lpData + lOffset) == 255)
			{
				if(i<(facelocation.bottom+facelocation.top)/2)
				{
					*(lpData + lOffset++) = 0;
					*(lpData + lOffset++) = 0;
					*(lpData + lOffset++) = 0;
				}
			}
		}
		GlobalUnlock(hDIB);
}

void DIB::DeleteScatePoint(HANDLE hDIB)
{	
	LPBITMAPINFOHEADER lpbi;
	int height;
	int width;
	LPBYTE lpData;
	WORD wBytesPerLine;
	long lOffset;
	
	//得到图象的基本信息
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	height = lpbi->biHeight;
	width  = lpbi->biWidth;
	wBytesPerLine = this->BytePerLine(hDIB);
	lpData = this->FindDIBBits(hDIB);
	
	for (int i=0; i<height; i++)
		for(int j=0; j<width; j++)
		{	
			//得到偏移
			lOffset = this->PixelOffset(i, j, wBytesPerLine);
			//如果当前点为白色点
			if(*(lpData + lOffset) == 255)
			{	
				//设定判断数组
				for(int ii = 0;ii<ImgRange;ii++)
					for (int jj=0; jj<ImgRange; jj++)
						this->lab[ii][jj] = false;
					//设定判断长度
					this->lenth=0;
					//判断是否为离散点
				bool judge = this->IsScaterPoint(j, i, width,height,lpData,wBytesPerLine,3,this->lab);
				if(!judge)
				{	
					//是离散点则把该点设置为黑色
					*(lpData + lOffset++) = 0;
					*(lpData + lOffset++) = 0;
					*(lpData + lOffset++) = 0;
				}
			}
		}
	GlobalUnlock(hDIB);
}

void  DIB::  MouseMap(LPBYTE lpRgb, const LPBYTE lpYcc,  WORD wBytesPerLine, CRect faceLocation)
{	
	//下面的循环在人脸的区域内实现嘴巴的匹配
	for (int i=faceLocation.top; i<faceLocation.bottom; i++)
		for (int j=faceLocation.left; j<faceLocation.right; j++)
		{	
			//得到偏移
			long lOffset = this->PixelOffset(i, j, wBytesPerLine);
			//得到cr，cb的数值
			int cr = *(lpYcc+lOffset+1);
			int cb = *(lpYcc+lOffset+2);
			//标志
			bool lab;
			int mapm;
			//根据cr的数值设定标志
			cr = cr-143;
			if(cr <-5 || cr>5)
			{
				cr = 0;
				
			}
		
			cr *=cr;
			
			if(cr>16)
				 lab = true;
			else
				lab = false;
			//根据cb的时值设定标志
			cb= cb-120;
			if(cb<-5 || cb >5)
				
			{
				cb = 0;
				if(lab = true)
					lab = false;
			}
			//如果cr，cb两项数值都在设定的范围之内，则设定颜色位白色，否则黑色
			if(lab)
				mapm = 255;
			else
				mapm = 0;
			 
			*(lpRgb + lOffset++) = mapm;
			*(lpRgb + lOffset++) = mapm;
			*(lpRgb + lOffset++) = mapm;

			
		}
}

void DIB::MouthCenter(HANDLE hDIB, CRect faceLocation, CPoint &mouthLocation)
{
	LPBITMAPINFOHEADER lpbi;
	int height;
	int width;
	long lOffset;
	WORD wBytesPerLine;
	LPBYTE lpData;
	
	//得到图象的基本信息
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	height = lpbi->biHeight;
	width  = lpbi->biWidth;
	wBytesPerLine = this->BytePerLine(hDIB);
	lpData = this->FindDIBBits(hDIB);
	
	//下面的三个变量用来累计嘴巴区域的象素的x，y和象素点数
	int xnum = 0 ;
	int ynum = 0 ;
	int count = 0;
	for (int i=faceLocation.top; i<faceLocation.bottom; i++)
		for (int j=faceLocation.left; j<faceLocation.right; j++)
		{
			lOffset = this->PixelOffset(i, j, wBytesPerLine);
			//白色点
			if(*(lpData + lOffset) == 255)
			{	
				//x值加
				xnum +=j;
				//y值加
				ynum +=i;
				//点数加
				count++;
			}
		}
		//得到中心点位置
	mouthLocation.x = xnum/count;
	mouthLocation.y = ynum/count;
	
	//把中心点设置位绿色
	lOffset = this->PixelOffset(mouthLocation.y, mouthLocation.x, wBytesPerLine);
	*(lpData + lOffset++) =0;
	*(lpData + lOffset++) =255;
	*(lpData + lOffset++) =0;

	GlobalUnlock(hDIB);
}

void DIB::EyeCenter(HANDLE hDIB, CRect faceLocation, CPoint &eye1, CPoint &eye2)
{
	LPBITMAPINFOHEADER lpbi;
	LPBYTE lpData;
	long lOffset;
	WORD wBytesPerLine;
	int height;
	int width;
	int pixelnum =0;
	int num =0;
	//得到图象基本信息
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	height = lpbi->biHeight;
	width  = lpbi->biWidth;
	lpData = this->FindDIBBits(hDIB);
	wBytesPerLine  = this->BytePerLine(hDIB);
	//考察人脸区域
	for(int i=faceLocation.top; i<faceLocation.bottom; i++)
		for (int j=faceLocation.left; j<faceLocation.right; j++)
		{
			lOffset = this->PixelOffset(i, j, wBytesPerLine);
			//白色点
			if(*(lpData + lOffset) == 255)
				//递归统计象素并修改象素值
				this->RecursiveCal(lpData,i,j,wBytesPerLine,pixelnum,++num);
		}
		//初始化眼睛的坐标
		eye1.x =0;
		eye1.y =0;
		eye2.x =0;
		eye2.y =0;
		//初始化象素点个数
		int eye1count=0;
		int eye2count =0;
		for (i=faceLocation.top; i<faceLocation.bottom; i++)
			for (int j=faceLocation.left; j<faceLocation.right; j++)
			{
				lOffset = this->PixelOffset(i, j, wBytesPerLine);
				//如果象素点的数值为1
				if(*(lpData + lOffset) == 1)
				{	
					//眼睛1的横坐标和纵坐标加上当前点的坐标值
					eye1.x +=j;
					eye1.y +=i;
					eye1count++;
					//把当前点改成白色
					*(lpData + lOffset++) = 255;
					*(lpData + lOffset++) = 255;
					*(lpData + lOffset++) = 255;

				}
				//如果当前象素的数值为2
				else if(*(lpData + lOffset) == 2)
				{	
					//眼睛2的横坐标和纵坐标加上当前点的坐标值
					eye2.x +=j;
					eye2.y +=i;
					//象素点个数加一
					eye2count++;
					//把当前点设置为白色
					*(lpData + lOffset++) = 255;
					*(lpData + lOffset++) = 255;
					*(lpData + lOffset++) = 255;
				}
			}
			//计算眼睛的中心点坐标
			eye1.x /=eye1count;
			eye1.y /=eye1count;
			eye2.x /=eye2count;
			eye2.y /=eye2count;
			//把中心点设置为绿色
			lOffset = this->PixelOffset(eye1.y, eye1.x ,wBytesPerLine);
			*(lpData + lOffset++) = 0;
			*(lpData + lOffset++) = 255;
			*(lpData + lOffset++) = 0;

			lOffset = this->PixelOffset(eye2.y, eye2.x ,wBytesPerLine);
			*(lpData + lOffset++) = 0;
			*(lpData + lOffset++) = 255;
			*(lpData + lOffset++) = 0;
	GlobalUnlock(hDIB);
}

void DIB::EllipseFace(HANDLE hDIB, CPoint mouth, CPoint eye1, CPoint eye2)
{
	LPBYTE lpData;
	LPBITMAPINFOHEADER lpbi;
	int width;
	int height;
	WORD wBytesPerLine;
	long lOffset;
	//得到图象的基本信息
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	height = lpbi->biHeight;
	width  = lpbi->biWidth;
	lpData = this->FindDIBBits(hDIB);
	wBytesPerLine = this->BytePerLine(hDIB);
	
	//用dda算法画三角形
	this->DdaLine(mouth,eye1,lpData,wBytesPerLine);
	this->DdaLine(mouth,eye2,lpData,wBytesPerLine);
	this->DdaLine(eye1,eye2,lpData,wBytesPerLine);
	
	//椭圆的中心点和两个焦点坐标
	int ellipsecenter_x;
	int ellipsecenter_y;
	int ellipseFocusTop_x;
	int ellipseFocusTop_y;
	int ellipseFocusBottom_x;
	int ellipseFocusBottom_y;
	
	//根据眼睛和嘴巴的坐标计算椭圆的中心点坐标
	ellipsecenter_x = (eye1.x + eye2.x + mouth.x )/3;
	ellipsecenter_y = (eye1.y + eye2.y)/2 -abs(eye2.x - eye1.x)/2;

	//上面的焦点
	ellipseFocusTop_x = ellipsecenter_x;
	ellipseFocusBottom_x = ellipsecenter_x;

	//下面的焦点
	ellipseFocusTop_y =  ellipsecenter_y + (eye1.y +eye2.y)/2 -mouth.y;
	ellipseFocusBottom_y = ellipsecenter_y - ((eye1.y +eye2.y)/2 -mouth.y)+2;

	//长轴
	int a = (eye1.x-eye2.x)*2-2;
	
	for (int i=0; i<height; i++)
		for (int j=0; j<width; j++)
		{	
			//得到一个点到两个焦点的距离和
			int lenth = sqrt(pow(j-ellipseFocusTop_x,2)+pow(i-ellipseFocusTop_y,2))
				+sqrt(pow(j-ellipseFocusBottom_x,2)+ pow(i-ellipseFocusBottom_y,2));
			//判断距离和与长轴的关系
			if(lenth<2*a+2 && lenth >2*a-2)
			{	
				//把点设置为绿色
				lOffset = this->PixelOffset(i, j, wBytesPerLine);
				*(lpData + lOffset++) = 0;
				*(lpData + lOffset++) = 255;
				*(lpData + lOffset++) = 0;
			}
		}


	GlobalUnlock(hDIB);
}


void DIB::DdaLine(CPoint from, CPoint end, LPBYTE lpData, WORD wBytesPerLine)
{	
	//x，y的增量
	float delta_x;
	float delta_y;
	//x，y的坐标
	float x;
	float y;
	//x，y上的差值
	int dx;
	int dy;
	//总的步长
	int steps;
	int k;
	//得到x，y的差值
	dx = end.x - from.x;
	dy = end.y - from.y;
	//判断x，y上的差值大小，确定步长
	if(abs(dx) > abs(dy))
	{
		steps = abs(dx);
	}
	else
	{
		steps = abs(dy);
	}

	//得到每次增量的大小
	delta_x = (float)dx / (float)steps;
	delta_y = (float)dy / (float)steps;
	//设定x，y的起点
	x = (float)from.x;
	y = (float)from.y;

	//设定初始点的颜色为绿色
	long lOffset = this->PixelOffset(y, x, wBytesPerLine);
	*(lpData + lOffset++) = 0;
	*(lpData + lOffset++) = 255;
	*(lpData + lOffset++) = 0;

	//根据计算得到的步长，把直线上的点填充成绿色
	for (k=1;k<=steps; k++)
	{	
		//x，y分别加上各自的增量
		x+=delta_x;
		y+=delta_y;
		//设置点的颜色
		lOffset = this->PixelOffset(y, x, wBytesPerLine);
		*(lpData + lOffset++) = 0;
		*(lpData + lOffset++) = 255;
		*(lpData + lOffset++) = 0;

	}
	

}
