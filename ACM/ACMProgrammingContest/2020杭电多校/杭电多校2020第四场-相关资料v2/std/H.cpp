#include<bits/stdc++.h>
using namespace std;

#define pii pair<int,int>
#define fi first
#define se second
#define ll long long

int n=6;

vector<vector<pii> >fuck;

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
    if (x-1>=0&&fl[x-1][y]&&!dn[x-1][y]){
        dfs(x-1,y,B,A*-1);
    }
    if (x+1<n&&fl[x+1][y]&&!dn[x][y]){
        dfs(x+1,y,B*-1,A);
    }
    if (y-1>=0&&fl[x][y-1]&&!ri[x][y-1]){
        dfs(x,y-1,xxx(A,B)*-1,B);
    }
    if (y+1<n&&fl[x][y+1]&&!ri[x][y]){
        dfs(x,y+1,xxx(A,B)*1,B);
    }
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

bool chk2(){
    fa.resize(n*n);
    for (int i=0;i<n*n;++i) fa[i]=i;
    E.clear();
    for (int i=0;i<n;++i)
        for (int j=0;j<n;++j)
            if (fl[i][j]){
                if (i+1<n&&fl[i+1][j]) E.push_back({{i,j},{i+1,j}});
                if (j+1<n&&fl[i][j+1]) E.push_back({{i,j},{i,j+1}});
            }
    return gaoE(0);
}

namespace gaofuck{
    int n=5;
    set<ll>TMP;
    ll fixed(ll S){
        while (1){
            int cnt=0;
            for (int i=0;i<n;++i)
                cnt+=S>>(i*n)&1;
            if (cnt) break;
            S>>=1;
        }
        while (1){
            int cnt=0;
            for (int i=0;i<n;++i)
                cnt+=S>>i&1;
            if (cnt) break;
            S>>=n;
        }
        return S;
    }
    void dfs(ll S,ll T){
        if (__builtin_popcountll(S)>=6){
            memset(fl,0,sizeof fl);
            memset(ri,0,sizeof ri);
            memset(dn,0,sizeof dn);
            for (int i=0;i<n*n;++i)
                if (S>>i&1) fl[i/n][i%n]=1;
            if (chk2()){
                TMP.insert(fixed(S));
                return;
            }
        }
        if (__builtin_popcountll(S)>=8) return;
        for (int i=0;i<n*n;++i)
            if (!(T>>i&1)&&!(S>>i&1)){
                int x=i/n, y=i%n, fl=0;
                if (x!=0) if (S>>((x-1)*n+y)&1) fl=1;
                if (y!=0) if (S>>((x)*n+y-1)&1) fl=1;
                if (x!=n-1) if (S>>((x+1)*n+y)&1) fl=1;
                if (y!=n-1) if (S>>((x)*n+y+1)&1) fl=1;
                if (fl){
                    dfs(S|1ll<<i,T);
                    dfs(S,T|1ll<<i);
                    break;
                }
            }
    }

    void realmain(){
        ll now=0;
        for (int i=0;i<n;++i){
            dfs(1ll<<i,now);
            now|=1ll<<i;
        }
        for (auto S:TMP){
            int fl=0;
            for (int i=0;i<n*n;++i)
                if (S>>i&1)
                    if (TMP.count(fixed(S^1ll<<i)))
                        fl=1;
            if (fl) continue;
            for (int i=0;i<n*n;++i)
                if (S>>i&1){
                    vector<pii>v;
                    for (int j=0;j<n*n;++j)
                        if (S>>j&1){
                            v.push_back({j/n-i/n,j%n-i%n});
                        }
                    fuck.push_back(v);
                }
        }
        // cerr<<"fuck : "<<fuck.size()<<endl;
    }
}

unordered_set<ll>all;

vector<ll>kil[64];

ll bas1, bas2;
void initfixed(){
    for (int i=0;i<n;++i){
        bas1|=1ll<<i*n;
        bas2|=1ll<<i;
    }
}

ll fixed(ll S){
    while ((S&bas1)==0) S>>=1;
    while ((S&bas2)==0) S>>=n;
    return S;
}

ll superfix(ll S){
    ll mn=S;
    for (int tim=4;tim--;){
        ll T=0;
        for (int i=0;i<n*n;++i)
            if (S>>i&1) T|=1ll<<(i%n)*n+i/n;
        mn=min(mn,min(fixed(S),fixed(T)));
        T=0;
        for (int i=0;i<n*n;++i)
            if (S>>i&1) T|=1ll<<(n-1-i%n)*n+i/n;
        S=T;
    }
    return mn;
}
bool chk3(ll S){
    S=superfix(S); static unordered_map<ll,bool>mp;
    if (mp.count(S)) return mp[S];
    memset(fl,0,sizeof fl); memset(ri,0,sizeof ri); memset(dn,0,sizeof dn);
    for (int i=0;i<n*n;++i) fl[i/n][i%n]=S>>i&1;
    return mp[S]=chk2();
}

void dfs(ll S,ll T){
    all.insert(fixed(S));
    for (int i=0;i<n*n;++i)
        if (!(T>>i&1)&&!(S>>i&1)){
            int x=i/n, y=i%n, fl=0;
            if (x!=0) if (S>>((x-1)*n+y)&1) fl=1;
            if (y!=0) if (S>>((x)*n+y-1)&1) fl=1;
            if (x!=n-1) if (S>>((x+1)*n+y)&1) fl=1;
            if (y!=n-1) if (S>>((x)*n+y+1)&1) fl=1;
            if (fl){
                for (auto o:kil[i])
                    if ((S&o)==o){
                        fl=0; break;
                    }
            }
            if (fl){
                dfs(S|1ll<<i,T);
                dfs(S,T|1ll<<i);
                break;
            }
        }
}

unordered_set<ll>die;

signed main(){
    initfixed();
    gaofuck::realmain();// return 0;
    for (int i=0;i<n;++i)
        for (int j=0;j<n;++j){
            for (auto o:fuck){
                int fl=1; ll S=0;
                for (int k=0;k<o.size();++k){
                    int x=i+o[k].fi, y=j+o[k].se;
                    if (x==i&&y==j) continue;
                    if (x>=0&&x<n&&y>=0&&y<n){
                        S|=1ll<<(x*n+y);
                    }else{
                        fl=0;
                    }
                }
                if (fl) kil[i*n+j].push_back(S);
            }
        }
    ll now=0;
    for (int i=0;i<n*n;++i){
        dfs(1ll<<i,now);
        now|=1ll<<i;
    }
    //cerr<<"all "<<all.size()<<endl; //return 0;
    for (auto o:all) if (!chk3(o)) die.insert(o);
    //cerr<<"die "<<die.size()<<endl;
    {
        int T; scanf("%d",&T);
        while (T--){
            ll x=0;
            int a, b; cin>>a>>b;
            for (int i=0;i<a;++i){
                string str; cin>>str;
                for (int j=0;j<b;++j){
                    if (str[j]=='1') x|=1ll<<(i*6+j);
                }
            }
            puts(die.count(fixed(x))? "No": "Yes");
        }
    }
}