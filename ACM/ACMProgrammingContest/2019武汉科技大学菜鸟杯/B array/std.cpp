#include<stdio.h>
#include <math.h>
using namespace std;
typedef long long ll;
double len[1000];
int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        int a1,a2,k;
        scanf("%d%d%d",&a1,&a2,&k);
        len[1]=log10(a1);len[2]=log10(a2);
        for(int i=1;;i++){
            if(i>2) len[i]=len[i-1]+len[i-2];
            if((int)len[i]+1>k){printf("%d\n",i);break;}
        }
    }
    return 0;
}