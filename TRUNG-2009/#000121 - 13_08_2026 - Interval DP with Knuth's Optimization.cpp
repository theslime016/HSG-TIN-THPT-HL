#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  long long l;
  int n;
  cin >> l >> n;

  vector<long long> gap(n + 5, 0);
  for (int i = 1; i <= n; i++)
    cin >> gap[i];
  gap[n + 1] = l;
  // n+2 gap
  // 0 a b c d maxl

  vector<vector<long long>> dp(n + 5, vector<long long>(n + 5, LLONG_MAX));
  vector<vector<int>> opt(n + 5, vector<int>(n + 5, -1));
  for (int i = 0; i <= n + 1; i++) {
    dp[i][i + 1] = 0;
    opt[i][i + 1] = i;
  }

  for (int len = 2; len <= n + 1; len++) {
    for (int start = 0; start + len <= n + 1; start++) {
      int end = start + len;

      for (int k = opt[start][end - 1]; k <= opt[start + 1][end]; k++) {
        long long cost =
            dp[start][k] + dp[k][end] +
            1LL * (gap[end] - gap[start]) * (gap[end] - gap[start]);

        if (cost < dp[start][end]) {
          dp[start][end] = cost;
          opt[start][end] = k;
        }
      }
    }
  }

  cout << dp[0][n + 1];
}
