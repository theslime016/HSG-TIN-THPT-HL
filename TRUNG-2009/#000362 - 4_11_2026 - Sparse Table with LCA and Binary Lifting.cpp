#include <bits/stdc++.h>
using namespace std;

#if defined(__has_include) && __has_include("slime_debug_016.h")
#include "slime_debug_016.h"

#else
#define _debug 0

#endif // defined

/// MACRO
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
#define debug(...) void(0)
#define newline void(0)

#endif // _debug

const int maxn = 3e5 + 5;
const int maxlog = __lg(maxn);

int n, q;
vector<pair<int, long long>> adj[maxn]; // index - value
int up[maxn][maxlog];
long long dist[maxn][maxlog];
int timein[maxn], timeout[maxn];
int timer = 1;

void make_dfs(int index, int parent) {
  timein[index] = timer++;

  for (int exp = 1; exp < maxlog; exp++) {
    up[index][exp] = up[ up[index][exp-1] ][exp-1];
    dist[index][exp] = dist[index][exp-1] + dist[ up[index][exp-1] ][exp-1];
  }

  for (const pair<int, long long>& x : adj[index]) {
    if (x.first == parent) continue;

    up[x.first][0] = index;
    dist[x.first][0] = x.second;

    make_dfs(x.first, index);
  }

  timeout[index] = timer - 1;
}

bool is_lca(int a, int b) {
  return timein[a] <= timein[b] && timeout[a] >= timeout[b];
}

long long binary_lift(int index, int tar) {
  long long res = 0;
  for (int exp = maxlog - 1; exp >= 0; exp--) {
    int next_index = up[index][exp];
    long long d = dist[index][exp];
    if (next_index && !is_lca(next_index, tar)) {
      res += d;
      index = next_index;
    }
  }

  if (up[index][0]) res += dist[index][0];
  return res;
}

long long get_dist(int a, int b) {
  return binary_lift(a, b) + binary_lift(b, a);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else
  freopen("distance.inp", "r", stdin);
  freopen("distance.out", "w", stdout);

#endif // _debug

  int t;
  cin >> t;

  cin >> n;
  for (int i = 1; i < n; i++) {
    int a, b;
    long long w;
    cin >> a >> b >> w;
    adj[a].push_back({b, w});
    adj[b].push_back({a, w});
  }

  make_dfs(1, 0);

  #if _debug == 1
  int log_cnt = __lg(n);
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < log_cnt; j++) {
      debug(i, j, up[i][j], dist[i][j]);
    }
    newline;
  }

  int t1 = 7, t2 = 5;
  debug(binary_lift(t1, t2));
  debug(binary_lift(t2, t1));
  newline;

  #endif // _debug

  cin >> q;
  while (q--) {
    int a, b;
    cin >> a >> b;
    cout << get_dist(a, b) << '\n';
  }

}
