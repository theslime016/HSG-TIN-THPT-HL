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
int n, root;
vector<int> adj[maxn];

long long fenwick[maxn];
void update(int index, int val) {
  for (; index > 0; index -= index & -index) {
    fenwick[index] += val;
  }
}

long long fetch(int index) {
  long long res = 0;
  for (; index <= n; index += index & -index) {
    res += fenwick[index];
  }
  return res;
}

long long make_dfs(int index, int parent) {
  long long res = 0;
  res += fetch(index);
  update(index, 1);

  for (int x : adj[index]) {
    if (x == parent) continue;
    res += make_dfs(x, index);
  }

  update(index, -1);
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else
  freopen("treeinv.inp", "r", stdin);
  freopen("treeinv.out", "w", stdout);

#endif // _debug

  int t;
  cin >> t;
  long long res = 0;
  cin >> n >> root;
  for (int i = 1; i <= n; i++) adj[i].clear();
  for (int i = 1; i < n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  res += make_dfs(root, 0);
  cout << res;

}
