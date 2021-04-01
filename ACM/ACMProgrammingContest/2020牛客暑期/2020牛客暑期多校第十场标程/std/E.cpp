#include<bits/stdc++.h>

#define y1 dmytxdy
#define pb push_back
#define fi first
#define se second
#define mp make_pair

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef long double ld;

template <typename T> bool chkmin(T &x,T y){return x>y?x=y,1:0;}
template <typename T> bool chkmax(T &x,T y){return x<y?x=y,1:0;}

int readint(){
	int x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

int n;
ll a[100005];

int main(){
//	freopen("11.in","r",stdin);
//	freopen("11.out","w",stdout);
	int T=readint();
	while(T--){
		n=readint();
		for(int i=1;i<=n;i++) a[i]=readint();
		int l=1,r=1e9,res;
		while(l<=r){
			int mid=(l+r)/2,fl=0; ll now=0;
			for(int i=1;i<=n;i++){
				now+=mid-a[i];
				if(now<0) fl=1;
			}
			if(fl) l=mid+1;
			else res=mid,r=mid-1;
		}
		printf("%d\n",res);
	}
	return 0;
}
