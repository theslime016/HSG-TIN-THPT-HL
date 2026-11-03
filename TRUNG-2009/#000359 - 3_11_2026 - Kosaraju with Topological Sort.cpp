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
const int maxnode = 2e5 + 5;

int n, m;
vector<int> adj[maxn];
vector<int> rev_adj[maxn];
//vector<int> new_adj[maxn];
//vector<int> new_rev_adj[maxn];

int visited[maxn];

int topo[maxn];
int ptr = 1;

int indeg[maxn];
int outdeg[maxn];

void make_dfs(int index) {
  visited[index] = 1;

  for (int x : adj[index]) {
    if (visited[x])
      continue;
    make_dfs(x);
  }

  topo[ptr++] = index;
}

int root[maxn];
int get_index[maxn];
void make_rev_dfs(int index, int head) {
  root[index] = head;
  visited[index] = 1;

  for (int x : rev_adj[index]) {
    if (visited[x])
      continue;
    make_rev_dfs(x, head);
  }
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
    rev_adj[b].push_back(a);
  }

  for (int i = 1; i <= n; i++) {
    if (visited[i])
      continue;
    make_dfs(i);
  }

  memset(visited, 0, sizeof visited);
  int comp_num = 0;
  for (int i = n; i >= 1; i--) {
    int rindex = topo[i];
    if (visited[rindex])
      continue;
    comp_num++;
    get_index[comp_num] = rindex;
    make_rev_dfs(rindex, comp_num);
  }

  if (comp_num == 1) {
    cout << "YES" << '\n';
    if (n == 1)
      cout << 1 << ' ' << 1;
    else
      cout << 1 << ' ' << 2;
    exit(0);
  }


  for (int i = 1; i <= n; i++) {
    for (int x : adj[i]) {
      if (root[i] != root[x]) {
        int a = root[i], b = root[x]; /// a -> b;
//        new_adj[a].push_back(b);
//        new_rev_adj[b].push_back(a);


        indeg[b]++;
        outdeg[a]++;
      }
    }
  }

  int no_inarc = 0, no_outarc = 0;
  for (int i = 1; i <= comp_num; i++) {
    if (indeg[i] == 0) {
      if (no_inarc != 0) {
        cout << "NO";
        exit(0);
      } else {
        no_inarc = i;
      }
    }

    if (outdeg[i] == 0) {
      if (no_outarc != 0) {
        cout << "NO";
        exit(0);
      } else {
        no_outarc = i;
      }
    }
  }

  cout << "YES" << '\n';
  cout << get_index[no_outarc] << ' ' << get_index[no_inarc];
  exit(0);
//
//  for (int i = 1; i <= comp_num; i++) {
//    sort(new_adj[comp_num].begin(), new_adj[comp_num].end());
//    new_adj[comp_num].erase(unique(new_adj[comp_num].begin(), new_adj[comp_num].end()), new_adj[comp_num].end());
//
//    sort(new_rev_adj[comp_num].begin(), new_rev_adj[comp_num].end());
//    new_rev_adj[comp_num].erase(unique(new_rev_adj[comp_num].begin(), new_rev_adj[comp_num].end()), new_rev_adj[comp_num].end());
//  }
//
//#if _debug == 1
//  for (int i = 1; i <= comp_num; i++) {
//    cerr << "COMP" << i << ' ';
//    for (int x : new_adj[i])
//      cerr << x << ' ';
//
//    newline;
//    cerr << "REVCOMP" << i << ' ';
//    for (int x : new_rev_adj[i])
//      cerr << x << ' ';
//    newline;
//    newline;
//  }
//
//#endif // _debug
}
