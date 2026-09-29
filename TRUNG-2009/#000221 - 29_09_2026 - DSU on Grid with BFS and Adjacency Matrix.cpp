#include <bits/stdc++.h>
using namespace std;

// Problem: https://i.postimg.cc/yxdSNznJ/image.png

const int maxn = 1e3 + 5;
char A[maxn][maxn];
int proc[maxn][maxn];
char color[maxn * maxn];
int bucket[maxn * maxn];
int arc[maxn][maxn];
int timer;

struct uf {
  int n;
  int active;
  int res;
  vector<int> data;

  uf(int n) {
    this->n = n;
    this->active = n;
    this->res = 0;
    data.assign(n + 1, 0);
    iota(data.begin(), data.end(), 0);
  }

  int fnd(int index) {
    if (data[index] == index)
      return index;
    return data[index] = fnd(data[index]);
  }

  void proc(int a, int b) {
    a = fnd(a);
    b = fnd(b);
    if (a != b) {
      bucket[a] += bucket[b];
      data[b] = a;
      active--;
      res = max(res, bucket[a]);
    }
  }
};

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

  queue<pair<int, int>> q; // index
  int dx[] = {1, -1, 0, 0};
  int dy[] = {0, 0, 1, -1};
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (!proc[i][j]) {
        proc[i][j] = ++timer;
        q.push({i, j});
        color[timer] = A[i][j];
        bucket[timer] = 1;
        while (!q.empty()) {
          auto [x, y] = q.front();
          q.pop();
          for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx >= 1 && ny >= 1 && nx <= n && ny <= m &&
                A[nx][ny] == A[i][j] && !proc[nx][ny]) {
              proc[nx][ny] = timer;
              bucket[timer]++;
              q.push({nx, ny});
            }
          }
        }
      }
    }
  }

#if _debug == 1
  for (int i = 1; i <= timer; i++) {
    cout << color[i] << ' ';
  }
  cout << '\n';

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cout << proc[i][j] << ' ';
    }
    cout << '\n';
  }
#endif

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      for (int k = 0; k < 4; k++) {
        int x = dx[k] + i;
        int y = dy[k] + j;
        if (x >= 1 && y >= 1 && x <= n && y <= m && proc[x][y] != proc[i][j]) {
          int tag1 = proc[x][y];
          int tag2 = proc[i][j];
          arc[tag1][tag2] = 1;
          arc[tag2][tag1] = 1;
        }
      }
    }
  }

#if _debug == 1
  for (int i = 1; i <= timer; i++) {
    for (int j = 1; j <= timer; j++) {
      cout << arc[i][j] << ' ';
    }
    cout << '\n';
  }
#endif

  uf dsu(timer);
  for (int i = 1; i <= timer; i++)
    dsu.res = max(dsu.res, bucket[i]);

  int t;
  cin >> t;
  while (t--) {
    char c;
    int a, b;
    cin >> c >> a >> b;
    int v = proc[a][b];
    int index = dsu.fnd(v);
    if (color[index] != c) {
      color[index] = c;
      for (int j = 1; j <= timer; j++) {
        if (j == index)
          continue;
        if (!arc[index][j])
          continue;
        int rindex = dsu.fnd(j);
        if (rindex == index || color[rindex] != color[index])
          continue;
        dsu.proc(index, rindex);
        arc[index][j] = 0;
        arc[j][index] = 0;
        for (int k = 1; k <= timer; k++) {
          if (k == j || k == index)
            continue;
          if (!arc[k][j])
            continue;
          arc[k][j] = 0;
          arc[j][k] = 0;

          arc[index][k] = 1;
          arc[k][index] = 1;
        }
      }
    }
    cout << dsu.active << ' ' << dsu.res << '\n';
  }
}
