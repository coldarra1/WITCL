#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
 
int c[200010];
long long c2[200010];
int lowbit(int x)
{
    return x&(-x);
}
void add(int i,int val)
{
    long long tt = (long long)val*i;
    while(i <= 200000)
    {
        c[i] += val;
        c2[i] += tt;
        i += lowbit(i);
    }
}
int sum(int i)
{
    int s = 0;
    while(i > 0)
    {
        s += c[i];
        i -= lowbit(i);
    }
    return s;
}
int sum(int l,int r)
{
    if(l > r)return 0;
    return sum(r) - sum(l-1);
}
long long sum2(int i)
{
    long long s = 0;
    while(i > 0)
    {
        s += c2[i];
        i -= lowbit(i);
    }
    return s;
}
struct Node
{
    int x,y,z;
    void input()
    {
        scanf("%d%d%d",&x,&y,&z);
    }
}node[100010];
vector<int>avec[100010];
vector<int>dvec[100010];
 
int main()
{
    // freopen("1.in","r",stdin);
    // freopen("1.out","w",stdout);
    int T;
    int iCase = 0;
    int n;
    scanf("%d",&T);
    while(T--)
    {
        iCase++;
        printf("Case #%d: ",iCase);
        scanf("%d",&n);
        for(int i = 1;i <= n;i++)
            node[i].input();
        for(int i = 1;i <= n;i++)
        {
            avec[i].clear();
            dvec[i].clear();
        }
        int m;
        int t,L,R;
        scanf("%d",&m);
        while(m--)
        {
            scanf("%d%d%d",&t,&L,&R);
            avec[L].push_back(t);
            dvec[R].push_back(t);
        }
        set<int>st;
        set<int>::iterator it;
        memset(c,0,sizeof(c));
        memset(c2,0,sizeof(c2));
        long long ans = 0;
        for(int i = 1;i <= n;i++)
        {
            int sz1 = avec[i].size();
            for(int j = 0;j < sz1;j++)
            {
                if(st.empty())
                {
                    st.insert(avec[i][j]);
                    continue;
                }
                it = st.lower_bound(avec[i][j]);
                if(it != st.begin() && it != st.end())
                {
                    int tp1 = (*it);
                    it--;
                    int tp2 = (*it);
                    it++;
                    add(tp1-tp2,-1);
                }
                if(it != st.end())
                    add((*it)-avec[i][j],1);
                if(it != st.begin())
                {
                    it--;
                    add(avec[i][j]-(*it),1);
                }
                st.insert(avec[i][j]);
            }
 
            if(!st.empty())
            {
                int first = *(st.begin());
                long long tmp = node[i].x + (long long)node[i].y*first;
                if(tmp > node[i].z)tmp = node[i].z;
                ans += tmp;
                if(node[i].y > 0)
                {
                    int tt = node[i].z/node[i].y;
                    if(tt > 200000)tt = 200000;
                    ans += (long long)sum2(tt)*node[i].y;
                    ans += (long long)node[i].z * sum(tt+1,200000);
                }
            }
            int sz2 = dvec[i].size();
            for(int j = 0;j < sz2;j++)
            {
                it = st.lower_bound(dvec[i][j]);
                it++;
                if(it != st.end())
                    add((*it)-dvec[i][j],-1);
                it--;
                if(it != st.begin())
                {
                    it--;
                    add(dvec[i][j]-(*it),-1);
                }
                st.erase(dvec[i][j]);
                it = st.lower_bound(dvec[i][j]);
                if(it != st.end() && it != st.begin())
                {
                    int tp1 = *it;
                    it--;
                    int tp2 = *it;
                    add(tp1-tp2,1);
                }
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
