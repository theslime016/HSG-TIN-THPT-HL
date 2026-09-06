#include <bits/stdc++.h>
using namespace std;

const int maxn = 405;
long long A[maxn];
long long dp[maxn][maxn];

struct query {
  int r;
  int ref;
  long long cost;
};
vector<query> task[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    cin >> A[i];
  while (m--) {
    int l, r;
    long long cost;
    int ref;
    cin >> l >> r >> cost >> ref;
    task[l].push_back({r, ref, cost});
  }

  long long res = 0;
  for (int l = 1; l <= n; l++) {
    for (int r = 1; r <= n; r++) {
      dp[0][r] = A[r] - A[l];
    }

    for (int k = 1; k <= n; k++) {
      int opt = l;
      for (int r = l; r <= n; r++) {
        while (opt < r) {
          long long current = max(dp[k - 1][opt], A[r] - A[opt]);
          long long next = max(dp[k - 1][opt + 1], A[r] - A[opt + 1]);
          if (current >= next) {
            opt++;
          } else {
            break;
          }
        }
        dp[k][r] = max(dp[k - 1][opt], A[r] - A[opt]);
      }
    }

    for (const auto &x : task[l]) {
      res = max(res, dp[x.ref][x.r] * x.cost);
    }
  }
  cout << res;
}
