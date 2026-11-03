#include <bits/stdc++.h>
using namespace std;

#if defined(__has_include) && __has_include("slime_debug_016.h")
#include "slime_debug_016.h"

#else
#define _debug 0

#endif // defined

/// MACRO
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
#define debug(...) void(0)
#define newline void(0)

#endif // _debug

const int maxn = 1e5 + 5;
const int maxnode = 2e5 + 5;
int n, m;
vector<int> adj[maxn];
int visited[maxn];
int proc;

void make_dfs(int index) {
  visited[index] = 1;
  proc++;

  for (int x : adj[index]) {
    if (visited[x]) continue;
    make_dfs(x);
  }
}

bool check(int a, int b) {
  adj[a].push_back(b);
  int ok = 1;

  for (int i = 1; i <= n; i++) {
    memset(visited, 0, sizeof visited);
    proc = 0;
    make_dfs(i);
    if (proc != n) {
      ok = 0;
      break;
    }
  }

  adj[a].pop_back();
  return ok;
}


int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);

  #elif _debug == 2
  freopene("input.inp", "r", stdin);

  #else

  #endif // _debug

  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
  }

  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      if (check(i, j)) {
        cout << "YES" << '\n';
        cout << i << ' ' << j;
        exit(0);
      }

      if (check(j, i)) {
        cout << "YES" << '\n';
        cout << j << ' ' << i;
        exit(0);
      }
    }
  }

  cout << "NO";

}
