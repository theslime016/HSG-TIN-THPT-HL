#include <bits/stdc++.h>
using namespace std;

const int maxq = 2e3;
const long long inf = 1e18;

long long A[maxq];
long long dp[maxq][maxq];
int opt[maxq][maxq];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  while (cin >> n >> m) {
    int pos = 0;
    A[pos++] = 0;
    for (int i = 0; i < m; i++) {
      cin >> A[pos++];
    }
    A[pos++] = n;
    m = pos;

    memset(dp, 0, sizeof dp);
    memset(opt, 0, sizeof opt);

    for (int i = 0; i < m - 1; i++) {
      dp[i][i + 1] = 0;
      opt[i][i + 1] = i;
    }

    for (int len = 2; len < m; len++) {
      for (int i = 0; i < m - len; i++) {
        int j = i + len;
        dp[i][j] = inf;

        for (int k = opt[i][j - 1]; k <= opt[i + 1][j]; k++) {
          if (k >= j)
            break;
          long long current = dp[i][k] + dp[k][j] + abs(A[j] - A[i]);
          if (current < dp[i][j]) {
            dp[i][j] = current;
            opt[i][j] = k;
          }
        }
      }
    }
    cout << dp[0][m - 1] << '\n';
  }
}
