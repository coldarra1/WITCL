#include <bits/stdc++.h>
using namespace std;
#define modp1 998244353
#define modp2 100000007
#define Maxn 4007
#define Maxlen 267
#define inf 10007
const char op1[]="<<<<<<< branch1";
const char op2[]="=======";
const char op3[]=">>>>>>> branch2";
const int base=307;
pair<int,int> op1_hash,op2_hash,op3_hash;
char s1[Maxn][Maxlen],s2[Maxn][Maxlen];
int len1[Maxn],len2[Maxn];
char s[Maxlen];
int n1=0,n2=0;
pair<int,int> hash1[Maxn],hash2[Maxn];
short f[Maxn][Maxn][3],g[Maxn][Maxn][3];
pair<pair<int,int>,int> que[Maxn];
int cnt=0;
int main()
{
    op1_hash=make_pair(0,0);
    for (int i=0;i<strlen(op1);i++)
    {
        op1_hash.first=(1LL*base*op1_hash.first+op1[i]+1)%modp1;
        op1_hash.second=(1LL*base*op1_hash.second+op1[i]+1)%modp2;
    }
    op2_hash=make_pair(0,0);
    for (int i=0;i<strlen(op2);i++)
    {
        op2_hash.first=(1LL*base*op2_hash.first+op2[i]+1)%modp1;
        op2_hash.second=(1LL*base*op2_hash.second+op2[i]+1)%modp2;
    }
    op3_hash=make_pair(0,0);
    for (int i=0;i<strlen(op3);i++)
    {
        op3_hash.first=(1LL*base*op3_hash.first+op3[i]+1)%modp1;
        op3_hash.second=(1LL*base*op3_hash.second+op3[i]+1)%modp2;
    }
    int cur_status=0;
    char ch=getchar();
    while (ch!=EOF)
    {
        int len=0;
        while (ch!='\n'&&ch!=EOF)
        {
            s[len++]=ch;
            ch=getchar();
        }
        pair<int,int> h=make_pair(0,0);
        for (int i=0;i<len;i++)
        {
            h.first=(1LL*base*h.first+s[i]+1)%modp1;
            h.second=(1LL*base*h.second+s[i]+1)%modp2;
        }
        if (h==op1_hash) cur_status=1;
        else if (h==op2_hash) cur_status=2;
        else if (h==op3_hash) cur_status=0;
        else
        {
            if (cur_status!=1)
            {
                len2[++n2]=len;
                hash2[n2]=h;
                for (int i=0;i<len;i++)
                    s2[n2][i]=s[i];
            }
            if (cur_status!=2)
            {
                len1[++n1]=len;
                hash1[n1]=h;
                for (int i=0;i<len;i++)
                    s1[n1][i]=s[i];
            }
        }
        if (ch!=EOF) ch=getchar();
    }
    for (int i=0;i<=n1;i++)
        for (int j=0;j<=n2;j++)
            for (int k=0;k<3;k++)
                f[i][j][k]=inf,g[i][j][k]=0;
    f[0][0][0]=0;
    f[0][0][1]=1;
    g[0][0][1]=0;
    f[0][0][2]=1;
    g[0][0][2]=0;
    for (int i=0;i<=n1;i++)
        for (int j=0;j<=n2;j++)
        {
            if (i==0&&j==0) continue;
            if (i>0)
            {
                if (f[i][j][1]>f[i-1][j][1]+1)
                {
                    f[i][j][1]=f[i-1][j][1]+1;
                    g[i][j][1]=-1;
                }
            }
            if (j>0)
            {
                if (f[i][j][2]>f[i][j-1][2]+1)
                {
                    f[i][j][2]=f[i][j-1][2]+1;
                    g[i][j][2]=-1;
                }
            }
            if (i>0&&j>0&&hash1[i]==hash2[j])
            {
                if (f[i][j][0]>f[i-1][j-1][0]+1)
                {
                    f[i][j][0]=f[i-1][j-1][0]+1;
                    g[i][j][0]=-1;
                }
            }
            for (int k1=0;k1<3;k1++)
                for (int k2=0;k2<3;k2++)
                    if (f[i][j][k1]>f[i][j][k2]+1)
                    {
                        f[i][j][k1]=f[i][j][k2]+1;
                        g[i][j][k1]=k2;
                    }
        }
    que[++cnt]=make_pair(make_pair(n1,n2),0);
    while (que[cnt].first.first!=0||que[cnt].first.second!=0||que[cnt].second!=0)
    {
        int x=que[cnt].first.first;
        int y=que[cnt].first.second;
        int k=que[cnt].second;
        if (g[x][y][k]!=-1) k=g[x][y][k];
        else if (k==0) --x,--y;
        else if (k==1) --x;
        else --y;
        que[++cnt]=make_pair(make_pair(x,y),k);
    }
    for (int i=cnt-1;i;i--)
    {
        int x=que[i].first.first;
        int y=que[i].first.second;
        int k=que[i].second;
        if (g[x][y][k]!=-1)
        {
            if (g[x][y][k]==0)
            {
                if (k==1) printf("#ifdef branch1\n");
                else if (k==2) printf("#ifdef branch2\n");
            } else
            {
                if (k==0) printf("#endif\n");
                else printf("#else\n");
            }
        } else
        {
            if (k==1)
            {
                for (int i=0;i<len1[x];i++)
                    printf("%c",s1[x][i]);
                printf("\n");
            } else
            {
                for (int i=0;i<len2[y];i++)
                    printf("%c",s2[y][i]);
                printf("\n");
            }
        }
    }
    return 0;
}
