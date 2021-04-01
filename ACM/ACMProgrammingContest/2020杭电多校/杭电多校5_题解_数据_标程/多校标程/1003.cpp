#include<bits/stdc++.h>
#define dd(x) cout<<#x<<" = "<<x<<" "
#define de(x) cout<<#x<<" = "<<x<<endl
#define sz(x) int(x.size())
#define All(x) x.begin(),x.end()
#define pb push_back
#define mp make_pair
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> P;
const double eps=1e-8;
inline int sign(double x){return (x>eps)-(x<-eps);}
const int maxn=1e6+10,mod=1e9+7,INF=0x3f3f3f3f;
int a[maxn];
vector<int> v[maxn];
int main()
{
	int T;
	cin>>T;
	while (T--){
		int n,k;
		scanf("%d%d",&n,&k);
		int N=2*n*(1<<k);
		int m=1<<k;
		for (int i=1;i<=m;++i)	
			v[i].clear();
		for (int i=1;i<=N;++i)
			scanf("%d",&a[i]),v[m].pb(a[i]);
		reverse(All(v[m]));
		for (int t=0;t<k;++t){
			for (int i=m-(1<<t)+1,j=i-1;i<=m;++i,--j){
				int mid=sz(v[i])/2;
				for (int o=0;o<mid;++o){
					v[j].pb(v[i].back());
					v[i].pop_back();
				}
			}
		}
		for (int i=2*n-1;i>=0;--i)
			for (int j=1;j<=m;++j)
				printf("%d%c",v[j][i]," \n"[i==0&&j==m]);
	}
	return 0;
}

