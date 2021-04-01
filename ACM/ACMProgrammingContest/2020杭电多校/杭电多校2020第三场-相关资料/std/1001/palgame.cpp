#include<cstdio>
const int N=100010,S=26;
int T,n,m,i,A,B,C,D,ans;char s[N];
struct AP{
  int s,d,r;
  AP(){}
  AP(int _s,int _d,int _r){s=_s,d=_r?_d:0,r=_r;}
}a[N],b[N];
struct Eertree{
  int all,son[N][S],fail[N],len[N],diff[N],top[N],text[N],last,tot,f[N];
  int newnode(int l){
    for(int i=0;i<S;i++)son[tot][i]=0;
    fail[tot]=diff[tot]=top[tot]=0,len[tot]=l;
    return tot++;
  }
  void init(){
    last=tot=all=0;
    newnode(0),newnode(-1);
    text[0]=-1,fail[0]=1;
  }
  int getfail(int x){
    while(text[all-len[x]-1]!=text[all])x=fail[x];
    return x;
  }
  void add(int w){
    w-='a';
    text[++all]=w;
    int x=getfail(last);
    if(!son[x][w]){
      int y=newnode(len[x]+2);
      int z=son[getfail(fail[x])][w];
      son[x][w]=y;
      fail[y]=z;
      diff[y]=len[y]-len[z];
      if(diff[y]!=diff[z]||len[z]<1)top[y]=y;else top[y]=top[z];
    }
    last=son[x][w];
    f[all]=last;
  }
  void get(int x,int lim,AP q[],int&cnt){
    cnt=0;
    x=f[x];
    while(len[x]>0){
      int y=top[x];
      if(len[y]<=lim){
        if(len[x]<=lim){
          q[++cnt]=AP(len[x],diff[x],(len[x]-len[y])/diff[x]);
        }else{
          q[++cnt]=AP(lim,diff[x],(lim-len[y])/diff[x]);
        }
      }
      x=fail[y];
    }
  }
}DS;
inline int query(int A,int B,int C,int D){
  int ca,cb,i,j,F,G;
  DS.get(B,B-A+1,a,ca);
  DS.get(D,D-C+1,b,cb);
  a[ca+1]=AP(0,0,0);
  b[cb+1]=AP(0,0,0);
  for(i=j=1;i<=ca&&j<=cb;){
    if(a[i].s!=b[j].s){
      if(a[i].s<b[j].s)return -1;
      return 1;
    }
    if(a[i].d==b[j].d){
      if(a[i].r==b[j].r){
        i++;
        j++;
        continue;
      }
      if(a[i].r<b[j].r){
        F=a[i+1].s;
        G=b[j].s-(a[i].r+1)*b[j].d;
      }else{
        F=a[i].s-(b[j].r+1)*a[i].d;
        G=b[j+1].s;
      }
    }else{
      F=a[i].r?a[i].s-a[i].d:a[i+1].s;
      G=b[j].r?b[j].s-b[j].d:b[j+1].s;
    }
    if(F<G)return -1;
    if(F>G)return 1;
    if(a[i].r){
      a[i].r--;
      a[i].s-=a[i].d;
    }else i++;
    if(b[j].r){
      b[j].r--;
      b[j].s-=b[j].d;
    }else j++;
  }
  if(i>ca&&j>cb)return 0;
  if(i<=ca)return 1;
  return -1;
}
int main(){
  scanf("%d",&T);
  while(T--){
    scanf("%d%s",&n,s+1);
    DS.init();
    for(i=1;i<=n;i++)DS.add(s[i]);
    scanf("%d",&m);
    while(m--){
      scanf("%d%d%d%d",&A,&B,&C,&D);
      ans=query(A,B,C,D);
      if(ans==-1)puts("sjfnb");
      else if(ans==1)puts("cslnb");
      else puts("draw");
    }
  }
}