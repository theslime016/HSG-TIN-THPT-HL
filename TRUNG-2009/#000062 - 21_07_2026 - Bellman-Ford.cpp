#include <bits/stdc++.h>
using namespace std;

struct ed {
  int u, v;
  long long w;
};
vector<ed> edge;
vector<long long> dist;
const long long inf = 4e18;
int v, e;
bool Bellman_Ford(int start) {
  dist[start] = 0;
  for (int i = 0; i < v - 1; i++) {
    for (ed &A : edge) {
      if (dist[A.u] < inf && dist[A.u] + A.w < dist[A.v]) {
        dist[A.v] = dist[A.u] + A.w;
      }
    }
  }

  for (ed &B : edge) {
    if (dist[B.u] < inf && dist[B.u] + B.w < dist[B.v]) {
      return false;
    }
  }

  return true;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> v >> e;
  edge.resize(e);
  dist.assign(v + 1, inf);
  for (int i = 0; i < e; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    edge[i] = {u, v, w};
  }

  if (Bellman_Ford(1)) {
    for (int i = 1; i <= v; i++)
      cout << dist[i] << ' ';
  } else {
    cout << -1;
  }

  return 0;
}
