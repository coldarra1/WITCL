#include<stdio.h>
#include <math.h>
int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        int n;
        scanf("%d",&n);
        printf("%d\n",(int)log2(n)+1);
    }
    return 0;
}