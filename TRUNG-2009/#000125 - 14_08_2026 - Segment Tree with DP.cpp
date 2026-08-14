#include <bits/stdc++.h>
using namespace std;

// Problem: https://i.postimg.cc/Df6NC2PF/image.png

const long long inf = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, k;
  cin >> n >> k;

  struct ST {
    int n;
    vector<long long> data;

    ST(int n) {
      this->n = n;
      data.assign(2 * n + 1, -inf);
    }

    void build(const vector<long long> &a) {
      for (int i = 0; i < n; i++) {
        data[n + i] = a[i];
      }

      for (int i = n - 1; i > 0; i--) {
        data[i] = max(data[i * 2], data[i * 2 + 1]);
      }
    }

    void process(int index, const long long &val) {
      for (data[index += n] = val; index > 1; index >>= 1) {
        data[index >> 1] = max(data[index], data[index ^ 1]);
      }
    }

    long long fetch(int l, int r) {
      long long res = -inf;
      r++;
      l += n, r += n;
      for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
          res = max(data[l++], res);
        if (r & 1)
          res = max(data[--r], res);
      }
      return res;
    }
  } segment(n);

  // i-k -> i-1
  long long res = -inf;
  for (int i = 0; i < n; i++) {
    long long val;
    cin >> val;

    if (i - 1 >= 0) {
      int l = max(0, i - k);
      int r = i - 1;

      long long dp = segment.fetch(l, r);
      if (dp > 0)
        val += dp;
    }
    segment.process(i, val);
    res = max(res, val);
  }

  cout << res;
}
