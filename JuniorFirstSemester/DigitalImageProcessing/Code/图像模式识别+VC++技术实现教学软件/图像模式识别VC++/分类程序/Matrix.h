//matrix.h//////////////////////////////////////////////////////////////////
// 2005.1.13－16：02 By Superman 

#include "math.h"

/******************************************************************
*函数名称：bsdet(double a[],int n)
*函数类型：double
*参数说明：a--双精度实型数组，n--整型变量，方阵A的阶数
*函数功能：用全选主元高斯（Gauss）消去法计算n阶方阵A所对应的行列式值。
******************************************************************/
double bsdet(double a[],int n)
{ 
	int i,j,k,is,js,l,u,v;
	double f,det,q,d;
	f=1.0; det=1.0;
	for (k=0; k<=n-2; k++)
	{ 
		q=0.0;
		for (i=k; i<=n-1; i++)
		for (j=k; j<=n-1; j++)
		{ 
			l=i*n+j; d=fabs(a[l]);
			if (d>q) 
			{ 
				q=d; is=i; js=j;
			}
		}
		if (q+1.0==1.0)
		{ 
			det=0.0; return(det);
		}
		if (is!=k)
		{ 
			f=-f;
			for (j=k; j<=n-1; j++)
			{ 
				u=k*n+j; v=is*n+j;
				d=a[u]; a[u]=a[v]; a[v]=d;
			}
		}
		if (js!=k)
		{ 
			f=-f;
			for (i=k; i<=n-1; i++)
			{ 
				u=i*n+js; v=i*n+k;
				d=a[u]; a[u]=a[v]; a[v]=d;
			}
		}
		l=k*n+k;
		det=det*a[l];
		for (i=k+1; i<=n-1; i++)
		{ 
			d=a[i*n+k]/a[l];
			for (j=k+1; j<=n-1; j++)
			{ 
				u=i*n+j;
				a[u]=a[u]-d*a[k*n+j];
			}
		}
	}
	det=f*det*a[n*n-1];
	return(det);
}

/******************************************************************
*函数名称：brinv(double a[],int n)
*函数类型：void
*参数说明：a--双精度实型数组，n--整型变量，方阵A的阶数
*函数功能：用全选主元Gauss-Jordan消去法求n阶实矩阵A的逆矩阵
******************************************************************/
void brinv(double a[],int n)
{ 
	int *is,*js,i,j,k,l,u,v;
    double d,p;
    is=new int[n];
    js=new int[n];
    for (k=0; k<=n-1; k++)
	{ 
		d=0.0;
        for (i=k; i<=n-1; i++)
			for (j=k; j<=n-1; j++)
			{ 
				l=i*n+j; p=fabs(a[l]);
				if (p>d) 
				{ 
					d=p; is[k]=i; js[k]=j;
				}
			}
			if (d+1.0==1.0)
			{ 
				free(is); free(js); printf("err**not inv\n");
				return;
			}
			if (is[k]!=k)
				for (j=0; j<=n-1; j++)
				{ 
					u=k*n+j; v=is[k]*n+j;
					p=a[u]; a[u]=a[v]; a[v]=p;
				}
				if (js[k]!=k)
					for (i=0; i<=n-1; i++)
					{ 
						u=i*n+k; v=i*n+js[k];
						p=a[u]; a[u]=a[v]; a[v]=p;
					}
					l=k*n+k;
					a[l]=1.0/a[l];
					for (j=0; j<=n-1; j++)
						if (j!=k)
						{
							u=k*n+j; a[u]=a[u]*a[l];
						}
						for (i=0; i<=n-1; i++)
							if (i!=k)
								for (j=0; j<=n-1; j++)
									if (j!=k)
									{ 
										u=i*n+j;
										a[u]=a[u]-a[i*n+k]*a[k*n+j];
									}
									for (i=0; i<=n-1; i++)
										if (i!=k)
										{
											u=i*n+k; a[u]=-a[u]*a[l];
										}
	}
    for (k=n-1; k>=0; k--)
	{ 
		if (js[k]!=k)
			for (j=0; j<=n-1; j++)
            { 
				u=k*n+j; v=js[k]*n+j;
				p=a[u]; a[u]=a[v]; a[v]=p;
            }
			if (is[k]!=k)
				for (i=0; i<=n-1; i++)
				{ 
					u=i*n+k; v=i*n+is[k];
					p=a[u]; a[u]=a[v]; a[v]=p;
				}
	}
    delete is; 
	delete js;
}

/******************************************************************
*函数名称：brmul(double a[],double b[][25],int n,double c[])
*函数类型：void
*参数说明：a－双精度实型数组，存放A的元素。
*          b－双精度实型数组，存放B的元素。
*          n－整型变量，矩阵A的列数，也是矩阵B的行数。
*          c－双精度实型数组，存放乘积矩阵C=AB的元素。
*函数功能：求矩阵A与B的乘积矩阵C=AB。
******************************************************************/
void brmul(double a[],double b[][25],int n,double c[])//矩阵乘法，c=a*b
{ 
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			c[i]+=a[j]*b[j][i];
	}
	return;
}

/******************************************************************
*函数名称：brmul(double a[][25],double b[],int n,double c[]
*函数类型：void
*参数说明：a－双精度实型数组，存放A的元素。
*          b－双精度实型数组，存放B的元素。
*          n－整型变量，矩阵A的列数，也是矩阵B的行数。
*          c－双精度实型数组，存放乘积矩阵C=AB的元素。
*函数功能：求矩阵A与B的乘积矩阵C=AB。
******************************************************************/
void brmul(double a[][25],double b[],int n,double c[])  
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			c[i]+=a[i][j]*b[i];
	}
	return;
}

/******************************************************************
*函数名称：brmul(double a[26][60],double b[60],double c[26])  
*函数类型：void
*参数说明：a－双精度实型数组，存放A的元素。
*          b－双精度实型数组，存放B的元素。
*          c－双精度实型数组，存放乘积矩阵C=AB的元素。
*函数功能：求矩阵A与B的乘积矩阵C=AB。
******************************************************************/
void brmul(double a[26][60],double b[60],double c[26])  
{
	for(int i=0;i<26;i++)
	{
		c[i]=0.0;
		for(int j=0;j<60;j++)
			c[i]+=a[i][j]*b[j];
	}
	return;
}

/******************************************************************
*函数名称：brmul(double a[60][26],double b[26],double c[60])  
*函数类型：void
*参数说明：a－双精度实型数组，存放A的元素。
*          b－双精度实型数组，存放B的元素。
*          c－双精度实型数组，存放乘积矩阵C=AB的元素。
*函数功能：求矩阵A与B的乘积矩阵C=AB。
******************************************************************/
void brmul(double a[60][26],double b[26],double c[60])  
{
	for(int i=0;i<60;i++)
	{
		c[i]=0.0;
		for(int j=0;j<26;j++)
			c[i]+=a[i][j]*b[j];
	}
	return;
}

/******************************************************************
*函数名称：brmul(double a[],double b[][5],int n,double c[])
*函数类型：void
*参数说明：a－双精度实型数组，存放A的元素。
*          b－双精度实型数组，存放B的元素。
*          n－整型变量，矩阵A的列数，也是矩阵B的行数。
*          c－双精度实型数组，存放乘积矩阵C=AB的元素。
*函数功能：求矩阵A与B的乘积矩阵C=AB。
******************************************************************/
void brmul(double a[],double b[][5],int n,double c[])
{ 
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			c[i]+=a[j]*b[j][i];
	}
	return;
}

/******************************************************************
*函数名称：brmul(double a[],double b[][9],int n,double c[])
*函数类型：void
*参数说明：a－双精度实型数组，存放A的元素。
*          b－双精度实型数组，存放B的元素。
*          n－整型变量，矩阵A的列数，也是矩阵B的行数。
*          c－双精度实型数组，存放乘积矩阵C=AB的元素。
*函数功能：求矩阵A与B的乘积矩阵C=AB。
******************************************************************/
void brmul(double a[],double b[][9],int n,double c[])
{ 
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			c[i]+=a[j]*b[j][i];
	}
	return;
}

/******************************************************************
*函数名称：brmul(double a[],double b[],int n)
*函数类型：double
*参数说明：a－双精度实型一维数组，存放行矩阵A的元素。
*          b－双精度实型一维数组，存放列矩阵B的元素。
*          n－整型变量，矩阵A的列数，也是矩阵B的行数。
*函数功能：求行矩阵A与列矩阵B的乘积，结果为一双精度的数。
******************************************************************/
double brmul(double a[],double b[],int n)
{
	double temp=0;
	for(int i=0;i<n;i++)
		temp+=a[i]*b[i];
	return temp;
}

/******************************************************************
*函数名称：guifanni(double a[60][26],double b[26][60])
*函数类型：void
*参数说明：a－双精度实型二维数组，存放矩阵A的元素。
*          b－双精度实型二维数组，存放矩阵B的元素。
*函数功能：求矩阵A的规范逆矩阵B，结果存放在b中。
******************************************************************/
void guifanni(double a[60][26],double b[26][60])
{
	double aT[26][60];//a转置
	double aTa[26][26];
	double aTa_[26][26];
	int i,j,k;

	for(i=0;i<60;i++)
	{
		for(j=0;j<26;j++)
		{
			aT[j][i]=a[i][j];
		}
	}

	for(i=0;i<26;i++)
	{
		for(j=0;j<26;j++)
		{
			double temp=0;
			for(k=0;k<60;k++)
			{
				temp+=aT[i][k]*a[k][j];
			}
			aTa[i][j]=temp;
			aTa_[i][j]=temp;
		}
	}
	
	double(*p)[26]=aTa_;
	brinv(*p,26);

	for(i=0;i<26;i++)
	{
		for(j=0;j<60;j++)
		{
			double temp=0;
			for(k=0;k<26;k++)
			{
				temp+=aTa_[i][k]*aT[k][j];
			}
			b[i][j]=temp;
		}
	}
}
