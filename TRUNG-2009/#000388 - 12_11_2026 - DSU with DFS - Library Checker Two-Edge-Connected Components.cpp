#include <bits/stdc++.h>
using namespace std;

#define _debug 0

#if _debug == 1
void log_out() {
  cerr << endl;
}
template<typename H, typename... T>
void log_out(H h, T... t) {
  cerr << h << ", ";
  log_out(t...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:" << endl, log_out(__VA_ARGS__)
#define newline cerr << endl

#else
#define debug(...) (void(0))
#define newline (void(0))

#endif // _debug

const int maxn = 2e5 + 5;
int n, m;

pair<int, int> task[maxn];
vector<int> adj[maxn];

int parent[maxn], depth[maxn];
void make_dfs(int index, int parent_index) {
  parent[index] = parent_index;
  depth[index] = depth[parent_index] + 1;
  for (int x : adj[index]) {
    if (x == parent_index)
      continue;
    make_dfs(x, index);
  }
}

struct DSU {
  int data[maxn];
  int bucket[maxn];
  int cc;

  void init() {
    cc = n;
    iota(data, data + maxn, 0);
    fill_n(bucket, maxn, 1);
  }

  int fnd(int index) {
    if (data[index] == index)
      return index;
    return data[index] = fnd(data[index]);
  }

  int make_union(int a, int b) {
    a = fnd(a);
    b = fnd(b);
    if (a != b) {
      bucket[a] += bucket[b];
      data[b] = a;
      cc--;

      return true;
    }
    return false;
  }

} checker, dsu;
vector<int> tecc[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  cin >> n >> m;

  checker.init();
  int task_cnt = 0;
  for (int i = 1; i <= m; i++) {
    int a, b;
    cin >> a >> b;
    a++;
    b++;

    if (checker.make_union(a, b)) {
      adj[a].push_back(b);
      adj[b].push_back(a);
    } else {
      task[++task_cnt] = {a, b};
    }
  }

  for (int i = 1; i <= n; i++) {
    if (!parent[i])
      make_dfs(i, 0);
  }

  dsu.init();
  for (int i = 1; i <= task_cnt; i++) {
    int a = task[i].first;
    int b = task[i].second;
    while (true) {
      a = dsu.fnd(a);
      b = dsu.fnd(b);
      if (a == b)
        break;
      if (depth[a] < depth[b])
        swap(a, b);
      dsu.make_union(parent[a], a);
    }
  }

  for (int i = 1; i <= n; i++) {
    int head = dsu.fnd(i);
    tecc[head].push_back(i);
  }

  cout << dsu.cc << '\n';
  for (int i = 1; i <= n; i++) {
    if (dsu.data[i] != i)
      continue;
    cout << dsu.bucket[i] << ' ';
    for (int x : tecc[i])
      cout << x - 1 << ' ';
    cout << '\n';
  }

}
