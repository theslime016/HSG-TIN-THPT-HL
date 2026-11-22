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

const int maxn = 105;
const int maxval = 1e4 + 5;
const long long inf = 1e18;

int n, m;

pair<int, long long> item[maxn]; /// cost - profit
long long dp[maxn][maxval];
long long query_res[maxval];

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  cin >> n >> m;
  long long base_profit = 0;
  for (int i = 1; i <= n; i++) {
    cin >> item[i].first >> item[i].second;
    base_profit += item[i].second;
  }

  sort(item + 1, item + n + 1, greater<pair<int, long long>>());

  for (int k = 0; k <= n; k++) {
    for (int x = 0; x <= m; x++) {
      dp[k][x] = (k == 0) ? 0LL : (-inf);
    }
  }

  int timer = m;
  int item_index = 1;
  int item_cnt = 0;

  while (item_index <= n) {
    int current_cost = item[item_index].first;

    /// make_query_res
    for (int x = timer; x >= current_cost; x--) {
      long long best = 0;
      for (int k = 0; k <= item_cnt; k++) {
        long long diff = 1LL * (timer - x) * k;
        if (diff > m)
          break;
        best = max(best, dp[k][m - diff]);
      }
      best += base_profit;
      query_res[x] = best;
    }

    /// remove
    if (timer > current_cost) {
      for (int k = 1; k <= item_cnt; k++) {
        long long diff = 1LL * (timer - current_cost) * k;
        for (int x = m; x >= 0; x--) {
          if (x >= diff) {
            dp[k][x] = dp[k][x - diff];
          } else {
            dp[k][x] = -inf;
          }
        }
      }
      timer = current_cost;
    }

    /// add
    while (item_index <= n && item[item_index].first == current_cost) {
      base_profit -= item[item_index].second;

      for (int k = item_cnt; k >= 0; k--) {
        for (int x = m; x >= 0; x--) {
          if (dp[k][x] != -inf) {
            dp[k + 1][x] = max(dp[k + 1][x], dp[k][x] + item[item_index].second);
          }
        }
      }

      item_index++;
      item_cnt++;
    }
  }

#if _debug == 1
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      debug(i, j, dp[i][j]);
    }
    newline;
  }

#endif // _debug

  for (int x = timer; x >= 0; x--) {
    long long best = 0;
    for (int k = 0; k <= item_cnt; k++) {
      long long diff = 1LL * (timer - x) * k;
      if (diff > m)
        break;
      best = max(best, dp[k][m - diff]);
    }
    best += base_profit;
    query_res[x] = best;
  }

  for (int i = 0; i <= m; i++) {
    cout << query_res[i] << '\n';
  }
}
