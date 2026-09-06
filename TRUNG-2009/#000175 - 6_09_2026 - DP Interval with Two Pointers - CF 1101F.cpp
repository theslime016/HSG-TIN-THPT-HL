#include <bits/stdc++.h>
using namespace std;

const int maxn = 405;
long long A[maxn];
long long dp[maxn][maxn];
long long ndp[maxn][maxn];

struct query {
  int l, r;
  long long cost;
  int rank;
};
vector<query> task[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    cin >> A[i];
  for (int i = 1; i <= m; i++) {
    int l, r;
    long long cost;
    int ref;
    cin >> l >> r >> cost >> ref;
    task[ref].push_back({l, r, cost, i});
  }

  long long res = 0;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      dp[i][j] = A[j] - A[i];
    }
  }

  for (const auto &x : task[0]) {
    res = max(res, dp[x.l][x.r] * x.cost);
  }

  for (int ref = 1; ref <= n; ref++) {
    for (int i = 1; i <= n; i++) {
      int k = i;
      for (int j = i; j <= n; j++) {
        while (k < j) {
          long long current = max(dp[i][k], A[j] - A[k]);
          long long next = max(dp[i][k + 1], A[j] - A[k + 1]);
          if (current > next) {
            k++;
          } else {
            break;
          }
        }
        ndp[i][j] = max(dp[i][k], A[j] - A[k]);
      }
    }

    swap(dp, ndp);
    for (const auto &x : task[ref]) {
      res = max(res, dp[x.l][x.r] * x.cost);
    }
  }
  cout << res;
}
