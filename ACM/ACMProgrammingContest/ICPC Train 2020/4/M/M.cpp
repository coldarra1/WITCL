#include <bits/stdc++.h>
#define N 2005
#define fi first
#define sc second
using namespace std;

int a[N];

unordered_map<int,int> mp;

int main(){
    int tt;
    scanf("%d",&tt);
    while(tt--){
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]); mp[a[i]]++;
        }
        int num=0;
        mp[a[1]]--;
        for(int j=2;j<=n-1;j++){
            mp[a[j]]--;
            for(int i=1;i<j;i++){
                int val=2*a[j]-a[i];
                if(mp.find(val)!=mp.end()){
                    num+=mp[val];
                }
            }
        }
        printf("%d\n",num);
        mp.clear();
    }
}


