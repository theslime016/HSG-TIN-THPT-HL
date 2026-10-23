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
const int inf = 1e9;
const int maxlog = __lg(maxn);
vector<pair<int, int>> adj[maxn]; // index - value

int up[maxn][maxlog], dist[maxn], node_cnt[maxn];
int timein[maxn], timeout[maxn];
int timer;

int n, k;

int best = inf;
void make_dfs(int index, int parent, int cnt, int current, int w) {
  if (current + w == k && cnt > 0) best = min(best, cnt + 1);
  for (const auto& x : adj[index]) {
    if (x.first == parent) continue;
    make_dfs(x.first, index, cnt + 1, current + w, x.second);
    make_dfs(x.first, index, 1, w, x.second);
  }
}

int solve1() { /// SOLVE 1
  make_dfs(1, 0, 0, 0, 0);
  if (best == inf) return -1;
  else return best;
}

void make_build(int index, int parent) {
  timein[index] = ++timer;

  for (int exp = 1; exp < maxlog; exp++) {
    up[index][exp] = up[ up[index][exp-1] ][exp-1];
  }

  for (const auto& x : adj[index]) {
    if (x.first == parent) continue;

    up[x.first][0] = index;
    dist[x.first] = dist[index] + x.second;
    node_cnt[x.first] = node_cnt[index] + 1;

    make_build(x.first, index);
  }

  timeout[index] = timer;
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

int solve2() { /// SOLVE 2

  node_cnt[1] = 1;
  make_build(1, 0);

  int cand = inf;
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      if (get_dist(i, j) == k) {
        cand = min(cand, get_node_cnt(i, j));
      }
    }
  }

  if (cand == inf) return -1;
  else return cand;
}

int best_path(int N, int K, int (*H)[2], int* L) {
  n = N;
  k = K;
  for (int i = 0; i < n - 1; i++) {
    int a = H[i][0];
    int b = H[i][1];
    a++;
    b++;
    int w = L[i];
    adj[a].push_back({b, w});
    adj[b].push_back({a, w});
  }

  return solve2();
}

#if _debug == 1

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

#endif
