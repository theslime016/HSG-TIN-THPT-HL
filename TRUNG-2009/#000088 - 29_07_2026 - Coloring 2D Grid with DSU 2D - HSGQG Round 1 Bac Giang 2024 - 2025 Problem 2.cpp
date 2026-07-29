#include <bits/stdc++.h>
using namespace std;

struct UF2D {
  int n, m;
  static const int maxn = 505;
  long long data[maxn][maxn];
  long long count;
  UF2D(int n, int m) {
    this->n = n;
    this->m = m;
    for (int i = 1; i <= n; i++) {
      iota(data[i], data[i] + m + 2, 0LL);
    }
    count = 0;
  }

  int find(int r, int c) {
    int root = c;
    while (root != data[r][root]) {
      root = data[r][root];
    }

    int current = c;
    while (current != root) {
      int next = data[r][current];
      data[r][current] = root;
      current = next;
    }

    return root;

    // if (data[r][c] == c)
    //   return c;
    // return data[r][c] = find(r, data[r][c]);
  }

  int compress(int r, int a, int b) {
    a = find(r, a);
    b = find(r, b);
    if (a != b) {
      if (a < b)
        swap(a, b);
      data[r][b] = a;
      count++; // HERE
    }
    return a; // NEXT
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(false);

  freopen("REDSTONE.INP", "r", stdin);
  freopen("REDSTONE.ANS", "w", stdout);

  int n, m, k, q;
  cin >> n >> m >> k >> q;
  UF2D DSU(n, m);

  while (q--) {
    int x, y;
    cin >> x >> y;
    int start_r = max(1, x - k);
    int end_r = min(n, x + k);
    for (int i = start_r; i <= end_r; i++) {
      int h = abs(x - i);
      int start_c = max(1, y - k + h);
      int end_c = min(m, y + k - h);

      int j = DSU.find(i, start_c);
      while (j <= end_c) {
        j = DSU.compress(i, j, j + 1);
      }
    }

    // for (int i = 1; i <= n; i++) {
    //   for (int j = 1; j <= m; j++) {
    //     cout << A[i][j] << ' ';
    //   }
    //   cout << '\n';
    // }

    cout << DSU.count << '\n';
  }

  return 0;
}
