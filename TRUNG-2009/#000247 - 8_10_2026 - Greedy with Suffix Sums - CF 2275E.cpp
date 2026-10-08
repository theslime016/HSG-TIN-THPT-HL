#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
long long A[maxn], B[maxn];
long long suff[maxn];

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
    for (int i = 1; i <= n; i++) cin >> B[i];

    long long res = 0;
    if (n > 1) {
      res += (A[n] == B[n-1] ? 2 : 1);
      res += (A[n] == B[n] ? 2 : 1);
      suff[n] = res;
    }
    for (int i = n-1; i >= 2; i--) {
      res += (A[i] == B[i-1] ? 2 : 1);
      res += (A[i] == B[i+1] ? 2 : 1);
      suff[i] = res;
    }

    if (A[1] == B[1] || (n > 1 && A[1] == B[2])) res += 2;
    else res++;

    if (n > 1) {
      long long current = 0;
      for (int i = 1; i < n; i++) {
        current += (A[i] == B[i] ? 2 : 1);
        res = max(res, current + suff[i+1]);
        current += (B[i] == A[i+1] ? 2 : 1);
      }
    }

    cout << res << '\n';
  }
}
