// O(nlogn)
# include <iostream>

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

template <typename T>
void put(T x){
    static char s[20];
    int bas;
    
    if(x < 0) {
        putchar('-');
        x = -x;
    }
      
    if(x == 0) {
        putchar('0');
        return;
    }
      
    bas = 0;
    for(;x;x/=10)
        s[bas++] = x%10+'0';
          
    for(;bas--;)
        putchar(s[bas]);
}
  
const int mod = 998244353;
struct  Node {
    int a[2][2] = {{1,1},{1,0}};
    Node& operator* (Node& b ) {
        Node x;
        x.a[0][0] = 1ll * (1ll * this->a[0][0] * b.a[0][0] ) % mod + (1ll * this->a[0][1] * b.a[1][0] ) % mod;
        x.a[0][1] = 1ll * (1ll * this->a[0][0] * b.a[0][1] ) % mod + (1ll * this->a[0][1] * b.a[1][1] ) % mod;
        x.a[1][0] = 1ll * (1ll * this->a[1][0] * b.a[0][0] ) % mod + (1ll * this->a[1][1] * b.a[1][0] ) % mod;
        x.a[1][1] = 1ll * (1ll * this->a[1][0] * b.a[0][1] ) % mod + (1ll * this->a[1][1] * b.a[1][1] ) % mod;
          
        for (int i=0; i<2; i++) {
            for (int j=0; j<2; j++) {
                a[i][j] = x.a[i][j];
            }
        }
          
        return *this;
    }
};
  
Node qpow(Node x, int p) {
    Node ans;
    ans.a[0][0] = 1;
    ans.a[0][1] = 0;
    ans.a[1][0] = 0;
    ans.a[1][1] = 1;
  
    while (p) {
        if (p & 1) {
            ans = ans * x;
        }
        x = x * x;
        p >>= 1 ;
    }
      
    return ans;
}
  
void solve(int n) {
    if (n == 1 || n ==2){
        put(1);
        puts("");
        return;
    }
      
    Node a;
    a = qpow(a, n-1);
    put(a.a[0][0] % mod);
    puts("");
}
  
int main() {
    int T;
    read(T);
      
    while (T--) {
        int n;
        read(n);
          
        solve(n);
    }
      
    return 0;
}
