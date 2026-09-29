#include <bits/stdc++.h>
using namespace std;

/*
To mau giong trong paint
*/

const int maxn = 1e3 + 5;
char A[maxn][maxn];
int proc[maxn][maxn];
int timer = 0;

#define _debug 1
int main() {
    cin.tie(0)->sync_with_stdio(0);

    #if _debug == 1
    freopen("input.inp", "r", stdin);
    #else

    #endif // _debug

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> A[i][j];
        }
    }

    int q;
    cin >> q;
    queue<pair<int, int>> wait; // index
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    while (q--) {
        char c;
        int x, y;
        cin >> c >> x >> y;
        A[x][y] = c;
        wait.push({x, y});
        while (!wait.empty()) {
            auto [a, b] = wait.front();
            wait.pop();
            for (int i = 0; i < 4; i++) {
                int na = a + dx[i];
                int nb = b + dy[i];
                if (na >= 1 && nb >= 1 && na <= n && nb <= m && A[na][nb] != c) {
                    A[na][nb] = c;
                    wait.push({na, nb});
                }
            }
        }

        int res = 0;
        int cnt = 0;
        timer++;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (proc[i][j] != timer) {
                    wait.push({i, j});
                    int local = 1;
                    proc[i][j] = timer;
                    cnt++;
                    while (!wait.empty()) {
                        auto [a, b] = wait.front();
                        wait.pop();
                        for (int k = 0; k < 4; k++) {
                            int na = a + dx[k];
                            int nb = b + dy[k];
                            if (na >= 1 && nb >= 1 && na <= n && nb <= m && A[na][nb] == A[i][j]
                                && proc[na][nb] != timer) {
                                proc[na][nb] = timer;
                                local++;
                                wait.push({na, nb});
                            }
                        }
                    }
                    res = max(res, local);
                }
            }
        }
        cout << cnt << ' ' << res << '\n';
    }
}
