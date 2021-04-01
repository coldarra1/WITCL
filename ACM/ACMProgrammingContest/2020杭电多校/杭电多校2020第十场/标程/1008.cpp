#include<bits/stdc++.h>
#define rep(i,n) for(int i=1;i<=n;++i)
#define mp make_pair
#define pb push_back
#define st first
#define nd second
#define x0 fuckcjb
#define y0 fuckyzc
#define x1 fucksf
#define y1 fuckjsb
using namespace std;
using ll=long long;
using ld=long double;
const int N=5000+5;
int T,n;
bool a[N][N];
char s[N/4];

int dfn[N],low[N],tot;
int sta[N],top;
int col[N],scc;
bool in[N];
void dfs(int x){
    dfn[x]=low[x]=++tot;
    in[x]=1;sta[++top]=x;
    rep(i,n)if(a[x][i]){
        if(dfn[i]==0)dfs(i),low[x]=min(low[x],low[i]);
        else if(in[i])low[x]=min(low[x],dfn[i]);
    }
    if(low[x]==dfn[x]){
        ++scc;
        for(;;){
            col[sta[top]]=scc;
            in[sta[top]]=0;
            --top;
            if(sta[top+1]==x)break;
        }
    }
}
void tarjan(){
    rep(i,n)dfn[i]=low[i]=in[i]=0;
    tot=top=scc=0;
    rep(i,n)if(dfn[i]==0)dfs(i);
}

int head,nxt[N];
void Hpath(){
    head=1;rep(i,n)nxt[i]=0;

    for(int i=2;i<=n;++i){
        if(a[i][head]){nxt[i]=head,head=i;continue;}
        int j=head;
        for(;nxt[j]!=0;j=nxt[j])
            if(a[i][nxt[j]]){nxt[i]=nxt[j],nxt[j]=i;break;}
        if(nxt[j]==0)nxt[j]=i;
    }
}

int q[N],lop;
void Hloop(){
    Hpath();
    for(int i=1,ptr=head;i<=n;++i,ptr=nxt[ptr])
        q[i]=ptr;
    lop=0;
    for(int i=n;i;--i)if(a[q[i]][q[1]]){
        lop=i;nxt[q[i]]=q[1];
        break;
    }

    for(int i=lop+1;i<=n;++i)
        for(int ptr=q[1];nxt[ptr]!=q[1];ptr=nxt[ptr])
            if(a[q[i]][nxt[ptr]]){
                nxt[q[i]]=nxt[ptr];
                nxt[ptr]=q[lop+1];
                lop=i;
                break;
            }
}
int ans[N][N];
int rk[N];
int cnt[N][N];
void add(int x0,int x1,int y0,int y1){
    if(x0>x1||y0>y1)return;
    ++cnt[x0][y0];
    --cnt[x1+1][y0];
    --cnt[x0][y1+1];
    ++cnt[x1+1][y1+1];
}
int main(){
    for(scanf("%d",&T);T--;){
        scanf("%d",&n);
        rep(i,n)rep(j,n)a[i][j]=0;
        for(int i=2;i<=n;++i){
            scanf("%s",s+1);int len=strlen(s+1);
            rep(j,len)s[j]=(s[j]<='9'?s[j]-'0':s[j]-'A'+10);
            rep(j,i-1)if(( s[(j-1)/4+1] & (1<<((j-1)%4)) )>0)
                a[i][j]=1,a[j][i]=0;
            else a[i][j]=0,a[j][i]=1;
        }
        if(n==2){puts("0");continue;}
        for(int i=2;i<=n;++i)
            rep(j,((i-1)-1)/4+1)ans[i][j]=0;
        tarjan();
        if(scc==1){
            for(int i=2;i<=n;++i)
                rep(j,i-1)ans[i][(j-1)/4+1]|=1<<((j-1)%4);
            Hloop();
            for(int i=1,ptr=1;i<=n;++i,ptr=nxt[ptr])
                rk[ptr]=i;//,printf("%d%c",ptr," \n"[i==n]);

            for(int i=0;i<=n;++i)
                for(int j=0;j<=n;++j)
                    cnt[i][j]=0;
            rep(i,n)rep(j,n)if(i!=j&&a[i][j]){
                if(rk[i]<rk[j]){
                    add(rk[i],rk[j]-1,rk[j],n);
                    add(rk[i],rk[j]-1,1,rk[i]-1);
                }else{
                    add(rk[i],n,rk[j],rk[i]-1);
                    add(1,rk[j]-1,rk[j],rk[i]-1);
                }
            }
            rep(i,n)rep(j,n)cnt[i][j]+=cnt[i-1][j]+cnt[i][j-1]-cnt[i-1][j-1];
            //rep(i,n)rep(j,n)printf("%d%c",cnt[i][j]," \n"[j==n]);
            rep(i,n)rep(j,n)if(i!=j&&cnt[rk[i]][rk[j]]==1){
                int x=i,y=nxt[i];
                if(x<y)swap(x,y);
                ans[x][(y-1)/4+1]-=1<<((y-1)%4);
                break;
            }
        }else{   
            for(int i=2;i<=n;++i)
                rep(j,i-1)if((col[i]==1&&col[j]==scc)||(col[i]==scc&&col[j]==1))
                    ans[i][(j-1)/4+1]|=1<<((j-1)%4);
        }
        

        for(int i=2;i<=n;++i){
            rep(j,((i-1)-1)/4+1)
                printf("%c",ans[i][j]<=9?ans[i][j]+'0':ans[i][j]-10+'A');
            puts("");
        }
    }
}