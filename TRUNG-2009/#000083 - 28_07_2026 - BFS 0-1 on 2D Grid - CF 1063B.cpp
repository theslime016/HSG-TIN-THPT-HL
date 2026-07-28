#include <bits/stdc++.h>
using namespace std;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

const int maxn = 2e3 + 10;
int dist[maxn][maxn]{};

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int n, m;
  cin >> n >> m;
  int r, c;
  cin >> r >> c;
  r--;
  c--;

  int left, right;
  cin >> left >> right;

  vector<string> A(n);
  for (int i = 0; i < n; i++) {
    cin >> A[i];
  }

  deque<pair<int, int>> dq;
  memset(dist, 0x3f, sizeof(dist));
  dist[r][c] = 0;
  dq.push_back({r, c});

  while (!dq.empty()) {
    auto [x, y] = dq.front();
    dq.pop_front();

    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];
      if (nx < 0 || nx >= n || ny < 0 || ny >= m || A[nx][ny] == '*')
        continue;

      int cost = (i == 2);
      if (dist[x][y] + cost < dist[nx][ny]) {
        int nright = dist[x][y] + cost;
        int nleft = nright - (ny - c);
        if (nleft <= left && nright <= right) {
          dist[nx][ny] = nright;

          if (cost == 1) {
            dq.push_back({nx, ny});
          } else {
            dq.push_front({nx, ny});
          }
        }
      }
    }
  }

  int res = 0;
  int inf = dist[maxn - 1][maxn - 1];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      res += (dist[i][j] != inf);
    }
  }

  cout << res;

  return 0;
}
