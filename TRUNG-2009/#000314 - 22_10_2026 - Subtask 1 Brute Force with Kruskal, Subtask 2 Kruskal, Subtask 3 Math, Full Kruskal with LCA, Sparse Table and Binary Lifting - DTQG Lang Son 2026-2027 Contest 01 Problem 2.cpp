#include <bits/stdc++.h>
using namespace std;

#define _debug 1

#if _debug == 1
#define debug(x) cerr << #x << ':' << (x) << ' ';
#define newline cerr << '\n';

#else
#define debug(x)
#define newline

#endif // _debug

const int maxn = 2e5 + 5;
const int maxedge = 3e5 + 5;
const int maxlog = __lg(maxn);
const long long inf = 1e18;

struct EDGE {
  int a, b;
  long long w;

  friend bool operator<(const EDGE& a, const EDGE& b) {
    return a.w < b.w;
  }

} edge[maxedge];

int get_index[maxedge];
long long query_res[maxedge];

vector<pair<int, long long>> adj[maxn]; // index - w
int mark[maxedge];
int up[maxn][maxlog];
int timein[maxn], timeout[maxn];
long long max_table[maxn][maxlog];
int timer = 1;

int n, m;

struct DSU {
  int n;
  int rem;
  long long total;
  vector<int> data;
  vector<int> bucket;

  DSU(int n) {
    this->n = n;
    rem = n - 1;
    total = 0;
    data.assign(n+1, 0);
    iota(data.begin(), data.end(), 0);
    bucket.assign(n+1, 1);
  }

  void reset() {
    iota(data.begin(), data.end(), 0);
    bucket.assign(n+1, 1);
    total = 0;
    rem = n - 1;
  }

  int fnd(int index) {
    if (data[index] == index) return index;
    return data[index] = fnd(data[index]);
  }

  bool proc(int a, int b, long long w) {
    a = fnd(a);
    b = fnd(b);
    if (a != b) {
      if (bucket[a] < bucket[b]) swap(a, b);
      bucket[a] += bucket[b];
      data[b] = a;
      total += w;
      rem--;
      return true;
    }
    return false;
  }
};

long long solve_subtask2() {
  DSU dsu(n);

  for (int i = 1; i <= m; i++) {
    dsu.proc(edge[i].a, edge[i].b, edge[i].w);
  }

  return dsu.total;
}

long long solve_subtask3() {
  long long cost = edge[1].w;
  long long res = cost * (n - 1);
  return res;
}

long long solve_brute(int index, DSU& dsu) {
  dsu.reset();
  dsu.proc(edge[index].a, edge[index].b, edge[index].w);
  for (int i = 1; i <= m && dsu.rem > 0; i++) {
    dsu.proc(edge[i].a, edge[i].b, edge[i].w);
  }
  return dsu.total;
}

void make_dfs(int index, int parent) {
  timein[index] = timer++;
  for (int exp = 1; exp < maxlog; exp++) {
    up[index][exp] = up[ up[index][exp-1] ][exp];
    max_table[index][exp] = max(max_table[index][exp-1],
                                max_table[ up[index][exp-1] ][exp-1]);
  }

  for (const auto& x: adj[index]) {
    if (x.first == parent) continue;
    up[x.first][0] = index;
    max_table[x.first][0] = x.second;
    make_dfs(x.first, index);
  }

  timeout[index] = timer - 1;
}

bool is_lca(int a, int b) {
  return timein[a] <= timein[b] && timeout[a] >= timeout[b];
}

void init_full(DSU& dsu) {
  for (int i = 1; i <= m; i++) {
    if (dsu.proc(edge[i].a, edge[i].b, edge[i].w)) {
      mark[i] = 1;
      adj[ edge[i].a ].push_back({edge[i].b, edge[i].w});
      adj[ edge[i].b ].push_back({edge[i].a, edge[i].w});
    }
  }

  make_dfs(1, 0);
}

long long solve_full(int index, DSU& dsu) {
  if (mark[index]) return dsu.total;

  long long cand = -inf;
  int a = edge[index].a;
  int b = edge[index].b;
  for (int exp = maxlog - 1; exp >= 0; exp--) {
    if (!is_lca(up[a][exp], b) && up[a][exp]) {
      cand = max(cand, max_table[a][exp]);
      a = up[a][exp];
    }
  }

  for (int exp = maxlog - 1; exp >= 0; exp--) {
    if (!is_lca(up[b][exp], a) && up[b][exp]) {
      cand = max(cand, max_table[b][exp]);
      b = up[b][exp];
    }
  }

  if (!is_lca(a, b)) cand = max(cand, max_table[a][0]);
  if (!is_lca(b, a)) cand = max(cand, max_table[b][0]);

  return dsu.total - cand + edge[index].w;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else
  freopen("SPANEDGE.INP", "r", stdin);
  freopen("SPANEDGE.OUT", "w", stdout);

#endif // _debug

  cin >> n >> m;
  bool subtask3 = true;
  long long temp_last = -1;
  for (int i = 1; i <= m; i++) {
    int a, b;
    long long w;
    cin >> a >> b >> w;

    if (temp_last == -1) temp_last = w;
    else if (temp_last != w) {
      temp_last = w;
      subtask3 = false;
    }

    edge[i] = {a, b, w};
  }

  iota(get_index + 1, get_index + m + 1, 1);
  sort(get_index + 1, get_index + m + 1, [&](const int x, const int y) {
    return edge[x].w < edge[y].w;
  });
  sort(edge +  1, edge + m + 1);

  if (m == n - 1) {
    debug("SUBTASK2");
    newline;
    long long res = solve_subtask2();
    for (int i = 1; i <= m; i++) {
      cout << res << '\n';
    }
    return 0;
  }

  if (subtask3) {
    debug("SUBTASK3");
    newline;
    long long res = solve_subtask3();
    for (int i = 1; i <= m; i++) {
      cout << res << '\n';
    }
    return 0;
  }


  if (n <= 200 && m <= 500) {
    debug("BRUTE");
    newline;

    DSU dsu(n);

#if _debug == 1
    for (int i = 1; i <= n; i++) {
      debug(i);
      debug(edge[i].a);
      debug(edge[i].b);
      debug(edge[i].w);
      newline;
    }
#endif // _debug

    for (int i = 1; i <= m; i++) {
      query_res[get_index[i]] = solve_brute(i, dsu);
    }

    for (int i = 1; i <= m; i++) {
      cout << query_res[i] << '\n';
    }
    return 0;
  }

  DSU dsu(n);
  init_full(dsu);

  for (int i = 1; i <= m; i++) {
    query_res[get_index[i]] = solve_full(i, dsu);
  }

  for (int i = 1; i <= m; i++) {
    cout << query_res[i] << '\n';
  }
}
