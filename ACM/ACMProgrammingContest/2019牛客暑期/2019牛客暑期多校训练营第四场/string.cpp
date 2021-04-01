#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define SZ 455555
char s[SZ]; int n;
struct PTree
{
int ch[SZ][26],len[SZ],fail[SZ],s[SZ],cl,an,lst;
int addn(int l) {len[an]=l; return an++;}
PTree()
{
	cl=an=lst=0;
	memset(ch,0,sizeof(ch));
	addn(0); addn(-1);
	fail[0]=1; s[0]=-233;
}
int gfail(int x,int l)
{
	while(s[l-len[x]-1]!=s[l]) x=fail[x];
	return x;
}
void add(int c)
{
	s[++cl]=c;
	int cp=gfail(lst,cl);
	if(!ch[cp][c])
	{
		int nn=addn(len[cp]+2);
		fail[nn]=ch[gfail(fail[cp],cl)][c];
		ch[cp][c]=nn;
	}
	lst=ch[cp][c];
}
}pt;
int sa[SZ],rk[SZ],su[SZ],ork[SZ],h[SZ];
bool diff(int a,int b,int g)
{return ork[a]!=ork[b]||ork[a+g]!=ork[b+g];}
void build_sa()
{
	int G=max(n,200);
	for(int i=0;i<=G;++i) su[i]=0;
	for(int i=0;i<n;++i)
		++su[rk[i]=s[i]];
	for(int i=1;i<=G;++i) su[i]+=su[i-1];
	for(int i=0;i<n;++i)
		sa[--su[rk[i]]]=i;
	for(int g=1;g<=n;g<<=1)
	{
		for(int i=0;i<=G;++i) su[i]=0;
		static int ts[SZ]; int tn=0;
		for(int i=n-1;i>=0;--i)
		{
			if(sa[i]>=g) ts[++tn]=sa[i]-g;
			ork[i]=rk[i];
		}
		for(int i=n-g;i<n;++i) ts[++tn]=i;
		for(int i=1;i<=tn;++i) ++su[rk[ts[i]]];
		for(int i=1;i<=G;++i) su[i]+=su[i-1];
		for(int i=1;i<=tn;++i)
			sa[--su[rk[ts[i]]]]=ts[i];
		int t=0;
		for(int i=0;i<n;++i)
		{
			if(i&&diff(sa[i-1],sa[i],g)) ++t;
			rk[sa[i]]=t;
		}
	}
	for(int i=0;i<n;++i) rk[sa[i]]=i;
	int g=0;
	for(int i=0;i<n;++i)
	{
		g=max(g-1,0);
		if(rk[i]==n-1)
		{
			h[rk[i]]=0;
			continue;
		}
		int A=i,B=sa[rk[i]+1];
		while(s[A+g]==s[B+g]) ++g;
		h[rk[i]]=g;
	}
}
int main()
{
	scanf("%s",s); n=strlen(s);
	for(int i=0;i<n;++i) pt.add(s[i]-'a');
	int p=pt.an-2,N=n; s[N]='|';
	for(int i=0;i<N;++i)
		s[N+i+1]=s[N-i-1];
	n=N+N+1; build_sa();
	ll tt=0;
	for(int i=1;i<=n;++i)
		tt+=i-h[i-1];
	printf("%lld\n",(tt-(N+1)*ll(N+1)+p)/2);
}

