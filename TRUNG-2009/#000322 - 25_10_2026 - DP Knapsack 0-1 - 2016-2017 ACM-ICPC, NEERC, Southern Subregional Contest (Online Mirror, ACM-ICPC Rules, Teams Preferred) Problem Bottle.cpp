#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e2 + 5;
pair<int, int> X[maxn];
int dp[maxn][maxn*maxn];

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  int n;
  cin >> n;

  int sum_A = 0, sum_B = 0;
  for (int i = 1; i <= n; i++) {
    cin >> X[i].first;
    sum_A += X[i].first;
  }
  for (int i = 1; i <= n; i++) {
    cin >> X[i].second;
    sum_B += X[i].second;
  }

  sort(X + 1, X + n + 1, [](const auto& x, const auto& y) {
    return x.second > y.second;
  });

  int min_bottle = 1;
  int temp = 0;
  for (; min_bottle < n; min_bottle++) {
    temp += X[min_bottle].second;
    if (temp >= sum_A) break;
  }

  memset(dp, -1, sizeof dp);

  dp[0][0] = 0;
  for (int i = 1; i <= n; i++) {
    int a = X[i].first;
    int b = X[i].second;
    for (int j = min_bottle - 1; j >= 0; j--) {
      for (int k = sum_B; k >= 0; k--) {
        if (dp[j][k] != -1) {
          dp[j + 1][k + b] = max(dp[j][k] + a, dp[j + 1][k + b]);
        }
      }
    }
  }

  int cand = 0;
  for (int k = sum_A; k <= sum_B; k++) {
    cand = max(dp[min_bottle][k], cand);
  }

  cout << min_bottle << ' ' << sum_A - cand;

}
