#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

struct UF {
  int n;
  vector<long long> data;
  vector<long long> size;
  long long val;
  long long max_size;
  long long group;
  UF(int n) {
    this->n = n;
    data.resize(n + 1);
    iota(data.begin(), data.end(), 0LL);
    size.assign(n + 1, 1);
    max_size = 1;
    group = n;
  }

  int find(int v) {
    if (v == data[v])
      return v;
    return data[v] = find(data[v]);
  }

  void collect(int v, int u) {
    v = find(v);
    u = find(u);
    if (v != u) {
      if (size[v] < size[u])
        swap(v, u);
      data[u] = v;
      size[v] += size[u];
      max_size = max(max_size, size[v]);
      group--;
    }
  }

  int sz(int v) { return size[find(v)]; }
};

struct query {
  int a, b;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m;
  cin >> n >> m;
  UF DSU(n);
  vector<query> q(m);
  for (int i = 0; i < m; i++) {
    cin >> q[i].a >> q[i].b;
  }

  vector<pair<int, int>> res(m);
  for (int j = m - 1; j >= 0; j--) {
    DSU.collect(q[j].a, q[j].b);
    res[j] = {DSU.group, DSU.max_size};
    for (int x : DSU.data)
      cout << x << ' ';
    cout << '\n';
  }

  for (int i = 0; i < m; i++) {
    cout << res[i].first << ' ' << res[i].second << '\n';
  }

  return 0;
}
