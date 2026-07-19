#include <bits/stdc++.h>
using namespace std;

#ifndef NDEBUG
#define NDEBUG
#endif

int start[1500 + 10] = {0};
int pos[1500 + 10] = {0};
int sz[1500 + 10] = {0};
int aut[2'300'000] = {0};
const int inf = -100;
struct op {
  int type = inf;
  int x = inf, y = inf;
  int r = inf, c = inf;
};
struct Offline2DFWT {
  int n;
  vector<op> rmemo;
  vector<vector<int>> rindex;
  vector<vector<int>> data;
  // Convert data to 1D array

  // void build() {
  //   sort(rmemo.begin(), rmemo.end(),
  //        [](auto &a, auto &b) { return a.y < b.y; });
  //   this->n = num;
  //   rindex.assign(n + 1, vector<int>(1, 0));
  //   data.resize(n + 1);
  //   for (op &A : rmemo) {
  //     for (; A.x <= n; A.x += A.x & -A.x) {
  //       if (rindex[A.x].back() != A.y)
  //         rindex[A.x].push_back(A.y);
  //     }
  //   }
  //   for (int i = 1; i <= n; i++)
  //     data[i].resize(rindex[i].size() + 1);
  // }

  Offline2DFWT(int n) {
    this->n = n;
    rindex.assign(n + 1, vector<int>());
    data.resize(n + 1);
    memset(start, 0, sizeof(start));
    memset(pos, 0, sizeof(pos));
    memset(sz, 0, sizeof(sz));
    memset(aut, 0, sizeof(aut));
  }

  void preprocess(int x, int y) {
    if (x <= 0 || y <= 0)
      return;
    for (; x <= n; x += x & -x) {
      rindex[x].push_back(y);
    }
  }

  void build() {
    for (int i = 1; i <= n; i++) {
      sort(rindex[i].begin(), rindex[i].end());
      rindex[i].erase(unique(rindex[i].begin(), rindex[i].end()),
                      rindex[i].end());
      data[i].assign(rindex[i].size() + 1, 0);

      sz[i] = rindex[i].size();
      start[i] = start[i - 1] + sz[i - 1];
      pos[i] = start[i];
      for (auto &A : rindex[i]) {
        aut[pos[i]++] = A;
      }
    }
  }

  int get(int x, int y) {
    if (x <= 0 || y <= 0)
      return 0;
    return upper_bound(aut + start[x], aut + start[x] + sz[x], y) -
           (aut + start[x]);
    // return lower_bound(rindex[x].begin(), rindex[x].end(), y) -
    //        rindex[x].begin();
    // Build Automaton for upper_bound
  }

  void process(int x, int y, int val) {
    if (x <= 0 || y <= 0)
      return;
    for (; x <= n; x += x & -x) {
      int index = get(x, y);
      for (; index < (int)data[x].size(); index += index & -index) {
        data[x][index] += val;
      }
    }
  }

  int fetch(int x, int y) {
    int pref = 0;
    for (; x > 0; x -= x & -x) {
      int index = get(x, y);
      for (; index > 0; index -= index & -index) {
        pref += data[x][index];
      }
    }
    return pref;
  }

  int refetch(int x1, int y1, int x2, int y2) {
    return fetch(x2, y2) + fetch(x1 - 1, y1 - 1) - fetch(x2, y1 - 1) -
           fetch(x1 - 1, y2);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  // freopen("test_input.txt", "r", stdin);

  int num, q;
  cin >> num >> q;
  Offline2DFWT reBIT(num);
  char grid[num + 1][num + 1];
  for (int i = 1; i <= num; i++) {
    for (int j = 1; j <= num; j++) {
      cin >> grid[i][j];
      if (grid[i][j] == '*') {
        reBIT.rmemo.push_back({0, i, j});
        reBIT.preprocess(i, j);
      }
    }
  }

  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int x, y;
      cin >> x >> y;
      reBIT.rmemo.push_back({1, x, y});
      reBIT.preprocess(x, y);
    } else {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      reBIT.rmemo.push_back({2, x1, y1, x2, y2});
      reBIT.preprocess(x2, y2);
      reBIT.preprocess(x1 - 1, y1 - 1);
      reBIT.preprocess(x2, y1 - 1);
      reBIT.preprocess(x1 - 1, y2);
    }
  }

  reBIT.build();
  for (const op &A : reBIT.rmemo) {
    // cout << A.type << ' ' << A.x << ' ' << A.y << ' ' << A.r << ' ' << A.c
    //      << '\n';
    // continue;
    if (A.type == 0) {
      reBIT.process(A.x, A.y, 1);
    } else if (A.type == 1) {
      int val = 0;
      if (grid[A.x][A.y] == '*') {
        val = -1;
        grid[A.x][A.y] = '.';
      } else {
        val = 1;
        grid[A.x][A.y] = '*';
      }
      reBIT.process(A.x, A.y, val);
    } else {
      cout << reBIT.refetch(A.x, A.y, A.r, A.c) << '\n';
    }
  }

  return 0;
}
