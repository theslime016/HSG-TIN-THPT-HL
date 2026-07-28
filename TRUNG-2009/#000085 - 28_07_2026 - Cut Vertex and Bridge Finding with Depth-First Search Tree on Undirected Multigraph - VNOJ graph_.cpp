#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e4 + 10;
vector<pair<int, int>> adj[maxn];
int timer = 0;
int num[maxn], low[maxn];
vector<pair<int, int>> bridges;
bitset<maxn> cut_vertex{};

void dfs(int u, int p_id) {
  num[u] = low[u] = ++timer;
  int children = 0;

  for (auto &edge : adj[u]) {
    int v = edge.first;
    int id = edge.second;
    if (id == p_id)
      continue;

    if (num[v]) {
      low[u] = min(low[u], num[v]);
    }

    else {
      children++;

      dfs(v, id);
      low[u] = min(low[u], low[v]);

      if (low[v] > num[u]) {
        bridges.push_back({u, v});
      }

      if (p_id != 0 && low[v] >= num[u]) {
        cut_vertex[u] = true;
      }
    }
  }
  if (p_id == 0 && children > 1)
    cut_vertex[u] = true;
}

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back({b, i});
    adj[b].push_back({a, i});
  }

  for (int i = 1; i <= n; i++) {
    if (!num[i])
      dfs(i, 0);
  }

  cout << cut_vertex.count() << ' ' << bridges.size();

  return 0;
}
