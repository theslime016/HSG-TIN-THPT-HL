#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
const long long inf = 1e18;
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

long long pref[maxn], suff[maxn];
long long A[maxn], B[maxn], C[maxn];

#define _debug 1
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

    for (int i = 1; i <= n; i++) {
      cin >> A[i] >> B[i] >> C[i];
    }

    pref[1] = proc(A[1], B[1], C[1]);
    for (int i = 2; i <= n; i++) {
      pref[i] = min(proc(A[1], B[1], C[1]), pref[i-1]);
    }

    suff[n] = proc(A[n], B[n], C[n]);
    for (int i = n - 1; i >= 1; i--) {
      suff[i] = min(proc(A[i], B[i], C[i]), suff[i+1]);
    }

    long long res = -inf;
    for (int i = 1; i <= n; i++) {
      long long val = proc(A[i], B[i], C[i]);
      if (i > 1) res = max(res, min(val, pref[i - 1]));
      if (i < n) res = max(res, min(val, suff[i + 1]));
    }

    cout << res << '\n';
  }

}
