#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n + 1);
  vector<int> in_deg(n + 1, 0);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    in_deg[v]++;
    adj[u].push_back(v);
  }

  stack<int> s;
  int parity = 0;
  for (int i = 1; i <= n; i++) {
    if (!in_deg[i])
      s.push(i);
  }

  vector<int> rank(n + 1, -1);
  int timer = 1;
  while (!s.empty()) {
    if (s.empty())
      parity = !parity;
    int index = s.top();
    s.pop();
    rank[index] = timer++;

    for (int x : adj[index]) {
      in_deg[x]--;
      if (!in_deg[x])
        s.push(x);
    }
  }

  for (int i = 1; i <= n; i++)
    cout << rank[i] << ' ';

  return 0;
}
