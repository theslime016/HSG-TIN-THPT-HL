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
  cerr << '\n';
}
template<typename H, typename... T>
void log_out(H h, T... t) {
  cerr << h << ", ";
  log_out(t...);
}

#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:\n", log_out(__VA_ARGS__)
#define newline cerr << '\n'

#else
#define debug(...) void(0)
#define newline void(0)

#endif // _debug

const int maxn = 1e5 + 5;
const int maxlog = __lg(maxn) + 1;
vector<int> adj[maxn];
int task[maxn];
int ptr_task = 0;

int min_dist[maxn];
int visited[maxn];
int qtimer = 1;

void make_build() {
  deque<int> dq; // index

  qtimer++;
  for (int i = 1; i <= ptr_task; i++) {
    int index = task[i];
    visited[index] = qtimer;
    min_dist[index] = 0;
    dq.push_back(index);
  }
  ptr_task = 0;

  while (!dq.empty()) {
    int index = dq.front();
    dq.pop_front();

    for (int x : adj[index]) {
      if (visited[x] == qtimer) continue;
      if (min_dist[x] > min_dist[index] + 1) {
        min_dist[x] = min_dist[index] + 1;
        visited[x] = qtimer;
        dq.push_back(x);
      }
    }

  }
}

int timein[maxn], timeout[maxn];
int dist[maxn], up[maxn][maxlog];
int timer = 1;

void make_lca(int index, int parent) {
  timein[index] = timer++;
  up[index][0] = parent;

  for (int exp = 1; exp < maxlog; exp++) {
    up[index][exp] = up[ up[index][exp-1] ][exp-1];
  }

  for (int x : adj[index]) {
    if (x == parent) continue;
    dist[x] = dist[index] + 1;
    make_lca(x, index);
  }

  timeout[index] = timer - 1;
}

bool is_lca(int a, int b) {
  return timein[a] <= timein[b] && timeout[a] >= timeout[b];
}

int get_lca(int a, int b) {
  for (int exp = maxlog - 1; exp >= 0; exp--) {
    int nxt = up[a][exp];
    if (nxt && !is_lca(nxt, b)) {
      a = nxt;
    }
  }
  if (up[a][0] && !is_lca(a, b)) a = up[a][0];
  return a;
}

int get_dist(int a, int b) {
  return dist[a] + dist[b] - 2*dist[get_lca(a, b)];
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  int n, q;
  cin >> n >> q;
  for (int i = 1; i < n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  make_lca(1, 0);
  memcpy(min_dist, dist, sizeof dist);

#if _debug == 1
  cerr << "dist: ";
  for (int i = 1; i <= n; i++) cerr << dist[i] << ' ';
  newline;

  cerr << "min_dist: ";
  for (int i = 1; i <= n; i++) cerr << min_dist[i] << ' ';
  newline;
#endif // _debug

  int block_size = sqrt(q);
  int block_num = (q - 1)/block_size + 1;

  #if _debug == 1
  debug(block_size, block_num);
  #endif // _debug

  for (int i = 1; i <= block_num; i++) {
    int lbound = (i - 1) * block_size + 1;
    int rbound = min(q, i * block_size);

    for (int t = lbound; t <= rbound; t++) {
      int type;
      cin >> type;
      if (type == 1) {
        int index;
        cin >> index;
        task[++ptr_task] = index;
      } else if (type == 2) {
        int index;
        cin >> index;
        int res = min_dist[index];

        for (int j = 1; j <= ptr_task; j++) {
          res = min(res, get_dist(task[j], index));
        }
        cout << res << '\n';
      }
    }

    make_build();
  }


}
