#include<bits/stdc++.h>
using namespace std;

#define rep(i,n) for(int i=0;i<(n);i++)
#define REP(i,n) for(int i=1;i<=(n);i++)
#define mp make_pair
#define pb push_back
#define fst first
#define snd second
typedef long long ll;
typedef pair<int,int> pii;
typedef double db;

const int maxn=105;
const int maxm=10005;
int test,n;
int a[maxn];
int f[maxn][maxm],val[maxn][maxm];
db g[2][maxn][maxm],c[maxn][maxn];
vector<int>num;
bool vis[100005];

int gcd(int a,int b){
	return !b?a:gcd(b,a%b);
}

void dfs(int x){
	if(vis[x])return;
	vis[x]=true;
	num.pb(x);
	rep(i,n)dfs(gcd(x,a[i]));
}

int main(){
	scanf("%d",&test);
	while(test--){
		scanf("%d",&n);
		int gg=0;
		rep(i,n){
			scanf("%d",&a[i]);
			gg=gcd(gg,a[i]);
		}
		if(gg>1){
			if(n&1)puts("1.0000");
			else puts("0.0000");
			continue;
		}
		num.clear();
		dfs(0);
		sort(num.begin(),num.end());
		int sz=int(num.size());
		rep(i,sz)vis[num[i]]=false;
		rep(i,n)rep(j,sz){
			int x=gcd(a[i],num[j]);
			val[i][j]=lower_bound(num.begin(),num.end(),x)-num.begin();
		}
		rep(i,n+1)rep(j,sz)f[i][j]=0;
		for(int i=n;i>=0;i--)rep(j,sz){
			if(j==1)f[i][j]=1;
			else if(i==n)f[i][j]=0;
			else{
				int c=0;
				rep(k,n){
					if(j&&a[k]%num[j]==0)c++;
					else f[i][j]|=(f[i+1][val[k][j]]==0);
				}
				if(c>i)f[i][j]|=(f[i+1][j]==0);
			}
		}
		rep(i,2)rep(j,n+1)rep(k,sz)g[i][j][k]=0;
		int z=0;
		g[z][0][0]=1;
		rep(i,n){
			rep(j,n+1)rep(k,sz){
				g[z^1][j][k]+=g[z][j][k];
				if(k!=1)g[z^1][j+1][val[i][k]]+=g[z][j][k];
				g[z][j][k]=0;
			}
			z^=1;
		}
		rep(i,n+1)c[i][0]=1;
		REP(i,n)REP(j,n)c[i][j]=c[i-1][j-1]+c[i-1][j];
		db ans=0,tot=0;
		rep(i,n)rep(j,sz)if(j!=1){
			rep(k,n)if(val[k][j]==1){
				if((i+1)%2==0)ans+=g[z][i][j]/c[n][i]/(n-i);
			}
		}
		printf("%.9lf\n",ans);
	}
	return 0;
}
