#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;

int n=6;
set<ll>all;

bool fl[9][9], fl2[9][9], ri[9][9], dn[9][9];

struct P{
    int x, y, z;
};
P xxx(P a,P b){
    return (P){a.y*b.z-a.z*b.y , a.z*b.x-a.x*b.z , a.x*b.y-a.y*b.x};
}
P operator * (P a,int b){
    return (P){a.x*b,a.y*b,a.z*b};
}
bool operator < (P a,P b){
    return make_tuple(a.x,a.y,a.z)<make_tuple(b.x,b.y,b.z);
}

set<P>face;
void dfs(int x,int y,P A,P B){
    fl[x][y]=0; face.insert(A);
    if (x-1>=0&&fl[x-1][y]&&!dn[x-1][y]) dfs(x-1,y,B,A*-1);
    if (x+1<n&&fl[x+1][y]&&!dn[x][y]) dfs(x+1,y,B*-1,A);
    if (y-1>=0&&fl[x][y-1]&&!ri[x][y-1]) dfs(x,y-1,xxx(A,B)*-1,B);
    if (y+1<n&&fl[x][y+1]&&!ri[x][y]) dfs(x,y+1,xxx(A,B)*1,B);
}

bool chk(){
    for (int i=0;i<n;++i)
        for (int j=0;j<n;++j)
            if (fl[i][j]){
                face.clear();
                dfs(i,j,{0,0,-1},{0,1,0});
                if (face.size()==6) return 1;
            }
    return 0;
}


vector<int>fa;
int GF(int x){
    return fa[x]==x? x: fa[x]=GF(fa[x]);
}

vector<pair<pii,pii> >E;
int ID(pii p){ return p.fi*n+p.se; }

bool gaoE(int it){
    if (it==E.size()){
        memcpy(fl2,fl,sizeof fl);
        int res=chk();
        memcpy(fl,fl2,sizeof fl);
        return res;
    }
    bool res=0; vector<int>bak=fa;
    if (GF(ID(E[it].fi))!=GF(ID(E[it].se))){
        fa[GF(ID(E[it].fi))]=GF(ID(E[it].se));
        res|=gaoE(it+1);
    }
    if (res) return 1;
    fa=bak;
    for (int i=it+1;i<E.size();++i){
        fa[GF(ID(E[i].fi))]=GF(ID(E[i].se));
    }
    if (GF(ID(E[it].fi))==GF(ID(E[it].se))){
        fa=bak;
        if (E[it].fi.fi==E[it].se.fi) ri[E[it].fi.fi][E[it].fi.se]=1;
        else dn[E[it].fi.fi][E[it].fi.se]=1;
        res|=gaoE(it+1);
        if (E[it].fi.fi==E[it].se.fi) ri[E[it].fi.fi][E[it].fi.se]=0;
        else dn[E[it].fi.fi][E[it].fi.se]=0;
    }
    return res;
}

bool chk2(ll S){
    for (int i=0;i<n*n;++i) fl[i/n][i%n]=S>>i&1;
    fa.resize(n*n);
    for (int i=0;i<n*n;++i) fa[i]=i;
    E.clear();
    for (int i=0;i<n;++i)
        for (int j=0;j<n;++j)
            if (fl[i][j]){
                if (i+1<n&&fl[i+1][j]) E.push_back({{i,j},{i+1,j}});
                if (j+1<n&&fl[i][j+1]) E.push_back({{i,j},{i,j+1}});
            }
    random_shuffle(E.begin(),E.end());
    return (bool)gaoE(0);
}

int main(){
    int T, n, m;
    for (cin>>T;T--;){
        cin>>n>>m;
        string s; ll S=0;
        for (int i=0;i<n;++i){
            cin>>s;
            for (int j=0;j<m;++j)
                if (s[j]=='1') S|=1ll<<i*m+j;
        }
        if (!chk2(S)) puts("No");
        else puts("Yes");
    }
}