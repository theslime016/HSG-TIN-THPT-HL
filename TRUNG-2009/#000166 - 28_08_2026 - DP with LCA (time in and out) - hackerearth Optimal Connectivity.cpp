#include <bits/stdc++.h>
using namespace std;

const int _log = 20;
const int maxn = 1e5 + 5;
vector<pair<int, long long>> adj[maxn];
int jump[maxn][_log];
long long dp[maxn][_log];

int timer = 1;
int tin[maxn];
int tout[maxn];
void dfs(int index, int parent) {
  tin[index] = timer++;
  for (int exp = 1; exp < _log; exp++) {
    jump[index][exp] = jump[jump[index][exp - 1]][exp - 1];
    dp[index][exp] = max(dp[index][exp - 1], dp[jump[index][exp - 1]][exp - 1]);
  }

  for (auto &x : adj[index]) {
    if (x.first == parent) continue;

    jump[x.first][0] = index;
    dp[x.first][0] = x.second;
    dfs(x.first, index);
  }
  tout[index] = timer++;
}

inline bool isancestor(int a, int b) {
    if (a == 0) return true;
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

long long lca(int a, int b) {
  long long res = 0;
  for (int exp = _log - 1; exp >= 0; exp--) {
    if (!isancestor(jump[a][exp], b)) {
        res = max(res, dp[a][exp]);
        a = jump[a][exp];
    }
  }

  for (int exp = _log - 1; exp >= 0; exp--) {
    if (!isancestor(jump[b][exp], a)) {
        res = max(res, dp[b][exp]);
        b = jump[b][exp];
    }
  }

  if (!isancestor(a, b)) res = max(res, dp[a][0]);
  if (!isancestor(b, a)) res = max(res, dp[b][0]);
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  //freopen("input.inp", "r", stdin);

  int n;
  cin >> n;
  for (int index = 1; index < n; index++) {
    int a, b;
    long long w;
    cin >> a >> b >> w;
    adj[a].push_back({b, w});
    adj[b].push_back({a, w});
  }

  dfs(1, 0);
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
