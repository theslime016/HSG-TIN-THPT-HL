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

vector<int> adj[maxn];
stack<int> st;
int timein[maxn], low[maxn];
int root[maxn], get_rindex[maxn];
int in_stack[maxn];
int timer = 1;
int comp_cnt = 0;

void make_dfs(int index) {
  timein[index] = timer++;
  low[index] = timein[index];
  st.push(index);
  in_stack[index] = 1;

  for (int x : adj[index]) {
    if (!timein[x]) {
      make_dfs(x);
      if (in_stack[x]) low[index] = min(low[index], low[x]);
    } else if (in_stack[x]) {
      low[index] = min(low[index], timein[x]);
    }
  }

  if (low[index] == timein[index]) {
    comp_cnt++;
    get_rindex[comp_cnt] = index;
    while (!st.empty()) {
      int x = st.top();
      st.pop();
      in_stack[x] = 0;
      root[x] = comp_cnt;
      if (x == index)
        break;
    }
  }
}

vector<int> new_adj[maxn], new_rev_adj[maxn];

int proc = 0;
int walk_timer = 1;
int visited[maxn];
int dag_walk(int index, vector<int>* ptr_adj) {
  visited[index] = walk_timer;
  proc++;
  for (int x : ptr_adj[index]) {
    if (visited[x] == walk_timer) continue;
    dag_walk(x, ptr_adj);
  }
  return proc;
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
    adj[a].push_back(b);
  }

  for (int i = 1; i <= n; i++) {
    if (timein[i])
      continue;
    make_dfs(i);
  }

  if (comp_cnt == 1) {
    cout << "YES" << '\n';
    if (n == 1)
      cout << 1 << ' ' << 1;
    else
      cout << 1 << ' ' << 2;
    exit(0);
  }

  for (int i = 1; i <= n; i++) {
    for (int x : adj[i]) {
      int a = root[i], b = root[x];
      new_adj[a].push_back(b);
      new_rev_adj[b].push_back(a);
    }
  }

  auto compress_vector = [](vector<int>& A) {
    sort(A.begin(), A.end());
    A.erase(unique(A.begin(), A.end()), A.end());
  };

  for (int i = 1; i <= comp_cnt; i++) {
    compress_vector(new_adj[i]);
    compress_vector(new_rev_adj[i]);
  }

  #if _debug == 1
  for (int i = 1; i <= n; i++) {
    debug(i, root[i]);
  }
  newline;

  debug(comp_cnt);
  for (int i = 1; i <= comp_cnt; i++) {
    cerr << "COMP" << i << ' ';
    for (int x : new_adj[i]) cerr << x << ' ';
    newline;

    cerr << "REVCOMP" << i << ' ';
    for (int x : new_rev_adj[i]) cerr << x << ' ';
    newline;
    newline;
  }


  #endif // _debug


  int best = 0, rev_best = 0;
  for (int i = 1; i <= comp_cnt; i++) {
    proc = 0;
    walk_timer++;
    int c = dag_walk(i, new_adj);
    walk_timer++;
    proc = 0;
    int rc = dag_walk(i, new_rev_adj);

    #if _debug == 1
    debug(i, c, rc);
    #endif // _debug

    if (c == comp_cnt) {
      if (best > 0) {
        cout << "NO";
        exit(0);
      } else {
        best = i;
      }
    }

    if (rc == comp_cnt) {
      if (rev_best > 0) {
        cout << "NO";
        exit(0);
      } else {
        rev_best = i;
      }
    }

  }

  if (best != 0 && rev_best != 0) {
    cout << "YES" << '\n';
    cout << get_rindex[rev_best] << ' ' << get_rindex[best];
  } else {
    cout << "NO";
  }
}
