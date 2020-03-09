# include <iostream>
# include <set>

template <typename T>
void read(T &val) {
    T x = 0;
    int bz = 1;
    char c;
     
    for (c = getchar(); (c<'0' || c>'9') && c != '-';
    c = getchar());
     
    if (c == '-') {
        bz = -1;
        c = getchar();
    }
     
    for (; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - 48;
         
    val = x * bz;
}
 
const int MAXN = 100000 + 5;
int f[MAXN];
int s[MAXN];
 
int findfa(int x){
    return (f[x] == x) ? x : f[x] = findfa(f[x]);
}
 
void merge(int x, int y) {
    f[x] = y;
}
 
int main(){
    int T;
    std::cin >> T;
     
    while (T--) {
        int n, m, t;
        read(n);
        read(m);
        read(t);
        int cnt = 0;
         
        for(int i=1;i<=n;i++){
            f[i] = i;
        }
         
        for (int i=1; i<=m; i++) {
            read(s[i]);
        }
         
        for(int i=1; i<=t; i++){
            int u, v;
            read(u);
            read(v);
             
            if(findfa(u) != findfa(v)){
                merge(f[u], f[v]);
            }
        }
         
        std::set<int> st;
        for (int i=1; i<=m; i++) {
            st.insert(findfa(s[i]));
        }
         
        for (int i=1; i<=n; i++) {
            if (st.find(findfa(f[i])) != st.end()) {
                ++cnt;
            }
        }
         
        std::cout << cnt << "\n";
    }
    
    return 0;
}
