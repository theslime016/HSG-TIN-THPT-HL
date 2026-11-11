#include <bits/stdc++.h>
using namespace std;

#define _debug 0

#if _debug == 1
void log_out() {cerr << endl;}
template<typename H, typename... T>
void log_out(H h, T... t) {
  cerr << h << ", ";
  log_out(t...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:" << endl, log_out(__VA_ARGS__)
#define newline cerr << endl

#else
#define debug(...) (void(0))
#define newline (void(0))

#endif // _debug

const int maxn = 505;
const int maxq = 1e5 + 5;
const long long inf = 1e18;

int n, m, q;
long long dp[maxn][maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);

  #else

  #endif // _debug

  cin >> n >> m >> q;

  fill_n((long long*)dp, maxn * maxn, inf);

  for (int i = 1; i <= m; i++) {
    int a, b;
    long long val;
    cin >> a >> b >> val;
    dp[a][b] = min(dp[a][b], val);
    dp[b][a] = min(dp[b][a], val);
  }

  for (int i = 1; i <= n; i++) {
    dp[i][i] = 0;
  }

  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (dp[i][k] != inf && dp[k][j] != inf) {
          dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
        }
      }
    }
  }

  while (q--) {
    int a, b;
    cin >> a >> b;
    if (dp[a][b] == inf) cout << -1 << '\n';
    else cout << dp[a][b] << '\n';
  }


}
