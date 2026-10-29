#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
const long long inf = 2'000'000'000'000'000'000;
int n;
long long k;

int f(long long x, long long y) {
  if (x - y > 0) return 1;
  else if (x - y < 0) return -1;
  else return 0;
}

long long get_cost(long long x, long tar) {
  return x - tar;
}

long long proc(long long a, long long b, long long c) {
  if (a == b && b == c) return a + b + c;

  /// a += f(b, c)
  /// b += f(a, c)
  /// c += f(a, b)

  if (a > b || a > c || b > c) {
    return a + b + c + k;
  }

  /// a < b < c
  /// a <= b && b < c
  /// a < b && b <= c

  /// b -> a - 1
  long long res = a + b + c;
  if (k - get_cost(b, a - 1)) res = max(res, a + a - 1 + k - get_cost(b, a - 1) + c);
  if (a != b) {
    if (k - get_cost(c, a - 1)) res = max(res, a + a - 1 + k - get_cost(c, a - 1) + b);
    if (k - get_cost(c, b - 1)) res = max(res, a + b - 1 + k - get_cost(c, b - 1) + b);
  }
  return res;
}

long long sum[maxn];
long long cost[maxn];

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  int t;
  cin >> t;
  while (t--) {
    cin >> n >> k;

    long long l = inf, r = inf;
    for (int i = 1; i <= n; i++) {
      long long a, b, c;
      cin >> a >> b >> c;

      sum[i] = a + b + c;
      if (a == b && b == c) cost[i] = inf;
      else if (a <= b && b <= c) cost[i] = min(c - b, b - a) + 1;
      else cost[i] = 0;

      l = min(l, sum[i]);
    }

    auto check = [&](long long tar) -> bool {
      long long rem = k;
      for (int i = 1; i <= n; i++) {
        if (sum[i] >= tar) continue;

        if (cost[i] == inf) return false;

        rem -= (tar - sum[i]) + 2 * cost[i];

        if (rem < 0) return false;
      }
      return true;
    };

    for (long long d = r - l; d > 0; d >>= 1) {
      while (l + d <= r && check(l + d)) l += d;
    }

    cout << l << '\n';
  }

}
