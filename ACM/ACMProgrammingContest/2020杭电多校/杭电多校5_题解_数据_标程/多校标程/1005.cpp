#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define endl "\n"
typedef int ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

#define mem(a,x) memset(a,x,sizeof(a))
#define rep_it(it,x) for (__typeof((x).begin()) it=(x).begin(); it!=(x).end(); it++)
#define ____ puts("\n_______________\n\n") 
#define debug(x) ____; cout<< #x << " => " << (x) << endl
#define debug_pair(x) cout<<"\n{ "<<(x).fir<<" , "<<(x).sec<<" }\n"
#define debug_arr(x,n) ____; cout<<#x<<":\n"; rep(i,0,n+1) cout<<#x<<"["<<(i)<<"] => "<<x[i]<<endl
#define debug_arr2(x,n,m) ____; cout<<#x<<":\n"; rep(i,0,n+1) rep(j,0,m+1) cout<<#x<<"["<<(i)<<"]["<<(j)<<"]= "<<x[i][j]<<((j==m)?"\n\n":"    ")
#define debug_set(x) ____; cout<<#x<<": \n"; rep_it(it,x) cout<<(*it)<<" "; cout<<endl
#define debug_map(x) ____; cout<<#x<<": \n"; rep_it(it,x) debug_pair(*it)

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

const ll P=998244353;

const int _N=1000005; ll inv[_N<<2],fac[_N<<2],fac_inv[_N<<2];
inline ll add(ll x,ll y) { x+=y; return x%P; }
inline ll mul(ll x,ll y) { return (long long)x*y%P; }
inline ll Pow(ll x,ll k) { ll ans=1; for (;k;k>>=1,x=(long long)x*x%P) if (k&1) ans=(long long)ans*x%P; return ans; } 
inline void init_inv(int n) { inv[1]=1; rep(i,2,n+1) inv[i]=mul(P-P/i,inv[P%i]); }
inline void init_fac(int n) { 
	fac[0]=fac_inv[0]=1; 
	rep(i,1,n+1) fac[i]=mul(fac[i-1],i),fac_inv[i]=mul(fac_inv[i-1],inv[i]); 
}

template <class V>
struct FT{
	int n,nn; V w[2][_N<<2],rev[_N<<2],tmp;
	inline int init_len(int _n) { for (n=1; n<=_n; n<<=1); return n; }
	inline int Init(int _n) {
		init_len(_n); if (n==nn) return n; nn=n;
		V w0=Pow(3,(P-1)/n); w[0][0]=w[1][0]=1;
		rep(i,1,n) w[0][i]=w[1][n-i]=mul(w[0][i-1],w0);
		rep(i,0,n) rev[i]=(rev[i>>1]>>1)|((i&1)*(n>>1)); return n;
	}
	void FFT(V A[],int op){
		rep(i,0,n) if (i<rev[i]) swap(A[i],A[rev[i]]);
		for (int i=1; i<n; i<<=1)
			for (int j=0,t=n/(i<<1); j<n; j+=i<<1)
				for (int k=j,l=0; k<j+i; k++,l+=t) {
					V x=A[k],y=mul(w[op][l],A[k+i]);
					A[k]=add(x,y),A[k+i]=add(x-y,P);
				}
		if (op) { tmp=inv[n]; rep(i,0,n) A[i]=mul(A[i],tmp); }
	}
};

template <class V>
struct Calculator{
	FT<V> T; V X[_N<<2],Y[_N<<2],A[_N<<2],B[_N<<2],C[_N<<2]; V AA[_N<<2],BB[_N<<2]; V AL[_N<<2],BL[_N<<2]; 
	inline void Fill(V a[],V b[],int n,int len) {
		if (a!=b) memcpy(a,b,sizeof(V)*n); fill(a+n,a+len,0);
	}
	inline void Dot_Mul(V a[],V b[],int len,V c[]) {
		rep(i,0,len) c[i]=mul(a[i],b[i]);
	}
	inline void Mul(V a[],int n,V b[],int m,V c[]) {
		int len=T.Init(n+m-1); Fill(X,a,n,len),Fill(Y,b,m,len);
		T.FFT(X,0),T.FFT(Y,0),Dot_Mul(X,Y,len,c),T.FFT(c,1);
	}
	inline void Int(V a[],int n,V b[]) {
		per(i,0,n) b[i+1]=mul(a[i],inv[i+1]); b[0]=0;
	}
	inline void Der(V a[],int n,V b[]) {
		rep(i,1,n) b[i-1]=mul(a[i],i); b[n-1]=0;
	}
	inline void Inv(V a[],int n,V b[]) {
		if (n==1) { b[0]=Pow(a[0],P-2),b[1]=0; return; }
		Inv(a,(n+1)>>1,b); int len=T.Init(2*n-1);
		Fill(X,a,n,len),Fill(b,b,n,len),T.FFT(X,0),T.FFT(b,0);
		rep(i,0,len) b[i]=mul(b[i],2-mul(b[i],X[i]));
		T.FFT(b,1),Fill(b,b,n,len);
	}
	inline void Log(V a[],int n,V b[]) {
		Der(a,n,AL),Inv(a,n,BL),Mul(AL,n,BL,n,b);
		Int(b,n,b),Fill(b,b,n,T.n);
	}
	inline void To_egf(V a[],int n,V b[]) { Dot_Mul(a,fac,n,b); }
	inline void To_ogf(V a[],int n,V b[]) { Dot_Mul(a,fac_inv,n,b); }
	inline void Bin_Mul(V a[],int n,V b[],int m,V c[]) {
		To_ogf(a,n,AA),To_ogf(b,m,BB),Mul(AA,n,BB,m,c),To_egf(c,T.n,c);
	}
	inline void Bin_Log(V a[],int n,V c[]) {
		To_ogf(a,n,AA),Log(AA,n,c),To_egf(c,n,c);
	}
};

ll C(int n,int m) {
	if (n<m || n<0 || m<0) return 0;
	return mul(mul(fac[n],fac_inv[m]),fac_inv[n-m]); 
}

Calculator<ll> T;

// ll ret[_N],ans[_N],a[_N],b[_N],c[_N],S[_N];
int n,nn; ll a[_N<<2],b[_N<<2],f[_N<<2]; 

/*
ll g[_N],s[_N],tmp[_N];
ll AA=0,BB=0;
*/

int main() {
	//file_put();
	
	init_inv((_N<<2)-1);
	init_fac((_N<<2)-1);
	
	
	scanf("%d",&nn),++nn;
	rep(i,0,nn) a[i]=Pow(i,i);
	T.Bin_Log(a,nn,b),T.Bin_Mul(a,nn,b,nn,f);
	rep(n,1,nn) {
		ll ans=(mul(n,Pow(1-inv[n],n))+P)%P;
		ll ret=(mul(Pow(inv[n],n),f[n])+P)%P;
		ll ans1=(n-ret+P)%P, ans2=(n-ret+ans+P)%P;
		printf("0 %d %d\n",ans1,ans2);
	}
	
	
	
	
	
	/*
	
	scanf("%d",&nn),++nn;
	rep(i,0,nn) a[i]=Pow(i,i);
	T.Bin_Log(a,nn,b),T.Bin_Mul(a,nn,b,nn,f);
	rep(n,1,nn) {
		ll ans=(mul(n,Pow(1-inv[n],n))+P)%P;
		ll ret=(mul(Pow(inv[n],n),f[n])+P)%P;
		ll ans1=(n-ret+P)%P, ans2=(n-ret+ans+P)%P;
		//printf("0 %lld %lld\n",ans1,ans2);
		AA^=ans1^ans2;
	}
	
	
	
	s[0]=1;
	rep(k,1,nn) {
		T.Bin_Mul(b,nn,s,nn,s);
		T.Add(g,nn,s,nn,g,fac_inv[k-1]);
	}
	rep(n,1,nn) {
		ll ans=(mul(n,Pow(1-inv[n],n))+P)%P;
		ll ret=(mul(Pow(inv[n],n),g[n])+P)%P;
		ll ans1=(n-ret+P)%P, ans2=(n-ret+ans+P)%P;
		//printf("0 %lld %lld\n",ans1,ans2);
		BB^=ans1^ans2;
	}
	
	printf("%lld\n",AA);
	printf("%lld\n",BB);
	*/
	
	
	
	
	/*
	
	scanf("%d",&n);
	rep(i,0,n+1) a[i]=Pow(i,i);
	//debug_arr(a,n);
	T.To_ogf(a,n+1,b);
	//debug_arr(b,n);
	
	T.Log(b,n+1,c);
	//debug(233);
	//debug_arr(c,n);
	T.To_egf(c,n+1,ans);
	rep(k,1,n+1) {
		rep(i,1,k) ret[k]=add(ret[k],mul(mul(C(k,i),fac[i]),Pow(k,k-i-1)));
		ret[k]=add(ret[k],fac[k-1]);
	}
	
	debug_arr(ans,n);
	debug_arr(ret,n);
	
	
	*/
	
	
	
	
	
	/*
	scanf("%d",&n);
	
	T.Init_Stiriling_Num_2_H_B(S,n+1,n);
	//debug_arr(S,n);
	
	ll ans=(mul(n,1-Pow(1-inv[n],n))+P)%P;
	ll ret=0;
	rep(k,1,n+1) ret=add(ret,mul(mul(mul(mul(k,C(n,k)),S[k]),fac[k]),Pow(inv[n],n)));
	debug(ans);
	debug(ret); 
	*/
	
	
	
	return 0;
}




