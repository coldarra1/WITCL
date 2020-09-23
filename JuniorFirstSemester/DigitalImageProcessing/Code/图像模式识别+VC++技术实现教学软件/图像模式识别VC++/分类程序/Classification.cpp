// Classification.cpp: implementation of the Classification class.
// 2005.1.13－16：02 By Superman 
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "DSPLIT.h"
#include "Classification.h"
#include "matrix.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Classification::Classification()
{

}

Classification::~Classification()
{

}



/******************************************************************
*   函数名称：LeastDistance()
*   函数类型：number_no，结构体
*   函数功能：最小距离法 ,返回数字类别和编号
******************************************************************/
number_no Classification::LeastDistance()
{
	double min=10000000000;
	number_no number_no;
	for(int n=0;n<10;n++)
	{
		for(int i=0;i<pattern[n].number;i++)
		{
			if(pipei(pattern[n].feature[i],testsample)<min)
			{
				//匹配的最小值
				min=pipei(pattern[n].feature[i],testsample);
				number_no.number=n;//样品类别
				number_no.no=i;//样品序号
			}
		}
	}
	return number_no;//返回手写数字的类别和序号
}

/******************************************************************
*   函数名称：Fisher_2Classes(int Class0, int Class1)
*   函数类型：int 
*   参数说明：Class0,Class1：0～9中的任意两个类别
*   函数功能：两类Fisher分类器,返回Class0，Class1中的一个
******************************************************************/
int Classification::Fisher_2Classes(int Class0, int Class1)
{
	double Xmeans[2][25];//两类的均值
	double S[2][25][25];//样品类内离散度矩阵
	double Sw[25][25];//总类间离散度矩阵
	double Sw_[25][25];//Sw的逆矩阵
	double W[25];//解向量w*
	double difXmeans[25];//均值差
	double X[25];//未知样品
	double m0,m1;//类样品均值
	double y0;//阈值y0
	int i,j,k;

	for(i=0;i<2;i++)
		for(j=0;j<25;j++)
			Xmeans[i][j]=0;
	int num0,num1;		//两类样品的个数
	//两类样品特征
	double mode0[200][25],mode1[200][25];
	//两类样品个数
	num0=40;//pattern[Class0].number;
	num1=40;//pattern[Class1].number;
	for(i=0;i<num0;i++)
	{
		for(j=0;j<25;j++)
		{
			Xmeans[0][j]+=pattern[Class0].feature[i][j];
			mode0[i][j]=pattern[Class0].feature[i][j];
		}
	}

	for(i=0;i<num1;i++)
	{
		for(j=0;j<25;j++)
		{
			Xmeans[1][j]+=pattern[Class1].feature[i][j];	
			mode1[i][j]=pattern[Class1].feature[i][j];
		}
	}
	//求得两个样品均值向量
	for(i=0;i<25;i++)	
	{
		Xmeans[0][i]/=(double)num0;
		Xmeans[1][i]/=(double)num1;
	}
	//求两类样品类内离散度矩阵
	for(i=0;i<25;i++)
	for(j=0;j<25;j++)
	{
		double s0=0.0,s1=0.0;
		for(k=0;k<num0;k++)
			s0=s0+(mode0[k][i]-Xmeans[0][i])*(mode0[k][j]-Xmeans[0][j]);
		s0=s0/(double)(num0-1);
		S[0][i][j]=s0;//第一类
		for(k=0;k<num1;k++)
			s1=s1+(mode1[k][i]-Xmeans[1][i])*(mode1[k][j]-Xmeans[1][j]);
		s1=s1/(double)(num1-1);
		S[1][i][j]=s1;//第二类		
	}
	//总类间离散度矩阵
	for(i=0;i<25;i++)
	for(j=0;j<25;j++)
	{
		Sw[i][j]=S[0][i][j]+S[1][i][j];
	}
	//Sw的逆矩阵
	for(i=0;i<25;i++)
		for(j=0;j<25;j++)
			Sw_[i][j]=Sw[i][j];	
	double(*p)[25]=Sw_;	
	brinv(*p,25);		//Sw的逆矩阵Sw_
	//计算w*  w*＝Sw_×(Xmeans0-Xmeans1)
	for(i=0;i<25;i++)
		difXmeans[i]=Xmeans[0][i]-Xmeans[1][i];
	for(i=0;i<25;i++)
		W[i]=0.0;
	brmul(Sw_,difXmeans,25,W);//计算出W*
	
	//各类样品均值
	m0=0.0;
	m1=0.0;
	for(i=0;i<num0;i++)
	{
		m0+=brmul(W,mode0[i],25);
	}
	for(i=0;i<num1;i++)
	{
		m1+=brmul(W,mode1[i],25);
	}
	m0/=(double)num0;
	m1/=(double)num1;
	y0=(num0*m0+num1*m1)/(num0+num1);//阈值y0
	
	//对于任意的手写数字X
	for(i=0;i<25;i++)
		X[i]=testsample[i];
	double y;//X在w*上的投影点
	y=brmul(W,X,25);
	if (y>=y0) 
		return Class0;
	else
		return Class1;
}

/******************************************************************
*   函数名称：Fisher()
*   函数类型：int 
*   函数功能：Fisher分类器,返回手写数字的类别
******************************************************************/
int Classification::Fisher()
{
	int i,j,number,maxval,num[10];
	for(i=0;i<10;i++)
		num[i]=0;
	for(i=0;i<10;i++)
		for(j=0;j<i;j++)
			num[Fisher_2Classes(i,j)]++;
	maxval=num[0];
	number=0;
	for(i=1;i<10;i++)
	{
		if(num[i]>maxval)
		{
			maxval=num[i];
			number=i;
		}
	}
	return number;
}

/******************************************************************
*   函数名称：BayesErzhishuju()
*   函数类型：int 
*   函数功能：基于二值数据的Bayes分类器 ,返回手写数字的类别
******************************************************************/
int Classification::BayesErzhishuju()
{
	double Pw[10];//先验概率P(wj)=Nj/N
	double P[10][25];//Pj(wi)wi:wi类，j:第j个特征
	double PXw[10];//类条件概率P(X|wj)
	double PwX[10];//后验概率P(wj|X)

	int i,j;

	//求先验概率
	int n[10];//各类样品数
	int N=0;//样品总数
	for(i=0;i<10;i++)
	{
		//各数字类别样品数
		n[i]=pattern[i].number;
		N+=n[i];//样品总数
	}
	for(i=0;i<10;i++)
		Pw[i]=(double)n[i]/(double)N;//先验概率
	
	//求类条件概率
	for(i=0;i<10;i++)
	{
		for(j=0;j<25;j++)
		{
			int numof1=0;//二值数据中1的个数
			for(int k=0;k<pattern[i].number;k++)
				numof1+=pattern[i].feature[k][j]>0.1?1:0;
			P[i][j]=(double)(numof1+1)/(double)(n[i]+2);
		}
	}

	for(i=0;i<10;i++)
	{
		double p=1;
		for(int j=0;j<25;j++)
		{
			p*=(testsample[j]>0.1)?P[i][j]:1-P[i][j];
		}
		PXw[i]=p;
	}

	//求后验概率
	double PX=0.0,maxP=0.0;
	int number;
	for(i=0;i<10;i++)
	{
		PX+=Pw[i]*PXw[i];
	}

	for(i=0;i<10;i++)
	{
		PwX[i]=Pw[i]*PXw[i]/PX;
		if(PwX[i]>maxP)
		{
			maxP=PwX[i];
			number=i;
		}
	}
	return number;
}

/******************************************************************
*   函数名称：BayesLeasterror()
*   函数类型：int 
*   函数功能：最小错误概率的Bayes分类器 ,返回手写数字的类别
******************************************************************/
int Classification::BayesLeasterror()
{
	double X[25];//待测样品
	double Xmeans[25];//样品的均值
	double S[25][25];//协方差矩阵
	double S_[25][25];//S的逆矩阵
	double Pw;//先验概率
	double hx[10];//判别函数
	
	int i,j,k,n;
	
	for(n=0;n<10;n++)//循环类别0～9
	{
		int num=pattern[n].number;//样品个数
		//求样品平均值
		for(i=0;i<25;i++)
			Xmeans[i]=0.0;
		for(k=0;k<num;k++)
		{
			for(i=0;i<25;i++)
				Xmeans[i]+=pattern[n].feature[k][i]>0.10?1.0:0.0;
		}
		for(i=0;i<25;i++)
			Xmeans[i]/=(double)num;
		//求协方差矩阵
		double mode[200][25];
		for(i=0;i<num;i++)
			for(j=0;j<25;j++)
				mode[i][j]=pattern[n].feature[i][j]>0.10?1.0:0.0;
		for(i=0;i<25;i++)
		for(j=0;j<25;j++)
		{
			double s=0.0;
			for(k=0;k<num;k++)
				s=s+(mode[k][i]-Xmeans[i])*(mode[k][j]-Xmeans[j]);
			s=s/(double)(num-1);
			S[i][j]=s;
		}
		//求先验概率
		int total=0;
		for(i=0;i<10;i++)
			total+=pattern[i].number;
		Pw=(double)num/(double)total;
		//求S的逆矩阵
		for(i=0;i<25;i++)
			for(j=0;j<25;j++)
				S_[i][j]=S[i][j];

		double(*p)[25]=S_;

		brinv(*p,25);//S的逆矩阵
		//求S的行列式
		double (*pp)[25]=S;
		double DetS;
		DetS=bsdet(*pp,25);//S的行列式
		//求判别函数
		for(i=0;i<25;i++)
			X[i]=testsample[i]>0.10?1.0:0.0;
		for(i=0;i<25;i++)
			X[i]-=Xmeans[i];
		double t[25];
		for(i=0;i<25;i++)
			t[i]=0;
		brmul(X,S_,25,t);
		double t1=brmul(t,X,25);
		double t2=log(Pw);
		double t3=log(DetS+1);
		hx[n]=-t1/2+t2-t3/2;
	}

	double maxval=hx[0];
	int number=0;
	//判别函数的最大值
	for(n=1;n<10;n++)
	{
		if(hx[n]>maxval)
		{
			maxval=hx[n];
			number=n;
		}
	}
	return number;
}

/******************************************************************
*   函数名称：BayesLeastRisk(double loss[10][10])
*   函数类型：double*
*   参数说明：double loss[10][10]：损失
*   函数功能：最小风险的Bayes分类器 ，返回各类的风险值
******************************************************************/
double* Classification::BayesLeastRisk(double loss[10][10])
{
	double X[25];//待测样品
	double Xmeans[25];//样品的均值
	double S[25][25];//协方差矩阵S
	double S_[25][25];//S的逆矩阵
	double P[10];//后验概率
	double Pw;//先验概率
	double hx[10];//判别函数
	
	int i,j,k,n;
	
	for(n=0;n<10;n++)//
	{
		int num=pattern[n].number;//样品个数
		//求样品均值
		for(i=0;i<25;i++)
			Xmeans[i]=0.0;
		for(k=0;k<num;k++)
		{
			for(i=0;i<25;i++)
				Xmeans[i]+=pattern[n].feature[k][i]>0.2?1.0:0.0;
		}
		for(i=0;i<25;i++)
			Xmeans[i]/=(double)num;
		//求协方差矩阵
		double mode[200][25];
		for(i=0;i<num;i++)
			for(j=0;j<25;j++)
				mode[i][j]=pattern[n].feature[i][j]>0.2?1.0:0.0;
		for(i=0;i<25;i++)
		for(j=0;j<25;j++)
		{
			double s=0.0;
			for(k=0;k<num;k++)
				s=s+(mode[k][i]-Xmeans[i])*(mode[k][j]-Xmeans[j]);
			s=s/(double)(num-1);
			S[i][j]=s;
		}
		//求先验概率
		int total=0;//样品总数
		for(i=0;i<10;i++)
			total+=pattern[i].number;
		Pw=(double)num/(double)total;
		//求S的逆矩阵
		for(i=0;i<25;i++)
			for(j=0;j<25;j++)
				S_[i][j]=S[i][j];

		double(*p)[25]=S_;

		brinv(*p,25);//S的逆矩阵
		//求S的行列式
		double (*pp)[25]=S;
		double DetS;
		DetS=bsdet(*pp,25);//S的行列式
		//求判别函数
		for(i=0;i<25;i++)
			X[i]=testsample[i]>0.2?1.0:0.0;
		for(i=0;i<25;i++)
			X[i]-=Xmeans[i];
		double t[25];
		for(i=0;i<25;i++)
			t[i]=0;
		brmul(X,S_,25,t);
		double t1=brmul(t,X,25);
		double t2=log(Pw);
		double t3=log(DetS+1);
		P[n]=-t1/2+t2-t3/2;
	}
	
	for(n=0;n<10;n++)
	{
		double t=0.0;
		for(i=0;i<10;i++)
			t+=loss[n][i]*P[i];
		hx[n]=t;
	}
	
	return (double*)hx;
}

/******************************************************************
*   函数名称：Jiangcheng()
*   函数类型：int 
*   函数功能：奖惩算法 ,返回手写数字的类别
******************************************************************/
int Classification::Jiangcheng()
{
	double w[10][26];//权值
	double d[10];//迭代计算结果权矢量
	double x[26];//增1样品
	double hx[10];//判别函数
	bool flag;
	int n,i,j,k;
	int c=0;//迭代次数

	//权值初值为0
	for(n=0;n<10;n++)
		for(i=0;i<26;i++)
			w[n][i]=0;
	do
	{
		flag=true;
		for(n=0;n<10;n++)
		{
			for(i=0;i<40;i++)//for(i=0;i<pattern[n].number;i++)
			{
				//取已知样品
				for(j=0;j<25;j++)
					x[j]=pattern[n].feature[i][j];
				x[25]=1;//最后一位置1
				//计算结果权矢量
				for(j=0;j<10;j++)
					d[j]=0;
				for(j=0;j<10;j++)
					for(k=0;k<26;k++)
						d[j]+=w[j][k]*x[k];
				bool f=true;
				//判断d[n]是否为最大值
				for(j=0;j<10;j++)
				{
					if(j!=n)
						f&=(d[n]>d[j])?true:false;
				}

				if(f)//若d[n]为最大值
					flag&=true;//通过检验
				else//否则，未通过检验需要修正权值
				{
					for(j=0;j<10;j++)
					{
						for(k=0;k<26;k++)
						{
							if(j==n)
								w[j][k]+=x[k];
							else if(d[j]>d[n])
								w[j][k]-=x[k];
							else;
						}
					}
					flag&=false;
				}
			}
		}
		if(++c>2000)break;
	}while(!flag);//到此为止得到线性判别函数权矢量

	double num[26];//未知样品
	for(i=0;i<25;i++)
		num[i]=testsample[i];
	num[25]=1;//末位置1
	for(n=0;n<10;n++)//计算判别函数
	{
		hx[n]=0;
		for(i=0;i<26;i++)
			hx[n]+=w[n][i]*num[i];
	}

	double maxval=hx[0];
	int number=0;
	for(n=1;n<10;n++)//取判别函数最大值
	{
		if(hx[n]>maxval)
		{
			maxval=hx[n];
			number=n;
		}
	}
	return number;
}

/******************************************************************
*   函数名称：LMSE()
*   函数类型：int 
*   函数功能：LMSE算法 ,返回手写数字的类别
******************************************************************/
int Classification::LMSE()
{
	double w[10][26];//权值
	double d[10];//迭代计算结果权矢量
	double x[26];//增1样品
	bool flag;
	int n,i,j,k;

	//权值初值为0
	for(n=0;n<10;n++)
		for(i=0;i<26;i++)
			w[n][i]=0;
	int c=0,cc=1;
	do
	{
		flag=true;
		for(n=0;n<10;n++)
		{
				for(i=0;i<40;i++)//for(i=0;i<pattern[n].number;i++)
			{
				//取已知样品
				for(j=0;j<25;j++)
					x[j]=pattern[n].feature[i][j];
				x[25]=1;//末位置1
				//计算结果权矢量
				for(j=0;j<10;j++)
					d[j]=0;
				for(j=0;j<10;j++)
					for(k=0;k<26;k++)
						d[j]+=w[j][k]*x[k];
				bool f=true;
				//d[n]是否最大值？
				for(j=0;j<10;j++)
				{
					if(j!=n)
						f&=(d[n]>d[j])?true:false;
				}

				if(f)//若d[n]为最大值
					flag&=true;
				else
					flag&=false;

				for(j=0;j<10;j++)//改变权值，10个
				{
					double rX;
					if(j==n)//是当前类别
						rX=1.0;//r[X(k)]=1
					else
						rX=0.0;//r[X(k)]=0
					
					for(k=0;k<26;k++)
					{
						w[j][k]+=x[k]*(rX-d[j])/cc;
					}
				}
				++cc;
			}
		}
		if(++c>2000)break;
	}while(!flag);//到此为止得到线性判别函数权矢量
	
	double hx[10];
	double num[26];
	//取未知样品
	for(i=0;i<25;i++)
		num[i]=testsample[i];
	num[25]=1;//末位置1
	//计算判别函数
	for(n=0;n<10;n++)
	{
		hx[n]=0;
		for(i=0;i<26;i++)
			hx[n]+=w[n][i]*num[i];
	}
	//判别函数最大值
	double maxval=hx[0];
	int number=0;
	for(n=1;n<10;n++)
	{
		if(hx[n]>maxval)
		{
			maxval=hx[n];
			number=n;
		}
	}
	return number;
}

/******************************************************************
*   函数名称：Zengliangjiaozheng()
*   函数类型：int 
*   函数功能：增量校正算法 ,返回手写数字的类别
******************************************************************/
int Classification::Zengliangjiaozheng()
{
	double w[10][26];//权值
	double d[10];//迭代计算结果权矢量
	double x[26];//增1样品
	bool flag;
	int n,i,j,k;

	//权值初值为0
	for(n=0;n<10;n++)
		for(i=0;i<26;i++)
			w[n][i]=0;
	int c=0,cc=1;
	do
	{
		flag=true;
		for(n=0;n<10;n++)
		{
			for(i=0;i<10;i++)//	for(i=0;i<pattern[n].number;i++)
			{
				//取已知样品
				for(j=0;j<25;j++)
					x[j]=pattern[n].feature[i][j];
				x[25]=1;//末位置1
				//计算结果权矢量
				for(j=0;j<10;j++)
					d[j]=0;
				for(j=0;j<10;j++)
					for(k=0;k<26;k++)
						d[j]+=w[j][k]*x[k];
				bool f=true;
				//d[n]是否最大值？
				for(j=0;j<10;j++)
				{
					if(j!=n)
						f&=(d[n]>d[j])?true:false;
				}

				if(f)//若d[n]为最大值
					flag&=true;
				else//否则
					flag&=false;

				for(j=0;j<10;j++)
				{
					double rX;
					if(j==n)//是当前类别
						rX=1.0;//r[X(k)]=1
					else
						rX=0.0;//r[X(k)]=0

					if(d[j]<rX)//W(k)X(k)<r[X(k)]
					{
						for(k=0;k<26;k++)
							w[j][k]+=x[k]/cc;
					}
					else//W(k)X(k)≥r[X(k)]
					{
						for(k=0;k<26;k++)
							w[j][k]-=x[k]/cc;
					}
				}
				++cc;
			}
		}
		if(++c>2000)break;
	}while(!flag);//到此为止得到线性判别函数权矢量
	
	double hx[10];
	double num[26];
	//取未知样品
	for(i=0;i<25;i++)
		num[i]=testsample[i];
	num[25]=1;//末位置1
	//求判别函数
	for(n=0;n<10;n++)
	{
		hx[n]=0;
		for(i=0;i<26;i++)
			hx[n]+=w[n][i]*num[i];
	}
	//判别函数最大值
	double maxval=hx[0];
	int number=0;
	for(n=1;n<10;n++)
	{
		if(hx[n]>maxval)
		{
			maxval=hx[n];
			number=n;
		}
	}
	return number;
}

/******************************************************************
*   函数名称：ifClassified(int Class0,int Class1)
*   函数类型：CString
*   参数说明：int Class0,int Class1:要验证的两个类别
*   函数功能：用LMSE方法验证两类的可分性,返回每次迭代的权值
******************************************************************/
CString Classification::ifClassified(int Class0,int Class1)
{
	double X[60][26];//增1样品矩阵
	double Xsharp[26][60];//X的规范逆矩阵X#
	double w[26];//权值向量
	double Xw[60];//X*W
	double b[60];//向量
	double e[60];//向量
	bool flag;
	int c=1;//迭代次数
	CString str;
	CString s;
	CStdioFile cf;//文件
	int i,j;
	
	//增1样品矩阵的前30个取Class0的样品
	for(i=0;i<30;i++)
	{
		for(j=0;j<25;j++)
		{
			X[i][j]=pattern[Class0].feature[i][j];
		}
		X[i][25]=1;//最后一位取1
	}
	//增1样品矩阵的后30个取Class1的样品（取负）
	for(i=30;i<59;i++)
	{
		for(j=0;j<25;j++)
		{
			X[i][j]=-pattern[Class1].feature[i-30][j];
		}
		X[i][25]=-1;
	}
	//求X的规范逆矩阵X#
	guifanni(X,Xsharp);
	//b赋初值，b(1)={1,1,1,...,1}
	for(i=0;i<40;i++)
		b[i]=1;
	do
	{
		s.Format("第%d次迭代：										",c);
		str.Insert(str.GetLength(),s);
		brmul(Xsharp,b,w);//w=x#*b
		brmul(X,w,Xw);//x*w
		flag=true;
		for(i=0;i<40;i++)
		{
			e[i]=Xw[i]-b[i];
			flag&=e[i]<0?true:false;//e的分量是否全负？
			s.Format("%d,\t",e[i]);
			str.Insert(str.GetLength(),s);
		}
		if(!flag)//e的分量不是全负，调整b
		{
			for(i=0;i<40;i++)
				b[i]+=2*e[i];
		}
		if(++c>300) break;//迭代超过300次，退出。
	}while(!flag);
	//存入文件“lmse.txt”
	if(cf.Open("lmse.txt",CFile::modeCreate|CFile::modeWrite))
	{
		cf.WriteString(str);
		cf.Close();
	}
	return str;	
}


/******************************************************************
*   函数名称：Shihanshu()
*   函数类型：int 
*   函数功能：势函数分类法 ,返回手写数字的类别
******************************************************************/
int Classification::Shihanshu()
{
	int r[10][2000];//系数
	int x[2000][2];//样品
	double hx[10];//判别函数
	int i,j,k,n,c=0;

	for(k=0;k<10;k++)//循环10次
	{
		for(n=0;n<10;n++)//10个类别
		{
			for(i=0;i<20;i++)//每类取20个样品
			{
				if(c==0)
				{
					for(j=0;j<10;j++)
						r[j][0]=1;
				}
				else
				{
					for(j=0;j<10;j++)
					{
						double t=0.0;
						for(int l=0;l<c;l++)
							t+=r[j][l]*K(pattern[n].feature[i],pattern[x[l][0]].feature[x[l][1]]);
						hx[j]=t;
					}
					for(j=0;j<10;j++)
					{
						if(j==n)
						{
							if(hx[j]>0)//分类正确
								r[n][c]=0;
							else//分类错误
								r[n][c]=1;
						}
						else
						{
							if(hx[j]<0)//分类正确
								r[n][c]=0;
							else//分类错误
								r[n][c]=-1;
						}
					}
				}
				x[c][0]=n;
				x[c][1]=i;	
				c++;
			}
		}
	}

	for(j=0;j<10;j++)
	{
		double t=0.0;
		for(int l=0;l<200;l++)
			t+=r[j][l]*K(testsample,pattern[x[l][0]].feature[x[l][1]]);
		hx[j]=t;
	}
	
	double maxval=hx[0];
	int number=0;
	for(n=1;n<10;n++)
	{
		if(hx[n]>maxval)
		{
			maxval=hx[n];
			number=n;
		}
	}
	return number;	
}

/****************************************************************
*   函数名称：K(double X[], double Xk[])
*   函数类型：double 
*   参数说明：X[], Xk[]:两个样品的特征
*   函数功能：计算两个样品的势函数 ,返回两各样品的势函数函数值。
****************************************************************/
double Classification::K(double X[], double Xk[])
{
	double d=0.0;
	for(int i=0;i<25;i++)
		d+=(X[i]-Xk[i])*(X[i]-Xk[i]);
	return exp(-d);
}

/****************************************************************
*   函数名称：pipei(double s1[], double s2[])
*   函数类型：double 
*   参数说明：double s1[], double s2[]:两个样品的特征
*   函数功能：计算两个样品的匹配程度 ,返回两各样品的的匹配程度。
****************************************************************/
double Classification::pipei(double s1[], double s2[])
{
	double count=0.0;
	for(int i=0;i<25;i++)
	{
		count+=(s1[i]-s2[i])*(s1[i]-s2[i]);
	}
	return count;
}
