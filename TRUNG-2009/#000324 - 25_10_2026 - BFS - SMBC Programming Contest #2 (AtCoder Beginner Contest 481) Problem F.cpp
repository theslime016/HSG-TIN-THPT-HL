#include <bits/stdc++.h>
using namespace std;

#define _debug 0

#if _debug == 1
#define debug(x) cerr << #x << ':' << (x) << ' ';
#define newline cerr << '\n';

#else
#define debug(x)
#define newline

#endif // _debug


const int maxn = 2e5 + 5;
const long long inf = 1e18;
const long long mod = 998244353;

vector<pair<int, int>> adj[maxn]; // index - value
long long dist[maxn];
int visited[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);

  #else

  #endif // _debug

  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int a, b, w;
    cin >> a >> b >> w;
    adj[a].push_back({b, w});
  }

  #if _debug == 1
  for (int i = 1; i <= n; i++) {
    debug(i);
    newline;
    for (const auto& x : adj[i]) {
      debug(x.first);
      debug(x.second);
      newline;
    }
    newline;
    newline;
  }

  #endif // _debug

  vector<vector<int>> task;
  task.push_back({1});
  dist[1] = 0;
  visited[1] = 1;
  while (!task.empty()) {
    vector<vector<int>> next_task;

    for (const auto& current_task : task) {
      for (int c = 1; c <= 9; c++) {
        vector<int> new_task;

        for (int index : current_task) {
          for (const auto& nxt : adj[index]) {
            if (visited[nxt.first]) continue;
            if (nxt.second != c) continue;

            dist[nxt.first] = ((dist[index] * 10)%mod + nxt.second)%mod;
            visited[nxt.first] = 1;
            new_task.push_back(nxt.first);
          }
        }

        if (!new_task.empty()) {
          next_task.push_back(new_task);
        }
      }

    }
    task = move(next_task);

    #if _debug == 1
    for (const auto& current_task : task) {
      for (int index : current_task) {
        debug(index);
      }
      newline;
    }


    #endif // _debug

  }

  for (int i = 2; i <= n; i++) cout << dist[i] << '\n';

}
