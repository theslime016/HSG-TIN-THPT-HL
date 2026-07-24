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
    val = 0;
  }

  int find(int v) {
    if (v == data[v])
      return v;
    return data[v] = find(data[v]);
  }

  void collect(int v, int u, long long sum) {
    v = find(v);
    u = find(u);
    if (v != u) {
      if (size[v] < size[u])
        swap(v, u);
      data[u] = v;
      size[v] += size[u];
      max_size = max(max_size, size[v]);
      val += sum;
      group--;
    }
  }

  int sz(int v) { return size[find(v)]; }
};

struct query {
  int a, b;
  long long w;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m;
  cin >> n >> m;
  UF DSU(n);
  vector<query> q(m);
  for (int i = 0; i < m; i++) {
    cin >> q[i].a >> q[i].b >> q[i].w;
  }

  sort(q.begin(), q.end(), [](auto &u, auto &v) { return u.w < v.w; });

  for (query &x : q) {
    DSU.collect(x.a, x.b, x.w);
  }

  if (DSU.group > 1) {
    cout << "IMPOSSIBLE";
    return 0;
  }

  cout << DSU.val;

  return 0;
}
