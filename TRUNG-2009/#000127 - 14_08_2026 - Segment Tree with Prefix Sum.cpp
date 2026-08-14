#include <bits/stdc++.h>
using namespace std;

// Problem: https://i.postimg.cc/Pr9n4XT2/image.png

const long long inf = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  struct ST {
    int n;
    vector<long long> data;

    ST(int n) {
      this->n = n;
      data.assign(2 * n + 1, inf);
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
  vector<long long> a(n, 0);
  vector<long long> pref(n, 0);
  long long last = inf;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    pref[i] = a[i];
    pref[i] += last != inf ? last : 0;
    last = pref[i];
  }

  ST segment(n);
  segment.build(pref);

  int m;
  cin >> m;
  while (m--) {
    int x, y;
    cin >> x >> y;
    x--, y--;
    long long res = -inf;
    for (int index = x; index <= y; index++) {
      res = max({res, pref[index] - segment.query(x, index), a[index]});
    }
    cout << res;
  }
}
