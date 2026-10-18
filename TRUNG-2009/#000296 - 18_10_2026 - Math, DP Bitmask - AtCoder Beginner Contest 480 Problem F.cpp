#include <bits/stdc++.h>
using namespace std;

#define _debug 1

#if _debug == 1
#define debug(x) cerr << #x << ':' << (x) << ' ';
#define debugn(x) cerr << #x << ':' << (x) << '\n';
#define new_line cerr << '\n';

#else
#define debug(x)
#define debugn(x)
#define new_line

#endif // _debug

#define popcount(x) __builtin_popcountll(x)

const int maxn = 1 << 23;
const long long inf = 1e18;
long long A[maxn];
long long dp[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);
#else

#endif // _debug

  long long n, m;
  cin >> n >> m;
  long long s = 0;
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    s += A[i];
  }

  memset(dp, -1, sizeof dp);
  dp[0] = m - 1;
  for (int mask = 0; mask < (1LL << n) - 1; mask++) {
    if (popcount(mask) == n-1) continue;
    long long current = 0;
    for (int i = 0; i < n; i++) {
      if ((mask >> i) & 1) current += A[i+1];
    }

    for (int i = 0; i < n; i++) {
      if (!((mask >> i) & 1)) {
        long long nxt = current + A[i + 1];
        long long op = dp[mask] - (nxt * m % s == 0);
        int new_mask = mask | (1 << i);
        if (dp[new_mask] == -1) dp[new_mask] = op;
        else dp[new_mask] = min(dp[new_mask], op);
        debug(mask);
        debug(new_mask);
        debug(nxt);
        debug(dp[mask]);
        debug(dp[new_mask]);
        debugn(op);
      }
    }
  }

  long long res = inf;
  int mask = (1LL << n) - 1;
  for (int i = 0; i < n; i++) {
    int new_mask = mask ^ (1 << i);
    res = min(res, dp[new_mask]);
  }

  cout << res;

}
