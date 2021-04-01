#include<bits/stdc++.h>
#define LL long long
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
using namespace std;
namespace IO
{
    const int sz=1<<15;
    char inbuf[sz],outbuf[sz];
    char *pinbuf=inbuf+sz;
    char *poutbuf=outbuf;
    inline char _getchar()
    {
        if (pinbuf==inbuf+sz)fread(inbuf,1,sz,stdin),pinbuf=inbuf;
        return *(pinbuf++);
    }
    inline void _putchar(char x)
    {
        if (poutbuf==outbuf+sz)fwrite(outbuf,1,sz,stdout),poutbuf=outbuf;
        *(poutbuf++)=x;
    }
    inline void flush()
    {
        if (poutbuf!=outbuf)fwrite(outbuf,1,poutbuf-outbuf,stdout),poutbuf=outbuf;
    }
}
inline int read(){
	int v=0,f=1;
	char c=getchar();
	while (c<'0' || c>'9'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0' && c<='9'){
		v=v*10+c-'0';
		c=getchar();
	}
	return v*f;
}
const int mod=1e9+7;
const int dlt=1000;
void Add(int &x,int y){
	x+=y;
	if (x>=mod) x-=mod;
}
int dp[105][2005][2][2];
char s[105];
int n,v[105];
int main(){
	scanf("%s",s+1); 
	n=strlen(s+1);
	for (int i=1;i<=n;i++) v[i]=s[i]-'0';
	
	dp[0][dlt][0][0]=1;
	
	for (int i=0;i<n;i++){
		for (int d=0;d<2005;d++){
			for (int f0=0;f0<2;f0++){
				for (int f1=0;f1<2;f1++){
					if (!dp[i][d][f0][f1]) continue;
					int V=v[i+1];
					for (int A=0;A<10;A++){
						for (int B=0;B<10;B++){
							if (A>B && !f0) continue;
							if (B>V && !f1) continue;
							int nf0=f0|(A<B);
							int nf1=f1|(B<V);
							Add(dp[i+1][d+A-B][nf0][nf1],dp[i][d][f0][f1]);
						}
					}
				}
			}
		}
	}
	
	int res=0;
	for (int d=dlt+1;d<2005;d++){
		for (int f1=0;f1<2;f1++){
			Add(res,dp[n][d][1][f1]);
		}
	}
	printf("%d\n",res);
	return 0;
}
