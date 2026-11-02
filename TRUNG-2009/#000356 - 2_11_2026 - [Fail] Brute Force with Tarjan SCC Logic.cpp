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
#define debug(...) cerr << "(" << #__VA_ARGS__ << "):\n", log_out(__VA_ARGS)
#define newline cerr << endl

#else
#define debug(...) void(0)
#define newline void(0)

#endif // _debug

const int maxn = 1e5 + 5;
const int maxedge = 2e5 + 5;

vector<int> adj[maxn];

int n, m;

int timein[maxn], head[maxn];
int timer = 1;
int proc = 0;
bool make_dfs(int index) {
  timein[index] = timer++;
  head[index] = index;
  proc++;

  for (int x : adj[index]) {
    if (!timein[x]) {
      if (!make_dfs(x)) return false;
    }
    head[index] = min(head[index], head[x]);
  }

  if (index != 1 && head[index] >= index) {
    return false;
  }
  return true;
}


bool check(int a, int b) {
  adj[a].push_back(b);
  timer = 1;
  proc = 0;
  memset(timein, 0, sizeof timein);
  bool res = make_dfs(1);
  adj[a].pop_back();

  return res && proc == n;
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
