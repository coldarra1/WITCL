// Cluster.cpp: implementation of the CCluster class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mode.h"
#include "Cluster.h"

#include "math.h"
#include "DlgInfor.h"
#include "DlgMohu.h"
#include "DlgFuzzyDistance.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const int MAX=1000;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCluster::CCluster()
{
	centernum=0;
	patternnum=0;
	m_pattern=NULL;
	m_center=NULL;

}

CCluster::~CCluster()
{

}
//***********************************************************//
//函数名称		GetFeature()
//参数			void
//返回值		void
//函数功能		将含有数据的图像标号、分割、编号及提取特征值，
//				特征值存入数组m_pattern中。
//************************************************************//	
void CCluster::GetFeature()
{
	////////////////////以下对数据区域标号whx/////////////////////
	
	BYTE * p_temp;
	int stop;
	int i,j;
	int counter;//记录相互独立的连通区域的个数；
	int present;//记录当前点的值1,2,...,counter.

	height=GetHeight();//图像高
	wide=GetWidth();//图像宽，

	stop=0;
	counter=0;
    p_temp=new BYTE[wide*height];//开辟一个临时内存区
	memset(p_temp,255,wide*height);//置白
	
	//从左到右、从上到下标号
	const int T=5;//T为阈值，RGB值小于该阈值被认为是黑，
	for(i=0; i<wide; i++)//将第零行置白
		*(m_pData+(height-1)*wide+i)=255;
	for(j=0;j<height;j++)//将第零列置白
		*(m_pData+(height-j-1)*wide)=255;
	for( j=1;j<height-1;j++)	// 从第一行开始搜索
	{
		if(stop==1)//判断连通区是否太多
			break;
		for( i=1;i<wide-1;i++)	// 从第一列开始搜索
		{
			if(counter>255)
			{
				AfxMessageBox("连通区数目太多，请减少样品个数");
				stop=1;
				return;
			}
			if(*(m_pData+(height-j-1)*wide+i)<T)//若当前点为黑点
			{
				if(*(m_pData+(height-j-1+1)*wide+i+1)<T)//若当前点的右上点为黑点
				{
					*(p_temp+(height-j-1)*wide+i)=*(p_temp+(height-j-1+1)*wide+i+1);//当前点标号应该与右上点相同
					present=*(p_temp+(height-j-1+1)*wide+i+1);//记录当前点的标号
					
					if(*(m_pData+(height-j-1)*wide+i-1)<T && *(p_temp+(height-j-1)*wide+i-1)!=present)//左前与右上点都为黑且标号不同
					{
						int temp=*(p_temp+(height-j-1)*wide+i-1);//记录左前点的标号
						if (present>temp)//当前点标号记录两者中的较小值
						{
							present=temp;
							temp=*(p_temp+(height-j-1+1)*wide+i+1);
						}
						counter--;//合并左前和右上标号，标号总数减一
						for(int m=1;m<=height-1;m++)
							for(int n=1;n<=wide-1;n++)
							{
								if(*(p_temp+(height-m-1)*wide+n)==temp)//将较大标号该成较小标号
								{	
									*(p_temp+(height-m-1)*wide+n)=present;
								}
								else if (*(p_temp+(height-m-1)*wide+n)>temp)//将较大标号以后的所有标号减一，以保持标号的连续性
								{
									*(p_temp+(height-m-1)*wide+n)-=1;
								}
							}
					}//end//左前
					if( *(m_pData+(height-j-1+1)*wide+i-1)<T && *(p_temp+(height-j-1+1)*wide+i-1)!=present)//左上与右上点都为黑且标号不同
					{
						counter--;//合并左上和右上标号，标号总数减一
						int temp=*(p_temp+(height-j-1+1)*wide+i-1);//记录左上点的值
						if (present<temp)//当前点标号记录两者中的较小值
						{
							temp=present;
							present=*(p_temp+(height-j-1+1)*wide+i-1);
						}

						for(int m=1;m<=height-1;m++)
							for(int n=1;n<=wide-1;n++)
							{
								if(*(p_temp+(height-m-1)*wide+n)==present)//将较大标号该成较小标号
								{	
									*(p_temp+(height-m-1)*wide+n)=temp;
								}
								else if (*(p_temp+(height-m-1)*wide+n)>present)//将较大标号以后的所有标号减一，以保持标号的连续性
								{
									*(p_temp+(height-m-1)*wide+n)-=1;
								}
							}
						present=temp;
					}//end//左上
				}
				else if(*(m_pData+(height-j-1+1)*wide+i)<T)//当前点黑，右上不为黑，正上为黑
				{
					*(p_temp+(height-j-1)*wide+i)=*(p_temp+(height-j-1+1)*wide+i);//当前标号＝正上标号
					present=*(p_temp+(height-j-1+1)*wide+i);
				}
				else if(*(m_pData+(height-j-1+1)*wide+i-1)<T)//左上
				{
					*(p_temp+(height-j-1)*wide+i)=*(p_temp+(height-j-1+1)*wide+i-1);
					present=*(p_temp+(height-j-1+1)*wide+i-1);
				}
				else if(*(m_pData+(height-j-1)*wide+i-1)<T)//左前
				{
					*(p_temp+(height-j-1)*wide+i)=*(p_temp+(height-j-1)*wide+i-1);
					present=*(p_temp+(height-j-1)*wide+i-1);
				}
				else//产生新标号
				{				
					++counter;
					present=counter;
					*(p_temp+(height-j-1)*wide+i)=present;
				}
			}//end if
		}// 列
	}//end 行
 // //////////////////////以上对数据区域标号//////////////////////////
				  
					
 //////////////////////以下获得各个样品所在位置及编号///////////////////
	patternnum=counter;//样品总数

	if (m_pattern!=NULL)
		delete []m_pattern;
	m_pattern=new Pattern[patternnum];				
						  
	for( i=0;i<patternnum;i++) 
	{
		m_pattern[i].index=i+1;
		m_pattern[i].category=0;
		m_pattern[i].lefttop.x=wide;
		m_pattern[i].lefttop.y=height;
		m_pattern[i].rightbottom.x=0;
		m_pattern[i].rightbottom.y=0;
	}

	for(int t=1;t<=patternnum;t++)//记录每个样品（独立连通区域）的左上、右下点坐标
	{	
		for(int j=1;j<height-1;j++)//搜索整幅图像
			for(int i=1;i<wide-1;i++)
			{
				if(*(p_temp+(height-j-1)*wide+i)==t)
				{
					if (m_pattern[t-1].lefttop.x>i)//get the lefttop point
						m_pattern[t-1].lefttop.x=i;
					if (m_pattern[t-1].lefttop.y>j)
						m_pattern[t-1].lefttop.y=j;
					if (m_pattern[t-1].rightbottom.x<i)//get the rightbottom point
						m_pattern[t-1].rightbottom.x=i;
					if (m_pattern[t-1].rightbottom.y<j)
						m_pattern[t-1].rightbottom.y=j;
				}				
			}
	}
	
	delete []p_temp;
	//////////////////////以下获得所有样品特征放入m_pattern中//////////////////////////////
	for ( i=0;i<patternnum;i++)//=patternnum
	{
		CalFeature(&m_pattern[i]);//调用函数计算第i号模板的值
	}
	
	//////////////////////以上获得所有样品特征放入m_pattern中//////////////////////////////

}
/***********************************************************
*函数名称		CalFeature(CCluster::Pattern *m_pattern)
*参数			CCluster::Pattern *m_pattern
*返回值	    	void
*函数功能		计算样品m_pattern的特征值，存入m_pattern－>feature中
*************************************************************/
void CCluster::CalFeature(CCluster::Pattern *m_pattern)
{
	int w,h,count;
	int i,j;

	w=(int)(m_pattern->rightbottom.x-m_pattern->lefttop.x)/N;//特征值中每个特征的宽
	h=(int)(m_pattern->rightbottom.y-m_pattern->lefttop.y)/N;//特征值中每个特征的高

	for ( j=0;j<N;j++)//col
	{
		for ( i=0;i<N;i++)//line
		{
			count=0;//每个特征内黑点的个数
            for(int m= height-m_pattern->rightbottom.y+h*j;m<height-m_pattern->rightbottom.y+h*j+h;m++)//col
				for (int n=m_pattern->lefttop.x+i*w; n<m_pattern->lefttop.x+i*w+w; n++)//line
					if (*(m_pData+m*wide+n)==0)
						count++;
			m_pattern->feature[j*N+i]=(double)count/(double)(w*h);
		}
	}
}

/*********************************************************
*函数名称		CalCenter(CCluster::Center *pcenter)
*参数			CCluster::Center *pcenter
*返回值		    void
*函数功能		计算中心pcenter的特征值（本类所有样品的均值），及样品个数
************************************************************/	
void CCluster::CalCenter(CCluster::Center *pcenter)
{
	double temp[N*N];//临时存储中心的特征值
	int a=0;//记录该类中元素个数
	for (int i=0;i<N*N;i++)//中心清空
		temp[i]=0;
	for (i=0;i<patternnum;i++)
		if (m_pattern[i].category==pcenter->index)//累加中心所有样品
		{
			a++;
			for (int j=0;j<N*N;j++)
				temp[j]+=m_pattern[i].feature[j];
		}
	pcenter->patternnum=a;
	for ( i=0;i<N*N;i++)
			if(a!=0)
			{
				pcenter->feature[i]=(double)(temp[i]/(double)a);//取均值
			}
			else
			{
				pcenter->feature[i]=temp[i];
			}

}

/***********************************************************
*函数名称		GetDistance( CCluster::Pattern pattern1, CCluster::Pattern  pattern2, const int distype)
*参数			CCluster::Pattern pattern1   样品1
*				CCluster::Pattern pattern2	 样品2
*				const int distype	         距离模式  1：欧氏距离；2：夹角余弦距离；
*													   3：特征是二值时的夹角余弦距离；4：具有二值特征的Tanimoto测度
*返回值	    	double
*函数功能		计算样品1和样品2间的距离，距离模式由参数distype给定
*************************************************************/
double CCluster::GetDistance( CCluster::Pattern pattern1, CCluster::Pattern  pattern2, const int distype)
{

	double   result;
	result=0;

	if (distype==1)//欧氏距离
	{
		for (int i=0; i<N*N; i++)
			result+=(pattern1.feature[i]-pattern2.feature[i])*(pattern1.feature[i]-pattern2.feature[i]);
		return (double)sqrt(result);
	}
	else if (distype==2)//夹角余弦
	{
		double	a,b1,b2;
		a=0;
		b1=0;
		b2=0;
		for (int i=0; i<N*N; i++)
		{
			a+=pattern1.feature[i]*pattern2.feature[i];
			b1+=pattern1.feature[i]*pattern1.feature[i];
			b2+=pattern2.feature[i]*pattern2.feature[i];
		}
		if (b2*b1!=0)
		result=a/sqrt(b1*b2);
		else 
		{
			return -1;
		}

		return (1-result);
	}
	else if (distype==3)//二值夹角余弦
	{
		int *t1,*t2;
		int a,b1,b2;
		 
		a=0;b1=0;b2=0;
		t1=new int [N*N];
		t2=new int [N*N];
		for(int i=0; i<N*N; i++)
		{
			t1[i]=pattern1.feature[i]>0.2? 1:0;
			t2[i]=pattern2.feature[i]>0.2? 1:0;
		}
		
		for ( i=0; i<N*N; i++)
		{
			a+=t1[i]*t2[i];
			b1+=t1[i]*t1[i];
			b2+=t2[i]*t2[i];
		}
		delete	[]t1;
		delete	[]t2;
		if (b2*b1!=0)
		result=(double)(a/sqrt(b1*b2));
		else 
		{
			return -1;
		}

		return (1-result);
	}
	else if (distype==4)//Tanimoto
	{
		int *t1,*t2;
		int a,b1,b2;
		 
		a=0;b1=0;b2=0;
		t1=new int [N*N];
		t2=new int [N*N];
		for(int i=0; i<N*N; i++)
		{
			t1[i]=pattern1.feature[i]>0.2? 1:0;
			t2[i]=pattern2.feature[i]>0.2? 1:0;
		}
		
		for ( i=0; i<N*N; i++)
		{
			a+=t1[i]*t2[i];
			b1+=t1[i]*t1[i];
			b2+=t2[i]*t2[i];
		}
		delete	[]t1;
		delete	[]t2;
		if ((b2*b1-a)!=0)
		result=(double)(a/(b1+b2-a));
		else 
		{
			return -1;
		}
		return (1-result);
	}
	else
		return -1;

}
/***************************************************************
*函数名称		GetDistance(CCluster::Pattern pattern,  CCluster::Center center, const int distype)
*参数			CCluster::Pattern pattern  样品
*				CCluster::Center center    中心
*				const int distype	         距离模式  1：欧氏距离；2：夹角余弦距离；
*													   3：特征是二值时的夹角余弦距离；
*													   4：具有二值特征的Tanimoto测度
*返回值			double
*函数功能		计算样品和聚类中心间的距离，距离模式由distype给定
************************************************************/
double CCluster::GetDistance(CCluster::Pattern pattern,  CCluster::Center center, const int distype)
{
	double   result;
	result=0;

	if (distype==1)//欧氏距离
	{
		for (int i=0; i<N*N; i++)
			result+=(pattern.feature[i]-center.feature[i])*(pattern.feature[i]-center.feature[i]);
		return (double)sqrt(result);
	}
	else if (distype==2)//夹角余弦
	{
		double	a,b1,b2;
		a=0;
		b1=0;
		b2=0;
		for (int i=0; i<N*N; i++)
		{
			a+=pattern.feature[i]*center.feature[i];
			b1+=pattern.feature[i]*pattern.feature[i];
			b2+=center.feature[i]*center.feature[i];
		}
		if (b2*b1!=0)
		result=a/sqrt(b1*b2);
		else 
		{
			return -1;
		}

		return (1-result);
	}
	else if (distype==3)//二值夹角余弦
	{
		int *t1,*t2;
		int a,b1,b2;
		 
		a=0;b1=0;b2=0;
		t1=new int [N*N];
		t2=new int [N*N];
		for(int i=0; i<N*N; i++)
		{
			t1[i]=pattern.feature[i]>0.2? 1:0;
			t2[i]=center.feature[i]>0.2? 1:0;
		}
		
		for ( i=0; i<N*N; i++)
		{
			a+=t1[i]*t2[i];
			b1+=t1[i]*t1[i];
			b2+=t2[i]*t2[i];
		}
		delete	[]t1;
		delete	[]t2;
		if (b2*b1!=0)
		result=a/sqrt(b1*b2);
		else 
		{
			return -1;
		}

		return (1-result);
	}
	else if (distype==4)//Tanimoto
	{
		int *t1,*t2;
		int a,b1,b2;
		 
		a=0;b1=0;b2=0;
		t1=new int [N*N];
		t2=new int [N*N];
		for(int i=0; i<N*N; i++)
		{
			t1[i]=pattern.feature[i]>0.2? 1:0;
			t2[i]=center.feature[i]>0.2? 1:0;
		}
		
		for ( i=0; i<N*N; i++)
		{
			a+=t1[i]*t2[i];
			b1+=t1[i]*t1[i];
			b2+=t2[i]*t2[i];
		}
		delete	[]t1;
		delete	[]t2;
		if ((b2*b1-a)!=0)
		result=(double)(a/(b1+b2-a));
		else 
		{
			return -1;
		}
		return (1-result);
	}
	else
		return -1;
}
/*************************************************************
*函数名称		GetDistance(CCluster::Center mCenter1,CCluster::Center mCenter2,int distype)
*参数			CCluster::Center mCenter1   中心1
*				CCluster::Center mCenter2   中心2
*				const int distype	         距离模式   1：欧氏距离；2：夹角余弦距离；		
*											            3：特征是二值时的夹角余弦距离；
*														4：具有二值特征的Tanimoto测度
*返回值			double
*函数功能		计算两个聚类中心间的距离，距离模式由distype给定
*************************************************************/
double CCluster::GetDistance(CCluster::Center mCenter1,CCluster::Center mCenter2,int distype)
{
	double result;
	result=0;

	if (distype==1)//欧氏距离
	{
		for ( int m=0;m<N*N;m++)
		result+=(mCenter1.feature[m]-mCenter2.feature[m])*(mCenter1.feature[m]-mCenter2.feature[m]);
		return (double)sqrt(result);
	}
	else if (distype==2)//夹角余弦
	{
		double	a,b1,b2;
		a=0;
		b1=0;
		b2=0;
		for (int i=0; i<N*N; i++)
		{
			a+=mCenter1.feature[i]*mCenter2.feature[i];
			b1+=mCenter1.feature[i]*mCenter1.feature[i];
			b2+=mCenter2.feature[i]*mCenter2.feature[i];
		}
		if (b2*b1!=0)
		result=a/sqrt(b1*b2);
		else 
		{
			return -1;
		}

		return (1-result);
	}
	else if (distype==3)//二值夹角余弦
	{
		int *t1,*t2;
		int a,b1,b2;
		 
		a=0;b1=0;b2=0;
		t1=new int [N*N];
		t2=new int [N*N];
		for(int i=0; i<N*N; i++)
		{
			t1[i]=mCenter1.feature[i]>0.2? 1:0;
			t2[i]=mCenter2.feature[i]>0.2? 1:0;
		}
		
		for ( i=0; i<N*N; i++)
		{
			a+=t1[i]*t2[i];
			b1+=t1[i]*t1[i];
			b2+=t2[i]*t2[i];
		}
		delete	[]t1;
		delete	[]t2;
		if (b2*b1!=0)
		result=(double)(a/sqrt(b1*b2));
		else 
		{
			return -1;
		}

		return (1-result);
	}
	else if (distype==4)//Tanimoto
	{
		int *t1,*t2;
		int a,b1,b2;
		 
		a=0;b1=0;b2=0;
		t1=new int [N*N];
		t2=new int [N*N];
		for(int i=0; i<N*N; i++)
		{
			t1[i]=mCenter1.feature[i]>0.2? 1:0;
			t2[i]=mCenter2.feature[i]>0.2? 1:0;
		}
		
		for ( i=0; i<N*N; i++)
		{
			a+=t1[i]*t2[i];
			b1+=t1[i]*t1[i];
			b2+=t2[i]*t2[i];
		}
		delete	[]t1;
		delete	[]t2;
		if ((b2*b1-a)!=0)
		result=(double)(a/(b1+b2-a));
		else 
		{
			return -1;
		}
		return (1-result);
	}
	else
		return -1;	
}

/************************************************************
*函数名称		GetDistance(double *dis, int i, int j)
*参数			double *dis    指向模糊距离数组的指针大小为[patternnum*patternnum]
*				int i			数组的第i行
*				int j			数组的第j列
*返回值		    double
*函数功能		返回模糊距离数组中第i行第j列的模糊积
*************************************************************/
double CCluster::GetDistance(double *dis, int i, int j)
{
	double result;
	result=0;

	for(int t=0;t<patternnum;t++)
	{
		double td=dis[i*patternnum+t]<dis[t*patternnum+j]? dis[i*patternnum+t]:dis[t*patternnum+j];
		if (result<td)
			result=td;
	}
	return result;
}
/************************************************************
*函数名称		GetFuzzyDistance(CCluster::Pattern pattern1,CCluster::Pattern pattenr2, int distype)
*参数			CCluster::Pattern pattern1    样品1
*				CCluster::Pattern pattern2    样品2
*				int distype					  距离计算形式：1，欧氏距离；2，数量积；
*															3，相关系数
*															4，最大最小法；5，算数平均法; 
*															6,几何平均最小法
*返回值         double
*功能			计算两个样品的模糊距离，距离模式由参数distype给出
************************************************************/
double CCluster::GetFuzzyDistance(CCluster::Pattern pattern1,CCluster::Pattern pattern2, int distype)
{
	switch	(distype)
	{
	case 1://欧氏距离
		{
				double max=0;
				for (int i=0; i<patternnum-1; i++)
					for (int j=i+1; j<patternnum; j++)
						if (max<GetDistance(m_pattern[i],m_pattern[j],1))
							max=GetDistance(m_pattern[i],m_pattern[j],1);
				return (max-GetDistance(pattern1,pattern2,1))/max;
		}
	case 2://数量积
		{
			double temp,max;
			max=0;
			for (int i=0; i<patternnum-1; i++)
				for (int j=0; j<patternnum; j++)
				{
					temp=0;
					for (int k=0; k<N*N; k++)
					{
						temp+=m_pattern[i].feature[k]*m_pattern[j].feature[k];
					}
					if (max<temp)
						max=temp;
				}
			temp=0;
			for ( i=0; i<N*N; i++)
			{
				temp+=pattern1.feature[i]*pattern2.feature[i];
			}
			return (temp/max);
		}
	case 3://相关系数
		{
			double ap1,ap2;
			ap1=0;ap2=0;
			for (int i=0; i<N*N; i++)
			{
				ap1+=pattern1.feature[i];
				ap2+=pattern2.feature[i];
			}
			ap1/=N; 
			ap1/=N;

			double a,b1,b2;
			a=0;b1=0;b2=0;

			for (i=0; i<N*N; i++)
			{
				a+=(pattern1.feature[i]-ap1)*(pattern2.feature[i]-ap2);
				b1+=(pattern1.feature[i]-ap1)*(pattern1.feature[i]-ap1);
				b2+=(pattern2.feature[i]-ap2)*(pattern2.feature[i]-ap2);
			}
			if (b2*b1!=0)
				return (a/sqrt(b1*b2));
		}
	case 4://最大最小法
		{
			double min ,max;
			min=0; max=0;
			for (int i=0; i<N*N; i++)
			{
				min+=pattern1.feature[i]<pattern2.feature[i]? pattern1.feature[i]:pattern2.feature[i];
				max+=pattern1.feature[i]<pattern2.feature[i]? pattern2.feature[i]:pattern1.feature[i];
			}
			if (max!=0)
			return (min/max);
		}
	case 5://算数平均法
		{
			double min ,max;
			min=0; max=0;
			for (int i=0; i<N*N; i++)
			{
				min+=pattern1.feature[i]<pattern2.feature[i]? pattern1.feature[i]:pattern2.feature[i];
				max+=pattern1.feature[i]+pattern2.feature[i];
			}
			if (max!=0)
			return (2*min/max);	
		}
	case 6://几何平均最小法
		{
			double min ,max;
			min=0; max=0;
			for (int i=0; i<N*N; i++)
			{
				min+=pattern1.feature[i]<pattern2.feature[i]? pattern1.feature[i]:pattern2.feature[i];
				max+=sqrt(pattern1.feature[i]*pattern2.feature[i]);
			}
			if (max!=0)
			return (min/max);			
		}
	default:
		return -1;
	}
}

/************************************************************
*函数名称		Zuilinjinguize()
*参数			void
*返回值		    void
*函数功能		按照最临近规则对全体样品进行分类
************************************************************/
void CCluster::Zuilinjinguize()//最临近规则
{
	GetFeature();

	double  T;//阈值
	int		distype;//距离模式（欧氏、余弦。。。）
	int     i,j;

///////////////输出阈值参考值/////////////////////
	double minous,maxous,mincos,maxcos,minbcos,maxbcos,mintan,maxtan;

	minous=MAX; mincos=MAX; minbcos=MAX; mintan=MAX;
	maxous=0; maxcos=0; maxbcos=0; maxtan=0;

	for (  i=0;i<patternnum-1;i++)//计算四种距离模式的参考值
		for ( j=i+1;j<patternnum;j++)
		{
			if (minous>GetDistance(m_pattern[i],m_pattern[j],1))
				minous=GetDistance(m_pattern[i],m_pattern[j],1);
			if (maxous<GetDistance(m_pattern[i],m_pattern[j],1))
				maxous=GetDistance(m_pattern[i],m_pattern[j],1);

			if (mincos>GetDistance(m_pattern[i],m_pattern[j],2))
				mincos=GetDistance(m_pattern[i],m_pattern[j],2);
			if (maxcos<GetDistance(m_pattern[i],m_pattern[j],2))
				maxcos=GetDistance(m_pattern[i],m_pattern[j],2);

			if (minbcos>GetDistance(m_pattern[i],m_pattern[j],3))
				minbcos=GetDistance(m_pattern[i],m_pattern[j],3);
			if (maxbcos<GetDistance(m_pattern[i],m_pattern[j],3))
				maxbcos=GetDistance(m_pattern[i],m_pattern[j],3);
			
			if (mintan>GetDistance(m_pattern[i],m_pattern[j],4))
				mintan=GetDistance(m_pattern[i],m_pattern[j],4);
			if (maxtan<GetDistance(m_pattern[i],m_pattern[j],4))
				maxtan=GetDistance(m_pattern[i],m_pattern[j],4);
		}
	DlgInfor mDlgInfor;
	mDlgInfor.ShowInfor(minous,maxous,mincos,maxcos,minbcos,maxbcos,mintan,maxtan);

////////////////////////读入阈值和距离形式///////////////
	if (mDlgInfor.DoModal()==IDOK)
	{
		T=mDlgInfor.m_T;
		distype=mDlgInfor.m_DisType;
	}
	else return;
	centernum=1;
	m_center=new Center[patternnum];

    //将第一个样品作为第一个中心
	for ( i=0;i<N*N;i++)
		m_center[0].feature[i]=m_pattern[0].feature[i];
	m_center[0].index=1;
	m_center[0].patternnum=1;
	m_pattern[0].category=1;

	for ( i=1;i<patternnum;i++)//对所有模版进行归类
	{
		double centerdistance=MAX;
		int index=1;
		//找到距离最近的中心index，记录最小距离centerdistance
		for (int j=0;j<centernum;j++)
		{	
			double dis= GetDistance(m_pattern[i],m_center[j],distype);
			if (dis<centerdistance)
			{
				centerdistance=dis;
				index=j;
			}
		}

		if (centerdistance<T)//距离小于阈值则将样品归入该类
		{
			m_pattern[i].category=m_center[index].index;
			CalCenter(&m_center[j]);
		}
		else //新建聚类中心
		{
			centernum++;
			m_pattern[i].category=centernum;
			for (int m=0;m<N*N;m++)
				m_center[centernum-1].feature[m]=m_pattern[i].feature[m];
			m_center[centernum-1].index=centernum;
		}
	}//end of all pattern
	delete []m_center;
}


/************************************************************
*函数名称		Zuidazuixiaojulifa()
*参数			void
*返回值		void
*函数功能		按照最大最小距离规则对全体样品进行分类
************************************************************/
void CCluster::Zuidazuixiaojulifa()
{
	GetFeature();

	int	distype;//距离的形式（欧氏、余弦。。。）
	int i,j;

	DlgInfor mDlgInfor;
	mDlgInfor.ShowInfor(1);
	if (mDlgInfor.DoModal()==IDOK)
	{
		distype=mDlgInfor.m_DisType;
	}
	else return;
	
	double maxdistance=0;//记录两类间的最大距离，用做类分割阈值

	int index=1;//记录距离第一个中心最远的样品

	m_center=new Center[patternnum];

	for ( i=0;i<N*N;i++)//第一个聚类中心
		m_center[0].feature[i]=m_pattern[0].feature[i];
	m_center[0].index=1;
	m_pattern[0].category=1;

	for( i=1;i<patternnum;i++)//第二个聚类中心
		if (maxdistance<GetDistance(m_pattern[i],m_center[0],distype))
		{
			maxdistance=GetDistance(m_pattern[i],m_center[0],distype);
			index=i;
		}
	for ( i=0;i<N*N;i++)//第二个聚类中心
		m_center[1].feature[i]=m_pattern[index].feature[i];
	
	m_center[1].index=2;
	m_pattern[index].category=2;

	centernum=2;

	for ( i=1;i<patternnum;i++)//对所有模板分类
	{
		
		double tdistance=MAX;
		index=0;//记录样品距离最近的中心
		for ( j=0;j<centernum;j++)//2
			if (tdistance>GetDistance(m_pattern[i],m_center[j],distype))
			{
				tdistance=GetDistance(m_pattern[i],m_center[j],distype);
				index=j;
			}

		if (tdistance>maxdistance/2)//样品到最近中的距离大于阈值，建立新的聚类中心
		{
				++centernum;
				for (int m=0;m<N*N;m++)
					m_center[centernum-1].feature[m]=m_pattern[i].feature[m];
				m_center[centernum-1].index=centernum;
				m_pattern[i].category=centernum;
		}
		else//归入index类中
		{
			m_pattern[i].category=m_center[index].index;
			CalCenter(&m_center[index]);
		}
			
	}
	delete []m_center;

}
/************************************************************
*函数名称		Zuiduanjulifa()
*参数			void
*返回值 		void
*函数功能		按照最短距离法对全体样品进行分类
************************************************************/
void CCluster::Zuiduanjulifa()//最短距离法
{
	GetFeature();

	double  T;//阈值
	int		distype;//距离的形式（欧氏、余弦。。。）
	int     i,j;

	double minous,maxous,mincos,maxcos,minbcos,maxbcos,mintan,maxtan;

	minous=MAX; mincos=MAX; minbcos=MAX; mintan=MAX;
	maxous=0; maxcos=0; maxbcos=0; maxtan=0;
	//计算四种距离模式的参考值
	for (  i=0;i<patternnum-1;i++)
		for ( j=i+1;j<patternnum;j++)
		{
			if (minous>GetDistance(m_pattern[i],m_pattern[j],1))
				minous=GetDistance(m_pattern[i],m_pattern[j],1);
			if (maxous<GetDistance(m_pattern[i],m_pattern[j],1))
				maxous=GetDistance(m_pattern[i],m_pattern[j],1);

			if (mincos>GetDistance(m_pattern[i],m_pattern[j],2))
				mincos=GetDistance(m_pattern[i],m_pattern[j],2);
			if (maxcos<GetDistance(m_pattern[i],m_pattern[j],2))
				maxcos=GetDistance(m_pattern[i],m_pattern[j],2);

			if (minbcos>GetDistance(m_pattern[i],m_pattern[j],3))
				minbcos=GetDistance(m_pattern[i],m_pattern[j],3);
			if (maxbcos<GetDistance(m_pattern[i],m_pattern[j],3))
				maxbcos=GetDistance(m_pattern[i],m_pattern[j],3);
			
			if (mintan>GetDistance(m_pattern[i],m_pattern[j],4))
				mintan=GetDistance(m_pattern[i],m_pattern[j],4);
			if (maxtan<GetDistance(m_pattern[i],m_pattern[j],4))
				maxtan=GetDistance(m_pattern[i],m_pattern[j],4);
		}
	DlgInfor mDlgInfor;
	mDlgInfor.ShowInfor(minous,maxous,mincos,maxcos,minbcos,maxbcos,mintan,maxtan);

	if (mDlgInfor.DoModal()==IDOK)
	{
		T=mDlgInfor.m_T;
		distype=mDlgInfor.m_DisType;
	}
	else return;

    //初始化，所有样品各分一类 
	centernum=patternnum;
	m_center=new Center[centernum];
	for ( i=0;i<patternnum;i++)
	{
		m_pattern[i].category=i+1;

		for (j=0;j<N*N;j++)
			m_center[i].feature[j]=m_pattern[i].feature[j];
		m_center[i].index=i+1;
	}

	while (1)
	{
		int pi,pj;
		double mindis;

		pi=0;
		pj=0;
		mindis=MAX;
		//寻找距离最近的两类pi、pj，记录最小距离mindis
		for ( i=0;i<patternnum-1;i++)
			for ( j=i+1;j<patternnum;j++)
				if (m_pattern[i].category!=m_pattern[j].category)
					if (GetDistance(m_pattern[i],m_pattern[j],distype)<mindis)
					{
						mindis=GetDistance(m_pattern[i],m_pattern[j],distype);
						pi=i;
						pj=j;
					};
		if (mindis<=T)//距离小于阈值，合并pi、pj类
		{
			if (pi>pj)//将较大类号归入较小类号
			{
				int temp=pi;
				pi=pj;
				pj=temp;
			}
			int tcenter=m_pattern[pj].category;
			for ( i=0;i<patternnum;i++)
			{
				if (m_pattern[i].category==tcenter)
					m_pattern[i].category=m_pattern[pi].category;
				if (m_pattern[i].category>tcenter)//保持序号的连续性
					m_pattern[i].category--;
			}
		}
		else break;//最小距离大于阈值，退出循环
	}
	delete []m_center;

}
/************************************************************
*函数名称		Zuichangjulifa()
*参数			void
*返回值		    void
*函数功能		按照最长距离法对全体样品进行分类
************************************************************/
void CCluster::Zuichangjulifa()//最长距离法
{
	GetFeature();

	double  T;//阈值
	int		distype;//距离的形式（欧氏、余弦。。。）
	int     i,j;

	double minous,maxous,mincos,maxcos,minbcos,maxbcos,mintan,maxtan;

	minous=MAX; mincos=MAX; minbcos=MAX; mintan=MAX;
	maxous=0; maxcos=0; maxbcos=0; maxtan=0;
	//计算四种距离模式的参考值
	for (  i=0;i<patternnum-1;i++)
		for ( j=i+1;j<patternnum;j++)
		{
			if (minous>GetDistance(m_pattern[i],m_pattern[j],1))
				minous=GetDistance(m_pattern[i],m_pattern[j],1);
			if (maxous<GetDistance(m_pattern[i],m_pattern[j],1))
				maxous=GetDistance(m_pattern[i],m_pattern[j],1);

			if (mincos>GetDistance(m_pattern[i],m_pattern[j],2))
				mincos=GetDistance(m_pattern[i],m_pattern[j],2);
			if (maxcos<GetDistance(m_pattern[i],m_pattern[j],2))
				maxcos=GetDistance(m_pattern[i],m_pattern[j],2);

			if (minbcos>GetDistance(m_pattern[i],m_pattern[j],3))
				minbcos=GetDistance(m_pattern[i],m_pattern[j],3);
			if (maxbcos<GetDistance(m_pattern[i],m_pattern[j],3))
				maxbcos=GetDistance(m_pattern[i],m_pattern[j],3);
			
			if (mintan>GetDistance(m_pattern[i],m_pattern[j],4))
				mintan=GetDistance(m_pattern[i],m_pattern[j],4);
			if (maxtan<GetDistance(m_pattern[i],m_pattern[j],4))
				maxtan=GetDistance(m_pattern[i],m_pattern[j],4);
		}
	DlgInfor mDlgInfor;
	mDlgInfor.ShowInfor(minous,maxous,mincos,maxcos,minbcos,maxbcos,mintan,maxtan);

	if (mDlgInfor.DoModal()==IDOK)
	{
		T=mDlgInfor.m_T;
		distype=mDlgInfor.m_DisType;
	}
	else return;

    //初始化，所有样品各归一类
	for ( i=0;i<patternnum;i++)
	{
		m_pattern[i].category=i+1;
	}
 
	centernum=patternnum;

	while (1)
	{
		int pi,pj;
		double mindis,maxdis;

		pi=0;
		pj=0;
		mindis=MAX;
        //求两类间的最大距离，找出所有类间距离中最小的为mindis，记录类号pi，pj
		for ( i=1;i<=centernum-1;i++)
			for ( j=i+1;j<=centernum;j++)
			{
   				maxdis=-1;
				for (int m=0;m<patternnum-1;m++)
					for (int n=m+1;n<patternnum;n++)
					{
						if ((m_pattern[m].category==i)&&(m_pattern[n].category==j)||((m_pattern[m].category==j)&&(m_pattern[n].category==i)))
							if (GetDistance(m_pattern[m],m_pattern[n],distype)>maxdis)
							{
								maxdis=GetDistance(m_pattern[m],m_pattern[n],distype);
							}
					}
				if ((maxdis<mindis)&&(maxdis!=-1))
				{
					mindis=maxdis;
					pi=i;
					pj=j;
				}
			}
		if (mindis<T)//距离小于阈值，合并pi、pj类
		{
			int tcenter=pj;
			for ( i=0;i<patternnum;i++)
			{
				if (m_pattern[i].category==tcenter)
					m_pattern[i].category=pi;
				if (m_pattern[i].category>tcenter)//对样品排序，保持类号的连续性
					m_pattern[i].category--;
			}
			centernum--;
		}
		else break;//退出循环
	}

}
/************************************************************
*函数名称		Zhongjianjulifa()
*参数			void
*返回值		    void
*函数功能		按照中间距离法对全体样品进行分类
*************************************************************/
void CCluster::Zhongjianjulifa()
{
	GetFeature();
	
	double	**centerdistance;//记录类间距离
	double  T;//阈值
	int		distype;//距离的形式（欧氏、余弦。。。）
	int     i,j;

	double minous,maxous,mincos,maxcos,minbcos,maxbcos,mintan,maxtan;

	minous=MAX; mincos=MAX; minbcos=MAX; mintan=MAX;
	maxous=0; maxcos=0; maxbcos=0; maxtan=0;
	//计算四种距离模式的参考值
	for (  i=0;i<patternnum-1;i++)
		for ( j=i+1;j<patternnum;j++)
		{
			if (minous>GetDistance(m_pattern[i],m_pattern[j],1))
				minous=GetDistance(m_pattern[i],m_pattern[j],1);
			if (maxous<GetDistance(m_pattern[i],m_pattern[j],1))
				maxous=GetDistance(m_pattern[i],m_pattern[j],1);

			if (mincos>GetDistance(m_pattern[i],m_pattern[j],2))
				mincos=GetDistance(m_pattern[i],m_pattern[j],2);
			if (maxcos<GetDistance(m_pattern[i],m_pattern[j],2))
				maxcos=GetDistance(m_pattern[i],m_pattern[j],2);

			if (minbcos>GetDistance(m_pattern[i],m_pattern[j],3))
				minbcos=GetDistance(m_pattern[i],m_pattern[j],3);
			if (maxbcos<GetDistance(m_pattern[i],m_pattern[j],3))
				maxbcos=GetDistance(m_pattern[i],m_pattern[j],3);
			
			if (mintan>GetDistance(m_pattern[i],m_pattern[j],4))
				mintan=GetDistance(m_pattern[i],m_pattern[j],4);
			if (maxtan<GetDistance(m_pattern[i],m_pattern[j],4))
				maxtan=GetDistance(m_pattern[i],m_pattern[j],4);
		}
	DlgInfor mDlgInfor;
	mDlgInfor.ShowInfor(minous,maxous,mincos,maxcos,minbcos,maxbcos,mintan,maxtan);

	if (mDlgInfor.DoModal()==IDOK)
	{
		T=mDlgInfor.m_T;
		distype=mDlgInfor.m_DisType;
	}
	else return;

    //初始化
	for ( i=0;i<patternnum;i++)//每个样品自成一类
	{
		m_pattern[i].category=i+1;
	}

	centerdistance=new double *[patternnum];//建立类间距离数组，centerdistance[i][j]表示i类和j类距离
	for ( i=1;i<patternnum;i++)
	{
		centerdistance[i]=new double [patternnum+1];
	}

	for ( i=1;i<patternnum;i++)
		for (int j=i+1;j<=patternnum;j++)
		{
			centerdistance[i][j]=GetDistance(m_pattern[i-1],m_pattern[j-1],distype);
		}

	centernum=patternnum;
	
	while(1)
	{
		double td,**tempdistance;
		int ti,tj;
		td=MAX;
		ti=0;
		tj=0;

		tempdistance= new double *[patternnum];//临时记录类间距离
		for (i=1;i<patternnum;i++)
		{
			tempdistance[i]=new double[patternnum+1];
		}

		for( i=1;i<centernum;i++)//找到距离最近的两类:ti,tj,记录最小距离td;
			for ( j=i+1;j<=centernum;j++)
			{
				if (td>centerdistance[i][j])	
				{
					td=centerdistance[i][j];
					ti=i;tj=j;
				}
			}

		if(td<T)//合并类i,j
		{
			for ( i=0;i<patternnum;i++)
			{
				if (m_pattern[i].category==tj)
					m_pattern[i].category=ti;
				if (m_pattern[i].category>tj)
					m_pattern[i].category--;
			}
			centernum--;

			for (i=1;i<centernum;i++)//重新计算合并后的类到其他各类的新距离
				for ( j=i+1;j<=centernum;j++)
				{
					if (i<ti)
					{
						if(j==ti)
							tempdistance[i][j]=sqrt (centerdistance[i][ti]*centerdistance[i][ti]/2+centerdistance[i][tj]*centerdistance[i][tj]/2-centerdistance[ti][tj]*centerdistance[ti][tj]/4);
						else if (j>=tj)
							tempdistance[i][j]=centerdistance[i][j+1];
						else
							tempdistance[i][j]=centerdistance[i][j];
					
					}
					else if (i==ti)
					{
						if (j<tj)
							tempdistance[i][j]=sqrt (centerdistance[ti][j]*centerdistance[ti][j]/2+centerdistance[j][tj]*centerdistance[j][tj]/2-centerdistance[ti][tj]*centerdistance[ti][tj]/4);
                        else
							tempdistance[i][j]=sqrt (centerdistance[ti][j+1]*centerdistance[ti][j+1]/2+centerdistance[tj][j+1]*centerdistance[tj][j+1]/2-centerdistance[ti][tj]*centerdistance[ti][tj]/4);
					}
					else if((i>ti)&&(i<tj))
					{
						if(j<tj)
							tempdistance[i][j]=centerdistance[i][j];
						else
							tempdistance[i][j]=centerdistance[i][j+1];
					}
					else //i>=tj
					{
						tempdistance[i][j]=centerdistance[i+1][j+1];
					}
				}
			for (i=1;i<centernum;i++)
				for ( j=i+1;j<=centernum;j++)
				{
					centerdistance[i][j]=tempdistance[i][j];
				}

		}
		else break;
		delete []tempdistance;
	}
	delete []centerdistance;

}
/************************************************************
*函数名称		Zhongxinfa()
*参数			void
*返回值  		void
*函数功能		按照重心法对全体样品进行分类
************************************************************/
void CCluster::Zhongxinfa()
{
	GetFeature();
	
	double	**centerdistance;//记录类间距离
	double  T;//阈值
	int		distype;//距离的形式（欧氏、余弦。。。）
	int     i,j;
	double minous,maxous,mincos,maxcos,minbcos,maxbcos,mintan,maxtan;

	minous=MAX; mincos=MAX; minbcos=MAX; mintan=MAX;
	maxous=0; maxcos=0; maxbcos=0; maxtan=0;
	//计算四种距离模式的参考值
	for (  i=0;i<patternnum-1;i++)
		for ( j=i+1;j<patternnum;j++)
		{
			if (minous>GetDistance(m_pattern[i],m_pattern[j],1))
				minous=GetDistance(m_pattern[i],m_pattern[j],1);
			if (maxous<GetDistance(m_pattern[i],m_pattern[j],1))
				maxous=GetDistance(m_pattern[i],m_pattern[j],1);

			if (mincos>GetDistance(m_pattern[i],m_pattern[j],2))
				mincos=GetDistance(m_pattern[i],m_pattern[j],2);
			if (maxcos<GetDistance(m_pattern[i],m_pattern[j],2))
				maxcos=GetDistance(m_pattern[i],m_pattern[j],2);

			if (minbcos>GetDistance(m_pattern[i],m_pattern[j],3))
				minbcos=GetDistance(m_pattern[i],m_pattern[j],3);
			if (maxbcos<GetDistance(m_pattern[i],m_pattern[j],3))
				maxbcos=GetDistance(m_pattern[i],m_pattern[j],3);
			
			if (mintan>GetDistance(m_pattern[i],m_pattern[j],4))
				mintan=GetDistance(m_pattern[i],m_pattern[j],4);
			if (maxtan<GetDistance(m_pattern[i],m_pattern[j],4))
				maxtan=GetDistance(m_pattern[i],m_pattern[j],4);
		}
	DlgInfor mDlgInfor;
	mDlgInfor.ShowInfor(minous,maxous,mincos,maxcos,minbcos,maxbcos,mintan,maxtan);

	if (mDlgInfor.DoModal()==IDOK)
	{
		T=mDlgInfor.m_T;
		distype=mDlgInfor.m_DisType;
	}
	else return;

    //初始化
	for ( i=0;i<patternnum;i++)//每个样品自成一类
	{
		m_pattern[i].category=i+1;
	}

	centerdistance=new double *[patternnum];//建立类间距离数组，centerdistance[i][j]表示i类和j类距离
	for ( i=1;i<patternnum;i++)
	{
		centerdistance[i]=new double [patternnum+1];
	}

	for ( i=1;i<patternnum;i++)
		for (int j=i+1;j<=patternnum;j++)
		{
			centerdistance[i][j]=GetDistance(m_pattern[i-1],m_pattern[j-1],distype);
		}

	centernum=patternnum;
	
	
    while(1)
	{
		double td,**tempdistance;
		int ti,tj;//距离最小的类
		int numi,numj;//i,j类中的元素个数

		td=MAX;
		ti=0;
		tj=0;
		numi=0;
		numj=0;
		tempdistance= new double *[patternnum];//临时记录类间距离
		for (i=1;i<patternnum;i++)
		{
			tempdistance[i]=new double[patternnum+1];
		}

		for( i=1;i<centernum;i++)//找到距离最近的两类:ti,tj,记录最小距离td;
			for ( j=i+1;j<=centernum;j++)
			{
				if (td>centerdistance[i][j])	
				{
					td=centerdistance[i][j];
					ti=i;tj=j;
				}
			}

		if(td<T)//最小距离小于阈值，合并类i,j
		{
			for (int i=0;i<patternnum;i++)
			{
				if (m_pattern[i].category==ti)
					numi++;
				if (m_pattern[i].category==tj)
				{
					m_pattern[i].category=ti;
					numj++;
				}
				if (m_pattern[i].category>tj)
					m_pattern[i].category--;
			}
			centernum--;
			//重新计算类间距离，保持类号的连续性
			for (i=1;i<centernum;i++)
				for (int j=i+1;j<=centernum;j++)
				{
					if (i<ti)
					{
						if(j==ti)
							tempdistance[i][j]=sqrt (centerdistance[i][ti]*centerdistance[i][ti]*numi/(numi+numj)+centerdistance[i][tj]*centerdistance[i][tj]*numj/(numi+numj)-centerdistance[ti][tj]*centerdistance[ti][tj]*numi*numj/(numi+numj));
						else if (j>=tj)
							tempdistance[i][j]=centerdistance[i][j+1];
						else
							tempdistance[i][j]=centerdistance[i][j];
					
					}
					else if (i==ti)
					{
						if (j<tj)
							tempdistance[i][j]=sqrt (centerdistance[ti][j]*centerdistance[ti][j]*numi/(numi+numj)+centerdistance[j][tj]*centerdistance[j][tj]*numj/(numi+numj)-centerdistance[ti][tj]*centerdistance[ti][tj]*numi*numj/(numi+numj));
                        else
							tempdistance[i][j]=sqrt (centerdistance[ti][j+1]*centerdistance[ti][j+1]*numi/(numi+numj)+centerdistance[tj][j+1]*centerdistance[tj][j+1]*numj/(numi+numj)-centerdistance[ti][tj]*centerdistance[ti][tj]*numi*numj/(numi+numj));
					}
					else if((i>ti)&&(i<tj))
					{
						if(j<tj)
							tempdistance[i][j]=centerdistance[i][j];
						else
							tempdistance[i][j]=centerdistance[i][j+1];
					}
					else //i>=tj
					{
						tempdistance[i][j]=centerdistance[i+1][j+1];
					}
				}
			for (i=1;i<centernum;i++)
				for (int j=i+1;j<=centernum;j++)
				{
					centerdistance[i][j]=tempdistance[i][j];
				}

		}//end if(td<T)
		else break;
		delete []tempdistance;
	}
	delete  []centerdistance;
}
/************************************************************
*函数名称		Leipingjunjulifa()
*参数			void
*返回值			void
*函数功能		按照类平均距离法法对全体样品进行分类
************************************************************/
void CCluster::Leipingjunjulifa()
{
	GetFeature();
	
	double	**centerdistance;//记录类间距离
	double T;//阈值
	int		distype;//距离的形式（欧氏、余弦。。。）
	double minous,maxous,mincos,maxcos,minbcos,maxbcos,mintan,maxtan;

	minous=MAX; mincos=MAX; minbcos=MAX; mintan=MAX;
	maxous=0; maxcos=0; maxbcos=0; maxtan=0;
	//计算四种距离模式的参考值
	for (int  i=0;i<patternnum-1;i++)
		for (int j=i+1;j<patternnum;j++)
		{
			if (minous>GetDistance(m_pattern[i],m_pattern[j],1))
				minous=GetDistance(m_pattern[i],m_pattern[j],1);
			if (maxous<GetDistance(m_pattern[i],m_pattern[j],1))
				maxous=GetDistance(m_pattern[i],m_pattern[j],1);

			if (mincos>GetDistance(m_pattern[i],m_pattern[j],2))
				mincos=GetDistance(m_pattern[i],m_pattern[j],2);
			if (maxcos<GetDistance(m_pattern[i],m_pattern[j],2))
				maxcos=GetDistance(m_pattern[i],m_pattern[j],2);

			if (minbcos>GetDistance(m_pattern[i],m_pattern[j],3))
				minbcos=GetDistance(m_pattern[i],m_pattern[j],3);
			if (maxbcos<GetDistance(m_pattern[i],m_pattern[j],3))
				maxbcos=GetDistance(m_pattern[i],m_pattern[j],3);
			
			if (mintan>GetDistance(m_pattern[i],m_pattern[j],4))
				mintan=GetDistance(m_pattern[i],m_pattern[j],4);
			if (maxtan<GetDistance(m_pattern[i],m_pattern[j],4))
				maxtan=GetDistance(m_pattern[i],m_pattern[j],4);
		}
	DlgInfor mDlgInfor;
	mDlgInfor.ShowInfor(minous,maxous,mincos,maxcos,minbcos,maxbcos,mintan,maxtan);
	if (mDlgInfor.DoModal()==IDOK)
	{
		T=mDlgInfor.m_T;
		distype=mDlgInfor.m_DisType;
	}
	else return;

    //初始化
	for ( i=0;i<patternnum;i++)//每个样品自成一类
	{
		m_pattern[i].category=i+1;
	}

	centerdistance=new double *[patternnum];//建立类间距离数组，centerdistance[i][j]表示i类和j类距离
	for ( i=1;i<patternnum;i++)
	{
		centerdistance[i]=new double [patternnum+1];
	}

	for ( i=1;i<patternnum;i++)
		for (int j=i+1;j<=patternnum;j++)
		{
			centerdistance[i][j]=GetDistance(m_pattern[i-1],m_pattern[j-1],distype);
		}

	centernum=patternnum;

	while(1)
	{
		double td,**tempdistance;
		int ti,tj;//距离最小的类
		int numi,numj;//i,j类中的元素个数
		double dis1,dis2;

	    dis1=0;
		dis2=0;
		td=MAX;
		ti=0;
		tj=0;
		numi=0;
		numj=0;
		tempdistance= new double *[patternnum];//临时记录类间距离
		for (int i=1;i<patternnum;i++)
		{
			tempdistance[i]=new double[patternnum+1];
		}
		//找距离最近的两类ti,tj，记录最小距离td
		for( i=1;i<centernum;i++)
		{
			for (int j=i+1;j<=centernum;j++)
			{
				if (td>centerdistance[i][j])	
				{
					td=centerdistance[i][j];
					ti=i;tj=j;
				}
			}
		}

		if(td<T)//合并类ti,tj
		{
			centernum--;
			//对类间距离数组排序，以保持类号的连续性
			for (int i=1;i<centernum;i++)
				for (int j=i+1;j<=centernum;j++)
				{
					if (i<ti)
					{
						if(j==ti)
						{
							numi=0;numj=0;
							dis1=0;dis2=0;
							for (int m=0;m<patternnum;m++)
								if (m_pattern[m].category==i)
								{
									for (int n=0;n<patternnum;n++)
									{
										if (m_pattern[n].category==ti)
										{
											numi++;
											dis1+=GetDistance(m_pattern[m],m_pattern[n],distype)*GetDistance(m_pattern[m],m_pattern[n],distype);
										}
										if(m_pattern[n].category==tj)
										{
											numj++;
											dis2+=GetDistance(m_pattern[m],m_pattern[n],distype)*GetDistance(m_pattern[m],m_pattern[n],distype);
										}
									}
								}
                            tempdistance[i][j]=sqrt((dis1+dis2)/(numi+numj));
						}
						else if (j>=tj)
							tempdistance[i][j]=centerdistance[i][j+1];
						else
							tempdistance[i][j]=centerdistance[i][j];
					
					}
					else if (i==ti)
					{
						if (j<tj)
						{
							numi=0;numj=0;
							dis1=0;dis2=0;
							for (int m=0;m<patternnum;m++)
								if (m_pattern[m].category==j)
								{
									for (int n=0;n<patternnum;n++)
									{
										if (m_pattern[n].category==ti)
										{
											numi++;
											dis1+=GetDistance(m_pattern[m],m_pattern[n],distype)*GetDistance(m_pattern[m],m_pattern[n],distype);
										}
										if(m_pattern[n].category==tj)
										{
											numj++;
											dis2+=GetDistance(m_pattern[m],m_pattern[n],distype)*GetDistance(m_pattern[m],m_pattern[n],distype);
										}
									}
								}
                            tempdistance[i][j]=sqrt((dis1+dis2)/(numi+numj));
						
						}
                        else
						{
							numi=0;numj=0;
							dis1=0;dis2=0;
							for (int m=1;m<=patternnum;m++)
								if (m_pattern[m].category==(j+1))
								{
									for (int n=1;n<=patternnum;n++)
									{
										if (m_pattern[n].category==ti)
										{
											numi++;
											dis1+=GetDistance(m_pattern[m],m_pattern[n],distype)*GetDistance(m_pattern[m],m_pattern[n],distype);
										}
										if(m_pattern[n].category==tj)
										{
											numj++;
											dis2+=GetDistance(m_pattern[m],m_pattern[n],distype)*GetDistance(m_pattern[m],m_pattern[n],distype);
										}
									}
								}
                            tempdistance[i][j]=sqrt((dis1+dis2)/(numi+numj));
						
						}
					}
					else if((i>ti)&&(i<tj))
					{
						if(j<tj)
							tempdistance[i][j]=centerdistance[i][j];
						else
							tempdistance[i][j]=centerdistance[i][j+1];
					}
					else //i>=tj
					{
						tempdistance[i][j]=centerdistance[i+1][j+1];
					}
				}
			for (i=1;i<centernum;i++)
				for (int j=i+1;j<=centernum;j++)
				{
					centerdistance[i][j]=tempdistance[i][j];
				}

			for ( i=0;i<patternnum;i++)
			{
				if (m_pattern[i].category==tj)
					m_pattern[i].category=ti;
				if (m_pattern[i].category>tj)
					m_pattern[i].category--;
			}
			delete []tempdistance;
		}//end if(td<T)
		else break;
	}//end while
	delete []centerdistance;
}
/************************************************************
*函数名称		Kjunzhi()
*参数			void
*返回值		    void
*函数功能		按照K均值对全体样品进行分类
************************************************************/
void CCluster::Kjunzhi()
{
	GetFeature();

	int		distype;//距离的形式(欧氏、余弦...)
	int		times;//max loop number
	int		i,j;

	DlgInfor mDlgInfor;
	mDlgInfor.ShowInfor(4);
	if (mDlgInfor.DoModal()==IDOK)
	{
		distype=mDlgInfor.m_DisType;
		times=mDlgInfor.m_Times;
		centernum=mDlgInfor.m_CenterNum;
	}
	else return;

	BOOL change=true;//退出标志，false时表示样品所属类别不再变化，中止计算
	int counter=0;//记录当前已经循环的次数
	double distance;//到各中心的距离
	distance=MAX;
	
	m_center=new Center[centernum];

	for ( i=0;i<patternnum;i++)
		m_pattern[i].distance=MAX;
	for ( i=0;i<centernum;i++)//初始化，前centernum个模版各自分为一类
	{
		m_pattern[i].category=i+1;
		m_pattern[i].distance=0;
		for ( j=0;j<N*N;j++)
			m_center[i].feature[j]=m_pattern[i].feature[j];
		m_center[i].index=i+1;
	}

	while (change && counter<times)
	{
		counter++;
		change=false;
		for( i=0;i<patternnum;i++)//对所有样品重新归类
		{
			//计算第i个模式到各个聚类中心的最小距离，
			int index=1;
			distance=MAX;
            
			for (int j=0;j<centernum;j++)
				if (distance>GetDistance(m_pattern[i],m_center[j],distype))
				{
					distance=GetDistance(m_pattern[i],m_center[j],distype);
					index=j;//找到最小距离,是到第index个聚类中心的距离
				}
			
			//比较原中心号与新中心号
			//相同：更新距离。
			//不同：1，新距离小，则归入新中心，更新距离，重新计算前后两个聚类中心模式
			//2，新距离大于原距离，不处理；
			//counter＋＋
			if (m_pattern[i].category==m_center[index].index)//属于原类
			{
				m_pattern[i].distance=distance;
			}
			else//不属于原类
			{
				int tpcenter=m_pattern[i].category;//记录原类号
				m_pattern[i].category=m_center[index].index;//归入新类
				m_pattern[i].distance=distance;
				if(tpcenter!=0)
				{
					for (int k=0;k<centernum;k++)
						if (m_center[k].index==tpcenter)
					CalCenter(&m_center[k]);//计算原属类中心
				}
				CalCenter(&m_center[index]);//计算新属类中心
				change=true;
			}
		}
		
	}//end of while 
	delete []m_center;
}
/************************************************************
*函数名称		ISODATA()
*参数			void
*返回值		void
*函数功能		用ISODATA方法对全体样品进行分类
************************************************************/
void CCluster::ISODATA()
{
	GetFeature();
	
	int i,j;
	int      distype;
	int      times;//迭代的最多次数，用户输入
	int      precenternum;//当前类数
	double   T;//两类中心的最小距离，小于该阈值将合并
	double   equation;//类内方差阈值
	double   *avedistance;//avedistance[i]:第i+1类内平均距离,i=0,1,...,centernum.
	double   allavedis;//全部模式样本中心平均距离

	double minous,maxous,mincos,maxcos,minbcos,maxbcos,mintan,maxtan;

	minous=MAX; mincos=MAX; minbcos=MAX; mintan=MAX;
	maxous=0; maxcos=0; maxbcos=0; maxtan=0;
	//计算四种距离模式的参考值
	for (  i=0;i<patternnum-1;i++)
		for ( j=i+1;j<patternnum;j++)
		{
			if (minous>GetDistance(m_pattern[i],m_pattern[j],1))
				minous=GetDistance(m_pattern[i],m_pattern[j],1);
			if (maxous<GetDistance(m_pattern[i],m_pattern[j],1))
				maxous=GetDistance(m_pattern[i],m_pattern[j],1);

			if (mincos>GetDistance(m_pattern[i],m_pattern[j],2))
				mincos=GetDistance(m_pattern[i],m_pattern[j],2);
			if (maxcos<GetDistance(m_pattern[i],m_pattern[j],2))
				maxcos=GetDistance(m_pattern[i],m_pattern[j],2);

			if (minbcos>GetDistance(m_pattern[i],m_pattern[j],3))
				minbcos=GetDistance(m_pattern[i],m_pattern[j],3);
			if (maxbcos<GetDistance(m_pattern[i],m_pattern[j],3))
				maxbcos=GetDistance(m_pattern[i],m_pattern[j],3);
			
			if (mintan>GetDistance(m_pattern[i],m_pattern[j],4))
				mintan=GetDistance(m_pattern[i],m_pattern[j],4);
			if (maxtan<GetDistance(m_pattern[i],m_pattern[j],4))
				maxtan=GetDistance(m_pattern[i],m_pattern[j],4);
		}
	//求所有样品总方差
	double cen[N*N],equ[N*N];
	for (i=0; i<N*N; i++)
	{
		cen[i]=0;
		equ[i]=0;
	}
	for (i=0;i<patternnum;i++)//所有样品特征累加
		for (j=0;j<N*N;j++)
		    cen[j]+=m_pattern[i].feature[j];
	for (i=0;i<N*N;i++)//求所有样品特征均值
		cen[i]=cen[i]/(double)patternnum;
	for (i=0;i<patternnum;i++)//总方差
		for (j=0;j<N*N;j++)
			equ[j]+=(m_pattern[i].feature[j]-cen[j])*(m_pattern[i].feature[j]-cen[j]);
	for (i=0;i<N*N;i++)//均方差
		equ[i]=sqrt(equ[i]/(double)patternnum);
	double minequ=MAX;
	double maxequ=0.0;
	//求均方差中的最大最小值
	for (i=0;i<N*N;i++)
	{
		if (minequ>equ[i])
            minequ=equ[i];
		if (maxequ<equ[i])
			maxequ=equ[i];
	}

	DlgInfor    mDlgInfor;
//输出到对话框
	mDlgInfor.ShowInfor(minous,maxous,mincos,maxcos,minbcos,maxbcos,mintan,maxtan,minequ,maxequ);//OUTPUT EQUATIONOUT!!!
	if (mDlgInfor.DoModal()==IDOK)
	{
		distype=mDlgInfor.m_DisType;
		T=mDlgInfor.m_T;
		times=mDlgInfor.m_Times;
		equation=mDlgInfor.m_EquationIn;
		centernum=mDlgInfor.m_CenterNum;
	}
	else return;
    //所有样品各归一类
	precenternum=centernum;
	m_center=new Center[precenternum];
	for ( i=0;i<precenternum;i++)
	{
		m_pattern[i].category=i+1;
		for (j=0;j<N*N;j++)
			m_center[i].feature[j]=m_pattern[i].feature[j];
		m_center[i].index=i+1;
		m_center[i].patternnum=1;
	}

	int counter=0;//循环次数

	avedistance=new double[precenternum];

	while (++counter<times)
	{
		for ( i=0;i<patternnum;i++)//把所有样品重新归类
		{
			double td=MAX;
			int index=0;
			for (int j=0;j<precenternum;j++)
				if (td>GetDistance(m_pattern[i],m_center[j],distype))
				{
					td=GetDistance(m_pattern[i],m_center[j],distype);
					index=j;
				}
			m_pattern[i].category=m_center[index].index;
		}
		//修正各中心
		for (i=0;i<precenternum;i++)
			CalCenter(&m_center[i]);
		for (i=0; i<precenternum;i++)
		{
			if (m_center[i].patternnum==0)
			{
				for(j=i; j<precenternum-1; j++)
					m_center[j]=m_center[j+1];
				precenternum--;

			}
		}
		//计算各类距中心平均距离
		for (i=0;i<centernum;i++)
			avedistance[i]=0.0;//初始化

		allavedis=0;	//全部样本平均距离

		for (i=0;i<precenternum;i++)
		{
			int num=0;//类中成员个数
			double dis;
			dis=0.0;
			for ( j=0;j<patternnum;j++)
			{
				if (m_pattern[j].category==i+1)
				{
					++num;
					dis+=GetDistance(m_pattern[j],m_pattern[i],distype);
				}
			}
			allavedis+=dis;
			avedistance[i]=(double)(dis/(double)num);
		}

		allavedis/=patternnum;
	 
		if ((precenternum>=2*centernum) || ((counter%2)==0) && (precenternum>(int)(centernum/2+0.5)))//合并
		{
			//找到距离最近的两个类
			double td=MAX;
			int ti,tj;
			for( i=0;i<precenternum;i++)
				for ( j=i+1;j<precenternum;j++)
				{
					double tdin;
					tdin=GetDistance(m_center[i],m_center[j],distype);
					if (td<tdin)
					{
						td=tdin;
						ti=i;
						tj=j;
					}
				}
			//判断是否要合并
			if(td<T)//合并
			{
				for ( i=0;i<patternnum;i++)
				{
					if (m_pattern[i].category==m_center[tj].index)
						m_pattern[i].category=m_center[ti].index;
					if (m_pattern[i].category>m_center[tj].index)
						m_pattern[i].category--;
				}
				CalCenter(&m_center[ti]);
				for (i=tj;i<precenternum-1;i++)
				{
					m_center[i]=m_center[i+1];
					m_center[i].index--;
				}
				precenternum--;
			}
		}//end 合并
		else//分裂
		{
			double **mequation;//标准差
			int ti,tj;//记录最大标准差出现位置,第ti+1号类的第tj+1位。ti＝0,1,...,precenternum-1.
			
			mequation= new double *[precenternum];
			for (i=0;i<precenternum;i++)
			{
				mequation[i]=new double[N*N];
				for (j=0;j<N*N;j++)
					mequation[i][j]=0.0;
			}
			//计算标准差
			for ( i=0;i<precenternum;i++)
			{
				for ( j=0;j<patternnum;j++)
					if (m_pattern[j].category==m_center[i].index)
					{
						for (int k=0;k<N*N;k++)
								mequation[i][k]+=(m_pattern[j].feature[k]-m_center[i].feature[k])*(m_pattern[j].feature[k]-m_center[i].feature[k]);
					}
					for (int k=0;k<N*N;k++)
						mequation[i][k]=sqrt(mequation[i][k]/m_center[i].patternnum);
			}
			//找最大标准差
			ti=0;
			tj=0;
			for (i=0;i<precenternum;i++)
				for ( j=0;j<N*N;j++)
					if(mequation[i][j]>mequation[ti][tj])
						{
							ti=i;tj=j;
						};
			//判断是否要分裂
			if (mequation[ti][tj]>equation)//大于给定阈值
			{
				if (avedistance[ti]>allavedis )
					//类平均距离大于总平均距离  分裂
				{
					precenternum++;
					Center *tempcenter;
					tempcenter=new Center [precenternum];

					for (i=0;i<precenternum-1;i++)
						tempcenter[i]=m_center[i];
					tempcenter[precenternum-1].index=precenternum;
					for (j=0;j<N*N;j++)
						tempcenter[precenternum-1].feature[j]=m_center[ti].feature[j];
					tempcenter[precenternum-1].feature[tj]-=0.5*mequation[ti][tj];
					tempcenter[ti].feature[tj]+=0.5*mequation[ti][tj];

					delete []m_center;
					m_center=tempcenter;
									
				}
			}
			delete []mequation;
		}//end 分裂
	}//end while(1)*/
	delete []avedistance;
	delete []m_center;
}

/************************************************************
*函数名称		Mohujulei()
*参数			void
*返回值		    void
*函数功能		用模糊聚类方法对全体样品进行分类
************************************************************/
void CCluster::FuzzyCluster()
{
	GetFeature();//获得所有样品特征

	double	*dis, *tempdis;
	double	dismax;
	int		i,j;
	int		distype;
	dismax=0;

	dis=new double [patternnum*patternnum];//模糊系数矩阵
	tempdis=new double [patternnum*patternnum];
	DlgFuzzyDistance  dfd;
	if (dfd.DoModal()==IDOK)
	{
		distype=dfd.mfuzzydistance;
	}
	else 
		return;
    //得到初始模糊距离
	for ( i=0; i<patternnum; i++)
		for (j=0; j<patternnum; j++)
	{
		dis[i*patternnum+j]=GetFuzzyDistance(m_pattern[i],m_pattern[j],distype);//distype
	}

   //构造等价类
	bool flag;
	flag=true;
	while (flag)
	{
		flag=false;
		for ( i=0; i<patternnum; i++)
			for ( j=0; j<patternnum; j++)
				if (i==j)//对角线为1
					tempdis[i*patternnum+j]=1;
				else
					tempdis[i*patternnum+j]=GetDistance(dis,i,j);
		for ( i=0; i<patternnum; i++)
		{
			for ( j=0; j<patternnum; j++)
				if ((tempdis[i*patternnum+j]-dis[i*patternnum+j])*(tempdis[i*patternnum+j]-dis[i*patternnum+j])>0.000001)//(tdis[i][j]!=dis[i][j])
				{
					flag=true;
					break;
				}
			if (flag)
				break;
		}
	
		for ( i=0; i<patternnum*patternnum; i++)
				dis[i]=tempdis[i];
	}
	//输出模糊矩阵
	CString ts,sout;
	//第一行标号1，2，。。。，patternnum。
	sout.Insert(sout.GetLength(),"   \t");
	for (i=1; i<=patternnum; i++)
	{
		ts.Format("%d   \t",i);
		sout.Insert(sout.GetLength(),ts);
	}
	sout.Insert(sout.GetLength(),"\n\n");

	for (i=0; i<patternnum; i++)
	{
		//每列开头标号
		ts.Format("%d   \t",i+1);
		sout.Insert(sout.GetLength(),ts);
		//输出模糊系数矩阵
		for(j=0; j<patternnum; j++)
		{
			ts.Format("%0.3f\t",dis[i*patternnum+j]);
			sout.Insert(sout.GetLength(),ts);
			if ((j+1)%patternnum==0)
				sout.Insert(sout.GetLength(),"\n\n\n");

		}
	}
	MessageBox(NULL,sout,"模糊矩阵",MB_OK);

	delete []tempdis;

	double *xishu=new double [patternnum*patternnum];
	for(i=0; i<patternnum*patternnum; i++)
		xishu[i]=-1;

	int pointer=0;
	//记录模糊系数矩阵中不同的系数
	for ( i=0; i<patternnum; i++)
		for ( j=i; j<patternnum; j++)
		{
			bool done=false;
			for (int k=0; k<pointer; k++)
			{
				if ((xishu[k]-dis[i*patternnum+j])*(xishu[k]-dis[i*patternnum+j])<0.000001)
				{
					done=true;
					break;
				}
			}
			if (!done)
			{
				xishu[pointer]=dis[i*patternnum+j];
				pointer++;
			}
		}
	
	for(i=0; i<pointer-1; i++)//对阈值由小到大排序
		for (j=0; j<pointer-i-1; j++)
		{
			if (xishu[j]>xishu[j+1])
			{
				double	temp=xishu[j];
				xishu[j]=xishu[j+1];
				xishu[j+1]=temp;
			}
		}
	CString s,str;
	for (i=0; i<pointer; i++)
	{
		s.Format("%0.4f  ",xishu[i]);
		str.Insert(str.GetLength(),s);
	}
	delete   []xishu;
	//用户输入聚类阈值
	double    yz;
	DlgMohu		mohu;
	mohu.m_Mohuxishu=str;
	if (mohu.DoModal()==IDOK)
	{
		yz=mohu.m_Mohuyuzhi;	
	}
	else return;
	
	int *result;
	//根据阈值输出聚类结果
	result=new int [patternnum*patternnum];
	for (i=0; i<patternnum*patternnum; i++)
		if (dis[i]>=yz)
			result[i]=1;
		else 
			result[i]=0;

		//分类后输出

	//第一行标号
	sout="";
	sout.Insert(-1,"每行中\"1\"对应的列为同一类");
	sout.Insert(sout.GetLength(),"\n\n");
	sout.Insert(sout.GetLength(),"   \t");
	for (i=1; i<=patternnum; i++)
	{
		ts.Format("%d   \t",i);
		sout.Insert(sout.GetLength(),ts);
	}
	sout.Insert(sout.GetLength(),"\n\n");
		

	for (i=0; i<patternnum; i++)
	{
		//每列开头标号
		ts.Format("%d   \t",i+1);
		sout.Insert(sout.GetLength(),ts);
		for(j=0; j<patternnum; j++)//首行为原模糊系数
		{
			ts.Format("%0.3f\t",dis[i*patternnum+j]);
			sout.Insert(sout.GetLength(),ts);
			if ((j+1)%patternnum==0)
				sout.Insert(sout.GetLength(),"\n");
		}
		sout.Insert(sout.GetLength(),"   \t");
		for(j=0; j<patternnum; j++)//次行为根据阈值修改后的系数“1”或“0”
		{
			ts.Format("%d\t",result[i*patternnum+j]);
			sout.Insert(sout.GetLength(),ts);
			if ((j+1)%patternnum==0)
				sout.Insert(sout.GetLength(),"\n\n");
		}
	}
	MessageBox(NULL,sout,"分类前后的矩阵对照",MB_OK);

	centernum=0;

	for (i=0; i<patternnum; i++)//按照阈值分类
		for (j=i; j<patternnum; j++)
		{
			if (result[i*patternnum+j]==1)
			{
				if (m_pattern[i].category!=0)
					m_pattern[j].category=m_pattern[i].category;
				else if (m_pattern[j].category!=0)
					m_pattern[i].category=m_pattern[j].category;
				else
				{
					centernum++;
					m_pattern[j].category=centernum;
					m_pattern[i].category=centernum;
				}
			}
		}
	delete []dis;
	delete []result;
}




