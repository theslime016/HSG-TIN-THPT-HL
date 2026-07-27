#include <bits/stdc++.h>
using namespace std;

struct query {
  int a, b;
  long long w;
};
vector<int> shop;
vector<query> edge;
int n, m, k;

bool check(int mask, long long &current) {
  current = 0;

  vector<int> parent(n + 1);
  vector<bool> has(n + 1, 0);
  iota(parent.begin(), parent.end(), 0LL);
  for (int x : shop) {
    has[x] = true;
  }

  auto fnd = [&](int index, auto &self) -> int {
    return index == parent[index] ? index
                                  : parent[index] = self(parent[index], self);
  };

  for (int i = 0; i < m; i++) {
    if ((mask & (1 << i))) {
      current += edge[i].w;

      int u = fnd(edge[i].a, fnd);
      int v = fnd(edge[i].b, fnd);
      if (u != v) {
        parent[v] = u;
        has[u] = has[v] | has[u];
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    if (!has[fnd(i, fnd)])
      return false;
  }
  return true;
}

int main() {
  cin.tie(0)->sync_with_stdio(false);

  freopen("input.inp", "r", stdin);
  freopen("output.out", "w", stdout);

  cin >> n >> m >> k;
  for (int i = 0; i < k; i++) {
    int x;
    cin >> x;
    shop.push_back(x);
  }

  for (int i = 0; i < m; i++) {
    int a, b;
    long long w;
    cin >> a >> b >> w;
    edge.push_back({a, b, w});
  }

  long long res = LLONG_MAX;
  for (int mask = 0; mask < (1 << m); mask++) {
    long long current = 0;
    if (check(mask, current)) {
      res = min(res, current);
    }
  }

  if (res == LLONG_MAX)
    cout << -1;
  else
    cout << res;

  return 0;
}
