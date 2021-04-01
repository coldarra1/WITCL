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
const int N=5e3+5;
const int mod = 998244353;
int qpow(int x,int n){
	int res = 1;
	while(n > 0){
		if(n&1)res = (ll)res*x%mod;
		x = (ll)x*x%mod;
		n >>= 1;
	}
	return res;
}
int n , k ;
int dp[N][N],sum[N],com[N][N],f[N],ans[N];
inline int add(int a,int b){
	return a + b >= mod?a + b - mod:a + b;
}
inline int mul(int a,int b){
	return (ll)a*b%mod;
}
void init(){
	com[0][0] = 1,f[0] = 1;
	rep(i , 1 , N){
		f[i] = mul(f[i - 1],i);
		rep(j , 0 ,i + 1){
			com[i][j] = com[i- 1][j];
			if(j > 0)com[i][j] = add(com[i][j],com[i - 1][j - 1]);
		}
	}
}
int main()
{
	init();
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		if(n%(k + 1) == 0){
			rep(i , 1 , n + 1){
				printf("0");
				if(i == n)printf("\n");
				else printf(" ");
			}
			continue;
		}	
		if(n < k + 1){
			rep(i , 1 , n + 1){
				printf("1");
				if(i == n)printf("\n");
				else printf(" ");
			}
			continue;
		}
		rep(i , 0 ,n + 1){
			sum[i] = ans[i] = 0;
			rep(j , 0 , n + 1)dp[i][j] = 0;
		} 
		dp[0][0] = 1;
		rep(i , 0 , n)
			rep(j , 0 , n + 1){
				if(j + k <= n - i - 1)dp[i + 1][j + k] = add(dp[i + 1][j + k],dp[i][j]);
				if(j > 0)dp[i + 1][j - 1] = add(dp[i + 1][j - 1],mul(dp[i][j],j));
			}
		int p = 0,r = n%(k + 1);
		rep(i , 1 , n - r + 1){
			int j = n - i - r;
			int now = mul(mul(dp[i][j],com[n - i - 1][j]),f[j]);
			p = add(p,now),ans[i + 1] = add(ans[i + 1],now);
			if(n - i - 2 >= j)sum[i] = add(sum[i],mul(mul(dp[i][j],f[j]),com[n - i - 2][j]));	
		}
		rep(i , 1 , n + 1)sum[i] = add(sum[i - 1],sum[i]);
		p = qpow(p , mod - 2);
		rep(i , 2 , n + 1)
			ans[i] = add(ans[i],sum[i - 2]);
		rep(i , 1 , n + 1){
			ans[i] = mul(ans[i],p);
		 	printf("%d",ans[i]);
		 	if(i == n)printf("\n");
			else printf(" ");
		}
	}
	return 0;
}


