#include <bits/stdc++.h>
using namespace std;
#define Maxn 20007
vector<int> g[Maxn],c[Maxn];
vector<int> e[Maxn];
int p[Maxn],total=0;
bool chk[Maxn];
int sz[Maxn];
int fa[17][Maxn],num[17][Maxn];
int n,col[Maxn],que[Maxn],dep[Maxn];
int dfn[Maxn],ptr=0;
int stk[Maxn],top=0;
int s,t,tot=0;
#define Maxm 2200007
#define inf 3000007
int last[Maxm],pre[Maxm],other[Maxm],flow[Maxm],cnt=1,cur_ans=0;
int lastt[Maxm],q[Maxm],l[Maxm];
int last1[Maxm],pre1[Maxm],other1[Maxm],flow1[Maxm],cnt1=1,cur1_ans=0;
void insert(int u,int v,int f)
{
    other[++cnt]=v,pre[cnt]=last[u],last[u]=cnt;
    flow[cnt]=f;
    other[++cnt]=u,pre[cnt]=last[v],last[v]=cnt;
    flow[cnt]=0;
}
void save_graph()
{
    cnt1=cnt;
    cur1_ans=cur_ans;
    for (int i=0;i<=t;i++)
        last1[i]=last[i];
    for (int i=0;i<=cnt;i++)
        other1[i]=other[i],pre1[i]=pre[i],flow1[i]=flow[i];
}
void get_graph()
{
    cnt=cnt1;
    cur_ans=cur1_ans;
    for (int i=0;i<=t;i++)
        last[i]=last1[i];
    for (int i=0;i<=cnt;i++)
        other[i]=other1[i],pre[i]=pre1[i],flow[i]=flow1[i];
}
bool bfs()
{
    int lx=0,rx=1;
    q[1]=s;
    for (int i=1;i<=t;i++)
        l[i]=-1;
    l[s]=1;
    while (lx<rx)
    {
        int u=q[++lx];
        for (int q1=last[u];q1;q1=pre[q1])
        {
            int v=other[q1];
            if (flow[q1]>0&&l[v]==-1)
            {
                l[v]=l[u]+1;
                q[++rx]=v;
            }
        }
    }
    if (l[t]!=-1) return true; else return false;
}
int find(int x,int maxf)
{
    if (x==t) return maxf;
    int ans=0;
    for (int &q=last[x];q;q=pre[q])
    {
        int v=other[q];
        if (l[v]==l[x]+1)
        {
            int t=find(v,min(flow[q],maxf-ans));
            flow[q]-=t;
            flow[q^1]+=t;
            ans+=t;
            if (ans==maxf) return ans;
        }
    }
    if (ans<maxf) l[x]=-1;
    return ans;
}
int dinic()
{
    for (int i=1;i<=t;i++)
        lastt[i]=last[i];
    int ans=0;
    while (bfs())
    {
        ans+=find(s,inf);
        for (int i=1;i<=t;i++)
            last[i]=lastt[i];
    }
    return ans;
}
bool check(int r)
{
    for (int i=cur_ans;i<r;i++)
        insert(tot+i,t,1);
    bool flag=true;
    if (dinic()==r-cur_ans) flag=true; else flag=false;
    cur_ans=r;
    return flag;
}
bool cmp(int a,int b)
{
    return (dfn[a]<dfn[b]);
}
void pre_dfs(int u,int f,int d)
{
    dfn[u]=++ptr;
    dep[u]=d;
    for (int i=0;i<(int)g[u].size();i++)
        pre_dfs(g[u][i],u,d+1);
}
void init()
{
    pre_dfs(1,0,1);
    for (int i=1;i<17;i++)
        for (int j=1;j<=n;j++)
            fa[i][j]=fa[i-1][fa[i-1][j]];
    s=1;
    for (int i=1;i<=n;i++)
        insert(s,i+1,1);
    tot=n+1;
    for (int i=0;i<17;i++)
        for (int j=1;j<=n;j++)
            if ((1<<i)<=dep[j]) num[i][j]=(++tot);
    for (int i=1;i<=n;i++)
        insert(i+1,num[0][i],1);
    for (int i=1;i<=16;i++)
        for (int j=1;j<=n;j++)
            if ((1<<i)<=dep[j])
            {
                insert(num[i-1][j],num[i][j],1<<(i-1));
                if (fa[i-1][j]!=0) insert(num[i-1][fa[i-1][j]],num[i][j],1<<(i-1));
            }
    ++tot;
    t=tot+n+1;
    for (int i=1;i<=n;i++)
        insert(i+1,tot,1);
}
int lca(int x,int y)
{
    if (dep[x]<dep[y]) swap(x,y);
    for (int i=16;i>=0;i--)
        if (dep[fa[i][x]]>=dep[y]) x=fa[i][x];
    for (int i=16;i>=0;i--)
        if (fa[i][x]!=fa[i][y])
        {
            x=fa[i][x];
            y=fa[i][y];
        }
    return x==y?x:fa[0][x];
}
void add_edge(int x,int y)
{
    if (x==y) return;
    if (!chk[x])
    {
        chk[x]=true;
        p[++total]=x;
    }
    if (!chk[y])
    {
        chk[y]=true;
        p[++total]=y;
    }
    e[x].push_back(y);
    e[y].push_back(x);
}
void virtree(int cur)
{
    top=1;
    stk[1]=1;
    int lc;
    for (int i=0;i<(int)c[cur].size();i++)
    {
        lc=lca(stk[top],c[cur][i]);
        while (dep[lc]<dep[stk[top]])
        {
            if (dep[stk[top-1]]<=dep[lc])
            {
                if (stk[top]!=lc)
                {
                    add_edge(lc,stk[top]);
                    --top;
                    stk[++top]=lc;
                }
                break;
            }
            add_edge(stk[top-1],stk[top]);
            --top;
        }
        stk[++top]=c[cur][i];
    }
    while (top>1)
    {
        add_edge(stk[top-1],stk[top]);
        --top;
    }
}
void ins(int u,int v,int tmp)
{
    int k=dep[u]-dep[v];
    int t=0;
    while ((1<<t)<=k) ++t;
    --t;
    insert(num[t][u],tot+tmp,1);
    k-=(1<<t);
    for (int i=16;i>=0;i--)
        if (k&(1<<i)) u=fa[i][u];
    insert(num[t][u],tot+tmp,1);
}
void dfs(int cur,int u,int fa)
{
    if (col[u]==cur) sz[u]=1; else sz[u]=0;
    for (int i=0;i<(int)e[u].size();i++)
    {
        int v=e[u][i];
        if (v!=fa)
        {
            dfs(cur,v,u);
            sz[u]+=sz[v];
        }
    }
    if (cur*sz[u]<=n) ins(u,fa,cur*sz[u]);
}
int main()
{
    scanf("%d",&n);
    for (int i=2;i<=n;i++)
    {
        scanf("%d",&fa[0][i]);
        g[fa[0][i]].push_back(i);
    }
    init();
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&col[i]);
        que[i]=col[i];
        c[col[i]].push_back(i);
    }
    sort(que+1,que+n+1);
    int m=1;
    for (int i=2;i<=n;i++)
        if (que[i]!=que[m]) que[++m]=que[i];
    memset(e,0,sizeof(e));
    for (int i=1;i<=m;i++)
    {
        int cur=que[i];
        sort(c[cur].begin(),c[cur].end(),cmp);
        virtree(cur);
        dfs(cur,1,0);
        for (int j=1;j<=total;j++)
        {
            int u=p[j];
            chk[u]=false;
            e[u].clear();
            sz[u]=0;
        }
        total=0;
    }
    save_graph();
    int l=1,r=n;
    while (r-l>1)
    {
        int mid=(l+r)/2;
        if (check(mid))
        {
            l=mid;
            save_graph();
        } else
        {
            r=mid;
            get_graph();
        }
    }
    get_graph();
    if (check(r)) printf("%d\n",r); else printf("%d\n",l);
    return 0;
}