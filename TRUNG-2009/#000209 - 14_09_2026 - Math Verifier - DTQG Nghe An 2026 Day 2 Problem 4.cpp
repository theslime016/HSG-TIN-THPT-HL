#include <bits/stdc++.h>
using namespace std;

const int maxn = 50;

bool A[100][100];
int dx[] = {1, -1, 1, -1};
int dy[] = {1, -1, -1, 1};
bool check(int i, int j, int x, int y) {
    if (x == i || y == j) return true;
    for (int h = 0; h < 4; h++) {
        int tempx = x;
        int tempy = y;
        while (tempx >= 1 && tempx <= maxn && tempy >= 1 && tempy <= maxn) {
            if (tempx == i && tempy == j) return true;
            tempx += dx[h];
            tempy += dy[h];
        }
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    for (int x = 1; x <= maxn; x++) {
        for (int y = 1; y <= maxn; y++) {
            int newx, newy;
                newx = x + y - 1;
                newy = 1;
int tempx = x, tempy = y;
            for (;
            tempx >= 1 && tempx <= maxn && tempy >= 1 && tempy <= maxn;
                tempx++, tempy--
            ) {
                if (tempy == 1) break;
            }
            if (tempx != newx && tempy != newy) {
                cout << x << ' ' << y << ' ' << tempx << ' ' << tempy << ' ' << newx << ' ' << newy << '\n';
                return 0;
            }
        }
    }


    return 0;

    for (int i = 1; i <= maxn; i++) {
        for (int j = 1; j <= maxn; j++) {
            for (int x = 1; x <= maxn; x++) {
                for (int y = 1; y <= maxn; y++) {
                    if (x == i && y == j) continue;
                    int res = (x == i || y == j || abs(x - i) == abs(y - j));
                    A[i][j] = A[x][y] = 1;
                    int ans = check(i, j, x, y);
                    if (res != ans) {
                        cout << res << ' ' << ans << '\n';
                        for (int k = 1; k <= maxn; i++) {
                            for (int h = 1; h <= maxn; h++) {
                                cout << A[k][h] << ' ';
                            } cout << '\n';
                        }
                        return 0;
                    }
                    A[i][j] = A[x][y] = 0;
                }
            }
        }
    }
}
