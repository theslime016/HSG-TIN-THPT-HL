#include <bits/stdc++.h>
using namespace std;

#define _debug 0

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
#define debug(...) (void(0))
#define newline (void(0))

#endif // _debug

const int maxn = 1e5 + 5;
const int maxedge = 2e5 + 5;
const long long inf = 1e18;

int n, m;

struct EDGE {
  int a, b;
  long long val;
} task[maxedge];
long long dist[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);

  #else

  #endif // _debug

  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> task[i].a >> task[i].b >> task[i].val;
  }

  fill_n((long long*)dist, maxn, inf);
  dist[1] = 0;
  for (int t = 1; t < n; t++) {
    for (int i = 1; i <= m; i++) {
      int a = task[i].a;
      int b = task[i].b;
      long long val = task[i].val;
      if (dist[a] != inf) {
        dist[b] = min(dist[b], dist[a] + val);
      }
    }
  }

  for (int i = 1; i <= m; i++) {
    if (dist[task[i].a] == inf) continue;
    if (dist[task[i].a] + task[i].val < dist[task[i].b]) {
      cout << "INF";
      return 0;
    }
  }

  for (int i = 1; i <= n; i++) {
    cout << dist[i] << ' ';
  }

}
