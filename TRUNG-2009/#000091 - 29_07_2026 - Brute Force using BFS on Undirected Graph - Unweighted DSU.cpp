#include <bits/stdc++.h>
using namespace std;

#ifndef NDEBUG
#define NDEBUG
#endif

int n, q;
struct Edge {
  int to;
  long long w;
};

vector<vector<Edge>> adj;
pair<bool, long long> bfs(int start, int target) {
  if (start == target)
    return {true, 0};

  vector<bool> visited(n + 1, false);
  visited[start] = true;

  queue<pair<int, long long>> q;
  q.push({start, 0});

  while (!q.empty()) {
    auto [u, d] = q.front();
    q.pop();
    if (u == target)
      return {true, d};
    for (const auto &ed : adj[u]) {
      int v = ed.to;
      long long w = ed.w;
      if (!visited[v]) {
        visited[v] = true;
        q.push({v, w + d});
      }
    }
  }
  return {false, 0};
}

int main() {
  cin.tie(0)->sync_with_stdio(false);

  cin >> n >> q;
  adj.assign(n + 1, vector<Edge>());
  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int a, b;
      long long w;
      cin >> a >> b >> w;
      auto [found, dist] = bfs(a, b);
      if (found) {
        if (dist != w)
          cout << "CONFLICT" << '\n';
      } else {
        adj[a].push_back({b, w});
        adj[b].push_back({a, -w});
      }
    } else {
      int a, b;
      cin >> a >> b;
      auto [found, dist] = bfs(a, b);
      if (found) {
        cout << dist << '\n';
      } else {
        cout << "UNKNOWN" << '\n';
      }
    }
  }

  return 0;
}
