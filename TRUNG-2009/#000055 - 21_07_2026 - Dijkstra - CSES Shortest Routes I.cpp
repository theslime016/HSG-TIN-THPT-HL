#include <bits/stdc++.h>
using namespace std;

const long long inf = 1e18;
const int MAX_N = 1e5 + 10;

// typedef pair<int, long long> edge;
struct edge {
  int vertex;
  long long ed;
};
struct cmp {
  const bool operator()(const edge &a, const edge &b) const {
    return a.ed > b.ed;
  }
};

vector<edge> adj[MAX_N];
long long dist[MAX_N];

void dijkstra(int start) {
  fill(dist, dist + MAX_N, inf);
  priority_queue<edge, vector<edge>, cmp> task;

  dist[start] = 0;
  task.push({start, 0});
  while (!task.empty()) {
    auto [u, d] = task.top();
    task.pop();
    if (d > dist[u])
      continue;
    for (auto [v, w] : adj[u]) {
      if (dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        task.push({v, dist[v]});
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  // freopen("set.txt", "r", stdin);

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int a, b, k;
    cin >> a >> b >> k;
    adj[a].push_back({b, k});
  }

  dijkstra(1);
  for (int i = 1; i <= n; i++) {
    cout << dist[i] << ' ';
  }

  return 0;
}
