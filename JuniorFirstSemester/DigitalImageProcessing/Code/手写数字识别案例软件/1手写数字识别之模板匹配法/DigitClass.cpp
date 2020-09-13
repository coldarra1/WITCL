// DigitClass.cpp: implementation of the CDigitClass class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DigitRecog.h"
#include "DigitClass.h"
#include "Thinner.h"
#include "dib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDigitClass::CDigitClass()
{

}

CDigitClass::~CDigitClass()
{

}

void CDigitClass::CopyArToBitmap(void)
{
	LONG x, y;
	digitWidth = digitdib.GetWidth();
	digitHeight = digitdib.GetHeight();
	for(x=0; x<digitWidth; x++)
	{
		for(y=0; y<digitHeight; y++)
		{
			digitdib.SetPixel8(x, y, digitarray[x][y]);
			//digitdib.SetPixel8(x, y, 0);
		}
	}
}

void CDigitClass::CopyBitmapToAr(void)
{
	LONG x, y;
	digitWidth = digitdib.GetWidth();
	digitHeight = digitdib.GetHeight();

	for(x=0; x<digitWidth; x++)
	{
		for(y=0; y<digitHeight; y++)
		{
			digitarray[x][y] = digitdib.GetPixel8(x, y);
		}
	}
}

void CDigitClass::BinaryDigit(BYTE thre)
{
	digitWidth = digitdib.GetWidth();
	digitHeight = digitdib.GetHeight();
	LONG x, y;

	for(x=0; x<digitWidth; x++)
	{
		for(y=0; y<digitHeight; y++)
		{
			if(digitarray[x][y] >= thre)
				digitarray[x][y]=(BYTE)1;
			else
				digitarray[x][y]=(BYTE)0;
		}
	}
}

void CDigitClass::ThinDigit_1()
{
	LONG x,y,k;
	k=0;

	digitWidth = digitdib.GetWidth();
	digitHeight = digitdib.GetHeight();

	for(x=0; x<digitWidth; x++)
	{
		digitarray[x][0] = (BYTE)0;
		digitarray[x][digitHeight-1] = (BYTE)0;
	}

	for(y=0; y<digitHeight; y++)
	{
		digitarray[0][y] = (BYTE)0;
		digitarray[digitWidth-1][y] = (BYTE)0;
	}

	for(x=0; x<digitWidth; x++)
	{
		for(y=0; y<digitHeight; y++)
		{
			digitarray1[k] = digitarray[x][y];
			if(digitarray1[k] != 0)
				digitarray1[k] = (BYTE)1;
			k++;
		}
	}

	ThinnerHilditch((void *)digitarray1, digitWidth, digitHeight);

	k=0;
	for(x=0; x<digitWidth; x++)
	{
		for(y=0; y<digitHeight; y++)
		{
			digitarray[x][y] = digitarray1[k];
			if(digitarray[x][y]!=0)
				digitarray[x][y] = (BYTE)1;
			k++;
		}
	}
}

void CDigitClass::ThinDigit_2()
{
	LONG x,y,k;
	k=0;

	digitWidth = digitdib.GetWidth();
	digitHeight = digitdib.GetHeight();

	for(x=0; x<digitWidth; x++)
	{
		digitarray[x][0] = (BYTE)0;
		digitarray[x][digitHeight-1] = (BYTE)0;
	}

	for(y=0; y<digitHeight; y++)
	{
		digitarray[0][y] = (BYTE)0;
		digitarray[digitWidth-1][y] = (BYTE)0;
	}

	for(x=0; x<digitWidth; x++)
	{
		for(y=0; y<digitHeight; y++)
		{
			digitarray1[k] = digitarray[x][y];
			if(digitarray1[k] != 0)
				digitarray1[k] = (BYTE)1;
			k++;
		}
	}

	ThinnerPavlidis((void *)digitarray1, digitWidth, digitHeight);

	k=0;
	for(x=0; x<digitWidth; x++)
	{
		for(y=0; y<digitHeight; y++)
		{
			digitarray[x][y] = digitarray1[k];
			if(digitarray[x][y]!=0)
				digitarray[x][y] = (BYTE)1;
			k++;
		}
	}
}

void CDigitClass::ThinDigit_3()
{
	LONG x,y,k;
	k=0;

	digitWidth = digitdib.GetWidth();
	digitHeight = digitdib.GetHeight();

	for(x=0; x<digitWidth; x++)
	{
		digitarray[x][0] = (BYTE)0;
		digitarray[x][digitHeight-1] = (BYTE)0;
	}

	for(y=0; y<digitHeight; y++)
	{
		digitarray[0][y] = (BYTE)0;
		digitarray[digitWidth-1][y] = (BYTE)0;
	}

	for(x=0; x<digitWidth; x++)
	{
		for(y=0; y<digitHeight; y++)
		{
			digitarray1[k] = digitarray[x][y];
			if(digitarray1[k] != 0)
				digitarray1[k] = (BYTE)1;
			k++;
		}
	}

	ThinnerHilditch((void *)digitarray1, digitWidth, digitHeight);

	k=0;
	for(x=0; x<digitWidth; x++)
	{
		for(y=0; y<digitHeight; y++)
		{
			digitarray[x][y] = digitarray1[k];
			if(digitarray[x][y]!=0)
				digitarray[x][y] = (BYTE)1;
			k++;
		}
	}
}

void CDigitClass::ThinDigit_4()
{
	LONG x,y,k;
	k=0;

	digitWidth = digitdib.GetWidth();
	digitHeight = digitdib.GetHeight();
	
	for(x=0; x<digitWidth; x++)
	{
		digitarray[x][0] = (BYTE)0;
		digitarray[x][digitHeight-1] = (BYTE)0;
	}

	for(y=0; y<digitHeight; y++)
	{
		digitarray[0][y] = (BYTE)0;
		digitarray[digitWidth-1][y] = (BYTE)0;
	}

	for(x=0; x<digitWidth; x++)
	{
		for(y=0; y<digitHeight; y++)
		{
			digitarray1[k] = digitarray[x][y];
			if(digitarray1[k] != 0)
				digitarray1[k] = (BYTE)1;
			k++;
		}
	}

	ThiningDIBSkeleton((LPSTR)digitarray1, digitHeight, digitWidth);

	k=0;
	for(x=0; x<digitWidth; x++)
	{
		for(y=0; y<digitHeight; y++)
		{
			digitarray[x][y] = digitarray1[k];
			if(digitarray[x][y]!=0)
				digitarray[x][y] = (BYTE)1;
			k++;
		}
	}
}

void CDigitClass::GetFeature()
{
	int i,j;
	for(i=0; i<13; i++)
		feature[i] = 0;

	//图象是20×36大小的，分成9块

	//第一块
	for(i=0; i<7; i++)
	{
		for(j=0; j<12; j++)
		{
			if(digitarray[i][j]==1)
				feature[0]+=1.0;
		}
	}

	//第二块
	for(i=0; i<7; i++)
	{
		for(j=12; j<24; j++)
		{
			if(digitarray[i][j]==1)
				feature[1]+=1.0;
		}
	}

	//第三块
	for(i=0; i<7; i++)
	{
		for(j=24; j<36; j++)
		{
			if(digitarray[i][j]==1)
				feature[2]+=1.0;
		}
	}

	//第四块
	for(i=7; i<13; i++)
	{
		for(j=0; j<12; j++)
		{
			if(digitarray[i][j]==1)
				feature[3]+=1.0;
		}
	}

	//第五块
	for(i=7; i<13; i++)
	{
		for(j=12; j<24; j++)
		{
			if(digitarray[i][j]==1)
				feature[4]+=1.0;
		}
	}

	//第六块
	for(i=7; i<13; i++)
	{
		for(j=24; j<36; j++)
		{
			if(digitarray[i][j]==1)
				feature[5]+=1.0;
		}
	}

	//第七块
	for(i=13; i<20; i++)
	{
		for(j=0; j<12; j++)
		{
			if(digitarray[i][j]==1)
				feature[6]+=1.0;
		}
	}

	//第八块
	for(i=13; i<20; i++)
	{
		for(j=12; j<24; j++)
		{
			if(digitarray[i][j]==1)
				feature[7]+=1.0;
		}
	}

	//第九块
	for(i=13; i<20; i++)
	{
		for(j=24; j<36; j++)
		{
			if(digitarray[i][j]==1)
				feature[8]+=1.0;
		}
	}

	//下面统计方向交点特征

	for(j=0; j<36; j++)
	{
		if(digitarray[7][j]==1)
			feature[9]+=1.0;
	}

	for(j=0; j<36; j++)
	{
		if(digitarray[13][j]==1)
			feature[10]+=1.0;
	}

	for(i=0; i<20; i++)
	{
		if(digitarray[i][12]==1)
			feature[11]+=1.0;
	}

	for(i=0; i<20; i++)
	{
		if(digitarray[i][24]==1)
			feature[12]+=1.0;
	}
}