#include <bits/stdc++.h>
using namespace std;

// Problem: https://i.postimg.cc/Pr9n4XT2/image.png

const long long inf = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  freopen("input.inp", "r", stdin);
  freopen("output.ans", "w", stdout);

  struct ST {
    int n;
    vector<long long> data;

    ST(int n) {
      this->n = n;
      data.assign(2 * n, inf);
    }

    void build(const vector<long long> &a) {
      for (int i = 0; i < n; i++) {
        data[n + i] = a[i];
      }

      for (int i = n - 1; i > 0; i--) {
        data[i] = min(data[i * 2], data[i * 2 + 1]);
      }
    }

    void process(int index, const long long &val) {
      for (data[index += n] = val; index > 1; index >>= 1) {
        data[index >> 1] = min(data[index], data[index ^ 1]);
      }
    }

    long long query(int l, int r) {
      long long res = inf;
      r++;
      l += n, r += n;
      for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
          res = min(data[l++], res);
        if (r & 1)
          res = min(data[--r], res);
      }
      return res;
    }
  };

  int n;
  cin >> n;
  vector<long long> A(n + 1, 0);
  vector<long long> pref(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    pref[i] = A[i] + pref[i - 1];
  }

  ST segment(n + 1);
  segment.build(pref);

  int m;
  cin >> m;
  while (m--) {
    int x, y;
    cin >> x >> y;
    long long res = -inf;
    for (int index = x; index <= y; index++) {
      long long val = pref[index] - segment.query(x - 1, index - 1);
      res = max(res, val);
    }
    cout << res << '\n';
  }
}
