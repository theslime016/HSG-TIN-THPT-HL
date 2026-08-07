#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n + 1);
  while (m--) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
  }

  vector<int> state(n + 1, 0); // 0 = !visit, 1 = running, 2 = processed
  stack<int> rank;
  stack<int> wait;
  for (int i = 1; i <= n; i++) {
    if (state[i] != 0)
      continue;

    wait.push(i);
    while (!wait.empty()) {
      int a = wait.top();
      wait.pop();

      if (state[a] == 0) {
        state[a] = 1;
        wait.push(a);

        for (int x : adj[a]) {
          if (state[x] == 0) {
            wait.push(x);
          } else if (state[x] == 1) {
            cout << -1;
            return 0;
          }
        }
      } else if (state[a] == 1) {
        rank.push(a);
        state[a] = 2;
      }
    }
  }

  vector<int> ans(n + 1, -1);
  int timer = 1;
  while (!rank.empty()) {
    ans[rank.top()] = timer++;
    rank.pop();
  }

  for (int i = 1; i <= n; i++)
    cout << ans[i] << ' ';

  return 0;
}
