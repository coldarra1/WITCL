#include<bits/stdc++.h>
const int MAX_N = 2000000;
char s[MAX_N + 1];
int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        int n;
        scanf("%d", &n);
        scanf("%s", s);
        for(int i = 0; i < n; i++) s[i] -= '0';
        int an=0;
        int clam_cnt = 0;
        for(int i = 0; i < n; i++) {
            if(s[i] & 2) an++;
            else if(s[i] & 1) clam_cnt++;
            else {
                if(clam_cnt > 0) {
                    clam_cnt --;
                    an++;
                }
            }
        }
        printf("%d\n", an + clam_cnt / 2);
    }
    return 0;
}
