#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int>pii;
typedef vector<int>vi;

#define rep(i,a,b) for(int i=(a);i<(b);i++)
#define fi first
#define se second
#define de(x) cout<<#x<<"="<<x<<"\n"
#define dd(x) cout<<#x<<"="<<x<<" "
#define pb(x) push_back(x)
#define all(x) x.begin(),x.end()
#define sz(x) (int)x.size()
#define lowbit(a) ((a)&-(a))
#define per(i,a,b) for(int i=(b)-1;i>=(a);--i)
const int N=5e6+5;
const int mod = 998244353;
int qpow(int x,int n){
	int res = 1;
	while(n){
		if(n&1)res = (ll)res*x%mod;
		x = (ll)x*x%mod;
		n>>=1;
	}
	return res;
}
int n,f[N],invf[N],ans[N];
inline int add(int a,int b){
	return a + b >= mod?a + b - mod:a + b;
}
void init(){
	f[0] = invf[0] = 1;
	rep(i , 1 , N)f[i] = (ll)i*f[i - 1]%mod;
	invf[N - 1] = qpow(f[N - 1],mod - 2);
	for(int i = N - 2;i >= 1;--i)invf[i] = (ll)(i + 1)*invf[i + 1]%mod;
}
int comb(int n,int m){
	return (ll)f[n]*invf[m]%mod*invf[n-m]%mod;
}
int gao(int k){
	int l = k - 1,r = n - k;
	int res = comb(l , r);
	res = (ll)res*f[r]%mod;
	if(l > r){
		int cc = qpow(2,mod - 2);
		cc = qpow(cc , (l - r)/2);
		res = (ll)res*cc%mod*f[l - r]%mod;
		res = (ll)res*invf[(l - r)/2]%mod;
	}
	return res;
}
int main()
{
	init();
	int TT;
	scanf("%d",&TT);
	while(TT--){
		scanf("%d",&n);
		rep(i , 1 , n + 1)ans[i] = 0;
		ll sum = 0;
		rep(i , (n + 1)/2 , n + 1){
			ans[i] = gao(i);
			sum = add(ans[i],sum);
		}
		sum = qpow(sum,mod - 2);
		rep(i , 1 , n + 1)ans[i] = (ll)ans[i]*sum%mod;
		rep(i , 1 , n + 1){
			printf("%d",ans[i]);
			if(i == n)printf("\n");
			else printf(" ");
		}
	}
	return 0;
}


