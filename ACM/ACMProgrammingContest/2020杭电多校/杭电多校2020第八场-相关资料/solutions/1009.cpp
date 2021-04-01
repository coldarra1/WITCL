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
const int N=5e6+5,K=3,M=1e7+5;
int n;
char s[N];
int mod[K] = {
    //1000003,
    //1000037,
    2000039,
    5000011,
    7000061
};
int hsh[K][N];
int pm[K][N];
int Hsh(int k,int l,int r){
    return (hsh[k][r] - hsh[k][l-1]*1ll*pm[k][r-l+1] % mod[k] + mod[k]) % mod[k];
}
int ct = 0;
int tmp[M];
bool check(int k,int d){
    ++ct;
    int cur = Hsh(k,1,d);
    tmp[cur] = ct;
    ROF(i,d,2){
        cur = ((cur-(s[d-i+1]-'a'+1)*1ll*pm[k][d-1]) % mod[k] * 29ll % mod[k] + s[d-i+1]-'a'+1) % mod[k];
        cur = (cur + mod[k]) % mod[k];
        tmp[cur] = ct;
    }
    ROF(i,n/d-1,0){
        int x = Hsh(k,i*d+1,i*d+d);
        if(tmp[x] != ct)return 0;
    }
    return 1;
}
void go(){
    scanf("%d",&n);
    scanf("%s",s+1);
    FOR(k,0,K-1){
        FOR(i,1,n){
            hsh[k][i] = (hsh[k][i-1]*29ll + s[i]-'a'+1) % mod[k];
        }
    }
    FOR(d,1,n-1)if(n%d == 0){
        bool flag = 1;
        FOR(k,0,K-1){
            if(check(k,d) == 0){
                flag = 0;
                break;
            }
        }
        if(flag)return puts("Yes"), void();
    }
    puts("No");
}

int main(){
    FOR(k,0,K-1){
        pm[k][0] = 1;
        FOR(i,1,N-1)pm[k][i] = pm[k][i-1] * 29ll % mod[k];
    }
    int t;
    scanf("%d",&t);
    FOR(i,1,t)go();
    return 0;
}
