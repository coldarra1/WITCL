#include<bits/stdc++.h>
#define N 20005
#define Ms(a,b) memset(a,b,sizeof a)
#define db(x) cerr<<#x<<"="<<x<<endl;
#define db2(x,y) cerr<<#x<<"="<<x<<" "<<#y<<"="<<y<<endl;
#define db3(x,y,z) cerr<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl;
using namespace std;
char s[N];
struct BIGINT{
    int a[185],l;
    void clr(){Ms(a,l=0);}
    BIGINT operator +(const BIGINT &b)const{
        BIGINT c;c.clr();
        c.l=max(l,b.l);
        for(int i=1;i<=c.l;i++){
            c.a[i]+=a[i]+b.a[i];
            while(c.a[i]>9)c.a[i]-=10,c.a[i+1]++;
        }
        if(c.a[c.l+1])c.l++;
        return c;
    }
    BIGINT operator *(const BIGINT &b)const{
        BIGINT c;c.clr();
        c.l=l+b.l-1;
        for(int i=1;i<=l;i++)
            for(int j=1;j<=b.l;j++)
                c.a[i+j-1]+=a[i]*b.a[j];
        for(int i=1;i<=c.l;i++){
            c.a[i+1]+=c.a[i]/10,c.a[i]%=10;
            if(c.a[c.l+1])c.l++;
        }
        return c;
    }
    void operator +=(BIGINT b){*this=*this+b;}
    void div2(){
        for(int i=l;i>=1;i--){
            if(a[i]&1)a[i-1]+=10;
            a[i]>>=1;
        }
        if(l&&!a[l])l--;
    }
    void Print(){
        for(int i=l;i>=1;i--)printf("%d",a[i]);
        puts("");
    }
}stk[N];
int n,tp;
BIGINT Pow(BIGINT &b){
    BIGINT a,res;
    a.clr(),res.clr();
    a.a[1]=2,a.l=1;
    res.a[1]=1,res.l=1;
    while(b.l){
        if(b.a[1]&1)res=res*a;
        b.div2();
        if(b.l)a=a*a;
    }
    return res;
}
int main(){
    scanf("%s",s+1),n=strlen(s+1);
    for(int i=1;i<=n;i++){
        if(s[i]=='2'&&s[i+1]!='(')stk[tp].a[1]+=2;
        if(s[i]=='(')++tp,stk[tp].l=1;
        if(s[i]==')')stk[tp-1]+=Pow(stk[tp]),tp--;
    }
    stk[0].Print();
    return 0;
}
