#include <iostream>		// jk
#include <string.h>
#include <algorithm>

using namespace std;

char board[105][105];
int m, n, q;

int checkLogic(int i, int j) {
    int count = 0;
    int left = j - 1;
    int right = j + 1;
    int top = i - 1;
    int bottom = i + 1;
    for(int x = top; x <= bottom; x++){
        for(int y = left; y <= right; y++){
            count = board[x][y] == 1 || board[x][y] == -1 ? count + 1 : count;
        }
    }
    return board[i][j] == 1 ? (count == 3 || count == 4 ? 1 : -1) : (count == 3 ? -2 : 0);
}

void update() {
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            board[i][j] = checkLogic(i, j);
        }
    }
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            board[i][j] = board[i][j] == 1 || board[i][j] == -2 ? 1 : 0;
        }
    }
}

int main() {
    cin >> m >> n >> q;
    memset(board, 0, sizeof(board));
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> board[i][j];
            board[i][j] -= '0';
        }
    }

    while (q--) update();

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << (int)board[i][j] << " \n"[j==n];
        }
    }
    return 0;
}
