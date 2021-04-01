#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<(b);++i)
#define per(i,a,b) for(int i=(b)-1;i>=(a);--i)
#define ll long long
#define lb(x) ((x)&-(x))
#define pii pair<int,int>
#define vi vector<int>
#define pb push_back
#define fi first
#define se second
#define de(x) cout<<#x<<" x"<<endl
#define LCAFA rep(i,1,20)rep(j,1,n+1)fa[j][i]=fa[fa[j][i-1]][i-1]
#define all(x) x.begin(),x.end()
#define ls(x) x<<1
#define rs(x) x<<1|1
#define pr(x) {for(auto v:x)cout<<v<<' ';cout<<#x<<endl;}
using namespace std;
const int N=6e6+5;
const ll mod=998244353;
const ll Inf=1e18;
int inv[N],sum[N];
int main(){
	inv[0]=1,inv[1]=1;
	rep(i,2,N)inv[i]=-mod/i*inv[mod%i]%mod+mod;
	rep(i,1,N){
		sum[i]=sum[i-1]+1ll*inv[i]*inv[i]%mod;
		if(sum[i]>=mod)sum[i]-=mod;
	}
	int T;
	scanf("%d",&T);
	while(T--){
		int n;
		scanf("%d",&n);
		ll ans=3ll*sum[n]*inv[n]%mod;
		printf("%lld\n",ans);
	}
} 

