#include <bits/stdc++.h>
using namespace std;

struct point {
  int r, c;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  freopen("input.inp", "r", stdin);

  int n, m;
  cin >> n >> m;
  int wall;
  cin >> wall;
  vector<vector<bool>> grid(n, vector<bool>(m, 0));
  while (wall--) {
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    r1--;
    r2--;
    c1--;
    c2--;
    for (int i = r1; i <= r2; i++) {
      for (int j = c1; j <= c2; j++) {
        grid[i][j] = true;
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << grid[i][j];
    }
    cout << '\n';
  }

  vector<vector<long long>> dist(n, vector<long long>(m, -1));
  queue<point> task;

  dist[0][0] = 0;
  task.push({0, 0});

  int dr[] = {-1, 1, 0, 0};
  int dc[] = {0, 0, -1, 1};
  while (!task.empty()) {
    auto [r, c] = task.front();
    task.pop();
    if (r == n - 1 && c == m - 1) {
      break;
    }
    for (int i = 0; i < 4; i++) {
      int nr = dr[i] + r;
      int nc = dc[i] + c;
      if (nr >= 0 && nc >= 0 && nr < n && nc < m && !grid[nr][nc] &&
          dist[nr][nc] == -1) {
        dist[nr][nc] = dist[r][c] + 1;
        task.push({nr, nc});
      }
    }
  }

  if (dist[n - 1][m - 1] == -1)
    cout << -1;
  else
    cout << dist[n - 1][m - 1];

  return 0;
}
