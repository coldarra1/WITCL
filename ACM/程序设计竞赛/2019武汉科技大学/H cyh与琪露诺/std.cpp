#include<bits/stdc++.h>
using namespace std;
bool cmp(int a,int b)
{
    return a>b;
}
const int N=1e3+10;
int a[N];
int la[10][11],cur[10][11];
bool check(int a[],int b[],int x)
{
    a[x]++;

    for(int i=9; i>=0; i--)
    {
        if(a[i]>b[i])
        {
            a[x]--;
            return 1;
        }
        else if(a[i]<b[i])
        {
            a[x]--;
            return 0;
        }
    }
    a[x]--;
    return 1;
}
void cpy(int a[],int b[],int x)
{

    for(int i=0; i<=10; i++)
        a[i]=b[i];
    a[x]++;
    a[10]++;
}
void cpy2(int a[],int b[])
{
    for(int i=0; i<=10; i++)
        a[i]=b[i];
}
int main()
{

    int n;
    freopen("20.in","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
     freopen("20.out","w",stdout);
  //  clock_t bg,ed;
 //   bg=clock();
    scanf("%d",&n);
    for(int i=1; i<=n; i++)
    {
        scanf("%d",&a[i]);
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1; i<=n; i++)
    {
        for(int j=0; j<9; j++)
        {
            int mo=(j-a[i]+9)%9;
            if(la[mo][10]==0&&la[j][10]==0&&j!=a[i]%9)
                continue;
            int tl=la[mo][10],tr=la[j][10];
            if(tl+1>tr||(tl+1==tr&&check(la[mo],la[j],a[i])))
            {
                cpy(cur[j],la[mo],a[i]);
            }
            else
                cpy2(cur[j],la[j]);
            //cout<<dp[i][j]<<endl;

        }
        for(int j=0; j<9; j++)
            cpy2(la[j],cur[j]);

    }
    if(cur[0][10])
    {
        if(cur[0][10]==cur[0][0])
        {
            printf("0");
            return 0;
        }
        for(int i=9; i>=0; i--)
            for(int j=1; j<=cur[0][i]; j++)
            {
                printf("%d",i);
            }
    }
    else
        printf("cyhnb");
  //  ed=clock();
   // cout<<'\n';
    //cout<<"time:"<<(ed-bg)*1000.0/CLOCKS_PER_SEC<<"ms";
    return 0;
}
