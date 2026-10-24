#include <bits/stdc++.h>
using namespace std;

#define _debug 0

#if _debug == 1
#define debug(x) cerr << #x << ':' << (x) << ' ';
#define newline cerr << '\n';

#else
#define debug(x)
#define newline

#endif // _debug


const int maxn = 2e5 + 5;
const int maxk = 1e6 + 5;
const int inf = 1e9;
const int maxlog = __lg(maxn);

struct SUBTASK1 {
  int n, k;
  int cand;
  vector<vector<pair<int, int>>> adj;

  void init(int n, int k, vector<vector<pair<int, int>>>&& adj) {
    this->n = n;
    this->k = k;
    this->adj = move(adj);
    this->cand = inf;
  }

  void make_dfs(int index, int parent, int current, int cnt) {
    if (current == k) cand = min(cand, cnt);
    for (const auto& x : adj[index]) {
      if (x.first == parent) continue;
      make_dfs(x.first, index, current + x.second, cnt+1);
    }
  }

  int solve() {
    for (int i = 1; i <= n; i++) {
      make_dfs(i, 0, 0, 0);
    }
    if (cand == inf) return -1;
    else return cand;
  }

} subtask1;

struct SUBTASK2 {
  int n, k;
  int timer;
  int cand;
  vector<vector<pair<int, int>>> adj;
  vector<vector<int>> up;
  vector<int> dist, node_cnt;
  vector<int> timein, timeout;

  void init(int n, int k, vector<vector<pair<int, int>>>&& adj) { /// INIT
    this->n = n;
    this->k = k;
    this->timer = 1;
    this->cand = inf;

    this->adj = move(adj);
    this->up.assign(n+1, vector<int>(maxlog+1, 0));
    this->dist.assign(n+1, 0);
    this->node_cnt.assign(n+1, 0);
    this->timein.assign(n+1, 0);
    this->timeout.assign(n+1, 0);
  }

  void make_dfs(int index, int parent) {
    timein[index] = timer++;

    for (int exp = 1; exp < maxlog; exp++) {
      up[index][exp] = up[ up[index][exp-1] ][exp-1];
    }

    for (const auto& x : adj[index]) {
      if (x.first == parent) continue;

      up[x.first][0] = index;
      dist[x.first] = dist[index] + x.second;
      node_cnt[x.first] = node_cnt[index] + 1;

      make_dfs(x.first, index);
    }

    timeout[index] = timer - 1;
  }

  bool is_lca(int a, int b) {
    return timein[a] <= timein[b] && timeout[a] >= timeout[b];
  }

  int get_lca(int a, int b) {
    if (is_lca(a, b)) return a;
    if (is_lca(b, a)) return b;

    for (int exp = maxlog - 1; exp >= 0; exp--) {
      if (!is_lca(up[a][exp], b) && up[a][exp]) {
        a = up[a][exp];
      }
    }

    for (int exp = maxlog - 1; exp >= 0; exp--) {
      if (!is_lca(up[b][exp], a) && up[b][exp]) {
        b = up[b][exp];
      }
    }

    return up[a][0];
  }

  int get_dist(int a, int b) {
    return dist[a] + dist[b] - 2*dist[get_lca(a, b)];
  }

  int get_node_cnt(int a, int b) {
    return node_cnt[a] + node_cnt[b] - 2*node_cnt[get_lca(a, b)];
  }

  int solve() { /// SOLVE
    node_cnt[1] = 1;
    make_dfs(1, 0);

    for (int i = 1; i <= n; i++) {
      for (int j = i + 1; j <= n; j++) {
        if (get_dist(i, j) == k) cand = min(cand, get_node_cnt(i, j));
      }
    }

    if (cand == inf) return -1;
    else return cand;
  }

} subtask2;

struct FULL {
  int n, k;
  int res;
  vector<vector<pair<int, int>>> adj;
  vector<int> deleted;
  vector<int> child;
  vector<int> min_edge;
  vector<int> restart;
  vector<pair<int, int>> subtree;

  void init(int n, int k, vector<vector<pair<int, int>>>&& adj) { /// INIT
    this->n = n;
    this->k = k;
    this->res = inf;

    this->adj = move(adj);
    this->deleted.assign(n+1, 0);
    this->child.assign(n+1, 0);
    this->min_edge.assign(k+1, inf);
    this->restart.reserve(n+1);
    this->subtree.reserve(n+1);

    this->min_edge[0] = 0;
  }

  int make_build(int index, int parent) {
    child[index] = 1;
    for (const auto& x : adj[index]) {
      if (x.first == parent) continue;

      if (deleted[x.first]) continue;

      make_build(x.first, index);
      child[index] += child[x.first];
    }
    return child[index];
  }

  int get_centroid(int index, int parent, int total_size) {
    for (const auto& x : adj[index]) {
      if (x.first == parent) continue;

      if (deleted[x.first]) continue;

      if (child[x.first] > total_size/2) return get_centroid(x.first, index, total_size);
    }
    return index;
  }

  void make_subtree(int index, int parent, int dist, int cnt) {
    if (dist > k) return;
    subtree.push_back({dist, cnt});
    for (const auto& x : adj[index]) {
      if (x.first == parent) continue;
      if (deleted[x.first]) continue;

      make_subtree(x.first, index, dist + x.second, cnt + 1);
    }
  }

  void dnc(int index) {
    int total_size = make_build(index, 0);
    int centroid = get_centroid(index, 0, total_size);

    for (const auto& x : adj[centroid]) {
      if (deleted[x.first]) continue;

      subtree.clear();
      make_subtree(x.first, centroid, x.second, 1);

      for (const auto& cand : subtree) { // dist - cnt
        if (cand.first <= k) res = min(res, min_edge[k - cand.first] + cand.second);
      }

      for (const auto& cand : subtree) {
        if (cand.first <= k && min_edge[cand.first] > cand.second) {
          min_edge[cand.first] = cand.second;
          restart.push_back(cand.first);
        }
      }
    }

    while (!restart.empty()) {
      min_edge[ restart.back() ] = inf;
      restart.pop_back();
    }

    deleted[centroid] = 1;
    for (const auto& x : adj[centroid]) {
      if (deleted[x.first]) continue;
      dnc(x.first);
    }
  }

  int solve() { /// SOLVE
    dnc(1);
    if (res == inf) return -1;
    else return res;
  }

} full;

int best_path(int n, int k, int (*H)[2], int* L) {
  vector<vector<pair<int, int>>> adj(n+1);

  for (int i = 0; i < n - 1; i++) {
    int a = H[i][0];
    int b = H[i][1];
    a++;
    b++;

    int w = L[i];

    adj[a].push_back({b, w});
    adj[b].push_back({a, w});
  }


  if (n <= 100 && k <= 100) {
    debug("SUBTASK1");
    newline;

    subtask1.init(n, k, move(adj));
    return subtask1.solve();
  }

  if (n <= 1'000 && k <= 1'000'000) {
    debug("SUBTASK2");
    newline;

    subtask2.init(n, k, move(adj));
    return subtask2.solve();
  }

  debug("FULL");
  newline;
  full.init(n, k, move(adj));
  return full.solve();
}


#if _debug != 0

int H[maxn][2];
int L[maxn];
void test() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n - 1; i++) {
    cin >> H[i][0] >> H[i][1] >> L[i];
  }

  cout << best_path(n, k, H, L);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  freopen("input.inp", "r", stdin);

  test();

}
#endif // _debug
