#include<bits/stdc++.h>
using namespace std;
#define Mod1(x) ((x>=P)&&(x-=P))
#define Mod2(x) ((x<0)&&(x+=P))

#define reg register
typedef long long ll;
#define rep(i,a,b) for(reg int i=a,i##end=b;i<=i##end;++i)
#define drep(i,a,b) for(reg int i=a,i##end=b;i>=i##end;--i)

const int K=20,N=(1<<K)|10,P=998244353;

int n,m,k,a[N],v[N],b[N];
int qpow(int x,int k=P-2) {
	int res=1;
	for(;k;k>>=1,x=1ll*x*x%P) if(k&1) res=1ll*res*x%P;
	return res;
}

typedef vector <int> Poly;
int Mod_Inv[N],w[N],rev[N];
void Init_w() {
	w[1<<(K-1)]=1;
	ll t=qpow(3,(P-1)>>K);
	rep(i,(1<<(K-1))+1,(1<<K)-1) w[i]=w[i-1]*t%P;
	drep(i,(1<<(K-1))-1,1) w[i]=w[i<<1];
	Mod_Inv[0]=Mod_Inv[1]=1;
	rep(i,2,(1<<K)) Mod_Inv[i]=1ll*(P-P/i)*Mod_Inv[P%i]%P;
}
int Init(int n){
	int R=1,cc=-1;
	while(R<n) R<<=1,cc++;
	rep(i,1,R-1) rev[i]=(rev[i>>1]>>1)|((i&1)<<cc);
	return R;
}

void NTT(int n,Poly &a,int f){
	if((int)a.size()<n) a.resize(n);
	rep(i,0,n-1) if(rev[i]<i) swap(a[i],a[rev[i]]);
	for(reg int i=1,c=1;i<n;i<<=1,++c) {
		int *e=w+i; 
		for(reg int l=0;l<n;l+=i*2) {
			for(reg int j=l;j<l+i;++j) {
				reg int t=1ll*a[j+i]*e[j-l]%P;
				a[j+i]=a[j]-t,Mod2(a[j+i]);
				a[j]+=t,Mod1(a[j]);
			}
		}
	}
	if(f==-1) {
		reverse(a.begin()+1,a.end());
		int Base=Mod_Inv[n];
		rep(i,0,n-1) a[i]=1ll*a[i]*Base%P;
	}
}

Poly operator * (Poly a,Poly b){
	int n=a.size()+b.size()-1,R=Init(n);
	NTT(R,a,1),NTT(R,b,1);
	rep(i,0,R-1) a[i]=1ll*a[i]*b[i]%P;
	NTT(R,a,-1),a.resize(n);
	return a;
}

Poly Inv(Poly a) {
	int n=a.size();
	if(n==1) return Poly{qpow(a[0],P-2)};
	Poly b=a; b.resize((n+1)/2),b=Inv(b);
	int R=Init(n*2);
	NTT(R,a,1),NTT(R,b,1);
	rep(i,0,R-1) a[i]=(2-1ll*a[i]*b[i]%P+P)*b[i]%P;
	NTT(R,a,-1),a.resize(n);
	return a;
}

// Solve(l,r)=
// \Pi(l,r) (1+b[i])
Poly Solve(int l,int r) {
	if(r-l+1<=50) {
		Poly res(r-l+2);
		res[0]=1;
		rep(i,l,r) drep(j,i-l+1,1) res[j]=(res[j]+1ll*res[j-1]*b[i])%P;
		return res;
	}
	int mid=(l+r)>>1;
	return Solve(l,mid)*Solve(mid+1,r);
}

/*

O(n*k) Version
int main(){
	while(~scanf("%d%d%d",&n,&m,&k)){
		int sum=0;
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=1;i<=m;i++) scanf("%d",&v[i]),sum=(sum+v[i])%P;
		memset(dp,0,sizeof dp),dp[0]=1;
		for(int i=1;i<=n;i++) dp[0]=1ll*dp[0]*v[a[i]]%P;
		for(int i=0;i<=n;i++) {
			int cur=(sum-v[a[i]]+P)%P;
			for(int j=1;j<=k;j++)dp[j]=(dp[j]+1ll*dp[j-1]*cur)%P;
		}
		int ans=0;
		for(int i=0;i<=k;i++)ans=(ans+dp[i])%Mod;
		printf("%d\n",ans);
	}
	return 0;
}
 */

int main(){
	// freopen("data1.in","r",stdin);
	// freopen("data1.out","w",stdout); 
	Init_w();
	while(scanf("%d%d%d",&n,&m,&k) && n){
		int sum=0,Base=1;
		rep(i,1,n) scanf("%d",a+i);
		rep(i,1,m) scanf("%d",v+i),sum+=v[i],Mod1(sum);
		rep(i,1,n) Base=1ll*Base*v[a[i]]%P;
		rep(i,0,n) b[i]=v[a[i]]-sum,Mod2(b[i]);
		Poly Res=Solve(0,n);
		Res.resize(k+1),Res=Inv(Res);
		int ans=0;
		rep(i,0,k) ans+=Res[i],Mod1(ans);
		printf("%lld\n",1ll*ans*Base%P);
	}
}
