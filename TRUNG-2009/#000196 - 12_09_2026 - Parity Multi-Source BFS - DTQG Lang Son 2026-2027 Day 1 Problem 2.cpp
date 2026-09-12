#include <bits/stdc++.h>
using namespace std;

int m, n;
int totalcell;

int inline get_index_bfs(int x, int y) {
    return (x-1) * n + (y-1);
}

pair<int, int> inline get_index_table(int index) {
    return {(index/n) + 1, (index%n) + 1};
}

struct object {
    int x;
    int y;
    char type;
};

const int inf = 1e9;
const int maxtable = 2005;
char A[maxtable][maxtable];
int dist[maxtable][2];
int cnt_appear[maxtable][2];
int bfs[maxtable][2];

bool make_bfs(int start_x, int start_y, char type) {
    memset(bfs, -1, sizeof bfs);
    bool can_go = false;

    queue<pair<int, int>> q; // index_bfs, parity
    int start_index = get_index_bfs(start_x, start_y);
    q.push({start_index, 0});
    bfs[start_index][0] = 0;

    static vector<pair<int, int>> moves;
    if (type == 'M') {
        moves = { {1, 2}, {-1, 2}, {-1, -2}, {1, -2},     {2, 1}, {-2, 1}, {-2, -1}, {2, -1} };
    } else {
        moves = { {1, 0}, {-1, 0}, {0, 1}, {0, -1},       {1, 1}, {-1, 1}, {-1, -1}, {1, -1} };
    }

    while (!q.empty()) {
        auto [index, parity] = q.front();
        q.pop();

        auto [x, y] = get_index_table(index);
        for (int i = 0; i < 8; i++) {
            int next_x = x + moves[i].first;
            int next_y = y + moves[i].second;
            if (next_x >= 1 && next_x <= m && next_y >= 1 && next_y <= n && A[next_x][next_y] != '#') {
                int rindex = get_index_bfs(next_x, next_y);
                int nparity = !parity;
                if (bfs[rindex][nparity] == -1) {
                    bfs[rindex][nparity] = bfs[index][parity]+1;
                    q.push({rindex, nparity});
                    can_go = true;
                }
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (A[i][j] == '#') continue;
            int index = get_index_bfs(i, j);
            if (bfs[index][0] != -1) {
                dist[index][0] = max(dist[index][0], bfs[index][0]);
                cnt_appear[index][0]++;
            }
            if (bfs[index][1] != -1) {
                dist[index][1] = max(dist[index][1], bfs[index][1]);
                cnt_appear[index][1]++;
            }
        }
    }

    return can_go;
}

#define _DEBUG 0

int main() {
    cin.tie(0)->sync_with_stdio(0);

    //freopen("input.inp", "r", stdin);
    freopen("GATHER.INP", "r", stdin);
    freopen("GATHER.OUT", "w", stdout);

    vector<object> character;

    cin >> m >> n;
    totalcell = m*n;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> A[i][j];
            if (A[i][j] == 'T' || A[i][j] == 'M') {
                character.push_back({i, j, A[i][j]});
            }
        }
    }

    int max_step = inf;
    for (const object& s : character) {
        if (!make_bfs(s.x, s.y, s.type)) {
            max_step = 0;
            break;
        }
    }


    #if _DEBUG
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int index = get_index_bfs(i, j);
            cout << i << ' ' << j << ' ' << index << '\n';
            cout << cnt_appear[index][0] << ' ' << cnt_appear[index][1] << '\n';
            cout << dist[index][0] << ' ' << dist[index][1] << '\n';
            cout << '\n';
        }
    }
    #endif


    int res = inf;
    int totalobject = character.size();
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (A[i][j] == '#') continue;
            int index = get_index_bfs(i, j);
            if (cnt_appear[index][0] == totalobject && dist[index][0] <= max_step) res = min(res, dist[index][0]);
            if (cnt_appear[index][1] == totalobject && dist[index][1] <= max_step) res = min(res, dist[index][1]);
        }
    }
    if (res == inf) cout << -1;
    else cout << res;
}
