#include <bits/stdc++.h>
#define M 100005
using namespace std;
const int P=998244353;
#define calc(x,y) x=((y)+(x))%P
void Mul(int &x,int y){
	x=1LL*x*y%P;
}
int qikpow(int a,int b){
	int ret=1;
	for(;b;b>>=1,Mul(a,a))
		if(b&1)Mul(ret,a);
	return ret;
}
const int N=1<<20;
int rev[N];
const int g_=3;
const int g_inv=qikpow(g_,P-2);
void DFT(int *A,int n,int fl){
	for(int i=0;i<n;i++)
		if(i<rev[i])swap(A[i],A[rev[i]]);
	static int W[N];W[0]=1;
	for(int k=1;k<<1<=n;k<<=1){
		int Wn=qikpow(!fl?g_:g_inv,(P-1)/(k<<1)),L,t;
		for(int i=k-2;i>=0;i-=2)W[i+1]=1LL*(W[i]=W[i>>1])*Wn%P;
		for(int i=0;i<n;i+=k<<1)
			for(int j=0;j<k;j++){
				L=A[i+j],t=1LL*A[i+j+k]*W[j]%P;
				A[i+j]=(L+t)%P,A[i+j+k]=(L-t+P)%P;
			}
	}
}
void Mul(vector<int> &F,vector<int> &G,vector<int> &Val){
	int lf=F.size(),lg=G.size(),m=0;for(;1<<m<lf+lg-1;m++);
	static int f[N],g[N];
	for(int i=0;i<1<<m;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<m-1);
	for(int i=0;i<lf;i++)f[i]=F[i];memset(f+lf,0,(1<<m)-lf<<2);
	for(int i=0;i<lg;i++)g[i]=G[i];memset(g+lg,0,(1<<m)-lg<<2);
	DFT(f,1<<m,0),DFT(g,1<<m,0);
	for(int i=0;i<1<<m;i++)Mul(f[i],g[i]);
	DFT(f,1<<m,1);
	F.clear(),G.clear();
	for(int i=0,INV=qikpow(1<<m,P-2);i<lf+lg-1;i++)Val.push_back(1LL*f[i]*INV%P);
}

vector<int>f[M<<2];
int V[M];
void Solve(int l,int r,int p){
	if(l==r){
		f[p].push_back(1);
		f[p].push_back(P-V[l]);
		return;
	}
	int mid=l+r>>1;
	Solve(l,mid,p<<1);
	Solve(mid+1,r,p<<1|1);
	Mul(f[p<<1],f[p<<1|1],f[p]);
}

void Rd(int &x){scanf("%d",&x);}
int n,m,K,A[M],Val[M];
void Ask_Inv(int *A,int n){
	static int Ans[N],tmp[N];
	Ans[0]=qikpow(A[0],P-2);
	for(int len=1,m=2;len<=n;len<<=1,m++){
		for(int i=0;i<1<<m;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<m-1);
		memcpy(tmp,A,len<<3),memset(tmp+(len<<1),0,len<<3);
		memset(Ans+len,0,len*3<<2),DFT(tmp,1<<m,0),DFT(Ans,1<<m,0);
		for(int i=0;i<1<<m;i++)Ans[i]=(2LL*Ans[i]+1LL*P*P-1LL*Ans[i]*Ans[i]%P*tmp[i])%P;
		DFT(Ans,1<<m,1);
		for(int i=0,Inv=qikpow(1<<m,P-2);i<len<<1;i++)Mul(Ans[i],Inv);
	}
	memcpy(A,Ans,n<<2);
}
void Solve(){
	f[1].clear();
	int tt=0;
	for(int i=1;i<=m;i++)calc(tt,Val[i]);
	for(int i=1;i<=n;i++)V[i]=(P+tt-Val[A[i]])%P;
	V[n+1]=tt;
	Solve(1,n+1,1);
	static int g[N];
	for(int i=0;i<=min(K,1+n);i++)g[i]=f[1][i];
	Ask_Inv(g,K+1);
	int ans=0;
	for(int i=0;i<=K;i++)calc(ans,g[i]);
	for(int i=1;i<=n;i++)Mul(ans,Val[A[i]]);
	printf("%d\n",ans);
	memset(g,0,K+1<<2);
}
int main(){
	while(Rd(n),Rd(m),Rd(K),n+m+K){
		for(int i=1;i<=n;i++)Rd(A[i]);
		for(int i=1;i<=m;i++)Rd(Val[i]);
		Solve();
	}
	return 0;
}	
