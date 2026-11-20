#include <bits/stdc++.h>
using namespace std;

#define _debug 0

#if _debug == 1
void logout() {
  cerr << endl;
}
template<typename H, typename... T>
void logout(H h, T... t) {
  cerr << h << ", ";
  logout(t...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:" << endl, logout(__VA_ARGS__)
#define debugtitle cerr << __PRETTY_FUNCTION__ << " line: " << __LINE__ << endl
#define newline cerr << endl

#else
#define debug(...) (void(0))
#define debugtitle (void(0))
#define newline (void(0))

#endif // _debug

const int maxn = 16;
const int maxmask = (1 << maxn);

long long dp[maxmask][maxn];

long long solve(int n, int k) {
  for (int i = 0; i < (1 << n); i++) {
    for (int j = 0; j <= n; j++) {
      dp[i][j] = 0;
    }
  }

  dp[0][0] = 1;
  for (int mask = 0; mask < (1 << n); mask++) {
    for (int i = 1; i <= n; i++) {
      if ((mask >> (i - 1)) & 1) {
        continue;
      }

      int new_mask = mask | (1 << (i - 1));
      for (int j = 0; j <= n; j++) {
        if (j == 0) {
          dp[new_mask][i] += dp[mask][j];
          continue;
        }

        if (abs(j - i) > k)
          continue;
        if ((mask >> (j - 1)) & 1) {
          dp[new_mask][i] += dp[mask][j];
        }
      }
    }
  }

  long long res = 0;
  for (int i = 1; i <= n; i++) {
    res += dp[(1 << n) - 1][i];
  }
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  int t;
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;
    cout << solve(n, k) << '\n';
  }
}
