// GetFeature.cpp: implementation of the GetFeature class.
// 2005.1.13－16：02 By Superman 
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DSPLIT.h"
#include "GetFeature.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GetFeature::GetFeature()
{

}

GetFeature::~GetFeature()
{

}

/***************************************************************
*	函数名称：GetPosition()
*   函数类型：void 
*   函数功能：搜索手写数字的位置，赋值给bottom,down,right,left
****************************************************************/
void GetFeature::GetPosition()
{
	width=GetWidth();
	height=GetHeight();
	LineBytes=(width*8+31)/32*4;

	int i,j;
	BOOL flag;
	for(j=0;j<height;j++)
	{
		flag=FALSE;
		for(i=0;i<width;i++)
			if(m_pData[j*LineBytes+i]==0)
			{
				flag=TRUE;
				break;
			}
		if(flag)
			break;
	}
	bottom=j;
	for(j=height-1;j>0;j--)
	{
		flag=FALSE;
		for(i=0;i<width;i++)
			if(m_pData[j*LineBytes+i]==0)
			{
				flag=TRUE;
				break;
			}
		if(flag)
			break;
	}
	top=j;
	for(i=0;i<width;i++)
	{
		flag=FALSE;
		for(j=0;j<height;j++)
			if(m_pData[j*LineBytes+i]==0)
			{
				flag=TRUE;
				break;
			}
		if(flag)
			break;
	}
	left=i;
	for(i=width-1;i>0;i--)
	{
		flag=FALSE;
		for(j=0;j<height;j++)
			if(m_pData[j*LineBytes+i]==0)
			{
				flag=TRUE;
				break;
			}
		if(flag)
			break;
	}
	right=i;
}

/***************************************************************
*   函数名称：SetFeature()
*   函数类型：void 
*   函数功能：将手写数字特征保存在变量testsample中
****************************************************************/
void GetFeature::SetFeature()
{
	int i,j;
	for(j=0;j<5;j++)
	{
		for(i=0;i<5;i++)
		{
			testsample[5*(4-j)+i]=Cal(j,i);//(Cal(j,i)>0.10)?1:0;//
		}
	}	
}

/****************************************************************
*   函数名称：Cal(int row, int col)
*   函数类型：double 
*   参数说明：int row, int col:第row行，第col个区域
*   函数功能：计算某一小区域内黑像素所占比例,返回某一小区域内黑像素所占比例
****************************************************************/
double GetFeature::Cal(int row, int col)
{
	double w,h,count;
	w=(right-left)/5;
	h=(top-bottom)/5;
	count=0;

	for(int j=bottom+row*h;j<bottom+(row+1)*h;j++)
	for(int i=left+col*w;i<left+(col+1)*w;i++)
	{
		if(m_pData[j*LineBytes+i]==0)
			count++;
	}

	return (double)count/(w*h);
}

/***************************************************************
*   函数名称：Savealbe(int cls)
*   函数类型：BOOL 
*   参数说明：int cls:类别
*   函数功能：判断手写数字可否保存为cls类别的一个样品
*             同一类别的样品不能有重复的
****************************************************************/
BOOL GetFeature::Saveable(int cls)
{
	for(int i=0;i<pattern[cls].number;i++)
	{
		BOOL flag=TRUE;
		for(int j=0;j<25;j++)
			flag&=(pattern[cls].feature[i][j]==testsample[j])?TRUE:FALSE;
		if (flag) return FALSE;
	}
	return TRUE;
}

/***************************************************************
*   函数名称：Save(int cls)
*   函数类型：void 
*   参数说明：int cls:类别
*   函数功能：将手写数字保存为cls类别的一个样品，保存在样品的第一个
****************************************************************/
void GetFeature::Save(int cls)
{
	for(int i=pattern[cls].number;i>0;i--)
		for(int j=0;j<25;j++)
			pattern[cls].feature[i][j]=pattern[cls].feature[i-1][j];
	for(i=0;i<25;i++)
		pattern[cls].feature[0][i]=testsample[i];
	pattern[cls].number++;	
}



