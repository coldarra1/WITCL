#include<stdio.h>
#include<math.h>
#include<string.h>
#include<string>
#include<stack>
#include<map>
#include<set>
#include<queue>
#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#define PI acos(-1)
#define pb push_back
#define all(x) x.begin(),x.end()
#define INF 0x3f3f3f3f
#define dd(x) cout<<#x<<" = "<<x<<","
#define de(x) cout<<#x<<" = "<<x<<"\n"
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int N=1e5+5;
struct node{
    int id1,id2,l,r;
};
node p[2*N];
int a[N],at[N],b[N],bt[N],ls[10*N],rs[10*N],cnt,n;
vector<int> v[10*N];
int build1(int l,int r){
    int now=++cnt;
    if(l==r){
        v[now].pb(p[l].id2);
        return cnt;
    } 
    int mid=(l+r)/2;
    ls[now]=build1(l,mid);
    rs[now]=build1(mid+1,r);
    v[now].pb(ls[now]);
    v[now].pb(rs[now]);
    return now;
}
int build2(int l,int r){
    int now=++cnt;
    if(l==r){
        v[p[l].id1].pb(cnt);
        return cnt;
    }
    int mid=(l+r)/2;
    ls[now]=build2(l,mid);
    rs[now]=build2(mid+1,r);
    
    v[ls[now]].pb(now);
    v[rs[now]].pb(now);
    return now;
}
void link1(int id,int ql,int qr,int l,int r,int k){
    if(ql>r||qr<l){
        return;
    }
    else if(ql<=l&&qr>=r){
        v[id].pb(k);
        return;
    }
    int mid=(l+r)/2;
    link1(id,ql,qr,l,mid,ls[k]);
    link1(id,ql,qr,mid+1,r,rs[k]);
}
void link2(int id,int ql,int qr,int l,int r,int k){
    if(ql>r||qr<l){
        return;
    }
    else if(ql<=l&&qr>=r){
        v[k].pb(id);
        return;
    }
    int mid=(l+r)/2;
    link2(id,ql,qr,l,mid,ls[k]);
    link2(id,ql,qr,mid+1,r,rs[k]);
}
bool cmp(node a,node b){
    if(a.l!=b.l)
    return a.l<b.l;
    return a.r<b.r; 
}
int dfn[10*N],low[10*N],belong[10*N],cnt1,cnt2;
int s[10*N],top;
void tarjan(int x){
    dfn[x]=low[x]=++cnt1;
    s[++top]=x;
    for(int i=0;i<v[x].size();i++){
        if(!dfn[v[x][i]]){
            tarjan(v[x][i]); 
            low[x]=min(low[x],low[v[x][i]]);
        }
        else if(!belong[v[x][i]]){
            low[x]=min(low[x],dfn[v[x][i]]);
        }
    }
    if(dfn[x]==low[x]){
        cnt2++;
        while(1){
            belong[s[top]]=cnt2;
            if(s[top]==x){
                top--;
                break;
            }
            top--;
        }
    }
}
int temp[2*N];
int rt1,rt2;
void init(){
    for(int i=1;i<=cnt;i++){
        v[i].clear();
    }
    cnt=0;
    for(int i=1;i<=n;i++){
        p[i]={cnt+1,cnt+2,a[i],a[i]+at[i]};
        p[i+n]={cnt+2,cnt+1,b[i],b[i]+bt[i]};
        cnt+=2; 
    }
    sort(p+1,p+2*n+1,cmp);
    for(int i=1;i<=2*n;i++){
        temp[i]=p[i].l;
    }
    rt1=build1(1,2*n);
    rt2=build2(1,2*n);
    for(int i=1;i<=2*n;i++){
        int pos1=lower_bound(temp+1,temp+2*n+1,p[i].l)-temp;
        int pos2=upper_bound(temp+1,temp+2*n+1,p[i].r)-temp-1;
        link1(p[i].id1,pos1,i-1,1,2*n,rt1);
        link1(p[i].id1,i+1,pos2,1,2*n,rt1);
        link2(p[i].id2,pos1,i-1,1,2*n,rt2);
        link2(p[i].id2,i+1,pos2,1,2*n,rt2);
    }
} 
bool check(int mid){
    for(int i=1;i<=cnt;i++){
        dfn[i]=low[i]=belong[i]=0;
    }
    cnt1=cnt2=top=0;
    int num=0;
    for(int i=1;i<=n;i++){
        if(a[i]+at[i]>mid){
            v[num+1].pb(num+2); 
        }
        if(b[i]+bt[i]>mid){
            v[num+2].pb(num+1);
        }
        num+=2; 
    }
    for(int i=1;i<=2*n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    num=0;
    for(int i=1;i<=n;i++){
        if(a[i]+at[i]>mid){
            v[num+1].pop_back();
        }
        if(b[i]+bt[i]>mid){
            v[num+2].pop_back();
        }
        num+=2; 
    }
    for(int i=1;i<=2*n;i+=2){
        if(belong[i]==belong[i+1])
        return false;
    }
    return true;
} 

int c[2*N];
int main()
{
    int t;
    scanf("%d",&t);
    while(scanf("%d",&n)!=EOF){
        t--;
        int l=n,r=0;
        for(int i=1;i<=n;i++){
            scanf("%d%d%d%d",&a[i],&at[i],&b[i],&bt[i]);
            c[++r]=a[i]+at[i];
            c[++r]=b[i]+bt[i];
        }
        init();
        if(!check(2e9)){
            printf("-1\n");
            continue;
        }
        sort(c+1,c+r+1);
        int ans=-1;
        while(l<=r){
            int mid=(l+r)/2;
            if(check(c[mid])){
                ans=c[mid];
                r=mid-1; 
            }
            else{
                l=mid+1;
            }
        }
        printf("%d\n",ans);
    }
}
