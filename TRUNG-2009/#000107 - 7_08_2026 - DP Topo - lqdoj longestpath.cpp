#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n + 1);
  while (m--) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
  }

  vector<int> state(n + 1, 0);
  vector<int> dp(n + 1, n);
  stack<int> wait;
  int res = n;
  for (int i = 1; i <= n; i++) {
    if (state[i] != 0)
      continue;

    wait.push(i);
    while (!wait.empty()) {
      int a = wait.top();
      wait.pop();

      state[a] = 1;

      for (int x : adj[a]) {
        dp[x] = min(dp[x], dp[a] + 1);
        res = min(res, dp[x]);
        wait.push(x);
      }
    }
  }

  cout << res;
}
