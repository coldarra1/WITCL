# include <iostream>
# include <cstdlib>
# include <cstdio>
# include <cstring>
# include <queue>
 
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
  
int n, m;          
char maze[1005][1005];
int d[1005][1005];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
 
int sx;    
int sy;        
int gx;    
int gy;    
 
const int INF = 0x3f3f3f3f;
 
typedef std::pair<int, int> P;
 
bool check(int nx, int ny) {
    return 0<=nx && nx<n && 0<=ny && ny<m && d[nx][ny]==INF && maze[nx][ny]!='*';
}
 
void bfs() {
    memset(d, 0x3f, sizeof(d));
     
    std::queue<P> que;
 
    que.push(std::make_pair(sx, sy));
    d[sx][sy] = 0;
     
 
    while (que.size()) {
        P p = que.front();
        que.pop();
         
        if (p.first==gx && p.second==gy) {
            break;
        }
         
        for (int i=0; i<4; i++) {
            int nx = p.first + dx[i];
            int ny = p.second + dy[i];
             
            if (check(nx, ny)) {
                que.push(std::make_pair(nx, ny));
                d[nx][ny] = d[p.first][p.second] + 1;          
            }
        }
    }
}
 
int main() {
    int T;
    std::cin >> T;
     
    while (T--) {
        std::cin >> n >> m;
         
        for (int i=0; i<n; i++) {
			scanf("%s", maze[i]);
        }
            
        int x1;
        int y1;
        int x2;
        int y2;
        int x3;
        int y3;
        read(x1);
        read(y1);
        read(x2);
        read(y2);
        read(x3);
        read(y3);
        sx = x1 - 1;
        sy = y1 - 1;
        gx = x2 - 1;
        gy = y2 - 1;
        bfs();
         
        int t1 = d[gx][gy];
         
        sx = x2 - 1;
        sy = y2 - 1;
        gx = x3 - 1;
        gy = y3 - 1;
        bfs();
         
        int t2 = d[gx][gy];
         
        if (t1 == INF || t2 == INF) {
            std::cout << "-1\n";
            continue;
        }
         
        std::cout << 1ll * t1 + t2 << "\n";
    }
     
    return 0;
}
