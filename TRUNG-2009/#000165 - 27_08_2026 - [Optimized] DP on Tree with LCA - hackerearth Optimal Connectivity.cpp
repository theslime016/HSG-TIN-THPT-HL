#include <bits/stdc++.h>
using namespace std;

const int _log = 20;
const int maxn = 1e5 + 5;
vector<pair<int, long long>> adj[maxn];
int jump[maxn][_log];
int depth[maxn];
long long dp[maxn][_log];
void dfs(int index) {
  for (int exp = 1; exp < _log; exp++) {
    jump[index][exp] = jump[jump[index][exp - 1]][exp - 1];
    dp[index][exp] = max(dp[index][exp - 1], dp[jump[index][exp - 1]][exp - 1]);
  }

  for (auto &x : adj[index]) {
    if (depth[x.first])
      continue;

    depth[x.first] = depth[index] + 1;
    jump[x.first][0] = index;
    dp[x.first][0] = x.second;
    dfs(x.first);
  }
}

long long lca(int a, int b) {
  if (depth[a] < depth[b])
    swap(a, b);
  long long res = 0;
  for (int exp = _log - 1; exp >= 0; exp--) {
    if (depth[jump[a][exp]] >= depth[b]) {
      res = max(res, dp[a][exp]);
      a = jump[a][exp];
    }
  }

  if (a == b)
    return res;

  for (int exp = _log - 1; exp >= 0; exp--) {
    if (jump[a][exp] != jump[b][exp]) {
      res = max({res, dp[a][exp], dp[b][exp]});
      a = jump[a][exp];
      b = jump[b][exp];
    }
  }

  return max({res, dp[a][0], dp[b][0]});
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  for (int index = 1; index < n; index++) {
    int a, b;
    long long w;
    cin >> a >> b >> w;
    adj[a].push_back({b, w});
    adj[b].push_back({a, w});
  }

  depth[1] = 1;
  dfs(1);
  int q;
  cin >> q;
  while (q--) {
    int a, b;
    long long w;
    cin >> a >> b >> w;
    long long opt = lca(a, b);
    cout << (opt > w ? "YES\n" : "NO\n");
  }
}
