#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  string s;
  cin >> n >> m >> s;

  vector<vector<int>> adj(n);
  while (m--) {
    int a, b;
    cin >> a >> b;
    adj[--a].push_back(--b);
  }

  vector<int> state(n, 0);
  vector<std::array<int, 26>> dp(n, {0});
  int res = 0;
  auto dfs = [&](auto &self, int index) -> void {
    state[index] = 1;

    for (int x : adj[index]) {
      if (state[x] == 1) {
        cout << -1;
        exit(0);
      }

      if (!state[x]) {
        self(self, x);
      }

      for (int i = 0; i < 26; i++) {
        dp[index][i] = max(dp[index][i], dp[x][i]);
      }
    }

    state[index] = 2;
    res = max(res, ++dp[index][s[index] - 'a']);
  };

  for (int i = 0; i < n; i++) {
    if (!state[i])
      dfs(dfs, i);
  }

  cout << res;
}
