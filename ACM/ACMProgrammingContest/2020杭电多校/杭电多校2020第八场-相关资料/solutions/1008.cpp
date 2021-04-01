//by Sshwy
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define ROF(i,a,b) for(int i=(a);i>=(b);--i)

namespace RA{
    int rnd(int p){return 1ll*rand()*rand()%p;}
    int rnd(int L,int R){return rnd(R-L+1)+L;}
}
const int L=2e6+5;
int n, ls;
char s[L];

void walk(int x,int y){
    assert(x>2);
    FOR(i,1,x-2){
        s[ls++]='0'+(4+y-1)%6+1;
        s[ls++]='0'+(2+y-1)%6+1;
    }
    s[ls++]='0'+(3+y-1)%6+1;
}
void walk_circle(int x){
    FOR(i,0,5)walk(x,i);
    s[ls-3]='2';
    s[ls-2]='4';
    s[ls-1]='3';
}
void go(){
    ls=0;
    scanf("%d",&n);
    if(n%2==0){
        for(int i=n;i>2;i-=2)walk_circle(i);
        ROF(i,5,1)s[ls++]='0'+i;
        s[ls++]='5';
    }else {
        for(int i=n;i>1;i-=2)walk_circle(i);
    }
    s[ls]=0;
    printf("%s\n",s);
}
int main(){
    int t;
    scanf("%d",&t);
    FOR(i,1,t)go();
    return 0;
}