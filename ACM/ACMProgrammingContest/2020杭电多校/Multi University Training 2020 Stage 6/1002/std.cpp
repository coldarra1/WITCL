#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

string raw,num1,num2,num3;
char o;
int minr;

void init()
{
    num1.clear();
    num2.clear();
    num3.clear();
    minr=2;
}

void get_num()
{
    int now=1;
    for (char c:raw)
    {
        if (!isdigit(c) && !isalpha(c))
        {
            now++;
            if (c!='=') o=c;
        }
        else
        {
            if (isdigit(c)) minr=max(minr,c-'0'+1);
            else minr=max(minr,c-'A'+11);
            if (now==1) num1+=c;
            else if (now==2) num2+=c;
            else num3+=c;
        }
        
    }
}

long long cal(string s,int r)
{
    long long re=0;
    for (char c:s)
    {
        if (isdigit(c)) re=re*r+c-'0';
        else re=re*r+c-'A'+10;
    }
    return re;
}

bool check(int r)
{
    long long t1=cal(num1,r);
    long long t2=cal(num2,r);
    long long t3=cal(num3,r);
    if (o=='+') return t1+t2==t3;
    if (o=='-') return t1-t2==t3;
    if (o=='*') return t1*t2==t3;
    if (t2==0) return false;
    if (t1%t2) return false;
    return t1/t2==t3;
}

int get_ans()
{
    for (int i=minr;i<=16;i++)
    {
        if (check(i)) return i;
    }
    return -1;
}

int main()
{
    while (cin>>raw)
    {
        init();
        get_num();
        cout<<get_ans()<<'\n';
    }
    getchar(); getchar();
    return 0;
}