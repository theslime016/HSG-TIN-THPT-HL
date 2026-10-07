#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
int A[maxn];
int pos[maxn];

long long proc(long long a, long long b, long long s) {
  if (s < 0) return 0;
  long long res = 0;

  long long x1 = min({a, s, s - b});
  if (x1 >= 0) {
    res += (x1 + 1) * (b + 1);
  } else {
    x1 = -1;
  }

  long long x2 = min(a, s);
  if (x1 < x2) {
    long long num = x2 - x1;
    long long v_first = s - (x1+1) + 1;
    long long v_end = s - x2 + 1;
    res += num * (v_first + v_end)/2;
  }
  return res;
}

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
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> A[i];
    for (int i = 1; i <= n; i++) pos[ A[i] ] = i;
    pos[n] = n + 1;

    long long res = 0;
    int l = pos[0], r = pos[0];
    for (int k = 1; k <= n; k++) {
      int lbound = 1;
      int rbound = n;
      if (pos[k] < l) {
        lbound = min(l, pos[k] + 1);
      } else if (pos[k] > r) {
        rbound = max(r, pos[k] - 1);
      } else {
        l = min(l, pos[k]);
        r = max(r, pos[k]);
        continue;
      }

      long long a = l - lbound;
      long long b = rbound - r;
      long long s = 2LL*k - (r - l + 1);

      res += proc(a, b, s);
      l = min(l, pos[k]);
      r = max(r, pos[k]);
    }

    cout << res << '\n';

  }
}
