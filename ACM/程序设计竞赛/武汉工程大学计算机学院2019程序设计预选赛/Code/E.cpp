# include <iostream>	// kcxz ?
# include <cstdio>

bool vis[705];
int pos[705];

int main(){
	int n;
	int k;
    scanf("%d %d", &n, &k);
    
    int x;
    for (int i=1; i<=k; i++) {
    	scanf("%d", &x);
        vis[x] = true;
	} 
    
	int j = 0;
    for (int i=1; i<=n+k; i++) {
    	if(!vis[i]) {
    		pos[++j] = i;
		}
	}
	
    n /= 10;
    printf("%d %d\n%d %d\n%d %d\n", pos[1], pos[n], pos[n+1], pos[n*3], pos[n*3+1], pos[n*6]);
    
    return 0;
}
