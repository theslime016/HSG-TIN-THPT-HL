#include <bits/stdc++.h>
using namespace std;

const int maxn = 2005;
const int maxel = 5e6;
const int _log = 25;
const long long inf = 1e16;
long long A[maxn];
// long long table[maxn][_log];

struct node {
  long long max;
  node() = default;
  node(long long x) { max = x; }
} segment[2 * maxel];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  fill(segment, segment + 2 * maxel, node(-inf));

  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    cin >> A[i];

  auto calc = [&](int l, int r) -> pair<int, int> {
    l--;
    int start = (n * (n + 1) / 2) - (n - l) * (n - l + 1) / 2;
    return {start + 1, start + abs(r - l)};
  };

  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      auto [a, b] = calc(i, j);
      // cout << a << ' ' << b << '\n';
    }
  }

  int padding = 1;
  int h = 0;
  int sz = n * (n - 1) / 2;
  while (padding <= sz + 1)
    padding <<= 1, h++;

  int pos = 0;
  for (int i = 1; i <= n; i++) {
    long long sum = 0;
    for (int j = i; j <= n; j++) {
      sum += A[j];
      int index = pos++;
      segment[padding + index].max = sum;
      cerr << "index" << pos - 1 << ':' << i << ' ' << j << ' '
           << segment[index + padding].max << '\n';
    }
  }

  // pos = 0;
  // for (int i = 1; i <= n; i++) {
  //   for (int j = 1; j <= i; j++) {
  //     long long sum = 0;
  //     for (int k = 1; k <= i; k++) {
  //       sum += A[k];
  //     }
  //   }
  // }

  for (int i = padding - 1; i > 0; i--) {
    segment[i].max = max(segment[i << 1].max, segment[i << 1 | 1].max);
  }

  for (int i = 1; i < padding + sz; i++) {
    cerr << segment[i].max << ' ';
  }

  // auto pushup = [&](int index) {
  //   for (index >>= 1; index > 0; index >>= 1) {
  //     segment[index].sum =
  //         segment[index << 1].sum + segment[index << 1 | 1].sum;
  //     segment[index].max =
  //         max({segment[index << 1].max, segment[index << 1 | 1].max,
  //              segment[index].sum});
  //   }
  // };

  // A[0] = -inf;
  // for (int i = 1; i <= n; i++) {
  //   table[i][0] = max(A[i], A[i - 1]);
  //   for (int exp = 1; exp < _log; exp++) {
  //     table[i][exp] = max(table[i][exp - 1], table[table[i][exp - 1]][exp -
  //     1]);
  //   }
  // }

  while (m--) {
    int l, r;
    long long val;
    cin >> l >> r >> val;

    auto [a, b] = calc(l, r);
    int s = padding + a - 1;
    int t = padding + b + 1;

    long long res = -inf;
    for (; s ^ t ^ 1; s >>= 1, t >>= 1) {
      if ((~s & 1) && segment[s ^ 1].max <= val) {
        res = max(res, segment[s ^ 1].max);
        // cout << (s ^ 1) << '\n';
      }
      if ((t & 1) && segment[t ^ 1].max <= val) {
        res = max(res, segment[t ^ 1].max);
        // cout << (t ^ 1) << '\n';
      }
    }
    if (res == -inf)
      cout << -1 << '\n';
    else
      cout << res << '\n';
  }
}
