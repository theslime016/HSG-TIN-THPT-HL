#include <bits/stdc++.h>
using namespace std;
 
const long long mod = 1e9 + 7;
 
int main() {
  cin.tie(0)->sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n + 1);
  vector<int> indeg(n + 1, 0);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    indeg[b]++;
    adj[a].push_back(b);
  }
 
  queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (indeg[i] == 0) {
      q.push(i);
    }
  }
 
  vector<long long> dp(n + 1, 0);
  dp[1] = 1;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
 
    for (int v : adj[u]) {
      if (dp[u] != 0) {
        dp[v] = (dp[v] + dp[u]) % mod;
      }
      indeg[v]--;
      if (indeg[v] == 0) {
        q.push(v);
      }
    }
  }
 
  cout << dp[n];
 
  return 0;
}
