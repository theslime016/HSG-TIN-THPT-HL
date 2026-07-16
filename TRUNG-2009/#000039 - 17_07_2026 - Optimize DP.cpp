#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  freopen("input.inp", "r", stdin);
  freopen("output.out", "w", stdout);

  const long long mod = 1e9 + 7;
  int k, n, m;
  cin >> n >> m >> k;
  string a, b;
  cin >> a >> b;
  b = '-' + b;

  vector<vector<vector<long long>>> dp(
      m + 1, vector<vector<long long>>(k + 1, vector<long long>(2, 0)));
  dp[0][0][0] = 1;
  for (char c : a) {
    for (int j = m; j > 0; j--) {
      for (int l = k; l > 0; l--) {
        long long odp = dp[j][l][1];

        if (c == b[j]) {
          dp[j][l][1] =
              (dp[j - 1][l - 1][0] + dp[j - 1][l - 1][1] + dp[j - 1][l][1]) %
              mod;
        } else {
          dp[j][l][1] = 0;
        }

        dp[j][l][0] = (dp[j][l][0] + odp) % mod;
      }
    }
  }

  cout << (dp[m][k][1] + dp[m][k][0]) % mod;

  return 0;
}
