#include<bits/stdc++.h>
#define rep(i,a,b) for (int i=(a); i<=(b); i++)
#define per(i,a,b) for (int i=(a); i>=(b); i--)
using namespace std;
typedef long long ll;
template<class T> inline void read(T &x){
	x=0; char c=getchar(); int f=1;
	while (!isdigit(c)) {if (c=='-') f=-1; c=getchar();}
	while (isdigit(c)) {x=x*10+c-'0'; c=getchar();} x*=f;
}
const int N = 1<<22|3, mo = 998244353, inv2 =(mo+1)/2;
const ll MOD=7LL*mo*mo;
inline void add(int &x, int y){x=x+y<mo?x+y:x+y-mo;}
inline void sub(int &x, int y){x=x-y>=0?x-y:x-y+mo;}
inline int power(int a, int n) {
	int res=1;
	while (n) {
		if (n&1) res=1LL*res*a%mo;
		a=1LL*a*a%mo; n>>=1;
	}
	return res;
}

int fac[N],ifac[N],n,c,p,q,f[N],ans[N],w[N];
void iniC(int n){
	fac[0]=1;rep(i,1,n)fac[i]=1LL*fac[i-1]*i%mo;
	ifac[n]=power(fac[n],mo-2);
	per(i,n-1,0)ifac[i]=1LL*ifac[i+1]*(i+1)%mo;
}
inline int C(int n, int m){return m>=0&&m<=n?1LL*fac[n]*ifac[m]%mo*ifac[n-m]%mo:0;}
inline void exgcd(int a, int b, int &x, int &y) {
	if (!b) {x=1; y=0; return;}
	exgcd(b,a%b,y,x); y-=a/b*x;
}
inline int inv(int a) {int x,y; exgcd(a,mo,x,y); return x>=0 ? x : x+mo;}
inline void fft(int *a, int n, int tp) {
	for (int i=1,j=0; i<n; i++) {
		for (int k=n>>1; !((j^=k)&k); k>>=1);
		if (i<j) swap(a[i],a[j]);
	}
	for (int j=2; j<=n; j<<=1) {
		w[0]=1; w[1]=power(3,(mo-1)/j); w[1]=tp==1?w[1]:inv(w[1]); int m=(j>>1)-1; //mo-1
		rep(i,2,m) w[i]=1LL*w[i-1]*w[1]%mo;
		for (int i=0; i<n; i+=j) rep(k,0,m) {
			int x=1LL*a[i+k+(j>>1)]*w[k]%mo;
			a[i+k+(j>>1)]=a[i+k]-x>=0?a[i+k]-x:a[i+k]-x+mo;
			a[i+k]=a[i+k]+x<mo?a[i+k]+x:a[i+k]+x-mo;
		}
	}
}
inline void mul(int *a, int *b, int n1, int n2, int *c){
	int n;for(n=1;n<=n1+n2-2;n<<=1);
	fft(a,n,1);fft(b,n,1);rep(i,0,n-1)a[i]=1LL*a[i]*b[i]%mo;
	int ni=inv(n);fft(a,n,-1);rep(i,0,n-1)c[i]=1LL*a[i]*ni%mo;
}
int a[N],b[N],miq[N];
int main() {//freopen("1.in","r",stdin);freopen("1.out","w",stdout);
	iniC(N-1);int T;read(T);while(T--){
		int A,B;
		read(n);read(A);read(B);read(c);p=1ll*A*power(B,mo-2)%mo;q=(1+mo-p)%mo;
		rep(i,0,n<<2)miq[i]=a[i]=b[i]=f[i]=ans[i]=w[i]=0;
		miq[0]=1;rep(i,1,n)miq[i]=1ll*miq[i-1]*q%mo;
		f[0]=1;
		rep(i,0,n-1)f[i+1]=(1ll*((1ll*(c-1)*q+n-c-1ll*(q+1)*i)%mo*f[i]+1ll*q*(n-i)%mo*(i?f[i-1]:0))%mo*ifac[i+1]%mo*fac[i]%mo+mo)%mo;
		rep(i,0,n-1)f[i]=1ll*f[i]*power(1-miq[i+1]+mo,mo-2)%mo;
		rep(i,0,n-1)a[n-i-1]=1ll*f[i]*fac[i]%mo,b[i]=i&1?mo-ifac[i]:ifac[i];
		mul(a,b,n,n,ans);
		rep(i,0,n-1)ans[n-1-i]=1ll*ans[n-1-i]*ifac[i]%mo;
		rep(i,0,n-1)ans[i]=1ll*ans[i]*p%mo;
		rep(i,1,n)printf("%d\n",ans[i-1]);
	}
	return 0;
}