#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

ll readint(){
    ll x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

ll a,b,k;

int main(){
    int T=readint();
    while(T--){
        a=readint(); b=readint(); k=readint();
        if(a>b) swap(a,b);
        ll n=b-a;
        n/=(k+1);
        ld tmp=sqrt(k*k+2*k+5);
        ld x=(1-k+tmp)/2.0,y=(3+k+tmp)/2.0;
        if((ll)(x*n)!=a||(ll)(y*n)!=b) puts("1");
        else puts("0");
    }
    return 0;
}