#include<stdio.h>
#include<string.h>
const int MAXN=1e6+5;
char s[MAXN];
char ss[MAXN];
int a,n;
int main()
{
    scanf("%s%d",s+1,&n);
    int len=strlen(s+1);
    for(int i=1;i<=len;i++)a=a*10+s[i]-'0';
    for(int i=1;i<=n;i++)
    {
        scanf("%s",ss+1);
        for(int j=1;j<=9;j++)
        {
            int flag=1;
            for(int k=1;k<=len;k++)
            {
                int x=s[k]-'0',y=ss[k]-'0';
                if(x*j%10!=y)
                {
                    flag=0;
                    break;
                }
            }
            if(flag)
            {
                a*=j;
                break;
            }
        }
        strcpy(s+1,ss+1);
    }
    printf("%d",a);
}
