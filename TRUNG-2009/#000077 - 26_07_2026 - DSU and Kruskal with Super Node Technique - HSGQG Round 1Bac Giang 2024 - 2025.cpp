#include <bits/stdc++.h>
using namespace std;

struct que {
  int u, v;
  long long w;
};

struct uf {
  int n;
  long long sum;
  vector<int> data;
  vector<int> size;

  uf(int n) {
    this->n = n;
    sum = 0;
    data.resize(n + 1);
    iota(data.begin(), data.end(), 0LL);
    size.assign(n + 1, 1);
  }

  int find(int index) {
    if (data[index] == index)
      return index;
    return data[index] = find(data[index]);
  }

  void group(int u, int v, long long w) {
    u = find(u);
    v = find(v);
    if (u != v) {
      if (data[u] < data[v])
        swap(u, v);
      data[v] = u;
      size[u] += size[v];
      sum += w;
    }
  }

  int sz(int index) { return size[find(index)]; }
};

int main() {
  cin.tie(0)->sync_with_stdio(false);
  int n, m, k;
  cin >> n >> m >> k;

  vector<que> query;
  query.reserve(k + m);
  for (int i = 0; i < k; i++) {
    int x;
    cin >> x;
    query.push_back({0, x, 0});
  }

  for (int i = 0; i < m; i++) {
    int x, y;
    long long w;
    cin >> x >> y >> w;
    query.push_back({x, y, w});
  }

  sort(query.begin(), query.end(), [](auto &a, auto &b) { return a.w < b.w; });

  uf dsu(n);
  for (const que &q : query) {
    dsu.group(q.u, q.v, q.w);
  }

  if (dsu.sz(0) < n + 1) {
    cout << -1;
  } else {
    cout << dsu.sum;
  }

  return 0;
}
