#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m, q;
  cin >> n >> m >> q;
  const long long inf = 1e18;
  vector<vector<long long>> dp(n + 1);
  dp[0].push_back(inf);
  for (int i = 1; i <= n; i++) {
    dp[i].assign(i + 1, inf);
    dp[i][i] = 0;
  }

  auto fetch = [&](int u, int v) -> long long & {
    if (u < v)
      swap(u, v);
    return dp[u][v];
  };

  for (int i = 0; i < m; i++) {
    int a, b;
    long long w;
    cin >> a >> b >> w;
    fetch(a, b) = min(fetch(a, b), w);
  }

  for (auto &x : dp) {
    for (auto &y : x) {
      ((y != inf) ? (cout << y) : (cout << "inf")) << ' ';
    }
    cout << '\n';
  }

  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (fetch(i, k) < inf && fetch(k, j) < inf)
          fetch(i, j) = min(fetch(i, j), fetch(i, k) + fetch(k, j));
      }
    }
  }

  while (q--) {
    int a, b;
    cin >> a >> b;
    if (fetch(a, b) < inf)
      cout << fetch(a, b) << '\n';
    else
      cout << -1 << '\n';
  }

  return 0;
}
