#include<cstdio>
typedef unsigned long long ull;
const int N=3000005;
int Case,i;ull A,B,C,f[N];
inline ull read(){
  int n,i,x;ull ret=0;
  scanf("%d",&n);
  for(i=1;i<=n;i++){
    scanf("%d",&x);
    if(x)ret+=f[i];
  }
  return ret;
}
int main(){
  for(f[1]=1,f[2]=2,i=3;i<N;i++)f[i]=f[i-1]+f[i-2];
  scanf("%d",&Case);
  while(Case--){
    A=read();
    B=read();
    C=read();
    A*=B;
    for(i=1;C+f[i]!=A;i++);
    printf("%d\n",i);
  }
}