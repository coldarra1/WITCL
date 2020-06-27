#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxx=500+10;
const ll mod=10;
int a[maxx][maxx],ans[maxx][maxx];
int main(){
    int n; cin>>n;
    for(int i=1;i<=n;i++){
        string s; cin>>s;
        for(int j=0;j<n;j++){
            a[i][j+1]=s[j]-'0';
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            ans[i][j]=a[i][j];
            if(ans[i][j]){
                for(int k=j+1;k<=n;k++){
                    a[i][k]=(a[i][k]-a[j][k]+mod)%mod;
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            cout<<ans[i][j]; puts("");
    }
}


