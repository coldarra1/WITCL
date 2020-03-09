# include <iostream>
# include <queue>

const int INF = 0x3f3f3f3f;
typedef std::pair<int, int> P;
char maze[1005][1005];
int sx = 0;
int sy = 0;
int d[1005][1005];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
  
int n;
int m;
  
int bfs() {
    std::queue<P> que;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            d[i][j] = INF;
        }
    }
      
    que.push(P(sx, sy));
    d[sx][sy] = {0};
      
    while (que.size()) {
        P p = que.front();
        que.pop();
  
        for (int i=0; i<4; i++) {
            int nx = p.first + dx[i];
            int ny = p.second + dy[i];
              
            if (0<=nx && nx<n && 0<=ny && ny<m && maze[nx][ny]!='*' && d[nx][ny]==INF) {
                que.push(P(nx, ny));
                d[nx][ny] = d[p.first][p.second] + 1;
            }
        }
    }
      
    int max = 0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (d[i][j] > max && d[i][j]!=INF) {
                max = d[i][j];
            }
        }
    }
      
    return max;
}
  
int main() {
    std::cin >> n >> m;
    std::cin.ignore(1, '\n');
      
    for (int i=0; i<n; i++) {
        std::cin >> maze[i];
        std::cin.ignore(1, '\n');
    }
      
    std::cout << bfs();
      
    return 0;
}
