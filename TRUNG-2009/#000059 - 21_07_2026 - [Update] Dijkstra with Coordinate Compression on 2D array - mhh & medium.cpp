#include <bits/stdc++.h>
using namespace std;

// test:
//  40 40
//  14
//  1 12 4 12
//  6 12 14 12
//  16 12 24 12
//  26 12 34 12
//  36 12 38 12
//  1 25 7 25
//  9 25 17 25
//  19 25 27 25
//  29 25 38 25
//  10 1 10 4
//  10 6 10 11
//  10 13 10 19
//  10 21 10 24
//  10 26 10 38

// output:
//  76

struct obstacle {
  int r1, c1;
  int r2, c2;
};

struct path {
  int r, c;
  long long edge;
};

struct cmp {
  bool operator()(const path &A, const path &B) { return A.edge > B.edge; }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  freopen("input.inp", "r", stdin);
  freopen("output.ans", "w", stdout);

  int n, m;
  cin >> n >> m;
  int wall;
  cin >> wall;
  vector<int> R{0, n - 1}, C{0, m - 1};
  vector<obstacle> obs;
  obs.reserve(wall);
  auto add_R = [&](int r) {
    if (r >= 0 && r < n)
      R.push_back(r);
  };
  auto add_C = [&](int c) {
    if (c >= 0 && c < m)
      C.push_back(c);
  };
  while (wall--) {
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    r1--;
    r2--;
    c1--;
    c2--;
    add_R(r1 - 1);
    add_R(r1);
    add_R(r2 + 1);

    add_C(c1 - 1);
    add_C(c1);
    add_C(c2 + 1);

    obs.push_back({r1, c1, r2 + 1, c2 + 1});
  }

  // for (int i = 0; i < (int)obs.size(); i++) {
  //   cout << obs[i].r1 << ' ' << obs[i].c1 << ' ' << obs[i].r2 << ' '
  //        << obs[i].c2 << '\n';
  // }

  sort(R.begin(), R.end());
  R.erase(unique(R.begin(), R.end()), R.end());
  sort(C.begin(), C.end());
  C.erase(unique(C.begin(), C.end()), C.end());

  // for (int x : R)
  //   cout << x << ' ';
  // cout << '\n';
  // for (int y : C)
  //   cout << y << ' ';
  // cout << '\n';

  vector<vector<bool>> grid(R.size(), vector<bool>(C.size()));
  vector<path> adjacent;
  for (const obstacle &H : obs) {
    int r_start = lower_bound(R.begin(), R.end(), H.r1) - R.begin();
    int r_end = lower_bound(R.begin(), R.end(), H.r2) - R.begin();
    int c_start = lower_bound(C.begin(), C.end(), H.c1) - C.begin();
    int c_end = lower_bound(C.begin(), C.end(), H.c2) - C.begin();

    // cout << r_start << ' ' << r_end << '\n';
    // cout << c_start << ' ' << c_end << '\n';

    for (int i = r_start; i < r_end; i++) {
      for (int j = c_start; j < c_end; j++) {
        grid[i][j] = true;
      }
    }
  }

  // for (int i = 0; i < (int)R.size(); i++) {
  //   for (int j = 0; j < (int)C.size(); j++) {
  //     cout << grid[i][j];
  //   }
  //   cout << '\n';
  // }

  int start_R = lower_bound(R.begin(), R.end(), 0) - R.begin();
  int end_R = lower_bound(R.begin(), R.end(), n - 1) - R.begin();
  int start_C = lower_bound(C.begin(), C.end(), 0) - C.begin();
  int end_C = lower_bound(C.begin(), C.end(), m - 1) - C.begin();

  const long long inf = 4e18;
  vector<vector<long long>> dist((int)R.size(),
                                 vector<long long>(C.size(), inf));
  priority_queue<path, vector<path>, cmp> task;

  int dr[] = {-1, 1, 0, 0};
  int dc[] = {0, 0, -1, 1};
  dist[start_R][start_C] = 0;
  if (!grid[start_R][start_C])
    task.push({start_R, start_C, 0LL});
  while (!task.empty()) {
    auto [r, c, d] = task.top();
    task.pop();
    if (d > dist[r][c])
      continue;
    if (r == end_R && c == end_C)
      break;
    for (int i = 0; i < 4; i++) {
      int ne_R = dr[i] + r;
      int ne_C = dc[i] + c;
      if (ne_R >= 0 && ne_C >= 0 && ne_R <= end_R && ne_C <= end_C &&
          !grid[ne_R][ne_C]) {
        long long weight = abs(R[ne_R] - R[r]) + abs(C[ne_C] - C[c]);
        if (dist[r][c] + weight < dist[ne_R][ne_C]) {
          dist[ne_R][ne_C] = dist[r][c] + weight;
          task.push({ne_R, ne_C, dist[ne_R][ne_C]});
        }
      }
    }
  }

  // for (int i = 0; i < (int)R.size(); i++) {
  //   for (int j = 0; j < (int)C.size(); j++) {
  //     cout << dist[i][j] << ' ';
  //   }
  //   cout << '\n';
  // }

  // return 0;

  if (dist[end_R][end_C] == inf)
    cout << -1;
  else
    cout << dist[end_R][end_C];

  return 0;
}
