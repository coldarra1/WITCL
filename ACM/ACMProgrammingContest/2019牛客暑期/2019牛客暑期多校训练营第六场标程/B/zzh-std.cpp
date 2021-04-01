#include <bits/stdc++.h>

const int N = 130;

char s[N];
int a[N];

std::string get(int l, int r){
    std::string ret;
    for (int i = 0; i < 8; ++ i){
        static char buf[N];
        if (i == l){
            ret += l == 0 ? "::" : ":";
            i = r;
        }
        else if (i < 7){
            sprintf(buf, "%x:", a[i]);
            ret += buf;
        }
        else{
            sprintf(buf, "%x", a[i]);
            ret += buf;
        }
    }
    return ret;
}

void update(std::string &ans, const std::string &cur){
    if (ans.empty()){
        ans = cur;
    }
    else if (ans.size() > cur.size()){
        ans = cur;
    }
    else if (ans.size() == cur.size() && ans > cur){
        ans = cur;
    }
}

void solve(){
    scanf("%s", s);
    memset(a, 0, sizeof(a));
    for (int i = 0; i < 8; ++ i){
        for (int j = 0; j < 16; ++ j) {
            a[i] = a[i] << 1 | (s[i * 16 + j] - '0');
        }
    }
    int now = -1;
    std::string ans = get(-1, -1);
    for (int i = 0; i <= 8; ++ i){
        if (a[i] || i == 8){
            int l = now + 1, r = i - 1;
            if (r - l + 1 >= 2){
                update(ans, get(l, r));
            }
            now = i;
        }
    }
    puts(ans.c_str());
}

int main(){
    int test;
    scanf("%d", &test);
    for (int i = 1; i <= test; ++ i){
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}
