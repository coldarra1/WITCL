#include"stdio.h"
#include"time.h"

double Surplus(double A[],int m,int n) /*求矩阵行列式*/ 
{ 
	
	int i,j,k,p,r; 
	double X,temp=1,temp1=1,s=0,s1=0; 
	
	if(n==2) 
	{for(i=0;i<m;i++) 
	for(j=0;j<n;j++) 
		if((i+j)%2) temp1*=A[i*n+j]; 
		else temp*=A[i*n+j]; 
		X=temp-temp1;} 
	else{ 
		for(k=0;k<n;k++) 
		{for(i=0,j=k;i<m,j<n;i++,j++) 
		temp*=A[i*n+j]; 
		if(m-i) 
		{for(p=m-i,r=m-1;p>0;p--,r--) 
		temp*=A[r*n+p-1];} 
		s+=temp; 
		temp=1; 
		} 
		
		for(k=n-1;k>=0;k--) 
		{for(i=0,j=k;i<m,j>=0;i++,j--) 
		temp1*=A[i*n+j]; 
		if(m-i) 
		{for(p=m-1,r=i;r<m;p--,r++) 
		temp1*=A[r*n+p];} 
		s1+=temp1; 
		temp1=1; 
		} 
		
		X=s-s1;} 
	return X; 
} 
double * MatrixInver(double A[],int m,int n) /*矩阵转置*/ 
{ 
	int i,j; 
	double *B=NULL; 
	B=(double *)malloc(m*n*sizeof(double)); 
	
	for(i=0;i<n;i++) 
	{
		for(j=0;j<m;j++) 
			B[i*m+j]=A[j*n+i]; 
	}
	return B; 
} 
double * MatrixOpp(double A[],int m,int n) /*逆矩阵*/
{ 
	int i,j,x,y,k; 
	double *SP=NULL,*AB=NULL,*B=NULL,X,*C; 
	SP=(double *)malloc(m*n*sizeof(double)); 
	AB=(double *)malloc(m*n*sizeof(double)); 
	B=(double *)malloc(m*n*sizeof(double)); 
	
	X=Surplus(A,m,n); 
	X=1/X; 
	
	for(i=0;i<m;i++) 
	{ 
		for(j=0;j<n;j++) 
		{
			for(k=0;k<m*n;k++) 
				B[k]=A[k]; 
			{
				for(x=0;x<n;x++) 
					B[i*n+x]=0; 
				for(y=0;y<m;y++) 
					B[m*y+j]=0; 
				B[i*n+j]=1; 
				SP[i*n+j]=Surplus(B,m,n); 
				AB[i*n+j]=X*SP[i*n+j]; 
			} 
		}
	}
	C=MatrixInver(AB,m,n); 
	
	return C; 
}

double * MatrixMul(double A[],double B[],int m,int n,int p) /*矩阵相乘*/ 
// A:m×n  B:n×p  C:m×p  C等于A乘以B
{ 
	int i,j,k; 
	double *C=NULL; 
	C=(double*)malloc(m*p*sizeof(double)); 
	
	for(i=0;i<m;i++) 
		for(j=0;j<p;j++) 
		{   C[i*p+j]=0;
			for(k=0;k<n;k++)
				C[i*p+j]=C[i*p+j]+A[i*n+k]*B[k*p+j]; 
		}

	return C; 
} 

double * MatrixMulNum(double A[],int m,int n,double num) /*矩阵数乘*/ 
// A:m×n, m行n列
{ 
	int i,j; 
	double *C=NULL; 
	C=(double*)malloc(m*n*sizeof(double)); 	
	for(i=0;i<m;i++) 
		for(j=0;j<n;j++) 
		  C[i*n+j]=num*A[i*n+j];
	return C; 
}

double * MatrixAdd(double A[],double B[],int m,int n) /*矩阵相加*/ 
// A:m×n  B:m×n C:m×n  C等于A加B
{ 
	int i,j; 
	double *C=NULL; 
	C=(double*)malloc(m*n*sizeof(double)); 	
	for(i=0;i<m;i++) 
		for(j=0;j<n;j++) 
		   C[i*n+j]=A[i*n+j]+B[i*n+j];		
	return C; 
} 

double * MatrixSub(double A[],double B[],int m,int n) /*矩阵相减*/ 
// A:m×n  B:m×n C:m×n  C等于A减B
{ 
	int i,j; 
	double *C=NULL; 
	C=(double*)malloc(m*n*sizeof(double)); 	
	for(i=0;i<m;i++) 
		for(j=0;j<n;j++) 
		   C[i*n+j]=A[i*n+j]-B[i*n+j];		
	return C; 
} 

double Matrix2Num(double A[])/*将一行一列的矩阵A转化为数*/
{
	return A[0];
}

double * MatrixRand(int m,int n)/*用(-1,1)之间的随机数生成填充一个m×n的矩阵*/
{   int i,j;
    double* C=NULL;
	C=(double*)malloc(m*n*sizeof(double));
	srand((unsigned)(time(NULL)));
    for (i=0;i<m;i++) 
	{
		for (j=0;j<n;j++) 
		{
			//rand()函数产生的随机数是整数，所以需要将之做适当的变换，变到-1～1之间
			C[i*n+j]= (double)(rand())/(32767/2) - 1;
		}
	}
	return C;	
}

double ABS(double a) /*返回a的绝对值*/
{  if(a>=0) return a;
   else return -a;
}

int* Rand2(int a,int b)/*产生b个0到a-1的随机数*/
{   int i;
    int* C=NULL;C=(int*)malloc(b*sizeof(int));
	srand((unsigned)(time(NULL)));
	for (i=0;i<b;i++) 
		{
			//rand()函数产生的随机数是整数，所以需要将之做适当的变换，变到0到a-1之间
			C[i]=int(a*rand()/32767);
		}
	return C;
}
