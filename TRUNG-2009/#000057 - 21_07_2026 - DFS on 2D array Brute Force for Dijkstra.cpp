#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#ifndef NDEBUG
#define NDEBUG
#endif

vector<vector<bool>> grid;
atomic<long long> min_val = LLONG_MAX;
int n, m;

void update(long long val) {
  long long current = min_val.load(std::memory_order_relaxed);
  while (val < current) {
    if (min_val.compare_exchange_weak(current, val, memory_order_relaxed)) {
      break;
    }
  }
}

void backtrack(int r, int c, long long val, int depth = 1) {
  if (r == n - 1 && c == m - 1) {
    update(val);
    return;
  }

  if (val >= min_val.load(std::memory_order_relaxed)) {
    return;
  }

  bool down = (r + 1 < n && !grid[r + 1][c]);
  bool right = (c + 1 < m && !grid[r][c + 1]);
  if (depth <= 8) {
    if (down && right) {
#pragma omp task shared(min_val)
      {
        backtrack(r + 1, c, val + 1, depth + 1);
      }
      backtrack(r, c + 1, val + 1, depth + 1);
#pragma omp taskwait
    } else if (down) {
      if (down)
        backtrack(r + 1, c, val + 1, depth);
    } else {
      if (right)
        backtrack(r, c + 1, val + 1, depth);
    }
  } else {
    if (down)
      backtrack(r + 1, c, val + 1, depth);
    if (right)
      backtrack(r, c + 1, val + 1, depth);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  freopen("input.inp", "r", stdin);

  cin >> n >> m;
  int wall;
  cin >> wall;
  grid.assign(n, vector<bool>(m, 0));
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

#pragma omp parallel
  {
#pragma omp single
    {
      backtrack(0, 0, !grid[0][0]);
    }
  }
  cout << min_val;

  return 0;
}
