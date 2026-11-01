#include <bits/stdc++.h>
using namespace std;

#if defined(__has_include) && __has_include("slime_debug_016.h")
#include "slime_debug_016.h"

#else
#define _debug 0

#endif // defined

#if _debug == 1
void log_out() {cerr << '\n';}
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
vector<int> adj[maxn];
int color[maxn]; // 0:blue/1:red
int proc[maxn];
deque<pair<int, int>> dq; // index - dist
int timer = 1;

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

  color[1] = 1;
  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int index;
      cin >> index;
      color[index] = 1;
    } else if (type == 2) {
      int node_index;
      cin >> node_index;

      int res = 0;

      dq.clear();
      dq.push_back({node_index, 0});
      timer++;
      while (!dq.empty()) {
        int index = dq.front().first;
        int dist = dq.front().second;
        dq.pop_front();

        if (color[index] == 1) {
          res = dist;
          break;
        }

        for (int x : adj[index]) {
          if (proc[x] == timer) continue;
          proc[x] = timer;
          dq.push_back({x, dist + 1});
        }

      }

      cout << res << '\n';

    }
  }

}
