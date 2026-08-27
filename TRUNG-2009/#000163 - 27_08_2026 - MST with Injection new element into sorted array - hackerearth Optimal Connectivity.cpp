#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
struct edge {
  int a, b;
  long long w;

  bool operator<(const edge &other) const { return this->w < other.w; }
  bool operator>(const edge &other) const { return this->w > other.w; }
};
edge arc[maxn];

struct uf {
  vector<int> data;
  vector<int> bucket;
  long long total;
  uf(int n) {
    total = 0;
    bucket.assign(n + 1, 1);
    data.assign(n + 1, 0);
    iota(data.begin(), data.end(), 0);
  }

  int fetch(int index) {
    if (index == data[index])
      return index;
    return data[index] = fetch(data[index]);
  }

  void compress(int a, int b, long long w) {
    a = fetch(a);
    b = fetch(b);
    if (a != b) {
      if (bucket[a] < bucket[b])
        swap(a, b);
      data[b] = a;
      bucket[a] += bucket[b];
      total += w;
    }
  }

  void restart() {
    total = 0;
    fill(bucket.begin(), bucket.end(), 1);
    iota(data.begin(), data.end(), 0);
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  long long global = 0;
  for (int i = 1; i < n; i++) {
    cin >> arc[i].a >> arc[i].b >> arc[i].w;
    global += arc[i].w;
  }

  sort(arc + 1, arc + n,
       [&](const edge &x, const edge &y) { return x.operator<(y); });

  uf dsu(n);
  int q;
  cin >> q;
  while (q--) {
    dsu.restart();
    int flag = 0;
    int a, b;
    long long w;
    cin >> a >> b >> w;
    for (int i = 1; i < n; i++) {
      if (!flag && w <= arc[i].w) {
        dsu.compress(a, b, w);
        flag = 1;
      }
      dsu.compress(arc[i].a, arc[i].b, arc[i].w);
    }
    if (flag == 0) {
      dsu.compress(a, b, w);
    }

    if (global > dsu.total)
      cout << "YES" << '\n';
    else
      cout << "NO" << '\n';
  }
}
