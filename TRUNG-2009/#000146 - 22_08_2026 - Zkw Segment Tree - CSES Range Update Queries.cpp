#include <bits/stdc++.h>
using namespace std;

struct zkw {
  int m, h;
  vector<long long> data, lazy;

  zkw(int n) {
    m = 1;
    h = 0;
    while (m <= n + 1) {
      m <<= 1;
      h++;
    }
    data.assign(2 * m, 0);
    lazy.assign(2 * m, 0);
  }

  void inline prebuild(int index, const long long &val) {
    data[index + m] = val;
  }

  void build() {
    for (int i = m - 1; i > 0; i--) {
      data[i] = data[i << 1] + data[i << 1 | 1];
    }
  }

  void inline apply(int index, int len, const long long &val) {
    data[index] += len * val;
    if (index < m)
      lazy[index] += val;
  }

  void inline pushup(int index) {
    int len = 1;
    for (index >>= 1, len <<= 1; index > 0; index >>= 1, len <<= 1) {
      data[index] = data[index << 1] + data[index << 1 | 1] + lazy[index] * len;
    }
  }

  void inline pushdown(int index) {
    for (int rank = h, len = 1 << (h - 1); rank > 0; rank--, len >>= 1) {
      int rindex = index >> rank;
      if (lazy[rindex]) {
        apply(rindex << 1, len, lazy[rindex]);
        apply(rindex << 1 | 1, len, lazy[rindex]);
        lazy[rindex] = 0;
      }
    }
  }

  void update(int l, int r, const long long &val) {
    int s = m + l - 1;
    int t = m + r + 1;
    pushdown(s);
    pushdown(t);

    int os = s, ot = t;
    int len = 1;
    for (; s ^ t ^ 1; s >>= 1, t >>= 1, len <<= 1) {
      if (~s & 1)
        apply(s ^ 1, len, val);
      if (t & 1)
        apply(t ^ 1, len, val);
    }
    pushup(os);
    pushup(ot);
  }

  long long fetch(int l, int r) {
    int s = m + l - 1;
    int t = m + r + 1;
    pushdown(s);
    pushdown(t);

    long long res = 0;
    for (; s ^ t ^ 1; s >>= 1, t >>= 1) {
      if (~s & 1)
        res += data[s ^ 1];
      if (t & 1)
        res += data[t ^ 1];
    }
    return res;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;

  zkw segment(n);
  for (int i = 1; i <= n; i++) {
    long long val;
    cin >> val;
    segment.prebuild(i, val);
  }
  segment.build();

  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int l, r;
      long long val;
      cin >> l >> r >> val;
      segment.update(l, r, val);
    } else {
      int k;
      cin >> k;
      cout << segment.fetch(k, k) << '\n';
    }
  }
}
