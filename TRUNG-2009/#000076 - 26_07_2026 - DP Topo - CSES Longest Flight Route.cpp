#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n + 1);
  vector<int> in_degree(n + 1, 0);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    in_degree[b]++;
    adj[a].push_back(b);
  }

  queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (in_degree[i] == 0) {
      q.push(i);
    }
  }

  const long long inf = 1e9;
  vector<int> dp(n + 1, -inf);
  vector<int> trace(n + 1, 0);
  dp[1] = 1;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v : adj[u]) {
      if (dp[u] != -inf && dp[u] + 1 > dp[v]) {
        dp[v] = dp[u] + 1;
        trace[v] = u;
      }
      in_degree[v]--;
      if (in_degree[v] == 0) {
        q.push(v);
      }
    }
  }

  if (dp[n] == -inf) {
    cout << "IMPOSSIBLE";
  } else {
    cout << dp[n] << '\n';
    int u = n;
    vector<int> res;
    res.reserve(dp[u]);
    while (u != 0) {
      res.push_back(u);
      u = trace[u];
    }
    for (int i = res.size() - 1; i >= 0; i--)
      cout << res[i] << ' ';
  }

  return 0;
}
