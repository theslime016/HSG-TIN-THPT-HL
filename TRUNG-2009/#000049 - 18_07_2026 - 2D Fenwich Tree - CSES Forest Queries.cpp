#include <bits/stdc++.h>
using namespace std;

struct FWT2D {
  int r, c;
  vector<vector<long long>> data;
  FWT2D(int n, int m) {
    this->r = n;
    this->c = m;
    data.assign(n + 1, vector<long long>(m + 1, 0));
  }

  FWT2D(const vector<vector<long long>> &S, int n, int m)
      : r(n), c(m), data(S) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        int pc = j + (j & -j);
        if (pc <= m)
          data[i][pc] += data[i][j];
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        int pr = i + (i & -i);
        if (pr <= n)
          data[pr][j] += data[i][j];
      }
    }
  }

  void process(int indexr, int indexc, long long val) {
    for (int i = indexr; i <= r; i += i & (-i)) {
      for (int j = indexc; j <= c; j += j & (-j)) {
        data[i][j] += val;
      }
    }
  }

  long long fetch(int indexr, int indexc) {
    long long pref = 0;
    for (int i = indexr; i > 0; i -= i & (-i)) {
      for (int j = indexc; j > 0; j -= j & (-j)) {
        pref += data[i][j];
      }
    }
    return pref;
  }

  long long calc(int x, int y, int a, int b) {
    return fetch(a, b) - fetch(x - 1, b) - fetch(a, y - 1) +
           fetch(x - 1, y - 1);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, q;
  cin >> n >> q;
  vector<vector<long long>> A(n + 1, vector<long long>(n + 1, 0));

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      char c;
      cin >> c;
      A[i][j] = (c == '*');
    }
  }

  FWT2D BIT(A, n, n);
  while (q--) {
    int x, y, a, b;
    cin >> x >> y >> a >> b;
    cout << BIT.calc(x, y, a, b) << '\n';
  }

  return 0;
}
