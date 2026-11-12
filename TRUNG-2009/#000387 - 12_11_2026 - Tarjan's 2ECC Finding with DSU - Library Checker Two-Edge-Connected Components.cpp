#include <bits/stdc++.h>
using namespace std;

#define _debug 1

#if _debug == 1
void log_out() {cerr << endl;}
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
vector<pair<int, int>> adj[maxn]; /// index - tag
int is_bridge[maxn];

int low[maxn], timein[maxn];
int timer = 1;
void make_dfs(int index, int tag) {
  timein[index] = timer++;
  low[index] = timein[index];

  for (const auto& x : adj[index]) {
    if (x.second == tag) continue;
    if (timein[x.first]) {
      low[index] = min(low[index], timein[x.first]);
    } else {
      make_dfs(x.first, x.second);
      low[index] = min(low[index], low[x.first]);
    }
  }

  for (const auto& x : adj[index]) {
    if (x.second == tag) continue;

    if (low[x.first] > timein[index]) {
      is_bridge[x.second] = 1;
    }
  }
}

struct DSU {
  int data[maxn];
  int bucket[maxn];
  int cc;

  void init() {
    cc = n;
    iota(data, data + maxn, 0);
    fill_n((int*)bucket, maxn, 1);
  }

  int fnd(int index) {
    if (data[index] == index) return index;
    return data[index] = fnd(data[index]);
  }

  void make_union(int a, int b) {
    a = fnd(a);
    b = fnd(b);
    if (a != b) {
      if (bucket[a] < bucket[b]) swap(a, b);
      bucket[a] += bucket[b];
      data[b] = a;
      cc--;
    }
  }

};
vector<int> twocc[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);

  #else

  #endif // _debug

  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int a, b;
    cin >> a >> b;
    a++;
    b++;
    task[i] = {a, b};
    adj[a].push_back({b, i});
    adj[b].push_back({a, i});
  }

  for (int i = 1; i <= n; i++) {
    if (!timein[i]) make_dfs(i, 0);
  }

  #if _debug == 1
  for (int i = 1; i <= n; i++) {
    debug(i, timein[i], low[i]);
  }

  #endif // _debug

  DSU dsu;
  dsu.init();
  for (int i = 1; i <= m; i++) {
    if (is_bridge[i]) continue;
    dsu.make_union(task[i].first, task[i].second);
  }

  for (int i = 1; i <= n; i++) {
    int head = dsu.fnd(i);
    twocc[head].push_back(i);
  }

  cout << dsu.cc << '\n';
  for (int i = 1; i <= n; i++) {
    if (dsu.data[i] == i) {
      cout << dsu.bucket[i] << ' ';
      for (int x : twocc[i]) cout << x - 1 << ' ';
      cout << '\n';
    }
  }

}
