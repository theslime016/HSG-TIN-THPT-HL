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
int Cnt[MAX_N];
bool inqueue[MAX_N];
int n, m;
bool spfa(int start) {
  fill(dist, dist + MAX_N, inf);
  fill(inqueue, inqueue + MAX_N, 0);
  fill(Cnt, Cnt + MAX_N, 0);
  queue<long long> task;

  dist[start] = 0;
  inqueue[start] = true;
  task.push({start});
  while (!task.empty()) {
    auto u = task.front();
    task.pop();
    inqueue[u] = false;

    for (auto [v, w] : adj[u]) {
      if (dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;

        if (!inqueue[v]) {
          task.push({v});
          Cnt[v]++;
          inqueue[v] = true;
          if (Cnt[v] > n) {
            return false;
          }
        }
      }
    }
  }
  return true;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  // freopen("set.txt", "r", stdin);

  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int a, b, k;
    cin >> a >> b >> k;
    adj[a].push_back({b, k});
  }

  spfa(1);
  for (int i = 1; i <= n; i++) {
    cout << dist[i] << ' ';
  }

  return 0;
}
