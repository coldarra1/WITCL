#include <bits/stdc++.h>
#define pb emplace_back
using namespace std;
using i64=long long;
const int N=1e7+5,M=20,L=101000,mod=1e9+7;
int f[N],g[N],p2[M],ip2[M];
int q,su[L];
bool is[N];
struct Query{
    int w,d,x,i;
};
vector<Query> z;
int main(){
    for(int i=2;i<N;++i) if(!f[i]) {
        is[i]=1;
        for(int j=i;j<N;j+=i) ++f[j];
    }
    p2[0]=ip2[0]=1;
    for(int i=1;i<M;++i){
        p2[i]=p2[i-1]*2%mod;
        ip2[i]=(i64)ip2[i-1]*(mod/2+1)%mod;
    }
    for(int i=1;i<N;++i) g[i]=ip2[f[i]],f[i]=p2[f[i]];
    for(int p=N-1;p>=2;--p) if(is[p]) for(int i=(N-1)/p;i>=1;--i) g[i*p]=(g[i*p]-g[i]+mod)%mod;
    scanf("%d",&q);
    for(int i=1;i<=q;++i){
        int n,m;
        scanf("%d%d",&n,&m);
        for(int d=1;d*d<=n;++d){
            if(n%d==0){
                Query t; int u=d;
                t.w=(i64)f[n]*g[u]%mod;
                t.d=u;
                t.x=(m/u)*u;
                t.i=i;
                z.pb(t);
                if(d*d!=n){
                    u=n/d;
                    t.w=(i64)f[n]*g[u]%mod;
                    t.d=u;
                    t.x=(m/u)*u;
                    t.i=i;
                    //printf("tt %d %d %d %d\n",t.w,t.d,t.x,t.i);
                    z.pb(t);
                }
            }
        }
    }
    sort(z.begin(),z.end(),[&](Query a,Query b){
        if(a.d==b.d) return a.x<b.x;
        return a.d<b.d;
        });
    int d=0,l=0; i64 w=0;
    for(int k=0;k<z.size();++k){
        auto t=z[k];
        if(d!=t.d) d=t.d,l=d,w=0;
        while(l<=t.x) w+=f[l],l+=d;
        w%=mod;
        su[t.i]=(su[t.i]+t.w*w)%mod;
    }
    for(int i=1;i<=q;++i) printf("%d\n",su[i]);
}