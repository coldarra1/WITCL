#include<bits/stdc++.h>		// Enal
 
using namespace std;
 
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        char c[200];
        scanf("%s",c);
        int cnt=0,maxnum=0;
        for(int j=0;j<strlen(c);++j){
            if(c[j]=='('){
                ++cnt;
            }else{
                --cnt;
            }
            if(cnt<0){
                puts("-1");
                break;
            }else{
                maxnum=max(cnt,maxnum);
            }
        }
        if(cnt==0){
            cout<<maxnum-1<<endl;
        }else if(cnt>0){
            puts("-1");
        }
    }
    return 0;
}