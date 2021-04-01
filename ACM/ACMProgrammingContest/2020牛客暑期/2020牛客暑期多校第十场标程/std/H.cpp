#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <ctime>
#include <cassert>
#include <string.h>
//#include <unordered_set>
//#include <unordered_map>
//#include <bits/stdc++.h>

#define MP(A,B) make_pair(A,B)
#define PB(A) push_back(A)
#define SIZE(A) ((int)A.size())
#define LEN(A) ((int)A.length())
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define fi first
#define se second

using namespace std;

template<typename T>inline bool upmin(T &x,T y) { return y<x?x=y,1:0; }
template<typename T>inline bool upmax(T &x,T y) { return x<y?x=y,1:0; }

typedef long long ll;
typedef unsigned long long ull;
typedef long double lod;
typedef pair<int,int> PR;
typedef vector<int> VI;

const lod eps=1e-11;
const lod pi=acos(-1);
const int oo=1<<30;
const ll loo=(1ll<<60)-1;
const int mods=998244353;
const int MAXN=600005;
const int INF=0x3f3f3f3f;//1061109567
/*--------------------------------------------------------------------*/
inline ll read()
{
	ll f=1,x=0; char c=getchar();
	while (c<'0'||c>'9') { if (c=='-') f=-1; c=getchar(); }
	while (c>='0'&&c<='9') { x=(x<<3)+(x<<1)+(c^48); c=getchar(); }
	return x*f;
}
int a[1005][1005];
int st0[36]={
1,0,0,1,0,1,
0,1,0,0,0,0,
0,0,0,1,0,1,
1,0,1,0,0,0,
0,0,0,0,1,0,
1,0,1,0,0,1};
int st2[64]={
1,0,1,0,1,0,0,1,
0,0,0,0,0,0,1,0,
1,0,1,0,1,0,0,0,
0,0,0,0,0,1,0,1,
1,0,1,0,1,0,0,0,
0,0,0,1,0,1,0,1,
0,1,0,0,0,0,0,0,
1,0,0,1,0,1,0,1};
int st4[100]={
1,0,1,0,0,1,0,1,0,1,
0,0,0,0,1,0,0,0,0,0,
1,0,1,0,0,1,0,1,0,1,
0,1,0,1,0,0,1,0,0,0,
0,0,0,0,0,1,0,1,0,1,
1,0,1,0,1,0,0,0,0,0,
0,0,0,1,0,0,1,0,1,0,
1,0,1,0,1,0,0,1,0,1,
0,0,0,0,0,0,0,0,0,0,
1,0,1,0,1,0,0,1,0,1};

int st1[169]={
1,0,1,0,1,0,1,0,1,0,1,0,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,
1,0,1,0,1,0,1,0,1,0,1,0,1,
0,0,0,1,0,1,0,1,0,1,0,0,0,
1,0,1,0,0,0,0,0,0,0,1,0,1,
0,0,0,1,0,1,0,1,0,1,0,0,0,
0,1,0,0,0,0,1,0,0,0,1,0,1,
1,0,0,1,0,1,0,1,0,1,0,0,0,
0,0,1,0,1,0,0,0,0,0,1,0,1,
0,1,0,0,0,1,0,1,0,1,0,0,0,
1,0,1,0,1,0,1,0,1,0,1,0,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,
1,0,1,0,1,0,1,0,1,0,1,0,1,};

int st3[225]={
1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,
1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,
0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,
1,0,1,0,0,0,1,0,0,0,0,0,1,0,1,
0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,
0,1,0,0,0,0,0,0,1,0,0,0,1,0,1,
1,0,0,1,0,1,0,1,0,1,0,1,0,0,0,
0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,
0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,
1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,};

int st5[289]={
1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,
1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,
1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,
0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,
1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,1,
0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,
0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,1,
1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,
0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,
0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,
1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
};

void solve(int n) {
	int MX=250;
	memset(a,0,sizeof(a));
	if (n==1) {
		puts("1");
		return;
	}
	if (n==2) {
		puts("10\n00");
		return;
	}
	if (n==3) {
		puts("101\n000\n101");
		return;
	}
	if (n==4) {
		puts("1001\n0000\n0100\n1001");
		return;
	}
	if (n==5) {
		puts("10101\n00000\n10101\n00000\n10101");
		return;
	}

	if (n%6==0)
	{
		for (int i=0;i<6;i++)
			for (int j=0;j<6;j++) a[MX+i][MX+j]=st0[i*6+j];
		for (int t=1;t<n/6;t++)
		{
			for (int i=-t*3;i<=t*3+3;i+=2)
			{
				if (a[MX-(t-1)*3][MX+i]) a[MX-t*3+1][MX+i]=1,i++;
				a[MX-t*3][MX+i]=a[MX-t*3+2][MX+i]=1;
			}
			for (int i=t*3+5;i>=-t*3+3;i-=2)
			{
				if (a[MX+i][MX-(t-1)*3]) a[MX+i][MX-t*3+1]=1,i--;
				a[MX+i][MX-t*3]=a[MX+i][MX-t*3+2]=1;
			}
			
			for (int i=t*3+5;i>=-t*3+4;i-=2)
			{
				if (a[MX+t*3+2][MX+i]) a[MX+t*3+4][MX+i]=1,i--;
				a[MX+t*3+5][MX+i]=a[MX+t*3+3][MX+i]=1;
			}
			for (int i=-t*3;i<=t*3+5;i+=2)
			{
				if (a[MX+i][MX+t*3+2]) a[MX+i][MX+t*3+4]=1,i++;
				a[MX+i][MX+t*3+5]=a[MX+i][MX+t*3+3]=1;
			}
		}
		int ans=0;
		for (int i=MX-n/2+3;i<=MX+n/2+2;i++)
		{
			for (int j=MX-n/2+3;j<=MX+n/2+2;j++) putchar(a[i][j]+'0'),ans+=a[i][j];
			puts("");
		}
//		cout<<ans<<" "<<((n-1)*(n-1)+2*((n+1)/2)+2*((n+1)/2))/3<<endl;
	}
	
	
	
	if (n%6==2)
	{
		for (int i=0;i<8;i++)
			for (int j=0;j<8;j++) a[MX+i][MX+j]=st2[i*8+j];
		for (int t=1;t<n/6;t++)
		{
			
			for (int i=-t*3;i<=t*3+7;i+=2)
			{
				if (a[MX-(t-1)*3][MX+i]) a[MX-t*3+1][MX+i]=1,i++;
				a[MX-t*3][MX+i]=a[MX-t*3+2][MX+i]=1;
			}
			for (int i=t*3+7;i>=-t*3;i-=2)
			{
				if (a[MX+i][MX-(t-1)*3]) a[MX+i][MX-t*3+1]=1,i--;
				a[MX+i][MX-t*3]=a[MX+i][MX-t*3+2]=1;
			}
			
			for (int i=t*3+7;i>=-t*3;i-=2)
			{
				if (a[MX+t*3+4][MX+i]) a[MX+t*3+6][MX+i]=1,i--;
				a[MX+t*3+7][MX+i]=a[MX+t*3+5][MX+i]=1;
			}
			
			for (int i=-t*3;i<=t*3+7;i+=2)
			{
				if (a[MX+i][MX+t*3+4]) a[MX+i][MX+t*3+6]=1,i++;
				a[MX+i][MX+t*3+7]=a[MX+i][MX+t*3+5]=1;
			}
			
		}
		int ans=0;
		for (int i=MX-n/2+4;i<=MX+n/2+3;i++)
		{
			for (int j=MX-n/2+4;j<=MX+n/2+3;j++) putchar(a[i][j]+'0'),ans+=a[i][j];
			puts("");
		}
//		cout<<ans<<" "<<((n-1)*(n-1)+2*((n+1)/2)+2*((n+1)/2))/3<<endl;
	}
	
	if (n%6==4)
	{
		for (int i=0;i<10;i++)
			for (int j=0;j<10;j++) a[MX+i][MX+j]=st4[i*10+j];
		for (int t=1;t<n/6;t++)
		{
			for (int i=-t*3;i<=t*3+9;i+=2)
			{
				if (a[MX-(t-1)*3][MX+i]) a[MX-t*3+1][MX+i]=1,i++;
				a[MX-t*3][MX+i]=a[MX-t*3+2][MX+i]=1;
			}
			
			for (int i=t*3+9;i>=-t*3;i-=2)
			{
				if (a[MX+i][MX-(t-1)*3]) a[MX+i][MX-t*3+1]=1,i--;
				a[MX+i][MX-t*3]=a[MX+i][MX-t*3+2]=1;
			}
			for (int i=t*3+9;i>=-t*3;i-=2)
			{
				if (a[MX+t*3+6][MX+i]) a[MX+t*3+8][MX+i]=1,i--;
				a[MX+t*3+9][MX+i]=a[MX+t*3+7][MX+i]=1;
			}
			for (int i=-t*3;i<=t*3+9;i+=2)
			{
				if (a[MX+i][MX+t*3+6]) a[MX+i][MX+t*3+8]=1,i++;
				a[MX+i][MX+t*3+9]=a[MX+i][MX+t*3+7]=1;
			}
		}
		int ans=0;
		for (int i=MX-n/2+5;i<=MX+n/2+4;i++)
		{
			for (int j=MX-n/2+5;j<=MX+n/2+4;j++) putchar(a[i][j]+'0'),ans+=a[i][j];
			puts("");
		}
//		cout<<ans<<" "<<((n-1)*(n-1)+2*((n+1)/2)+2*((n+1)/2))/3<<endl;
	}
	
	
	
	if (n%6==1)
	{
		for (int i=0;i<13;i++)
			for (int j=0;j<13;j++) a[MX+i][MX+j]=st1[i*13+j];
		for (int t=1;t<n/6;t++)
		{
			
			for (int i=-t*3;i<=t*3+12;i+=2)
			{
				if (a[MX-(t-1)*3][MX+i]) a[MX-t*3+1][MX+i]=1,i++;
				a[MX-t*3][MX+i]=a[MX-t*3+2][MX+i]=1;
			}
			
			for (int i=t*3+12;i>=-t*3;i-=2)
			{
				if (a[MX+i][MX-(t-1)*3]) a[MX+i][MX-t*3+1]=1,i--;
				a[MX+i][MX-t*3]=a[MX+i][MX-t*3+2]=1;
			}
			for (int i=t*3+12;i>=-t*3;i-=2)
			{
				if (a[MX+t*3+9][MX+i]) a[MX+t*3+11][MX+i]=1,i--;
				a[MX+t*3+12][MX+i]=a[MX+t*3+10][MX+i]=1;
			}
			for (int i=-t*3;i<=t*3+12;i+=2)
			{
				if (a[MX+i][MX+t*3+9]) a[MX+i][MX+t*3+11]=1,i++;
				a[MX+i][MX+t*3+12]=a[MX+i][MX+t*3+10]=1;
			}
		}
		int ans=0;
		if (n==7) a[MX+9][MX+3]=1,a[MX+8][MX+4]=0;
		for (int i=MX-n/2+6;i<=MX+n/2+6;i++)
		{
			for (int j=MX-n/2+6;j<=MX+n/2+6;j++) putchar(a[i][j]+'0'),ans+=a[i][j];
			puts("");
		}
//		cout<<ans<<" "<<((n-1)*(n-1)+2*((n+1)/2)+2*((n+1)/2))/3<<endl;
	}
	
	
	
	if (n%6==3)
	{
		for (int i=0;i<15;i++)
			for (int j=0;j<15;j++) a[MX+i][MX+j]=st3[i*15+j];
		for (int t=1;t<n/6;t++)
		{
			
			for (int i=-t*3;i<=t*3+14;i+=2)
			{
				if (a[MX-(t-1)*3][MX+i]) a[MX-t*3+1][MX+i]=1,i++;
				a[MX-t*3][MX+i]=a[MX-t*3+2][MX+i]=1;
			}
			
			for (int i=t*3+14;i>=-t*3;i-=2)
			{
				if (a[MX+i][MX-(t-1)*3]) a[MX+i][MX-t*3+1]=1,i--;
				a[MX+i][MX-t*3]=a[MX+i][MX-t*3+2]=1;
			}
			for (int i=t*3+14;i>=-t*3;i-=2)
			{
				if (a[MX+t*3+11][MX+i]) a[MX+t*3+13][MX+i]=1,i--;
				a[MX+t*3+14][MX+i]=a[MX+t*3+12][MX+i]=1;
			}
			for (int i=-t*3;i<=t*3+14;i+=2)
			{
				if (a[MX+i][MX+t*3+11]) a[MX+i][MX+t*3+13]=1,i++;
				a[MX+i][MX+t*3+14]=a[MX+i][MX+t*3+12]=1;
			}
		}
		int ans=0;
		if (n==9) a[MX+11][MX+3]=1,a[MX+10][MX+4]=0;
		for (int i=MX-n/2+7;i<=MX+n/2+7;i++)
		{
			for (int j=MX-n/2+7;j<=MX+n/2+7;j++) putchar(a[i][j]+'0'),ans+=a[i][j];
			puts("");
		}
//		cout<<ans<<" "<<((n-1)*(n-1)+2*((n+1)/2)+2*((n+1)/2))/3<<endl;
	}
	
	
	if (n%6==5)
	{
		for (int i=0;i<17;i++)
			for (int j=0;j<17;j++) a[MX+i][MX+j]=st5[i*17+j];
		for (int t=1;t<n/6;t++)
		{
			
			for (int i=-t*3;i<=t*3+16;i+=2)
			{
				if (a[MX-(t-1)*3][MX+i]) a[MX-t*3+1][MX+i]=1,i++;
				a[MX-t*3][MX+i]=a[MX-t*3+2][MX+i]=1;
			}
			
			for (int i=t*3+16;i>=-t*3;i-=2)
			{
				if (a[MX+i][MX-(t-1)*3]) a[MX+i][MX-t*3+1]=1,i--;
				a[MX+i][MX-t*3]=a[MX+i][MX-t*3+2]=1;
			}
			for (int i=t*3+16;i>=-t*3;i-=2)
			{
				if (a[MX+t*3+13][MX+i]) a[MX+t*3+15][MX+i]=1,i--;
				a[MX+t*3+16][MX+i]=a[MX+t*3+14][MX+i]=1;
			}
			for (int i=-t*3;i<=t*3+16;i+=2)
			{
				if (a[MX+i][MX+t*3+13]) a[MX+i][MX+t*3+15]=1,i++;
				a[MX+i][MX+t*3+16]=a[MX+i][MX+t*3+14]=1;
			}
		}
		int ans=0;
		if (n==11) a[MX+13][MX+3]=1,a[MX+12][MX+4]=0;
		for (int i=MX-n/2+8;i<=MX+n/2+8;i++)
		{
			for (int j=MX-n/2+8;j<=MX+n/2+8;j++) putchar(a[i][j]+'0'),ans+=a[i][j];
			puts("");
		}
//		cout<<ans<<" "<<((n-1)*(n-1)+2*((n+1)/2)+2*((n+1)/2))/3<<endl;
	}
}

int _,n;
int main() {
	for (scanf("%d",&_);_;_--) {
		scanf("%d",&n);
		solve(n);
	}
}