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

const int maxn = 1e5 + 5;
const int maxedge = 2e5 + 5;

int n, m;
vector<int> init_adj[maxn], init_rev_adj[maxn];
vector<int> adj[maxn], rev_adj[maxn];
int timein[maxn], timeout[maxn];
int visited[maxn];
int timer = 1;

void make_timer(int index) {
  timein[index] = timer++;

  for (int x : init_rev_adj[index]) {
    if (timein[x])
      continue;
    make_timer(x);
  }

  timeout[index] = timer - 1;
}

int timeout_index[maxn];
int root[maxn];
int get_index_root[maxn];
int component_num = 0;
void make_component(int index, int head) {
  root[index] = head;
  visited[index] = 1;

  for (int x : init_adj[index]) {
    if (visited[x])
      continue;
    make_component(x, head);
  }
}

int indeg[maxn];
int rev_indeg[maxn];
void make_condensation(int index) {
  visited[index] = 1;
  for (int x : init_adj[index]) {

    if (root[index] != root[x]) {
      debug(index, x, root[index], root[x]);
      adj[root[index]].push_back(root[x]);
      rev_adj[root[x]].push_back(root[index]);

      rev_indeg[root[index]]++;
      indeg[root[x]]++;
    }

    if (visited[x])
      continue;

    make_condensation(x);
  }
}

int proc = 0;
void make_dfs(int index) {
  proc++;

  for (int x : adj[index]) {
    make_dfs(x);
  }
}

void make_rev_dfs(int index) {
  proc++;

  for (int x : rev_adj[index]) {
    make_rev_dfs(x);
  }
}

int topo[maxn];
void make_topo() {
  if (component_num == 1) {
    cout << "YES" << '\n';
    cout << 1 << ' ' << 2;
    exit(0);
  }

  for (int i = 1; i <= component_num; i++) {
    if (adj[i].empty()) continue;
    sort(adj[i].begin(), adj[i].end());
    adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
  }

  for (int i = 1; i <= component_num; i++) {
    if (rev_adj[i].empty()) continue;
    sort(rev_adj[i].begin(), rev_adj[i].end());
    rev_adj[i].erase(unique(rev_adj[i].begin(), rev_adj[i].end()), rev_adj[i].end());
  }

  #if _debug == 1
  newline;
  for (int i = 1; i <= component_num; i++) {
    cerr << "COMP" << i << ' ';
    for (int x : adj[i]) cerr << x << ' ';
    newline;

    cerr << "REVCOMP" << i << ' ';
    for (int x : rev_adj[i]) cerr << x << ' ';
    newline;
    newline;
  }
  newline;
  #endif // _debug

  deque<int> wait;
  for (int i = 1; i <= component_num; i++) {
    if (indeg[i])
      continue;
    wait.push_back(i);
  }

  #if _debug == 1
  for (int i = 1; i <= component_num; i++) {
    debug(i, indeg[i], rev_indeg[i]);
  }

  #endif // _debug

  int ptr = 1;
  while (!wait.empty()) {
    int index = wait.front();
    wait.pop_front();

    topo[ptr++] = index;

    for (int x : adj[index]) {
      indeg[x]--;

      if (!indeg[x])
        wait.push_back(x);
    }
  }

  #if _debug == 1
  cerr << "topo: ";
  for (int i = 1; i < ptr; i++) {
    cerr << topo[i] << ' ';
  }
  newline;
  #endif // _debug

  proc = 0;
  make_dfs(topo[1]);
  if (proc < component_num) {
    cout << "NO";
    exit(0);
  }
  proc = 0;
  make_rev_dfs(topo[component_num]);
  if (proc < component_num) {
    cout << "NO";
    exit(0);
  }

  cout << get_index_root[topo[component_num]] << ' ' << get_index_root[topo[1]];

  exit(0);
}


int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int a, b;
    cin >> a >> b;
    init_adj[a].push_back(b);
    init_rev_adj[b].push_back(a);
  }

  for (int i = 1; i <= n; i++) {
    if (timein[i])
      continue;
    make_timer(i);
  }

  #if _debug == 1
  for (int i = 1; i <= n; i++) {
    debug(i, timein[i], timeout[i]);
  }
  newline;
  #endif // _debug

  iota(timeout_index, timeout_index + maxn, 0);
  sort(timeout_index + 1, timeout_index + n + 1, [&](const int x, const int y) {
    return timeout[x] > timeout[y];
  });

  for (int i = 1; i <= n; i++) {
    int fnd = timeout_index[i];
    if (visited[fnd])
      continue;
    component_num++;
    get_index_root[component_num] = fnd;
    make_component(fnd, component_num);
  }

  memset(visited, 0, sizeof visited);
  for (int i = 1; i <= n; i++) {
    int fnd = timeout_index[i];
    if (visited[fnd])
      continue;
    make_condensation(fnd);
  }

  #if _debug == 1
  debug(component_num);
  for (int i = 1; i <= n; i++) {
    debug(i, root[i]);
  }
  #endif // _debug

  make_topo();
}
